#include <stdio.h>
#include "iom1280.h"
#include "version.h"
#include "inavr.h"
#include "RTOS.h"

#include "constants.h"
#include "hart_common.h"
#include "hart.h"
#include "hart_diag.h"
#include "hart_msg.h"

////////////////////////////////////////////////////////////////////////////////
//
// private defines
//
////////////////////////////////////////////////////////////////////////////////
#define HART_TASK_STACK_SIZE            80

#define HART_MAX_TX_BUFFER_SIZE         384
#define HART_MAX_RX_BUFFER_SIZE         384

#define HART_EVENT_RX_COMPLETE          0x01
#define HART_EVENT_RX_ERROR             0x02

#define HART_TRANSACTION_TIMEOUT        2000

#define HART_ENABLE_MODULATOR           0
#define HART_DISABLE_MODULATOR          1

#define HART_RTS_CONTROL_FROM_IRQ       1
#define HART_RTS_CONTROL_FROM_TASK      0

#define ENTER_IRQ                 \
   OS_EnterInterrupt();           \
   OS_EnterIntStack();

#define LEAVE_IRQ                 \
    OS_LeaveIntStack();           \
    OS_LeaveInterruptNoSwitch();

#define _BV(A)    __BIT_MASK(A)


#define offsetof(TYPE, MEMBER) ((uint16_t) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) (type *)((char *)ptr - offsetof(type,member))

typedef enum
{
  HartCommErr_RX_Error,
  HartCommErr_RX_Timeout,
} HartCommErrType;

typedef struct {
  OS_STACKPTR int             stack[HART_TASK_STACK_SIZE];
  OS_TASK                     task;
  const char*                 name;
  const uint8_t               modem_no;
  const uint8_t               start_chnl;
  const uint8_t               end_chnl;

  //
  // TX buffer
  //
  volatile uint16_t           tx_buf_ndx;
  volatile uint16_t           tx_len;
  volatile hart_data_t        tx_buf[HART_MAX_TX_BUFFER_SIZE];

  //
  // RX buffer
  //
  volatile uint16_t           rx_buf_ndx;
  volatile uint16_t           rx_len;
  volatile hart_data_t        rx_buf[HART_MAX_RX_BUFFER_SIZE];

  //
  // hart RX message parser
  //
  HartMessageParser           hart_parser;    

  //
  // hart TX message encoder
  //
  HartMessageEncoder          hart_encoder;
} HartTaskStruct;


typedef void (*hart_prepare_handler)(HartTaskStruct* task, uint8_t current_chnl);
typedef void (*hart_rx_complete_handler)(HartTaskStruct* task, uint8_t current_chnl);
typedef void (*hart_rx_error_handler)(HartTaskStruct* task, uint8_t current_chnl, HartCommErrType err_type);

typedef struct
{
  uint8_t                     error_occurred;
  hart_prepare_handler        make_request;
  hart_rx_complete_handler    complete;
  hart_rx_error_handler       error;
} HartTransaction;

////////////////////////////////////////////////////////////////////////////////
//
// private prototypes
//
////////////////////////////////////////////////////////////////////////////////
static void hart_select_comm_channel(uint8_t chnl);
static void hart_control_hart_mux(uint8_t mux_num, uint8_t on);
static void hart_control_hart_rts(uint8_t modem_num, uint8_t control, uint8_t from_irq);
static void hart_control_power(uint8_t chnl, uint8_t on_off);
static void hart_power_on_all_channels(void);

static void hart_start_uart(HartTaskStruct* task);
static void hart_reset_tx(HartTaskStruct* task);
static void hart_reset_rx(HartTaskStruct* task);
static void hart_start_transaction(HartTaskStruct* task);
static void hart_stop_transaction(HartTaskStruct* task);

static void hart_irq_start_tx(HartTaskStruct* task);
static void hart_irq_tx_next_byte(HartTaskStruct* task);
static void hart_irq_rx_common(HartTaskStruct* task, uint8_t rxb);

