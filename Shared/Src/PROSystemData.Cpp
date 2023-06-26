#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
	#include "MainUnit.h"
#endif

#ifdef S2TXU
    #include "GUITouchConf.h"
extern int TouchScreenTimeOut;
extern OS_TIMER AlarmSilenceTimer;
#else
int                                               TouchScreenTimeOut             = 30000;
#endif


ValueList PROSystemData                           ::ServiceReportSystemValueList[] =  {
    { L_WORD304 , L_WORD237, SVT_BLANK },                                         //  {"Unused"           ,"",SVT_BLANK},
    { L_WORD404 , L_WORD237, SVT_ATM_PRESSURE },                                  //  {"AtmPress"         ,"",SVT_ATM_PRESSURE},
    { L_WORD460 , L_WORD237, SVT_TRIM_M },                                        //  {"Trim"             ,"",SVT_TRIM_M},
    { L_WORD461 , L_WORD237, SVT_LIST_ANGLE },                                    //  {"List"             ,"",SVT_LIST_ANGLE},
    { L_WORD448 , L_WORD237, SVT_LATITUDE },                                      //  {"Latitude"         ,"",SVT_LATITUDE},
    { L_WORD1097, L_WORD237, SVT_SEAWATER_TEMP   },                               //  {"Seawater temp"    ,"",SVT_SEAWATER_TEMP   },
    { L_WORD1098, L_WORD237, SVT_AMBIENT_TEMP},                               //  {"Environment temp" ,"",SVT_AMBIENT_TEMP},
};


PROSystemData *PROSystemData::TXUSystemData                = NULL;
volatile bool  PROSystemData::HasConfigWritePermission     = false;

float PROSystemData::Latitude                     = 51.0;

int   PROSystemData::CurrentUnitSystem            = UNIT_SYS_SI;
int   PROSystemData::CurrentLanguage              = L_ENGLISH;

int   PROSystemData::AlarmOffDelay                = DEFAULT_ALARM_OFF_DELAY;
int   PROSystemData::AlarmOnDelay                 = DEFAULT_ALARM_ON_DELAY;
int   PROSystemData::TrimSource                   = C_SD_INC_SOURCE;
int   PROSystemData::ListSource                   = C_SD_INC_SOURCE;
float PROSystemData::ManualTrim                   = 0.0;
float PROSystemData::ManualList                   = 0.0;
float PROSystemData::TrimValue                    = 0.0;
float PROSystemData::ListValue                    = 0.0;

float PROSystemData::BallastDensity               = DNS_SEA_WATER;
float PROSystemData::SeaWaterDensity              = DNS_SEA_WATER;
float PROSystemData::FreshWaterDensity            = DNS_FRESH_WATER;
float PROSystemData::HeavyFuelDensity             = DNS_HEAVY_FUEL_OIL;
float PROSystemData::DieselDensity                = DNS_DIESEL_OIL;
float PROSystemData::LubricantsDensity            = DNS_LUBRICANTS;
float PROSystemData::SeaWaterTemp                 = DEFAULT_SEA_TEMP;
float PROSystemData::AmbientTemp                  = DEFAULT_SEA_TEMP;

int   PROSystemData::TimeFromGMT                  = 0;
int   PROSystemData::DaylightSaving               = 0;

int   PROSystemData::LogTime                      = 0;
bool  PROSystemData::LogToFile                    = false;
bool  PROSystemData::LogAlarms                    = false;
bool  PROSystemData::LogBallastExchange           = false;
bool  PROSystemData::LogCargo                     = false;
bool  PROSystemData::LogService                   = false;
bool  PROSystemData::LogTemperature               = false;
bool  PROSystemData::LogTankPressure              = false;
bool  PROSystemData::PrinterOnThisTXU             = false;
bool  PROSystemData::ReceiveWeightVolume          = false;


