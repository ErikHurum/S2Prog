/****************************************************************************************
/ Com protocol for USART0
/
***************************************************************************************/

#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

/*************************************************************************
*   (This is a timer calback)
*  Timout timer USART 0
*
*************************************************************************/
void TimoutUSART0(void) {

    UCSR0B &= ~(__BIT_MASK( UDRIE0)) ;            // transmission end, disable int.
    ClrBit(PORTE, 0x04) ;                              // TXE0 off
    OS_StopTimer(&TimerUSART0);                    // and stop timer
}

/*************************************************************************
*   (This is a timer calback)
*  Timout timer USART 1
*
*************************************************************************/
void TimoutUSART1(void) {

    UCSR1B &= ~(__BIT_MASK( UDRIE1)) ;            // transmission end, disable int.
    ClrBit(PORTE, 0x08) ;                              // TXE1 off
    OS_StopTimer(&TimerUSART1);                    // and stop timer
}


/*************************************************************************
*   (This is a task)
*  Usart0 handler
*
*************************************************************************/
void Usart0Handler(void) {
    char stat;

    while (1) {
        stat = OS_WaitEventTimed(1,500);
        if (stat) {
            OS_Use(&UARTSEND);
            UsartCheckPackage(0) ;
            OS_Unuse(&UARTSEND);
        }
    }
}

/*************************************************************************
*   (This is a task)
*  Usart1 handler
*
*************************************************************************/
void Usart1Handler(void) {
    char stat;

    while (1) {
        stat = OS_WaitEventTimed(1,500);
        if (stat) {
            OS_Use(&UARTSEND);
            UsartCheckPackage(1) ;
            OS_Unuse(&UARTSEND);
        }
    }
}

/*************************************************************************
*
*  Check the incoming packages
*
*************************************************************************/
void UsartCheckPackage(char ch) {

    unsigned int pointer;
    char    retval ;

    UART[ch].RxSendReply = false ;                           // flag for answering set to fault
    UART[ch].TxFirst = 11 ;                                 // Start pos for first TX command
    pointer = 7 ;
    do {
        retval = CheckActionUart(ch, pointer);
        pointer = pointer + UART[ch].pRxBuffer[pointer+2]
                  + (UART[ch].pRxBuffer[pointer+3]*256) + 4;          // Point to a command cmd hb/lb
    } while (retval && (pointer < (UART[ch].RxPacklen - 4 )));
    if (UART[ch].RxSendReply) {                              //send answer
        Uart_BuildTail(ch);
    }
    GoToSyncUART(ch) ;                                    // go to sync modus for recive
}


