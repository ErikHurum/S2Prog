
/****************************************************************************************
/ Uart communication to external ADcards
/
***************************************************************************************/

#include "iom1281.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"
//#include "stdlib.h"
//#include "string.h"



/************************************************ *************************
*   (This is a timer calback)
*  Timout timer UART 0
*
*************************************************************************/
void TimoutUART0(void) {

    U0_MCR &= ~RTS;      // set RTS off
}

/*************************************************************************
*   (This is a timer calback)
*  Timout timer UART 1
*
*************************************************************************/
void TimoutUART1(void) {

    U1_MCR &= ~RTS;       // set RTS off
}


/*************************************************************************
*   (This is a task)
*  Usart handler UART send request
*
*************************************************************************/
void ExtRS485Ctl(void) {
    char SeqCnt = 0;
    char PowerOnTimer = POWER_ON_CNT;                    // do not make a unwanted power on sequence in the starting phase
    char EventStatus;
    char AskMD[2];

    
    Init16552(0, 9600);                                      // Init UART channel 0
    Init16552(1, 9600);                                      // Init UART channel 1
    
    TData.RS4.PortUsed = ReadEEPROMByte(EEPROM_PORTSETUP);   // Get setup from EEPROM
    TData.RS4.SensorType[0] = ReadEEPROMByte(EEPROM_PORTSETUP + 1);
    TData.RS4.SensorType[1] = ReadEEPROMByte(EEPROM_PORTSETUP + 2);

    TData.RS4.ToTargetBuffer[0][0] = false;
    TData.RS4.ToTargetBuffer[1][0] = false;
    TData.RS4.FromTargetBuffer[0][0] = false;
    TData.RS4.FromTargetBuffer[1][0] = false;
    
    
    for (char i = 0; i < 8; i++) {
        SetBit(PORTC, (TData.RS4.PortUsed & (0x01 << i)));      // Switch on power
        OS_Delay(100);
    }
    OS_Delay(UART_START_DELAY);                               // Waiting for target startup
    
    while (1) {
        for (PortPair = 0; PortPair < 4; PortPair++) {        // loop through all ports
            if (UART16552[0].RxFaultCnt > MAX_16552_FAIL) {
                EmptyRxBuf16552(0);                            // Empty UART channel 0
            }
            if (UART16552[1].RxFaultCnt > MAX_16552_FAIL) {
                EmptyRxBuf16552(1);                            // Empty UART channel 1
            }
            if (PowerOnTimer < POWER_ON_CNT) {
                if (++PowerOnTimer >= POWER_ON_CNT) {          // check if time to switch on power
                    SetRS4Port();                                // and set power on ports
                }
            }
            SetBit(PORTE, 0xf0);
            ClrBit(PORTE, (0x10 << PortPair) & 0xf0);           // set mux port
            if ((TData.RS4.PortUsed >> PortPair) & 0x01) {      // sensor on port 0?
                UART16552[0].TxFirst = 6;                       // Start packet build at pos.
                char SnsType = (TData.RS4.SensorType[0] >> (2 * PortPair)) & 0x3;
                switch (SnsType) {
                case 0x01:    //Water ingress??
                    switch (SeqCnt) {
                    case 0:
                        Uart_BuildReqWISCardStatus(0);          //Card status
                        break;
                    case 20:
                        if ((TData.RS4.FromTargetBuffer[0][0] == false) && (TData.RS4.EEPROMPortpair[0] == PortPair)) { // buffer ready
                            Uart_BuildReqWISXData(0, 115);            // Request serial no
                            if (++TData.RS4.EEPROMPortpair[0] >= 4) {
                                TData.RS4.EEPROMPortpair[0] = 0;
                            }
                        } else {
                            Uart_BuildReqWISData(0);                //WIS data
                        }
                        break;
                    default:
                        Uart_BuildReqWISData(0);                //WIS data
                        break;
                    }
                    break;
                case 0x02: // Radar??
                    switch (SeqCnt) {
                    case 20:
                        if ((TData.RS4.FromTargetBuffer[0][0] == false) && (TData.RS4.EEPROMPortpair[0] == PortPair)) { // buffer ready
                            if (++TData.RS4.EEPROMPortpair[0] >= 4) {
                                TData.RS4.EEPROMPortpair[0] = 0;
                            }
                        }
                        // Fall through and send the request
                    default:
                        Uart_BuildReqRadarData(0);          // Radar data
                        break;
                    case 0:
                        Uart_BuildReqRadarInfo(0);          //Radar Information
                        break;
                    }
                    break;
                case 0x00:  // AN-SGCNV
                    if ((TData.RS4.ToTargetBuffer[0][0] == true) && // Data ready for this AD card
                        (TData.RS4.ToTargetBuffer[0][1] == PortPair)) {
                        Uart_BuildSndData(0);                       // add data to AD card package
                        Uart_BuildReqConfig(0);                 //Config data, cmd 17
                        AskMD[0] = false;
                    } else {
                        AskMD[0] = true;
                    }
                    if (SeqCnt == 0) {
                        Uart_BuildReqCardStatus(0);             //Card status, cmd 27
                    } else if (SeqCnt == 5) {
                        Uart_BuildReqR16552(0);                 //Raw data, cmd 13
                    } else if (SeqCnt == 10) {
                        Uart_BuildReqConfig(0);                 //Config data, cmd 17
                    } else if (SeqCnt == 15) {
                        Uart_BuildReqC16552(0);                 //Cal data, cmd 16
                    } else if (SeqCnt == 20) {
                        if ((TData.RS4.FromTargetBuffer[0][0] == false) && (TData.RS4.EEPROMPortpair[0] == PortPair)) { // buffer ready
                            Uart_BuildReqEEPROMData(0);             //EEpromdata cmd, 24
                            if ((TData.RS4.EEPROMADChannel[0] += 2) > 14) { //Next channel
                                TData.RS4.EEPROMADChannel[0] = 0;
                                if (++TData.RS4.EEPROMPortpair[0] >= 4) {
                                    TData.RS4.EEPROMPortpair[0] = 0;
                                }
                            }
                        } else if (AskMD[0] == true) {
                            Uart_BuildReqM16552(0);                 //Measure data, cmd 10
                        }
                    } else if (AskMD[0] == true) {
                        Uart_BuildReqM16552(0);                 //Measure data, cmd 10
                    }
                    break;
                }
                Uart_BuildTail16552(0);
            } else {
                if (TData.RS4.EEPROMPortpair[0] == PortPair) {
                    if (++TData.RS4.EEPROMPortpair[0] >= 4) {  // make sure that the EEPROM reading is not stopped
                        TData.RS4.EEPROMPortpair[0] = 0;
                    }
                }
            }
            if ((TData.RS4.PortUsed >> (PortPair + 4)) & 0x01) {              // sensor on port 1?
                UART16552[1].TxFirst = 6;                       // Start at
                char SnsType = ((TData.RS4.SensorType[1] >> (2 * PortPair))) & 0x3;
                switch (SnsType) {
                case 0x01:    //Water ingress??
                    switch (SeqCnt) {
                    case 0:
                        Uart_BuildReqWISCardStatus(1);          //Card status
                        break;
                    case 20:
                        if ((TData.RS4.FromTargetBuffer[1][0] == false) && (TData.RS4.EEPROMPortpair[1] == PortPair)) { // buffer ready
                            Uart_BuildReqWISXData(1, 115);            // Request serial no
                            if (++TData.RS4.EEPROMPortpair[1] >= 4) {
                                TData.RS4.EEPROMPortpair[1] = 0;
                            }
                        } else {
                            Uart_BuildReqWISData(1);                //WIS data
                        }
                        break;
                    default:
                        Uart_BuildReqWISData(1);                //WIS data
                        break;
                    }
                    break;
                case 0x02:    // Radar??
                    switch (SeqCnt) {
                    case 20:
                        if ((TData.RS4.FromTargetBuffer[1][0] == false) && (TData.RS4.EEPROMPortpair[1] == PortPair)) { // buffer ready
                            if (++TData.RS4.EEPROMPortpair[1] >= 4) {
                                TData.RS4.EEPROMPortpair[1] = 0;
                            }
                        }
                        // Fall through and send the request
                    default:
                        Uart_BuildReqRadarData(1);          // Radar data
                        break;
                    case 0:
                        Uart_BuildReqRadarInfo(1);          //Radar Information
                        break;
                    }
                    break;
                case 0x00:  // AN-SGCNV
                    if ((TData.RS4.ToTargetBuffer[1][0] == true) && // Data ready for this AD card
                        (TData.RS4.ToTargetBuffer[1][1] == (PortPair + 4))) {
                        Uart_BuildSndData(1);                       // add data to AD card package
                        Uart_BuildReqConfig(1);                 //Config data, cmd 17
                        AskMD[1] = false;
                    } else {
                        AskMD[1] = true;
                    }
                    if (SeqCnt == 0) {
                        Uart_BuildReqCardStatus(1);             //Card status, cmd 27
                    } else if (SeqCnt == 5) {
                        Uart_BuildReqR16552(1);                 //Raw data cmd, 13
                    } else if (SeqCnt == 10) {
                        Uart_BuildReqConfig(1);                 //Config data, cmd 17
                    } else if (SeqCnt == 15) {
                        Uart_BuildReqC16552(1);                 //Cal data  cmd, 16
                    } else if (SeqCnt == 20) {
                        if ((TData.RS4.FromTargetBuffer[1][0] == false) && (TData.RS4.EEPROMPortpair[1] == PortPair)) { // buffer ready
                            Uart_BuildReqEEPROMData(1);             //EEpromdata cmd, 24
                            if ((TData.RS4.EEPROMADChannel[1] += 2) > 14) { //Next channel
                                TData.RS4.EEPROMADChannel[1] = 0;
                                if (++TData.RS4.EEPROMPortpair[1] >= 4) {
                                    TData.RS4.EEPROMPortpair[1] = 0;
                                }
                            }
                        } else if (AskMD[1] == true) {
                            Uart_BuildReqM16552(1);                 //Measure data, cmd 10
                        }
                    } else if (AskMD[1] == true) {
                        Uart_BuildReqM16552(1);                 //Measure data, cmd 10
                    }
                    break;
                }
                Uart_BuildTail16552(1);
            } else {
                if (TData.RS4.EEPROMPortpair[1] == PortPair) {
                    if (++TData.RS4.EEPROMPortpair[1] >= 4) {  // make sure that the EEPROM reading is not stopped
                        TData.RS4.EEPROMPortpair[1] = 0;
                    }
                }
            }
            EventStatus = OS_WaitEventTimed(1, 1000);              // Wait for ready to send next
            if (EventStatus & 0x02) {
                if (PowerOnTimer >= POWER_ON_CNT) {
                    PowerOnTimer = 0;                              // and start over again
                }
            }
        }
        if (++SeqCnt > 20) {              //  all request within 20 x 2 sec.
            SeqCnt = 0;
        }
    }
}


