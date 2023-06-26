#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

ValueList AnalogInput::ServiceReportSensorValueList[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },                                               // {"Unused"    ,"",SVT_BLANK},
    { L_WORD449, L_WORD237, SVT_AI_TYPE_TEXT },                                   // {"Type"         ,"",SVT_AI_TYPE_TEXT},
    { L_WORD390, L_WORD237, SVT_AI_SERIAL_NUMBER },                               // {"Serial number","",SVT_AI_SERIAL_NUMBER},
    { L_WORD124, L_WORD237, SVT_AI_LOCATION },                                    // {"Location"     ,"",SVT_AI_LOCATION},
    { L_WORD434, L_WORD237, SVT_AI_ENABLE_TEXT },                                 // {"On/Off"       ,"",SVT_AI_ENABLE_TEXT},
    { L_WORD126, L_WORD237, SVT_AI_GAIN   },                                        // {"Gain"         ,"",SVT_AI_GAIN},
    { L_WORD127, L_WORD237, SVT_AI_OFFSET },                                      // {"Offset"       ,"",SVT_AI_OFFSET},
    { L_WORD128, L_WORD237, SVT_AI_CALC_VAL },                                    // {"Value"        ,"",SVT_AI_CALC_VAL},
    { L_WORD36, L_WORD237, SVT_AI_UNIT },                                        // {"Unit"         ,"",SVT_AI_UNIT},
    { L_WORD450, L_WORD237, SVT_AI_DB },                                          // {"SnsDB"        ,"",SVT_AI_DB},
    { L_WORD451, L_WORD237, SVT_AI_PLACING },                                     // {"Placing"      ,"",SVT_AI_PLACING},
    { L_WORD74, L_WORD237, SVT_AI_PRONAME },                                     // {"Name"         ,"",SVT_AI_PRONAME},
    { L_WORD390, L_WORD237, SVT_AI_SERIAL_NUMBER },                               // {"SerNumber"    ,"",SVT_AI_SERIAL_NUMBER},
    { L_WORD452, L_WORD237, SVT_AI_MIN_RANGE },                                   // {"MinRange"     ,"",SVT_AI_MIN_RANGE},
    { L_WORD453, L_WORD237, SVT_AI_MAX_RANGE },                                   // {"MaxRange"     ,"",SVT_AI_MAX_RANGE},
    { L_WORD454, L_WORD237, SVT_AI_CABLE_LENGTH },                                // {"CableLength"  ,"",SVT_AI_CABLE_LENGTH},
    { L_WORD455, L_WORD237, SVT_IOC_TCU_ADDRES },                                 // {"TCUAddress"   ,"",SVT_IOC_TCU_ADDRES},
    { L_WORD456, L_WORD237, SVT_IOC_TCU_PORT },                                   // {"Port"         ,"",SVT_IOC_TCU_PORT},
    { L_WORD457, L_WORD237, SVT_IOC_IO_ADDRESS },                                 // {"IOAddress"    ,"",SVT_IOC_IO_ADDRESS},
    { L_WORD458, L_WORD237, SVT_IOC_IO_CHANNEL },                                 // {"Channel"      ,"",SVT_IOC_IO_CHANNEL},
    { L_WORD459, L_WORD237, SVT_IOC_ADCARD_CHANNEL },                             // {"ADCardChn"    ,"",SVT_IOC_ADCARD_CHANNEL},
};

vector<AnalogInput *> AnalogInput::AIPtrVector;
AnalogInput::AnalogInput(void) {
    Init();
    AIPtrVector.push_back(this);
}

void AnalogInput::Init(void) {
    //IDNumber     = GetFirstFreeId();
    SerialNumber        = "None";
    PROPtr              = NULL;
    Distance            = 0.00;
    AdjustedDistance    = 0.00;
    IsPressureSns       = false;
    Enable              = true;
    Modified            = false;
    ResultOK            = false;
    NewSensor           = false;
    Failure             = 0;
    IsStartUp           = true;
    Gain                = 1.0;
    Offset              = 0.0;
    CalcValue           = 0.0;
    FilteredValue       = 0.0;
    OutsideCnt          = MAX_OUTSIDE_WIN_CNT;
    HasDistance         = false;

    TimeModified        = time(NULL);
    ModifiedBy          = C_MOD_CONFIG;

    Location            = C_AI_LOC_NOT_DEFINED;
    LocationKWord       = L_WORD585;
    MinRange            = 0.0;
    MaxRange            = 0.0; // EHSMark Can be a problem
//  CableLength         = 0.0;   //only for temp

    TCUAddress          = 0;
    TCUPortNo           = 0;
    IOType              = 0;
    IOAddress           = 0;
    IOChannel           = 0;
    ADCardChannel       = 0;
    BasicSensorType     = AI_SENSOR_NOT_DEFINED;
    BasicSensorTypeWord = L_WORD485; //Unknown
    TimeChecked         = 0;
    DataTransferSet.insert(this);
}

