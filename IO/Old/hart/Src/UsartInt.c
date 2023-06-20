/****************************************************************************************
/ USART1 functions and interrupt
/   This routines sync and check the ANPRO10
/   Uart1Pro.c handle the package
/
***************************************************************************************/


#include "iom1280.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

#if (OS_UART != 0)

// USART0
#pragma vector=USART0_RX_vect
__interrupt void IntHandler_RX_USART0( void ){   

    OS_EnterInterrupt();
    OS_EnterIntStack();
    if ( UCSR0A & __BIT_MASK( DOR0 ) ) {                // Overrun error? 
    }

    if ( UCSR0A & __BIT_MASK( FE0 ) ) {                 // Framing error? 
    }

    while ( UCSR0A & __BIT_MASK( RXC0)  ) {                // New byte avaiable?
		char Data = UDR0;
		OS_PutMailCond1(&UART[0].RxMailBox,&Data);
    }
    OS_LeaveIntStack();
    OS_LeaveInterruptNoSwitch();
} 


#pragma vector=USART0_TX_vect
__interrupt void IntHandler_TX_USART0( void ){   

   OS_EnterInterrupt();
   OS_EnterIntStack();
    
    UCSR0B &= ~(__BIT_MASK( TXCIE0)) ;            // transmission end, disable int.
    PORTE &= ~0x04 ;                              // TXE0 off
    OS_StopTimer(&TimerUSART0);                    // and stop timer
    GoToSyncUART(0) ;                                    // go to sync modus for recive
    
    OS_LeaveIntStack();
    OS_LeaveInterruptNoSwitch();
}


#pragma vector = USART0_UDRE_vect
__interrupt void IntHandler_UDRE_USART0( void ){   

    OS_EnterInterrupt();
    OS_EnterIntStack();
    if ( UART[0].TxLast < UART[0].TxCount ) {
        UDR0 = UART[0].pTxBuffer[ UART[0].TxLast ];     // Send a character
        UART[0].TxLast++;
    } else{                                             // Last byte sent?
          UCSR0B &= ~(__BIT_MASK( UDRIE0)) ;            // transmission end, disable int.
          UCSR0A |= (__BIT_MASK( TXC0)) ;               // Clear int bit in TXC.
          UCSR0B |= __BIT_MASK( TXCIE0) ;               // Enable TXC int.
    }           
    OS_LeaveIntStack();
    OS_LeaveInterruptNoSwitch();
} 
#endif

