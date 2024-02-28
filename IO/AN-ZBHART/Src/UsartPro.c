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

__no_init int RestartCnt             @0x21FD;
__no_init char BootloaderRevision    @0x21FF;

char hasStartedUARTTask = 0;

//extern __no_init TargetData  TData;                    
/*************************************************************************
*   
*  Handle the ANPRO10 protocol
* 
*  Returns 1 if a reply has been sent
*
*************************************************************************/
static unsigned LastCommand = 0;
char ANPRO10_UnpackPacket(void) {
    char *Buf = My485UART.pRxBuffer;
    const ANPRO10_PacketHeading *pPH = (ANPRO10_PacketHeading *)Buf;
    My485UART.RxCount++;
    My485UART.TxAddress   = pPH->txadr;
    My485UART.TxId        = pPH->txtypeid;
    My485UART.RxSendReply = false;                              // flag for answering set to fault
    My485UART.TxFirst     = 11;                                 // Start pos for first TX command

    Buf += sizeof(ANPRO10_PacketHeading);
    const char *EndPtr =  (char*)&Buf[pPH->nob];
    // Sanity check
    if ( pPH->nob >= RXSIZE_UART-5 ) {
        return 0;
    }
    ANPRO10_CommandHeading *pCH;
    char MoreCommands = true;
    do {
        pCH = (ANPRO10_CommandHeading *)Buf;
        Buf += sizeof(ANPRO10_CommandHeading);  // ??
        switch ( pCH->CommandNo ) {
        case ECMD_NMDWOACK:
        case ECMD_NMDRQACK:
            break;
        default:
            LastCommand = pCH->CommandNo;
            break;
        }
        switch ( pCH->CommandNo ) {
        case CMD_REQ_STATUS :                           // Regusest status for target
            BuildStatusData();                          // make package
            break;
        case CMD_GET_STACKSTATUS :                      // Request stck status
            BuildStackStatus( Buf);
            break;
        case CMD_EEPROM_RESET :                         // Reset EEPROM??
            GetResetEEPROM();
            break;
        case CMD_GOTO_BOOTLOADER :                      // Goto bootlaoder??
            GetGotoBootloader(Buf);
            break;
        case CMD_SND_EEPROM_DATA :                      // Receive EEPROM data
            GetEEPROMData(Buf);
            break;
        case CMD_REQ_EEPROM_DATA :                      // Request to send EEPROM data
            BuildEEPROMData( Buf);
            break;
        case CMD_REQ_INT_DATA :                         // Request external data
            BuildADInt( Buf);
            break;
        case CMD_SND_HART_SETUP :                       // Receive sertup of AN-RSANA
            GetHartSetup(Buf, pCH->ndb);
            break;
        case CMD_REQ_HART_SETUP :                       // Request for sertup of AN-RSANA
            BuildHartSetup( Buf);
            break;
        case CMD_SND_HART_FILTER :                      // Receive filter of AN-RSANA
            GetHartFilter(Buf);
            break;
        case CMD_REQ_HART_FILTER :                      // Request filter of AN-RSANA
            BuildHartFilter( Buf);
            break;
        case CMD_REQ_HART_DATA :                        // Request ANA data(4-20ma)
            BuildMDataHart();
            break;

        case ECMD_NMDWOACK:
        case ECMD_NMDRQACK:
            MoreCommands = false;
            break;
        default:
            break;

        }
        if ( MoreCommands ) {
            Buf += pCH->ndb;
        }
    } while ( MoreCommands && (Buf < EndPtr) );
    if ( My485UART.RxSendReply ) {                                   //send answer?
        My485UART_BuildTail();                                       // yes, build tail (and header) and start sending
    }
    return (My485UART.RxSendReply);
}

#define MAX_TIME_BETWEEN_BYTE	15

