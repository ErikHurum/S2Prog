#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmLevelSwitchTest::NumberOfAlarmSettings=0;

AlarmLevelSwitchTest::AlarmLevelSwitchTest(PRogramObjectBase *PROPtr, float Lim, float Win):AlarmBasic(PROPtr)
{
	PROPointer          = PROPtr;
	NumberOfAlarmSettings++;
	IDNumber            = (ID_AL_LSWITCH_TEST << 16)+NumberOfAlarmSettings;
	Type                = ID_AL_LSWITCH_TEST;
	Limit               = Lim;
	Deadband            = Win;
	MessageKey          = L_WORD929;	// Test
	TPCMessageKey       = L_WORD930;	// Tst
}

void AlarmLevelSwitchTest::Check(void)
{
	int Status = AL_STAT_IN_DEADBAND;
	switch ( int(((AILevelSwitch_mA*)PROPointer)->CalcValue) ) {
	case LEVELSWITCH_TEST:
		Status = AL_STAT_IN_ALARM;
		break;
	default:
		Status = AL_STAT_IN_NORMAL;
		break;
	}
	UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int AlarmLevelSwitchTest::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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

int  AlarmLevelSwitchTest::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
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


int AlarmLevelSwitchTest::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
      Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmLevelSwitchTest::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
 //   default:
      Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
 //     break;
	//}
	return (Status);
}

