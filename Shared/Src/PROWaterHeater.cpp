#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

vector<PRogramObjectBase *>PROWaterHeater::AllObjVector;
set<PRogramObjectBase *>PROWaterHeater::ObjectSet;
vector<PROWaterHeater *>PROWaterHeater::ObjectVector;

//---------------------------------------------------------------------------


PROWaterHeater::PROWaterHeater(int idNumber, bool addToList)
    : PROXRefObject(true) {
    Initiate(idNumber, addToList);
}
//---------------------------------------------------------------------------


PROWaterHeater::~PROWaterHeater(void) {
    PROXRefObject::~PROXRefObject();
    ObjectSet.erase(this);
    EraseFromVector(AllObjVector, this);
}
//---------------------------------------------------------------------------


void PROWaterHeater::Initiate(int idNumber, bool addToList) {
    if ( addToList ) {
        ObjectSet.insert(this);
        AllObjVector.push_back(this);
        AddToIOObjectList();
    }
    ObjectVector.push_back(this);

    if ( idNumber == 0 ) {
        IDNumber = (C_PRO_WATER_HEATER << 16) + ObjectSet.size();
    } else {
        IDNumber = idNumber;
    }

    Type = C_PRO_WATER_HEATER;
    HasPressure             = false;
    HasInputTemperature     = false;
    HasOutputTemperature    = false;
    ptrPipePressure         = NULL;
    ptrInputTempSensor      = NULL;
    ptrOutputTempSensor     = NULL;
    ManualPressure          = 0.0;
    ManualInputTemp         = 0.0;
    ManualOutputTemp        = 0.0;
    MDO_Efficiency          = WATER_HEATER_DEFAULT_EFFICIENCY;
    MDO_kWh_per_ton         = MDO_KWH_PER_TON;
}
//---------------------------------------------------------------------------


void PROWaterHeater::WriteConfigToFile(TSNConfigString &ConfigString) {

    AnsiString LocalString;
    AnsiString IntNumStr;
    IntNumStr.cat_sprintf("0x%0x", IDNumber);
    LocalString += KeyWord(C_PRO_WATER_HEATER) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PRO_ID_NUMBER) + IntNumStr + CrLfStr;
    LocalString += MakeConfigString();   //common

    LocalString += TabStr1 + KeyWord(C_PRO_WATER_HEATER_INPUT_TEMP      ) + TabStr1 + FloatToAnsiString(ManualInputTemp) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PRO_WATER_HEATER_OUTPUT_TEMP     ) + FloatToAnsiString(ManualOutputTemp) + CrLfStr;

    if ( PROProjectInfo::PressLim_mBar ) {
        LocalString += TabStr1 + KeyWord(C_PRO_WATER_HEATER_PRESSURE    ) + TabStr1 + FloatToAnsiString(ManualPressure/ MH2O_TO_BAR) + CrLfStr;
    }else{
        LocalString += TabStr1 + KeyWord(C_PRO_WATER_HEATER_PRESSURE    ) + TabStr1 + FloatToAnsiString(ManualPressure) + CrLfStr;
    }

    LocalString += TabStr1 + KeyWord(C_PRO_WATER_HEATER_EFFICIENCY      ) + TabStr1 + FloatToAnsiString(MDO_Efficiency) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PRO_WATER_HEATER_FUEL_KWH_PER_TON) + TabStr1 + FloatToAnsiString(MDO_kWh_per_ton) + CrLfStr;

    for ( unsigned i = 0; i < AllAnalogInList.size(); i++ ) {
        LocalString += AllAnalogInList[i]->MakeConfigString();          //common
    }
    LocalString += CrLfStr;
    LocalString += KeyWord(C_PRO_END) + CrLfStr;
    LocalString += CrLfStr;
    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------


