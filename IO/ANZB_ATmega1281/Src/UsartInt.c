/****************************************************************************************
/ USART1 functions and interrupt
/   This routines sync and check the ANPRO10
/   Uart1Pro.c handle the package
/
***************************************************************************************/

#if USE_MODBUS_PROTOCOL == 0

#include "iom1281.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

#if (OS_UART != 0)

// USART0
void Int_Handler_RX_USART0( void ){   

    if ( UCSR0A & __BIT_MASK( DOR0 ) ) {                // Overrun error? 
    }

    if ( UCSR0A & __BIT_MASK( FE0 ) ) {                 // Framing error? 
    }

    while ( UCSR0A & __BIT_MASK( RXC0)  ) {                // New byte avaiable?
        UART[0].pRxBuffer[ UART[0].RxFirst ] = UDR0;    // Read the character 

        if (UART[0].RxState != HANDLE) {                // ok to receive? 
            switch (UART[0].RxState) {                   // Yes, check state
            case SYNC :
                if ( UART[0].pRxBuffer[ UART[0].RxFirst ] == ANPRO10_SYN) {
                    UART[0].SyncCnt ++ ;                 // count sync
                    UART[0].RxFirst = 0;                 // start at start of buff
                } else if ((UART[0].SyncCnt >= 2) && 
                           (UART[0].pRxBuffer[ UART[0].RxFirst ] == ANPRO10_SOH)) {       // minimum two sync bytes
                    UART[0].SyncCnt = 0 ;                // reset counter
                    UART[0].RxState = HEADER ;
                    UART[0].RxLast = 0 ;
                    UART[0].RxTimeout = RX_TO_TIME ;    // reset timeout
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
} 


#pragma vector=USART0_RX_vect
__interrupt void IntHandler_RX_USART0( void ){   
    OS_CallISR(Int_Handler_RX_USART0);
}

void Int_Handler_TX_USART0( void ){   

    UCSR0B &= ~(__BIT_MASK( TXCIE0)) ;            // transmission end, disable int.
    PORTE &= ~0x04 ;                              // TXE0 off
    OS_StopTimer(&TimerUSART0);                    // and stop timer
    GoToSyncUART(0) ;                                    // go to sync modus for recive
    
}

#pragma vector=USART0_TX_vect
__interrupt void IntHandler_TX_USART0( void ){   
    OS_CallISR(Int_Handler_TX_USART0);
}

void Int_Handler_UDRE_USART0( void ){   
    if ( UART[0].TxCount-- > 0 ) {
        UDR0 = UART[0].pTxBuffer[ UART[0].TxLast ];     // Send a character
        UART[0].TxLast++;
    } else{                                             // Last byte sent?
          UCSR0B &= ~(__BIT_MASK( UDRIE0)) ;            // transmission end, disable int.
          UCSR0A |= (__BIT_MASK( TXC0)) ;               // Clear int bit in TXC.
          UCSR0B |= __BIT_MASK( TXCIE0) ;               // Enable TXC int.
    }           
} 
#endif

#pragma vector=USART0_UDRE_vect
__interrupt void IntHandler_UDRE_USART0( void ){   
    OS_CallISR(Int_Handler_UDRE_USART0);
}
// USART1
 void Int_Handler_RX_USART1( void ){   
    if ( UCSR1A & __BIT_MASK( DOR1 ) ) {                // Overrun error? 
    }

    if ( UCSR1A & __BIT_MASK( FE1 ) ) {                 // Framing error? 
    }

    while ( UCSR1A & __BIT_MASK( RXC1)  ) {                // New byte avaiable?
        UART[1].pRxBuffer[ UART[1].RxFirst ] = UDR1;    // Read the character 

        if (UART[1].RxState != HANDLE) {                // ok to receive? 
            switch (UART[1].RxState) {                   // Yes, check state
            case SYNC :
                if ( UART[1].pRxBuffer[ UART[1].RxFirst ] == ANPRO10_SYN) {
                    UART[1].SyncCnt ++ ;                 // count sync
                    UART[1].RxFirst = 0;                 // start at start of buff
                } else if ((UART[1].SyncCnt >= 2) && 
                           (UART[1].pRxBuffer[ UART[1].RxFirst ] == ANPRO10_SOH)) {       // minimum two sync bytes
                    UART[1].SyncCnt = 0 ;                // reset counter
                    UART[1].RxState = HEADER ;
                    UART[1].RxLast = 0 ;
                    UART[1].RxTimeout = RX_TO_TIME ;      // reset timeout
                } else {
                    UART[1].SyncCnt = 0 ;                // start over once more
                }
                break;
            default :
                if ((++UART[1].RxFirst) > RXSIZE_UART) { // Point to next location
                    GoToSyncUART(1) ;                    // go to sync mode
                } else {
                    ReceivePacketUart(1) ;              // Check package
                }
                break ;   
            }
        }
    }
} 

#pragma vector=USART1_RX_vect
__interrupt void IntHandler_RX_USART1( void ){   
    OS_CallISR(Int_Handler_RX_USART1);
}

void Int_Handler_TX_USART1( void ){   

    UCSR1B &= ~(__BIT_MASK( TXCIE1)) ;            // transmission end, disable int.
    PORTE &= ~0x08 ;                              // TXE1 off
    OS_StopTimer(&TimerUSART1);                    // and stop timer
    GoToSyncUART(1) ;                                    // go to sync modus for recive
}

#pragma vector=USART1_TX_vect
__interrupt void IntHandler_TX_USART1( void ){   
    OS_CallISR(Int_Handler_TX_USART1);
}

void Int_Handler_UDRE_USART1( void ){   

     if ( UART[1].TxCount-- > 0 ) {
        UDR1 = UART[1].pTxBuffer[ UART[1].TxLast ];  // Send a character
        UART[1].TxLast++;
     } else {
        UCSR1B &= ~(__BIT_MASK( UDRIE1)) ;            // transmission end, disable int.
        UCSR1A |= (__BIT_MASK( TXC1)) ;               // Clear int bit in TXC.
        UCSR1B |= __BIT_MASK( TXCIE1) ;               // Enable TXC int.
     }
} 

#pragma vector=USART1_UDRE_vect
__interrupt void IntHandler_UDRE_USART1( void ){   
    OS_CallISR(Int_Handler_UDRE_USART1);
}
#endif /* USE_MODBUS_PROTOCOL == 0 */
