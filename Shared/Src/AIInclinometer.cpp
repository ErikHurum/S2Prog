#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIInclinometer::AIInclinometer(int SnsType) {
    Type                = SnsType;
    BasicSensorType     = AI_SENSOR_INCLINOMETER;
    BasicSensorTypeWord = L_WORD551;    //Inclinometer
    Location            = C_AI_LOC_SYSTEM; // Start with this
    Sign                = 1.0;

}
//---------------------------------------------------------------------------

AIInclinometer::~AIInclinometer(void) {
}
//---------------------------------------------------------------------------


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

void AIInclinometer::SetSign(float Sgn) {
    Sign = Sgn;
}


AnsiString AIInclinometer::MakeConfigString(int ExtraTabs) {
    AnsiString TabStr1 = AnsiString::StringOfChar('\t', 1 + ExtraTabs);
    AnsiString TabStr2 = AnsiString::StringOfChar('\t', 2 + ExtraTabs);
    AnsiString TabStr3 = AnsiString::StringOfChar('\t', 3 + ExtraTabs);
    AnsiString TabStr4 = AnsiString::StringOfChar('\t', 4 + ExtraTabs);
    AnsiString TabStr5 = AnsiString::StringOfChar('\t', 5 + ExtraTabs);
    AnsiString TabStr6 = AnsiString::StringOfChar('\t', 6 + ExtraTabs);
    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord(Type) + CrLfStr;
    LocalString += AnalogInput::MakeConfigString();   //common

    LocalString += TabStr1 + KeyWord(C_AI_END) + CrLfStr;
    LocalString += CrLfStr;

    return (LocalString);
    //ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

bool AIInclinometer::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning("Inclinometer sensor", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning("Inclinometer sensor", InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_START_COMMON:
                AnalogInput::LoadConfigString(ConfigString);
                break;
            case C_AI_END:
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_AI_END) );
    return (NoError);
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AIInclinometer::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
        Offset = ConvertToSi(NewValue, ValUnitId = ANGLE_UNIT, Status, -3.0, 3.0, Offset);
        break;
    case SVT_AI_CALC_VAL :
        Status = AdjustSensor(NewValue, ValUnitId = ANGLE_UNIT, -3.0, 3.0, Local);
        break;
    default:
        Status = AnalogInput::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    if ( Status == E_NO_ERR ) {
        SetModifiedFlag();
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int  AIInclinometer::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
        MyRetValue = Offset;
        DecPnt     = 2;
        Unit       = ANGLE_UNIT;
        break;
    case SVT_AI_CALC_VAL :
        if ( !CanCalculate() ) {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        } else {
            MyRetValue = Calculate();
        }
        DecPnt     = 2;
        Unit       = ANGLE_UNIT;
        break;
    default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AIInclinometer::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_UNIT:
        MyString = GetUnitName(ANGLE_UNIT);
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int AIInclinometer::PutFloatValue(int ValueId, float NewValue) {
    return (AnalogInput::PutFloatValue(ValueId, NewValue));
}

////////////////////////////////////////////////////////// 
/// 
/// Misc routines for calculations
/// 
/// 
////////////////////////////////////////////////////////// 
// Should support correction of the inclinometer
float AIInclinometer::CalculateRaw(void) {
    return Gain * FilteredValue * Sign / RAD_FACTOR - Offset;
}

