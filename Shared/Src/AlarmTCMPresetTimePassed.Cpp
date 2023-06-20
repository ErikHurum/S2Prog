#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmTCMPresetTimePassed::NumberOfAlarmSettings = 0;

AlarmTCMPresetTimePassed::AlarmTCMPresetTimePassed(PRogramObjectBase *PROPtr) : AlarmBasic(PROPtr) {
    NumberOfAlarmSettings++;
    PROPointer          = PROPtr;
    PROTCMPtr           = (PROTankWashingMachine *)PROPtr;
    IDNumber            = (ID_AL_TWM_ELAPSED_TIME << 16) + NumberOfAlarmSettings;
    Type                = ID_AL_TWM_ELAPSED_TIME;
    Limit				= DEFAULT_TWM_PRESET_TIME * SEC_TO_HOURS;
    Enable              = false;
    Locked              = false;
    Deadband            = 0.0;          // Not used for this type of alarm
    MessageKey          = L_WORD1118;   // Preset time
    TPCMessageKey       = L_WORD1119;   // PreTm
    PreviousEnable      = Enable;
}

void AlarmTCMPresetTimePassed::Check(void) {
    float Speed       = PROTCMPtr->Speed;
    float RunningTime = PROTCMPtr->RunningTime;
    int Status        = AL_STAT_IN_DEADBAND;
    if ( PROTCMPtr->IsNewData ) {
        if ( RunningTime > Limit ) {
            Status = AL_STAT_IN_ALARM;
        } else if ( Speed < MIN_TWM_SPEED ) {
            Status = AL_STAT_IN_NORMAL;
        }
    } else {
        Status = AL_STAT_IN_NORMAL;
    }
    UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmTCMPresetTimePassed::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    if ( Locked ) {
        Status = E_NO_INPUT_PERMISSION;
    } else {
        switch ( ValueId ) {
        case SVT_AL_ENABLE:
            {
                int Key = FindConfigKey(NewValue);
                switch ( Key ) {
                case C_ON		:
                case C_OPEN		:
                case C_ENABLE	:
                    SetEnable(EnableTrue);
                    break;
                case C_OFF		:
                case C_CLOSE	:
                case C_DISABLE	:
                    SetEnable(EnableFalse);
                }//switch ( Key )
            } 
            break;
        case SVT_AL_LIMIT:
            {
                float OrgLimit = Limit;
                float Value = ConvertToSi(NewValue, ValUnitId = HOUR_UNIT, Status, 0/*MIN_TWM_PRESET_TIME * SEC_TO_HOURS*/, MAX_TWM_PRESET_TIME * SEC_TO_HOURS, DEFAULT_TWM_PRESET_TIME * SEC_TO_HOURS);
                if ( Status == E_NO_ERR ) {
                    Limit = Value;
                    SetModifiedFlag();
                    if ( Limit != OrgLimit ) {
                        LogEvent("New limit");
                    }
                }
            }
            break;
        default:
            Status = AlarmBasic::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
            break;
        } // Switch ValueId
    } // if ( Locked ) else
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int  AlarmTCMPresetTimePassed::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AL_LIMIT:
        MyRetValue = Limit;
        DecPnt     = 1;
        Unit       = HOUR_UNIT;
        if ( !Enable ) {
            Status     = GETVAL_DISABLED;
        }
        break;
    case SVT_AL_VALUE:
        {
            float RunningTime = PROTCMPtr->RunningTime;
            MyRetValue = RunningTime;
            DecPnt     = 1;
            Unit       = HOUR_UNIT;
        }
        break;
    default:
        Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AlarmTCMPresetTimePassed::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //	default:
    Status = AlarmBasic::GetStringValue(ValueId, Index, MyString);
    //		break;
    //}
    return (Status);
}

int AlarmTCMPresetTimePassed::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return (Status);
}