void ANPRO10_IO_Receive(void) {
    unsigned char *RxBuf = (unsigned char *)My485UART.pRxBuffer;
    const ANPRO10_PacketHeading *pPH =  (ANPRO10_PacketHeading *)RxBuf;
    char Data;
    char dataAvailable = 1;
    int  SyncCnt       = 1;     // Initialize to 1 as 1 must have been found when exiting the while loop
    char PacketOK      = false; // Assume the worse at the beginning
    // Look for ANPRO10_SYN, ignore the rest
    do {
        OS_GetMail1(&My485UART.RxMailBox, &Data);
    }while ( Data != ANPRO10_SYN );
    // We know we have a ANPRO10_SYN
    // A minimum of 2 SYN to accept start
    //Message("First SYN");
    //SyncCnt = 0;
    do {
        dataAvailable = !OS_GetMailTimed(&My485UART.RxMailBox, &Data, MAX_TIME_BETWEEN_BYTE);
        if ( dataAvailable && (Data == ANPRO10_SYN) ) SyncCnt++;
    } while ( dataAvailable && (Data == ANPRO10_SYN) );
    if ( dataAvailable && SyncCnt && (Data == ANPRO10_SOH) ) {
        unsigned char *RxPtr = RxBuf;
        for ( unsigned i = 0; dataAvailable && i < sizeof(NetHeading); i++ ) {
            dataAvailable = !OS_GetMailTimed(&My485UART.RxMailBox, RxPtr++, MAX_TIME_BETWEEN_BYTE);
        }
        if ( dataAvailable ) {
            unsigned char HCSum = 0;
            {
                unsigned char *TmpRxPtr = RxBuf;
                for ( unsigned i = 0; i < sizeof(ANPRO10_PacketHeading) - 1; i++ ) {
                    HCSum     = crc[HCSum ^ *TmpRxPtr++];
                }

            }
            if ( HCSum == pPH->HCRC ) {
                unsigned DataSize = (unsigned)pPH->nob;
                // Before checked against MAX_ANPRO10_IO_SIZE which is not related to the buffer size for AN-ZBHART
                if ( DataSize > 3 && DataSize < RXSIZE_UART ) { 
                    for ( unsigned i = 0; dataAvailable && i < DataSize - sizeof(ANPRO10_PacketHeading); i++ ) {
                        dataAvailable = !OS_GetMailTimed(&My485UART.RxMailBox, RxPtr++, MAX_TIME_BETWEEN_BYTE);
                    }
                    if ( dataAvailable ) {
                        RxPtr = RxBuf;
                        volatile unsigned char CSum = 0;

                        for ( unsigned i = 0; i < DataSize - 2; i++ ) {
                            CSum     = crc[CSum ^ *RxPtr++];
                        }
                        unsigned char  PacketCheckSum = *((unsigned char *)&RxBuf[DataSize - 2]);
                        if ( PacketCheckSum == CSum ) {
                            My485UART.SequenceNumber = RxBuf[DataSize - 3];
                            // U16 EndCommand = *((U16*)&ARxBuf[DataSize-6]);
                            // unsigned char EndData = *((unsigned char*)&ARxBuf[DataSize-4]);
                            unsigned char EOTByte = *((unsigned char *)&RxBuf[DataSize - 1]);
                            if ( EOTByte == ANPRO10_EOT ) {
                                switch ( pPH->txtypeid ) {
                                case DEVICE_TCU :
                                    if ( (pPH->rxadr == MyAddress()) && (pPH->rxtypeid == (UnitID + DEVICE_IO)) ) {
                                        ANPRO10_UnpackPacket();
                                        PacketOK = true; // Packet accepted so signal OK!
                                    } else {
                                        //Ignore = true;
                                    }
                                    break;
                                case DEVICE_ZBHART:
                                    //Echo = true;
                                    break;
                                default:
                                    // Ignore message
                                    break;
                                }
                            }
                        }
                    } else {
                        OS_Delay(0);
                    }
                }
            }
        }
    }
    if ( !PacketOK ) {
        My485UART.RxFaultCnt++;
    }
}

/*************************************************************************
*   (This is a task)
*  Usart0 handler
*
*************************************************************************/
void Usart0Handler(void) {
    hasStartedUARTTask = 1;
    UCSR0B  = 1 << RXCIE0 | 1 << RXEN0 | 1 << TXEN0;  //0x98;                                       /* tx/ rx enable, int udre/rxon */
    while ( 1 ) {

        ANPRO10_IO_Receive();
    }
}




/*************************************************************************
*
* Build send packet header
*
*************************************************************************/
void My485UART_BuildHeader(void) {

    My485UART.TxLast  = 0;
    char *txBuf = My485UART.pTxBuffer;

    txBuf[ 0] = ANPRO10_SYN;                        /* Sync */
    txBuf[ 1] = ANPRO10_SYN;                        /* Sync */
    txBuf[ 2] = ANPRO10_SYN;                        /* Sync */
    txBuf[ 3] = ANPRO10_SOH;                        /* Start of header */
    txBuf[ 4] = My485UART.TxId;                        /* RXID */
    txBuf[ 5] = My485UART.TxAddress;                   /* Rx address */
    txBuf[ 6] = DEVICE_IO + UnitID;                 /* Unit ID */
    txBuf[ 7] = MyAddress();                        /* Tx address */
    txBuf[ 8] = 0;                                  /* packlen HB, don't know yet */
    txBuf[ 9] = 0;                                  /* packlen LB, don't know yet */
    txBuf[10] = 0;                                  /* Header checksum, don't know yet */
}

