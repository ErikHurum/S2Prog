#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmHighLevel::NumberOfAlarmSettings = 0;

AlarmHighLevel::AlarmHighLevel(PRogramObjectBase *PROPtr, float Lim, bool Lock):AlarmBasic(PROPtr) {
    PROPointer  = PROPtr;
    PROTankPtr  = (PROTank *)PROPtr;
    Locked      = Lock;
    Limit       = Lim;

    if ( PROTankPtr->LevVolumeTab ) {
        LevVolumeTab = PROTankPtr->LevVolumeTab;
        UllVolumeTab = NULL;
        VolumeTab    = LevVolumeTab;
    } else if ( PROTankPtr->UllVolumeTab ) {
        UllVolumeTab = PROTankPtr->UllVolumeTab;
        LevVolumeTab = NULL;
        VolumeTab    = UllVolumeTab;
    } else {
        UllVolumeTab = NULL;
        LevVolumeTab = NULL;
        VolumeTab    = NULL;
    }
    if ( UllVolumeTab || LevVolumeTab ) {
        LimitType = AL_LIM_VOLPERCENT;
        OnlyLevel = false;
    } else {
        LimitType = AL_LIM_LEVEL;
        OnlyLevel = true;
    }
    NumberOfAlarmSettings++;
    IDNumber            =  (ID_AL_HIGH_LEVEL << 16) + NumberOfAlarmSettings;
    Type                = ID_AL_HIGH_LEVEL;
    Deadband            = 0.1;
    MessageKey          = L_WORD503; // HighLevel
    TPCMessageKey       = L_WORD502; // HLev
}

