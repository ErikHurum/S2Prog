#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

int PRODraft::NumberOfPRO       = 0;
int PRODraft::DraftFilterDegree = 0;
#ifdef S2TXU
OS_TIMER PRODraft::FilterTimer;
#endif
PRODraft::PRODraft(int DType) {
    Type = DType;
    NumberOfPRO++;

    Initiate();
}
//---------------------------------------------------------------------------

void PRODraft::Initiate(void) {
    int DraftNum = 0;
    switch (Type) {
    case C_DRAFT_DF:
        Name = "DF";
        DraftNum = 1;
        break;
    case C_DRAFT_DP:
        Name = "DP";
        DraftNum = 2;
        break;
    case C_DRAFT_DS:
        Name = "DS";
        DraftNum = 3;
        break;
    case C_DRAFT_DA:
        Name = "DA";
        DraftNum = 4;
        break;
    case C_DRAFT_DAP:
        Name = "DAP";
        DraftNum = 5;
        break;
    case C_DRAFT_DAS:
        Name = "DAS";
        DraftNum = 6;
        break;
    case C_DRAFT_DFP:
        Name = "DFP";
        DraftNum = 7;
        break;
    case C_DRAFT_DFS:
        Name = "DFS";
        DraftNum = 8;
        break;
    }
    switch (Type) {
    case C_DRAFT_DF :
    case C_DRAFT_DFP:
#ifdef S2TXU
        OS_CREATETIMER(&FilterTimer, SetDraftFilter, 60000);
#endif
        break;
    case C_DRAFT_DP :
    case C_DRAFT_DS :
    case C_DRAFT_DA :
    case C_DRAFT_DAP:
    case C_DRAFT_DAS:
    case C_DRAFT_DFS:
    default         :
        break;
    }

    IDNumber = (C_PRO_DRAFT << 16) + DraftNum;
    HasMetriTapeSns       = false;
    DraftSensor           = NULL;
    DraftAtMark           = 0.0;
    DraftAtPP             = 0.0;
    DLMark1               = 0.0;
    DTMark1               = 0.0;
    DLMark2               = 0.0;
    DTMark2               = 0.0;
    DLPerp                = 0.0;
    DTPerp                = 0.0;

    DSnsToMid             = 0.0;
    DSnsToCL              = 0.0;
    DMarkToMid1           = 0.0;
    DMarkToCL1            = 0.0;
    DMarkToMid2           = 0.0;
    DMarkToCL2            = 0.0;

    DPerpToMid            = 0.0;
    DPerpToCL             = 0.0;

    DLRef1                = 0.0;
    DTRef1                = 0.0;
    DLRef2                = 0.0;
    DTRef2                = 0.0;
    DLFCenter             = 0.0;
    DTFCenter             = 0.0;
    DraftOffset           = 0.0;
    Draft                 = 0.0;
    MarkTable             = NULL;
    DraftStatus           = GETVAL_NOT_AVAILABLE; // Start with this status
    if (DataFromOther) {
        DraftFilterDegree = 0;
    }
    AddToIOObjectList();
    AddToScratchPageVector();

}
//---------------------------------------------------------------------------

