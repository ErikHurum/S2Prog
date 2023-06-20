#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AILevelSwitchOptical_mA::AILevelSwitchOptical_mA(int SnsType, float mA_On, float mA_Off, float mA_Win, float mA_Test, float mA_Light)
{
	Type                = SnsType;
	BasicSensorTypeWord = L_WORD599;//LSw
	Location            = C_AI_LOC_DECK;
	SwitchOn_mA         = mA_On;
	SwitchOff_mA        = mA_Off;
	SwitchWindow        = mA_Win;
	SwitchTest          = mA_Test;
	SwitchLight         = mA_Light;
	AlarmmAmpShortCircuit *ShortCircuitPtr      = new AlarmmAmpShortCircuit( this);
	AlarmmAmpOpenLoop     *OpenLoopPtr          = new AlarmmAmpOpenLoop( this);
	AlarmLevelSwitchTest  *LevelSwitchTest      = new AlarmLevelSwitchTest( this,LEVELSWITCH_HS_MA_TEST,LEVELSWITCH_HS_MA_WIN);
	AlarmLevelSwitchLight *LevelSwitchLightPtr  = new AlarmLevelSwitchLight( this);
	AlarmLevelSwitchDead  *LevelSwitchDeadPtr   = new AlarmLevelSwitchDead( this);
	AlarmLSwitchFailure   *LSwitchFailurePtr    = new AlarmLSwitchFailure( this);
	AlarmSet.insert(ShortCircuitPtr);
	AlarmSet.insert(OpenLoopPtr);
	AlarmSet.insert(LevelSwitchTest);
	AlarmSet.insert(LevelSwitchLightPtr);
	AlarmSet.insert(LevelSwitchDeadPtr);
	AlarmSet.insert(LSwitchFailurePtr);
}

AILevelSwitchOptical_mA::~AILevelSwitchOptical_mA(void)
{
}

//---------------------------------------------------------------------------
U8 AILevelSwitchOptical_mA::GetFilter(void)
{
	return(FILTER_LEVEL_SWITCH);
}

AnsiString AILevelSwitchOptical_mA::MakeConfigString(int ExtraTabs)
{
	AnsiString TabStr1= AnsiString::StringOfChar('\t',1+ExtraTabs);
	AnsiString LocalString;
	LocalString +=TabStr1+KeyWord(Type)+CrLfStr;
	LocalString += AnalogInput::MakeConfigString();	  //common

	LocalString +=TabStr1+KeyWord(C_AI_END)+CrLfStr;
	LocalString += CrLfStr;

	return(LocalString);
	//ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

bool AILevelSwitchOptical_mA::LoadConfigString(TSNConfigString &ConfigString)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning("Level switch sensor",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
			default:
				GiveConfigWarning("Level switch sensor",InputKeyWord,ConfigString.LineCount);
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
// Routines for Calculation of values
//
///////////////////////////////////////////////////////////////



#define LEVEL_SWITCH_HISTORY_SIZE	20
float AILevelSwitchOptical_mA::Calculate(void)
{
	if ( TSNElapsedTicks(TimeChecked)>CLOCKS_PER_SEC/10 ) {
		TimeChecked = clock();
		if ( CanCalculate() ) {
			float tmpCalcValue = Gain*FilteredValue-Offset;
			float MinVal       = ValueVector[0];
			float MaxVal       = ValueVector[0];
			ValueVector.push_back(tmpCalcValue);
			if ( ValueVector.size() > LEVEL_SWITCH_HISTORY_SIZE ) {
				ValueVector.erase(ValueVector.begin());
			}
			for ( unsigned i=0; i < ValueVector.size(); i++ ) {
				MinVal = MIN(MinVal, ValueVector[i]);
				MaxVal = MAX(MaxVal, ValueVector[i]);
			}
			SwitchVariation = fabs(MaxVal - MinVal);
			if ( fabs(tmpCalcValue-SwitchOn_mA) < SwitchWindow ) {
				CalcValue = LEVELSWITCH_ON;
				Failure = false;
			} else if ( fabs(tmpCalcValue-SwitchOff_mA) < SwitchWindow ) {
				CalcValue = LEVELSWITCH_OFF;
				Failure   = false;
			} else if ( fabs(tmpCalcValue-SwitchTest) < SwitchWindow ) {
				CalcValue = LEVELSWITCH_TEST;
				Failure   = false;
			} else if ( fabs(tmpCalcValue-SwitchLight) < SwitchWindow ) {
				CalcValue = LEVELSWITCH_LIGHT;
				Failure   = false;
			} else {
				CalcValue = LEVELSWITCH_ERROR;
				Failure   = true;
			}
		} else {
			if ( Enable ) {
				CalcValue = LEVELSWITCH_HW_ERROR;
			} else {
				CalcValue = LEVELSWITCH_OFF;
				Failure   = false;
			}
		}
	}
	return(CalcValue);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AILevelSwitchOptical_mA::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status = E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
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

int  AILevelSwitchOptical_mA::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_AI_OFFSET   :
		MyRetValue = Offset;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_AI_CALC_VAL :
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

int AILevelSwitchOptical_mA::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_AI_UNIT:
		MyString = GetUnitName(CURRENT_UNIT);
		break;
	default:
		Status = AnalogInput::GetStringValue(ValueId,Index, MyString);
		break;
	}
	return(Status);
}

int AILevelSwitchOptical_mA::PutFloatValue( int ValueId, float NewValue)
{
	return(AnalogInput::PutFloatValue(ValueId, NewValue));
}



