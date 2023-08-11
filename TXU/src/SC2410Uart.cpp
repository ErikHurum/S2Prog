#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "def.h"
#include "2410addr.h"
#include "2410lib.h"
#include "2410slib.h"
#include "rtos.h"
//#include "ANPro10Inc.h"
#include "TSNDefines.h"
#include "TSNConstants.h"
#include "ANSIString.h"
#include "TSNConfigString.h"
#include "TsnUart.h"
#include "SC2410Uart.h"


extern int OS_FSys;

SC2410Uart::SC2410Uart(int PortNum,unsigned BdRate,unsigned WrdLength,unsigned StpBits,char Prty, unsigned BufSize, int Dev, int HWProt,int SWProt, bool IsMstr,int MaxTimeChar,bool Relax, int LogP, int LogE, int DelayP):
TSNUart(PortNum,BdRate,WrdLength, StpBits, Prty, BufSize, Dev, HWProt,SWProt, IsMstr,MaxTimeChar, Relax, LogP, LogE,DelayP)
{
	OS_CREATERSEMA(&TxSema);
	Channels[PortNumber] = this;

	RxBufPtr=(U8*)malloc(BufSize);
	OS_CreateMB(&RxBuf,1,BufSize,(char*)RxBufPtr);

	switch ( PortNumber ) {
	case 0:
		BitSubRx  = BIT_SUB_RXD0;
		BitSubTx  = BIT_SUB_TXD0;
		BitSubErr = BIT_SUB_ERR0;
		break;
	case 1:
		BitSubRx  = BIT_SUB_RXD1;
		BitSubTx  = BIT_SUB_TXD1;
		BitSubErr = BIT_SUB_ERR1;
		break;
	case 2:
		BitSubRx  = BIT_SUB_RXD2;
		BitSubTx  = BIT_SUB_TXD2;
		BitSubErr = BIT_SUB_ERR2;
		break;
	}
	{
		unsigned PortOffset = 0x4000*PortNumber;
		rTxReg          =(unsigned char*)(ADDR_UTXH0   + PortOffset);
		rRxReg          =(unsigned char*)(ADDR_URXH0   + PortOffset);
		rLineControl    =(unsigned*)(ADDR_ULCON0  + PortOffset);
		rUartControl    =(unsigned*)(ADDR_UCON0   + PortOffset);
		rFIFOControl    =(unsigned*)(ADDR_UFCON0  + PortOffset);
		rModemControl   =(unsigned*)(ADDR_UMCON0  + PortOffset);
		rTxRxStatus     =(unsigned*)(ADDR_UTRSTAT0+ PortOffset);
		rRxErrorStatus  =(unsigned*)(ADDR_UERSTAT0+ PortOffset);
		rFIFOStatus     =(unsigned*)(ADDR_UFSTAT0 + PortOffset);
		rModemStatus    =(unsigned*)(ADDR_UMSTAT0 + PortOffset);
		rBaudRateDivisor=(unsigned*)(ADDR_UBRDIV0 + PortOffset);
	}

	switch ( toupper(Parity) ) {
	case 'E':
		ParityValue = 0x05;
		break;
	case 'O':
		ParityValue = 0x04;
		break;
	default:
	case 'N':
		ParityValue = 0x00;
		break;
	}
	*rUartControl = 0x85;	// Rx timeout enable
	*rLineControl =  (ParityValue<<3) | (WordLength-5) | (StopBits-1);
	*rBaudRateDivisor = (OS_FSys/4)/(16*BaudRate)-1;
	if ( HWProtocol == C_UART_HWPRO_485 ) {
		// Turn off the RS485 if nothing to send on this interrupt
		rGPHDAT &= ~2;
	}
	switch(SWProt){
	case C_UART_SWPRO_MODBUS:
		if ( BdRate > 19200 ) {
			//Speed too high to measure time between character so better use FIFO
			EnableFIFO(0,12);   
			//EnableFIFO(0,0); 
		}
		break;
	default:
		EnableFIFO(0,12);
		break;
	}

	EnableInt();
}

