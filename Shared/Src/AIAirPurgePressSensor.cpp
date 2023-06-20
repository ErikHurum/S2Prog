#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIAirPurgePressSensor::AIAirPurgePressSensor(void)
{
    Type                        = C_AI_AirPurge;
    IOType                      = C_IO_MODBUS;
    BasicSensorTypeWord         = L_WORD996;//Air
    Location                    = C_AI_LOC_BOTTOM;
    MinRange                    = 0.0;
    MaxRange                    = 100.0;
    AlAirPurgeSensorFailurePtr  = new AlarmAirPurgeSensorFailure(this);
    AlarmSet.insert(AlAirPurgeSensorFailurePtr);
}

AIAirPurgePressSensor::~AIAirPurgePressSensor(void)
{
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIAirPurgePressSensor::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_AI_OFFSET   :
        Offset = ConvertToSi(NewValue, ValUnitId = PRESSURE_UNIT2, Status, -5.0, 5.0, Offset);
        break;
    case SVT_AI_CALC_VAL :
        Status = AdjustSensor(NewValue, ValUnitId = PRESSURE_UNIT2, 0.0, 50.0, Local);
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

int  AIAirPurgePressSensor::GetValue(int ValueId, int Index, float& MyRetValue, int& DecPnt, int& Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AI_OFFSET   :
        MyRetValue = Offset;
        DecPnt     = 3;
        Unit       = PRESSURE_UNIT2;
        break;
    case SVT_AP_LEVEL_PRESSURE_MH2O:
    case SVT_AP_TANK_PRESSURE_MB   :
    case SVT_AP_LEVEL_PRESSURE_MB  :
        MyRetValue = Calculate();
        DecPnt     = 3;
        Unit       = PRESSURE_UNIT2;
        break;
	case SVT_AI_CALC_VAL :
		MyRetValue = Calculate();
		DecPnt     = 3;
		Unit       = PRESSURE_UNIT2;
		break;
	case SVT_AP_TPRESS_SNS_FAIL    :
	case SVT_AP_LPRESS_SNS_FAIL    :
		MyRetValue = Failure;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AIAirPurgePressSensor::GetStringValue(int ValueId, int Index, AnsiString& MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
	case SVT_AP_TPRESS_SNS_FAIL    :
    case SVT_AP_LPRESS_SNS_FAIL    :
        {
            AnsiString tmpStr;
			Status = AlAirPurgeSensorFailurePtr->GetStringValue(ValueId, Index, tmpStr);
            if ( Status == GETVAL_NO_ERR ) {
                MyString = AnsiString(Failure) + ":" + tmpStr;
            }
        }
        break;
    case SVT_AI_UNIT:
        MyString = GetUnitName(PRESSURE_UNIT2);
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

//---------------------------------------------------------------------------
int AIAirPurgePressSensor::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_AP_TANK_PRESSURE_MB:
    case SVT_AP_LEVEL_PRESSURE_MB:
        NewValue /= MH2O_TO_MBAR;
    case SVT_AP_LEVEL_PRESSURE_MH2O:
        FilteredValue = NewValue;
        ActiveAlarms = CheckAlarms(AlarmSet, &MyHWFailure);
       break;
    case SVT_AP_TPRESS_SNS_FAIL    :
    case SVT_AP_LPRESS_SNS_FAIL    :
        if (NewValue) {
			Failure |= AIR_PURGE_SNS_FAIL;
        }else{
			Failure &= (~AIR_PURGE_SNS_FAIL)&0xff;
        }
        break;
    default:
        Status = AnalogInput::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);

}

//---------------------------------------------------------------------------

float AIAirPurgePressSensor::Calculate(void)
{
    if ( CanCalculate() && !Failure ) {
        // This value should be checked for alarm
        float RawCalcValue = Gain*FilteredValue-Offset;
        if (RawCalcValue < 0.0) {
            RawCalcValue = 0.0;
        }
        CalcValue = RawCalcValue;
        ResultOK  = true;

    }
    return(CalcValue);

}

int AIAirPurgePressSensor::ReceiveData(U8* data)
{
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading*)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2508  *pData = (ANPRO10_COMMAND_2508*) data;
            HWFailure       = pData->HWFailure;
            MyHWFailure     = pData->MyHWFailure;
            ActiveAlarms    = pData->ActiveAlarms;
            FilteredValue   = pData->FilteredValue;
            CalcValue       = pData->CalcValue;
            ResultOK        = pData->ResultOK;
            Failure         = pData->FreeValue;
            // Only check alarm for Master TCU for now
            if ( !CurrentDeviceAddress && CurrentDeviceId == DEVICE_TCU ) {
                CheckAlarms(AlarmSet);
            }

        }
        return(E_OK);
    default:
        return AnalogInput::ReceiveData(data);
    };
}
int AIAirPurgePressSensor::SendData(U16 cmd)
{
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2508  Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;

            Cmd.Data.CommandNo      = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.ndb            = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.HWFailure      = HWFailure;
            Cmd.Data.MyHWFailure    = MyHWFailure;
            Cmd.Data.ActiveAlarms   = ActiveAlarms;
            Cmd.Data.FilteredValue  = FilteredValue;
            Cmd.Data.CalcValue      = CalcValue;
            Cmd.Data.ResultOK       = ResultOK;
            Cmd.Data.FreeValue      = Failure;
            bool sent =ANPRO10SendNormal(&Cmd);
            if ( !sent )
                return(E_QUEUE_FULL);
            else
                return(E_OK);
        }
    default:
        return AnalogInput::SendData(cmd);
    };
}

