#ifndef MODBUS_RTU_H_
#define MODBUS_RTU_H_

#include "common_def.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// a bunch of definitions for standard MODBUS RTU
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Constants which defines the format of a modbus frame. The example is
 * shown for a Modbus RTU/ASCII frame. Note that the Modbus PDU is not
 * dependent on the underlying transport.
 *
 * <------------------------ MODBUS SERIAL LINE PDU (1) ------------------->
 *              <----------- MODBUS PDU (1') ---------------->
 *  +-----------+---------------+----------------------------+-------------+
 *  | Address   | Function Code | Data                       | CRC/LRC     |
 *  +-----------+---------------+----------------------------+-------------+
 *  |           |               |                                   |
 * (2)        (3/2')           (3')                                (4)
 *
 * (1)  ... MB_SER_PDU_SIZE_MAX = 256
 * (2)  ... MB_SER_PDU_ADDR_OFF = 0
 * (3)  ... MB_SER_PDU_PDU_OFF  = 1
 * (4)  ... MB_SER_PDU_SIZE_CRC = 2
 *
 * (1') ... MB_PDU_SIZE_MAX     = 253
 * (2') ... MB_PDU_FUNC_OFF     = 0
 * (3') ... MB_PDU_DATA_OFF     = 1
 */
#define MB_PDU_SIZE_MAX                 253
#define MB_PDU_SIZE_MIN                 1
#define MB_PDU_FUNC_OFF                 0
#define MB_PDU_DATA_OFF                 1

#define MB_SER_RTU_PDU_SIZE_MIN         4
#define MB_SER_RTU_PDU_SIZE_MAX         280
#define MB_SER_PDU_SIZE_CRC             2
#define MB_SER_PDU_ADDR_OFF             0
#define MB_SER_PDU_PDU_OFF              1

#define MB_ADDRESS_BROADCAST            0
#define MB_ADDRESS_MIN                  1
#define MB_ADDRESS_MAX                  247

#define MB_FUNC_NONE                          (  0 )
#define MB_FUNC_READ_COILS                    (  1 )
#define MB_FUNC_READ_DISCRETE_INPUTS          (  2 )
#define MB_FUNC_WRITE_SINGLE_COIL             (  5 )
#define MB_FUNC_WRITE_MULTIPLE_COILS          ( 15 )
#define MB_FUNC_READ_HOLDING_REGISTER         (  3 )
#define MB_FUNC_READ_INPUT_REGISTER           (  4 )
#define MB_FUNC_WRITE_REGISTER                (  6 )
#define MB_FUNC_WRITE_MULTIPLE_REGISTERS      ( 16 )
#define MB_FUNC_READWRITE_MULTIPLE_REGISTERS  ( 23 )
#define MB_FUNC_DIAG_READ_EXCEPTION           (  7 )
#define MB_FUNC_DIAG_DIAGNOSTIC               (  8 )
#define MB_FUNC_DIAG_GET_COM_EVENT_CNT        ( 11 )
#define MB_FUNC_DIAG_GET_COM_EVENT_LOG        ( 12 )
#define MB_FUNC_OTHER_REPORT_SLAVEID          ( 17 )
#define MB_FUNC_ERROR                         ( 128)
 
typedef enum
{
  MB_EX_NONE                    = 0x00,
  MB_EX_ILLEGAL_FUNCTION        = 0x01,
  MB_EX_ILLEGAL_DATA_ADDRESS    = 0x02,
  MB_EX_ILLEGAL_DATA_VALUE      = 0x03,
  MB_EX_SLAVE_DEVICE_FAILURE    = 0x04,
  MB_EX_ACKNOWLEDGE             = 0x05,
  MB_EX_SLAVE_BUSY              = 0x06,
  MB_EX_MEMORY_PARITY_ERROR     = 0x08,
  MB_EX_GATEWAY_PATH_FAILED     = 0x0A,
  MB_EX_GATEWAY_TGT_FAILED      = 0x0B
} MBException;

typedef enum
{
  MB_ENOERR,                  /*!< no error. */
  MB_ENOREG,                  /*!< illegal register address. */
  MB_EINVAL,                  /*!< illegal argument. */
  MB_EPORTERR,                /*!< porting layer error. */
  MB_ENORES,                  /*!< insufficient resources. */
  MB_EIO,                     /*!< I/O error. */
  MB_EILLSTATE,               /*!< protocol stack in illegal state. */
  MB_ETIMEDOUT                /*!< timeout error occurred. */
} MBErrorCode;


typedef struct
{
  uint8_t               uart_num;
  uint8_t               my_address;
  volatile uint8_t      data_buffer[MB_SER_RTU_PDU_SIZE_MAX];
  volatile uint16_t     data_ndx;
  volatile uint16_t     tx_ndx;
  // TaskTimerElem         t35;
  uint8_t               t35_val;

  // stats for debugging
  volatile uint16_t     rx_buffer_overflow;
  volatile uint16_t     rx_usart_overflow;
  volatile uint16_t     rx_usart_frame_error;
  volatile uint16_t     rx_usart_parity_error;
  volatile uint16_t     rx_short_frame;
  volatile uint16_t     rx_crc_error;
  uint16_t              rx_frames;
  uint16_t              req_fails;
  uint16_t              my_frames;
  volatile uint16_t     tx_frames;
} ModbusCTX;

extern void modbus_rtu_init(uint8_t device_addr, uint8_t baud_rate_config);
extern void modbus_rtu_reinit(uint8_t device_addr, uint8_t baud_rate_config);

#endif /* MODBUS_RTU_H_ */
