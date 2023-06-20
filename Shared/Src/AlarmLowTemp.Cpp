#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmLowTemp::NumberOfAlarmSettings=0;

AlarmLowTemp::AlarmLowTemp(PRogramObjectBase *PROPtr):AlarmBasic(PROPtr)
{
	NumberOfAlarmSettings++;
	PROPointer          = PROPtr;
	PROTmpPtr           = (PROTemperature*)PROPtr;
	IDNumber            =  (ID_AL_LOW_TEMP << 16)+NumberOfAlarmSettings;
	Type                = ID_AL_LOW_TEMP;
	Locked              = PROProjectInfo::LowTempLocked;
	Limit               = PROProjectInfo::LowTempLimit;
	Deadband            = 0.1;
	MessageKey          = L_WORD524;	// LowTemp
	TPCMessageKey       = L_WORD525;	//	LTmp
	PreviousEnable      = Enable;
}

void AlarmLowTemp::Check(void)
{
	float Val = PROTmpPtr->Temperature;
	bool  HasTemp = PROTmpPtr->HasTemp;
	int Status = AL_STAT_IN_DEADBAND;
	if ( HasTemp ) {
		if ( Val > Limit + Deadband ) {
			Status = AL_STAT_IN_NORMAL;
		} else if ( Val <= Limit ) {
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

int AlarmLowTemp::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	if ( Locked ) {
		Status = E_NO_INPUT_PERMISSION;
	} else {
        float OrgLimit = Limit;
		int Key = FindConfigKey(NewValue);
		switch ( Key ) {
		case C_ON:
		case C_OPEN:
		case C_ENABLE:
            SetEnable(EnableTrue);
			break;
		case C_OFF:
		case C_CLOSE:
		case C_DISABLE:
            SetEnable(EnableFalse);
			break;
		default:
			switch ( ValueId ) {
			case SVT_AL_LIMIT:
				{
					float Value = ConvertToSi(NewValue, ValUnitId=TEMP_UNIT, Status,MIN_TEMP ,MAX_TEMP,0.0);
					if ( Status== E_NO_ERR ) {
						Limit = Value;
					}
				}
				break;
			default:
				Status = AlarmBasic::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
				break;
			}
			break; // switch ( ValueId )
		}//switch ( Key )
		if ( Status==E_NO_ERR ) {
			SetModifiedFlag();
			if ( Limit != OrgLimit ) {
				LogEvent("New limit");
			}
		}
	}// if ( Locked ) else
	if ( UnitId ) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AlarmLowTemp::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_AL_LIMIT:
		MyRetValue = Limit;
		DecPnt     = 1;
		Unit       = TEMP_UNIT;
		if ( !Enable ) {
			Status     = GETVAL_DISABLED;
		}
		break;
	case SVT_AL_VALUE:
		MyRetValue =((PROTemperature*)PROPointer)->Temperature;
		DecPnt     = 1;
		Unit       = TEMP_UNIT;
		break;
	default:
		Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
		break;
	}
	return(Status);
}

int AlarmLowTemp::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmLowTemp::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}

