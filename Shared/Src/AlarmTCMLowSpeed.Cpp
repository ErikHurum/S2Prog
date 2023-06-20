#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmTCMLowSpeed::NumberOfAlarmSettings = 0;

AlarmTCMLowSpeed::AlarmTCMLowSpeed(PRogramObjectBase *PROPtr) : AlarmBasic(PROPtr) {
    NumberOfAlarmSettings++;
    PROPointer          = PROPtr;
    PROTCMPtr           = (PROTankWashingMachine *)PROPtr;
    IDNumber            = (ID_AL_TWM_LOW_SPEED << 16) + NumberOfAlarmSettings;
    Type                = ID_AL_TWM_LOW_SPEED;
    Enable              = false;
    Locked              = false;
    CanDisableOnly      = true;
    Limit				= MIN_TWM_SPEED;
    Deadband            = 0.1;
    MessageKey          = L_WORD1116;   // Low speed
    TPCMessageKey       = L_WORD1117;   // LoSpd
    PreviousEnable      = Enable;
}

void AlarmTCMLowSpeed::Check(void) {
    float Val = PROTCMPtr->Speed;
    int Status = AL_STAT_IN_DEADBAND;
    if ( PROTCMPtr->IsNewData ) {
        if ( Val > Limit + Deadband ) {
            Status = AL_STAT_IN_NORMAL;
        } else if ( Val <= Limit ) {
            Status = AL_STAT_IN_ALARM;
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

int AlarmTCMLowSpeed::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AL_ENABLE:
        if ( Locked && !CanDisableOnly ) {
            Status = E_NO_INPUT_PERMISSION;
        } else {
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
                break;
            } //switch ( Key )
        }
        break;
    case SVT_AL_LIMIT:
        if ( Locked  ) {
            Status = E_NO_INPUT_PERMISSION;
        } else {
            float OrgLimit = Limit;
            float Value = ConvertToSi(NewValue, ValUnitId = REVOLUTIONS_UNIT, Status, MIN_TWM_SPEED, MAX_TWM_SPEED, MIN_TWM_SPEED);
            if ( Status == E_NO_ERR ) {
                Limit = Value;
                if ( Status == E_NO_ERR ) {
                    SetModifiedFlag();
                    if ( Limit != OrgLimit ) {
                        LogEvent("New limit");
                    }
                }
            }
        }
        break;
    default:
        Status = AlarmBasic::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    } // switch ( ValueId )
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int  AlarmTCMLowSpeed::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AL_LIMIT:
        MyRetValue = Limit;
        DecPnt     = 2;
        Unit       = REVOLUTIONS_UNIT;
        if ( !Enable ) {
            Status     = GETVAL_DISABLED;
        }
        break;
    case SVT_AL_VALUE:
        MyRetValue = PROTCMPtr->Speed;
        DecPnt     = 2;
        Unit       = REVOLUTIONS_UNIT;
        break;
    default:
        Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AlarmTCMLowSpeed::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //	default:
    Status = AlarmBasic::GetStringValue(ValueId, Index, MyString);
    //		break;
    //}
    return (Status);
}

int AlarmTCMLowSpeed::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return (Status);
}

