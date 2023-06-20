#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

vector<PRogramObjectBase *>PROLevelSwitch::AllObjVector;
vector<PRogramObjectBase *>PROLevelSwitch::ObjVector;
set<PRogramObjectBase *>PROLevelSwitch::ObjectSet;
bool PROLevelSwitch::Adjustable = false;
PROLevelSwitch::PROLevelSwitch(void) : PROXRefObject(true) {
    ObjectSet.insert(this);
    AllObjVector.push_back(this);
    IDNumber = (C_PRO_LEVSWITCH << 16) + ObjectSet.size();
    TankType = TANKTYPE_LEVEL_SWITCH;
    Initiate();
}
//---------------------------------------------------------------------------

PROLevelSwitch::PROLevelSwitch(int number) : PROXRefObject(true) {
    ObjectSet.insert(this);
    AllObjVector.push_back(this);
    if ( number == 0 ) {
        IDNumber = (C_PRO_LEVSWITCH << 16) + ObjectSet.size();
    } else {
        IDNumber = number;
    }
    Type       = C_PRO_LEVSWITCH;
    TankType = TANKTYPE_LEVEL_SWITCH;
    Initiate();
}
//---------------------------------------------------------------------------

void PROLevelSwitch::Initiate(void) {
    IsActive              = false;
    IsFailure             = false;
    Location              = C_AI_LOC_DECK;
    LevelSwitchSensor     = NULL;
    LevelSwitchAlPtr      = NULL;
    AddToIOObjectList();
    Page                  = 0;
    XPos                  = 0;
    YPos                  = 0;
    IsWarning             = false;

    //AddAlarms(CompleteAlarmInfoList);
}
//---------------------------------------------------------------------------

PROLevelSwitch::~PROLevelSwitch(void) {
    ObjectSet.erase(this);
    EraseFromVector(ObjVector, this);
    EraseFromVector(AllObjVector, this);
}
//---------------------------------------------------------------------------

void PROLevelSwitch::WriteConfigToFile(TSNConfigString &ConfigString) {
    AnsiString LocalString;
    AnsiString IdNumStr;
    IdNumStr.cat_sprintf("0x%0x", IDNumber);
    LocalString += KeyWord(Type) + TabStr1 + IdNumStr + CrLfStr;
    LocalString += PRogramObject::MakeConfigString();    //common
    LocalString += TabStr1 + KeyWord(C_PAGE) + TabStr1 + (AnsiString)Page + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_XPOS) + TabStr1 + (AnsiString)XPos + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_YPOS) + TabStr1 + (AnsiString)YPos + CrLfStr;
    if ( IsWarning ) {
        LocalString += TabStr1 + KeyWord(C_WARNING) + CrLfStr;
    }
    if ( LevelSwitchSensor ) {
        if ( Location != C_AI_LOC_DECK ) {
            LocalString += TabStr1 + KeyWord(Location) + CrLfStr;
        }
    }
    LocalString += LevelSwitchSensor->MakeConfigString();
    LocalString += KeyWord(C_PRO_END) + CrLfStr;
    LocalString += CrLfStr;

    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