int PROWaterHeater::LoadConfigFromFile(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    //HighTempPtr           = new AlarmHighTemp( this);
    //LowTempPtr            = new AlarmLowTemp( this);
    //AlarmSet.insert(HighTempPtr);
    //AlarmSet.insert(LowTempPtr);
    //AddAlarms(CompleteAlarmInfoList);
    AnsiString warningStartText("Water Heater ");
    bool NoError = true;
    int ErrorLine = 0;
    int Key;

    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning(warningStartText + Name, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning(warningStartText + Name, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_PRO_START_PRO:
                PRogramObject::LoadConfigString(ConfigString);
                break;
            case C_XREF_START:
                LoadConfigString(ConfigString);
                break;
            case C_PRO_WATER_HEATER_EFFICIENCY:
                MDO_Efficiency = (float)ConfigString.ReadDouble(ErrorLine);
                break;
            case C_PRO_WATER_HEATER_FUEL_KWH_PER_TON:
                MDO_kWh_per_ton = (float)ConfigString.ReadDouble(ErrorLine);
                break;
            case C_AI_Pt100:
                {
                    AITempSensor_Pt100 *AnalogInPtr = new AITempSensor_Pt100();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_PRO_WATER_HEATER_INPUT_TEMP:
                ManualInputTemp = ConfigString.ReadDouble(ErrorLine);
                if ( ErrorLine ) {
                    GiveConfigWarning(warningStartText + Name, InputKeyWord, ConfigString.LineCount);
                }
                break;
            case C_PRO_WATER_HEATER_OUTPUT_TEMP:
                ManualOutputTemp = ConfigString.ReadDouble(ErrorLine);
                if ( ErrorLine ) {
                    GiveConfigWarning(warningStartText + Name, InputKeyWord, ConfigString.LineCount);
                }
                break;
            case C_PRO_WATER_HEATER_PRESSURE:
                ManualPressure = ConfigString.ReadDouble(ErrorLine);
                if ( ErrorLine ) {
                    GiveConfigWarning(warningStartText + Name, InputKeyWord, ConfigString.LineCount);
                } else if ( PROProjectInfo::PressLim_mBar ) {
                    ManualPressure /= MH2O_TO_BAR;
                }
                break;
            case C_AI_Pt1000:
                {
                    AITempSensor_Pt1000 *AnalogInPtr = new AITempSensor_Pt1000();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_TEMP_mA:
                {
                    AITempSensor_mA *AnalogInPtr = new AITempSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_P906_0110:
            case C_AI_P906_0111:
                if ( ptrPipePressure != NULL ) {
                    GiveConfigWarning(warningStartText + Name, InputKeyWord, ConfigString.LineCount);
                } else {
                    AIPressSensor_mV *AnalogInPtr = new AIPressSensor_mV(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    MaxPressureRange = MAX(AnalogInPtr->MaxRange, MaxPressureRange);
                    AnalogInPtr->Location = C_AI_LOC_VAPOUR;
                    AnalogInPtr->SetIsPressureSns();
//#ifndef ANCONF
                    ////For picture on TDU, no need?
                    //AnalogInList.push_back((AnalogInput*)AnalogInPtr);
                    // This sensor will currently not be visible
                    AITempSensor_Pt1000 *tmpSensor = new AITempSensor_Pt1000(AnalogInPtr);
                    AnalogInList.push_back((AnalogInput *)tmpSensor);
//#endif
                    ptrPipePressure = (AIPressSensor *)AnalogInPtr;
                }
                break;
            case C_AI_ATM_N_Ex:
            case C_AI_ATM_Ex:
            case C_AI_ATM_Ex_H:
            case C_AI_ATM_N_Ex_0_1:
            case C_AI_APT500	  :
            case C_AI_SPT900	  :
            case C_AI_Gen_4_20mA:
                if ( ptrPipePressure != NULL ) {
                    GiveConfigWarning(warningStartText + Name, InputKeyWord, ConfigString.LineCount);
                } else {
                    AIPressSensor_mA *AnalogInPtr = new AIPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    MaxPressureRange = MAX(AnalogInPtr->MaxRange, MaxPressureRange);
                    AnalogInPtr->Location = C_AI_LOC_VAPOUR;
                    AnalogInPtr->SetIsPressureSns();
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    ptrPipePressure = (AIPressSensor *)AnalogInPtr;
                }
                break;
            case C_AI_DIFF_PRESSURE_mA:
                if ( ptrPipePressure != NULL ) {
                    GiveConfigWarning(warningStartText + Name, InputKeyWord, ConfigString.LineCount);
                } else {
                    AIDiffPressSensor_mA *AnalogInPtr = new AIDiffPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    MaxPressureRange = MAX(AnalogInPtr->MaxRange, MaxPressureRange);
                    AnalogInPtr->Location = C_AI_LOC_TANK_CLEAN;
                    AnalogInPtr->SetIsPressureSns();
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    ptrPipePressure = (AIPressSensor *)AnalogInPtr;
                }
                break;

            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_PRO_END) );

    CopyAnalogList();
    AddSensorAlarms();

    // input and output temperature sensor pointers
    for ( unsigned i = 0; i < AnalogInList.size(); i++ ) {
        if ( AnalogInList[i]->Location == C_AI_LOC_TEMP_IN ) {
            ptrInputTempSensor = (AITempSensor *)AnalogInList[i];
        } else if ( AnalogInList[i]->Location == C_AI_LOC_TEMP_OUT ) {
            ptrOutputTempSensor = (AITempSensor *)AnalogInList[i];
        }
    }

    SetChildUserRights();
    PROWaterHeater::AllObjVector.push_back(this);
    PROWaterHeater::ObjectSet.insert(this);
    return ErrorLine;
}
//---------------------------------------------------------------------------


/*bool PROWaterHeater::IsAvailableNewData(void)
{
    return bool(abs(clock() - TimeStamp) < 4*RS485_IO_PERIODE);
}*/
//---------------------------------------------------------------------------

// Must prepare improved logic to support multiple heaters properly
// One thing to correct at that time is HasPressure, HasInputTemperature, OutputTemperatureValue 

void PROWaterHeater::Calculate(void) {
    // Do temperatures
    if ( !AnalogInList.empty() ) {
        if ( ptrPipePressure != NULL ) {
            float tmpPress = ptrPipePressure->Calculate();
            if ( ptrPipePressure->ResultOK ) {
                HasPressure     = true;
                PressureValue   = tmpPress;
            } else {
                PressureValue   = ManualPressure;
            }
        } else {
            HasPressure     = true;
            PressureValue   = ManualPressure;
        }

        if ( ptrInputTempSensor != NULL ) {
            float tmpTemp = ptrInputTempSensor->Calculate();
            if ( ptrInputTempSensor->ResultOK ) {
                HasInputTemperature     = true;
                InputTemperatureValue   = tmpTemp;
            } else {
                InputTemperatureValue   = ManualInputTemp;
            }
        } else {
            HasInputTemperature     = true;
            InputTemperatureValue   = ManualInputTemp;
        }

        if ( ptrOutputTempSensor != NULL ) {
            OutputTemperatureValue = ptrOutputTempSensor->Calculate();
            float tmpTemp = ptrInputTempSensor->Calculate();
            if ( ptrInputTempSensor->ResultOK ) {
                HasInputTemperature  = true;
                HasOutputTemperature = true;
            } else {
                OutputTemperatureValue   = ManualOutputTemp;
            }
        } else {
            HasOutputTemperature    = true;
            OutputTemperatureValue  = ManualOutputTemp;
        }
    } else {
        HasPressure             = true;
        PressureValue           = ManualPressure;
        HasInputTemperature     = true;
        InputTemperatureValue   = ManualInputTemp;
        HasOutputTemperature    = true;
        OutputTemperatureValue  = ManualOutputTemp;
    }

    SendData();
}
///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////
void PROWaterHeater::SaveSettings(TSNConfigString *SettingsString) {
    if (IsModified || WriteAll) {
        IsModified = false;
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", IDNumber);
        LocalString += KeyWord(Type) + IdNumStr + CrLfStr;

        LocalString += TabStr1 + KeyWord(C_PRO_WATER_HEATER_PRESSURE       ) + TabStr2  + FloatToAnsiString(ManualPressure      ) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PRO_WATER_HEATER_INPUT_TEMP     ) + TabStr2  + FloatToAnsiString(ManualInputTemp     ) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PRO_WATER_HEATER_OUTPUT_TEMP    ) + TabStr1  + FloatToAnsiString(ManualOutputTemp    ) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PRO_WATER_HEATER_EFFICIENCY ) + TabStr2  + FloatToAnsiString(MDO_Efficiency ) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PRO_WATER_HEATER_FUEL_KWH_PER_TON   ) + TabStr2  + FloatToAnsiString(MDO_kWh_per_ton       ) + CrLfStr;
        set<AlarmBasic *>::iterator pBIt;
        for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
            AlarmBasic *element = *pBIt;
            if (element && !element->Locked) LocalString += (AnsiString)element->SaveSettings();
        }
        for ( unsigned j = 0; j < AnalogInList.size(); j++ ) {
            if ( AnalogInList[j] ) LocalString += AnalogInList[j]->SaveAISettings();
        }
        LocalString += KeyWord(C_PRO_END) + CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}


      
    
   

  


