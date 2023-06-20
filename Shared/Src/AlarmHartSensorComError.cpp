#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AlarmHartSensorComError::~AlarmHartSensorComError(void) {
}

unsigned AlarmHartSensorComError::NumberOfAlarms = 0;

AlarmHartSensorComError::AlarmHartSensorComError(PRogramObjectBase *PROPtr, int &HartComErrorCnt) : AlarmBasic(PROPtr), Count(HartComErrorCnt) {
    NumberOfAlarms++;
    PROPointer      = PROPtr;
    IDNumber        = (ID_AL_SNS_HART_COM_ERROR << 16) + NumberOfAlarms;
    Type            = ID_AL_SNS_HART_COM_ERROR;
    Limit           = MAX_HART_COM_ERRORS;
    Deadband        = 0;
    MessageKey      = L_WORD998;        // HartCom
    TPCMessageKey   = L_WORD540;        // HWErr
    IsHWAlarm       = true;
}

void AlarmHartSensorComError::Check(void) {

    int Status = AL_STAT_IN_DEADBAND;
    if ( Count > MAX_HART_COM_ERRORS ) {
        Status = AL_STAT_IN_ALARM;
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

int AlarmHartSensorComError::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
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

int  AlarmHartSensorComError::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AL_LIMIT:
        MyRetValue = Limit;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_AL_VALUE:
        MyRetValue = float(Count);
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    default:
        Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}


int AlarmHartSensorComError::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //	default:
    Status = AlarmBasic::GetStringValue(ValueId, Index, MyString);
    //		break;
    //}
    return (Status);
}

int AlarmHartSensorComError::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return (Status);
}


