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
    #pragma diag_suppress=Pa082



    #if USE_1281_RX_INT_TASK==1
static void _ATMega1281_irq_handler(char Ch) {
    char RxByte;
    OS_GetMail1(&UART[Ch].RxMailBox, &RxByte);

    UART[Ch].pRxBuffer[UART[Ch].RxFirst] = RxByte;    // Read the character
    switch (UART[Ch].RxState) {
    case HANDLE:
        // Not OK to receive as we are handling the message
        break;
    case SYNC :
        if (UART[Ch].pRxBuffer[UART[Ch].RxFirst] == ANPRO10_SYN) {
            UART[Ch].SyncCnt++;                 // count sync
            UART[Ch].RxFirst = 0;                 // start at start of buff
        } else if ((UART[Ch].SyncCnt >= 2) &&
                   (UART[Ch].pRxBuffer[UART[Ch].RxFirst] == ANPRO10_SOH)) {       // minimum two sync bytes
            UART[Ch].SyncCnt = 0;                // reset counter
            UART[Ch].RxState = HEADER;
            UART[Ch].RxLast = 0;
            UART[Ch].RxTimeout = RX_TO_TIME;    // reset timeout
        } else {
            UART[Ch].SyncCnt = 0;                // start over once more
        }
        break;
    default :
        if ((++UART[Ch].RxFirst) > RXSIZE_UART) { // Point to next location
            GoToSyncUART(Ch);                       // go to sync mode
        } else {
            ReceivePacketUart(Ch);              // Check package
        }
        break;
    }
}

        #pragma diag_suppress=Pe767

void ATMega1281_RX_driver_task(void *pVoid) {
    char Ch = (char)pVoid;
    Init_USART(Ch, 38400);              //
    while (1) {
        _ATMega1281_irq_handler(Ch);
    }
}

OS_TASK TCB_ATMega1281RX_Driver0;
OS_TASK TCB_ATMega1281RX_Driver1;
static OS_STACKPTR int stack1[300], stack2[300]; /* Task stacks */

void ATMega1281_driver_task_init(void) {
    OS_CREATETASK_EX(&TCB_ATMega1281RX_Driver0, "ATMega1281 RX Driver0", ATMega1281_RX_driver_task, 121, stack1, (void *)0);
    OS_CREATETASK_EX(&TCB_ATMega1281RX_Driver1, "ATMega1281 RX Driver1", ATMega1281_RX_driver_task, 120, stack2, (void *)1);
}
    #endif



// USART0
void Int_Handler_RX_USART0(void) {

    if (UCSR0A & __BIT_MASK(DOR0)) {                // Overrun error?
    }

    if (UCSR0A & __BIT_MASK(FE0)) {                 // Framing error?
    }
#if USE_1281_RX_INT_TASK==0
    while (UCSR0A & __BIT_MASK(RXC0)) {                // New byte avaiable?
        UART[0].pRxBuffer[UART[0].RxFirst] = UDR0;    // Read the character

        if (UART[0].RxState != HANDLE) {                // ok to receive?
            switch (UART[0].RxState) {                   // Yes, check state
            case SYNC :
                if (UART[0].pRxBuffer[UART[0].RxFirst] == ANPRO10_SYN) {
                    UART[0].SyncCnt++;                 // count sync
                    UART[0].RxFirst = 0;                 // start at start of buff
                } else if ((UART[0].SyncCnt >= 2) &&
                           (UART[0].pRxBuffer[UART[0].RxFirst] == ANPRO10_SOH)) {       // minimum two sync bytes
                    UART[0].SyncCnt = 0;                // reset counter
                    UART[0].RxState = HEADER;
                    UART[0].RxLast = 0;
                    UART[0].RxTimeout = RX_TO_TIME;    // reset timeout
                } else {
                    UART[0].SyncCnt = 0;                // start over once more
                }
                break;
            default :
                if ((++UART[0].RxFirst) > RXSIZE_UART) { // Point to next location
                    GoToSyncUART(0);                       // go to sync mode
                } else {
                    ReceivePacketUart(0);              // Check package
                }
                break;
            }
        }
    }
#else
    while (UCSR0A & __BIT_MASK(RXC0)) {                 // New byte avaiable?
        UART[0].RxByte = UDR0;                          // Read the character
        //if (OS_IsTask(&TCB_ATMega1281RX_Driver0)) {
            OS_PutMailCond1(&UART[0].RxMailBox, &UART[0].RxByte);
        //}
    }
#endif

}


    #pragma vector=USART0_RX_vect
__interrupt void IntHandler_RX_USART0(void) {
    OS_CallISR(Int_Handler_RX_USART0);
}

