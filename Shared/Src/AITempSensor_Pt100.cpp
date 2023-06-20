#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AITempSensor_Pt100::AITempSensor_Pt100(float pRadarDistance)
{
    Type                 = C_AI_Pt100;
    DistJunctionBoxToBot = pRadarDistance;
    Initialize(NULL);
}
//---------------------------------------------------------------------------

AITempSensor_Pt100::~AITempSensor_Pt100(void)
{
}
//---------------------------------------------------------------------------

void AITempSensor_Pt100::Initialize(AnalogInput *Sns)
{
    if ( Sns ) {
        Distance          = Sns->Distance;
        AdjustedDistance  = Distance;
        Type              = C_AI_Pt100;
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
        IsPressureSns    = Sns->GetIsPressureSns();
    } else {
        Type              = C_AI_Pt100;
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

    AlarmSensorConvError *SnsHWErrAlPtr  = new AlarmSensorConvError( this,&ADConfigData);
    AlarmSet.insert(SnsHWErrAlPtr);
}
//---------------------------------------------------------------------------

void AITempSensor_Pt100::CalculateCableCorrection(void)
{
    float CableResistance = CableLengthSensor*CableResistanceSensor; 
    if ( CableMsrdResistance ) {
        CableResistance += CableMsrdResistance;
    }else{
        CableResistance += CableLengthShip*CableResistanceShip;
    }
    CableOffset = CableResistance/PT100_OHM_DEG;
}
///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AITempSensor_Pt100::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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

int  AITempSensor_Pt100::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
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

int AITempSensor_Pt100::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    return AITempSensor::GetStringValue(ValueId,Index, MyString);
}

int AITempSensor_Pt100::PutFloatValue( int ValueId, float NewValue)
{
    return AITempSensor::PutFloatValue(ValueId, NewValue);
}
void AITempSensor_Pt100::SetStatus(U8 *NewStatus)
{
    ADConfigData = *(ConfigPacket*)NewStatus;
}


