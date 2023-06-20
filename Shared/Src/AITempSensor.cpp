#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

////////////////////////////////////////////////////////////////////// 
///// 
///  The calculations has been verified using the datasets her. 
/// 
/// 
///
/*
    double Tmp1 = GetTempFromR(18.52);
    double Tmp2 = GetTempFromR(35.54);
    double Tmp3 = GetTempFromR(60.26);
    double Tmp4 = GetTempFromR(80.31);
    double Tmp5 = GetTempFromR(100);
    double Tmp6 = GetTempFromR(103.9);
    double Tmp7 = GetTempFromR(119.4);
    double Tmp8 = GetTempFromR(138.51);
*/
    /*
double Tmp = 0.0;
temp_PRTTemperatureValue(18.52 ,100,Tmp);
temp_PRTTemperatureValue(35.54 ,100,Tmp);
temp_PRTTemperatureValue(60.26 ,100,Tmp);
temp_PRTTemperatureValue(80.31 ,100,Tmp);
temp_PRTTemperatureValue(100   ,100,Tmp);
temp_PRTTemperatureValue(103.9 ,100,Tmp);
temp_PRTTemperatureValue(119.4 ,100,Tmp);
temp_PRTTemperatureValue(138.51,100,Tmp);
*/
///////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------

AITempSensor::AITempSensor(void) {
    Init();
}

AITempSensor::AITempSensor(int SnsType) {
    Init();
    Type                = SnsType;
}

AITempSensor::~AITempSensor(void) {
}

void AITempSensor::Init(void) {
    CableLengthShip         = 0.0;
    CableLengthSensor       = 0.0;
    CableResistanceShip     = PROProjectInfo::CableResistanceShip  ;
    CableResistanceSensor   = PROProjectInfo::CableResistanceSensor;
    CableMsrdResistance     = 0.0;
    CableOffset             = 0.0;
    DistJunctionBoxToBot    = 0.0;
    Location                = C_AI_LOC_TEMP;
    BasicSensorType         = AI_SENSOR_TEMP;
    BasicSensorTypeWord     = L_WORD338; //Temp
    CalData                 = NULL;
    hasCableLengthSensor    = false;
    hasCableResistanceShip  = false;  
    hasCableResistanceSensor= false;
}


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AITempSensor::MakeConfigString(int ExtraTabs) {
    AnsiString TabStr1 = AnsiString::StringOfChar('\t', 1 + ExtraTabs);
    AnsiString TabStr2 = AnsiString::StringOfChar('\t', 2 + ExtraTabs);
    AnsiString TabStr3 = AnsiString::StringOfChar('\t', 3 + ExtraTabs);
    AnsiString TabStr4 = AnsiString::StringOfChar('\t', 4 + ExtraTabs);
    AnsiString TabStr5 = AnsiString::StringOfChar('\t', 5 + ExtraTabs);
    AnsiString TabStr6 = AnsiString::StringOfChar('\t', 6 + ExtraTabs);
    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord(Type) + CrLfStr;
    // Force 0.0 for distance as it will be calculated if distance 0.0 and sensor cable length is configured
    if ( !HasDistance ) {
        Distance = 0.0;
    }
    LocalString += AnalogInput::MakeConfigString();     //common

    switch ( Location ) {
        case C_AI_LOC_TEMP_IN :
        case C_AI_LOC_TEMP_OUT:
            LocalString += TabStr4 + KeyWord(Location) + CrLfStr;
            break;
        default:
            break;
    }

    if ( CableLengthShip ) {
        LocalString += TabStr2 + KeyWord(C_AI_CABLE_LENGTH_SHIP) + FloatToAnsiString(CableLengthShip) + CrLfStr;
    }
    if ( hasCableLengthSensor ) {
        LocalString += TabStr2 + KeyWord(C_AI_CABLE_LENGTH_SENS) + FloatToAnsiString(CableLengthSensor) + CrLfStr;
    }
    if ( CableResistanceShip != SHIP_BOARD_CABLE_RES ) {
        LocalString += TabStr2 + KeyWord(C_AI_CABLE_RES_SHIP) + FloatToAnsiString(CableResistanceShip) + CrLfStr;
    }
    if ( CableResistanceSensor != TEMP_SENS_CABLE_RES ) {
        LocalString += TabStr2 + KeyWord(C_AI_CABLE_RES_SENS) + FloatToAnsiString(CableResistanceSensor) + CrLfStr;
    }
    if ( CableMsrdResistance ) {
        LocalString += TabStr2 + KeyWord(C_AI_CABLE_RES_MSRD) + FloatToAnsiString(CableMsrdResistance) + CrLfStr;
    }
    if ( CalData ) {
        LocalString += CalData->MakeConfigString();
    }
    LocalString += TabStr1 + KeyWord(C_AI_END) + CrLfStr;
    LocalString += CrLfStr;

    return (LocalString);
}
//---------------------------------------------------------------------------

