#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmAtmOutOfRange::NumberOfAlarmSettings=0;

AlarmAtmOutOfRange::AlarmAtmOutOfRange(PRogramObjectBase *PROPtr):AlarmBasic(PROPtr)
{
	PROPointer = PROPtr;
	//PROAtmReference *PROAtmPtr = (PROAtmReference*)PROPointer;
	NumberOfAlarmSettings++;
	IDNumber  = (ID_AL_ATM_OUT_OF_RANGE << 16)+NumberOfAlarmSettings;
	Type      = ID_AL_ATM_OUT_OF_RANGE;
	Limit     = 1.0;
	Deadband  = 0.0;
	MessageKey   = L_WORD500; // OutOfRange
}


void AlarmAtmOutOfRange::Check(void)
{
	bool IsOutOfRange = ((PROAtmReference*)PROPointer)->IsOutOfRange;

	int Status = AL_STAT_IN_DEADBAND;
	if ( IsOutOfRange ) {
		Status = AL_STAT_IN_ALARM;
	} else {
		Status = AL_STAT_IN_NORMAL;
	}
	UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int AlarmAtmOutOfRange::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AlarmAtmOutOfRange::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = 1.0;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		case SVT_AL_VALUE:
			MyRetValue = (float)((PROAtmReference*)PROPointer)->IsOutOfRange;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}

int AlarmAtmOutOfRange::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmAtmOutOfRange::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}