PROSystemData::PROSystemData(void) {
    Name = "SystemData";
    PROSystemData::TXUSystemData = this;
    switch (CurrentDeviceId) {
    case 0: //TCU
        MyTypeId = 0x20;
        MyAddress = 0; // Should be set later
        break;
    case 1: //TDU
        MyTypeId = 0x30;
        MyAddress = 0;
        break;
    default:
        MyTypeId = 0x40;
        MyAddress = 0;   // At the moment 0
        break;
    }
    IDNumber          = (C_PRO_SYSDATA << 16) + 0;
    Type              = C_PRO_SYSDATA;
    LastTimeModified  = time(NULL);
    UserPinCode       = AnsiString(DEFAULT_PIN_CODE);
    CargoVolume       = 0.0;
    CargoWeight       = 0.0;
    BallastVolume     = 0.0;
    BallastWeight     = 0.0;
    HeavyFuelVolume   = 0.0;
    HeavyFuelWeight   = 0.0;
    DieselOilVolume   = 0.0;
    DieselOilWeight   = 0.0;
    LubricantsVolume  = 0.0;
    LubricantsWeight  = 0.0;
    FreshWaterVolume  = 0.0;
    FreshWaterWeight  = 0.0;
    MiscVolume        = 0.0;
    MiscWeight        = 0.0;
    DataTransferSet.insert(this);
}

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PROSystemData::SaveSettings(TSNConfigString *SettingsString) {
    if (IsModified || WriteAll) {
        IsModified = false;
        AnsiString LocalString;
        LocalString += KeyWord(C_PRO_SYSDATA) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_MOD_SYSTEM) + TabStr2 + (AnsiString)((int)time(NULL)) + CrLfStr;
        if (!PROCargoTank::ObjectSet.empty() || !PROBallastTank::ObjectSet.empty() || !PROServiceTank::ObjectSet.empty()) {
            LocalString += TabStr1 + KeyWord(C_SD_TRIM_SOURCE)      + TabStr2 + KeyWord(TrimSource) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_MANUAL_TRIM)      + TabStr2 + FloatToAnsiString(ManualTrim) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_LIST_SOURCE)      + TabStr2 + KeyWord(ListSource) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_MANUAL_LIST)      + TabStr2 + FloatToAnsiString(ManualList) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_BALLAST_DNS)      + TabStr2 + FloatToAnsiString(BallastDensity) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_FRESHWATER_DNS)   + TabStr1 + FloatToAnsiString(FreshWaterDensity) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_HEAVY_FUEL_DNS)   + TabStr1 + FloatToAnsiString(HeavyFuelDensity) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_DIESEL_DNS)       + TabStr2 + FloatToAnsiString(DieselDensity) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_LUBRICANTS_DNS)   + TabStr1 + FloatToAnsiString(LubricantsDensity) + CrLfStr;
            if (PRODraftSystem::PRODraftSysPtr) {
                LocalString += TabStr1 + KeyWord(C_SD_SEAWATER_TEMP) + TabStr2 + FloatToAnsiString(SeaWaterTemp) + CrLfStr;
                LocalString += TabStr1 + KeyWord(C_SD_SEAWATER_DNS) + TabStr2 + FloatToAnsiString(SeaWaterDensity) + CrLfStr;
                LocalString += TabStr1 + KeyWord(C_SD_AMBIENT_TEMP) + TabStr2 + FloatToAnsiString(AmbientTemp) + CrLfStr;
            }
        } else if (PRODraftSystem::PRODraftSysPtr) {
            LocalString += TabStr1 + KeyWord(C_SD_TRIM_SOURCE)      + TabStr2 + KeyWord(TrimSource) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_MANUAL_TRIM)      + TabStr2 + FloatToAnsiString(ManualTrim) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_LIST_SOURCE)      + TabStr2 + KeyWord(ListSource) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_MANUAL_LIST)      + TabStr2 + FloatToAnsiString(ManualList) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_SEAWATER_TEMP)    + TabStr2 + FloatToAnsiString(SeaWaterTemp) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_SEAWATER_DNS)     + TabStr2 + FloatToAnsiString(SeaWaterDensity) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_SD_AMBIENT_TEMP) + TabStr2 + FloatToAnsiString(AmbientTemp) + CrLfStr;
        }
        LocalString += TabStr1 + KeyWord(C_SD_TIME_GMT) + TabStr2 + (AnsiString)TimeFromGMT + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_SD_DAYLIGH_SAVING) + TabStr1 + (AnsiString)DaylightSaving + CrLfStr;

        LocalString += TabStr1 + KeyWord(C_SD_SCREEN_OFF_TIME) + TabStr2 + (AnsiString)TouchScreenTimeOut + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_SD_ALARM_OFF_DELAY) + TabStr2 + (AnsiString)AlarmOffDelay + CrLfStr;

        /*
#ifdef S2TXU
        switch ( GlobalDeviceHWId ) {
            case TCU_R1://TCU
            case TCU_R2://TCU CurrentDeviceId should be 0x21
                break;
            case TDU_R1://TCU
            case TDU_R2://TCU CurrentDeviceId should be 0x21
                {
                    int xMin,xMax,yMin,yMax;
                    GUI_TOUCH_GetCalData(0,&xMin,&xMax);
                    GUI_TOUCH_GetCalData(1,&yMin,&yMax);
                    char Buf[BUF_SIZE];
                    sprintf(Buf,"\t%s\t\t%5i %5i %5i% 5i\n",KeyWord(C_SD_SCREEN_CAL).c_str(),xMin,xMax,yMin,yMax);
                    LocalString += Buf;
                }
                break;
        }
#endif
*/
        LocalString += TabStr1 + KeyWord(C_SD_UNITSYSTEM) + TabStr2 + (AnsiString)CurrentUnitSystem + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_SD_LANGUAGE) + TabStr2 + (AnsiString)CurrentLanguage + CrLfStr;

        LocalString += TabStr1 + KeyWord(C_SD_USER_PIN_CODE) + TabStr2 + UserPinCode + CrLfStr;
        //AnsiString LogTimeStr   = FloatToAnsiString(LogTime,,8,5);
        LocalString += TabStr1 + KeyWord(C_SD_LOG_TIME) + TabStr3 + (AnsiString)LogTime + CrLfStr;
        if (LogToFile)          LocalString += TabStr1 + KeyWord(C_SD_LOG_TO_FILE) + CrLfStr;
        if (LogAlarms)          LocalString += TabStr1 + KeyWord(C_SD_LOG_ALARMS) + CrLfStr;
        if (LogBallastExchange) LocalString += TabStr1 + KeyWord(C_SD_LOG_BALLAST_EXCH) + CrLfStr;
        if (LogCargo)           LocalString += TabStr1 + KeyWord(C_SD_LOG_CARGO) + CrLfStr;
        if (LogService)         LocalString += TabStr1 + KeyWord(C_SD_LOG_SERVICE) + CrLfStr;
        if (LogTemperature)     LocalString += TabStr1 + KeyWord(C_SD_LOG_TEMPERATURE) + CrLfStr;
        if (LogTankPressure)    LocalString += TabStr1 + KeyWord(C_SD_LOG_TANK_PRESSURE) + CrLfStr;
        if (PrinterOnThisTXU)   LocalString += TabStr1 + KeyWord(C_SD_PRINTER_ON_TDU) + CrLfStr;
        if (ReceiveWeightVolume)LocalString += TabStr1 + KeyWord(C_SD_RECEIVE_VOL_WGT) + CrLfStr;

        LocalString += TabStr1 + KeyWord(C_MOD_USER) + TabStr3 + AnsiString((unsigned)LastTimeModified) + CrLfStr;
        LocalString += KeyWord(C_PRO_END) + CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PROSystemData::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError   = true;
    int  ErrorLine = 0;
    int  Key;
    TrimSource =  C_SD_INC_SOURCE;
    ListSource =  C_SD_INC_SOURCE;  // DRAFT_SOURSE ;
                                    //TouchScreenTimeOut = DEFAULT_SCREEN_OFF_DELAY; // Allready initialized
    CurrentUnitSystem = UNIT_SYS_SI;
    UserPinCode       = (AnsiString)DEFAULT_PIN_CODE;
    ManualTrim        = 0.0;
    ManualList        = 0.0;

    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                RestoreSettingsWarning((AnsiString)"System Data " + Name + ":\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"System Data " + Name + ":\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_CT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case C_MOD_CONFIG:
            case C_MOD_SYSTEM:
            case C_MOD_USER  :
//            ModifiedBy = Key;
                LastTimeModified = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_TRIM_SOURCE:
                {
                    AnsiString SettingsKWord = SettingsString->NextWord(ErrorLine);
                    if (!ErrorLine) {
                        TrimSource = FindConfigKey(SettingsKWord);
                    }
                }
                break;
            case C_SD_MANUAL_TRIM:
                ManualTrim = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_LIST_SOURCE:
                {
                    AnsiString SettingsKWord = SettingsString->NextWord(ErrorLine);
                    if (!ErrorLine) {
                        ListSource = FindConfigKey(SettingsKWord);
                    }
                }
                break;
            case C_SD_MANUAL_LIST:
                ManualList = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_SEAWATER_DNS:
                SeaWaterDensity = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_BALLAST_DNS    :
                BallastDensity = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_FRESHWATER_DNS :
                FreshWaterDensity = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_HEAVY_FUEL_DNS :
                HeavyFuelDensity = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_DIESEL_DNS     :
                DieselDensity = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_LUBRICANTS_DNS :
                LubricantsDensity = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_SEAWATER_TEMP:
                SeaWaterTemp = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_AMBIENT_TEMP:
                AmbientTemp = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_SCREEN_OFF_TIME:
                TouchScreenTimeOut = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_SCREEN_CAL:
#ifdef S2TXU
                {
                    U32 xMin = SettingsString->ReadLong(ErrorLine);
                    if (!ErrorLine) {
                        U32 xMax = SettingsString->ReadLong(ErrorLine);
                        if (!ErrorLine) {
                            U32 yMin = SettingsString->ReadLong(ErrorLine);
                            if (!ErrorLine) {
                                U32 yMax = SettingsString->ReadLong(ErrorLine);
                                if (!ErrorLine) {
                                    GUI_TOUCH_SetCalData(0, xMin, xMax);
                                    GUI_TOUCH_SetCalData(1, yMin, yMax);
                                }
                            }
                        }
                    }
                }
                NoError = !ErrorLine;
#endif
                break;
            case C_SD_ALARM_OFF_DELAY:
                AlarmOffDelay = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
			case C_SD_UNITSYSTEM:
                CurrentUnitSystem = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_TIME_GMT:
                {
                    TimeFromGMT = SettingsString->ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                    if (NoError) {
                        TSNSetTimeZone(TimeFromGMT);
                    }
                }
                break;
			case C_SD_DAYLIGH_SAVING:
				{
					int tmpDaylightSaving = SettingsString->ReadLong(ErrorLine);
					SetDaylightSaving( tmpDaylightSaving);
					NoError = !ErrorLine;
				}
                break;
            case C_SD_LANGUAGE:
                {
                    int CLanguage = SettingsString->ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                    if (NoError) {
                        SetCurrentLanguage(CLanguage);
                    }
                }
                break;
            case C_SD_USER_PIN_CODE:
                UserPinCode = SettingsString->NextWord(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_LOG_TIME:
                LogTime = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_SD_LOG_TO_FILE       :
                LogToFile          = true; break;
            case C_SD_LOG_ALARMS        :
                LogAlarms          = true; break;
            case C_SD_LOG_BALLAST_EXCH  :
                LogBallastExchange = true; break;
            case C_SD_LOG_CARGO         :
                LogCargo           = true; break;
            case C_SD_LOG_SERVICE       :
                LogService         = true; break;
            case C_SD_LOG_TEMPERATURE   :
                LogTemperature     = true; break;
            case C_SD_LOG_TANK_PRESSURE :
                LogTankPressure    = true; break;
            case C_SD_RECEIVE_VOL_WGT   :
                ReceiveWeightVolume = true; break;
            case C_SD_PRINTER_ON_TDU    :
                PrinterOnThisTXU   = true;
                if (PrinterOnThisTXU) {
                    PROPrinter::CurPrinterId = PROPrinter::LastDefPrinter->IDNumber;
                }
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    if (Master && NoError) {
        SendData(CMD_GENERIC_STATIC_DATA);
    }
    return (NoError);
}


ValueList* PROSystemData::GetValueInfoTable(int &Entries, int Index) {
    return GetValueInfoTableStatic(Entries, Index);
}

ValueList PROSystemData::SelectSystemValueList[] = {
    { L_WORD404, L_WORD237, SVT_ATM_PRESSURE },                               // {"AtmPress"         ,"",SVT_ATM_PRESSURE},
    { L_WORD425, L_WORD237, SVT_TRIM_ANGLE_NOSIGN },                               // {"Trim in deg"      ,"",SVT_TRIM_ANGLE},
    { L_WORD426, L_WORD237, SVT_TRIM_M_NOSIGN },                                   // {"Trim in meter"    ,"",SVT_TRIM_M},
	{ L_WORD427, L_WORD237, SVT_LIST_ANGLE_NOSIGN },                               // {"List in deg"      ,"",SVT_LIST_ANGLE},
    { L_WORD447, L_WORD237, SVT_LIST_M_NOSIGN },                                   // {"List in meter"    ,"",SVT_LIST_M},
};


ValueList* PROSystemData::GetValueInfoTableStatic(int &Entries, int Index) {
    Entries = NELEMENTS(SelectSystemValueList);
    return (SelectSystemValueList);
}

void PROSystemData::CalcTotals(vector<PRogramObjectBase *> &ObjectVector, float *Volume, float *Weight) {
    float                              TmpVol = 0.0;
    float                              TmpWgt = 0.0;
    set<PRogramObjectBase *>::iterator pBIt;
    for (unsigned i = 0; i < ObjectVector.size(); i++) {
        PROTank *TankPtr = (PROTank *)ObjectVector[i];
        TmpVol += TankPtr->Volume;
        TmpWgt += TankPtr->Weight;
    }
    *Volume = TmpVol;
    *Weight = TmpWgt;


}

void PROSystemData::Calculate(void) {
    // Trim
    switch (TrimSource) {
    case C_SD_MAN_SOURCE  :
        TrimValue = ManualTrim;
        break;
	case C_SD_DRAFT_SOURCE:
        if (PRODraftSystem::PRODraftSysPtr && PRODraftSystem::PRODraftSysPtr->HasTrimValue) {
            TrimValue = PRODraftSystem::PRODraftSysPtr->TrimValue;
        } else if (PROInclinometer::HasTrimValue) {
            TrimValue = PROInclinometer::PROInclinPtr->TrimValue;
        } else {
            TrimValue = ManualTrim;
        }
        break;
    case C_SD_INC_SOURCE  :
        TrimValue = PROInclinometer::TrimValue;
        break;
    }
    switch (ListSource) {
    case C_SD_MAN_SOURCE  :
        ListValue = ManualList;
        break;
    case C_SD_DRAFT_SOURCE:
        if (PRODraftSystem::PRODraftSysPtr && PRODraftSystem::PRODraftSysPtr->HasListValue) {
            ListValue = PRODraftSystem::PRODraftSysPtr->ListValue;
        } else if (PROInclinometer::HasListValue) {
            ListValue = PROInclinometer::ListValue;
        } else {
            ListValue = ManualList;
        }
		break;
    case C_SD_INC_SOURCE  :
        ListValue = PROInclinometer::ListValue;
        break;
    }
    CalcTotals(PROCargoTank::AllObjVector, &CargoVolume, &CargoWeight);
    CalcTotals(PROBallastTank::AllObjVector, &BallastVolume, &BallastWeight);
    CalcTotals(PROServiceTank::AllHeavyFuelOilVector, &HeavyFuelVolume, &HeavyFuelWeight);
    CalcTotals(PROServiceTank::AllDieselVector, &DieselOilVolume, &DieselOilWeight);
    CalcTotals(PROServiceTank::AllLubricantsVector, &LubricantsVolume, &LubricantsWeight);
    CalcTotals(PROServiceTank::MiscVector, &MiscVolume, &MiscWeight);
    CalcTotals(PROServiceTank::FreshWaterVector, &FreshWaterVolume, &FreshWaterWeight);
    SendData();
}

int PROSystemData::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_LATITUDE:
        DecPnt     = 1;
        Unit       = ANGLE_UNIT;
		MyRetValue = Latitude;
        break;
	case SVT_TRIM_M_NOSIGN:
        Status     = GETVAL_FWD_AFT;
    case SVT_TRIM_M:
        if (PROProjectInfo::IsInlandVessel) {
            DecPnt     = 2;
        } else {
            DecPnt     = 1;
        }
        Unit       = LENGTH_UNIT;
		MyRetValue = TrimValue * PROProjectInfo::LengthBetweenPP;
		break;
    case SVT_TRIM_MARKS_M:
        if (PRODraftSystem::PRODraftSysPtr) {
			Status = PRODraftSystem::PRODraftSysPtr->GetValue(ValueId,Index, MyRetValue,DecPnt,Unit);
			if ( Status != GETVAL_NO_ERR){
	            Status 	   = GETVAL_NO_ERR;
				DecPnt     = 1;
				Unit       = LENGTH_UNIT;
				MyRetValue = TrimValue * PROProjectInfo::LengthBetweenMarks;
			}
		} else {
			DecPnt     = 1;
			Unit       = LENGTH_UNIT;
			MyRetValue = TrimValue * PROProjectInfo::LengthBetweenMarks;
		}
		break;
    case SVT_TRIM_ANGLE_NOSIGN:
        Status     = GETVAL_FWD_AFT;
    case SVT_TRIM_ANGLE:
        DecPnt     = 1;
        Unit       = ANGLE_UNIT;
        MyRetValue = TrimValue;
        break;
    case SVT_TRIM_DEG:
        DecPnt     = 1;
        Unit       = NO_UNIT;
        MyRetValue = TrimValue * RAD_FACTOR;
        break;
    case SVT_TRIM_SOURCE:
        DecPnt      = 0;
        Unit        = NO_UNIT;
        MyRetValue  = TrimSource;
        break;
    case SVT_LIST_M_NOSIGN:
        Status      = GETVAL_PORT_STBD;
    case SVT_LIST_M:
        if (PROProjectInfo::IsInlandVessel) {
            DecPnt     = 2;
        } else {
            DecPnt     = 1;
        }
        Unit        = LENGTH_UNIT;
        MyRetValue  = ListValue * PROProjectInfo::PROProjectInfoPtr->Width;
        break;
    case SVT_LIST_ANGLE_NOSIGN :
        Status      = GETVAL_PORT_STBD;
    case SVT_LIST_ANGLE :
        DecPnt      = 1;
        Unit        = ANGLE_UNIT;
        MyRetValue  = ListValue;
        break;
    case SVT_LIST_DEG:
        DecPnt     = 1;
        Unit       = NO_UNIT;
        MyRetValue = ListValue * RAD_FACTOR;
        break;
    case SVT_ATM_PRESSURE :
        DecPnt     = 1;
        Unit = PRESSURE_UNIT1;
        MyRetValue = AIPressSensor::AtmPressure;
        break;
    case SVT_LIST_SOURCE:
        DecPnt      = 0;
        Unit        = NO_UNIT;
        MyRetValue  = ListSource;
        break;
    case SVT_CURRENT_UNIT_SYSTEM:
        DecPnt      = 0;
        Unit        = NO_UNIT;
        MyRetValue  = (float)CurrentUnitSystem;
        break;
    case SVT_ALARM_OFF_DELAY  :
        DecPnt      = 0;
        Unit        = SECOND_UNIT;
        MyRetValue  = (float)AlarmOffDelay / 1000;
        break;
    case SVT_TOUCH_SCREEN_TIMEOUT  :
        DecPnt      = 0;
        Unit        = NO_UNIT;
        MyRetValue  = (float)TouchScreenTimeOut / 60000;
        break;
    case SVT_SEAWATER_TEMP :
        DecPnt      = 1;
        Unit        = TEMP_UNIT;
        MyRetValue  = SeaWaterTemp;
        break;
    case SVT_AMBIENT_TEMP :
        DecPnt      = 1;
        Unit        = TEMP_UNIT;
        MyRetValue  = AmbientTemp;
        break;
    case SVT_SEAWATER_DNS  :
    case SVT_BALLAST_DNS   :
    case SVT_FRESHWATER_DNS:
    case SVT_HEAVY_FUEL_DNS:
    case SVT_DIESEL_DNS    :
    case SVT_LUBRICANTS_DNS:
        DecPnt = 4;
        Unit   = DENSITY_UNIT;
        {
            switch (ValueId) {
            case SVT_SEAWATER_DNS  :
                MyRetValue = SeaWaterDensity; break;
            case SVT_BALLAST_DNS   :
                MyRetValue = BallastDensity; break;
            case SVT_FRESHWATER_DNS:
                MyRetValue = FreshWaterDensity; break;
            case SVT_HEAVY_FUEL_DNS:
                MyRetValue = HeavyFuelDensity; break;
            case SVT_DIESEL_DNS    :
                MyRetValue = DieselDensity; break;
            case SVT_LUBRICANTS_DNS:
                MyRetValue = LubricantsDensity; break;
            }
        }
        break;
    case SVT_LOG_TIME            :
        DecPnt = 2;
        Unit   = TIME_UNIT;
        MyRetValue = ((float)LogTime) / (MSEC_TO_SEC * SEC_TO_HOURS);
        break;
    case SVT_LOG_TO_FILE          :
        DecPnt = 0;
        Unit   = NO_UNIT;
        MyRetValue = (float)LogToFile;
        break;
    case SVT_LOG_ALARMS          :
        DecPnt = 0;
        Unit   = NO_UNIT;
        MyRetValue = (float)LogAlarms;
        break;
    case SVT_LOG_BALLAST_EXCH    :
        DecPnt = 0;
        Unit   = NO_UNIT;
        MyRetValue = (float)LogBallastExchange;
        break;
    case SVT_LOG_CARGO           :
        DecPnt = 0;
        Unit   = NO_UNIT;
        MyRetValue = (float)LogCargo;
        break;
    case SVT_LOG_SERVICE:
        DecPnt = 0;
        Unit   = NO_UNIT;
        MyRetValue = (float)LogService;
        break;
    case SVT_LOG_TEMPERATURE     :
        DecPnt = 0;
        Unit   = NO_UNIT;
        MyRetValue = (float)LogTemperature;
        break;
    case SVT_LOG_TANK_PRESSURE   :
        DecPnt = 0;
        Unit   = NO_UNIT;
        MyRetValue = (float)LogTankPressure;
        break;
    case SVT_PRINTER_ON_TXU      :
        DecPnt = 0;
        Unit   = NO_UNIT;
        MyRetValue = (float)PrinterOnThisTXU;
        break;
    case SVT_CARGO_VOLUME      :
    case SVT_BALLAST_VOLUME    :
    case SVT_HEAVY_FUEL_VOLUME :
    case SVT_DIESEL_OIL_VOLUME :
    case SVT_LUBRICANTS_VOLUME :
    case SVT_FRESH_WATER_VOLUME:
    case SVT_MISC_VOLUME       :
    case SVT_TOTAL_VOLUME      :
        DecPnt = 1;
        Unit   = VOLUME_UNIT;
        switch (ValueId) {
        case SVT_CARGO_VOLUME      :
            MyRetValue = CargoVolume;
            break;
        case SVT_BALLAST_VOLUME    :
            MyRetValue = BallastVolume;
            break;
        case SVT_HEAVY_FUEL_VOLUME :
            MyRetValue = HeavyFuelVolume;
            break;
        case SVT_DIESEL_OIL_VOLUME :
            MyRetValue = DieselOilVolume;
            break;
        case SVT_LUBRICANTS_VOLUME :
            MyRetValue = LubricantsVolume;
            break;
        case SVT_FRESH_WATER_VOLUME:
            MyRetValue = FreshWaterVolume;
            break;
        case SVT_MISC_VOLUME       :
            MyRetValue = MiscVolume;
            break;
        case SVT_TOTAL_VOLUME      :
            MyRetValue =   CargoVolume + BallastVolume + FreshWaterVolume
                + HeavyFuelVolume + DieselOilVolume + LubricantsVolume
                + MiscVolume;
            break;
        }
        break;

    case SVT_CARGO_WEIGHT      :
    case SVT_BALLAST_WEIGHT    :
    case SVT_HEAVY_FUEL_WEIGHT :
    case SVT_DIESEL_OIL_WEIGHT :
    case SVT_LUBRICANTS_WEIGHT :
    case SVT_FRESH_WATER_WEIGHT:
    case SVT_MISC_WEIGHT       :
    case SVT_TOTAL_WEIGHT      :
        DecPnt = 1;
        Unit   = WEIGHT_UNIT;
        switch (ValueId) {
        case SVT_CARGO_WEIGHT      :
            MyRetValue = CargoWeight;
            break;
        case SVT_BALLAST_WEIGHT    :
            MyRetValue = BallastWeight;
            break;
        case SVT_HEAVY_FUEL_WEIGHT :
            MyRetValue = HeavyFuelWeight;
            break;
        case SVT_DIESEL_OIL_WEIGHT :
            MyRetValue = DieselOilWeight;
            break;
        case SVT_LUBRICANTS_WEIGHT :
            MyRetValue = LubricantsWeight;
            break;
        case SVT_FRESH_WATER_WEIGHT:
            MyRetValue = FreshWaterWeight;
            break;
        case SVT_MISC_WEIGHT       :
            MyRetValue = MiscWeight;
            break;
        case SVT_TOTAL_WEIGHT      :
            MyRetValue = CargoWeight + BallastWeight + FreshWaterWeight
                + HeavyFuelWeight + DieselOilWeight + LubricantsWeight
                + MiscWeight;
            break;

        }
        break;
    case SVT_ROLLING_PERIOD     :
    case SVT_ROLLING_FREQUENCY  :
    case SVT_LIST_MAX_P         :
    case SVT_LIST_MAX_S         :
    case SVT_LIST_BUF_MAX_P     :
    case SVT_LIST_BUF_MAX_S     :
    case SVT_RESET_MAX_LIST     :
        if (PROInclinometer::PROInclinPtr) {
            Status = PROInclinometer::PROInclinPtr->GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_SECONDS:
        DecPnt = 0;
        Unit   = NO_UNIT;
        MyRetValue = (float)(time(NULL) & 0xffff);
        break;
    default:
        Status = PRogramObject::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;

    }
    return (Status);
}