PRODraft::~PRODraft(void) {
    // Draftsensor assumed to be deleted via AnalogList[];
    //Only increase: NumberOfPRO--;
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString PRODraft::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord(Type) + CrLfStr;
    if (TagName != "0" && !TagName.IsEmpty() ) {
        LocalString += TabStr2 + KeyWord(C_PRO_TAGNAME) + TagName + CrLfStr;
    }
    if (PRODraftSystem::PRODraftSysPtr->GlobalRefSystem) {
        switch (Type) {
        case C_DRAFT_DF:
        case C_DRAFT_DA:
            LocalString += TabStr2 + KeyWord(C_D_MARK_MID) + FloatToAnsiString(DMarkToMid1) + CrLfStr;
            if (PRODraftSystem::Has2ndMark) {
                LocalString += TabStr2 + KeyWord(C_D_MARK_MID2) + FloatToAnsiString(DMarkToMid2) + CrLfStr;
            }
        case C_DRAFT_DP:
        case C_DRAFT_DS:
        case C_DRAFT_DAP:
        case C_DRAFT_DAS:
        case C_DRAFT_DFP:
        case C_DRAFT_DFS:
            LocalString += TabStr2 + KeyWord(C_D_SNS_MID) + FloatToAnsiString(DSnsToMid) + CrLfStr;
            LocalString += TabStr2 + KeyWord(C_D_SNS_CL) + FloatToAnsiString(DSnsToCL) + CrLfStr;
            break;
        }
    } else {
        LocalString += TabStr2 + KeyWord(C_D_L_MARK) + FloatToAnsiString(DLMark1) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_D_T_MARK) + FloatToAnsiString(DTMark1) + CrLfStr;
        if (PRODraftSystem::Has2ndMark) {
            LocalString += TabStr2 + KeyWord(C_D_L_MARK2) + FloatToAnsiString(DLMark2) + CrLfStr;
            LocalString += TabStr2 + KeyWord(C_D_T_MARK2) + FloatToAnsiString(DTMark2) + CrLfStr;
        }

        LocalString += TabStr2 + KeyWord(C_D_L_PERP) + FloatToAnsiString(DLPerp) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_D_T_PERP) + FloatToAnsiString(DTPerp) + CrLfStr;
    }
    if (DraftSensor) {
        LocalString += DraftSensor->MakeConfigString(2);
    }
    LocalString += TabStr1 + KeyWord(C_DRAFT_END) + CrLfStr;
    LocalString += CrLfStr;

    return (LocalString);
}
//---------------------------------------------------------------------------