AnalogInput::~AnalogInput(void) {
}

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

unsigned AnalogInput::GetFirstFreeId(set<unsigned> &AISet) {
    unsigned FirstFreeId = 0;
    unsigned MaxId       = (C_IOC_ANALOG_IN << 16);
    for ( unsigned i = 0; !FirstFreeId && i < AISet.size(); i++ ) {
        unsigned IDNum = (C_IOC_ANALOG_IN << 16) + i + 1;
        set<unsigned>::iterator pBIt;
        pBIt = AISet.find(IDNum);
        if ( pBIt == AISet.end() ) {
            FirstFreeId = IDNum;
        } else if ( *pBIt > MaxId ) {
            MaxId = *pBIt;
        }
    }
    if ( !FirstFreeId ) {
        FirstFreeId = MaxId + 1;
    }
    AISet.insert(FirstFreeId);

    return (FirstFreeId);
}

void AnalogInput::CreateIdNum(void) {
    set<unsigned> AISet;
    vector<AnalogInput *>::iterator pBIt;
    for ( pBIt = AIPtrVector.begin(); pBIt != AIPtrVector.end(); pBIt++ ) {
        if ( pBIt != AIPtrVector.end() ) {
            AnalogInput *tmpPtr = *pBIt;
            if ( tmpPtr->IDNumber ) {
                AISet.insert(tmpPtr->IDNumber);
            }
        }
    }

    for ( pBIt = AIPtrVector.begin(); pBIt != AIPtrVector.end(); pBIt++ ) {
        if ( pBIt != AIPtrVector.end() ) {
            AnalogInput *tmpPtr = *pBIt;
            if ( !tmpPtr->IDNumber || ((tmpPtr->IDNumber) >> 16 == C_PRO_BASIC) ) {
                tmpPtr->IDNumber = GetFirstFreeId(AISet);
            }
        }
    }

}

void AnalogInput::SetPROPtr(PRogramObject *PPtr) {
    if ( PROPtr != PPtr ) {
        PROPtr = PPtr;
        switch ( Location ) {
        case C_AI_LOC_NOT_DEFINED:
            LocationKWord = L_WORD585; break;
        case C_AI_LOC_BOTTOM     :
            LocationKWord = L_WORD587; break;
        case C_AI_LOC_MIDDLE     :
            LocationKWord = L_WORD588; break;
        case C_AI_LOC_UPPER      :
            LocationKWord = L_WORD589; break;
        case C_AI_LOC_VAPOUR     :
            LocationKWord = L_WORD590; break;
        case C_AI_LOC_PUMP_ROOM  :
            LocationKWord = L_WORD591; break;
        case C_AI_LOC_ENGINE_ROOM:
            LocationKWord = L_WORD592; break;
        case C_AI_LOC_SYSTEM     :
            LocationKWord = L_WORD96; break;
        case C_AI_LOC_WI_MAIN    :
            LocationKWord = L_WORD596; break;
        case C_AI_LOC_WI_PRE     :
            LocationKWord = L_WORD597; break;
        case C_AI_LOC_INC_TRIM   :
            LocationKWord = L_WORD460; break;
        case C_AI_LOC_INC_LIST   :
            LocationKWord = L_WORD461; break;
        case C_AI_LOC_DECK       :
            LocationKWord = L_WORD594; break;
        case C_AI_LOC_LINE       :
            LocationKWord = L_WORD595; break;
        case C_AI_LOC_ATM        :
            LocationKWord = L_WORD586; break;
        case C_AI_LOC_TEMP       :
            LocationKWord = L_WORD338; break;
        case C_AI_LOC_POWER1     :
            LocationKWord = L_WORD654; break;
        case C_AI_LOC_POWER2     :
            LocationKWord = L_WORD655; break;
        case C_AI_LOC_POWER_AC   :
            LocationKWord = L_WORD1125; break;
        case C_AI_LOC_POWER_DC   :
            LocationKWord = L_WORD1126; break;
        case C_AI_LOC_AC_OK      :
            LocationKWord = L_WORD890; break;
        case C_AI_LOC_FUSES      :
            LocationKWord = L_WORD891; break;
        case C_AI_LOC_TRIM       :
            LocationKWord = L_WORD460; break;
        case C_AI_LOC_LIST       :
            LocationKWord = L_WORD461; break;
        case C_AI_LOC_TEMP1      :
        case C_AI_LOC_TEMP2      :
        case C_AI_LOC_TEMP3      :
        case C_AI_LOC_TEMP4      :
        case C_AI_LOC_TEMP5      :
        case C_AI_LOC_TEMP6      :
        case C_AI_LOC_TEMP7      :
        case C_AI_LOC_TEMP8      :
        case C_AI_LOC_TEMP9      :
        case C_AI_LOC_TEMP10     :
            LocationKWord = L_WORD985 + Location - C_AI_LOC_TEMP1;
            break;
        case C_AI_LOC_TEMP_IN :
            LocationKWord = L_WORD1113;
            break;
        case C_AI_LOC_TEMP_OUT:
            LocationKWord = L_WORD1114;
            break;
        case C_AI_LOC_TANK_CLEAN:
            LocationKWord = L_WORD1115;
            break;
        case C_AI_LOC_REDUNDANCY1:
        case C_AI_LOC_REDUNDANCY2:
        case C_AI_LOC_REDUNDANCY3:
            LocationKWord = L_WORD749 + Location - C_AI_LOC_REDUNDANCY1;
            break;

        }
        Name = GetName();
    }
}


