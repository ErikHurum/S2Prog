#include "common_def.h"
#include "modbus_rtu_request_handler.h"
#include "modbus_funcs.h"
#include "modbus_util.h"
#include "version.h"
#include "externals.h"

typedef struct
{
  int16_t   offset;
  int16_t   gain;
} off_gain_reg_t;

typedef struct
{
  uint8_t   p;
  uint8_t   t;
  uint8_t   o;
} filter_reg_t;

extern OS_RSEMA    rs485_tx_lock[2];

extern void modbus_rtu_set_system_reset(ModbusCTX* ctx);

extern void rs485_task_set_power(uint8_t ch, uint8_t on);
extern uint8_t rs485_task_get_power(uint8_t ch);
extern uint8_t rs485_task_get_sensor_type(uint8_t ch);
extern void rs485_task_set_sensor_type(uint8_t ch, uint8_t sensor_type);
extern void rs485_task_set_rsp_delay(uint8_t port, uint16_t delay);
extern uint16_t rs485_task_get_rsp_delay(uint8_t port);
extern uint8_t rs485_task_get_comm_status(uint8_t port);
extern uint8_t rs485_task_get_channel_status(uint8_t port, uint8_t ch);
extern int16_t rs485_task_get_channel_value(uint8_t port, uint8_t ch);
extern int16_t rs485_task_get_channel_raw_value(uint8_t port, uint8_t ch);
extern int16_t rs485_task_get_channel_cal_value(uint8_t port, uint8_t ch);

#define HI_BYTE(w)      ((uint8_t)((w >> 8) &0xff))
#define LO_BYTE(w)      ((uint8_t)(w & 0xff))

#define BUFFER_TO_U16(b)  ((uint16_t)b[0] << 8 | (uint16_t)b[1])
#define U16_TO_BUFFER(w, b)       \
  b[0] = HI_BYTE(w);              \
  b[1] = LO_BYTE(w);

static off_gain_reg_t _offGainReg[2][14];
static uint8_t _setupReg[2][14];
static filter_reg_t _filterReg[2];

static void
rs485_task_queue_anp1_request_and_wait(uint8_t mux)
{
  uint16_t count = 0;

  TData.RS4.ToTargetBuffer[mux][0] = true;

  // 3 second timeout
  while(TData.RS4.ToTargetBuffer[mux][0] == true && count < 300)
  {
    OS_Delay(10);
    count++;
  }
  
  // just to make sure
  TData.RS4.ToTargetBuffer[mux][0] = false;
}

static void
do_ansgcnv_setup(uint8_t port, uint8_t org_uart)
{
  #define ANP1_SND_SET_UP   20
  uint8_t mux = port <= 3 ? 0 : 1;
  uint8_t ndx = 0;

  OS_Use(&rs485_tx_lock[mux]);

  // 0 : true/false flag
  // 1 : 485 port (0-8)
  // 2:  number of bytes
  //
  TData.RS4.ToTargetBuffer[mux][1] = port; // RS45 channel

  // request packet
  TData.RS4.ToTargetBuffer[mux][3 + ndx++] = ANP1_SND_SET_UP;   // command
  TData.RS4.ToTargetBuffer[mux][3 + ndx++] = 15;   // length
  for(uint8_t i = 0; i < 14; i++)
  {
    TData.RS4.ToTargetBuffer[mux][3 + ndx++] = _setupReg[org_uart][i];
  }

  TData.RS4.ToTargetBuffer[mux][3 + ndx++] = 0x01; // non-zero updates eeprom

  TData.RS4.ToTargetBuffer[mux][2] = ndx; // number of total bytes including command & NoB

  // technically this should be the last
  // for proper synchronization
  rs485_task_queue_anp1_request_and_wait(mux);

  OS_Unuse(&rs485_tx_lock[mux]);
}