int PROLevelSwitch::LoadConfigFromFile(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)"Level Switch " + Name, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning((AnsiString)"Level Switch " + Name, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_PRO_START_PRO:
                PRogramObject::LoadConfigString(ConfigString);
                break;
            case C_XREF_START:
                LoadConfigString(ConfigString);
                break;
            case C_AI_LeSw_HS:
                switch ( Key ) {
                case C_AI_LeSw_HS:
                    LevelSwitchSensor = (AnalogInput *)new AILevelSwitchOptical_mA(Key, LEVELSWITCH_HS_MA_ON, LEVELSWITCH_HS_MA_OFF, LEVELSWITCH_HS_MA_WIN, LEVELSWITCH_HS_MA_TEST, LEVELSWITCH_HS_MA_LIGHT);
                    break;
                }
                LevelSwitchSensor->LoadConfigString(ConfigString);
                AnalogInList.push_back((AnalogInput *)LevelSwitchSensor);
                if ( Description.IsEmpty() ) {
                    Description = "LevSwitch";
                }
                LevelSwitchAlPtr = new AlarmLevelSwitch(this, Name, Description);
                AlarmSet.insert(LevelSwitchAlPtr);
                break;
            case C_AI_LeSw_mA:
            case C_AI_LeSw_Valcom:
            case C_AI_LeSw_API:
            case C_AI_LeSw_Vega:
            case C_AI_LeSw_Vega62:
            case C_AI_LeSw_Vega64:
                {
                    switch ( Key ) {
                    case C_AI_LeSw_mA:
                        LevelSwitchSensor = (AnalogInput *)new AILevelSwitch_mA(C_AI_LeSw_mA, PROProjectInfo::Default_SwitchOn_mA, PROProjectInfo::Default_SwitchOff_mA, PROProjectInfo::Default_SwitchWindow);
                        break;
                    case C_AI_LeSw_Valcom:
                        LevelSwitchSensor = (AnalogInput *)new AILevelSwitch_mA(C_AI_LeSw_Valcom, LEVELSWITCH_VALCOM_MA_ON, LEVELSWITCH_VALCOM_MA_OFF, LEVELSWITCH_VALCOM_MA_WIN);
                        break;
                    case C_AI_LeSw_API:
                        LevelSwitchSensor = (AnalogInput *)new AILevelSwitch_mA(C_AI_LeSw_API, LEVELSWITCH_API_MA_ON, LEVELSWITCH_API_MA_OFF, LEVELSWITCH_API_MA_WIN);
                        break;
                    case C_AI_LeSw_Vega     :
                    case C_AI_LeSw_Vega62   :
                        LevelSwitchSensor = (AnalogInput *)new AILevelSwitchVega(C_AI_LeSw_Vega62, LEVELSWITCH_VEGA62_MA_ON, LEVELSWITCH_VEGA62_MA_OFF, LEVELSWITCH_VEGA62_MA_WIN, LEVELSWITCH_VEGA62_MA_TEST);
                        break;
                    case C_AI_LeSw_Vega64   :
                        LevelSwitchSensor = (AnalogInput *)new AILevelSwitchVega(C_AI_LeSw_Vega64, LEVELSWITCH_VEGA64_MA_ON, LEVELSWITCH_VEGA64_MA_OFF, LEVELSWITCH_VEGA64_MA_WIN, LEVELSWITCH_VEGA64_MA_TEST);
                        break;
                    }
                }
                LevelSwitchSensor->LoadConfigString(ConfigString);
                AnalogInList.push_back((AnalogInput *)LevelSwitchSensor);

                if ( Description.IsEmpty() ) {
                    Description = "LevSwitch";
                }
                LevelSwitchAlPtr = new AlarmLevelSwitch(this, Name, Description);
                AlarmSet.insert(LevelSwitchAlPtr);
                switch ( Key ) {
                case C_AI_LeSw_mA:
                case C_AI_LeSw_Valcom:
                case C_AI_LeSw_API:
                    break;
                case C_AI_LeSw_Vega62:
                    LevelSwitchAlPtr->SetAlarmDelay(5000);
                    break;
                }
                break;
            case C_AI_WATERINGRESS:
                LevelSwitchSensor = (AnalogInput *)new AIWaterIngressSensor(Key);
                LevelSwitchSensor->LoadConfigString(ConfigString);
                AnalogInList.push_back((AnalogInput *)LevelSwitchSensor);
                if ( Description.IsEmpty() ) {
                    Description = "WaterDetect";
                }

                LevelSwitchAlPtr = new AlarmLevelSwitch(this, Name, Description);
                AlarmSet.insert(LevelSwitchAlPtr);
                break;
            case C_AI_LeSw_ADCard:
                LevelSwitchSensor = (AnalogInput *)new AiLevelSwitchSensor_mV(Key);
                LevelSwitchSensor->LoadConfigString(ConfigString);
                AnalogInList.push_back((AnalogInput *)LevelSwitchSensor);
                if ( Description.IsEmpty() ) {
                    Description = "LevSwitch";
                }

                LevelSwitchAlPtr = new AlarmLevelSwitch(this, Name, Description);
                AlarmSet.insert(LevelSwitchAlPtr);
                break;
            case C_AI_COIL_IN:
                LevelSwitchSensor = (AnalogInput *)new AiCoilInSensor(Key);
                LevelSwitchSensor->LoadConfigString(ConfigString);
                AnalogInList.push_back((AnalogInput *)LevelSwitchSensor);
                if ( Description.IsEmpty() ) {
                    Description = "Alarm";
                }
                LevelSwitchAlPtr = new AlarmLevelSwitch(this, Name, Description);
                AlarmSet.insert(LevelSwitchAlPtr);
                break;
            case C_XPOS:
                XPos = ConfigString.ReadLong(ErrorLine);
                break;
            case C_YPOS:
                YPos = ConfigString.ReadLong(ErrorLine);
                break;
            case C_PAGE:
                Page = ConfigString.ReadLong(ErrorLine);
                break;
            case C_WARNING:
                IsWarning = true;
                break;
            case C_AI_LOC_BOTTOM      :
            case C_AI_LOC_MIDDLE      :
            case C_AI_LOC_UPPER       :
            case C_AI_LOC_DECK        :
            case C_AI_LOC_PUMP_ROOM   :
            case C_AI_LOC_ENGINE_ROOM :
                Location = Key;
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_PRO_END) );
    CopyAnalogList();

    if ( LevelSwitchSensor ) {
        LevelSwitchSensor->Location = Location;
    }
    AddAlarms(CompleteAlarmInfoList);
    AddSensorAlarms();
    SetChildUserRights();
    return ErrorLine;
}

