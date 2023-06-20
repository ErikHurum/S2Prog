#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------


AlarmmAmpOpenLoop::~AlarmmAmpOpenLoop(void)
{
}

unsigned AlarmmAmpOpenLoop::NumberOfAlarmSettings=0;

AlarmmAmpOpenLoop::AlarmmAmpOpenLoop(PRogramObjectBase *PROPtr, int AlDelay):AlarmBasic(PROPtr)
{
	NumberOfAlarmSettings++;
    PROPointer 		= PROPtr;
	IDNumber 		=  (ID_AL_SNS_OPEN_LOOP << 16)+NumberOfAlarmSettings;
	Type     		= ID_AL_SNS_OPEN_LOOP;
	Limit    		= LIMIT_MA_OPEN_LOOP;
	Deadband 		= 0.0001;
	MessageKey		= L_WORD531;	// OpenLoop
	TPCMessageKey	= L_WORD531;	// oloop
	IsHWAlarm       = true;
	AlarmDelay		= AlDelay;
}

void AlarmmAmpOpenLoop::Check(void)
{
	float Val = ((AnalogInput*)PROPointer)->FilteredValue;
	int Status = AL_STAT_IN_DEADBAND;
	if ( Val > Limit + Deadband ) {
		Status = AL_STAT_IN_NORMAL;
		((AnalogInput*)PROPointer)->Failure &= ~HART_STATUS_OPEN_LOOP_BIT;
		LastInactiveTime = clock();
	} else if ( Val <= Limit ) {
		if ( TSNElapsedTicks(LastInactiveTime) < AlarmDelay ) {
			Status = AL_STAT_IN_NORMAL;
			((AnalogInput*)PROPointer)->Failure &= ~HART_STATUS_OPEN_LOOP_BIT;
		}else{
			Status = AL_STAT_IN_ALARM;
            ((AnalogInput*)PROPointer)->Failure |= HART_STATUS_OPEN_LOOP_BIT;
		}
	}
	UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmmAmpOpenLoop::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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
	if ( Status==E_NO_ERR){
			SetModifiedFlag();
	}
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AlarmmAmpOpenLoop::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = Limit;
			DecPnt     = 3;
			Unit       = CURRENT_UNIT;
			break;
		case SVT_AL_VALUE:
			MyRetValue = ((AnalogInput*)PROPointer)->FilteredValue;
			DecPnt     = 3;
			Unit       = CURRENT_UNIT;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return (Status);
}


int AlarmmAmpOpenLoop::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
      Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmmAmpOpenLoop::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
 //   default:
      Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
 //     break;
	//}
	return (Status);
}


