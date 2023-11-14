#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
AITempSensor_Hart::AITempSensor_Hart(void)
{
    Type = C_AI_TEMP_Hart;

    // Init the other variables
    MaxRange  = 200.0;
    MinRange  = -25.0;
}
//---------------------------------------------------------------------------

AITempSensor_Hart::~AITempSensor_Hart(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

/*
AnsiString AITempSensor_Hart::MakeConfigString(int ExtraTabs)
{
    AnsiString TabStr1= AnsiString::StringOfChar('\t',1+ExtraTabs);
    AnsiString TabStr2= AnsiString::StringOfChar('\t',2+ExtraTabs);
    AnsiString TabStr3= AnsiString::StringOfChar('\t',3+ExtraTabs);
    AnsiString TabStr4= AnsiString::StringOfChar('\t',4+ExtraTabs);
    AnsiString TabStr5= AnsiString::StringOfChar('\t',5+ExtraTabs);
    AnsiString TabStr6= AnsiString::StringOfChar('\t',6+ExtraTabs);
    AnsiString LocalString;
    LocalString +=TabStr1+KeyWord(Type)+CrLfStr;
    LocalString += AnalogInput::MakeConfigString(1);     //common
    LocalString +=TabStr1+KeyWord(C_AI_END)+CrLfStr;
    LocalString += CrLfStr;

    return(LocalString);
}
*/

//---------------------------------------------------------------------------
bool AITempSensor_Hart::LoadConfigString(TSNConfigString &ConfigString)
{
    bool NoError = AITempSensor::LoadConfigString(ConfigString);
    if (NoError) {
        switch (IOType) {
        case C_IO_AN_ZBHART:
            {
                AlarmmAmpShortCircuit *ShortCircuitPtr  = new AlarmmAmpShortCircuit(this);
                AlarmmAmpOpenLoop     *OpenLoopPtr      = new AlarmmAmpOpenLoop(this,10000); // Was 5000
                AlarmSet.insert(ShortCircuitPtr);
                AlarmSet.insert(OpenLoopPtr);
            }
            break;
        case C_IO_MODBUS:
            {
                AlarmHartSensorShortCircuit *AlShortCircuitPtr  = new AlarmHartSensorShortCircuit(this);
                AlarmHartSensorOpenLoop     *AlOpenLoopPtr      = new AlarmHartSensorOpenLoop(this);
                AlarmSet.insert(AlShortCircuitPtr);
                AlarmSet.insert(AlOpenLoopPtr);
            }
            break;
        }
        AlarmHartSensorComError     *AlHartComErrPtr    = new AlarmHartSensorComError(this,HartComErrorCnt);
        AlarmSet.insert(AlHartComErrPtr);
    }
    return (NoError);
}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AITempSensor_Hart::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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

int  AITempSensor_Hart::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_HART_STATUS :
        MyRetValue = Failure & HART_STATUS_COM_ERROR_BIT;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_HART_OPEN_LOOP :
        MyRetValue = Failure & HART_STATUS_OPEN_LOOP_BIT;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_HART_SHORT_CIRCUIT :
        MyRetValue = Failure & SVT_HART_SHORT_CIRCUIT;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_AI_OFFSET   :
        MyRetValue = Offset;
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        break;
    case SVT_HART_TEMPERATURE  :
        MyRetValue = HartValue;
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        break;
    case SVT_HART_MA:
        MyRetValue = FilteredValue;
        DecPnt     = 3;
        Unit       = CURRENT_UNIT;
        break;
    case SVT_AI_CALC_VAL :
        MyRetValue = Calculate();
        DecPnt     = 3;
        Unit       = TEMP_UNIT;
        break;
    default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AITempSensor_Hart::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AI_UNIT:
        MyString = GetUnitName(TEMP_UNIT);
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int AITempSensor_Hart::PutFloatValue( int ValueId, float NewValue)
{
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_HART_MA:
        FilteredValue = NewValue*CNV_MILIAMP_TO_AMP;
        break;
    case SVT_HART_TEMPERATURE:
        HartValue     = NewValue;
         // HartComErr alarm is triggered by Failure status active. So HWFailure is based on mA alarms and HartComError
        ActiveAlarms = CheckAlarms(AlarmSet, &HWFailure);
       break;
    case SVT_HART_OPEN_LOOP:
        if (NewValue) {
            // 0x0xfe as mask to ignore possible Hart com fault
            Failure &= 0xfe;
            Failure |= HART_STATUS_OPEN_LOOP_BIT;
        }else{
            Failure &= (~HART_STATUS_OPEN_LOOP_BIT)&0xff;
        }
        break;
    case SVT_HART_SHORT_CIRCUIT:
        if (NewValue) {
            // 0x0xfe as mask to ignore possible Hart com fault
            Failure &= 0xfe;
            Failure |= HART_STATUS_SHORT_CIRCUIT_BIT;
        }else{
            Failure &= (~HART_STATUS_SHORT_CIRCUIT_BIT)&0xff;
        }
        break;
    case SVT_HART_STATUS:
        if (NewValue == HART_STATUS_COM_ERROR_BIT) {
            // Do not set if HART_STATUS_OPEN_LOOP_BIT or HART_STATUS_SHORT_CIRCUIT_BIT are active
            if (!(Failure & (HART_STATUS_OPEN_LOOP_BIT | HART_STATUS_SHORT_CIRCUIT_BIT))) {
                HartComErrorCnt++;
            }
        }else{
            HartComErrorCnt = 0;
        }
        break;
    case SVT_HART_ERROR_CNT:
        HartComErrorCnt = NewValue;
        break;
    default:
        Status = AnalogInput::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);

}
//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////


float AITempSensor_Hart::Calculate(void)
{
    if (CanCalculate() && !Failure) {
        // This value should be checked for alarm
        float RawCalcValue = Gain * HartValue - Offset;
        if (RawCalcValue < 0.0) {
            RawCalcValue = 0.0;
        }
        CalcValue = RawCalcValue;
        ResultOK  = true;

    }
    return (CalcValue);

}


void AITempSensor_Hart::SetNewStatus(bool NewStatus) {
    Failure = NewStatus;
}

void AITempSensor_Hart::NewValue(float NewValue) {
    HWFailure = false;
    HartValue = NewValue;
    SetTimeStamp();
}