bool PRODraft::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning("Draft", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning("Draft", InputKeyWord, ConfigString.LineCount);
                break;
            case C_DRAFT_END:
            case C_AI_END:          // If AI type not found can continue with this
                break;
            case C_PRO_TAGNAME:
                TagName = ConfigString.GetRemainingLine(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_L_MARK  :
                DLMark1 = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_T_MARK  :
                DTMark1 = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_L_MARK2  :
                DLMark2 = ConfigString.ReadDouble(ErrorLine);
                PRODraftSystem::Has2ndMark = true;
                NoError = !ErrorLine;
                break;
            case C_D_T_MARK2  :
                DTMark2 = ConfigString.ReadDouble(ErrorLine);
                PRODraftSystem::Has2ndMark = true;
                NoError = !ErrorLine;
                break;
            case C_D_L_PERP  :
                DLPerp = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_T_PERP  :
                DTPerp = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_SNS_MID :
            case C_D_SNS_MID2:
                DSnsToMid = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_SNS_CL  :
            case C_D_SNS_CL2 :
                DSnsToCL = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_PERP_MID:
                DPerpToMid = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_MARK_MID:
                DMarkToMid1 = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_MARK_MID2:
                DMarkToMid2 = ConfigString.ReadDouble(ErrorLine);
                PRODraftSystem::Has2ndMark = true;
                NoError = !ErrorLine;
                break;
            case C_AI_P906_0110:
            case C_AI_P906_0111:
                {
                    AIPressSensor_mV *AnalogInPtr = new AIPressSensor_mV(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    DraftSensor = AnalogInPtr;
                    DraftSensor->Location = C_AI_LOC_BOTTOM;
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    LevelPressures.push_back((AIPressSensor *)AnalogInPtr);
                    // This sensor will currently not be visible
                    AITempSensor_Pt1000 *tmpTempSnsPtr = new AITempSensor_Pt1000(AnalogInPtr);
                    AnalogInList.push_back((AnalogInput *)tmpTempSnsPtr);
                }
                break;
            case C_AI_ATM_N_Ex:
            case C_AI_ATM_Ex:
            case C_AI_ATM_Ex_H:
            case C_AI_ATM_N_Ex_0_1:
			case C_AI_APT500		  :
			case C_AI_SPT900		  :
            case C_AI_Gen_4_20mA:
                {
                    AIPressSensor_mA *AnalogInPtr = new AIPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    DraftSensor           = AnalogInPtr;
                    DraftSensor->Location = C_AI_LOC_BOTTOM;
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    LevelPressures.push_back((AIPressSensor *)AnalogInPtr);
                }
                break;
            case C_AI_DIFF_PRESSURE_mA:
                {
                    AIDiffPressSensor_mA *AnalogInPtr = new AIDiffPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    DraftSensor           = AnalogInPtr;
                    DraftSensor->Location = C_AI_LOC_BOTTOM;
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    LevelPressures.push_back((AIPressSensor *)AnalogInPtr);
                }
                break;

            case C_AI_MetriTape:
                HasMetriTapeSns = true; {
                    AIMetriTapeSensor *AnalogInPtr = new AIMetriTapeSensor();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    DraftSensor           = AnalogInPtr;
                    DraftSensor->Location = C_AI_LOC_BOTTOM;
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    ModbusSensorSet.insert(AnalogInPtr);
                }
                break;
            case C_AI_AirPurge:
                {
                    AIAirPurgePressSensor *AnalogInPtr = new AIAirPurgePressSensor();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    DraftSensor           = AnalogInPtr;
                    DraftSensor->Location = C_AI_LOC_BOTTOM;
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    ModbusSensorSet.insert(AnalogInPtr);
                }
                break;
            case C_AI_MB_Press_mA   :
                {
                    AIModbusPressSensor_mA *AnalogInPtr = new AIModbusPressSensor_mA();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    DraftSensor           = AnalogInPtr;
                    DraftSensor->Location = C_AI_LOC_BOTTOM;
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    ModbusSensorSet.insert(AnalogInPtr);
                }
                break;
            case C_AI_MB_DiffPre_mA :
                {
                    AIModbusDiffPressSensor_mA *AnalogInPtr = new AIModbusDiffPressSensor_mA();
                    DraftSensor           = AnalogInPtr;
                    DraftSensor->Location = C_AI_LOC_BOTTOM;
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    ModbusSensorSet.insert(AnalogInPtr);
                }
                break;

            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_DRAFT_END));
    CopyAnalogList();
    if (PRODraftSystem::PRODraftSysPtr->GlobalRefSystem) {
        switch (Type) {
        case C_DRAFT_DF:
            DPerpToMid  = PROProjectInfo::LengthBetweenPP / 2.0;
            DPerpToCL   = 0.0;
            break;
        case C_DRAFT_DP:
            DPerpToMid  = 0.0;      // No perpendicular at midship
            DPerpToCL   = -PROProjectInfo::Width / 2.0;
            DMarkToCL1  = DPerpToCL;
            break;
        case C_DRAFT_DS:
            DPerpToMid  = 0.0;      // No perpendicular at midship
            DPerpToCL   = PROProjectInfo::Width / 2.0;
            DMarkToCL1  = DPerpToCL;
            break;
        case C_DRAFT_DA:
            DPerpToMid  = -PROProjectInfo::LengthBetweenPP / 2.0;
            DPerpToCL   = 0.0;
            break;
        case C_DRAFT_DAP:
            DPerpToMid  = -PROProjectInfo::LengthBetweenPP / 2.0;
            DPerpToCL   = -PROProjectInfo::Width / 2.0;
            DMarkToCL1  = DPerpToCL;
            break;
        case C_DRAFT_DAS:
            DPerpToMid  = -PROProjectInfo::LengthBetweenPP / 2.0;
            DPerpToCL   = PROProjectInfo::Width / 2.0;
            DMarkToCL1  = DPerpToCL;
            break;
        case C_DRAFT_DFP:
            DPerpToMid  = PROProjectInfo::LengthBetweenPP / 2.0;
            DPerpToCL   = -PROProjectInfo::Width / 2.0;
            DMarkToCL1  = DPerpToCL;
            break;
        case C_DRAFT_DFS:
            DPerpToMid  = PROProjectInfo::LengthBetweenPP / 2.0;
            DPerpToCL   = PROProjectInfo::Width / 2.0;
            DMarkToCL1  = DPerpToCL;
            break;
        }
        if (MarkTable) {
            float tableDLRef, tableDTRef;
            MarkTable->Calculate(0.0, &tableDLRef, &tableDTRef);
            DLRef1  = tableDLRef  - DSnsToMid;
            DTRef1  = tableDTRef  - DSnsToCL;
        } else {
            DLRef1  = DMarkToMid1 - DSnsToMid;
            DTRef1  = DMarkToCL1  - DSnsToCL;
        }
        if (PRODraftSystem::Has2ndMark) {
            DLRef2      = DMarkToMid2 - DSnsToMid;
            DTRef2      = DMarkToCL2  - DSnsToCL;
        }
        DLFCenter   = DPerpToMid   - DSnsToMid;
        DTFCenter   = DPerpToCL    - DSnsToCL;
    } else {
        if (MarkTable) {
            MarkTable->Calculate(0.0, &DLRef1, &DTRef1);
        } else {
            DLRef1     = DLMark1;
            DTRef1     = DTMark1;
        }
        if (PRODraftSystem::Has2ndMark) {
            DLRef2      = DLMark2;
            DTRef2      = DTMark2;
        }
        DLFCenter = DLPerp;
        DTFCenter = DTPerp;
    }
    for (unsigned i = 0; i < LevelPressures.size(); i++) {
        AIPressSensor *tmpPtr = LevelPressures[i];
        tmpPtr->AddLevelPressSensor(LevelPressures[i]);
    }
    AddAlarms(CompleteAlarmInfoList);
    AddSensorAlarms();

    return (NoError);
}

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PRODraft::SaveSettings(TSNConfigString *SettingsString) {
    if (IsModified || WriteAll) {
        IsModified = false;
        AnsiString LocalString;
        LocalString += TabStr1 + KeyWord(Type) + CrLfStr;
        if (DraftOffset) {
            LocalString += TabStr2 + KeyWord(C_DRAFT_OFFSET) + FloatToAnsiString(DraftOffset) + CrLfStr;
        }
        for (unsigned j = 0; j < AnalogInList.size(); j++) {
            if (AnalogInList[j]) LocalString += AnalogInList[j]->SaveAISettings(1);
        }
        LocalString += TabStr1 + KeyWord(C_DRAFT_END) + CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PRODraft::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                RestoreSettingsWarning((AnsiString)"Draft " + Name + ":\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"Draft " + Name + ":\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_CT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
            case C_DRAFT_END:
                Key = C_DRAFT_END;
                break;
            case C_DRAFT_OFFSET:
                DraftOffset = SettingsString->ReadDouble(ErrorLine);
                break;
            case C_AI_Pt1000            :
            case C_AI_P906_0111         :
            case C_AI_ATM_N_Ex          :
            case C_AI_ATM_Ex            :
            case C_AI_ATM_Ex_H          :
            case C_AI_ATM_N_Ex_0_1      :
			case C_AI_APT500		  	:
			case C_AI_SPT900		  	:
            case C_AI_Gen_4_20mA        :
            case C_AI_DIFF_PRESSURE_mA  :
            case C_AI_MB_Press_mA       :
            case C_AI_MB_DiffPre_mA     :
            case C_AI_MetriTape         :
            case C_AI_HSH_LNG_Float     :
            case C_AI_AirPurge          :
                {
                    int AIIDNumber = SettingsString->ReadInteger(ErrorLine);
                    AnalogInput *AnalogInPtr = (AnalogInput *)FindObject(AIIDNumber);
                    if (AnalogInPtr) AnalogInPtr->RestoreAISettings(SettingsString);
                }
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_DRAFT_END));
    return (NoError);
}


