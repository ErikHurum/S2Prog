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

void HART_Task(void);

static void demo1_hart_make_request(HartTaskStruct *task, hart_channel_t current_chnl);
static void demo1_hart_handle_rx_error(HartTaskStruct *task, hart_channel_t current_chnl, HartCommErrType err_type);
static uint8_t ReceiveReply(HartTaskStruct *task, hart_channel_t current_chnl);

HartTaskStruct       _hart_task0 =
{
	.modem_no     = hart_modem_0,
	.start_chnl   = hart_channel_0,
	.end_chnl     = hart_channel_3,
};

HartTaskStruct       _hart_task1 =
{
	.modem_no     = hart_modem_1,
	.start_chnl   = hart_channel_4,
	.end_chnl     = hart_channel_7,
};

HartTaskStruct       _hart_task2 =
{
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
	.make_request = demo1_hart_make_request,
	.complete     = ReceiveReply,
	.error        = demo1_hart_handle_rx_error,
};

HartChannel          _hart_channels[HART_MAX_CHANNEL] =
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


inline void hart_channel_lock(HartChannel *channel) {
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

inline void hart_channel_unlock(HartChannel *channel) {
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
hart_channel_reset(HartChannel *channel) {
	hart_channel_lock(channel);

	channel->status         = HartChannelStatus_No_Response;
	channel->power_status   = HartChannelPowerStatus_OFF;

	channel->MsrdCurrent     = 0.0;

	channel->rx_invalid_msg = 0;
	channel->rx_csum_err    = 0;
	channel->rx_timeout     = 0;
	channel->total_reqs     = 0;
	channel->total_success  = 0;

	hart_channel_unlock(channel);
}

static inline void
hart_channel_set_status(HartChannel *channel, HartChannelStatus status) {
	hart_channel_lock(channel);

	channel->status     = status;

	hart_channel_unlock(channel);
}

static inline void
hart_channel_set_power_status(HartChannel *channel, HartChannelPowerStatus status) {
	hart_channel_lock(channel);

	channel->power_status   = status;

	hart_channel_unlock(channel);
}

static char hart_channel_ready_to_poll(hart_channel_t chnl) {
	char isLoopOK = false;

	//hart_channel_lock(&_hart_channels[chnl]);

	if (_hart_channels[chnl].power_status == HartChannelPowerStatus_ON &&
		_hart_channels[chnl].MsrdCurrent   >= HART_MINIMUM_MA_FEEDBACK_FOR_OK) {
		isLoopOK = true;
	}

	//hart_channel_unlock(&_hart_channels[chnl]);

	return isLoopOK;
}

static inline void
hart_channel_inc_stat(HartChannel *channel, HartChannelStatItem item) {
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
hart_control_power(hart_channel_t chnl, HartChannelPowerStatus on_off) {
	HartChannel *c = &_hart_channels[chnl];

	if (on_off == HartChannelPowerStatus_ON) {
		hart_gpio_power_on(chnl);
	} else {
		hart_gpio_power_off(chnl);
	}
	hart_channel_set_power_status(c, on_off);
}

static void
hart_control_Rx_Enable(hart_modem_t   modem, uint8_t enable, uint8_t from_irq) {
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
hart_irq_tx_next(HartTaskStruct *task) {
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
hart_irq_finish_tx(HartTaskStruct *task) {
	switch (task->modem_no) {
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
	OS_SignalEvent(HART_EVENT_TX_COMPLETE, &task->tcb);

	return;
}


////////////////////////////////////////////////////////////////////////////////
//
// HART0 USART1 IRQ handler
//
////////////////////////////////////////////////////////////////////////////////
#pragma vector=USART1_RX_vect
__interrupt void USART1_RXC(void) {
	ENTER_IRQ;
	if (_hart_task0.rx_Listen[_hart_task0.rx_Channel]) {
		 char Dummy = UDR1;
		_hart_task0.rx_Time[_hart_task0.rx_Channel] = OS_Time;
	} else {
		const char tmpData = UDR1;
		OS_PutMailCond1(&_hart_task0.RxMailBox, &tmpData);
	}

	LEAVE_IRQ;
}

#pragma vector=USART1_TX_vect
__interrupt void USART1_TXC(void) {
	ENTER_IRQ;

	hart_irq_finish_tx(&_hart_task0);

	LEAVE_IRQ;
}

#pragma vector=USART1_UDRE_vect
__interrupt void USART1_UDRE(void) {
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
__interrupt void USART2_RXC(void) {
	ENTER_IRQ;
	if (_hart_task1.rx_Listen[_hart_task1.rx_Channel]) {
		 char Dummy = UDR2;
		_hart_task1.rx_Time[_hart_task1.rx_Channel] = OS_Time;
	} else {
		const char tmpData = UDR2;
		OS_PutMailCond1(&_hart_task1.RxMailBox, &tmpData);
	}
	LEAVE_IRQ;
}

#pragma vector=USART2_TX_vect
__interrupt void USART2_TXC(void) {
	ENTER_IRQ;

	hart_irq_finish_tx(&_hart_task1);

	LEAVE_IRQ;
}

#pragma vector=USART2_UDRE_vect
__interrupt void USART2_UDRE(void) {
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
__interrupt void USART3_RXC(void) {
	ENTER_IRQ;

	if (_hart_task2.rx_Listen[_hart_task2.rx_Channel]) {
		 char Dummy = UDR3;
		_hart_task2.rx_Time[_hart_task2.rx_Channel] = OS_Time;
	} else {
		const char tmpData = UDR3;
		OS_PutMailCond1(&_hart_task2.RxMailBox, &tmpData);
	}
	LEAVE_IRQ;
}

#pragma vector=USART3_TX_vect
__interrupt void USART3_TXC(void) {
	ENTER_IRQ;

	hart_irq_finish_tx(&_hart_task2);

	LEAVE_IRQ;
}

#pragma vector=USART3_UDRE_vect
__interrupt void USART3_UDRE(void) {
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
hart_config_uart(HartTaskStruct *task) {
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
hart_reset_tx(HartTaskStruct *task) {
	task->tx_buf_ndx  = 0;
	task->tx_len      = 0;

	hart_msg_encoder_reset(&task->hart_encoder);
}

static void
hart_reset_rx(HartTaskStruct *task, hart_channel_t current_chnl) {
	task->rx_buf_ndx   	 = 0;
	task->rx_len       	 = 0;
	//task->rx_Time    	   = 0;
	//task->rx_Listen[0]   = false;
	//task->rx_Listen[1]   = false;
	//task->rx_Listen[2]   = false;
	//task->rx_Listen[3]   = false;
	hart_msg_parser_reset(&task->hart_parser);
}

static void
hart_start_transaction(HartTaskStruct *task) {
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
demo1_hart_make_request(HartTaskStruct *task, hart_channel_t current_chnl) {
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
demo1_hart_handle_rx_error(HartTaskStruct *task, hart_channel_t current_chnl, HartCommErrType err_type) {
	switch (err_type) {
	case HartCommErr_RX_Error:
		// XXX
		// do whatevern necessary here
		TData.Hart.FailCnt[current_chnl][0]++;
		TData.Hart.FailCnt[current_chnl][1]++;
		break;

	case HartCommErr_RX_Timeout:
		// XXX
		// do whatever necessary here
		TData.Hart.FailCnt[current_chnl][0]++;
		TData.Hart.FailCnt[current_chnl][1]++;
		break;

	case HartCommErr_RX_Checksum:
		// XXX
		// do whatever necessary here
		TData.Hart.FailCnt[current_chnl][0]++;
		TData.Hart.FailCnt[current_chnl][1]++;
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
		if (RxByte == 0xff) {
			SyncCnt++;
                        TimeOut = 25;
		}
	}while (!RxTimeOut && (RxByte == 0xff));

	if (!RxTimeOut && SyncCnt >= 4) {
		*BufPtr = RxByte;
		BufPtr++;
		char MasterNum   = RxByte;
		switch (MasterNum) {
		case HART_MSG_START_FROM_MASTER_TO_SLAVE:
			break;
		case HART_MSG_START_FROM_SLAVE_TO_MASTER:
			break;
		case HART_MSG_START_FROM_SLAVE_TO_MASTER_LONG:
			{
				HARTLongMessage *Msg = (HARTLongMessage *)BufPtr;
				int  hRxCnt = 0;
				do {
					char RxByte;
					RxTimeOut = OS_GetMailTimed(&task->RxMailBox, &RxByte, TimeOut);
					BufPtr[hRxCnt++] = RxByte;
				}while (!RxTimeOut && hRxCnt < sizeof(HARTLongMessage));
				if (RxTimeOut) {
					RxStatus	 = HART_EVENT_TIMEOUT;
				} else {
					int  mRxCnt = 0;
					BufPtr += sizeof(HARTLongMessage);
					do {
						char RxByte;
						RxTimeOut = OS_GetMailTimed(&task->RxMailBox, &RxByte, TimeOut);
						BufPtr[mRxCnt++] = RxByte;
					}while (!RxTimeOut && (mRxCnt < Msg->MsessageSize) && (mRxCnt < HART_MAX_DATA_LENGTH));
					if (RxTimeOut) {
						RxStatus	 = HART_EVENT_TIMEOUT;
					} else {
						uint8_t pcsum = task->rx_buf[hRxCnt + mRxCnt];
						uint8_t csum = hart_msg_calc_csum((const uint8_t *)task->rx_buf, hRxCnt + mRxCnt);
						if (csum == pcsum) {
							TData.Hart.HartCurrent[current_chnl] = ConvertBigEndianToLittleEndian(&BufPtr[1]);
							// Ignore UnitId and other data. char UnitId     = BufPtr[5+Offset];
							// Only keep Distance and level
							TData.Hart.Distance[current_chnl] = ConvertBigEndianToLittleEndian(&BufPtr[6 + 0]);
							TData.Hart.Level[current_chnl] = ConvertBigEndianToLittleEndian(&BufPtr[6 + 5]);
							TData.Hart.FailCnt[current_chnl][0] = 0;
							RxStatus 						 		= HART_EVENT_RX_COMPLETE;
						} else {
							RxStatus 						 		= HART_EVENT_CHECKSUM_ERROR;
						}
                                                int Cnt=0;
                                                do {
                                                        char RxByte;
                                                        RxTimeOut = OS_GetMailTimed(&task->RxMailBox, &RxByte, TimeOut);
                                                        Cnt++;
                                                }while (!RxTimeOut );
                                                
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
	long t1 = OS_Time;

	HartChannel *chnl = &_hart_channels[current_chnl];

	const hart_channel_t ModemChannel = (const hart_channel_t)(current_chnl - task->start_chnl);

	hart_channel_inc_stat(chnl, HartChannelStatItem_TOTAL_REQS);

	t->error_occurred   = 1;

	hart_reset_rx(task, current_chnl);
	hart_reset_tx(task);
	//uint8_t tmp1= PORTC;
	hart_gpio_channel_select(current_chnl);
	OS_Delay(10);

	//uint8_t tmp3= PORTC;
	// Don't change channel before other channel is selected
	task->rx_Channel= ModemChannel;
	long LastRxTime = 0;
	if (task->rx_Time[ModemChannel]) {
		LastRxTime = OS_Time - task->rx_Time[ModemChannel];
	}

	char NoOtherRx = LastRxTime > 30000L;
       // NoOtherRx = 1;
	if (!LastRxTime || NoOtherRx) {

		t->make_request(task, current_chnl);
		//
		// now set the tx length of tx_buf
		//
		task->tx_len = task->hart_encoder.tx_ndx;
		hart_gpio_hart_carrier_on(task->modem_no);
		OS_Delay(5);
		// Be sure we have no unhandled signals before start
		OS_ClearEvents(&task->tcb);
		//OS_ClearMB(&task->RxMailBox);
		hart_start_transaction(task);
		// Task will halt if no signal!
		// Changed code to avoid halt EHS
		char TxFlag = OS_WaitEventTimed(HART_EVENT_TX_COMPLETE, 2000);
		if (TxFlag) {
			int StartT = OS_Time;
			hart_gpio_hart_carrier_off(task->modem_no);
			task->rx_Listen[ModemChannel] = false;

			hart_control_Rx_Enable(task->modem_no, TRUE, FALSE);
			uint8_t event_status = t->complete(task, current_chnl);
			task->rx_Time[ModemChannel] = 0;
			task->rx_Listen[ModemChannel] = true;
			switch (event_status) {
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
	} else if (!NoOtherRx) {
		OS_Delay(2);
		task->rx_Listen[ModemChannel] = true;
		hart_control_Rx_Enable(task->modem_no, TRUE, FALSE);
	}
	OS_DelayUntil(t1 + 750);
	hart_control_Rx_Enable(task->modem_no, FALSE, FALSE);
	task->rx_Listen[ModemChannel] = false;
}

////////////////////////////////////////////////////////////////////////////////
//
// HART Task
//
////////////////////////////////////////////////////////////////////////////////
void HART_Task(void) {
	OS_TASK *taskPtr = OS_GetpCurrentTask();
	HartTaskStruct *myTask  = container_of(taskPtr, HartTaskStruct, tcb);
	OS_CreateMB(&myTask->RxMailBox, 1, HART_MAX_RX_BUFFER_SIZE, (char *)myTask->mailBuf);


	hart_msg_parser_init(&myTask->hart_parser, myTask->rx_buf, HART_MAX_RX_BUFFER_SIZE);
	hart_msg_encoder_init(&myTask->hart_encoder, myTask->tx_buf, HART_MAX_TX_BUFFER_SIZE);

	hart_config_uart(myTask);
	hart_gpio_hart_carrier_off(myTask->modem_no);
	hart_control_Rx_Enable(myTask->modem_no, FALSE, FALSE);

	long t0 = OS_GetTime();
	while (1) {
		uint8_t num_chnls_handled = 0;

		for (hart_channel_t current_chnl = myTask->start_chnl; current_chnl <= myTask->end_chnl; current_chnl++) {

			if (hart_channel_ready_to_poll(current_chnl)) {
				num_chnls_handled++;
				do_hart_transaction(myTask, current_chnl, &_demo1_transaction);
			}
		}
		OS_DelayUntil(t0 += 3000);
		myTask->LastHartTaskRunTime = OS_Time;
		/*
		if (num_chnls_handled == 0) {
			//
			// if all the task channels are either power down or
			// fault state, then get some sleep
			// much better cooperative bullshit
			//
			OS_Delay(200);
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
hart_start(void) {
	hart_channel_t   chnl;

	OS_CREATERSEMA(&_hart_task0.channel_lock);
	OS_CREATERSEMA(&_hart_task1.channel_lock);
	OS_CREATERSEMA(&_hart_task2.channel_lock);

	hart_for_each_channel(chnl) {
		hart_channel_reset(&_hart_channels[chnl]);
		hart_control_power(chnl, HartChannelPowerStatus_ON);
	}
	hart_gpio_enable_all_mux();
	hart_diag_task_start();

	//
	// now power on modem one by one.
	// don't care about start up time
	//
	hart_diag_init();
	OS_Delay(HART_START_UP_POWER_UP_DELAY);

	OS_CREATETASK(&_hart_task0.tcb, "HART0", HART_Task, HART_TASK_PRIORITY, _hart_task0.Mystack);
	OS_CREATETASK(&_hart_task1.tcb, "HART1", HART_Task, HART_TASK_PRIORITY, _hart_task1.Mystack);
	OS_CREATETASK(&_hart_task2.tcb, "HART2", HART_Task, HART_TASK_PRIORITY, _hart_task2.Mystack);


}


HartChannel* hart_channel_get_with_lock(hart_channel_t chnl_num) {
	HartChannel *chnl = &_hart_channels[chnl_num];

	hart_channel_lock(chnl);
	return chnl;
}

void hart_channel_put_with_unlock(HartChannel *chnl) {
	hart_channel_unlock(chnl);
}