bool PROWaterHeater::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError   = true;
    int  ErrorLine = 0;
    int  Key;
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                RestoreSettingsWarning((AnsiString)"Temperature " + Name + ":\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"Temperature " + Name + ":\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_CT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case C_PRO_WATER_HEATER_PRESSURE               :
                ManualPressure = SettingsString->ReadDouble(ErrorLine);
                break;
            case C_PRO_WATER_HEATER_INPUT_TEMP      :
                ManualInputTemp = SettingsString->ReadDouble(ErrorLine);
                break;
            case C_PRO_WATER_HEATER_OUTPUT_TEMP     :
                ManualOutputTemp = SettingsString->ReadDouble(ErrorLine);
                break;
            case C_PRO_WATER_HEATER_EFFICIENCY      :
                MDO_Efficiency = SettingsString->ReadDouble(ErrorLine);
                break;
            case C_PRO_WATER_HEATER_FUEL_KWH_PER_TON  		:
                MDO_kWh_per_ton = SettingsString->ReadDouble(ErrorLine);
                break;
            case C_AI_P906_0110 :
            case C_AI_P906_0111 :
            case C_AI_Pt100     :
            case C_AI_Pt1000    :
            case C_AI_TEMP_mA   :
            case C_AI_TEMP_AD590:
                {
                    int         AIIDNumber   = SettingsString->ReadInteger(ErrorLine);
					AnalogInput *AnalogInPtr = (AnalogInput *)FindObject(AIIDNumber);
					if (AnalogInPtr) {
						AnalogInPtr->RestoreAISettings(SettingsString);
					}else{
						RestoreSettingsWarning((AnsiString)"Temperature " + Name + ":\nSensor Id " + AnsiString(AIIDNumber) + " is not found!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
					}
                }
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    return (NoError);
}
//---------------------------------------------------------------------------
int PROWaterHeater::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;

    //HasPressure = true;
    //IsNewData = true;
    switch ( ValueId ) {
    case SVT_PRESSURE                       :
    case SVT_TWM_PRESSURE                   :
        DecPnt     = 1;
        Unit       = PRESSURE_UNIT3;
        MyRetValue = PressureValue;
        break;
    case SVT_TWM_HEATER_INPUT_TEMP          :
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        MyRetValue = InputTemperatureValue;
        break;
    case SVT_TWM_HEATER_OUTPUT_TEMP         :
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        MyRetValue = OutputTemperatureValue;
        break;
    case SVT_TWM_MAN_PRESSURE               :
        DecPnt     = 1;
        Unit       = PRESSURE_UNIT3;
        MyRetValue = ManualPressure;
        break;
    case SVT_TWM_MAN_HEATER_INPUT_TEMP      :
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        MyRetValue = ManualInputTemp;
        break;
    case SVT_TWM_MAN_HEATER_OUTPUT_TEMP     :
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        MyRetValue = ManualOutputTemp;
        break;
    case SVT_TWM_HEATER_EFFICIENCY      :
        DecPnt     = 1;
        Unit       = PERCENT_UNIT;
        MyRetValue = MDO_Efficiency;
        break;
	case SVT_TWM_FUEL_TON_PER_KWH  		:
        DecPnt     = 1;
        Unit       = NO_UNIT;
        MyRetValue = MDO_kWh_per_ton;
        break;
    default:
        Status = PROXRefObject::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int PROWaterHeater::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    default:
        Status = PROXRefObject::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}


int PROWaterHeater::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status    = E_NO_ERR; 
    int ValUnitId = NO_UNIT;

    switch ( ValueId ) {
    case SVT_TWM_MAN_PRESSURE              :
        {
			float NewManualPressure  = ConvertToSi(NewValue, ValUnitId = PRESSURE_UNIT3, Status, 0.0, 15.0/MH2O_TO_BAR, 0.0);
            if (Status == E_NO_ERR) {
                ManualPressure = NewManualPressure;
            }

        }
        break;
    case SVT_TWM_MAN_HEATER_INPUT_TEMP     :
        {
			float NewManualInputTemp  = ConvertToSi(NewValue, ValUnitId = TEMP_UNIT, Status, 0.0, 75.0, 0.0);
            if (Status == E_NO_ERR) {
                ManualInputTemp = NewManualInputTemp;
            }

        }
        break;
    case SVT_TWM_MAN_HEATER_OUTPUT_TEMP    :
        {
            float NewManualOutputTemp  = ConvertToSi(NewValue, ValUnitId = TEMP_UNIT, Status, 0.0, 150, 0.0);
            if (Status == E_NO_ERR) {
                ManualOutputTemp = NewManualOutputTemp;
            }

        }
        break;
    case SVT_TWM_HEATER_EFFICIENCY :
        {
            float NewMDO_Efficiency  = ConvertToSi(NewValue, ValUnitId = PERCENT_UNIT, Status, 0.0, 100.0, 0.0);
            if (Status == E_NO_ERR) {
                MDO_Efficiency = NewMDO_Efficiency;
            }

        }
        break;
    case SVT_TWM_FUEL_TON_PER_KWH   :
        {
            float NewMDO_Ton_per_kWh  = ConvertToSi(NewValue, ValUnitId = NO_UNIT, Status, 0.0, MDO_KWH_PER_TON*1.2, 0.0);
            if (Status == E_NO_ERR) {
                MDO_kWh_per_ton = NewMDO_Ton_per_kWh;
            }

        }
        break;
    default:
        Status = PROXRefObject::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
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






int PROWaterHeater::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2150  *pData = (ANPRO10_COMMAND_2150 *)data;
            HWFailure               = pData->HWFailure;
            IsNewData               = pData->IsNewData;
            PressureValue           = pData->PressureValue;
            InputTemperatureValue   = pData->InputTemperatureValue;
            OutputTemperatureValue  = pData->OutputTemperatureValue;
            HasPressure             = pData->HasPressure;
            HasInputTemperature     = pData->HasInputTemperature;
            HasOutputTemperature    = pData->HasOutputTemperature;
            ErrorStatus             = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            ANPRO10_COMMAND_2151    *pData = (ANPRO10_COMMAND_2151 *)data;
            ManualPressure          = pData->ManualPressure     ;
            ManualInputTemp         = pData->ManualInputTemp    ;
            ManualOutputTemp        = pData->ManualOutputTemp   ;
            MDO_Efficiency          = pData->MDO_Efficiency     ;
            MDO_kWh_per_ton         = pData->MDO_kWh_per_ton    ;
            ErrorStatus             = E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}
//---------------------------------------------------------------------------


int PROWaterHeater::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2150 Cmd;
            Cmd.TxInfo.Port                 = NULL;
            Cmd.TxInfo.rxAddr               = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId                 = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId               = IDNumber;
            Cmd.Data.ndb                    = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo              = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.HWFailure              = HWFailure;
            Cmd.Data.IsNewData              = IsNewData;
            Cmd.Data.PressureValue          = PressureValue;
            Cmd.Data.InputTemperatureValue  = InputTemperatureValue;
            Cmd.Data.OutputTemperatureValue = OutputTemperatureValue;
            Cmd.Data.HasPressure            = HasPressure;
            Cmd.Data.HasInputTemperature    = HasInputTemperature;
            Cmd.Data.HasOutputTemperature   = HasOutputTemperature;

            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2151 Cmd;
            Cmd.TxInfo.Port                 = NULL;
            Cmd.TxInfo.rxAddr               = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId                 = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId               = IDNumber;
            Cmd.Data.ndb                    = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo              = CMD_GENERIC_STATIC_DATA;
            Cmd.Data.ManualPressure         = ManualPressure;  
            Cmd.Data.ManualInputTemp        = ManualInputTemp; 
            Cmd.Data.ManualOutputTemp       = ManualOutputTemp;
            Cmd.Data.MDO_Efficiency         = MDO_Efficiency;
            Cmd.Data.MDO_kWh_per_ton         = MDO_kWh_per_ton      ;
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}
//---------------------------------------------------------------------------