//---------------------------------------------------------------------------

void PRODraft::Calculate(void) {
    bool  HasResult = false;

    if (DataFromOther) {
        DraftStatus = GETVAL_NO_ERR;
        HasResult   = true;
    } else if (DraftSensor) {
        if (HasMetriTapeSns) {
            if (DraftSensor->ActiveAlarms) {
                DraftStatus = GETVAL_HW_ALARM;
            } else {
                float tmpLevel = DraftSensor->Calculate();
                if (tmpLevel >= LEVEL_NOISE_LIMIT_METRI_TAPE) {
                    Draft = tmpLevel + DraftSensor->Distance - DraftOffset;
                    HasResult = true;
                } else {
                    DraftStatus = GETVAL_DRY_SENSOR;
                    DraftAtMark = 0.0;
                    DraftAtPP   = 0.0;
                }
            }
        } else {
            if (DraftSensor->ActiveAlarms) {
                DraftStatus = GETVAL_HW_ALARM;
            } else {
                float SWDensity = (PROSystemData::SeaWaterDensity - D_AIR_ADJ);
                if (SWDensity < MIN_SW_DENSITY) {
                    SWDensity = DNS_SEA_WATER;
                }
                float Pressure = DraftSensor->Calculate();
                if (Pressure >= LEVEL_NOISE_LIMIT_DRAFT) {
                    Draft = Pressure / SWDensity * PROTank::GravityCorrection + DraftSensor->Distance - DraftOffset;
                    HasResult = true;
                } else {
                    DraftStatus = GETVAL_DRY_SENSOR;
                    DraftAtMark = 0.0;
                    DraftAtPP   = 0.0;
                }
            }
        }
    }

    if (HasResult) {
        if (MarkTable) {
            if (PRODraftSystem::PRODraftSysPtr->GlobalRefSystem) {
                float tableDLRef, tableDTRef;
                MarkTable->Calculate(Draft, &tableDLRef, &tableDTRef);
                DLRef1 = tableDLRef  - DSnsToMid;
                DTRef1 = tableDTRef  - DSnsToCL;
            } else {
                MarkTable->Calculate(Draft, &DLRef1, &DTRef1);
            }
        }
        switch (Type) {
        case C_DRAFT_DF:
        case C_DRAFT_DA:
        case C_DRAFT_DAP:
        case C_DRAFT_DAS:
        case C_DRAFT_DFP:
        case C_DRAFT_DFS:
            {
                float NewDraftAtMark = Draft + TrimListCorrectionRef();
                float NewDraftAtPP   = Draft + TrimListCorrectionFC();
                DraftAtMark  = FilterVal(DraftAtMark, NewDraftAtMark, DraftFilterDegree);
                DraftAtPP    = FilterVal(DraftAtPP, NewDraftAtPP, DraftFilterDegree);
            }
            break;
        case C_DRAFT_DP:
        case C_DRAFT_DS:
            {
                float NewDraftAtPP   = Draft + TrimListCorrectionFC();
                DraftAtPP = FilterVal(DraftAtPP, NewDraftAtPP, DraftFilterDegree);
                DraftAtMark  = DraftAtPP;
            }
            break;
        }
        DraftStatus = GETVAL_NO_ERR;
    }
    SendData();
}