AnsiString AnalogInput::MakeConfigString(int ExtraTabs) {
    AnsiString TabStr1 = AnsiString::StringOfChar('\t', 1 + ExtraTabs);
    AnsiString TabStr2 = AnsiString::StringOfChar('\t', 2 + ExtraTabs);
    AnsiString TabStr3 = AnsiString::StringOfChar('\t', 3 + ExtraTabs);
    AnsiString TabStr4 = AnsiString::StringOfChar('\t', 4 + ExtraTabs);
    AnsiString TabStr5 = AnsiString::StringOfChar('\t', 5 + ExtraTabs);
    AnsiString TabStr6 = AnsiString::StringOfChar('\t', 6 + ExtraTabs);
    AnsiString LocalString;
    if ( SerialNumber.IsEmpty() ) {
        SerialNumber = "None";
    }
    AnsiString IdNumStr;
    IdNumStr.cat_sprintf("0x%0x", IDNumber);
    LocalString += TabStr3 + KeyWord(C_AI_START_COMMON) + CrLfStr;
    LocalString += TabStr4 + KeyWord(C_PRO_ID_NUMBER) + IdNumStr + CrLfStr;

    LocalString += TabStr4 + KeyWord(C_AI_SERIALNO) + SerialNumber + CrLfStr;
    switch ( Type ) {
    case C_AI_WashTrackSensor  :
        LocalString += TabStr4 + KeyWord(C_AI_MIN_RANGE) + FloatToAnsiString(MinRange,  6, 3) + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_AI_MAX_RANGE) + FloatToAnsiString(MaxRange,  6, 3) + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_TCU_ADDRESS) + (AnsiString)TCUAddress + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_TCU_PORT_NO) + (AnsiString)TCUPortNo + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_IO_TYPE) + TabStr2 + KeyWord(IOType) + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_IO_ADDRESS) + (AnsiString)IOAddress + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_IO_CHANNEL) + (AnsiString)IOChannel + CrLfStr;
        break;
    case C_AI_HSH_LNG_Float :
        LocalString += TabStr4 + KeyWord(C_AI_DISTANCE) + FloatToAnsiString(Distance) + CrLfStr;
        break;
    case C_AI_AirPurge :
        LocalString += TabStr4 + KeyWord(C_AI_DISTANCE) + FloatToAnsiString(Distance) + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_AI_MIN_RANGE) + FloatToAnsiString(MinRange, 6, 3) + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_AI_MAX_RANGE) + FloatToAnsiString(MaxRange, 6, 3) + CrLfStr;
        break;
    default                 :
        if ( HasDistance ) {
            LocalString += TabStr4 + KeyWord(C_AI_DISTANCE) + FloatToAnsiString(Distance) + CrLfStr;
        }
        LocalString += TabStr4 + KeyWord(C_AI_MIN_RANGE) + FloatToAnsiString(MinRange,  6, 3) + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_AI_MAX_RANGE) + FloatToAnsiString(MaxRange,  6, 3) + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_TCU_ADDRESS) + (AnsiString)TCUAddress + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_TCU_PORT_NO) + (AnsiString)TCUPortNo + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_IO_TYPE) + TabStr2 + KeyWord(IOType) + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_IO_ADDRESS) + (AnsiString)IOAddress + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_IO_CHANNEL) + (AnsiString)IOChannel + CrLfStr;
        break;
    }

//Test on type
    if ( (IOType == C_IO_AN_ZB485) && (
                                       (Type != C_AI_WATERINGRESS) ||
                                       (Type != C_AI_WATERINGR_MAIN) ||
                                       (Type != C_AI_WATERINGR_PRE) ||
                                       (Type != C_AI_VOLTAGE)) ) {
        LocalString += TabStr4 + KeyWord(C_ADCARD_CH) + (AnsiString)ADCardChannel + CrLfStr;
    }

    LocalString += TabStr3 + KeyWord(C_AI_END_COMMON) + CrLfStr;

    LocalString += PROIOComponent::MakeConfigString();
    return (LocalString);
}
//---------------------------------------------------------------------------

