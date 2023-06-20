#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIRadarSensor::AIRadarSensor(int SnsType) {
    Type                = SnsType;
    BasicSensorType     = AI_SENSOR_RADAR;
    BasicSensorTypeWord = L_WORD600; //Rad
    Location            = C_AI_LOC_DECK;
}

AIRadarSensor::~AIRadarSensor(void) {
}


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AIRadarSensor::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString = TabStrX(1, ExtraTabs) + KeyWord(Type) + CrLfStr;
    LocalString += AnalogInput::MakeConfigString();     //common
    LocalString += TabStrX(1, ExtraTabs) + KeyWord(C_AI_END) + CrLfStr;
    LocalString += CrLfStr;

	return (LocalString);
}
//---------------------------------------------------------------------------

bool AIRadarSensor::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    AnsiString PROName = "Radar sensor";
    if (PROPtr)   PROName += (AnsiString)", for " + PROPtr->Name;
    PROName += ":\n";
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
			if (ErrorLine != EOF) {
                GiveConfigWarning(PROName, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning(PROName, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_START_COMMON:
                AnalogInput::LoadConfigString(ConfigString);
                break;
            case C_AI_END:
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_AI_END));
    if (!MinRange && !MaxRange) {
        MinRange = Distance;
    }

    return (NoError);
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIRadarSensor::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_AI_OFFSET   :
        Offset = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, -5.0, 50.0, Offset);
        break;
    case SVT_AI_CALC_VAL :
        Status = AdjustSensor(NewValue, ValUnitId = LENGTH_UNIT, 0.0, 50.0, Local);
        break;
    default:
        Status = AnalogInput::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    if (Status == E_NO_ERR) {
        SetModifiedFlag();
    }
    if (UnitId) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int  AIRadarSensor::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AI_OFFSET   :
        MyRetValue = Offset;
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        break;
    case SVT_AI_CALC_VAL :
        MyRetValue = Calculate();
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        break;
    default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}


int AIRadarSensor::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AI_UNIT:
        MyString = GetUnitName(LENGTH_UNIT);
        break;
    case SVT_AI_RANGE:

        MyString = "Range:" + LibGetValue(SVT_AI_MIN_RANGE, this) + " to " + LibGetValue(SVT_AI_MAX_RANGE, this) + " meter";
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int AIRadarSensor::PutFloatValue(int ValueId, float NewValue) {
    return (AnalogInput::PutFloatValue(ValueId, NewValue));
}