/*************************************************************************
*   (This is a task)
*  Usart handler UART receive data
*
*************************************************************************/
void ExtRS485Rec(void) {

    char portresp;

    OS_Delay(UART_START_DELAY + 800);           // Waiting for target startup and power on sequence

    while (1) {
        OS_Delay(499);                          // wait for answer and correct the speed (.5 * 4 = 2 sec update)
        portresp = OS_WaitEventTimed(3, 1);     // Wait for receive from both channels
        if (portresp & 0x01) {                  // answer on ch 0
            Usart16552CheckPackage(0);         // handle incomming package
            TData.RS4.FailCnt[PortPair][0] = 0; // Reset counter
            TData.RS4.IOUnitStatus[PortPair] &= ~COMFAIL_BIT; // No error
            UART16552[0].RxFaultCnt = 0;          // OK package on 16552 channel
        } else {
            UART16552[0].RxFaultCnt++;          // Fault in package on 16552 channel
            TData.RS4.FailCnt[PortPair][1]++;      // no answer total counter
            if (TData.RS4.FailCnt[PortPair][0]++ > FAILCNT_ERROR) {
                TData.RS4.IOUnitStatus[PortPair] |= COMFAIL_BIT;      // report fault
            }
            if ((TData.RS4.PortUsed >> PortPair) & 0x01) {              // sensor on port 0?
                if ((TData.RS4.FailCnt[PortPair][0] & 0x0007) == 0x0004) {   //check if powqer shall be switched off
                    ClrBit(PORTC, (0x01 << PortPair));            // Switch off power
                    OS_SignalEvent(2, &TCB_RS485Ctl);
                }
            }
        }
        if (portresp & 0x02) {                  // answer on ch 1
            Usart16552CheckPackage(1);         // handle incomming package
            TData.RS4.FailCnt[PortPair + 4][0] = 0; // Reset counter
            TData.RS4.IOUnitStatus[PortPair + 4] &= ~COMFAIL_BIT; // No error
            UART16552[1].RxFaultCnt = 0;          // OK package on 16552 channel
        } else {
            UART16552[1].RxFaultCnt++;          // Fault in package on 16552 channel
            TData.RS4.FailCnt[PortPair + 4][1]++;      // no answer
            if (TData.RS4.FailCnt[PortPair + 4][0]++ > FAILCNT_ERROR) {
                TData.RS4.IOUnitStatus[PortPair + 4] |= COMFAIL_BIT;      // report fault
            }
            if ((TData.RS4.PortUsed >> (PortPair + 4)) & 0x01) {              // sensor on port 1?
                if ((TData.RS4.FailCnt[PortPair + 4][0] & 0x0007) == 0x0004) {   //check if powqer shall be switched off
                    ClrBit(PORTC, (0x01 << (PortPair + 4)));            // Switch off power
                    OS_SignalEvent(2, &TCB_RS485Ctl);
                }
            }
        }
        OS_SignalEvent(1, &TCB_RS485Ctl);
    }
}