int PROSystemData::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_CURRENT_UNIT_SYSTEM:
        {
            switch (CurrentUnitSystem) {
            case UNIT_SYS_SI:
                MyString = "SI";
                break;
            case UNIT_SYS_US:
                MyString = "US";
                break;
            case UNIT_SYS_USER:
                MyString = "User";
                break;
            default:
                CurrentUnitSystem = UNIT_SYS_SI;
                MyString = "SI";
                break;
            }
        }
        break;
    case SVT_CURRENT_LANGUAGE:
        MyString = GetCurrentLanguage();
        break;
    case SVT_CALL_SIGN   :
        MyString = PROProjectInfo::CallSign;
        break;
    case SVT_SHIP_OWNER  :
        MyString = PROProjectInfo::ProjOwner;
        break;
    case SVT_SHIP_NAME   :
        if (PROProjectInfo::PROProjectInfoPtr) MyString = PROProjectInfo::PROProjectInfoPtr->Name;
        break;
    case SVT_SYSTEM_ID   :
        MyString = PROProjectInfo::ProjectName;
        break;
    case SVT_DATA_VERSION:
        {
            char Buf[BUF_SIZE];
            if (TSNConfigInfo::ConfigInfoPtr) sprintf(Buf, "%i", TSNConfigInfo::ConfigInfoPtr->PrevConfigDataRevision);
            MyString = Buf;
        }
        break;
    case SVT_PROG_VERSION:
        {
            char Buf[BUF_SIZE];
            sprintf(Buf, "%i.%i.%i.%i", MyProgramVersion.ProdNo, MyProgramVersion.PacketFormat,
                    MyProgramVersion.NewFunctions, MyProgramVersion.Build);
            MyString = Buf;
        }
        break;
    case SVT_USER_PIN_CODE    :
        MyString = UserPinCode;
        break;
    case SVT_FORCE_WRITE_CONFIG:
        if (HasConfigWritePermission) {
            MyString = FindKeyWord(C_ENABLE);
        } else {
            MyString = FindKeyWord(C_DISABLE);
        }
        if (MyString.IsEmpty())   Status = GETVAL_ERROR;
        break;
    case SVT_TANK_STATE_STR    :
    case SVT_TANK_STATE_STR_CGO:
    case SVT_TANK_STATE_STR_BAL:
    case SVT_TANK_STATE_STR_SER:
    case SVT_TANK_STATE_STR_LSW:
    case SVT_TANK_STATE_STR_PRE:
        MyString = PROXRefObject::GetStateString(GetOpModeState(ValueId));
        break;
    case SVT_IGNORE_VOL_VGT_MESSAGE:
        if (PROSystemData::ReceiveWeightVolume) {
            MyString = FindKeyWord(C_ENABLE);
        } else {
            MyString = FindKeyWord(C_DISABLE);
        }
        if (MyString.IsEmpty())   Status = GETVAL_ERROR;
        break;
    default:
        Status = PRogramObject::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}


