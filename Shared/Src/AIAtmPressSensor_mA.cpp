#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif
#include "TSNAsyncsender.h"

//---------------------------------------------------------------------------

AIAtmPressSensor_mA::AIAtmPressSensor_mA(int SnsType, bool TCUFlag):AIPressSensor_mA(SnsType,true)
//:m_iSizeAlloc(10)
{
    IsOnTCU         = TCUFlag;
    CalcValue       = NORMAL_ATM;
    FilteredValue = 0.008; // About Normal atmospheric pressure
    Location        = C_AI_LOC_SYSTEM;
}
//---------------------------------------------------------------------------

AIAtmPressSensor_mA::~AIAtmPressSensor_mA(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIAtmPressSensor_mA::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status    = E_NO_ERR, ValUnitId = NO_UNIT;

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


//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////

void AIAtmPressSensor_mA::FilterValue(float NewCalcVal,float FilterDegree)
{
    CalcValue += (NewCalcVal - CalcValue)/(FilterDegree+1.0);
}

float AIAtmPressSensor_mA::Calculate(void)
{
    if ( CanCalculate() ) {
        float tmpCalcValue = Gain*(Get_Press(FilteredValue,15.0)-NORMAL_ATM)+NORMAL_ATM-Offset;
        if ( IsOnTCU ) {
            FilterValue(tmpCalcValue,INT_ATM_REF_FILTER);
        } else {
            CalcValue = tmpCalcValue;
        }
        ResultOK  = true;

        if ( CalcValue > MAX_ATM || CalcValue < MIN_ATM ) {
            //Failure = true;
            CalcValue = NORMAL_ATM;
        }else{
        //    Failure = false;
        }

    }
    return(CalcValue);

}

