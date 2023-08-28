#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

#include "TSNVersion.h"
//---------------------------------------------------------------------------

ValueList IOUnitZBHart::IOUnitZBHartValueList[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },                              //  {"Unused"       ,"",SVT_BLANK},
    { L_WORD379, L_WORD237, SVT_IO_COM_CHANNEL },                     //  {"Com Channel"  ,"",SVT_IO_COM_CHANNEL},
    { L_WORD24, L_WORD237, SVT_IO_PROG_VERSION },                    //  {"ProgVersion"  ,"",SVT_IO_PROG_VERSION},
    { L_WORD380, L_WORD237, SVT_IO_COM_VERSION },                     //  {"Com Version"  ,"",SVT_IO_COM_VERSION},
    { L_WORD381, L_WORD237, SVT_IO_STORE_VERSION },                   //  {"Store Ver."   ,"",SVT_IO_STORE_VERSION},
    { L_WORD382, L_WORD237, SVT_IO_RXBUF_SIZE },                      //  {"Rx Buf Size"  ,"",SVT_IO_RXBUF_SIZE},
    { L_WORD383, L_WORD237, SVT_IO_TXBUF_SIZE },                      //  {"Tx Buf Size"  ,"",SVT_IO_TXBUF_SIZE},
    { L_WORD384, L_WORD237, SVT_IO_RESET_STATUS },                    //  {"Reset Status" ,"",SVT_IO_RESET_STATUS},
    { L_WORD385, L_WORD237, SVT_IO_TOTAL_RESTARTS },                  //  {"Total Restart","",SVT_IO_TOTAL_RESTARTS},
    { L_WORD386, L_WORD237, SVT_IO_FAIL_CNT_CHK },                    //  {"Fail count"   ,"",SVT_IO_FAIL_CNT_CHK},
    { L_WORD387, L_WORD237, SVT_IO_FAIL_CNT_TOT },                    //  {"Tot. fail cnt","",SVT_IO_FAIL_CNT_TOT},
    { L_WORD388, L_WORD237, SVT_IO_P_TYPE_RUNNING },                  //  {"Program"      ,"",SVT_IO_P_TYPE_RUNNING},
    { L_WORD389, L_WORD237, SVT_IO_CARD_VOLTAGE },                    //  {"Pwr 24V"      ,"",SVT_IO_CARD_VOLTAGE},

};

set<PRogramObjectBase *>IOUnitZBHart::ObjectSet;
IOUnitZBHart::IOUnitZBHart(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr) : IOUnitZBAna(IOCompPtr, ElementPtr) {
    ObjectSet.insert(this);
    Type        = C_IO_AN_ZBHART;
    IDNumber    = (C_IO_AN_ZBHART << 16) + ObjectSet.size();
    for ( int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++ ) {
        Filters[i]      = 0;
        Status[i]       = 0;
        IOComponent[i]  = NULL;
        mAValues[i]     = 0.0;
    }
    TCUAddress  = IOCompPtr->TCUAddress;
    TCUPortNo   = IOCompPtr->TCUPortNo;
    IOType      = IOCompPtr->IOType;
    IOAddress   = IOCompPtr->IOAddress;
    Name = AnsiString("ZBHart:") + AnsiString(IOAddress);
    Add(IOCompPtr, ElementPtr);
    GlobalPRO_IOList.insert(this);
    ReqStatusTime = 0;
}

IOUnitZBHart::~IOUnitZBHart(void) {
    for ( int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++ ) {
        if ( IOComponent[i] ) {
            //done elsewhere     delete IOComponent[i];
            IOComponent[i] = NULL;
        }
    }
    ObjectSet.erase(this);
}
//---------------------------------------------------------------------------