int PROSystemData::GetFloatValue(int ValueId, int Index, float &MyValue) {
    int Status        = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_LATITUDE:
        MyValue = Latitude;
        break;
    case SVT_TRIM_M_NOSIGN:
        Status     = GETVAL_FWD_AFT;
    case SVT_TRIM_M:
        MyValue = TrimValue * PROProjectInfo::LengthBetweenPP;
        break;
    case SVT_TRIM_MARKS_M:
        MyValue = TrimValue * PROProjectInfo::LengthBetweenMarks;
        break;
    case SVT_TRIM_ANGLE_NOSIGN:
        Status     = GETVAL_FWD_AFT;
    case SVT_TRIM_ANGLE:
        MyValue = TrimValue;
        break;
    case SVT_TRIM_DEG:
        MyValue = TrimValue * RAD_FACTOR;
        break;
    case SVT_LIST_M_NOSIGN:
        Status      = GETVAL_PORT_STBD;
    case SVT_LIST_M:
        MyValue  = ListValue * PROProjectInfo::PROProjectInfoPtr->Width;
        break;
    case SVT_LIST_ANGLE_NOSIGN :
        Status      = GETVAL_PORT_STBD;
    case SVT_LIST_ANGLE :
        MyValue  = ListValue;
        break;
    case SVT_LIST_DEG:
        MyValue = ListValue * RAD_FACTOR;
        break;
    case SVT_ATM_PRESSURE :
        MyValue = AIPressSensor::AtmPressure;
        break;
    case SVT_SEAWATER_TEMP :
        MyValue  = SeaWaterTemp;
        break;
    case SVT_AMBIENT_TEMP :
        MyValue  = AmbientTemp;
        break;
    case SVT_SEAWATER_DNS  :
        MyValue = SeaWaterDensity; break;
    case SVT_BALLAST_DNS   :
        MyValue = BallastDensity; break;
    case SVT_FRESHWATER_DNS:
        MyValue = FreshWaterDensity; break;
    case SVT_HEAVY_FUEL_DNS:
        MyValue = HeavyFuelDensity; break;
    case SVT_DIESEL_DNS    :
        MyValue = DieselDensity; break;
    case SVT_LUBRICANTS_DNS:
        MyValue = LubricantsDensity; break;
    case SVT_CARGO_VOLUME      :
        MyValue = CargoVolume;
        break;
    case SVT_BALLAST_VOLUME    :
        MyValue = BallastVolume;
        break;
    case SVT_HEAVY_FUEL_VOLUME :
        MyValue = HeavyFuelVolume;
        break;
    case SVT_DIESEL_OIL_VOLUME :
        MyValue = DieselOilVolume;
        break;
    case SVT_LUBRICANTS_VOLUME :
        MyValue = LubricantsVolume;
        break;
    case SVT_FRESH_WATER_VOLUME:
        MyValue = FreshWaterVolume;
        break;
    case SVT_MISC_VOLUME       :
        MyValue = MiscVolume;
        break;
    case SVT_TOTAL_VOLUME      :
        MyValue =   CargoVolume + BallastVolume + FreshWaterVolume
            + HeavyFuelVolume + DieselOilVolume + LubricantsVolume
            + MiscVolume;
        break;
    case SVT_CARGO_WEIGHT      :
        MyValue = CargoWeight;
        break;
    case SVT_BALLAST_WEIGHT    :
        MyValue = BallastWeight;
        break;
    case SVT_HEAVY_FUEL_WEIGHT :
        MyValue = HeavyFuelWeight;
        break;
    case SVT_DIESEL_OIL_WEIGHT :
        MyValue = DieselOilWeight;
        break;
    case SVT_LUBRICANTS_WEIGHT :
        MyValue = LubricantsWeight;
        break;
    case SVT_FRESH_WATER_WEIGHT:
        MyValue = FreshWaterWeight;
        break;
    case SVT_MISC_WEIGHT       :
        MyValue = MiscWeight;
        break;
    case SVT_TOTAL_WEIGHT      :
        MyValue = CargoWeight + BallastWeight + FreshWaterWeight
            + HeavyFuelWeight + DieselOilWeight + LubricantsWeight
            + MiscWeight;
        break;
    case SVT_ROLLING_PERIOD     :
    case SVT_ROLLING_FREQUENCY  :
    case SVT_LIST_MAX_P         :
    case SVT_LIST_MAX_S         :
    case SVT_LIST_BUF_MAX_P     :
    case SVT_LIST_BUF_MAX_S     :
    case SVT_RESET_MAX_LIST     :
        if (PROInclinometer::PROInclinPtr) {
            Status = PROInclinometer::PROInclinPtr->GetFloatValue(ValueId, Index, MyValue);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    default:
        Status = PRogramObject::GetFloatValue(ValueId, Index, MyValue);
        break;

    }
    return Status;
}
///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input/output
//
///////////////////////////////////////////////////////////////


