#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

#define NMAXSQRT 64

//---------------------------------------------------------------------------
float PROInclinometer::TrimValue                = 0.0;
float PROInclinometer::ListValue                = 0.0;
bool  PROInclinometer::HasTrimValue             = false;
bool  PROInclinometer::HasListValue             = false;
PROInclinometer *PROInclinometer::PROInclinPtr  = NULL;

#ifdef S2TXU
TSN_STACKPTR int PROInclinometer::TaskStack[2][256];
TSN_TASK PROInclinometer::TaskHandle[2];
#endif
PROInclinometer::PROInclinometer(void)
{
    IDNumber = (C_PRO_INC << 16 )+1;
    MountedOn = C_INC_PORT;
    PROInclinPtr = this;

    Inc1Sensor      = NULL;
    Inc2Sensor      = NULL;
    TrimSensor      = NULL;
    ListSensor      = NULL;
    HasTrimValue    = false;
    HasListValue    = false;
    FrequencyCalc   = false;
    AddToIOObjectList();
	//clock_t CurrentClock = clock();
    for ( int i=0; i<ROL_LIST_ENTRIES; i++ ) {
        HeelLog[i] = 0.0;
    }
    MaxListS                =  0.0;
    MaxListP                =  0.0;
    MaxBufListP             =  0.0;
    MaxBufListS             =  0.0;
    ListRollFilter          = 10;  // 4 EHSMark Changed 2 June 2021
    AvgRollingPeriod        = 0.0;
    AvgFrequency            = 0.0;
    RollingTimeStart        = 0;
    ListSema                = new ANCriticalSection;
}
//---------------------------------------------------------------------------

PROInclinometer::~PROInclinometer(void)
{
    delete ListSema;
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

void PROInclinometer::WriteConfigToFile(TSNConfigString &ConfigString)
{
    AnsiString LocalString;
    LocalString +=KeyWord(C_PRO_INC)+CrLfStr;
    LocalString += PRogramObjectBase::MakeConfigString();    //common
    LocalString +=TabStr1+KeyWord(C_INC_MOUNTED)+KeyWord(MountedOn)+CrLfStr;
    if ( Inc1Sensor )
        LocalString += Inc1Sensor->MakeConfigString();
    if ( Inc2Sensor )
        LocalString += Inc2Sensor->MakeConfigString();
    LocalString +=KeyWord(C_PRO_END)+CrLfStr;
    LocalString += CrLfStr;
    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

int PROInclinometer::LoadConfigFromFile(TSNConfigString &ConfigString)
{
    SetLineNumber(ConfigString.LineCount);
    bool NoError = true;
    int ErrorLine=0;
    int Key;
    do {
        AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)"Inclinometer"+Name,ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning((AnsiString)"Inclinometer"+Name,InputKeyWord,ConfigString.LineCount);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_PRO_START_COMMON:
                PRogramObjectBase::LoadConfigString(ConfigString);
                break;
            case C_PRO_START_PRO:
                LoadConfigString(ConfigString);
                break;
            case C_INC_MOUNTED:
                {
                    AnsiString temp = ConfigString.NextWord(ErrorLine);
                    if ( !ErrorLine )
                        MountedOn = FindConfigKey(temp);
                    NoError = !ErrorLine;
                }
                break;
            case C_AI_INCLINOMETER:
            case C_AI_INC1_N2:
                if ( Inc1Sensor ) {
                    GiveConfigWarning((AnsiString)"Inclinometer 1 redefined.",ConfigString.LineCount);
                } else {
                    Inc1Sensor = (AIInclinometer*) new AIInclinometerN2(Key);
                    Inc1Sensor->SetPROPtr(this);
                    Inc1Sensor->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput*)Inc1Sensor);
                    FrequencyCalc = true;
                }
                break;
            case C_AI_INC2_N2:
                if ( Inc2Sensor ) {
                    GiveConfigWarning((AnsiString)"Inclinometer 2 redefined.",ConfigString.LineCount);
                } else {
                    Inc2Sensor = (AIInclinometer*)new AIInclinometerN2(Key);
                    Inc2Sensor->SetPROPtr(this);
                    Inc2Sensor->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput*)Inc2Sensor);
                    FrequencyCalc = true;
                }
                break;
            case C_AI_INC1_MACRON:
                if ( Inc1Sensor ) {
                    GiveConfigWarning((AnsiString)"Inclinometer 1 redefined.",ConfigString.LineCount);
                } else {
                    Inc1Sensor = (AIInclinometer*) new AIInclinometer_mA(Key);
                    Inc1Sensor->SetPROPtr(this);
                    Inc1Sensor->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput*)Inc1Sensor);
                }
                break;
            case C_AI_INC2_MACRON:
                if ( Inc2Sensor ) {
                    GiveConfigWarning((AnsiString)"Inclinometer 2 redefined.",ConfigString.LineCount);
                } else {
                    Inc2Sensor = (AIInclinometer*) new AIInclinometer_mA(Key);
                    Inc2Sensor->SetPROPtr(this);
                    Inc2Sensor->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput*)Inc2Sensor);
                }
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_PRO_END ) );
    CopyAnalogList();

    AddSensorAlarms();

