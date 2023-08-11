#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

ValueList SCADCard::SCAdCardValueList[] = {
    { L_WORD304, L_WORD237, SVT_BLANK },                               //   {"Unused"       ,"",SVT_BLANK},
    { L_WORD24, L_WORD237, SVT_IO_PROG_VERSION },                     //   {"ProgVersion"  ,"",SVT_IO_PROG_VERSION},
    { L_WORD390, L_WORD237, SVT_IO_SERIAL_NUMBER },                    //   {"Serial Number","",SVT_IO_SERIAL_NUMBER},
    { L_WORD126, L_WORD237, SVT_IO_CAL_GAIN },                         //   {"Gain"         ,"",SVT_IO_CAL_GAIN},
    { L_WORD384, L_WORD237, SVT_IO_RESET_STATUS },                     //   {"Reset Status" ,"",SVT_IO_RESET_STATUS},
    { L_WORD391, L_WORD237, SVT_IO_UNIT_STATUS },                      //   {"Unit status"  ,"",SVT_IO_UNIT_STATUS},
    { L_WORD392, L_WORD237, SVT_IO_CARD_STATUS },                      //   {"Card status"  ,"",SVT_IO_CARD_STATUS},
    { L_WORD386, L_WORD237, SVT_IO_FAIL_CNT_CHK },                     //   {"Fail cnt chk" ,"",SVT_IO_FAIL_CNT_CHK},
    { L_WORD387, L_WORD237, SVT_IO_FAIL_CNT_TOT },                     //   {"Fail cnt tot" ,"",SVT_IO_FAIL_CNT_TOT},
};

#define SGCNV_DEFAULT_FILTER 2

const int SCADCard::EEPromInfo[4] = { L_WORD486, L_WORD161, L_WORD487, L_WORD488 }; //" None","OK","Err","NoUs"
const int SCADCard::ADSensorType[AD_SNS_TYPES] = { L_WORD485, L_WORD338, L_WORD489, L_WORD490 }; //"Unknown","Temp","Other","Press"

SCADCard::SCADCard(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr, IOUnit *IOModulePtr) : SignalConverter(IOCompPtr, ElementPtr, IOModulePtr) {
    IDNumber = (C_SC_ADCARD << 16) + ObjectSet.size();
    Type = C_SC_ADCARD;
    IsFirstTime = true;
    RxBufSize = 0;
    TxBufSize = 0;
    CalNull = 0;
    EEPromGain = 1.0;
    RequestADConfig = 2;
    RequestRawCnt = 0;
    hasForcedPressureSensor = false;
    HasPressureSensor = false;
    FilterDegreeOther = SGCNV_DEFAULT_FILTER;
    memset((void *)&ADConfigData, 0, sizeof(ADConfigData));
    for ( int i = 0; i < MAX_AN_SGCNV_CHANNELS; i++ ) {
        ADConfigData[i].CalError = false;
        ADConfigData[i].ConvError = false;
        ADConfigData[i].PCSensor = 0;
        ADConfigData[i].UsePCSetUp = false;
        ADConfigData[i].FoundSensor = 0;
        ADConfigData[i].NewSensor = false;
        ADConfigData[i].EEP_PCStatus = 0;
        ADConfigData[i].EEPUsePCData = false;
        ADConfigData[i].EEPromStatus = AD_EEPROM_OK;
    }
    for ( int i = 0; i < MAX_WASHTRACK_CHANNELS; i++ ) {
        IOComponentWT[i] = NULL;
        WashTrackCnt[i] = 0;
        WashTrackNoMoveCnt[i] = 0;
        WashTrackSpeed[i] = 0.0;
    }
    for ( int i = 0; i < MAX_LEVEL_SWITCH_CHANNELS; i++ ) {
        LevelSwitch[i] = 0;
    }

    Name = "ADCard[" + (AnsiString)IOModulePtr->IOAddress + ":" + (AnsiString)(IOChannel + 1) + "]";
    DataTransferSet.insert(this);
}

SCADCard::~SCADCard(void) {
}
//---------------------------------------------------------------------------



