#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
vector<PRogramObjectBase *>PROTemperature::AllObjVector;
vector<PRogramObjectBase *>PROTemperature::ObjVector;
set<PRogramObjectBase *>   PROTemperature::ObjectSet;

unsigned PROTemperature::MaxTempCnt             = 0;

PROTemperature::PROTemperature(bool AddToList, int LNumber) : PROXRefObject(AddToList) {
    LineNumber = LNumber;
    Initiate();
    if (AddToList) {
        ObjectSet.insert(this);
        AllObjVector.push_back(this);
        AddToIOObjectList();
    }
    SetIdNumber(this, 0,C_PRO_TEMP,AllObjVector);
    CreateAlarms();
}

PROTemperature::PROTemperature(int IdNum, PROXRefObject *CreatedFromTank, bool AddToList, int LNumber) : PROXRefObject(AddToList) {
    if (CreatedFromTank) {
        LineNumber = CreatedFromTank->GetLineNumber();
    }else{
        LineNumber = LNumber;
    }
    Initiate();
    ObjectSet.insert(this);
    AllObjVector.push_back(this);
    if (CreatedFromTank) {
        CreatedFromThisTank = CreatedFromTank;
        SetIdNumber(this, (C_PRO_TEMP << 16) | ( CreatedFromTank->IDNumber & 0x7fff),C_PRO_TEMP,AllObjVector,true);
    } else {
        AddToIOObjectList();
		SetIdNumber(this, IdNum,C_PRO_TEMP,AllObjVector);
    }

}
//---------------------------------------------------------------------------

void PROTemperature::Initiate(void) {
    HasTemp               = false;
    CreatedFromThisTank   = NULL;
    Type                  = C_PRO_TEMP;
    Temperature           = 0.0;
    Level                 = 0.0;
    VaporTemp             = 0.0;
    BottomTemp            = 0.0;
    BottomTempOK          = false;
    NotEmptyTank          = true;
    StatusTemp            = GETVAL_FLOAT_NOT_LEGAL;
    OutsideCnt            = MAX_OUTSIDE_WIN_CNT;            // Accept first reading
    HighTempLimit         = PROProjectInfo::HighTempLimit;
    LowTempLimit          = PROProjectInfo::LowTempLimit;
    TankType              = TANKTYPE_TEMPERATURE;
    HighTempPtr           = NULL;
    LowTempPtr            = NULL;
    HighBotTempPtr        = NULL;
    LowBotTempPtr         = NULL;
}
//---------------------------------------------------------------------------


void PROTemperature::CreateAlarms(void)
{
    HighTempPtr    = new AlarmHighTemp(this);
    LowTempPtr     = new AlarmLowTemp(this);
    HighTempPtr->Limit = HighTempLimit;
    LowTempPtr->Limit  = LowTempLimit;
    AlarmSet.insert(HighTempPtr);
    AlarmSet.insert(LowTempPtr);

    if ( AnalogInList.size() > 1) {
        HighBotTempPtr = new AlarmHighBotTemp(this);
        LowBotTempPtr  = new AlarmLowBotTemp(this);
        HighBotTempPtr->Limit = HighTempLimit;
        LowBotTempPtr->Limit  = LowTempLimit;
        AlarmSet.insert(HighBotTempPtr);
        AlarmSet.insert(LowBotTempPtr);

    }
    AddAlarms(CompleteAlarmInfoList);
    MaxTempCnt = MAX(AnalogInList.size(), MaxTempCnt);
}
//---------------------------------------------------------------------------