/*************************************************************************
*
*  Check action on received data
*
*************************************************************************/
char CheckActionUart(char ch, unsigned int pointer) {

    unsigned int   command;
    char    retval = true;
    float test = 2.0;

    test *= pointer;
    test = 0;

    command = UART[ch].pRxBuffer[pointer] | (UART[ch].pRxBuffer[pointer+1] << 8);
    switch (command) {                                  // check action
    case CMD_REQ_STATUS :                           // Regusest status for target
        BuildStatusData(ch) ;                         // make package
        break;

    case CMD_GET_STACKSTATUS :                        // Request stck status
        BuildStackStatus(ch, pointer+4) ;                     // receive package	
        break ;

    case CMD_GET_PROMDATA :                        // Request Skarpenord PromData
        BuildPromData(ch, pointer+4) ;                     // receive package	
        break ;

    case CMD_EEPROM_RESET :                        // Reset EEPROM??
        GetResetEEPROM(ch, pointer+4) ;                     // receive package	
        break ;

    case CMD_GOTO_BOOTLOADER :                        // Goto bootlaoder??
        GetGotoBootloader(ch, pointer+4) ;                     // receive package	
        break ;

    case CMD_SND_EEPROM_DATA :                              // Receive EEPROM data
        GetEEPROMData(ch, pointer+4) ;                     // receive package	
        break ;

    case CMD_REQ_EEPROM_DATA :                              // Request to send EEPROM data
        BuildEEPROMData(ch, pointer+4) ;                     // receive package	
        break ;

    case CMD_REQ_INT_DATA :                              // Request external data
        BuildADInt(ch, pointer+4) ;                     // receive package	
        break ;

    case CMD_SND_RS4_SETUP :                              // Receive sertup of AN-RS485
        if (UnitID == AN_ZB485) {
            GetRS4Setup(ch, pointer+4) ;                     // receive package	
        }
        break ;

    case CMD_REQ_RS4_SETUP :                              // Request for sertup of AN-RS485
        if (UnitID == AN_ZB485) {
            BuildRS4Setup(ch, pointer+4) ;                     // receive package	
        }
        break ;

    case CMD_SND_RS4_ADBUF :                              // Request external AD data
        if (UnitID == AN_ZB485) {
            GetADData(ch, pointer+4) ;                     // receive package	
        }
        break;

    case CMD_REQ_RS4_DATA :                              // Request external AD eeprom data
        if (UnitID == AN_ZB485) {
            switch (UART[ch].pRxBuffer[pointer+4]) {
            case 0:                                         // Measure data
                BuildMData485(ch, pointer+5) ;              // receive package	
                if (TData.RS4.FromTargetBuffer[0][0] == true) {     // send eepromdata ch 0?
                  BuildADEpromdata(ch, 0);
                  TData.RS4.FromTargetBuffer[0][0] = false ;  // Marked as sent
                }
                if (TData.RS4.FromTargetBuffer[1][0] == true) {     // send eepromdata ch 1?
                  BuildADEpromdata(ch, 1);                  // channel 1
                  TData.RS4.FromTargetBuffer[1][0] = false ;  // Marked as sent
                }
                break;
            case 1:                                         // Raw and cal data
                BuildRData485(ch, pointer+5) ;                     // receive package	
                break;
            }
        }
        break;

    case CMD_SND_ANA_SETUP :                              // Receive sertup of AN-RSANA
        if (UnitID == AN_ZBANA) {
            GetANASetup(ch, pointer+4) ;                     // receive package	
        }
        break ;

    case CMD_REQ_ANA_SETUP :                              // Request for sertup of AN-RSANA
        if (UnitID == AN_ZBANA) {
            BuildANASetup(ch, pointer+4) ;                     // receive package	
        }
        break ;

    case CMD_SND_ANA_FILTER :                              // Receive filter of AN-RSANA
        if (UnitID == AN_ZBANA) {
            GetANAFilter(ch, pointer+4) ;                     // receive package	
        }
        break ;

    case CMD_REQ_ANA_FILTER :                              // Request filter of AN-RSANA
        if (UnitID == AN_ZBANA) {
            BuildANAFilter(ch, pointer+4) ;                     // receive package	
        }
        break ;

    case CMD_REQ_ANA_DATA :                              // Request ANA data(4-20ma)
        if (UnitID == AN_ZBANA) {
            BuildMDataANA(ch, pointer+4) ;                     // receive
        }
        break ;

    default:
        if (command < MAX_ECMD) {                   // handle end commands
            retval = false ;
        }
        break;

    }
    return retval;
}

/*************************************************************************
*
* Build send packet header
*
*************************************************************************/
void Uart_BuildHeader(char ch) {

    UART[ch].RxFirst = 0;                                // Reset pointers
    UART[ch].RxLast  = 0;
    UART[ch].TxLast  = 0;

    UART[ch].pTxBuffer[0] = ANPRO10_SYN ;                        /* Sync */
    UART[ch].pTxBuffer[1] = ANPRO10_SYN ;                        /* Sync */
    UART[ch].pTxBuffer[2] = ANPRO10_SYN ;                        /* Sync */
    UART[ch].pTxBuffer[3] = ANPRO10_SOH ;                        /* Start of header */
    UART[ch].pTxBuffer[4] = UART[ch].pRxBuffer[2] ;      /* RXID */
    UART[ch].pTxBuffer[5] = UART[ch].pRxBuffer[3] ;      /* Rx address */
    UART[ch].pTxBuffer[6] = 0x10 + UnitID ;              /* Unit ID */
    UART[ch].pTxBuffer[7] = MyAddress();                 /* Tx address */
    UART[ch].pTxBuffer[8] = 0 ;                          /* packlen HB, don't know yet */
    UART[ch].pTxBuffer[9] = 0 ;                          /* packlen LB, don't know yet */
    UART[ch].pTxBuffer[10] = 0 ;                         /* Header checksum, don't know yet */
}

