/****************************************************************************************
/ AD converter handling , AD7715
/
***************************************************************************************/

#include "iom1280.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"

/*************************************************************************
*
*  External int 0 (UART PC16554 on AN-ZB485 or ADready on AN-ZBANA)
*
*************************************************************************/
#pragma vector=INT0_vect
__interrupt void IntHandler_INT0( void ){               //Int handler for ext int 0

    // OBS!!!
    // Uses UART16552[].TxStatus as intreason and
    // UART16552[].TxSeqCnt as counter because these needs to be globale 
    // by using OS_EnterIntStack()

    
    OS_EnterInterrupt();
    OS_EnterIntStack();

    switch (UnitID) {
    case AN_ZB485:                  // AN-ZB485
          UART16552[0].TxStatus = (U0_IIR & 0x0f);          // reason for interrupt
        do {
            switch (UART16552[0].TxStatus) {
            case 0x02 :             // transmit holding reg emty
                if (UART16552[0].TxCount == 0) {
                    U0_MCR &= ~RTS;        // set RTS off
                    OS_StopTimer(&TimerUART0);                    // and stop timer
                } else {
                    for (UART16552[0].TxSeqCnt = 0;( UART16552[0].TxSeqCnt < FIFO_TX_BUFSIZE ) && (UART16552[0].TxCount > 0 ); UART16552[0].TxSeqCnt++, --UART16552[0].TxCount) {
                        U0_THR = UART16552[0].pTxBuffer[UART16552[0].TxLast++];
                    }
                }
                break;
            case 0x04 :             // Receive data available    
            case 0x0C :             // or caracter timeout (FIFO)
                while (U0_LSR & DATA_READY) {

                    UART16552[0].pRxBuffer[ UART16552[0].RxFirst ] = U0_RBR;             // Read the character 

                    if (UART16552[0].RxState != HANDLE) {                 // ok to receive? 
                        switch (UART16552[0].RxState) {                   // Yes, check state
                        case SYNC :
                            if ( UART16552[0].pRxBuffer[ UART16552[0].RxFirst ] == ANPRO1_SYN) {
                                UART16552[0].SyncCnt ++ ;                 // count sync
                                UART16552[0].RxFirst = 0;                 // start at start of buff
                            } else if (UART16552[0].SyncCnt >= 2) {       // minimum two sync bytes
                                UART16552[0].SyncCnt = 0 ;                // reset counter
                                UART16552[0].RxState = HEADER ;
                                UART16552[0].RxLast = 0 ;
                                UART16552[0].RxTimeout = RX_TO_TIME ;   // reset timeout
                                UART16552[0].RxFirst++ ;                 //  1. char OK, start on next
                                ReceivePacketUart16552(0) ;              // Check package
                            } else {
                                UART16552[0].SyncCnt = 0 ;                // start over once more
                            }
                            break;
                        default :
                            if ((++UART16552[0].RxFirst) > RXSIZE_UART_16552) { // Point to next location
                                GoToSyncUART16552(0) ;                       // go to sync mode
                            } else {
                                ReceivePacketUart16552(0) ;              // Check package
                            }
                            break ;   
                        }
                    }
                } 
                break;
            case 0x06 :                 // Receiver line status, OR, PE, FR, Break int.
                U0_LSR;      // Dummy read to empty register        
                break;
            case 0x00 :                 // Modem status.
                U0_MSR;      // Dummy read to empty register           
                break;
            }
            UART16552[0].TxStatus = (U0_IIR & 0x0f) ;      // reason for interrupt, 
                                                                      // check again before exit to avoid lost int. and hang
        } while ((UART16552[0].TxStatus & 0x01) != 0x01) ;  
        break;
    case AN_ZBHART: //AN_ZBANA:                  // AN-ZBANA ADready EHSMark
        OS_SignalEvent(1, &TCB_AD7715);
        break;
    }
    OS_LeaveIntStack();
    OS_LeaveInterruptNoSwitch();

}


/*************************************************************************
*
*  External int 1 (UART PC16554 on AN-ZB485)
*
*************************************************************************/
#pragma vector=INT1_vect
__interrupt void IntHandler_INT1( void ){               //Int handler for Ext int 1

    // OBS!!!
    // Uses UART16552[].TxStatus as intreason and
    // UART16552[].TxSeqCnt as counter because these needs to be globale 
    // by using OS_EnterIntStack()
    
  
    OS_EnterInterrupt();
    OS_EnterIntStack();

    switch (UnitID) {
    case AN_ZB485:               // AN-ZB485
        UART16552[1].TxStatus = (U1_IIR & 0x0f) ;      // reason for interrupt
        do {
            switch (UART16552[1].TxStatus) {
            case 0x02 :             // transmit holding reg emty
                if (UART16552[1].TxCount == 0) {
                    U1_MCR &= ~RTS;        // set RTS off
                    OS_StopTimer(&TimerUART1);                    // and stop timer
                } else {
                    for (UART16552[1].TxSeqCnt = 0;( UART16552[1].TxSeqCnt < FIFO_TX_BUFSIZE ) && (UART16552[1].TxCount > 0 ); UART16552[1].TxSeqCnt++, UART16552[1].TxCount--) {
                       U1_THR = UART16552[1].pTxBuffer[UART16552[1].TxLast++] ;
                    }
                }
                break;
            case 0x04 :             // Receive data available    
            case 0x0C :             // or caracter timeout (FIFO)
                while (U1_LSR & DATA_READY) {

                    UART16552[1].pRxBuffer[ UART16552[1].RxFirst ] = U1_RBR;          // Read the character 

                    if (UART16552[1].RxState != HANDLE) {        // ok to receive? 
                        switch (UART16552[1].RxState) {                   // Yes, check state
                        case SYNC :
                            if ( UART16552[1].pRxBuffer[ UART16552[1].RxFirst ] == ANPRO1_SYN) {
                                UART16552[1].SyncCnt ++ ;                 // count sync
                                UART16552[1].RxFirst = 0;                 // start at start of buff
                            } else if (UART16552[1].SyncCnt >= 2) {       // minimum two sync bytes
                                UART16552[1].SyncCnt = 0 ;                // reset counter
                                UART16552[1].RxState = HEADER ;
                                UART16552[1].RxLast = 0 ;
                                UART16552[1].RxTimeout = RX_TO_TIME ;     // reset timeout
                                UART16552[1].RxFirst++ ;                  //  1. char OK, start on next
                                ReceivePacketUart16552(1) ;               // Check package
                            } else {
                                UART16552[1].SyncCnt = 0 ;                // start over once more
                            }
                            break;
                        default :
                            if ((++UART16552[1].RxFirst) > RXSIZE_UART_16552) { // Point to next location
                                GoToSyncUART16552(1) ;                       // go to sync mode
                            } else {
                                ReceivePacketUart16552(1) ;              // Check package
                            }
                            break ;   
                        }
                    }
                }
                break;
            case 0x06 :                 // Receiver line status, OR, PE, FR, Break int.
                U1_LSR;      // Dummy read to empty register        
                break;
            case 0x00 :                 // Modem status.
                U1_MSR;      // Dummy read to empty register           
                break;
            }
            UART16552[1].TxStatus = (U1_IIR & 0x0f) ;      // reason for interrupt, 
                                                                      // check again before exit to avoid lost int. and hang
       } while ((UART16552[1].TxStatus & 0x01) != 0x01);  
        break;
    case AN_ZBANA:                  // AN-ZBANA Not connected!
        break;
    }
    OS_LeaveIntStack();
    OS_LeaveInterruptNoSwitch();
}