float PRODraft::TrimListCorrectionRef(void) {
    return PROSystemData::TrimListCorrection(DLRef1, DTRef1);
}
float PRODraft::TrimListCorrectionFC(void) {
    return PROSystemData::TrimListCorrection(DLFCenter, DTFCenter);
}


int  PRODraft::GetCalcVal(float *DraftPP, float *DraftMark) {
    if (DraftPP) {
        *DraftPP = DraftAtPP;
    }
    if (DraftMark) {
        *DraftMark = DraftAtMark;
    }
    return (DraftStatus);
}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int PRODraft::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_DRAFT:
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        MyRetValue = Draft;
        Status     = DraftStatus;
        break;
    case SVT_LEVEL_OFFSET:
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        MyRetValue = DraftOffset;
        Status     = GETVAL_NO_ERR;
        break;
    case SVT_MB_MA_PRESSURE:
        // Assume only one Modbus level sensor for one tank
        if ( DraftSensor ) {
            Status = DraftSensor->GetValue(SVT_AI_CALC_VAL, 0, MyRetValue, DecPnt, Unit);
        }
        break;
    case SVT_AP_LPRESS_SNS_FAIL     :
    case SVT_AP_LEVEL_PRESSURE_MB   :
    case SVT_AP_LEVEL_PRESSURE_MH2O :
        if (DraftSensor) {
            Status = DraftSensor->GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        }
        break;

    case SVT_BP :
    case SVT_BP_OFFSET :
    case SVT_BP_GAIN :
    case SVT_BP_ENABLE :
    case SVT_BP_SERIAL_NO :
        {
            Unit = PRESSURE_UNIT1;
            DecPnt = 3;
			int  SnsValId = SVT_NOT_DEFINED;
            switch (ValueId) {
			case SVT_BP_GAIN :
				SnsValId = SVT_AI_GAIN;
                break;
            case SVT_BP_OFFSET :
                SnsValId = SVT_AI_OFFSET;
                break;
            case SVT_BP :
                SnsValId = SVT_AI_CALC_VAL;
                break;
            case SVT_BP_ENABLE :
                SnsValId = SVT_AI_ENABLE;
                break;
            case SVT_BP_SERIAL_NO :
                SnsValId = SVT_AI_SERIAL_NUMBER;
                break;

            }
            if (DraftSensor) {
                Status = DraftSensor->GetValue( SnsValId, Index, MyRetValue, DecPnt, Unit );
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    default:
        Status = PRogramObject::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int PRODraft::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //  default:
    Status = PRogramObject::GetStringValue(ValueId, Index, MyString);
    //      break;
    //}
    return (Status);
}


int PRODraft::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_DRAFT:
        {
            // Should have E.g.
            float NewDft = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, 0.0, PRODraftSystem::MaxSummerDraft, 0.0);
            if (Status == E_NO_ERR) {
                DraftOffset -=  NewDft - DraftAtMark;
                SetDraftFilterTimer(0);
            }
        }
        break;
    case SVT_DRAFT_PP:
        {
            // Should have E.g.
            float NewDft = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, 0.0, PRODraftSystem::MaxSummerDraft, 0.0);
            if (Status == E_NO_ERR) {
                DraftOffset -=  NewDft - DraftAtPP;
                SetDraftFilterTimer(0);
            }
        }
        break;
    case SVT_LEVEL_OFFSET:
        DraftOffset = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, -1.0, 1.0, DraftOffset);
        if (Status == E_NO_ERR) {
            SetDraftFilterTimer(0);
        }
        break;
    case SVT_ZEROSET_LEVEL:
        if (!LevelPressures.empty()) {
            AnsiString TmpString = ZeroSetDraftSensors(Local);
#ifndef BORLAND
            if (Local && TmpString.Length()) {
                AnsiString Text1("Zero set warnings:");
                DisplayMessage(Text1, TmpString);
            }
#endif
            /*
            for ( unsigned i=0; i < LevelPressures.size(); i++ ) {
                    int ErrorStatus = LevelPressures[i]->PutValue(SVT_AI_CALC_VAL,"0.0",Local);
                    if ( Local && ErrorStatus != E_NO_ERR ) {
                            TmpString += Name + ": "+InputErrorMsg[ErrorStatus]+ '\n';
                    }
                    if ( ErrorStatus ) Status = E_NOT_ADJUSTABLE;
            }
            */

        } else {
            Status = LevelPressures[0]->PutValue(SVT_AI_CALC_VAL, Index, "0.0", Local);
        }
        break;
    default:
        Status = PRogramObject::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
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

