/****************************************************************************************
/ Com protocol for USART0
/
***************************************************************************************/

#include "iom1280.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "RTOS.h"
#include "hart.h"
#include "externals.h"
#include "version.h"
#include "structs.h"

/*************************************************************************
*   (This is a timer calback)
*  Timout timer USART 0
*
*************************************************************************/
void TimoutUSART0(void) {

	UCSR0B &= ~(__BIT_MASK(UDRIE0));            // transmission end, disable int.
	ClrBit(PORTE, 0x04);                              // TXE0 off
	OS_StopTimer(&TimerUSART0);                    // and stop timer
	GoToSyncUART(0);                                    // go to sync modus for recive
}

/*************************************************************************
*   (This is a timer calback)
*  Timer USART 0 on before TX
*
*************************************************************************/
void TimoutUSART0On(void) {

	UCSR0B |= __BIT_MASK(UDRIE0);                     // start sending by enableing interrupt
	OS_StopTimer(&TimerUSART0On);                    // and stop timer
}

/*************************************************************************
*   (This is a timer calback)
*  Timout timer USART 1
*
*************************************************************************/

/*************************************************************************
*   (This is a timer calback)
*  Timer USART 1 on before TX
*
*************************************************************************/


/*************************************************************************
*   
*  Handle the ANPRO10 protocol
*
*************************************************************************/
unsigned short LastCommand = 0;
char ANPRO10_UnpackPacket(UARTDataType *pUART, unsigned char *Buf) {
	char ch = pUART->Channel;
	pUART->RxCount++;
	pUART->RxSendReply = false;                              // flag for answering set to fault
	pUART->TxFirst     = 11;                                 // Start pos for first TX command

	ANPRO10_PacketHeading *pPH = (ANPRO10_PacketHeading *)Buf;
	char MyPacket = (pPH->rxadr == MyAddress());
	if (MyPacket) {
		Buf += sizeof(ANPRO10_PacketHeading);
		unsigned char *EndPtr =  &Buf[pPH->nob];
		ANPRO10_CommandHeading *pCH;
		char MoreCommands = true;
		do {
			pCH = (ANPRO10_CommandHeading *)Buf;
			Buf += sizeof(ANPRO10_CommandHeading);  // ??
			switch (pCH->CommandNo) {
			case ECMD_NMDWOACK:
			case ECMD_NMDRQACK:
				break;
			default:
				LastCommand = pCH->CommandNo;
				break;
			}
			switch (pCH->CommandNo) {
			case CMD_TXU_COMPRESSED_PACKET:
				//Decompress(Size,Buf,Port);
				break;
			case CMD_REQ_STATUS :                           // Regusest status for target
				BuildStatusData(ch);                         // make package
				break;
			case CMD_GET_STACKSTATUS :                        // Request stck status
				BuildStackStatus(ch, Buf);                     // receive package
				break;
			case CMD_EEPROM_RESET :                        // Reset EEPROM??
				GetResetEEPROM(ch, Buf);                     // receive package
				break;
			case CMD_GOTO_BOOTLOADER :                        // Goto bootlaoder??
				GetGotoBootloader(ch, Buf);                     // receive package
				break;
			case CMD_SND_EEPROM_DATA :                              // Receive EEPROM data
				GetEEPROMData(ch, Buf);                     // receive package
				break;
			case CMD_REQ_EEPROM_DATA :                              // Request to send EEPROM data
				BuildEEPROMData(ch, Buf);                     // receive package
				break;
			case CMD_REQ_INT_DATA :                              // Request external data
				BuildADInt(ch, Buf);                     // receive package
				break;
			case CMD_SND_HART_SETUP :                              // Receive sertup of AN-RSANA
				GetHartSetup(ch, Buf);                     // receive package
				break;
			case CMD_REQ_HART_SETUP :                              // Request for sertup of AN-RSANA
				BuildHartSetup(ch, Buf);                     // receive package
				break;
			case CMD_SND_HART_FILTER :                              // Receive filter of AN-RSANA
				GetHartFilter(ch, Buf);                     // receive package
				break;
			case CMD_REQ_HART_FILTER :                              // Request filter of AN-RSANA
				BuildHartFilter(ch, Buf);                     // receive package
				break;
			case CMD_REQ_HART_DATA :                              // Request ANA data(4-20ma)
				//EHSMark BuildMDataANA(ch, pointer+4) ;                     // receive
				BuildMDataHart(pUART);                     // receive
				break;

			case ECMD_NMDWOACK:
			case ECMD_NMDRQACK:
				MoreCommands = false;
				break;
			default:
				break;

			}
			if (MoreCommands) {
				Buf += pCH->ndb;
			}
		} while (MoreCommands && (Buf < EndPtr));
	}
	if (MyPacket) {
		if (pUART->RxSendReply) {                                   //send answer?
			Uart_BuildTail(pUART);                                       // yes, build tail (and header) and start sending
		}
	}
	return (MyPacket);
}

