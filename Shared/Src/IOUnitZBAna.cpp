#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

#include "TSNVersion.h"
//---------------------------------------------------------------------------

ValueList IOUnitZBAna::IOUnitZBAnaValueList[] =  {
    { L_WORD304 , L_WORD237, SVT_BLANK },                              //  {"Unused"       ,"",SVT_BLANK},
    { L_WORD379 , L_WORD237, SVT_IO_COM_CHANNEL },                     //  {"Com Channel"  ,"",SVT_IO_COM_CHANNEL},
    { L_WORD24  , L_WORD237, SVT_IO_PROG_VERSION },                    //  {"ProgVersion"  ,"",SVT_IO_PROG_VERSION},
    { L_WORD380 , L_WORD237, SVT_IO_COM_VERSION },                     //  {"Com Version"  ,"",SVT_IO_COM_VERSION},
    { L_WORD381 , L_WORD237, SVT_IO_STORE_VERSION },                   //  {"Store Ver."   ,"",SVT_IO_STORE_VERSION},
    { L_WORD1130, L_WORD237, SVT_IO_BOOT_VERSION },                    //   {"ProgVersion"  ,"",SVT_IO_PROG_VERSION},
    { L_WORD382 , L_WORD237, SVT_IO_RXBUF_SIZE },                      //  {"Rx Buf Size"  ,"",SVT_IO_RXBUF_SIZE},
    { L_WORD383 , L_WORD237, SVT_IO_TXBUF_SIZE },                      //  {"Tx Buf Size"  ,"",SVT_IO_TXBUF_SIZE},
    { L_WORD384 , L_WORD237, SVT_IO_RESET_STATUS },                    //  {"Reset Status" ,"",SVT_IO_RESET_STATUS},
    { L_WORD385 , L_WORD237, SVT_IO_TOTAL_RESTARTS },                  //  {"Total Restart","",SVT_IO_TOTAL_RESTARTS},
    { L_WORD386 , L_WORD237, SVT_IO_FAIL_CNT_CHK },                    //  {"Fail count"   ,"",SVT_IO_FAIL_CNT_CHK},
    { L_WORD387 , L_WORD237, SVT_IO_FAIL_CNT_TOT },                    //  {"Tot. fail cnt","",SVT_IO_FAIL_CNT_TOT},
    { L_WORD388 , L_WORD237, SVT_IO_P_TYPE_RUNNING },                  //  {"Program"      ,"",SVT_IO_P_TYPE_RUNNING},
    { L_WORD389 , L_WORD237, SVT_IO_CARD_VOLTAGE },                    //  {"Pwr 24V"      ,"",SVT_IO_CARD_VOLTAGE},

};

set<PRogramObjectBase *>IOUnitZBAna::ObjectSet;
IOUnitZBAna::IOUnitZBAna(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr) : IOUnit(IOCompPtr->TCUPortNo) {
    ObjectSet.insert(this);
    Type        = C_IO_AN_ZBANA;
    IDNumber    = (C_IO_AN_ZBANA << 16) + ObjectSet.size();
    for (int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++) {
        Filters[i] = 0;
        Status[i] = 0;
        IOComponent[i] = NULL;
        mAValues[i] = 0.0;
    }
    TCUAddress  = IOCompPtr->TCUAddress;
    TCUPortNo   = IOCompPtr->TCUPortNo;
    IOType      = IOCompPtr->IOType;
    IOAddress   = IOCompPtr->IOAddress;
    Name = AnsiString("ZBANA:") + AnsiString(IOAddress);
    Add(IOCompPtr, ElementPtr);
    GlobalPRO_IOList.insert(this);
    ReqStatusTime = 0;
}

IOUnitZBAna::~IOUnitZBAna(void) {
    for (int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++) {
        if (IOComponent[i]) {
            //done elsewhere     delete IOComponent[i];
            IOComponent[i] = NULL;
        }
    }
    ObjectSet.erase(this);
}
//---------------------------------------------------------------------------

