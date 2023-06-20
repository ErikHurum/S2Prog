#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AlarmAirPurgeSensorFailure::~AlarmAirPurgeSensorFailure(void) {
}

unsigned AlarmAirPurgeSensorFailure::NumberOfAlarms = 0;

AlarmAirPurgeSensorFailure::AlarmAirPurgeSensorFailure(PRogramObjectBase *PROPtr) : AlarmBasic(PROPtr) {
    NumberOfAlarms++;
    PROPointer      = PROPtr;
    IDNumber        = (ID_AL_SNS_AIR_PURGE_FAILURE << 16) + NumberOfAlarms;
    Type            = ID_AL_SNS_AIR_PURGE_FAILURE;
    Limit           = true;
    Deadband        = 0;
    MessageKey      = L_WORD528;        // Failure
    TPCMessageKey   = L_WORD540;        // HWErr
    Count           = 0;
    IsHWAlarm       = true;
}

void AlarmAirPurgeSensorFailure::Check(void) {
    int Status = AL_STAT_IN_DEADBAND;
    if ( ((AnalogInput *)PROPointer)->Failure & AIR_PURGE_SNS_FAIL ) {
        Status = AL_STAT_IN_ALARM;
    } else {
        if ( TSNElapsedTicks(LastActiveTime) > 10000 ) {
            Status = AL_STAT_IN_NORMAL;
        }
    }
    UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmAirPurgeSensorFailure::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AL_LIMIT:
        Status = E_NO_INPUT_PERMISSION;
        break;
    default:
        Status = AlarmBasic::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    if ( Status == E_NO_ERR ) {
        SetModifiedFlag();
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int  AlarmAirPurgeSensorFailure::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AL_LIMIT:
        MyRetValue = Limit;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_AL_VALUE:
        MyRetValue = !((AnalogInput *)PROPointer)->ResultOK;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    default:
        Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}


int AlarmAirPurgeSensorFailure::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AP_TPRESS_SNS_FAIL:
    case SVT_AP_LPRESS_SNS_FAIL:
        Status = AlarmBasic::GetStringValue(SVT_AL_STATE, Index, MyString);
        break;
    default:
        Status = AlarmBasic::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int AlarmAirPurgeSensorFailure::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return (Status);
}


