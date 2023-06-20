/****************************************************************************************
/ USART1 functions and interrupt
/   This routines sync and check the ANPRO10
/   My485UART1Pro.c handle the package
/
***************************************************************************************/


#include "iom1280.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"
extern OS_TASK     TCB_USART0;                                         /* Task-control-blocks */


#if (OS_UART != 0)

// USART0
void INT_Handler_RX_USART0( void ){   
    OS_DI();             // Disable before allowing new Rx interrupt
    if ( UCSR0A & __BIT_MASK( DOR0 ) ) {                // Overrun error? 
    }

    if ( UCSR0A & __BIT_MASK( FE0 ) ) {                 // Framing error? 
    }

    while ( UCSR0A & __BIT_MASK( RXC0)  ) {                // New byte avaiable?
		char Data = UDR0;
        if ( hasStartedUARTTask ) {
            CriticalComError = OS_PutMailCond1(&My485UART.RxMailBox, &Data);
        }
    }
} 
#pragma vector=USART0_RX_vect

__interrupt void IntHandler_RX_USART0( void ){   
    OS_CallISR(INT_Handler_RX_USART0);
} 
void INT_Handler_TX_USART0( void ){   
    UCSR0B &= ~(__BIT_MASK( TXCIE0)) ;            // transmission end, disable int.
    PORTE &= ~0x04 ;                              // TXE0 off
    OS_SignalEvent(UART0_EVENT_TX_COMPLETE, &TCB_USART0); // No more to send
}

#pragma vector=USART0_TX_vect

__interrupt void IntHandler_TX_USART0( void ){   
    OS_CallISR(INT_Handler_TX_USART0); 
    
}

void INT_Handler_UDRE_USART0( void ){   

    if ( My485UART.TxLast < My485UART.TxCount ) { // Last byte sent?
        UDR0 = My485UART.pTxBuffer[ My485UART.TxLast ];     // Send a character
        My485UART.TxLast++;
    } else{   
        OS_DI();             // Disable before allowing Tx interrupt
        UCSR0B &= ~(__BIT_MASK( UDRIE0)) ;            // transmission end, disable int.
        UCSR0A |= (__BIT_MASK( TXC0)) ;               // Clear int bit in TXC.
        UCSR0B |= __BIT_MASK( TXCIE0) ;               // Enable TXC int.
    }           
} 

#pragma vector = USART0_UDRE_vect
__interrupt void IntHandler_UDRE_USART0( void ){   
    OS_CallISR(INT_Handler_UDRE_USART0);
} 
#endif