static void do_hart_transaction(HartTaskStruct* task, uint8_t current_chnl, HartTransaction* t);

static void HART_Task(void);

static void demo1_hart_make_request(HartTaskStruct* task, uint8_t current_chnl);
static void demo1_hart_handle_rx_error(HartTaskStruct* task, uint8_t current_chnl, HartCommErrType err_type);
static void demo1_hart_handle_rx_complete(HartTaskStruct* task, uint8_t current_chnl);


////////////////////////////////////////////////////////////////////////////////
//
// hart module privates
//
////////////////////////////////////////////////////////////////////////////////
static HartTaskStruct       _hart_task1 = 
{
  .name         = "HART1",
  .modem_no     = 0,
  .start_chnl   = 0,
  .end_chnl     = 5,
};

static HartTaskStruct       _hart_task2 = 
{
  .name         = "HART2",
  .modem_no     = 1,
  .start_chnl   = 6,
  .end_chnl     = 11,
};


static HartTransaction      _demo1_transaction =
{
  .make_request = demo1_hart_make_request,
  .complete     = demo1_hart_handle_rx_complete,
  .error        = demo1_hart_handle_rx_error,
};

////////////////////////////////////////////////////////////////////////////////
//
// private utilities
//
////////////////////////////////////////////////////////////////////////////////
static void
hart_control_hart_mux(uint8_t mux_num, uint8_t on)
{
  if(mux_num == 0)
  {
    if(on)
    {
      SetBit(PORTH, 0x08); 
    }
    else
    {
      ClrBit(PORTH, 0x08); 
    }
  }
  else
  {
    if(on)
    {
      SetBit(PORTJ, 0x08); 
    }
    else
    {
      ClrBit(PORTJ, 0x08); 
    }
  }
}

static void
hart_control_hart_rts(uint8_t modem_num, uint8_t control, uint8_t from_irq)
{
  if(modem_num == 0)
  {
    if(control == HART_ENABLE_MODULATOR)
    {
      if(from_irq)
      {
        PORTH &= ~0x04;
      }
      else
      {
        ClrBit(PORTH, 0x04); 
      }
    }
    else
    {
      if(from_irq)
      {
        PORTH |= 0x04;
      }
      else
      {
        SetBit(PORTH, 0x04); 
      }
    }
  }
  else
  {
    if(control == HART_ENABLE_MODULATOR)
    {
      if(from_irq)
      {
        PORTJ &= ~0x04;
      }
      else
      {
        ClrBit(PORTJ, 0x04); 
      }
    }
    else
    {
      if(from_irq)
      {
        PORTJ |= 0x04;
      }
      else
      {
        SetBit(PORTJ, 0x04); 
      }
    }
  }
}

static void
hart_select_comm_channel(uint8_t chnl)
{
  if(chnl < 6)
  {
    ClrBit(PORTK, 0x07);
    SetBit(PORTK, (chnl & 0x07));
  }
  else
  {
    ClrBit(PORTK, 0x38);
    SetBit(PORTK, ((chnl - 6) & 0x07) << 3);
  }
}

static void
hart_control_power(uint8_t chnl, uint8_t on_off)
{
  if(chnl <= 7)
  {
    if(on_off)
    {
      SetBit(PORTA, (1 << chnl));
    }
    else
    {
      ClrBit(PORTA, (1 << chnl));
    }
  }
  else if(chnl <= 11)
  {
    if(on_off)
    {
      SetBit(PORTJ, (1 << (chnl - 7 + 4)));
    }
    else
    {
      ClrBit(PORTJ, (1 << (chnl - 7 + 4)));
    }
  }
  else
  {
    // bug
  }
}

static void
hart_power_on_all_channels(void)
{
  uint8_t chnl;

  for(chnl = 0; chnl < HART_MAX_CHANNEL; chnl++)
  {
    hart_control_power(chnl, 1);
  }
}


