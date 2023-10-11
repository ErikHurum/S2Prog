#include "TSNIncludes.h"
#ifdef ANWIN
	#include "LiteCall.hpp"
    #include "LiteAccess.hpp"
    #pragma hdrstop
    #include "MainUnit.h"
#endif
 
#pragma hdrstop

#include <ctime>
#include "PROTankWashingMachine.h"
//---------------------------------------------------------------------------
#ifdef ANWIN
    #pragma package(smart_init)
#endif


set<PRogramObjectBase *>PROTankWashingMachine::ObjectSet;
vector<PRogramObjectBase *>PROTankWashingMachine::AllObjVector;
vector<PROTankWashingMachine *>PROTankWashingMachine::AllTankWashingMachinesVector;
const int PROTankWashingMachine::ValueNameList_Length = 1;

#if defined(ANWIN)
    #define PRO_TANK_WASHING_MACHINE_VALUE_NAME_LIST_LENGTH 1
#endif


/// Maps this object's values to column names
#if defined(S2TXU) || defined(ANTDUSIM)
ValueList PROTankWashingMachine::ValueNameList[PROTankWashingMachine::ValueNameList_Length] = {
#else
ValueList PROTankWashingMachine::ValueNameList[PRO_TANK_WASHING_MACHINE_VALUE_NAME_LIST_LENGTH] = {
#endif
    { L_WORD391, 0, SVT_TWM_ON_OFF_STATUS }
};

/// Init new object
/// @param id Tank Washing Machine id
/// @param tankId Cargo tank id
///
PROTankWashingMachine::PROTankWashingMachine(int tankId, AnsiString TankName)
	: PROXRefObject(true) {
    ObjectSet.insert(this);
    AllObjVector.push_back(this);
    AllTankWashingMachinesVector.push_back(this);


    // IDCheck done in TankWashingAPI.cpp, LoadTankWashingMachineConfigString
    IDNumber 	           = (C_PRO_TANK_WASH_MACHINE << 16) | (ObjectSet.size() & 0xFFFF);;
    Type   		           = C_PRO_TANK_WASH_MACHINE;
    twm.TankId	           = tankId;
    twm.TankName           = TankName;
	Speed                  = 0.0;
    serialId               = AnsiString();
    machineStatus          = tcmos_idle;
	RunningTimeStart       = 0;
    TotalRunningTime       = 0;
    IdleTimeStart          = 0;
    TotalIdleTime          = 0;
    RunningTime            = 0;
    TCMLowSpeedPtr         = new AlarmTCMLowSpeed(this);
    TCMPresetTimePassedPtr = new AlarmTCMPresetTimePassed(this);
    AlarmSet.insert(TCMLowSpeedPtr);
    AlarmSet.insert(TCMPresetTimePassedPtr);
    AddAlarms(CompleteAlarmInfoList);
}

//---------------------------------------------------------------------------


PROTankWashingMachine::~PROTankWashingMachine(void) {
    // Should delete from set and
    if ( AllTankWashingMachinesVector.size() > 0 ) {
        AllTankWashingMachinesVector.clear();          // Don't need to delete objects, they are deleted on TankWashingMachineVector deconstruction
    }
}





///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
void PROTankWashingMachine::WriteConfigToFile(TSNConfigString &ConfigString) {
    AnsiString LocalString;
    AnsiString IdNumStr;
    IdNumStr.cat_sprintf("0x%0x", IDNumber);
    LocalString += KeyWord(TWM_TANK_WASHING_MACHINE) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PRO_ID_NUMBER) + IdNumStr + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PRO_NAME) + Name + CrLfStr;
    LocalString += TabStr1 + KeyWord(TWM_SERIAL_ID) + twm.SerialId + CrLfStr;
    LocalString += TabStr1 + KeyWord(TWM_MACHINE_TYPE_ID) + AnsiString(twm.MachineTypeId) + CrLfStr;
    LocalString += TabStr1 + KeyWord(TWM_NOZZLE_DIAMETER_MM) + AnsiString(twm.NozzleDiameter_mm) + CrLfStr;
    LocalString += TabStr1 + KeyWord(TWM_NUMBER_OF_NOZZLES) + AnsiString(twm.NumberOfNozzles) + CrLfStr;
    LocalString += TabStr1 + KeyWord(TWM_GEAR_RATIO) + FloatToAnsiString(twm.GearRatio, 6, 3) + CrLfStr;

    for ( unsigned i = 0; i < AllAnalogInList.size(); i++ ) {
        LocalString += AllAnalogInList[i]->MakeConfigString();          //common
    }
    LocalString += CrLfStr;
    LocalString += KeyWord(TWM_END_TANK_WASHING_MACHINE) + CrLfStr;
    LocalString += CrLfStr;
    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------




