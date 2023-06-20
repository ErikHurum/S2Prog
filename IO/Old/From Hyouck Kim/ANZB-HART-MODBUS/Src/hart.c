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
#include "hart_gpio.h"
#include "externals.h"


////////////////////////////////////////////////////////////////////////////////
//
// some notes
//
// 1) according to schematic,
//    HART MODEM0 is mapped to UART1
//    HART MODEM1 is mapped to UART2
//    HART MODEM2 is mapped to UART3
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// module configuration
//
////////////////////////////////////////////////////////////////////////////////
#define HART_CONTROL_RTS_IN_TASK          0

////////////////////////////////////////////////////////////////////////////////
//
// private defines
//
////////////////////////////////////////////////////////////////////////////////
#define TRUE      1
#define FALSE     0

#define HART_MINIMUM_MA_FEEDBACK_FOR_OK     0.0030        // 3mA
#define HART_TASK_STACK_SIZE            80
#define HART_MAX_TX_BUFFER_SIZE         384
#define HART_MAX_RX_BUFFER_SIZE         384
#define HART_EVENT_RX_COMPLETE          0x01
#define HART_EVENT_RX_ERROR             0x02
#define HART_EVENT_TX_COMPLETE          0x04
#define HART_TRANSACTION_TIMEOUT        500 //2000
#define HART_TASK_PRIORITY              120
#define HART_START_UP_POWER_UP_DELAY    1500

//
// for chinese radar.
// not sure about vega
//
#define HART_POLL_TARGET                1000     // every 1000ms


#define ENTER_IRQ                 \
   OS_EnterInterrupt();           \
   OS_EnterIntStack();

#define LEAVE_IRQ                 \
    OS_LeaveIntStack();           \
    OS_LeaveInterruptNoSwitch();

#define _BV(A)    __BIT_MASK(A)

#define USART1_EVEN_PARITY            (_BV(UPM11))
#define USART1_ODD_PARITY             (_BV(UPM11) | _BV(UPM10))
#define USART1_NO_PARITY              (0)

#define USART2_EVEN_PARITY            (_BV(UPM21))
#define USART2_ODD_PARITY             (_BV(UPM21) | _BV(UPM20))
#define USART2_NO_PARITY              (0)

#define USART3_EVEN_PARITY            (_BV(UPM31))
#define USART3_ODD_PARITY             (_BV(UPM31) | _BV(UPM30))
#define USART3_NO_PARITY              (0)

#define USART1_1_STOP_BIT             (0)
#define USART1_2_STOP_BIT             (_BV(USBS1))

#define USART2_1_STOP_BIT             (0)
#define USART2_2_STOP_BIT             (_BV(USBS2))

#define USART3_1_STOP_BIT             (0)
#define USART3_2_STOP_BIT             (_BV(USBS3))


#define offsetof(TYPE, MEMBER) ((uint16_t) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) (type *)((char *)ptr - offsetof(type,member))

typedef enum
{
  HartCommErr_RX_Error,
  HartCommErr_RX_Timeout,
  HartCommErr_RX_Checksum,
} HartCommErrType;

typedef struct
{
  OS_STACKPTR int             stack[HART_TASK_STACK_SIZE];
  OS_TASK                     tcb;
  const hart_modem_t          modem_no;
  const hart_channel_t        start_chnl;
  const hart_channel_t        end_chnl;

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

  //
  // semaphore lock for shared data access
  //
  OS_RSEMA                    channel_lock;
} HartTaskStruct;


typedef void (*hart_prepare_handler)(HartTaskStruct *task, hart_channel_t current_chnl);
typedef void (*hart_rx_complete_handler)(HartTaskStruct *task, hart_channel_t current_chnl);
typedef void (*hart_rx_error_handler)(HartTaskStruct *task, hart_channel_t current_chnl, HartCommErrType err_type);

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
static void hart_control_power(hart_channel_t chnl, HartChannelPowerStatus on_off);

static void hart_config_uart(HartTaskStruct *task);
static void hart_reset_tx(HartTaskStruct *task);
static void hart_reset_rx(HartTaskStruct *task);
static void hart_start_transaction(HartTaskStruct *task);

static void hart_irq_tx_next(HartTaskStruct *task);
static void hart_irq_finish_tx(HartTaskStruct *task);
static void hart_irq_rx_common(HartTaskStruct *task, uint8_t rxb);