#define MAX_TIME_BETWEEN_BYTE	50

char ANPRO10_IO_Receive(UARTDataType *pUART) {
	unsigned char *RxBuf = (unsigned char *)pUART->pRxBuffer;
	volatile ANPRO10_PacketHeading *pPH =  (ANPRO10_PacketHeading *)RxBuf;
	char Data;
	OS_GetMail1(&pUART->RxMailBox, &Data);
	char dataAvailable = 1;
	int SyncCnt = 1;
	char PacketOK      = false;
	char Echo          = false;
	do {
		do {
			dataAvailable = !OS_GetMailTimed(&pUART->RxMailBox, &Data, MAX_TIME_BETWEEN_BYTE);
		}  while (dataAvailable && Data != ANPRO10_SYN);
		if (dataAvailable) {
			// A minimum of 2 SYN to accept start
			//Message("First SYN");
			//SyncCnt = 0;
			do {
				dataAvailable = !OS_GetMailTimed(&pUART->RxMailBox, &Data, MAX_TIME_BETWEEN_BYTE);
				if (dataAvailable && (Data == ANPRO10_SYN)) SyncCnt++;
			} while (dataAvailable && (Data == ANPRO10_SYN));
			if (dataAvailable && SyncCnt && (Data == ANPRO10_SOH)) {
				unsigned char *RxPtr = RxBuf;
				for (unsigned i = 0; dataAvailable && i < sizeof(NetHeading); i++) {
					dataAvailable = !OS_GetMailTimed(&pUART->RxMailBox, RxPtr++, MAX_TIME_BETWEEN_BYTE);
				}
				if (dataAvailable) {
					unsigned char HCSum = 0;
					{
						unsigned char *TmpRxPtr = RxBuf;
						for (unsigned i = 0; i < sizeof(ANPRO10_PacketHeading) - 1; i++) {
							HCSum     = crc[HCSum ^ *TmpRxPtr++];
						}

					}
					if (HCSum == pPH->HCRC) {
						//OS_Delay(1000);
						unsigned DataSize = (unsigned)pPH->nob;
						if (DataSize > 3 && DataSize < MAX_ANPRO10_IO_SIZE) {
							int Cnt = 0;
							for (unsigned i = 0; dataAvailable && i < DataSize - sizeof(ANPRO10_PacketHeading); i++) {
								dataAvailable = !OS_GetMailTimed(&pUART->RxMailBox, RxPtr++, MAX_TIME_BETWEEN_BYTE);
								Cnt++;
							}
							if (!dataAvailable) {
								//OS_Delay(100);
							}
							if (dataAvailable) {
								RxPtr = RxBuf;
								volatile unsigned char CSum = 0;

								for (unsigned i = 0; i < DataSize - 2; i++) {
									CSum     = crc[CSum ^ *RxPtr++];
								}
								unsigned char  PacketCheckSum = *((unsigned char *)&RxBuf[DataSize - 2]);
								if (PacketCheckSum == CSum) {
									pUART->SequenceNumber = RxBuf[DataSize - 3];
									//U16 EndCommand = *((U16*)&ARxBuf[DataSize-6]);
									//                  unsigned char EndData = *((unsigned char*)&ARxBuf[DataSize-4]);
									unsigned char EOTByte = *((unsigned char *)&RxBuf[DataSize - 1]);
									if (EOTByte == ANPRO10_EOT) {
										switch (pPH->txtypeid) {
										case DEVICE_TCU :
											if ((pPH->rxadr == MyAddress()) && (pPH->rxtypeid == (UnitID + DEVICE_IO))) {
												pUART->TxAddress = pPH->txadr;
												pUART->TxId      = pPH->txtypeid;
												Echo = !ANPRO10_UnpackPacket(pUART, RxBuf);
												if (!Echo) {
													PacketOK = true;
												}
												break;
											} else {
												//Ignore = true;
											}

											break;
										case DEVICE_ZBHART:
											Echo = true;
											break;
										default:
											// Ignore message
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}while (Echo && dataAvailable);
	if (!PacketOK) {
		pUART->RxFaultCnt++;
	}
	return (PacketOK);
}

/*************************************************************************
*   (This is a task)
*  Usart0 handler
*
*************************************************************************/
void Usart0Handler(void) {

	while (1) {
		ANPRO10_IO_Receive(&UART[0]);
	}
}

/*************************************************************************
*   (This is a task)
*  Usart1 handler
*
*************************************************************************/
void Usart1Handler(void) {
	while (1) {
		while (1) {
			ANPRO10_IO_Receive(&UART[1]);
		}
	}
}



/*************************************************************************
*
* Build send packet header
*
*************************************************************************/
void Uart_BuildHeader(UARTDataType *pUART) {

	pUART->TxLast  = 0;
	char *txBuf = pUART->pTxBuffer;

	txBuf[0] = ANPRO10_SYN;                        /* Sync */
	txBuf[1] = ANPRO10_SYN;                        /* Sync */
	txBuf[2] = ANPRO10_SYN;                        /* Sync */
	txBuf[3] = ANPRO10_SOH;                        /* Start of header */
	txBuf[4] = pUART->TxId;                        /* RXID */
	txBuf[5] = pUART->TxAddress;                   /* Rx address */
	txBuf[6] = DEVICE_IO + UnitID;                 /* Unit ID */
	txBuf[7] = MyAddress();                        /* Tx address */
	txBuf[8] = 0;                                  /* packlen HB, don't know yet */
	txBuf[9] = 0;                                  /* packlen LB, don't know yet */
	txBuf[10] = 0;                                  /* Header checksum, don't know yet */
}

/*************************************************************************
*
* Build  packet tail
*
*************************************************************************/
void Uart_BuildTail(UARTDataType *pUART) {

	Uart_BuildHeader(pUART);                                    // fist build the header
	char *txBuf = pUART->pTxBuffer;
	txBuf[pUART->TxFirst++] = ECMD_NMDWOACK & 0xff;  // End command lb
	txBuf[pUART->TxFirst++] = ECMD_NMDWOACK >> 8;    // End command hb
	txBuf[pUART->TxFirst++] = 0x00;                  // End data

	txBuf[pUART->TxFirst++] = pUART->TxSeqCnt++;   // Sequence counter

	txBuf[8] = pUART->TxFirst - 2;                    // correct length because stx's
	txBuf[9] = (pUART->TxFirst - 2) >> 8;             // packet len high

	txBuf[10] = CalcDSTxChecksum(pUART, 6);         // Get header checksum

	txBuf[pUART->TxFirst] = CalcDSTxChecksum(pUART, pUART->TxFirst-4); // Get checksum
	pUART->TxFirst++;                                        // OBS!! must be inc here due to ANSI standard !!!!

	txBuf[pUART->TxFirst++] = ANPRO10_EOT;            // End of transmission
	pUART->TxCount          = pUART->TxFirst;         //bytes to send
	pUART->TxLast 			= 0;                                     // reset cunter
	// Turn on TXE for channel
	OS_RetriggerTimer(&TimerUSART0);                     // and start timeout TX timer

	SetBit(PORTE, 0x04);                                // TXE0 on
	OS_RetriggerTimer(&TimerUSART0On);                   // and start timer for on before TX
}

/*************************************************************************
*
* Build datablock for card status
*
*************************************************************************/

void BuildStatusData(char ch) {

	short ntna;
	UART[ch].RxSendReply = true;                               // flag for answering

	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_STATUS & 0xff;
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_STATUS >> 8;
	ntna = UART[ch].TxFirst;                                    /* remember index */
	UART[ch].TxFirst += 2;                                      // two byte length
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = ch;               // channel
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = DEVICE_IO + UnitID;   // Product ID
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = MyAddress();           // unit adddress
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = PROG_VERSION;       // software version */
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = COMP_VERSION;        // cpmpability version
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = STORE_VERSION;        // cpmpability version
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = (RXSIZE_UART & 0xff);         // rx buffer size
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((RXSIZE_UART >> 8) & 0xff); // rx buffer size
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = (TXSIZE_UART & 0xff);         // tx buffer size
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((TXSIZE_UART >> 8) & 0xff);  // tx buffer size
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = RestartStatus;                  // restart flag
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = PROGTYPE_APP;                // Application program

	UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2) & 0xff;      // length of data block lb
	UART[ch].pTxBuffer[ntna + 1] = ((UART[ch].TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb

	RestartStatus = 0;                                                       // set reset stat to 0 = read
}

/*************************************************************************
*
* Build EEPROM data package
*
*************************************************************************/
void BuildEEPROMData(char ch, unsigned char *pointer) {

	short ntna;
	char channel;
	UART[ch].RxSendReply = true;                               // flag for answering

	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_EEPROM_DATA & 0xff;
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_EEPROM_DATA >> 8;
	ntna = UART[ch].TxFirst;                                    /* remember index */
	UART[ch].TxFirst += 2;                                      // two byte length

	channel = pointer[0];
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = channel; //channel

	ReadEEPROMBuffer((channel * sizeof(float) * 2), sizeof(float), (char *)&UART[ch].pTxBuffer[UART[ch].TxFirst]);
	UART[ch].TxFirst += sizeof(float);
	ReadEEPROMBuffer((channel * sizeof(float) * 2) + sizeof(float), sizeof(float), (char *)&UART[ch].pTxBuffer[UART[ch].TxFirst]);
	UART[ch].TxFirst += sizeof(float);

	UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2) & 0xff;      // length of data block lb
	UART[ch].pTxBuffer[ntna + 1] = ((UART[ch].TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb
}


/*************************************************************************
*
* Build datablock for Internal AD
*
*************************************************************************/
void BuildADInt(char ch, unsigned char *pointer) {

	short ntna, i;
	UART[ch].RxSendReply = true;                               // flag for answering

	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_INT_DATA & 0xff;
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_INT_DATA >> 8;
	ntna = UART[ch].TxFirst;                                    /* remember index */
	UART[ch].TxFirst += 2;                                      // two byte length

	for (i = 0; i < 3; i++) {
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = ADInt.Result[i];
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = ADInt.Result[i] >> 8;   // ADresult
	}

	UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2) & 0xff;      // length of data block lb
	UART[ch].pTxBuffer[ntna + 1] = ((UART[ch].TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb

}


/*************************************************************************
*
* Build setup data package for AN-ZBHART
*
*************************************************************************/
void BuildHartSetup(char ch, unsigned char *pointer) {

	short ntna;
	UART[ch].RxSendReply = true;                               // flag for answering

	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_HART_SETUP & 0xff;
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_HART_SETUP >> 8;
	ntna = UART[ch].TxFirst;                                    /* remember index */
	UART[ch].TxFirst += 2;                                      // two byte length

	UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.Hart.PortUsed & 0xff;
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = (TData.Hart.PortUsed >> 8) & 0xff;

	UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2) & 0xff;      // length of data block lb
	UART[ch].pTxBuffer[ntna + 1] = ((UART[ch].TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb
}

/*************************************************************************
*
* Build filter data package for AN-ZBHART
*
*************************************************************************/
void BuildHartFilter(char ch, unsigned char *pointer) {

	char port;
	short ntna;
	UART[ch].RxSendReply = true;                               // flag for answering

	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_HART_FILTER & 0xff;
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_HART_FILTER >> 8;
	ntna = UART[ch].TxFirst;                                    /* remember index */
	UART[ch].TxFirst += 2;                                      // two byte length

	for (port = 0; port < 12; port++) {
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.Hart.Filter[port];
	}

	UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2) & 0xff;      // length of data block lb
	UART[ch].pTxBuffer[ntna + 1] = ((UART[ch].TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb
}

/*************************************************************************
*
* Build datablock for Hart (Hart)
*
*************************************************************************/
void BuildMDataHart(UARTDataType *pUART) {
	short Index        = 11; // // Add data after the heading, Heading size is 11
	char *Buf          = pUART->pTxBuffer;
	pUART->RxSendReply = true;                               // flag for answering
	Buf[Index++] = CMD_REP_HART_MDATA & 0xff;
	Buf[Index++] = CMD_REP_HART_MDATA >> 8;
	short ntna = Index;                                  /* remember index */
	Index  += 2;                                      // two byte length

	Buf[Index++] = (RestartStatus << 4);    // Add restart status
	// Hart PV
	for (short i = 0; i < 12; i++) {
		*((unsigned short *)&Buf[Index]) = TData.Hart.FailCnt[i][0];   // Hart 1st
		Index += sizeof(unsigned short);

		*((unsigned short *)&Buf[Index]) = TData.Hart.FailCnt[i][1];   // Hart 1st
		Index += sizeof(unsigned short);
		hart_channel_lock(&_hart_channels[i]);
		*((float *)&Buf[Index]) = TData.Hart.Distance[i];   // Hart 1st
		Index += sizeof(float);
		*((float *)&Buf[Index]) = TData.Hart.Level[i];   // Hart 2nd
		Index += sizeof(float);
		*((float *)&Buf[Index]) = TData.Hart.ADCurrent[i];   // Measured current
		Index += sizeof(float);
		hart_channel_unlock(&_hart_channels[i]);
	}
	Buf[ntna] = (Index - ntna - 2) & 0xff;      // length of data block lb
	Buf[ntna + 1] = ((Index - ntna - 2) >> 8) & 0xff; // length of data block hb
	pUART->TxFirst = Index; // Add data after the heading


}


/*************************************************************************
*
* Build datablock for Stack status
*
*************************************************************************/
void BuildStackStatus(char ch, unsigned char *pointer) {

	short ntna, stack;
	UART[ch].RxSendReply = true;                               // flag for answering

	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_STACKSTATUS & 0xff;
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_STACKSTATUS >> 8;
	ntna = UART[ch].TxFirst;                                    /* remember index */
	UART[ch].TxFirst += 2;                                      // two byte length

	stack = OS_GetStackSpace(&TCB_USART0);                            // USART 0
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff);
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack >> 8) & 0xff);
	/*
	stack = OS_GetStackSpace(&TCB_USART1);                            // USART 1
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
	*/
	stack = OS_GetStackSpace(&TCB_WATCHDOG);                            // watchdog
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff);
	UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack >> 8) & 0xff);
	switch (UnitID) {
	case AN_ZB485 :
		/*
		stack = OS_GetStackSpace(&TCB_RS485Ctl);                            // RS485 Control
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
		stack = OS_GetStackSpace(&TCB_RS485Rec);                            // RS485 receive
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
		*/
		break;
	case AN_ZBANA :
		/*
		stack = OS_GetStackSpace(&TCB_AD7715);                            // AD handling
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0 ;
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0 ;
		*/
		break;
	case AN_ZBHART :
		/*
		stack = OS_GetStackSpace(&TCB_AD7715);                            // AD handling
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0 ;
		UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0 ;
		*/
		break;
	}

	UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2) & 0xff;      // length of data block lb
	UART[ch].pTxBuffer[ntna + 1] = ((UART[ch].TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb

}

//////////////////////////////////////////////////////////////////////////////
// Receiving data to IO module here
/////////////////////////////////////////////////////////////////////////////

/*************************************************************************
*
* Receive Command to Reset the EEPROM
*
*************************************************************************/
void GetResetEEPROM(char ch, unsigned char *pointer) {

	EEPROMReset();
}


/*************************************************************************
*
* Receive Command to go to the bootloader program
*
*************************************************************************/
void GetGotoBootloader(char ch, unsigned char *pointer) {

//    void (*BootApp)(void) = (void(*)())0xF000;

	while ((EECR & 1 << EEPE) != 0) //chech if EEPROM is ready
	;
	EEARL = (0x0fff & 0xff);
	EEARH = (0x0fff >> 8);
	EEDR = 0xff;
	EECR |= (1 << EEMPE);
	EECR |= (1 << EEPE);
	while (EECR & (1 << EEPE))
	;

	WDTCSR = 0x18;               //Start watchdog to genetate restart
	WDTCSR = 0x08;               //Start watchdog to genetate restart
}

/*************************************************************************
*
* Receive EEPROM data
*
*************************************************************************/
void GetEEPROMData(char ch, unsigned char *pointer) {

	char channel;
	int t0;

	channel = pointer[0];
	switch (UnitID) {
	case AN_ZBANA:
		break;
	case AN_ZBHART:
		if (channel >= 0x80) {
			*((float *)&TData.Hart.Offset[channel & 0x0f]) = *((float *)&pointer[1]);  //offset
			*((float *)&TData.Hart.Gain[channel & 0x0f]) = *((float *)&pointer[5]);  //gain
		}
		break;
	case AN_ZB485:
		break;
	}
	WriteEEPROMBuffer((channel * sizeof(float) * 2), sizeof(float), (char *)&pointer[1]);
	t0 = OS_GetTime();
	do {
		OS_Delay(1);
	}while ((OS_GetTime() - t0) < (sizeof(float) * 9) && !EEPWriteOK);  //8.5 ms programming time
	WriteEEPROMBuffer((channel * sizeof(float) * 2) + sizeof(float), sizeof(float), (char *)&pointer[5]);
	t0 = OS_GetTime();
	do {
		OS_Delay(1);
	}while ((OS_GetTime() - t0) < (sizeof(float) * 9) && !EEPWriteOK);
}



/*************************************************************************
*
* Receive AN-ZBHART setup
*
*************************************************************************/
void GetHartSetup(char ch, unsigned char *pointer) {

	TData.Hart.PortUsed = pointer[0] + (pointer[1] << 8);  //Get the setup
	WriteEEPROMByte(EEPROM_PORTSETUP, pointer[0]);   // store in EEPROM
	WriteEEPROMByte(EEPROM_PORTSETUP + 1, pointer[1]);
#if 0  // blocked by hkim for ZBHART
	SetAnaPort();                           // set the port on or off
#endif
}

/*************************************************************************
*
* Receive AN-ZBHART filter
*
*************************************************************************/
void GetHartFilter(char ch, unsigned char *pointer) {
	char port;

	for (port = 0; port < 12; port++) {
		TData.Hart.Filter[port] = *pointer++;  //Get the filter
	}
}

/*************************************************************************
*
* Calculate rx packet checksum (header and package) using Dallas Semiconductor one-wire CRC
*
*************************************************************************/
short CalcDSRxChecksum(char ch, unsigned short len) {

	unsigned short  cnt;
	unsigned char   csum;

	csum = 0;
	for (cnt = 0; cnt < len; cnt++) {
		csum = crc[csum ^ UART[ch].pRxBuffer[cnt]];
	}
	if (csum == UART[ch].pRxBuffer[len]) {
		return true;
	} else {
		return false;
	}
}

/*************************************************************************
*
* Goes to sync mode
*
*************************************************************************/
__monitor void GoToSyncUART(char ch) {

}

/*************************************************************************
*
* Calculate tx checksum (header and package) using Dallas Semiconductor one-wire CRC
*
*************************************************************************/
char CalcDSTxChecksum(UARTDataType *pUART, unsigned short Length) {
	unsigned char csum = 0;
	for (short cnt = 0; cnt < Length; cnt++) {
		csum = crc[csum ^ pUART->pTxBuffer[cnt+4]];
	}
	return csum;
}


