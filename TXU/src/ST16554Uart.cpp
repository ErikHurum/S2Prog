#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "def.h"

#include "2410addr.h"
#include "2410lib.h"
#include "2410slib.h"
#include "rtos.h"
#include "TSNDefines.h"
#include "TSNConstants.h"
#include "ANSIString.h"
#include "TSNConfigString.h"
#include "TsnUart.h"
#include "ST16554Uart.h"
#ifndef MIN
    #define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif


ST165540Uart::ST165540Uart(int PortNum, unsigned BdRate, unsigned WrdLength, unsigned StpBits, char Prty, unsigned BufSize, int Dev, int HWProt, int SWProt, bool IsMstr, int MaxTimeChar, bool Relax, int LogP, int LogE, int DelayP) :
    TSNUart(PortNum, BdRate, WrdLength, StpBits, Prty, BufSize, Dev, HWProt, SWProt, IsMstr, MaxTimeChar, Relax, LogP, LogE, DelayP),
    FIFOInstalled(Unknown) {
    LastTxTime = 0;
    OS_CREATERSEMA(&TxSema);

    Channels[PortNumber] = this;

    RxBufPtr = (U8 *)malloc(BufSize);
    OS_CreateMB(&RxBuf, 1, BufSize, (char *)RxBufPtr);

    U8 *BasePtr[] = { rEXT_UART0, rEXT_UART1, rEXT_UART2, rEXT_UART3 };
    UartBase = BasePtr[PortNumber - FIRST_ST16554_PORT];


    switch (toupper(Parity)) {
    case 'E':
        ParityValue = 0x18;
        break;
    case 'O':
        ParityValue = 0x08;
        break;
    default:
    case 'N':
        ParityValue = 0x00;
        break;
    }
    UartBase[IER] = 0;
    UartBase[LCR] = 0x80;
    UartBase[DLL] = (XTAL_UART / 16 / BaudRate) & 0xff;
    UartBase[DLM] = ((XTAL_UART  / 16 / BaudRate) >> 8) & 0xff;
    UartBase[LCR] = (WordLength - 5) + ((StopBits - 1) << 2) + ParityValue;
    switch (SWProt) {
    case C_UART_SWPRO_MODBUS:
        if (BdRate <= 19200) {
            EnableFIFO(1);  //EHSMark Was 0
        } else {
            //Speed too high to measure time between character so better use FIFO
            EnableFIFO(8);
        }
        break;
    default:
        EnableFIFO(8);
        break;
    }
    EnableInt();

}

void ST165540Uart::EnableInt(void) {
    switch (PortNumber - FIRST_ST16554_PORT) {
    case 0:
        rINTMSK    &= ~BIT_EINT0;
        break;
    case 1:
        rINTMSK    &= ~BIT_EINT1;
        break;
    case 2:
        rINTMSK    &= ~BIT_EINT2;
        break;
    case 3:
        rINTMSK    &= ~BIT_EINT3;
        break;
    default:
        break;
    }
    UartBase[MCR] = MCR_OUT2;   // Enable interrupt
    UartBase[IER] = IER_TBE | IER_RXRDY;
}

/******************************************************************************
*
*   Tsn16550PhysicalHasFIFO
*/


FIFOStatus ST165540Uart::PhysicalHasFIFO(void) {
    if ((UartBase[FCR] & 0x30) == 0) {
        if ((UartBase[FCR] & 0xC0) == 0xC0) return (FIFOPresent);
        /* FIFO not enabeled allready, so we can continue */
        UartBase[FCR] = 0x01;
        if ((UartBase[FCR] & 0xC0) == 0xC0) return (FIFOPresent);
        else return (FIFONotPresent);
    } else return (FIFONotPresent);
}

/******************************************************************************
*
*   PhysicalHasFIFO
*/


/******************************************************************************
*
*   HasFIFO
*/

bool  ST165540Uart::HasFIFO(void) {
    if (FIFOInstalled == Unknown) FIFOInstalled = PhysicalHasFIFO();
    return (FIFOInstalled == FIFOPresent);
}


