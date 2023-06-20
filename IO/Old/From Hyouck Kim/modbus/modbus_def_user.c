#include "common_def.h"
#include "modbus_rtu_request_handler.h"
#include "modbus_funcs.h"

#pragma weak modbus_user_coil_cb=__modbus_user_coil_cb
MBErrorCode
__modbus_user_coil_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNCoils, MBRegisterMode eMode)
{
  return MB_EIO;
}

#pragma weak modbus_user_holding_cb=__modbus_user_holding_cb
MBErrorCode
__modbus_user_holding_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, MBRegisterMode eMode)
{
  return MB_EIO;
}

#pragma weak modbus_user_input_cb=__modbus_user_input_cb
MBErrorCode
__modbus_user_input_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs)
{
  return MB_EIO;
}

#pragma weak modbus_user_discrete_cb=__modbus_user_discrete_cb
MBErrorCode
__modbus_user_discrete_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNDiscrete)
{
  return MB_EIO;
}

#pragma weak modbus_rtu_init_snoop=__modbus_rtu_init_snoop
void
__modbus_rtu_init_snoop(ModbusCTX* ctx)
{
}

#pragma weak modbus_rtu_frame_snoop=__modbus_rtu_frame_snoop
void
__modbus_rtu_frame_snoop(ModbusCTX* ctx,uint8_t addr, uint8_t* pdu, uint16_t len)
{
}
