#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif
#define SAAB_DELAY  30 // In Saab spec minimum 20 mS
vector<SaabProtcol *>SaabProtcol::SaabProtcolVector;
set<PRogramObjectBase *>SaabProtcol::ObjectSet;

//---------------------------------------------------------------------------


SaabProtcol::SaabProtcol(int PortNum, unsigned IDNum) {
    ObjectSet.insert(this);
    SaabProtcolVector.push_back(this);
    if (IDNum == 0) {
        IDNumber = (C_PRO_SAAB_PROTOCOL << 16) + SaabProtcolVector.size();
    } else {
        IDNumber = IDNum;
    }
    Initiate();
    if (PortNum >= 0) {
        WinUart = PortNum;
    }
}

void SaabProtcol::Initiate(void) {
    Delay           = SAAB_DELAY;
    CurrentRequest  = 0;
    TCUAddress      = 0;
}

SaabProtcol::~SaabProtcol(void) {
    ObjectSet.erase(this);
}

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

void SaabProtcol::WriteConfigToFile(TSNConfigString& ConfigString) {

    AnsiString LocalString;
    LocalString += KeyWord(C_PRO_SAAB_PROTOCOL) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_TCU_ADDRESS) + (AnsiString)TCUAddress + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_TCU_PORT_NO) + (AnsiString)WinUart + CrLfStr;

    LocalString += MakeConfigString();   //common
    LocalString += TabStr1 + KeyWord(C_DELAY) + TabStr1 + (AnsiString)Delay + CrLfStr;
    if (!ExtraParameters.empty()) {
        for (unsigned i = 0; i < ExtraParameters.size(); i++) {
            LocalString += TabStr1 + KeyWord(ExtraParameters[i].Key);
        }
    }
    if (!BlockVector.empty()) {
        for (unsigned i = 0; i < BlockVector.size(); i++) {
            LocalString += TabStr1 + KeyWord(BlockVector[i].ValKey + C_SVT_OFFSET);
        }
    }
    LocalString += KeyWord(C_PRO_END) + CrLfStr2;

    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

int SaabProtcol::LoadConfigFromFile(TSNConfigString& ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning("Saab Protocol", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning("Saab protocol", InputKeyWord, ConfigString.LineCount);
                break;
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_PRO_START_PRO:
                PRogramObject::LoadConfigString(ConfigString);
                break;
            case C_TCU_ADDRESS:
                TCUAddress = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_TCU_PORT_NO:
                WinUart = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_DELAY:
                Delay = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SAAB_EXPORT_LPRESS    :
                {
                    SaabData tmpData = { C_SAAB_EXPORT_LPRESS, SVT_PRESSURE, 100, false, C_PRO_LINEPRESS, SAAB_ACT_NORMAL };
                    ExtraParameters.push_back(tmpData);
                }
                break;
            case C_SAAB_EXPORT_TPRESS    :
                {
                    SaabData tmpData = { C_SAAB_EXPORT_TPRESS, SVT_PRESSURE, 1000, true, C_PRO_TANKPRESS, SAAB_ACT_NORMAL };
                    ExtraParameters.push_back(tmpData);
                }
                break;
            case C_SAAB_EXPORT_ATM_PRESS :
                {
                    SaabData tmpData = { C_SAAB_EXPORT_ATM_PRESS, SVT_ATM_PRESSURE, 1000, false, C_PRO_ATMREFSENS, SAAB_ACT_SPECIAL };
                    ExtraParameters.push_back(tmpData);
                }
                break;
            case C_SAAB_EXPORT_TEMP      :
                {
                    SaabData tmpData = { C_SAAB_EXPORT_TEMP, SVT_TEMP, 10, true, C_PRO_TEMP, SAAB_ACT_NORMAL };
                    ExtraParameters.push_back(tmpData);
                }
                break;
            case SVT_LEVEL_SENSOR  + C_SVT_OFFSET:
            case SVT_VOLPERCENT    + C_SVT_OFFSET:
            case SVT_TEMP          + C_SVT_OFFSET:
            case SVT_WEIGHT        + C_SVT_OFFSET:
            case SVT_PRESSURE      + C_SVT_OFFSET:
            case SVT_DENSITY       + C_SVT_OFFSET:
            case SVT_LOADRATE      + C_SVT_OFFSET:
                {
                    unsigned FTank, NoOfTanks;
                    FTank = ConfigString.ReadLong(ErrorLine);
                    if (!ErrorLine) {
                        NoOfTanks = ConfigString.ReadLong(ErrorLine);
                        if (!ErrorLine) {
                            BlockDef B = { Key - C_SVT_OFFSET, FTank, NoOfTanks };
                            BlockVector.push_back(B);
                        }
                    }
                }
                break;
            }
        }
    }
    while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    return ErrorLine;
}




void SaabProtcol::SendString(TSNUart *PortPtr, char *TxBuf, int OutPtr) {
    unsigned short CheckSum = 0;
    for (int i = 0; i < OutPtr; i++) {
        CheckSum += TxBuf[i];
    }
    OutPtr += sprintf(&TxBuf[OutPtr], "%04X\r\n", CheckSum);
    PortPtr->Send((U8 *)TxBuf, OutPtr, SEND_COMPLETE_EVENT);
    switch (PortPtr->HWProtocol) {
    case C_UART_HWPRO_485 :
        {
            PortPtr->ClearRxBuffer();
            U8 tmpBuf[16];
            PortPtr->Receive(tmpBuf, 16, 10);  // Be sure to remove the ecco
        }
        break;
    case C_UART_HWPRO_232 :
        break;
    }
}