////////////////////////////////////////////////////////////////////////////////
//
// common IRQ context utilities
//
// this routines shouldn't be called in task context.
//
////////////////////////////////////////////////////////////////////////////////
static void
hart_irq_start_tx(HartTaskStruct* task)
{
  uint8_t   b;

  b = task->tx_buf[task->tx_buf_ndx];
  task->tx_buf_ndx++;

  switch(task->modem_no)
  {
  case 0:
    // disable underrun and enable tx complete
    UCSR2B &= ~_BV(UDRIE2);
          
    UDR2 = b;
    UCSR2B |=  _BV(TXCIE2);
    break;

  case 1:
    UCSR3B &= ~_BV(UDRIE3);
          
    UDR3 = b;
    UCSR3B |=  _BV(TXCIE3);
    break;
  }
}

static void
hart_irq_tx_next_byte(HartTaskStruct* task)
{
  uint8_t   b;
  uint16_t    tndx;

  // to prevent IAR warning
  tndx = task->tx_buf_ndx;

  if(tndx >= task->tx_len)
  {
    //
    // TX complete
    // switch to RX mode immediately
    // so we won't lose any RX byte
    //

    // disable TX complete first
    switch(task->modem_no)
    {
    case 0:
      UCSR2B &=  ~_BV(TXCIE2);
      break;

    case 1:
      UCSR3B &=  ~_BV(TXCIE3);
      break;
    }

    //
    // enable demodulator on hart modem
    //
    hart_control_hart_rts(task->modem_no, HART_DISABLE_MODULATOR, HART_RTS_CONTROL_FROM_IRQ);
    return;
  }

  b = task->tx_buf[task->tx_buf_ndx];
  task->tx_buf_ndx++;

  switch(task->modem_no)
  {
  case 0:
    UDR2 = b;
    break;

  case 1:
    UDR3 = b;
    break;
  }
}

static void
hart_irq_rx_common(HartTaskStruct* task, uint8_t rxb)
{
  switch(hart_msg_parser_handle_byte(&task->hart_parser, rxb))
  {
  case HartMessageParsing_Pass:
    // nothing to do
    break;

  case HartMessageParsing_Error:
    OS_SignalEvent(HART_EVENT_RX_ERROR, &task->task);
    break;

  case HartMessageParsing_Complete:
    task->rx_len = task->hart_parser.rx_ndx;
    OS_SignalEvent(HART_EVENT_RX_COMPLETE, &task->task);
    break;
  }
}


////////////////////////////////////////////////////////////////////////////////
//
// HART0 USART2 IRQ handler
//
////////////////////////////////////////////////////////////////////////////////
#pragma vector=USART2_RX_vect
__interrupt void USART2_RXC(void)
{
  uint8_t   rxb;

  ENTER_IRQ;

  rxb = UDR2;
  hart_irq_rx_common(&_hart_task1, rxb);


  LEAVE_IRQ;
}

#pragma vector=USART2_TX_vect
__interrupt void USART2_TXC(void)
{
  ENTER_IRQ;

  hart_irq_tx_next_byte(&_hart_task1);

  LEAVE_IRQ;
}

#pragma vector=USART2_UDRE_vect
__interrupt void USART2_UDRE(void)
{
  ENTER_IRQ;

  hart_irq_start_tx(&_hart_task1);

  LEAVE_IRQ;
}

////////////////////////////////////////////////////////////////////////////////
//
// HART1 USART3 IRQ handler
//
////////////////////////////////////////////////////////////////////////////////
#pragma vector=USART3_RX_vect
__interrupt void USART3_RXC(void)
{
  uint8_t   rxb;

  ENTER_IRQ;

  rxb = UDR3;
  hart_irq_rx_common(&_hart_task2, rxb);

  LEAVE_IRQ;
}

#pragma vector=USART3_TX_vect
__interrupt void USART3_TXC(void)
{
  ENTER_IRQ;

  hart_irq_tx_next_byte(&_hart_task2);

  LEAVE_IRQ;
}