///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int SCADCard::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_IO_CH_WT_SPEED :
        if ( Index < MAX_WASHTRACK_CHANNELS ) {
            MyRetValue = WashTrackSpeed[Index];
            DecPnt = 1;
            Unit = REVOLUTIONS_UNIT;
        } else {
            Status = GETVAL_ERROR;
        }
        break;
    case SVT_IO_CH_WT_COUNT :
        if ( Index < MAX_WASHTRACK_CHANNELS ) {
            MyRetValue = WashTrackCnt[Index];
            DecPnt = 0;
            Unit = NO_UNIT;
        } else {
            Status = GETVAL_ERROR;
        }
        break;
    case SVT_IO_CH_LEVEL_SWITCH  :
        if ( Index < MAX_LEVEL_SWITCH_CHANNELS ) {
            MyRetValue = MsrdValues[Index];
            DecPnt = 0;
            Unit = NO_UNIT;
        } else {
            Status = GETVAL_ERROR;
        }
        break;
    case SVT_IO_CH_VALUE :
        if ( Index < MAX_AN_SGCNV_CHANNELS ) {
            MyRetValue = MsrdValues[Index];
            DecPnt = 3;
            Unit = NO_UNIT;
        } else {
            Status = GETVAL_ERROR;
        }
        break;
    case SVT_IO_CH_STATUS :
        if ( Index < MAX_AN_SGCNV_CHANNELS ) {
            MyRetValue = *((U16 *)&ADConfigData[Index]);
            DecPnt = 0;
            Unit = NO_UNIT;
        } else {
            Status = GETVAL_ERROR;
        }
        break;
    case SVT_IO_CH_CAL_VAL :
        if ( Index < MAX_AN_SGCNV_CHANNELS ) {
            MyRetValue = CalValues[Index];
            DecPnt = 0;
            Unit = NO_UNIT;
        } else {
            Status = GETVAL_ERROR;
        }
        break;
    case SVT_IO_CH_RAW_VAL :
        if ( Index < MAX_AN_SGCNV_CHANNELS ) {
            MyRetValue = RawValues[Index];
            DecPnt = 0;
            Unit = NO_UNIT;
        } else {
            Status = GETVAL_ERROR;
        }
        break;
    case SVT_IO_RXBUF_SIZE:
        MyRetValue = RxBufSize;
        DecPnt = 0;
        Unit = NO_UNIT;
        break;
    case SVT_IO_TXBUF_SIZE:
        MyRetValue = TxBufSize;
        DecPnt = 0;
        Unit = NO_UNIT;
        break;
    case SVT_IO_CAL_NULL:
        MyRetValue = CalNull;
        DecPnt = 0;
        Unit = NO_UNIT;
        break;
    case SVT_IO_CAL_GAIN:
        MyRetValue = EEPromGain;
        DecPnt = 6;
        Unit = NO_UNIT;
        break;
    case SVT_IO_RESET_STATUS:
        MyRetValue = Restart;
        DecPnt = 0;
        Unit = NO_UNIT;
        break;
    case SVT_IO_NEW_SENSOR:
        {
            bool NSns = false;
            for ( int i = 0; i < MAX_AN_SGCNV_CHANNELS; i++ ) {
                NSns |= ADConfigData[i].NewSensor;
            }
            MyRetValue = (float)NSns;
        }
        DecPnt = 0;
        Unit = NO_UNIT;
        break;
    default:
        Status = SignalConverter::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int SCADCard::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_IO_CH_NAME :
        {
            PROIOComponent *IOCPtr = IOComponent[Index];
            if ( IOCPtr ) {
                Status = IOCPtr->GetStringValue(SVT_AI_PRONAME, 0, MyString);
            } else {
                MyString = "";
            }
        }
        break;
    case SVT_IO_CH_LOCATION :
        {
            PROIOComponent *IOCPtr = IOComponent[Index];
            if ( IOCPtr ) {
                Status = IOCPtr->GetStringValue(SVT_AI_LOCATION, 0, MyString);
            } else {
                MyString = "";
            }
        }
        break;
    case SVT_IO_CH_TYPE_TEXT :
        {
            PROIOComponent *IOCPtr = IOComponent[Index];
            if ( IOCPtr ) {
                Status = IOCPtr->GetStringValue(SVT_AI_TYPE_TEXT, 0, MyString);
            } else {
                MyString = "";
            }
        }
        break;
    case SVT_IO_CH_CONV_ERROR :
        MyString = LibGetText(StatusText, SizeofStatusText, ST_TXT_ERROR_STAT, ADConfigData[Index].ConvError);
        break;
    case SVT_IO_CH_CNV_CAL_ERROR:
        {
            bool ADStatus = ADConfigData[Index].ConvError;
            ADStatus |= ADConfigData[Index].CalError;
            MyString = LibGetText(StatusText, SizeofStatusText, ST_TXT_ERROR_STAT, ADStatus);
        }
        break;
    case SVT_IO_CH_CAL_ERROR :
        MyString = LibGetText(StatusText, SizeofStatusText, ST_TXT_ERROR_STAT, ADConfigData[Index].CalError);
        break;
    case SVT_IO_CH_EEP_SNS_STAT :
        MyString = FindDictionaryWord(EEPromInfo[ADConfigData[Index].EEPromStatus]);
        break;
    case SVT_IO_CH_EEP_PC_STAT :
        MyString = FindDictionaryWord(EEPromInfo[ADConfigData[Index].EEP_PCStatus]);
        break;
    case SVT_IO_CH_EEP_USE_PCDATA:
        MyString = LibGetText(StatusText, SizeofStatusText, ST_TXT_NO_YES, ADConfigData[Index].EEPUsePCData);
        break;
    case SVT_IO_CH_USE_PC_SETUP :
        MyString = LibGetText(StatusText, SizeofStatusText, ST_TXT_NO_YES, ADConfigData[Index].UsePCSetUp);
        break;
    case SVT_IO_CH_AD_SENSOR :
        MyString = FindDictionaryWord(ADSensorType[ADConfigData[Index].FoundSensor]);
        break;
    case SVT_IO_CH_FROM_PC_SENSOR :
        MyString = FindDictionaryWord(ADSensorType[ADConfigData[Index].PCSensor]);
        break;
    case SVT_IO_CH_NEW_SENSOR :
        MyString = LibGetText(StatusText, SizeofStatusText, ST_TXT_NO_YES, ADConfigData[Index].NewSensor);
        break;
    default:
        Status = SignalConverter::GetStringValue(ValueId, Index, MyString);
        break;
    }

    return (Status);
}

