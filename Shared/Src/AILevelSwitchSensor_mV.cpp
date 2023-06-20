#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AiLevelSwitchSensor_mV::AiLevelSwitchSensor_mV(int SnsType)
{
    Type = SnsType;
    ADConfigData.CalError     = false;
    ADConfigData.ConvError    = false;
    ADConfigData.EEP_PCStatus = AD_EEPROM_OK;
    ADConfigData.EEPromStatus = AD_EEPROM_OK;
    ADConfigData.EEPUsePCData = false;
    ADConfigData.FoundSensor  = AD_NO_SNS;
    ADConfigData.NewSensor    = false;
    ADConfigData.PCSensor     = AD_NO_SNS;
    ADConfigData.UsePCSetUp   = false;

    AlarmSensorConCalError *SnsHWErrAlPtr = new AlarmSensorConCalError( this,&ADConfigData);
    AlarmSet.insert(SnsHWErrAlPtr);

}
//---------------------------------------------------------------------------

AiLevelSwitchSensor_mV::~AiLevelSwitchSensor_mV(void)
{
}
//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AiLevelSwitchSensor_mV::MakeConfigString(int ExtraTabs)
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

bool AiLevelSwitchSensor_mV::LoadConfigString(TSNConfigString &ConfigString)
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


int AiLevelSwitchSensor_mV::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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

int  AiLevelSwitchSensor_mV::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
	case SVT_AI_OFFSET      :
		// Note that the unit is in Volt for offset and NO_UNIT for calculated value.
        // This should maybe be modified later
        MyRetValue = Offset;
		DecPnt     = 3;
		Unit       = VOLTAGE_UNIT;
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

int AiLevelSwitchSensor_mV::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_IO_CH_CONV_ERROR   :
        MyString = LibGetText(StatusText,SizeofStatusText,ST_TXT_ERROR_STAT,ADConfigData.ConvError);
        break;
    case SVT_IO_CH_CNV_CAL_ERROR:
        if ( ADConfigData.ConvError && ADConfigData.CalError ) {
            MyString = FindDictionaryWord(L_WORD624);//CnvCal
        } else if ( ADConfigData.ConvError ) {
            MyString = FindDictionaryWord(L_WORD625);//CnvErr
        } else if ( ADConfigData.CalError ) {
            MyString = FindDictionaryWord(L_WORD626);//CalErr
        } else {
            MyString = FindDictionaryWord(L_WORD161);//OK
        }
        break;
    case SVT_IO_CH_CAL_ERROR    :
        MyString = LibGetText(StatusText,SizeofStatusText,ST_TXT_ERROR_STAT,ADConfigData.CalError);
        break;
    case SVT_IO_CH_EEP_SNS_STAT  :
        MyString = FindDictionaryWord(SCADCard::EEPromInfo[ADConfigData.EEPromStatus]);
        break;
    case SVT_IO_CH_EEP_PC_STAT  :
        MyString = FindDictionaryWord(SCADCard::EEPromInfo[ADConfigData.EEP_PCStatus]);
        break;
    case SVT_IO_CH_EEP_USE_PCDATA:
        MyString = LibGetText(StatusText,SizeofStatusText,ST_TXT_NO_YES,ADConfigData.EEPUsePCData);
        break;
    case SVT_IO_CH_USE_PC_SETUP  :
        MyString = LibGetText(StatusText,SizeofStatusText,ST_TXT_NO_YES,ADConfigData.UsePCSetUp);
        break;
    case SVT_IO_CH_AD_SENSOR :
        MyString = (AnsiString)SCADCard::ADSensorType[ADConfigData.FoundSensor];
        break;
    case SVT_IO_CH_FROM_PC_SENSOR :
        MyString = (AnsiString)SCADCard::ADSensorType[ADConfigData.PCSensor];
        break;
    case SVT_IO_CH_NEW_SENSOR   :
        MyString = LibGetText(StatusText,SizeofStatusText,ST_TXT_NO_YES,ADConfigData.NewSensor);
        break;
    case SVT_AI_UNIT:
        {
            int Unit = NO_UNIT;
            MyString = GetUnitName(Unit);
        }
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId,Index, MyString);
        break;
    }
    return(Status);
}

int AiLevelSwitchSensor_mV::PutFloatValue( int ValueId, float NewValue)
{
    return(AnalogInput::PutFloatValue(ValueId, NewValue));
}

void AiLevelSwitchSensor_mV::SetStatus(U8 *NewStatus)
{
    ADConfigData = *(ConfigPacket*)NewStatus;
}

float AiLevelSwitchSensor_mV::Calculate(void)
{
    if ( CanCalculate() ) {
        float tmpCalcValue = Gain*FilteredValue-Offset;
        if ( tmpCalcValue < LEVELSWITCH_VOLT_LIMIT ) {
            CalcValue = LEVELSWITCH_ON;
            Failure = false;
        } else {
            CalcValue = LEVELSWITCH_OFF;
            Failure = false;
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

