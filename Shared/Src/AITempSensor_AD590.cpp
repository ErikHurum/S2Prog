#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AITempSensor_AD590::AITempSensor_AD590(void)
{
    Initialize();
}
//---------------------------------------------------------------------------

AITempSensor_AD590::~AITempSensor_AD590(void)
{
}
//---------------------------------------------------------------------------

void AITempSensor_AD590::Initialize(void)
{
    Type                      = C_AI_TEMP_AD590;
    AdjustedDistance          = 0.0;

    ADConfigData.CalError     = false;
    ADConfigData.ConvError    = false;
    ADConfigData.EEP_PCStatus = AD_EEPROM_OK;
    ADConfigData.EEPromStatus = AD_EEPROM_OK;
    ADConfigData.EEPUsePCData = false;
    ADConfigData.FoundSensor  = AD_NO_SNS;
    ADConfigData.NewSensor    = false;
    ADConfigData.PCSensor     = AD_NO_SNS;
    ADConfigData.UsePCSetUp   = false;

    AlarmSensorConCalError *SnsHWErrAlPtr = new AlarmSensorConCalError( this,&ADConfigData);
    AlarmSet.insert(SnsHWErrAlPtr);
}

//---------------------------------------------------------------------------
AnsiString AITempSensor_AD590::MakeConfigString(int ExtraTabs)
{
    AnsiString LocalString;
    LocalString +=TabStr1+KeyWord(Type)+CrLfStr;
    LocalString += AnalogInput::MakeConfigString(ExtraTabs);
    LocalString +=TabStr1+KeyWord(C_AI_END)+CrLfStr;
    LocalString += CrLfStr;
    return(LocalString);
}

//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////
//
//
void AITempSensor_AD590::NewValue(float NewValue)
{
#ifndef ANCONF
    FilteredValue = NewValue*1442.5 - TEMP_ZERO; // 1 ^C/mV
    CalcValue     = NewValue*1442.5 - TEMP_ZERO;
    HWFailure     = false;
    ResultOK      = true;

    if ( CurrentDeviceId == DEVICE_TCU ) {
        CheckAlarms(AlarmSet);
        SendData();
    }
#endif
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AITempSensor_AD590::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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

int  AITempSensor_AD590::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
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

int AITempSensor_AD590::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    return(AITempSensor::GetStringValue(ValueId,Index, MyString));
}

int AITempSensor_AD590::PutFloatValue( int ValueId, float NewValue)
{
    return(AITempSensor::PutFloatValue(ValueId, NewValue));
}

void AITempSensor_AD590::SetStatus(U8 *NewStatus)
{
    ADConfigData = *(ConfigPacket*)NewStatus;
}




