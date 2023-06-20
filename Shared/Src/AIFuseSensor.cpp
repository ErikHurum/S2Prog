#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif


//---------------------------------------------------------------------------

AIFuseSensor::AIFuseSensor(void)
{
    Type                    = C_AI_FUSE;
    BasicSensorType         = AI_SENSOR_FUSE;
    BasicSensorTypeWord     = L_WORD551;    //Inclinometer
    Location                = C_AI_LOC_FUSES;
    AlarmFuse   *FuseAlPtr  = new AlarmFuse( this);
    HasVoltage              = true;
    AlarmSet.insert(FuseAlPtr);
}
//---------------------------------------------------------------------------

AIFuseSensor::~AIFuseSensor(void)
{

}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIFuseSensor::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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

int  AIFuseSensor::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
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

int AIFuseSensor::GetStringValue(int ValueId, int Index, AnsiString &MyString)
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

int AIFuseSensor::PutFloatValue( int ValueId, float NewValue)
{
    return(AnalogInput::PutFloatValue(ValueId, NewValue));
}


void AIFuseSensor::NewValue(float NewValue)
{
#ifndef ANCONF
    FilteredValue = NewValue;
    CalcValue     = NewValue;
    HWFailure     = false;
    ResultOK      = true;

    if ( CurrentDeviceId == DEVICE_TCU ) {
        CheckAlarms(AlarmSet);
        SendData();
    }
#endif
}

float AIFuseSensor::Calculate(void)
{
    ResultOK  = true;
    CalcValue = FilteredValue;
    return(CalcValue);
}