static void do_hart_transaction(HartTaskStruct *task, hart_channel_t current_chnl, HartTransaction *t);

void HART_Task(void);

static void vega_radar_make_request(HartTaskStruct *task, hart_channel_t current_chnl);
static void vega_radar_handle_rx_error(HartTaskStruct *task, hart_channel_t current_chnl, HartCommErrType err_type);
static void vega_radar_handle_rx_complete(HartTaskStruct *task, hart_channel_t current_chnl);


////////////////////////////////////////////////////////////////////////////////
//
// hart module privates
//
////////////////////////////////////////////////////////////////////////////////
static HartTaskStruct       _hart_task0 =
{
  .modem_no     = hart_modem_0,
  .start_chnl   = hart_channel_0,
  .end_chnl     = hart_channel_3,
};

static HartTaskStruct       _hart_task1 =
{
  .modem_no     = hart_modem_1,
  .start_chnl   = hart_channel_4,
  .end_chnl     = hart_channel_7,
};

static HartTaskStruct       _hart_task2 =
{
  .modem_no     = hart_modem_2,
  .start_chnl   = hart_channel_8,
  .end_chnl     = hart_channel_11,
};


static HartTransaction      _demo1_transaction =
{
  .make_request = vega_radar_make_request,
  .complete     = vega_radar_handle_rx_complete,
  .error        = vega_radar_handle_rx_error,
};

static HartChannel          _hart_channels[HART_MAX_CHANNEL] =
{
  { .chnl_num       = hart_channel_0  },
  { .chnl_num       = hart_channel_1  },
  { .chnl_num       = hart_channel_2  },
  { .chnl_num       = hart_channel_3  },
  { .chnl_num       = hart_channel_4  },
  { .chnl_num       = hart_channel_5  },
  { .chnl_num       = hart_channel_6  },
  { .chnl_num       = hart_channel_7  },
  { .chnl_num       = hart_channel_8  },
  { .chnl_num       = hart_channel_9  },
  { .chnl_num       = hart_channel_10 },
  { .chnl_num       = hart_channel_11 },
};

#define HART_EEPROM_START_ADDRESS         0x800
#define HART_EEPROM_RSP_DELAY_ADDRESS     (HART_EEPROM_START_ADDRESS + 2)

static volatile uint16_t          _eeprom_power_status;
static volatile uint16_t          _rsp_delay = 0;

////////////////////////////////////////////////////////////////////////////////
//
// hart channel specifics
//
////////////////////////////////////////////////////////////////////////////////
/*
void hart_debug_check(void)
{
  if((UCSR2B & _BV(TXCIE2)) == 0)
  {
    while(1)
      ;
  }
}
*/

static inline void
hart_channel_lock(HartChannel *channel)
{
  switch (channel->chnl_num) {
  case hart_channel_0:
  case hart_channel_1:
  case hart_channel_2:
  case hart_channel_3:
    OS_Use(&_hart_task0.channel_lock);
    break;

  case hart_channel_4:
  case hart_channel_5:
  case hart_channel_6:
  case hart_channel_7:
    OS_Use(&_hart_task1.channel_lock);
    break;

  case hart_channel_8:
  case hart_channel_9:
  case hart_channel_10:
  case hart_channel_11:
    OS_Use(&_hart_task2.channel_lock);
    break;
  }
}

static inline void
hart_channel_unlock(HartChannel *channel)
{
  switch (channel->chnl_num) {
  case hart_channel_0:
  case hart_channel_1:
  case hart_channel_2:
  case hart_channel_3:
    OS_Unuse(&_hart_task0.channel_lock);
    break;

  case hart_channel_4:
  case hart_channel_5:
  case hart_channel_6:
  case hart_channel_7:
    OS_Unuse(&_hart_task1.channel_lock);
    break;

  case hart_channel_8:
  case hart_channel_9:
  case hart_channel_10:
  case hart_channel_11:
    OS_Unuse(&_hart_task2.channel_lock);
    break;
  }
}