int SCADCard::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    return (SignalConverter::PutValue(ValueId, Index, NewValue, Local, UnitId));
}

int SCADCard::PutFloatValue(int ValueId, float NewValue) {
    return (SignalConverter::PutFloatValue(ValueId, NewValue));
}

ValueList* SCADCard::GetValueInfoTable(int &Entries, int Index) {
    Entries = NELEMENTS(SCAdCardValueList);
    return (SCAdCardValueList);
}

// For communication

void SCADCard::SetHWFailure(bool Failure) {
    if ( Failure ) {
        for ( int i = 0; i < MAX_AN_SGCNV_CHANNELS; i++ ) {
            PROIOComponent *CompPtr = IOComponent[i];
            if ( CompPtr && CompPtr->HWFailure ) {
                CompPtr->HWFailure = true;
                CompPtr->SendData();
            }
        }
    }
}

#ifdef S2TXU
int SCADCard::AddCommand(U8 *BufPtr, U8 Command, U8 Size, U8 *Data) {
    BufPtr[0] = Command;
    BufPtr[1] = Size;

    memcpy(&BufPtr[2], Data, Size);
    return (Size + 2);
}


void SCADCard::SendToAD(U8 Command, U8 Size, U8 *Data) {
    NetPacket Packet;
    ANPRO10_Command_1160_Single ADData;
    Packet.Command = CMD_SND_RS4_ADBUF;
    Packet.RxAddress = IOAddress;
    Packet.RxTypeId = DEVICE_ZB485;
    Packet.RequestAck = 0;
    Packet.Size = sizeof(ADData) - sizeof(ADData.Data) + Size;
    Packet.Data = (U8 *)&ADData;

    ADData.Channel = IOChannel;
    ADData.Cmd = Command;
    ADData.Size = Packet.Size - 2; // Notice this one!!!
    ADData.DSize = Size;
    memcpy(ADData.Data, Data, Size);
    SendPacket(Packet);
}


void SCADCard::SendToAD(U8 Size, U8 *Data) {
    NetPacket Packet;
    ANPRO10_Command_1160 ADData;
    Packet.Command = CMD_SND_RS4_ADBUF;
    Packet.RxAddress = IOAddress;
    Packet.RxTypeId = DEVICE_ZB485;
    Packet.RequestAck = 0;
    Packet.Size = sizeof(ADData) - sizeof(ADData.Data) + Size;
    Packet.Data = (U8 *)&ADData;

    ADData.Channel = IOChannel;
    ADData.Size = Packet.Size - 2; // Notice this one!!!
    memcpy(ADData.Data, Data, Size);
    SendPacket(Packet);
}

    #define IO_DELAY 5000
void SCADCard::SendGainAndOffset(void) {
    AdjustPacket AdjustData[MAX_AN_SGCNV_CHANNELS];
    int Cnt = 0;
    for ( int Ch = 0; Ch < MAX_AN_SGCNV_CHANNELS; Ch++ ) {
        if ( IOComponent[Ch] ) {
            switch ( IOComponent[Ch]->Type ) {
            case C_AI_WashTrackSensor :
                break;
            case C_AI_Pt100 :
            case C_AI_Pt1000 :
            case C_AI_TEMP_AD590 :
                {
                    AITempSensor *SnsPtr = (AITempSensor *)IOComponent[Ch];
                    short Offset = short(SnsPtr->GetCableCorrection() * 10 + 0.5);
                    if ( Offset ) {
                        AdjustData[Cnt].ChNo = Ch;
                        AdjustData[Cnt].GainHigh = 0;
                        AdjustData[Cnt].GainLow = 0;
                        AdjustData[Cnt].OffsetHigh = Offset >> 8;
                        AdjustData[Cnt].OffsetLow = Offset & 0xFF;
                        Cnt++;
                    }    // End if
                }
                break;
            } // End switch
        }   // End If IO-component
    } // End for loop
    if ( Cnt ) {
        SendToAD(ANP1_SND_OFF_GAIN, Cnt * sizeof(AdjustPacket), (U8 *)AdjustData);
        OS_Delay(IO_DELAY);
    }
}

    #define DUMMY_PRESS_CHANNEL 13
    #define SETUP_BUF_SIZE      15

