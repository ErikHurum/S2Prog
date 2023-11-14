#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif
#include "TSNAsyncsender.h"

//---------------------------------------------------------------------------

AIDiffPressSensor_mA::AIDiffPressSensor_mA(int SnsType):AIPressSensor_mA(SnsType,true)
{
}
//---------------------------------------------------------------------------

AIDiffPressSensor_mA::~AIDiffPressSensor_mA(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIDiffPressSensor_mA::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_CALC_VAL:
        Status = AIPressSensor::PutValue(SVT_AI_CALC_VAL, Index,NewValue,Local,&ValUnitId);
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


//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////


float AIDiffPressSensor_mA::Calculate(void)
{
    if ( CanCalculate() ) {
        CalcValue = Gain*Get_Press(FilteredValue,15.0)-Offset;
        ResultOK  = true;
        /*
        if ( CalcValue > MAX_ATM || CalcValue < MIN_ATM ) {
            Failure = true;
        }else{
            Failure = false;
        }
        */
    }
    return(CalcValue);

}


void AIDiffPressSensor_mA::AdjustOffset(float OffsetAdjust)
{

}