void AlarmHighLevel::Check(void) {
    int Status = AL_STAT_IN_DEADBAND;
    if ( PROTankPtr->HasLevelSensors ) {
        float Val;
        if ( LevVolumeTab || UllVolumeTab ) {
            Val = PROTankPtr->VolumePercent;
        } else {
            Val = PROTankPtr->Level;
        }
        if ( Val < Limit - Deadband ) {
            if ( TSNElapsedTicks(LastActiveTime) > PROSystemData::AlarmOffDelay ) {
                Status = AL_STAT_IN_NORMAL;
            }
        } else if ( Val >= Limit ) {
            Status = AL_STAT_IN_ALARM;
        }
    } else if ( TSNElapsedTicks(LastActiveTime) > PROSystemData::AlarmOffDelay ) {
        Status = AL_STAT_IN_NORMAL;
    }
    UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmHighLevel::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
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
            PROTankPtr->SetState(tUndefined);
            break;
        case C_OFF:
        case C_CLOSE:
        case C_DISABLE:
            SetEnable(EnableFalse);
            PROTankPtr->SetState(tUndefined);
            break;
        default:
            switch ( ValueId ) {
            case SVT_AL_LIMIT_TYPE_LEV:
                if ( !OnlyLevel ) {
                    int Value = GetInt(NewValue, Status);
                    if ( Status == E_NO_ERR ) {
                        LimitType = Value;
                    }
                } else {
                    Status = E_ILLEGAL;
                }
                break;
            case SVT_AL_LIMIT:
                if ( OnlyLevel ) {
                    Limit = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, 0.0, PROTankPtr->DBotUllRefPnt, Limit);
                } else {
                    Limit = ConvertToSi(NewValue, ValUnitId = PERCENT_UNIT, Status, 0.0, 100.0, Limit);
                }
                break;
            case SVT_HI_VOLPCNT_LIM:
                switch ( LimitType ) {
                case AL_LIM_VOLPERCENT:
                    Limit = ConvertToSi(NewValue, ValUnitId = PERCENT_UNIT, Status, 0.0, 100.0, Limit);
                    break;
                case AL_LIM_LEVEL     :
                    Status = E_ILLEGAL;
                    break;
                }
                break;
            case SVT_HI_VOLUME_LIM :
                switch ( LimitType ) {
                case AL_LIM_VOLPERCENT:
                    {
                        float MaxVolume = VolumeTab->MaxY;
                        float NewLimit = ConvertToSi(NewValue, ValUnitId = VOLUME_UNIT, Status, 0.0, MaxVolume, 0.0);
                        if ( Status == E_NO_ERR ) {
                            Limit = NewLimit / MaxVolume * 100.0;
                        }
                    }
                    break;
                case AL_LIM_LEVEL     :
                    Status = E_ILLEGAL;
                    break;
                }
                break;
            case SVT_HI_WEIGHT_LIM :
                switch ( LimitType ) {
                case AL_LIM_VOLPERCENT:
                    {
                        float MaxWeight = VolumeTab->MaxY * PROTankPtr->Density;
                        float NewLimit = ConvertToSi(NewValue, ValUnitId = WEIGHT_UNIT, Status, 0.0, MaxWeight, 0.0);
                        NewLimit = CorrectToWeightInVacuum(NewLimit, PROTankPtr->Density);
                        if ( Status == E_NO_ERR ) {
                            Limit = NewLimit / MaxWeight * 100.0;
                        }
                    }
                    break;
                case AL_LIM_LEVEL     :
                    Status = E_ILLEGAL;
                    break;
                }
                break;
            case SVT_HI_ULLAGE_LIM :
                switch ( LimitType ) {
                case AL_LIM_VOLPERCENT:
                    {
                        float NewLimit = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, 0.0, PROTankPtr->DBotUllRefPnt, 0.0);
                        if ( Status == E_NO_ERR ) {
                            if ( UllVolumeTab ) {
                                Limit = UllVolumeTab->Calc_YPercent(NewLimit);
                            } else {
                                float Level = PROTankPtr->DBotUllRefPnt - NewLimit;
                                Limit = LevVolumeTab->Calc_YPercent(Level);
                            }
                        }
                    }
                    break;
                case AL_LIM_LEVEL     :
                    Status = E_ILLEGAL;
                    break;
                }
                break;
            case SVT_HI_LEVEL_LIM  :
                switch ( LimitType ) {
                case AL_LIM_VOLPERCENT:
                    {
                        float NewLimit = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, 0.0, PROTankPtr->DBotUllRefPnt, 0.0);
                        if ( Status == E_NO_ERR ) {
                            if ( UllVolumeTab ) {
                                float UllageRef = PROTankPtr->DBotUllRefPnt - NewLimit;
                                Limit = UllVolumeTab->Calc_YPercent(UllageRef);
                            } else {
                                Limit = LevVolumeTab->Calc_YPercent(NewLimit);
                            }
                        }
                    }
                    break;
                case AL_LIM_LEVEL     :
                    Limit = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, 0.0, PROTankPtr->DBotUllRefPnt, Limit);
                    break;
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