bool AnalogInput::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    AnsiString PROName = "Analog input";
    if ( PROPtr )   PROName += (AnsiString)", for " + PROPtr->Name;
    PROName += ":\n";
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning(PROName, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning(PROName, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_END_COMMON:
                break;
            case C_AI_DISTANCE:
                Distance 		 = ConfigString.ReadDouble(ErrorLine);
                AdjustedDistance = Distance;
                HasDistance 	 = true;
                NoError 		 = !ErrorLine;
                break;
            case C_PRO_ID_NUMBER:
                {
                    unsigned tmpIDNumber = ConfigString.ReadInteger(ErrorLine);
                    if ( tmpIDNumber != IDNumber ) {
                        //OS_Delay(1);
                    }
                    IDNumber = tmpIDNumber;
                }
                NoError  = !ErrorLine;
                break;
            case C_AI_SERIALNO:
                SerialNumber = ConfigString.NextWord(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_GAIN:
                {
                    float tmpGain = ConfigString.ReadDouble(ErrorLine);
                    if ( tmpGain > MIN_GAIN && tmpGain > MAX_GAIN ) {
                        Gain = tmpGain;
                    } else {
                        Gain = 1.000;
                    }
                    NoError = !ErrorLine;
                }
                break;
            case C_AI_OFFSET:
                Offset = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_MIN_RANGE:
                MinRange = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_MAX_RANGE:
                MaxRange = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_TCU_ADDRESS:
                TCUAddress = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_TCU_PORT_NO:
                TCUPortNo = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_IO_TYPE:
                {
                    AnsiString temp = ConfigString.NextWord(ErrorLine);
                    if ( !ErrorLine ) {
                        IOType = FindConfigKey(temp);
                    }
                    NoError = !ErrorLine;
                }
                break;
            case C_IO_ADDRESS:
                IOAddress = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_IO_CHANNEL:
                IOChannel = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_ADCARD_CH:
                ADCardChannel = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            }
        }                                                                                                                                           //remove this later
    }while ( NoError && (ErrorLine != EOF) && (Key != C_AI_END_COMMON) && (Key != C_DI_END_COMMON) );
    return (NoError);
}
//---------------------------------------------------------------------------
void AnalogInput::SetLocationKeyWord(int KWd) {
    LocationKWord = KWd;
}

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

AnsiString AnalogInput::SaveAISettings(int ExtraTabs) {
    AnsiString TabStr1 = AnsiString::StringOfChar('\t', 1 + ExtraTabs);
    AnsiString TabStr2 = AnsiString::StringOfChar('\t', 2 + ExtraTabs);
    AnsiString TabStr3 = AnsiString::StringOfChar('\t', 3 + ExtraTabs);
    AnsiString TabStr4 = AnsiString::StringOfChar('\t', 4 + ExtraTabs);
    AnsiString TabStr5 = AnsiString::StringOfChar('\t', 5 + ExtraTabs);
    AnsiString TabStr6 = AnsiString::StringOfChar('\t', 6 + ExtraTabs);

    AnsiString LocalString;
    AnsiString IdNumStr;
    IdNumStr.cat_sprintf("0x%0x", IDNumber);
    LocalString += TabStr1 + KeyWord(Type) + IdNumStr + CrLfStr;
    //if ( SerialNumber != "" ) LocalString +=TabStr2+KeyWord(C_AI_SERIALNO)+SerialNumber+CrLfStr;
    if ( Enable ) {
        LocalString += TabStr2 + KeyWord(C_ENABLE) + CrLfStr;
    } else {
        LocalString += TabStr2 + KeyWord(C_DISABLE) + CrLfStr;
    }
    AnsiString GainStr     = FloatToAnsiString(Gain,  8, 5);
    AnsiString OffseTabStr = FloatToAnsiString(Offset,  8, 3);

    LocalString += TabStr2 + KeyWord(C_AI_GAIN) + TabStr2 + GainStr + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_AI_OFFSET) + TabStr2 + OffseTabStr + CrLfStr;
    LocalString += TabStr2 + KeyWord(ModifiedBy) + (AnsiString)((int)TimeModified) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_AI_END) + CrLfStr;
    LocalString += CrLfStr;
    return (LocalString);
}

bool AnalogInput::RestoreAISettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    AnsiString PROName = "Analog input";
    if ( PROPtr )   PROName += (AnsiString)", for " + PROPtr->Name;
    PROName += ":\n";
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                RestoreSettingsWarning(PROName + (AnsiString)"Unknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                RestoreSettingsWarning(PROName + (AnsiString)"The keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                NoError = false;
                break;
            case C_AI_SERIALNO:
                SerialNumber = SettingsString->NextWord(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_GAIN:
                Gain = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_OFFSET:
                Offset = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_ENABLE:
                Enable = true;
                break;
            case C_DISABLE:
                Enable = false;
                break;
            case C_MOD_CONFIG:
            case C_MOD_SYSTEM:
            case C_MOD_USER  :
                ModifiedBy = Key;
                TimeModified = int(SettingsString->ReadDouble(ErrorLine));
                NoError = !ErrorLine;
                break;
            case C_AI_END:
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_AI_END) );
    return (NoError);
}

