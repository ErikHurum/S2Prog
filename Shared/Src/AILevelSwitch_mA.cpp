#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AILevelSwitch_mA::AILevelSwitch_mA(int SnsType, float mA_On, float mA_Off, float mA_Win) {
    Type                = SnsType;
    BasicSensorTypeWord = L_WORD599; //LSw
    Location            = C_AI_LOC_DECK;
    SwitchOn_mA         = mA_On;
    SwitchOff_mA        = mA_Off;
    SwitchWindow        = mA_Win;
    SwitchMax_mA        = LIMIT_MA_SHORT_CIRCUIT + 0.02; // Add 2 mA margin as default
    OverrideSwitchLimits = false;

    OpenLoopPtr         = (AlarmBasic *)(new AlarmmAmpOpenLoop(this));
    ShortCircuitPtr     = (AlarmBasic *)(new AlarmmAmpShortCircuit(this));
    AlarmSet.insert(OpenLoopPtr);
    AlarmSet.insert(ShortCircuitPtr);
    switch (SnsType) {
    case C_AI_LeSw_mA       :
    case C_AI_LeSw_Valcom   :
    case C_AI_LeSw_API      :
        {
            AlarmLSwitchFailure *LSwitchFailurePtr  = new AlarmLSwitchFailure(this);
            AlarmSet.insert(LSwitchFailurePtr);
        }
        break;
    case C_AI_LeSw_Vega     :
    case C_AI_LeSw_Vega62   :
    case C_AI_LeSw_Vega64   :
        break;
    }
}

AILevelSwitch_mA::~AILevelSwitch_mA(void) {
}

//---------------------------------------------------------------------------
U8 AILevelSwitch_mA::GetFilter(void) {
    return (FILTER_LEVEL_SWITCH);
}

AnsiString AILevelSwitch_mA::MakeConfigString(int ExtraTabs) {
    AnsiString TabStr1 = AnsiString::StringOfChar('\t', 1 + ExtraTabs);
    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord(Type) + CrLfStr;
    LocalString += AnalogInput::MakeConfigString();   //common
    if (OverrideSwitchLimits) {
        LocalString += TabStr1 + KeyWord(C_AI_MA_LEV_SWITCH_ON) + FloatToAnsiString(SwitchOn_mA) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_AI_MA_LEV_SWITCH_OFF) + FloatToAnsiString(SwitchOff_mA) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_AI_MA_LEV_SWITCH_WIN) + FloatToAnsiString(SwitchWindow) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_AI_MA_LEV_SWITCH_MAX) + FloatToAnsiString(SwitchMax_mA) + CrLfStr;
    }
    LocalString += TabStr1 + KeyWord(C_AI_END) + CrLfStr;
    LocalString += CrLfStr;

    return (LocalString);
    //ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

bool AILevelSwitch_mA::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning("Level switch sensor", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning("Level switch sensor", InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_START_COMMON:
                AnalogInput::LoadConfigString(ConfigString);
                break;
            case C_AI_MA_LEV_SWITCH_ON  :
                SwitchOn_mA = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                OverrideSwitchLimits = true;
                break;
            case C_AI_MA_LEV_SWITCH_OFF :
                SwitchOff_mA = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                OverrideSwitchLimits = true;
                break;
            case C_AI_MA_LEV_SWITCH_WIN :
                SwitchWindow = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                OverrideSwitchLimits = true;
                break;
            case C_AI_MA_LEV_SWITCH_MAX:
                SwitchMax_mA = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                OverrideSwitchLimits = true;
                if (NoError) {
                    ((AlarmmAmpShortCircuit *)ShortCircuitPtr) ->SetAlarmLimit(SwitchMax_mA);
                }
                break;
            case C_AI_END:
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_AI_END));
    return (NoError);
}
///////////////////////////////////////////////////////////////
//
// Routines for Calculation of values
//
///////////////////////////////////////////////////////////////




float AILevelSwitch_mA::Calculate(void) {
    if (CanCalculate()) {
        float tmpCalcValue = Gain * FilteredValue - Offset;
        if (fabs(tmpCalcValue - SwitchOn_mA) < SwitchWindow) {
            CalcValue = LEVELSWITCH_ON;
            Failure = false;
        } else if (fabs(tmpCalcValue - SwitchOff_mA) < SwitchWindow) {
            CalcValue = LEVELSWITCH_OFF;
            Failure   = false;
        } else {
            CalcValue = LEVELSWITCH_ERROR;
            Failure   = true;
        }
    } else {
        if (Enable) {
            CalcValue = LEVELSWITCH_HW_ERROR;
        } else {
            CalcValue = LEVELSWITCH_OFF;
            Failure   = false;
        }
    }
    return (CalcValue);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AILevelSwitch_mA::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_MA_ON  :
        {
            float Value = ConvertToSi(NewValue, CURRENT_UNIT, Status, 4.0 / 1000, 20.0 / 1000, SwitchOn_mA);
            if (Status == E_NO_ERR) {
                SwitchOn_mA = Value;
                TimeModified = time(NULL);
            }
        }
        break;
    case SVT_MA_OFF  :
        {
            float Value = ConvertToSi(NewValue, CURRENT_UNIT, Status, 4.0 / 1000, 20.0 / 1000, SwitchOff_mA);
            if (Status == E_NO_ERR) {
                SwitchOff_mA = Value;
                TimeModified = time(NULL);
            }
        }
        break;
    case SVT_MA_WINDOW:
        {
            float Value = ConvertToSi(NewValue, CURRENT_UNIT, Status, 0.0, 4.0 / 1000, SwitchWindow);
            if (Status == E_NO_ERR) {
                SwitchWindow = Value;
                TimeModified = time(NULL);
            }
        }
        break;
    default:
        Status = AnalogInput::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
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

int  AILevelSwitch_mA::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AI_OFFSET   :
        MyRetValue = Offset;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_AI_CALC_VAL :
        MyRetValue = Calculate();
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;

    case SVT_MA_ON  :
        MyRetValue = SwitchOn_mA;
        DecPnt     = 2;
        Unit       = CURRENT_UNIT;
        break;
    case SVT_MA_OFF  :
        MyRetValue = SwitchOff_mA;
        DecPnt     = 2;
        Unit       = CURRENT_UNIT;
        break;
    case SVT_MA_WINDOW:
        MyRetValue = SwitchWindow;
        DecPnt     = 2;
        Unit       = CURRENT_UNIT;
        break;
    default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AILevelSwitch_mA::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AI_UNIT:
        MyString = GetUnitName(CURRENT_UNIT);
        break;
    case SVT_AI_RANGE:
        MyString = "Normal" + LibGetValue(SVT_MA_OFF, this) + " Alarm " + LibGetValue(SVT_MA_ON, this);
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int AILevelSwitch_mA::PutFloatValue(int ValueId, float NewValue) {
    return (AnalogInput::PutFloatValue(ValueId, NewValue));
}



