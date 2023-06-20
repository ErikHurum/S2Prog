/****************************************************************************************
/ USART1 functions and interrupt
/   This routines sync and check the ANPRO1
/   Uart1Pro.c handle the package
/
***************************************************************************************/


#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

#if (OS_UART != 0)

// USART0
#pragma vector=USART0_RXC_vect
__interrupt void IntHandler_RX_USART0( void ){   

    OS_EnterInterrupt();
    OS_EnterIntStack();
    if ( UCSR0A & __BIT_MASK( DOR0 ) ) {                // Overrun error? 
    }

    if ( UCSR0A & __BIT_MASK( FE0 ) ) {                 // Framing error? 
    }

    if ( UCSR0A & __BIT_MASK( RXC0)  ) {                // Reception data full interrupt?
        UART[0].pRxBuffer[ UART[0].RxFirst ] = UDR0;                               // Read the character 

        if (UART[0].RxState != HANDLE) {        // ok to receive? 
            switch (UART[0].RxState) {                   // Yes, check state
            case SYNC :
                if (UART[0].pRxBuffer[ UART[0].RxFirst ] == ANPRO1_SYN) {
                    UART[0].SyncCnt ++ ;                 // count sync
                    UART[0].RxFirst = 0;                 // start at start of buff
                } else if (UART[0].SyncCnt >= 2) {       // minimum two sync bytes
                    UART[0].SyncCnt = 0 ;                // reset counter
                    UART[0].RxState = HEADER ;
                    UART[0].RxLast = 0 ;
                    UART[0].RxTimeout = RX_TO_TIME ;   // reset timeout
                    ++UART[0].RxFirst;
                    ReceivePacketUart(0) ;              // Check package
                } else {
                    UART[0].SyncCnt = 0 ;                // start over once more
                }
                break;
            default :
                if ((++UART[0].RxFirst) > RXSIZE_UART) { // Point to next location
                    GoToSyncUART(0) ;                       // go to sync mode
                } else {
                    ReceivePacketUart(0) ;              // Check package
                }
                break ;   
            }
        }
    }
    OS_LeaveIntStack();
    OS_LeaveInterrupt();
} 


#pragma vector=USART0_TXC_vect
__interrupt void IntHandler_TX_USART0( void ){   

    OS_EnterInterrupt();
    OS_EnterIntStack();
    OS_LeaveIntStack();
    OS_LeaveInterrupt();
}


#pragma vector = USART0_UDRE_vect
__interrupt void IntHandler_UDRE_USART0( void ){   

    OS_EnterInterrupt();
    OS_EnterIntStack();
    if ( UCSR0A & __BIT_MASK( UDRE0) ) {                  // Any characters to send?
        if ( UART[0].TxCount > 0 ) {
            UDR0 = UART[0].pTxBuffer[ UART[0].TxLast ];  // Send a character

            if ((++UART[0].TxLast)> TXSIZE_UART ) {     // End of buffer?
                UART[0].TxLast = 0 ;                     // yes, reset pointer
            }
            UART[0].TxCount--; 
        } else {
            UCSR0B &= ~(__BIT_MASK( UDRIE0)) ;            // transmission end, disable int.
            PORTE &= ~0x04 ;                              // TXE0 off
        }
    }
    OS_LeaveIntStack();
    OS_LeaveInterrupt();
} 
#endif

