#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AlarmSensorConvError::~AlarmSensorConvError(void)
{
}

unsigned AlarmSensorConvError::NumberOfAlarmSettings=0;

AlarmSensorConvError::AlarmSensorConvError(PRogramObjectBase *PROPtr,ConfigPacket *ADConfDataPtr):AlarmBasic(PROPtr)
{
	NumberOfAlarmSettings++;
	PROPointer      = PROPtr;
	ADConfigDataPtr = ADConfDataPtr;
	IDNumber        = (ID_AL_SNS_CONV_ERROR << 16)+NumberOfAlarmSettings;
	Type            = ID_AL_SNS_CONV_ERROR;
	Limit           = 1;
	Deadband        = 0;
	MessageKey      = L_WORD541;		// Conv Error
	TPCMessageKey   = L_WORD540;		// HWErr
	IsHWAlarm       = true;
	AlarmDelay      = 30000;
}

void AlarmSensorConvError::Check(void)
{

	int Status = AL_STAT_IN_DEADBAND;
	if ( ADConfigDataPtr->ConvError ) {
		if ( TSNElapsedTicks(LastInactiveTime) < AlarmDelay ) {
			Status = AL_STAT_IN_NORMAL;
		}else{
			Status = AL_STAT_IN_ALARM;
		}
	} else {
		LastInactiveTime = clock();
		Status = AL_STAT_IN_NORMAL;
	}
	UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmSensorConvError::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			Status = E_NO_INPUT_PERMISSION;
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

int  AlarmSensorConvError::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = Limit;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		case SVT_AL_VALUE:
			MyRetValue = (float)ADConfigDataPtr->ConvError;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}


int AlarmSensorConvError::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmSensorConvError::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}


