#ifndef MODBUS_RTU_REQUEST_HANDLER_H_
#define MODBUS_RTU_REQUEST_HANDLER_H_

#include "modbus_rtu.h"

extern uint8_t modbus_rtu_handler_request_rx(ModbusCTX* ctx, uint8_t addr, uint16_t len, uint8_t* pdu);

#endif /* MODBUS_RTU_REQUEST_HANDLER_H_ */