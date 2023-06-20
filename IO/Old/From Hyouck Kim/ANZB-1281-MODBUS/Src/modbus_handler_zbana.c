#include "common_def.h"
#include "modbus_rtu_request_handler.h"
#include "modbus_funcs.h"
#include "modbus_util.h"
#include "version.h"
#include "externals.h"

extern void adc_task_set_gain(uint8_t ch, uint16_t gain);
extern uint16_t adc_task_get_gain(uint8_t ch);
extern void adc_task_set_offset(uint8_t ch, uint16_t offset);
extern uint16_t adc_task_get_offset(uint8_t ch);
extern void adc_task_set_filter(uint8_t ch, uint16_t filter);
extern uint16_t adc_task_get_filter(uint8_t ch);
extern void adc_task_set_power(uint8_t ch, uint8_t on);
extern uint8_t adc_task_get_power(uint8_t ch);
extern uint8_t adc_task_get_status(uint8_t ch);
extern uint16_t adc_task_get_ma(uint8_t ch);
extern uint16_t adc_task_get_rsp_delay(char port);
extern void adc_task_set_rsp_delay(char port, uint16_t delay);
extern void modbus_rtu_set_system_reset(ModbusCTX* ctx);

#define HI_BYTE(w)      ((uint8_t)((w >> 8) &0xff))
#define LO_BYTE(w)      ((uint8_t)(w & 0xff))

#define BUFFER_TO_U16(b)  ((uint16_t)b[0] << 8 | (uint16_t)b[1])
#define U16_TO_BUFFER(w, b)       \
  b[0] = HI_BYTE(w);              \
  b[1] = LO_BYTE(w);

MBErrorCode
zbana_modbus_user_coil_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNCoils, MBRegisterMode eMode)
{
  uint16_t reg_address,
           end_address;
  uint8_t  ch,
           status,
           bitNdx;
  static const modbus_address_range_t ranges[] = 
  {
    {
      .min = 1000, 
      .max = 1011 
    },
    {
      .min = 40000,
      .max = 40000
    },
  };

  reg_address = usAddress;
  end_address = usAddress + usNCoils - 1;

  if(modbus_check_address_range(reg_address, end_address, ranges, sizeof(ranges)/sizeof(modbus_address_range_t)) == FALSE)
  {
    return MB_ENOREG;
  }
  
  for(bitNdx = 0; reg_address <= end_address; reg_address++, bitNdx++)
  {
    if(reg_address >= 1000 && reg_address <= 1011)
    {
      // ch0-ch12 power
      ch = (uint8_t)(reg_address - 1000);

      if(eMode == MB_REG_READ)
      {
        status = adc_task_get_power(ch);
        xMBUtilSetBits(pucRegBuffer, bitNdx, 1, status ? 1 : 0);
      }
      else
      {
        status = xMBUtilGetBits(pucRegBuffer, bitNdx, 1);
        adc_task_set_power(ch, status);
      }
    }
    else if(reg_address == 40000)
    {
      // eeprom reset
      if(eMode == MB_REG_READ)
      {
        // always 0
        xMBUtilSetBits(pucRegBuffer, 0, 1, 0);
      }
      else
      {
        status = xMBUtilGetBits(pucRegBuffer, 0, 1);
        if(status == 1)
        {
          WriteEEPROMByte(0xfff, 0xbb);
          modbus_rtu_set_system_reset(ctx);
        }
      }
    }
    else
    {
      // bug if we reach here
      return MB_ENOREG;
    }
  }

  return MB_ENOERR;
}