/*************************************************************************
*
* Build  packet tail
*
*************************************************************************/
void Uart_BuildTail(char ch) {

    Uart_BuildHeader(ch);                                    // fist build the header

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ECMD_NMDWOACK & 0xff ;  // End command lb
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ECMD_NMDWOACK >> 8 ;    // End command hb
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0x00 ;                  // End data

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = UART[ch].TxSeqCnt++ ;   // Sequence counter

    UART[ch].pTxBuffer[8] = UART[ch].TxFirst -2;                    // correct length because stx's
    UART[ch].pTxBuffer[9] = (UART[ch].TxFirst-2) >> 8 ;             // packet len high

    UART[ch].pTxBuffer[10] = CalcDSTxChecksum(ch, 10) ;         // Get header checksum

    UART[ch].pTxBuffer[UART[ch].TxFirst] = CalcDSTxChecksum(ch, UART[ch].TxFirst) ; // Get checksum
    UART[ch].TxFirst++ ;                                        // OBS!! must be inc here due
                                                                // to ANSI standard !!!!

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ANPRO10_EOT ;            // End of transmission
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0x00 ;            //switch off transmitter delay

    UART[ch].TxCount = UART[ch].TxFirst;                      //bytes to send
    UART[ch].TxLast = 0;                                     // reset cunter
    UART[ch].TxPkCnt++ ;                                     // Count sent packages
    if (ch == 0) {                                           // Turn on TXE for channel
        OS_RetriggerTimer(&TimerUSART0);                    // and start timeout timer
        SetBit(PORTE, 0x04) ;                                     // TXE0 on
        OS_Delay(5);                                       // Wait (ms) for tx stable
        UCSR0B |= __BIT_MASK( UDRIE0) ;                     // start sending by enableing interrupt
    } else if (ch ==1) {
        OS_RetriggerTimer(&TimerUSART1);                    // and start timeout timer
        SetBit(PORTE, 0x08) ;                                     // TXE1 on
        OS_Delay(5);                                       // Wait (ms) for tx stable
        UCSR1B |= __BIT_MASK( UDRIE1) ;                     // start sending by enableing interrupt
    }
}

/*************************************************************************
*
* Build datablock for card status
*
*************************************************************************/
void BuildStatusData(char ch){

    int ntna ;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_STATUS & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_STATUS >> 8;
    ntna = UART[ch].TxFirst ;                                    /* remember index */
    UART[ch].TxFirst += 2 ;                                      // two byte length
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ch ;               // channel
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = DEVICE_IO + UnitID ;   // Product ID
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = MyAddress();           // unit adddress
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = PROG_VERSION ;       // software version */
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = COMP_VERSION;        // cpmpability version
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = STORE_VERSION;        // cpmpability version
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (RXSIZE_UART & 0xff);         // rx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (( RXSIZE_UART >> 8) & 0xff); // rx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (TXSIZE_UART & 0xff);         // tx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((TXSIZE_UART >> 8) & 0xff);  // tx buffer size
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = RestartStatus ;                  // restart flag
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = PROGTYPE_APP ;                // Application program

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

    RestartStatus = 0 ;                                                       // set reset stat to 0 = read
}

/*************************************************************************
*
* Build EEPROM data package
*
*************************************************************************/
void BuildEEPROMData(char ch, int pointer) {

    int ntna ;
    char channel;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_EEPROM_DATA & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_EEPROM_DATA >> 8;
    ntna = UART[ch].TxFirst ;                                    /* remember index */
    UART[ch].TxFirst += 2 ;                                      // two byte length

    channel = UART[ch].pRxBuffer[pointer];
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = channel; //channel

    ReadEEPROMBuffer( (channel * sizeof(float)* 2) , sizeof(float), (char*)&UART[ch].pTxBuffer[UART[ch].TxFirst] );
    UART[ch].TxFirst += sizeof(float) ;
    ReadEEPROMBuffer( (channel * sizeof(float) * 2) + sizeof(float), sizeof(float), (char*)&UART[ch].pTxBuffer[UART[ch].TxFirst] );
    UART[ch].TxFirst += sizeof(float) ;

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb
}


/*************************************************************************
*
* Build datablock for Internal AD
*
*************************************************************************/
void BuildADInt(char ch, int pointer) {

    int ntna, i ;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_INT_DATA & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_INT_DATA >> 8;
    ntna = UART[ch].TxFirst ;                                    /* remember index */
    UART[ch].TxFirst += 2 ;                                      // two byte length

    for (i = 0; i<3; i++) {
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = ADInt.Result[i] ;
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = ADInt.Result[i] >> 8 ;   // ADresult
    }

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

}