bool AITempSensor::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key; 
    AnsiString PROName = "Temperature sensor";
    if ( PROPtr )   PROName += (AnsiString)", for " + PROPtr->Name;
    PROName += ":\n";
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning(PROName, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning(PROName, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_START_COMMON:
				AnalogInput::LoadConfigString(ConfigString);
                PROName = "Temperature sensor";
                break;
            case C_AI_CABLE_LENGTH_SHIP:
                CableLengthShip     = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_CABLE_LENGTH_SENS2:
            case C_AI_CABLE_LENGTH_SENS:
                hasCableLengthSensor = true;
                CableLengthSensor    = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_CABLE_RES_SHIP   :
                hasCableResistanceShip = true;
                CableResistanceShip    = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_CABLE_RES_SENS   :
                hasCableResistanceSensor = true;
                CableResistanceSensor    = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_CABLE_RES_MSRD   :
                CableMsrdResistance = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_T_LEVEL_VOL_TABLE:
                CalData = new TSNTable1Degree(Key);
                if ( CalData ) CalData->LoadConfigString(ConfigString, this);
                break;
            case C_AI_CAL_DATA:
                CalData = new TSNTable1Degree(Key);
                if ( CalData ) CalData->LoadConfigString(ConfigString, this);
                break;
            case C_AI_LOC_TEMP_IN :
            case C_AI_LOC_TEMP_OUT:
                Location = Key;
                break;
            case C_AI_END:
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_AI_END) );
    if ( hasCableLengthSensor && !HasDistance ) {
        // Use radar height as the vertical zero point assuming that
        // the junction box is at the same height
        Distance = DistJunctionBoxToBot - CableLengthSensor;
        if ( Distance < 0.0 ) {
            GiveConfigWarning(PROName + " Incorrect sensor cable length?", ConfigString.LineCount);
            Distance = 0.0;
        }
    } else if ( !hasCableLengthSensor && HasDistance ){
        CableLengthSensor = DistJunctionBoxToBot - Distance;
    }
    CalculateCableCorrection();
    return (NoError);
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AITempSensor::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
        Offset = ConvertToSi(NewValue, ValUnitId = TEMP_UNIT, Status, -180.0, 200.0, Offset);
        break;
    case SVT_AI_CALC_VAL :
        Status = AdjustSensor(NewValue, ValUnitId = TEMP_UNIT, -25.0, 125.0, Local);
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

int  AITempSensor::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
        MyRetValue = Offset;
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        break;
    case SVT_AI_CALC_VAL :
        if ( !CanCalculate() ) {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        } else {
            MyRetValue = Calculate();
        }
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        break;
    case SVT_AI_CABLE_LENGTH:
        MyRetValue = CableLengthSensor;
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        break;
    default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AITempSensor::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_UNIT:
        MyString = GetUnitName(TEMP_UNIT);
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return Status;
}

int AITempSensor::PutFloatValue(int ValueId, float NewValue) {
    return (AnalogInput::PutFloatValue(ValueId, NewValue));
}

///////////////////////////////////////////////////////////////////
//
// Sensor check methode her, because here we know the application
//
///////////////////////////////////////////////////////////////////
int AITempSensor::CheckInput(float Operator_Val, int &Action) {
    int InpStat   = E_NO_ERR;
    if ( Enable ) {
        if ( ActiveAlarms ) {
            InpStat = E_SENSOR_ERROR;
            Action  = SNS_ADJUST_ABORT;
        } else {
            Action = SNS_ADJUST_OFFSET;
        }

    } else {
        InpStat = E_SENSOR_IS_DISABELED;
        Action  = SNS_ADJUST_ABORT;
    }
    return (InpStat);
}


void AITempSensor::CalculateCableCorrection(void) {
}
float AITempSensor::GetCableCorrection(void) {
    return CableOffset;
}

bool AITempSensor::IsHWError(void) {
    return false; // Default to no error EHSMark
}

//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
// Formula for Pt100
// Rt = R0 * (1 + A* t + B*t2 + C*(t-100)* t3)
// Where:
// Rt is the resistance at temperature t, R0 is the resistance at 0 °C, and
// A= 3.9083 E–3
// B = –5.775 E–7
// C = –4.183 E–12 (below 0 °C), or
// C = 0 (above 0 °C)
//
// Relationship between temperature and resistance
// For each temperature there is exactly one resistance value.
// This clear relationship can be described by mathematical formulae.
// For the temperature range -200 ... 0 °C the following applies,
// irrespective of the resistor design:
// Rt = R 0 [1 + At + Bt² + C ( t - 100 °C) • t³ ]
// For the temperature range 0 ... 600 °C the following applies:
// Rt = R 0 [1 + At + Bt² ] Legend: t = Temperature in °C
// Rt = Resistance in ohms at the measured temperature R0 = Resistance in ohms at t = 0 °C (e.g. 100 ohms)
// For the calculation, the following constants apply
// A = 3.9083 • 10-3 (°C-1) B = -5.7750 • 10-7 (°C-2) C = -4.1830 • 10-12 (°C-4)
//
//
//
//
//////////////////////////////////////////////////////////////////
float AITempSensor::Calculate(void) {

    if ( CanCalculate() ) {
        float CorrectedTemp; 
        if ( CalData ) {
            CorrectedTemp = CalData->Calc_Y(FilteredValue);
        }else{
            CorrectedTemp = FilteredValue;
        }
        CalcValue = Gain * CorrectedTemp - Offset - GetCableCorrection();
        if ( CalcValue > MAX_TEMP || CalcValue < MIN_TEMP ) {
            Failure = true;
        } else {
            Failure = false;
        }
        ResultOK  = !Failure;
    }
    return (CalcValue);
}

