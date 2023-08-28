#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIRadarSensorHart::AIRadarSensorHart(void) : AIRadarSensor(C_AI_Radar_Hart) {
    BasicSensorType     = AI_SENSOR_RADAR;
    BasicSensorTypeWord = L_WORD600; //Rad
    Location            = C_AI_LOC_DECK;
    IOType              = C_IO_MODBUS;
    HartValue           = 0.0;
    HartComErrorCnt     = 0;
}

AIRadarSensorHart::~AIRadarSensorHart(void) {
}


//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AIRadarSensorHart::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString = TabStrX(1, ExtraTabs) + KeyWord(Type) + CrLfStr;
    LocalString += AnalogInput::MakeConfigString();     //common
    LocalString += TabStrX(1, ExtraTabs) + KeyWord(C_AI_END) + CrLfStr;
    LocalString += CrLfStr;

	return (LocalString);
}
//---------------------------------------------------------------------------

bool AIRadarSensorHart::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    AnsiString PROName = "Radar(Hart)";
    if (PROPtr)   PROName += (AnsiString)", for " + PROPtr->Name;
    PROName += ":\n";
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
			if (ErrorLine != EOF) {
                GiveConfigWarning(PROName, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning(PROName, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_START_COMMON:
                AnalogInput::LoadConfigString(ConfigString);
                break;
            case C_AI_END:
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_AI_END));
    if (!MinRange && !MaxRange) {
        MinRange = Distance;
    }

    switch (IOType) {
    case C_IO_AN_ZBHART:
        {
            AlarmmAmpShortCircuit *ShortCircuitPtr  = new AlarmmAmpShortCircuit(this);
            AlarmmAmpOpenLoop     *OpenLoopPtr      = new AlarmmAmpOpenLoop(this,10000); // Was 5000
            AlarmSet.insert(ShortCircuitPtr);
            AlarmSet.insert(OpenLoopPtr);
            // Cover for a BUG in AN-ZBHART up to V7
            //OpenLoopPtr->SetAlarmDelay(10000);
        }
        break;
    case C_IO_MODBUS:
        {
            AlarmHartSensorShortCircuit *AlShortCircuitPtr  = new AlarmHartSensorShortCircuit(this);
            AlarmHartSensorOpenLoop     *AlOpenLoopPtr      = new AlarmHartSensorOpenLoop(this);
            AlarmSet.insert(AlShortCircuitPtr);
            AlarmSet.insert(AlOpenLoopPtr);
        }
        break;
    }
    AlarmHartSensorComError     *AlHartComErrPtr    = new AlarmHartSensorComError(this,HartComErrorCnt);
    AlarmSet.insert(AlHartComErrPtr);
    return (NoError);
}
///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIRadarSensorHart::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_AI_OFFSET   :
        Offset = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, -5.0, 50.0, Offset);
        break;
    case SVT_AI_CALC_VAL :
        Status = AdjustSensor(NewValue, ValUnitId = LENGTH_UNIT, 0.0, 50.0, Local);
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

int  AIRadarSensorHart::GetValue(int ValueId, int Index, float& MyRetValue, int& DecPnt, int& Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_HART_STATUS :
        MyRetValue = Failure & HART_STATUS_COM_ERROR_BIT;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_HART_OPEN_LOOP :
        MyRetValue = Failure & HART_STATUS_OPEN_LOOP_BIT;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_HART_SHORT_CIRCUIT :
        MyRetValue = Failure & SVT_HART_SHORT_CIRCUIT;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_AI_OFFSET   :
        MyRetValue = Offset;
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        break;
    case SVT_HART_RADAR  :
        MyRetValue = HartValue;
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        break;
    case SVT_HART_MA:
        MyRetValue = FilteredValue;
        DecPnt     = 3;
        Unit       = CURRENT_UNIT;
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
    return (Status);
}

