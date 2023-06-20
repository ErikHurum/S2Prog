#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmWaterDetect::NumberOfAlarmSettings=0;

AlarmWaterDetect::AlarmWaterDetect(PRogramObjectBase *PROPtr):AlarmBasic(PROPtr)
{
	PROPointer = PROPtr;
	NumberOfAlarmSettings++;
	IDNumber            =  (ID_AL_WATER_DETECT << 16)+NumberOfAlarmSettings;
	Type                = ID_AL_WATER_DETECT;
	MessageKey		    = L_WORD896;	// Oil
	TPCMessageKey	    = L_WORD896;	// Oil
}

void AlarmWaterDetect::Check(void)
{
	char AlValue = ((PROTank*)PROPointer)->HasWater;
	int Status = AL_STAT_IN_DEADBAND;
	// Override is the same as Alarm disable and is done from input
	
	if ( AlValue == WSENSOR_CARGO ) {
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

int AlarmWaterDetect::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
	//		break;
	//}
	if ( Status==E_NO_ERR ) {
		SetModifiedFlag();
	}
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AlarmWaterDetect::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = Limit;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		case SVT_AL_VALUE:
			MyRetValue =((PROTank*)PROPointer)->HasWater;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}

int AlarmWaterDetect::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmWaterDetect::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}