void SC2410Uart::EnableInt(void)
{
	switch ( PortNumber ) {
	case 0:
		rINTMSK    &= ~BIT_UART0;
		rINTSUBMSK &= ~(BIT_SUB_TXD0 | BIT_SUB_RXD0);
		break;
	case 1:
		rINTMSK    &= ~BIT_UART1;
		rINTSUBMSK &= ~(BIT_SUB_TXD1 | BIT_SUB_RXD1);
		break;
	case 2:
		rINTMSK    &= ~BIT_UART2;
		rINTSUBMSK &= ~(BIT_SUB_TXD2 | BIT_SUB_RXD2);
		break;
	default:
		break;

	}
}


/******************************************************************************
*
*   EnableFIFO
*/

void SC2410Uart::EnableFIFO(int TxTrigger, int RxTrigger)
{
	unsigned RxTmpTrigger=0,TxTmpTrigger=0;
	switch ( TxTrigger ) {
	default:
	case  0: TxTmpTrigger= 0x00; break;
	case  4: TxTmpTrigger= 0x01; break;
	case  8: TxTmpTrigger= 0x02; break;
	case 12: TxTmpTrigger= 0x03; break;
	}
	switch ( RxTrigger ) {
	default:
	case  4: RxTmpTrigger= 0x00; break;
	case  8: RxTmpTrigger= 0x01; break;
	case 12: RxTmpTrigger= 0x02; break;
	case 16: RxTmpTrigger= 0x03; break;
	}
	*rFIFOControl = (TxTmpTrigger << 6) | (RxTmpTrigger << 4 ) | 1;

	TxFIFOSize = 16-TxTrigger;
	RxFIFOSize = RxTrigger;
}



/*******************************************************************************
*
* IntWr - handle a transmitter interrupt
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

void SC2410Uart::Transmit(void)
{

	bool SomeDataSent = false;
	if ( TxDataPtr ) {
		for ( int i=0; i < TxFIFOSize && TxDataPos < TxDataSize; i++ ) {
			*rTxReg = TxDataPtr[TxDataPos++];
			TxByteCnt++;
			SomeDataSent = true;
		}
	}
	if ( !SomeDataSent ) {
		if ( HWProtocol == C_UART_HWPRO_485 ) {
			switch (SWProtocol) {
			case C_UART_SWPRO_ANPRO10:
				// Turn off the RS485 if nothing to send on this interrupt
				rGPHDAT &= ~2;
				ProtocolState = pNew_Sync;
				break;
			default:
				break;
			}
		}
		if ( TxTaskPtr ) {
			if ( EventMask ) {
				OS_SignalEvent(EventMask,(TSN_TASK*)TxTaskPtr);
			}
			TxTaskPtr = NULL;
		}
	}
}

/*******************************************************************************
*
* Tsn16550IntRd - handle a  receiver interrupt
*
* This routine handles read interrupts from the UART.
*
* RETURNS: N/A
*
*/

void SC2410Uart::ReceiveInt(void){
	/* read character from Receive Holding Reg.                 */
	/* I will allways read rx register and push it on the stack */
	if ( RxFIFOSize > 1 ) {
		if ( *rFIFOStatus & 0x100 ) {
			*rFIFOControl |= 0x2;
		} else {
			int Cnt = *rFIFOStatus & 0x0F;
			while ( Cnt >0 ) {
				char RxData = *rRxReg;
				OS_PutMailCond1(&RxBuf,&RxData);
				RxByteCnt++;
				Cnt--;
			}
		}
	} else {
		char RxData = *rRxReg;
		char Status = OS_PutMailCond1(&RxBuf,&RxData);
	}
	LastRxTime      = (int)OS_Time;
}


