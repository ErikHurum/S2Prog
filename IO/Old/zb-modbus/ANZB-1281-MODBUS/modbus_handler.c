#include "common_def.h"
#include "modbus_rtu_request_handler.h"
#include "modbus_funcs.h"
#include "modbus_util.h"

extern MBErrorCode
zbana_modbus_user_coil_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNCoils, MBRegisterMode eMode);
extern MBErrorCode
zbana_modbus_user_holding_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, MBRegisterMode eMode);
extern MBErrorCode
zbana_modbus_user_input_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs);
extern MBErrorCode
zbana_modbus_user_discrete_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNDiscrete);

MBErrorCode
modbus_user_coil_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNCoils, MBRegisterMode eMode)
{
  switch (UnitID)
  {
  case 0x00: // ZB485
    break;

  case 0x01: // ZBANA
    return zbana_modbus_user_coil_cb(ctx, addr, pucRegBuffer, usAddress, usNCoils, eMode);
  }
  return MB_ENOREG;
}

MBErrorCode
modbus_user_coil_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNCoils, MBRegisterMode eMode)
{
  switch (UnitID)
  {
  case 0x00: // ZB485
    break;

  case 0x01: // ZBANA
    return zbana_modbus_user_coil_cb(ctx, addr, pucRegBuffer, usAddress, usNCoils, eMode);
  }
  return MB_ENOREG;
}

MBErrorCode
modbus_user_input_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs)
{
  return MB_ENOREG;
}

MBErrorCode
modbus_user_discrete_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNDiscrete)
{
  return MB_ENOREG;
}