/*************************************************************************
*
*  Set ports on or off
*
*************************************************************************/
void SetRS4Port(void) {

    PORTC = TData.RS4.PortUsed;

}

/*************************************************************************
*
*  Check the incoming packages from AN_SGCNV / WIS
*
*************************************************************************/
void Usart16552CheckPackage(char ch) {

    unsigned short pointer;
    char count_out, more;

    count_out = MAX_PROT_CMD;                  // max command
    more = true;
    pointer = 4;
    do {
        if (!CheckActionUart16552(ch, pointer)) {
            more = false;                          // terminate while loop
        }
        pointer += UART16552[ch].pRxBuffer[pointer + 1] + 2;            // Point to a command cmd hb/lb
        if (!--count_out) {
            more = false;
        }
    } while (more && (pointer < UART16552[ch].RxPacklen - 3));
    GoToSyncUART16552(ch);
}

/*************************************************************************
*
*  Check action on received data from AN_SGCNV
*
*************************************************************************/
char CheckActionUart16552(char ch, unsigned short pointer) {

    char retval = true;

    switch (UART16552[ch].pRxBuffer[pointer]) {    // check action

    case ANP1_REP_MP_DATA :                              // Measured pressure data
    case ANP1_REP_MT_DATA :                              // Measured temperature data
    case ANP1_REP_MO_DATA :                              // Measured "other" data
        ReceivePTOData(ch, pointer + 2);                     // receive package
        break;
    case ANP1_REP_WH_DATA :                              // Measured "washtrack and high level" data
        ReceiveWHData(ch, pointer + 2);                     // receive package
        break;
    case ANP1_REP_RP_DATA :                              // Raw pressure data
    case ANP1_REP_RT_DATA :                              // Raw temp. data
    case ANP1_REP_RO_DATA :                              // Raw "other" data
        ReceiveRData(ch, pointer + 2);              // receive package
        break;
    case ANP1_REP_CAL_DATA :                             // Raw "other" data
        ReceiveCData(ch, pointer + 2);              // receive package
        break;

    case ANP1_REP_CARD_STAT :                             // card status package
        ReceiveCardStatus(ch, pointer + 2);          // receive package
        break;

    case ANP1_REP_CONFIG :                             // config data
        ReceiveConfigData(ch, pointer + 2);          // receive package
        break;

    case ANP1_REP_EEP_DATA :                             // card eeprome
        ReceiveCardEEPROMData(ch, pointer + 2);          // receive package
        break;

    case ANP1_REP_WIS_STAT :                             // Card status from WIS
        ReceiveWISStatus(ch, pointer + 2);            // receive package
        break;

    case ANP1_REP_WIS_XDATA :                             // Card WIS protocol
        ReceiveWISXData(ch, pointer + 2);            // receive package
        break;

    case ANP1_REP_WIS_DATA :                             // Data from WIS
        ReceiveWISData(ch, pointer + 2);             // receive package
        break;
    case ANP1_REP_GODA_DATA:
        ReceiveRadarData(ch, pointer + 2);             // receive package
        break;
    case ANP1_REP_GODA_INFO:
        ReceiveRadarInfo(ch, pointer + 2);             // receive package
        break;
    case ANP1_ECMD_NMDRQACK :                             // No more data, send ack.
    case ANP1_ECMD_NMDWOACK :                         // No more data
        retval = false;
        break;
    }
    return retval;
}

