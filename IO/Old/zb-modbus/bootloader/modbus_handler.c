#ifdef __ATMEGA_1280__
#include	"iom1280.h"
#endif

#ifdef __ATMEGA_1281__
#include	"iom1281.h"
#endif

#include <inavr.h>

#include "common_def.h"
#include "modbus_funcs.h"
#include "modbus_util.h"

#include "flash.h"
#include "timer.h"
#include "events.h"

#define HI_BYTE(w)      ((uint8_t)((w >> 8) &0xff))
#define LO_BYTE(w)      ((uint8_t)(w & 0xff))

#define BUFFER_TO_U16(b)  ((uint16_t)b[0] << 8 | (uint16_t)b[1])
#define U16_TO_BUFFER(w, b)       \
  b[0] = HI_BYTE(w);              \
  b[1] = LO_BYTE(w);

#define MAX_CHUNK_SIZE        FLASH_PAGE_SIZE

#define VERSION   100

extern unsigned char read_boot_eeprom(void);
extern void write_eeprom(unsigned short addr, unsigned char data);

static uint16_t   _flash_addr;
static uint8_t    _chunk[MAX_CHUNK_SIZE];

MBErrorCode
modbus_user_holding_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, MBRegisterMode eMode)
{
  uint16_t  reg_address,
            end_address;
  uint16_t  val;
  uint8_t*  buffer = (uint8_t*)pucRegBuffer;
  static const modbus_address_range_t ranges[] = 
  {
    //  address register
    {
      .min = 30000,
      .max = 30000,
    },
    // data register: 256 bytes
    {
      .min = 31000,
      .max = 31000 + MAX_CHUNK_SIZE / 2 - 1,
    },
    // boot or app mode register
    {
      .min = 32000,
      .max = 32000,
    },
    // write flash command
    {
      .min = 33000,
      .max = 33000,
    },
    // version
    {
      .min = 34000,
      .max = 34000,
    },
  };

  reg_address = usAddress;
  end_address = usAddress + usNRegs - 1;
  
  if(modbus_check_address_range(reg_address, end_address, ranges, sizeof(ranges)/sizeof(modbus_address_range_t)) == FALSE)
  {
    return MB_ENOREG;
  }

  for(; reg_address <= end_address; reg_address++)
  {
    if (reg_address == 30000)
    {
      // address register
      if(eMode == MB_REG_READ)
      {
        U16_TO_BUFFER(_flash_addr, buffer);
      }
      else
      {
        _flash_addr = BUFFER_TO_U16(buffer);
      }
    }
    else if (reg_address >= 31000 && reg_address <= (31000 + MAX_CHUNK_SIZE / 2 - 1))
    {
      // chunk register
      uint8_t ndx = reg_address - 31000;

      // low address should go low, high address should go high
      // so chunk register is little endian in 16 bit sense
      if(eMode == MB_REG_READ)
      {
        buffer[0] = _chunk[ndx*2];
        buffer[1] = _chunk[ndx*2 + 1];
      }
      else
      {
        _chunk[ndx*2    ] = buffer[0];
        _chunk[ndx*2 + 1] = buffer[1];
      }
    }
    else if(reg_address == 32000)
    {
      // boot or app mode register
      if(eMode == MB_REG_READ)
      {
        // 0 is boot mode
        U16_TO_BUFFER(0, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);

        if (val == 1)
        {
          __disable_interrupt();
          if (read_boot_eeprom() != 0xff)
          {
            //
            // make that we are done with flashing
            //
            write_eeprom(EEPROM_BOOT_FLAG_ADDR, 0xff);
          }
          __enable_interrupt();

          // schedule system reset in 250ms
          start_timer(timer_num_2, 250, EVENTS_FLAG_RESET);
        }
      }
    }
    else if(reg_address == 33000)
    {
      // flash command register

      if(eMode == MB_REG_READ)
      {
        // always 0
        U16_TO_BUFFER(0, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);

        if (val == 1)
        {
          //
          // program flash
          //
          uint32_t addr = _flash_addr * FLASH_PAGE_SIZE;

          __disable_interrupt();
          if (read_boot_eeprom() != 0xaa)
          {
            // mark flashing in progress so that
            // board comes into bootloader mode
            // in case of power failure in the middle of
            // programming
            write_eeprom(EEPROM_BOOT_FLAG_ADDR, 0xaa);
          }
          __enable_interrupt();
          
          flash_erase(addr);
          if(flash_program(addr, _chunk, 256) == 0)
          {
            return MB_EIO;
          }

        }
        else if(val == 2)
        {
          //
          // load flash
          //
          uint32_t addr = _flash_addr * FLASH_PAGE_SIZE;
          
          flash_read(addr, _chunk, 256);
        }
      }
    }
    else if(reg_address == 34000)
    {
      // version
      if(eMode == MB_REG_READ)
      {
        U16_TO_BUFFER(VERSION, buffer);
      }
    }
    else
    {
      // bug if we reach here
      return MB_ENOREG;
    }
    buffer += 2;
  }

  return MB_ENOERR;
}
