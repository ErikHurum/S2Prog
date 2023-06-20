#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmLowVoltage::NumberOfAlarmSettings=0;

// This constructor is not to be used for this type of alarm
AlarmLowVoltage::AlarmLowVoltage(PRogramObjectBase *PROPtr, float Lim, int AlType):AlarmBasic(PROPtr)
{
	PROPointer = PROPtr;
	NumberOfAlarmSettings++;
	IDNumber =  (AlType << 16)+NumberOfAlarmSettings;
	Type     = AlType;
	Limit    = Lim;
	Deadband = 0.1;
	MessageKey      = L_WORD526;	// Low Voltage
	TPCMessageKey   = L_WORD527;	// LVolt
	IsHWAlarm       = true;
}

void AlarmLowVoltage::Check(void)
{
	float Val = ((AIVoltageSensor*)PROPointer)->Calculate();
	int Status = AL_STAT_IN_DEADBAND;
	if ( Val > Limit + Deadband ) {
		Status = AL_STAT_IN_NORMAL;
	} else if ( Val <= Limit ) {
		Status = AL_STAT_IN_ALARM;
	}
	UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int AlarmLowVoltage::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	if (Locked) {
		Status = E_NO_INPUT_PERMISSION;
	} else switch ( ValueId ) {
			case SVT_AL_LIMIT:
				{
					float Value = ConvertToSi(NewValue, ValUnitId=VOLTAGE_UNIT, Status,0.0 ,((AIVoltageSensor*)PROPointer)->Calculate(),0.0);
					if ( Status== E_NO_ERR ) {
						Limit = Value;
					}
				}
				break;
			default:
				Status = AlarmBasic::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
				break;
		}
	if ( Status==E_NO_ERR) {
		SetModifiedFlag();
	}
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AlarmLowVoltage::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = Limit;
			DecPnt     = 1;
			Unit       = VOLTAGE_UNIT;
			break;
		case SVT_AL_VALUE:
			MyRetValue = ((AIVoltageSensor*)PROPointer)->Calculate();
			DecPnt     = 1;
			Unit       = VOLTAGE_UNIT;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}

int AlarmLowVoltage::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmLowVoltage::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}


