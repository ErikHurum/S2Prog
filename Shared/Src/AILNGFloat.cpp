#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AILNGFloat::AILNGFloat(void)
{
    Type = C_AI_HSH_LNG_Float;
}
//---------------------------------------------------------------------------

AILNGFloat::~AILNGFloat(void)
{
}
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AILNGFloat::MakeConfigString(int ExtraTabs)
{
    AnsiString LocalString =TabStrX(1,ExtraTabs)+KeyWord(Type)+CrLfStr;
    LocalString += AnalogInput::MakeConfigString();     //common
    LocalString +=TabStrX(1,ExtraTabs)+KeyWord(C_AI_END)+CrLfStr;
    LocalString += CrLfStr;

    return(LocalString);
}
//---------------------------------------------------------------------------

bool AILNGFloat::LoadConfigString(TSNConfigString &ConfigString)
{
    bool NoError = true;
    int ErrorLine=0;
    int Key;
    AnsiString PROName = "LNG_float";
    if ( PROPtr )   PROName +=(AnsiString)", for "+PROPtr->Name;
    PROName += ":\n";
    do {
        AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning(PROName,ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning(PROName,InputKeyWord,ConfigString.LineCount);
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


///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////
int  AILNGFloat::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
        MyRetValue = Offset;
        break;
    case SVT_AI_CALC_VAL :
        if ( CanCalculate() ) {
            MyRetValue = Calculate();
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return(Status);
}
int AILNGFloat::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_UNIT:
        MyString = GetUnitName(LENGTH_UNIT);
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId,Index, MyString);

    }
    return(Status);
}

//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////

float AILNGFloat::Calculate(void)
{
    if ( CanCalculate() ) {
        // This value should be checked for alarm
        float RawCalcValue = AdjustedDistance - Gain*FilteredValue-Offset;
        if (RawCalcValue < 0.0) {
            RawCalcValue = 0.0;
        }
        CalcValue = RawCalcValue;
        ResultOK  = true;

    }
    return(CalcValue);

}