void SCADCard::InitSensorTypes(bool ForceDummyPress) {
    // Must check all the channels to be sure that we don't skip a pressure sensor
    for ( int Ch = 0; Ch < MAX_AN_SGCNV_CHANNELS; Ch++ ) {
        unsigned SnsType;
        PROIOComponent *AIPtr = IOComponent[Ch];
        if ( AIPtr ) {
            switch ( AIPtr->Type ) {
            case C_AI_Pt100 :
            case C_AI_Pt1000 :
                SnsType = AD_TEMP_SNS;
                break;
            case C_AI_1728 :
            case C_AI_P906_0110 :
            case C_AI_P906_0111 :
                SnsType = AD_PRESS_SNS;
                HasPressureSensor = true;
                break;
            case C_AI_LeSw_ADCard :
                FilterDegreeOther = 0;
                SnsType = AD_OTHER_SNS;
                break;
            case C_AI_INCLINOMETER :
            case C_AI_TEMP_AD590 :
                SnsType = AD_OTHER_SNS;
                break;
            default :
                // This is an error in sensor object!!!
                SnsType = AD_NO_SNS;
                break;
            }
        } else if ( (Ch == DUMMY_PRESS_CHANNEL) && !HasPressureSensor ) {
            SnsType = AD_PRESS_SNS;
        } else {
            SnsType = AD_NO_SNS; //AD_NO_SNS;
        }
        SensorType[Ch] = SnsType;
    }
    if ( ForceDummyPress ) {
        for ( int i = 0; i < MAX_AN_SGCNV_CHANNELS; i += 2 ) {
            SensorType[i] = AD_PRESS_SNS;
        }
    }
}



bool SCADCard::Correct_AD_Config(void) {
    bool CfgDiffer = false;
    // Must check all the channels to be sure that we don't skip a pressure sensor
    for ( int Ch = 0; !CfgDiffer && Ch < MAX_AN_SGCNV_CHANNELS; Ch++ ) {
        CfgDiffer |= (SensorType[Ch] != ADConfigData[Ch].PCSensor);
    }

    if ( CfgDiffer ) {
        U8 SnsSetUpBuf[SETUP_BUF_SIZE];
        for ( int Ch = 0; Ch < MAX_AN_SGCNV_CHANNELS; Ch++ ) {
            SnsSetUpBuf[Ch] = (SensorType[Ch] | AD_USE_PC_INFO) << 2;
        }
        SnsSetUpBuf[14] = 1;     // Flag that this information shall be used
                                 // Send configuration to the AD card
        SendToAD(ANP1_SND_SET_UP, SETUP_BUF_SIZE, (U8 *)SnsSetUpBuf);
    }
    return CfgDiffer;
}

void SCADCard::GetADConfigInfo(void) {
    SendToAD(ANP1_REQ_CONFIG, 0, NULL);
}

bool SCADCard::ExtraADSetUp(void) {
    U8 TxBuf[BUF_SIZE];
    int Size = 0;
    //Size += AddCommand(TxBuf, ANP1_REQ_CONFIG, 0, NULL);
    if ( !HasPressureSensor ) {
        // Change temperature conversion time
        U8 ScanDelay = 1;   // Seconds temp scan delay
        Size += AddCommand(TxBuf, ANP1_SND_TBTR, sizeof(ScanDelay), &ScanDelay);
    }
    if ( FilterDegreeOther != SGCNV_DEFAULT_FILTER ) {
        // Change filters    Default is 5,2,2, Press,Tmp,Other
        U8 Filter[3] = { 5, 2, FilterDegreeOther }; // Seconds pressure.
        Size += AddCommand(TxBuf, ANP1_SND_FILTER, sizeof(Filter), Filter);
    }
    SendToAD(Size, TxBuf);
    return bool(Size);
}
    #define ADC_ERROR_VALUE     53249
    #define ADC_CAL_ERROR_VAL1  32768
    #define ADC_CAL_ERROR_VAL2  32769
