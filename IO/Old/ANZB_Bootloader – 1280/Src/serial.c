//#include "iom1280.h"
#include "stdio.h"
//#include "math.h"
#include "externals.h"

void sendchar(char c){
    UART_DATA_REG0 = c;                                   // prepare transmission
    while (!(UART_STATUS_REG0 & (1 << TRANSMIT_COMPLETE_BIT0)));// wait until byte sendt
    UART_STATUS_REG0 |= (1 << TRANSMIT_COMPLETE_BIT0);          // delete TXCflag
}


void recchar(void){
  if((UART_STATUS_REG0 & (1 << RECEIVE_COMPLETE_BIT0)) ||(UART_STATUS_REG0 & 0x10)){
    My485UART.pRxBuffer[ My485UART.RxFirst ] = UART_DATA_REG0;                     // Read the character 
    if (My485UART.RxState != HANDLE) {        // ok to receive? 
        switch (My485UART.RxState) {                   // Yes, check state
        case SYNC :
            if ( My485UART.pRxBuffer[ My485UART.RxFirst ] == ANPRO10_SYN) {
                My485UART.SyncCnt ++ ;                 // count sync
                My485UART.RxFirst = 0;                 // start at start of buff
            } else if ((My485UART.SyncCnt >= 2) && 
                       (My485UART.pRxBuffer[ My485UART.RxFirst ] == ANPRO10_SOH)) {       // minimum two sync bytes
                My485UART.SyncCnt = 0 ;                // reset counter
                My485UART.RxState = HEADER ;
                My485UART.RxLast = 0 ;
                My485UART.RxTimeout = RX_TO_TIME ;   // reset timeout
            } else {
                My485UART.SyncCnt = 0 ;                // start over once more
            }
            break;
        default :
            if ((++My485UART.RxFirst) > RXSIZE_UART) { // Point to next location
                GoToSyncUART() ;                       // go to sync mode
            } else {
                ReceivePacketUart() ;              // Check package
            }
            break ;   
        }
    }
  }
}
