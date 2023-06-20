#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmAC_Voltage::NumberOfAlarmSettings=0;

AlarmAC_Voltage::AlarmAC_Voltage(PRogramObjectBase *PROPtr):AlarmBasic(PROPtr)
{
	PROPointer = PROPtr;
	NumberOfAlarmSettings++;
	IDNumber =  (ID_AL_AC_VOLTAGE << 16)+NumberOfAlarmSettings;
	Type     = ID_AL_AC_VOLTAGE;
	Limit    = 1.0;
	Deadband = 0.0;
	MessageKey      = L_WORD898;	// Low voltage
	TPCMessageKey   = L_WORD890;	// AC
	IsHWAlarm       = true;
}

void AlarmAC_Voltage::Check(void)
{
	bool Val = bool(((AI_AC_Sensor*)PROPointer)->Calculate());
	int Status = AL_STAT_IN_DEADBAND;
	if ( Val ) {
		Status = AL_STAT_IN_NORMAL;
	} else  {
		Status = AL_STAT_IN_ALARM;
	}
	UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int AlarmAC_Voltage::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	if ( Locked ) {
		Status = E_NO_INPUT_PERMISSION;
	} else switch ( ValueId ) {
		case SVT_AL_LIMIT:
			{
				float Value = ConvertToSi(NewValue, ValUnitId=NO_UNIT, Status,0.0 ,((AIFuseSensor*)PROPointer)->Calculate(),0.0);
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

int  AlarmAC_Voltage::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_AL_LIMIT:
		MyRetValue = Limit;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_AL_VALUE:
		MyRetValue = ((AI_AC_Sensor*)PROPointer)->Calculate();
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	default:
		Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
		break;
	}
	return(Status);
}

int AlarmAC_Voltage::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmAC_Voltage::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}