bool AITempSensor::temp_PRTResistanceValue(double aTemp, double R0, double &Resistance) {
// The function temp_PRTResistanceValue calculates the electrical
// resistance for a Platinum Resistance Thermometer (PRT) at given
// temperature and defined resistance R0 at 0°C for a PRT element.
// E.g. for a Pt1000 element resistance R0=1000. Function returns
// TRUE if aTemp is within the ranges polynomial approximation
// are defined, the respective resistance for the temperature aTemp
// is found in Resistance.
//----------------------------------------------------------------
// Units:
//  aTemp        Input temperature in ITS-90                   °C
//  R0           Type of PRT (resistance at 0°C; e.g. Pt100)   Ohm
//  Resistance   Returned resistance of R0 type PRT at aTemp   Ohm
//----------------------------------------------------------------
// References:
//  Preston-Thomas & Quinn 1990 - Techniques for approximating
//    the international temperature scale of 1990 - Bureau
//    International des Poids et Mesures, 2nd Edition 1997,
//    respecting the amendments of the 2nd Edition
//-------------------------------------------------------------
//  (c) Dr. Jan Schulz, 17. December 2008, www.code10.info
//expect best case
    bool hasPRTResistanceValue = true;

    // is aTemp within defined ranges for the polynomial approximation
    if ( (aTemp >= -200) && (aTemp <= 850) ) {
        // aTemp decides which polynomial to use
        if ( aTemp >= 0 ) {
            Resistance = R0 * ((-5.775E-7 * aTemp + 3.9083E-3) * aTemp + 1);
        } else {
            Resistance = R0 * ((((aTemp - 100) * -4.183E-12 * aTemp - 5.775E-7) * aTemp + 3.9083E-3) * aTemp + 1);
        }
    } else {
        // otherwise return False and defined Resistance
        hasPRTResistanceValue = false;
        Resistance              = 0;
    }
    return hasPRTResistanceValue;
}


bool AITempSensor::temp_PRTTemperatureValue(double aResistance, double R0, double &Temperature) {
// The function temp_PRTTemperatureValue calculates the temperature
// measured by a Platinum Resistance Thermometer (PRT) at given
// electrical resistance and defined resistance R0 at 0°C for a
// PRT element. E.g. for a Pt1000 element resistance R0=1000.
// Function returns TRUE if aResistance is within the ranges
// polynomial approximation are defined, the respective temperature
// for resistance aResistance is found in Temperature.
//----------------------------------------------------------------
// Units:
//  aResistance  Input electrical resistance                   Ohm
//  R0           Type of PRT (electrical resistance at 0°C)    Ohm
//  Temperature  Returned ITS-90 Temperature                   °C
//----------------------------------------------------------------
// References:
//  Preston-Thomas & Quinn 1990 - Techniques for approximating
//    the international temperature scale of 1990 - Bureau
//    International des Poids et Mesures, 2nd Edition 1997,
//    respecting the amendments of the 2nd Edition
//-------------------------------------------------------------
//  (c) Dr. Jan Schulz, 18. December 2008, www.code10.info
    double MinResistance;
    double MaxResistance;
    // expect worst case
    bool hasResult = false;
    Temperature              = 0;

    // find min and max resistance values for defined range
    if ( temp_PRTResistanceValue(-200, R0, MinResistance) &&
         temp_PRTResistanceValue(+850, R0, MaxResistance) ) {
        // is aResitance within defined range of polynomial approximation
        if ( (aResistance >= MinResistance) && (aResistance <= MaxResistance) ) {
            // then calculate temperature
            Temperature = (-R0 * 3.9083E-3 +
                           sqrt(R0 * R0 * +3.9083E-3 * 3.9083E-3 - 4 * R0 * -5.775E-7 * (R0 - aResistance))) /
                (2 * R0 * -5.775E-7);
            // and notify that we expect reliable results
            hasResult = true;
        }
    }
    return hasResult;
}

//
float AITempSensor::GetTempFromR(double R) {
    const double C0 = -245.19;
    const double C1 = 2.5293;
    const double C2 = -0.066046;
    const double C3 = 4.0422e-3;
    const double C4 = -2.0697e-6;
    const double C5 = -0.025422;
    const double C6 = 1.6883e-3;
    const double C7 = -1.3601e-6;
    double Tmp = C0 + R * (C1 + R * (C2 + R * (C3 + C4 * R))) / (1 + R * (C5 + R * (C6 + C7 * R)));
    return Tmp;
}
