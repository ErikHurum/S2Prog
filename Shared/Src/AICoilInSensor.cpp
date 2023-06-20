#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AiCoilInSensor::AiCoilInSensor(int SnsType)
{
	Type = SnsType;
}
//---------------------------------------------------------------------------

AiCoilInSensor::~AiCoilInSensor(void)
{
}
//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AiCoilInSensor::MakeConfigString(int ExtraTabs)
{
	AnsiString TabStr1= AnsiString::StringOfChar('\t',1+ExtraTabs);
	AnsiString LocalString;
	LocalString +=TabStr1+KeyWord(Type)+CrLfStr;

	LocalString +=TabStr1+KeyWord(C_AI_END)+CrLfStr;
	LocalString += CrLfStr;

	return(LocalString);
	//ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

bool AiCoilInSensor::LoadConfigString(TSNConfigString &ConfigString)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning("Voltage level switch sensor",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
			default:
				GiveConfigWarning("Voltage level switch sensor",InputKeyWord,ConfigString.LineCount);
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


int AiCoilInSensor::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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

int  AiCoilInSensor::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_AI_OFFSET      :
		MyRetValue = Offset;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_AI_CALC_VAL    :
		MyRetValue = Calculate();
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	default:
		Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
		break;
	}
	return(Status);
}

int AiCoilInSensor::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	default:
		Status = AnalogInput::GetStringValue(ValueId,Index, MyString);
		break;
	}
	return(Status);
}

int AiCoilInSensor::PutFloatValue( int ValueId, float NewValue)
{
	return(AnalogInput::PutFloatValue(ValueId, NewValue));
}

void AiCoilInSensor::SetNewStatus(bool NewStatus)
{
    HWFailure     = false;
	FilteredValue = float(NewStatus);
}

float AiCoilInSensor::Calculate(void)
{
	if ( CanCalculate() ) {
		float tmpCalcValue = Gain*FilteredValue-Offset;
		if ( tmpCalcValue ) {
			CalcValue = LEVELSWITCH_ON;
			Failure   = false;
		} else {
			CalcValue = LEVELSWITCH_OFF;
			Failure   = false;
	   }
	} else {
		if ( Enable ) {
			CalcValue = LEVELSWITCH_HW_ERROR;
		} else {
			CalcValue = LEVELSWITCH_OFF;
		}
	}
	return(CalcValue);
}

