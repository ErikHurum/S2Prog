#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif


//---------------------------------------------------------------------------

AIVoltageSensor::AIVoltageSensor(int Loc,int BasicSnsType,float MinVolt, float MaxVolt)
{
    Type                    = C_AI_VOLTAGE;
    BasicSensorType         = AI_SENSOR_VOLT;
    BasicSensorTypeWord     = BasicSnsType; //L_WORD653;//24V
    MaxVoltage              = MaxVolt;
    MinVoltage              = MinVolt;
    Location                = Loc;
    AlarmHighVoltage *HiVPtr= NULL;
    AlarmLowVoltage  *LoVPtr= NULL;

    switch ( Location ) {
    default             :
    case C_AI_LOC_POWER1:
        {
            switch ( TSNConfigInfo::ConfigInfoPtr->ConfigCompatibilityNo ) {
            case 0:
                HiVPtr  = new AlarmHighVoltage(this, MaxVoltage, ID_AL_HI_VOLTAGE   );
                LoVPtr  = new AlarmLowVoltage( this, MinVoltage, ID_AL_LOW_VOLTAGE  );
                break;
            case 1:
                HiVPtr  = new AlarmHighVoltage(this, MaxVoltage, ID_AL_HI_VOLTAGE_1 );
                LoVPtr  = new AlarmLowVoltage( this, MinVoltage, ID_AL_LOW_VOLTAGE_1);
                break;
            }
        }
        break;
    case C_AI_LOC_POWER2:
        {
            switch ( TSNConfigInfo::ConfigInfoPtr->ConfigCompatibilityNo ) {
            case 0:
                HiVPtr  = new AlarmHighVoltage(this, MaxVoltage, ID_AL_HI_VOLTAGE   );
                LoVPtr  = new AlarmLowVoltage( this, MinVoltage, ID_AL_LOW_VOLTAGE  );
                break;                                                                
            case 1:                                                                   
                HiVPtr  = new AlarmHighVoltage(this, MaxVoltage, ID_AL_HI_VOLTAGE_2 );
                LoVPtr  = new AlarmLowVoltage( this, MinVoltage, ID_AL_LOW_VOLTAGE_2);
                break;
            }
        }
        break;
    }
    AlarmSet.insert(HiVPtr);
    AlarmSet.insert(LoVPtr);
}
//---------------------------------------------------------------------------

AIVoltageSensor::~AIVoltageSensor(void)
{

}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIVoltageSensor::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
    case SVT_AI_CALC_VAL :
    default:
        ValUnitId = VOLTAGE_UNIT;
        Status = AnalogInput::PutValue(ValueId, Index,NewValue,Local);
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

int  AIVoltageSensor::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
        Unit       = VOLTAGE_UNIT;
        DecPnt     = 1;
        MyRetValue = Offset;
        break;
    case SVT_AI_CALC_VAL :
        Unit       = VOLTAGE_UNIT;
        DecPnt     = 1;
        MyRetValue = Calculate();
        break;
    default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return(Status);
}

int AIVoltageSensor::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_UNIT:
        MyString = GetUnitName(VOLTAGE_UNIT);
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId,Index, MyString);
        break;
    }
    return(Status);
}

int AIVoltageSensor::PutFloatValue( int ValueId, float NewValue)
{
    return(AnalogInput::PutFloatValue(ValueId, NewValue));
}

void AIVoltageSensor::NewValue(float NewValue)
{
#ifndef ANCONF
    FilteredValue = NewValue;
    CalcValue     = NewValue;
    HWFailure     = false;
    ResultOK      = true;
    // Only check alarm for Master TCU for now
    if ( !CurrentDeviceAddress && CurrentDeviceId == DEVICE_TCU ) {
        CheckAlarms(AlarmSet);
    }
    SendData();
#endif
}

float AIVoltageSensor::Calculate(void)
{
    ResultOK  = true;
    CalcValue = FilteredValue;
    return(CalcValue);
}

