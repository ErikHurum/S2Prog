#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AILevelSwitchVega::AILevelSwitchVega(int SnsType, float mA_On, float mA_Off, float mA_Win, float mA_Test) :
    AILevelSwitch_mA(SnsType, mA_On, mA_Off, mA_Win) {
    LastTestTime = clock();
    SwitchTest = mA_Test;
    ((AlarmmAmpOpenLoop *)OpenLoopPtr)->SetAlarmDelay(10000);
    ((AlarmmAmpShortCircuit *)ShortCircuitPtr)->SetAlarmDelay(10000);
    ((AlarmmAmpShortCircuit *)ShortCircuitPtr)->SetAlarmLimit(LIMIT_MA_SHORT_CIRCUIT + 0.002);

    AlarmLevelSwitchTest  *LevelSwitchTestPtr = new AlarmLevelSwitchTest(this, SwitchTest, SwitchWindow);
    AlarmSet.insert(LevelSwitchTestPtr);
    LastTestTime = clock();
    TestCount    = 0;
}

AILevelSwitchVega::~AILevelSwitchVega(void) {
}



AnsiString AILevelSwitchVega::SaveAISettings(int ExtraTabs) {
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
    if (Enable) {
        LocalString += TabStr2 + KeyWord(C_ENABLE) + CrLfStr;
    } else {
        LocalString += TabStr2 + KeyWord(C_DISABLE) + CrLfStr;
    }
    AnsiString GainStr          = FloatToAnsiString(Gain        , 8, 5);
    AnsiString OffseTabStr      = FloatToAnsiString(Offset      , 8, 3);
    AnsiString SwitchOn_mAStr   = FloatToAnsiString(SwitchOn_mA , 8, 4);
    AnsiString SwitchOff_mAStr  = FloatToAnsiString(SwitchOff_mA, 8, 4);
    AnsiString SwitchWindowStr  = FloatToAnsiString(SwitchWindow, 8, 4);



    LocalString += TabStr2 + KeyWord(C_AI_GAIN) + TabStr2 + GainStr + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_AI_OFFSET) + TabStr2 + OffseTabStr + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_AI_MA_LEV_SWITCH_ON) + TabStr2 + SwitchOn_mAStr + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_AI_MA_LEV_SWITCH_OFF) + TabStr2 + SwitchOff_mAStr + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_AI_MA_LEV_SWITCH_WIN) + TabStr2 + SwitchWindowStr + CrLfStr;
    LocalString += TabStr2 + KeyWord(ModifiedBy) + (AnsiString)((int)TimeModified) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_AI_END) + CrLfStr;
    LocalString += CrLfStr;
    return (LocalString);
}

bool AILevelSwitchVega::RestoreAISettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    AnsiString PROName = "Analog input";
    if (PROPtr)   PROName += (AnsiString)", for " + PROPtr->Name;
    PROName += ":\n";
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                RestoreSettingsWarning(PROName + (AnsiString)"Unknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
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
            case C_AI_MA_LEV_SWITCH_ON :
                SwitchOn_mA = SettingsString->ReadDouble(ErrorLine);
                break;
            case C_AI_MA_LEV_SWITCH_OFF:
                SwitchOff_mA = SettingsString->ReadDouble(ErrorLine);
                break;
            case C_AI_MA_LEV_SWITCH_WIN:
                SwitchWindow = SettingsString->ReadDouble(ErrorLine);
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
    }while (NoError && (ErrorLine != EOF) && (Key != C_AI_END));
    return (NoError);
}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AILevelSwitchVega::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_MA_ON  :
        {
            // This value starts with a threshold of 0.1 mA
            float Value = ConvertToSi(NewValue, CURRENT_UNIT, Status,  0.1 / 1000, 20.0 / 1000, SwitchOn_mA);
            if (Status == E_NO_ERR) {
                SwitchOn_mA = Value + SwitchOff_mA;
                TimeModified = time(NULL);
            }
        }
        break;
    case SVT_MA_OFF  :
        {
            float Value = ConvertToSi(NewValue, CURRENT_UNIT, Status, SwitchTest + 0.1 / 1000, 20.0 / 1000, SwitchOff_mA);
            if (Status == E_NO_ERR) {
                SwitchOff_mA = Value;
                TimeModified = time(NULL);
            }
        }
        break;
    default:
        Status = AILevelSwitch_mA::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
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

int  AILevelSwitchVega::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_MA_ON  :
        MyRetValue = SwitchOn_mA - SwitchOff_mA;
        DecPnt     = 2;
        Unit       = CURRENT_UNIT;
        break;
    default:
        Status = AILevelSwitch_mA::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}


int AILevelSwitchVega::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AI_RANGE:
        MyString = "Norm " + LibGetValue(SVT_MA_OFF, this) + " Threshold " + LibGetValue(SVT_MA_ON, this);
        break;
    default:
        Status = AILevelSwitch_mA::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}




///////////////////////////////////////////////////////////////
//
// Routines for Calculation of values
//
///////////////////////////////////////////////////////////////




float AILevelSwitchVega::Calculate(void) {
    if (CanCalculate()) {
        float tmpCalcValue = Gain * FilteredValue - Offset;
        // Don't use window for ON and OFF
        if ( (fabs(tmpCalcValue - SwitchTest) < SwitchWindow)) {
            LastTestTime  = clock();
            CalcValue     = LEVELSWITCH_TEST;
            Failure       = false;
        } else if (TSNElapsedTicks(LastTestTime) > 5000) {
            if (tmpCalcValue <= SwitchOff_mA) {
                CalcValue = LEVELSWITCH_OFF;
                Failure = false;
            } else if (tmpCalcValue >= SwitchOn_mA) {
                CalcValue = LEVELSWITCH_ON;
                Failure   = false;
            } else {
                CalcValue = LEVELSWITCH_OFF; // Was LEVELSWITCH_ERROR;
                Failure   = true;
            }
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