int AIRadarSensorHart::GetStringValue(int ValueId, int Index, AnsiString& MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AI_UNIT:
        MyString = GetUnitName(LENGTH_UNIT);
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int AIRadarSensorHart::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_HART_MA:
        FilteredValue = NewValue*CNV_MILIAMP_TO_AMP;
        break;
    case SVT_HART_RADAR:
        HartValue     = NewValue;
         // HartComErr alarm is triggered by Failure status active. So HWFailure is based on mA alarms and HartComError
        ActiveAlarms = CheckAlarms(AlarmSet, &HWFailure);
       break;
    case SVT_HART_OPEN_LOOP:
        if (NewValue) {
            // 0x0xfe as mask to ignore possible Hart com fault
            Failure &= 0xfe;
            Failure |= HART_STATUS_OPEN_LOOP_BIT;
        }else{
            Failure &= (~HART_STATUS_OPEN_LOOP_BIT)&0xff;
        }
        break;
    case SVT_HART_SHORT_CIRCUIT:
        if (NewValue) {
            // 0x0xfe as mask to ignore possible Hart com fault
            Failure &= 0xfe;
            Failure |= HART_STATUS_SHORT_CIRCUIT_BIT;
        }else{
            Failure &= (~HART_STATUS_SHORT_CIRCUIT_BIT)&0xff;
        }
        break;
    case SVT_HART_STATUS:
        if (NewValue == HART_STATUS_COM_ERROR_BIT) {
            // Do not set if HART_STATUS_OPEN_LOOP_BIT or HART_STATUS_SHORT_CIRCUIT_BIT are active
            if (!(Failure & (HART_STATUS_OPEN_LOOP_BIT | HART_STATUS_SHORT_CIRCUIT_BIT))) {
                HartComErrorCnt++;
            }
        }else{
            HartComErrorCnt = 0;
        }
        break;
    case SVT_HART_ERROR_CNT:
        HartComErrorCnt = NewValue;
        break;
    default:
        Status = AnalogInput::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);

}


int AIRadarSensorHart::ReceiveData(U8 *data) {
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch (pCH->CommandNo) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2520  *pData = (ANPRO10_COMMAND_2520 *)data;
            HWFailure       = pData->HWFailure;
            MyHWFailure     = pData->MyHWFailure;
            ResultOK        = pData->ResultOK;
            Failure         = pData->Failure;
            ActiveAlarms    = pData->ActiveAlarms;
            FilteredValue   = pData->FilteredValue;
            CalcValue       = pData->CalcValue;
            HartValue       = pData->HartValue;
            HartComErrorCnt = pData->HartComErrorCnt;
            TimeStamp       = pData->TimeStamp;
        }
        return (E_OK);
    case CMD_GENERIC_STATIC_DATA:
        return AnalogInput::ReceiveData(data);
    default:
        return (E_UNKNOWN_COMMAND);
    };
}
int AIRadarSensorHart::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch (cmd) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            QueueANPRO10_COMMAND_2520  Cmd;
            Cmd.TxInfo.Port             = NULL;
            Cmd.TxInfo.rxAddr           = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId             = DEVICE_BROADCAST_TXU;

            Cmd.Data.CommandNo          = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.ndb                = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.ObjectId           = IDNumber;
            Cmd.Data.HWFailure          = HWFailure;
            Cmd.Data.MyHWFailure        = MyHWFailure;
            Cmd.Data.Failure            = Failure;
            Cmd.Data.ActiveAlarms       = ActiveAlarms;
            Cmd.Data.FilteredValue      = FilteredValue;
            Cmd.Data.CalcValue          = CalcValue;
            Cmd.Data.HartValue          = HartValue;
            Cmd.Data.HartComErrorCnt    = HartComErrorCnt;
            Cmd.Data.ResultOK           = ResultOK;
            Cmd.Data.TimeStamp          = TimeStamp;

            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        ErrorStatus =  AnalogInput::SendData(cmd);
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
    };
    return ErrorStatus;
  
}

float AIRadarSensorHart::Calculate(void) {
    if (CanCalculate() && !Failure) {
        // This value should be checked for alarm
        float RawCalcValue = Gain * HartValue - Offset;
        if (RawCalcValue < 0.0) {
            RawCalcValue = 0.0;
        }
        CalcValue = RawCalcValue;
        ResultOK  = true;

    }
    return (CalcValue);

}


void AIRadarSensorHart::SetNewStatus(bool NewStatus) {
    Failure = NewStatus;
}

void AIRadarSensorHart::NewValue(float NewValue) {
    HWFailure = false;
    HartValue = NewValue;
}
