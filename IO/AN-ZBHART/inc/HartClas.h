
class HartClass{
public:

	int                         Mystack[HART_TASK_STACK_SIZE];
	char                        mailBuf[HART_MB_BUFFER_SIZE];
	OS_MAILBOX					RxMailBox;
	OS_TASK                     tcb;
	const HART_MODEM_t          modem_no;
	const char                  start_chnl;
	const char                  end_chnl;

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
	volatile char		        rx_Channel;
	volatile char 				rx_Listen[4];
	volatile long				rx_Time[4];
	volatile long				LastHartTaskRunTime;

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
  HartClass(){
    
  }