/*************************************************************************
*
* Build datablock for eeprom on ADcard
*
*************************************************************************/
void BuildADEpromdata(char ch, char portch) {

    int ntna, i ;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_RS4_ADBUF & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_RS4_ADBUF >> 8;
    ntna = UART[ch].TxFirst ;                                    // remember index
    UART[ch].TxFirst += 2 ;                                      // two byte length

    for (i = 0; i < 44; i++) {
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.RS4.FromTargetBuffer[portch][i] ;
    }

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

}



/*************************************************************************
*
* Build setup dat package for AN-ZB485
*
*************************************************************************/
void BuildRS4Setup(char ch, int pointer) {

    int ntna ;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_RS4_SETUP & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_RS4_SETUP >> 8;
    ntna = UART[ch].TxFirst ;                                    /* remember index */
    UART[ch].TxFirst += 2 ;                                      // two byte length

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.RS4.PortUsed;  // send the setup
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.RS4.SensorType;  // send the sensor type

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb
}

/*************************************************************************
*
* Build datablock of measured data for ADcard
*
*************************************************************************/
void BuildMData485(char ch, int pointer) {

    int ntna, i ;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_RS4_MDATA & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_RS4_MDATA >> 8;
    ntna = UART[ch].TxFirst ;                                    /* remember index */
    UART[ch].TxFirst += 2 ;                                      // two byte length

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = UART[ch].pRxBuffer[pointer] ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.RS4.IOUnitStatus[UART[ch].pRxBuffer[pointer]] | (RestartStatus <<4); // IOUnit status +  restart status
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.RS4.FailCnt[UART[ch].pRxBuffer[pointer]][0] & 0xff; // Failcnt error
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (TData.RS4.FailCnt[UART[ch].pRxBuffer[pointer]][0] >> 8) & 0xff; // Failcnt error
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.RS4.FailCnt[UART[ch].pRxBuffer[pointer]][1] & 0xff; // Failcnt total
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (TData.RS4.FailCnt[UART[ch].pRxBuffer[pointer]][1] >> 8) & 0xff; // Failcnt total
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.RS4.TargetStatusSWVer[UART[ch].pRxBuffer[pointer]] ; // Target status byte 1
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.RS4.TargetStatusAddress[UART[ch].pRxBuffer[pointer]] ; // Target status byte 2

    TData.RS4.TargetStatusAddress[UART[ch].pRxBuffer[pointer]] &= ~0x80;                                  //reset restart flag for adcard

    for (i = 0; i < 14; i++) {
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.RS4.TargetSetup1[UART[ch].pRxBuffer[pointer]][i] ;
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.RS4.TargetSetup2[UART[ch].pRxBuffer[pointer]][i] ;
        *((float*)&UART[ch].pTxBuffer[UART[ch].TxFirst]) = *((float*)&TData.RS4.Result[UART[ch].pRxBuffer[pointer]][i]) ;   // ADresult
        UART[ch].TxFirst += sizeof(float) ;
    }

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

}

/*************************************************************************
*
* Build datablock of raw and cal data for ADcard
*
*************************************************************************/
void BuildRData485(char ch, int pointer) {

    int ntna, i ;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_RS4_RDATA & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_RS4_RDATA >> 8;
    ntna = UART[ch].TxFirst ;                                    /* remember index */
    UART[ch].TxFirst += 2 ;                                      // two byte length

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = UART[ch].pRxBuffer[pointer] ;
    for (i = 0; i < 14; i++) {
        *((int*)&UART[ch].pTxBuffer[UART[ch].TxFirst]) = *((int*)&TData.RS4.Raw[UART[ch].pRxBuffer[pointer]][i]) ;   // Raw data
        UART[ch].TxFirst += sizeof(int) ;
        *((int*)&UART[ch].pTxBuffer[UART[ch].TxFirst]) = *((int*)&TData.RS4.Cal[UART[ch].pRxBuffer[pointer]][i]) ;   // Cal data
        UART[ch].TxFirst += sizeof(int) ;
    }

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

}

