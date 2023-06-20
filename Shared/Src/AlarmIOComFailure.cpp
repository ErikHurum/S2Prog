#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AlarmIOComFailure::~AlarmIOComFailure(void)
{
}

unsigned AlarmIOComFailure::NumberOfAlarmSettings=0;

AlarmIOComFailure::AlarmIOComFailure(PRogramObjectBase *PROPtr, float Lim):AlarmBasic(PROPtr)
{
	PROPointer = PROPtr;
	NumberOfAlarmSettings++;
	IDNumber   = (ID_AL_IO_COM_ERROR << 16)+NumberOfAlarmSettings;
	Type       = ID_AL_IO_COM_ERROR;
	Limit      = Lim;
	MessageKey		= L_WORD516;	// ComFault
	TPCMessageKey	= L_WORD517;	// IOErr
	IsHWAlarm       = true;
}

void AlarmIOComFailure::Check(void)
{
	int FailCnt = ((IOUnit *)PROPointer)->FailCnt;
	int Status = AL_STAT_IN_DEADBAND;
	if ( FailCnt < Limit ) {
		Status = AL_STAT_IN_NORMAL;
	} else /*if ( FailCnt >= Limit ) */{
		Status = AL_STAT_IN_ALARM;
	}
	UpdateAlarm(Status);

}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmIOComFailure::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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
	if ( Status==E_NO_ERR){
			SetModifiedFlag();
	}
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AlarmIOComFailure::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = (float)Limit;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		case SVT_AL_VALUE:
			MyRetValue = (float)((IOUnit *)PROPointer)->FailCnt;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}


int AlarmIOComFailure::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmIOComFailure::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}

