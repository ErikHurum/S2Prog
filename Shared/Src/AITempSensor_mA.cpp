#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
AITempSensor_mA::AITempSensor_mA(int SnsType)
{
    Type = SnsType;
    AlarmmAmpShortCircuit *ShortCircuitPtr  = new AlarmmAmpShortCircuit( this);
    AlarmmAmpOpenLoop     *OpenLoopPtr      = new AlarmmAmpOpenLoop(this,10000); // Was 0
    AlarmSet.insert(ShortCircuitPtr);
    AlarmSet.insert(OpenLoopPtr);

    // Init the other variables
    MaxRange  = 100.0;
    MinRange  = 0.0;
    MakeConstants();
}
//---------------------------------------------------------------------------

AITempSensor_mA::~AITempSensor_mA(void)
{
}
//---------------------------------------------------------------------------

U8 AITempSensor_mA::GetFilter(void)
{
    return(FILTER_MA_TEMP);
}

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

/*
AnsiString AITempSensor_mA::MakeConfigString(int ExtraTabs)
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
bool AITempSensor_mA::LoadConfigString(TSNConfigString &ConfigString)
{
    bool NoError = AITempSensor::LoadConfigString(ConfigString);
    MakeConstants();
    return(NoError);
}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AITempSensor_mA::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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

int  AITempSensor_mA::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
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

int AITempSensor_mA::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    return(AITempSensor::GetStringValue(ValueId,Index, MyString));
}

int AITempSensor_mA::PutFloatValue( int ValueId, float NewValue)
{
    return(AITempSensor::PutFloatValue(ValueId, NewValue));
}
//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////

void AITempSensor_mA::MakeConstants(void)
{
    a             =( MaxRange - MinRange) / ( 0.02 - 0.004);
    b             = MaxRange - a*0.02;
}

float AITempSensor_mA::Get_Temp(float Amp)
{
    float Temp = a*Amp + b;
    return(Temp);
}

float AITempSensor_mA::Calculate(void)
{
    if ( CanCalculate() ) {
        // This value should be checked for alarm
        CalcValue = Gain*Get_Temp(FilteredValue)-Offset;
        if ( CalcValue > MAX_TEMP || CalcValue < MIN_TEMP ) {
            Failure = true;
        } else {
            Failure = false;
        }
        ResultOK  = !Failure;
    }
    return(CalcValue);

}


