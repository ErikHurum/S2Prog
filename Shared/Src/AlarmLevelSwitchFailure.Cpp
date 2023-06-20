#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmLSwitchFailure::NumberOfAlarmSettings=0;

AlarmLSwitchFailure::AlarmLSwitchFailure(PRogramObjectBase *PROPtr):AlarmBasic(PROPtr)
{
	PROPointer = PROPtr;
	//PROAtmReference *PROAtmPtr = (PROAtmReference*)PROPointer;
	NumberOfAlarmSettings++;
	IDNumber  = (ID_AL_LSWITCH_FAILURE << 16)+NumberOfAlarmSettings;
	Type      = ID_AL_LSWITCH_FAILURE;
	Limit     = 1.0;
	Deadband  = 0.0;
	FailureCnt= 0;
	MessageKey      = L_WORD528;	// Failure
}

void AlarmLSwitchFailure::Check(void)
{
	int Status = AL_STAT_IN_DEADBAND;
	switch ( int(((AILevelSwitch_mA*)PROPointer)->CalcValue) ) {
	case LEVELSWITCH_HW_ERROR:
		UpdateAlarm(AL_STAT_IN_NORMAL);
		if (State == AlActive) {
			MoveAlarmToAknowledge();
		}
		break;
	case LEVELSWITCH_ERROR: 
		if ( FailureCnt < LEVELSWITCH_ERROR_CNT ) {
			FailureCnt++;
			Status = AL_STAT_IN_NORMAL;
		} else {
			Status  = AL_STAT_IN_ALARM;
		}
		UpdateAlarm(Status);
		break;
	default:
		Status       = AL_STAT_IN_NORMAL;
		FailureCnt = 0;
		UpdateAlarm(Status);
		break;
	}
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int AlarmLSwitchFailure::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
	case SVT_AL_LIMIT:
		Status = E_NOT_ADJUSTABLE;
		break;
	default:
		Status = AlarmBasic::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
		break;
	}
	if ( Status==E_NO_ERR ) {
		SetModifiedFlag();
	}
	if ( UnitId ) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AlarmLSwitchFailure::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_AL_LIMIT:
		MyRetValue = 1.0;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_AL_VALUE:
		MyRetValue = (float)((AILevelSwitch_mA*)PROPointer)->CalcValue;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	default:
		Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
		break;
	}
	return(Status);
}

int AlarmLSwitchFailure::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmLSwitchFailure::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}

