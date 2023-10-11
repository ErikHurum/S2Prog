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


extern volatile char CriticalComError = 0;
////////////////////////////////////////////////////////////////////////////////
//
// private prototypes
//
////////////////////////////////////////////////////////////////////////////////
static void hart_control_power(hart_channel_t chnl, HartChannelPowerStatus on_off);

static void hart_config_uart(HartTaskStruct *task);
static void hart_reset_tx(HartTaskStruct *task);
static void hart_reset_rx(HartTaskStruct *task, hart_channel_t current_chnl);
static void hart_start_transaction(HartTaskStruct *task);

static void hart_irq_tx_next(HartTaskStruct *task);
static void hart_irq_finish_tx(HartTaskStruct *task);

static void do_hart_transaction(HartTaskStruct *task, hart_channel_t current_chnl, HartTransaction *t);

void HART_Task(void *pVoid);

static void vega_radar_make_request(HartTaskStruct *task, hart_channel_t current_chnl);
static void vega_radar_handle_rx_error(HartTaskStruct *task, hart_channel_t current_chnl, HartCommErrType err_type);
//static void vega_radar_handle_rx_complete(HartTaskStruct *task, hart_channel_t current_chnl);
static uint8_t ReceiveReply(HartTaskStruct *task, hart_channel_t current_chnl);

HartTaskStruct       _hart_task0 =
{
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
    .StackTest1   = { "123456789" },
    .StackTest2   = { "123456789" },
#endif
    .modem_no     = hart_modem_0,
    .start_chnl   = hart_channel_0,
    .end_chnl     = hart_channel_3,
};

HartTaskStruct       _hart_task1 =
{
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
    .StackTest1   = { "123456789" },
    .StackTest2   = { "123456789" },
#endif
    .modem_no     = hart_modem_1,
    .start_chnl   = hart_channel_4,
    .end_chnl     = hart_channel_7,
};

HartTaskStruct       _hart_task2 =
{
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
    .StackTest1   = { "123456789" },
    .StackTest2   = { "123456789" },
#endif
    .modem_no     = hart_modem_2,
    .start_chnl   = hart_channel_8,
    .end_chnl     = hart_channel_11,
};

