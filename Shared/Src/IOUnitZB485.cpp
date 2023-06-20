#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

#include "TSNVersion.h"
set<PRogramObjectBase *>IOUnitZB485::ObjectSet;

//---------------------------------------------------------------------------


ValueList IOUnitZB485::IOUnitZB485ValueList[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },                               //   {"Unused"       ,"",SVT_BLANK},
    { L_WORD379, L_WORD237, SVT_IO_COM_CHANNEL },                      //   {"Com Channel"  ,"",SVT_IO_COM_CHANNEL},
    { L_WORD24, L_WORD237, SVT_IO_PROG_VERSION },                     //   {"ProgVersion"  ,"",SVT_IO_PROG_VERSION},
    { L_WORD380, L_WORD237, SVT_IO_COM_VERSION },                      //   {"Com Version"  ,"",SVT_IO_COM_VERSION},
    { L_WORD381, L_WORD237, SVT_IO_STORE_VERSION },                    //   {"Store Ver."   ,"",SVT_IO_STORE_VERSION},
    { L_WORD382, L_WORD237, SVT_IO_RXBUF_SIZE },                       //   {"Rx Buf Size"  ,"",SVT_IO_RXBUF_SIZE},
    { L_WORD383, L_WORD237, SVT_IO_TXBUF_SIZE },                       //   {"Tx Buf Size"  ,"",SVT_IO_TXBUF_SIZE},
    { L_WORD384, L_WORD237, SVT_IO_RESET_STATUS },                     //   {"Reset Status" ,"",SVT_IO_RESET_STATUS},
    { L_WORD385, L_WORD237, SVT_IO_TOTAL_RESTARTS },                   //   {"Total Restart","",SVT_IO_TOTAL_RESTARTS},
    { L_WORD386, L_WORD237, SVT_IO_FAIL_CNT_CHK },                     //   {"Fail count"   ,"",SVT_IO_FAIL_CNT_CHK},
    { L_WORD387, L_WORD237, SVT_IO_FAIL_CNT_TOT },                     //   {"Tot. fail cnt","",SVT_IO_FAIL_CNT_TOT},
    { L_WORD388, L_WORD237, SVT_IO_P_TYPE_RUNNING },                   //   {"Program"      ,"",SVT_IO_P_TYPE_RUNNING},
    { L_WORD389, L_WORD237, SVT_IO_CARD_VOLTAGE },                     //   {"Pwr 24V"      ,"",SVT_IO_CARD_VOLTAGE},

};

IOUnitZB485::IOUnitZB485(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr) : IOUnit(IOCompPtr->TCUPortNo) {
    ObjectSet.insert(this);
    Type        = C_IO_AN_ZB485;
    IDNumber    = (C_IO_AN_ZB485 << 16) + ObjectSet.size();
    SCType[0] = 0;    // All channels set to standard ADConverter
    SCType[1] = 0;    // All channels set to standard ADConverter
    for ( int i = 0; i < MAX_AN_ZB485_CHANNELS; i++ ) {
        SConverter[i] = NULL;
    }
    TCUAddress  = IOCompPtr->TCUAddress;
    TCUPortNo   = IOCompPtr->TCUPortNo;
    IOType      = IOCompPtr->IOType;
    IOAddress   = IOCompPtr->IOAddress;
    Name        = "ZB485:" + (AnsiString)IOAddress;
    Add(IOCompPtr, ElementPtr);
    DownloadEEPROMTime[0] = 0;
    DownloadEEPROMTime[1] = 0;
}

IOUnitZB485::~IOUnitZB485(void) {

    /*
     for ( int i=0; i < MAX_AN_ZB485_CHANNELS; i++ ) {
         if ( SConverter[i] ) delete SConverter[i];
         SConverter[i] = NULL;
     }
     */
    ObjectSet.erase(this);
}
//---------------------------------------------------------------------------

