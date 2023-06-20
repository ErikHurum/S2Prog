#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif
//---------------------------------------------------------------------------

AIAtmPressSensor_mV::AIAtmPressSensor_mV(int SnsType):AIPressSensor_mV(SnsType)
{
	Location    = C_AI_LOC_SYSTEM;
}
//---------------------------------------------------------------------------

AIAtmPressSensor_mV::~AIAtmPressSensor_mV(void)
{
}
//---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////
float AIAtmPressSensor_mV::Calculate(void)
{
	if ( CanCalculate() ) {
		float Val = Gain*(FilteredValue-NORMAL_ATM)+NORMAL_ATM-Offset;
		CalcValue = Val;
		ResultOK  = true;
                if ( CalcValue > MAX_ATM || CalcValue < MIN_ATM ) {
                    //Failure = true;
                }else{
                    CalcValue = NORMAL_ATM;
                //    Failure = false;
                }
	}
	return(CalcValue);

}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIAtmPressSensor_mV::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
	case SVT_ATM_PRESSURE:
	case SVT_AI_CALC_VAL:
		{
			float OrgOffset = Offset;
			Status = AIPressSensor::PutValue(SVT_AI_CALC_VAL, Index,NewValue,Local,&ValUnitId);
			if ( Status == E_NO_ERR ) {
				AdjustOffsets(OrgOffset - Offset,Local);
			}
		}
		break;
	default:
		Status = AIPressSensor::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
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