int  AlarmHighLevel::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AL_LIMIT_TYPE_LEV:
        MyRetValue = LimitType;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_AL_LIMIT:
        MyRetValue = Limit;
        if ( OnlyLevel ) {
            DecPnt     = 2;
            Unit       = LENGTH_UNIT;
        } else {
            DecPnt     = 1;
            Unit       = PERCENT_UNIT;
        }
        break;
    case SVT_HI_VOLPCNT_LIM:
        switch ( LimitType ) {
        case AL_LIM_VOLPERCENT:
            MyRetValue = Limit;
            if ( !Enable ) {
                Status     = GETVAL_DISABLED;
            }
            break;
        case AL_LIM_LEVEL     :
            Status = GETVAL_NOT_AVAILABLE;
            break;
        }
        DecPnt     = 1;
        Unit       = PERCENT_UNIT;
        break;
    case SVT_HI_VOLUME_LIM :
        switch ( LimitType ) {
        case AL_LIM_VOLPERCENT:
            MyRetValue = VolumeTab->MaxY * Limit / 100.0;
            if ( !Enable ) {
                Status     = GETVAL_DISABLED;
            }
            break;
        case AL_LIM_LEVEL     :
            Status = GETVAL_NOT_AVAILABLE;
            break;
        }
        DecPnt     = 1;
        Unit       = VOLUME_UNIT;
        break;
    case SVT_HI_WEIGHT_LIM :
        switch ( LimitType ) {
        case AL_LIM_VOLPERCENT:
            MyRetValue = GetCorrectedWeight(VolumeTab->MaxY * Limit / 100.0 * PROTankPtr->Density, PROTankPtr->Density);
            if ( !Enable ) {
                Status     = GETVAL_DISABLED;
            }
            break;
        case AL_LIM_LEVEL     :
            Status = GETVAL_NOT_AVAILABLE;
            break;
        }
        DecPnt     = 1;
        Unit       = WEIGHT_UNIT;
        break;
    case SVT_HI_ULLAGE_LIM :
        switch ( LimitType ) {
        case AL_LIM_VOLPERCENT:
            if ( UllVolumeTab ) {
                MyRetValue = UllVolumeTab->Calc_XPercent(Limit);
            } else {
                float MyLevel = LevVolumeTab->Calc_XPercent(Limit);
                MyRetValue    = PROTankPtr->DBotUllRefPnt - MyLevel;
            }
            break;
        case AL_LIM_LEVEL     :
            MyRetValue = PROTankPtr->DBotUllRefPnt - Limit;
            break;
        }
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        if ( !Enable ) {
            Status     = GETVAL_DISABLED;
        }
        break;
    case SVT_HI_LEVEL_LIM  :
        switch ( LimitType ) {
        case AL_LIM_VOLPERCENT:
            if ( UllVolumeTab ) {
                float MyUllageRef = UllVolumeTab->Calc_XPercent(Limit);
                MyRetValue    = PROTankPtr->DBotUllRefPnt - MyUllageRef;
            } else {
                MyRetValue = LevVolumeTab->Calc_XPercent(Limit);
            }
            break;
        case AL_LIM_LEVEL     :
            MyRetValue = Limit;
            break;
        }
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        if ( !Enable ) {
            Status     = GETVAL_DISABLED;
        }
        break;
    case SVT_AL_VALUE:
        switch ( LimitType ) {
        case AL_LIM_VOLPERCENT:
            MyRetValue = PROTankPtr->VolumePercent;
            DecPnt     = 1;
            Unit       = PERCENT_UNIT;
            break;
        case AL_LIM_LEVEL     :
            MyRetValue = PROTankPtr->Level;
            DecPnt     = 2;
            Unit       = LENGTH_UNIT;
            break;
        }
        if ( !Enable ) {
            Status     = GETVAL_DISABLED;
        }
        break;
    default:
        Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AlarmHighLevel::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //	default:
    Status = AlarmBasic::GetStringValue(ValueId, Index, MyString);
    //		break;
    //}
    return (Status);
}

int AlarmHighLevel::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch ( ValueId ) {
    case SVT_HI_ULLAGE_LIM :
        switch ( LimitType ) {
        case AL_LIM_VOLPERCENT:
            if ( UllVolumeTab ) {
                Limit = UllVolumeTab->Calc_YPercent(NewValue);
            } else {
                float Level = PROTankPtr->DBotUllRefPnt - NewValue;
                Limit = LevVolumeTab->Calc_YPercent(Level);
            }
            break;
        case AL_LIM_LEVEL     :
            {
                float Lim = PROTankPtr->DBotUllRefPnt - NewValue;
                if ( Lim < 0.0 ) {
                    Lim = 0.0;
                }
                Limit = Lim;
            }
            break;
        }
        break;
    case SVT_HI_LEVEL_LIM  :
        switch ( LimitType ) {
        case AL_LIM_VOLPERCENT:
            if ( UllVolumeTab ) {
                float UllageRef = PROTankPtr->DBotUllRefPnt - NewValue;
                Limit = UllVolumeTab->Calc_YPercent(UllageRef);
            } else {
                Limit = LevVolumeTab->Calc_YPercent(NewValue);
            }
            break;
        case AL_LIM_LEVEL     :
            Limit = NewValue;
            break;
        }
        break;
    default:
        Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);
}