/*************************************************************************
*
* Build setup data package for AN-ZBANA
*
*************************************************************************/
void BuildANASetup(char ch, int pointer) {

    int ntna ;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_ANA_SETUP & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_ANA_SETUP >> 8;
    ntna = UART[ch].TxFirst ;                                    /* remember index */
    UART[ch].TxFirst += 2 ;                                      // two byte length

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.Ana.PortUsed & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (TData.Ana.PortUsed >> 8) & 0xff;

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb
}

/*************************************************************************
*
* Build filter data package for AN-ZBANA
*
*************************************************************************/
void BuildANAFilter(char ch, int pointer) {

    char port;
    int ntna ;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_ANA_FILTER & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_ANA_FILTER >> 8;
    ntna = UART[ch].TxFirst ;                                    /* remember index */
    UART[ch].TxFirst += 2 ;                                      // two byte length

    for (port = 0; port < 12; port++) {
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.Ana.Filter[port];
    }

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb
}

/*************************************************************************
*
* Build datablock for External AD (ANA)
*
*************************************************************************/
void BuildMDataANA(char ch, int pointer) {

    int ntna, i ;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_ANA_MDATA & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_ANA_MDATA >> 8;
    ntna = UART[ch].TxFirst ;                                    /* remember index */
    UART[ch].TxFirst += 2 ;                                      // two byte length

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (RestartStatus << 4) ;    // Add restart status
    for (i = 0; i<12; i++) {
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = TData.Ana.Status[i] ;
        *((float*)&UART[ch].pTxBuffer[UART[ch].TxFirst]) = *((float*)&TData.Ana.Result[i]) ;   // ADresult
        UART[ch].TxFirst += sizeof(float) ;
    }

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

}

/*************************************************************************
*
* Build datablock for Stack status
*
*************************************************************************/
void BuildStackStatus(char ch, int pointer) {

    int ntna, stack ;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_STACKSTATUS & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_STACKSTATUS >> 8;
    ntna = UART[ch].TxFirst ;                                    /* remember index */
    UART[ch].TxFirst += 2 ;                                      // two byte length

    stack = OS_GetStackSpace(&TCB_USART0);                            // USART 0
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
    stack = OS_GetStackSpace(&TCB_USART1);                            // USART 1
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
    stack = OS_GetStackSpace(&TCB_WATCHDOG);                            // watchdog
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
    switch (UnitID) {
    case AN_ZB485 :
        stack = OS_GetStackSpace(&TCB_RS485Ctl);                            // RS485 Control
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
        stack = OS_GetStackSpace(&TCB_RS485Rec);                            // RS485 receive
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
        break;
    case AN_ZBANA :
        stack = OS_GetStackSpace(&TCB_AD7715);                            // AD handling
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = (stack & 0xff) ;
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = ((stack>>8) & 0xff) ;
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0 ;
        UART[ch].pTxBuffer[UART[ch].TxFirst++] = 0 ;
        break;
    }

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

}

/*************************************************************************
*
* Build datablock for Skarpenord Promdata
*
*************************************************************************/
void BuildPromData(char ch, int pointer) {

    int ntna, i ;
    UART[ch].RxSendReply = true ;                               // flag for answering

    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_PROMDATA & 0xff;
    UART[ch].pTxBuffer[UART[ch].TxFirst++] = CMD_REP_PROMDATA >> 8;
    ntna = UART[ch].TxFirst ;                                    /* remember index */
    UART[ch].TxFirst += 2 ;                                      // two byte length

    for (i = 0; i <= 31; i++) {
      ClrBit(PORTC,0x3F);
      SetBit(PORTC, i);
      SetBit(PORTC, 0x20);
  //    PORTC = 0x20 + i;
      OS_Delay(2);
      UART[ch].pTxBuffer[UART[ch].TxFirst++] = PINA ;
    }

    UART[ch].pTxBuffer[ntna] = (UART[ch].TxFirst - ntna - 2)  & 0xff ;      // length of data block lb
    UART[ch].pTxBuffer[ntna+1] = ((UART[ch].TxFirst - ntna - 2) >> 8 ) & 0xff ; // length of data block hb

}

//////////////////////////////////////////////////////////////////////////////
// Receiving data to IO module here
/////////////////////////////////////////////////////////////////////////////

