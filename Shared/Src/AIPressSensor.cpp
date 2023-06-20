#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif


float AIPressSensor::AtmPressure = NORMAL_ATM;
set<AIPressSensor *>AIPressSensor::ObjectSet;


//---------------------------------------------------------------------------

AIPressSensor::AIPressSensor(bool IsAtmRef) {
    Initialize();
    BasicSensorType     = AI_SENSOR_PRESS;
    BasicSensorTypeWord = L_WORD339; //Pres
    RefPressDiff        = 0.0;
    if ( !IsAtmRef ) {
        ObjectSet.insert(this);
    }
}
//---------------------------------------------------------------------------

AIPressSensor::AIPressSensor(int SnsType, bool IsAtmRef) {
    Initialize();
    Type      = SnsType;
    BasicSensorTypeWord = L_WORD339; //Pres
    RefPressDiff        = 0.0;
    if ( !IsAtmRef ) {
        ObjectSet.insert(this);
    }
}
//---------------------------------------------------------------------------

AIPressSensor::~AIPressSensor(void) {
    set<AIPressSensor *>::iterator it = ObjectSet.find(this);

    if ( it != ObjectSet.end() ) {
        ObjectSet.erase(this);
    }
}
//---------------------------------------------------------------------------
void AIPressSensor::Initialize(void) {
    CableLengthShip          = 0.0;
    CableLengthSensor        = 0.0;
    CableResistanceShip      = PROProjectInfo::CableResistanceShip;
    CableResistanceSensor    = PROProjectInfo::CableResistanceSensor;
    CableMsrdResistance      = 0.0;
    hasCableLengthSensor     = false;
    hasCableResistanceShip   = false;
    hasCableResistanceSensor = false;
    NoShortCircuitAlarm      = false;

}
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString AIPressSensor::MakeConfigString(int ExtraTabs) {
    AnsiString TabStr1 = AnsiString::StringOfChar('\t', 1 + ExtraTabs);
    AnsiString TabStr2 = AnsiString::StringOfChar('\t', 2 + ExtraTabs);
    AnsiString TabStr3 = AnsiString::StringOfChar('\t', 3 + ExtraTabs);
    AnsiString TabStr4 = AnsiString::StringOfChar('\t', 4 + ExtraTabs);
    AnsiString TabStr5 = AnsiString::StringOfChar('\t', 5 + ExtraTabs);
    AnsiString TabStr6 = AnsiString::StringOfChar('\t', 6 + ExtraTabs);
    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord(Type) + CrLfStr;
    LocalString += AnalogInput::MakeConfigString();     //common

    if ( IsPressureSns                      ) LocalString += TabStr2 + KeyWord(C_AI_TANK_PRESS        ) + CrLfStr;
    if ( Location == C_AI_LOC_TANK_CLEAN    ) LocalString += TabStr2 + KeyWord(C_AI_LOC_TANK_CLEAN    ) + CrLfStr;
    if ( NoShortCircuitAlarm                ) LocalString += TabStr2 + KeyWord( C_AI_NO_SHORT_CIRC_AL ) + CrLfStr;

    switch ( Type ) {
    case C_AI_1728      :
    case C_AI_P906_0111 :
        {
            AIPressSensor_mV *temSensor = (AIPressSensor_mV *)this;
            if (CableLengthShip) {
                LocalString += TabStr2 + KeyWord(C_AI_CABLE_LENGTH_SHIP) + FloatToAnsiString(CableLengthShip) + CrLfStr;
            }
            if (hasCableLengthSensor) {
                LocalString += TabStr2 + KeyWord(C_AI_CABLE_LENGTH_SENS) + FloatToAnsiString(CableLengthSensor) + CrLfStr;
            }
            if (CableResistanceShip != SHIP_BOARD_CABLE_RES) {
                LocalString += TabStr2 + KeyWord(C_AI_CABLE_RES_SHIP) + FloatToAnsiString(CableResistanceShip) + CrLfStr;
            }
            if (CableResistanceSensor != TEMP_SENS_CABLE_RES) {
                LocalString += TabStr2 + KeyWord(C_AI_CABLE_RES_SENS) + FloatToAnsiString(CableResistanceSensor) + CrLfStr;
            }
            if (CableMsrdResistance) {
                LocalString += TabStr2 + KeyWord(C_AI_CABLE_RES_MSRD) + FloatToAnsiString(CableMsrdResistance) + CrLfStr;
            }
            LocalString += TabStr2 + KeyWord(C_AI_FRO);
            for ( int ind = 0; ind < MAX_MV_CALDATA; ind++ ) {
                LocalString += TabStr1 + (AnsiString)temSensor->FRO[ind];
            }
            LocalString += CrLfStr;

            LocalString += TabStr2 + KeyWord(C_AI_G1);
            for ( int ind = 0; ind < MAX_MV_CALDATA; ind++ ) {
                LocalString += TabStr1 + (AnsiString)temSensor->G1[ind];
            }
            LocalString += CrLfStr;

            LocalString += TabStr2 + KeyWord(C_AI_G2);
            for ( int ind = 0; ind < MAX_MV_CALDATA; ind++ ) {
                LocalString += TabStr1 + (AnsiString)temSensor->G2[ind];
            }
            LocalString += CrLfStr;

            LocalString += TabStr2 + KeyWord(C_AI_G3);
            for ( int ind = 0; ind < MAX_MV_CALDATA; ind++ ) {
                LocalString += TabStr1 + (AnsiString)temSensor->G3[ind];
            }
            LocalString += CrLfStr;

            LocalString += TabStr2 + KeyWord(C_AI_NL1) + (AnsiString)temSensor->NL1 + CrLfStr;
            LocalString += TabStr2 + KeyWord(C_AI_NL2) + (AnsiString)temSensor->NL2 + CrLfStr;
            if ( temSensor->EEPromGain != 1.0 ) {
                LocalString += TabStr2 + KeyWord(C_AI_EEPROM_GAIN) + (AnsiString)temSensor->EEPromGain + CrLfStr;
            }
            if ( temSensor->EEPromOffset != 0.0 ) {
                LocalString += TabStr2 + KeyWord(C_AI_EEPROM_OFFSET) + (AnsiString)temSensor->EEPromOffset + CrLfStr;
            }
        }
        break;
    case C_AI_ATM_N_Ex          :
    case C_AI_ATM_Ex            :
    case C_AI_ATM_Ex_H          :
    case C_AI_ATM_N_Ex_0_1      :
    case C_AI_Gen_4_20mA        :
	case C_AI_DIFF_PRESSURE_mA  :
	case C_AI_APT500		    :
	case C_AI_SPT900		    :
    case C_AI_MB_Press_mA       :
    case C_AI_MB_DiffPre_mA     :

        {
            AIPressSensor_mA *temSensor = (AIPressSensor_mA *)this;
            LocalString += TabStr2 + KeyWord(C_AI_CAL_DATA) + CrLfStr;
            for ( unsigned ind = 0; ind < temSensor->mAPcnt.size(); ind++ ) {
                float Percent = temSensor->mAPcnt[ind] * 100.0;
                float CalVal  = temSensor->mACal[ind] * 1000.0;

                //LocalString +=TabStr3+FloatToAnsiString(Percent,5,1);
                //LocalString +=TabStr1+FloatToAnsiString(CalVal ,5,1)+CrLfStr;
                LocalString += TabStr3 + FloatToAnsiString(temSensor->mAPcnt[ind] * 100.0, 5, 1);
                LocalString += TabStr1 + FloatToAnsiString(temSensor->mACal[ind] * 1000.0, 5, 1) + CrLfStr;
            }
            LocalString += TabStr2 + KeyWord(C_T_TABLE_END) + CrLfStr;;
            LocalString += TabStr2 + KeyWord(C_AI_TZS) + FloatToAnsiString(temSensor->TZS, 5, 3) + CrLfStr;
            LocalString += TabStr2 + KeyWord(C_AI_TSS) + FloatToAnsiString(temSensor->TSS, 5, 3) + CrLfStr;
        }
        break;
    }
    LocalString += TabStr1 + KeyWord(C_AI_END) + CrLfStr;
    LocalString += CrLfStr;

    return (LocalString);
}
//---------------------------------------------------------------------------