bool SCADCard::ANPRO10_IO_UnpackPacket(U8 *Buf) {
    bool MoreCommands = true;
    ANPRO10_PacketHeading *pPH = (ANPRO10_PacketHeading *)Buf;
    U8 *EndPtr = &Buf[pPH->nob];

    Buf += sizeof(ANPRO10_PacketHeading);

    volatile ANPRO10_CommandHeading *pCH;
    bool MyPacket = (pPH->txadr == this->IOAddress);
    if ( MyPacket ) {
        do {
            pCH = (ANPRO10_CommandHeading *)Buf;
            Buf += sizeof(ANPRO10_CommandHeading);  // ??
            switch ( pCH->CommandNo ) {
            case CMD_REP_RS4_ADBUF:
                {
                    //bool DataIsValid = (bool)Buf[0];
                    U8 Ch = Buf[1];
                    SignalConverter *SConverter = FindSignalConverter(Ch);
                    if ( SConverter ) {
                        SConverter->GetEEPromData(&Buf[2]);
                    }
                }
                break;
            case CMD_SND_RS4_WHBUF:
                {
                    SgCnvWHDataStruct &MsrdData = *(SgCnvWHDataStruct *)Buf;
                    // Know where we start. We must start with the current count from AN-SGCNV

                    for ( int i = 0; i < MAX_WASHTRACK_CHANNELS; i++ ) {
                        if ( SoftwareVersion >= 12 ) {
                            float Counter = MsrdData.Counter[i];
                            if ( MsrdData.Ticks && Counter > 1.0 ) {
                                WashTrackCnt[i]  += MsrdData.Counter[i];
                                WashTrackSpeed[i] = 60000.0 / 4.0 * Counter / float(MsrdData.Ticks); // 4 pulses per rotation
                                WashTrackNoMoveCnt[i] = 0;
                            } else {
                                if ( WashTrackNoMoveCnt[i] > 2 ) {
                                    WashTrackSpeed[i] = 0.0;
                                } else {
                                    WashTrackNoMoveCnt[i]++;
                                }
                            }
                        } else {
                            // Avoid divide by zero. ElapsedTicks shold never be 0 anyway
                            // Can only detect that the machine moves, but not the speed
                            if ( WashTrackCnt[i] != MsrdData.Counter[i] ) {
                                WashTrackCnt[i] = MsrdData.Counter[i];
                                WashTrackSpeed[i] = 100.0;
                                WashTrackNoMoveCnt[i] = 0;
                            } else {
                                if ( WashTrackNoMoveCnt[i] > 4 ) {
                                    WashTrackSpeed[i] = 0.0;
                                } else {
                                    WashTrackNoMoveCnt[i]++;
                                }
                            }
                        }
                        if ( IOComponentWT[i] ) {
                            IOComponentWT[i]->NewValue(WashTrackSpeed[i]);
                            IOComponentWT[i]->ActiveAlarms = CheckAlarms(IOComponentWT[i]->AlarmSet, &IOComponentWT[i]->MyHWFailure);
                            IOComponentWT[i]->Calculate();
                            IOComponentWT[i]->SendData();
                        }
                    }

                    for ( int i = 0; i < MAX_LEVEL_SWITCH_CHANNELS; i++ ) {
                        LevelSwitch[i] = (MsrdData.LevelSwitch >> i) & 0x01;
                    }
                }
                break;
            case CMD_REP_RS4_MDATA:
                {
                    SgCnvMeasuredDataStruct &MsrdData = *(SgCnvMeasuredDataStruct *)Buf;
                    if ( MsrdData.IOChannel == IOChannel ) {
                        IOUnitZB485 &ZB485Module = *(IOUnitZB485 *)IOModule;
                        IOUnitStatus = MsrdData.IOUnitStatus;
                        U8 TmpStatus = IOUnitStatus >> 4;
                        if ( TmpStatus ) {
                            ZB485Module.ResetStatus = TmpStatus;
                            ZB485Module.Restart = true;
                        }
                        FailCnt = MsrdData.FailCnt;
                        FailCntTotal = MsrdData.FailCntTotal;
                        SoftwareVersion = MsrdData.TargetStatusSWVer;
                        SCAddress = MsrdData.TargetStatusAddress & 0x7f;
                        Restart = (bool)(MsrdData.TargetStatusAddress >> 7);
                        ActiveAlarms = CheckAlarms(AlarmSet);
                        if ( !Restart ) {
                            if ( !ActiveAlarms && !TmpStatus ) {
                                U8 TxBuf[2 * BUF_SIZE];
                                int Size = 0;
                                ConfigPacket tmpADConfigData[MAX_AN_SGCNV_CHANNELS];
                                memcpy((void *)&tmpADConfigData, (void *)&ADConfigData, sizeof(tmpADConfigData));
                                for ( int i = 0; i < MAX_AN_SGCNV_CHANNELS; i++ ) {
                                    ((U8 *)&ADConfigData[i])[0] = MsrdData.Channel[i].Status1;
                                    ((U8 *)&ADConfigData[i])[1] = MsrdData.Channel[i].Status2;
                                    // Check channel status eeprom setup, (Refreshed on AN485 every 15 sec.
                                    // Check sensor type and parameters, if fault, download sensor type
                                    // and sensor parameters
                                    MsrdValues[i] = MsrdData.Channel[i].MsrdValue;
                                    AnalogInput *CompPtr = (AnalogInput*)IOComponent[i];
                                    if ( CompPtr ) {
                                        //int Test = ADConfigData[i].EEPromStatus;
#ifdef S2TXU
                                        int Index = IOChannel / 4;
                                        int DownloadEEPROMTime = abs(OS_Time - ZB485Module.DownloadEEPROMTime[Index]);
                                        switch ( CompPtr->Type ) {
                                        case C_AI_1728 :
                                        case C_AI_P906_0110 :
                                        case C_AI_P906_0111 :
                                            if ( (!ADConfigData[i].CalError && !ADConfigData[i].ConvError && !ADConfigData[i].EEPUsePCData && (ADConfigData[i].EEP_PCStatus != 0x1))
                                                 && (DownloadEEPROMTime > IO_DELAY) ) {
                                                switch ( ADConfigData[i].EEPromStatus ) {
                                                case AD_EEPROM_OK :
                                                case AD_NOT_USED :
                                                case AD_NO_EEPROM :
                                                    break;
                                                case AD_EEPROM_ERROR:
                                                    {

                                                        AIPressSensor_mV &SnsPtr = *(AIPressSensor_mV *)CompPtr;
                                                        ZB485Module.DownloadEEPROMTime[Index] = OS_Time;
                                                        // Check that our sensor has EEProm
                                                        // When user input of cal data, this logic must be improved
                                                        U8 EEPData[EEPROM_SIZE + 2] = { i };     // Reference AN_PRO1. Command 18
                                                        SnsPtr.PackSensorData(&EEPData[1]);
                                                        EEPData[41] = 1;   // Use data from the PC
                                                        Size += AddCommand(TxBuf, ANP1_SND_EEP_DATA, EEPROM_SIZE + 2, EEPData);
                                                    }
                                                    break;
                                                }
                                            }
                                            break;
                                        default:
                                            break;
                                        }
#endif
                                        if ( ((SensorType[i] == ADConfigData[i].PCSensor)/*&& ADConfigData[i].UsePCSetUp*/)
                                             || (SensorType[i] == ADConfigData[i].FoundSensor) ) {
                                            CompPtr->SetStatus((U8 *)&ADConfigData[i]);
                                            CompPtr->NewValue(MsrdValues[i]);
                                            CompPtr->ActiveAlarms = CheckAlarms(CompPtr->AlarmSet, &CompPtr->MyHWFailure);
                                            CompPtr->Calculate();
                                            if ( !CompPtr->ActiveAlarms ) {
                                                CompPtr->SetTimeStamp();
                                                // Also set time stamp on the e.g. linked tank object
                                                if ( CompPtr->PROPtr ) {
                                                    CompPtr->PROPtr->SetTimeStamp();
                                                }
                                            }
                                            CompPtr->SendData();
                                        } else {
                                            RequestADConfig = 3;
                                        }
                                    }
                                }
                                if ( Size ) {
                                    SendToAD(Size, TxBuf);
                                }
                                if ( memcmp((void *)&ADConfigData, &tmpADConfigData, sizeof(ADConfigData)) ) {
                                    SendData(CMD_GENERIC_STATIC_DATA);
                                }
                            }
                            SetHWFailure((bool)ActiveAlarms);
                            SendData();
                        }
                    }
                }
                break;
            case CMD_REP_RS4_RDATA:
                {
                    SgCnvRawDataStruct &MsrdData = *(SgCnvRawDataStruct *)Buf;
                    if ( MsrdData.IOChannel == IOChannel ) {
                        int ErrCnt = 0;
                        for ( int i = 0; i < MAX_AN_SGCNV_CHANNELS; i++ ) {
                            RawValues[i] = MsrdData.Channel[i][0];
                            CalValues[i] = MsrdData.Channel[i][1];
                            if ( (RawValues[i] == ADC_ERROR_VALUE) || (CalValues[i] == ADC_CAL_ERROR_VAL1) || (CalValues[i] == ADC_CAL_ERROR_VAL2) ) {
                                ErrCnt++;
                            }
                        }
                        // If Error count > 6 we must assume the ADC don't work
                        if ( ErrCnt > 6 ) {
                            InitSensorTypes(true);
                            hasForcedPressureSensor = true;
                            ForcePowerOff = true;
                        } else {
                            if ( hasForcedPressureSensor ) {
                                InitSensorTypes(false);
                                hasForcedPressureSensor = false;
                            }
                        }
                    }
                }
                break;
                //case CMD_REP_RS4_CDATA:
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
        }while ( MoreCommands && (Buf < EndPtr) );
    }
    return (MyPacket);       // We came from ObjectSet
                             //return true;

}

void SCADCard::GetEEPromData(U8 *DataPtr) {
    U8 Ch = *DataPtr++;
    if ( Ch == MAX_AN_SGCNV_CHANNELS ) {
        SerialNumber = DataPtr[0] | (DataPtr[1] << 8) | (DataPtr[2] << 16) | (DataPtr[3] << 24);
        SendData(CMD_GENERIC_STATIC_DATA);
    } else if ( Ch < MAX_AN_SGCNV_CHANNELS ) {
        if ( !ADConfigData[Ch].EEPUsePCData && ADConfigData[Ch].EEPromStatus == AD_EEPROM_OK ) {
            PROIOComponent *CompPtr = IOComponent[Ch];
            if ( CompPtr ) {
                switch ( CompPtr->Type ) {
                case C_AI_1728 :
                case C_AI_P906_0110 :
                case C_AI_P906_0111 :
                    {
                        U8 OKPacket = 0;
                        for ( int i = 1; i < 8; i++ ) {
                            OKPacket |= DataPtr[i];
                        }
                        if ( OKPacket ) {
                            OKPacket = 0;
                            for ( int i = 1; i < 8; i++ ) {
                                if ( DataPtr[i] != 0xff ) {
                                    OKPacket++;
                                }
                            }
                            if ( OKPacket ) {
                                // Make one additional check
                                OKPacket = 0;    // Changed in Ulsan EHS 16/1/1
                                for ( int i = 10; i < 20; i++ ) {
                                    OKPacket |= DataPtr[i];
                                }
                                if ( OKPacket ) {
                                    AIPressSensor_mV *SnsPtr = (AIPressSensor_mV *)CompPtr;
                                    if ( SnsPtr->UnpackSensorData(DataPtr) ) {
                                        SnsPtr->SendData(CMD_GENERIC_STATIC_DATA);
                                        if ( OS_IsTask(&SaveConfigTaskHandle) ) {
                                            OS_SignalEvent(FLASH_WRITE_CONFIG_DELAY, &SaveConfigTaskHandle);
                                        }
                                    }
                                } else {
                                    ADConfigData[Ch].EEPromStatus = AD_EEPROM_ERROR;
                                }
                            }
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}


void SCADCard::RequestMeasuredData(int DataType) {
    NetPacket Packet;
    volatile U8 Data[2] = { (U8)DataType, (U8)IOChannel };
    Packet.Command = CMD_REQ_RS4_DATA;
    Packet.RxAddress = IOAddress;
    Packet.RxTypeId = DEVICE_ZB485;
    Packet.RequestAck = 0;
    Packet.Size = 2;
    Packet.Data = (U8 *)Data;
    SendPacket(Packet);
}

bool SCADCard::HandleCard(int Delay) {
    bool ReceivedAnswer = false;

    int Index = IOChannel / 4;
    IOUnitZB485 &ZB485Module = *(IOUnitZB485 *)IOModule;
    int *DownloadTime = &ZB485Module.DownloadEEPROMTime[Index];
    if ( abs(OS_Time - *DownloadTime) > IO_DELAY ) {
        if ( Restart ) {
            if ( IsFirstTime ) {
                IsFirstTime = false;
                InitSensorTypes();
            }
            // Should ask for sensor info for all channels here
            // Should set up filters and sensor cable length etc
            //SendGainAndOffset(); // EHSMark We don't use
            RequestADConfig = 2;
            Restart = false;
            // Download setup, Sensor types
            // Download filters
            // Use packet 1160
            // Can not download to any other card next 2 seconds
        } else if ( NewSensor ) {
            NewSensor = false;
            // Should ask for sensor info for all channels here
        } else { // The normal place
            RequestMeasuredData(0);

            if ( ANPRO10_IO_Receive() ) {
                if ( RequestADConfig ) {
                    bool AddDelay = true;
                    switch ( RequestADConfig ) {
                    case 3:
                        AddDelay = Correct_AD_Config();
                        break;
                    case 2:
                        GetADConfigInfo();
                        break;
                    case 1:
                        AddDelay = ExtraADSetUp();
                        break;
                    }
                    if ( AddDelay ) {
                        *DownloadTime = OS_Time;
                        OS_Delay(Delay);
                    }
                    RequestADConfig--;
                } else if ( RequestRawCnt++ >= 5 ) {
                    RequestRawCnt = 0;
                    OS_Delay(Delay);
                    RequestMeasuredData(1);
                    ReceivedAnswer = ANPRO10_IO_Receive();
                }
            } else {
                // Be sure that we set HWFailure when no communication
                SetHWFailure((bool)ActiveAlarms);
            }
        }
    } else {
        OS_Delay(Delay);
        ReceivedAnswer = true;
    }

    return (ReceivedAnswer);
}
#endif

int SCADCard::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2620 *pData = (ANPRO10_COMMAND_2620 *)data;
            FailCnt = pData->FailCnt;
            FailCntTotal = pData->FailCntTotal;
            for ( int i = 0; i < MAX_AN_SGCNV_CHANNELS; i++ ) {
                MsrdValues[i] = pData->MsrdValues[i];
                CalValues[i] = pData->CalValues[i];
                RawValues[i] = pData->RawValues[i];
                memcpy((void *)&ADConfigData[i], &pData->ADConfigData[i], sizeof(ConfigPacket));
                PROIOComponent *CompPtr = IOComponent[i];
                if ( CompPtr ) {
                    CompPtr->SetStatus((U8 *)&ADConfigData[i]);
                }
            }
            for ( int i = 0; i < MAX_WASHTRACK_CHANNELS; i++ ) {
                WashTrackSpeed[i]   = pData->Speed[i];
                WashTrackCnt[i]     = pData->WashTrackCnt[i];
            }
            for ( int i = 0; i < MAX_LEVEL_SWITCH_CHANNELS; i++ ) {
                LevelSwitch[i] = (pData->LevelSwitches >> i) & 0x01;
            }
            ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            ANPRO10_COMMAND_2621 *pData = (ANPRO10_COMMAND_2621 *)data;
            SoftwareVersion = pData->SoftwareVersion;
            RxBufSize = pData->RxBufSize;
            TxBufSize = pData->TxBufSize;
            CalNull = pData->CalNull;
            SerialNumber = pData->SerialNumber;
            EEPromGain = pData->EEPromGain;
            ErrorStatus = E_OK;
        }
        break;

    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int SCADCard::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2620 Cmd;
            Cmd.TxInfo.Port = NULL;
            Cmd.TxInfo.rxAddr = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId = IDNumber;
            Cmd.Data.ndb = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.FailCnt = FailCnt;
            Cmd.Data.FailCntTotal = FailCntTotal;
            for ( int i = 0; i < MAX_AN_SGCNV_CHANNELS; i++ ) {
                Cmd.Data.MsrdValues[i] = MsrdValues[i];
                Cmd.Data.CalValues[i] = CalValues[i];
                Cmd.Data.RawValues[i] = RawValues[i];
                memcpy((void *)&Cmd.Data.ADConfigData[i], (void *)&ADConfigData[i], sizeof(ConfigPacket));
            }
            for ( int i = 0; i < MAX_WASHTRACK_CHANNELS; i++ ) {
                Cmd.Data.Speed[i]        = WashTrackSpeed[i];
                Cmd.Data.WashTrackCnt[i] = WashTrackCnt[i];
            }
            U8 LevelSwitchState = 0;
            for ( int i = 0; i < MAX_LEVEL_SWITCH_CHANNELS; i++ ) {
                LevelSwitchState |= LevelSwitch[i] << i;
            }
            Cmd.Data.LevelSwitches = LevelSwitchState;
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2621 Cmd;
            Cmd.TxInfo.Port = NULL;
            Cmd.TxInfo.rxAddr = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId = IDNumber;
            Cmd.Data.ndb = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo = CMD_GENERIC_STATIC_DATA;

            Cmd.Data.SoftwareVersion = SoftwareVersion;
            Cmd.Data.RxBufSize = RxBufSize;
            Cmd.Data.TxBufSize = TxBufSize;
            Cmd.Data.CalNull = CalNull;
            Cmd.Data.SerialNumber = SerialNumber;
            Cmd.Data.EEPromGain = EEPromGain;

            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

//---------------------------------------------------------------------------
bool SCADCard::Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr) {
    bool SensorAdded = false;
    switch ( IOCompPtr->Type ) {
    case C_AI_WashTrackSensor:
        if ( IOCompPtr->ADCardChannel >= 0 && IOCompPtr->ADCardChannel < MAX_WASHTRACK_CHANNELS ) {
            if ( IOComponentWT[IOCompPtr->ADCardChannel] ) {
                AnsiString Message = (AnsiString)"TCU " + (AnsiString)IOCompPtr->TCUAddress;
                Message += (AnsiString)" com-port " + (AnsiString)IOCompPtr->TCUPortNo + ".\n";
                Message += (AnsiString)"WT Channel " + (AnsiString)(IOCompPtr->ADCardChannel + 1);
                Message += (AnsiString)" on ADCard on channel" + (AnsiString)(IOCompPtr->IOChannel + 1);
                Message += (AnsiString)" on IO " + KeyWord(IOType) + " addr." + (AnsiString)IOAddress;
                Message += (AnsiString)"\nChannel allredy used.\n Try to set sensor for ";
                Message += (AnsiString)ElementPtr->Name + ".\n";
                HardwareSetupWarning(Message);
                SensorAdded = false;
            } else {
                SensorAdded = true;
                IOComponentWT[IOCompPtr->ADCardChannel] = IOCompPtr;
                pair<set<PRogramObject *>::iterator, bool> Ret;
                Ret = UniquePROList.insert(ElementPtr);

                if ( Ret.second ) {
                    AddAlarms(ElementPtr->CompleteAlarmInfoList);
                }

                //((AnalogInput*)IOCompPtr)->SetPROPtr(ElementPtr);
                IOCompPtr->AddIOMdulePtr((ANPRO10Object *)this);
            }
        }
        break;
    default:
        if ( IOCompPtr->ADCardChannel >= 0 && IOCompPtr->ADCardChannel < MAX_AN_SGCNV_CHANNELS ) {
            if ( IOComponent[IOCompPtr->ADCardChannel] ) {
                AnsiString Message = (AnsiString)"TCU " + (AnsiString)IOCompPtr->TCUAddress;
                Message += (AnsiString)" com-port " + (AnsiString)IOCompPtr->TCUPortNo + ".\n";
                Message += (AnsiString)"Channel " + (AnsiString)(IOCompPtr->ADCardChannel + 1);
                Message += (AnsiString)" on ADCard on channel" + (AnsiString)(IOCompPtr->IOChannel + 1);
                Message += (AnsiString)" on IO " + KeyWord(IOType) + " addr." + (AnsiString)IOAddress;
                Message += (AnsiString)"\nChannel allredy used.\n Try to set sensor for ";
                Message += (AnsiString)ElementPtr->Name + ".\n";
                HardwareSetupWarning(Message);
                SensorAdded = false;
            } else {
                SensorAdded = true;
                IOComponent[IOCompPtr->ADCardChannel] = IOCompPtr;
                pair<set<PRogramObject *>::iterator, bool> Ret;
                Ret = UniquePROList.insert(ElementPtr);

                if ( Ret.second ) {
                    AddAlarms(ElementPtr->CompleteAlarmInfoList);
                }

                //((AnalogInput*)IOCompPtr)->SetPROPtr(ElementPtr);
                IOCompPtr->AddIOMdulePtr((ANPRO10Object *)this);
            }
        }
        break;
    }
    ElementPtr->MergeChildUserRights(this);
    return (SensorAdded);
}