////////////////////////////////////////////////////////////////////////////
//
//  Add alarm status
//
///////////////////////////////////////////////////////////////////////////

void SaabProtcol::AddAlarmStatus(char *OutBuf, int& OutPtr, int Index, int ObjectType) {
    // Include alarm status
    switch (ObjectType) {
    case SAAB_LPRESSVAL:
        {
            PROLinePressure *tmpPtr = (PROLinePressure *)PROXRefObject::GetSaabObject(Index);
            if (tmpPtr) {
                int AlStatus;
                if (tmpPtr->HWFailure) {    // HW is first priority
                    AlStatus = 1;
                } else if (tmpPtr->HighPressurePtr->State != AlarmBasic::AlIdle) {
                    AlStatus = 4;
                } else if (tmpPtr->LowPressurePtr->State != AlarmBasic::AlIdle) {
                    AlStatus = 5;
                } else AlStatus   = 0;
                OutBuf[OutPtr++] = '0' + AlStatus; // Add the alarm status
            } else {
                // Flag that the value is invalid
                OutBuf[OutPtr++] = '8'; // Add the alarm status
            }
        }
        break;
    case SAAB_TPRESSVAL:
        {
            PROTankPressure *tmpPtr = (PROTankPressure *)PROXRefObject::GetSaabObject(Index);
            if (tmpPtr) {
                int AlStatus;
                if (tmpPtr->HWFailure) {    // HW is first priority
                    AlStatus = 1;
                } else if (tmpPtr->HighPressurePtr->State) {
                    AlStatus = 4;
                } else if (tmpPtr->LowPressurePtr->State != AlarmBasic::AlIdle) {
                    AlStatus = 5;
                } else AlStatus   = 0;
                OutBuf[OutPtr++] = '0' + AlStatus; // Add the alarm status
            } else {
                // Flag that the value is invalid
                OutBuf[OutPtr++] = '8'; // Add the alarm status
            }
        }
        break;
    case SAAB_TANKVAL:
        {
            PROTank *tmpPtr = (PROTank *)PROXRefObject::GetSaabObject(Index);
            if (tmpPtr) {
                int AlStatus;
                if (tmpPtr->HWFailure) { // HW is first priority
                    AlStatus = 1;
                } else if (tmpPtr->OverfillPtr && tmpPtr->OverfillPtr->State != AlarmBasic::AlIdle) {
                    AlStatus = 3;
                } else if (tmpPtr->HighLevelPtr->State != AlarmBasic::AlIdle) {
                    AlStatus = 4;
                } else if (tmpPtr->LowLevelPtr->State != AlarmBasic::AlIdle) {
                    AlStatus = 5;
                } else if (tmpPtr->LoLoLevelPtr && tmpPtr->LoLoLevelPtr->State != AlarmBasic::AlIdle) {
                    AlStatus = 6;
                } else AlStatus   = 0;
                OutBuf[OutPtr++] = '0' + AlStatus; // Add the alarm status
            } else {
                // Flag that the value is invalid
                OutBuf[OutPtr++] = '8'; // Add the alarm status
            }
        }
        break;

    }

}