PROTemperature::~PROTemperature(void) {
    ObjectSet.erase(this);
    EraseFromVector(ObjVector, this);
    EraseFromVector(AllObjVector, this);
}
//---------------------------------------------------------------------------
void PROTemperature::SortAnalogInputs(void) {
    PRogramObject::SortAnalogInputs();
    for (unsigned j = 0; j < AnalogInList.size(); j++) {
        if (AnalogInList[j]->GetIsPressureSns()) {
            AnalogInList[j]->Location = C_AI_LOC_VAPOUR; // This should be the topmost sensor.
        } else {
            AnalogInList[j]->Location = C_AI_LOC_TEMP1 + j;
        }
    }
}


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
void PROTemperature::WriteConfigToFile(TSNConfigString &ConfigString) {
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

int PROTemperature::LoadConfigFromFile(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    bool NoError   = true;
    int  ErrorLine = 0;
    int  Key;
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
            case AL_LIM_HIGHTEMP:
                HighTempLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                if (NoError) {
                    HighTempPtr->Limit = HighTempLimit;
                }
                break;
            case AL_LIM_LOWTEMP:
                LowTempLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                if (NoError) {
                    LowTempPtr->Limit = LowTempLimit;
                }
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
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    CreateAlarms();
    SetChildUserRights();
    CopyAnalogList();
    AddSensorAlarms();
    return ErrorLine;
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////
void PROTemperature::SaveSettings(TSNConfigString *SettingsString) {
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

bool PROTemperature::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError   = true;
    int  ErrorLine = 0;
    int  Key;
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
            case ID_AL_HIGH_TEMP:
                if (HighTempPtr) {
                    HighTempPtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case ID_AL_LOW_TEMP:
                if (LowTempPtr) {
                    LowTempPtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case ID_AL_HIGH_BOT_TEMP:
                if (HighBotTempPtr) {
                    HighBotTempPtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case ID_AL_LOW_BOT_TEMP:
                if (LowBotTempPtr) {
                    LowBotTempPtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case C_AI_P906_0110         :
            case C_AI_P906_0111         :
            case C_AI_Pt100             :
            case C_AI_Pt1000            :
            case C_AI_TEMP_mA           :
            case C_AI_TEMP_AD590        :
            case C_AI_WATERINGR_TEMP    :
            case C_AI_WATERINGR_TEMP_P  :
            case C_AI_WATERINGR_TEMP_M  :


                {
                    int         AIIDNumber   = SettingsString->ReadInteger(ErrorLine);
					AnalogInput *AnalogInPtr = (AnalogInput *)FindObject(AIIDNumber);
					if (AnalogInPtr) {
						AnalogInPtr->RestoreAISettings(SettingsString);
					}else{
						RestoreSettingsWarning((AnsiString)"Temperature " + Name + ":\nSensor Id " + AnsiString(AIIDNumber) + " is not found!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
					}
                }
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    return (NoError);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////
int PROTemperature::FindPROStatus(AnsiString &MyString) {
    int PROStatus1 = ST_OK;
    int PROStatus2 = ST_OK;

    if (HWFailure) {
        PROStatus1 = ST_ERROR;
    }
    if (PROStatus1 != ST_ERROR) {
        for (unsigned i = 0; i < AnalogInList.size() && (PROStatus1 != ST_ERROR); i++) {
            PROStatus2 = AnalogInList[i]->FindPROStatus(MyString);
            if (PROStatus2 > PROStatus1) {
                PROStatus1 = PROStatus2;
            }
        }
    }
    if (PROStatus1 != ST_ERROR) {
        bool                        AlActive = false;
        set<AlarmBasic *>::iterator pBIt;
        for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
            AlarmBasic *Element = *pBIt;
            if (Element && (Element->State != AlarmBasic::AlIdle)) AlActive = true;
        }
        if (AlActive)	PROStatus2 = ST_ALARM;
        if (PROStatus2 > PROStatus1) {
            PROStatus1 = PROStatus2;
        }
    }
    MyString = FindStatusChar(PROStatus1);
    return (PROStatus1);
}

int PROTemperature::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_T1  :
    case SVT_T1_GAIN :
    case SVT_T1_OFFSET :
    case SVT_T2  :
    case SVT_T2_GAIN :
    case SVT_T2_OFFSET :
    case SVT_T3  :
    case SVT_T3_GAIN :
    case SVT_T3_OFFSET :
    case SVT_T4  :
    case SVT_T4_GAIN :
    case SVT_T4_OFFSET :
    case SVT_T5  :
    case SVT_T5_GAIN :
    case SVT_T5_OFFSET :
    case SVT_TT  :
    case SVT_TT_GAIN :
    case SVT_TT_OFFSET :
    case SVT_T1_ENABLE :
    case SVT_T2_ENABLE :
    case SVT_T5_ENABLE :
    case SVT_T3_ENABLE :
    case SVT_T4_ENABLE :
    case SVT_TP_ENABLE :
        {
            AnalogInput *SnsPtr = NULL;
            switch (ValueId) {
            case SVT_T1 :
            case SVT_T1_GAIN :
            case SVT_T1_OFFSET :
            case SVT_T1_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_TEMP1, AI_SENSOR_TEMP);
                break;
            case SVT_T2 :
            case SVT_T2_GAIN :
            case SVT_T2_OFFSET :
            case SVT_T2_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_TEMP2, AI_SENSOR_TEMP);
                break;
            case SVT_T3 :
            case SVT_T3_GAIN :
            case SVT_T3_OFFSET :
            case SVT_T3_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_TEMP3, AI_SENSOR_TEMP);
                break;
            case SVT_T4 :
            case SVT_T4_GAIN :
            case SVT_T4_OFFSET :
            case SVT_T4_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_TEMP4, AI_SENSOR_TEMP);
                break;
            case SVT_T5 :
            case SVT_T5_GAIN :
            case SVT_T5_OFFSET :
            case SVT_T5_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_TEMP5, AI_SENSOR_TEMP);
                break;
            case SVT_TT :
            case SVT_TT_GAIN :
            case SVT_TT_OFFSET :
            case SVT_TT_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_VAPOUR, AI_SENSOR_TEMP);
                if (!SnsPtr) {
                    SnsPtr = FindAnalogInput(C_AI_LOC_DECK, AI_SENSOR_TEMP);
                    if (!SnsPtr) {
                        SnsPtr = FindAnalogInput(C_AI_LOC_TEMP6, AI_SENSOR_TEMP);
                    }
                }
                break;
            }
            int SnsValId = SVT_NOT_DEFINED;
            switch (ValueId) {
            case SVT_T1_GAIN :
            case SVT_T2_GAIN :
            case SVT_T5_GAIN :
            case SVT_T3_GAIN :
            case SVT_T4_GAIN :
            case SVT_TT_GAIN :
                SnsValId = SVT_AI_GAIN;
                break;
            case SVT_T1_OFFSET :
            case SVT_T2_OFFSET :
            case SVT_T5_OFFSET :
            case SVT_T3_OFFSET :
            case SVT_T4_OFFSET :
            case SVT_TT_OFFSET :
                SnsValId = SVT_AI_OFFSET;
                break;
            case SVT_T1 :
            case SVT_T2 :
            case SVT_T5 :
            case SVT_T3 :
            case SVT_T4 :
            case SVT_TMP1 :
            case SVT_TMP2 :
            case SVT_TMP5 :
            case SVT_TMP3 :
            case SVT_TMP4 :
            case SVT_TT :
                SnsValId = SVT_AI_CALC_VAL;
                break;
            case SVT_T1_ENABLE :
            case SVT_T2_ENABLE :
            case SVT_T5_ENABLE :
            case SVT_T3_ENABLE :
            case SVT_T4_ENABLE :
            case SVT_TP_ENABLE :
                SnsValId = SVT_AI_ENABLE;
                break;

            }
            if (SnsPtr) {
                if ((SnsValId == SVT_AI_CALC_VAL) && (!SnsPtr->CanCalculate() || !SnsPtr->ResultOK)) {
                    DecPnt = 1;
                    Unit   = TEMP_UNIT;
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                } else {
                    Status = SnsPtr->GetValue(SnsValId, Index, MyRetValue,  DecPnt, Unit);
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
        if (IsOnline) {
            if (HasTemp && IsNewData) {
                MyRetValue = Temperature;
                Status     = StatusTemp;
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            MyRetValue = Temperature;
            Status     = GETVAL_OFFLINE;
        }
        break;
    case SVT_VAPOR_TEMP:
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        if (IsOnline) {
            if (HasTemp && IsNewData) {
                MyRetValue = VaporTemp;
                Status     = StatusTemp;
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            MyRetValue = Temperature;
            Status     = GETVAL_OFFLINE;
        }
        break;
    case SVT_HI_TEMP_ENABLE     :
    case SVT_LO_TEMP_ENABLE     :
    case SVT_HI_BOT_TEMP_ENABLE :
    case SVT_LO_BOT_TEMP_ENABLE :
    case SVT_HI_TEMP_LIMIT      :
    case SVT_LO_TEMP_LIMIT      :
    case SVT_HI_TEMP_STATE      :
    case SVT_LO_TEMP_STATE      :
    case SVT_HI_BOT_TEMP_LIMIT  :
    case SVT_LO_BOT_TEMP_LIMIT  :
    case SVT_HI_TEMP_VALUE      :
    case SVT_LO_TEMP_VALUE      :
    case SVT_HI_BOT_TEMP_VALUE  :
    case SVT_LO_BOT_TEMP_VALUE  :
    case SVT_HI_BOT_TEMP_STATE  :
    case SVT_LO_BOT_TEMP_STATE  :
        {
            int        tmpValKey;
            AlarmBasic *tmpPtr;
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
            case SVT_HI_TEMP_STATE:
                tmpValKey = SVT_AL_STATE;
                tmpPtr = (AlarmBasic *)HighTempPtr;
                break;
            case SVT_LO_TEMP_STATE:
                tmpValKey = SVT_AL_STATE;
                tmpPtr = (AlarmBasic *)LowTempPtr;
                break;
            case SVT_HI_BOT_TEMP_STATE:
                tmpValKey = SVT_AL_STATE;
                tmpPtr = (AlarmBasic *)HighBotTempPtr;
                break;
            case SVT_LO_BOT_TEMP_STATE:
                tmpValKey = SVT_AL_STATE;
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
                Status = tmpPtr->GetValue(tmpValKey, 0, MyRetValue,  DecPnt, Unit);
            } else {
                Status = GETVAL_NO_DISPLAY;
            }
        }
        break;
    default:
        Status = PRogramObject::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int PROTemperature::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
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

int PROTemperature::GetBitValue(int ValueId, int Index, bool &MyBit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_HI_TEMP_ENABLE     :
    case SVT_LO_TEMP_ENABLE     :
    case SVT_HI_BOT_TEMP_ENABLE :
    case SVT_LO_BOT_TEMP_ENABLE :
        {
            int        tmpValKey;
            AlarmBasic *tmpPtr;
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
            }
            if (tmpPtr) {
                Status = tmpPtr->GetBitValue(tmpValKey, 0, MyBit);
            } else {
                Status = GETVAL_NO_DISPLAY;
            }
        }
        break;
    default:
        Status = PRogramObject::GetBitValue(ValueId, Index, MyBit);
        break;
    }
    return (Status);
}


int PROTemperature::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status    = E_NO_ERR,
        ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_TEMP       :
    case SVT_VAPOR_TEMP :
        Temperature = ConvertToSi(NewValue, TEMP_UNIT, Status, MIN_TEMP, MAX_TEMP, Temperature);
        if (Status == E_NO_ERR) {
            if (!Master) {
				IsOnline = false;
            }
            if (CreatedFromThisTank ) {
                ((PROTank *)CreatedFromThisTank)->Temperature = Temperature;
                if (!Master) {
					CreatedFromThisTank->SetToOffline();
                }
            }
        }
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
    case SVT_HI_BOT_TEMP_ENABLE:
        if (HighBotTempPtr) {
            Status = HighBotTempPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_BOT_TEMP_ENABLE:
        if (LowBotTempPtr) {
            Status = LowBotTempPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
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
    case SVT_HI_BOT_TEMP_LIMIT:
        if (HighBotTempPtr) {
            Status = HighBotTempPtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_BOT_TEMP_LIMIT:
        if (LowBotTempPtr) {
            Status = LowBotTempPtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_T1  :
    case SVT_T1_GAIN :
    case SVT_T1_OFFSET :
    case SVT_T2  :
    case SVT_T2_GAIN :
    case SVT_T2_OFFSET :
    case SVT_T3  :
    case SVT_T3_GAIN :
    case SVT_T3_OFFSET :
    case SVT_T4  :
    case SVT_T4_GAIN :
    case SVT_T4_OFFSET :
    case SVT_T5  :
    case SVT_T5_GAIN :
    case SVT_T5_OFFSET :
    case SVT_TT  :
    case SVT_TT_GAIN :
    case SVT_TT_OFFSET :
    case SVT_T1_ENABLE :
    case SVT_T2_ENABLE :
    case SVT_T5_ENABLE :
    case SVT_T3_ENABLE :
    case SVT_T4_ENABLE :
    case SVT_TP_ENABLE :
        {
            AnalogInput *SnsPtr = NULL;
            switch (ValueId) {
            case SVT_T1 :
            case SVT_T1_GAIN :
            case SVT_T1_OFFSET :
            case SVT_T1_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_TEMP1, AI_SENSOR_TEMP);
                break;
            case SVT_T2 :
            case SVT_T2_GAIN :
            case SVT_T2_OFFSET :
            case SVT_T2_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_TEMP2, AI_SENSOR_TEMP);
                break;
            case SVT_T3 :
            case SVT_T3_GAIN :
            case SVT_T3_OFFSET :
            case SVT_T3_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_TEMP3, AI_SENSOR_TEMP);
                break;
            case SVT_T4 :
            case SVT_T4_GAIN :
            case SVT_T4_OFFSET :
            case SVT_T4_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_TEMP4, AI_SENSOR_TEMP);
                break;
            case SVT_T5 :
            case SVT_T5_GAIN :
            case SVT_T5_OFFSET :
            case SVT_T5_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_TEMP5, AI_SENSOR_TEMP);
                break;
            case SVT_TT :
            case SVT_TT_GAIN :
            case SVT_TT_OFFSET :
            case SVT_TT_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_VAPOUR, AI_SENSOR_TEMP);
                if (!SnsPtr) {
                    SnsPtr = FindAnalogInput(C_AI_LOC_DECK, AI_SENSOR_TEMP);
                    if (!SnsPtr) {
                        SnsPtr = FindAnalogInput(C_AI_LOC_TEMP6, AI_SENSOR_TEMP);
                    }
                }
                break;
            }
            int SnsValId = SVT_NOT_DEFINED;
            switch (ValueId) {
            case SVT_T1_GAIN :
            case SVT_T2_GAIN :
            case SVT_T5_GAIN :
            case SVT_T3_GAIN :
            case SVT_T4_GAIN :
            case SVT_TT_GAIN :
                SnsValId = SVT_AI_GAIN;
                break;
            case SVT_T1_OFFSET :
            case SVT_T2_OFFSET :
            case SVT_T5_OFFSET :
            case SVT_T3_OFFSET :
            case SVT_T4_OFFSET :
            case SVT_TT_OFFSET :
                SnsValId = SVT_AI_OFFSET;
                break;
            case SVT_T1 :
            case SVT_T2 :
            case SVT_T5 :
            case SVT_T3 :
            case SVT_T4 :
            case SVT_TT :
                SnsValId = SVT_AI_CALC_VAL;
                break;
            case SVT_T1_ENABLE :
            case SVT_T2_ENABLE :
            case SVT_T5_ENABLE :
            case SVT_T3_ENABLE :
            case SVT_T4_ENABLE :
            case SVT_TT_ENABLE :
                SnsValId = SVT_AI_ENABLE;
                break;

            }
            if (SnsPtr) {
                Status = SnsPtr->PutValue(SnsValId, Index, NewValue, Local, &ValUnitId);
            } else {
                Status     = GETVAL_NOT_AVAILABLE;
            }
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

int PROTemperature::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_TEMP:
        HasTemp   	= true;
        IsNewData 	= true;
        Temperature = NewValue;
        StatusTemp 	= GETVAL_NO_ERR;
        break;
    case SVT_HI_TEMP_LIMIT:
        if (HighTempPtr) {
            Status = HighTempPtr->PutFloatValue(SVT_AL_LIMIT, NewValue);
        }
        break;
    case SVT_LO_TEMP_LIMIT:
        if (LowTempPtr) {
            Status = LowTempPtr->PutFloatValue(SVT_AL_LIMIT, NewValue);
        }
        break;
    case SVT_HI_BOT_TEMP_LIMIT:
        if (HighBotTempPtr) {
            Status = HighBotTempPtr->PutFloatValue(SVT_AL_LIMIT, NewValue);
        }
        break;
    case SVT_LO_BOT_TEMP_LIMIT:
        if (LowBotTempPtr) {
            Status = LowBotTempPtr->PutFloatValue(SVT_AL_LIMIT, NewValue);
        }
        break;
    default:
        Status = PRogramObject::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);
}