#pragma vector=USART3_UDRE_vect
__interrupt void USART3_UDRE(void)
{
  ENTER_IRQ;

  hart_irq_start_tx(&_hart_task2);

  LEAVE_IRQ;
}

////////////////////////////////////////////////////////////////////////////////
//
// UART Utilities
//
////////////////////////////////////////////////////////////////////////////////
static void
hart_start_uart(HartTaskStruct* task)
{
  #define USART2_EVEN_PARITY            (_BV(UPM21))
  #define USART2_ODD_PARITY             (_BV(UPM21) | _BV(UPM20))
  #define USART2_NO_PARITY              (0)

  #define USART3_EVEN_PARITY            (_BV(UPM31))
  #define USART3_ODD_PARITY             (_BV(UPM31) | _BV(UPM30))
  #define USART3_NO_PARITY              (0)
  
  #define USART2_1_STOP_BIT             (0)
  #define USART2_2_STOP_BIT             (_BV(USBS2))

  #define USART3_1_STOP_BIT             (0)
  #define USART3_2_STOP_BIT             (_BV(USBS3))

  uint16_t    baud = 1200;
  uint16_t    baud_setting = (XTAL_CPU / 4 / baud - 1) / 2;

  switch(task->modem_no)
  {
  case 0:
    // try U2X mode first
    UCSR2A      = _BV(U2X2);
    if (((XTAL_CPU == 16000000UL) && (baud == 57600)) || (baud_setting >4095))
    {
      UCSR2A      = 0;
      baud_setting  = (XTAL_CPU / 8 / baud - 1) / 2;
    }

    UBRR2H      = baud_setting >> 8;
    UBRR2L      = baud_setting;
    
    UCSR2C      = _BV(UCSZ20) | _BV(UCSZ21) | USART2_NO_PARITY | USART2_1_STOP_BIT;      // 8 bit data, no parity, 1 stop-bit
    UCSR2B      = _BV(RXEN2)  | _BV(TXEN2) | _BV(RXCIE2);
    break;

  case 1:
    UCSR3A      = _BV(U2X3);
    if (((XTAL_CPU == 16000000UL) && (baud == 57600)) || (baud_setting >4095))
    {
      UCSR3A      = 0;
      baud_setting  = (XTAL_CPU / 8 / baud - 1) / 2;
    }

    UBRR3H      = baud_setting >> 8;
    UBRR3L      = baud_setting;
    
    UCSR3C      = _BV(UCSZ30) | _BV(UCSZ31) | USART3_NO_PARITY | USART3_1_STOP_BIT;      // 8 bit data, no parity, 1 stop-bit
    UCSR3B      = _BV(RXEN3)  | _BV(TXEN3) | _BV(RXCIE3);
    break;

  default:
    // XXX fucked up
    break;
  }
}

static void
hart_reset_tx(HartTaskStruct* task)
{
  task->tx_buf_ndx  = 0;
  task->tx_len      = 0;

  hart_msg_encoder_reset(&task->hart_encoder);
}

static void
hart_reset_rx(HartTaskStruct* task)
{
  task->rx_buf_ndx  = 0;
  task->rx_len      = 0;

  hart_msg_parser_reset(&task->hart_parser);
}

static void
hart_start_transaction(HartTaskStruct* task)
{
  if(task->tx_len == 0)
  {
    // fucked up
    return;
  }

  // just to make sure
  task->tx_buf_ndx    = 0;

  switch(task->modem_no)
  {
  case 0:
    UCSR2B |= _BV(UDRIE2);
    break;

  case 1:
    UCSR3B |= _BV(UDRIE3);
    break;
  }
}