/*************************************************************************
*
* Receive Command to Reset the EEPROM
*
*************************************************************************/
void GetResetEEPROM(char ch, int pointer) {

    EEPROMReset();
}


/*************************************************************************
*
* Receive Command to go to the bootloader program
*
*************************************************************************/
void GetGotoBootloader(char ch, int pointer) {

//    void (*BootApp)(void) = (void(*)())0xF000;

    while ( (EECR & 1<<EEWE) != 0 ) //chech if EEPROM is ready
        ;
    EEARL = (0x0fff & 0xff);
    EEARH = (0x0fff >> 8);
    EEDR = 0xff;
    EECR |= (1<<EEMWE);
    EECR |= (1<<EEWE);
    while (EECR & (1<<EEWE))
        ;

    WDTCR = 0x18;               //Start watchdog to genetate restart
    WDTCR = 0x08;               //Start watchdog to genetate restart
}

/*************************************************************************
*
* Receive EEPROM data
*
*************************************************************************/
void GetEEPROMData(char ch, int pointer) {

  char channel;
  int t0;

    channel = UART[ch].pRxBuffer[pointer] ;
    if ((channel >= 0x80) && (UnitID == 0x01)) { // AN-ZBANA
      *((float*)&TData.Ana.Offset[channel & 0x0f]) = *((float*)&UART[ch].pRxBuffer[pointer+1]) ;  //offset
      *((float*)&TData.Ana.Gain[channel & 0x0f]) = *((float*)&UART[ch].pRxBuffer[pointer+5]) ;  //gain
    }
    WriteEEPROMBuffer((channel * sizeof(float) * 2), sizeof(float), (char*)&UART[ch].pRxBuffer[pointer+1]);
    t0 = OS_GetTime();
    do {
      OS_Delay(1);
    }while ((OS_GetTime()-t0)< (sizeof(float)*9) && !EEPWriteOK);  //8.5 ms programming time
    WriteEEPROMBuffer( (channel * sizeof(float) * 2) + sizeof(float), sizeof(float), (char*)&UART[ch].pRxBuffer[pointer+5]);
    t0 = OS_GetTime();
    do {
      OS_Delay(1);
    }while ((OS_GetTime()-t0)< (sizeof(float)*9) && !EEPWriteOK);
}

/*************************************************************************
*
* Receive AN-ZB485 setup
*
*************************************************************************/
void GetRS4Setup(char ch, int pointer) {

    TData.RS4.PortUsed = UART[ch].pRxBuffer[pointer];           // Get the setup
    TData.RS4.SensorType = UART[ch].pRxBuffer[pointer+1];       // Get the sensor type
    WriteEEPROMByte(EEPROM_PORTSETUP, TData.RS4.PortUsed);      // store in EEPROM
    WriteEEPROMByte(EEPROM_PORTSETUP+1, TData.RS4.SensorType);
    SetRS4Port();                                               // Set power on ports
}

/*************************************************************************
*
* Rceive data fo AD card
*
*************************************************************************/
void GetADData(char ch, int pointer) {

   char i;

    TData.RS4.ToTargerBuffer[0] = true;                            //  Availible data for AD card
    TData.RS4.ToTargerBuffer[1] = UART[ch].pRxBuffer[pointer++];   //  Channel to AD card
    TData.RS4.ToTargerBuffer[2] = UART[ch].pRxBuffer[pointer++];   // nob in datablock
    for (i = 3; i < TData.RS4.ToTargerBuffer[2] + 3; i++) {
        TData.RS4.ToTargerBuffer[i] = UART[ch].pRxBuffer[pointer++];  //Get the buffer
    }
}

/*************************************************************************
*
* Receive AN-ZBANA setup
*
*************************************************************************/
void GetANASetup(char ch, int pointer) {

    TData.Ana.PortUsed = UART[ch].pRxBuffer[pointer] + (UART[ch].pRxBuffer[pointer+1] << 8);  //Get the setup
    WriteEEPROMByte(EEPROM_PORTSETUP,UART[ch].pRxBuffer[pointer]);   // store in EEPROM
    WriteEEPROMByte(EEPROM_PORTSETUP+1,UART[ch].pRxBuffer[pointer+1]);
    SetAnaPort();                           // set the port on or off
}