/*************************************************************************
*
*  Receive card status from WIS
*
*************************************************************************/
void ReceiveWISStatus(char ch, unsigned short pointer) {

    TData.RS4.TargetStatusSWVer[(ch * 4) + PortPair] |= UART16552[ch].pRxBuffer[pointer];
    TData.RS4.TargetStatusAddress[(ch * 4) + PortPair] = UART16552[ch].pRxBuffer[pointer + 1];
    if (UART16552[ch].pRxBuffer[pointer + 4]) {
        TData.RS4.TargetStatusAddress[(ch * 4) + PortPair] |= 0x80;
    }
}

/*************************************************************************
*
*  Receive WIS protocol data
*
*************************************************************************/
void ReceiveWISXData(char ch, unsigned short pointer) {

    char i;

    switch (UART16552[ch].pRxBuffer[pointer++]) {
    case 115:                                     // Serial number
        TData.RS4.FromTargetBuffer[ch][0] = true;
        TData.RS4.FromTargetBuffer[ch][1] = (ch * 4) + PortPair;
        for (i = 2; i < (4 + 2); i++) {
            TData.RS4.FromTargetBuffer[ch][i] = UART16552[ch].pRxBuffer[pointer++];
        }
        break;
    default:
        break;
    }
}

/*************************************************************************
*
*  Receive measured data from WIS
*
*************************************************************************/
void ReceiveWISData(char ch, unsigned short pointer) {

    TData.RS4.Result[(ch * 4) + PortPair][0] = (float)UART16552[ch].pRxBuffer[pointer + 0];       // Water detected
    TData.RS4.Result[(ch * 4) + PortPair][1] = (float)((UART16552[ch].pRxBuffer[pointer + 1] << 8) // Temperature
                                                       + UART16552[ch].pRxBuffer[pointer + 2]) / 10.0;
    TData.RS4.TargetSetup1[(ch * 4) + PortPair][0] = UART16552[ch].pRxBuffer[pointer + 3];         // Status
    TData.RS4.TargetSetup2[(ch * 4) + PortPair][0] = 0;                                            // Unused
}