void Int_Handler_TX_USART0(void) {

    UCSR0B &= ~(__BIT_MASK(TXCIE0));            // transmission end, disable int.
    PORTE &= ~0x04;                              // TXE0 off
#if USE_1281_RX_INT_TASK == 0
    OS_StopTimer(&TimerUSART0);                    // and stop timer
#endif
    GoToSyncUART(0);                                    // go to sync modus for recive

}

    #pragma vector=USART0_TX_vect
__interrupt void IntHandler_TX_USART0(void) {
    OS_CallISR(Int_Handler_TX_USART0);
}

void Int_Handler_UDRE_USART0(void) {
    if (UART[0].TxCount-- > 0) {
        UDR0 = UART[0].pTxBuffer[UART[0].TxLast];     // Send a character
        UART[0].TxLast++;
    } else {                                             // Last byte sent?
        UCSR0B &= ~(__BIT_MASK(UDRIE0));            // transmission end, disable int.
        UCSR0A |= (__BIT_MASK(TXC0));               // Clear int bit in TXC.
        UCSR0B |= __BIT_MASK(TXCIE0);       // Enable TXC int.
        UART[0].RxState = SYNC;
    }
}


    #pragma vector=USART0_UDRE_vect
__interrupt void IntHandler_UDRE_USART0(void) {
    OS_CallISR(Int_Handler_UDRE_USART0);
}
// USART1
void Int_Handler_RX_USART1(void) {
#if USE_1281_RX_INT_TASK==0

    if (UCSR1A & __BIT_MASK(DOR1)) {                // Overrun error?
    }

    if (UCSR1A & __BIT_MASK(FE1)) {                 // Framing error?
    }

    while (UCSR1A & __BIT_MASK(RXC1)) {                // New byte avaiable?
        UART[1].pRxBuffer[UART[1].RxFirst] = UDR1;    // Read the character

        if (UART[1].RxState != HANDLE) {                // ok to receive?
            switch (UART[1].RxState) {                   // Yes, check state
            case SYNC :
                if (UART[1].pRxBuffer[UART[1].RxFirst] == ANPRO10_SYN) {
                    UART[1].SyncCnt++;                 // count sync
                    UART[1].RxFirst = 0;                 // start at start of buff
                } else if ((UART[1].SyncCnt >= 2) &&
                           (UART[1].pRxBuffer[UART[1].RxFirst] == ANPRO10_SOH)) {       // minimum two sync bytes
                    UART[1].SyncCnt = 0;                // reset counter
                    UART[1].RxState = HEADER;
                    UART[1].RxLast = 0;
                    UART[1].RxTimeout = RX_TO_TIME;      // reset timeout
                } else {
                    UART[1].SyncCnt = 0;                // start over once more
                }
                break;
            default :
                if ((++UART[1].RxFirst) > RXSIZE_UART) { // Point to next location
                    GoToSyncUART(1);                    // go to sync mode
                } else {
                    ReceivePacketUart(1);              // Check package
                }
                break;
            }
        }
    }
#else
    while (UCSR1A & __BIT_MASK(RXC1)) {                // New byte avaiable?
        UART[1].RxByte = UDR1;    // Read the character
        //if (OS_IsTask(&TCB_ATMega1281RX_Driver1)) {
            OS_PutMailCond1(&UART[1].RxMailBox, &UART[1].RxByte);
        //}
    }
#endif

}

    #pragma vector=USART1_RX_vect
__interrupt void IntHandler_RX_USART1(void) {
    OS_CallISR(Int_Handler_RX_USART1);
}

void Int_Handler_TX_USART1(void) {

    UCSR1B &= ~(__BIT_MASK(TXCIE1));            // transmission end, disable int.
    PORTE &= ~0x08;                              // TXE1 off
//    OS_StopTimer(&TimerUSART1);                    // and stop timer
    GoToSyncUART(1);                                    // go to sync modus for recive
}

    #pragma vector=USART1_TX_vect
__interrupt void IntHandler_TX_USART1(void) {
    OS_CallISR(Int_Handler_TX_USART1);
}

void Int_Handler_UDRE_USART1(void) {

    if (UART[1].TxCount-- > 0) {
        UDR1 = UART[1].pTxBuffer[UART[1].TxLast];     // Send a character
        UART[1].TxLast++;
    } else {
        UCSR1B &= ~(__BIT_MASK(UDRIE1));            // transmission end, disable int.
        UCSR1A |= (__BIT_MASK(TXC1));               // Clear int bit in TXC.
        UCSR1B |= __BIT_MASK(TXCIE1);       // Enable TXC int.
    }
}

    #pragma vector=USART1_UDRE_vect
__interrupt void IntHandler_UDRE_USART1(void) {
    OS_CallISR(Int_Handler_UDRE_USART1);
}

#endif /* USE_MODBUS_PROTOCOL == 0 */