///////////////////////////////////////////////////////////////
//
// Routines for Calculation of values
//
///////////////////////////////////////////////////////////////
float AnalogInput::Calculate(void) {
    if ( CanCalculate() ) {
        CalcValue = Gain * FilteredValue - Offset;
        ResultOK = true;
    } else {
        ResultOK = false;
    }
    Failure  = false;
    return (CalcValue);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

void AnalogInput::UpdateAllDependingSensorOffsets(float OffsetChange, bool IsLocal) {
}

int AnalogInput::CheckInput(float Operator_Val, int &Action) {
    return (E_ILLEGAL);
}

int AnalogInput::AdjustSensor(AnsiString NewValue, int Unit, float Min, float Max, bool Local) {
    int Status = E_NO_ERR;
    float Value = ConvertToSi(NewValue, Unit, Status, Min, Max, 0.0);
    if ( Status == E_NO_ERR ) {
        Status = AdjustSensorF(Value, Local);
    }
    return (Status);
}

int AnalogInput::AdjustSensorF(float Operator_Val, bool Local) {
    int ErrStatus = E_NO_ERR;
    int Action;
    if ( !CanCalculate() ) {
        ErrStatus = E_SENSOR_ERROR;
    } else {
        ErrStatus = CheckInput(Operator_Val, Action);
        if ( !Local && (ErrStatus == E_NO_ERR) ) {
            switch ( Action ) {
            default:
            case SNS_ADJUST_ABORT:
                break;
            case SNS_ADJUST_ONLY_INP:
                CalcValue = Operator_Val;
                break;
            case SNS_ADJUST_GAIN:
                {
                    float GainCorrection = Operator_Val / CalcValue;
                    Gain *= GainCorrection;
                }
                Modified = true;
                break;
            case SNS_ADJUST_OFFSET:
                {
                    float OffsetChange = CalcValue - Operator_Val;
                    Offset += OffsetChange;
                    Modified = true;
                    UpdateAllDependingSensorOffsets(OffsetChange, Local);
                }
                break;
            }
        }
    }
    return (ErrStatus);
}

AnsiString AnalogInput::GetName(void) {
    AnsiString Loc      = FindDictionaryWord(LocationKWord);
    AnsiString BSnsType = FindDictionaryWord(BasicSensorTypeWord);
    AnsiString Name;
    if ( PROPtr ) {
        Name = PROPtr->Name;
    } else {
        Name = "Error";
    }
    int LMarg = 15 - 3 - Name.Length() - BSnsType.Length();
    if ( LMarg <= 0 ) {
        LMarg = 1;
        BSnsType = BSnsType.SetLength(BSnsType.Length() - 1);
    } else if ( LMarg > 4 ) {
        LMarg = 4;
    }
    if ( Loc.Length() > LMarg ) {
        Loc.SetLength(LMarg);
    }
    AnsiString tName = Name + "(" + Loc + ":" + BSnsType + ")";
    return (tName);
}

int AnalogInput::FindPROStatus(AnsiString &MyString) {
    int PROStatus = ST_OK;
    if ( HasActiveAlarms() ) {
        PROStatus = ST_ERROR;
    } else if ( !Enable ) {
        PROStatus = ST_WARNING;
    }
    MyString = FindStatusChar(PROStatus);
    return (PROStatus);
}

int AnalogInput::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;

    switch ( ValueId ) {
    case SVT_AI_LOCATION:
        MyString = FindDictionaryWord(LocationKWord);
        if ( MyString.IsEmpty() )   Status = GETVAL_ERROR;
        break;
    case SVT_AI_TYPE_TEXT:
        MyString = FindKeyWord(Type);
        if ( MyString.IsEmpty() )   Status = GETVAL_ERROR;
        break;
    case SVT_AI_ENABLE_TEXT:
        if ( Enable ) {
            MyString = FindKeyWord(C_ENABLE);
        } else {
            MyString = FindKeyWord(C_DISABLE);
        }
        if ( MyString.IsEmpty() )   Status = GETVAL_ERROR;
        break;
    case SVT_AI_PRONAME:
        if ( PROPtr ) {
            MyString = PROPtr->Name;
        } else {
            MyString = "";
        }
        break;
    case SVT_AI_RANGE:
        MyString = "Range:" + LibGetValue(SVT_AI_MIN_RANGE, this) + " to " + LibGetValue(SVT_AI_MAX_RANGE, this) + " Bar";
        break;
    default:
        Status = PROIOComponent::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int AnalogInput::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_TYPE:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = (float)Type;
        break;
    case SVT_AI_GAIN:
        DecPnt     = 5;
        Unit       = NO_UNIT;
        MyRetValue = (float)Gain;
        break;
    case SVT_AI_ENABLE:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = (float)Enable;
        break;
    case SVT_AI_DB:
    case SVT_AI_PLACING:
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        MyRetValue = (float)Distance;
        break;
    case SVT_AI_MIN_RANGE :
        DecPnt     = 2;
        Unit       = NO_UNIT;
        MyRetValue = MinRange;
        break;
    case SVT_AI_MAX_RANGE :
        DecPnt     = 2;
        Unit       = NO_UNIT;
        MyRetValue = MaxRange;
        break;
    default:
        Status = PROIOComponent::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}



int AnalogInput::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_GAIN:
        {
            float Value = ConvertToSi(NewValue, NO_UNIT, Status, MIN_GAIN, MAX_GAIN, 0.0);
            if ( Status == E_NO_ERR ) {
                Gain = Value;
                TimeModified        = time(NULL);
            }
        }
        break;
    case SVT_AI_ENABLE:
    case SVT_AI_ENABLE_TEXT:
        {
            int Key = FindConfigKey(NewValue);
            switch ( Key ) {
            case C_ON:
            case C_OPEN:
            case C_ENABLE:
                Enable = true;
                break;
            case C_OFF:
            case C_CLOSE:
            case C_DISABLE:
                Enable = false;
                break;
            default:
                {
                    bool Value = (bool)GetUnsigned(NewValue, Status);
                    if ( Status == E_NO_ERR ) {
                        Enable = Value;
                        TimeModified = time(NULL);
                    }
                }
                break;
            }
        }
        break;
    case SVT_AI_MIN_RANGE :
        {
            float Value = ConvertToSi(NewValue, NO_UNIT, Status, 0, 150, 0.0);
            if ( Status == E_NO_ERR ) {
                MinRange = Value;
                TimeModified        = time(NULL);
            }
        }
        break;
    case SVT_AI_MAX_RANGE :
        {
            float Value = ConvertToSi(NewValue, NO_UNIT, Status, 0, 150, 0.0);
            if ( Status == E_NO_ERR ) {
                MaxRange = Value;
                TimeModified        = time(NULL);
            }
        }
        break;
    default:
        Status = PROIOComponent::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int AnalogInput::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_GAIN:
        Gain = NewValue;
        break;
    case SVT_AI_OFFSET:
        Offset = NewValue;
        break;
    default:
        Status = E_NOT_ADJUSTABLE;
        break;

    }
    return (Status);
}

