/*******************************************************
USARTs initialization created by the
CodeWizardAVR V3.49 Automatic Program Generator
© Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
*******************************************************/

#ifndef _USARTS_INIT_INCLUDED_
#define _USARTS_INIT_INCLUDED_
#include "Routine.h"

// USART0 is used as the default input device by the 'getchar' function
// #define _ALTERNATE_GETCHAR_ is inserted for this purpose
// in the main program source file before #include <stdio.h>
//char getchar(void);
// USART0 is used as the default output device by the 'putchar' function
// #define _ALTERNATE_PUTCHAR_ is inserted for this purpose
// in the main program source file before #include <stdio.h>
void putchar(char c);
// USART0 initialization
void usart0_init(void);

//// USART0 Receiver buffer
#define RX_BUFFER_SIZE_USART0 8       // Routine.h
//extern char rx_buffer_usart0[RX_BUFFER_SIZE_USART0];
//
//#if RX_BUFFER_SIZE_USART0 <= 256
//extern volatile unsigned char rx_wr_index_usart0,rx_rd_index_usart0;
//#else
//extern volatile unsigned int rx_wr_index_usart0,rx_rd_index_usart0;
//#endif
//
//#if RX_BUFFER_SIZE_USART0 < 256
//extern volatile unsigned char rx_counter_usart0;
//#else
//extern volatile unsigned int rx_counter_usart0;
//#endif
//
//// This flag is set on USART0 Receiver buffer overflow
//extern bit rx_buffer_overflow_usart0;
//
//// USART0 Transmitter buffer
#define TX_BUFFER_SIZE_USART0 8
//extern char tx_buffer_usart0[TX_BUFFER_SIZE_USART0];
//
//#if TX_BUFFER_SIZE_USART0 <= 256
//extern volatile unsigned char tx_wr_index_usart0,tx_rd_index_usart0;
//#else
//extern volatile unsigned int tx_wr_index_usart0,tx_rd_index_usart0;
//#endif
//
//#if TX_BUFFER_SIZE_USART0 < 256
//extern volatile unsigned char tx_counter_usart0;
//#else
//extern volatile unsigned int tx_counter_usart0;
//#endif

#endif
