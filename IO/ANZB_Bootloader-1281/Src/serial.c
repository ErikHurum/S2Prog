#ifdef __ATMEGA_1280__
#include	"iom1280.h"
#endif

#ifdef __AVR_ATmega1281__
#include	"iom1281.h"
#endif
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include <intrinsics.h>
void sendchar(char c){
    UART_DATA_REG0 = c;                                   // prepare transmission
    while (!(UART_STATUS_REG0 & (1 << TRANSMIT_COMPLETE_BIT0)));// wait until byte sendt
    UART_STATUS_REG0 |= (1 << TRANSMIT_COMPLETE_BIT0);          // delete TXCflag
}


void recchar(void){
  if((UART_STATUS_REG0 & (1 << RECEIVE_COMPLETE_BIT0)) ||(UART_STATUS_REG0 & 0x10)){
    RxBufferCh0[ myUART.RxFirst ] = UART_DATA_REG0;                     // Read the character 
    __watchdog_reset();
    if (myUART.RxState != HANDLE) {        // ok to receive? 
        switch (myUART.RxState) {                   // Yes, check state
        case SYNC :
            if ( RxBufferCh0[ myUART.RxFirst ] == ANPRO10_SYN) {
                myUART.SyncCnt ++ ;                 // count sync
                myUART.RxFirst = 0;                 // start at start of buff
            } else if ((myUART.SyncCnt >= 2) && 
                       (RxBufferCh0[ myUART.RxFirst ] == ANPRO10_SOH)) {       // minimum two sync bytes
                myUART.SyncCnt = 0 ;                // reset counter
                myUART.RxState = HEADER ;
                myUART.RxLast = 0 ;
                myUART.RxTimeout = RX_TO_TIME ;   // reset timeout
            } else {
                myUART.SyncCnt = 0 ;                // start over once more
            }
            break;
        default :
            if ((++myUART.RxFirst) > RXSIZE_UART) { // Point to next location
                GoToSyncUART() ;                       // go to sync mode
            } else {
                ReceivePacketUart(0) ;              // Check package
            }
            break ;   
        }
    }
  }
}
