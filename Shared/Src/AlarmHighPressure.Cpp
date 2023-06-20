#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmHighPressure::NumberOfAlarmSettings = 0;

AlarmHighPressure::AlarmHighPressure(void):AlarmBasic((PRogramObjectBase*)NULL) {
    NumberOfAlarmSettings++; // Should not do this, but must maintain backward compatibility
    Deadband          = 10.0 / MH2O_TO_MBAR;
}

AlarmHighPressure::AlarmHighPressure(PRogramObjectBase *PROPtr, bool isParent):AlarmBasic(PROPtr) {
    NumberOfAlarmSettings++;
    PROPointer        = PROPtr;
    PROTPressPtr      = (PROTankPressure *)PROPtr;
    IDNumber          = (ID_AL_HIGH_T_PRESS << 16) + NumberOfAlarmSettings;
    Type              = ID_AL_HIGH_T_PRESS;
    Deadband          = 10.0 / MH2O_TO_MBAR;
    Locked            = PROTPressPtr->HighTankPressLocked;
    Limit             = PROTPressPtr->HighTankPressLimit;
    if ( PROProjectInfo::IsInlandVessel ) {
        MessageKey      = L_WORD774;    // High
        char Buf[BUF_SIZE];
        sprintf(Buf, "%s %3.0fkPa", FindDictionaryWord(MessageKey).c_str(), Limit * MH2O_TO_KPA);
        Description = AnsiString(Buf);
    } else {
        MessageKey     = L_WORD506;  // HighPressure
    }
    TPCMessageKey      = L_WORD507;  // HPre
}
AnsiString AlarmHighPressure::Get_Message(void) {
    if ( PROProjectInfo::IsInlandVessel ) {
        return (Description);
    } else {
        return (FindDictionaryWord(MessageKey));
    }
}


void AlarmHighPressure::Check(void) {
    int Status = AL_STAT_IN_DEADBAND;
    if ( PROTPressPtr->HasPressure ) {
        float Val = PROTPressPtr->Pressure;
        if ( Val < Limit - Deadband ) {
            Status = AL_STAT_IN_NORMAL;
        } else if ( Val >= Limit ) {
            Status = AL_STAT_IN_ALARM;
        }
    } else {
        Status = AL_STAT_IN_NORMAL;
    }
    UpdateAlarm(Status);
}

int AlarmHighPressure::GetOperationMode(void) {
    return int(PROTPressPtr->VapourAlarmSet);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmHighPressure::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    if ( Locked ) {
        Status = E_NO_INPUT_PERMISSION;
    } else {
        float OrgLimit = Limit;
        int Key = FindConfigKey(NewValue);
        switch ( Key ) {
        case C_ON:
        case C_OPEN:
        case C_ENABLE:
            SetEnable(EnableTrue);
            PROTPressPtr->SetState(tUndefined);
            break;
        case C_OFF:
        case C_CLOSE:
        case C_DISABLE:
            SetEnable(EnableFalse);
            PROTPressPtr->SetState(tUndefined);
            break;
        default:
            switch ( ValueId ) {
            case SVT_AL_LIMIT:
                if ( PROTPressPtr->MaxPressureRange > 4.0 ) {
                    float Value = ConvertToSi(NewValue, ValUnitId = PRESSURE_UNIT1, Status, 2 * LIMIT_LOW_LPG_PRESS, LIMIT_HIGH_LPG_PRESS, 0.0);
                    if ( Status == E_NO_ERR ) {
                        Limit = Value;
                    }
                } else {
                    float MinInput, MaxInput;
                    PROTPressPtr->GetMaxPresureLimits(MinInput, MaxInput);
                    float Value = ConvertToSi(NewValue, ValUnitId = PRESSURE_UNIT1, Status, MinInput, MaxInput, 0.0);
                    if ( Status == E_NO_ERR ) {
                        Limit = Value;
                    }
                }
                break;
            default:
                Status = AlarmBasic::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
                break;
            }
            break; // switch ( ValueId )
        } //switch ( Key )
        if ( Status == E_NO_ERR ) {
            SetModifiedFlag();
            if ( Limit != OrgLimit ) {
                LogEvent("New limit");
            }
        }
    } // if ( Locked ) else
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int  AlarmHighPressure::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AL_LIMIT:
        MyRetValue = Limit;
        DecPnt     = 1;
        Unit       = PRESSURE_UNIT1;
        if ( !Enable ) {
            Status     = GETVAL_DISABLED;
        }
        break;
    case SVT_AL_VALUE:
        MyRetValue = PROTPressPtr->Pressure;
        DecPnt     = 1;
        Unit       = PRESSURE_UNIT1;
        break;
    default:
        Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AlarmHighPressure::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //	default:
    Status = AlarmBasic::GetStringValue(ValueId, Index, MyString);
    //		break;
    //}
    return (Status);
}

int AlarmHighPressure::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return (Status);
}

//---------------------------------------------------------------------------

bool AlarmHighPressure::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    if ( !Locked ) {
        int ErrorLine   = 0;
        int Key         = C_UNDEFINED;
        AnsiString PROName = "Alarm setting";
        if ( PROPointer )   PROName += (AnsiString)", for " + PROPointer->Name;
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
                    NoError = false;
                    RestoreSettingsWarning(PROName + (AnsiString)"The keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                    break;
                case C_AL_LIMIT:
                    {
                        float NewLimit = SettingsString->ReadDouble(ErrorLine);
                        if ( NoError ) {
                            if ( PROTPressPtr->MaxPressureRange > 4.0 ) {
                                if ( NewLimit >= 2 * LIMIT_LOW_LPG_PRESS && NewLimit <= LIMIT_HIGH_LPG_PRESS ) {
                                    Limit = NewLimit;
                                }
                            } else {
                                float MinInput, MaxInput;
                                PROTPressPtr->GetMaxPresureLimits(MinInput, MaxInput);
                                if ( NewLimit >= MinInput && NewLimit <= MaxInput ) {
                                    Limit = NewLimit;
                                }
                            }
                        }
                    }
                    NoError = !ErrorLine;
                    break;
                case C_ENABLE:
                    Enable = true;
                    break;
                case C_DISABLE:
                    Enable = false;
                    break;
                case C_PREVIOUS_ENABLE:
                    PreviousEnable = true;
                    break;
                case C_PREVIOUS_DISABLE:
                    PreviousEnable = false;
                    break;
                case C_AL_END:
                    break;
                }
            }
        }while ( NoError && (ErrorLine != EOF) && (Key != C_AL_END) );
    }
    return (NoError);
}


