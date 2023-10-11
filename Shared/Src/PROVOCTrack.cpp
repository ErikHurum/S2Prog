#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
vector<PRogramObjectBase *>PROVOCTrack::AllObjVector;
vector<PRogramObjectBase *>PROVOCTrack::ObjVector;
set<PRogramObjectBase *>PROVOCTrack::ObjectSet;


PROVOCTrack::PROVOCTrack(bool AddToList) : PROXRefObject(AddToList) {
    Initiate();
    if (AddToList) {
        ObjectSet.insert(this);
        AllObjVector.push_back(this);
        AddToIOObjectList();
    }
    IDNumber = (C_PRO_WOCTRACK << 16) + ObjectSet.size();
}

PROVOCTrack::PROVOCTrack(int IdNum, PROXRefObject *CreatedFromTank, bool AddToList) : PROXRefObject(AddToList) {
    Initiate();
    if (CreatedFromTank) {
        CreatedFromThisTank = CreatedFromTank;
        ObjectSet.insert(this);
        AllObjVector.push_back(this);
        IDNumber = ((C_PRO_WOCTRACK << 16) + 0x1000) + ObjectSet.size();
        AddAlarms(CompleteAlarmInfoList);
    } else {
        AddToIOObjectList();
        ObjectSet.insert(this);
        AllObjVector.push_back(this);
        if (IdNum) {
            IDNumber = IdNum;
        } else {
            IDNumber = (C_PRO_WOCTRACK << 16) + ObjectSet.size();
        }
    }

}
//---------------------------------------------------------------------------

void PROVOCTrack::Initiate(void) {
    Type        = C_PRO_WOCTRACK;
    Temperature = 0;
	IGSRunning  = false;
    IGSVolume   = 0.0;
	Temperature = 0.0;
    Press1      = 0.0;
    Press2      = 0.0;
    Vol1        = 0.0;
    Vol2        = 0.0;
    Temp1       = 0.0;
    Temp2       = 0.0;
}
//---------------------------------------------------------------------------

PROVOCTrack::~PROVOCTrack(void) {
    ObjectSet.erase(this);
    EraseFromVector(ObjVector, this);
    EraseFromVector(AllObjVector, this);
}


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
void PROVOCTrack::WriteConfigToFile(TSNConfigString& ConfigString) {
    if (!CreatedFromThisTank) {
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", IDNumber);
        LocalString += KeyWord(C_PRO_TEMP) + TabStr1 + IdNumStr + CrLfStr;
        LocalString += MakeConfigString();   //common

        if (HighTempLimit != PROProjectInfo::HighTempLimit) {
            LocalString += TabStr1 + KeyWord(AL_LIM_HIGHTEMP) + FloatToAnsiString(HighTempLimit);
        }
        if (LowTempLimit != PROProjectInfo::LowTempLimit) {
            LocalString += TabStr1 + KeyWord(AL_LIM_LOWTEMP) + FloatToAnsiString(LowTempLimit);
        }
        for (unsigned i = 0; i < AnalogInList.size(); i++) {
            LocalString += AnalogInList[i]->MakeConfigString();     //common
        }

        LocalString += KeyWord(C_PRO_END) + CrLfStr;
        LocalString += CrLfStr;

        ConfigString.AddString(LocalString);
    }
}
//---------------------------------------------------------------------------

