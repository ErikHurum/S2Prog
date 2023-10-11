#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
PROAtmReference *PROAtmReference::PROAtmRefPtr = NULL;

PROAtmReference::PROAtmReference(bool IsConfig):IsConfigured(IsConfig)
{
    PROAtmRefPtr    = this;
    Type            = C_PRO_ATMREFSENS;
    IDNumber = (C_PRO_ATMREFSENS << 16 )+0;//NumberOfPRO;
    Name            = "Atm";
    UseManual       = true;
    ManualPressure  = AIPressSensor::AtmPressure;
    SensorOnTCU     = true;
    if (IsConfigured) {
        AddToIOObjectList();
    }
    DataTransferSet.insert(this);
}
//---------------------------------------------------------------------------

PROAtmReference::~PROAtmReference(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////


void PROAtmReference::WriteConfigToFile(TSNConfigString &ConfigString)
{
    if ( IsConfigured ) {
        AnsiString LocalString;
        LocalString +=KeyWord(C_PRO_ATMREFSENS)+CrLfStr;
        LocalString += PRogramObjectBase::MakeConfigString();
        if ( SensorOnTCU )
            LocalString +=TabStr1+KeyWord(C_ATM_ON_TCU)+CrLfStr;
        for (unsigned i=0; i < AtmRefSensors.size(); i++) {
            LocalString += AtmRefSensors[i]->MakeConfigString();
        }
        LocalString +=KeyWord(C_PRO_END)+CrLfStr;
        LocalString += CrLfStr;
        ConfigString.AddString(LocalString);
    }
}
//---------------------------------------------------------------------------

int PROAtmReference::LoadConfigFromFile(TSNConfigString &ConfigString)
{
    SetLineNumber(ConfigString.LineCount);
    SensorOnTCU = false;
    bool NoError = true;
    int ErrorLine=0;
    int Key;
    do {
        AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning("Atmospheric reference",ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning("Atmospheric reference",InputKeyWord,ConfigString.LineCount);
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
            case C_ATM_ON_TCU:
                SensorOnTCU = true;
                break;
            case C_AI_P906_0110:
            case C_AI_P906_0111:
                {
                    AIAtmPressSensor_mV *AnalogInPtr = new AIAtmPressSensor_mV(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInPtr->Location = C_AI_LOC_SYSTEM;
                    AtmRefSensors.push_back(AnalogInPtr);
                    AnalogInList.push_back(AnalogInPtr);
                    AnalogInPtr->SetPROPtr(this);
                    // This sensor will currently not be visible
                    AITempSensor_Pt1000 *tmpTempSnsPtr = new AITempSensor_Pt1000(AnalogInPtr);
                    AnalogInList.push_back((AnalogInput*)tmpTempSnsPtr);


                }
                break;
            case C_AI_ATM_N_Ex      :
            case C_AI_ATM_Ex        :
            case C_AI_ATM_Ex_H      :
            case C_AI_ATM_N_Ex_0_1  :
			case C_AI_APT500		:
			case C_AI_SPT900		:
            case C_AI_Gen_4_20mA    :
            case C_AI_DIFF_PRESSURE_mA:
                {
                    AIAtmPressSensor_mA *AnalogInPtr = new AIAtmPressSensor_mA(Key,SensorOnTCU);
                    AnalogInPtr->Location = C_AI_LOC_SYSTEM;
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AtmRefSensors.push_back(AnalogInPtr);
                    AnalogInList.push_back((AnalogInput*)AnalogInPtr);
                }
                break;
            case C_AI_MB_Press_mA   :
                {
                    AIModbusPressSensor_mA *AnalogInPtr = new AIModbusPressSensor_mA(true);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AtmRefSensors.push_back(AnalogInPtr);
                    ModbusSensorSet.insert(AnalogInPtr);
                }
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_PRO_END ) );
    CopyAnalogList();
    if ( !AtmRefSensors.empty() ) {
        UseManual = false;
        AlarmAtmOutOfRange *TmpPtr = new AlarmAtmOutOfRange(this);
        AlarmSet.insert(TmpPtr);
        AddAlarms(CompleteAlarmInfoList);
    }
    AddSensorAlarms();
    return ErrorLine;
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PROAtmReference::SaveSettings(TSNConfigString *SettingsString)
{
    if ( IsModified || WriteAll ) {
        IsModified = false;
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x",IDNumber);
        LocalString +=KeyWord(Type)+IdNumStr+CrLfStr;

        LocalString +=TabStr1+KeyWord(C_ATM_MAN_PRESS)+FloatToAnsiString(ManualPressure)+CrLfStr;
        if ( UseManual ) {
            LocalString +=TabStr1+KeyWord(C_ATM_USEMANUAL)+CrLfStr;
        } else {
            LocalString +=TabStr1+KeyWord(C_ATM_NOT_USEMANUAL)+CrLfStr;
        }

        if ( !AlarmSet.empty() ) {
            set<AlarmBasic*>::iterator pBIt;
            for ( pBIt=AlarmSet.begin(); pBIt!=AlarmSet.end(); pBIt++ ) {
                AlarmBasic *element =*pBIt;
                if ( element ) LocalString +=(AnsiString) element->SaveSettings();
            }
        }
        for (unsigned i=0; i < AtmRefSensors.size(); i++) {
            LocalString += AtmRefSensors[i]->SaveAISettings();
        }
        LocalString +=KeyWord(C_PRO_END)+CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PROAtmReference::RestoreSettings(TSNConfigString *SettingsString)
{
    bool NoError = true;
    int ErrorLine=0;
    int Key;
    UseManual = false;
    do {
        AnsiString InputKeyWord= SettingsString->NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                RestoreSettingsWarning((AnsiString)"AtmRef "+Name+":\nUnknown error started at line:"+(AnsiString)ErrorLine+NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"AtmRef "+Name+":\nThe keyword " + InputKeyWord +" is not allowed here!! Line:"+(AnsiString)SettingsString->LineCount+NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_CT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case C_ATM_MAN_PRESS:
                ManualPressure = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_ATM_USEMANUAL:
                UseManual = true;
                break;
            case C_ATM_NOT_USEMANUAL:
                UseManual = false;
                break;
            case C_AI_P906_0111       :
            case C_AI_ATM_N_Ex        :
            case C_AI_ATM_Ex          :
            case C_AI_ATM_Ex_H        :
            case C_AI_ATM_N_Ex_0_1    :
			case C_AI_APT500		  :
			case C_AI_SPT900		  :
            case C_AI_Gen_4_20mA      :
            case C_AI_DIFF_PRESSURE_mA:
                {
                    int AIIDNumber = SettingsString->ReadInteger(ErrorLine);
                    AnalogInput *AnalogInPtr = (AnalogInput *)FindObject(AIIDNumber);
                    if (AnalogInPtr) AnalogInPtr->RestoreAISettings(SettingsString);
                }
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_PRO_END ) );
    return(NoError);
}

///////////////////////////////////////////////////////////////
//
// Routines for Calculation of values
//
///////////////////////////////////////////////////////////////
void PROAtmReference::Calculate(void)
{
    HWFailure = false;
    if ( !AtmRefSensors.empty() ) {
        if ( UseManual || !AtmRefSensors[0]->Enable ) {
            AIPressSensor::AtmPressure = ManualPressure;
        } else {
            float CurrentPressure = AtmRefSensors[0]->Calculate();
            AtmRefSensors[0]->ActiveAlarms = CheckAlarms(AtmRefSensors[0]->AlarmSet,&AtmRefSensors[0]->MyHWFailure);
            // See if we have one acceptable atmospheric pressure reading.
            // If not override the value and set the sensor status to normal
            if ( AtmRefSensors[0]->ActiveAlarms || ( CurrentPressure < MIN_ATM) || ( CurrentPressure > MAX_ATM ) ) {
                AIPressSensor::AtmPressure  = NORMAL_ATM;
                IsOutOfRange= true;
            } else {
                AIPressSensor::AtmPressure  = CurrentPressure;
                IsOutOfRange= false;
            }
        }
        SendData();
    }else{
         AIPressSensor::AtmPressure = ManualPressure;
         SendData();
    }
}

void PROAtmReference::SimCalculate(void)
{
    if ( UseManual || !AtmRefSensors[0]->Enable ) {
        AIPressSensor::AtmPressure = ManualPressure;
    } else {

        if ( AIPressSensor::AtmPressure < 0.9*NORMAL_ATM ) {
            SimulatorSign = 1.0;
        } else if ( AIPressSensor::AtmPressure > 1.1*NORMAL_ATM ) {
            SimulatorSign = -1.0;
        }
        AIPressSensor::AtmPressure += 0.01*NORMAL_ATM*SimulatorSign;
    }
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////
int PROAtmReference::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_CALC_VAL :
        if ( AtmRefSensors[0] ) {
            Status = AtmRefSensors[0]->GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
    case SVT_PRESSURE     :
    case SVT_ATM_PRESSURE :
        Unit = PRESSURE_UNIT1;
        MyRetValue = AIPressSensor::AtmPressure;
        break;
    case SVT_ATM_P_ENABLE :
        Unit = NO_UNIT;
        MyRetValue = (float)UseManual;
        break;
    case SVT_AI_ENABLE :
        if ( AtmRefSensors[0] ) {
            Status = AtmRefSensors[0]->GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_ATM_TEMP   :
    case SVT_ATM_T_ENABLE :
        break;
    default:
        Status = PRogramObject::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
        break;
    }
    return(Status);
}

int PROAtmReference::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //  default:
    Status = PRogramObject::GetStringValue(ValueId,Index, MyString);
    //      break;
    //}
    return(Status);
}


int PROAtmReference::GetFloatValue(int ValueId, int Index, float &MyValue) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_PRESSURE     :
    case SVT_ATM_PRESSURE :
        MyValue = AIPressSensor::AtmPressure;
        if ( HWFailure ) {
            Status = GETVAL_HW_ALARM;
        }
        break;
    default:
        Status = PRogramObject::GetFloatValue(ValueId, Index, MyValue);
        break;
    }
    return (Status);
}


int PROAtmReference::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status=E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_CALC_VAL :
        if ( !AtmRefSensors.empty() ) {
            Status = AtmRefSensors[0]->PutValue(ValueId, 0,NewValue,Local,&ValUnitId);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_ATM_PRESSURE :
        {
            float Pressure = ConvertToSi(NewValue, ValUnitId=PRESSURE_UNIT1, Status,MIN_ATM ,MAX_ATM,0.0);
            if ( Status == E_NO_ERR ) {
                if ( UseManual ) {
                    ManualPressure = Pressure;
                    AIPressSensor::AtmPressure = ManualPressure;
                } else if ( !AtmRefSensors.empty() ) {
                    Status = AtmRefSensors[0]->PutValue(ValueId, 0,NewValue,Local,&ValUnitId);
                } else {
                    Status = E_INVALID_POINTER;
                }
            } else {
                Status = E_NO_INPUT_PERMISSION;
            }
        }
        break;
    case SVT_ATM_P_ENABLE :
        {
            bool Value =(bool) ConvertToSi(NewValue, NO_UNIT, Status,0 ,1,0.0);
            if ( Status== E_NO_ERR ) {
                UseManual = !Value;
            }
        }
        break;
    case SVT_AI_ENABLE :
        if ( !AtmRefSensors.empty() ) {
            Status = AtmRefSensors[0]->PutValue(ValueId, 0,NewValue,Local,&ValUnitId);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;

    case SVT_ATM_TEMP  :
    case SVT_ATM_T_ENABLE :
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

int PROAtmReference::PutFloatValue( int ValueId, float NewValue)
{
    int Status = E_NO_ERR;
    switch ( ValueId ) {
    case SVT_ATM_PRESSURE :
        ManualPressure = NewValue;
        UseManual      = true;
        //Calculate();
       // SendData();
        break;
    default:
        Status = PRogramObject::PutFloatValue(ValueId,NewValue);
        break;
    }
    return(Status);
}

ValueList *PROAtmReference::GetValueInfoTableStatic(int &Entries, int Index)
{
    Entries = 0;
    return(NULL);
}

int PROAtmReference::ReceiveData(U8* data)
{
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading*)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2740  *pData = (ANPRO10_COMMAND_2740*) data;
            AIPressSensor::AtmPressure = pData->AtmPressure;
            ManualPressure  = pData->ManualPressure;
			UseManual       = pData->UseManual;
            UpdateTimeInfo(pData->TimeStampPeriod);

            ErrorStatus     =  E_UNKNOWN_OBJECT;
            ErrorStatus =  E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            //ANPRO10_COMMAND_2741  *pData = (ANPRO10_COMMAND_2741*) data;
            ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return(ErrorStatus);
}

int PROAtmReference::SendData(U16 cmd)
{
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            QueueANPRO10_COMMAND_2740 Cmd;

            Cmd.TxInfo.Port          = NULL;
            Cmd.TxInfo.rxAddr        = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId          = DEVICE_BROADCAST_TXU;

            Cmd.Data.ObjectId        = IDNumber;
            Cmd.Data.ndb             = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo       = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.AtmPressure     = AIPressSensor::AtmPressure;
            Cmd.Data.ManualPressure  = ManualPressure;
            Cmd.Data.UseManual       = UseManual;
            Cmd.Data.TimeStampPeriod= TimeStampPeriod;
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent )
                ErrorStatus =  E_QUEUE_FULL;
            else
                ErrorStatus =  E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2741 Cmd;

            Cmd.TxInfo.Port           = NULL;
            Cmd.TxInfo.rxAddr         = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId           = DEVICE_BROADCAST_TXU;

            Cmd.Data.ObjectId         = IDNumber;
            Cmd.Data.ndb              = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo        = CMD_GENERIC_STATIC_DATA;
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent )
                ErrorStatus =  E_QUEUE_FULL;
            else
                ErrorStatus =  E_OK;
        }
        break;

    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return(ErrorStatus);
}

void PROAtmReference::RefreshData(int ValueKey)
{
    PRogramObject::RefreshData();
    if ( !IsNewData ) {
        AIPressSensor::AtmPressure  = NORMAL_ATM;
    }
}

