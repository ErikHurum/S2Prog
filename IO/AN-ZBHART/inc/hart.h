#ifndef __HART_DEF_H__
#define __HART_DEF_H__
#include "rtos.h"
#include "hart_common.h"
#include "hart_msg.h"
////////////////////////////////////////////////////////////////////////////////
//
// some notes
//
// 1) according to schematic,
//    HART MODEM0 is mapped to My485UART1
//    HART MODEM1 is mapped to My485UART2
//    HART MODEM2 is mapped to My485UART3
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// module configuration
//
////////////////////////////////////////////////////////////////////////////////
#define HART_CONTROL_RTS_IN_TASK          1

////////////////////////////////////////////////////////////////////////////////
//
// private defines
//
////////////////////////////////////////////////////////////////////////////////
#define TRUE      1
#define FALSE     0

#define HART_MINIMUM_MA_FEEDBACK_FOR_OK     3.0        // 3mA
#define HART_MAXIMUM_MA_FEEDBACK_FOR_OK     21.0        // 21mA
#define HART_TASK_STACK_SIZE            225
#define HART_MAX_TX_BUFFER_SIZE         384
#define HART_MAX_RX_BUFFER_SIZE         384
#define HART_MB_BUFFER_SIZE             50
#define HART_EVENT_NONE          		0x00
#define HART_EVENT_RX_COMPLETE          0x01
#define HART_EVENT_RX_ERROR             0x02
#define HART_EVENT_TX_COMPLETE          0x04
#define HART_EVENT_TIMEOUT				0x08
#define HART_EVENT_CHECKSUM_ERROR		0x10
#define HART_TRANSACTION_TIMEOUT        500 //2000
#define HART_TASK_PRIORITY              120
#define HART_START_UP_POWER_UP_DELAY    1500


#define HART_LONG_MSG_HEADING_SIZE      7


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
typedef struct {
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
	char						StackTest1[10];
#endif
	int                         Mystack[HART_TASK_STACK_SIZE];
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
	char						StackTest2[10];
#endif
	char                        mailBuf[HART_MB_BUFFER_SIZE];
	OS_MAILBOX					RxMailBox;
	OS_TASK                     tcb;
	const hart_modem_t          modem_no;
	const hart_channel_t        start_chnl;
	const hart_channel_t        end_chnl;

	//
	// TX buffer
	//
	volatile uint16_t           tx_buf_ndx;
	volatile uint16_t           tx_len;
	hart_data_t        tx_buf[HART_MAX_TX_BUFFER_SIZE];

	//
	// RX buffer
	//
	volatile uint16_t           rx_buf_ndx;
	volatile uint16_t           rx_len;
	hart_data_t                 rx_buf[HART_MAX_RX_BUFFER_SIZE];
	volatile hart_channel_t		rx_Channel;
	volatile char 				rx_Listen[4];
	volatile OS_U32				rx_Time[4];
	volatile OS_U32				LastHartTaskRunTime;

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
	//OS_RSEMA                    channel_lock;
} HartTaskStruct;


typedef void (*hart_prepare_handler)(HartTaskStruct *task, hart_channel_t current_chnl);
typedef uint8_t (*hart_rx_complete_handler)(HartTaskStruct *task, hart_channel_t current_chnl);
typedef void (*hart_rx_error_handler)(HartTaskStruct *task, hart_channel_t current_chnl, HartCommErrType err_type);

typedef struct
{
	hart_prepare_handler        make_request;
	hart_rx_complete_handler    complete;
	hart_rx_error_handler       error;
} HartTransaction;

#define HART_ADDRESS_SIZE 5
typedef struct
{
	char Address[HART_ADDRESS_SIZE];
	//char Expansion;
	char Command;
	char MsessageSize;
	char Status;
} HARTLongMessage;

extern HartTaskStruct       _hart_task0;
extern HartTaskStruct       _hart_task1;
extern HartTaskStruct       _hart_task2;

extern HartChannel          _hart_channels[HART_MAX_CHANNEL];

//extern inline void hart_channel_lock(HartChannel *channel);
//extern inline void hart_channel_unlock(HartChannel *channel);
extern void hart_start(void);
extern void RestartHart(void);

#endif /* !__HART_DEF_H__ !*/
