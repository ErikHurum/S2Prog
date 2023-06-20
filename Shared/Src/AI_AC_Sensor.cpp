#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif


//---------------------------------------------------------------------------

AI_AC_Sensor::AI_AC_Sensor(void)
{
    Type                        = C_AI_FUSE;
    BasicSensorType             = AI_SENSOR_AC_AVALABLE;
    BasicSensorTypeWord         = L_WORD897;    //AC
    Location                    = C_AI_LOC_AC_OK;
    AlarmAC_Voltage *FuseAlPtr  = new AlarmAC_Voltage( this);
    AlarmSet.insert(FuseAlPtr);
    HasVoltage                  = true;
}
//---------------------------------------------------------------------------

AI_AC_Sensor::~AI_AC_Sensor(void)
{

}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AI_AC_Sensor::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
    case SVT_AI_CALC_VAL :
    default:
        ValUnitId = NO_UNIT;
        Status = AnalogInput::PutValue(ValueId, Index,NewValue,Local);
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

int  AI_AC_Sensor::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
        Unit       = NO_UNIT;
        DecPnt     = 0;
        MyRetValue = Offset;
        break;
    case SVT_AI_CALC_VAL :
        Unit       = NO_UNIT;
        DecPnt     = 0;
        MyRetValue = Calculate();
        break;
    default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return(Status);
}

int AI_AC_Sensor::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_UNIT:
        MyString = GetUnitName(NO_UNIT);
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId,Index, MyString);
        break;
    }
    return(Status);
}

int AI_AC_Sensor::PutFloatValue( int ValueId, float NewValue)
{
    return(AnalogInput::PutFloatValue(ValueId, NewValue));
}


void AI_AC_Sensor::NewValue(float NewValue)
{
#ifndef ANCONF
    FilteredValue = NewValue;
    CalcValue     = NewValue;
    ResultOK      = true;
    HWFailure     = false;

    if ( CurrentDeviceId == DEVICE_TCU ) {
        CheckAlarms(AlarmSet);
        SendData();
    }
#endif
}

float AI_AC_Sensor::Calculate(void)
{
    ResultOK  = true;
    CalcValue = FilteredValue;
    return(CalcValue);
}