static inline void
hart_channel_reset(HartChannel *channel)
{
  hart_channel_lock(channel);

  channel->status         = HartChannelStatus_No_Response;
  channel->power_status   = HartChannelPowerStatus_OFF;

  channel->ma_feedback    = 0.0;

  channel->rx_invalid_msg = 0;
  channel->rx_csum_err    = 0;
  channel->rx_timeout     = 0;
  channel->total_reqs     = 0;
  channel->total_success  = 0;

  channel->last_access_time = 0;

  hart_channel_unlock(channel);
}

static inline void
hart_channel_set_status(HartChannel *channel, HartChannelStatus status)
{
  hart_channel_lock(channel);

  if(channel->power_status == HartChannelPowerStatus_OFF)
  {
    channel->status     = HartChannelStatus_No_Response;
  }
  else
  {
    channel->status     = status;
  }

  hart_channel_unlock(channel);
}

static uint8_t
hart_channel_ready_to_poll(hart_channel_t chnl)
{
  uint8_t   ret = FALSE;

  hart_channel_lock(&_hart_channels[chnl]);

  if (_hart_channels[chnl].power_status == HartChannelPowerStatus_ON &&
      _hart_channels[chnl].ma_feedback >= HART_MINIMUM_MA_FEEDBACK_FOR_OK)
  {
    ret = TRUE;
  }

  hart_channel_unlock(&_hart_channels[chnl]);

  return ret;
}

static inline void
hart_channel_inc_stat(HartChannel *channel, HartChannelStatItem item)
{
  hart_channel_lock(channel);

  switch (item) {
  case HartChannelStatItem_RX_INVALID:
    channel->rx_invalid_msg++;
    break;

  case HartChannelStatItem_RX_CSUM:
    channel->rx_csum_err++;
    break;

  case HartChannelStatItem_RX_TIMEOUT:
    channel->rx_timeout++;
    break;

  case HartChannelStatItem_TOTAL_REQS:
    channel->total_reqs++;
    break;

  case HartChannelStatItem_TOTAL_SUCCESS:
    channel->total_success++;
    break;
  }

  hart_channel_unlock(channel);
}


////////////////////////////////////////////////////////////////////////////////
//
// private utilities
//
////////////////////////////////////////////////////////////////////////////////
static void
hart_control_power(hart_channel_t chnl, HartChannelPowerStatus on_off)
{
  //
  // XXX be careful about channel lock when calling this function.
  //
  HartChannel *c = &_hart_channels[chnl];

  if (on_off == HartChannelPowerStatus_ON) {
    hart_gpio_power_on(chnl);
  } else {
    hart_gpio_power_off(chnl);
  }

  c->power_status   = on_off;

  if(on_off == HartChannelPowerStatus_OFF)
  {
    c->status     = HartChannelStatus_No_Response;
  }
}

