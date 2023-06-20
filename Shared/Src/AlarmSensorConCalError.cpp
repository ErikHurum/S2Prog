#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AlarmSensorConCalError::~AlarmSensorConCalError(void)
{
}

unsigned AlarmSensorConCalError::NumberOfAlarms=0;

AlarmSensorConCalError::AlarmSensorConCalError(PRogramObjectBase *PROPtr,ConfigPacket *ADConfDataPtr):AlarmBasic(PROPtr)
{
	NumberOfAlarms++;
	PROPointer      = PROPtr;
	ADConfigDataPtr = ADConfDataPtr;
	IDNumber        = (ID_AL_SNS_CONCAL_ERROR << 16)+NumberOfAlarms;
	Type            = ID_AL_SNS_CONCAL_ERROR;
	Limit           = 1;
	Deadband        = 0;
	MessageKey      = L_WORD539;		// Cnv&Cal Error
	TPCMessageKey   = L_WORD540;		// HWErr
	AlarmDelay      = 30000;
	IsHWAlarm       = true;
}

void AlarmSensorConCalError::Check(void)
{

	int Status = AL_STAT_IN_DEADBAND;
	if ( ADConfigDataPtr->CalError || ADConfigDataPtr->ConvError ) {
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

int AlarmSensorConCalError::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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

int  AlarmSensorConCalError::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = Limit;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		case SVT_AL_VALUE:
			MyRetValue = (float)(ADConfigDataPtr->CalError | ADConfigDataPtr->ConvError);
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}


int AlarmSensorConCalError::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmSensorConCalError::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}


