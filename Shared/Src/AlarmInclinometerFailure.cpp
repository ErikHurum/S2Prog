#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AlarmInclinometerFailure::~AlarmInclinometerFailure(void) {
}

unsigned AlarmInclinometerFailure::NumberOfAlarmSettings = 0;

AlarmInclinometerFailure::AlarmInclinometerFailure(PRogramObjectBase *PROPtr):AlarmBasic(PROPtr) {
    PROPointer = PROPtr;
    NumberOfAlarmSettings++;
    IDNumber        = (ID_AL_INCLINOMETER << 16) + NumberOfAlarmSettings;
    Type            = ID_AL_INCLINOMETER;
    Limit           = DATA_EXPIRATION_TIME;
    MessageKey		= L_WORD528;    // Failure
    TPCMessageKey	= L_WORD1003;    // Fail
    IsHWAlarm       = true;
}

void AlarmInclinometerFailure::Check(void) {

    int Status = AL_STAT_IN_DEADBAND;
	if (PROPointer->IsAvailableNewData()) {
        Status = AL_STAT_IN_NORMAL;
    } else /*if ( FailCnt >= Limit ) */ {
        Status = AL_STAT_IN_ALARM;
    }
    UpdateAlarm(Status);

}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

AnsiString AlarmInclinometerFailure::Get_CompleteMessage(void)
{
	AnsiString Loc = PROPointer->GetName();
	return(Loc + " " + Get_Message());
}

int AlarmInclinometerFailure::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_AL_LIMIT:
        Status = E_NOT_ADJUSTABLE;
        break;
    default:
        Status = AlarmBasic::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
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

int  AlarmInclinometerFailure::GetValue(int ValueId, int Index, float& MyRetValue, int& DecPnt, int& Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AL_LIMIT:
        MyRetValue = (float)Limit;
        DecPnt     = 0;
        Unit       = MSECOND_UNIT;
        break;
    case SVT_AL_VALUE:
        MyRetValue = float(PROPointer->TimeStamp);
        DecPnt     = 0;
        Unit       = MSECOND_UNIT;
        break;
    default:
        Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}


int AlarmInclinometerFailure::GetStringValue(int ValueId, int Index, AnsiString& MyString) {
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //	default:
    Status = AlarmBasic::GetStringValue(ValueId, Index, MyString);
    //		break;
    //}
    return (Status);
}

int AlarmInclinometerFailure::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return (Status);
}