////////////////////////////////////////////////////////////
//
//  Handles input
//
// NOTE: Several values like pressure and BT,MT,UT and TT are
// not supported, load rate
////////////////////////////////////////////////////////////
void SaabProtcol::SAABHandleInput(TSNUart *PortPtr, U8 Data) {
    volatile bool DataAvailable;
    U8 Data2;
    char InBuf[SAAB_BUF_SIZE] = { Data };
    int Ptr = 1;
    do {
        DataAvailable = PortPtr->Receive(&Data2, 1, 200); // wait till a character comes in
        InBuf[Ptr++]  = (char)Data2;
    }
    while (DataAvailable && (Data2 != 0x0A) && (Ptr < SAAB_BUF_SIZE));
    // Do we want to receive the data and does it seem like a valid packet?
    if ((PROSystemData::ReceiveWeightVolume) && (Ptr >= SAAB_MIN_PACKET) && (Ptr < SAAB_BUF_SIZE)) {
        char *EndPtr;
        unsigned CheckSum = 0;
        Ptr -= 6;
        unsigned PacketCheckSum = strtoul(&InBuf[Ptr], &EndPtr, 16);
        for (int i = 0; i < Ptr; i++) {
            CheckSum += InBuf[i];
        }
        // Compare the checksum
        if (CheckSum == PacketCheckSum) {
            short TNo = 0;
            switch (Data) {
            case 'v':    // Tank values
            case 'V':    // Tank values
            case 'a':    // Tank values with alarm status
            case 'A':    // Tank values with alarm status
                {
                    int FirstTank     = (InBuf[1] - '0') * 10 + (InBuf[2] - '0');
                    int NumberOfTanks = (InBuf[3] - '0') * 10 + (InBuf[4] - '0');
                    int ValKey = -1;
                    float Scale;
                    switch (InBuf[5]) {
                    case 'U':
                        ValKey = SVT_ULLAGE;     // Corrected to ref point
                        Scale = 1000.0;
                        break;
                    case 'C':
                        ValKey = SVT_ULLAGE_FC; // Corrected to FC
                        Scale = 1000.0;
                        break;
                    case 'I':
                        ValKey = SVT_LEVEL_FC; // Corrected to FC
                        Scale = 1000.0;
                        break;
                    case 'K':
                        ValKey = SVT_SOUNDING; // Corrected to FC
                        Scale = 1000.0;
                        break;
                    case 'D':
                        ValKey = SVT_DENSITY;
                        Scale = 10000.0;
                        break;
                    case 'V':
                        ValKey = SVT_LC_VOLUME;
                        Scale = 1.0;
                        break;
                    case 'W':
                        ValKey = SVT_LC_WEIGHT;
                        Scale = 1.0;
                        break;
                    case 'E':
                        ValKey = SVT_LOADRATE;
                        Scale = 10.0;
                        break;
                    case 'F':
                        ValKey = SVT_VOLPERCENT;
                        Scale = 100.0;
                        break;
                    case 'P':
                        ValKey = SVT_PRESSURE;
                        Scale = 1000.0;
                        break;
                    case 'T':
                        ValKey = SVT_TEMP;
                        Scale = 10.0;
                        break;
                    case 'R':   // Not supported
                        break;
                    case 'X':
                        ValKey = SVT_T1;
                        Scale = 100.0;
                        break;
                    case 'Y':
                        ValKey = SVT_T3;
                        Scale = 100.0;
                        break;
                    case 'Z':
                        ValKey = SVT_T4;
                        Scale = 100.0;
                        break;
                    default:
                        TNo = -1;
                        ValKey = SVT_BLANK;
                        break;
                    }
                    char *InPtr = &InBuf[6];
                    if (TNo >= 0) {
                        // I have a value I support
                        int LastTank = FirstTank + NumberOfTanks;
                        for (int Index = FirstTank; Index < LastTank; Index++) {
                            PROTank *TmpPtr = (PROTank *)PROXRefObject::GetSaabObject(Index);
                            if (TmpPtr) {
                                char TmpBuf[BUF_SIZE];
                                memcpy(TmpBuf, InPtr, 5);
                                TmpBuf[5] = 0; // Terminate the string
                                //InPtr += 5;
                                if ((*TmpBuf == 'E') || (*TmpBuf == '*')) {} else {
                                    char *EndPtr;
                                    //int IStatus;
                                    float Value = strtod(TmpBuf, &EndPtr);
                                    if (EndPtr) {
                                        Value /= Scale;
                                        switch (ValKey) {
                                        case SVT_LC_VOLUME:
                                        case SVT_LC_WEIGHT:
                                        case SVT_LC_DENSITY:
                                            /*IStatus = */TmpPtr->PutFloatValue(ValKey, Value);
                                            break;
                                        default:
                                            /*IStatus = */TmpPtr->PutFloatValue(ValKey, Value);
                                            break;
                                        }
                                    }
                                }
                            }
                            switch (Data) {
                            case 'V':
                            case 'v':
                                InPtr += 5;      // Step 5 chars in the inbuffer
                                break;
                            case 'a':
                            case 'A':
                                // Include alarm status
                                /*  if ( TNo >= 0){
                                OnlineTank *T  = OnlineTank::Table[TNo];
                                    switch(InPtr[5]){
                                    case '0':
                                    case '1':
                                    case '2':
                                    case '3':
                                    case '4':
                                    case '5':
                                    case '8':
                                        break; // All alarms handeled by master.
                                                 // Slave alarms are all ignored
                                    }
                                }
                                                                */
                                InPtr += 6;      // Step 5 chars in the inbuffer
                                break;
                            } // End of switch
                        }
                    } else {
                        // Not supported value, juste ignore
                    }
                }   // End case 'V', 'A'
                break;
            case 'h':
            case 'H':
            case 'l':
            case 'L':
                {
                    int FirstTank     = (InBuf[1] - '0') * 10 + (InBuf[2] - '0');
                    int NumberOfTanks = (InBuf[3] - '0') * 10 + (InBuf[4] - '0');
                    int ValKey = -1;
                    float Scale;
                    switch (InBuf[5]) {
                    case 'u':
                        switch (Data) {
                        case 'h':
                        case 'H':
                            ValKey = SVT_HI_ULLAGE_LIM;
                            break;
                        case 'l':
                        case 'L':
                            ValKey = SVT_LO_ULLAGE_LIM;
                            break;
                        }
                        Scale = 1000.0;
                        break;
                    case 'i':   // Not supported
                        switch (Data) {
                        case 'h':
                        case 'H':
                            ValKey = SVT_HI_LEVEL_LIMIT;
                            break;
                        case 'l':
                        case 'L':
                            ValKey = SVT_LO_LEVEL_LIMIT;
                            break;
                        }
                        Scale = 1000.0;
                        break;
                    }
                    char *InPtr = &InBuf[6];
                    if (TNo >= 0) {
                        // I have a value I support
                        int LastTank = FirstTank + NumberOfTanks;
                        for (int Index = FirstTank; Index < LastTank; Index++) {
                            PROTank *TmpPtr = (PROTank *)PROXRefObject::GetSaabObject(Index);
                            if (TmpPtr) {
                                char TmpBuf[BUF_SIZE];
                                memcpy(TmpBuf, InPtr, 5);
                                TmpBuf[5] = 0; // Terminate the string
                                InPtr += 5;
                                if ((*TmpBuf == 'E') || (*TmpBuf == '*')) {} else {
                                    char *EndPtr;
                                    //int   IStatus;
                                    float Value = strtod(TmpBuf, &EndPtr);
                                    if (EndPtr) {
                                        Value /= Scale;
                                        /*IStatus = */TmpPtr->PutFloatValue(ValKey, Value);
                                    }
                                }
                            }
                            InPtr += 5;      // Step 5 chars in the inbuffer
                        }
                    } else {
                        // Not supported value, juste ignore
                    }
                }   // End case 'H', 'h'
                break;
            case 's':
            case 'S':
                // No reason to support this??
                if (InBuf[1] == 'D') {} else {}
                break;

            } // End of block swicth
        }   // end of Checksum OK
    } // End of if Valid packet

}

