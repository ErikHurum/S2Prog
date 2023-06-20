#if USE_MODBUS_PROTOCOL == 1

#include <iom1280.h>
#include "RTOS.h"

#include "constants.h"
#include "externals.h"

#include "common_def.h"
#include "modbus_rtu.h"
#include "modbus_crc.h"
#include "modbus_rtu_request_handler.h"
#include "modbus_funcs.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// private structures & definitions
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MODBUS_ADDRESS_START        10

#define offsetof(TYPE, MEMBER) ((uint16_t) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) (type *)((char *)ptr - offsetof(type,member))

#define ENTER_IRQ                 \
   OS_EnterInterrupt();           \
   OS_EnterIntStack();

#define LEAVE_IRQ                 \
    OS_LeaveIntStack();           \
    OS_LeaveInterruptNoSwitch();
   
#define MODBUS_RTU_TASK_STACK_SIZE      140
#define MODBUS_RTU_TASK_PRIORITY        100
   
#define MODBUS_RTU_EVENT_RX_CHAR        0x01
#define MODBUS_RTU_EVENT_RX_ERROR       0x02
#define MODBUS_RTU_EVENT_TX_COMPLETE    0x04

typedef enum {
  MODBUSTaskUART_USART0 = 0,
} MODBUSTaskUART;

typedef struct __MODBUSTaskStruct MODBUSTaskStruct;

struct __MODBUSTaskStruct {
  OS_STACKPTR int       stack[MODBUS_RTU_TASK_STACK_SIZE];
  OS_TASK               tcb;
  ModbusCTX             mb_rtu_ctx;
  MODBUSTaskUART        uart;
  uint8_t               system_reset;
  void (*uart_init)(unsigned long baud);
  void (*state_handler)(MODBUSTaskStruct*);
};

extern uint16_t hart_get_rsp_delay(void);

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
// FIXME static void t35_timeout_handler(TaskTimerElem* te);
static uint8_t mb_rtu_start_handling_rx_frame(ModbusCTX* ctx);
static void mb_rtu_init_usart0(unsigned long baud);

static void MODBUS_RTU_State_Idle(MODBUSTaskStruct* self);
static void MODBUS_RTU_State_Receiving(MODBUSTaskStruct* self);
static void MODBUS_RTU_State_Handling(MODBUSTaskStruct* self);
static void MODBUS_RTU_State_Responding(MODBUSTaskStruct* self);