ValueList SensorValueList0[] =  {
    { L_WORD124, L_WORD237, SVT_AI_LOCATION },                                        // {"Location"  ,"",SVT_AI_LOCATION},
    { L_WORD434, L_WORD237, SVT_AI_ENABLE_TEXT },                                     // {"On/Off"    ,"",SVT_AI_ENABLE_TEXT},
    { L_WORD126, L_WORD237, SVT_AI_GAIN },                                            // {"Gain"      ,"",SVT_AI_GAIN},
    { L_WORD127, L_WORD237, SVT_AI_OFFSET },                                          // {"Offset"    ,"",SVT_AI_OFFSET},
    { L_WORD128, L_WORD237, SVT_AI_CALC_VAL },                                        // {"Value"     ,"",SVT_AI_CALC_VAL},
    { L_WORD36, L_WORD237, SVT_AI_UNIT },                                            // {"Unit"      ,"",SVT_AI_UNIT},
};

ValueList SensorValueList1[] =  {
    { L_WORD293, L_WORD237, SVT_AI_CAL_DATA_PERCENT },                                // {"%"  ,"",SVT_AI_LOCATION},
    { L_WORD439, L_WORD237, SVT_AI_CAL_DATA_FRO },                                    // {"FRO"  ,"",SVT_AI_LOCATION},
    { L_WORD440, L_WORD237, SVT_AI_CAL_DATA_G1 },                                     // {"G1"    ,"",SVT_AI_ENABLE_TEXT},
    { L_WORD441, L_WORD237, SVT_AI_CAL_DATA_G2 },                                     // {"G2"      ,"",SVT_AI_GAIN},
    { L_WORD442, L_WORD237, SVT_AI_CAL_DATA_G3 },                                     // {"G3"    ,"",SVT_AI_OFFSET},
};

ValueList SensorValueList2[] = {
    { L_WORD439, L_WORD237, SVT_AI_CAL_DATA_FRO },                             // {"FRO"              ,"",SVT_AI_CAL_DATA_FRO},
    { L_WORD440, L_WORD237, SVT_AI_CAL_DATA_G1 },                              // {"G1"               ,"",SVT_AI_CAL_DATA_G1},
    { L_WORD441, L_WORD237, SVT_AI_CAL_DATA_G2 },                              // {"G2"               ,"",SVT_AI_CAL_DATA_G2},
    { L_WORD442, L_WORD237, SVT_AI_CAL_DATA_G3 },                              // {"G3"               ,"",SVT_AI_CAL_DATA_G3},
    { L_WORD443, L_WORD237, SVT_AI_CAL_DATA_NL1 },                             // {"NL1"              ,"",SVT_AI_CAL_DATA_NL1},
    { L_WORD444, L_WORD237, SVT_AI_CAL_DATA_NL2 },                             // {"NL2"              ,"",SVT_AI_CAL_DATA_NL2},
};

