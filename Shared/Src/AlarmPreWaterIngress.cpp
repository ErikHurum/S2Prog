#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmPreWaterIngress::NumberOfAlarmSettings=0;

AlarmPreWaterIngress::AlarmPreWaterIngress(PRogramObjectBase *PROPtr):AlarmBasic(PROPtr)
{
	PROPointer = PROPtr;
	NumberOfAlarmSettings++;
	IDNumber            =  (ID_AL_PRE_WATERINGR << 16)+NumberOfAlarmSettings;
	Type                = ID_AL_PRE_WATERINGR;

//	Limit    = ;
//	Deadband = 0.1;
	MessageKey          = L_WORD535;	// PreWater
	TPCMessageKey       = L_WORD536;	// PWat
}

void AlarmPreWaterIngress::Check(void)
{
	bool AlValue = (char)((PROWaterIngress*)PROPointer)->PreAlarmValue;
	int Status = AL_STAT_IN_DEADBAND;
	// Override is the same as Alarm disable and is done from input
	if ( AlValue ) {
		Status = AL_STAT_IN_ALARM;
	} else if (TSNElapsedTicks(LastActiveTime) > PROSystemData::AlarmOffDelay ) {
		Status = AL_STAT_IN_NORMAL;
	}
	UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int AlarmPreWaterIngress::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
	//		break;
	//}
	if ( Status==E_NO_ERR) {
		SetModifiedFlag();
	}
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AlarmPreWaterIngress::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = Limit;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		case SVT_AL_VALUE:
			MyRetValue =((PROWaterIngress*)PROPointer)->PreAlarmValue;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}

int AlarmPreWaterIngress::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmPreWaterIngress::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}