/*************************************************************************
*
* Receive AN-ZBANA filter
*
*************************************************************************/
void GetANAFilter(char ch, int pointer) {
    char port;

    for (port = 0; port <12; port++) {
        TData.Ana.Filter[port] = UART[ch].pRxBuffer[pointer++];  //Get the filter
    }
}

/*************************************************************************
*
*  Receive data on USARTs
*
*************************************************************************/
void ReceivePacketUart(char ch) {

    switch (UART[ch].RxState) {                  // check status
    case SYNC :
        // all functionallity in inerrupt routine
        break ;
    case HEADER :
        if (UART[ch].RxLast >= 6) {             // receive header
            UART[ch].RxPacklen = (UART[ch].pRxBuffer[4] + (UART[ch].pRxBuffer[5] * 256)) ; // Find length of package
            if (CalcDSRxChecksum(ch, 6) && (UART[ch].pRxBuffer[0] == (DEVICE_IO + UnitID))) {
                // header checksum OK and to me
                if ((UART[ch].RxPacklen < ((int) RXSIZE_UART-UART[ch].RxLast)) &&    /* chk. header */
                    (UART[ch].RxPacklen >= MIN_PACK_LEN)) {
                    UART[ch].RxState = RECEIVE ;       // Header ok go to data receive state
                    UART[ch].RxCount = UART[ch].RxLast + 1 ;    // Set receive counter
                } else {
                    GoToSyncUART(ch) ;                        // go to sync modus for recive
                }
            } else {
                GoToSyncUART(ch) ;                            // go to sync modus for recive
            }
        }
        break ;
    case RECEIVE :
        if (++UART[ch].RxCount >= UART[ch].RxPacklen) {
            if ((UART[ch].pRxBuffer[UART[ch].RxPacklen -1]) == ANPRO10_EOT) {
                if (CalcDSRxChecksum(ch, UART[ch].RxPacklen-2)) {
                    if ((UART[ch].pRxBuffer[1] == MyAddress())||      // message to me? or
                        (UART[ch].pRxBuffer[1] == 0xff)) {            // broadcast
                        hostAddress = UART[ch].pRxBuffer[3];            // address to sender (host)
                        UART[ch].RxState = HANDLE ;                     // Package OK
                        if (ch == 0) {
                            OS_SignalEvent(1, &TCB_USART0);
                        } else if (ch == 1) {
                            OS_SignalEvent(1, &TCB_USART1);
                        }
                    } else {
                        GoToSyncUART(ch) ;                             // go to sync modus for recive
                    }
                } else {
                    GoToSyncUART(ch) ;                                // go to sync modus for recive
                }
            } else {
                GoToSyncUART(ch) ;                                    // go to sync modus for recive
            }
        }
        break ;
    case HANDLE :
        break;
    default :
        GoToSyncUART(ch) ;                                            // go to sync modus for recive
        break ;
    }                                                           // end switch
    if (++UART[ch].RxLast >= RXSIZE_UART) {                     // check pointer
        UART[ch].RxLast = 0;                                     // reset pointer
    }
}


/*************************************************************************
*
* Calculate tx checksum (header and package) using Dallas Semiconductor one-wire CRC
*
*************************************************************************/
char CalcDSTxChecksum(char ch, unsigned int len) {

    unsigned int  cnt ;
    unsigned char   csum ;

    csum = 0 ;
    for (cnt = 4 ; cnt < len ; cnt++) {
        csum = crc[csum ^ UART[ch].pTxBuffer[cnt]] ;
    }
    return csum ;
}

/*************************************************************************
*
* Calculate rx packet checksum (header and package) using Dallas Semiconductor one-wire CRC
*
*************************************************************************/
int CalcDSRxChecksum(char ch, unsigned int len) {

    unsigned int  cnt ;
    unsigned char   csum ;

    csum = 0 ;
    for (cnt=0 ; cnt < len ; cnt++) {
        csum = crc[csum ^ UART[ch].pRxBuffer[cnt]] ;
    }
    if (csum == UART[ch].pRxBuffer[len]) {
        return true ;
    } else {
        return false ;
    }
}

/*************************************************************************
*
* Goes to sync mode
*
*************************************************************************/
__monitor void GoToSyncUART(char ch) {

    if (ch < 2) {
        UART[ch].SyncCnt = 0 ;                        // ready for sync
        UART[ch].RxState = SYNC ;
        UART[ch].RxFirst = 0 ;
    }
}