bool IOUnitZB485::Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr) {
    bool Error = false;
    int tmpIOChannel = IOCompPtr->IOChannel;
    if ( tmpIOChannel >= 0 && tmpIOChannel < MAX_AN_ZB485_CHANNELS ) {
        SignalConverter *SConvPtr = SConverter[tmpIOChannel];
        if ( SConvPtr ) {
            switch ( IOCompPtr->Type ) {
            case C_AI_P906_0110         :
            case C_AI_P906_0111         :
            case C_AI_1728              :
            case C_AI_Pt100             :
            case C_AI_Pt1000            :
            case C_AI_TEMP_AD590        :
            case C_AI_LeSw_ADCard       :
                {
                    SCADCard *SCADPtr = (SCADCard *)SConverter[tmpIOChannel];
                    if ( SCADPtr->IOComponent[IOCompPtr->ADCardChannel] ) {
                        AnsiString Message = (AnsiString)"TCU " + (AnsiString)IOCompPtr->TCUAddress;
                        Message += (AnsiString)" com-port " + (AnsiString)IOCompPtr->TCUPortNo + ".\n";
                        Message += (AnsiString)"Channel " + (AnsiString)(IOCompPtr->ADCardChannel + 1);
                        Message += (AnsiString)" on ADCard on channel" + (AnsiString)(IOCompPtr->IOChannel + 1);
                        Message += (AnsiString)" on IO " + KeyWord(IOType) + " addr." + (AnsiString)IOAddress;
                        Message += (AnsiString)"\nChannel allredy used.\n Try to set sensor for ";
                        Message += (AnsiString)ElementPtr->Name + ".\n";
                        HardwareSetupWarning(Message);
                        Error = true;
                    } else {
                        Error = !SCADPtr->Add(IOCompPtr, ElementPtr);
                    }
                }
                break;
            case C_AI_WashTrackSensor      :
                {
                    SCADCard *SCADPtr = (SCADCard *)SConverter[tmpIOChannel];
                    if ( SCADPtr->IOComponentWT[IOCompPtr->ADCardChannel] ) {
                        AnsiString Message = (AnsiString)"TCU " + (AnsiString)IOCompPtr->TCUAddress;
                        Message += (AnsiString)" com-port " + (AnsiString)IOCompPtr->TCUPortNo + ".\n";
                        Message += (AnsiString)"Channel " + (AnsiString)(IOCompPtr->ADCardChannel + 1);
                        Message += (AnsiString)" on ADCard on channel" + (AnsiString)(IOCompPtr->IOChannel + 1);
                        Message += (AnsiString)" on IO " + KeyWord(IOType) + " addr." + (AnsiString)IOAddress;
                        Message += (AnsiString)"\nChannel allredy used.\n Try to set sensor for ";
                        Message += (AnsiString)ElementPtr->Name + ".\n";
                        HardwareSetupWarning(Message);
                        Error = true;
                    } else {
                        Error = !SCADPtr->Add(IOCompPtr, ElementPtr);
                    }
                }
                break;
            case C_AI_WATERINGRESS      :
            case C_AI_WATERINGR_MAIN    :
            case C_AI_WATERINGR_PRE     :
            case C_AI_WATERINGR_TEMP    :
            case C_AI_WATERINGR_TEMP_M  :
            case C_AI_WATERINGR_TEMP_P  :
                {
                    SCWaterIngress *SCADPtr = (SCWaterIngress *)SConverter[tmpIOChannel];
                    if ( SCADPtr->IOComponent[IOCompPtr->ADCardChannel] ) {
                        AnsiString Message = (AnsiString)"TCU " + (AnsiString)IOCompPtr->TCUAddress;
                        Message += (AnsiString)" com-port " + (AnsiString)IOCompPtr->TCUPortNo + ".\n";
                        Message += (AnsiString)"Channel " + (AnsiString)(IOCompPtr->ADCardChannel + 1);
                        Message += (AnsiString)" on WIS on channel" + (AnsiString)(IOCompPtr->IOChannel + 1);
                        Message += (AnsiString)" on IO " + KeyWord(IOType) + " addr." + (AnsiString)IOAddress;
                        Message += (AnsiString)"\nChannel allredy used.\n Try to set sensor for ";
                        Message += (AnsiString)ElementPtr->Name + ".\n";
                        HardwareSetupWarning(Message);
                        Error = true;
                    } else {
                        Error = !SCADPtr->Add(IOCompPtr, ElementPtr);
                    }
                }
                break;
            case C_AI_INCLINOMETER  :
            case C_AI_INC1_N2       :
            case C_AI_INC2_N2       :
            case C_AI_INC1_MACRON   :
            case C_AI_INC2_MACRON   :
            default:
                {
                    AnsiString Message = (AnsiString)"TCU " + (AnsiString)IOCompPtr->TCUAddress;
                    Message += (AnsiString)" com-port " + (AnsiString)IOCompPtr->TCUPortNo + ".\n";
                    Message += (AnsiString)"Channel " + (AnsiString)(IOCompPtr->IOChannel + 1);
                    Message += (AnsiString)" on IO " + KeyWord(IOType) + " addr." + (AnsiString)IOAddress;
                    Message += (AnsiString)" Not legal.\n Try to set sensor for ";
                    Message += (AnsiString)ElementPtr->Name + ".\n";
                    HardwareSetupWarning(Message);
                    Error = true;
                }
                break;
            }
        } else {
            switch ( IOCompPtr->Type ) {
            case C_AI_1728              :
            case C_AI_P906_0111         :
            case C_AI_ATM_N_Ex          :
            case C_AI_ATM_Ex            :
            case C_AI_ATM_Ex_H          :
            case C_AI_ATM_N_Ex_0_1      :
            case C_AI_APT500		  :
            case C_AI_SPT900		  :
            case C_AI_Gen_4_20mA        :
            case C_AI_Radar_4_20mA      :
            case C_AI_Float_4_20mA      :
            case C_AI_Pt100             :
            case C_AI_Pt1000            :
            case C_AI_TEMP_mA           :
            case C_AI_TEMP_AD590        :
            case C_AI_LeSw_ADCard       :
            case C_AI_DIFF_PRESSURE_mA  :
            case C_AI_WashTrackSensor      :
                SConvPtr = new SCADCard(IOCompPtr, ElementPtr, this);
                SConvPtr->Add(IOCompPtr, ElementPtr);
                break;
            case C_AI_WATERINGRESS      :
            case C_AI_WATERINGR_MAIN    :
            case C_AI_WATERINGR_PRE     :
            case C_AI_WATERINGR_TEMP    :
            case C_AI_WATERINGR_TEMP_M  :
            case C_AI_WATERINGR_TEMP_P  :
                SConvPtr = new SCWaterIngress(IOCompPtr, ElementPtr, this);
                SConvPtr->Add(IOCompPtr, ElementPtr);
                if ( tmpIOChannel < 4 ) {
                    SCType[0] |= 0x01 << (2 * tmpIOChannel);
                } else {
                    SCType[1] |= 0x01 << (2 * (tmpIOChannel - 4));
                }
                //SCType |= 2 << 2 * tmpIOChannel;
                break;
            case C_AI_GODA_RADAR        :
                SConvPtr = new SCWaterIngress(IOCompPtr, ElementPtr, this);
                SConvPtr->Add(IOCompPtr, ElementPtr);
                if ( tmpIOChannel < 4 ) {
                    SCType[0] |= 0x02 << (2 * tmpIOChannel);
                } else {
                    SCType[1] |= 0x02 << (2 * (tmpIOChannel - 4));
                }
                break;
            case C_AI_INCLINOMETER      :
            case C_AI_INC1_N2           :
            case C_AI_INC2_N2           :
            default:
                {
                    AnsiString Message = (AnsiString)"TCU " + (AnsiString)IOCompPtr->TCUAddress;
                    Message += (AnsiString)" com-port " + (AnsiString)IOCompPtr->TCUPortNo + ".\n";
                    Message += (AnsiString)"Channel " + (AnsiString)(IOCompPtr->IOChannel + 1);
                    Message += (AnsiString)" on IO " + KeyWord(IOType) + " addr." + (AnsiString)IOAddress;
                    Message += (AnsiString)" Not legal.\n Try to set sensor for ";
                    Message += (AnsiString)ElementPtr->Name + ".\n";
                    HardwareSetupWarning(Message);
                    Error = true;
                }
                break;
            }
            if ( !Error ) {
                SConverter[tmpIOChannel] = SConvPtr;
            }
        }
    } else {
        AnsiString Message = (AnsiString)"TCU " + (AnsiString)IOCompPtr->TCUAddress;
        Message += (AnsiString)" com-port " + (AnsiString)IOCompPtr->TCUPortNo + ".\n";
        Message += (AnsiString)"Channel " + (AnsiString)(IOCompPtr->IOChannel + 1);
        Message += (AnsiString)" on IO " + KeyWord(IOType) + " addr." + (AnsiString)IOAddress;
        Message += (AnsiString)".\n Not legal ZB485 Channel.\n Try to set sensor for ";
        Message += (AnsiString)ElementPtr->Name + ".\n";
        HardwareSetupWarning(Message);
        Error = true;
    }
    if ( !Error ) {
        pair<set<PRogramObject *>::iterator, bool> Ret;
        Ret = IOUniquePROSet.insert(ElementPtr);

        if ( Ret.second ) {
            AddAlarms(ElementPtr->CompleteAlarmInfoList);
        }
        PowerStatus |= 1 << tmpIOChannel;
        IOCompPtr->AddIOMdulePtr((ANPRO10Object *)this);
        ElementPtr->MergeChildUserRights(this);
    }
    return (!Error);
}
//---------------------------------------------------------------------------