//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
///////////////////////////////////////////////////////////////

void PROLevelSwitch::SaveSettings(TSNConfigString *SettingsString) {

    if ( IsModified || WriteAll ) {
        IsModified = false;
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", IDNumber);
        LocalString += KeyWord(Type) + IdNumStr + CrLfStr;
        set<AlarmBasic *>::iterator pBIt;
        for ( pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++ ) {
            AlarmBasic *element = *pBIt;
            if ( element && !element->Locked ) LocalString += (AnsiString)element->SaveSettings();
        }
        for ( unsigned j = 0; j < AnalogInList.size(); j++ ) {
            LocalString += AnalogInList[j]->SaveAISettings();
        }
        LocalString += KeyWord(C_PRO_END) + CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PROLevelSwitch::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                RestoreSettingsWarning((AnsiString)"Level switch " + Name + ":\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"Level switch " + Name + ":\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_CT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case C_AI_LeSw_ADCard   :
            case C_AI_LeSw_Valcom   :
            case C_AI_LeSw_API      :
            case C_AI_LeSw_Vega     :
            case C_AI_LeSw_Vega62   :
            case C_AI_LeSw_Vega64   :
            case C_AI_LeSw_HS       :
            case C_AI_LeSw_mA       :
            case C_AI_COIL_IN       :
                {
                    int AIIDNumber = SettingsString->ReadInteger(ErrorLine);
                    AnalogInput *AnalogInPtr = (AnalogInput *)FindObject(AIIDNumber);
                    if ( AnalogInPtr ) AnalogInPtr->RestoreAISettings(SettingsString);
                }
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_PRO_END) );
    if ( Master && NoError ) {
        SendData(CMD_GENERIC_STATIC_DATA);
    }

    return (NoError);
}