#ifndef ANCONF
    switch ( MountedOn ) {
    case C_INC_FORWARD:
        TrimSensor = Inc2Sensor;
        ListSensor = Inc1Sensor;
        if ( TrimSensor ) TrimSensor->SetSign( 1.0);
        if ( ListSensor ) ListSensor->SetSign( 1.0);
        break;
    case C_INC_AFT:
        TrimSensor = Inc2Sensor;
        ListSensor = Inc1Sensor;
        if ( TrimSensor ) TrimSensor->SetSign(-1.0);
        if ( ListSensor ) ListSensor->SetSign(-1.0);
        break;
    case C_INC_PORT:
        TrimSensor = Inc1Sensor;
        ListSensor = Inc2Sensor;
        if ( TrimSensor ) TrimSensor->SetSign( 1.0);
        if ( ListSensor ) ListSensor->SetSign(-1.0);
        break;
    case C_INC_STARBOARD:
        TrimSensor = Inc1Sensor;
        ListSensor = Inc2Sensor;
        if ( TrimSensor ) TrimSensor->SetSign(-1.0);
        if ( ListSensor ) ListSensor->SetSign( 1.0);
        break;
    }
    if ( TrimSensor ) {
        TrimSensor->Location        = C_AI_LOC_INC_TRIM;
        TrimSensor->SetLocationKeyWord(L_WORD460);
    }
    if ( ListSensor ) {
        ListSensor->Location        = C_AI_LOC_INC_LIST;
        ListSensor->SetLocationKeyWord(L_WORD461);
    }
#endif
    return ErrorLine;

}