int PROTankWashingMachine::LoadConfigFromFile(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    AnsiString PROName = "Tank Washing Machine";
    bool NoError        = true;
    int ErrorLine       = 0;
    int Key;

    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)PROName, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning((AnsiString)PROName + Name, InputKeyWord, ConfigString.LineCount);
                break;
            case C_PRO_NAME     :
			case TWM_IDENTIFIER :
                Name = ConfigString.NextWord(ErrorLine);
                if ( !ErrorLine ) {
                    twm.Identifier = Name;
                }
                break;
            case C_PRO_ID_NUMBER:
                IDNumber = (unsigned)ConfigString.ReadInteger(ErrorLine);

                if ( !ErrorLine ) {
                    // Check and correct IDNumber if incorrect
                    if ( IDNumber >> 16 != C_PRO_TANK_WASH_MACHINE ) {
                        twm.IDNumber = unsigned(IDNumber);
                        AnsiString warning = "Tank washing machine IDNumber not correct";
                        GiveConfigWarning(warning, ErrorLine);
                    } else {
                        twm.IDNumber = (unsigned)IDNumber;
                    }
                }
                break;
            case TWM_NOZZLE_DIAMETER_MM:
                twm.NozzleDiameter_mm = ConfigString.ReadInteger(ErrorLine);
                break;
            case TWM_SERIAL_ID:
                twm.SerialId = ConfigString.NextWord(ErrorLine);
               break;
            case TWM_MACHINE_TYPE_ID:
                twm.MachineTypeId = (int)ConfigString.ReadInteger(ErrorLine);
                break;
            case C_AI_WashTrackSensor:
			case C_AI_WashTrackSensor2:
                WashTrackSnsPtr = new AiWashTrackSensor;
                NoError =  WashTrackSnsPtr->LoadConfigString(ConfigString);
                if ( NoError ) {
                    AnalogInList.push_back((AnalogInput *)WashTrackSnsPtr);
					twm.SerialId = WashTrackSnsPtr->SerialNumber;
                    WashTrackSnsPtr->SetPROPtr(this);
				}
                break;
            case TWM_NUMBER_OF_NOZZLES:
                twm.NumberOfNozzles = ConfigString.ReadInteger(ErrorLine);
                break;
            case TWM_GEAR_RATIO:
				twm.GearRatio = ConfigString.ReadDouble(ErrorLine);
                break;
            case TWM_END_TANK_WASHING_MACHINE:
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != TWM_END_TANK_WASHING_MACHINE) );
    if ( NoError ) {
        if ( Name.IsEmpty() ) {
            AnsiString warning = "Tank washing machine Name not declared";
            GiveConfigWarning(warning, ConfigString.LineCount);
        } else {
            if ( WashTrackSnsPtr ) {
                //WashTrackSnsPtr->Name = Name;
            } else {
                AnsiString warning = "Tank washing sensor not declared for " + Name;
                GiveConfigWarning(warning, ConfigString.LineCount);
            }

			if ( !twm.NumberOfNozzles ) {
				AnsiString warning = "Number of nozzles not declared for " + Name;
				GiveConfigWarning(warning, ConfigString.LineCount);
			}
			if ( !twm.NozzleDiameter_mm ) {
				AnsiString warning = "Nozzle diameter not declared for " + Name;
				GiveConfigWarning(warning, ConfigString.LineCount);
			}
			if ( !twm.GearRatio ) {
				 AnsiString warning = "Gear ratio not declared for " + Name;
				 GiveConfigWarning(warning, ConfigString.LineCount);
            }
#ifdef ANWIN
            TankWashingAPI twmAPI;
			NoError = twmAPI.InitTWMinDatabase(twm);
#endif
        }
    }
    return (NoError);
}
/*
void PROTankWashingMachine::SetProList(void)
{
}


void PROTankWashingMachine::SetAllProList(void)
{
    set<PRogramObjectBase*>::iterator pBIt;
    for ( pBIt=ObjectSet.begin(); pBIt!=ObjectSet.end(); pBIt++ ) {
        ((PROTankWashingMachine*)(*pBIt))->SetProList();
    }
}
*/
///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////
int PROTankWashingMachine::FindPROStatus(AnsiString &MyString) {
    int PROStatus1 = ST_OK;
    int PROStatus2 = ST_OK;

    if ( HWFailure || !IsAvailableNewData() ) {
        PROStatus1 = ST_ERROR;
    }
    if ( PROStatus1 != ST_ERROR ) {
        for ( unsigned i = 0; i < AnalogInList.size() && (PROStatus1 != ST_ERROR); i++ ) {
            PROStatus2 = AnalogInList[i]->FindPROStatus(MyString);
            if ( PROStatus2 > PROStatus1 ) PROStatus1 = PROStatus2;
        }
    }
    if ( PROStatus1 != ST_ERROR ) {
        bool AlActive = false;
        set<AlarmBasic *>::iterator pBIt;
        for ( pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++ ) {
            AlarmBasic *Element = *pBIt;
            if ( Element && (Element->State != AlarmBasic::AlIdle) ) AlActive = true;
        }
        if ( AlActive )	PROStatus2 = ST_ALARM;
        if ( PROStatus2 > PROStatus1 ) PROStatus1 = PROStatus2;
    }
    MyString = FindStatusChar(PROStatus1);
    return (PROStatus1);
}