static void
do_ansgcnv_update_filter(uint8_t port, uint8_t org_uart)
{
  #define ANP1_SND_FILTER	    26
  uint8_t mux = port <= 3 ? 0 : 1;
  uint8_t ndx = 0;

  OS_Use(&rs485_tx_lock[mux]);
  TData.RS4.ToTargetBuffer[mux][1] = port; // RS45 channel

  // request packet
  TData.RS4.ToTargetBuffer[mux][3 + ndx++] = ANP1_SND_FILTER;   // command
  TData.RS4.ToTargetBuffer[mux][3 + ndx++] = 3;   // length

  TData.RS4.ToTargetBuffer[mux][3 + ndx++] = _filterReg[org_uart].p;
  TData.RS4.ToTargetBuffer[mux][3 + ndx++] = _filterReg[org_uart].t;
  TData.RS4.ToTargetBuffer[mux][3 + ndx++] = _filterReg[org_uart].o;

  TData.RS4.ToTargetBuffer[mux][2] = ndx; // number of total bytes including command & NoB

  rs485_task_queue_anp1_request_and_wait(mux);

  OS_Unuse(&rs485_tx_lock[mux]);
}

static void
do_ansgcnv_update_off_gain(uint16_t mask, uint8_t port, uint8_t org_uart)
{
  #define ANP1_SND_OFF_GAIN   19

  uint8_t mux = port <= 3 ? 0 : 1;
  uint8_t ndx = 0;

  OS_Use(&rs485_tx_lock[mux]);
  TData.RS4.ToTargetBuffer[mux][1] = port; // RS45 channel

  // request packet
  TData.RS4.ToTargetBuffer[mux][3 + ndx++] = ANP1_SND_OFF_GAIN;   // command
  TData.RS4.ToTargetBuffer[mux][3 + ndx++] = 0;   // length

  for (uint8_t i = 0; i < 14; i++)
  {
    if (mask & (1 << i))
    {
      TData.RS4.ToTargetBuffer[mux][3 + ndx++] = i;   // channel

      TData.RS4.ToTargetBuffer[mux][3 + ndx++] = (uint8_t)((_offGainReg[org_uart][i].offset >> 8) & 0xff);   // offset high
      TData.RS4.ToTargetBuffer[mux][3 + ndx++] = (uint8_t)((_offGainReg[org_uart][i].offset >> 0) & 0xff);   // offset low

      TData.RS4.ToTargetBuffer[mux][3 + ndx++] = (uint8_t)((_offGainReg[org_uart][i].gain >> 8) & 0xff);   // gain high
      TData.RS4.ToTargetBuffer[mux][3 + ndx++] = (uint8_t)((_offGainReg[org_uart][i].gain >> 0) & 0xff);   // gain low
    }
  }

  TData.RS4.ToTargetBuffer[mux][4] = ndx - 2; // final length of sub command frame

  TData.RS4.ToTargetBuffer[mux][2] = ndx; // number of total bytes including command & NoB

  rs485_task_queue_anp1_request_and_wait(mux);

  OS_Unuse(&rs485_tx_lock[mux]);
}

