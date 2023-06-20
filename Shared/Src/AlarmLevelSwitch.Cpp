#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmLevelSwitch::NumberOfAlarmSettings = 0;

AlarmLevelSwitch::AlarmLevelSwitch(PRogramObjectBase *PROPtr, AnsiString LocName, AnsiString Descr):AlarmBasic(PROPtr) {
    PROPointer          = PROPtr;
    //PROAtmReference *PROAtmPtr = (PROAtmReference*)PROPointer;
    NumberOfAlarmSettings++;
    IDNumber            = (ID_AL_LEVEL_SWITCH << 16) + NumberOfAlarmSettings;
    Type                = ID_AL_LEVEL_SWITCH;
    Limit               = 1.0;
    Deadband            = 0.0;
    Name                = LocName;
    Description         = Descr;
    MessageKey          = L_WORD677;    // Level
    TPCMessageKey       = L_WORD678;    // Lvl
}

void AlarmLevelSwitch::Check(void) {
    bool IsActive = ((PROLevelSwitch *)PROPointer)->IsActive;

    int Status = AL_STAT_IN_DEADBAND;
    if (IsActive) {
		if ( TSNElapsedTicks(LastInactiveTime) < AlarmDelay ) {
			Status = AL_STAT_IN_NORMAL;
		}else{
			Status = AL_STAT_IN_ALARM;
		}
    } else {
		LastInactiveTime = clock();
        if (TSNElapsedTicks(LastActiveTime) > PROSystemData::AlarmOffDelay) {
            Status = AL_STAT_IN_NORMAL;
        }
    }
    UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int AlarmLevelSwitch::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
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

int  AlarmLevelSwitch::GetValue(int ValueId, int Index, float& MyRetValue, int& DecPnt, int& Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AL_LIMIT:
        MyRetValue = 1.0;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_AL_VALUE:
        MyRetValue = (float)((PROLevelSwitch *)PROPointer)->IsActive;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    default:
        Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AlarmLevelSwitch::GetStringValue(int ValueId, int Index, AnsiString& MyString) {
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //	default:
    Status = AlarmBasic::GetStringValue(ValueId, Index, MyString);
    //		break;
    //}
    return (Status);
}

int AlarmLevelSwitch::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return (Status);
}

AnsiString AlarmLevelSwitch::Get_Message(void)
{
    if (Description.IsEmpty()) {
        return  AlarmBasic::Get_Message();
    }
    return Description;
}