int PROSystemData::GetTimeZone(void) {
    return TimeFromGMT;
}

void PROSystemData::SetTimeZone(int NewZone) {
    if (TimeFromGMT != NewZone) {
        TimeFromGMT = NewZone;
        PROSystemData::TXUSystemData->SetModifiedFlag();
    }
}

void PROSystemData::SetDST(int NewDST) {
    if (DaylightSaving != NewDST) {
        DaylightSaving = NewDST;
        PROSystemData::TXUSystemData->SetModifiedFlag();
    }
}

int PROSystemData::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status    = E_NO_ERR,
        ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_LATITUDE:
        InputLatitude(ConvertToSi(NewValue, ValUnitId = ANGLE_UNIT, Status, -90.0, 90.0, Latitude));
        break;
    case SVT_CURRENT_UNIT_SYSTEM:
        {
            int NewUnitSystem = atoi(NewValue.c_str());
            switch (NewUnitSystem) {
            case UNIT_SYS_SI:
                CurrentUnitSystem = NewUnitSystem;
                SetStdSIUnits();
                break;
            case UNIT_SYS_US:
                CurrentUnitSystem = NewUnitSystem;
                SetStdUSUnits();
                break;
            case UNIT_SYS_USER:
                CurrentUnitSystem = NewUnitSystem;
                break;
            default:
                Status = E_INPUT_ERR;
                break;
            }
        }
        break;

    case SVT_TRIM_M_NOSIGN      :
    case SVT_TRIM_ANGLE_NOSIGN  :
    case SVT_TRIM_M             :
    case SVT_TRIM_MARKS_M       :
    case SVT_TRIM_ANGLE         :
        switch (TrimSource) {
        case C_SD_INC_SOURCE   :
            if (PROInclinometer::PROInclinPtr) {
                Status = PROInclinometer::PROInclinPtr->PutValue(ValueId, 0, NewValue, Local, &ValUnitId);
            }
            break;
        case C_SD_DRAFT_SOURCE :
            Status = E_NO_INPUT_PERMISSION;
            break;
        case C_SD_MAN_SOURCE   :
            {
                float NewTrim;
                switch (ValueId) {
                case SVT_TRIM_ANGLE:
                    NewTrim = ConvertToSi(NewValue, ValUnitId = ANGLE_UNIT, Status, -10.0, 5.0, 0.0);
                    break;
                case SVT_TRIM_M:
                    NewTrim = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, -15.0, 5.0, 0.0);
                    NewTrim /= PROProjectInfo::LengthBetweenPP;
                    break;
                case SVT_TRIM_MARKS_M:
                    NewTrim = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, -15.0, 5.0, 0.0);
                    NewTrim /= PROProjectInfo::LengthBetweenMarks;
                    break;
                }
                if (Status == E_NO_ERR) {
                    ManualTrim = NewTrim;
                    TrimValue  = NewTrim;
                }

            }
            break;
        }
        break;

    case SVT_LIST_M_NOSIGN:
    case SVT_LIST_ANGLE_NOSIGN:
    case SVT_LIST_M:
    case SVT_LIST_ANGLE:
        switch (ListSource) {
        case C_SD_INC_SOURCE   :
            if (PROInclinometer::PROInclinPtr) {
                Status = PROInclinometer::PROInclinPtr->PutValue(ValueId, 0, NewValue, Local, &ValUnitId);
            }
            break;
        case C_SD_DRAFT_SOURCE :
            Status = E_NO_INPUT_PERMISSION;
            break;
        case C_SD_MAN_SOURCE   :
            {
                float NewList;
                switch (ValueId) {
                case SVT_LIST_ANGLE:
                    ValUnitId = ANGLE_UNIT;
                    NewList = ConvertToSi(NewValue, ValUnitId = ANGLE_UNIT, Status, -15.0, 15.0, 0.0);
                    break;
                case SVT_LIST_M:
                    ValUnitId = LENGTH_UNIT;
                    NewList = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, -5.0, 5.0, 0.0);
                    NewList /= PROProjectInfo::Width;
                    break;
                }
                if (Status == E_NO_ERR) {
                    ManualList = NewList;
                    ListValue  = NewList;
                }

            }
            break;
        }
        break;

    case SVT_TRIM_SOURCE:
        ConvertToInt(&TrimSource, NewValue);
        break;
    case SVT_LIST_SOURCE:
        ConvertToInt(&ListSource, NewValue);
        break;
    case SVT_CURRENT_LANGUAGE :
        ConvertToInt(&CurrentLanguage, NewValue);
        SetCurrentLanguage(CurrentLanguage);
        break;
    case SVT_ALARM_OFF_DELAY  :
        {
            float AlDelay;
            ConvertToFloat(&AlDelay, NewValue);
            AlDelay = AlDelay * MSEC_TO_SEC;
            if (AlDelay < MIN_ALARM_OFF_DELAY) {
                Status = E_LOW;
            } else if (AlDelay > MAX_ALARM_OFF_DELAY) {
                Status = E_HIGH;
            } else {
                AlarmOffDelay = int(AlDelay);
            }
        }
        break;
    case SVT_ALARM_SOUND_SLEEP     :
        {

            int NewStatus = FindConfigKey(NewValue);
            switch (NewStatus) {
            case C_ENABLE:
                AlarmBasic::AlarmSound = true;
                break;
            case C_DISABLE:
                AlarmBasic::AlarmSound = false;
#ifdef S2TXU
                OS_RetriggerTimer(&AlarmSilenceTimer);
#endif
                break;
            default:
				{
					unsigned Value = GetUnsigned(NewValue, Status);
                    if (Status == E_NO_ERR) {
                        if (Value) {
							AlarmBasic::AlarmSound = true;
						} else {
#ifdef S2TXU
                            OS_RetriggerTimer(&AlarmSilenceTimer);
#endif
                            AlarmBasic::AlarmSound = false;
                        }
                    }
                }
                break;
            }
		}
        break;
    case SVT_TOUCH_SCREEN_TIMEOUT  :
        {
            int ScrOffDelay;
            ConvertToInt(&ScrOffDelay, NewValue);
            if (ScrOffDelay < TOUCH_MIN_TIMEOUT) {
                Status = E_LOW;
            } else if (ScrOffDelay > TOUCH_MAX_TIMEOUT) {
                Status = E_HIGH;
            } else {
                TouchScreenTimeOut = int (ScrOffDelay *MIN_TO_MSEC);
            }
        }
        break;
    case SVT_USER_PIN_CODE    :
        UserPinCode = NewValue;
        break;
    case SVT_FORCE_WRITE_CONFIG:
        {
            int  NewStatus = FindConfigKey(NewValue);
            bool tmpEnable = false;
            switch (NewStatus) {
            case C_ENABLE:
                tmpEnable = true;
                break;
            case C_DISABLE:
                break;
            default:
                {
                    bool Value = (bool)GetUnsigned(NewValue, Status);
                    if (Status == E_NO_ERR) {
                        tmpEnable = Value;
                    }
                }
                break;
            }
            HasConfigWritePermission = tmpEnable;
        }