////////////////////////////////////////////////////////////
//
//  Handles answer in Master mode
//
////////////////////////////////////////////////////////////
bool SaabProtcol::SAABHandleAnswer(TSNUart *PortPtr) {
    U8 Data;
    bool DataAvailable = PortPtr->Receive(&Data, 1, 500);
    if (DataAvailable) {
        switch (Data) {
        case 'V':    // Tank values
        case 'A':    // Tank values and alarm status
        case 'H':    // Tank high limits
        case 'L':    // Tank low limits
        case 'S':    // Ship information
            SAABHandleInput(PortPtr, Data);
            break;

        }
    }
    return (DataAvailable);
}

SaabProtcol* SaabProtcol::FindSaabProtocolObject(int portNo) {
    if (!SaabProtcolVector.empty()) {
        for (unsigned i = 0; i < SaabProtcolVector.size(); i++) {
            SaabProtcol *TempElement = SaabProtcolVector[i];
            if ((portNo == TempElement->WinUart)
                && (TempElement->TCUAddress == PROTanksystemUnit::MySelf->TCUAddress)) {
                return (TempElement); // Quick and dirty, simply return
            }
        }
    }
    return (NULL);
}


////////////////////////////////////////////////////////////////////////////
//
//  Sends request to Saab, when master. Follows configured request sequence
//
//
////////////////////////////////////////////////////////////////////////////
void SaabProtcol::SAABSendRequest(TSNUart *PortPtr) {
    if (CurrentRequest >= (int)BlockVector.size()) {
        CurrentRequest = 0;
    }
    BlockDef B = BlockVector[CurrentRequest++];
    char OutBuf[SAAB_BUF_SIZE] = { "V" };
    int Ptr = 1;
    Ptr += sprintf(&OutBuf[Ptr], "%02u", B.First_Tank);
    Ptr += sprintf(&OutBuf[Ptr], "%02u", B.Number_of_Tanks);
    switch (B.ValKey) {
    case SVT_ULLAGE_FC:
        OutBuf[Ptr++] = 'U';
        break;
    case SVT_ULLAGE:
        OutBuf[Ptr++] = 'C';
        break;
    case SVT_DENSITY:
        OutBuf[Ptr++] = 'D';
        break;
    case SVT_VOLUME:
        OutBuf[Ptr++] = 'V';
        break;
    case SVT_WEIGHT:
        OutBuf[Ptr++] = 'W';
        break;
    case SVT_LOADRATE:
        OutBuf[Ptr++] = 'E';
        break;
    case SVT_VOLPERCENT:
        OutBuf[Ptr++] = 'F';
        break;
    case SVT_PRESSURE:
        OutBuf[Ptr++] = 'P';
        break;
    case SVT_TEMP:
        OutBuf[Ptr++] = 'T';
        break;
    }
    SendString(PortPtr, OutBuf, Ptr);
}