int PRODraft::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_METRI_TAPE_SNS:
        if (DraftSensor) {
            DraftSensor->NewValue(NewValue);
            DraftSensor->Calculate();
            DraftSensor->ActiveAlarms = CheckAlarms(DraftSensor->AlarmSet, &DraftSensor->HWFailure);
            DraftSensor->SendData();
        }
        break;
    case SVT_HART_MA                :
    case SVT_HART_RADAR             :
    case SVT_HART_STATUS            :
    case SVT_HART_OPEN_LOOP         :
    case SVT_HART_SHORT_CIRCUIT     :
    case SVT_AP_LEVEL_PRESSURE_MB   :
    case SVT_AP_LEVEL_PRESSURE_MH2O :
    case SVT_AP_LPRESS_SNS_FAIL     :
        if (DraftSensor) {
            DraftSensor->PutFloatValue(ValueId, NewValue);
            switch (ValueId) {
            case SVT_HART_RADAR:
            case SVT_AP_LEVEL_PRESSURE_MH2O:
            case SVT_AP_LEVEL_PRESSURE_MB:
                DraftSensor->SendData();
                break;
            default:
                break;
            }
        }
        break;
    case SVT_DRAFT                  :
        Draft = NewValue;
        break;
    case SVT_MB_MA_PRESSURE:
        if (DraftSensor) {
            DraftSensor->NewValue(NewValue);
            DraftSensor->SendData();
            DraftSensor->ActiveAlarms = CheckAlarms(DraftSensor->AlarmSet, &DraftSensor->HWFailure);
        }
        break;
    default:
        Status = PRogramObject::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);

}