static void
hart_stop_transaction(HartTaskStruct* task)
{
  uint8_t     dummy = 0;

  //
  // XXX
  // this code assumes that TX is not in progress when this is called.
  // if not, you are pretty muched fucked up
  //

  //
  // disable hart demodulator, switching to TX mode
  //
  hart_control_hart_rts(task->modem_no, HART_ENABLE_MODULATOR, HART_RTS_CONTROL_FROM_TASK);

  //
  // no more RX data from modem
  // so clear any pending RX if there is any
  //
  OS_IncDI();

  switch(task->modem_no)
  {
  case 0:
    dummy = UDR2;
    break;

  case 1:
    dummy = UDR3;
    break;
  }
  OS_DecRI();

  (void)dummy;    // prevent warning
}

////////////////////////////////////////////////////////////////////////////////
//
// demo transaction
//
////////////////////////////////////////////////////////////////////////////////
static void
demo1_hart_make_request(HartTaskStruct* task, uint8_t current_chnl)
{
  uint8_t   addr[5] = {0, 0, 0, 0, 0};
  uint8_t   cmd = 2;                    // no fucking idea what to use
  uint8_t   data[] = {0, 1, 2, 3, 4};

  hart_msg_encoder_preamble(&task->hart_encoder, 5);        // we use preamble 5 for tx
#if 0
  hart_msg_encoder_long_start(&task->hart_encoder, 
      0x82,                                                 // master to slave request is always 82
      addr,                                                 // slave address
      cmd);                                                 // command to send
#else
  hart_msg_encoder_short_start(&task->hart_encoder, 
      0x82,                                                 // master to slave request is always 82
      0x00,                                                    // slave address
      cmd);                                                 // command to send
#endif

  //
  // request has no status bytes
  //

  hart_msg_encoder_data(&task->hart_encoder,
      data,                                                 // command data in request
      0);
      //(uint8_t)sizeof(data));                               // data length

  hart_msg_encoder_calc_csum(&task->hart_encoder);          // finally calculate checksum
}

static void
demo1_hart_handle_rx_error(HartTaskStruct* task, uint8_t current_chnl, HartCommErrType err_type)
{
  switch(err_type)
  {
  case HartCommErr_RX_Error:
    // XXX
    // do whatevern necessary here
    break;

  case HartCommErr_RX_Timeout:
    // XXX
    // do whatever necessary here
    break;
  }
}

static void
demo1_hart_handle_rx_complete(HartTaskStruct* task, uint8_t current_chnl)
{
  uint16_t    data;

  // 
  // XXX do whatever necessary here
  //

  //
  // task->hart_parser.status_ptr : 2 byte status pointer from slave
  //

  // XXX hkim arbitrary code here
  if(task->hart_parser.status_ptr[0] != 0 || task->hart_parser.status_ptr[1] == 1)
  {
    // negative response from slave
    return;
  }

  //
  // task->hart_parser.data_cnt   : user payload length
  //

  // XXX hkim arbitrary code here
  if(task->hart_parser.data_cnt != 2)
  {
    // expect 2 byte data response
    return;
  }

  //
  // task->hart_parser.data_ptr   : user payload pointer
  //

  // XXX hkim arbitrary code here
  data = task->hart_parser.data_ptr[0] << 8;
  data |= task->hart_parser.data_ptr[1];

  // to prevent warning
  (void)data;
}

////////////////////////////////////////////////////////////////////////////////
//
// core hart work
//
////////////////////////////////////////////////////////////////////////////////