////////////////////////////////////////////////////////////////////////////////
//
// hart module privates
//
////////////////////////////////////////////////////////////////////////////////
static HartTransaction   _demo1_transaction =
{
    .make_request = vega_radar_make_request,
    .complete     = ReceiveReply, //vega_radar_handle_rx_complete,
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

/*
static inline void hart_channel_lock(HartChannel *channel) {
    switch ( channel->chnl_num ) {
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

static inline void hart_channel_unlock(HartChannel *channel) {
    switch ( channel->chnl_num ) {
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
*/
static inline void hart_channel_reset(HartChannel *channel) {
    //hart_channel_lock(channel);

    channel->status         = HartChannelStatus_No_Response;
    channel->power_status   = HartChannelPowerStatus_OFF;

    channel->rx_invalid_msg = 0;
    channel->rx_csum_err    = 0;
    channel->rx_timeout     = 0;
    channel->total_reqs     = 0;
    channel->total_success  = 0;

    //hart_channel_unlock(channel);
}

static inline void hart_channel_set_status(HartChannel *channel, HartChannelStatus status) {
    //hart_channel_lock(channel);

    channel->status     = status;

    //hart_channel_unlock(channel);
}

static inline void hart_channel_set_power_status(HartChannel *channel, HartChannelPowerStatus status) {
    //hart_channel_lock(channel);

    channel->power_status   = status;

    //hart_channel_unlock(channel);
}

static inline void hart_channel_inc_stat(HartChannel *channel, HartChannelStatItem item) {
    //hart_channel_lock(channel);

    switch ( item ) {
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

    //hart_channel_unlock(channel);
}


////////////////////////////////////////////////////////////////////////////////
//
// private utilities
//
////////////////////////////////////////////////////////////////////////////////
static void hart_control_power(hart_channel_t chnl, HartChannelPowerStatus on_off) {
    //
    // XXX be careful about channel lock when calling this function.
    //
    HartChannel *c = &_hart_channels[chnl];

    if ( on_off == HartChannelPowerStatus_ON ) {
        hart_gpio_power_on(chnl);
    } else {
        hart_gpio_power_off(chnl);
    }
    hart_channel_set_power_status(c, on_off);
}

static void hart_control_Rx_Enable(hart_modem_t   modem, uint8_t enable) {
    switch ( modem ) {
    case hart_modem_0:
        if ( enable ) {
            UCSR1B |= _BV(RXEN1);
        } else {
            UCSR1B &= ~_BV(RXEN1);
        }
        break;

    case hart_modem_1:
        if ( enable ) {
            UCSR2B |= _BV(RXEN2);
        } else {
            UCSR2B &= ~_BV(RXEN2);
        }
        break;

    case hart_modem_2:
        if ( enable ) {
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
static void hart_irq_tx_next(HartTaskStruct *task) {
    uint8_t  tndx = task->tx_buf_ndx;
    uint16_t len  = task->tx_len;
    uint8_t b     = task->tx_buf[tndx++];
    OS_DI();             // Disable before allowing interrupt

    switch ( task->modem_no ) {
    case hart_modem_0:
        if ( tndx >= len ) {
            UCSR1A |=  _BV(TXC1);       // clear TXC flag if set by any chance
            UCSR1B &= ~_BV(UDRIE1);
            UCSR1B |=  _BV(TXCIE1);
        }
        UDR1 = b;
        break;

    case hart_modem_1:
        if ( tndx >= len ) {
            UCSR2A |=  _BV(TXC2);       // clear TXC flag if set by any chance
            UCSR2B &= ~_BV(UDRIE2);
            UCSR2B |=  _BV(TXCIE2);
        }
        UDR2 = b;
        break;

    case hart_modem_2:
        if ( tndx >= len ) {
            UCSR3A |=  _BV(TXC3);       // clear TXC flag if set by any chance
            UCSR3B &= ~_BV(UDRIE3);
            UCSR3B |=  _BV(TXCIE3);
        }
        UDR3 = b;
        break;
    }
    task->tx_buf_ndx = tndx;
}

static void hart_irq_finish_tx(HartTaskStruct *task) {
    OS_DI();             // Disable before allowing interrupt
    switch ( task->modem_no ) {
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
    // Disable demodulator on hart modem
    //
#if HART_CONTROL_RTS_IN_TASK  == 0
    hart_gpio_hart_carrier_off_irq(task->modem_no);
#endif
    if ( OS_IsTask(&task->tcb) ) {
        OS_SignalEvent(HART_EVENT_TX_COMPLETE, &task->tcb);
    }

    return;
}


////////////////////////////////////////////////////////////////////////////////
//
// HART0 USART1 IRQ handler
//
////////////////////////////////////////////////////////////////////////////////
void Handler_USART_RXC(HartTaskStruct *_hart_task) {
    char tmpData;
    switch ( _hart_task->modem_no ) {
    case 0:
        tmpData = UDR1;
        break;
    case 1:
        tmpData = UDR2;
        break;
    case 2:
        tmpData = UDR3;
        break;
    }
    if ( _hart_task->rx_Listen[_hart_task->rx_Channel] ) {
        _hart_task->rx_Time[_hart_task->rx_Channel] = OS_Time;
    } else if ( OS_IsTask(&_hart_task->tcb) ) {
        CriticalComError = OS_PutMailCond1(&_hart_task->RxMailBox, &tmpData);
    }
}

void hart_irq_finish_tx0(void) {
    hart_irq_finish_tx(&_hart_task0);
}

void hart_irq_finish_tx1(void) {
    hart_irq_finish_tx(&_hart_task1);
}
void hart_irq_finish_tx2(void) {
    hart_irq_finish_tx(&_hart_task2);
}

void Handler_USART_RXC0(void) {
    Handler_USART_RXC(&_hart_task0);
}

void Handler_USART_RXC1(void) {
    Handler_USART_RXC(&_hart_task1);
}
void Handler_USART_RXC2(void) {
    Handler_USART_RXC(&_hart_task2);
}

void hart_irq_tx_next0(void) {
    hart_irq_tx_next(&_hart_task0);
}
void hart_irq_tx_next1(void) {
    hart_irq_tx_next(&_hart_task1);
}
void hart_irq_tx_next2(void) {
    hart_irq_tx_next(&_hart_task2);
}



#pragma vector=USART1_RX_vect
__interrupt void USART1_RXC(void) {
    OS_CallISR(Handler_USART_RXC0);
}

#pragma vector=USART1_TX_vect
__interrupt void USART1_TXC(void) {
    OS_CallISR(hart_irq_finish_tx0);
}

#pragma vector=USART1_UDRE_vect
__interrupt void USART1_UDRE(void) {
    OS_CallISR(hart_irq_tx_next0);
}

////////////////////////////////////////////////////////////////////////////////
//
// HART1 USART2 IRQ handler
//
////////////////////////////////////////////////////////////////////////////////
#pragma vector=USART2_RX_vect
__interrupt void USART2_RXC(void) {
    OS_CallISR(Handler_USART_RXC1);
}

#pragma vector=USART2_TX_vect
__interrupt void USART2_TXC(void) {
    OS_CallISR(hart_irq_finish_tx1);
}

#pragma vector=USART2_UDRE_vect
__interrupt void USART2_UDRE(void) {
    OS_CallISR(hart_irq_tx_next1);
}

////////////////////////////////////////////////////////////////////////////////
//
// HART1 USART3 IRQ handler
//
////////////////////////////////////////////////////////////////////////////////
#pragma vector=USART3_RX_vect
__interrupt void USART3_RXC(void) {
    OS_CallISR(Handler_USART_RXC2);
}

#pragma vector=USART3_TX_vect
__interrupt void USART3_TXC(void) {
    OS_CallISR(hart_irq_finish_tx2);
}

#pragma vector=USART3_UDRE_vect
__interrupt void USART3_UDRE(void) {
    OS_CallISR(hart_irq_tx_next2);
}

////////////////////////////////////////////////////////////////////////////////
//
// UART Utilities
//
////////////////////////////////////////////////////////////////////////////////
void hart_config_uart(HartTaskStruct *task) {
    uint16_t    baud = 1200;
    uint16_t    baud_setting = (XTAL_CPU / 4 / baud - 1) / 2;

    switch ( task->modem_no ) {
    case hart_modem_0:
        // try U2X mode first
        UCSR1A      = _BV(U2X1);
        if ( ((XTAL_CPU == 16000000UL) && (baud == 57600)) || (baud_setting > 4095) ) {
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
        if ( ((XTAL_CPU == 16000000UL) && (baud == 57600)) || (baud_setting > 4095) ) {
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
        if ( ((XTAL_CPU == 16000000UL) && (baud == 57600)) || (baud_setting > 4095) ) {
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

static void hart_reset_tx(HartTaskStruct *task) {
    task->tx_buf_ndx  = 0;
    task->tx_len      = 0;

    hart_msg_encoder_reset(&task->hart_encoder);
}

static void hart_reset_rx(HartTaskStruct *task, hart_channel_t current_chnl) {
    task->rx_buf_ndx   	 = 0;
    task->rx_len       	 = 0;

    hart_msg_parser_reset(&task->hart_parser);
}

static void hart_start_transaction(HartTaskStruct *task) {
    if ( task->tx_len == 0 ) {
        // XXX fucked up. there is a bug
        return;
    }

    // just to make sure
    task->tx_buf_ndx    = 0;

    switch ( task->modem_no ) {
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
void vega_radar_make_request(HartTaskStruct *task, hart_channel_t current_chnl) {
    uint8_t   addr[5] = { 0x80, 0x00, 0x00, 0x00, 0x00 };
    uint8_t   cmd = TData.Hart.HartCmd[current_chnl];        // Can use command 1 later, possibly controlled from TCU no idea what to use

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

void vega_radar_handle_rx_error(HartTaskStruct *task, hart_channel_t current_chnl, HartCommErrType err_type) {
    switch ( err_type ) {
    case HartCommErr_RX_Error:
        // XXX
        // do whatevern necessary here
        if ( TData.Hart.FailCnt[current_chnl][0] < 0xffff ) {
            TData.Hart.FailCnt[current_chnl][0]++;
        }
        if ( TData.Hart.FailCnt[current_chnl][1] < 0xffff ) {
            TData.Hart.FailCnt[current_chnl][1]++;
        }
        break;

    case HartCommErr_RX_Timeout:
        // XXX
        // do whatever necessary here
        if ( TData.Hart.FailCnt[current_chnl][0] < 0xffff ) {
            TData.Hart.FailCnt[current_chnl][0]++;
        }
        if ( TData.Hart.FailCnt[current_chnl][1] < 0xffff ) {
            TData.Hart.FailCnt[current_chnl][1]++;
        }
        break;

    case HartCommErr_RX_Checksum:
        // XXX
        // do whatever necessary here
        if ( TData.Hart.FailCnt[current_chnl][0] < 0xffff ) {
            TData.Hart.FailCnt[current_chnl][0]++;
        }
        if ( TData.Hart.FailCnt[current_chnl][1] < 0xffff ) {
            TData.Hart.FailCnt[current_chnl][1]++;
        }
        break;
    }
}


float ConvertBigEndianToLittleEndian(char *Ptr) {
    const char FloatBuf[4] = { Ptr[3], Ptr[2], Ptr[1], Ptr[0] };
    const float *FloatNum  = (float *)FloatBuf;
    return *FloatNum;
}

uint8_t ReceiveReply(HartTaskStruct *task, hart_channel_t current_chnl) {
    char RxTimeOut   = false;
    char RxStatus    = HART_EVENT_NONE;
    char *BufPtr     = (char *)task->rx_buf;
    int  SyncCnt     = 0;
    char RxByte;
    int TimeOut = 200;
    do {
        RxTimeOut = OS_GetMailTimed(&task->RxMailBox, &RxByte, TimeOut);
        if ( RxByte == 0xff ) {
            SyncCnt++;
            TimeOut = 25;
        }
    }while ( (SyncCnt < HART_PREAMBLE_MAX_LENGTH) && !RxTimeOut && (RxByte == HART_PREAMBLE) );

    if ( !RxTimeOut && (SyncCnt >= HART_PREAMBLE_MIN_LENGTH ) &&  (SyncCnt < HART_PREAMBLE_MAX_LENGTH) ) {
        *BufPtr = RxByte;
        BufPtr++;
        char MasterNum   = RxByte;
        switch ( MasterNum ) {
        case HART_MSG_START_FROM_MASTER_TO_SLAVE:
            break;
        case HART_MSG_START_FROM_SLAVE_TO_MASTER:
            break;
        case HART_MSG_START_FROM_SLAVE_TO_MASTER_LONG:
            {
                HARTLongMessage *Msg = (HARTLongMessage *)BufPtr;
                int  hRxCnt = 0;
                do {
                    RxTimeOut = OS_GetMailTimed(&task->RxMailBox, &RxByte, TimeOut);
                    BufPtr[hRxCnt++] = RxByte;
                    // Make sure we are within limits of the buffer
                }while ( !RxTimeOut && hRxCnt < sizeof(HARTLongMessage) );
                if ( RxTimeOut ) {
                    RxStatus	 = HART_EVENT_TIMEOUT;
                } else if ( hRxCnt >= HART_MAX_RX_BUFFER_SIZE ||  Msg->MsessageSize >= HART_MAX_DATA_LENGTH ) {
                    RxStatus	 = HART_EVENT_RX_ERROR;
                } else {
                    int  mRxCnt = 0;
                    BufPtr += sizeof(HARTLongMessage);
                    do {
                        RxTimeOut = OS_GetMailTimed(&task->RxMailBox, &RxByte, TimeOut);
                        BufPtr[mRxCnt++] = RxByte;
                    }while ( !RxTimeOut && (mRxCnt < Msg->MsessageSize) );
                    if ( RxTimeOut ) {
                        RxStatus	  = HART_EVENT_TIMEOUT;
                    } else {
                        uint8_t pcsum = task->rx_buf[hRxCnt + mRxCnt];
                        uint8_t csum  = hart_msg_calc_csum((const uint8_t *)task->rx_buf, hRxCnt + mRxCnt);
                        if ( csum == pcsum ) {
                            switch ( TData.Hart.HartCmd[current_chnl] ) {
                            case 1:
                                TData.Hart.Distance[current_chnl] = ConvertBigEndianToLittleEndian(&BufPtr[2]);
                                TData.Hart.FailCnt[current_chnl][0] = 0;
                                break;
                            case 3:
                                TData.Hart.HartCurrent[current_chnl] = ConvertBigEndianToLittleEndian(&BufPtr[1]);
                                // Ignore UnitId and other data. char UnitId     = BufPtr[5+Offset];
                                // Only keep Distance and level
                                TData.Hart.Distance[current_chnl] = ConvertBigEndianToLittleEndian(&BufPtr[6 + 0]);
                                TData.Hart.Level[current_chnl] = ConvertBigEndianToLittleEndian(&BufPtr[6 + 5]);
                                TData.Hart.FailCnt[current_chnl][0] = 0;
                                break;
                            }
                            RxStatus = HART_EVENT_RX_COMPLETE;
                        } else {
                            RxStatus = HART_EVENT_CHECKSUM_ERROR;
                        }
                        char Cnt = 0;
                        do {
                            char RxByte;
                            RxTimeOut = OS_GetMailTimed(&task->RxMailBox, &RxByte, TimeOut);
                        }while ( !RxTimeOut && Cnt++ < HART_MAX_DATA_LENGTH );
                    }
                }
            }
            break;
        }
    } else {
        RxStatus = HART_EVENT_RX_ERROR;
    }
    return RxStatus;
}
////////////////////////////////////////////////////////////////////////////////
//
// core hart work
//
////////////////////////////////////////////////////////////////////////////////

void do_hart_transaction(HartTaskStruct *task, const hart_channel_t current_chnl, HartTransaction *t) {
    long        t1    = OS_Time;
    HartChannel *chnl = &_hart_channels[current_chnl];

    hart_channel_t ModemChannel = (hart_channel_t)(current_chnl - task->start_chnl);

    hart_channel_inc_stat(chnl, HartChannelStatItem_TOTAL_REQS);


    hart_reset_rx(task, current_chnl);
    hart_reset_tx(task);
    //uint8_t tmp1= PORTC;
    hart_gpio_channel_select(current_chnl);
    OS_Delay(15); // Wait a little to detect if any other HArt modem is active.

    //uint8_t tmp3= PORTC;
    // Don't change channel before other channel is selected
    task->rx_Channel = ModemChannel;
    long LastRxTime = 0;
    if ( task->rx_Time[ModemChannel] ) {
        LastRxTime = OS_Time - task->rx_Time[ModemChannel];
    }

    char NoOtherRx = LastRxTime > 30000L;
    // NoOtherRx = 1;
    if ( !LastRxTime || NoOtherRx ) {

        t->make_request(task, current_chnl);
        //
        // now set the tx length of tx_buf
        //
        task->tx_len = task->hart_encoder.tx_ndx;
#if HART_CONTROL_RTS_IN_TASK  == 1
        hart_gpio_hart_carrier_on(task->modem_no);
#endif
        OS_Delay(5);
        // Be sure we have no unhandled signals before start
        OS_ClearEvents(&task->tcb);
        //OS_ClearMB(&task->RxMailBox);
        hart_start_transaction(task);
        // Task will halt if no signal!
        // Changed code to avoid halt EHS
        char TxFlag = OS_WaitEventTimed(HART_EVENT_TX_COMPLETE, 2000);
#if HART_CONTROL_RTS_IN_TASK  == 1
        hart_gpio_hart_carrier_off(task->modem_no);
#endif
        if ( TxFlag ) {
            task->rx_Listen[ModemChannel] = false;

            hart_control_Rx_Enable(task->modem_no, TRUE);
            uint8_t event_status = t->complete(task, current_chnl);
            task->rx_Time[ModemChannel] = 0;
            task->rx_Listen[ModemChannel] = true;
            switch ( event_status ) {
            case HART_EVENT_TIMEOUT: // Timeout
                hart_channel_inc_stat(chnl, HartChannelStatItem_RX_TIMEOUT);
                hart_channel_set_status(chnl, HartChannelStatus_No_Response);

                t->error(task, current_chnl, HartCommErr_RX_Timeout);
                break;
            case HART_EVENT_RX_ERROR:
                // protocol parsing error
                hart_channel_inc_stat(chnl, HartChannelStatItem_RX_INVALID);
                hart_channel_set_status(chnl, HartChannelStatus_Invalid_Response);

                t->error(task, current_chnl, HartCommErr_RX_Error);
                break;
            case HART_EVENT_RX_COMPLETE:
                hart_channel_set_status(chnl, HartChannelStatus_Responding);
                break;
            case HART_EVENT_CHECKSUM_ERROR:
                hart_channel_set_status(chnl, HartChannelStatus_Responding);
                hart_channel_inc_stat(chnl, HartChannelStatItem_RX_CSUM);
                // checksum mismatch
                t->error(task, current_chnl, HartCommErr_RX_Checksum);
                break;
            }
        }
    } else if ( !NoOtherRx ) {
        // Seems like other hart Modem connected. So just start reading to get read of the data
        OS_Delay(2);
        task->rx_Listen[ModemChannel] = true;
        hart_control_Rx_Enable(task->modem_no, TRUE);
    }
    OS_DelayUntil(t1 + 750);
    hart_control_Rx_Enable(task->modem_no, FALSE);
    task->rx_Listen[ModemChannel] = false;
}

////////////////////////////////////////////////////////////////////////////////
//
// HART Task
//
////////////////////////////////////////////////////////////////////////////////
void HART_Task(void *pVoid) {
    HartTaskStruct *HartTasks[3] = { &_hart_task0, &_hart_task1, &_hart_task2 };
    char ModemNo            = (char)pVoid;
    //OS_TASK *taskPtr        = OS_GetpCurrentTask();
    //HartTaskStruct *myTask  = container_of(taskPtr, HartTaskStruct, tcb);
    HartTaskStruct *myTask  = HartTasks[ModemNo];



    hart_msg_parser_init(&myTask->hart_parser, myTask->rx_buf, HART_MAX_RX_BUFFER_SIZE);
    hart_msg_encoder_init(&myTask->hart_encoder, myTask->tx_buf, HART_MAX_TX_BUFFER_SIZE);

    hart_config_uart(myTask);
    hart_gpio_hart_carrier_off(myTask->modem_no);
    hart_control_Rx_Enable(myTask->modem_no, FALSE);

    while ( 1 ) {
        long t0 = OS_Time;
        myTask->LastHartTaskRunTime = OS_Time;

        for ( hart_channel_t current_chnl = myTask->start_chnl; current_chnl <= myTask->end_chnl; current_chnl++ ) {
            // Check if it's a HART sensor configured for the channel
            if ( TData.Hart.HartSensor & (1U << current_chnl) ) {
                float ADCurrent = TData.Hart.ADCurrent[current_chnl];
                if ( ADCurrent >= HART_MINIMUM_MA_FEEDBACK_FOR_OK  && ADCurrent <= HART_MAXIMUM_MA_FEEDBACK_FOR_OK ) {
                    do_hart_transaction(myTask, current_chnl, &_demo1_transaction);
                }
            } else {
                TData.Hart.FailCnt[current_chnl][0] = 0;
                TData.Hart.FailCnt[current_chnl][1] = 0;
            }

        }
        OS_DelayUntil(t0 + 3000);
    }
}


////////////////////////////////////////////////////////////////////////////////
//
// public interfaces
//
////////////////////////////////////////////////////////////////////////////////
void
hart_start(void) {
    hart_channel_t   chnl;
    OS_CreateMB(&_hart_task0.RxMailBox, 1, HART_MB_BUFFER_SIZE, (char *)_hart_task0.mailBuf);
    OS_CreateMB(&_hart_task1.RxMailBox, 1, HART_MB_BUFFER_SIZE, (char *)_hart_task1.mailBuf);
    OS_CreateMB(&_hart_task2.RxMailBox, 1, HART_MB_BUFFER_SIZE, (char *)_hart_task2.mailBuf);
/*
    OS_CREATERSEMA(&_hart_task0.channel_lock);
    OS_CREATERSEMA(&_hart_task1.channel_lock);
    OS_CREATERSEMA(&_hart_task2.channel_lock);
*/
    hart_for_each_channel(chnl) {
        hart_channel_reset(&_hart_channels[chnl]);
        hart_control_power(chnl, HartChannelPowerStatus_ON);
    }
    hart_gpio_enable_all_mux();

    //
    // now power on modem one by one.
    // don't care about start up time
    //

    //OS_CreateTask(&_hart_task0.tcb, "HART0", HART_TASK_PRIORITY,HART_Task,_hart_task0.Mystack,sizeof(_hart_task0.Mystack),0);
    //OS_CreateTask(&_hart_task1.tcb, "HART1", HART_TASK_PRIORITY,HART_Task,_hart_task1.Mystack,sizeof(_hart_task1.Mystack),0);
    //OS_CreateTask(&_hart_task2.tcb, "HART2", HART_TASK_PRIORITY,HART_Task,_hart_task2.Mystack,sizeof(_hart_task2.Mystack),0);
    OS_CREATETASK_EX(&_hart_task0.tcb, "HART0", HART_Task, HART_TASK_PRIORITY, _hart_task0.Mystack, (void *)0);
    OS_CREATETASK_EX(&_hart_task1.tcb, "HART1", HART_Task, HART_TASK_PRIORITY, _hart_task1.Mystack, (void *)1);
    OS_CREATETASK_EX(&_hart_task2.tcb, "HART2", HART_Task, HART_TASK_PRIORITY, _hart_task2.Mystack, (void *)2);


}


void RestartHart(void) {
    OS_EnterRegion();
    OS_TerminateTask(&_hart_task0.tcb);
    OS_TerminateTask(&_hart_task1.tcb);
    OS_TerminateTask(&_hart_task2.tcb);
    hart_diag_task_stop();
    //memset(&_hart_task0.tcb, 0, sizeof(_hart_task0.tcb));
    //memset(&_hart_task1.tcb, 0, sizeof(_hart_task0.tcb));
    //memset(&_hart_task2.tcb, 0, sizeof(_hart_task0.tcb));
    /*
    OS_DeleteRSema(&_hart_task0.channel_lock);
    OS_DeleteRSema(&_hart_task1.channel_lock);
    OS_DeleteRSema(&_hart_task2.channel_lock);
 */
    OS_DeleteMB(&_hart_task0.RxMailBox);
    OS_DeleteMB(&_hart_task1.RxMailBox);
    OS_DeleteMB(&_hart_task2.RxMailBox);
    OS_LeaveRegion();
    OS_Delay(100);
    hart_start();
}
