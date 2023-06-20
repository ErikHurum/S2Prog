#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"

void sendchar(char ch, char c){
  if (ch == 0) {
    UART_DATA_REG0 = c;                                   // prepare transmission
    while (!(UART_STATUS_REG0 & (1 << TRANSMIT_COMPLETE_BIT0)));// wait until byte sendt
    UART_STATUS_REG0 |= (1 << TRANSMIT_COMPLETE_BIT0);          // delete TXCflag
  }else if (ch == 1) {
    UART_DATA_REG1 = c;                                   // prepare transmission
    while (!(UART_STATUS_REG1 & (1 << TRANSMIT_COMPLETE_BIT1)));// wait until byte sendt
    UART_STATUS_REG1 |= (1 << TRANSMIT_COMPLETE_BIT1);          // delete TXCflag
  }  
}


void recchar(void){
  if((UART_STATUS_REG0 & (1 << RECEIVE_COMPLETE_BIT0)) ||(UART_STATUS_REG0 & 0x10)){
    UART[0].pRxBuffer[ UART[0].RxFirst ] = UART_DATA_REG0;                     // Read the character 
        if (UART[0].RxState != HANDLE) {        // ok to receive? 
            switch (UART[0].RxState) {                   // Yes, check state
            case SYNC :
                 if ( UART[0].pRxBuffer[ UART[0].RxFirst ] == ANPRO1_SYN) {
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
/* AStmark Not used on TPC
  if((UART_STATUS_REG1 & (1 << RECEIVE_COMPLETE_BIT1)) ||(UART_STATUS_REG1 & 0x10)){
    UART[1].pRxBuffer[ UART[1].RxFirst ] = UART_DATA_REG1;                     // Read the character 
    if (UART[1].RxState != HANDLE) {        // ok to receive? 
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
                UART[1].RxTimeout = RX_TO_TIME ;   // reset timeout
            } else {
                UART[1].SyncCnt = 0 ;                // start over once more
            }
            break;
        default :
            if ((++UART[1].RxFirst) > RXSIZE_UART) { // Point to next location
                GoToSyncUART(1) ;                       // go to sync mode
            } else {
                ReceivePacketUart(1) ;              // Check package
            }
            break ;   
        }
    }
  }
*/
}
