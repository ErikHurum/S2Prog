#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmLevelSwitchDead::NumberOfAlarmSettings=0;

AlarmLevelSwitchDead::AlarmLevelSwitchDead(PRogramObjectBase *PROPtr):AlarmBasic(PROPtr)
{
	PROPointer = PROPtr;
	//PROAtmReference *PROAtmPtr = (PROAtmReference*)PROPointer;
	NumberOfAlarmSettings++;
	IDNumber        = (ID_AL_LSWITCH_DEAD << 16)+NumberOfAlarmSettings;
	Type            = ID_AL_LSWITCH_DEAD;
	Limit           = LEVELSWITCH_HS_MA_DEAD;

	Deadband        = 0;
	MessageKey      = L_WORD933;	// Conv
	TPCMessageKey   = L_WORD934;	// Cnv
}

void AlarmLevelSwitchDead::Check(void)
{
	float Val = ((AILevelSwitchOptical_mA*)PROPointer)->SwitchVariation;
	int Status = AL_STAT_IN_DEADBAND;
	if ( Val >= Limit - Deadband ) {
		Status = AL_STAT_IN_NORMAL;
	} else if ( Val < Limit ) {
		Status = AL_STAT_IN_ALARM;
	}
	UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int AlarmLevelSwitchDead::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
	case SVT_AL_LIMIT:
		{
			float Value = ConvertToSi(NewValue, ValUnitId=CURRENT_UNIT, Status,0.000 ,0.025,0.0);
			if ( Status== E_NO_ERR ) {
				Limit = Value;
			}
		}
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

int  AlarmLevelSwitchDead::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_AL_LIMIT:
		MyRetValue = Limit;
		DecPnt     = 4;
		Unit       = CURRENT_UNIT;
		break;
	case SVT_AL_VALUE:
		MyRetValue = ((AILevelSwitchOptical_mA*)PROPointer)->SwitchVariation;
		DecPnt     = 4;
		Unit       = CURRENT_UNIT;
		break;
	default:
		Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
		break;
	}
	return(Status);
}


int AlarmLevelSwitchDead::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmLevelSwitchDead::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}