/*************************************************************************
*
*  Receive measured data from Radar
*
*************************************************************************/
void ReceiveRadarData(char ch, unsigned short pointer) {
    float *Data1 = (float *)&UART16552[ch].pRxBuffer[pointer + 0];
    float *Data2 = (float *)&UART16552[ch].pRxBuffer[pointer + 4];

    TData.RS4.Result[(ch * 4) + PortPair][0] = *Data1;       // Distance
    TData.RS4.Result[(ch * 4) + PortPair][1] = *Data2;      // Level
    TData.RS4.TargetSetup1[(ch * 4) + PortPair][0] = UART16552[ch].pRxBuffer[pointer + 8];         // Status
    TData.RS4.TargetSetup2[(ch * 4) + PortPair][0] = UART16552[ch].pRxBuffer[pointer + 9];         // Unused???
}


/*************************************************************************
*
*  Receive Serial number and version information from Radar
*
*************************************************************************/
void ReceiveRadarInfo(char ch, unsigned short pointer) {
    TData.RS4.SerialNumber[(ch * 4) + PortPair] = atol((const char *)&UART16552[ch].pRxBuffer[pointer + 0]);
    TData.RS4.TargetStatusSWVer[(ch * 4) + PortPair] = *((long *)&UART16552[ch].pRxBuffer[pointer + 10]);
}

/*************************************************************************
*
*  Receive pressure measured data from AN_SGCNV
*
*************************************************************************/
void ReceivePTOData(char ch, unsigned short pointer) {

    unsigned short pnt, ADCh;
    short packlen;

    packlen = UART16552[ch].pRxBuffer[pointer - 1];

    OS_Use(&UARTSEND);    // Do not write to buffer while the buffer can be read by other

    if (packlen > 0) {
        for (pnt = 0; pnt < packlen; pnt += 6) {
            ADCh = UART16552[ch].pRxBuffer[pointer + pnt];
            if (ADCh < 14) {
                TData.RS4.TargetSetup1[(ch * 4) + PortPair][ADCh] = UART16552[ch].pRxBuffer[pointer + pnt + 1];
                *((float *)&TData.RS4.Result[(ch * 4) + PortPair][ADCh]) = *((float *)&UART16552[ch].pRxBuffer[pointer + pnt + 2]);
            }
        }
    }
    OS_Unuse(&UARTSEND);
}
/*************************************************************************
*
*  Receive Wash Track and High Level data from AN_SGCNV
*
*************************************************************************/
void ReceiveWHData(char ch, unsigned short pointer) {

    // Fixed packet length
    //short packlen;

    //packlen = UART16552[ch].pRxBuffer[pointer - 1];

    OS_Use(&UARTSEND);    // Do not write to buffer while the buffer can be read by other
    short Index = (ch * 4) + PortPair;
    // Check if we have time information included
    if (UART16552[ch].pRxBuffer[pointer -1] == 4 ) {
        for (short pnt = 0; pnt < 3; pnt++) {
            TData.RS4.WTrackCnt[Index][pnt] = UART16552[ch].pRxBuffer[pointer+pnt];  // 4 x Wash track
        }
        // 4th WashTrack dont come
        TData.RS4.WTrackCnt[Index][3] = 0;  // Missing 4th Wash track because of BUG in H8 compiler
        TData.RS4.LevelSwitch[Index] = UART16552[ch].pRxBuffer[pointer +3]; // Hgh levels in 5th byte
        TData.RS4.WTTime[Index] = 0;
    }else{
        for (short pnt = 0; pnt < 4; pnt++) {
            TData.RS4.WTrackCnt[Index][pnt] = ((unsigned short *)&UART16552[ch].pRxBuffer[pointer])[pnt];  // 4 x Wash track
        }
        TData.RS4.LevelSwitch[Index] = UART16552[ch].pRxBuffer[pointer + 8]; // Hgh levels in 9th byte
        TData.RS4.WTTime[Index] = *((unsigned short *)&UART16552[ch].pRxBuffer[pointer + 9]);  // WashTrack time in 10th and 11th bytes
    }
    TData.RS4.WHDataAvailable |= 0x01 << ((ch * 4) + PortPair);
    OS_Unuse(&UARTSEND);
}


/************************************************************************
*
*  Receive raw data for pressure, temp and other from AN_SGCNV
*
*************************************************************************/
void ReceiveRData(char ch, unsigned short pointer) {

    char pnt, ADCh;
    short packlen;

    packlen = UART16552[ch].pRxBuffer[pointer - 1];

    if (packlen > 0) {
        for (pnt = 0; pnt < packlen; pnt += 4) {
            ADCh = UART16552[ch].pRxBuffer[pointer + pnt];
            if (ADCh < 14) {
                TData.RS4.TargetSetup1[(ch * 4) + PortPair][ADCh] = UART16552[ch].pRxBuffer[pointer + pnt + 1];
                *((short *)&TData.RS4.Raw[(ch * 4) + PortPair][ADCh]) = *((short *)&UART16552[ch].pRxBuffer[pointer + pnt + 2]);
            }
        }
    }
}

