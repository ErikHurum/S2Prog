#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AITempSensor_Pt1000::AITempSensor_Pt1000(float pRadarDistance)
{
    DistJunctionBoxToBot = pRadarDistance;
    Initialize(NULL);
}

//---------------------------------------------------------------------------

AITempSensor_Pt1000::AITempSensor_Pt1000(AnalogInput *Sns) 
{
    Initialize(Sns);
}
//---------------------------------------------------------------------------

AITempSensor_Pt1000::~AITempSensor_Pt1000(void)
{
}
//---------------------------------------------------------------------------

void AITempSensor_Pt1000::Initialize(AnalogInput *Sns)
{
    if ( Sns ) {
        IsIntegrated      = true;
        Distance          = Sns->Distance;
        AdjustedDistance  = Distance;
        Type              = C_AI_Pt1000;    //Type = Sns->Type;
        Name              = Sns->Name;
        SortNo            = Sns->SortNo;
        TagName           = Sns->TagName;
        SerialNumber      = Sns->SerialNumber;
        TCUAddress        = Sns->TCUAddress;
        //TCUPort               = Sns->TCUPort;
        TCUPortNo         = Sns->TCUPortNo;
        IOAddress         = Sns->IOAddress;
        IOChannel         = Sns->IOChannel;
        IOType            = Sns->IOType;
        ADCardChannel     = Sns->ADCardChannel+1;
        Location          = Sns->Location;
        IsPressureSns     = Sns->GetIsPressureSns();
        if ( IsPressureSns ) {
            Location = C_AI_LOC_VAPOUR;
        }
        {
            AIPressSensor_mV *tmpSensor =(AIPressSensor_mV *)Sns;
            tmpSensor->SetTmpSnsPtr((AITempSensor*)this);
            CableLengthShip          = tmpSensor->CableLengthShip         ;
            CableLengthSensor        = tmpSensor->CableLengthSensor       ;
            CableResistanceShip      = tmpSensor->CableResistanceShip     ;
            CableResistanceSensor    = tmpSensor->CableResistanceSensor   ;
            CableMsrdResistance      = tmpSensor->CableMsrdResistance     ;
            hasCableLengthSensor     = tmpSensor->hasCableLengthSensor    ;
            hasCableResistanceShip   = tmpSensor->hasCableResistanceShip  ;
            hasCableResistanceSensor = tmpSensor->hasCableResistanceSensor;
        }
        CalculateCableCorrection();
    } else {
        Type              = C_AI_Pt1000;
		IsIntegrated      = false;
        AdjustedDistance  = 0.0;
	}

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
AnsiString AITempSensor_Pt1000::MakeConfigString(int ExtraTabs)
{
    AnsiString LocalString;
    if ( !IsIntegrated ) {
        LocalString +=TabStr1+KeyWord(C_AI_Pt1000)+CrLfStr;
        LocalString += AnalogInput::MakeConfigString(ExtraTabs);
        LocalString +=TabStr1+KeyWord(C_AI_END)+CrLfStr;
        LocalString += CrLfStr;
    }
    return(LocalString);
}
//---------------------------------------------------------------------------
void AITempSensor_Pt1000::CalculateCableCorrection(void)
{
    float CableResistance = CableLengthSensor*CableResistanceSensor; 
    if ( CableMsrdResistance ) {
        CableResistance += CableMsrdResistance;
    }else{
        CableResistance += CableLengthShip*CableResistanceShip;
    }
    CableOffset = CableResistance/PT1000_OHM_DEG;
}
//---------------------------------------------------------------------------


///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AITempSensor_Pt1000::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
    case SVT_AI_CALC_VAL :
    default:
        Status = AITempSensor::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
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

int  AITempSensor_Pt1000::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
    case SVT_AI_CALC_VAL :
    default:
        Status = AITempSensor::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return(Status);
}

int AITempSensor_Pt1000::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    return(AITempSensor::GetStringValue(ValueId,Index, MyString));
}

int AITempSensor_Pt1000::PutFloatValue( int ValueId, float NewValue)
{
    return(AITempSensor::PutFloatValue(ValueId, NewValue));
}

void AITempSensor_Pt1000::SetStatus(U8 *NewStatus)
{
    ADConfigData = *(ConfigPacket*)NewStatus;
}