#ifdef S2TXU
        // Not required to check HasConfigWritePermission as the receiver task will check it
        if (OS_IsTask(&SaveConfigTaskHandle)) {
            OS_SignalEvent(FLASH_WRITE_CONFIG_NO_DELAY, &SaveConfigTaskHandle);
        }
#endif
        break;
    case SVT_SEAWATER_TEMP :
        {
            float TVal = ConvertToSi(NewValue, ValUnitId = TEMP_UNIT, Status, MIN_WATER_TEMP, MAX_WATER_TEMP, 0.0);
            if (Status == E_NO_ERR) {
                SeaWaterTemp = TVal;
            }
        }
        break;
    case SVT_AMBIENT_TEMP :
        {
            float TVal = ConvertToSi(NewValue, ValUnitId = TEMP_UNIT, Status, MIN_ENVIRONMENT_TEMP, MAX_ENVIRONMENT_TEMP, 0.0);
            if (Status == E_NO_ERR) {
                AmbientTemp = TVal;
            }
        }
        break;
    case SVT_SEAWATER_DNS  :
        {
            float TVal = ConvertToSi(NewValue, ValUnitId = DENSITY_UNIT, Status, MIN_DENSITY, MAX_DENSITY, 0.0);
            if (Status == E_NO_ERR) {
                SeaWaterDensity = TVal;
                if (!PROCargoTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROCargoTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROCargoTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROBallastTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROBallastTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROBallastTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROServiceTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROServiceTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROServiceTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
            }
        }
        break;
    case SVT_BALLAST_DNS   :
        {
            float TVal = ConvertToSi(NewValue, ValUnitId = DENSITY_UNIT, Status, MIN_DENSITY, MAX_DENSITY, 0.0);
            if (Status == E_NO_ERR) {
                BallastDensity = TVal;
                if (!PROCargoTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROCargoTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROCargoTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROBallastTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROBallastTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROBallastTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->InputBasicCargoType(CTY_BALLAST);
                    }
                }
                if (!PROServiceTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROServiceTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROServiceTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
            }
        }
        break;
    case SVT_FRESHWATER_DNS:
        {
            float TVal = ConvertToSi(NewValue, ValUnitId = DENSITY_UNIT, Status, MIN_DENSITY, MAX_DENSITY, 0.0);
            if (Status == E_NO_ERR) {
                FreshWaterDensity = TVal;
                if (!PROCargoTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROCargoTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROCargoTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROBallastTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROBallastTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROBallastTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROServiceTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROServiceTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROServiceTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROServiceTank::AllFreshWaterVector.empty()) {
                    for (unsigned i = 0; i < PROServiceTank::AllFreshWaterVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROServiceTank::AllFreshWaterVector[i];
                        if (TElement) TElement->CargoType->InputBasicCargoType(CTY_FW);
                    }
                }
            }
        }
        break;
    case SVT_HEAVY_FUEL_DNS:
        {
            float TVal = ConvertToSi(NewValue, ValUnitId = DENSITY_UNIT, Status, MIN_DENSITY, MAX_DENSITY, 0.0);
            if (Status == E_NO_ERR) {
                HeavyFuelDensity = TVal;
                if (!PROCargoTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROCargoTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROCargoTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROBallastTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROBallastTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROBallastTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROServiceTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROServiceTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROServiceTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROServiceTank::AllHeavyFuelOilVector.empty()) {
                    for (unsigned i = 0; i < PROServiceTank::AllHeavyFuelOilVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROServiceTank::AllHeavyFuelOilVector[i];
                        if (TElement) TElement->CargoType->InputBasicCargoType(CTY_HFO);
                    }
                }
            }
        }
        break;
    case SVT_DIESEL_DNS    :
        {
            float TVal = ConvertToSi(NewValue, ValUnitId = DENSITY_UNIT, Status, MIN_DENSITY, MAX_DENSITY, 0.0);
            if (Status == E_NO_ERR) {
                DieselDensity = TVal;
                if (!PROCargoTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROCargoTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROCargoTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROBallastTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROBallastTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROBallastTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROServiceTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROServiceTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROServiceTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROServiceTank::AllDieselVector.empty()) {
                    for (unsigned i = 0; i < PROServiceTank::AllDieselVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROServiceTank::AllDieselVector[i];
                        if (TElement) TElement->CargoType->InputBasicCargoType(CTY_DO);
                    }
                }
            }
        }
        break;
    case SVT_LUBRICANTS_DNS:
        {
            float TVal = ConvertToSi(NewValue, ValUnitId = DENSITY_UNIT, Status, MIN_DENSITY, MAX_DENSITY, 0.0);
            if (Status == E_NO_ERR) {
                LubricantsDensity = TVal;
                if (!PROCargoTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROCargoTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROCargoTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROBallastTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROBallastTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROBallastTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROServiceTank::AllObjVector.empty()) {
                    for (unsigned i = 0; i < PROServiceTank::AllObjVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROServiceTank::AllObjVector[i];
                        if (TElement) TElement->CargoType->Update_Density();
                    }
                }
                if (!PROServiceTank::AllLubricantsVector.empty()) {
                    for (unsigned i = 0; i < PROServiceTank::AllLubricantsVector.size(); i++) {
                        PROTank *TElement = (PROTank *)PROServiceTank::AllLubricantsVector[i];
                        if (TElement) TElement->CargoType->InputBasicCargoType(CTY_LUB);
                    }
                }
            }
        }
        break;
    case SVT_LOG_TIME            :
        {
            float LogDelay;
            ConvertToFloat(&LogDelay, NewValue);
            if (LogDelay < LOG_MIN_TIME) {
                Status = E_LOW;
            } else if (LogDelay > LOG_MAX_TIME) {
                Status = E_HIGH;
            } else {
                LogTime = (int)(LogDelay * (MSEC_TO_SEC * SEC_TO_HOURS));
            }
#ifdef S2TXU
            if (Master) {
                if (OS_IsTask(&LogTaskHandle)) {
                    OS_WakeTask(&LogTaskHandle);
                }
            }
#endif
        }
        break;
    case SVT_LOG_TO_FILE         :
    case SVT_LOG_ALARMS          :
    case SVT_LOG_BALLAST_EXCH    :
    case SVT_LOG_CARGO           :
    case SVT_LOG_SERVICE         :
    case SVT_LOG_TEMPERATURE     :
    case SVT_LOG_TANK_PRESSURE   :
    case SVT_PRINTER_ON_TXU      :
        {
            int  NewStatus = FindConfigKey(NewValue);
            bool tmpEnable = false;
            switch (NewStatus) {
            case C_ENABLE:
                tmpEnable = true;
                break;
            case C_DISABLE:
                break;
            default:
                {
                    bool Value = (bool)GetUnsigned(NewValue, Status);
                    if (Status == E_NO_ERR) {
                        tmpEnable = Value;
                    }
                }
                break;
            }
            switch (ValueId) {
            case SVT_LOG_TO_FILE         :
                LogToFile           = tmpEnable; break;
            case SVT_LOG_ALARMS          :
                LogAlarms           = tmpEnable; break;
            case SVT_LOG_BALLAST_EXCH    :
                LogBallastExchange  = tmpEnable; break;
            case SVT_LOG_CARGO           :
                LogCargo            = tmpEnable; break;
            case SVT_LOG_SERVICE         :
                LogService          = tmpEnable; break;
            case SVT_LOG_TEMPERATURE     :
                LogTemperature      = tmpEnable; break;
            case SVT_LOG_TANK_PRESSURE   :
                LogTankPressure     = tmpEnable; break;
            case SVT_PRINTER_ON_TXU      :
                PrinterOnThisTXU    = tmpEnable;
                Status              = E_LOCAL_ONLY;
                if (PrinterOnThisTXU) {
                    PROPrinter::CurPrinterId = PROPrinter::LastDefPrinter->IDNumber;
                } else {
                    // Assuming that the TCU has the first printer
                    unsigned PNo = PROPrinter::LastDefPrinter->IDNumber & 0xffff;
                    if (PNo >= 1) {
                        PROPrinter::CurPrinterId = (C_PRO_PRINTER << 16) | 1;
                    }
                }
                break;
            }
        }
        break;
    case SVT_TANK_STATE_STR    :
    case SVT_TANK_STATE_STR_CGO:
    case SVT_TANK_STATE_STR_BAL:
    case SVT_TANK_STATE_STR_SER:
    case SVT_TANK_STATE_STR_LSW:
    case SVT_TANK_STATE_STR_PRE:
        {
            TankState NewState = PROXRefObject::GetStateKey(NewValue);
            if (NewState == tUndefined) {
                NewState = (TankState)GetInt(NewValue, Status);
            }
            if (Status == E_NO_ERR) {
                SetOpModeState(NewState, ValueId, Index);
            }
        }
        break;
    case SVT_IGNORE_VOL_VGT_MESSAGE:
        {
            int Key = FindConfigKey(NewValue);
            switch (Key) {
            case C_ON:
            case C_OPEN:
            case C_ENABLE:
                PROSystemData::ReceiveWeightVolume = true;
                break;
            case C_OFF:
            case C_CLOSE:
            case C_DISABLE:
                PROSystemData::ReceiveWeightVolume = false;
                break;
            default:
                {
                    bool Value = (bool)GetUnsigned(NewValue, Status);
                    if (Status == E_NO_ERR) {
                        PROSystemData::ReceiveWeightVolume = Value;
                    }
                }
                break;
            }
        }
        break;
    default:
        Status = PRogramObject::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    switch (Status) {
    case E_NO_ERR     :
    case E_LOCAL_ONLY :
        SetModifiedFlag();
        break;
    default:
        break;
    }
    if (UnitId) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int PROSystemData::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_SEAWATER_DNS  :
        if (PROSystemData::SeaWaterDensity != NewValue) {
            PROSystemData::SeaWaterDensity    = NewValue;
            SendData(CMD_GENERIC_STATIC_DATA);
        }
        break;
    case SVT_BALLAST_DNS   :
        if (PROSystemData::BallastDensity != NewValue) {
            PROSystemData::BallastDensity     = NewValue;
            SendData(CMD_GENERIC_STATIC_DATA);
        }
        break;
    case SVT_FRESHWATER_DNS:
        if (PROSystemData::FreshWaterDensity != NewValue) {
            PROSystemData::FreshWaterDensity    = NewValue;
            SendData(CMD_GENERIC_STATIC_DATA);
        }
        break;
    case SVT_HEAVY_FUEL_DNS:
        if (PROSystemData::HeavyFuelDensity != NewValue) {
            PROSystemData::HeavyFuelDensity     = NewValue;
            SendData(CMD_GENERIC_STATIC_DATA);
        }
        break;
    case SVT_DIESEL_DNS    :
        if (PROSystemData::DieselDensity != NewValue) {
            PROSystemData::DieselDensity    = NewValue;
            SendData(CMD_GENERIC_STATIC_DATA);
        }
        break;
    case SVT_LUBRICANTS_DNS:
        if (PROSystemData::LubricantsDensity != NewValue) {
            PROSystemData::LubricantsDensity    = NewValue;
            SendData(CMD_GENERIC_STATIC_DATA);
        }
        break;
    case SVT_ALARM_SILENCE  :
        if ( NewValue ) {
            SendAlarmSilence();
        }
        break;
    case SVT_AL_ACKNOWLEDGE     :
        break;
    case SVT_ACKNOWLEGDE_ALL :
        if ( NewValue ) {
            AlarmBasic::AckAll();
        }
        break;
    default:
        Status = PRogramObject::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);

}