int PROTankWashingMachine::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;

    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2140  *pData = (ANPRO10_COMMAND_2140 *)data;
            // pData->NotEmptyTank #### check
            HWFailure     = pData->HWFailure;
            IsNewData     = pData->IsNewData;
            Speed         = pData->Speed;
            machineStatus = (tcm_operation_status)pData->machineStatus;
            RunningTime   = pData->RunningTime;
            ErrorStatus   = E_OK;
        }
#ifdef ANWIN
        if ( machineStatus == tcmos_running ) {
            // Start machine (unless it is already running, the function handles this):
            int newTankWashRunId = 0;
            TankWashingAPI::StartWashingRunIfIdle(IDNumber, newTankWashRunId);
        } else {
            // Stop the machine unless it is already stopped:
            TankWashingAPI::FinishWashingRunIfRunningOrError(IDNumber, false);
        }
#endif
        break;
    case CMD_GENERIC_STATIC_DATA:
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int PROTankWashingMachine::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            QueueANPRO10_COMMAND_2140 Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.ndb            = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo      = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.HWFailure      = HWFailure;
            Cmd.Data.IsNewData      = IsNewData;
            Cmd.Data.machineStatus  = machineStatus;
            Cmd.Data.Speed          = Speed;
            Cmd.Data.RunningTime    = RunningTime;

            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

float PROTankWashingMachine::FilterValue(float FilteredValue, float RawVal, float FilterDegree) {
    return FilteredValue + (RawVal - FilteredValue) / (FilterDegree + 1.0);
}