bool IOUnitZBAna::Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr) {

    int tmpIOChannel = IOCompPtr->IOChannel;
    if (tmpIOChannel >= 0 && tmpIOChannel < MAX_AN_ZBANA_CHANNELS) {
        if (IOComponent[tmpIOChannel]) {
            AnsiString Message = (AnsiString)"TCU " + (AnsiString)IOCompPtr->TCUAddress;
            Message += (AnsiString)" com-port " + (AnsiString)IOCompPtr->TCUPortNo + ".\n";
            Message += (AnsiString)"Channel " + (AnsiString)(tmpIOChannel + 1);
            Message += (AnsiString)" on IO " + KeyWord(IOType) + " addr." + (AnsiString)IOAddress;
            Message += (AnsiString)"\nChannel allredy used.\n Try to set sensor for ";
            Message += (AnsiString)ElementPtr->Name + ".\n";
            HardwareSetupWarning(Message);
            return (false);
        } else {
            IOComponent[tmpIOChannel] = IOCompPtr;
            PowerStatus |= 1 << tmpIOChannel;

            pair<set<PRogramObject *>::iterator, bool> Ret;
            Ret = IOUniquePROSet.insert(ElementPtr);

            if (Ret.second) {
                AddAlarms(ElementPtr->CompleteAlarmInfoList);
            }
            //((AnalogInput*)IOCompPtr)->SetPROPtr(ElementPtr);
            ElementPtr->MergeChildUserRights(this);
            IOCompPtr->AddIOMdulePtr((ANPRO10Object *)this);
        }
        return (true);
    }
    AnsiString Message = (AnsiString)"TCU " + (AnsiString)IOCompPtr->TCUAddress;
    Message += (AnsiString)" com-port " + (AnsiString)IOCompPtr->TCUPortNo + ".\n";
    Message += (AnsiString)"Channel " + (AnsiString)(IOCompPtr->IOChannel + 1);
    Message += (AnsiString)" on IO " + KeyWord(IOType) + " addr." + (AnsiString)IOAddress;
    Message += (AnsiString)".\n Not legal ZBANA Channel.\nTry to set sensor for ";
    Message += (AnsiString)ElementPtr->Name + ".\n";
    HardwareSetupWarning(Message);
    return (false);
}
//---------------------------------------------------------------------------

#ifndef ANCONF
///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int  IOUnitZBAna::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int ErrorStatus = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_IO_CH_VALUE    :
        ValueId = SVT_AI_CALC_VAL;
    case SVT_AI_GAIN        :
    case SVT_AI_OFFSET      :
    case SVT_AI_CALC_VAL    :
        {
            PROIOComponent *CompPtr = IOComponent[Index];
            if (CompPtr) {
                ErrorStatus = CompPtr->GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
            } else {
                ErrorStatus = GETVAL_NO_DISPLAY;
            }
        }
        break;
    case SVT_IO_CH_RAW_VAL:
        MyRetValue = mAValues[Index] / 1000.0;
        DecPnt     = 3;
        Unit       = CURRENT_UNIT;
        break;
    case SVT_IO_CH_STATUS :
        MyRetValue = Status[Index];
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
        //case SVT_IO_CH_CAL_VAL :
        //  MyRetValue = CalValues[Index];
        //  DecPnt     = 0;
        //  Unit       = NO_UNIT;
        //  break;
        //case SVT_IO_CH_RAW_VAL :
        //  MyRetValue = CalValues[Index];
        //  DecPnt     = 0;
        //  Unit       = NO_UNIT;
        //  break;
    default:
        ErrorStatus = IOUnit::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (ErrorStatus);
}

int IOUnitZBAna::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_IO_CH_NAME         :
        ValueId = SVT_AI_PRONAME;
    case SVT_AI_ENABLE_TEXT     :
        {
            PROIOComponent *IOCPtr = IOComponent[Index];
            if (IOCPtr) {
                Status = IOCPtr->GetStringValue(ValueId, 0, MyString);
            } else {
                MyString = "";
            }
        }
        break;
    case SVT_IO_CH_LOCATION         :
        {
            PROIOComponent *IOCPtr = IOComponent[Index];
            if (IOCPtr) {
                Status = IOCPtr->GetStringValue(SVT_AI_LOCATION, 0, MyString);
            } else {
                MyString = "";
            }
        }
        break;
    case SVT_IO_CH_TYPE_TEXT    :
        {
            PROIOComponent *IOCPtr = IOComponent[Index];
            if (IOCPtr) {
                Status = IOCPtr->GetStringValue(SVT_AI_TYPE_TEXT, 0, MyString);
            } else {
                MyString = "";
            }
        }
        break;
    default:
        Status = IOUnit::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int IOUnitZBAna::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    return (IOUnit::PutValue(ValueId, Index, NewValue, Local, UnitId));
}