/*************************************************************************
*
*  Receive cal data  from AN_SGCNV
*
*************************************************************************/
void ReceiveCData(char ch, unsigned short pointer) {

    char pnt, ADCh;
    short packlen;

    packlen = UART16552[ch].pRxBuffer[pointer - 1];

    if (packlen > 0) {
        for (pnt = 0; pnt < packlen; pnt += 4) {
            ADCh = UART16552[ch].pRxBuffer[pointer + pnt];
            if (ADCh < 14) {
                TData.RS4.TargetSetup1[(ch * 4) + PortPair][ADCh] = UART16552[ch].pRxBuffer[pointer + pnt + 1];
                *((short *)&TData.RS4.Cal[(ch * 4) + PortPair][ADCh]) = *((short *)&UART16552[ch].pRxBuffer[pointer + pnt + 2]);
            }
        }
    }
}

/*************************************************************************
*
*  Receive card status  from AN_SGCNV
*
*************************************************************************/
void ReceiveCardStatus(char ch, unsigned short pointer) {

    TData.RS4.TargetStatusSWVer[(ch * 4) + PortPair] = UART16552[ch].pRxBuffer[pointer];
    TData.RS4.TargetStatusAddress[(ch * 4) + PortPair] = UART16552[ch].pRxBuffer[pointer + 1];
}

/*************************************************************************
*
*  Receive config data from AN_SGCNV
*
*************************************************************************/
void ReceiveConfigData(char ch, unsigned short pointer) {

    char i, ADCh;

    for (i = 0; i < 14; i++) {
        ADCh = UART16552[ch].pRxBuffer[pointer++];
        if (ADCh < 14) {
            TData.RS4.TargetSetup1[(ch * 4) + PortPair][ADCh] = UART16552[ch].pRxBuffer[pointer];
            TData.RS4.TargetSetup2[(ch * 4) + PortPair][ADCh] = UART16552[ch].pRxBuffer[pointer + 1];
        }
        pointer += 2;
    }
}

/*************************************************************************
*
*  Receive eeprom data from AN_SGCNV
*
*************************************************************************/
void ReceiveCardEEPROMData(char ch, unsigned short pointer) {

    short i;

    TData.RS4.FromTargetBuffer[ch][0] = true;
    TData.RS4.FromTargetBuffer[ch][1] = (ch * 4) + PortPair;
    for (i = 2; i < (41 + 2); i++) {
        TData.RS4.FromTargetBuffer[ch][i] = UART16552[ch].pRxBuffer[pointer++];
    }
}

/*************************************************************************
*
* Build send packet header for AN-SGCNV
*
*************************************************************************/
void Uart_BuildHeader16552(char ch) {

    UART16552[ch].RxFirst = 0;                                // Reset pointers
    UART16552[ch].RxLast = 0;
    UART16552[ch].TxLast = 0;

    UART16552[ch].pTxBuffer[0] = ANPRO1_SYN;                        /* Sync */
    UART16552[ch].pTxBuffer[1] = ANPRO1_SYN;                        /* Sync */
    UART16552[ch].pTxBuffer[2] = 0;                          /* Rx address */
    UART16552[ch].pTxBuffer[3] = MY_SGCNV_ADDR;              /* My address to AD-SGCNV */
    UART16552[ch].pTxBuffer[4] = 0;                          /* packlen HB, don't know yet */
    UART16552[ch].pTxBuffer[5] = 0;                          /* packlen LB, don't know yet */
}

/*************************************************************************
*
* Build  packet tail
*
*************************************************************************/
void Uart_BuildTail16552(char ch) {

    Uart_BuildHeader16552(ch);                                // fist build the header

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 1;         // command, No more data
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 0;         // error

    UART16552[ch].pTxBuffer[4] = (UART16552[ch].TxFirst) >> 8;           // packet len high
    UART16552[ch].pTxBuffer[5] = UART16552[ch].TxFirst;                // correct length because stx's


    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst] = CalcDSTxChecksumUART16552(ch, UART16552[ch].TxFirst); // Get checksum
    UART16552[ch].TxFirst++;                                     // OBS!! must be inc here due
                                                                 // to ANSI standard !!!!

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANPRO1_EOT;            // End of transmission
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 0x00;            //switch off transmitter delay

    UART16552[ch].TxCount = UART16552[ch].TxFirst - 1;       //bytes to send (-1 for the start byte)
    UART16552[ch].TxLast = 1;                               // sent 1 byte
    GoToSyncUART16552(ch);                                 // go to sync modus for recive
    if (ch == 0) {                                           // Turn on TXE for channel
        OS_RetriggerTimer(&TimerUART0);                    // and start timeout timer
        U0_MCR |= RTS;                                    // set RTS on
        OS_Delay(20);                                           // Wait (ms) for tx stable
        U0_THR = UART16552[ch].pTxBuffer[0];                // Send 1. byte
    } else if (ch == 1) {
        OS_RetriggerTimer(&TimerUART1);                    // and start timeout timer
        U1_MCR |= RTS;                                      // set RTS on
        OS_Delay(20);                                           // Wait (ms) for tx stable
        U1_THR = UART16552[ch].pTxBuffer[0];                  // Send 1. byte
    }
}

