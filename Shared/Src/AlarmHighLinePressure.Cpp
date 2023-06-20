#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmHighLinePressure::NumberOfAlarmSettings=0;

AlarmHighLinePressure::AlarmHighLinePressure(void):AlarmBasic(NULL){
    NumberOfAlarmSettings++; // Should not do this, but must maintain backward compatibility
	Deadband            = 10.0 / MH2O_TO_MBAR;
}
AlarmHighLinePressure::AlarmHighLinePressure(PRogramObjectBase *PROPtr):AlarmBasic(PROPtr)
{
	NumberOfAlarmSettings++;
	PROPointer          = PROPtr;
	PROLPressPtr        = (PROLinePressure*)PROPtr;
	IDNumber            = (ID_AL_HIGH_LINE_PRESS << 16)+NumberOfAlarmSettings;
	Type                = ID_AL_HIGH_LINE_PRESS;
	Locked              = PROLPressPtr->HighLinePressLocked;
	Limit               = PROLPressPtr->HighPressLimit;
	Deadband            = 10.0 / MH2O_TO_MBAR;
	MessageKey          = L_WORD504; // HighLinePress
	TPCMessageKey       = L_WORD505;  // HLPr
}

void AlarmHighLinePressure::Check(void)
{
	int Status = AL_STAT_IN_DEADBAND;
	if ( PROLPressPtr->HasPressure ) {
		float Val = PROLPressPtr->Pressure;
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

int AlarmHighLinePressure::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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
							int NewStatus = FindConfigKey(NewValue);
							switch ( NewStatus ) {
								case C_ENABLE:
									Enable = true;
									break;
								case C_DISABLE:
									Enable = false;
									break;
								default:
									{
										float Value = ConvertToSi(NewValue, ValUnitId=PRESSURE_UNIT3, Status,LIMIT_LOW_LINEPRESS ,PROLPressPtr->GetHiHiPressLimit(),0.0);
										if ( Status== E_NO_ERR ) {
											Limit = Value;
										}
									}
									break;
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

int  AlarmHighLinePressure::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = Limit;
			DecPnt     = 1;
			Unit       = PRESSURE_UNIT3;
			if ( !Enable ) {
				Status     = GETVAL_DISABLED;
			}
			break;
		case SVT_AL_VALUE:
			MyRetValue = PROLPressPtr->Pressure;
			DecPnt     = 1;
			Unit       = PRESSURE_UNIT3;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}

int AlarmHighLinePressure::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmHighLinePressure::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}