ValueList* PRODraft::GetValueInfoTableStatic(int &Entries, int Index) {
    Entries = 0;
    return (NULL);
}

void PRODraft::SetDraftFilterTimer(int TempFilterDegree) {
#ifdef S2TXU
    DraftFilterDegree = TempFilterDegree;
    OS_RetriggerTimer(&FilterTimer);
#endif
}

void PRODraft::SetDraftFilter(void) {
    DraftFilterDegree = FILTER_DRAFT;
}

int PRODraft::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch (pCH->CommandNo) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2732  *pData = (ANPRO10_COMMAND_2732 *)data;
            DraftAtMark   = pData->DraftAtMark;
            DraftAtPP     = pData->DraftAtPP;
            Draft         = pData->Draft;
            DraftStatus   = pData->DraftStatus;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            ANPRO10_COMMAND_2733  *pData = (ANPRO10_COMMAND_2733 *)data;
            ErrorStatus = E_OK;
            DraftOffset = pData->DraftOffset;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}


int PRODraft::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch (cmd) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2732 Cmd;
            Cmd.TxInfo.Port        = NULL;
            Cmd.TxInfo.rxAddr      = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId        = DEVICE_BROADCAST_TXU;

            Cmd.Data.ObjectId      = IDNumber;
            Cmd.Data.ndb           = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo     = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.DraftAtMark   = DraftAtMark;
            Cmd.Data.DraftAtPP     = DraftAtPP;
            Cmd.Data.DraftStatus   = DraftStatus;
            Cmd.Data.Draft         = Draft;
            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2733 Cmd;
            Cmd.TxInfo.Port           = NULL;
            Cmd.TxInfo.rxAddr         = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId           = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId         = IDNumber;
            Cmd.Data.ndb              = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo        = CMD_GENERIC_STATIC_DATA;
            Cmd.Data.DraftOffset      = DraftOffset;

            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