int PROTemperature::PutBitValue(int ValueId, int Index, bool NewValue){
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_HI_TEMP_ENABLE     :
    case SVT_LO_TEMP_ENABLE     :
    case SVT_HI_BOT_TEMP_ENABLE :
    case SVT_LO_BOT_TEMP_ENABLE :
        {
            AlarmBasic *AlPtr = NULL;
            switch ( ValueId ) {
            case SVT_HI_TEMP_ENABLE       :
                AlPtr = (AlarmBasic *)HighTempPtr;
                break;
            case SVT_LO_TEMP_ENABLE       :
                AlPtr = (AlarmBasic *)LowTempPtr;
                break;
            case SVT_HI_BOT_TEMP_ENABLE  :
                AlPtr = (AlarmBasic *)HighBotTempPtr;
                break;
            case SVT_LO_BOT_TEMP_ENABLE  :
                AlPtr = (AlarmBasic *)LowBotTempPtr;
                break;
            }
            if ( AlPtr ) {
                Status = AlPtr->PutBitValue(SVT_AL_ENABLE, 0, NewValue);
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_HI_TEMP_AL_ACK      :
    case SVT_LO_TEMP_AL_ACK      :
    case SVT_HI_BOT_TEMP_AL_ACK  :
    case SVT_LO_BOT_TEMP_AL_ACK  :
        {
            AlarmBasic *AlPtr = NULL;
            switch ( ValueId ) {
            case SVT_HI_TEMP_AL_ACK       :
                AlPtr = (AlarmBasic *)HighTempPtr;
                break;
            case SVT_LO_TEMP_AL_ACK       :
                AlPtr = (AlarmBasic *)LowTempPtr;
                break;
            case SVT_HI_BOT_TEMP_AL_ACK  :
                AlPtr = (AlarmBasic *)HighBotTempPtr;
                break;
            case SVT_LO_BOT_TEMP_AL_ACK  :
                AlPtr = (AlarmBasic *)LowBotTempPtr;
                break;
            }
            if ( AlPtr ) {
                Status = AlPtr->PutBitValue(SVT_AL_ACKNOWLEDGE, 0, NewValue);
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    default:
        Status = PRogramObject::PutBitValue(ValueId, Index, NewValue);
        break;
    }
    return (Status);
}

// Routines for object internode communication
int PROTemperature::ReceiveData(U8 *data) {
    int                    ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH        = (ANPRO10_CommandHeading *)data;

    switch (pCH->CommandNo) {
    case CMD_GENERIC_REALTIME_DATA:
        if (IsOnline) {
            ANPRO10_COMMAND_2106 *pCommand = (ANPRO10_COMMAND_2106 *)data;
            HasTemp     = pCommand->HasTemp;
            HWFailure   = pCommand->HWFailure;
            IsNewData   = pCommand->IsNewData;
            StatusTemp  = pCommand->StatusTemp;
            Temperature = pCommand->Temperature;
            VaporTemp   = pCommand->VaporTemp;
            BottomTemp  = pCommand->BottomTemp;
            IsOnline    = pCommand->IsOnline;
            if (CreatedFromThisTank) {
                CreatedFromThisTank->SetTemperature(Temperature);
            }
            ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int PROTemperature::SendData(U16 CommandNo) {
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
            Cmd.Data.VaporTemp   = VaporTemp;
            Cmd.Data.BottomTemp  = BottomTemp;
            Cmd.Data.IsOnline    = IsOnline;
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

bool PROTemperature::IsTemperatureInsideWindow(float NewValue, float OldValue) {
    bool AcceptValue = true;
    if (fabs(NewValue - OldValue) > PROProjectInfo::TemperatureWindowTmpLim) {
        if (++OutsideCnt > PROProjectInfo::TemperatureWindowMaxCnt) {
            OutsideCnt  = 0;
            AcceptValue = true;
        } else {
            AcceptValue = false;
        }
    } else {
        OutsideCnt  = 0;
        AcceptValue = true;
    }
    return (AcceptValue);
}

ValueList PROTemperature::TempValueList1[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },                    // {"Unused"    ,"",SVT_BLANK},
    { L_WORD338, L_WORD338, SVT_TEMP },                     // {"Temp"      ,"Temp",SVT_TEMP},
    { L_WORD1049, L_WORD1049, SVT_VAPOR_TEMP },               // {"VaporTemp"      ,"VaporTemp",SVT_TEMP},
    { L_WORD112, L_WORD237, SVT_HI_TEMP_LIMIT },            // {"High Temp" ,"",SVT_HI_TEMP_LIMIT},
    { L_WORD113, L_WORD237, SVT_LO_TEMP_LIMIT },            // {"Low Temp"  ,"",SVT_LO_TEMP_LIMIT},
    { L_WORD1060, L_WORD1062, SVT_HI_BOT_TEMP_LIMIT },       // {"High Bot Temp" ,"",SVT_HI_TEMP_LIMIT},
    { L_WORD1061, L_WORD1063, SVT_LO_BOT_TEMP_LIMIT },       // {"Low Bot Temp"  ,"",SVT_LO_TEMP_LIMIT},
    { L_WORD985, L_WORD364, SVT_T1 },                       // {"Bot Temp"  ,"BT",SVT_T1},
    { L_WORD986, L_WORD1039, SVT_T2 },                       // {"Mid Temp"  ,"MT",SVT_T2},
    { L_WORD987, L_WORD365, SVT_T3 },                       // {"Upp Temp"  ,"UT",SVT_T3},
    { L_WORD988, L_WORD365, SVT_T4 },                       // {"Upp Temp"  ,"UT",SVT_T3},
    { L_WORD989, L_WORD365, SVT_T5 },                       // {"Upp Temp"  ,"UT",SVT_T3},
    { L_WORD363, L_WORD367, SVT_TT },                       // {"Top Temp"  ,"TT",SVT_TT},
};


ValueList PROTemperature::TempValueList2[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },                    // {"Unused"    ,"",SVT_BLANK},
    { L_WORD338, L_WORD338, SVT_TEMP },                     // {"Temp"      ,"Temp",SVT_TEMP},
    { L_WORD1049, L_WORD1049, SVT_VAPOR_TEMP },               // {"VaporTemp"      ,"VaporTemp",SVT_TEMP},
    { L_WORD112, L_WORD237, SVT_HI_TEMP_LIMIT },            // {"High Temp" ,"",SVT_HI_TEMP_LIMIT},
    { L_WORD113, L_WORD237, SVT_LO_TEMP_LIMIT },            // {"Low Temp"  ,"",SVT_LO_TEMP_LIMIT},
    { L_WORD1060, L_WORD1062, SVT_HI_BOT_TEMP_LIMIT },       // {"High Bot Temp" ,"",SVT_HI_TEMP_LIMIT},
    { L_WORD1061, L_WORD1063, SVT_LO_BOT_TEMP_LIMIT },       // {"Low Bot Temp"  ,"",SVT_LO_TEMP_LIMIT},
    { L_WORD360, L_WORD364 , SVT_T1 },                       // {"Temp 1"  ,"BT",SVT_T1},
    { L_WORD361, L_WORD1039, SVT_T2 },                       // {"Temp 2"  ,"MT",SVT_T2},
    { L_WORD362, L_WORD365 , SVT_T3 },                       // {"Temp 3"  ,"UT",SVT_T3},
    { L_WORD988, L_WORD832 , SVT_T4 },                       // {"Temp 4"  ,"UT",SVT_T3},
    { L_WORD989, L_WORD1040, SVT_T5 },                       // {"Temp 5"  ,"UT",SVT_T3},
    { L_WORD363, L_WORD367 , SVT_TT },                       // {"Top Temp"  ,"TT",SVT_TT},
};
ValueList PROTemperature::TempAlarmValueList[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },                    // {"Unused"    ,"",SVT_BLANK},
    { L_WORD338, L_WORD338, SVT_TEMP },                     // {"Temp"      ,"Temp",SVT_TEMP},
    { L_WORD1049, L_WORD1049, SVT_VAPOR_TEMP },               // {"VaporTemp"      ,"VaporTemp",SVT_TEMP},
    { L_WORD112, L_WORD237, SVT_HI_TEMP_LIMIT },            // {"High Temp" ,"",SVT_HI_TEMP_LIMIT},
    { L_WORD113, L_WORD237, SVT_LO_TEMP_LIMIT },            // {"Low Temp"  ,"",SVT_LO_TEMP_LIMIT},
    { L_WORD1060, L_WORD1062, SVT_HI_BOT_TEMP_LIMIT },        // {"Unused"    ,"",SVT_BLANK},
    { L_WORD1061, L_WORD1063, SVT_LO_BOT_TEMP_LIMIT },       // {"Low Bot Temp"  ,"",SVT_LO_TEMP_LIMIT},
};

ValueList PROTemperature::TempSensorValueList1[] =  {
    { L_WORD304 , L_WORD237 , SVT_BLANK },                  // {"Unused"    ,"",SVT_BLANK},
    { L_WORD338 , L_WORD338 , SVT_TEMP },                   // {"Temp"      ,"Temp",SVT_TEMP},
    { L_WORD1049, L_WORD1049, SVT_VAPOR_TEMP },             // {"VaporTemp"      ,"VaporTemp",SVT_TEMP},
    { L_WORD830 , L_WORD830 , SVT_T1 },                      // {"Bot Temp" ,"BT"  ,SVT_BT},
    { L_WORD1039, L_WORD1039, SVT_T2 },                      // {"Mid Temp" ,"MT"  ,SVT_MT},
    { L_WORD831 , L_WORD831 , SVT_T3 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD832 , L_WORD832 , SVT_T4 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD1040, L_WORD1040, SVT_T5 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD363 , L_WORD367 , SVT_TT },                      // {"Top Temp" ,"TT"  ,SVT_TT},
    { L_WORD822 , L_WORD834 , SVT_T1_GAIN   },                 // {"BT Gain"   ,"BTGn",SVT_T1_GAIN},
    { L_WORD1035, L_WORD1041, SVT_T2_GAIN   },                 // {"MT Gain"   ,"MTGn",SVT_T3_GAIN},
    { L_WORD823 , L_WORD835 , SVT_T3_GAIN   },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD824 , L_WORD836 , SVT_T4_GAIN   },                 // {"T4 Gain"   ,"TTGn",SVT_TT_GAIN},
    { L_WORD1036, L_WORD1042, SVT_T5_GAIN   },                 // {"T5 Gain"   ,"T5Gn",SVT_TT_GAIN},
    { L_WORD825 , L_WORD837 , SVT_TT_GAIN   },                 // {"TT Gain"   ,"TTGn",SVT_TT_GAIN},
    { L_WORD826 , L_WORD838 , SVT_T1_OFFSET },               // {"BT Offset" ,"BTOf",SVT_T1_OFFSET},
    { L_WORD1037, L_WORD1043, SVT_T2_OFFSET },               // {"MT Offset" ,"MTOf",SVT_T3_OFFSET},
    { L_WORD827 , L_WORD839 , SVT_T3_OFFSET },               // {"UT Offset" ,"UTOf",SVT_T4_OFFSET},
    { L_WORD828 , L_WORD840 , SVT_T4_OFFSET },               // {"T4 Offset" ,"T4Of",SVT_T4_OFFSET},
    { L_WORD1038, L_WORD1044, SVT_T5_OFFSET },               // {"T5 Offset" ,"T5Of",SVT_T4_OFFSET},
    { L_WORD829 , L_WORD841 , SVT_TT_OFFSET },               // {"TT Offset" ,"TTOf",SVT_TT_OFFSET},
};


ValueList PROTemperature::TempSensorValueList2[] =  {
    { L_WORD304 , L_WORD237 , SVT_BLANK  },                  // {"Unused"    ,"",SVT_BLANK},
    { L_WORD338 , L_WORD338 , SVT_TEMP   },                  // {"Temp"      ,"Temp",SVT_TEMP},
    { L_WORD1049, L_WORD1049, SVT_VAPOR_TEMP },              // {"VaporTemp"      ,"VaporTemp",SVT_TEMP},
    { L_WORD360 , L_WORD830 , SVT_T1      },                 // {"Bot Temp" ,"BT"  ,SVT_BT},
    { L_WORD361 , L_WORD1039, SVT_T2      },                 // {"Mid Temp" ,"MT"  ,SVT_MT},
    { L_WORD362 , L_WORD831 , SVT_T3      },                 // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD988 , L_WORD366 , SVT_T4      },                 // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD989 , L_WORD1040, SVT_T5      },                 // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD363 , L_WORD367 , SVT_TT      },                 // {"Top Temp" ,"TT"  ,SVT_TT},
    { L_WORD822 , L_WORD834 , SVT_T1_GAIN },                 // {"BT Gain"   ,"BTGn",SVT_T1_GAIN},
    { L_WORD1035, L_WORD1041, SVT_T2_GAIN },                 // {"MT Gain"   ,"MTGn",SVT_T3_GAIN},
    { L_WORD823 , L_WORD835 , SVT_T3_GAIN },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD824 , L_WORD836 , SVT_T4_GAIN },                 // {"T4 Gain"   ,"TTGn",SVT_TT_GAIN},
    { L_WORD1036, L_WORD1042, SVT_T5_GAIN },                 // {"T5 Gain"   ,"T5Gn",SVT_TT_GAIN},
    { L_WORD825 , L_WORD837 , SVT_TT_GAIN },                 // {"TT Gain"   ,"TTGn",SVT_TT_GAIN},
    { L_WORD826 , L_WORD838 , SVT_T1_OFFSET },               // {"BT Offset" ,"BTOf",SVT_T1_OFFSET},
    { L_WORD1037, L_WORD1043, SVT_T2_OFFSET },               // {"MT Offset" ,"MTOf",SVT_T3_OFFSET},
    { L_WORD827 , L_WORD839 , SVT_T3_OFFSET },               // {"UT Offset" ,"UTOf",SVT_T4_OFFSET},
    { L_WORD828 , L_WORD840 , SVT_T4_OFFSET },               // {"T4 Offset" ,"T4Of",SVT_T4_OFFSET},
    { L_WORD1038, L_WORD1044, SVT_T5_OFFSET },               // {"T5 Offset" ,"T5Of",SVT_T4_OFFSET},
    { L_WORD829 , L_WORD841 , SVT_TT_OFFSET },               // {"TT Offset" ,"TTOf",SVT_TT_OFFSET},
};

ValueList* PROTemperature::GetValueInfoTable(int &Entries, int Index) {
    return GetValueInfoTableStatic(Entries, Index);
}


ValueList* PROTemperature::GetValueInfoTableStatic(int &Entries, int Index) {
    ValueList *tmpPtr;
    switch (Index) {
    case TAB_TANK_VALUES:
        if (MaxTempCnt > 4) {
            Entries = NELEMENTS(TempValueList1);
            tmpPtr = TempValueList1;
        } else {
            Entries = NELEMENTS(TempValueList2);
            tmpPtr = TempValueList2;
        }
        break;
    case TAB_ALARM_LIMITS:
        Entries = NELEMENTS(TempAlarmValueList);
        tmpPtr = TempAlarmValueList;
        break;
    case TAB_SENSOR_VALUES:
        if (MaxTempCnt > 3) {
            Entries = NELEMENTS(TempSensorValueList1);
            tmpPtr = TempSensorValueList1;
        } else {
            Entries = NELEMENTS(TempSensorValueList2);
            tmpPtr = TempSensorValueList2;
        }
        break;
    }
    return (tmpPtr);
}


void PROTemperature::Calculate(void) {
    if (!AnalogInList.empty()) {
        float WetSum            = 0.0;
        float DrySum            = 0.0;
        float TopSubmergedTemp  = -273.15;
        float TopSensorLocation = 0.0;
        int   WetCnt            = 0;
        int   DryCnt            = 0;
        int   HWFailureCnt      = 0;
        float tmpTemp           = 0.0;
        bool  BotSnsNearBot     = true;
        bool  hasSubmergedSensor= false;
        for (unsigned i = 0; i < AnalogInList.size(); i++) {
            AITempSensor *SnsPtr = (AITempSensor *)AnalogInList[i];
            if (!SnsPtr->GetIsPressureSns()) {
                float        Tmp     = SnsPtr->Calculate();
                if (SnsPtr->ResultOK) {
                    StatusTemp = GETVAL_NO_ERR;
                    float AdjustedDistance = SnsPtr->AdjustedDistance;
                    if (AdjustedDistance < Level) { // See if the sensor is submerged
                        hasSubmergedSensor = true;
                        if (TopSensorLocation < AdjustedDistance ) {
                            TopSensorLocation = AdjustedDistance;
                            TopSubmergedTemp  = Tmp;
                        }
                        if (SnsPtr->Location == C_AI_LOC_TEMP1) {
                            BottomTemp     = Tmp;
                            BottomTempOK   = true;
                            if (AdjustedDistance < BOT_TEMP_DISTANCE_LIMIT) {
                                BotSnsNearBot = true;
                            } else {
                                BotSnsNearBot = false;
                            }
                        } else{
                            WetSum += Tmp;
                            WetCnt++;
                        }
                    } else { // Sensor not submerged
                        DrySum += Tmp;
                        DryCnt++;
                        if (SnsPtr->Location == C_AI_LOC_TEMP1) {
                            BottomTemp   = Tmp;
                            BottomTempOK = true;
                        }
                    }
                } else {
                    HWFailureCnt++;
                    if (SnsPtr->Location == C_AI_LOC_TEMP1) {
                        BottomTempOK   = false;
                    }
                }
            }
        }   // End for
        if (unsigned(HWFailureCnt) == AnalogInList.size()) {
            HWFailure  = true;
            HasTemp    = false;
            StatusTemp = GETVAL_FLOAT_NOT_LEGAL;
            SetAlarmsToNormal(AlarmSet);
        } else {
            HWFailure = false;
            // If level under 5 cm, Use all the temp sensors exept top to calculate an
            // average temp.
            if (NotEmptyTank) {
                if ( hasSubmergedSensor ) { // First see if we have submerged sensors
                    if (BotSnsNearBot && BottomTempOK) {
                        // Most likely P906 system with Only bottom and mid sensor. Bottom sensor is weighted with 1/4
                        switch (WetCnt) {
                        case 0:
                            tmpTemp = BottomTemp;
                            break;
                        case 1:
                            tmpTemp = (3 * WetSum + BottomTemp) / 4;
                            break;
                        default:
                            tmpTemp = WetSum / WetCnt;
                            break;
                        }
                    } else {
                        if (BottomTempOK && !BotSnsNearBot) { // See if we can use the bottom sensor
                            WetSum += BottomTemp;
                            WetCnt++;
                        }
                        tmpTemp = WetSum / WetCnt;
                    }

                    if (DryCnt) {
                        VaporTemp = DrySum / DryCnt;
                    } else {
                        // If all sensors are submerged, VapourTemp must be near the liquid Temperature from the uppermost temp sensor
                        VaporTemp = TopSubmergedTemp;
                    }
                } else {
                    if (BottomTempOK) { // See if we can use the bottom sensor
                        DrySum += BottomTemp;
                        DryCnt++;
                    }
                    // If all sensors are dry, VapourTemp must be equal to the average of all the sensors
                    if (DryCnt) {
                        VaporTemp = DrySum / DryCnt;
                        tmpTemp   = VaporTemp;
                        if (BottomTempOK) { // See if we can use the bottom sensor
                            tmpTemp   = BottomTemp;
                        }
                    }
                }
            } else { // else NotEmptyTank
                if (DryCnt) {
                    VaporTemp = DrySum / DryCnt;
                }
                // Set Temperature to BottomTemp
                tmpTemp = BottomTemp;
            }
            if (! PROProjectInfo::UseTemperatureWindow || IsTemperatureInsideWindow(tmpTemp, Temperature)) {
                Temperature = tmpTemp;
            }

            HasTemp = (bool)(DryCnt + WetCnt) || BottomTempOK;
            if (HasTemp) {
                StatusTemp = GETVAL_NO_ERR;
            } else {
                StatusTemp = GETVAL_FLOAT_NOT_LEGAL;
            }
        }

    } else {
        // We should never get here, This indicates taht no tempsensors are available
        StatusTemp = GETVAL_FLOAT_NOT_LEGAL;
        Temperature = 0.0;
    }
    if (CreatedFromThisTank) {
        CreatedFromThisTank->SetTemperature(Temperature);
    }
    SendData();
}

void PROTemperature::SimCalculate(void) {
    StatusTemp = GETVAL_NO_ERR;
    HasTemp    = true;
    IsNewData  = true;
    if (PROProjectInfo::SimulateFixedValues) {
        Temperature = (IDNumber & 0xFFF);
    } else {
        Calculate();
        /*
        if (Temperature < 10.0) {
            Temperature = 10.0;
        }
        Temperature += SimulatorSign * (rand() % 10) / 100.0;
        if (Temperature > 50.0 || Temperature < 10.0) {
            SimulatorSign = -SimulatorSign;
        }
        */
    }

    if (CreatedFromThisTank) {
        ((PROTank *)CreatedFromThisTank)->Temperature = Temperature;
    }
}

void PROTemperature::SetState(TankState newState) {
    switch (newState) {
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
    if (!ExcludeState && newState != tUndefined) {
        const AlarmBasic::StateAlarmTable AlarmSet[] = {   //tSeaGoing       , tLoad             , tDischarge        , tTankCleaning, tUndefined
            { (AlarmBasic *)HighTempPtr, { EnableUsePrevious, EnableUsePrevious, EnableUsePrevious, EnableNoMemFalse } },
            { (AlarmBasic *)LowTempPtr, { EnableUsePrevious, EnableUsePrevious, EnableUsePrevious, EnableNoMemFalse } },
            { (AlarmBasic *)HighBotTempPtr, { EnableUsePrevious, EnableUsePrevious, EnableUsePrevious, EnableNoMemFalse } },
            { (AlarmBasic *)LowBotTempPtr, { EnableUsePrevious, EnableUsePrevious, EnableUsePrevious, EnableNoMemFalse } },
        };
        for (unsigned i = 0; i < NELEMENTS(AlarmSet); i++) {
            AlarmBasic *AlPtr = AlarmSet[i].AlarmPtr;
            if (AlPtr && !AlPtr->Locked) {
                AlarmSet[i].AlarmPtr->SetEnable(AlarmSet[i].Enable[State]);
            }
        }
    }
}

float PROTemperature::GetTemperature(void) {
    if (IsOnline) {
        if (HasTemp && IsNewData) {
            return Temperature;
        } else {
            return 0.0;
        }
    } else {
        return Temperature;
    }

}
void PROTemperature::SetTemperature(float NewTemp) {
    Temperature = NewTemp;
}

bool PROTemperature::IsAvailableNewData(void) {
    bool Expired;
    if (abs(double(clock() - TimeStamp)) < 5 * DATA_EXPIRATION_TIME) {
        Expired = false;
    } else {
        Expired = true;
    }
    return !Expired;
    //return bool(abs(clock() - TimeStamp)<3*DATA_EXPIRATION_TIME);
}


void PROTemperature::UpdateLevelInfo(float pLevel, bool pEmpty) {
    Level 	     = pLevel;
    NotEmptyTank = pEmpty;
}


int PROTemperature::WriteXML(char *StrBuf, bool IncAlarms) {
#ifdef ANWIN
    AnsiString TempStr = LibGetValue(SVT_TEMP, this, 0);
    // Alarm status
    //
    int LEDStatus = TPC_LED_OFF;
    if (!CompleteAlarmInfoList.empty()) {
        bool ActiveAlarm = false;
        time_t NewestAlarmAct = 0;
        time_t NewestAlarmAck = 0;
        set<AlarmBasic *>::iterator pBIt;
        for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
            AlarmBasic *Element = *pBIt;
            if (Element) {
                switch (Element->State) {
                case AlarmBasic::AlIdle :
                    break;
                case AlarmBasic::AlActive :
                    if (Element->Time_Rised > NewestAlarmAct) {
                        LEDStatus = TPC_LED_FLASH;
                    }
                    break;
                case AlarmBasic::AlAknowledged :
                    if (!ActiveAlarm && (Element->Time_Acknowledged > NewestAlarmAck)) {
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
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Value>%s</Value>\r\n", TempStr);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Alarm>%i</Alarm>\r\n", LEDStatus);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t</Packet>\r\n");
    return tmpPtr;
#else
    return 0;
#endif
}


int PROTemperature::GetMaxTempSensors(void)
{
    return MaxTempCnt;
}