int PROVOCTrack::LoadConfigFromFile(TSNConfigString& ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    HighTempPtr           = new AlarmHighTemp(this);
    LowTempPtr            = new AlarmLowTemp(this);
    AlarmSet.insert(HighTempPtr);
    AlarmSet.insert(LowTempPtr);
    AddAlarms(CompleteAlarmInfoList);
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning((AnsiString)"Temperature " + Name, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning((AnsiString)"Temperature " + Name, InputKeyWord, ConfigString.LineCount);
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
            case C_AI_Pt100:
                {
                    AITempSensor_Pt100 *AnalogInPtr = new AITempSensor_Pt100();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_Pt1000:
                {
                    AITempSensor_Pt1000 *AnalogInPtr = new AITempSensor_Pt1000();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_TEMP_mA:
                {
                    AITempSensor_mA *AnalogInPtr = new AITempSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_TEMP_AD590:
                {
                    AITempSensor_AD590 *AnalogInPtr = new AITempSensor_AD590();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_DIFF_PRESSURE_mA:
                {
                    AIDiffPressSensor_mA *AnalogInPtr = new AIDiffPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_P906_0110:
            case C_AI_P906_0111:
                {
                    AIPressSensor_mV *AnalogInPtr = new AIPressSensor_mV(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
#ifndef ANCONF
                    AITempSensor_Pt1000 *tmpTemp = new AITempSensor_Pt1000(AnalogInPtr);
                    AnalogInList.push_back((AnalogInput *)tmpTemp);
#endif
                }
                break;
            case C_AI_1728:
                {
                    AIPressSensor_mV *AnalogInPtr = new AIPressSensor_mV(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_ATM_N_Ex:
            case C_AI_ATM_Ex:
            case C_AI_ATM_Ex_H:
            case C_AI_ATM_N_Ex_0_1:
			case C_AI_APT500	  :
			case C_AI_SPT900	  :
            case C_AI_Gen_4_20mA:
                {
                    AIPressSensor_mA *AnalogInPtr = new AIPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            }
        }
    }
    while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    CopyAnalogList();
    AddSensorAlarms();
    SetChildUserRights();
    return ErrorLine;
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////
void PROVOCTrack::SaveSettings(TSNConfigString *SettingsString) {
    if (IsModified || WriteAll) {
        IsModified = false;
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", IDNumber);
        LocalString += KeyWord(Type) + IdNumStr + CrLfStr;
        set<AlarmBasic *>::iterator pBIt;
        for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
            AlarmBasic *element = *pBIt;
            if (element && !element->Locked) LocalString += (AnsiString)element->SaveSettings();
        }
        for (unsigned j = 0; j < AnalogInList.size(); j++) {
            if (AnalogInList[j]) LocalString += AnalogInList[j]->SaveAISettings();
        }
        LocalString += KeyWord(C_PRO_END) + CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PROVOCTrack::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                RestoreSettingsWarning((AnsiString)"Temperature " + Name + ":\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"Temperature " + Name + ":\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_CT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case C_AI_P906_0110 :
            case C_AI_P906_0111 :
            case C_AI_Pt100     :
            case C_AI_Pt1000    :
            case C_AI_TEMP_mA   :
            case C_AI_TEMP_AD590:
                {
                    int AIIDNumber = SettingsString->ReadInteger(ErrorLine);
                    AnalogInput *AnalogInPtr = (AnalogInput *)FindObject(AIIDNumber);
                    if (AnalogInPtr) AnalogInPtr->RestoreAISettings(SettingsString);
                }
                break;
            }
        }
    }
    while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    return (NoError);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////
int PROVOCTrack::FindPROStatus(AnsiString& MyString) {
    int PROStatus1 = ST_OK;
    int PROStatus2 = ST_OK;

    if (HWFailure || !IsAvailableNewData()) {
        PROStatus1 = ST_ERROR;
    }
    if (PROStatus1 != ST_ERROR) {
        for (unsigned i = 0; i < AnalogInList.size() && (PROStatus1 != ST_ERROR); i++) {
            PROStatus2 = AnalogInList[i]->FindPROStatus(MyString);
            if (PROStatus2 > PROStatus1){
              PROStatus1 = PROStatus2;
            }
        }
    }
    if (PROStatus1 != ST_ERROR) {
        bool AlActive = false;
        set<AlarmBasic *>::iterator pBIt;
        for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
            AlarmBasic *Element = *pBIt;
            if (Element && (Element->State != AlarmBasic::AlIdle)) AlActive = true;
        }
        if (AlActive)	PROStatus2 = ST_ALARM;
        if (PROStatus2 > PROStatus1){
          PROStatus1 = PROStatus2;
        }
    }
    MyString = FindStatusChar(PROStatus1);
    return (PROStatus1);
}

int PROVOCTrack::GetValue(int ValueId, int Index, float& MyRetValue,  int& DecPnt, int& Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
	case
    case SVT_T4  :
    case SVT_T3  :
    case SVT_T1  :
    case SVT_TT  :
        {
            AnalogInput *SnsPtr = NULL;
            switch (ValueId) {
            case SVT_T1  :
                SnsPtr = FindAnalogInput(C_AI_LOC_BOTTOM);
                break;
            case SVT_T3  :
                SnsPtr = FindAnalogInput(C_AI_LOC_MIDDLE);
                break;
            case SVT_T4  :
                SnsPtr = FindAnalogInput(C_AI_LOC_UPPER);
                break;
            case SVT_TT  :
                SnsPtr = FindAnalogInput(C_AI_LOC_VAPOUR);
                break;
            }
            if (SnsPtr) {
                if (!SnsPtr->CanCalculate() || !SnsPtr->ResultOK) {
                    DecPnt = 1;
                    Unit   = TEMP_UNIT;
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                } else {
                    Status = SnsPtr->GetValue(SVT_AI_CALC_VAL, Index, MyRetValue,  DecPnt, Unit);
                }

            } else {
                DecPnt     = 1;
                Unit       = TEMP_UNIT;
                Status     = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_TEMP:
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        if (HasTemp && IsNewData) {
            MyRetValue = Temperature;
            Status     = StatusTemp;
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_HI_TEMP_ENABLE     :
    case SVT_LO_TEMP_ENABLE     :
    case SVT_HI_BOT_TEMP_ENABLE :
    case SVT_LO_BOT_TEMP_ENABLE :
    case SVT_HI_TEMP_LIMIT      :
    case SVT_LO_TEMP_LIMIT      :
    case SVT_HI_BOT_TEMP_LIMIT  :
    case SVT_LO_BOT_TEMP_LIMIT  :
    case SVT_HI_TEMP_STATE      :
    case SVT_LO_TEMP_STATE      :
    case SVT_HI_BOT_TEMP_STATE  :
    case SVT_LO_BOT_TEMP_STATE  :
    case SVT_HI_TEMP_VALUE      :
    case SVT_LO_TEMP_VALUE      :
    case SVT_HI_BOT_TEMP_VALUE  :
    case SVT_LO_BOT_TEMP_VALUE  :
        {
            int        tmpValKey;
            AlarmBasic *tmpPtr; = ( AlarmBasic* )
            switch (ValueId) {
            case SVT_HI_TEMP_ENABLE:
                tmpValKey = SVT_AL_ENABLE;
                tmpPtr = (AlarmBasic *)HighTempPtr;
                break;
            case SVT_LO_TEMP_ENABLE:
                tmpValKey = SVT_AL_ENABLE;
                tmpPtr = (AlarmBasic *)LowTempPtr;
                break;
            case SVT_HI_BOT_TEMP_ENABLE:
                tmpValKey = SVT_AL_ENABLE;
                tmpPtr = (AlarmBasic *)HighBotTempPtr;
                break;
            case SVT_LO_BOT_TEMP_ENABLE:
                tmpValKey = SVT_AL_ENABLE;
                tmpPtr = (AlarmBasic *)LowBotTempPtr;
                break;
            case SVT_HI_TEMP_LIMIT:
                tmpValKey = SVT_AL_LIMIT;
                tmpPtr = (AlarmBasic *)HighTempPtr;
                break;
            case SVT_LO_TEMP_LIMIT:
                tmpValKey = SVT_AL_LIMIT;
                tmpPtr = (AlarmBasic *)LowTempPtr;
                break;
            case SVT_HI_BOT_TEMP_LIMIT:
                tmpValKey = SVT_AL_LIMIT;
                tmpPtr = (AlarmBasic *)HighBotTempPtr;
                break;
            case SVT_LO_BOT_TEMP_LIMIT:
                tmpValKey = SVT_AL_LIMIT;
                tmpPtr = (AlarmBasic *)LowBotTempPtr;
                break;
            case SVT_HI_TEMP_LIMIT:
                tmpValKey = SVT_AL_STATE;
                tmpPtr = (AlarmBasic *)HighTempPtr;
                break;
            case SVT_LO_TEMP_LIMIT:
                tmpValKey = SVT_AL_STATE;
                tmpPtr = (AlarmBasic *)LowTempPtr;
                break;
            case SVT_HI_BOT_TEMP_STATE:
                tmpValKey = SVT_AL_LIMIT;
                tmpPtr = (AlarmBasic *)HighBotTempPtr;
                break;
            case SVT_LO_BOT_TEMP_STATE:
                tmpValKey = SVT_AL_LIMIT;
                tmpPtr = (AlarmBasic *)LowBotTempPtr;
                break;
            case SVT_HI_TEMP_VALUE:
                tmpValKey = SVT_AL_VALUE;
                tmpPtr = (AlarmBasic *)HighTempPtr;
                break;
            case SVT_LO_TEMP_VALUE:
                tmpValKey = SVT_AL_VALUE;
                tmpPtr = (AlarmBasic *)LowTempPtr;
                break;
            case SVT_HI_BOT_TEMP_VALUE:
                tmpValKey = SVT_AL_VALUE;
                tmpPtr = (AlarmBasic *)HighBotTempPtr;
                break;
            case SVT_LO_BOT_TEMP_VALUE:
                tmpValKey = SVT_AL_VALUE;
                tmpPtr = (AlarmBasic *)LowBotTempPtr;
                break;
            }
            if (tmpPtr) {
                Status = tmpPtr->GetValue( tmpValKey, 0, MyRetValue,  DecPnt, Unit );
            } else {
                Status = E_INVALID_POINTER;
            }
        }
        break;
    default:
        Status = PRogramObject::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int PROVOCTrack::GetStringValue(int ValueId, int Index, AnsiString& MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_PRO_STATUS:
        FindPROStatus(MyString);
        break;
    default:
        Status = PRogramObject::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int PROVOCTrack::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_TEMP:
        break;
    case SVT_HI_TEMP_ENABLE:
        if (HighTempPtr) {
            Status = HighTempPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_TEMP_ENABLE:
        if (LowTempPtr) {
            Status = LowTempPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_HI_TEMP_LIMIT:
        if (HighTempPtr) {
            Status = HighTempPtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_TEMP_LIMIT:
        if (LowTempPtr) {
            Status = LowTempPtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_HI_BOT_TEMP_ENABLE:
        if (HighBotTempPtr) {
            Status = HighBotTempPtr->PutValue( SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId );
        }
        break;
    case SVT_LO_BOT_TEMP_ENABLE:
        if (LowBotTempPtr) {
            Status = LowBotTempPtr->PutValue( SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId );
        }
        break;
    case SVT_HI_BOT_TEMP_LIMIT:
        if (HighBotTempPtr) {
            Status = HighBotTempPtr->PutValue( SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId );
        }
        break;
    case SVT_LO_BOT_TEMP_LIMIT:
        if (LowBotTempPtr) {
            Status = LowBotTempPtr->PutValue( SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId );
        }
        break;
    default:
        Status = PRogramObject::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    if (Status == E_NO_ERR) {
        SetModifiedFlag();
    }
    if (UnitId) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int PROVOCTrack::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_TEMP:
        HasTemp   	= true;
        IsNewData 	= true;
        Temperature = NewValue;
        StatusTemp 	= GETVAL_NO_ERR;
        break;
    default:
        Status = PRogramObject::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);
}

// Routines for object internode communication
int PROVOCTrack::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;

    switch (pCH->CommandNo) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2106 *pCommand = (ANPRO10_COMMAND_2106 *)data;
            HasTemp     = pCommand->HasTemp;
            HWFailure   = pCommand->HWFailure;
            IsNewData   = pCommand->IsNewData;
            StatusTemp  = pCommand->StatusTemp;
            Temperature        = pCommand->Temperature;
            ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int PROVOCTrack::SendData(U16 CommandNo) {
    int ErrorStatus = E_OK;
    switch (CommandNo) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2106 Cmd;
            Cmd.TxInfo.Port      = NULL;
            Cmd.TxInfo.rxAddr    = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId      = DEVICE_BROADCAST_TXU;
            Cmd.Data.CommandNo   = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.ndb         = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.ObjectId    = IDNumber;
            Cmd.Data.HasTemp     = HasTemp;
            Cmd.Data.HWFailure   = HWFailure;
            Cmd.Data.IsNewData   = IsNewData;
            Cmd.Data.StatusTemp  = StatusTemp;
            Cmd.Data.Temperature = Temperature;

            // post command on messageQ
            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus	=  E_OK;
        }
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

// EHSMark, must add correct words to dictionary
ValueList PROVOCTrack::VOCTrackValueList[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },
    { L_WORD338, L_WORD338, SVT_PRESSURE },
    { L_WORD112, L_WORD237, SVT_VOLUME },
    { L_WORD113, L_WORD237, SVT_VOLUME1 },
    { L_WORD360, L_WORD364, SVT_VOLUME2 },
    { L_WORD361, L_WORD365, SVT_PRESSURE1 },
    { L_WORD362, L_WORD366, SVT_PRESSURE2 },
    { L_WORD363, L_WORD367, SVT_DELTA_RELEASED_VOL },
    { L_WORD363, L_WORD367, SVT_TOTAL_RELEASED_VOL },
    { L_WORD360, L_WORD364, SVT_IGS_DELTA_SUPPLIED_VOL },
    { L_WORD360, L_WORD364, SVT_IGS_TOTAL_SUPPLIED_VOL },
    { L_WORD113, L_WORD237, SVT_START_TIME1 },
    { L_WORD360, L_WORD364, SVT_STOP_TIME2 },
};

ValueList* PROVOCTrack::GetValueInfoTable(int& Entries, int Index) {
    return GetValueInfoTableStatic(Entries, Index);
}

ValueList* PROVOCTrack::GetValueInfoTableStatic(int& Entries, int Index) {
    Entries = NELEMENTS(TempValueList);
    return (TempValueList);
}


void PROVOCTrack::Calculate(void) {
    SendData();
}

void PROVOCTrack::SimCalculate(void) {
    StatusTemp = GETVAL_NO_ERR;
    IsNewData  = true;
}

void PROVOCTrack::SetState(TankState newState) {
    switch (newState) {
    case tSeaGoing      :
        // Start logging
        State = newState;
        break;
    case tLoad          :
    case tDischarge     :
    case tTankCleaning  :
    case tUndefined     :
        // Stop logging
        State = newState;
        break;
    default:
        break;
    }
}