#ifndef ANCONF
///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int  IOUnitZB485::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    return (IOUnit::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit));
}

int IOUnitZB485::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    return (IOUnit::GetStringValue(ValueId, Index, MyString));
}

int IOUnitZB485::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    return (IOUnit::PutValue(ValueId, Index, NewValue, Local, UnitId));
}

int IOUnitZB485::PutFloatValue(int ValueId, float NewValue) {
    return (IOUnit::PutFloatValue(ValueId, NewValue));
}

ValueList* IOUnitZB485::GetValueInfoTable(int &Entries, int Index) {
    Entries = NELEMENTS(IOUnitZB485ValueList);
    return (IOUnitZB485ValueList);
}


///////////////////////////////////////////////////////////////
//
// Routines for communication
//
///////////////////////////////////////////////////////////////


bool IOUnitZB485::ANPRO10_IO_UnpackPacket(U8 *Buf) {
    ANPRO10_PacketHeading *pPH = (ANPRO10_PacketHeading *)Buf;
    Buf += sizeof(ANPRO10_PacketHeading);

    ANPRO10_CommandHeading *pCH;
    //bool RecalcTanks=false;
    bool MyPacket = (pPH->txadr == this->IOAddress);
    if ( MyPacket ) {
        do {
            pCH = (ANPRO10_CommandHeading *)Buf;
            Buf += sizeof(ANPRO10_CommandHeading);  // ??
            switch ( pCH->CommandNo ) {
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
                    ProgamTypeRunning = CardInfo->ProgamTypeRunning;
                    if ( CardInfo->ResetStatus ) {
                        Restart         = true;
                        ResetStatus     = CardInfo->ResetStatus;
                        TotalUnitRestart++;
                    }
                }
                SendData(CMD_GENERIC_STATIC_DATA);
                break;
            case CMD_REP_INT_DATA:
                {
                    ANPRO10_COMMAND_1091 *CardInfo = (ANPRO10_COMMAND_1091 *)Buf;
                    CardVoltage  = CardInfo->InternalAD[0] / 1024.0 * 2.56 * 16.0;
                }
                break;
            case CMD_REP_ANA_SETUP:
                break;
            default:
                break;

            }
            Buf += pCH->ndb;
        } while ( (pCH->CommandNo != ECMD_NMDWOACK) && (pCH->CommandNo != ECMD_NMDRQACK) );
    }
    return (MyPacket);

}