/******************************************************************************
*
*   EnableFIFO
*/

void ST165540Uart::EnableFIFO(int Trigger) {
    if (HasFIFO()) switch (Trigger) {
        case  0:
            UartBase[FCR] = 0x00; break;
        case  1:
            UartBase[FCR] = 0x01; break;
        case  4:
            UartBase[FCR] = 0x41; break;
        case  8:
            UartBase[FCR] = 0x81; break;
        case 14:
            UartBase[FCR] = 0xC1; break;
        default:
            /* Do nothing. Should give a message! */
            break;
        } else if (Trigger != 0) {}

    if (Trigger == 0) {
        TxFIFOSize = 1;
    } else {
        TxFIFOSize = 16;
    }
    //TxFIFOSize = 16-TxTrigger;

    RxFIFOSize = Trigger;
}



/*******************************************************************************
*
* 16550IntWr - handle a transmitter interrupt
*
* This routine handles write interrupts from the UART. It reads a character
* and puts it in the transmit holding register of the device for transfer.
*
* If there are no more characters to transmit, transmission is disabled by
* clearing the transmit interrupt enable bit in the IER(int enable register).
*
* RETURNS: N/A
*
*/

void ST165540Uart::Transmit(void) {
    bool SomeDataSent = false;
    if (TxDataPtr) {
        for (int i = 0; i < TxFIFOSize && TxDataPos < TxDataSize; i++) {
            UartBase[TXB] = TxDataPtr[TxDataPos++];
            TxByteCnt++;
            SomeDataSent = true;
        }
    }
    if (!SomeDataSent) {
        switch (SWProtocol) {
        case C_UART_SWPRO_ANPRO10:
            // Turn off the RS485 if nothing to send on this interrupt
            UartBase[MCR] = MCR_OUT2;
            ProtocolState = pNew_Sync;
            break;
        default:
            break;
        }
        if (TxTaskPtr && EventMask) {
            OS_SignalEvent(EventMask, (TSN_TASK *)TxTaskPtr);
            TxTaskPtr = NULL;
        }
    }
}

/*******************************************************************************
*
* 16550IntRd - handle a  receiver interrupt
*
* This routine handles read interrupts from the UART.
*
* RETURNS: N/A
*
*/

void ST165540Uart::ReceiveInt(void) {
    /* read character from Receive Holding Reg.                 */
    /* I will allways read rx register and push it on the stack */
    do {
        U8 RxData = UartBase[RXB];
        OS_PutMailCond1(&RxBuf, (char *)&RxData);
        RxByteCnt++;
    } while (UartBase[LSR] & LSR_RXRDY);
    LastRxTime      = (int)OS_Time;
}
/*******************************************************************************
*
* 16550Int - handle a receiver/transmitter interrupt
*
* This routine handles four sources of interrupts from the UART. They are
* prioritized in the following order by the Interrupt Identification Register:
* Receiver Line Status, Received Data Ready, Transmit Holding Register Empty
* and Modem Status.
*
* If there is another character to be transmitted, it sends it.  If
* not, or if a device has never been created for this channel, just
* disable the interrupt.
* When a modem status interrupt occurs, the transmit interrupt is enabled if
* the CTS signal is TRUE.
*
* RETURNS: N/A
*/
#pragma diag_suppress=Pe177

void ST165540Uart::HandleInterrupt(void) {

    volatile U8 interruptID = UartBase[IIR];

    do {
        interruptID &= IIR_MASK;
        switch (interruptID) {
        case IIR_SEOB:
            {
                U8 LineStatus = UartBase[LSR];
            }
            break;
        case IIR_TOUT:
        case IIR_RBRF:
            ReceiveInt();
            break;
        case IIR_THRE:
            Transmit();
            break;
        case IIR_MSTAT:
            {     /* Should never come her but anyway be a little prepared for the future */
                /* modem status register */
                U8 msr = UartBase[MSR];

                /* if CTS is asserted by modem, enable tx interrupt */

                if ((msr & MSR_CTS) && (msr & MSR_DCTS)) {
                    UartBase[IER] = IER_TBE | IER_RXRDY | IER_MSI;
                } else {
                    UartBase[IER] = IER_RXRDY | IER_MSI;
                }
            }
            break;
        }
        interruptID = UartBase[IIR];
    } while ((interruptID & 0x01) == 0);
}