///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PROInclinometer::SaveSettings(TSNConfigString *SettingsString)
{
    if ( IsModified || WriteAll ) {
        IsModified = false;
        AnsiString LocalString;
        LocalString +=KeyWord(C_PRO_INC)+CrLfStr;

        if ( Inc1Sensor ) LocalString += Inc1Sensor->SaveAISettings();
        if ( Inc2Sensor ) LocalString += Inc2Sensor->SaveAISettings();
        LocalString +=KeyWord(C_PRO_END)+CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PROInclinometer::RestoreSettings(TSNConfigString *SettingsString)
{
    bool NoError = true;
    int ErrorLine=0;
    int Key;
    do {
        AnsiString InputKeyWord= SettingsString->NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                RestoreSettingsWarning((AnsiString)"Inclinometer "+Name+":\nUnknown error started at line:"+(AnsiString)ErrorLine+NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"Inclinometer "+Name+":\nThe keyword " + InputKeyWord +" is not allowed here!! Line:"+(AnsiString)SettingsString->LineCount+NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_CT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case C_AI_INC1_N2:
            case C_AI_INC2_N2:
                {
                    int AIIDNumber = SettingsString->ReadInteger(ErrorLine);
                    AnalogInput *AnalogInPtr = (AnalogInput*)FindObject(AIIDNumber);
                    if ( AnalogInPtr ) AnalogInPtr->RestoreAISettings(SettingsString);
                }
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_PRO_END ) );
    return(NoError);
}


//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int PROInclinometer::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_TRIM_M  :
        if ( TrimSensor ) {
            Unit   = LENGTH_UNIT;
            DecPnt = 2;
            float TrimDeg = TrimSensor->Calculate();
            if ( TrimSensor->ResultOK ) {
                MyRetValue = TrimDeg*PROProjectInfo::LengthBetweenPP;
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_TRIM_MARKS_M  :
        if ( TrimSensor ) {
            Unit   = LENGTH_UNIT;
            DecPnt = 2;
            float TrimDeg = TrimSensor->Calculate();
            if ( TrimSensor->ResultOK ) {
                MyRetValue = TrimDeg*PROProjectInfo::LengthBetweenMarks;
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_TRIM_ANGLE:
        if ( TrimSensor ) {
            Status = TrimSensor->GetValue(SVT_AI_CALC_VAL,Index, MyRetValue,  DecPnt,Unit);
        }
        break;
    case SVT_LIST_M  :
        if ( ListSensor ) {
            Unit   = LENGTH_UNIT;
            DecPnt = 2;
            float ListDeg = ListSensor->Calculate();
            if ( ListSensor->ResultOK ) {
                MyRetValue = ListDeg*PROProjectInfo::Width;
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_LIST_ANGLE:
        if ( ListSensor ) {
            Status = ListSensor->GetValue(SVT_AI_CALC_VAL, Index, MyRetValue,  DecPnt,Unit);
        }
        break;
    case SVT_ROLLING_PERIOD:
        Unit        = SECOND_UNIT;
        DecPnt      = 2;
        MyRetValue  = AvgRollingPeriod;
        break;
    case SVT_LIST_MAX_P:
        Unit        = ANGLE_UNIT;
        DecPnt      = 2;
        MyRetValue  = MaxListP;
        break;
    case SVT_LIST_MAX_S:
        Unit        = ANGLE_UNIT;
        DecPnt      = 2;
        MyRetValue  = MaxListS;
        break;
    case SVT_LIST_BUF_MAX_P:
        Unit        = ANGLE_UNIT;
        DecPnt      = 2;
        MyRetValue  = MaxBufListP;
        break;
    case SVT_LIST_BUF_MAX_S:
        Unit        = ANGLE_UNIT;
        DecPnt      = 2;
        MyRetValue  = MaxBufListS;
        break;
    case SVT_ROLLING_FREQUENCY:
        Unit        = FREQUENCY_UNIT;
        DecPnt      = 2;
        MyRetValue  = AvgFrequency;
        break;
    default:
        Status = PRogramObject::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
        break;
    }
    return(Status);
}

int PROInclinometer::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //  default:
    Status = PRogramObject::GetStringValue(ValueId,Index, MyString);
    //      break;
    //}
    return(Status);
}

int PROInclinometer::GetFloatValue(int ValueId, int Index, float &MyValue) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_ROLLING_PERIOD:
        MyValue  = AvgRollingPeriod;
        if (HWFailure) {
             Status     = GETVAL_HW_ALARM;
         }
        break;
    default:
        Status = PRogramObject::GetFloatValue(ValueId, Index, MyValue);
        break;
    }
    return (Status);
}

int PROInclinometer::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status=E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_TRIM_M  :
        if ( TrimSensor ) {
            ValUnitId = LENGTH_UNIT;
            float NewTrim = ConvertToSi(NewValue, LENGTH_UNIT, Status,-10.0 ,5.0,0.0);
            if ( Status == E_NO_ERR ) {
                NewTrim /= PROProjectInfo::LengthBetweenPP;
                Status = TrimSensor->AdjustSensorF(NewTrim,Local);
            }
        }
        break;
    case SVT_TRIM_MARKS_M  :
        if ( TrimSensor ) {
            ValUnitId = LENGTH_UNIT;
            float NewTrim = ConvertToSi(NewValue, LENGTH_UNIT, Status,-10.0 ,5.0,0.0);
            if ( Status == E_NO_ERR ) {
                NewTrim /= PROProjectInfo::LengthBetweenMarks;
                Status = TrimSensor->AdjustSensorF(NewTrim,Local);
            }
        }
        break;
    case SVT_TRIM_ANGLE:
        if ( TrimSensor ) {
            Status = TrimSensor->PutValue(SVT_AI_CALC_VAL, Index,NewValue,Local,&ValUnitId);
        }
        break;
    case SVT_LIST_M  :
        if ( ListSensor ) {
            ValUnitId = LENGTH_UNIT;
            float NewList = ConvertToSi(NewValue, LENGTH_UNIT, Status,-10.0 ,10.0,0.0);
            NewList /= PROProjectInfo::Width;
            Status = ListSensor->AdjustSensorF(NewList,Local);
        }
        break;
    case SVT_LIST_ANGLE:
        if ( ListSensor ) {
            Status = ListSensor->PutValue(SVT_AI_CALC_VAL, Index,NewValue,Local,&ValUnitId);
        }
        break;
    default:
        Status = PRogramObject::PutValue( ValueId, Index,NewValue,Local,&ValUnitId);
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

int PROInclinometer::PutFloatValue( int ValueId, float NewValue)
{
    int Status = E_NO_ERR;
    switch ( ValueId ) {
    case SVT_RESET_MAX_LIST:
        if ( NewValue ) {
            MaxListP = 0.0;
            MaxListS = 0.0;
        }
        break;
    case SVT_LIST_ROLL_FILTER:
        ListRollFilter = NewValue;
        break;
    case SVT_LIST_MAX_P:
        if ( NewValue ) {
            MaxListP = 0.0;
        }
        break;
    case SVT_LIST_MAX_S:
        if ( NewValue ) {
            MaxListS = 0.0;
        }
        break;
    default:
        Status = PRogramObject::PutFloatValue(ValueId,NewValue);
        break;
    }
    return(Status);
}

ValueList *PROInclinometer::GetValueInfoTableStatic(int &Entries, int Index)
{
    Entries = 0;
    return(NULL);
}




////////////////////////////////////////////////////////////////////
//
//  Calculations

#define SEIKA_SENSITIVITY double(5.07e-3)
#pragma diag_suppress=Pa082
void PROInclinometer::Calculate(void)
{
#ifdef S2TXU
    HWFailure = false;
    if ( TrimSensor ) {
        TrimValue    = TrimSensor->Calculate();
        CheckAlarms(TrimSensor->AlarmSet,&TrimSensor->MyHWFailure);
        TrimSensor->SendData();
        HasTrimValue = TrimSensor->ResultOK;
    }

    if ( ListSensor ) {
        if ( FrequencyCalc ) {
            static double tmpHeelLog[ROL_LIST_ENTRIES + 1];
            ListValue    = ListSensor->Calculate();
            CheckAlarms(ListSensor->AlarmSet);
            ListSensor->SendData();
            HasListValue = ListSensor->ResultOK;
            ListSema->Acquire();
            memcpy(tmpHeelLog,HeelLog,ROL_LIST_ENTRIES*sizeof(double));
            ListSema->Release();

            double MaxS = 0.0;
            double MaxP = 0.0;
            for ( int i=0; i < ROL_LIST_ENTRIES-1; i++ ) {
                if ( tmpHeelLog[i] < 0.0  ) {
                    MaxP = min(MaxP, tmpHeelLog[i]);
                } else if ( tmpHeelLog[i] > 0.0 ) {
                    MaxS = max(MaxS, tmpHeelLog[i]);
                }
            }
            MaxBufListS = MaxS;
            MaxBufListP = MaxP;
            double DiffAngle = abs(MaxS-MaxP);
            if ( DiffAngle > ROL_MIN_FREQ_CALC_ANGLE ) {
                if ( !RollingTimeStart ) {
                    RollingTimeStart = OS_Time;
                } else if ( OS_Time - RollingTimeStart > ROL_LIST_ENTRIES*ROL_LIST_LOG_INTERVAL ) {
                    static int ip[NMAXSQRT + 2];
                    static double w[ROL_LIST_ENTRIES * 5 / 4];

                    ip[0] = 0;
                    rdft(ROL_LIST_ENTRIES, 1, tmpHeelLog, ip, w);
                    double Sum = 0.0;
                    for ( int i=1; i < ROL_LIST_ENTRIES/2; i++ ) {
                        Sum += tmpHeelLog[2*i+1];
                    }
                    double Average = Sum / (ROL_LIST_ENTRIES/2);
                    for ( int i=1; i < ROL_LIST_ENTRIES/2; i++ ) {
                        w[i] = abs(tmpHeelLog[2*i+1]-Average);
                    }
                    double Frequency = FindFrequencey(1,ROL_LIST_ENTRIES/2,ROL_LIST_ENTRIES/2,w)/double(ROL_LIST_ENTRIES/2.0);
                    if ( Frequency > double(1.0/60.0) && Frequency < double(1.0/5.0)) {
                        AvgFrequency = FilterVal(AvgFrequency,Frequency,ListRollFilter);
                        AvgRollingPeriod = 1/AvgFrequency;
                    }
                } else {
                    AvgRollingPeriod = 0.0;
                    AvgFrequency     = 0.0;
                }
            } else {
                AvgRollingPeriod = 0.0;
                AvgFrequency     = 0.0;
                RollingTimeStart = 0;
            }
        }else{ // End if FrequencyCalc
            ListValue    = ListSensor->Calculate();
            CheckAlarms(ListSensor->AlarmSet);
            ListSensor->SendData();
            HasListValue = ListSensor->ResultOK;
        }

    }
    SendData();
#endif
}


int PROInclinometer::ReceiveData(U8* data)
{
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading*)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2710  *pData = (ANPRO10_COMMAND_2710*) data;
            ErrorStatus     =  E_OK;
            TrimValue       = pData->Trim;
            ListValue       = pData->List;
            AvgRollingPeriod= pData->RolPeriod;
            AvgFrequency    = pData->RolFrequency;
            MaxBufListS     = pData->MaxS;
            MaxBufListP     = pData->MaxP;
        }
        break;
    case CMD_GENERIC_STATIC_DATA :
        {
            //ANPRO10_COMMAND_2711  *pData = (ANPRO10_COMMAND_2711*) data;
            ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return(ErrorStatus);
}

int PROInclinometer::SendData(U16 cmd)
{
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            QueueANPRO10_COMMAND_2710 Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;

            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.ndb            = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo      = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.Trim           = TrimValue;
            Cmd.Data.List           = ListValue;
            Cmd.Data.RolPeriod      = AvgRollingPeriod;
            Cmd.Data.RolFrequency   = AvgFrequency;
            Cmd.Data.MaxP           = MaxBufListP;
            Cmd.Data.MaxS           = MaxBufListS;
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) {
                ErrorStatus =  E_QUEUE_FULL;
            } else {
                ErrorStatus =  E_OK;
            }
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        /*
        {
            QueueANPRO10_COMMAND_2711 Cmd;

            Cmd.TxInfo.Port    = NULL;
            Cmd.TxInfo.rxAddr  = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId    = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId  = IDNumber;
            Cmd.Data.ndb       = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo = CMD_GENERIC_STATIC_DATA;
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) {
                ErrorStatus =  E_QUEUE_FULL;
            } else {
                ErrorStatus =  E_OK;
            }
        }
        */
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return(ErrorStatus);
}

#ifdef S2TXU
void PROInclinometer::LogList(void)
{
    int NextTime = OS_Time;
    while ( true ) {
        NextTime += ROL_LIST_LOG_INTERVAL;
        double Heel = ListSensor->CalculateRaw();
        ListSema->Acquire();
        memmove(&HeelLog[0],&HeelLog[1], sizeof(double)*(ROL_LIST_ENTRIES-1));
        HeelLog[ROL_LIST_ENTRIES-1] = Heel;
        ListSema->Release();
        OS_DelayUntil(NextTime);
    }
}

void PROInclinometer::LogListTask(void)
{
    OS_Delay(5000);
    if ( PROInclinPtr && PROInclinPtr->ListSensor ) {
        PROInclinPtr->LogList();
    }else{
        OS_Terminate(0);
    }
}

void PROInclinometer::RecIncData(void)
{
    IncMessage Msg;
    while ( true ) {
        OS_GetMail(&IncMailBox,&Msg);
        if ( FrequencyCalc ) {
            double TotalCount = double(Msg.IncCntUp) + double(Msg.IncCntDown);
            if ( TotalCount > double(10000.0) ) {
                double tH       = double(Msg.IncCntDown)/TotalCount;
                double tL       = double(Msg.IncCntUp)/TotalCount;
                double Diff     = tL - tH;
                if ( Diff ) {
                    float IncAngle = double(1.0/SEIKA_SENSITIVITY)*Diff;
                    switch ( Msg.IncNum ) {
                    case 1:
                        if ( Inc1Sensor ) {
                            Inc1Sensor->NewValue(IncAngle);
                        }
                        break;
                    case 2:
                        if ( Inc2Sensor ) {
                            Inc2Sensor->NewValue(IncAngle);
                        }
                        break;
                    }
                }
            }
        }
    }
}

void PROInclinometer::RecIncDataTask(void)
{
    if ( PROInclinPtr && PROInclinPtr->ListSensor ) {
        PROInclinPtr->RecIncData();
    }else{
        OS_Terminate(0);
    }
}
#endif
