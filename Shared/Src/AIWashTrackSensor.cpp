#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AiWashTrackSensor::AiWashTrackSensor(void)
{
    Type                 = C_AI_WashTrackSensor;
    BasicSensorType      = AI_SENSOR_REVOLUTIONS;
    BasicSensorTypeWord  = L_WORD1015; //Revolutions
    Location             = C_AI_LOC_DECK;
    LocationKWord        = L_WORD593;
}
//---------------------------------------------------------------------------

AiWashTrackSensor::~AiWashTrackSensor(void)
{
}
//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AiWashTrackSensor::MakeConfigString(int ExtraTabs)
{
    AnsiString TabStr1= AnsiString::StringOfChar('\t',1+ExtraTabs);
    AnsiString TabStr2= AnsiString::StringOfChar('\t',2+ExtraTabs);
    AnsiString TabStr3= AnsiString::StringOfChar('\t',3+ExtraTabs);
    AnsiString TabStr4= AnsiString::StringOfChar('\t',4+ExtraTabs);
    AnsiString TabStr5= AnsiString::StringOfChar('\t',5+ExtraTabs);
    AnsiString TabStr6= AnsiString::StringOfChar('\t',6+ExtraTabs);
    AnsiString LocalString;
    LocalString +=TabStr1+KeyWord(Type)+CrLfStr;
    LocalString += AnalogInput::MakeConfigString();   //common

    LocalString +=TabStr1+KeyWord(C_AI_END)+CrLfStr;
    LocalString += CrLfStr;

    return(LocalString);
    //ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

bool AiWashTrackSensor::LoadConfigString(TSNConfigString &ConfigString)
{
    bool NoError = true;
    int ErrorLine=0;
    int Key;
    do {
        AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning("Washtrack sensor",ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning("Washtrack sensor",InputKeyWord,ConfigString.LineCount);
                break;
            case C_AI_START_COMMON:
                AnalogInput::LoadConfigString(ConfigString);
                break;
            case C_AI_END:
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_AI_END ) );
    return(NoError);
}
//---------------------------------------------------------------------------


///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AiWashTrackSensor::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
    case SVT_AI_CALC_VAL :
    default:
        Status = AnalogInput::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
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

int  AiWashTrackSensor::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_OFFSET      :
        MyRetValue = Offset;
		DecPnt     = 1;
		Unit       = REVOLUTIONS_UNIT;
        break;
    case SVT_AI_CALC_VAL    :
        MyRetValue = Calculate();
		DecPnt     = 1;
        Unit       = REVOLUTIONS_UNIT;
        break;
    default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return(Status);
}

int AiWashTrackSensor::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_UNIT:
        {
            int Unit = REVOLUTIONS_UNIT;
            MyString = GetUnitName(Unit);
        }
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId,Index, MyString);
        break;
    }
    return(Status);
}

int AiWashTrackSensor::PutFloatValue( int ValueId, float NewValue)
{
    return(AnalogInput::PutFloatValue(ValueId, NewValue));
}


void AiWashTrackSensor::NewValue(float NewValue)
{
    HWFailure     = false;
    FilteredValue = FilterVal(FilteredValue, NewValue, 1);
}
float AiWashTrackSensor::Calculate(void)
{
    if ( CanCalculate() ) {
        CalcValue = Gain*FilteredValue-Offset;
    } else {
        CalcValue = 0.0;
    }
    return(CalcValue);
}