void PROTankWashingMachine::Calculate(void) {
#ifdef S2TXU
    if ( WashTrackSnsPtr ) {
        Speed = WashTrackSnsPtr->Calculate() / twm.GearRatio;
        if ( OS_GetTime() > 20000 ) {
            time_t Now = time(NULL);
            // Only start if above the speed which will trigger low speed alarm
            if ( Speed > MIN_TWM_SPEED ) {
                if ( machineStatus == tcmos_idle ) {
                    // Start machine (unless it is already running, the function handles this):
                    int newTankWashRunId = 0;
                    TankWashingAPI::StartWashingRunIfIdle(IDNumber, newTankWashRunId);
                    machineStatus = tcmos_running;
                    LibPutValue(SVT_AL_ENABLE, TCMLowSpeedPtr           , "Enabled");
                    LibPutValue(SVT_AL_ENABLE, TCMPresetTimePassedPtr   , "Enabled");
                    TotalRunningTime    = 0;
                    TotalIdleTime       = 0;
                }
                if ( !RunningTimeStart ) {
                    RunningTimeStart = Now;
                }
                if ( IdleTimeStart ) {
                    TotalIdleTime += Now - IdleTimeStart;
                    IdleTimeStart = 0;
                }
                RunningTime = Now - RunningTimeStart + TotalRunningTime;
            } else {
                if ( RunningTimeStart ) {
                    TotalRunningTime += Now - RunningTimeStart;
                    RunningTimeStart = 0;
                }
                if ( !IdleTimeStart ) {
                    IdleTimeStart     = Now;
                }
                if ( machineStatus == tcmos_running ) {
                    switch ( GetPresetTimeAlarmState() ) {
                    case AlarmBasic::AlActive       :
                        LibPutValue(SVT_AL_ENABLE, TCMLowSpeedPtr           , "Disabled");
                        break;
                    case AlarmBasic::AlAknowledged  :
                        // Only stop the machine unless it is already stopped and has reached preset time:
                        TankWashingAPI::FinishWashingRunIfRunningOrError(IDNumber, false);
                        machineStatus = tcmos_idle;
                        // If reached preset time disable relevant alarms
                        LibPutValue(SVT_AL_ENABLE, TCMPresetTimePassedPtr   , "Disabled");
                        LibPutValue(SVT_AL_ENABLE, TCMLowSpeedPtr           , "Disabled");
                        break;
                    default:
                        break;
                    }
                }
            }
            SendData();
        }
    }
#endif
}

int PROTankWashingMachine::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;

    switch ( ValueId ) {
    case SVT_TWM_PRESET_TIME_ENABLE :
        if ( TCMPresetTimePassedPtr ) {
            Status = TCMPresetTimePassedPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local);
            if ( !TCMPresetTimePassedPtr->Enable ) {
                machineStatus = tcmos_idle;
            }
        }
        break;
    case SVT_TWM_LOW_SPEED_ENABLE   :
        if ( TCMLowSpeedPtr ) {
            Status = TCMLowSpeedPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local);
            if ( !TCMLowSpeedPtr->Enable ) {
                machineStatus = tcmos_idle;
            }
        }
        break;
    case SVT_TWM_PRESET_TIME        :
        if ( TCMPresetTimePassedPtr ) {
            Status = TCMPresetTimePassedPtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local);
        }
        break;
    case SVT_TWM_SERIAL_ID:
        serialId = NewValue;
        break;
    default:
        Status = PRogramObject::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
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

int PROTankWashingMachine::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_TWM_SPEED  :
        if ( IsNewData ) {
            DecPnt     = 2;
            Unit       = REVOLUTIONS_UNIT;
            MyRetValue = Speed;
        } else {
            DecPnt     = 2;
            Unit       = REVOLUTIONS_UNIT;
            Status     = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_TWM_PRESET_TIME:
        if ( TCMPresetTimePassedPtr ) {
            Status = TCMPresetTimePassedPtr->GetValue(SVT_AL_LIMIT, Index, MyRetValue, DecPnt, Unit);
        } else {
            Status = GETVAL_ERROR;
        }
        break;
    case SVT_TWM_ON_OFF_STATUS:
        DecPnt      = 0;
        Unit        = NO_UNIT;
        MyRetValue  = (machineStatus == tcmos_running ? 1.0 : 0.0);
        break;
    case SVT_TWM_REMAINING_TIME:
        DecPnt      = 0;
        Unit        = HOUR_UNIT;
        MyRetValue  = GetRemainingRunTime();
        if ( MyRetValue< 0 ) {
            MyRetValue = 0;
        }
        break;
    case SVT_TWM_LOW_SPEED_STATUS:
        DecPnt      = 0;
        Unit        = NO_UNIT;
        MyRetValue  = GetRemainingRunTime();
        if ( MyRetValue< 0 ) {
            MyRetValue = 0;
        }
        break;
    default:
        Status = PRogramObject::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}