ValueList SensorValueList3[] = {
    { L_WORD937, L_WORD237, SVT_AI_CAL_DATA_ENTRY },                           // {"Entry"            ,"",SVT_AI_CAL_DATA_ENTRY},
    { L_WORD248, L_WORD237, SVT_AI_CAL_DATA_FRO },                             // {"mAmp"             ,"",SVT_AI_CAL_DATA_FRO},
    { L_WORD295, L_WORD237, SVT_AI_CAL_DATA_G1 },                              // {"G1"               ,"",SVT_AI_CAL_DATA_G1},
};

ValueList SensorValueList4[] = {
    { L_WORD439, L_WORD237, SVT_AI_CAL_DATA_FRO },                             // {"FRO"              ,"",SVT_AI_CAL_DATA_FRO},
    { L_WORD440, L_WORD237, SVT_AI_CAL_DATA_G1 },                              // {"G1"               ,"",SVT_AI_CAL_DATA_G1},
    { L_WORD935, L_WORD237, SVT_AI_CAL_DATA_TSS },                             // {"TSS"              ,"",SVT_AI_CAL_DATA_TZS},
    { L_WORD936, L_WORD237, SVT_AI_CAL_DATA_TZS },                             // {"TZS"              ,"",SVT_AI_CAL_DATA_TSS},
};

ValueList* AnalogInput::GetValueInfoTable(int &Entries, int Index) {
    return GetValueInfoTableStatic(Entries, Index);
}

ValueList* AnalogInput::GetValueInfoTableStatic(int &Entries, int Index) {
    ValueList *ValListPtr;
    switch ( Index ) {
    default:
    case 0:
        ValListPtr = SensorValueList0;
        Entries = NELEMENTS(SensorValueList0);
        break;
    case 1:
        ValListPtr = SensorValueList1;
        Entries = NELEMENTS(SensorValueList1);
        break;
    case 2:
        ValListPtr = SensorValueList2;
        Entries = NELEMENTS(SensorValueList2);
        break;
    case 3:
        ValListPtr = SensorValueList3;
        Entries = NELEMENTS(SensorValueList3);
        break;
    case 4:
        ValListPtr = SensorValueList4;
        Entries = NELEMENTS(SensorValueList4);
        break;
    }
    return (ValListPtr);
}


ValueList* AnalogInput::GetServiceValueInfoTable(int &Entries) {
    return GetServiceValueInfoTableStatic(Entries);
}
ValueList* AnalogInput::GetServiceValueInfoTableStatic(int &Entries) {
    Entries = NELEMENTS(ServiceReportSensorValueList);
    return (ServiceReportSensorValueList);
}


vector<int>AnalogInput::GetValueIdVector(int Index) {
    vector<int>tmpList;
    switch ( Index ) {
    default:
    case 0:
        for ( unsigned i = 0; i < NELEMENTS(SensorValueList0); i++ ) {
            tmpList.push_back(SensorValueList0[i].Value);
        }
        break;
    case 1:
        for ( unsigned i = 0; i < NELEMENTS(SensorValueList1); i++ ) {
            tmpList.push_back(SensorValueList1[i].Value);
        }
        break;
    case 2:
        for ( unsigned i = 0; i < NELEMENTS(SensorValueList2); i++ ) {
            tmpList.push_back(SensorValueList2[i].Value);
        }
    case 3:
        for ( unsigned i = 0; i < NELEMENTS(SensorValueList3); i++ ) {
            tmpList.push_back(SensorValueList3[i].Value);
        }
        break;
    case 4:
        for ( unsigned i = 0; i < NELEMENTS(SensorValueList4); i++ ) {
            tmpList.push_back(SensorValueList4[i].Value);
        }
        break;
    }
    return (tmpList);
}
vector<ValueList>AnalogInput::GetValueInfoVector(int Index) {
    vector<ValueList>tmpList;
    switch ( Index ) {
    case 0:
        for ( unsigned i = 0; i < NELEMENTS(SensorValueList0); i++ ) {
            tmpList.push_back(SensorValueList0[i]);
        }
        break;
    case 1:
        for ( unsigned i = 0; i < NELEMENTS(SensorValueList1); i++ ) {
            tmpList.push_back(SensorValueList1[i]);
        }
        break;
    case 2:
        for ( unsigned i = 0; i < NELEMENTS(SensorValueList2); i++ ) {
            tmpList.push_back(SensorValueList2[i]);
        }
        break;
    case 3:
        for ( unsigned i = 0; i < NELEMENTS(SensorValueList3); i++ ) {
            tmpList.push_back(SensorValueList3[i]);
        }
        break;
    case 4:
        for ( unsigned i = 0; i < NELEMENTS(SensorValueList4); i++ ) {
            tmpList.push_back(SensorValueList4[i]);
        }
        break;
    }
    return (tmpList);
}


