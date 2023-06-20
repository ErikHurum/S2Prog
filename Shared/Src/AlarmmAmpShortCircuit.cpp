#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AlarmmAmpShortCircuit::~AlarmmAmpShortCircuit(void)
{
}

unsigned AlarmmAmpShortCircuit::NumberOfAlarmSettings=0;

AlarmmAmpShortCircuit::AlarmmAmpShortCircuit(PRogramObjectBase *PROPtr) :AlarmBasic(PROPtr)
{
	NumberOfAlarmSettings++;
    PROPointer = PROPtr;
	IDNumber = (ID_AL_SNS_SHORT_CIRCUIT << 16)+NumberOfAlarmSettings;
	Type     = ID_AL_SNS_SHORT_CIRCUIT;
	Limit    = LIMIT_MA_SHORT_CIRCUIT;
	Deadband = 0.0001;
	MessageKey		= L_WORD543;	// ShortCircuit
	TPCMessageKey	= L_WORD544;	// scirc
	IsHWAlarm       = true;
}

void AlarmmAmpShortCircuit::Check(void)
{
	float Val = ((AnalogInput*)PROPointer)->FilteredValue;
 	int Status = AL_STAT_IN_DEADBAND;
	if ( Val < Limit - Deadband ) {
		Status = AL_STAT_IN_NORMAL;
		((AnalogInput*)PROPointer)->Failure &= ~HART_STATUS_SHORT_CIRCUIT_BIT;
	} else if ( Val >= Limit ) {
		Status = AL_STAT_IN_ALARM;
        ((AnalogInput*)PROPointer)->Failure |= HART_STATUS_SHORT_CIRCUIT_BIT;
	}
	UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmmAmpShortCircuit::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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

int  AlarmmAmpShortCircuit::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
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


int AlarmmAmpShortCircuit::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
      Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmmAmpShortCircuit::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
 //   default:
      Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
 //     break;
	//}
	return (Status);
}