void IOUnitZB485::SendToIO(U16 Command, void *Data, U16 Size, bool RequestAck) {
    NetPacket Packet;
    Packet.Command    = Command;
    Packet.RxAddress  = IOAddress;
    Packet.RxTypeId   = DEVICE_ZB485;
    Packet.RequestAck = RequestAck;
    Packet.Size       = Size;
    Packet.Data       = Data;
    SendPacket(Packet);
}

void IOUnitZB485::PowerOn(void) {
#ifdef S2TXU
    U8 Data[3] = { (U8)PowerStatus, SCType[0], SCType[1] };

    SendToIO(CMD_SND_RS4_SETUP, Data, sizeof(Data), false);
    PowerOnTime = RunningTime;
#endif
}

void IOUnitZB485::PowerOff(int Ch) {
#ifdef S2TXU
    U8 tmpPowerStatus = PowerStatus & ~(1 << Ch);
    U8 Data[3] = { tmpPowerStatus, SCType[0], SCType[1] };

    SendToIO(CMD_SND_RS4_SETUP, Data, sizeof(Data), false);
    //PowerOnTime = RunningTime;
#endif
}



void IOUnitZB485::HandleIO(int Delay) {
#ifdef S2TXU
    time_t MyCurentTime = RunningTime;
    if ( Restart ) {
        Request(CMD_REQ_STATUS);
        if ( ANPRO10_IO_Receive() ) {
            PowerOn();
            Restart = false;
            TSN_Delay(Delay);
        }
    } else {
        for ( int i = 0; i < MAX_AN_ZB485_CHANNELS; i++ ) {
            SignalConverter *SgCnvPtr = SConverter[i];
            if ( SgCnvPtr ) {
                SgCnvPtr->HandleCard(Delay);
                TSN_Delay(Delay);
                if ( SgCnvPtr->ForcePowerOff ) {
                    SgCnvPtr->ForcePowerOff = false;
                    PowerOff(i);
                    TSN_Delay(1000);
                    PowerOn();
                }
            }
        }
        if ( MyCurentTime > ReqStatusTime ) {
            ReqStatusTime = MyCurentTime + IO_STATUS_REQ_DELAY;
            Request(CMD_REQ_INT_DATA);
            ANPRO10_IO_Receive();
            TSN_Delay(Delay);
            Request(CMD_REQ_STATUS);
            ANPRO10_IO_Receive();
            TSN_Delay(Delay);
            if ( !ActiveAlarms ) {
                switch ( ProgamTypeRunning ) {
                case 0:
                    UpdateProgram();
                    break;
                case 1:
                    if ( UnitProgVersion <= 41 ) {
                        if (  (UnitProgVersion != VERSION_ANZB_PROG) || (ComVersion  != VERSION_ANZB_COMP) || (StoreVersion != VERSION_ANZB_EEPROM) ) {
                            UpdateProgram();
                        }
                    } else if ( UnitProgVersion > 100 ) {
                        if (  (UnitProgVersion != VERSION_ANZB_NEW_PROG) || (ComVersion  != VERSION_ANZB_NEW_COMP) || (StoreVersion != VERSION_ANZB_NEW_EEPROM) ) {
                            UpdateProgram();
                        }

                    }
                    break;
                }
            }
        }
    }
    ActiveAlarms = CheckAlarms(AlarmSet);
    SendData();

    if ( ActiveAlarms ) {
        for ( int i = 0; i < MAX_AN_ZB485_CHANNELS; i++ ) {
            SignalConverter *SgCnvPtr = SConverter[i];
            if ( SgCnvPtr ) {
                SgCnvPtr->SetHWFailure(true);
            }
        }
    }
#endif
}

