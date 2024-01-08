/****************************************************************************************
/ AD converter handling , AD7715
/
***************************************************************************************/

#include "iom1281.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#pragma diag_suppress=Pa082

#if USE_16552_DRIVER_TASK == 1
void _16552_Rx_handler(void *pData) {
    const char Ch = (char)pData;
    char *RxBuff = UART16552[Ch].pRxBuffer;
    OS_WaitEvent(0x01);
    while (true) {
        char RxByte;
        OS_GetMail1(&UART16552[Ch].RxMailBox, &RxByte);
        RxBuff[UART16552[Ch].RxFirst] = RxByte;
        if (UART16552[Ch].RxState != HANDLE) {                 // ok to receive?
            switch (UART16552[Ch].RxState) {                   // Yes, check state
            case SYNC :
                if (RxByte == ANPRO1_SYN) {
                    UART16552[Ch].SyncCnt++;                 // count sync
                    UART16552[Ch].RxFirst = 0;                 // start at start of buff
                } else if (UART16552[Ch].SyncCnt >= 2) {       // minimum two sync bytes
                    UART16552[Ch].SyncCnt = 0;                // reset counter
                    UART16552[Ch].RxState = HEADER;
                    UART16552[Ch].RxLast = 0;
                    UART16552[Ch].RxTimeout = RX_TO_TIME;   // reset timeout
                    UART16552[Ch].RxFirst++;                 //  1. char OK, start on next
                    ReceivePacketUart16552(Ch);              // Check package
                } else {
                    UART16552[Ch].SyncCnt = 0;                // start over once more
                }
                break;
            default :
                if ((++UART16552[Ch].RxFirst) > RXSIZE_UART_16552) { // Point to next location
                    GoToSyncUART16552(Ch);                       // go to sync mode
                } else {
                    ReceivePacketUart16552(Ch);              // Check package
                }
                break;
            }
        }
    }
}


OS_TASK TCB_16552_RxHandler1;
OS_TASK TCB_16552_RxHandler2;
static OS_STACKPTR int stack1[300]; /* Task stacks */
static OS_STACKPTR int stack2[300]; /* Task stacks */

void _16552_driver_task_init(void) {

    OS_CREATETASK_EX(&TCB_16552_RxHandler1, "16552_RX_Handler 0", _16552_Rx_handler, 96, stack1, (void *)0);
    OS_CREATETASK_EX(&TCB_16552_RxHandler2, "16552_RX_Handler 1", _16552_Rx_handler, 95, stack2, (void *)1);
}
#endif