vector<ValueList>AnalogInput::GetServiceValueInfoVector(void) {
    vector<ValueList>tmpList;
    for ( unsigned i = 0; i < NELEMENTS(ServiceReportSensorValueList); i++ ) {
        tmpList.push_back(ServiceReportSensorValueList[i]);
    }
    return (tmpList);
}



//end librerian

int AnalogInput::ReceiveData(U8 *data) {
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2508  *pData = (ANPRO10_COMMAND_2508 *)data;
            HWFailure       = pData->HWFailure;
            MyHWFailure     = pData->MyHWFailure;
            ActiveAlarms    = pData->ActiveAlarms;
            FilteredValue   = pData->FilteredValue;
            CalcValue       = pData->CalcValue;
            ResultOK        = pData->ResultOK;
            // Only check alarm for Master TCU for now
            if ( !CurrentDeviceAddress && CurrentDeviceId == DEVICE_TCU ) {
                CheckAlarms(AlarmSet);
            }

        }
        return (E_OK);
    case CMD_GENERIC_STATIC_DATA:
        {
            ANPRO10_COMMAND_2510  *pData = (ANPRO10_COMMAND_2510 *)data;
            Gain         = pData->Gain;
            Offset       = pData->Offset;
            MinRange     = pData->MinRange;
            MaxRange     = pData->MaxRange;
            Enable       = pData->Enable;
            NewSensor    = pData->NewSensor;
            SerialNumber = pData->SerialNo;
        }
        return (E_OK);
    default:
        return (E_UNKNOWN_COMMAND);
    };
}
int AnalogInput::SendData(U16 cmd) {
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2508  Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;

            Cmd.Data.CommandNo      = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.ndb            = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.HWFailure      = HWFailure;
            Cmd.Data.MyHWFailure    = MyHWFailure;
            Cmd.Data.ActiveAlarms   = ActiveAlarms;
            Cmd.Data.FilteredValue  = FilteredValue;
            Cmd.Data.CalcValue      = CalcValue;
            Cmd.Data.ResultOK       = ResultOK;

            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) return (E_QUEUE_FULL);
            else return (E_OK);
        }
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2510  Cmd;
            Cmd.TxInfo.Port        = NULL;
            Cmd.TxInfo.rxAddr      = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId        = DEVICE_BROADCAST_TXU;
            Cmd.Data.CommandNo     = CMD_GENERIC_STATIC_DATA;
            Cmd.Data.ndb           = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.ObjectId      = IDNumber;

            Cmd.Data.Gain          = Gain;
            Cmd.Data.Offset        = Offset;
            Cmd.Data.MinRange      = MinRange;
            Cmd.Data.MaxRange      = MaxRange;
            Cmd.Data.Enable        = Enable;
            Cmd.Data.NewSensor     = NewSensor;
            strncpy(Cmd.Data.SerialNo, SerialNumber.c_str(), 15);
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) return (E_QUEUE_FULL);
            else return (E_OK);
        }
    default:
        return (E_UNKNOWN_COMMAND);
    };

}


void AnalogInput::NewValue(float NewValue) {
    HWFailure     = false;
    FilteredValue = NewValue;
}

void AnalogInput::SetStatus(U8 *NewStatus) {
}

void AnalogInput::SetModifiedFlag(void) {
    IsModified = true;
    TimeModified = time(NULL);
    if ( PROPtr ) {
        PROPtr->SetModifiedFlag();
    } else {
        SignalSaveSettings(FLASH_SAVE_SETTINGS);
    }
}


int AnalogInput::GetBasicSensorType(void) {
    return BasicSensorType;
}

void AnalogInput::SetIsPressureSns(bool TPressState) {
    IsPressureSns = TPressState;
}

bool AnalogInput::GetIsPressureSns(void) {
    return IsPressureSns;
}

bool AnalogInput::CanCalculate(void) {
    bool CanCalc = false;
    if ( Enable ) {
        if ( HWFailure || MyHWFailure ) {
            // HWFailure is set by e.g. ZBAna or SCADCard
            CalcValue = 0.0;
            ResultOK  = false;
        } else {
            CanCalc = true;
        }
    } else {
        CalcValue = 0.0;
        ResultOK  = false;
    }
    return (CanCalc);
}


void AnalogInput::SetNewStatus(bool NewStatus) {
}

bool AnalogInput::GetErrorStatus(void) {
    return Failure;
}


vector<PRogramObjectBase *>AnalogInput::GetProgramObjectBaseVector(vector<AnalogInput *>MyVect) {
    vector<PRogramObjectBase *>ListVector;
    for ( unsigned i = 0; i < MyVect.size(); i++ ) {
        ListVector.push_back((PRogramObjectBase *)MyVect[i]);
    }
    return (ListVector);
}