int IOUnitZB485::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2610  *pData = (ANPRO10_COMMAND_2610 *)data;
            PowerStatus   = pData->PowerStatus;
            FailCnt      = pData->FailCnt;
            FailCntTotal = pData->FailCntTotal;
            ErrorStatus =  E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA    :
        {
            ANPRO10_COMMAND_2611  *pData = (ANPRO10_COMMAND_2611 *)data;
            CardChannel      = pData->CardChannel;
            CardId           = pData->CardId;
            CardAddress      = pData->CardAddress;
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

int IOUnitZB485::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2610 Cmd;

            Cmd.TxInfo.Port        = NULL;
            Cmd.TxInfo.rxAddr      = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId        = DEVICE_BROADCAST_TXU;

            Cmd.Data.ObjectId      = IDNumber;
            Cmd.Data.ndb           = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo     = CMD_GENERIC_REALTIME_DATA;

            Cmd.Data.PowerStatus   = PowerStatus;
            Cmd.Data.FailCnt      = FailCnt;
            Cmd.Data.FailCntTotal = FailCntTotal;
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA   :
        {
            QueueANPRO10_COMMAND_2611 Cmd;

            Cmd.TxInfo.Port           = NULL;
            Cmd.TxInfo.rxAddr         = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId           = DEVICE_BROADCAST_TXU;

            Cmd.Data.ObjectId         = IDNumber;
            Cmd.Data.ndb              = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo        = CMD_GENERIC_STATIC_DATA;
            //int Size = sizeof(Cmd);
            Cmd.Data.CardChannel      =  CardChannel;
            Cmd.Data.CardId           =  CardId;
            Cmd.Data.CardAddress      =  CardAddress;
            Cmd.Data.UnitProgVersion  =  UnitProgVersion;
            Cmd.Data.ComVersion       =  ComVersion;
            Cmd.Data.StoreVersion     =  StoreVersion;
            Cmd.Data.RxBufSize        =  RxBufSize;
            Cmd.Data.TxBufSize        =  TxBufSize;
            Cmd.Data.ResetStatus      =  ResetStatus;
            Cmd.Data.ProgamTypeRunning =  ProgamTypeRunning;
            Cmd.Data.TotalUnitRestart =  TotalUnitRestart;
            Cmd.Data.CardVoltage      =  CardVoltage;
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus =  E_QUEUE_FULL;
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
int IOUnitZB485::GetRequestNumber(void) {
    int Cnt = 0;
    for ( int i = 0; i < MAX_AN_ZB485_CHANNELS; i++ ) {
        if ( SConverter[i] ) {
            Cnt++;
        }
    }
    return Cnt;
}