//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////
int PROLevelSwitch::FindPROStatus(AnsiString &MyString) {
    int PROStatus1 = ST_OK;
    int PROStatus2 = ST_OK;
    if ( HWFailure ) {
        PROStatus1 = ST_ERROR;
    }
    if ( PROStatus1 != ST_ERROR ) {
        switch ( State ) {
        case tSeaGoing      :
        case tTankCleaning  :
            PROStatus1 = ST_WARNING;
            break;
        default:
            break;
        }
    }
    if ( PROStatus1 != ST_ERROR ) {
        if ( LevelSwitchSensor ) {
            PROStatus2 = LevelSwitchSensor->FindPROStatus(MyString);
            if ( PROStatus2 > PROStatus1 ) {
                PROStatus1 = PROStatus2;
            }
        }
    }
    if ( PROStatus1 != ST_ERROR ) {
        bool AlActive = false;
        set<AlarmBasic *>::iterator pBIt;
        for ( pBIt = AlarmSet.begin(); !AlActive && pBIt != AlarmSet.end(); pBIt++ ) {
            AlarmBasic *Element = *pBIt;
            if ( Element && (Element->State != AlarmBasic::AlIdle) ) AlActive = true;
        }
        if ( AlActive ) {
            PROStatus2 = ST_ALARM;
        }
        if ( PROStatus2 > PROStatus1 ) PROStatus1 = PROStatus2;
    }
    MyString = FindStatusChar(PROStatus1);
    return (PROStatus1);
}

int  PROLevelSwitch::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
    case SVT_LEVEL_SWITCH_STATUS    :
        {
            MyRetValue = (float)Status;
            DecPnt = 0;
            Unit   = NO_UNIT;
        }
        break;
    default:
        Status = PROXRefObject::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int PROLevelSwitch::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_LEVEL_SWITCH_STATUS:
		MyString = LibGetValue(SVT_AL_STATE, LevelSwitchAlPtr);
        break;
    case SVT_PRO_STATUS:
		FindPROStatus(MyString);
        break;
    default:
        Status = PROXRefObject::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int PROLevelSwitch::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    //switch ( ValueId ) {
    //  default:
    Status = PROXRefObject::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
    //      break;
    //}
    if ( Status == E_NO_ERR ) {
        SetModifiedFlag();
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int PROLevelSwitch::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch ( ValueId ) {
    case SVT_LEVEL_SWITCH_STATUS:
        LevelSwitchSensor->SetNewStatus(bool(NewValue));
        break;
    default:
        Status = PRogramObject::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);

}

void PROLevelSwitch::Calculate(void) {
    HWFailure = false;
    if ( LevelSwitchSensor ) {
        float LSSwitchresult = LevelSwitchSensor->Calculate();
        int LSwitchStatus  = int(LSSwitchresult);

        IsFailure = LevelSwitchSensor->Failure;
        switch ( LevelSwitchSensor->Type ) {
        case C_AI_WATERINGRESS:
            if ( HWFailure || LevelSwitchSensor->HasActiveAlarms() ) {
                LSwitchStatus = LEVELSWITCH_HW_ERROR;
            } else if ( LSwitchStatus & 0x10 ) {
                LSwitchStatus = LEVELSWITCH_ON;
            } else {
                LSwitchStatus = LEVELSWITCH_OFF;
            }
            break;
        case C_AI_LeSw_ADCard   :
        case C_AI_LeSw_Valcom   :
        case C_AI_LeSw_API      :
        case C_AI_LeSw_Vega     :
        case C_AI_LeSw_Vega62   :
        case C_AI_LeSw_Vega64   :
        case C_AI_COIL_IN       :
        default:
            if ( HWFailure ) {
                LSwitchStatus = LEVELSWITCH_HW_ERROR;
            }
            break;
        }
        switch ( LSwitchStatus ) {
        case LEVELSWITCH_ON    :
            IsActive       = true;
            IsFailure      = false;
            break;
        case LEVELSWITCH_OFF   :
            IsActive       = false;
        case LEVELSWITCH_TEST  : // Don't touch the IsActive flag
        case LEVELSWITCH_LIGHT : // Don't touch the IsActive flag
            IsFailure      = false;
            break;
        case LEVELSWITCH_HW_ERROR:
            IsActive       = false;
            IsFailure      = false;
            AcknowledgeAlarms(AlarmSet);
            AcknowledgeSoftAlarms(LevelSwitchSensor->AlarmSet);
            break;
        case LEVELSWITCH_ERROR :
        default:
            IsActive       = false;
            IsFailure      = true;
            break;

        }
    }
    SendData();
}