bool AIPressSensor::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    AnsiString PROName = "Pressure sensor";
    if ( PROPtr )	PROName += (AnsiString)", for " + PROPtr->Name;
    PROName += ":\n";
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning(PROName, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning(PROName, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_START_COMMON:
                AnalogInput::LoadConfigString(ConfigString);
                break;
            case C_AI_TANK_PRESS:
                IsPressureSns = true;
                break;
            case C_AI_LOC_TANK_CLEAN:
                IsPressureSns = true;
                Location = C_AI_LOC_TANK_CLEAN;
                break;
            case C_AI_CABLE_LENGTH_SHIP:
                CableLengthShip     = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_CABLE_LENGTH_SENS2:
            case C_AI_CABLE_LENGTH_SENS:
                hasCableLengthSensor = true;
                CableLengthSensor    = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_CABLE_RES_SHIP   :
                hasCableResistanceShip = true;
                CableResistanceShip    = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_CABLE_RES_SENS   :
                hasCableResistanceSensor = true;
                CableResistanceSensor    = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_CABLE_RES_MSRD   :
                CableMsrdResistance = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_AI_CAL_DATA:
                {
                    AIPressSensor_mA *tmpSensor = (AIPressSensor_mA *)this;
                    do {
                        float Percent = ConfigString.ReadDouble(ErrorLine, C_T_TABLE_END);
                        float mAmp;
                        if ( !ErrorLine ) {
                            mAmp = ConfigString.ReadDouble(ErrorLine, C_T_TABLE_END);
                        }
                        if ( !ErrorLine ) {
                            tmpSensor->mAPcnt.push_back(Percent / 100.0);
                            tmpSensor->mACal.push_back(mAmp / 1000.0);
                            tmpSensor->mACor.push_back(mAmp / 1000.0);
                        }
                    } while ( !ErrorLine );
                    if ( ErrorLine == END_FOUND ) {
                        // End found, Permitted in this case, so ErrorStatus set to 0
                        ErrorLine = 0;
                        if ( tmpSensor->mAPcnt.empty() || tmpSensor->mACal.empty() ) {
                            float Percent[2] = { 0.0, 100.0 };
                            float mAmp[2] = { 4.0, 20.0 };
                            tmpSensor->mAPcnt.clear();
                            tmpSensor->mACal.clear();
                            tmpSensor->mACor.clear();
                            for ( int i = 0; i < 2; i++ ) {
                                tmpSensor->mAPcnt.push_back(Percent[i] / 100.0);
                                tmpSensor->mACal.push_back(mAmp[i] / 1000.0);
                                tmpSensor->mACor.push_back(mAmp[i] / 1000.0);
                            }
                        }
                    }
                }
                break;
            case C_AI_FRO:
                {
                    AIPressSensor_mV *temSensor = (AIPressSensor_mV *)this;
                    for ( int ind = 0; ind < MAX_MV_CALDATA; ind++ ) {
                        temSensor->FRO[ind] = ConfigString.ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                    }
                }
                break;
            case C_AI_G1:
                {
                    AIPressSensor_mV *temSensor = (AIPressSensor_mV *)this;
                    for ( int ind = 0; ind < MAX_MV_CALDATA; ind++ ) {
                        temSensor->G1[ind] = ConfigString.ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                    }
                }
                break;
            case C_AI_G2:
                {
                    AIPressSensor_mV *temSensor = (AIPressSensor_mV *)this;
                    for ( int ind = 0; ind < MAX_MV_CALDATA; ind++ ) {
                        temSensor->G2[ind] = ConfigString.ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                    }
                }
                break;
            case C_AI_G3:
                {
                    AIPressSensor_mV *temSensor = (AIPressSensor_mV *)this;
                    for ( int ind = 0; ind < MAX_MV_CALDATA; ind++ ) {
                        temSensor->G3[ind] = ConfigString.ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                    }
                }
                break;
            case C_AI_NL1:
                {
                    AIPressSensor_mV *temSensor = (AIPressSensor_mV *)this;
                    temSensor->NL1 = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_AI_NL2:
                {
                    AIPressSensor_mV *temSensor = (AIPressSensor_mV *)this;
                    temSensor->NL2 = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_AI_TZS:
                {
                    AIPressSensor_mA *temSensor = (AIPressSensor_mA *)this;
                    temSensor->TZS = ConfigString.ReadDouble(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_AI_TSS:
                {
                    AIPressSensor_mA *temSensor = (AIPressSensor_mA *)this;
                    temSensor->TSS = ConfigString.ReadDouble(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_AI_EEPROM_GAIN:
                {
                    AIPressSensor_mV *temSensor = (AIPressSensor_mV *)this;
                    float tmpGain = ConfigString.ReadDouble(ErrorLine);
                    if ( tmpGain > MIN_GAIN && tmpGain > MAX_GAIN ) {
                        temSensor->EEPromGain = tmpGain;
                    } else {
                        temSensor->EEPromGain = 1.000;
                    }
                    NoError = !ErrorLine;
                }
                break;
            case C_AI_EEPROM_OFFSET:
                {
                    AIPressSensor_mV *temSensor = (AIPressSensor_mV *)this;
                    temSensor->EEPromOffset = ConfigString.ReadDouble(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_AI_NO_SHORT_CIRC_AL:
                NoShortCircuitAlarm = true;
                break;
            case C_AI_END:
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_AI_END) );
    switch ( Type  ) {
    case C_AI_ATM_N_Ex          :
    case C_AI_ATM_Ex            :
    case C_AI_ATM_Ex_H          :
    case C_AI_ATM_N_Ex_0_1      :
	case C_AI_APT500		    :
	case C_AI_SPT900		    :
    case C_AI_Gen_4_20mA        :
    case C_AI_DIFF_PRESSURE_mA  :
    case C_AI_Radar_4_20mA      :
    case C_AI_MB_Press_mA       :
    case C_AI_MB_DiffPre_mA     :
        {
            AIPressSensor_mA *tmpSensor = (AIPressSensor_mA *)this;
            if ( tmpSensor->mAPcnt.empty() || tmpSensor->mACal.empty() ) {
                float Percent[2]    = { 0.0, 100.0 };
                float mAmp[2]       = { 4.0, 20.0 };
                tmpSensor->mAPcnt.clear();
                tmpSensor->mACal.clear();
                tmpSensor->mACor.clear();
                for ( int i = 0; i < 2; i++ ) {
                    tmpSensor->mAPcnt.push_back(Percent[i] / 100.0);
                    tmpSensor->mACal.push_back(mAmp[i] / 1000.0);
                    tmpSensor->mACor.push_back(mAmp[i] / 1000.0);
                }
            }
        }
        if (!NoShortCircuitAlarm) {
            AddShortCircuitAlarm();
        }
        break;
    case C_AI_MB_Press_0_20mA   :
    case C_AI_MB_DiffPre_0_20mA :
        {
            AIPressSensor_mA *tmpSensor = (AIPressSensor_mA *)this;
            if ( tmpSensor->mAPcnt.empty() || tmpSensor->mACal.empty() ) {
                float Percent[2]    = { 0.0, 100.0 };
                float mAmp[2]       = { 0.0, 20.0 };
                tmpSensor->mAPcnt.clear();
                tmpSensor->mACal.clear();
                tmpSensor->mACor.clear();
                for ( int i = 0; i < 2; i++ ) {
                    tmpSensor->mAPcnt.push_back(Percent[i] / 100.0);
                    tmpSensor->mACal.push_back(mAmp[i] / 1000.0);
                    tmpSensor->mACor.push_back(mAmp[i] / 1000.0);
                }
            }
        }
        break;
    default:
        break;
    }
    return (NoError);
}
//---------------------------------------------------------------------------
void AIPressSensor::SetRefSnsPtr(AIPressSensor *SnsPtr) {
    if ( SnsPtr && (SnsPtr->Distance == Distance) || IsPressureSns || SnsPtr->IsPressureSns ) {
        RefPressSensorSet.insert(SnsPtr);
    }
}
///////////////////////////////////////////////////////////////
//
// Routines for Calculation of values
//
///////////////////////////////////////////////////////////////

float AIPressSensor::Calculate(void) {

    if ( CanCalculate() ) {
        float NewCalcValue = Gain * FilteredValue - Offset;
        ResultOK = true;
        switch ( Location ) {
        case C_AI_LOC_REDUNDANCY1   :
        case C_AI_LOC_REDUNDANCY2   :
        case C_AI_LOC_REDUNDANCY3   :
        case C_AI_LOC_BOTTOM        :
        case C_AI_LOC_MIDDLE        :
        case C_AI_LOC_UPPER         :
            NewCalcValue -= CalcRefPressure();
            break;
        default:
            break;

        }
        CalcValue = NewCalcValue;
    }
    return (CalcValue);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int  AIPressSensor::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    Unit = GetUnitId(&DecPnt);

    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
        MyRetValue = Offset;
        break;
    case SVT_AI_CALC_VAL :
        if ( !CanCalculate() ) {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        } else {
            MyRetValue = Calculate();
        }
        break;
    default:
        Status = AnalogInput::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int AIPressSensor::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_UNIT:
        {
            int Unit = GetUnitId();
            MyString = GetUnitName(Unit);
        }
        break;
    default:
        Status = AnalogInput::GetStringValue(ValueId, Index, MyString);

    }
    return (Status);
}

int AIPressSensor::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    int Unit = GetUnitId();
    switch ( ValueId ) {
    case SVT_AI_OFFSET   :
		Offset = ConvertToSi(NewValue, ValUnitId = Unit, Status, MinRange/MH2O_TO_BAR-NORMAL_ATM, MaxRange/MH2O_TO_BAR, Offset);
        break;
    case SVT_AI_CALC_VAL :
		{
			float NewVal = ConvertToSi(NewValue, ValUnitId = Unit, Status, MinRange/MH2O_TO_BAR-NORMAL_ATM, MaxRange/MH2O_TO_BAR);
            if ( IsPressureSns ) {
				Status = InputToLinkedRefSensors(SVT_AI_CALC_VAL, NewVal, Local);
            } else {
                if ( Status == E_NO_ERR ) {
                    Status = InputToLinkedLevelSensors(SVT_AI_CALC_VAL, NewVal, Local);
                }
            }
        }
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

int AIPressSensor::PutFloatValue(int ValueId, float NewValue) {
    return (AnalogInput::PutFloatValue(ValueId, NewValue));
}

void AIPressSensor::AdjustOffsets(float OffsetChange, bool Local) {
    if ( Master || !Local ) {
        set<AIPressSensor *>::iterator pBIt;
        for ( pBIt = ObjectSet.begin(); pBIt != ObjectSet.end(); pBIt++ ) {
            (*pBIt)->AdjustOffset(OffsetChange);
        }
    }
}

///////////////////////////////////////////////////////////////////
//
// Sensor check methode her, because here we know the application
//
///////////////////////////////////////////////////////////////////
int AIPressSensor::CheckInput(float Operator_Val, int &Action) {
    int InpStat   = E_NO_ERR;
    if ( Enable ) {
#ifndef WIN32
        if ( RunningTime < ALARM_SYSTEM_DELAY ) {
            InpStat = E_PLEASE_WAIT;
            Action  = SNS_ADJUST_ABORT;
        } else
#endif
        if ( ActiveAlarms ) {
            InpStat = E_SENSOR_ERROR;
            Action  = SNS_ADJUST_ABORT;
        } else {
            if ( PROPtr ) {
                switch ( PROPtr->Type ) {
                case C_PRO_DRAFT_SYSTEM   :
                case C_PRO_DRAFT          :
                case C_DRAFT_DF     :
                case C_DRAFT_DP     :
                case C_DRAFT_DS     :
                case C_DRAFT_DA     :
                case C_DRAFT_DAP    :
                case C_DRAFT_DAS    :
                case C_DRAFT_DFP    :
                case C_DRAFT_DFS    :
                    //Action = SNS_ADJUST_OFFSET;
                    //break;
                case C_PRO_ATMREFSENS     :
                case C_PRO_TANKPRESS      :
                case C_PRO_TANK           :
                case C_PRO_CARGO          :
                case C_PRO_BALLAST        :
                case C_PRO_HFO            :
                case C_PRO_DO             :
                case C_PRO_LUB            :
                case C_PRO_FW             :
                case C_PRO_MISC           :
                case C_PRO_VOIDSPACE      :
                    if ( CalcValue > SNS_ADJUST_GAIN_THRESHOLD ) {
                        // Adjust gain
                        float GainCorrection = Operator_Val / CalcValue;
                        if ( (GainCorrection > SNS_ADJUST_MAX_GAIN) ||
                             (GainCorrection < SNS_ADJUST_MIN_GAIN) ) {
                            InpStat = E_GAIN_OUT_OF_RANGE;
                            Action  = SNS_ADJUST_ABORT;
                        } else {
                            Action  = SNS_ADJUST_GAIN;
                        }
                    } else {
                        Action = SNS_ADJUST_OFFSET;
                    }
                    break;
                case C_PRO_LINEPRESS      :
                    if ( CalcValue > SNS_ADJUST_LP_GAIN_THRESHOLD ) {
                        // Adjust gain
                        float GainCorrection = Operator_Val / CalcValue;
                        if ( (GainCorrection > SNS_ADJUST_LP_MAX_GAIN) ||
                             (GainCorrection < SNS_ADJUST_LP_MIN_GAIN) ) {
                            InpStat = E_GAIN_OUT_OF_RANGE;
                            Action  = SNS_ADJUST_ABORT;
                        }
                    } else {
                        Action = SNS_ADJUST_OFFSET;
                    }
                    break;
                }

            } else {
                InpStat = E_INVALID_POINTER;
                Action  = SNS_ADJUST_ABORT;
            }
        }
    } else {
        InpStat = E_SENSOR_IS_DISABELED;
        Action  = SNS_ADJUST_ABORT;
    }

    return (InpStat);
}

int AIPressSensor::GetUnitId(int *DecPntPtr) {
    int Unit;
    int DecPnt = 0;
    switch ( Location ) {
    default:
        Unit       = PRESSURE_UNIT1;
        DecPnt     = 1;
        break;
    case C_AI_LOC_BOTTOM:
    case C_AI_LOC_MIDDLE:
    case C_AI_LOC_UPPER  :
    case C_AI_LOC_PUMP_ROOM:
    case C_AI_LOC_ENGINE_ROOM:
    case C_AI_LOC_REDUNDANCY1:
    case C_AI_LOC_REDUNDANCY2:
    case C_AI_LOC_REDUNDANCY3:
        Unit       = PRESSURE_UNIT2;
        DecPnt     = 3;
        break;
    case C_AI_LOC_NOT_DEFINED:
    case C_AI_LOC_SYSTEM  :
    case C_AI_LOC_VAPOUR  :
        Unit       = PRESSURE_UNIT1;
        DecPnt     = 1;
        break;
    case C_AI_LOC_LINE:
        Unit       = PRESSURE_UNIT3;
        DecPnt     = 1;
        break;
    }
    if ( DecPntPtr ) {
        *DecPntPtr = DecPnt;
    }
    return (Unit);
}

//---------------------------------------------------------------------------
//
void AIPressSensor::AddTempRefSensor(float *TmpPtr) {
    TempPtr = TmpPtr;
}

float AIPressSensor::CalcRefPressure(void) {
    float AvgPressure = 0.0;
    if ( !RefPressSensorSet.empty() ) {
        float PressureSum = 0.0;
        int Count         = 0;
        float MaxPress    = -MAXFLOAT;
        float MinPress    = MAXFLOAT;
        set<AIPressSensor *>::iterator pBIt;
        for ( pBIt = RefPressSensorSet.begin(); pBIt != RefPressSensorSet.end(); pBIt++ ) {
            AIPressSensor *SnsPtr = *pBIt;
            if ( SnsPtr->CanCalculate() ) {
                Count++;
                float Pessure = SnsPtr->Calculate();
                PressureSum  += Pessure;
                MaxPress      = max(MaxPress, Pessure);
                MinPress      = min(MinPress, Pessure);
                RefPressDiff  = MaxPress - MinPress;
            }
        }
        if ( Count ) {
            AvgPressure = PressureSum / Count;
        }
    }
    return AvgPressure;
}

int AIPressSensor::InputToLinkedRefSensors(int ValueId, float NewValue, bool Local) {
    int   ErrStatus      = E_NO_ERR;
    float OrgOffsetSum   = 0.0;
    float NewOffsetSum   = 0.0;
    int   Count          = 0;
    if ( !RefPressSensorSet.empty() ) {
        set<AIPressSensor *>::iterator pBIt;
        for ( pBIt = RefPressSensorSet.begin(); pBIt != RefPressSensorSet.end(); pBIt++ ) {
            AIPressSensor *SnsPtr = *pBIt;
            if ( SnsPtr->CanCalculate() ) {
                Count++;
                OrgOffsetSum += SnsPtr->Offset;
                ErrStatus     = SnsPtr->AdjustSensorF(NewValue, Local);
                NewOffsetSum += SnsPtr->Offset;
            }
        }
        if ( Count ) {
            float AvgOffsetChange = (OrgOffsetSum - NewOffsetSum) / Count;
            for ( pBIt = SensorSet.begin(); pBIt != SensorSet.end(); pBIt++ ) {
                AIPressSensor *SnsPtr = *pBIt;
                SnsPtr->Offset  -= AvgOffsetChange;
            }
        }
    }
    if ( ErrStatus != E_NO_ERR ) {
        ErrStatus = E_INPUT_ERR;
    }
    return ErrStatus;
}

int AIPressSensor::InputToLinkedLevelSensors(int ValueId, float NewValue, bool Local) {
    int   ErrStatus      = E_NO_ERR;
    if ( !SensorSet.empty() ) {
        set<AIPressSensor *>::iterator pBIt;
        for ( pBIt = SensorSet.begin(); pBIt != SensorSet.end(); pBIt++ ) {
            AIPressSensor *SnsPtr = *pBIt;
            ErrStatus = SnsPtr->AdjustSensorF(NewValue, Local);
        }
    }
    if ( ErrStatus != E_NO_ERR ) {
        ErrStatus = E_INPUT_ERR;
    }
    return ErrStatus;
}

void AIPressSensor::AddLevelPressSensor(AIPressSensor *SnsPtr) {
    if ( SnsPtr ) {
        if ( IsPressureSns ) {
            SensorSet.insert(SnsPtr);
        } else {
            switch ( Location ) {
            case C_AI_LOC_REDUNDANCY1   :
            case C_AI_LOC_REDUNDANCY2   :
            case C_AI_LOC_REDUNDANCY3   :
                switch ( SnsPtr->Location ) {
                case C_AI_LOC_REDUNDANCY1   :
                case C_AI_LOC_REDUNDANCY2   :
                case C_AI_LOC_REDUNDANCY3   :
                    SensorSet.insert(SnsPtr);
                    break;
                default:
                    break;
                }
                break;
            default:
                if ( Distance == SnsPtr->Distance ) {
                    SensorSet.insert(SnsPtr);
                }
                break;
            }
        }
    }
}

void AIPressSensor::SetTmpSnsPtr(AITempSensor *SnsPtr) {
}

AITempSensor* AIPressSensor::GetTmpSnsPtr(void) {
    return NULL;
}

void AIPressSensor::AdjustOffset(float OffsetAdjust) {
    Offset += OffsetAdjust;
}

void AIPressSensor::AddShortCircuitAlarm(void)
{
}

#ifdef ANWIN

void AIPressSensor::PrepareDatabase(TLiteQuery *LiteQuery)
{
	//LogSema.Acquire();
	//TLiteQuery *LiteQuery = new TLiteQuery(NULL);
    try {
        // LiteConnection is either TLiteConnection already set up
        //LiteQuery->Connection = MainForm->SensorLogLiteConnection;
		// retrieve data
        LiteQuery->Close();
		LiteQuery->SQL->Text = "SELECT * FROM Sensors";
		LiteQuery->Execute();
		set<AIPressSensor *>::iterator pBIt;
		for (pBIt = ObjectSet.begin(); pBIt != ObjectSet.end(); pBIt++) {
			(*pBIt)->AddSensorRecord(LiteQuery);
		}
    }
    __finally{
        //LiteQuery->Free();

    }
	//LogSema.Release();
}

void AIPressSensor::AddSensorRecord(TLiteQuery *LiteQuery)
{
	if ( !IsallreadyAdded(LiteQuery)){
		try {

			// append record
			LiteQuery->Append();
			LiteQuery->FieldByName("Id")->AsInteger          = IDNumber;
			LiteQuery->FieldByName("SerialNumber")->AsString = SerialNumber;
			LiteQuery->Post();
		}
		__finally{

		}
	}
}

bool AIPressSensor::IsallreadyAdded(TLiteQuery *LiteQuery){
	bool AlreadyAdded = true;
	//LogSema.Acquire();

	//TLiteQuery *LiteQuery = new TLiteQuery(NULL);
    try {
		//LiteQuery->Connection = MainForm->SensorLogLiteConnection;
		LiteQuery->SQL->Text = "SELECT * FROM Sensors";
		LiteQuery->Execute();
		TField *tmpFiledPtr1 = LiteQuery->FindField("Id");

		//LiteQuerySensorLog->SQL->Clear();
		if (tmpFiledPtr1 ) {
			AnsiString SQLText = "SELECT * FROM Sensors";
			SQLText += " WHERE Id=" + AnsiString(IDNumber);
			// retrieve data
			LiteQuery->SQL->Text = SQLText;

			LiteQuery->Execute();
			// retrieve data
			//	ShowMessage("Records of this alarm= "+IntToStr(LiteQuery->FetchRows));

			AlreadyAdded =  bool(LiteQuery->RecordCount);
		}
	}
	__finally{
		//LiteQuery->Free();
	}
	//LogSema.Release();

	return AlreadyAdded;
}

void AIPressSensor::LogData(TLiteQuery *LiteQuery,const volatile bool &Terminated, int Delay)
{
	//LogSema.Acquire();

	//TLiteQuery *LiteQuery1 = new TLiteQuery(NULL);
	try {
		//LiteQuery1->CachedUpdates = true;
		// LiteConnection is either TLiteConnection already set up
		//LiteQuery1->Connection = MainForm->SensorLogLiteConnection;

		// retrieve data
		LiteQuery->SQL->Text = "SELECT * FROM SensorDataLog";
		LiteQuery->Execute();

        set<AIPressSensor *>::iterator pBIt;
		for (pBIt = ObjectSet.begin(); !Terminated && pBIt != ObjectSet.end(); pBIt++) {
			(*pBIt)->LogDataFromSensor(LiteQuery);
            Sleep(Delay);
        }
	}
	__finally{
		//LiteQuery1->Free();
	}
	//LogSema.Release();

}
void AIPressSensor::LogDataFromSensor(TLiteQuery *LiteQuery) {

	time_t rawtime = GetGMT();
	try {

		// append record
		LiteQuery->Append();

		LiteQuery->FieldByName("SensorId")->AsInteger   = IDNumber;
		LiteQuery->FieldByName("LogTimeGMT")->AsInteger = rawtime;
		LiteQuery->FieldByName("Pressure")->AsFloat     = CalcValue / MH2O_TO_MBAR;
		LiteQuery->FieldByName("RawValue")->AsFloat  	= FilteredValue;

		LiteQuery->Post();
	}
	__finally{

	}

}
void AIPressSensor::CleanLogDataFromSensor(TLiteQuery *LiteQuery, int MaxAge) {

	try {
		if (MaxAge < 2) {
			MaxAge = 2;
		}
		AnsiString MaxAgeStr = MaxAge;
		LiteQuery->SQL->Text = "DELETE FROM SensorDataLog WHERE LogTimeGMT < strftime('%s', datetime('now', '-"+MaxAgeStr+" days'))";
		LiteQuery->Execute();
		LiteQuery->SQL->Clear();
	}
	__finally{

	}

}

#endif

