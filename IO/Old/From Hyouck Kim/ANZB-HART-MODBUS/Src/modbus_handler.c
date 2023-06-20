#include <math.h>
#include "common_def.h"
#include "hart_common.h"
#include "modbus_rtu_request_handler.h"
#include "modbus_funcs.h"
#include "modbus_util.h"
#include "version.h"
#include "externals.h"

#define HI_BYTE(w)      ((uint8_t)((w >> 8) &0xff))
#define LO_BYTE(w)      ((uint8_t)(w & 0xff))

#define BUFFER_TO_U16(b)  ((uint16_t)b[0] << 8 | (uint16_t)b[1])
#define U16_TO_BUFFER(w, b)       \
  b[0] = HI_BYTE(w);              \
  b[1] = LO_BYTE(w);


extern void modbus_rtu_set_system_reset(ModbusCTX* ctx);
extern void EEPROMMarkEnterBootloader(void);

MBErrorCode
modbus_user_coil_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNCoils, MBRegisterMode eMode)
{
  uint16_t        reg_address,
                  end_address;
  uint8_t         ch,
                  status,
                  bitNdx;
  HartChannel*    chnl;
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
        chnl = hart_channel_get_with_lock((hart_channel_t)ch);
        xMBUtilSetBits(pucRegBuffer, bitNdx, 1,
            chnl->power_status == HartChannelPowerStatus_ON ? 1 : 0);
        hart_channel_put_with_unlock(chnl);
      }
      else
      {
        status = xMBUtilGetBits(pucRegBuffer, bitNdx, 1);
        hart_channel_power_on_off((hart_channel_t)ch, status);
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
modbus_user_input_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs)
{
  uint16_t        reg_address,
                  end_address;
  uint16_t        val;
  uint8_t         ch,
                  reg_kind;
  uint8_t*        buffer = (uint8_t*)pucRegBuffer;
  HartChannel*    chnl;
  static const modbus_address_range_t ranges[] = 
  {
    {
      .min = 1000,
      .max = 1035
    },
    {
      .min = 30000,
      .max = 30000,
    },
    {
      .min = 40000,
      .max = 40000 + 119,
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
    if(reg_address >= 1000 && reg_address <= 1035)
    {
      ch = (uint8_t)((reg_address - 1000)/3);
      reg_kind = (reg_address - 1000) % 3;

      chnl = hart_channel_get_with_lock((hart_channel_t)ch);
      switch(reg_kind)
      {
      case 0:   // distance
        if (chnl->status != HartChannelStatus_Responding ||
            chnl->power_status == HartChannelPowerStatus_OFF)
        {
          val = 0xffff;
        }
        else
        {
          val = (uint16_t)(floor(chnl->distance * 1000 + 0.5f));
        }
        break;

      case 1:   // level
        if (chnl->status != HartChannelStatus_Responding ||
            chnl->power_status == HartChannelPowerStatus_OFF)
        {
          val = 0xffff;
        }
        else
        {
          val = (uint16_t)(floor(chnl->level * 1000 + 0.5f));
        }
        break;

      default:  // measured mA feedback
        //
        // ma_feedback is in Ampere unit
        //
        val = (uint16_t)(floor(chnl->ma_feedback * 1000 * 100 + 0.5f));
        break;
      }
      hart_channel_put_with_unlock(chnl);

      U16_TO_BUFFER(val, buffer);
    }
    else if(reg_address == 30000)
    {
      // version
      U16_TO_BUFFER(PROG_VERSION, buffer);
    }
    else if(reg_address >= 40000 && reg_address <=  (40000 + 119))
    {
      ch = (uint8_t)((reg_address - 40000)/10);
      reg_kind = (uint8_t)(reg_address % 10);

      val = 0;
      chnl = hart_channel_get_with_lock((hart_channel_t)ch);
      switch(reg_kind)
      {
      case 0: // rx_invalid_msg high word
        val = (uint16_t)(chnl->rx_invalid_msg >> 16) & 0xffff;
        break;

      case 1: // rx_invalid_msg low word
        val = (uint16_t)(chnl->rx_invalid_msg >> 0) & 0xffff;
        break;

      case 2: // rx_csum_err high word
        val = (uint16_t)(chnl->rx_csum_err >> 16) & 0xffff;
        break;

      case 3: // rx_csum_err low word
        val = (uint16_t)(chnl->rx_csum_err >> 0) & 0xffff;
        break;

      case 4: // rx_timeout high word
        val = (uint16_t)(chnl->rx_timeout >> 16) & 0xffff;
        break;

      case 5: // rx_timeout low word
        val = (uint16_t)(chnl->rx_timeout >> 0) & 0xffff;
        break;

      case 6: // total_reqs high word
        val = (uint16_t)(chnl->total_reqs >> 16) & 0xffff;
        break;

      case 7: // total_reqs low word
        val = (uint16_t)(chnl->total_reqs >> 0) & 0xffff;
        break;

      case 8: // total_success high word
        val = (uint16_t)(chnl->total_success >> 16) & 0xffff;
        break;

      case 9: // total_success high word
        val = (uint16_t)(chnl->total_success >> 0) & 0xffff;
        break;
      }
      hart_channel_put_with_unlock(chnl);
      U16_TO_BUFFER(val, buffer);
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
modbus_user_discrete_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNDiscrete)
{
  uint16_t          reg_address,
                    end_address;
  uint8_t           ch,
                    bitNdx;
  HartChannelStatus status;
  HartChannel*      chnl;
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

      chnl = hart_channel_get_with_lock((hart_channel_t)ch);
      if (chnl->power_status == HartChannelPowerStatus_ON)
      {
        status = chnl->status;
      }
      else
      {
        status = HartChannelStatus_No_Response;
      }
      hart_channel_put_with_unlock(chnl);

      xMBUtilSetBits(pucRegBuffer, bitNdx, 1, status == HartChannelStatus_Responding ? 1 : 0);
    }
    else
    {
      // bug if we reach here.
      return MB_ENOREG;
    }
  }

  return MB_ENOERR;
}

MBErrorCode
modbus_user_holding_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, MBRegisterMode eMode)
{
  uint16_t  reg_address,
            end_address;
  uint16_t  val;
  uint8_t*  buffer = (uint8_t*)pucRegBuffer;
  static const modbus_address_range_t ranges[] = 
  {
    {
      .min = 20000,
      .max = 20000,
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
    if(reg_address == 20000)
    {
      // response delay
      if(eMode == MB_REG_READ)
      {
        val = hart_get_rsp_delay();
        U16_TO_BUFFER(val, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);
        hart_set_rsp_delay(val);
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