void ST165540Uart::ActivateTx(void) {
    // Turn on the RS485 if nothing to send on this interrupt
    UartBase[MCR] = MCR_OUT2 | MCR_RTS;
    ProtocolState = pInTx;
    switch (SWProtocol) {
    case C_UART_SWPRO_ANPRO10:
        TxDataPtr[TxDataSize++] = 0x0;
        break;
    default:
        break;
    }
    LastTxTime   = OS_Time;
    OS_Delay(RS485_ON_DELAY);
    UartBase[TXB] = TxDataPtr[TxDataPos++];
}

void ST165540Uart::DeactivateTx(void) {
    // Turn off the RS485
    if (HWProtocol == C_UART_HWPRO_485) {
        UartBase[MCR] = MCR_OUT2;
    }
}

bool ST165540Uart::Send(U8 *MyData, int Size, char EventMsk, bool Wait) {
    bool TxOk = false;
    if (Size) {
        OS_Use(&TxSema);
        TxDataPtr   = MyData;
        TxDataSize  = Size;
        TxDataPos   = 0;

        EventMask = EventMsk;
        if (EventMsk) {
            TxTaskPtr = OS_GetpCurrentTask();
        } else {
            TxTaskPtr = NULL;
        }
        int sendDelay = (130000 * TxDataSize) / BaudRate + RS485_EXTRA_DELAY;
        switch (SWProtocol) {
        case C_UART_SWPRO_ANPRO10:
            if (IsMaster) {
                // Asume we have to force the tx if TxRequest = true!
                if (TxRequest || ProtocolState == pNew_Sync) {
                    TxRequest = false;
                    ActivateTx();
                } else {
                    sendDelay += RS485_DELAY;
                    TxRequest = true;
                }
            } else {
                TxRequest  = true;
                if (LastRxTime < 10) {
                    sendDelay     += RS485_DELAY; // Abort Tx if not completed within this time
                    ActivateIfTxRequest();
                } else {
                    sendDelay     += RS485_DELAY + 1000; // Abort Tx if not completed within this time
                }
            }
            break;
        default:
            ActivateTx();
            break;
        }

        char Status = 0;
        if (Wait && EventMsk) {
            Status = OS_WaitEventTimed(EventMsk, sendDelay);
            TxTaskPtr = NULL;
            switch (SWProtocol) {
            case C_UART_SWPRO_ANPRO10:
                ClearRxBuffer();
                DeactivateTx();
                ProtocolState = pNew_Sync;
                break;
            default:
                OS_Delay(RS485_ON_DELAY);
                DeactivateTx();
                break;
            }
        }
        OS_Unuse(&TxSema);
        TxOk = (Status == EventMsk);
    }

    return (TxOk);
}



bool ST165540Uart::Receive(U8 *MyData, int Size, int TimeOut) {
    int Cnt = 0;
    bool ReceivedData = true;

    while (ReceivedData && Cnt < Size) {
        ReceivedData = !OS_GetMailTimed(&RxBuf, (char *)&MyData[Cnt++], TimeOut);
    }
    return (ReceivedData);
}

void ST165540Uart::ClearRxBuffer(void) {
    OS_ClearMB(&RxBuf);
    //for(int i=0; i < 8; i++){
    //	U8 RxData = UartBase[RXB];
    //}
}

bool ST165540Uart::HasMore(void) {
    int RxBytesInBuf = OS_GetMessageCnt(&RxBuf);
    return (bool(RxBytesInBuf));
}