void PROLevelSwitch::SimCalculate(void) {
    // Simulate a level
    HWFailure = false;
    IsActive = (rand() % 10 == 2);
}

int PROLevelSwitch::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2120  *pData = (ANPRO10_COMMAND_2120 *)data;
            IsActive       = pData->IsActive;
            IsFailure      = pData->IsFailure;
            IsNewData      = pData->IsNewData;
            State          = (TankState)pData->State;
            ErrorStatus    = E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int PROLevelSwitch::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2120 Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.ndb            = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo      = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.HWFailure      = HWFailure;
            Cmd.Data.IsNewData      = IsNewData;
            Cmd.Data.IsActive       = IsActive;
            Cmd.Data.IsFailure      = IsFailure;
            Cmd.Data.State          = State;

            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

void PROLevelSwitch::SetState(TankState newState) {
    switch ( newState ) {
    case tSeaGoing      :
    case tLoad          :
    case tDischarge     :
    case tTankCleaning  :
    case tUndefined     :
        State = newState;
        break;
    default:
        break;
    }
    if ( !ExcludeState ) {
        const AlarmBasic::StateAlarmTable AlarmSet[] = {     //tSeaGoing  ,tLoad     , tDischarge, tTankCleaning, tUndefined
            { (AlarmBasic *)LevelSwitchAlPtr, { EnableFalse, EnableTrue, EnableTrue, EnableFalse } },
        };
        for ( unsigned i = 0; i < NELEMENTS(AlarmSet); i++ ) {
            AlarmBasic *AlPtr = AlarmSet[i].AlarmPtr;
            if ( AlPtr ) {
                AlarmSet[i].AlarmPtr->Enable = AlarmSet[i].Enable[State];
            }
        }
    }
}

int PROLevelSwitch::WriteXML(char *StrBuf, bool IncAlarms) {
#ifdef ANWIN
    //return 0;
    AnsiString UnitStr;
    AnsiString PressureStr = LibGetValue(SVT_PRESSURE, this, 0, &UnitStr) + SpaceStr + UnitStr;
    // Alarm status and text
    //
    AnsiString AlMessageStr = "No alarm";
    int LEDStatus = TPC_LED_OFF;
    if ( !CompleteAlarmInfoList.empty() ) {
        bool ActiveAlarm = false;
        time_t NewestAlarmAct = 0;
        time_t NewestAlarmAck = 0;
        set<AlarmBasic *>::iterator pBIt;
        for ( pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++ ) {
            AlarmBasic *Element = *pBIt;
            if ( Element ) {
                switch ( Element->State ) {
                case AlarmBasic::AlIdle :
                    break;
                case AlarmBasic::AlActive :
                    if ( Element->Time_Rised > NewestAlarmAct ) {
                        NewestAlarmAct = Element->Time_Rised;
                        ActiveAlarm = true;
                        AlMessageStr = Element->Get_TPCMessage();
                        LEDStatus = TPC_LED_FLASH;
                    }
                    break;
                case AlarmBasic::AlAknowledged :
                    if ( !ActiveAlarm && (Element->Time_Acknowledged > NewestAlarmAck) ) {
                        NewestAlarmAck = Element->Time_Acknowledged;
                        AlMessageStr = Element->Get_TPCMessage();
                        LEDStatus = TPC_LED_ON;
                    }
                    break;
                }
            }
        }
    }

    int  tmpPtr = sprintf(StrBuf, "\t<Packet>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<PacketID>Freevalue</PacketID>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<TagID>%s</TagID>\r\n", TagName.c_str());
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Value>%i</Value>\r\n", LEDStatus);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Alarm>%s</Alarm>\r\n", AlMessageStr);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t</Packet>\r\n");
    return tmpPtr;
#else
    return 0;
#endif
}