void SaabProtcol::SaabComTask(TSNUart *PortPtr) {
#ifdef S2TXU
    OS_Delay(5000);
    OS_TASK *TxTaskPtr = OS_GetpCurrentTask();
    OS_SetPriority(TxTaskPtr, SAAB_TASK_PRIORITY);

    // Clear all other requests
    PortPtr->ClearRxBuffer();
    if (!BlockVector.empty()) {
        FOREVER {
            SAABSendRequest(PortPtr);
            if (SAABHandleAnswer(PortPtr)) {
                OS_Delay(Delay);
            }
        }
    } else {
        // We are slave
        FOREVER {
            SAABHandleRequest(PortPtr);
        }
    }
#endif
}
////////////////////////////////////////////////////////////
//
//  Handles request in Slave mode
//
////////////////////////////////////////////////////////////
void SaabProtcol::SAABHandleRequest(TSNUart *PortPtr){
    U8 Data;
    if (PortPtr->Receive(&Data, 1, 0x7fffffff)) { // wait till a character comes in
        switch (Data) {
        case 'v':    // Tank values
        case 'a':    // Tank values and alarm status
        case 'h':    // Tank high limits
        case 'l':    // Tank low limits
        case 's':    // Ship information
            SAABHandleInput(PortPtr, Data);
            break;
        case 'V':    // Tank values
        case 'A':    // Tank values and alarm status
        case 'H':    // Tank high limits
        case 'L':    // Tank low limits
        case 'S':    // Ship information
            {
                volatile bool DataAvailable;
                volatile char Data2;
                char InBuf[SAAB_BUF_SIZE] = { Data };
                int Ptr = 1;
                do {
                    DataAvailable = PortPtr->Receive((U8 *)&Data2, 1, 200); /* wait till a character comes in */
                    InBuf[Ptr++] = (char)Data2;
                }
                while ((Ptr < SAAB_BUF_SIZE) && (DataAvailable) && (Data2 != 0x0A));
                // Does it seem like a valid packet?
                if (Ptr >= SAAB_MIN_PACKET) {
                    char *EndPtr;
                    unsigned CheckSum = 0;
                    Ptr -= 6;
                    unsigned PacketCheckSum = strtoul(&InBuf[Ptr], &EndPtr, 16);
                    for (int i = 0; i < Ptr; i++) {
                        CheckSum += InBuf[i];
                    }
                    // Compare the checksum
                    if (CheckSum == PacketCheckSum) {
                        int Action = SAAB_ACT_NORMAL;
                        // Allocate a temp-buffer and set up the packet heading
                        char OutBuf[SAAB_BUF_SIZE];
                        int OutPtr = 0;
                        float Scale;
                        bool Sign;
                        int ValKey = -1;
                        int ObjType = SAAB_OBJ_ERROR;

                        switch (Data) {
                        case 'V':    // Tank values
                        case 'A':    // Tank values with alarm status
                            memcpy(OutBuf, InBuf, 6); // Copy heading
                            OutPtr = 6; // Set pointer past heading, this is the default
                            {
                                int FirstTank     = (InBuf[1] - '0') * 10 + (InBuf[2] - '0');
                                int NumberOfTanks = (InBuf[3] - '0') * 10 + (InBuf[4] - '0');
                                switch (InBuf[5]) {
                                case '1':
                                case '2':
                                case '3':
                                case '4':
                                case '5':
                                case '6':
                                    {
                                        int ExtraParameterNo = InBuf[5] - '1';
                                        if (ExtraParameterNo < (int)ExtraParameters.size()) {
                                            ValKey = ExtraParameters[ExtraParameterNo].ValueKey;
                                            Scale  = ExtraParameters[ExtraParameterNo].Scale;
                                            Sign   = ExtraParameters[ExtraParameterNo].Sign;
                                            ObjType = ExtraParameters[ExtraParameterNo].ObjType;
                                            Action = ExtraParameters[ExtraParameterNo].Action;
                                        } else {
                                            Sign      = false;
                                            Action = SAAB_ACT_ERROR;
                                        }
                                    }
                                    break;
                                case 'U':
                                    ValKey = SVT_ULLAGE; // Corrected to ref point.
                                    Scale = 1000;
                                    Sign      = false;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'C':
                                    ValKey = SVT_ULLAGE_FC;    // Corrected to FC
                                    Scale = 1000;
                                    Sign      = false;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'D':
                                    ValKey = SVT_DENSITY;
                                    Scale = 10000;
                                    Sign      = false;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'V':
                                    ValKey = SVT_VOLUME;
                                    Scale = 1;
                                    Sign      = false;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'W':
                                    ValKey = SVT_WEIGHT;
                                    Scale = 1;
                                    Sign      = false;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'E':
                                    ValKey = SVT_LOADRATE;
                                    Scale = 10;
                                    Sign      = false;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'F':
                                    ValKey = SVT_VOLPERCENT;
                                    Scale = 100;
                                    Sign      = false;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'P':
                                    ValKey = SVT_PRESSURE;
                                    Scale  = 1000;
                                    Sign   = true;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'T':
                                    ValKey = SVT_TEMP;
                                    Scale  = 10;
                                    Sign   = true;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'I':
                                    ValKey = SVT_LEVEL_SENSOR;
                                    Scale  = 1000;
                                    Sign   = false;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'u':
                                case 'i':
                                    Sign   = false;
                                    Action = SAAB_ACT_ERROR;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'R':   // Not supported
                                case 'X':
                                case 'Y':
                                case 'Z':
                                    Sign   = true;
                                    Action = SAAB_ACT_ERROR;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                default:
                                    Sign   = false;
                                    Action = SAAB_ACT_ERROR;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                }
                                switch (Action) {
                                case SAAB_ACT_NORMAL:
                                    {
                                        // I have a value I support
                                        int LastTank = FirstTank + NumberOfTanks;
                                        for (int Index = FirstTank; Index < LastTank; Index++) {
                                            PROTank *TmpPtr = (PROTank *)PROXRefObject::GetSaabObject(Index);
                                            if (TmpPtr) {
                                                int DecPnt, Unit;
                                                float Value;
                                                switch (TmpPtr->GetValue(ValKey, 0, Value, DecPnt, Unit)) {
                                                case GETVAL_NOT_AVAILABLE   :
                                                case GETVAL_TANK_EMPTY      :
                                                case GETVAL_NO_DISPLAY      :
                                                case GETVAL_ERROR           :
                                                case GETVAL_FLOAT_NOT_LEGAL :
                                                case GETVAL_INT_NOT_LEGAL   :
                                                case GETVAL_STRING_NOT_LEGAL:
                                                case GETVAL_DRY_SENSOR      :
                                                case GETVAL_DISABLED        :
                                                case GETVAL_FWD_AFT         :
                                                case GETVAL_PORT_STBD       :
                                                case GETVAL_SHIP_UPRIGHT    :
                                                    Value = 0.0;
                                                    break;
                                                default:
                                                    break;

                                                }
                                                Value *= Scale;
                                                if (Sign) {
                                                    if (Value < 0.0) Value -= 0.5;
                                                    else Value += 0.5;
                                                    OutPtr += sprintf(&OutBuf[OutPtr], "%05i", (int)Value);
                                                } else {
                                                    if (Value >= 0.0) {
                                                        Value += 0.5;
                                                    } else {
                                                        Value = 0.0;
                                                    }
                                                    unsigned UVal = (unsigned)Value;
                                                    OutPtr += sprintf(&OutBuf[OutPtr], "%05u", UVal);
                                                }
                                            } else { // If unknown tank, send just ******
                                                OutPtr += sprintf(&OutBuf[OutPtr], "E****");
                                            }
                                            switch (Data) {
                                            case 'V':
                                                break;
                                            case 'A':
                                                // Include alarm status
                                                AddAlarmStatus(OutBuf, OutPtr, Index, ObjType);
                                                break;
                                            } // End of switch
                                        } // End for loop
                                    }

                                    break;
                                case SAAB_ACT_SPECIAL:
                                    {
                                        int DecPnt, Unit;
                                        float Value;
                                        switch (PROAtmReference::PROAtmRefPtr->GetValue(ValKey, 0, Value, DecPnt, Unit)) {
                                        case GETVAL_NOT_AVAILABLE   :
                                        case GETVAL_TANK_EMPTY      :
                                        case GETVAL_NO_DISPLAY      :
                                        case GETVAL_ERROR           :
                                        case GETVAL_FLOAT_NOT_LEGAL :
                                        case GETVAL_INT_NOT_LEGAL   :
                                        case GETVAL_STRING_NOT_LEGAL:
                                        case GETVAL_DRY_SENSOR      :
                                        case GETVAL_DISABLED        :
                                        case GETVAL_FWD_AFT         :
                                        case GETVAL_PORT_STBD       :
                                        case GETVAL_SHIP_UPRIGHT    :
                                            Value = 0.0;
                                            break;
                                        default:
                                            break;

                                        }
                                        Value *= Scale;
                                        if (Value < 0.0) Value -= 0.5;
                                        else Value += 0.5;
                                        OutPtr += sprintf(&OutBuf[OutPtr], "%05i", (int)Value);
                                    }
                                    break;
                                case SAAB_ACT_ERROR:
                                default:
                                    {   // Not supported value, juste send *****
                                        // Flag that the value is invalid
                                        switch (Data) {
                                        case 'V':
                                            {
                                                int LastTank = FirstTank + NumberOfTanks;
                                                for (int Index = FirstTank; Index < LastTank; Index++) {
                                                    OutPtr += sprintf(&OutBuf[OutPtr], "*****");
                                                }
                                            }
                                            break;
                                        case 'A':
                                            {
                                                int LastTank = FirstTank + NumberOfTanks;
                                                for (int Index = FirstTank; Index < LastTank; Index++) {
                                                    OutPtr += sprintf(&OutBuf[OutPtr], "******");
                                                }
                                            }
                                        } // End switch
                                    } // End case Error
                                } // End switch

                            }   // End case 'V', 'A'

                            break;

                        case 'H':
                        case 'L':
                            memcpy(OutBuf, InBuf, 6); // Copy heading
                            OutPtr = 6; // Set pointer past heading, this is the default
                            {
                                int FirstTank     = (InBuf[1] - '0') * 10 + (InBuf[2] - '0');
                                int NumberOfTanks = (InBuf[3] - '0') * 10 + (InBuf[4] - '0');
                                switch (InBuf[5]) {
                                case 'u':
                                    switch (Data) {
                                    case 'H':
                                        ValKey = SVT_HI_ULLAGE_LIM;
                                        break;
                                    case 'L':
                                        ValKey = SVT_LO_ULLAGE_LIM;
                                        break;
                                    }
                                    Scale   = 1000;
                                    Sign    = true;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                case 'i':
                                    switch (Data) {
                                    case 'H':
                                        ValKey = SVT_HI_LEVEL_LIMIT;
                                        break;
                                    case 'L':
                                        ValKey = SVT_LO_LEVEL_LIMIT;
                                        break;
                                    }
                                    Scale   = 1000;
                                    Sign    = true;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                default:
                                    Sign      = false;
                                    Action = SAAB_ACT_ERROR;
                                    ObjType = SAAB_TANKVAL;
                                    break;
                                }
                                switch (Action) {
                                case SAAB_ACT_NORMAL:
                                    {
                                        // I have a value I support
                                        int LastTank = FirstTank + NumberOfTanks;
                                        for (int Index = FirstTank; Index < LastTank; Index++) {
                                            PROTank *TmpPtr = (PROTank *)PROXRefObject::GetSaabObject(Index);
                                            if (TmpPtr) {
                                                int DecPnt, Unit;
                                                float Value;
                                                switch (TmpPtr->GetValue(ValKey, 0, Value, DecPnt, Unit)) {
                                                case GETVAL_NOT_AVAILABLE   :
                                                case GETVAL_TANK_EMPTY      :
                                                case GETVAL_NO_DISPLAY      :
                                                case GETVAL_ERROR           :
                                                case GETVAL_FLOAT_NOT_LEGAL :
                                                case GETVAL_INT_NOT_LEGAL   :
                                                case GETVAL_STRING_NOT_LEGAL:
                                                case GETVAL_DRY_SENSOR      :
                                                case GETVAL_DISABLED        :
                                                case GETVAL_FWD_AFT         :
                                                case GETVAL_PORT_STBD       :
                                                case GETVAL_SHIP_UPRIGHT    :
                                                    Value = 0.0;
                                                    break;
                                                default:
                                                    break;

                                                }
                                                Value *= Scale;
                                                if (Sign) {
                                                    if (Value < 0.0) Value -= 0.5;
                                                    else Value += 0.5;
                                                    OutPtr += sprintf(&OutBuf[OutPtr], "%05i", (int)Value);
                                                } else {
                                                    if (Value >= 0.0) {
                                                        Value += 0.5;
                                                    } else {
                                                        Value = 0.0;
                                                    }
                                                    unsigned UVal = (unsigned)Value;
                                                    OutPtr += sprintf(&OutBuf[OutPtr], "%05u", UVal);
                                                }
                                            } else { // If unknown tank, send just ******
                                                OutPtr += sprintf(&OutBuf[OutPtr], "E****");
                                            }
                                            switch (Data) {
                                            case 'V':
                                                break;
                                            case 'A':
                                                // Include alarm status
                                                AddAlarmStatus(OutBuf, OutPtr, Index, ObjType);
                                                break;
                                            } // End of switch
                                        } // End for loop
                                    }

                                    break;
                                case SAAB_ACT_SPECIAL:
                                    {
                                        int DecPnt, Unit;
                                        float Value;
                                        switch (PROAtmReference::PROAtmRefPtr->GetValue(ValKey, 0, Value, DecPnt, Unit)) {
                                        case GETVAL_NOT_AVAILABLE   :
                                        case GETVAL_TANK_EMPTY      :
                                        case GETVAL_NO_DISPLAY      :
                                        case GETVAL_ERROR           :
                                        case GETVAL_FLOAT_NOT_LEGAL :
                                        case GETVAL_INT_NOT_LEGAL   :
                                        case GETVAL_STRING_NOT_LEGAL:
                                        case GETVAL_DRY_SENSOR      :
                                        case GETVAL_DISABLED        :
                                        case GETVAL_FWD_AFT         :
                                        case GETVAL_PORT_STBD       :
                                        case GETVAL_SHIP_UPRIGHT    :
                                            Value = 0.0;
                                            break;
                                        default:
                                            break;

                                        }
                                        Value *= Scale;
                                        if (Value < 0.0) Value -= 0.5;
                                        else Value += 0.5;
                                        OutPtr += sprintf(&OutBuf[OutPtr], "%05i", (int)Value);
                                    }
                                    break;
                                case SAAB_ACT_ERROR:
                                default:
                                    {   // Not supported value, juste send *****
                                        // Flag that the value is invalid
                                        switch (Data) {
                                        case 'V':
                                            {
                                                int LastTank = FirstTank + NumberOfTanks;
                                                for (int Index = FirstTank; Index < LastTank; Index++) {
                                                    OutPtr += sprintf(&OutBuf[OutPtr], "*****");
                                                }
                                            }
                                            break;
                                        case 'A':
                                            {
                                                int LastTank = FirstTank + NumberOfTanks;
                                                for (int Index = FirstTank; Index < LastTank; Index++) {
                                                    OutPtr += sprintf(&OutBuf[OutPtr], "******");
                                                }
                                            }
                                        } // End switch
                                    } // End case Error
                                } // End switch

                            }   // End case 'V', 'A'
                            break;
                        case 'S':
                            memcpy(OutBuf, InBuf, 2); // Copy heading
                            OutPtr = 2; // Set pointer past heading, this is the default
                            if (InBuf[1] == 'D') {
                                switch (PROSystemData::TXUSystemData->TrimSource) {
                                case C_SD_DRAFT_SOURCE:
                                case C_SD_INC_SOURCE:
                                    OutBuf[OutPtr++] = 'A';
                                    break;
                                case C_SD_MAN_SOURCE:
                                    OutBuf[OutPtr++] = 'M';
                                    break;
                                }
                                switch (PROSystemData::TXUSystemData->ListSource) {
                                case C_SD_DRAFT_SOURCE:
                                case C_SD_INC_SOURCE:
                                    OutBuf[OutPtr++] = 'A';
                                    break;
                                case C_SD_MAN_SOURCE:
                                    OutBuf[OutPtr++] = 'M';
                                    break;
                                }
                                if (PRODraftSystem::PRODraftSysPtr) {
                                    int ValKey[4] = { SVT_DF_MARK, SVT_DA_MARK, SVT_DS, SVT_DP };
                                    for (int i = 0; i < 4; i++) {
                                        int DecPnt, Unit;
                                        float Value;
                                        switch (PRODraftSystem::PRODraftSysPtr->GetValue(ValKey[i], 0, Value, DecPnt, Unit)) {
                                        case GETVAL_NOT_AVAILABLE   :
                                        case GETVAL_TANK_EMPTY      :
                                        case GETVAL_NO_DISPLAY      :
                                        case GETVAL_ERROR           :
                                        case GETVAL_FLOAT_NOT_LEGAL :
                                        case GETVAL_INT_NOT_LEGAL   :
                                        case GETVAL_STRING_NOT_LEGAL:
                                        case GETVAL_DRY_SENSOR      :
                                        case GETVAL_DISABLED        :
                                        case GETVAL_FWD_AFT         :
                                        case GETVAL_PORT_STBD       :
                                        case GETVAL_SHIP_UPRIGHT    :
                                            Value = 0.0;
                                            break;
                                        case GETVAL_NOT_MEASURED    :
                                        default                     :
                                            break;

                                        }
                                        Value *= 100.0;
                                        if (Value > 9999) {
                                            Value = 9999;
                                        }
                                        OutPtr += sprintf(&OutBuf[OutPtr], "%5i", (int)Value);
                                    }
                                } else {
                                    for (int i = 0; i < 4; i++) {
                                        OutPtr += sprintf(&OutBuf[OutPtr], "*****");
                                    }
                                }
                                // Always trim and list.
                                // Sign convention oposite of Tanksystem
                                {
                                    int ValKey[] = { SVT_TRIM_M, SVT_LIST_DEG };
                                    for (unsigned i = 0; i < NELEMENTS(ValKey); i++) {
                                        int DecPnt, Unit;
                                        float Value;
                                        switch (PROSystemData::TXUSystemData->GetValue(ValKey[i], 0, Value, DecPnt, Unit)) {
                                        case GETVAL_NOT_AVAILABLE   :
                                        case GETVAL_TANK_EMPTY      :
                                        case GETVAL_NO_DISPLAY      :
                                        case GETVAL_ERROR           :
                                        case GETVAL_FLOAT_NOT_LEGAL :
                                        case GETVAL_INT_NOT_LEGAL   :
                                        case GETVAL_STRING_NOT_LEGAL:
                                        case GETVAL_DRY_SENSOR      :
                                        case GETVAL_DISABLED        :
                                        case GETVAL_FWD_AFT         :
                                        case GETVAL_PORT_STBD       :
                                        case GETVAL_SHIP_UPRIGHT    :
                                            Value = 0.0;
                                            break;
                                        default:
                                            break;

                                        }
                                        switch (ValKey[i]) {
                                        case SVT_TRIM_M   :
                                            Value *= 1000.0;
                                            break;
                                        case SVT_LIST_ANGLE :
                                            Value = -100.0 * RAD_FACTOR;
                                            break;
                                        }
                                        if (Value > 9999) {
                                            Value = 9999;
                                        } else if (Value < -9999) {
                                            Value = -9999;
                                        }

                                        OutPtr += sprintf(&OutBuf[OutPtr], "%5i", (int)Value);

                                    }
                                }

                                // Share force and bending moment
#if defined(S2TXU) || defined(ANTDUSIM)
#pragma diag_suppress=Pe550
                                {
                                    int ValKey[] = { SVT_S_MAX_BM, SVT_S_MAX_SF };
                                    for (int i = 0; i < NELEMENTS(ValKey); i++) {
                                        OutPtr   += sprintf(&OutBuf[OutPtr], "**********");
                                    }
                                }
#else
                                {
                                    if (PROProjectInfo::PROProjectInfoPtr->IntegratedLoadingComputer && !LCShipData::Stability_Only) {
                                        int ValKey[] = { SVT_S_MAX_BM, SVT_S_MAX_SF };
                                        for (unsigned i = 0; i < NELEMENTS(ValKey); i++) {
                                            int DecPnt, Unit;
                                            float Value;
                                            switch (PROSystemData::TXUSystemData->GetValue(ValKey[i], 0, Value, DecPnt, Unit)) {
                                            case GETVAL_NOT_AVAILABLE   :
                                            case GETVAL_TANK_EMPTY      :
                                            case GETVAL_NO_DISPLAY      :
                                            case GETVAL_ERROR           :
                                            case GETVAL_FLOAT_NOT_LEGAL :
                                            case GETVAL_INT_NOT_LEGAL   :
                                            case GETVAL_STRING_NOT_LEGAL:
                                            case GETVAL_DRY_SENSOR      :
                                            case GETVAL_DISABLED        :
                                            case GETVAL_FWD_AFT         :
                                            case GETVAL_PORT_STBD       :
                                            case GETVAL_SHIP_UPRIGHT    :
                                                Value = 0.0;
                                                break;
                                            default:
                                                break;

                                            }
                                            switch (ValKey[i]) {
                                            case SVT_S_MAX_BM   :
                                                Value *= 100.0;
                                                break;
                                            case SVT_S_MAX_SF :
                                                Value =  100.0;
                                                break;
                                            }
                                            OutPtr += sprintf(&OutBuf[OutPtr], "%5i", Value);
                                        }
                                    } else {
                                        OutPtr   += sprintf(&OutBuf[OutPtr], "**********");
                                    }
                                }
#endif

                            } else {}
                            break;
                        } // End of block swicth
                          // Send if we have more than just the heading
                        if (OutPtr > 6) {
                            TSN_Delay(SAAB_DELAY);
                            SendString(PortPtr, OutBuf, OutPtr);
                        }
                    }   // end of Checksum OK
                } // End of if Valid packet
            }
            break;
        default:
            break;
        }
    }
}