/*******************************************************************************
*
* Tsn16550Int - handle a receiver/transmitter interrupt
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

void SC2410Uart::HandleInterrupt(void)
{
	unsigned IntSubSource = rSUBSRCPND;
	unsigned InsSubMask   = rINTSUBMSK;

	if ( IntSubSource & BitSubErr ) {
		// Do nothing for now
		rSUBSRCPND = BitSubErr;
	}
	if ( IntSubSource & BitSubRx ) {
		// rUTXH1 = rURXH1;
		ReceiveInt();
		rSUBSRCPND = BitSubRx;
	}
	if ( IntSubSource & BitSubTx ) {
		Transmit();
		rSUBSRCPND = BitSubTx;
	}
}

void SC2410Uart::ActivateTx(void)
{
	rGPHDAT  |= 2;
	switch (SWProtocol) {
	case C_UART_SWPRO_ANPRO10:
		TxDataPtr[TxDataSize++] = 0x0;
		break;
	default:
		break;
	}
	ProtocolState = pInTx;
	OS_Delay(RS485_ON_DELAY);
	*rTxReg = TxDataPtr[TxDataPos++];
}

void SC2410Uart::DeactivateTx(void)
{
	// Turn off the RS485
    if ( HWProtocol == C_UART_HWPRO_485 ){
        rGPHDAT &= ~2;
    }
}


bool SC2410Uart::Send(U8* MyData, int Size, char EventMsk, bool Wait)
{
	bool TxOk = false;
	if ( !Size ) return true;
	OS_Use(&TxSema);
	TxDataPtr   = MyData;
	TxDataSize  = Size;
	TxDataPos   = 0;

	if ( Size ) {
		EventMask = EventMsk;
		if ( EventMsk ) {
			TxTaskPtr = OS_GetpCurrentTask();
		} else {
			TxTaskPtr = NULL;
		}
		int Delay=(130000*TxDataSize)/BaudRate+RS485_EXTRA_DELAY;
		switch ( HWProtocol ) {
		case C_UART_HWPRO_485 :
			switch (SWProtocol) {
			case C_UART_SWPRO_ANPRO10:
				if ( IsMaster ) {
					// Asume we have to force the tx if TxRequest = true!
					if ( TxRequest || ProtocolState == pNew_Sync ) {
						TxRequest = false;
 						ActivateTx();
					} else {
						TxRequest = true;
					}
				} else {
					TxRequest  = true;
					if (LastRxTime < 10 ) {
						Delay     += RS485_DELAY; // Abort Tx if not completed within this time
						ActivateIfTxRequest();
					} else {
						Delay     += RS485_DELAY+1000; // Abort Tx if not completed within this time
					}
				}
				break;
			default:
				ActivateTx();
				break;
			}
			break;
		case C_UART_HWPRO_232 :
			*rTxReg = TxDataPtr[TxDataPos++];
			break;

		}
		if ( Wait && EventMsk ) {
			char Status = OS_WaitEventTimed(EventMsk,Delay);
			TxTaskPtr = NULL;
			TxOk =(Status==EventMsk);
		} else {
			TxOk = true;
		}
		if ( HWProtocol == C_UART_HWPRO_485 ) {
			switch (SWProtocol) {
			case C_UART_SWPRO_ANPRO10:
				break;
			default:
				OS_Delay(2);
                DeactivateTx();
				ProtocolState = pNew_Sync;
				break;
			}
		}
		OS_Unuse(&TxSema);
	}
	return(TxOk);
}


bool SC2410Uart::Receive(U8* MyData, int Size, int TimeOut)
{
	int Cnt = 0;
	bool ReceivedData=true;

	do {
		ReceivedData = !OS_GetMailTimed(&RxBuf,(char*)&MyData[Cnt++],TimeOut);
	}while ( ReceivedData && Cnt < Size );
	return(ReceivedData);
}


void SC2410Uart::ClearRxBuffer(void)
{
	OS_ClearMB(&RxBuf);
}

bool SC2410Uart::HasMore(void)
{
	int RxBytesInBuf = OS_GetMessageCnt(&RxBuf);
	return(bool(RxBytesInBuf));
}