MBErrorCode
zb485_modbus_user_coil_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNCoils, MBRegisterMode eMode)
{
  uint16_t reg_address,
           end_address;
  uint8_t  ch,
           status,
           bitNdx;
  static const modbus_address_range_t ranges[] = 
  {
    {
      .min = 10000, 
      .max = 10007 
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
    if(reg_address >= 10000 && reg_address <= 10007)
    {
      // port power
      ch = (uint8_t)(reg_address - 10000);

      if(eMode == MB_REG_READ)
      {
        status = rs485_task_get_power(ch);
        xMBUtilSetBits(pucRegBuffer, bitNdx, 1, status ? 1 : 0);
      }
      else
      {
        status = xMBUtilGetBits(pucRegBuffer, bitNdx, 1);
        rs485_task_set_power(ch, status);
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
zb485_modbus_user_holding_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, MBRegisterMode eMode)
{
  uint16_t  reg_address,
            end_address;
  uint16_t  val;
  uint8_t*  buffer = (uint8_t*)pucRegBuffer;
  static const modbus_address_range_t ranges[] = 
  {
    // port sensor type
    { .min = 10000, .max = 10007, },
    // response delay
    { .min = 20000, .max = 20001, },
    // running mode
    { .min = 32000, .max = 32000, },
    // offset
    { .min = 1300, .max = 1313, },
    { .min = 2300, .max = 2313, },
    { .min = 3300, .max = 3313, },
    { .min = 4300, .max = 5313, },
    { .min = 5300, .max = 5313, },
    { .min = 6300, .max = 6313, },
    { .min = 7300, .max = 7313, },
    { .min = 8300, .max = 8313, },
    // gain
    { .min = 1320, .max = 1333, },
    { .min = 2320, .max = 2333, },
    { .min = 3320, .max = 3333, },
    { .min = 4320, .max = 5333, },
    { .min = 5320, .max = 5333, },
    { .min = 6320, .max = 6333, },
    { .min = 7320, .max = 7333, },
    { .min = 8320, .max = 8333, },
    // update offset/gain
    { .min = 1340, .max = 1340, },
    { .min = 2340, .max = 2340, },
    { .min = 3340, .max = 3340, },
    { .min = 4340, .max = 4340, },
    { .min = 5340, .max = 5340, },
    { .min = 6340, .max = 6340, },
    { .min = 7340, .max = 7340, },
    { .min = 8340, .max = 8340, },
    // setup
    { .min = 1350, .max = 1363, },
    { .min = 2350, .max = 2363, },
    { .min = 3350, .max = 3363, },
    { .min = 4350, .max = 5363, },
    { .min = 5350, .max = 5363, },
    { .min = 6350, .max = 6363, },
    { .min = 7350, .max = 7363, },
    { .min = 8350, .max = 8363, },
    // update setup
    { .min = 1370, .max = 1370, },
    { .min = 2370, .max = 2370, },
    { .min = 3370, .max = 3370, },
    { .min = 4370, .max = 4370, },
    { .min = 5370, .max = 5370, },
    { .min = 6370, .max = 6370, },
    { .min = 7370, .max = 7370, },
    { .min = 8370, .max = 8370, },
    // filter and filter update
    { .min = 1400, .max = 1403 },
    { .min = 2400, .max = 2403 },
    { .min = 3400, .max = 3403 },
    { .min = 4400, .max = 4403 },
    { .min = 5400, .max = 5403 },
    { .min = 6400, .max = 6403 },
    { .min = 7400, .max = 7403 },
    { .min = 8400, .max = 8403 },
  };

  reg_address = usAddress;
  end_address = usAddress + usNRegs - 1;

  if(modbus_check_address_range(reg_address, end_address, ranges, sizeof(ranges)/sizeof(modbus_address_range_t)) == FALSE)
  {
    return MB_ENOREG;
  }

  for(; reg_address <= end_address; reg_address++)
  {
    if(reg_address >= 10000 && reg_address <= 10007)
    {
      // port sensor type
      char port = reg_address - 10000;

      if(eMode == MB_REG_READ)
      {
        val = rs485_task_get_sensor_type(port);
        U16_TO_BUFFER(val, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer) & 0x03;
        rs485_task_set_sensor_type(port, (uint8_t)val);
      }
    }
    else if(reg_address >= 20000 && reg_address <= 20001)
    {
      char port = reg_address - 20000;

      // response delay
      if(eMode == MB_REG_READ)
      {
        val = rs485_task_get_rsp_delay(port);
        U16_TO_BUFFER(val, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);
        rs485_task_set_rsp_delay(port, val);
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
    else if((reg_address >= 1300 && reg_address <= 1313) ||
            (reg_address >= 2300 && reg_address <= 2313) ||
            (reg_address >= 3300 && reg_address <= 3313) ||
            (reg_address >= 4300 && reg_address <= 4313) ||
            (reg_address >= 5300 && reg_address <= 5313) ||
            (reg_address >= 6300 && reg_address <= 6313) ||
            (reg_address >= 7300 && reg_address <= 7313) ||
            (reg_address >= 8300 && reg_address <= 8313))
    {
      // offset
      uint8_t port = (reg_address - 1300)/1000;
      uint8_t ch = ((reg_address - ((port + 1) * 1000 + 300)) % 14);

      if(eMode == MB_REG_READ)
      {
        val = (uint16_t)_offGainReg[ctx->uart_num][ch].offset;
        U16_TO_BUFFER(val, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);
        _offGainReg[ctx->uart_num][ch].offset = (int16_t)val;
      }
    }
    else if((reg_address >= 1320 && reg_address <= 1333) ||
            (reg_address >= 2320 && reg_address <= 2333) ||
            (reg_address >= 3320 && reg_address <= 3333) ||
            (reg_address >= 4320 && reg_address <= 4333) ||
            (reg_address >= 5320 && reg_address <= 5333) ||
            (reg_address >= 6320 && reg_address <= 6333) ||
            (reg_address >= 7320 && reg_address <= 7333) ||
            (reg_address >= 8320 && reg_address <= 8333))
    {
      // gain
      uint8_t port = (reg_address - 1320)/1000;
      uint8_t ch = ((reg_address - ((port + 1) * 1000 + 320)) % 14);

      if(eMode == MB_REG_READ)
      {
        val = (uint16_t)_offGainReg[ctx->uart_num][ch].gain;
        U16_TO_BUFFER(val, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);
        _offGainReg[ctx->uart_num][ch].gain = (int16_t)val;
      }
    }
    else if(reg_address == 1340 ||
            reg_address == 2340 ||
            reg_address == 3340 ||
            reg_address == 4340 ||
            reg_address == 5340 ||
            reg_address == 6340 ||
            reg_address == 7340 ||
            reg_address == 8340)
    {
      // update offset/gain

      uint8_t port = (reg_address - 1340)/1000;

      if(eMode == MB_REG_READ)
      {
        U16_TO_BUFFER(0, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);

        if(val != 0)
        {
          do_ansgcnv_update_off_gain(val, port, ctx->uart_num);
        }
      }
    }
    else if((reg_address >= 1350 && reg_address <= 1363) ||
            (reg_address >= 2350 && reg_address <= 2363) ||
            (reg_address >= 3350 && reg_address <= 3363) ||
            (reg_address >= 4350 && reg_address <= 4363) ||
            (reg_address >= 5350 && reg_address <= 5363) ||
            (reg_address >= 6350 && reg_address <= 6363) ||
            (reg_address >= 7350 && reg_address <= 7363) ||
            (reg_address >= 8350 && reg_address <= 8363))
    {
      // setup
      uint8_t port = (reg_address - 1350)/1000;
      uint8_t ch = ((reg_address - ((port + 1) * 1000 + 350)) % 14);

      if(eMode == MB_REG_READ)
      {
        val = rs485_task_get_channel_status(port, ch) & 0x1c;
        U16_TO_BUFFER(val, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);
        _setupReg[ctx->uart_num][ch] = (uint8_t)(val & 0x1c);
      }
    }
    else if(reg_address == 1370 ||
            reg_address == 2370 ||
            reg_address == 3370 ||
            reg_address == 4370 ||
            reg_address == 5370 ||
            reg_address == 6370 ||
            reg_address == 7370 ||
            reg_address == 8370)
    {
      // update setup
      uint8_t port = (reg_address - 1370)/1000;

      if(eMode == MB_REG_READ)
      {
        U16_TO_BUFFER(0, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);

        if(val == 1)
        {
          if(rs485_task_get_sensor_type(port) == 0x00)
          {
            // only for SGCNV
            do_ansgcnv_setup(port, ctx->uart_num);
          }
        }
      }
    }
    else if((reg_address >= 1400 && reg_address <= 1402) ||
            (reg_address >= 2400 && reg_address <= 2402) ||
            (reg_address >= 3400 && reg_address <= 3402) ||
            (reg_address >= 4400 && reg_address <= 4402) ||
            (reg_address >= 5400 && reg_address <= 5402) ||
            (reg_address >= 6400 && reg_address <= 6402) ||
            (reg_address >= 7400 && reg_address <= 7402) ||
            (reg_address >= 8400 && reg_address <= 8402))
    {
      // filter
      uint8_t kind = (reg_address % 3);

      if(kind == 0)
      {
        // pressure
        if(eMode == MB_REG_READ)
        {
          val = _filterReg[ctx->uart_num].p;
        }
        else
        {
          val = BUFFER_TO_U16(buffer);
          _filterReg[ctx->uart_num].p = (uint8_t)val;
        }
      }
      else if(kind == 1)
      {
        // temperature
        if(eMode == MB_REG_READ)
        {
          val = _filterReg[ctx->uart_num].t;
        }
        else
        {
          val = BUFFER_TO_U16(buffer);
          _filterReg[ctx->uart_num].t = (uint8_t)val;
        }
      }
      else
      {
        // other
        if(eMode == MB_REG_READ)
        {
          val = _filterReg[ctx->uart_num].o;
        }
        else
        {
          val = BUFFER_TO_U16(buffer);
          _filterReg[ctx->uart_num].o = (uint8_t)val;
        }
      }
    }
    else if(reg_address == 1403 ||
            reg_address == 2403 ||
            reg_address == 3403 ||
            reg_address == 4403 ||
            reg_address == 5403 ||
            reg_address == 6403 ||
            reg_address == 7403 ||
            reg_address == 8403)
    {
      // filter update
      uint8_t port = (reg_address - 1403)/1000;

      if(eMode == MB_REG_READ)
      {
        U16_TO_BUFFER(0, buffer);
      }
      else
      {
        val = BUFFER_TO_U16(buffer);

        if(val == 1)
        {
          do_ansgcnv_update_filter(port, ctx->uart_num);
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
zb485_modbus_user_input_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs)
{
  uint16_t  reg_address,
            end_address;
  uint16_t  v;
  uint8_t*  buffer = (uint8_t*)pucRegBuffer;
  static const modbus_address_range_t ranges[] = 
  {
    {
      .min = 30000,
      .max = 30000,
    },
    // portX channel status/value
    { .min = 1000, .max = 1027, },
    { .min = 2000, .max = 2027, },
    { .min = 3000, .max = 3027, },
    { .min = 4000, .max = 4027, },
    { .min = 5000, .max = 5027, },
    { .min = 6000, .max = 6027, },
    { .min = 7000, .max = 7027, },
    { .min = 8000, .max = 8027, },
    // portX channel raw value
    { .min = 1100, .max = 1113, },
    { .min = 2100, .max = 2113, },
    { .min = 3100, .max = 3113, },
    { .min = 4100, .max = 4113, },
    { .min = 5100, .max = 5113, },
    { .min = 6100, .max = 6113, },
    { .min = 7100, .max = 7113, },
    { .min = 8100, .max = 8113, },
    // portX cal value
    { .min = 1200, .max = 1213, },
    { .min = 2200, .max = 2213, },
    { .min = 3200, .max = 3213, },
    { .min = 4200, .max = 4213, },
    { .min = 5200, .max = 5213, },
    { .min = 6200, .max = 6213, },
    { .min = 7200, .max = 7213, },
    { .min = 8200, .max = 8213, },
  };

  reg_address = usAddress;
  end_address = usAddress + usNRegs - 1;

  if(modbus_check_address_range(reg_address, end_address, ranges, sizeof(ranges)/sizeof(modbus_address_range_t)) == FALSE)
  {
    return MB_ENOREG;
  }
  
  for(; reg_address <= end_address; reg_address++)
  {
    if(reg_address == 30000)
    {
      // version
      U16_TO_BUFFER(PROG_VERSION, buffer);
    }
    else if((reg_address >= 1000 && reg_address <= 1027) ||
            (reg_address >= 2000 && reg_address <= 2027) ||
            (reg_address >= 3000 && reg_address <= 3027) ||
            (reg_address >= 4000 && reg_address <= 4027) ||
            (reg_address >= 5000 && reg_address <= 5027) ||
            (reg_address >= 6000 && reg_address <= 6027) ||
            (reg_address >= 7000 && reg_address <= 7027) ||
            (reg_address >= 8000 && reg_address <= 8027))
    {
      // port status/value
      uint8_t port = (reg_address - 1000)/1000;
      uint8_t ch = ((reg_address - (port + 1) * 1000) % 28)/2;
      uint8_t kind = (reg_address % 2);

      if (ch > 14 || port > 8)
      {
        // bug
        OS_Error(0xff);
      }

      if(kind == 0)
      {
        // channel status
        v = rs485_task_get_channel_status(port, ch);
      }
      else
      {
        // channel value
        v = (uint16_t)rs485_task_get_channel_value(port, ch);
      }
      U16_TO_BUFFER(v, buffer);
    }
    else if((reg_address >= 1100 && reg_address <= 1113) ||
            (reg_address >= 2100 && reg_address <= 2113) ||
            (reg_address >= 3100 && reg_address <= 3113) ||
            (reg_address >= 4100 && reg_address <= 4113) ||
            (reg_address >= 5100 && reg_address <= 5113) ||
            (reg_address >= 6100 && reg_address <= 6113) ||
            (reg_address >= 7100 && reg_address <= 7113) ||
            (reg_address >= 8100 && reg_address <= 8113))
    {
      // raw value
      uint8_t port = (reg_address - 1100)/1000;
      uint8_t ch = ((reg_address - ((port + 1) * 1000 + 100)) % 14);

      v = (uint16_t)rs485_task_get_channel_raw_value(port, ch);
      U16_TO_BUFFER(v, buffer);
    }
    else if((reg_address >= 1200 && reg_address <= 1213) ||
            (reg_address >= 2200 && reg_address <= 2213) ||
            (reg_address >= 3200 && reg_address <= 3213) ||
            (reg_address >= 4200 && reg_address <= 4213) ||
            (reg_address >= 5200 && reg_address <= 5213) ||
            (reg_address >= 6200 && reg_address <= 6213) ||
            (reg_address >= 7200 && reg_address <= 7213) ||
            (reg_address >= 8200 && reg_address <= 8213))
    {
      // cal value
      uint8_t port = (reg_address - 1200)/1000;
      uint8_t ch = ((reg_address - ((port + 1) * 1000 + 200)) % 14);

      v = (uint16_t)rs485_task_get_channel_cal_value(port, ch);
      U16_TO_BUFFER(v, buffer);
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
zb485_modbus_user_discrete_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNDiscrete)
{
  uint16_t reg_address,
           end_address;
  uint8_t  ch,
           status,
           bitNdx;
  static const modbus_address_range_t ranges[] = 
  {
    {
      .min = 10000, 
      .max = 10007 
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
    if(reg_address >= 10000 && reg_address <= 10007)
    {
      // communication status
      ch = (uint8_t)(reg_address - 10000);
      status = rs485_task_get_comm_status(ch);
      xMBUtilSetBits(pucRegBuffer, bitNdx, 1, status);
    }
    else
    {
      // bug if we reach here
      return MB_ENOREG;
    }
  }

  return MB_ENOERR;
}