/*************************************************************************
*
* Build send request for system status on WIS
*
*************************************************************************/
void Uart_BuildReqWISCardStatus(char ch) {

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANP1_SND_WIS_STAT;       /*command, send data */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 0;                 /*nob */

}

/*************************************************************************
*
* Build send request for WIS protocoler on WIS
*
*************************************************************************/
void Uart_BuildReqWISXData(char ch, char sndcmd) {

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANP1_SND_WIS_XDATA;       /*command, send data */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 1;                        /*nob */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = sndcmd;                 // xdata cmd

}

/*************************************************************************
*
* Build send request for measure data to Water ingress
*
*************************************************************************/
void Uart_BuildReqWISData(char ch) {

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANP1_SND_WIS_DATA;       /*command, send data */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 1;                 /*nob */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 0;                 /*data */

}


/*************************************************************************
*
* Build send request for GODA measurement
*
*************************************************************************/
void Uart_BuildReqRadarData(char ch) {

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANP1_SND_GODA_DATA;       /*command, send data */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 1;                        /*nob */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 0;                 // data

}

/*************************************************************************
*
* Build send request for GODA device information
*
*************************************************************************/
void Uart_BuildReqRadarInfo(char ch) {

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANP1_SND_GODA_INFO;       /*command, send data */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 0;                        /*nob */
}

/*************************************************************************
*
* Build datablock to AN-SGCNV
*
*************************************************************************/
void Uart_BuildSndData(char ch) {

    char i;

    for (i = 3; i < (TData.RS4.ToTargetBuffer[ch][2]) + 3; i++) {
        UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = TData.RS4.ToTargetBuffer[ch][i];       /*command, send data */
    }
    TData.RS4.ToTargetBuffer[ch][0] = false;            // data sent
}

/*************************************************************************
*
* Build send request for measure data to AN-SGCNV
*
*************************************************************************/
void Uart_BuildReqM16552(char ch) {

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANP1_REQ_M_DATA;       /*command, send data */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 1;                 /*nob */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 0;                 /*data */

}

/*************************************************************************
*
* Build send request for raw data to AN-SGCNV
*
*************************************************************************/
void Uart_BuildReqR16552(char ch) {

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANP1_REQ_R_DATA;       /*command, send data */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 1;                 /*nob */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 0;                 /*data */

}

/*************************************************************************
*
* Build send request for cal data to AN-SGCNV
*
*************************************************************************/
void Uart_BuildReqC16552(char ch) {

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANP1_REQ_C_DATA;       /*command, send data */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 1;                 /*nob */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 0;                 /*data */

}

/*************************************************************************
*
* Build send request for system status on AN_SGCNV
*
*************************************************************************/
void Uart_BuildReqCardStatus(char ch) {

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANP1_REQ_CARD_STAT;       /*command, send data */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 1;                 /*nob */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 0;                 /*data */

}

/*************************************************************************
*
* Build send request for card config on AN_SGCNV
*
*************************************************************************/
void Uart_BuildReqConfig(char ch) {

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANP1_REQ_CONFIG;       /*command, send data */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 0;                 /*nob */

}

/*************************************************************************
*
* Build send request for EEPROM data on AN_SGCNV
*
*************************************************************************/
void Uart_BuildReqEEPROMData(char ch) {

    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = ANP1_REQ_EEP_DATA;       /*command, send data */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = 1;                 /*nob */
    UART16552[ch].pTxBuffer[UART16552[ch].TxFirst++] = TData.RS4.EEPROMADChannel[ch];       /*data */

}
/*************************************************************************
*
*  Receive data on USARTs
*
*************************************************************************/
void ReceivePacketUart16552(char ch) {

    switch (UART16552[ch].RxState) {                  // check status
    case SYNC :
        // all functionallity in inerrupt routine
        break;
    case HEADER :
        if (UART16552[ch].RxLast >= 3) {             // receive header
            UART16552[ch].RxPacklen = ((UART16552[ch].pRxBuffer[2] * 256) +
                                       UART16552[ch].pRxBuffer[3]);    // Find length of package
            if ((UART16552[ch].RxPacklen < ((short)RXSIZE_UART_16552 - UART16552[ch].RxLast)) &&    /* chk. header */
                (UART16552[ch].RxPacklen >= MIN_PACK_LEN)) {
                UART16552[ch].RxState = RECEIVE;       // Header ok og to data receive state
                UART16552[ch].RxCount = UART16552[ch].RxLast + 1;    // Set receivcounter
            } else {
                GoToSyncUART16552(ch);                                    // go to sync modus for recive
            }
        }
        break;
    case RECEIVE :
        if (++UART16552[ch].RxCount >= UART16552[ch].RxPacklen) {
            if ((UART16552[ch].pRxBuffer[UART16552[ch].RxPacklen - 1]) == ANPRO1_EOT) {
                if (CalcDSRxChecksum16552(ch)) {
                    if (UART16552[ch].pRxBuffer[0] == MY_SGCNV_ADDR) {     // reply from AN_SGCNV
                        UART16552[ch].RxState = HANDLE;                   // Package OK
                        if (ch == 0) {
                            OS_SignalEvent(1, &TCB_RS485Rec);
                        } else if (ch == 1) {
                            OS_SignalEvent(2, &TCB_RS485Rec);
                        }
                    } else {
                        GoToSyncUART16552(ch);                             // go to sync modus for recive
                    }
                } else {
                    GoToSyncUART16552(ch);                                // go to sync modus for recive
                }
            } else {
                GoToSyncUART16552(ch);                                    // go to sync modus for recive
            }
        }
        break;
    case HANDLE :
        break;
    default :
        GoToSyncUART16552(ch);                                            // go to sync modus for recive
        break;
    }                                                           // end switch
    if (++UART16552[ch].RxLast >= RXSIZE_UART_16552) {                     // check pointer
        UART16552[ch].RxLast = 0;                                     // reset pointer
    }
}


