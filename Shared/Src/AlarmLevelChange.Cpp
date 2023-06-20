#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmLevelChange::NumberOfAlarmSettings=0;

AlarmLevelChange::AlarmLevelChange(PRogramObjectBase *PROPtr,float Lim, bool Lock):AlarmBasic(PROPtr)
{
	PROPointer          = PROPtr;
	PROTankPtr          =(PROTank*)PROPtr;
	Enable              = false;
	Locked              = Lock;
	Limit               = Lim;
	NumberOfAlarmSettings++;
	IDNumber            = (ID_AL_LEVEL_CHANGE << 16)+NumberOfAlarmSettings;
	Type                = ID_AL_LEVEL_CHANGE;
	Deadband            = 0.1;
	MessageKey          = L_WORD866; // Level diff.
	TPCMessageKey       = L_WORD867; // LDif
}

void AlarmLevelChange::Check(void)
{
#ifndef WIN32
	if ( Enable && RunningTime > 2*ALARM_SYSTEM_DELAY ){
		int Status = AL_STAT_IN_DEADBAND;
		float VolPrnctDiff = fabs(PROTankPtr->FilteredVolPercent - PROTankPtr->StartVolPercent);
		if ( VolPrnctDiff < Limit - Deadband ) {
			Status = AL_STAT_IN_NORMAL;
		} else if ( VolPrnctDiff >= Limit ) {
			Status = AL_STAT_IN_ALARM;
			switch ( State ) {
			case AlActive       :
			case AlIdle         :
				break;
			case AlAknowledged  :
				// Set new setpoint if acknowledged alarm
				PROTankPtr->StartVolPercent = PROTankPtr->FilteredVolPercent;
				break;
			}

		}
		UpdateAlarm(Status);
	} else {
		PROTankPtr->StartVolPercent = PROTankPtr->FilteredVolPercent;
	}
#endif
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmLevelChange::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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
			PROTankPtr->StartVolPercent = PROTankPtr->FilteredVolPercent;
			break;
		case C_OFF:
		case C_CLOSE:
		case C_DISABLE:
            SetEnable(EnableFalse);
			PROTankPtr->SetState(tUndefined);
			break;
		default:
			switch ( ValueId ) {
			case SVT_LEV_CHANGE_LIM:
			case SVT_AL_LIMIT:
				Limit           = ConvertToSi(NewValue, ValUnitId=PERCENT_UNIT, Status,0.0 ,2*LIMIT_LEVEL_CHANGE,Limit);
				PROTankPtr->StartVolPercent = PROTankPtr->FilteredVolPercent;
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

int  AlarmLevelChange::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
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
		MyRetValue = PROTankPtr->FilteredVolPercent - PROTankPtr->StartVolPercent;
		DecPnt     = 1;
		Unit       = PERCENT_UNIT;
		break;
	default:
		Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
		break;
	}
	return(Status);
}

int AlarmLevelChange::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmLevelChange::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}

void AlarmLevelChange::SetEnable(EnableCmd Cmd)
{
	PROTankPtr->StartVolPercent = PROTankPtr->FilteredVolPercent;
	AlarmBasic::SetEnable(Cmd);
}

