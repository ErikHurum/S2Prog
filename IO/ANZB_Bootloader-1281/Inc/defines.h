/* definitions generated by preprocessor, copy into defines.h */		
#ifndef	PPINC	
//#define	_ATMEGA128	// device select: _ATMEGAxxxx
#define	_B1024	// boot size select: _Bxxx (words)
//#include	"iom128.h"	

/* definitions for myUART control */		
#define	BAUD_RATE_LOW_REG0	UBRR0L
#define	UART_CONTROL_REG0	UCSR0B
#define	ENABLE_TRANSMITTER_BIT0	TXEN0
#define	ENABLE_RECEIVER_BIT0	RXEN0
#define	UART_STATUS_REG0        UCSR0A
#define	TRANSMIT_COMPLETE_BIT0	TXC0
#define	RECEIVE_COMPLETE_BIT0	RXC0
#define	UART_DATA_REG0	        UDR0

#define	BAUD_RATE_LOW_REG1	UBRR1L
#define	UART_CONTROL_REG1	UCSR1B
#define	ENABLE_TRANSMITTER_BIT1	TXEN1
#define	ENABLE_RECEIVER_BIT1	RXEN1
#define	UART_STATUS_REG1	UCSR1A
#define	TRANSMIT_COMPLETE_BIT1	TXC1
#define	RECEIVE_COMPLETE_BIT1	RXC1
#define	UART_DATA_REG1	        UDR1

/* definitions for SPM control */		
#define	LOAD_SPM_CONTROL_REGISTER_MACRO	STS SPMCSR, R18
#define	GET_SPM_CONTROL_REGISTER_MACRO	LDS R18, SPMCSR
#define	REENABLE_RWW_BIT	RWWSRE
#define	LARGE_MEMORY	
#define	PAGESIZE	256
#define	APP_END	        0x1e000     // 122880 (Dec)

/* definitions for AVRProg communication */		
#define	PARTCODE	        0x44
#define	SIGNATURE_BYTE_1	0x1E
#define	SIGNATURE_BYTE_2	0x97
#define	SIGNATURE_BYTE_3	0x02

/* define pin for enter-self-prog-mode */		
#define	PROGPORT	PORTD
#define	PROGPIN	PIND
#define	PROGCTRL	(1<<PD4)
#define	PROGMODE	!(PROGPIN & PROGCTRL)

/* indicate preprocessor result included */		
#define	PPINC	
#endif		
