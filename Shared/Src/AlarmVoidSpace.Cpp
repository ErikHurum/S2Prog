#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmVoidSpace::NumberOfAlarmSettings=0;

AlarmVoidSpace::AlarmVoidSpace(PRogramObjectBase *PROPtr,float Lim, bool Lock):AlarmBasic(PROPtr)
{
	PROPointer      = PROPtr;
	PROVoidSpacePtr =(PROVoidSpace*)PROPtr;

	Locked              = Lock;
	Limit               = Lim;
	NumberOfAlarmSettings++;
	IDNumber            =  (ID_AL_VOIDSPACE << 16)+NumberOfAlarmSettings;
	Type                = ID_AL_VOIDSPACE;
	Deadband            = 0.1;
	MessageKey          = L_WORD648; // Leakage
	TPCMessageKey       = L_WORD649; // Leak
}

void AlarmVoidSpace::Check(void)
{
	int Status = AL_STAT_IN_DEADBAND;
	if ( PROVoidSpacePtr->HasLevelSensors ) {
		float Level = PROVoidSpacePtr->Level;
		if ( Level < Limit - Deadband ) {
			Status = AL_STAT_IN_NORMAL;
		} else if ( Level >= Limit ) {
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

int AlarmVoidSpace::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			Limit = ConvertToSi(NewValue, ValUnitId=LENGTH_UNIT, Status,0.0 ,PROVoidSpacePtr->DBotUllRefPnt,Limit);
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

int  AlarmVoidSpace::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = Limit;
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			break;
		case SVT_AL_VALUE:
			MyRetValue = PROVoidSpacePtr->Level;
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}

int AlarmVoidSpace::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmVoidSpace::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}