/*************************************************************************
*
*  External int 0 (UART PC16554 on AN-ZB485 or ADready on AN-ZBANA)
*
*************************************************************************/
void Int_Handler_INT0(void) {               //Int handler for ext int 0

    // OBS!!!
    // Uses UART16552[].TxStatus as intreason and
    // UART16552[].TxSeqCnt as counter because these needs to be globale
    // by using OS_EnterIntStack()


    switch (UnitID) {
    case 0x00:                  // AN-ZB485
#if USE_16552_DRIVER_TASK == 0
        UART16552[0].TxStatus = (U0_IIR & 0x0f);          // reason for interrupt
        do {
            switch (UART16552[0].TxStatus) {
            case 0x02 :             // transmit holding reg emty
                if (UART16552[0].TxCount == 0) {
                    U0_MCR  &= ~RTS;        // set RTS off
                    UART16552[0].RxState = SYNC;
                    //OS_StopTimer(&TimerUART0);                    // and stop timer
                } else {
                    for (UART16552[0].TxSeqCnt = 0; (UART16552[0].TxSeqCnt < FIFO_TX_BUFSIZE) && (UART16552[0].TxCount > 0); UART16552[0].TxSeqCnt++, --UART16552[0].TxCount) {
                        U0_THR = UART16552[0].pTxBuffer[UART16552[0].TxLast++];
                    }
                }
                break;
            case 0x04 :             // Receive data available
            case 0x0C :             // or caracter timeout (FIFO)
                if (UART16552[0].RxState == SEND) {
                    while (U0_LSR & DATA_READY) {
                        U0_RBR;
                    }
                } else while (U0_LSR & DATA_READY) {
                    UART16552[0].pRxBuffer[UART16552[0].RxFirst] = U0_RBR;             // Read the character

                    if (UART16552[0].RxState != HANDLE) {                 // ok to receive?
                        switch (UART16552[0].RxState) {                   // Yes, check state
                        case SYNC :
                            if (UART16552[0].pRxBuffer[UART16552[0].RxFirst] == ANPRO1_SYN) {
                                UART16552[0].SyncCnt++;                 // count sync
                                UART16552[0].RxFirst = 0;                 // start at start of buff
                            } else if (UART16552[0].SyncCnt >= 2) {       // minimum two sync bytes
                                UART16552[0].SyncCnt = 0;                // reset counter
                                UART16552[0].RxState = HEADER;
                                UART16552[0].RxLast = 0;
                                UART16552[0].RxTimeout = RX_TO_TIME;   // reset timeout
                                UART16552[0].RxFirst++;                 //  1. char OK, start on next
                                ReceivePacketUart16552(0);              // Check package
                            } else {
                                UART16552[0].SyncCnt = 0;                // start over once more
                            }
                            break;
                        default :
                            if ((++UART16552[0].RxFirst) > RXSIZE_UART_16552) { // Point to next location
                                GoToSyncUART16552(0);                       // go to sync mode
                            } else {
                                ReceivePacketUart16552(0);              // Check package
                            }
                            break;
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
            UART16552[0].TxStatus = (U0_IIR & 0x0f);      // reason for interrupt,
            // check again before exit to avoid lost int. and hang
        } while ((UART16552[0].TxStatus & 0x01) != 0x01);
#else
        UART16552[0].TxStatus = (U0_IIR & IIR_MASK);          // reason for interrupt
        do {
            switch (UART16552[0].TxStatus) {
            case IIR_THRE :             // transmit holding reg emty
                if (UART16552[0].TxCount == 0) {
                    U0_MCR &= ~RTS;        // set RTS off
                    UART16552[0].RxState = SYNC;
                    //OS_StopTimer(&TimerUART0);                    // and stop timer
                } else {
                    for (UART16552[0].TxSeqCnt = 0; (UART16552[0].TxSeqCnt < FIFO_TX_BUFSIZE) && (UART16552[0].TxCount > 0); UART16552[0].TxSeqCnt++, --UART16552[0].TxCount) {
                        U0_THR = UART16552[0].pTxBuffer[UART16552[0].TxLast++];
                    }
                }
                break;
            case IIR_TOUT:          // Receive data available
            case IIR_RBRF:          // or caracter timeout (FIFO)
                if (UART16552[0].RxState == SEND) {
                    while (U0_LSR & DATA_READY) {
                        U0_RBR;
                    }
                } else {
                    while (U0_LSR & DATA_READY) {
                        UART16552[0].RxByte = U0_RBR;    // Read the character
                        OS_PutMailCond1(&UART16552[0].RxMailBox, &UART16552[0].RxByte);
                    }
                }
                break;
            case IIR_SEOB:   // Receiver line status, OR, PE, FR, Break int.
                U0_LSR;      // Dummy read to empty register
                break;
            case IIR_MSTAT :                 // Modem status.
                U0_MSR;      // Dummy read to empty register
                break;
            }
            UART16552[0].TxStatus = (U0_IIR & IIR_MASK);      // reason for interrupt,
            // check again before exit to avoid lost int. and hang
        } while ((UART16552[0].TxStatus & 0x01) == 0x00);

#endif
        break;
    case 0x01:                  // AN-ZBANA ADready
        OS_SignalEvent(1, &TCB_AD7715);
        break;
    }
}


#pragma vector=INT0_vect
__interrupt void IntHandler_INT0(void) {               //Int handler for ext int 0
    OS_CallISR(Int_Handler_INT0);
}

/*************************************************************************
*
*  External int 1 (UART PC16554 on AN-ZB485)
*
*************************************************************************/
void Int_Handler_INT1(void) {               //Int handler for Ext int 1

    // OBS!!!
    // Uses UART16552[].TxStatus as int reason and
    // UART16552[].TxSeqCnt as counter because these needs to be globale
    // by using OS_EnterIntStack()

    switch (UnitID) {
    case 0x00:                  // AN-ZB485
#if USE_16552_DRIVER_TASK == 0
        UART16552[1].TxStatus = (U1_IIR & 0x0f);          // reason for interrupt
        do {
            switch (UART16552[1].TxStatus) {
            case 0x02 :             // transmit holding reg emty
                if (UART16552[1].TxCount == 0) {
                    U1_MCR &= ~RTS;        // set RTS off
                    UART16552[1].RxState = SYNC;
                    //OS_StopTimer(&TimerUART1);                    // and stop timer
                } else {
                    for (UART16552[1].TxSeqCnt = 0; (UART16552[1].TxSeqCnt < FIFO_TX_BUFSIZE) && (UART16552[1].TxCount > 0); UART16552[1].TxSeqCnt++, UART16552[1].TxCount--) {
                        U1_THR = UART16552[1].pTxBuffer[UART16552[1].TxLast++];
                    }
                }
                break;
            case 0x04 :             // Receive data available
            case 0x0C :             // or caracter timeout (FIFO)
                if (UART16552[1].RxState == SEND) {
                    while (U1_LSR & DATA_READY) {
                        U1_RBR;
                    }
                } else while (U1_LSR & DATA_READY) {
                    UART16552[1].pRxBuffer[UART16552[1].RxFirst] = U1_RBR;             // Read the character

                    if (UART16552[1].RxState != HANDLE) {        // ok to receive?
                        switch (UART16552[1].RxState) {                   // Yes, check state
                        case SYNC :
                            if (UART16552[1].pRxBuffer[UART16552[1].RxFirst] == ANPRO1_SYN) {
                                UART16552[1].SyncCnt++;                 // count sync
                                UART16552[1].RxFirst = 0;                 // start at start of buff
                            } else if (UART16552[1].SyncCnt >= 2) {       // minimum two sync bytes
                                UART16552[1].SyncCnt = 0;                // reset counter
                                UART16552[1].RxState = HEADER;
                                UART16552[1].RxLast = 0;
                                UART16552[1].RxTimeout = RX_TO_TIME;     // reset timeout
                                UART16552[1].RxFirst++;                  //  1. char OK, start on next
                                ReceivePacketUart16552(1);               // Check package
                            } else {
                                UART16552[1].SyncCnt = 0;                // start over once more
                            }
                            break;
                        default :
                            if ((++UART16552[1].RxFirst) > RXSIZE_UART_16552) { // Point to next location
                                GoToSyncUART16552(1);                       // go to sync mode
                            } else {
                                ReceivePacketUart16552(1);              // Check package
                            }
                            break;
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
            UART16552[1].TxStatus = (U1_IIR & 0x0f);      // reason for interrupt,
            // check again before exit to avoid lost int. and hang
        } while ((UART16552[1].TxStatus & 0x01) != 0x01);
#else
        UART16552[1].TxStatus = (U1_IIR & IIR_MASK);          // reason for interrupt
        do {
            switch (UART16552[1].TxStatus) {
            case IIR_THRE :             // transmit holding reg emty
                if (UART16552[1].TxCount == 0) {
                    U1_MCR &= ~RTS;        // set RTS off
                    UART16552[1].RxState = SYNC;
                    //OS_StopTimer(&TimerUART0);                    // and stop timer
                } else {
                    for (UART16552[1].TxSeqCnt = 0; (UART16552[1].TxSeqCnt < FIFO_TX_BUFSIZE) && (UART16552[1].TxCount > 0); UART16552[1].TxSeqCnt++, --UART16552[1].TxCount) {
                        U1_THR = UART16552[1].pTxBuffer[UART16552[1].TxLast++];
                    }
                }
                break;
            case IIR_TOUT:          // Receive data available
            case IIR_RBRF:          // or caracter timeout (FIFO)
                if (UART16552[1].RxState == SEND) {
                    while (U1_LSR & DATA_READY) {
                        U1_RBR;
                    }
                } else {
                    while (U1_LSR & DATA_READY) {
                        UART16552[1].RxByte = U1_RBR;    // Read the character
                        OS_PutMailCond1(&UART16552[1].RxMailBox, &UART16552[1].RxByte);
                    }
                }
                break;
            case IIR_SEOB:   // Receiver line status, OR, PE, FR, Break int.
                U1_LSR;      // Dummy read to empty register
                break;
            case IIR_MSTAT :                 // Modem status.
                U1_MSR;      // Dummy read to empty register
                break;
            }
            UART16552[1].TxStatus = (U1_IIR & IIR_MASK);      // reason for interrupt,
            // check again before exit to avoid lost int. and hang
        } while ((UART16552[1].TxStatus & 0x01) == 0x00);
#endif
        break;
    case 0x01:                  // AN-ZBANA Not connected!
        break;
    }
}


#pragma vector=INT1_vect
__interrupt void IntHandler_INT1(void) {               //Int handler for Ext int 1

    OS_CallISR(Int_Handler_INT1);
}