static void
do_hart_transaction(HartTaskStruct* task, uint8_t current_chnl, HartTransaction* t)
{
  char              event_status;
  uint8_t           csum;

  t->error_occurred   = 1;

  hart_reset_rx(task);
  hart_reset_tx(task);

  hart_select_comm_channel(current_chnl);

  t->make_request(task, current_chnl);

  //
  // now set the tx length of tx_buf
  //
  task->tx_len = task->hart_encoder.tx_ndx;

  hart_start_transaction(task);

  event_status = OS_WaitEventTimed(HART_EVENT_RX_COMPLETE | HART_EVENT_RX_ERROR, HART_TRANSACTION_TIMEOUT);

  if(event_status == 0)
  {
    t->error(task, current_chnl, HartCommErr_RX_Timeout);
    goto exit_handling;
  }
  else if(event_status & HART_EVENT_RX_ERROR)
  {
    // protocol parsing error
    t->error(task, current_chnl, HartCommErr_RX_Error);
    goto exit_handling;
  }

  //
  // we calculate checksum in task context to reduce time spent in irq context
  //
  csum = hart_msg_calc_csum((const uint8_t*)task->rx_buf, task->rx_len);

  if(csum != task->hart_parser.csum)
  {
    // checksum mismatch
    t->error(task, current_chnl, HartCommErr_RX_Error);
    goto exit_handling;
  }

  t->complete(task, current_chnl);

  t->error_occurred   = 0;

exit_handling:
  hart_stop_transaction(task);

  //
  // not strictly necessary but this won't hurt
  //
  OS_ClearEvents(&task->task);
}

////////////////////////////////////////////////////////////////////////////////
//
// HART Task
//
////////////////////////////////////////////////////////////////////////////////
static void
HART_Task(void)
{
  OS_TASK*          taskPtr = OS_GetpCurrentTask();
  HartTaskStruct*   myTask  = container_of(taskPtr, HartTaskStruct, task);
  uint8_t           current_chnl;

  current_chnl = myTask->start_chnl;

  hart_msg_parser_init(&myTask->hart_parser, myTask->rx_buf, HART_MAX_RX_BUFFER_SIZE);
  hart_msg_encoder_init(&myTask->hart_encoder, myTask->tx_buf, HART_MAX_TX_BUFFER_SIZE);

  hart_start_uart(myTask);

  while(1)
  {
    do_hart_transaction(myTask, current_chnl, &_demo1_transaction);

    /*
    current_chnl++;
    if(current_chnl > myTask->end_chnl)
    {
      current_chnl = myTask->start_chnl;
    }
    */
  }
}

////////////////////////////////////////////////////////////////////////////////
//
// public interfaces
//
////////////////////////////////////////////////////////////////////////////////
void
hart_hw_init(void)
{
  ////////////////////////////////////////////////
  //
  // Signal   : HART-ADR0-5
  // Pin      : PK0-5
  // Dir      : Output
  // Purpose  : Used to select HART Data Mux
  //
  ////////////////////////////////////////////////
  DDRK    |= 0x1f;
  hart_select_comm_channel(0);


  ////////////////////////////////////////////////
  //
  // Signal   : HART-RTX0, HART-EN0
  //            HART-RTX1, HART-EN1
  // Pin      : PH2-3
  //            PJ2-3
  // Dir      : Output
  // Purpose  : Control HART MODEM0, HART MUX0
  //            Control HART MODEM1, HART MUX1
  //
  ////////////////////////////////////////////////
  DDRH |= 0x0c;
  DDRJ |= 0x0c;
  hart_control_hart_mux(0, 1);                              // turn on mux0
  hart_control_hart_mux(1, 1);                              // turn on mux1
  hart_control_hart_rts(0, HART_ENABLE_MODULATOR, HART_RTS_CONTROL_FROM_TASK);       // enable modulator for modem0
  hart_control_hart_rts(0, HART_ENABLE_MODULATOR, HART_RTS_CONTROL_FROM_TASK);       // enable modulator for modem1

  ////////////////////////////////////////////////
  //
  // Signal   : CHIP0-11
  // Pin      : PA0-7, PJ4-7
  // Dir      : Output
  // Purpose  : Used to control power supply of
  //            hart channel
  //
  ////////////////////////////////////////////////
  DDRA  |= 0xff;
  DDRJ  |= 0xf0;
  hart_power_on_all_channels();

  hart_diag_hw_init();
}

void
hart_start(void)
{
  OS_CREATETASK(&_hart_task1.task, "HART1", HART_Task, 90, _hart_task1.stack);
  OS_CREATETASK(&_hart_task2.task, "HART2", HART_Task, 90, _hart_task2.stack);

  hart_diag_task_start();
}
