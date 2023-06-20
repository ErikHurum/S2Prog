#include "common_def.h"
#include "modbus_rtu_request_handler.h"
#include "modbus_funcs.h"
#include "modbus_crc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// modbus handling logic entry point
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @return TRUE, when response is ready for TX
 *         FALSE, when there is no response due to error or whatever
 */
uint8_t
modbus_rtu_handler_request_rx(ModbusCTX* ctx, uint8_t addr, uint16_t len, uint8_t* pdu)
{
  uint8_t       func;
  MBException   ret;
  uint16_t      crc;
  
  func = pdu[MB_PDU_FUNC_OFF];
  //
  // at this moment, this implementation supports the following modbus functions
  //
  switch(func)
  {
  case MB_FUNC_READ_INPUT_REGISTER:           // read input register
    ret = modbus_func_handler_read_input_register(ctx, addr, pdu, &len);
    break;

  case MB_FUNC_READ_HOLDING_REGISTER:         // read holding register
    ret = modbus_func_handler_read_holding_register(ctx, addr, pdu, &len);
    break;

  case MB_FUNC_WRITE_MULTIPLE_REGISTERS:      // write multiple holding register
    ret = modbus_func_handler_write_multiple_holding_registers(ctx, addr, pdu, &len);
    break;

  case MB_FUNC_WRITE_REGISTER:                // write holding register
    ret = modbus_func_handler_write_holding_register(ctx, addr, pdu, &len);
    break;

  case MB_FUNC_READWRITE_MULTIPLE_REGISTERS:  // read/write multiple holding register
    ret = modbus_func_handler_read_write_multiple_holding_registers(ctx, addr, pdu, &len);
    break;

  case MB_FUNC_READ_COILS:                    // read coils
    ret = modbus_func_handler_read_coils(ctx, addr, pdu, &len);
    break;

  case MB_FUNC_WRITE_SINGLE_COIL:             // read coil
    ret = modbus_func_handler_write_coil(ctx, addr, pdu, &len);
    break;

  case MB_FUNC_WRITE_MULTIPLE_COILS:          // write multiple coils
    ret = modbus_func_handler_write_multiple_coils(ctx, addr, pdu, &len);
    break;

  case MB_FUNC_READ_DISCRETE_INPUTS:          // read multiple input registers
    ret = modbus_func_handler_read_discrete_inputs(ctx, addr, pdu, &len);
    break;

  default:
    ret = MB_EX_ILLEGAL_FUNCTION;
    break;
  }
  
  if(ret != MB_EX_NONE)
  {
    len = 0;
    pdu[len++] = (func | MB_FUNC_ERROR);
    pdu[len++] = ret;
  }
  
  // prepare response

  ctx->data_buffer[0] = addr;
  ctx->data_ndx       = 1 + len;
  crc = modbus_calc_crc((uint8_t*)ctx->data_buffer, ctx->data_ndx);
  
  ctx->data_buffer[ctx->data_ndx++] = (uint8_t)(crc & 0xff);
  ctx->data_buffer[ctx->data_ndx++] = (uint8_t)(crc >> 8);

  return ret == MB_EX_NONE ? TRUE : FALSE;
}