void modbus_rtu_update_rsp_delay(ModbusCTX* ctx, uint16_t delay);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// module privates
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static MODBUSTaskStruct         _mb_rtu_task0 = 
{
  .uart = MODBUSTaskUART_USART0,
  .uart_init = mb_rtu_init_usart0,
  .system_reset = 0,
};

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
  // during transmission./contai
  //
  if(ctx->uart_num == MODBUSTaskUART_USART0)
  {
    UCSR0B |= _BV(RXEN0)  | _BV(RXCIE0);
    ClrBit(MB_RS485_RTX_CONRTOL_PORT, _BV(MB_RS485_RTX_CONRTOL_USART0));
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
  if(ctx->uart_num == MODBUSTaskUART_USART0)
  {
    if(uart)
    {
      UCSR0B &= ~(_BV(RXEN0)  | _BV(RXCIE0));
    }
    if(gpio)
    {
      SetBit(MB_RS485_RTX_CONRTOL_PORT, _BV(MB_RS485_RTX_CONRTOL_USART0));
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

  if(ctx->uart_num == MODBUSTaskUART_USART0)
  {
    UCSR0B |= _BV(UDRIE0);
  }
}
static void
usart0_rx_irq_handler (void)
{
  MODBUSTaskStruct*     task = &_mb_rtu_task0;
  ModbusCTX*            ctx = &task->mb_rtu_ctx;
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
    OS_SignalEvent(MODBUS_RTU_EVENT_RX_ERROR, &task->tcb);
    return;
  }
  
  b = UDR0;

  if(ctx->data_ndx >= MB_SER_RTU_PDU_SIZE_MAX)
  {
    mb_rtu_reset_data_buffer(ctx);
    INC_ERR_CNT(ctx->rx_buffer_overflow);
    OS_SignalEvent(MODBUS_RTU_EVENT_RX_ERROR, &task->tcb);
    return;
  }

  mb_rtu_put_data(ctx, b);
  OS_SignalEvent(MODBUS_RTU_EVENT_RX_CHAR, &task->tcb);
}

#pragma vector=USART0_RX_vect
__interrupt void USART0_RX_vect_handler(void)
{
  ENTER_IRQ;
  
  usart0_rx_irq_handler();
  
  LEAVE_IRQ;
}

static void
usart0_udre_irq_handler (void)
{
  MODBUSTaskStruct*     task = &_mb_rtu_task0;
  ModbusCTX*            ctx = &task->mb_rtu_ctx;
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

#pragma vector=USART0_UDRE_vect
__interrupt void USART0_UDRE_vect_handler(void)
{
  ENTER_IRQ;
  
  usart0_udre_irq_handler();
  
  LEAVE_IRQ;
}

static void
usart0_txc_irq_handler(void)
{
  MODBUSTaskStruct*     task = &_mb_rtu_task0;
  ModbusCTX*            ctx = &task->mb_rtu_ctx;
  
  UCSR0B &=  ~_BV(TXCIE0);

  mb_rtu_reset_data_buffer(ctx);

  ctx->tx_frames++;
  OS_SignalEvent(MODBUS_RTU_EVENT_TX_COMPLETE, &task->tcb);
}

#pragma vector=USART0_TX_vect
__interrupt void USART0_TX_vect_handler(void)
{
  ENTER_IRQ;
  
  usart0_txc_irq_handler();
  
  LEAVE_IRQ;
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
    ret = modbus_rtu_handler_request_rx(ctx, addr, len, pdu);
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

  //FIXME
  //init_task_timer_elem(&ctx->t35);
  //ctx->t35.cb           = t35_timeout_handler;
  //ctx->t35.priv         = (void*)ctx;

  // T35
  // at 9600    : 3ms +- alpha
  // above 9600 : 2ms should be enough
  //
  // so we can safely go with 3ms for t35.
  //
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
// modbus statemachine
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void
MODBUS_RTU_State_Idle(MODBUSTaskStruct* self)
{
  char event_status;

  event_status = OS_WaitEvent(MODBUS_RTU_EVENT_RX_CHAR | MODBUS_RTU_EVENT_RX_ERROR);

  if (event_status & MODBUS_RTU_EVENT_RX_ERROR)
  {
    return;
  }

  self->state_handler = MODBUS_RTU_State_Receiving;
}

static void
MODBUS_RTU_State_Receiving(MODBUSTaskStruct* self)
{
  char event_status;
  
  event_status = OS_WaitEventTimed(MODBUS_RTU_EVENT_RX_CHAR | MODBUS_RTU_EVENT_RX_ERROR,
      self->mb_rtu_ctx.t35_val);

  if(event_status == 0)
  {
    // T35 timeout
    mb_rtu_disable_rx(&self->mb_rtu_ctx, 1, 0);
    //
    // due to race condition,
    // we might have RX IRQs before calling mb_rtu_disable_rx()
    // so just clear all events just to make sure and proceed.
    //
    OS_ClearEvents(&self->tcb);
    self->state_handler = MODBUS_RTU_State_Handling;
  }
  else if (event_status & MODBUS_RTU_EVENT_RX_ERROR)
  {
    self->state_handler = MODBUS_RTU_State_Idle;
  }
  else if (event_status & MODBUS_RTU_EVENT_RX_CHAR)
  {
    // nothing to do. keep receiving
  }
}

static void
MODBUS_RTU_State_Handling(MODBUSTaskStruct* self)
{
  if(mb_rtu_start_handling_rx_frame(&self->mb_rtu_ctx) == TRUE)
  {
    uint16_t rsp_delay = hart_get_rsp_delay();

    mb_rtu_disable_rx(&self->mb_rtu_ctx, 0, 1);

    self->state_handler = MODBUS_RTU_State_Responding;
    if (rsp_delay != 0)
    {
      OS_Delay(rsp_delay);
    }
    mb_rtu_start_tx(&self->mb_rtu_ctx);
  }
  else
  {
    self->state_handler = MODBUS_RTU_State_Idle;
    mb_rtu_enable_rx(&self->mb_rtu_ctx);
  }
}

static void
MODBUS_RTU_State_Responding(MODBUSTaskStruct* self)
{
  char event_status;
  
  event_status = OS_WaitEvent(MODBUS_RTU_EVENT_TX_COMPLETE);

  (void)event_status;

  self->state_handler = MODBUS_RTU_State_Idle;

  if(self->system_reset)
  {
    WDTCSR = 0x18;               //Start watchdog to genetate restart
    WDTCSR = 0x18;

    while(1)
      ;
  }

  mb_rtu_enable_rx(&self->mb_rtu_ctx);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// modbus main
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void
MODBUS_RTU_Task_Main(void)
{
  OS_TASK *taskPtr = OS_GetpCurrentTask();
  MODBUSTaskStruct *self = container_of(taskPtr, MODBUSTaskStruct, tcb);
  unsigned long baud_rate = 38400;
  uint8_t dev_addr = (uint8_t)MyAddress() + MODBUS_ADDRESS_START;

  //
  // wait for HART tasks to finish initialization
  //
  OS_WaitEvent(0x80);
  
  init_modbus_context(&self->mb_rtu_ctx, self->uart, dev_addr);
  mb_rtu_enable_rx(&self->mb_rtu_ctx);

  self->state_handler = MODBUS_RTU_State_Idle;
  self->uart_init(baud_rate);
  
  while (1)
  {
    self->state_handler(self);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// public interfaces
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void
modbus_rtu_task_init(void)
{
  OS_CREATETASK(&_mb_rtu_task0.tcb, "MBRTU0", MODBUS_RTU_Task_Main, MODBUS_RTU_TASK_PRIORITY, _mb_rtu_task0.stack);
}

void
modbus_rtu_notify_go(void)
{
  OS_SignalEvent(0x80, &_mb_rtu_task0.tcb);
}

void
modbus_rtu_set_system_reset(ModbusCTX* ctx)
{
  MODBUSTaskStruct *self = container_of(ctx, MODBUSTaskStruct, mb_rtu_ctx);

  self->system_reset = 1;
}

#endif /* USE_MODBUS_PROTOCOL == 1 */