int PROSystemData::PutBitValue(int ValueId, int Index, bool NewValue) {
    int Status = E_NO_ERR;
    switch(ValueId){
    case SVT_ALARM_SILENCE  :
        if ( NewValue ) {
            SendAlarmSilence();
        }
        break;
    case SVT_AL_ACKNOWLEDGE     :
        break;
    case SVT_ACKNOWLEGDE_ALL :
        if ( NewValue ) {
            AlarmBasic::AckAll();
        }
        break;
    default                 :
        Status = E_INPUT_ERR;
        break;
    }
    return (Status);
}


float PROSystemData::TrimListCorrection(float LongitudinalDist, float TransverceDist) {
    return TrimValue * LongitudinalDist + ListValue * TransverceDist;
}



int PROSystemData::ReceiveData(U8 *data) {
    int                    ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH        = (ANPRO10_CommandHeading *)data;
    switch (pCH->CommandNo) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2720  *pData = (ANPRO10_COMMAND_2720 *)data;
            ErrorStatus       =  E_OK;
            TrimValue         = pData->Trim;
            ListValue         = pData->List;
            CargoVolume       = pData->CargoVolume;
            CargoWeight       = pData->CargoWeight;
            BallastVolume     = pData->BallastVolume;
            BallastWeight     = pData->BallastWeight;
            HeavyFuelVolume   = pData->HeavyFuelVolume;
            HeavyFuelWeight   = pData->HeavyFuelWeight;
            DieselOilVolume   = pData->DieselOilVolume;
            DieselOilWeight   = pData->DieselOilWeight;
            LubricantsVolume  = pData->LubricantsVolume;
            LubricantsWeight  = pData->LubricantsWeight;
            FreshWaterVolume  = pData->FreshWaterVolume;
            FreshWaterWeight  = pData->FreshWaterWeight;
            MiscVolume        = pData->MiscVolume;
            MiscWeight        = pData->MiscWeight;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            ANPRO10_COMMAND_2721  *pData = (ANPRO10_COMMAND_2721 *)data;
            ErrorStatus         = E_OK;
            ManualTrim          = pData->ManualTrim;
            ManualList          = pData->ManualList;
            BallastDensity      = pData->BallastDensity;
            SeaWaterDensity     = pData->SeaWaterDensity;
            FreshWaterDensity   = pData->FreshWaterDensity;
            HeavyFuelDensity    = pData->HeavyFuelDensity;
            DieselDensity       = pData->DieselDensity;
            LubricantsDensity   = pData->LubricantsDensity;
            SeaWaterTemp        = pData->SeaWaterTemp;
            AmbientTemp     = pData->AmbientTemp;
            TrimSource          = pData->TrimSource;
            ListSource          = pData->ListSource;
            LogTime             = pData->Logtime;
            LogToFile           = pData->LogToFile;
            LogAlarms           = pData->LogAlarms;
            LogBallastExchange  = pData->LogBallastExchange;
            LogCargo            = pData->LogCargo;
            LogService          = pData->LogService;
            LogTemperature      = pData->LogTemperature;
            LogTankPressure     = pData->LogTankPressure;
            if (CurrentLanguage != pData->CurrentLanguage) {
                SetCurrentLanguage(pData->CurrentLanguage);
            }
            ReceiveWeightVolume = pData->ReceiveWeightVolume;
            Latitude            = pData->Latitude;
            HasConfigWritePermission  = pData->HasConfigWritePermission;
            AlarmBasic::AlarmSound    = pData->AlarmSoundSleep;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int PROSystemData::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch (cmd) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2720 Cmd;
            Cmd.TxInfo.Port             = NULL;
            Cmd.TxInfo.rxAddr           = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId             = DEVICE_BROADCAST_TXU;

            Cmd.Data.ObjectId           = IDNumber;
            Cmd.Data.ndb                = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo          = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.Trim               = TrimValue;
            Cmd.Data.List               = ListValue;
            Cmd.Data.CargoVolume        = CargoVolume;
            Cmd.Data.CargoWeight        = CargoWeight;
            Cmd.Data.BallastVolume      = BallastVolume;
            Cmd.Data.BallastWeight      = BallastWeight;
            Cmd.Data.HeavyFuelVolume    = HeavyFuelVolume;
            Cmd.Data.HeavyFuelWeight    = HeavyFuelWeight;
            Cmd.Data.DieselOilVolume    = DieselOilVolume;
            Cmd.Data.DieselOilWeight    = DieselOilWeight;
            Cmd.Data.LubricantsVolume   = LubricantsVolume;
            Cmd.Data.LubricantsWeight   = LubricantsWeight;
            Cmd.Data.FreshWaterVolume   = FreshWaterVolume;
            Cmd.Data.FreshWaterWeight   = FreshWaterWeight;
            Cmd.Data.MiscVolume         = MiscVolume;
            Cmd.Data.MiscWeight         = MiscWeight;

            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) {
                ErrorStatus =  E_QUEUE_FULL;
            } else {
                ErrorStatus =  E_OK;
            }
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2721 Cmd;

            Cmd.TxInfo.Port             = NULL;
            Cmd.TxInfo.rxAddr           = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId             = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId           = IDNumber;
            Cmd.Data.ndb                = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo          = CMD_GENERIC_STATIC_DATA;
            Cmd.Data.ManualTrim         = ManualTrim;
            Cmd.Data.ManualList         = ManualList;
            Cmd.Data.BallastDensity     = BallastDensity;
            Cmd.Data.SeaWaterDensity    = SeaWaterDensity;
            Cmd.Data.FreshWaterDensity  = FreshWaterDensity;
            Cmd.Data.HeavyFuelDensity   = HeavyFuelDensity;
            Cmd.Data.DieselDensity      = DieselDensity;
            Cmd.Data.LubricantsDensity  = LubricantsDensity;
            Cmd.Data.SeaWaterTemp       = SeaWaterTemp;
            Cmd.Data.AmbientTemp    = AmbientTemp;
            Cmd.Data.TrimSource         = TrimSource;
            Cmd.Data.ListSource         = ListSource;

            Cmd.Data.Logtime            = LogTime;
            Cmd.Data.LogToFile          = LogToFile;
            Cmd.Data.LogAlarms          = LogAlarms;
            Cmd.Data.LogBallastExchange = LogBallastExchange;
            Cmd.Data.LogCargo           = LogCargo;
            Cmd.Data.LogService         = LogService;
            Cmd.Data.LogTemperature     = LogTemperature;
            Cmd.Data.LogTankPressure    = LogTankPressure;
            Cmd.Data.CurrentLanguage    = CurrentLanguage;
            Cmd.Data.ReceiveWeightVolume = ReceiveWeightVolume;
            Cmd.Data.Latitude           = Latitude;
            Cmd.Data.HasConfigWritePermission = HasConfigWritePermission;
            Cmd.Data.AlarmSoundSleep    = AlarmBasic::AlarmSound;
            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) {
                ErrorStatus =  E_QUEUE_FULL;
            } else {
                ErrorStatus =  E_OK;
            }
        }
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

