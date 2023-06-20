#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmModbusInCoil::NumberOfAlarmSettings=0;

AlarmModbusInCoil::AlarmModbusInCoil(PRogramObjectBase *PROPtr, AnsiString LocName, AnsiString Descr):AlarmBasic(PROPtr)
{
	PROPointer  = PROPtr;
	NumberOfAlarmSettings++;
	IDNumber      = (ID_AL_MODBUS_INPUT_STATUS << 16)+NumberOfAlarmSettings;
	Type          = ID_AL_MODBUS_INPUT_STATUS;
	Limit         = 0.0;
	Deadband      = ((ModbusCoilIn*)PROPointer)->GetAlarmDelay();
	Name          = LocName;
	Description   = Descr;
	MessageKey    = L_WORD237;	// Blank
	TPCMessageKey = L_WORD237;	// Blank

}

AnsiString AlarmModbusInCoil::Get_Message(void)
{
	return(Description);
}


void AlarmModbusInCoil::Check(void)
{
	bool IsActive = ((ModbusObject*)PROPointer)->IsActive;

	int Status = AL_STAT_IN_DEADBAND;
	if ( IsActive ) {
		Status = AL_STAT_IN_ALARM;
	} else if (TSNElapsedTicks(LastActiveTime) > Deadband ) {
		Status = AL_STAT_IN_NORMAL;
	}
	UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int AlarmModbusInCoil::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			Status = E_NOT_ADJUSTABLE;
			break;
		default:
			Status = AlarmBasic::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
			break;
	}
	if ( Status==E_NO_ERR ) {
		SetModifiedFlag();
	}
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AlarmModbusInCoil::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_AL_LIMIT:
			MyRetValue = 1.0;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		case SVT_AL_VALUE:
			MyRetValue = (float)((ModbusCoilIn*)PROPointer)->IsActive;
			DecPnt     = 0;
			Unit       = NO_UNIT;
			break;
		default:
			Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
			break;
	}
	return(Status);
}

int AlarmModbusInCoil::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	//switch ( ValueId ) {
	//	default:
	Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
	//		break;
	//}
	return(Status);
}

int AlarmModbusInCoil::PutFloatValue( int ValueId, float NewValue)
{
	int Status= E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
	//     break;
	//}
	return(Status);
}