int IOUnitZBAna::PutFloatValue(int ValueId, float NewValue) {
    return (IOUnit::PutFloatValue(ValueId, NewValue));
}

ValueList* IOUnitZBAna::GetValueInfoTable(int &Entries, int Index) {
    Entries = NELEMENTS(IOUnitZBAnaValueList);
    return (IOUnitZBAnaValueList);
}

//////////////////////////////////////////////////
//
// Packets for IOUnitZBAna
//
//////////////////////////////////////////////////
    #pragma pack(push,1)

struct mASgCnvMeasuredDataStruct {
    U8 Status;
    float mAmp;
};

    #pragma pack(pop)

///////////////////////////////////////////////////////////////
//
// Routines for communication
//
///////////////////////////////////////////////////////////////
void IOUnitZBAna::SetHWFailure(bool Failure) {
    if (Failure) {
        for (int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++) {
            PROIOComponent *CompPtr = IOComponent[i];
            if (CompPtr && !CompPtr->HWFailure) {
                CompPtr->HWFailure = true;
                CompPtr->SendData();
            }
        }
    }
}

    #ifdef S2TXU
bool IOUnitZBAna::ANPRO10_IO_UnpackPacket(U8 *Buf) {
    ANPRO10_PacketHeading *pPH = (ANPRO10_PacketHeading *)Buf;
    bool MyPacket = (pPH->txadr == this->IOAddress);
    if (MyPacket) {
        SetTimeStamp();
        Buf += sizeof(ANPRO10_PacketHeading);
        U8 *EndPtr =  &Buf[pPH->nob];
        ANPRO10_CommandHeading *pCH;
        bool MoreCommands = true;
        do {
            pCH = (ANPRO10_CommandHeading *)Buf;
            Buf += sizeof(ANPRO10_CommandHeading);  // ??
            switch (pCH->CommandNo) {
            case CMD_TXU_COMPRESSED_PACKET:
                //Decompress(Size,Buf,Port);
                break;
            case CMD_REP_FLASH_PROG:
                ProgrammingStatus = *Buf;
                break;
            case  CMD_REP_FLASH_ERASE:
                FlashEraseStatus = *Buf;
                break;
            case CMD_REP_STATUS:
                {
                    ANPRO10_COMMAND_1001 *CardInfo = (ANPRO10_COMMAND_1001 *)Buf;
                    CardChannel       = CardInfo->CardChannel;
                    CardId            = CardInfo->CardId;
                    CardAddress       = CardInfo->CardAddress;
                    UnitProgVersion   = CardInfo->UnitProgVersion;
                    ComVersion        = CardInfo->ComVersion;
                    StoreVersion      = CardInfo->StoreVersion;
                    RxBufSize         = CardInfo->RxBufSize;
                    TxBufSize         = CardInfo->TxBufSize;
                    if (UnitProgVersion >= VERSION_ANZB_1281_PROG_FIRST) {
                        UnitBootVersion   = CardInfo->UnitBootVersion;
                        TotalUnitRestart  = CardInfo->TotalUnitRestart;
                        if (CardInfo->ResetStatus) {
                            ResetStatus       = CardInfo->ResetStatus;
                            Restart           = true;
                        }
                    }else{
                        ResetStatus         = CardInfo->ResetStatus;
                        if (CardInfo->ResetStatus) {
                            UnitBootVersion     = 0;
                            ResetStatus         = CardInfo->ResetStatus;
                            Restart             = true;
                            TotalUnitRestart++;
                        }
                    }
                    ProgamTypeRunning = CardInfo->ProgamTypeRunning;
                }
                //SendData(CMD_GENERIC_STATIC_DATA);
                break;
            case CMD_REP_INT_DATA:
                {
                    ANPRO10_COMMAND_1091 *CardInfo = (ANPRO10_COMMAND_1091 *)Buf;
                    CardVoltage  = CardInfo->InternalAD[0] / 1024.0 * 2.56 * 16.0;
                }
                break;
            case CMD_REP_ANA_MDATA:
                {
                    U8 TmpStatus    = Buf[0] >> 4;
                    if (TmpStatus) {
                        ResetStatus = TmpStatus;
                        Restart     = true;
                    } else {
                        mASgCnvMeasuredDataStruct *MsrdData = (mASgCnvMeasuredDataStruct *)&Buf[1];
                        for (int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++) {
                            Status[i] = MsrdData[i].Status;
                            mAValues[i] = MsrdData[i].mAmp;
                            AnalogInput *CompPtr = (AnalogInput *)IOComponent[i];
                            if (CompPtr) {
                                CompPtr->SetStatus((U8 *)Status[i]);
                                CompPtr->NewValue(mAValues[i] / 1000.0); // Convert to Ampere
                                CompPtr->Calculate();
                                CompPtr->ActiveAlarms = CheckAlarms(CompPtr->AlarmSet, &CompPtr->MyHWFailure);
                                /*
                                if (!CompPtr->ActiveAlarms) {
                                    CompPtr->SetTimeStamp();
                                 }
                                */
                                CompPtr->SendData();
                            }
                        }
                    }
                }
                 // Also set time stamp on the e.g. linked tank object
                {
                    set<PRogramObject *>::iterator pBIt;
                    for (pBIt = IOUniquePROSet.begin(); pBIt != IOUniquePROSet.end(); pBIt++) {
                        (*pBIt)->SetTimeStamp();
                    }
                    
                }
                break;
            case CMD_REP_ANA_FILTER:
                break;
            case CMD_REP_ANA_SETUP:
                {
                    U16 tmpPowerStatus = (Buf[1] << 8) | Buf[0];
                    if (tmpPowerStatus != PowerStatus) {
                        Restart = true;
                    }
                }
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
    return (MyPacket);
}

void IOUnitZBAna::SendToIO(U16 Command, void *Data, U16 Size, bool RequestAck) {
    NetPacket Packet;
    Packet.Command    = Command;
    Packet.RxAddress  = IOAddress;
    Packet.RxTypeId   = DEVICE_ZBANA;
    Packet.RequestAck = RequestAck;
    Packet.Size       = Size;
    Packet.Data       = Data;
    SendPacket(Packet);
}


void IOUnitZBAna::PowerOn(void) {
#ifdef S2TXU
    SendToIO(CMD_SND_ANA_SETUP, &PowerStatus, sizeof(PowerStatus), false);
    PowerOnTime = RunningTime + POWER_ON_ZBANA_START_DELAY;
#endif
}

void IOUnitZBAna::RequestSetup(void) {
#ifdef S2TXU
    SendToIO(CMD_REQ_ANA_SETUP, NULL, 0, false);
#endif
}



void IOUnitZBAna::HandleIO(int Delay) {
    time_t MyCurentTime = RunningTime;
    if (Restart) {
        Request(CMD_REQ_STATUS);
        if (ANPRO10_IO_Receive()) {
            SetFilters();
            TSN_Delay(Delay);
            PowerOn();
            TSN_Delay(Delay);
            Restart = false;
        }
    } else if (MyCurentTime > (PowerOnTime)) {
        Request(CMD_REQ_ANA_DATA);
        ANPRO10_IO_Receive();
        TSN_Delay(Delay);
        if (MyCurentTime > ReqStatusTime) {
            ReqStatusTime = MyCurentTime + IO_STATUS_REQ_DELAY;
            Request(CMD_REQ_INT_DATA);
            ANPRO10_IO_Receive();
            TSN_Delay(Delay);
            Request(CMD_REQ_STATUS);
            ANPRO10_IO_Receive();
            TSN_Delay(Delay);
            RequestSetup();
            ANPRO10_IO_Receive();
            if (!ActiveAlarms) {
                switch (ProgamTypeRunning) {
                case 0:
                    UpdateProgram();
                    break;
                case 1:
                    if (UnitProgVersion <= 41) {
                        if ((UnitProgVersion != VERSION_ANZB_128_PROG) || (ComVersion  != VERSION_ANZB_COMP) || (StoreVersion != VERSION_ANZB_EEPROM)) {
                            UpdateProgram();
                        }
                    } else if (UnitProgVersion > 100) {
                        if ((UnitProgVersion != VERSION_ANZB_1281_PROG) || (ComVersion  != VERSION_ANZB_COMP) || (StoreVersion != VERSION_ANZB_EEPROM)) {
                            UpdateProgram();
                        }
                    }
                    break;
                }
            }
        }
    }
    ActiveAlarms = CheckAlarms(AlarmSet);
    SetHWFailure(bool(ActiveAlarms));
    SendData();
    TSN_Delay(Delay);
}


void IOUnitZBAna::SetFilters(void) {
    U8 Filters[MAX_AN_ZBANA_CHANNELS];

    for (int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++) {
        if (IOComponent[i]) {
            Filters[i] = IOComponent[i]->GetFilter();
        } else {
            Filters[i] = FILTER_DEFAULT;
        }
    }
    NetPacket Packet;
    Packet.Command    = CMD_SND_ANA_FILTER;
    Packet.RxAddress  = IOAddress;
    Packet.RxTypeId   = DEVICE_ZBANA;
    Packet.RequestAck = 0;
    Packet.Size       = sizeof(Filters);
    Packet.Data       = (U8 *)Filters;
    SendPacket(Packet);
}

    #endif
int IOUnitZBAna::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch (pCH->CommandNo) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2601  *pData = (ANPRO10_COMMAND_2601 *)data;
            PowerStatus   = pData->PowerStatus;
            FailCnt      = pData->FailCnt;
            FailCntTotal = pData->FailCntTotal;
            for (int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++) {
                mAValues[i] = pData->mAValues[i];
                Status[i] = pData->Status[i];
            }
            ErrorStatus =  E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA :
        {
            ANPRO10_COMMAND_2602  *pData = (ANPRO10_COMMAND_2602 *)data;
            CardChannel      = pData->CardChannel;
            CardId           = pData->CardId;
            CardAddress      = pData->CardAddress;
            if (pCH->ndb < sizeof(ANPRO10_COMMAND_2602)) {
                UnitBootVersion = 0;
            }else{
                UnitBootVersion  = pData->UnitBootVersion;
            }
            UnitProgVersion  = pData->UnitProgVersion;
            ComVersion       = pData->ComVersion;
            StoreVersion     = pData->StoreVersion;
            RxBufSize        = pData->RxBufSize;
            TxBufSize        = pData->TxBufSize;
            ResetStatus      = pData->ResetStatus;
            ProgamTypeRunning = pData->ProgamTypeRunning;
            TotalUnitRestart = pData->TotalUnitRestart;
            CardVoltage      = pData->CardVoltage;
            ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int IOUnitZBAna::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch (cmd) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            QueueANPRO10_COMMAND_2601 Cmd;
            Cmd.TxInfo.Port        = NULL;
            Cmd.TxInfo.rxAddr      = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId        = DEVICE_BROADCAST_TXU;

            Cmd.Data.ObjectId      = IDNumber;
            Cmd.Data.ndb           = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo     = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.PowerStatus   = PowerStatus;
            Cmd.Data.FailCnt       = FailCnt;
            Cmd.Data.FailCntTotal  = FailCntTotal;
            for (int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++) {
                Cmd.Data.mAValues[i] = mAValues[i];
                Cmd.Data.Status[i] = Status[i];
            }
            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2602 Cmd;
            Cmd.TxInfo.Port           = NULL;
            Cmd.TxInfo.rxAddr         = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId           = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId         = IDNumber;
            Cmd.Data.ndb              = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo        = CMD_GENERIC_STATIC_DATA;
            Cmd.Data.CardChannel      = CardChannel;
            Cmd.Data.CardId           = CardId;
            Cmd.Data.CardAddress      = CardAddress;
            Cmd.Data.UnitProgVersion  = UnitProgVersion;
            Cmd.Data.ComVersion       = ComVersion;
            Cmd.Data.StoreVersion     = StoreVersion;
            Cmd.Data.RxBufSize        = RxBufSize;
            Cmd.Data.TxBufSize        = TxBufSize;
            Cmd.Data.ResetStatus      = ResetStatus;
            Cmd.Data.ProgamTypeRunning = ProgamTypeRunning;
            Cmd.Data.TotalUnitRestart =  TotalUnitRestart;
            Cmd.Data.CardVoltage      = CardVoltage;
            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}
#endif
//-----------------------------------------------------------------------------
int IOUnitZBAna::GetRequestNumber(void) {
    return 1;
}


