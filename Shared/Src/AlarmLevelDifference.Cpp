#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmLevelDifference::NumberOfAlarmSettings=0;

AlarmLevelDifference::AlarmLevelDifference(PRogramObjectBase *PROPtr,float Lim, bool Lock):AlarmBasic(PROPtr)
{
	PROPointer = PROPtr;
	PROTankPtr =(PROTank*)PROPtr;

	Locked              = Lock;
	Limit               = Lim;
	NumberOfAlarmSettings++;
	IDNumber            = (ID_AL_SNS_LEVEL_DIFFERENCE << 16)+NumberOfAlarmSettings;
	Type                = ID_AL_SNS_LEVEL_DIFFERENCE;
	Deadband            = 0.1;
	MessageKey          = L_WORD747; // Level diff.
	TPCMessageKey       = L_WORD748; // LDif
}

void AlarmLevelDifference::Check(void)
{
	int Status = AL_STAT_IN_DEADBAND;

	if ( PROTankPtr->HasLevelSensors ) {
		float Val = PROTankPtr->LevelDifference;
		if ( Val < Limit - Deadband ) {
			Status = AL_STAT_IN_NORMAL;
		} else if ( Val >= Limit ) {
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

int AlarmLevelDifference::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	if ( Locked ) {
		Status = E_NO_INPUT_PERMISSION;
	} else {
		int Key = FindConfigKey(NewValue);
        float OrgLimit = Limit;
		switch ( Key ) {
			case C_ON:
			case C_OPEN:
			case C_ENABLE:
                SetEnable(EnableTrue);
				PROTankPtr->SetState(tUndefined);
			 break;
			case C_OFF:
			case C_CLOSE:
			case C_DISABLE:
                SetEnable(EnableFalse);
				PROTankPtr->SetState(tUndefined);
			 break;
			default:
				switch ( ValueId ) {
					case SVT_AL_LIMIT:
						Limit = ConvertToSi(NewValue, ValUnitId=LENGTH_UNIT, Status,0.0 ,1.0,Limit);
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
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AlarmLevelDifference::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = Limit;
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			if ( !Enable ) {
				Status     = GETVAL_DISABLED;
			}
			break;
		case SVT_AL_VALUE:
			MyRetValue = PROTankPtr->LevelDifference;
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}

int AlarmLevelDifference::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmLevelDifference::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}