int PROTankWashingMachine::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int returnValue = GETVAL_NO_ERR;

    switch ( ValueId ) {
    case SVT_TWM_SERIAL_ID:
        MyString = serialId;
        break;

    case SVT_PRO_STATUS:
        FindPROStatus(MyString);
        break;

    case SVT_TWM_ON_OFF_STATUS:
        if ( machineStatus == tcmos_running /*isMachineOn == true*/ ) {
            //MyString = "ON";
            MyString = FindDictionaryWord(L_WORD3);
        } else {
            //MyString = "OFF";
            MyString = FindDictionaryWord(L_WORD4);
        }
        break;

    default:
        returnValue = PRogramObject::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return returnValue;
}

ValueList* PROTankWashingMachine::GetValueInfoTableStatic(int &Entries, int Index) {
    Entries = ValueNameList_Length;
    return ValueNameList;
}

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PROTankWashingMachine::SaveSettings(TSNConfigString *SettingsString) {

    if (IsModified || WriteAll) {
        IsModified = false;
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", IDNumber);
		LocalString += KeyWord(C_PRO_TANK_WASH_MACHINE) + IdNumStr + CrLfStr;
        set<AlarmBasic *>::iterator pBIt;
        for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
            AlarmBasic *element = *pBIt;
            if (element && !element->Locked) LocalString += (AnsiString)element->SaveSettings();
        }
        /*
        for (unsigned j = 0; j < AnalogInList.size(); j++) {
            if (AnalogInList[j]) LocalString += AnalogInList[j]->SaveAISettings();
        }
        */
        LocalString += KeyWord(C_PRO_END) + CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PROTankWashingMachine::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError   = true;
    int  ErrorLine = 0;
    int  Key;
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                RestoreSettingsWarning((AnsiString)"TWM " + Name + ":\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"TWM " + Name + ":\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case ID_AL_TWM_ELAPSED_TIME:
                if ( TCMLowSpeedPtr	) TCMLowSpeedPtr->RestoreSettings(SettingsString);
                break;
            case ID_AL_TWM_LOW_SPEED:
                if ( TCMPresetTimePassedPtr ) TCMPresetTimePassedPtr->RestoreSettings(SettingsString);
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_PRO_END) );
    return (NoError);
}



time_t PROTankWashingMachine::GetRemainingRunTime(void) {
    if ( TCMPresetTimePassedPtr ) {
        return TCMPresetTimePassedPtr->Limit - RunningTime;
    } else {
        return RunningTime;
    }
}

AlarmBasic::AlarmState PROTankWashingMachine::GetPresetTimeAlarmState(void) {
    if ( TCMPresetTimePassedPtr ) {
        return TCMPresetTimePassedPtr->State;
    }
    return AlarmBasic::AlError;
}

bool PROTankWashingMachine::IsPresetTimeAlarmEnabled(void) {
    if ( TCMPresetTimePassedPtr ) {
        return TCMPresetTimePassedPtr->Enable;
    }
    return false;
}


AlarmBasic::AlarmState PROTankWashingMachine::GetLowSpeedAlarmState(void) {
    if ( TCMLowSpeedPtr ) {
        return TCMLowSpeedPtr->State;
    }
    return AlarmBasic::AlError;
}

bool PROTankWashingMachine::IsLowSpeedAlarmEnabled(void) {
    if ( TCMLowSpeedPtr ) {
        return TCMLowSpeedPtr->Enable;
    }
    return false;
}


int  PROTankWashingMachine::GetGearRatio(void) {
    return twm.GearRatio;
}

int  PROTankWashingMachine::GetNozzleDiameter(void) {
    return twm.NozzleDiameter_mm;
}

int PROTankWashingMachine::GetNumberOfNozzles(void) {
    return twm.NumberOfNozzles;
}

tcm_operation_status PROTankWashingMachine::GetRunningState(void) {
    return machineStatus;
}


//---------------------------------------------------------------------------