bool IOUnitZBHart::Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr) {

    int tmpIOChannel = IOCompPtr->IOChannel;
    if ( tmpIOChannel >= 0 && tmpIOChannel < MAX_AN_ZBANA_CHANNELS ) {
        if ( IOComponent[tmpIOChannel] ) {
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

            if ( Ret.second ) {
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
    Message += (AnsiString)".\n Not legal ZBHart Channel.\nTry to set sensor for ";
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

int  IOUnitZBHart::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int ErrorStatus = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_IO_CH_HART_FAIL_COUNT1 :
        MyRetValue = FailCnt1[Index];
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_IO_CH_HART_FAIL_COUNT2 :
        MyRetValue = FailCnt2[Index];
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    default:
        ErrorStatus = IOUnitZBAna::GetValue(ValueId,Index, MyRetValue,  DecPnt,Unit);
        break;
    }
    return(ErrorStatus);
}

int IOUnitZBHart::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    default:
        Status = IOUnitZBAna::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int IOUnitZBHart::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    return (IOUnitZBAna::PutValue(ValueId, Index, NewValue, Local, UnitId));
}

int IOUnitZBHart::PutFloatValue(int ValueId, float NewValue) {
    return (IOUnitZBAna::PutFloatValue(ValueId, NewValue));
}

ValueList* IOUnitZBHart::GetValueInfoTable(int &Entries, int Index) {
    Entries = NELEMENTS(IOUnitZBHartValueList);
    return (IOUnitZBHartValueList);
}

//////////////////////////////////////////////////
//
// Packets for IOUnitZBHart
//
//////////////////////////////////////////////////
    #pragma pack(push,1)
struct mAHartMeasuredDataStruct {
    short FailCnt1;
    short FailCnt2;
    float Distance;
    float Level;
    float ADCurrent;
};

    #pragma pack(pop)

///////////////////////////////////////////////////////////////
//
// Routines for communication
//
///////////////////////////////////////////////////////////////
    #ifdef S2TXU
bool IOUnitZBHart::ANPRO10_IO_UnpackPacket(U8 *Buf) {
    ANPRO10_PacketHeading *pPH = (ANPRO10_PacketHeading *)Buf;
    bool MyPacket = (pPH->txadr == this->IOAddress);
    if ( MyPacket ) {
        SetTimeStamp();
        Buf += sizeof(ANPRO10_PacketHeading);
        U8 *EndPtr =  &Buf[pPH->nob];
        ANPRO10_CommandHeading *pCH;
        bool MoreCommands = true;
        bool RecalcTanks  = false;
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
                    TotalUnitRestart  = CardInfo->TotalUnitRestart;
                    if ( CardInfo->ResetStatus ) {
                        Restart         = true;
                        ResetStatus     = CardInfo->ResetStatus;
                        //TotalUnitRestart++;
                    }
                    ProgamTypeRunning = CardInfo->ProgamTypeRunning;
                }
                SendData(CMD_GENERIC_STATIC_DATA);
                break;
            case CMD_REP_INT_DATA:
                {
                    ANPRO10_COMMAND_1091 *CardInfo = (ANPRO10_COMMAND_1091 *)Buf;
                    CardVoltage  = CardInfo->InternalAD[0]*16.0*5.0 / 1024.0; // With externalk referance 5V With internal referance / 1024.0 * 2.56 * 16.0;
                }
                break;
            case CMD_REP_HART_MDATA:
                {

                    U8 TmpStatus    = Buf[0] >> 4;
                    if ( TmpStatus ) {
                        ResetStatus = TmpStatus;
                        Restart     = true;
                    } else {
                        mAHartMeasuredDataStruct *MsrdData = (mAHartMeasuredDataStruct *)&Buf[1];
                        for ( int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++ ) {
                            FailCnt1[i] = MsrdData[i].FailCnt1;
                            FailCnt2[i] = MsrdData[i].FailCnt2;
                            mAValues[i] = MsrdData[i].ADCurrent;
                            Distance[i] = MsrdData[i].Distance;
                            Level[i]    = MsrdData[i].Level;
                            AnalogInput *CompPtr = (AnalogInput*)IOComponent[i];
                            if ( CompPtr ) {
                                //CompPtr->SetStatus((U8 *)Status[i]);
                                switch ( CompPtr->Type ) {
                                case C_AI_Radar_Hart:
                                    CompPtr->NewValue(Distance[i]);
                                    CompPtr->PutFloatValue(SVT_HART_MA       , mAValues[i]); // Convert to Ampere
                                    CompPtr->PutFloatValue(SVT_HART_ERROR_CNT, FailCnt1[i]); 
                                    break;
                                default:
                                    CompPtr->NewValue(mAValues[i] / 1000.0); // Convert to Ampere
                                    break;
                                }
                                //CompPtr->PutFloatValue(SVT_HART_STATUS,FailCnt1[i]);// Convert to Ampere
                                CompPtr->Calculate();
                                CompPtr->ActiveAlarms = CheckAlarms(CompPtr->AlarmSet, &CompPtr->MyHWFailure);
                                if ( !CompPtr->ActiveAlarms ) {
                                    CompPtr->SetTimeStamp();
                                }
                                CompPtr->SendData();
                            }
                        }
                    }
                }
                 // Also set time stamp on the e.g. linked tank object
                {
                    set<PRogramObject*>::iterator pBIt;
                    for (pBIt = IOUniquePROSet.begin(); pBIt != IOUniquePROSet.end(); pBIt++) {
                        (*pBIt)->SetTimeStamp();
                    }
                    
                }
                break;
            case CMD_REP_HART_FILTER:
                break;
            case CMD_REP_HART_SETUP:
                {
                    U16 tmpPowerStatus = (Buf[1] << 8) | Buf[0];
                    if ( tmpPowerStatus != PowerStatus ) {
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
            if ( MoreCommands ) {
                Buf += pCH->ndb;
            }
        } while ( MoreCommands && (Buf < EndPtr) );
    }
    return (MyPacket);
}

void IOUnitZBHart::SendToIO(U16 Command, void *Data, U16 Size, bool RequestAck) {
    NetPacket Packet;
    Packet.Command    = Command;
    Packet.RxAddress  = IOAddress;
    Packet.RxTypeId   = DEVICE_ZBHART;
    Packet.RequestAck = RequestAck;
    Packet.Size       = Size;
    Packet.Data       = Data;
    SendPacket(Packet);
}


void IOUnitZBHart::PowerOn(void) {
#ifdef S2TXU
    for ( int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++ ) {
        PROIOComponent *CompPtr = IOComponent[i];
        if ( CompPtr ) {
            switch ( CompPtr->Type ) {
            case C_AI_Radar_Hart:
                HART_Sensor |= 1 << i;
                break;
            default:
                break;
            }
        }
    }
    U16 ResetCounters   =  (U16)(RunningTime < 10000 );
    U16 StartMessage[3] = { PowerStatus, HART_Sensor,ResetCounters };
    SendToIO(CMD_SND_HART_SETUP, &StartMessage, sizeof(StartMessage), false);
    PowerOnTime = RunningTime + POWER_ON_ZBANA_START_DELAY;
#endif
}

void IOUnitZBHart::RequestSetup(void) {
#ifdef S2TXU
    SendToIO(CMD_REQ_HART_SETUP, NULL, 0, false);
#endif
}



void IOUnitZBHart::HandleIO(int Delay) {
    time_t MyCurentTime = RunningTime;
    if ( Restart ) {
        Request(CMD_REQ_STATUS);
        if ( ANPRO10_IO_Receive() ) {
            SetFilters();
            TSN_Delay(Delay);
            PowerOn();
            TSN_Delay(Delay);
            Restart = false;
        }
    } else if ( MyCurentTime > (PowerOnTime) ) {
        Request(CMD_REQ_HART_DATA);
        ANPRO10_IO_Receive();
        //Request(CMD_REQ_ANA_DATA);
        //ANPRO10_IO_Receive();
        //TSN_Delay(Delay);
        if ( MyCurentTime > ReqStatusTime ) {
            TSN_Delay(Delay);
            ReqStatusTime = MyCurentTime + IO_STATUS_REQ_DELAY;
            Request(CMD_REQ_INT_DATA);
            ANPRO10_IO_Receive();
            TSN_Delay(Delay);
            Request(CMD_REQ_STATUS);
            ANPRO10_IO_Receive();
            TSN_Delay(Delay);
            RequestSetup();
            ANPRO10_IO_Receive();
            if ( !ActiveAlarms ) {
                switch ( ProgamTypeRunning ) {
                case 0:
                    UpdateProgram();
                    break;
                case 1:
                    if (  (UnitProgVersion != VERSION_ANZBHART_PROG) || (ComVersion  != VERSION_ANZBHART_COMP) || (StoreVersion != VERSION_ANZBHART_EEPROM) ) {
                        if ( UnitProgVersion >= 13 ) {
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


void IOUnitZBHart::SetFilters(void) {
    U8 Filters[MAX_AN_ZBANA_CHANNELS];

    for ( int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++ ) {
        if ( IOComponent[i] ) {
            Filters[i] = IOComponent[i]->GetFilter();
        } else {
            Filters[i] = FILTER_DEFAULT;
        }
    }
    NetPacket Packet;
    Packet.Command    = CMD_SND_HART_FILTER;
    Packet.RxAddress  = IOAddress;
    Packet.RxTypeId   = DEVICE_ZBHART;
    Packet.RequestAck = 0;
    Packet.Size       = sizeof(Filters);
    Packet.Data       = (U8 *)Filters;
    SendPacket(Packet);
}


bool IOUnitZBHart::UpdateProgram(void)
{
	bool ProgOK=true;
	#ifdef S2TXU
	if ( ProgamTypeRunning != 0 ) {
		Request(CMD_GOTO_BOOTLOADER);
		TSN_Delay(1000); // Wait for bootloader to be ready
		Request(CMD_REQ_STATUS);
		ANPRO10_IO_Receive();
	}
	if ( ProgamTypeRunning == 0 ) {	// Are the bootloader active
		if ( EraseFlash() ) {
			int NumberOfFullPackets = ProgramDataANZBHARTSize/ANPRO10_IO_PDATA_SIZE;
			U16 RemainingSize       = ProgramDataANZBHARTSize % ANPRO10_IO_PDATA_SIZE;
			int Cnt;
			for ( Cnt=0; ProgOK && Cnt < NumberOfFullPackets; Cnt++ ) {
				ProgOK = ProgramFlash(Cnt*ANPRO10_IO_PDATA_SIZE,ANPRO10_IO_PDATA_SIZE,ProgramDataANZBHART);
			}
			if ( ProgOK ) {
				ProgOK = ProgramFlash(NumberOfFullPackets*ANPRO10_IO_PDATA_SIZE,RemainingSize,ProgramDataANZBHART);
			}
			if ( ProgOK ) {
				Request(CMD_EXIT_BOOTLOADER);
			}
		} else {
			ProgOK = false;
		}
	} else {
		ProgOK = false;
	}
	#endif
	return ProgOK;
}


#endif
int IOUnitZBHart::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2603  *pData = (ANPRO10_COMMAND_2603 *)data;
            PowerStatus   = pData->PowerStatus;
            FailCnt      = pData->FailCnt;
            FailCntTotal = pData->FailCntTotal;
            for ( int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++ ) {
                mAValues[i] = pData->mAValues[i];
                FailCnt1[i] = pData->FailCnt1[i];
                FailCnt2[i] = pData->FailCnt2[i];
                Status[i]   = pData->Status[i];
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
            UnitProgVersion  = pData->UnitProgVersion;
            ComVersion       = pData->ComVersion;
            StoreVersion     = pData->StoreVersion;
            RxBufSize        = pData->RxBufSize;
            TxBufSize        = pData->TxBufSize;
			ResetStatus      = pData->ResetStatus;
            ProgamTypeRunning= pData->ProgamTypeRunning;
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

int IOUnitZBHart::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
			QueueANPRO10_COMMAND_2603 Cmd;
            Cmd.TxInfo.Port        = NULL;
            Cmd.TxInfo.rxAddr      = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId        = DEVICE_BROADCAST_TXU;

            Cmd.Data.ObjectId      = IDNumber;
            Cmd.Data.ndb           = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo     = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.PowerStatus   = PowerStatus;
            Cmd.Data.FailCnt        = FailCnt;
            Cmd.Data.FailCntTotal   = FailCntTotal;
            for ( int i = 0; i < MAX_AN_ZBANA_CHANNELS; i++ ) {
                Cmd.Data.mAValues[i] = mAValues[i];
				Cmd.Data.Status[i]   = Status[i];
				Cmd.Data.FailCnt1[i] = FailCnt1[i];
				Cmd.Data.FailCnt2[i] = FailCnt2[i];
            }
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus =  E_QUEUE_FULL;
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