/*************************************************************************
*
* Calculate tx checksum for Dallas Semiconductor one-wire CRC
*
*************************************************************************/
char CalcDSTxChecksumUART16552(char ch, unsigned short len) {

    unsigned short cnt;
    unsigned char csum;

    csum = 0;
    for (cnt = 2; cnt < len; cnt++) {
        csum = crc[csum ^ UART16552[ch].pTxBuffer[cnt]];
    }
    return csum;
}

/*************************************************************************
*
* Calculate rx checksum for Dallas Semiconductor one-wire CRC
*
*************************************************************************/
short CalcDSRxChecksum16552(char ch) {

    short cnt;
    unsigned char csum;

    csum = 0;
    for (cnt = 0; cnt < (UART16552[ch].RxPacklen - 2); cnt++) {
        csum = crc[csum ^ UART16552[ch].pRxBuffer[cnt]];
    }
    if (csum == UART16552[ch].pRxBuffer[UART16552[ch].RxPacklen - 2]) {
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
void GoToSyncUART16552(char ch) {

    if (ch < 2) {
        UART16552[ch].SyncCnt = 0;                        // ready for sync
        UART16552[ch].RxState = SYNC;
        UART16552[ch].RxFirst = 0;
        UART16552[ch].RxPacklen = 0;
    }
}

/*************************************************************************
*
*  Empty rx buffer on PC16552 UART
*
*************************************************************************/
void EmptyRxBuf16552(char uartno) {

    switch (uartno) {
    case 0:
        do {
            U0_RBR;
        } while (U0_LSR & DATA_READY);
        break;
    case 1:
        do {
            U1_RBR;
        } while (U1_LSR & DATA_READY);
        break;
    }
}

/*************************************************************************
*
*  Init the PC16552 UART
*
*************************************************************************/
void Init16552(char channel, unsigned long baud) {

    /*--- Configure UART data block ---*/
    UART16552[channel].TxFirst = 0x00;
    UART16552[channel].TxLast = 0x00;
    UART16552[channel].TxCount = 0x00;
    UART16552[channel].RxFirst = 0x00;
    UART16552[channel].RxLast = 0x00;
    UART16552[channel].RxCount = 0x00;
    UART16552[channel].RxState = SYNC;
    UART16552[channel].SyncCnt = 0;
    UART16552[channel].TxStatus = 0x00;

    switch (channel) {
    case 0x00 :
        UART16552[channel].RxTimeout = RX_TO_TIME;   // reset timeout
        UART16552[channel].pTxBuffer = TxBuf16552Ch0;
        UART16552[channel].pRxBuffer = RxBuf16552Ch0;
        U0_LCR = 0x80;          // set DLAB
        U0_DLL = ((XTAL_CPU / 8 / 16 / baud) & 0xff);
        U0_DLM = (((XTAL_CPU / 8 / 16 / baud) >> 8) & 0xff);
        U0_LCR = 0x03;          // reset DLAB and set 8,n,1
        U0_FCR = 0x01;          // enable FIFO ..
        U0_FCR = 0xC1;          // and set RXLevel to 14
        U0_IER = 0x03;          // enable TX and RX int.
        U0_MCR = 0x00;          // RTS off
        break;
    case 0x01 :
        UART16552[channel].RxTimeout = RX_TO_TIME;   // reset timeout
        UART16552[channel].pTxBuffer = TxBuf16552Ch1;
        UART16552[channel].pRxBuffer = RxBuf16552Ch1;
        U1_LCR = 0x80;          // set DLAB
        U1_DLL = ((XTAL_CPU / 8 / 16 / baud) & 0xff);
        U1_DLM = (((XTAL_CPU / 8 / 16 / baud) >> 8) & 0xff);
        U1_LCR = 0x03;          // reset DLAB and set 8,n,1
        U1_FCR = 0x01;          // enable FIFO ..
        U1_FCR = 0xC1;          // and set RXLevel to 14
        U1_IER = 0x03;          // enable TX and RX int.
        U1_MCR = 0x00;          // RTS off
        break;
    default:
        break;
    }
}