/*************************************************************************
*
* Build  packet tail
*
*************************************************************************/
void My485UART_BuildTail(void) {

    My485UART_BuildHeader();                      // fist build the header
    char *txBuf = My485UART.pTxBuffer;
    txBuf[My485UART.TxFirst++] = ECMD_NMDWOACK & 0xff;    // End command lb
    txBuf[My485UART.TxFirst++] = ECMD_NMDWOACK >> 8;      // End command hb
    txBuf[My485UART.TxFirst++] = 0x00;                    // End data

    txBuf[My485UART.TxFirst++] = My485UART.TxSeqCnt++;  // Sequence counter

    txBuf[ 8] = My485UART.TxFirst - 2;                     // correct length because stx's
    txBuf[ 9] = (My485UART.TxFirst - 2) >> 8;              // packet len high
    txBuf[10] = CalcDSTxChecksum( 6);                       // Get header checksum
    unsigned PacketStart = My485UART.TxFirst;
    txBuf[My485UART.TxFirst]      = CalcDSTxChecksum(PacketStart - 4); // Get checksum
    My485UART.TxFirst++;                                  // OBS!! must be inc here due to ANSI standard !!!!

    txBuf[My485UART.TxFirst++]    = ANPRO10_EOT;          // End of transmission
 //   txBuf[My485UART.TxFirst++]    = ANPRO10_EOT;          // End of transmission
    My485UART.TxCount             = My485UART.TxFirst;  //bytes to send
    My485UART.TxLast 			    = 0;                    // reset cunter
    // Turn on TXE for channel
    My_SetBit(PORTE, 0x04);                                 // TXE0 on
    OS_Delay(2);                                            // Ensure some settling time
    UCSR0B |= __BIT_MASK(UDRIE0);                           // start sending by enableing interrupt
    if (!OS_WaitEventTimed(UART0_EVENT_TX_COMPLETE, 1000)) {
        PORTE &= ~0x04 ;                                    // TXE0 off
    }

}

/*************************************************************************
*
* Build datablock for card status
*
*************************************************************************/

