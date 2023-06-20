#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIMetriTapeSensor::AIMetriTapeSensor(void)
{

	Type = C_AI_MetriTape;
	//AlarmmAmpShortCircuit *HighResistancePtr  = new AlarmmAmpShortCircuit( this);
	//AlarmmAmpOpenLoop  *LowResistancePtr  = new AlarmmAmpOpenLoop( this);
	//AlarmSet.insert(ShortCircuitPtr);
	//AlarmSet.insert(OpenLoopPtr);
	// Always assume that the radar is mounted on deck
	// or top of the tank

	// Init the other variables
	MaxRange    = 30.0;
	MinRange    = 0.0;
	MaxR        = 30000.0;
	MinR        = 0.0;
	Rk          = 47000;
	Ui          = 24.0;
	MakeConstants();
}
//---------------------------------------------------------------------------

AIMetriTapeSensor::~AIMetriTapeSensor(void)
{
}
//---------------------------------------------------------------------------
U8 AIMetriTapeSensor::GetFilter(void)
{
	return(FILTER_METRIC_TAPE);
}
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AIMetriTapeSensor::MakeConfigString(int ExtraTabs)
{
	AnsiString LocalString =TabStrX(1,ExtraTabs)+KeyWord(Type)+CrLfStr;
	LocalString += AnalogInput::MakeConfigString();		//common

	LocalString +=TabStr4+KeyWord(C_AI_RESISTANCE_MIN  )+FloatToAnsiString(MinR,6,3)+CrLfStr;
	LocalString +=TabStr4+KeyWord(C_AI_RESISTANCE_MAX  )+FloatToAnsiString(MaxR,6,3)+CrLfStr;
	LocalString +=TabStr4+KeyWord(C_AI_RESISTANCE_CONST)+FloatToAnsiString(Rk  ,6,3)+CrLfStr;
	LocalString +=TabStr4+KeyWord(C_AI_VOLTAGE_CONST   )+FloatToAnsiString(Ui  ,6,3)+CrLfStr;
	LocalString +=TabStrX(1,ExtraTabs)+KeyWord(C_AI_END)+CrLfStr;
	LocalString += CrLfStr;

	return(LocalString);
}
//---------------------------------------------------------------------------

bool AIMetriTapeSensor::LoadConfigString(TSNConfigString &ConfigString)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	AnsiString PROName = "MetriTape";
	if ( PROPtr )	PROName +=(AnsiString)", for "+PROPtr->Name;
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
			case C_AI_RESISTANCE_MIN:
				MinR = ConfigString.ReadDouble(ErrorLine);
				NoError = !ErrorLine;
				break;
			case C_AI_RESISTANCE_MAX:
				MaxR = ConfigString.ReadDouble(ErrorLine);
				NoError = !ErrorLine;
				break;
			case C_AI_RESISTANCE_CONST:
				Rk = ConfigString.ReadDouble(ErrorLine);
				NoError = !ErrorLine;
				break;
			case C_AI_VOLTAGE_CONST:
				Ui = ConfigString.ReadDouble(ErrorLine);
				NoError = !ErrorLine;
				break;
			case C_AI_END:
				break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_AI_END ) );
	MakeConstants();
	return(NoError);
}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int  AIMetriTapeSensor::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	Unit    = LENGTH_UNIT;
	DecPnt  = 3;

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

int AIMetriTapeSensor::GetStringValue(int ValueId, int Index, AnsiString &MyString)
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
int AIMetriTapeSensor::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = LENGTH_UNIT;
	switch ( ValueId ) {
	case SVT_AI_OFFSET   :
		Offset = ConvertToSi(NewValue, LENGTH_UNIT, Status,0.0 ,50.0,Offset);
		break;
	case SVT_AI_CALC_VAL :
		{
			float NewVal = ConvertToSi(NewValue, LENGTH_UNIT, Status,0.0 ,50.0);
		}
		break;
	default:
		Status = AnalogInput::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
		break;
	}
	if ( Status==E_NO_ERR ) {
		SetModifiedFlag();
	}
	if ( UnitId ) {
		*UnitId = LENGTH_UNIT;
	}
	return(Status);
}

int AIMetriTapeSensor::PutFloatValue( int ValueId, float NewValue)
{
	return(AnalogInput::PutFloatValue(ValueId, NewValue));
}

//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////

void AIMetriTapeSensor::MakeConstants(void)
{
	a   =( MaxRange - MinRange) / (MinR - MaxR);
	b   = MaxRange - a*MinR;
}

void AIMetriTapeSensor::FilterValue(float NewCalcVal,float FilterDegree)
{
	CalcValue += (NewCalcVal - CalcValue)/(FilterDegree+1.0);
}

float AIMetriTapeSensor::Get_Resistance(float Uv)
{
	float Rv = ( Uv*Rk)/(Ui-Uv);
	return(Rv);
}

float AIMetriTapeSensor::Get_Distance(float Resistance)
{
	float Dist = a*Resistance + b;
	return(Dist);
}

float AIMetriTapeSensor::Calculate(void)
{
	if ( CanCalculate() ) {
		Failure = false;
		float Rv = Get_Resistance(FilteredValue);
		float NewCalcValue = Gain*Get_Distance(Rv)-Offset;
		FilterValue(NewCalcValue,FILTER_METRIC_TAPE);
		ResultOK  = true;
	}
	return(CalcValue);

}


