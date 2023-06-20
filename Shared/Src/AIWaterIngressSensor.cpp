#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIWaterIngressSensor::AIWaterIngressSensor(int SnsType, bool DisOverride) {
    DisableOverride = DisOverride;
    Type            = SnsType;
    BasicSensorType     = AI_SENSOR_WATER_INGRESS;
    BasicSensorTypeWord = L_WORD601; //WIng
    ADCardChannel  		= 0;
    switch (Type) {
    case C_AI_WATERINGRESS:
    case C_AI_WATERINGR_MAIN:
        Location = C_AI_LOC_WI_MAIN;
        Distance = 3.0;
        break;
    case C_AI_WATERINGR_PRE:
        Location = C_AI_LOC_WI_PRE;
        Distance = 1.0;
        break;
    }
    AdjustedDistance = Distance;
}

AIWaterIngressSensor::~AIWaterIngressSensor(void) {
}

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AIWaterIngressSensor::MakeConfigString(int ExtraTabs) {
    AnsiString TabStr1     = AnsiString::StringOfChar( '\t', 1 + ExtraTabs );
    AnsiString TabStr2     = AnsiString::StringOfChar( '\t', 2 + ExtraTabs );
    AnsiString TabStr3     = AnsiString::StringOfChar( '\t', 3 + ExtraTabs );
    AnsiString TabStr4     = AnsiString::StringOfChar( '\t', 4 + ExtraTabs );
    AnsiString TabStr5     = AnsiString::StringOfChar( '\t', 5 + ExtraTabs );
    AnsiString TabStr6     = AnsiString::StringOfChar( '\t', 6 + ExtraTabs );
    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord( Type ) + CrLfStr;
    if (SerialNumber.IsEmpty()) {
        SerialNumber = "None";
    }
    LocalString += TabStr3 + KeyWord( C_AI_SERIALNO ) + SerialNumber + CrLfStr;
    LocalString += TabStr3 + KeyWord( C_AI_DISTANCE ) + FloatToAnsiString( Distance ) + CrLfStr;
    LocalString += TabStr3 + KeyWord( C_TCU_ADDRESS ) + (AnsiString)TCUAddress + CrLfStr;
    LocalString += TabStr3 + KeyWord( C_TCU_PORT_NO ) + (AnsiString)TCUPortNo + CrLfStr;
    LocalString += TabStr3 + KeyWord( C_IO_TYPE ) + KeyWord( IOType ) + CrLfStr;
    LocalString += TabStr3 + KeyWord( C_IO_ADDRESS ) + (AnsiString)IOAddress + CrLfStr;
    LocalString += TabStr3 + KeyWord( C_IO_CHANNEL ) + (AnsiString)IOChannel + CrLfStr;

    LocalString += TabStr1 + KeyWord( C_AI_END ) + CrLfStr;
    LocalString += CrLfStr;

    return (LocalString);
}
//---------------------------------------------------------------------------


float AIWaterIngressSensor::Calculate(void) {
    if (CanCalculate()) {
        CalcValue = FilteredValue;  // Ignore gain and offset
        ResultOK = true;

    }
    return (CalcValue);

}

bool AIWaterIngressSensor::LoadConfigString(TSNConfigString &ConfigString) {
    bool       NoError   = true;
    int        ErrorLine = 0;
    int        Key;
    AnsiString PROName   = "Water Ingress sensor";
    if (PROPtr) PROName += (AnsiString)", for " + PROPtr->Name;
    PROName += ":\n";
    do {
        AnsiString InputKeyWord = ConfigString.NextWord( ErrorLine );
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning( PROName, ErrorLine );
            }
        } else {
            Key = FindConfigKey( InputKeyWord );
            switch (Key) {
            default:
                GiveConfigWarning( PROName, InputKeyWord, ConfigString.LineCount );
                break;
            case C_AI_START_COMMON:
                AnalogInput::LoadConfigString( ConfigString );
                break;
            case C_AI_END:
                break;
            case C_AI_SERIALNO:
                SerialNumber = ConfigString.NextWord( ErrorLine );
                NoError = !ErrorLine;
                break;
            case C_AI_DISTANCE:
                Distance = ConfigString.ReadDouble( ErrorLine );
                AdjustedDistance = Distance;
                NoError = !ErrorLine;
                break;
            case C_TCU_ADDRESS:
                TCUAddress = ConfigString.ReadLong( ErrorLine );
                NoError = !ErrorLine;
                break;
            case C_TCU_PORT_NO:
                TCUPortNo = ConfigString.ReadLong( ErrorLine );
                NoError = !ErrorLine;
                break;
            case C_IO_TYPE:
                {
                    AnsiString temp = ConfigString.NextWord( ErrorLine );
                    if (!ErrorLine) {
                        IOType = FindConfigKey( temp );
                    }
                    NoError = !ErrorLine;
                }
                break;
            case C_IO_ADDRESS:
                {
                    IOAddress = ConfigString.ReadLong( ErrorLine );
                    NoError = !ErrorLine;
                }
                break;
            case C_IO_CHANNEL:
                {
                    IOChannel = ConfigString.ReadLong( ErrorLine );
                    NoError = !ErrorLine;
                }
                break;
            case C_ADCARD_CH:
                {
                    ConfigString.ReadLong( ErrorLine );
                    NoError = !ErrorLine;
                }
                break;
            }
        }                                                              //remove this later
    }while (NoError && ( ErrorLine != EOF ) && ( Key != C_AI_END ) && ( Key != C_DI_END ));
    return (NoError);
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////


int AIWaterIngressSensor::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status    = E_NO_ERR,
        ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_AI_GAIN:
        Status = E_ILLEGAL;
        break;
    default:
        Status = AnalogInput::PutValue( ValueId, Index, NewValue, Local, &ValUnitId );
        break;
    }
    if ( Status == E_NO_ERR ) {
        SetModifiedFlag();
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return Status;
}

int  AIWaterIngressSensor::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
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
        Status = AnalogInput::GetValue( ValueId, Index, MyRetValue, DecPnt, Unit );
        break;
    }
    return (Status);
}

int AIWaterIngressSensor::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AI_UNIT:
        MyString = GetUnitName( NO_UNIT );
        break;
    default:
        Status = AnalogInput::GetStringValue( ValueId, Index, MyString );
        break;
    }
    return (Status);
}

int AIWaterIngressSensor::PutFloatValue(int ValueId, float NewValue) {
    return (E_NO_ERR);
}

