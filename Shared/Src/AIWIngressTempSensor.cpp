#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIWIngressTempSensor::AIWIngressTempSensor(PROIOComponent *IOCompPtr)
{
	switch ( IOCompPtr->Type ) {
	default:
	case C_AI_WATERINGRESS:
		Type = C_AI_WATERINGR_TEMP;
		break;
	case C_AI_WATERINGR_MAIN:
		Type = C_AI_WATERINGR_TEMP_M;
        Distance = 3.0;
		break;
	case C_AI_WATERINGR_PRE:
		Type = C_AI_WATERINGR_TEMP_P;
        Distance = 1.0;
		break;
	}
    AdjustedDistance = Distance;
	Location =((AnalogInput*)IOCompPtr)->Location;
//	Name = IOCompPtr->Name;
	SerialNumber = IOCompPtr->SerialNumber;
	SortNo          = IOCompPtr->SortNo;
	TagName         = IOCompPtr->TagName;

	TCUAddress      = IOCompPtr->TCUAddress;
	TCUPortNo       = IOCompPtr->TCUPortNo;
	IOType          = IOCompPtr->IOType;
	IOAddress       = IOCompPtr->IOAddress;
	IOChannel       = IOCompPtr->IOChannel;
	ADCardChannel   = IOCompPtr->ADCardChannel+1;

}
//---------------------------------------------------------------------------

AIWIngressTempSensor::~AIWIngressTempSensor(void)
{
}
//---------------------------------------------------------------------------




///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIWIngressTempSensor::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
	case SVT_AI_OFFSET   :
	case SVT_AI_CALC_VAL :
	default:
		Status = AITempSensor::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
		break;
	}
	if ( Status==E_NO_ERR ) {
		SetModifiedFlag();
	}
	if ( UnitId ) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int  AIWIngressTempSensor::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_AI_OFFSET   :
	case SVT_AI_CALC_VAL :
	default:
		Status = AITempSensor::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
		break;
	}
	return(Status);
}

int AIWIngressTempSensor::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	return(AITempSensor::GetStringValue(ValueId,Index, MyString));
}

int AIWIngressTempSensor::PutFloatValue( int ValueId, float NewValue)
{
	return(AITempSensor::PutFloatValue(ValueId, NewValue));
}