float PRODraft::GetLDistanceMarkToPP(void) {
    return DLRef1 - DLFCenter;
}


AnsiString PRODraft::ZeroSetDraftSensors(bool Local) {
    AnsiString TmpString;
    for (unsigned i = 0; i < LevelPressures.size(); i++) {
        int ErrorStatus = LevelPressures[i]->AdjustSensorF(0.0, Local);
        if (Local && ErrorStatus != E_NO_ERR) {
            TmpString += Name + ": " + GetErrorMsg(ErrorStatus) + '\n';
        }
    }
    return (TmpString);
}


ValueList PRODraft::DraftValueList[ ]  = {

	{ L_WORD1073, L_WORD1073, SVT_SUBMENU  },
	{ L_WORD552, L_WORD552, SVT_DRAFT  },
	{ L_WORD550, L_WORD1068, SVT_LEVEL_OFFSET },
	{ L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
};
#define EXTERNAL_OBJECTS    5
ValueList* PRODraft::GetValueInfoTable(int &Entries, int Index) {
#ifdef ANWIN
    ValueList SubMenuEnd=   { L_WORD813, L_WORD813, SVT_SUBMENU_END };
    ValueList SubMenuStart[EXTERNAL_OBJECTS];

    ValueList  *VInfoList[EXTERNAL_OBJECTS] = {NULL, NULL, NULL, NULL, NULL};
    int ExtEntries[EXTERNAL_OBJECTS] = { 0, 0, 0, 0, 0,};
    int Cnt = 0;
	if ( !PROTank::TankVector.empty()){
        ValueList TankSubMenuStart=   { L_WORD1074, L_WORD1074, SVT_SUBMENU };
		VInfoList[Cnt] = PROTank::TankVector[0]->GetValueInfoTable(ExtEntries[Cnt],Index);
        SubMenuStart[Cnt]=  TankSubMenuStart;
        Cnt++;
    }
    if ( !PROLinePressure::ObjVector.empty()){
        ValueList LPressSubMenuStart=   { L_WORD1075, L_WORD1075, SVT_SUBMENU };
		VInfoList[Cnt] = PROLinePressure::ObjVector[0]->GetValueInfoTable(ExtEntries[Cnt],Index);
        SubMenuStart[Cnt]=  LPressSubMenuStart;
        Cnt++;
    }
	Entries = NELEMENTS(DraftValueList);
    for (int i =0; i < Cnt; i++) {
        if (VInfoList[i]) {
            Entries   += ExtEntries[i]+1;  // Exclude "Unused" and add SubMenuStart and SubMenuEnd
        }
    }
    ValueList *CombinedList = new ValueList[Entries];
    // First copy my own table (PRODraft)
    memcpy(CombinedList,DraftValueList, sizeof(DraftValueList) );
    char *ValKeyPtr = (char*)&CombinedList[NELEMENTS(DraftValueList)];
    for (int i =0; i < Cnt; i++) {
		if (VInfoList[i]) {
			// First SubMenu
			int NumberOfBytesToCopy = sizeof(ValueList);
			memcpy(ValKeyPtr,(char*)&SubMenuStart[i], NumberOfBytesToCopy);
			ValKeyPtr += NumberOfBytesToCopy;
			// Don't include "Unused"
			NumberOfBytesToCopy = sizeof(ValueList)*(ExtEntries[i]-1);
			memcpy(ValKeyPtr,&VInfoList[i][1], NumberOfBytesToCopy);
			ValKeyPtr += NumberOfBytesToCopy;
			// End Submenu
			NumberOfBytesToCopy = sizeof(ValueList);
			memcpy(ValKeyPtr,(char*)&SubMenuEnd, NumberOfBytesToCopy);
            ValKeyPtr += NumberOfBytesToCopy;
		}
    }
    return CombinedList;
#else
    return GetValueInfoTableStatic( Entries, Index );
#endif
}