MBErrorCode
zbana_modbus_user_holding_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, MBRegisterMode eMode)
{
  uint16_t  reg_address,
            end_address;
  uint16_t  val;
  uint8_t   ch;
  uint8_t*  buffer = (uint8_t*)pucRegBuffer;
  static const modbus_address_range_t ranges[] = 
  {
    {
      .min = 1000, 
      .max = 1035 
    },
    {
      .min = 20000,
      .max = 20001,
    },
    {
      .min = 32000,
      .max = 32000,
    }
  };

  reg_address = usAddress;
  end_address = usAddress + usNRegs - 1;

  if(modbus_check_address_range(reg_address, end_address, ranges, sizeof(ranges)/sizeof(modbus_address_range_t)) == FALSE)
  {
    return MB_ENOREG;
  }

  for(; reg_address <= end_address; reg_address++)
  {
    if(reg_address >= 1000 && reg_address <= 1011)
    {
      // gain
      ch = (uint8_t)(reg_address - 1000);

      if(eMode == MB_REG_READ)
      {
        val = adc_task_get_gain(ch);
        U16_TO_BUFFER(val, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);
        adc_task_set_gain(ch, val);
      }
    }
    else if(reg_address >= 1012 && reg_address <= 1023)
    {
      // offset
      ch = (uint8_t)(reg_address - 1012);

      if(eMode == MB_REG_READ)
      {
        val = adc_task_get_offset(ch);
        U16_TO_BUFFER(val, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);
        adc_task_set_offset(ch, val);
      }
    }
    else if(reg_address >= 1024 && reg_address <= 1035)
    {
      // filter
      ch = (uint8_t)(reg_address - 1024);

      if(eMode == MB_REG_READ)
      {
        val = adc_task_get_filter(ch);
        U16_TO_BUFFER(val, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);
        adc_task_set_filter(ch, val);
      }
    }
    else if(reg_address >= 20000 && reg_address <= 20001)
    {
      char port = reg_address - 20000;

      // response delay
      if(eMode == MB_REG_READ)
      {
        val = adc_task_get_rsp_delay(port);
        U16_TO_BUFFER(val, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);
        adc_task_set_rsp_delay(port, val);
      }
    }
    else if(reg_address == 32000)
    {
      // running mode
      if(eMode == MB_REG_READ)
      {
        // application mode
        U16_TO_BUFFER(1, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);
        if (val == 0)
        {
          WriteEEPROMByte(0xfff, 0xaa);
          modbus_rtu_set_system_reset(ctx);
        }
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

MBErrorCode
zbana_modbus_user_input_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs)
{
  uint16_t  reg_address,
            end_address;
  uint16_t  val;
  uint8_t   ch;
  uint8_t*  buffer = (uint8_t*)pucRegBuffer;
  static const modbus_address_range_t ranges[] = 
  {
    {
      .min = 1000, 
      .max = 1011 
    },
    {
      .min = 30000,
      .max = 30000,
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
    if(reg_address >= 1000 && reg_address <= 1011)
    {
      // 4-20ma input
      ch = (uint8_t)(reg_address - 1000);

      val = adc_task_get_ma(ch);
      U16_TO_BUFFER(val, buffer);
    }
    else if(reg_address == 30000)
    {
      // version
      U16_TO_BUFFER(PROG_VERSION, buffer);
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

MBErrorCode
zbana_modbus_user_discrete_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNDiscrete)
{
  uint16_t reg_address,
           end_address;
  uint8_t  ch,
           status,
           bitNdx;
  static const modbus_address_range_t ranges[] = 
  {
    {
      .min = 1000, 
      .max = 1011 
    }
  };

  reg_address = usAddress;
  end_address = usAddress + usNDiscrete - 1;

  if(modbus_check_address_range(reg_address, end_address, ranges, sizeof(ranges)/sizeof(modbus_address_range_t)) == FALSE)
  {
    return MB_ENOREG;
  }
  
  for(bitNdx = 0; reg_address <= end_address; reg_address++, bitNdx++)
  {
    if(reg_address >= 1000 && reg_address <= 1011)
    {
      // ch0-ch12 status
      ch = (uint8_t)(reg_address - 1000);

      //
      // XXX status 0 is okay. I know it's not even funny.
      // -hkim-
      //
      status = adc_task_get_status(ch);
      xMBUtilSetBits(pucRegBuffer, bitNdx, 1, status == 0 ? 1 : 0);
    }
    else
    {
      // bug if we reach here
      return MB_ENOREG;
    }
  }

  return MB_ENOERR;
}
