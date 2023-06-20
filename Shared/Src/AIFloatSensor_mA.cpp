#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIFloatSensor_mA::AIFloatSensor_mA(void)
{
    Type                = C_AI_Float_4_20mA;
    BasicSensorType     = AI_SENSOR_FLOAT;
    BasicSensorTypeWord = L_WORD947;//Float
    Location            = C_AI_LOC_DECK;
}

AIFloatSensor_mA::~AIFloatSensor_mA(void)
{
}


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AIFloatSensor_mA::MakeConfigString(int ExtraTabs)
{
    AnsiString LocalString =TabStrX(1,ExtraTabs)+KeyWord(Type)+CrLfStr;
    LocalString += AnalogInput::MakeConfigString();     //common
    {
        LocalString +=TabStr2+KeyWord(C_AI_CAL_DATA)+CrLfStr;
        for ( unsigned ind=0; ind< AmpPcnt.size(); ind++ ) {
            float Percent = AmpPcnt[ind]*100.0;
            float CalVal  = AmpCal[ind]*1000.0;

            LocalString +=TabStr3+FloatToAnsiString(AmpPcnt[ind]*100.0,5,1);
            LocalString +=TabStr1+FloatToAnsiString(AmpCal[ind]*1000.0,5,1)+CrLfStr;
        }
        LocalString +=TabStr2+KeyWord(C_T_TABLE_END)+CrLfStr;;
    }
    LocalString +=TabStrX(1,ExtraTabs)+KeyWord(C_AI_END)+CrLfStr;
    LocalString += CrLfStr;

    return(LocalString);
}
//---------------------------------------------------------------------------

bool AIFloatSensor_mA::LoadConfigString(TSNConfigString &ConfigString)
{
    bool NoError = true;
    int ErrorLine=0;
    int Key;
    AnsiString PROName = "Float sensor";
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
            case C_AI_CAL_DATA:
                do {
                    float Percent = ConfigString.ReadDouble(ErrorLine,C_T_TABLE_END);
                    float mAmp;
                    if ( !ErrorLine ) {
                        mAmp = ConfigString.ReadDouble(ErrorLine,C_T_TABLE_END);
                    }
                    if ( !ErrorLine ) {
                        AmpPcnt.push_back(Percent/100.0);
                        AmpCal.push_back(mAmp/1000.0);
                    }
                } while ( !ErrorLine );
                if ( ErrorLine == END_FOUND ) {
                    // End found, Permitted in this case, so ErrorStatus set to 0
                    ErrorLine = 0;
                    if ( AmpPcnt.empty() || AmpCal.empty() ) {
                        float Percent[2] = {0.0,100.0};
                        float mAmp[2]    = {4.0,20.0};
                        AmpPcnt.clear();
                        AmpCal.clear();
                        for ( int i=0; i < 2; i++ ) {
                            AmpPcnt.push_back(Percent[i]/100.0);
                            AmpCal.push_back(mAmp[i]/1000.0);
                        }
                    }
                }
                break;
            case C_AI_END:
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_AI_END ) );
    if (!MinRange && !MaxRange) {
        MinRange = Distance;
    }
    return(NoError);
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIFloatSensor_mA::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
        Offset = ConvertToSi(NewValue, ValUnitId=LENGTH_UNIT, Status,-5.0 ,50.0,Offset);
        break;
    case SVT_AI_CALC_VAL :
        Status = AdjustSensor(NewValue, ValUnitId=LENGTH_UNIT, 0.0 ,50.0,Local);
        break;
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

int  AIFloatSensor_mA::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
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
    return(Status);
}

int AIFloatSensor_mA::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_UNIT:
        MyString = GetUnitName(LENGTH_UNIT);
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId,Index, MyString);
        break;
    }
    return(Status);
}

int AIFloatSensor_mA::PutFloatValue( int ValueId, float NewValue)
{
    return(AnalogInput::PutFloatValue(ValueId, NewValue));
}

//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////
float AIFloatSensor_mA::Calculate(void)
{
	if ( CanCalculate() ) {
		CalcValue = Gain*Get_Level(FilteredValue) - Offset;
		ResultOK  = true;
	}
	return(CalcValue);
}
float AIFloatSensor_mA::Get_Percent(float Amp)
{
    int Index = 1;
    int LastI = AmpCal.size()-1;
    while ( ( Index < LastI ) && ( Amp >AmpCal[Index] ) )    Index++;

    return(IntPol1stDeg(AmpCal[Index-1],AmpCal[Index],AmpPcnt[Index-1],AmpPcnt[Index],Amp));
}

float AIFloatSensor_mA::Get_Level(float Amp)
{
    float  Percent= Get_Percent(Amp);
    return((MaxRange-MinRange)*Percent+MinRange);
}