TankState PROSystemData::GetOpModeState(int ValueKey) {
    TankState tmpState = tUndefined;
    switch (ValueKey) {
    case SVT_TANK_STATE_STR     :
        tmpState  = PROXRefObject::GetStateAll();
        break;
    case SVT_TANK_STATE_STR_CGO :
        tmpState = PROXRefObject::VectorGetState(PROCargoTank::ObjVector);
        break;
    case SVT_TANK_STATE_STR_BAL :
        tmpState = PROXRefObject::VectorGetState(PROBallastTank::ObjVector);
        break;
    case SVT_TANK_STATE_STR_SER :
        tmpState = PROXRefObject::VectorGetState(PROServiceTank::ObjVector);
        break;
    case SVT_TANK_STATE_STR_LSW :
        tmpState = PROXRefObject::VectorGetState(PROLevelSwitch::ObjVector);
        break;
    case SVT_TANK_STATE_STR_PRE :
        tmpState = PROXRefObject::VectorGetState(PROTankPressure::ObjVector);
        break;
    }
    return tmpState;
}


void PROSystemData::SetOpModeState(TankState newState, int ValueKey, int Index) {
    if (newState != tUndefined) {
        if (Index) {
            PROTanksystemUnit *UnitPtr = (PROTanksystemUnit *)FindObject(Index);
            if (UnitPtr) {
                switch (ValueKey) {
                case SVT_TANK_STATE_STR:
                    PROXRefObject::SetStateAll(newState);
                    break;
                case SVT_TANK_STATE_STR_CGO:
                    PROXRefObject::VectorSetState(UnitPtr->PROCargoTankVector, newState);
                    break;
                case SVT_TANK_STATE_STR_BAL:
                    PROXRefObject::VectorSetState(UnitPtr->PROBallastTankVector, newState);
                    break;
                case SVT_TANK_STATE_STR_SER:
                    PROXRefObject::VectorSetState(UnitPtr->PROServiceTankVector, newState);
                    break;
                case SVT_TANK_STATE_STR_LSW:
                    PROXRefObject::VectorSetState(UnitPtr->PROLevelSwitchVector, newState);
                    break;
                case SVT_TANK_STATE_STR_PRE:
                    PROXRefObject::VectorSetState(UnitPtr->PROTankPressureVector, newState);
                    break;
                }
            }
        } else {
            switch (ValueKey) {
            case SVT_TANK_STATE_STR:
                PROXRefObject::SetStateAll(newState);
                break;
            case SVT_TANK_STATE_STR_CGO:
                PROXRefObject::VectorSetState(PROCargoTank::ObjVector, newState);
                break;
            case SVT_TANK_STATE_STR_BAL:
                PROXRefObject::VectorSetState(PROBallastTank::ObjVector, newState);
                break;
            case SVT_TANK_STATE_STR_SER:
                PROXRefObject::VectorSetState(PROServiceTank::ObjVector, newState);
                break;
            case SVT_TANK_STATE_STR_LSW:
                PROXRefObject::VectorSetState(PROLevelSwitch::ObjVector, newState);
                break;
            case SVT_TANK_STATE_STR_PRE:
                PROXRefObject::VectorSetState(PROTankPressure::ObjVector, newState);
                break;
            }
        }
    }
}

int PROSystemData::LCWriteXML(char *StrBuf) {
    int  tmpPtr = sprintf(StrBuf, "\t<Packet>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<PacketID>SystemData</PacketID>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<TagID>%s</TagID>\r\n", TagName.c_str());
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Trim>%0.1f</Trim>\r\n", TrimValue * RAD_FACTOR);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<List>%0.1f</List>\r\n", ListValue * RAD_FACTOR);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<SeaWaterDensity>%0.4f</SeaWaterDensity>\r\n", SeaWaterDensity);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t</Packet>\r\n");
    return tmpPtr;
}

void PROSystemData::InputLatitude(float NewLatitude) {
    Latitude        = fabs(NewLatitude);                    // NB! Also store Latitude
    const double Ge = 9.780318;
    const double a  = 0.0053024;
    const double b  = -0.0000059;
    double       G  = Ge * (1 + a * sqr(sin(Latitude / RAD_FACTOR)) + b * sqr(sin(2 * Latitude / RAD_FACTOR)));
    PROTank::GravityCorrection = float(G);
}


#ifdef ANWIN
void PROSystemData::LogData(TLiteQuery *LiteQuery) {

	//PROCargoTank::LogSema.Acquire();
	//TLiteQuery *LiteQuery = new TLiteQuery(NULL);
 /*
	time_t rawtime;
	struct tm * ptm;

	time( &rawtime );

	ptm = gmtime ( &rawtime );
*/
	time_t rawtime = GetGMT();
	try {
		AnsiString MyStatusString;
		// LiteConnection is either TLiteConnection already set up
		//LiteQuery->Connection = MainForm->DataLogLiteConnection;

		// retrieve data
		LiteQuery->SQL->Text = "SELECT * FROM ShipDataLog";
		LiteQuery->Execute();

		// append record
		LiteQuery->Append();

		LiteQuery->FieldByName("LogTimeGMT")->AsInteger = rawtime;
		if ( PROAtmReference::PROAtmRefPtr ) {
			float AtmPress;
			if ( PROAtmReference::PROAtmRefPtr->GetFloatValue(SVT_ATM_PRESSURE,0,AtmPress) == GETVAL_NO_ERR){
				LiteQuery->FieldByName("AtmPress")->AsFloat = AtmPress*MH2O_TO_MBAR ;
			}
		}
		if ( TXUSystemData){
			{
				float Trim_m;
				if ( TXUSystemData->GetFloatValue(SVT_TRIM_M,0,Trim_m) == GETVAL_NO_ERR){
					LiteQuery->FieldByName("Trim_m")->AsFloat = Trim_m;
				}
			}
			{
				float List;
				if ( TXUSystemData->GetFloatValue(SVT_LIST_DEG,0,List) == GETVAL_NO_ERR){
					LiteQuery->FieldByName("List")->AsFloat = List;
				}
			}
			}
		if ( PRODraftSystem::PRODraftSysPtr ){
			float MeanDraft;
			if ( PRODraftSystem::PRODraftSysPtr->GetFloatValue(SVT_DRAFT_MID,0,MeanDraft) == GETVAL_NO_ERR){
				LiteQuery->FieldByName("Draft")->AsFloat = MeanDraft;
			}
		}
		if ( PROProjectInfo::IntegratedLoadingComputer ) {
			float Displacement;
			if ( LCStabCalc::StabCalc->GetFloatValue(SVT_S_DISPLACEMENT,0,Displacement) == GETVAL_NO_ERR){
				LiteQuery->FieldByName("Displacement")->AsFloat = Displacement;
			}
		}
		if (PROInclinometer::PROInclinPtr) {
			float RollPeriod;
			if ( PROInclinometer::PROInclinPtr->GetFloatValue(SVT_ROLLING_PERIOD,0,RollPeriod) == GETVAL_NO_ERR){
				LiteQuery->FieldByName("RollPeriod")->AsFloat = RollPeriod;
			}
		}
		LiteQuery->Post();
	}
	__finally{
		//LiteQuery->Free();

	}
	//PROCargoTank::LogSema.Release();
}
void PROSystemData::CleanLogData(TLiteQuery *LiteQuery,int MaxAge) {
	try {
		// retrieve data
		if (MaxAge < 2) {
			MaxAge = 2;
		}
		AnsiString MaxAgeStr = MaxAge;
		LiteQuery->SQL->Text = "DELETE FROM ShipDataLog WHERE LogTimeGMT < strftime('%s', datetime('now', '-"+MaxAgeStr+" days'))";
		LiteQuery->Execute();
		LiteQuery->SQL->Clear();
	}
	__finally{
		//LiteQuery->Free();

	}
	//PROCargoTank::LogSema.Release();

}
#endif