static void
hart_control_modem_control_rx(hart_modem_t   modem, uint8_t enable, uint8_t from_irq)
{
  if (enable) {
    if (from_irq) {
      hart_gpio_modem_rx_enable_irq(modem);
    } else {
      hart_gpio_modem_rx_enable(modem);
    }
  } else {
    if (from_irq) {
      hart_gpio_modem_rx_disable_irq(modem);
    } else {
      hart_gpio_modem_rx_disable(modem);
    }
  }

  switch (modem) {
  case hart_modem_0:
    if (enable) {
      UCSR1B |= _BV(RXEN1);
    } else {
      UCSR1B &= ~_BV(RXEN1);
    }
    break;

  case hart_modem_1:
    if (enable) {
      UCSR2B |= _BV(RXEN2);
    } else {
      UCSR2B &= ~_BV(RXEN2);
    }
    break;

  case hart_modem_2:
    if (enable) {
      UCSR3B |= _BV(RXEN3);
    } else {
      UCSR3B &= ~_BV(RXEN3);
    }
    break;
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
hart_irq_tx_next(HartTaskStruct *task)
{
  uint8_t   b;
  uint16_t  len;
  uint16_t  tndx;

  tndx = task->tx_buf_ndx;
  len  = task->tx_len;
  b = task->tx_buf[tndx];

  tndx++;
  switch (task->modem_no) {
  case hart_modem_0:
    if (tndx >= len) {
      UCSR1A |=  _BV(TXC1);       // clear TXC flag if set by any chance
      UCSR1B &= ~_BV(UDRIE1);
      UCSR1B |=  _BV(TXCIE1);
    }
    UDR1 = b;
    break;

  case hart_modem_1:
    if (tndx >= len) {
      UCSR2A |=  _BV(TXC2);       // clear TXC flag if set by any chance
      UCSR2B &= ~_BV(UDRIE2);
      UCSR2B |=  _BV(TXCIE2);
    }
    UDR2 = b;
    break;

  case hart_modem_2:
    if (tndx >= len) {
      UCSR3A |=  _BV(TXC3);       // clear TXC flag if set by any chance
      UCSR3B &= ~_BV(UDRIE3);
      UCSR3B |=  _BV(TXCIE3);
    }
    UDR3 = b;
    break;
  }
  task->tx_buf_ndx = tndx;
}

static void
hart_irq_finish_tx(HartTaskStruct *task)
{
  switch (task->modem_no)
  {
  case hart_modem_0:
    UCSR1B &=  ~_BV(TXCIE1);
    break;

  case hart_modem_1:
    UCSR2B &=  ~_BV(TXCIE2);
    break;

  case hart_modem_2:
    UCSR3B &=  ~_BV(TXCIE3);
    break;
  }

  //
  // enable demodulator on hart modem
  //
#if HART_CONTROL_RTS_IN_TASK  == 0
  //hart_gpio_modem_rx_enable_irq(task->modem_no);
  hart_control_modem_control_rx(task->modem_no, TRUE, TRUE);
#endif
  OS_SignalEvent(HART_EVENT_TX_COMPLETE, &task->tcb);

  return;
}

static void
hart_irq_rx_common(HartTaskStruct *task, uint8_t rxb)
{
  switch (hart_msg_parser_handle_byte(&task->hart_parser, rxb))
  {
  default:
    //OS_Delay(1);
    // nothing to do
    break;
  case HartMessageParsing_Pass:
    //OS_Delay(1);
    // nothing to do
    break;

  case HartMessageParsing_Error:
    OS_SignalEvent(HART_EVENT_RX_ERROR, &task->tcb);
    break;

  case HartMessageParsing_Complete:
    task->rx_len = task->hart_parser.rx_ndx;
    OS_SignalEvent(HART_EVENT_RX_COMPLETE, &task->tcb);
    break;
  }
}


////////////////////////////////////////////////////////////////////////////////
//
// HART0 USART1 IRQ handler
//
////////////////////////////////////////////////////////////////////////////////
#pragma vector=USART1_RX_vect
__interrupt void USART1_RXC(void)
{
  ENTER_IRQ;

  hart_irq_rx_common(&_hart_task0, UDR1);

  LEAVE_IRQ;
}

#pragma vector=USART1_TX_vect
__interrupt void USART1_TXC(void)
{
  ENTER_IRQ;

  hart_irq_finish_tx(&_hart_task0);

  LEAVE_IRQ;
}

#pragma vector=USART1_UDRE_vect
__interrupt void USART1_UDRE(void)
{
  ENTER_IRQ;

  hart_irq_tx_next(&_hart_task0);

  LEAVE_IRQ;
}

////////////////////////////////////////////////////////////////////////////////
//
// HART1 USART2 IRQ handler
//
////////////////////////////////////////////////////////////////////////////////
#pragma vector=USART2_RX_vect
__interrupt void USART2_RXC(void)
{
  ENTER_IRQ;

  hart_irq_rx_common(&_hart_task1, UDR2);


  LEAVE_IRQ;
}

#pragma vector=USART2_TX_vect
__interrupt void USART2_TXC(void)
{
  ENTER_IRQ;

  hart_irq_finish_tx(&_hart_task1);

  LEAVE_IRQ;
}

#pragma vector=USART2_UDRE_vect
__interrupt void USART2_UDRE(void)
{
  ENTER_IRQ;

  hart_irq_tx_next(&_hart_task1);

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
  ENTER_IRQ;

  hart_irq_rx_common(&_hart_task2, UDR3);

  LEAVE_IRQ;
}

#pragma vector=USART3_TX_vect
__interrupt void USART3_TXC(void)
{
  ENTER_IRQ;

  hart_irq_finish_tx(&_hart_task2);

  LEAVE_IRQ;
}

#pragma vector=USART3_UDRE_vect
__interrupt void USART3_UDRE(void)
{
  ENTER_IRQ;

  hart_irq_tx_next(&_hart_task2);

  LEAVE_IRQ;
}

////////////////////////////////////////////////////////////////////////////////
//
// UART Utilities
//
////////////////////////////////////////////////////////////////////////////////
static void
hart_config_uart(HartTaskStruct *task)
{
  uint16_t    baud = 1200;
  uint16_t    baud_setting = (XTAL_CPU / 4 / baud - 1) / 2;

  switch (task->modem_no) {
  case hart_modem_0:
    // try U2X mode first
    UCSR1A      = _BV(U2X1);
    if (((XTAL_CPU == 16000000UL) && (baud == 57600)) || (baud_setting > 4095)) {
      UCSR1A      = 0;
      baud_setting  = (XTAL_CPU / 8 / baud - 1) / 2;
    }

    UBRR1H      = baud_setting >> 8;
    UBRR1L      = baud_setting;

    UCSR1C      = _BV(UCSZ10) | _BV(UCSZ11) | USART1_ODD_PARITY | USART1_1_STOP_BIT;
    UCSR1B      = _BV(RXEN1) | _BV(TXEN1) | _BV(RXCIE1);
    break;

  case hart_modem_1:
    UCSR2A      = _BV(U2X2);
    if (((XTAL_CPU == 16000000UL) && (baud == 57600)) || (baud_setting > 4095)) {
      UCSR2A      = 0;
      baud_setting  = (XTAL_CPU / 8 / baud - 1) / 2;
    }

    UBRR2H      = baud_setting >> 8;
    UBRR2L      = baud_setting;

    UCSR2C      = _BV(UCSZ20) | _BV(UCSZ21) | USART2_ODD_PARITY | USART2_1_STOP_BIT;
    UCSR2B      = _BV(RXEN2) | _BV(TXEN2) | _BV(RXCIE2);
    break;

  case hart_modem_2:
    UCSR3A      = _BV(U2X3);
    if (((XTAL_CPU == 16000000UL) && (baud == 57600)) || (baud_setting > 4095)) {
      UCSR3A      = 0;
      baud_setting  = (XTAL_CPU / 8 / baud - 1) / 2;
    }

    UBRR3H      = baud_setting >> 8;
    UBRR3L      = baud_setting;

    UCSR3C      = _BV(UCSZ30) | _BV(UCSZ31) | USART3_ODD_PARITY | USART3_1_STOP_BIT;
    UCSR3B      = _BV(RXEN3) | _BV(TXEN3) | _BV(RXCIE3);
    break;
  }
}

static void
hart_reset_tx(HartTaskStruct *task)
{
  task->tx_buf_ndx  = 0;
  task->tx_len      = 0;

  hart_msg_encoder_reset(&task->hart_encoder);
}

static void
hart_reset_rx(HartTaskStruct *task)
{
  task->rx_buf_ndx  = 0;
  task->rx_len      = 0;

  hart_msg_parser_reset(&task->hart_parser);
}

static void
hart_start_transaction(HartTaskStruct *task)
{
  if (task->tx_len == 0) {
    // XXX fucked up. there is a bug
    return;
  }

  // just to make sure
  task->tx_buf_ndx    = 0;

  switch (task->modem_no) {
  case hart_modem_0:
    UCSR1B |= _BV(UDRIE1);
    break;

  case hart_modem_1:
    UCSR2B |= _BV(UDRIE2);
    break;

  case hart_modem_2:
    UCSR3B |= _BV(UDRIE3);
    break;
  }
}

////////////////////////////////////////////////////////////////////////////////
//
// demo transaction
//
// IT IS YOUR JOB TO OVERRIDE THESE CALLBACKS
//
////////////////////////////////////////////////////////////////////////////////
static void
vega_radar_make_request(HartTaskStruct *task, hart_channel_t current_chnl)
{
  uint8_t   addr[5] = { 0x80, 0x00, 0x00, 0x00, 0x00 };
  uint8_t   cmd = 0x03;                                      // no idea what to use

  hart_msg_encoder_preamble(&task->hart_encoder, 5);        // we use preamble 5 for tx
  hart_msg_encoder_long_start(&task->hart_encoder,
      0x82,                                                 // master to slave request is always 82
      addr,                                                 // slave address
      cmd);                                                 // command to send
  //
  // request has no status bytes
  //

  hart_msg_encoder_data(&task->hart_encoder,
      NULL,                                                 // command data in request
      0);                                                   // no data. thus data length 0

  hart_msg_encoder_calc_csum(&task->hart_encoder);          // finally calculate checksum
}

static void
vega_radar_handle_rx_error(HartTaskStruct *task, hart_channel_t current_chnl, HartCommErrType err_type)
{
  switch (err_type) {
  case HartCommErr_RX_Error:
    // XXX
    // do whatevern necessary here
    break;

  case HartCommErr_RX_Timeout:
    // XXX
    // do whatever necessary here
    break;

  case HartCommErr_RX_Checksum:
    // XXX
    // do whatever necessary here
    break;
  }
}

static void
vega_radar_handle_rx_complete(HartTaskStruct *task, hart_channel_t current_chnl)
{
  uint16_t data;

  //
  // XXX do whatever necessary here
  //

  //
  // task->hart_parser.status_ptr : 2 byte status pointer from slave
  //

  //
  // seems like the so called radar sends this status bytes
  //
  if (task->hart_parser.status_ptr[0] != 0 || task->hart_parser.status_ptr[1] != 0x40)
  {
    // negative response from slave
    //     TData.Ana.Result[current_chnl] = task->hart_parser.ProsData[0];   // PROData 0 is the Hart PV(Primary Value)
    return;
  }

  //
  // task->hart_parser.data_cnt   : user payload length
  //

  // XXX hkim arbitrary code here
  // expect 2 byte data response???
  if (task->hart_parser.data_cnt != 2)
  {
    char floatBuf[4];
    HartChannel *chnl = hart_channel_get_with_lock(current_chnl);

    // current via HART
    floatBuf[0] = task->hart_parser.data_ptr[3];
    floatBuf[1] = task->hart_parser.data_ptr[2];
    floatBuf[2] = task->hart_parser.data_ptr[1];
    floatBuf[3] = task->hart_parser.data_ptr[0];

    chnl->hart_current = *((float*)floatBuf);
    chnl->ma_feedback /= 1.0028280;

    floatBuf[0] = task->hart_parser.data_ptr[8];
    floatBuf[1] = task->hart_parser.data_ptr[7];
    floatBuf[2] = task->hart_parser.data_ptr[6];
    floatBuf[3] = task->hart_parser.data_ptr[5];

    chnl->distance = *((float*)floatBuf);

    floatBuf[0] = task->hart_parser.data_ptr[13];
    floatBuf[1] = task->hart_parser.data_ptr[12];
    floatBuf[2] = task->hart_parser.data_ptr[11];
    floatBuf[3] = task->hart_parser.data_ptr[10];

    chnl->level = *((float*)floatBuf);

#if 0 // hkim
    TData.Hart.HartCurrent[current_chnl] = task->hart_parser.Current;   // PROData 0 is the Hart PV(Primary Value)
    TData.Hart.ADCurrent[current_chnl] = chnl->ma_feedback / 1.0028280; // PROData 0 is the Hart PV(Primary Value)
    TData.Hart.Result[current_chnl] = task->hart_parser.ProsData[0];    // PROData 0 is the Hart PV(Primary Value)
    TData.Hart.Distance[current_chnl] = task->hart_parser.ProsData[0];  // PROData 0 is the Hart PV(Primary Value)
    TData.Hart.Level[current_chnl] = task->hart_parser.ProsData[1];     // PROData 0 is the Hart PV(Primary Value)
#else
    TData.Hart.HartCurrent[current_chnl] = chnl->hart_current;
    TData.Hart.ADCurrent[current_chnl] = chnl->ma_feedback / 1.0028280;
    TData.Hart.Result[current_chnl] = chnl->distance;
    TData.Hart.Distance[current_chnl] = chnl->distance;
    TData.Hart.Level[current_chnl] = chnl->level;
#endif
    hart_channel_put_with_unlock(chnl);

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
do_hart_transaction(HartTaskStruct *task, hart_channel_t current_chnl, HartTransaction *t)
{
  char              event_status;
  uint8_t           csum;
  HartChannel *chnl = &_hart_channels[current_chnl];

  hart_channel_inc_stat(chnl, HartChannelStatItem_TOTAL_REQS);

  t->error_occurred   = 1;

  hart_reset_rx(task);
  hart_reset_tx(task);

  hart_gpio_channel_select(current_chnl);

  t->make_request(task, current_chnl);

  //
  // now set the tx length of tx_buf
  //
  task->tx_len = task->hart_encoder.tx_ndx;

  hart_start_transaction(task);

  event_status = OS_WaitEvent(HART_EVENT_TX_COMPLETE);

#if HART_CONTROL_RTS_IN_TASK == 1
  //hart_gpio_modem_rx_enable(task->modem_no);
  hart_control_modem_control_rx(task->modem_no, TRUE, FALSE);
#endif

  event_status = OS_WaitSingleEventTimed(HART_EVENT_RX_COMPLETE | HART_EVENT_RX_ERROR, HART_TRANSACTION_TIMEOUT);

  //hart_gpio_modem_rx_disable(task->modem_no);
  hart_control_modem_control_rx(task->modem_no, FALSE, FALSE);

  if (event_status == 0) {
    hart_channel_inc_stat(chnl, HartChannelStatItem_RX_TIMEOUT);
    hart_channel_set_status(chnl, HartChannelStatus_No_Response);

    t->error(task, current_chnl, HartCommErr_RX_Timeout);
    goto exit_handling;
  } else if (event_status & HART_EVENT_RX_ERROR) {
    // protocol parsing error
    hart_channel_inc_stat(chnl, HartChannelStatItem_RX_INVALID);
    hart_channel_set_status(chnl, HartChannelStatus_Invalid_Response);

    t->error(task, current_chnl, HartCommErr_RX_Error);
    goto exit_handling;
  }

  hart_channel_set_status(chnl, HartChannelStatus_Responding);

  // we calculate checksum in task context to reduce time spent in irq context
  csum = hart_msg_calc_csum((const uint8_t *)task->rx_buf, task->rx_len);

  if (csum != task->hart_parser.csum) {
    hart_channel_inc_stat(chnl, HartChannelStatItem_RX_CSUM);

    // checksum mismatch
    t->error(task, current_chnl, HartCommErr_RX_Checksum);
    goto exit_handling;
  }

  hart_channel_inc_stat(chnl, HartChannelStatItem_TOTAL_SUCCESS);

  t->complete(task, current_chnl);

  t->error_occurred   = 0;

exit_handling:
  //
  // not strictly necessary but this won't hurt
  //
  OS_ClearEvents(&task->tcb);
}

////////////////////////////////////////////////////////////////////////////////
//
// HART Task
//
////////////////////////////////////////////////////////////////////////////////
static inline uint32_t
time_delta(uint32_t last_time)
{
  return (OS_GetTime32() - last_time);
}

void HART_Task(void)
{
  OS_TASK *taskPtr = OS_GetpCurrentTask();
  HartTaskStruct *myTask  = container_of(taskPtr, HartTaskStruct, tcb);
  hart_channel_t    current_chnl;
  uint8_t           num_chnls_handled;
  uint32_t          delta;

  hart_msg_parser_init(&myTask->hart_parser, myTask->rx_buf, HART_MAX_RX_BUFFER_SIZE);
  hart_msg_encoder_init(&myTask->hart_encoder, myTask->tx_buf, HART_MAX_TX_BUFFER_SIZE);

  hart_config_uart(myTask);
  hart_control_modem_control_rx(myTask->modem_no, FALSE, FALSE);

  while (1) {
    num_chnls_handled = 0;
    hart_for_each_task_channel(current_chnl, myTask) {
      if (hart_channel_ready_to_poll(current_chnl) == TRUE) {

        if(HART_POLL_TARGET != 0 && 
           _hart_channels[current_chnl].status == HartChannelStatus_Responding)
        {
          delta = time_delta(_hart_channels[current_chnl].last_access_time);
          if(delta < HART_POLL_TARGET)
          {
            OS_Delay(HART_POLL_TARGET - delta);
          }
        }

        num_chnls_handled++;

        _hart_channels[current_chnl].last_access_time = OS_GetTime32();
        do_hart_transaction(myTask, current_chnl, &_demo1_transaction);
      }
      else
      {
        _hart_channels[current_chnl].last_access_time = OS_GetTime32();
      }
    }

    if (num_chnls_handled == 0) {
      //
      // if all the task channels are either power down or
      // fault state, then get some sleep
      // much better cooperative bullshit
      //
      OS_Delay(200);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//
// Modem start-up task
//
// Note: This is starting a task for the first two Hart modems. After starting
// it will handle the last Hart modem.
//
////////////////////////////////////////////////////////////////////////////////
static void
__hart_load_eeprom(void)
{
  ReadEEPROMBuffer(HART_EEPROM_START_ADDRESS, sizeof(uint16_t), (char*)&_eeprom_power_status);
  ReadEEPROMBuffer(HART_EEPROM_RSP_DELAY_ADDRESS, sizeof(uint16_t), (char*)&_rsp_delay);

  if (_rsp_delay > 5000)
  {
    _rsp_delay = 0;
  }
}

static void
HART_StartUPTask(void)
{
  hart_channel_t chnl;

  //
  // just to make sure.
  //
  hart_for_each_channel(chnl) {
    hart_control_power(chnl, HartChannelPowerStatus_OFF);
  }

  //
  // Read Power Status from EEPROM
  //
  __hart_load_eeprom();


  hart_diag_task_start();

  //
  // now power on modem one by one.
  // don't care about start up time
  //
  hart_for_each_channel(chnl) {
    if(_eeprom_power_status & (1 << chnl))
    {
      hart_control_power(chnl, HartChannelPowerStatus_ON);
    }

    if (chnl == _hart_task0.end_chnl)
    {
      OS_CREATETASK(&_hart_task0.tcb, "HART0", HART_Task, HART_TASK_PRIORITY, _hart_task0.stack);
    }
    else if (chnl == _hart_task1.end_chnl)
    {
      OS_CREATETASK(&_hart_task1.tcb, "HART1", HART_Task, HART_TASK_PRIORITY, _hart_task1.stack);
    }
    OS_Delay(HART_START_UP_POWER_UP_DELAY);
  }

#if USE_MODBUS_PROTOCOL == 1
  //
  // now it's safe to kick off MODBUS task
  //
  {
    extern void modbus_rtu_notify_go(void);
    
    modbus_rtu_notify_go();
  }
#endif

  HART_Task();
}

////////////////////////////////////////////////////////////////////////////////
//
// public interfaces
//
////////////////////////////////////////////////////////////////////////////////
void
hart_start(void)
{
  hart_channel_t   i;

  OS_CREATERSEMA(&_hart_task0.channel_lock);
  OS_CREATERSEMA(&_hart_task1.channel_lock);
  OS_CREATERSEMA(&_hart_task2.channel_lock);

  hart_for_each_channel(i) {
    hart_channel_reset(&_hart_channels[i]);
  }

  hart_diag_init();

  OS_CREATETASK(&_hart_task2.tcb, "HART2", HART_StartUPTask, HART_TASK_PRIORITY, _hart_task2.stack);
}


HartChannel*
hart_channel_get_with_lock(hart_channel_t chnl_num)
{
  HartChannel *chnl = &_hart_channels[chnl_num];

  hart_channel_lock(chnl);
  return chnl;
}

void
hart_channel_put_with_unlock(HartChannel *chnl)
{
  hart_channel_unlock(chnl);
}

void
hart_channel_power_on_off(hart_channel_t chnl_num, uint8_t on)
{
  HartChannel*  chnl;
  uint8_t       changed = FALSE;

  chnl = hart_channel_get_with_lock(chnl_num);
  if(on && chnl->power_status == HartChannelPowerStatus_OFF)
  {
    // turn on
    hart_control_power(chnl_num, HartChannelPowerStatus_ON);
    _eeprom_power_status |= (1 << chnl_num);
    changed = TRUE;
  }
  else if(!on && chnl->power_status == HartChannelPowerStatus_ON)
  {
    // turn off
    hart_control_power(chnl_num, HartChannelPowerStatus_OFF);
    _eeprom_power_status &= ~(1 << chnl_num);
    changed = TRUE;
  }
  hart_channel_put_with_unlock(chnl);

  if(changed)
  {
    WriteEEPROMU16(HART_EEPROM_START_ADDRESS, _eeprom_power_status);
  }
}

uint16_t
hart_get_rsp_delay(void)
{
  return _rsp_delay;
}

void
hart_set_rsp_delay(uint16_t delay)
{
  if (delay != _rsp_delay && delay <= 5000)
  {
    _rsp_delay = delay;
    WriteEEPROMU16(HART_EEPROM_RSP_DELAY_ADDRESS, _rsp_delay);
  }
}
