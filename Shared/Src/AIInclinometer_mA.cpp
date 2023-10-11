#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIInclinometer_mA::AIInclinometer_mA(int SnsType) : AIInclinometer(SnsType) {
    AlarmmAmpShortCircuit    *ShortCircuitPtr             = new AlarmmAmpShortCircuit(this);
    AlarmmAmpOpenLoop        *OpenLoopPtr                 = new AlarmmAmpOpenLoop(this);
    AlarmInclinometerFailure *AlarmInclinometerFailurePtr = new AlarmInclinometerFailure(this);
    AlarmSet.insert(ShortCircuitPtr);
    AlarmSet.insert(OpenLoopPtr);
    AlarmSet.insert(AlarmInclinometerFailurePtr);

    // Init the other variables
    MaxRange  = 100.0;
    MinRange  = 0.0;
    MakeConstants();
}
//---------------------------------------------------------------------------

AIInclinometer_mA::~AIInclinometer_mA(void) {
}
//---------------------------------------------------------------------------

void AIInclinometer_mA::NewValue(float NewVal) {
    SetTimeStamp();
    HWFailure     = false;
    FilteredValue = NewVal;//FilterVal(FilteredValue, NewVal, 1);
}

//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////

void AIInclinometer_mA::MakeConstants(void) {
    a = (MaxRange - MinRange) / (0.02 - 0.004);
    b = MaxRange - a * 0.02;
}

float AIInclinometer_mA::Get_Angle(float Amp) {
    float Angle = a * Amp + b;
    return (Angle);
}
// Should support correction of the inclinometer
float AIInclinometer_mA::Calculate(void) {
    if ( CanCalculate() ) {
        // This value should be checked for alarm
        CalcValue = Gain * Get_Angle(FilteredValue) * Sign / RAD_FACTOR - Offset;
        if ( CalcValue > MaxRange*1.1 || CalcValue < MinRange*1.1 ) {
            Failure = true;
        } else {
            Failure = false;
        }
        ResultOK  = !Failure;
    }
    return (CalcValue);

}


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AIInclinometer_mA::MakeConfigString(int ExtraTabs) {
    AnsiString TabStr1 = AnsiString::StringOfChar('\t', 1 + ExtraTabs);
    AnsiString TabStr2 = AnsiString::StringOfChar('\t', 2 + ExtraTabs);
    AnsiString TabStr3 = AnsiString::StringOfChar('\t', 3 + ExtraTabs);
    AnsiString TabStr4 = AnsiString::StringOfChar('\t', 4 + ExtraTabs);
    AnsiString TabStr5 = AnsiString::StringOfChar('\t', 5 + ExtraTabs);
    AnsiString TabStr6 = AnsiString::StringOfChar('\t', 6 + ExtraTabs);
    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord(Type) + CrLfStr;
    LocalString += AnalogInput::MakeConfigString();  //common
    LocalString += TabStr1 + KeyWord(C_AI_END) + CrLfStr;
    LocalString += CrLfStr;

    return (LocalString);
}
//---------------------------------------------------------------------------

bool AIInclinometer_mA::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning("Inclinometer sensor", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning("Inclinometer sensor", InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_START_COMMON:
                AnalogInput::LoadConfigString(ConfigString);
                break;
            case C_AI_END_COMMON:
            case C_AI_END:
                break;
            case C_AI_SERIALNO:
                {
                    SerialNumber = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_TCU_ADDRESS:
                {
                    TCUAddress = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_AI_END) );
    MakeConstants();
    return (NoError);
}
//---------------------------------------------------------------------------

AnsiString AIInclinometer_mA::GetName(void) {
    AnsiString Loc      = FindDictionaryWord(LocationKWord);
    AnsiString BSnsType = FindDictionaryWord(BasicSensorTypeWord);
    AnsiString tName = Loc + " " + BSnsType;
    return (tName);
}
///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AIInclinometer_mA::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    //switch ( ValueId ) {
    //  default:
    Status = AnalogInput::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
    //      break;
    //}

    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
        Offset = ConvertToSi(NewValue, ValUnitId = ANGLE_UNIT, Status, -15.0, 15.0, Offset);
        break;
    case SVT_AI_CALC_VAL :
        Status = AdjustSensor(NewValue, ValUnitId = ANGLE_UNIT, -15.0, 15.0, Local);
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

int  AIInclinometer_mA::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
        DecPnt     = 2;
        Unit       = ANGLE_UNIT;
        MyRetValue = (float)Offset;
        break;
    case SVT_AI_CALC_VAL :
        DecPnt     = 2;
        Unit       = ANGLE_UNIT;
        MyRetValue = (float)CalcValue;
        break;
    default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AIInclinometer_mA::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_UNIT:
        MyString = GetUnitName(ANGLE_UNIT);
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int AIInclinometer_mA::PutFloatValue(int ValueId, float NewValue) {
    return (AnalogInput::PutFloatValue(ValueId, NewValue));
}

///////////////////////////////////////////////////////////////////
//
// Sensor check methode her, because here we know the application
//
///////////////////////////////////////////////////////////////////
int AIInclinometer_mA::CheckInput(float Operator_Val, int &Action) {
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


int AIInclinometer_mA::ReceiveData(U8 *data) {
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2522  *pData = (ANPRO10_COMMAND_2522 *)data;
            HWFailure       = pData->HWFailure;
            MyHWFailure     = pData->MyHWFailure;
            ResultOK        = pData->ResultOK;
            Failure         = pData->Failure;
            ActiveAlarms    = pData->ActiveAlarms;
            FilteredValue   = pData->FilteredValue;
            CalcValue       = pData->CalcValue;
            UpdateTimeInfo(pData->TimeStampPeriod);
        }
        return (E_OK);
    case CMD_GENERIC_STATIC_DATA:
        return AnalogInput::ReceiveData(data);
    default:
        return (E_UNKNOWN_COMMAND);
    };
}
int AIInclinometer_mA::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            QueueANPRO10_COMMAND_2522  Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;

            Cmd.Data.CommandNo      = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.ndb            = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.HWFailure      = HWFailure;
            Cmd.Data.MyHWFailure    = MyHWFailure;
            Cmd.Data.Failure        = Failure;
            Cmd.Data.ActiveAlarms   = ActiveAlarms;
            Cmd.Data.FilteredValue  = FilteredValue;
            Cmd.Data.CalcValue      = CalcValue;
            Cmd.Data.TimeStampPeriod= TimeStampPeriod;
            Cmd.Data.ResultOK       = ResultOK;

            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        ErrorStatus =  AnalogInput::SendData(cmd);
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    };
    return ErrorStatus;
}


