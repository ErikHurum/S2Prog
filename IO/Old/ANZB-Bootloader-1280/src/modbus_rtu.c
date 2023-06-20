#include <iom1280.h>

#include "common_def.h"
#include "modbus_rtu.h"
#include "modbus_crc.h"
#include "modbus_funcs.h"

#include "events.h"
#include "timer.h"

#define XTAL_CPU      16000000UL

extern char MyAddress(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// private structures & definitions
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MODBUS_ADDRESS_START        10

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// pin definitions for RS-485
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define     MB_RS485_RTX_CONRTOL_PORT         (PORTE)
#define     MB_RS485_RTX_CONRTOL_USART0       (2)
#define     MB_RS485_RTX_CONRTOL_USART1       (3)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// macros for convenience
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INC_ERR_CNT(err_cnt)    \
  if(err_cnt < 0xffff)          \
  {                             \
    err_cnt++;                  \
  }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// private prototoypes
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint8_t mb_rtu_start_handling_rx_frame(ModbusCTX* ctx);
static void mb_rtu_init_usart0(unsigned long baud);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// module privates
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ModbusCTX             _mb_rtu_ctx_uart0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// buffer management utilities
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static inline void
mb_rtu_reset_data_buffer(ModbusCTX* ctx)
{
  ctx->data_ndx   = 0;
  ctx->tx_ndx     = 0;
}

static inline void
mb_rtu_put_data(ModbusCTX* ctx, uint8_t b)
{
  ctx->data_buffer[ctx->data_ndx] = b;
  ctx->data_ndx++;
}

static inline uint16_t
mb_rtu_rx_len(ModbusCTX* ctx)
{
  return ctx->data_ndx;
}

static inline volatile uint8_t*
mb_rtu_buffer(ModbusCTX* ctx)
{
  return ctx->data_buffer;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// USART/RS486 specific
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static inline void
mb_rtu_enable_rx(ModbusCTX* ctx)
{
  mb_rtu_reset_data_buffer(ctx);
  
  //
  // ZB-ANA/485 board has /RE pulled down.
  // This means we get echo back for our TX.
  // Whatever the reason is, we need to disable RX
  // during transmission.
  //
  if(ctx->uart_num == 0)
  {
    UCSR0B |= _BV(RXEN0)  | _BV(RXCIE0);
    MB_RS485_RTX_CONRTOL_PORT &= ~_BV(MB_RS485_RTX_CONRTOL_USART0);
  }
}

static inline void
mb_rtu_disable_rx(ModbusCTX* ctx, uint8_t uart, uint8_t gpio)
{
  //
  // ZB-ANA/485 board has /RE pulled down.
  // This means we get echo back for our TX.
  // Whatever the reason is, we need to disable RX
  // during transmission.
  //
  if(ctx->uart_num == 0)
  {
    if(uart)
    {
      UCSR0B &= ~(_BV(RXEN0)  | _BV(RXCIE0));
    }
    if(gpio)
    {
      MB_RS485_RTX_CONRTOL_PORT |= _BV(MB_RS485_RTX_CONRTOL_USART0);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// USART H/W specific part
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static inline void
mb_rtu_start_tx(ModbusCTX* ctx)
{
  //
  // bug check
  // why try to send zero len data? find the bug and fix it!!!
  //
  ctx->tx_ndx = 0;

  if(ctx->uart_num == 0)
  {
    UCSR0B |= _BV(UDRIE0);
  }
}

#pragma vector=USART0_RX_vect
__interrupt void USART0_RX_vect_handler(void)
{
  ModbusCTX*            ctx = &_mb_rtu_ctx_uart0;
  uint8_t               sra,
                        b;

  sra = UCSR0A;
  if (sra & ((1 << DOR0) | (1 << UPE0) | (1 << FE0)))
  {
    if(sra & _BV(DOR0))
      INC_ERR_CNT(ctx->rx_usart_overflow);
    
    if(sra & _BV(UPE0))
      INC_ERR_CNT(ctx->rx_usart_parity_error);
    
    if(sra & _BV(FE0))
      INC_ERR_CNT(ctx->rx_usart_frame_error);

    b= UDR0;
    mb_rtu_reset_data_buffer(ctx);
    return;
  }
  
  b = UDR0;

  if(ctx->data_ndx >= MB_SER_RTU_PDU_SIZE_MAX)
  {
    mb_rtu_reset_data_buffer(ctx);
    INC_ERR_CNT(ctx->rx_buffer_overflow);
    return;
  }

  mb_rtu_put_data(ctx, b);
  set_event(EVENTS_FLAG_UART0_RX);
}

#pragma vector=USART0_UDRE_vect
__interrupt void USART0_UDRE_vect_handler(void)
{
  ModbusCTX*            ctx = &_mb_rtu_ctx_uart0;
  uint8_t               b;
  uint16_t              dndx;

  dndx = ctx->data_ndx;
  if(ctx->tx_ndx >= dndx)
  {
    UCSR0B &= ~_BV(UDRIE0);
    UCSR0B |=  _BV(TXCIE0);
  }
  else
  {
    b = ctx->data_buffer[ctx->tx_ndx];
    UCSR0A |= _BV(TXC0);
    UDR0 = b;
    ctx->tx_ndx++;
  }
}

#pragma vector=USART0_TX_vect
__interrupt void USART0_TX_vect_handler(void)
{
  ModbusCTX*            ctx = &_mb_rtu_ctx_uart0;
  
  UCSR0B &=  ~_BV(TXCIE0);

  mb_rtu_reset_data_buffer(ctx);

  ctx->tx_frames++;
  set_event(EVENTS_FLAG_UART0_TXC);
}

static void
mb_rtu_init_usart0(unsigned long baud)
{
  uint16_t baud_setting = (XTAL_CPU / 4 / baud - 1) / 2;

  // try u2x mode first
  UCSR0A      = _BV(U2X0);

  if (((XTAL_CPU == 16000000UL) && (baud == 57600)) || (baud_setting >4095))
  {
    UCSR0A        = 0;
    baud_setting  = (XTAL_CPU / 8 / baud - 1) / 2;
  }

  UBRR0H      = baud_setting >> 8;
  UBRR0L      = baud_setting;

  UCSR0C      = _BV(UCSZ00) | _BV(UCSZ01);                  // 8 bit data, no parity, 1 stop-bit
  UCSR0B      = _BV(RXEN0)  | _BV(TXEN0) | _BV(RXCIE0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MODBUS RX/TX in mainloop
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint8_t
mini_modbus_rtu_handler_request_rx(ModbusCTX* ctx, uint8_t addr, uint16_t len, uint8_t* pdu)
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
  case MB_FUNC_READ_HOLDING_REGISTER:         // read holding register
    ret = modbus_func_handler_read_holding_register(ctx, addr, pdu, &len);
    break;

  case MB_FUNC_WRITE_MULTIPLE_REGISTERS:      // write multiple holding register
    ret = modbus_func_handler_write_multiple_holding_registers(ctx, addr, pdu, &len);
    break;

  case MB_FUNC_WRITE_REGISTER:                // write holding register
    ret = modbus_func_handler_write_holding_register(ctx, addr, pdu, &len);
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

static uint8_t
mb_rtu_handle_rx_frame(ModbusCTX* ctx)
{
  uint8_t   addr,
            *pdu,
            ret;
  uint16_t  len;

  addr = mb_rtu_buffer(ctx)[MB_SER_PDU_ADDR_OFF];
  len  = mb_rtu_rx_len(ctx) - MB_SER_PDU_PDU_OFF - MB_SER_PDU_SIZE_CRC;
  pdu  = (uint8_t*)&mb_rtu_buffer(ctx)[MB_SER_PDU_PDU_OFF];

  ctx->my_address = (uint8_t)MyAddress() + MODBUS_ADDRESS_START;
  if(addr == ctx->my_address || addr == MB_ADDRESS_BROADCAST)
  {
    ret = mini_modbus_rtu_handler_request_rx(ctx, addr, len, pdu);
    if(addr != MB_ADDRESS_BROADCAST)
    {
      ctx->my_frames++;
      if(ret != TRUE)
      {
        ctx->req_fails++;
      }
      return TRUE;
    }
  }
  return FALSE;
}

static uint8_t
mb_rtu_start_handling_rx_frame(ModbusCTX* ctx)
{
  ctx->rx_frames++;

  if(mb_rtu_rx_len(ctx) == 0)
  {
    // buffer overflow due to long frame has just occurred.
    return FALSE;
  }

  if(mb_rtu_rx_len(ctx) < MB_SER_RTU_PDU_SIZE_MIN)
  {
    INC_ERR_CNT(ctx->rx_short_frame);
    return FALSE;
  }

  if(modbus_calc_crc((uint8_t*)mb_rtu_buffer(ctx), mb_rtu_rx_len(ctx)) != 0)
  {
    // crc16 error
    INC_ERR_CNT(ctx->rx_crc_error);
    return FALSE;
  }

  return mb_rtu_handle_rx_frame(ctx);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MODBUS utilities
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void
init_modbus_context(ModbusCTX* ctx, uint8_t uart_num, uint8_t addr)
{
  ctx->uart_num     = uart_num;
  ctx->my_address   = addr;

  mb_rtu_reset_data_buffer(ctx);

  ctx->t35_val                  = 3;        // just 3ms max for every baud rate. 3ms buffer.

  ctx->rx_buffer_overflow       = 0;
  ctx->rx_usart_overflow        = 0;
  ctx->rx_usart_frame_error     = 0;
  ctx->rx_usart_parity_error    = 0;
  ctx->rx_short_frame           = 0;
  ctx->rx_crc_error             = 0;
  ctx->rx_frames                = 0;
  ctx->req_fails                = 0;
  ctx->my_frames                = 0;
  ctx->tx_frames                = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// event handlers
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void
modbus_uart_evt(unsigned char evt)
{
  switch(evt)
  {
  case EVENTS_FLAG_UART0_RX:
    start_timer(timer_num_0, 4, EVENTS_FLAG_UART0_T35);
    break;

  case EVENTS_FLAG_UART0_T35:
    mb_rtu_disable_rx(&_mb_rtu_ctx_uart0, 1, 0);
    if(mb_rtu_start_handling_rx_frame(&_mb_rtu_ctx_uart0) == TRUE)
    {
      mb_rtu_disable_rx(&_mb_rtu_ctx_uart0, 0, 1);
      mb_rtu_start_tx(&_mb_rtu_ctx_uart0);
    }
    else
    {
      mb_rtu_enable_rx(&_mb_rtu_ctx_uart0);
    }
    break;

  case EVENTS_FLAG_UART0_TXC:
    mb_rtu_enable_rx(&_mb_rtu_ctx_uart0);
    break;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// public interfaces
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void
modbus_init(void)
{
  unsigned long baud_rate = 38400;
  uint8_t dev_addr = (uint8_t)MyAddress() + MODBUS_ADDRESS_START;

  init_modbus_context(&_mb_rtu_ctx_uart0, 0, dev_addr);
  mb_rtu_enable_rx(&_mb_rtu_ctx_uart0);

  register_event_handler(EVENTS_FLAG_UART0_RX, modbus_uart_evt);
  register_event_handler(EVENTS_FLAG_UART0_T35, modbus_uart_evt);
  register_event_handler(EVENTS_FLAG_UART0_TXC, modbus_uart_evt);

  mb_rtu_init_usart0(baud_rate);
}
