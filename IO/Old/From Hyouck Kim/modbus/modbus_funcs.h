/*
 * modbus_funcs.h
 *
 */ 


#ifndef MODBUS_FUNCS_H_
#define MODBUS_FUNCS_H_

#include "common_def.h"
#include "modbus_rtu.h"

typedef enum
{
  MB_REG_READ,                /*!< Read register values and pass to protocol stack. */
  MB_REG_WRITE                /*!< Update register values. */
} MBRegisterMode;


extern MBException modbus_func_handler_read_coils(ModbusCTX* ctx, uint8_t addr, uint8_t * pucFrame, uint16_t * usLen);
extern MBException modbus_func_handler_write_coil(ModbusCTX* ctx, uint8_t addr, uint8_t * pucFrame, uint16_t * usLen);
extern MBException modbus_func_handler_write_multiple_coils(ModbusCTX* ctx, uint8_t addr, uint8_t * pucFrame, uint16_t * usLen);

extern MBException modbus_func_handler_write_holding_register(ModbusCTX* ctx, uint8_t addr, uint8_t * pucFrame, uint16_t * usLen);
extern MBException modbus_func_handler_write_multiple_holding_registers(ModbusCTX* ctx, uint8_t addr, uint8_t * pucFrame, uint16_t * usLen);
extern MBException modbus_func_handler_read_holding_register(ModbusCTX* ctx, uint8_t addr, uint8_t * pucFrame, uint16_t * usLen);
extern MBException modbus_func_handler_read_write_multiple_holding_registers(ModbusCTX* ctx, uint8_t addr, uint8_t * pucFrame, uint16_t * usLen);

extern MBException modbus_func_handler_read_input_register(ModbusCTX* ctx, uint8_t addr, uint8_t* pucFrame, uint16_t * usLen);

extern MBException modbus_func_handler_read_discrete_inputs(ModbusCTX* ctx, uint8_t addr, uint8_t * pucFrame, uint16_t * usLen);


////////////////////////////////////////////////////////////////////////////////
//
// The following callbacks are expected to be implemented by the user
//
////////////////////////////////////////////////////////////////////////////////
extern MBErrorCode modbus_user_coil_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNCoils, MBRegisterMode eMode);
extern MBErrorCode modbus_user_holding_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, MBRegisterMode eMode);
extern MBErrorCode modbus_user_input_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs);
extern MBErrorCode modbus_user_discrete_cb(ModbusCTX* ctx, uint8_t addr, uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNDiscrete);

extern void modbus_rtu_init_snoop(ModbusCTX* ctx);
extern void modbus_rtu_frame_snoop(ModbusCTX* ctx,uint8_t addr, uint8_t* pdu, uint16_t len);

#endif /* MODBUS_FUNCS_H_ */
