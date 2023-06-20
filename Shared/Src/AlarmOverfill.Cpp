#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmOverfill::NumberOfAlarmSettings=0;
AlarmOverfill::AlarmOverfill(PRogramObjectBase *PROPtr,float Lim, bool Lock) :AlarmBasic(PROPtr)
{
	PROPointer = PROPtr;
	PROTankPtr = (PROTank*)PROPtr;
	NumberOfAlarmSettings++;
	IDNumber            =  (ID_AL_OVERFILL << 16)+NumberOfAlarmSettings;
	Type                = ID_AL_OVERFILL;
	Limit               = Lim;
	Locked              = Lock;
	Deadband            = 0.1;
	MessageKey          = L_WORD109;	// Overfill
	TPCMessageKey       = L_WORD534;	// OFill
}

void AlarmOverfill::Check(void)
{
	int Status = AL_STAT_IN_DEADBAND;
	if ( PROTankPtr->HasLevelSensors ) {
		float Val = PROTankPtr->VolumePercent;
		if ( Val < Limit - Deadband ) {
			if ( TSNElapsedTicks(LastActiveTime) > PROSystemData::AlarmOffDelay ) {
				Status = AL_STAT_IN_NORMAL;
			}
		} else if ( Val >= Limit ) {
			Status = AL_STAT_IN_ALARM;
		}
	} else if ( TSNElapsedTicks(LastActiveTime) > PROSystemData::AlarmOffDelay ) {
		Status = AL_STAT_IN_NORMAL;
	}
	UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmOverfill::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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
						{
							float Value = ConvertToSi(NewValue, ValUnitId=PERCENT_UNIT, Status,0.0 ,100.0,0.0);
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
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AlarmOverfill::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = Limit;
			DecPnt     = 1;
			Unit       = PERCENT_UNIT;
			if ( !Enable ) {
				Status     = GETVAL_DISABLED;
			}
			break;
		case SVT_AL_VALUE:
			MyRetValue = PROTankPtr->VolumePercent;
			DecPnt     = 1;
			Unit       = PERCENT_UNIT;
			if ( !Enable ) {
				Status     = GETVAL_DISABLED;
			}
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}


int AlarmOverfill::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmOverfill::PutFloatValue( int ValueId, float NewValue)
{
    int Status = E_NO_ERR;
    switch ( ValueId ) {
    case SVT_HIHI_VOLPCNT_LIM :
	case SVT_AL_LIMIT:
		Limit = NewValue;
        break;
    default:
        Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);
}