void BuildStatusData(void) {
    if ( My485UART.TxFirst < TXSIZE_UART -20 ) {
        short ntna;
        My485UART.RxSendReply = true;                               // flag for answering

        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_STATUS & 0xff;
        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_STATUS >> 8;
        ntna = My485UART.TxFirst;                                    /* remember index */
        My485UART.TxFirst += 2;                                                       // two byte length
        My485UART.pTxBuffer[My485UART.TxFirst++] = 0;                               // channel fixed to 0
        My485UART.pTxBuffer[My485UART.TxFirst++] = DEVICE_IO + UnitID;              // Product ID
        My485UART.pTxBuffer[My485UART.TxFirst++] = MyAddress();                     // unit adddress
        My485UART.pTxBuffer[My485UART.TxFirst++] = PROG_VERSION;                    // software version */
        My485UART.pTxBuffer[My485UART.TxFirst++] = COMP_VERSION;                    // cpmpability version
        My485UART.pTxBuffer[My485UART.TxFirst++] = STORE_VERSION;                   // cpmpability version
        My485UART.pTxBuffer[My485UART.TxFirst++] = (RXSIZE_UART & 0xff);            // rx buffer size
        My485UART.pTxBuffer[My485UART.TxFirst++] = ((RXSIZE_UART >> 8) & 0xff);     // rx buffer size
        My485UART.pTxBuffer[My485UART.TxFirst++] = (TXSIZE_UART & 0xff);            // tx buffer size
        My485UART.pTxBuffer[My485UART.TxFirst++] = ((TXSIZE_UART >> 8) & 0xff);     // tx buffer size
        My485UART.pTxBuffer[My485UART.TxFirst++] = RestartStatus;                   // restart flag
        My485UART.pTxBuffer[My485UART.TxFirst++] = PROGTYPE_APP;                    // Application program
        My485UART.pTxBuffer[My485UART.TxFirst++] = RestartCnt & 0xff;               // Unit restart count
        My485UART.pTxBuffer[My485UART.TxFirst++] = (RestartCnt >> 8 ) & 0xff;       // Unit restart count
        My485UART.pTxBuffer[My485UART.TxFirst++] = BootloaderRevision;              // Bootloader version


        My485UART.pTxBuffer[ntna] =   (My485UART.TxFirst - ntna - 2) & 0xff;      // length of data block lb
        My485UART.pTxBuffer[ntna + 1] = ((My485UART.TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb

        RestartStatus = 0;                                                       // set reset stat to 0 = read
    }
}

/*************************************************************************
*
* Build EEPROM data package
*
*************************************************************************/
void BuildEEPROMData(char *pointer) {
    if ( My485UART.TxFirst < TXSIZE_UART - 20 ) {
        short ntna;
        char channel;
        My485UART.RxSendReply = true;                               // flag for answering

        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_EEPROM_DATA & 0xff;
        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_EEPROM_DATA >> 8;
        ntna = My485UART.TxFirst;                                    /* remember index */
        My485UART.TxFirst += 2;                                      // two byte length

        channel = pointer[0];
        My485UART.pTxBuffer[My485UART.TxFirst++] = channel; //channel

        ReadEEPROMBuffer((channel * sizeof(float) * 2), sizeof(float), (char *)&My485UART.pTxBuffer[My485UART.TxFirst]);
        My485UART.TxFirst += sizeof(float);
        ReadEEPROMBuffer((channel * sizeof(float) * 2) + sizeof(float), sizeof(float), (char *)&My485UART.pTxBuffer[My485UART.TxFirst]);
        My485UART.TxFirst += sizeof(float);

        My485UART.pTxBuffer[ntna] = (My485UART.TxFirst - ntna - 2) & 0xff;      // length of data block lb
        My485UART.pTxBuffer[ntna + 1] = ((My485UART.TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb
    }
}


/*************************************************************************
*
* Build datablock for Internal AD
*
*************************************************************************/
void BuildADInt(char *pointer) {
    if ( My485UART.TxFirst < TXSIZE_UART - 20 ) {
        short ntna, i;
        My485UART.RxSendReply = true;                               // flag for answering

        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_INT_DATA & 0xff;
        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_INT_DATA >> 8;
        ntna = My485UART.TxFirst;                                    /* remember index */
        My485UART.TxFirst += 2;                                      // two byte length

        for ( i = 0; i < 3; i++ ) {
            My485UART.pTxBuffer[My485UART.TxFirst++] = ADInt.Result[i];
            My485UART.pTxBuffer[My485UART.TxFirst++] = ADInt.Result[i] >> 8;   // ADresult
        }

        My485UART.pTxBuffer[ntna] = (My485UART.TxFirst - ntna - 2) & 0xff;      // length of data block lb
        My485UART.pTxBuffer[ntna + 1] = ((My485UART.TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb
    }

}


/*************************************************************************
*
* Build setup data package for AN-ZBHART
*
*************************************************************************/
void BuildHartSetup( char *pointer) {
    if ( My485UART.TxFirst < TXSIZE_UART - 20) {
        short ntna;
        My485UART.RxSendReply = true;                               // flag for answering

        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_HART_SETUP & 0xff;
        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_HART_SETUP >> 8;
        ntna = My485UART.TxFirst;                                    /* remember index */
        My485UART.TxFirst += 2;                                      // two byte length

        My485UART.pTxBuffer[My485UART.TxFirst++] = TData.Hart.PortUsed & 0xff;
        My485UART.pTxBuffer[My485UART.TxFirst++] = (TData.Hart.PortUsed >> 8) & 0xff;

        My485UART.pTxBuffer[ntna] =  (My485UART.TxFirst - ntna - 2) & 0xff;      // length of data block lb
        My485UART.pTxBuffer[ntna + 1] = ((My485UART.TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb
    }
}

/*************************************************************************
*
* Build filter data package for AN-ZBHART
*
*************************************************************************/
void BuildHartFilter( char *pointer) {
    if ( My485UART.TxFirst < TXSIZE_UART - 20 ) {
        char port;
        short ntna;
        My485UART.RxSendReply = true;                               // flag for answering

        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_HART_FILTER & 0xff;
        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_HART_FILTER >> 8;
        ntna = My485UART.TxFirst;                                    /* remember index */
        My485UART.TxFirst += 2;                                      // two byte length

        for ( port = 0; port < 12; port++ ) {
            My485UART.pTxBuffer[My485UART.TxFirst++] = TData.Hart.Filter[port];
        }

        My485UART.pTxBuffer[ntna] =  (My485UART.TxFirst - ntna - 2) & 0xff;      // length of data block lb
        My485UART.pTxBuffer[ntna + 1] = ((My485UART.TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb
    }
}

/*************************************************************************
*
* Build datablock for Hart (Hart)
*
*************************************************************************/
void BuildMDataHart(void) {
    if ( My485UART.TxFirst < TXSIZE_UART - 20 ) {
        short Index        = 11; // // Add data after the heading, Heading size is 11
        char *Buf          = My485UART.pTxBuffer;
        My485UART.RxSendReply = true;                               // flag for answering
        Buf[Index++] = CMD_REP_HART_MDATA & 0xff;
        Buf[Index++] = CMD_REP_HART_MDATA >> 8;
        short ntna = Index;                                  /* remember index */
        Index  += 2;                                      // two byte length

        Buf[Index++] = (RestartStatus << 4);    // Add restart status
        // Hart PV
        for ( short i = 0; i < 12; i++ ) {
            *((unsigned short *)&Buf[Index]) = TData.Hart.FailCnt[i][0];   // Hart 1st
            Index += sizeof(unsigned short);
            *((unsigned short *)&Buf[Index]) = TData.Hart.FailCnt[i][1];   // Hart 2nd
            Index += sizeof(unsigned short);
            //hart_channel_lock(&_hart_channels[i]);
            *((float *)&Buf[Index]) = TData.Hart.Distance[i];       // Hart 1st
            Index += sizeof(float);
            *((float *)&Buf[Index]) = TData.Hart.Level[i];          // Hart 2nd
            Index += sizeof(float);
            *((float *)&Buf[Index]) = TData.Hart.ADCurrent[i];      //*TData.Hart.Gain[i] - TData.Hart.Offset[i];   // Measured current via onboard ADC
            Index += sizeof(float);
            //*((float *)&Buf[Index]) = TData.Hart.HartCurrent[i];    // mA current from the device
            //Index += sizeof(float);
            //hart_channel_unlock(&_hart_channels[i]);
        }
        Buf[ntna] = (Index - ntna - 2) & 0xff;      // length of data block lb
        Buf[ntna + 1] = ((Index - ntna - 2) >> 8) & 0xff; // length of data block hb
        My485UART.TxFirst = Index; // Add data after the heading
    }


}


/*************************************************************************
*
* Build datablock for Stack status
*
*************************************************************************/
void BuildStackStatus( char *pointer) {
    if ( My485UART.TxFirst < TXSIZE_UART - 20 ) {
        short ntna, stack;
        My485UART.RxSendReply = true;                               // flag for answering

        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_STACKSTATUS & 0xff;
        My485UART.pTxBuffer[My485UART.TxFirst++] = CMD_REP_STACKSTATUS >> 8;
        ntna = My485UART.TxFirst;                                    /* remember index */
        My485UART.TxFirst += 2;                                      // two byte length

        stack = OS_GetStackSpace(&TCB_USART0);                            // USART 0
        My485UART.pTxBuffer[My485UART.TxFirst++] = (stack & 0xff);
        My485UART.pTxBuffer[My485UART.TxFirst++] = ((stack >> 8) & 0xff);

        stack = OS_GetStackSpace(&TCB_WATCHDOG);                            // watchdog
        My485UART.pTxBuffer[My485UART.TxFirst++] = (stack & 0xff);
        My485UART.pTxBuffer[My485UART.TxFirst++] = ((stack >> 8) & 0xff);
        switch ( UnitID ) {
        case AN_ZB485 :
        case AN_ZBANA :
            break;
        case AN_ZBHART :
            stack = OS_GetStackSpace(&TCB_AD7715);                            // AD handling
            My485UART.pTxBuffer[My485UART.TxFirst++] = (stack & 0xff);
            My485UART.pTxBuffer[My485UART.TxFirst++] = ((stack >> 8) & 0xff);
            My485UART.pTxBuffer[My485UART.TxFirst++] = 0;
            My485UART.pTxBuffer[My485UART.TxFirst++] = 0;
            break;
        }

        My485UART.pTxBuffer[ntna] = (My485UART.TxFirst - ntna - 2) & 0xff;      // length of data block lb
        My485UART.pTxBuffer[ntna + 1] = ((My485UART.TxFirst - ntna - 2) >> 8) & 0xff; // length of data block hb
    }

}

//////////////////////////////////////////////////////////////////////////////
// Receiving data to IO module here
/////////////////////////////////////////////////////////////////////////////

/*************************************************************************
*
* Receive Command to Reset the EEPROM
*
*************************************************************************/
void GetResetEEPROM(void) {

    EEPROMReset();
}


/*************************************************************************
*
* Receive Command to go to the bootloader program
*
*************************************************************************/
extern volatile char RestartCmd;
void GetGotoBootloader( char *pointer) {

    void (*BootApp)(void) = (void(*)())0xF000;
    while ( (EECR & 1 << EEPE) != 0 ) //chech if EEPROM is ready
    ;
    EEARL = (0x0fff & 0xff);
    EEARH = (0x0fff >> 8);
    EEDR = 0x00;
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
    while ( EECR & (1 << EEPE) );
    //RestartCmd = 1;
    BootApp();
    //OS_Error(ZB_REBOOT);
}

/*************************************************************************
*
* Receive EEPROM data
*
*************************************************************************/
void GetEEPROMData( char *pointer) {

    char channel;
    OS_U32 t0;

    channel = pointer[0];
    switch ( UnitID ) {
    case AN_ZBANA:
        break;
    case AN_ZBHART:
        if ( channel >= 0x80 ) {
            *((float *)&TData.Hart.Offset[channel & 0x0f]) = *((float *)&pointer[1]);  //offset
            *((float *)&TData.Hart.Gain[channel   & 0x0f]) = *((float *)&pointer[5]);  //gain
        }
        break;
    case AN_ZB485:
        break;
    }
    WriteEEPROMBuffer((channel * sizeof(float) * 2), sizeof(float), (char *)&pointer[1]);
    t0 = OS_GetTime();
    do {
        OS_Delay(1);
    }while ( (OS_GetTime() - t0) < (sizeof(float) * 9) && !EEPWriteOK );  //8.5 ms programming time
    WriteEEPROMBuffer((channel * sizeof(float) * 2) + sizeof(float), sizeof(float), (char *)&pointer[5]);
    t0 = OS_GetTime();
    do {
        OS_Delay(1);
    }while ( (OS_GetTime() - t0) < (sizeof(float) * 9) && !EEPWriteOK );
}



/*************************************************************************
*
* Receive AN-ZBHART setup
*
*************************************************************************/
void GetHartSetup( char *pointer, unsigned Size) {
    switch ( Size ) {
    case 4:
        TData.Hart.PortUsed     = pointer[0] + (pointer[1] << 8);  //Get the setup
        TData.Hart.HartSensor   = pointer[2] + (pointer[3] << 8);  //Get the setup
        WriteEEPROMByte(EEPROM_PORTSETUP, pointer[0]);     // store in EEPROM
        WriteEEPROMByte(EEPROM_HART_SNS , pointer[2]);
        for ( char i = 0; i < 12; i++ ) {
            TData.Hart.FailCnt[i][0] = 0;
            TData.Hart.FailCnt[i][1] = 0;
        }
        break;
    case 6:
        {
            TData.Hart.PortUsed     = pointer[0] + (pointer[1] << 8);  //Get the setup
            TData.Hart.HartSensor   = pointer[2] + (pointer[3] << 8);  //Get the setup
            unsigned AdditionalCmd  = pointer[4] + (pointer[5] << 8);  //Get the extra command
            if ( AdditionalCmd & 1 ) {
                WriteEEPROMByte(EEPROM_PORTSETUP, pointer[0]);     // store in EEPROM
                WriteEEPROMByte(EEPROM_HART_SNS , pointer[2]);
                RestartCnt  = 0;
                for ( char i = 0; i < 12; i++ ) {
                    TData.Hart.FailCnt[i][0] = 0;
                    TData.Hart.FailCnt[i][1] = 0;
                }
            }
            
        }
        break;
    }
                                                               

}

/*************************************************************************
*
* Receive AN-ZBHART filter
*
*************************************************************************/
void GetHartFilter( char *pointer) {

    for ( int port = 0; port < 12; port++ ) {
        TData.Hart.Filter[port] = *pointer++;  //Get the filter
    }
}


/*************************************************************************
*
* Calculate tx checksum (header and package) using Dallas Semiconductor one-wire CRC
*
*************************************************************************/
char CalcDSTxChecksum(unsigned  Length) {
    unsigned char csum = 0;
    for ( short cnt = 0; cnt < Length; cnt++ ) {
        csum = crc[csum ^ My485UART.pTxBuffer[cnt + 4]];
    }
    return csum;
}


