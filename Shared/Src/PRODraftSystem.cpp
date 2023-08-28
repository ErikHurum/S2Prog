#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif


set<PRogramObjectBase *>PRODraftSystem::ObjectSet;
ValueList PRODraftSystem::DraftSystemValueList[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },         // {"Unused"           ,"",SVT_BLANK
    { L_WORD430, L_WORD237, SVT_DF_MARK },       // {"DF@Mark"          ,"",SVT_DF_MARK},
    { L_WORD431, L_WORD237, SVT_DA_MARK },       // {"DA@Mark"          ,"",SVT_DA_MARK},
    { L_WORD432, L_WORD237, SVT_DF_PP },         // {"DF@PP"            ,"",SVT_DF_PP},
    { L_WORD433, L_WORD237, SVT_DA_PP },         // {"DA@PP"            ,"",SVT_DA_PP},
    { L_WORD421, L_WORD237, SVT_DP },            // {"DP"               ,"",SVT_DP},
    { L_WORD422, L_WORD237, SVT_DS },            // {"DS"               ,"",SVT_DS},
    { L_WORD1066, L_WORD237, SVT_DFP },           // {"DFP"              ,"",SVT_DFP},
    { L_WORD1067, L_WORD237, SVT_DFS },           // {"DFS"              ,"",SVT_DFS},
    { L_WORD1066, L_WORD237, SVT_DAP },           // {"DAP"              ,"",SVT_DAP
    { L_WORD1067, L_WORD237, SVT_DAS },           // {"DAS"              ,"",SVT_DAS},
    { L_WORD83, L_WORD237, SVT_DENSITY },       // {"Density"          ,"",SVT_DENSITY},
    { L_WORD1086, L_WORD237, SVT_FREEBOARD },     // {"Freeboard"        ,"",SVT_FREEBOARD},

};


//---------------------------------------------------------------------------
PRODraftSystem *PRODraftSystem::PRODraftSysPtr  = NULL;
float PRODraftSystem::MaxSummerDraft            = 50.0;
int PRODraftSystem::NumberOfPRO                 = 0;
bool PRODraftSystem::Has2ndMark                 = false;

PRODraftSystem::PRODraftSystem(void) {
    PRODraftSysPtr = this;
    ObjectSet.insert(this);
    NumberOfPRO++;
    IDNumber = (C_PRO_DRAFT_SYSTEM << 16) + NumberOfPRO;
    Initiate();
}
//---------------------------------------------------------------------------

void PRODraftSystem::Initiate(void) {
    Name               = "DraftSys";
    DraftSystem        = DftNoDef;
    GlobalRefSystem    = false;
    DFPtr              = NULL;
    DPPtr              = NULL;
    DSPtr              = NULL;
    DAPtr              = NULL;
    DAPPtr             = NULL;
    DASPtr             = NULL;
    DFPPtr             = NULL;
    DFSPtr             = NULL;
    TrimValue          = 0.0;
    ListValue          = 0.0;
    DftFwd             = 0.0;
    DftAft             = 0.0;
    DftP               = 0.0;
    DftS               = 0.0;
    DftAftP            = 0.0;
    DftAftS            = 0.0;
    DftFwdP            = 0.0;
    DftFwdS            = 0.0;
    DftFwdMarkP        = 0.0;
    DftFwdMarkS        = 0.0;
    DftAftMarkP        = 0.0;
    DftAftMarkS        = 0.0;
    Deflection         = 0.0;
    MaxDraft           = 0.0;
    MeanDraft          = 0.0;
    HasTrimValue       = false;
    HasListValue       = false;
    HasDeflection      = false;
    StatusDftFwd       = GETVAL_ERROR;
    StatusDftAft       = GETVAL_ERROR;
    StatusDftP         = GETVAL_ERROR;
    StatusDftS         = GETVAL_ERROR;
    StatusDftAftP      = GETVAL_ERROR;
    StatusDftAftS      = GETVAL_ERROR;
    StatusDftFwdP      = GETVAL_ERROR;
    StatusDftFwdS      = GETVAL_ERROR;
    StatusDftMean      = GETVAL_ERROR;
    DraftIndicationAtPP = false;


}
//---------------------------------------------------------------------------

PRODraftSystem::~PRODraftSystem(void) {
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = DraftList.begin(); pBIt != DraftList.end(); pBIt++) {
        delete (*pBIt);
    }
    // Cheat a little to avoid that the sensors are deleted here as this object not is thow owner.
    // The individual drafts are owners
    AnalogInList.clear();
}
//---------------------------------------------------------------------------

void PRODraftSystem::WriteConfigToFile(TSNConfigString &ConfigString) {
    AnsiString LocalString;
    LocalString += KeyWord(C_PRO_DRAFT_SYSTEM) + CrLfStr;
    LocalString += MakeConfigString();       //common
    if (GlobalRefSystem) {
        LocalString += TabStr1 + KeyWord(C_GLOBAL_REFSYS) + CrLfStr;
    }
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = DraftList.begin(); pBIt != DraftList.end(); pBIt++) {
        PRODraft *Element = (PRODraft *)(*pBIt);
        LocalString += Element->MakeConfigString();
    }

    LocalString += TabStr1 + KeyWord(C_MAX_SUMMER_DRAFT) + FloatToAnsiString(MaxSummerDraft) + CrLfStr;
    LocalString += KeyWord(C_PRO_END) + CrLfStr;
    LocalString += CrLfStr;

    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

int PRODraftSystem::LoadConfigFromFile(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
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
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_DRAFT_END:
                break;
            case C_PRO_START_COMMON:
                PRogramObjectBase::LoadConfigString(ConfigString);
                break;
            case C_PRO_START_PRO:
                LoadConfigString(ConfigString);
                break;
            case C_GLOBAL_REFSYS:
                GlobalRefSystem = true;
                break;
            case C_DRAFT_DF:
                if (!DFPtr)  DFPtr = new PRODraft(C_DRAFT_DF);
                DraftList.insert(DFPtr);
                DFPtr->LoadConfigString(ConfigString);
                DFPtr->DataFromOther = DataFromOther;
                for (vector<AnalogInput *>::iterator it = DFPtr->AnalogInList.begin(); it != DFPtr->AnalogInList.end(); ++it) {
                    AnalogInList.push_back(*it);
                }
                break;
            case C_DRAFT_DP:
                if (!DPPtr)   DPPtr = new PRODraft(C_DRAFT_DP);
                DraftList.insert(DPPtr);
                DPPtr->LoadConfigString(ConfigString);
                DPPtr->DataFromOther = DataFromOther;
                for (vector<AnalogInput *>::iterator it = DPPtr->AnalogInList.begin(); it != DPPtr->AnalogInList.end(); ++it) {
                    AnalogInList.push_back(*it);
                }
                break;
            case C_DRAFT_DS:
                if (!DSPtr)   DSPtr = new PRODraft(C_DRAFT_DS);
                DraftList.insert(DSPtr);
                DSPtr->LoadConfigString(ConfigString);
                DSPtr->DataFromOther = DataFromOther;
                for (vector<AnalogInput *>::iterator it = DSPtr->AnalogInList.begin(); it != DSPtr->AnalogInList.end(); ++it) {
                    AnalogInList.push_back(*it);
                }
                break;
            case C_DRAFT_DA:
                if (!DAPtr)       DAPtr = new PRODraft(C_DRAFT_DA);
                DraftList.insert(DAPtr);
                DAPtr->LoadConfigString(ConfigString);
                DAPtr->DataFromOther = DataFromOther;
                for (vector<AnalogInput *>::iterator it = DAPtr->AnalogInList.begin(); it != DAPtr->AnalogInList.end(); ++it) {
                    AnalogInList.push_back(*it);
                }
                break;
            case C_DRAFT_DAP:
                if (!DAPPtr) DAPPtr = new PRODraft(C_DRAFT_DAP);
                DraftList.insert(DAPPtr);
                DAPPtr->LoadConfigString(ConfigString);
                DAPPtr->DataFromOther = DataFromOther;
                for (vector<AnalogInput *>::iterator it = DAPPtr->AnalogInList.begin(); it != DAPPtr->AnalogInList.end(); ++it) {
                    AnalogInList.push_back(*it);
                }
                break;
            case C_DRAFT_DAS:
                if (!DASPtr) DASPtr = new PRODraft(C_DRAFT_DAS);
                DraftList.insert(DASPtr);
                DASPtr->LoadConfigString(ConfigString);
                DASPtr->DataFromOther = DataFromOther;
                for (vector<AnalogInput *>::iterator it = DASPtr->AnalogInList.begin(); it != DASPtr->AnalogInList.end(); ++it) {
                    AnalogInList.push_back(*it);
                }
                break;
            case C_DRAFT_DFP:
                if (!DFPPtr) DFPPtr = new PRODraft(C_DRAFT_DFP);
                DraftList.insert(DFPPtr);
                DFPPtr->LoadConfigString(ConfigString);
                DFPPtr->DataFromOther = DataFromOther;
                for (vector<AnalogInput *>::iterator it = DFPPtr->AnalogInList.begin(); it != DFPPtr->AnalogInList.end(); ++it) {
                    AnalogInList.push_back(*it);
                }
                break;
            case C_DRAFT_DFS:
                if (!DFSPtr) DFSPtr = new PRODraft(C_DRAFT_DFS);
                DraftList.insert(DFSPtr);
                DFSPtr->LoadConfigString(ConfigString);
                DFSPtr->DataFromOther = DataFromOther;
                for (vector<AnalogInput *>::iterator it = DFSPtr->AnalogInList.begin(); it != DFSPtr->AnalogInList.end(); ++it) {
                    AnalogInList.push_back(*it);
                }
                break;
            case C_MAX_SUMMER_DRAFT:
                MaxSummerDraft = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    AddAlarms(CompleteAlarmInfoList);
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = DraftList.begin(); pBIt != DraftList.end(); pBIt++) {
        PRODraft *Element = (PRODraft *)(*pBIt);
        Element->AddCompleteList(CompleteAlarmInfoList);
    }
    if (DFPPtr && DFSPtr && DAPPtr && DASPtr && DPPtr && DSPtr) {
        DraftSystem = DftFwdMidShipAftPS;
    } else if (DFPtr && DPPtr && DSPtr && DAPtr) {
        DraftSystem = DftFwdMidShipAft;
    } else if (DFPtr && DAPtr) {
        DraftSystem = DftFwdAft;
    } else if (DFPtr && DAPPtr && DASPtr) {
        DraftSystem = DftFwdAPortAStbd;
    } else if (DFPPtr && DFSPtr && DAPPtr && DASPtr) {
        DraftSystem = DftCorners;
    } else if (DFPtr) {
        DraftSystem = DftAftOnly;
    } else if (DAPtr) {
        DraftSystem = DftFwdOnly;
    } else if (DataFromOther) {
        DraftSystem = DftFromOther;
    } else {
        DraftSystem = DftNoDef;
        GiveConfigWarning((AnsiString)"Draft:\nUnsupported configuration.\nSome sensors missing?\n");
    }
    SetChildUserRights();
    return ErrorLine;

}

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PRODraftSystem::SaveSettings(TSNConfigString *SettingsString) {
    if (IsModified || WriteAll) {
        IsModified = false;
        AnsiString LocalString = KeyWord(C_PRO_DRAFT_SYSTEM) + CrLfStr;
        SettingsString->AddString(LocalString);
        set<PRogramObjectBase *>::iterator pBIt;
        for (pBIt = DraftList.begin(); pBIt != DraftList.end(); pBIt++) {
            PRODraft *Element = (PRODraft *)(*pBIt);
            Element->SaveSettings(SettingsString);
        }
        LocalString = KeyWord(C_PRO_END) + CrLfStr + CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PRODraftSystem::RestoreSettings(TSNConfigString *SettingsString) {
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
            case C_DRAFT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case C_AI_P906_0110:
            case C_AI_P906_0111:
            case C_AI_ATM_N_Ex:
            case C_AI_ATM_Ex:
            case C_AI_ATM_Ex_H:
            case C_AI_ATM_N_Ex_0_1:
            case C_AI_APT500		  :
            case C_AI_SPT900		  :
            case C_AI_Gen_4_20mA:
            case C_AI_DIFF_PRESSURE_mA:
                {
                    int AIIDNumber = SettingsString->ReadInteger(ErrorLine);
                    AnalogInput *AnalogInPtr = (AnalogInput *)FindObject(AIIDNumber);
                    if (AnalogInPtr) AnalogInPtr->RestoreAISettings(SettingsString);
                }
                break;
            case C_DRAFT_DF  :
                if (DFPtr) {
                    DFPtr->RestoreSettings(SettingsString);
                }
                break;
            case C_DRAFT_DP  :
                if (DPPtr) {
                    DPPtr->RestoreSettings(SettingsString);
                }
                break;
            case C_DRAFT_DS  :
                if (DSPtr) {
                    DSPtr->RestoreSettings(SettingsString);
                }
                break;
            case C_DRAFT_DA  :
                if (DAPtr) {
                    DAPtr->RestoreSettings(SettingsString);
                }
                break;
            case C_DRAFT_DAP :
                if (DAPPtr) {
                    DAPPtr->RestoreSettings(SettingsString);
                }
                break;
            case C_DRAFT_DAS :
                if (DASPtr) {
                    DASPtr->RestoreSettings(SettingsString);
                }
                break;
            case C_DRAFT_DFP :
                if (DFPPtr) {
                    DFPPtr->RestoreSettings(SettingsString);
                }
                break;
            case C_DRAFT_DFS :
                if (DFSPtr) {
                    DFSPtr->RestoreSettings(SettingsString);
                }
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    return (NoError);
}


//---------------------------------------------------------------------------
void PRODraftSystem::Calculate(void) {
    HWFailure = false;
    switch (DraftSystem) {
    case DftFwdOnly:
        StatusDftFwd = DFPtr->GetCalcVal(&DftFwd, &DftFwdMark);
        if (!StatusDftFwd) {
            DftAft =  DftFwd - PROInclinometer::TrimValue * PROProjectInfo::LengthBetweenPP;
            HasTrimValue = false;
            MeanDraft     = (DftFwd + DftAft) / 2.0;
            StatusDftMean = GETVAL_NO_ERR;
        } else {
            MeanDraft     = 0.0;
        }
        // Now, we can calculate DP, DS
        DftP = (DftFwd + DftAft) / 2 - PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
        DftS = (DftFwd + DftAft) / 2 + PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
        // Should check inclinometer status
        StatusDftAft = StatusDftFwd;
        StatusDftP   = StatusDftFwd;
        StatusDftS   = StatusDftFwd;
        HasListValue = false;
        break;
    case DftAftOnly:
        StatusDftAft = DAPtr->GetCalcVal(&DftAft, &DftAftMark);
        if (!StatusDftAft) {
            DftFwd =  DftAft + PROInclinometer::TrimValue * PROProjectInfo::LengthBetweenPP;
            HasTrimValue = false;
            MeanDraft     = (DftFwd + DftAft) / 2.0;
            StatusDftMean = GETVAL_NO_ERR;
        } else {
            MeanDraft     = 0.0;
        }
        // Now, we can calculate DP, DS
        DftP = (DftFwd + DftAft) / 2 - PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
        DftS = (DftFwd + DftAft) / 2 + PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
        // Should check inclinometer status
        StatusDftFwd = StatusDftAft;
        StatusDftP   = StatusDftAft;
        StatusDftS   = StatusDftAft;
        HasListValue = false;
        break;
    case DftFwdAft:
        StatusDftFwd = DFPtr->GetCalcVal(&DftFwd, &DftFwdMark);
        StatusDftAft = DAPtr->GetCalcVal(&DftAft, &DftAftMark);
        if (!StatusDftFwd && !StatusDftAft) {
            TrimValue = (DftFwd - DftAft) / PROProjectInfo::LengthBetweenPP;
            HasTrimValue = true;
        } else if (!StatusDftFwd) {
            DftAft =  DftFwd - PROInclinometer::TrimValue * PROProjectInfo::LengthBetweenPP;
            HasTrimValue = false;
        } else if (!StatusDftAft) {
            DftFwd =  DftAft + PROInclinometer::TrimValue * PROProjectInfo::LengthBetweenPP;
            HasTrimValue = false;
        }
        // Now, we can calculate DP, DS
        DftP = (DftFwd + DftAft) / 2 - PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
        DftS = (DftFwd + DftAft) / 2 + PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
        // Should check inclinometer status
        if (!StatusDftFwd || !StatusDftAft) {
            StatusDftP    = GETVAL_NOT_MEASURED;
            StatusDftS    = GETVAL_NOT_MEASURED;
            MeanDraft     = (DftFwd + DftAft) / 2.0;
            StatusDftMean = GETVAL_NO_ERR;
        } else {
            if ((StatusDftFwd == GETVAL_HW_ALARM) && (StatusDftFwd == GETVAL_HW_ALARM)) {
                StatusDftP   = GETVAL_HW_ALARM;
                StatusDftS   = GETVAL_HW_ALARM;
            } else if ((StatusDftFwd == GETVAL_DRY_SENSOR) && (StatusDftFwd == GETVAL_DRY_SENSOR)) {
                StatusDftP   = GETVAL_DRY_SENSOR;
                StatusDftS   = GETVAL_DRY_SENSOR;
            } else {
                StatusDftP   = GETVAL_UNKNOWN_ERROR;
                StatusDftS   = GETVAL_UNKNOWN_ERROR;
            }
            MeanDraft    = 0.0;
        }

        HasListValue  = false;
        break;
    case DftFwdAPortAStbd:
        {
            float DraftAftAtMarkP = 0.0, DraftAftAtMarkS = 0.0;
            float DraftAftAtPPP   = 0.0, DraftAftAtPPS  = 0.0;
            float CurrentList = 0.0;
            StatusDftFwd  = DFPtr->GetCalcVal(&DftFwd, &DftFwdMark);
            StatusDftAftP   = DAPPtr->GetCalcVal(&DraftAftAtPPP, &DraftAftAtMarkP);
            StatusDftAftS   = DASPtr->GetCalcVal(&DraftAftAtPPS, &DraftAftAtMarkS);
            if (!StatusDftAftP && !StatusDftAftS) {
                StatusDftAft = GETVAL_NOT_MEASURED;
                StatusDftP   = GETVAL_NOT_MEASURED;
                StatusDftS   = GETVAL_NOT_MEASURED;
                DftAft       = (DraftAftAtPPP + DraftAftAtPPS) / 2;
                DftAftMark   = (DraftAftAtMarkP + DraftAftAtMarkS) / 2;
                CurrentList  = (DraftAftAtPPS - DraftAftAtPPP) / PROProjectInfo::Width;
                ListValue    = CurrentList;
                HasListValue = true;
            } else {
                CurrentList = PROInclinometer::ListValue;
                HasListValue  = false;
                if (!StatusDftAftP) {
                    StatusDftAft = GETVAL_NOT_MEASURED;
                    StatusDftP   = GETVAL_NOT_MEASURED;
                    StatusDftS   = GETVAL_NOT_MEASURED;
                    // Assume that we must use the inclinometer
                    DftAft     = DraftAftAtPPP   - CurrentList * PROProjectInfo::Width / 2;
                    DftAftMark = DraftAftAtMarkP - CurrentList * PROProjectInfo::Width / 2;
                } else if (!StatusDftAftS) {
                    StatusDftAft = GETVAL_NOT_MEASURED;
                    StatusDftP   = GETVAL_NOT_MEASURED;
                    StatusDftS   = GETVAL_NOT_MEASURED;
                    // Assume that we must use the inclinometer
                    DftAft     = DraftAftAtPPS   + CurrentList * PROProjectInfo::Width / 2;
                    DftAftMark = DraftAftAtMarkS + CurrentList * PROProjectInfo::Width / 2;
                } else {
                    StatusDftAft  = GETVAL_ERROR;
                    StatusDftP    = GETVAL_ERROR;
                    StatusDftS    = GETVAL_ERROR;
                    StatusDftMean = GETVAL_ERROR;
                    MeanDraft     = 0.0;
                }
            }
            // Now, we can calculate DP, DS
            if (!StatusDftFwd && (!StatusDftP || !StatusDftS)) {
                MeanDraft     = (DftFwd + DftAft) / 2.0;
                StatusDftMean = GETVAL_NO_ERR;
                DftP          = MeanDraft - CurrentList * PROProjectInfo::Width / 2;
                DftS          = MeanDraft + CurrentList * PROProjectInfo::Width / 2;
                TrimValue     = (DftFwd - DftAft) / PROProjectInfo::LengthBetweenPP;
                HasTrimValue  = true;

            } else {
                HasTrimValue = false;
                MeanDraft     = 0.0;
                StatusDftMean = GETVAL_ERROR;
            }
        }
        break;
    case DftFwdMidShipAft:
        {
            StatusDftFwd = DFPtr->GetCalcVal(&DftFwd, &DftFwdMark);
            StatusDftAft = DAPtr->GetCalcVal(&DftAft, &DftAftMark);
            StatusDftP   = DPPtr->GetCalcVal(&DftP);
            StatusDftS   = DSPtr->GetCalcVal(&DftS);
            if (!StatusDftFwd && !StatusDftAft && !StatusDftP && !StatusDftS) {
                TrimValue = (DftFwd - DftAft) / PROProjectInfo::LengthBetweenPP;
                ListValue = (DftS  - DftP) / PROProjectInfo::Width;
                Deflection = (DftFwd + DftAft) / 2 - (DftS + DftP) / 2;
                HasListValue  = true;
                HasTrimValue  = true;
                HasDeflection = true;
                MeanDraft     = (DftFwd + DftAft + DftP + DftS) / 4;
                StatusDftMean = GETVAL_NO_ERR;
            } else if (!StatusDftFwd && !StatusDftAft) {
                TrimValue     = (DftFwd - DftAft) / PROProjectInfo::LengthBetweenPP;
                HasTrimValue  = true;
                HasDeflection = false;
                Deflection    = 0.0;
                float DftM    = (DftFwd + DftAft) / 2.0;
                MeanDraft     = DftM;
                StatusDftMean = GETVAL_NO_ERR;
                if (!StatusDftP) {
                    HasListValue = true;
                    ListValue = (DftM - DftP) * 2.0 / PROProjectInfo::Width;
                    DftS = (DftFwd + DftAft) / 2 + ListValue * PROProjectInfo::Width / 2.0;
                } else if (!StatusDftS) {
                    HasListValue = true;
                    ListValue = (DftS - DftM) * 2.0 / PROProjectInfo::Width;
                    DftP = (DftFwd + DftAft) / 2 - ListValue * PROProjectInfo::Width / 2.0;
                } else {
                    DftP = (DftFwd + DftAft) / 2 - PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
                    DftS = (DftFwd + DftAft) / 2 + PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
                    HasListValue = false;
                }
            } else if (!StatusDftP && !StatusDftS) {
                ListValue = (DftS  - DftP) / PROProjectInfo::Width;
                HasListValue = true;
                HasDeflection = false;
                Deflection   = 0.0;
                float DftM   = (DftP + DftS) / 2.0;
                MeanDraft    = DftM;
                StatusDftMean = GETVAL_NO_ERR;
                if (!StatusDftFwd) {
                    HasTrimValue = true;
                    TrimValue = (DftFwd - DftM) * 2.0 / PROProjectInfo::LengthBetweenPP;
                    DftAft    = DftFwd - TrimValue / PROProjectInfo::LengthBetweenPP;
                } else if (!StatusDftAft) {
                    HasTrimValue = true;
                    TrimValue = (DftM - DftAft) * 2.0 / PROProjectInfo::LengthBetweenPP;
                    DftFwd    = DftAft + TrimValue / PROProjectInfo::LengthBetweenPP;
                } else {
                    DftAft    = DftM - PROInclinometer::TrimValue * PROProjectInfo::LengthBetweenPP / 2.0;
                    DftFwd    = DftM + PROInclinometer::TrimValue * PROProjectInfo::LengthBetweenPP / 2.0;
                    HasTrimValue = false;
                }
            } else {
                MeanDraft     = 0.0;
                StatusDftMean = GETVAL_ERROR;
                HasListValue  = false;
                HasTrimValue  = false;
                HasDeflection = false;
            }
        }
        break;
    case DftCorners:
        {
            StatusDftFwdP = DFPPtr->GetCalcVal(&DftFwdP, &DftFwdMarkP);
            StatusDftFwdS = DFSPtr->GetCalcVal(&DftFwdS, &DftFwdMarkS);
            StatusDftAftP = DAPPtr->GetCalcVal(&DftAftP, &DftAftMarkP);
            StatusDftAftS = DASPtr->GetCalcVal(&DftAftS, &DftAftMarkS);
            if (!StatusDftFwdP && !StatusDftFwdS && !StatusDftAftP && !StatusDftAftS) {
                DftFwdMark    = (DftFwdMarkP + DftFwdMarkS) / 2.0;
                DftAftMark    = (DftAftMarkP + DftAftMarkS) / 2.0;
                DftFwd        = (DftFwdP + DftFwdS) / 2.0;
                DftAft        = (DftAftP + DftAftS) / 2.0;
                DftP          = (DftFwdP + DftAftP) / 2.0;
                DftS          = (DftFwdS + DftAftS) / 2.0;

                TrimValue     = (DftFwd - DftAft) / PROProjectInfo::LengthBetweenPP;
                ListValue     = (DftS  - DftP) / PROProjectInfo::Width;
                HasListValue  = true;
                HasTrimValue  = true;
                MeanDraft     = (DftFwd + DftAft + DftS + DftP) / 4.0;
                StatusDftMean = GETVAL_NO_ERR;
                StatusDftFwd  = GETVAL_NOT_MEASURED;
                StatusDftAft  = GETVAL_NOT_MEASURED;
                StatusDftP    = GETVAL_NOT_MEASURED;
                StatusDftS    = GETVAL_NOT_MEASURED;

            } else if (!StatusDftAftP && !StatusDftAftS) {
                HasListValue  = true;
                ListValue     = (DftAftS - DftAftP) / PROProjectInfo::Width;
                DftAftMark    = (DftAftMarkP + DftAftMarkS) / 2.0;
                DftAft        = (DftAftP + DftAftS) / 2.0;

                if (!StatusDftFwdP) {
                    HasTrimValue = true;
                    DftFwdS    = DftFwdP + DftAftS - DftAftP;
                    TrimValue  = (DftFwdP - DftAftP) / PROProjectInfo::LengthBetweenPP;
                } else if (!StatusDftFwdS) {
                    HasTrimValue = true;
                    DftFwdP    = DftFwdS + DftAftP - DftAftS;
                    TrimValue  = (DftFwdS - DftAftS) / PROProjectInfo::LengthBetweenPP;
                } else {
                    HasTrimValue  = false;
                }
                if (HasTrimValue) {
                    DftFwdMark  = (DftFwdMarkP + DftFwdMarkS) / 2.0;
                    DftFwd      = (DftFwdP + DftFwdS) / 2.0;
                    DftP        = (DftFwdP + DftAftP) / 2.0;
                    DftS        = (DftFwdS + DftAftS) / 2.0;
                } else {
                    DftFwd      =  DftAft + PROInclinometer::TrimValue * PROProjectInfo::LengthBetweenPP;
                    DftFwdMark  =  DftFwd + PROInclinometer::TrimValue * (DFPPtr->GetLDistanceMarkToPP() + DFSPtr->GetLDistanceMarkToPP()) / 2.0;
                    DftP        = (DftFwd + DftAft) / 2 - PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
                    DftS        = (DftFwd + DftAft) / 2 + PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
                }
                MeanDraft     = (DftFwd + DftAft + DftS + DftP) / 4.0;
                StatusDftMean = GETVAL_NOT_MEASURED;
                StatusDftFwd  = GETVAL_NOT_MEASURED;
                StatusDftAft  = GETVAL_NOT_MEASURED;
                StatusDftP    = GETVAL_NOT_MEASURED;
                StatusDftS    = GETVAL_NOT_MEASURED;
            } else if (!StatusDftFwdP && !StatusDftFwdS) {
                HasListValue    = true;
                ListValue       = (DftFwdS - DftFwdP) / PROProjectInfo::Width;
                DftFwdMark      = (DftFwdMarkP + DftFwdMarkS) / 2.0;
                DftFwd          = (DftFwdP + DftFwdS) / 2.0;

                if (!StatusDftAftP) {
                    HasTrimValue = true;
                    DftAftS      = DftAftP + DftFwdS - DftFwdP;
                    TrimValue    = (DftFwdP - DftAftP) / PROProjectInfo::LengthBetweenPP;
                } else if (!StatusDftAftS) {
                    HasTrimValue = true;
                    DftAftP      = DftAftS + DftFwdP - DftFwdS;
                    TrimValue    = (DftFwdS - DftAftS) / PROProjectInfo::LengthBetweenPP;
                } else {
                    HasTrimValue  = false;
                }
                if (HasTrimValue) {
                    DftAftMark  = (DftAftMarkP + DftAftMarkS) / 2.0;
                    DftAft      = (DftFwdP + DftFwdS) / 2.0;
                    DftP        = (DftFwdP + DftAftP) / 2.0;
                    DftS        = (DftFwdS + DftAftS) / 2.0;
                } else {
                    DftAft      =  DftFwd - PROInclinometer::TrimValue * PROProjectInfo::LengthBetweenPP;
                    DftAftMark  =  DftAft - PROInclinometer::TrimValue * (DFPPtr->GetLDistanceMarkToPP() + DFSPtr->GetLDistanceMarkToPP()) / 2.0;
                    DftP        = (DftFwd + DftAft) / 2 - PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
                    DftS        = (DftFwd + DftAft) / 2 + PROInclinometer::ListValue * PROProjectInfo::Width / 2.0;
                }
                MeanDraft     = (DftFwd + DftAft + DftS + DftP) / 4.0;
                StatusDftMean = GETVAL_NOT_MEASURED;
                StatusDftFwd  = GETVAL_NOT_MEASURED;
                StatusDftAft  = GETVAL_NOT_MEASURED;
                StatusDftP    = GETVAL_NOT_MEASURED;
                StatusDftS    = GETVAL_NOT_MEASURED;
            } else {
                MeanDraft     = 0.0;
                HasListValue  = false;
                HasTrimValue  = false;
                StatusDftMean = GETVAL_NOT_AVAILABLE;
                StatusDftFwd  = GETVAL_NOT_AVAILABLE;
                StatusDftAft  = GETVAL_NOT_AVAILABLE;
                StatusDftP    = GETVAL_NOT_AVAILABLE;
                StatusDftS    = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case DftFwdMidShipAftPS:
        {
            StatusDftFwdP = DFPPtr->GetCalcVal(&DftFwdP, &DftFwdMarkP);
            StatusDftFwdS = DFSPtr->GetCalcVal(&DftFwdS, &DftFwdMarkS);
            StatusDftAftP = DAPPtr->GetCalcVal(&DftAftP, &DftAftMarkP);
            StatusDftAftS = DASPtr->GetCalcVal(&DftAftS, &DftAftMarkS);
            // Only use measured draft for DP, DS
            StatusDftP    = DPPtr->GetCalcVal(&DftP);
            StatusDftS    = DSPtr->GetCalcVal(&DftS);
            if (!StatusDftFwdP && !StatusDftFwdS && !StatusDftAftP && !StatusDftAftS) {
                DftFwdMark    = (DftFwdMarkP + DftFwdMarkS) / 2.0;
                DftAftMark    = (DftAftMarkP + DftAftMarkS) / 2.0;
                DftFwd        = (DftFwdP + DftFwdS) / 2.0;
                DftAft        = (DftAftP + DftAftS) / 2.0;

                TrimValue     = (DftFwd - DftAft) / PROProjectInfo::LengthBetweenPP;
                ListValue     = (DftS  - DftP) / PROProjectInfo::Width;
                HasListValue  = true;
                HasTrimValue  = true;
                MeanDraft     = (DftFwd + DftAft + DftS + DftP) / 4.0;
                StatusDftMean = GETVAL_NO_ERR;
                StatusDftFwd  = GETVAL_NOT_MEASURED;
                StatusDftAft  = GETVAL_NOT_MEASURED;

            } else if (!StatusDftAftP && !StatusDftAftS) {
                HasListValue  = true;
                ListValue     = (DftAftS - DftAftP) / PROProjectInfo::Width;
                DftAftMark    = (DftAftMarkP + DftAftMarkS) / 2.0;
                DftAft        = (DftAftP + DftAftS) / 2.0;

                if (!StatusDftFwdP) {
                    HasTrimValue = true;
                    DftFwdS    = DftFwdP + DftAftS - DftAftP;
                    TrimValue  = (DftFwdP - DftAftP) / PROProjectInfo::LengthBetweenPP;
                } else if (!StatusDftFwdS) {
                    HasTrimValue = true;
                    DftFwdP    = DftFwdS + DftAftP - DftAftS;
                    TrimValue  = (DftFwdS - DftAftS) / PROProjectInfo::LengthBetweenPP;
                } else {
                    HasTrimValue  = false;
                }
                if (HasTrimValue) {
                    DftFwdMark  = (DftFwdMarkP + DftFwdMarkS) / 2.0;
                    DftFwd      = (DftFwdP + DftFwdS) / 2.0;
                    DftP        = (DftFwdP + DftAftP) / 2.0;
                    DftS        = (DftFwdS + DftAftS) / 2.0;
                } else {
                    DftFwd      =  DftAft + PROInclinometer::TrimValue * PROProjectInfo::LengthBetweenPP;
                    DftFwdMark  =  DftFwd + PROInclinometer::TrimValue * (DFPPtr->GetLDistanceMarkToPP() + DFSPtr->GetLDistanceMarkToPP()) / 2.0;
                }
                MeanDraft     = (DftFwd + DftAft + DftS + DftP) / 4.0;
                StatusDftMean = GETVAL_NOT_MEASURED;
                StatusDftFwd  = GETVAL_NOT_MEASURED;
                StatusDftAft  = GETVAL_NOT_MEASURED;
            } else if (!StatusDftFwdP && !StatusDftFwdS) {
                HasListValue    = true;
                ListValue       = (DftFwdS - DftFwdP) / PROProjectInfo::Width;
                DftFwdMark      = (DftFwdMarkP + DftFwdMarkS) / 2.0;
                DftFwd          = (DftFwdP + DftFwdS) / 2.0;

                if (!StatusDftAftP) {
                    HasTrimValue = true;
                    DftAftS      = DftAftP + DftFwdS - DftFwdP;
                    TrimValue    = (DftFwdP - DftAftP) / PROProjectInfo::LengthBetweenPP;
                } else if (!StatusDftAftS) {
                    HasTrimValue = true;
                    DftAftP      = DftAftS + DftFwdP - DftFwdS;
                    TrimValue    = (DftFwdS - DftAftS) / PROProjectInfo::LengthBetweenPP;
                } else {
                    HasTrimValue  = false;
                }
                if (HasTrimValue) {
                    DftAftMark  = (DftAftMarkP + DftAftMarkS) / 2.0;
                    DftAft      = (DftFwdP + DftFwdS) / 2.0;
                } else {
                    DftAft      =  DftFwd - PROInclinometer::TrimValue * PROProjectInfo::LengthBetweenPP;
                    DftAftMark  =  DftAft - PROInclinometer::TrimValue * (DFPPtr->GetLDistanceMarkToPP() + DFSPtr->GetLDistanceMarkToPP()) / 2.0;
                }
                MeanDraft     = (DftFwd + DftAft + DftS + DftP) / 4.0;
                StatusDftMean = GETVAL_NOT_MEASURED;
                StatusDftFwdP = GETVAL_NOT_MEASURED;
                StatusDftAftS = GETVAL_NOT_MEASURED;
            } else {
                MeanDraft     = 0.0;
                HasListValue  = false;
                HasTrimValue  = false;
                StatusDftMean = GETVAL_NOT_AVAILABLE;
                StatusDftFwd  = GETVAL_NOT_AVAILABLE;
                StatusDftAft  = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case DftFromOther:
        TrimValue    = (DftFwd - DftAft) / PROProjectInfo::LengthBetweenPP;
        ListValue    = (DftS  - DftP) / PROProjectInfo::Width;
        HasListValue = true;
        HasTrimValue = true;
        break;
    case DftNoDef:
    default:

        break;
    }
    float TmpMaxDraft = 0.0;
    if (!StatusDftAft) {
        if (DraftIndicationAtPP) {
            TmpMaxDraft = max(TmpMaxDraft, DftAft);
        } else {
            TmpMaxDraft = max(TmpMaxDraft, DftAftMark);
        }
    }
    if (!StatusDftFwd) {
        if (DraftIndicationAtPP) {
            TmpMaxDraft = max(TmpMaxDraft, DftFwd);
        } else {
            TmpMaxDraft = max(TmpMaxDraft, DftFwdMark);
        }
    }

    if (!StatusDftAft) {
        if (DraftIndicationAtPP) {
            TmpMaxDraft = max(TmpMaxDraft, DftAft);
        } else {
            TmpMaxDraft = max(TmpMaxDraft, DftAftMark);
        }
    }
    if (!StatusDftP) {
        TmpMaxDraft = max(TmpMaxDraft, DftP);
    }
    if (!StatusDftS) {
        TmpMaxDraft = max(TmpMaxDraft, DftS);
    }
    if (!StatusDftAftP) {
        if (DraftIndicationAtPP) {
            TmpMaxDraft = max(TmpMaxDraft, DftAftP);
        } else {
            TmpMaxDraft = max(TmpMaxDraft, DftAftMarkP);
        }
    }
    if (!StatusDftAftS) {
        if (DraftIndicationAtPP) {
            TmpMaxDraft = max(TmpMaxDraft, DftAftS);
        } else {
            TmpMaxDraft = max(TmpMaxDraft, DftAftMarkS);
        }
    }
    if (!StatusDftFwdP) {
        if (DraftIndicationAtPP) {
            TmpMaxDraft = max(TmpMaxDraft, DftFwdP);
        } else {
            TmpMaxDraft = max(TmpMaxDraft, DftFwdMarkP);
        }
    }
    if (!StatusDftFwdS) {
        if (DraftIndicationAtPP) {
            TmpMaxDraft = max(TmpMaxDraft, DftFwdS);
        } else {
            TmpMaxDraft = max(TmpMaxDraft, DftFwdMarkS);
        }
    }
    MaxDraft    = TmpMaxDraft;
    SendData();
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int PRODraftSystem::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_DA:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        if (DraftIndicationAtPP) {
            MyRetValue = DftAft;
        } else {
            MyRetValue = DftAftMark;
        }
        if (HWFailure) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftAft;
        }
        break;
    case SVT_DA_MARK:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = DftAftMark;
        if (HWFailure) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftAft;
        }
        break;
    case SVT_DA_PP:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = DftAft;
        if (HWFailure) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftAft;
        }
        break;
    case SVT_DF:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        if (DraftIndicationAtPP) {
            MyRetValue = DftFwd;
        } else {
            MyRetValue = DftFwdMark;
        }
        if (HWFailure) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftFwd;
        }
        break;
    case SVT_DF_MARK:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = DftFwdMark;
        if (HWFailure) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftFwd;
        }
        break;
    case SVT_DF_PP:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = DftFwd;
        if (HWFailure) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftFwd;
        }
        break;
    case SVT_DP:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = DftP;
        if (HWFailure && DPPtr) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftP;
        }
        break;
    case SVT_DS:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = DftS;
        if (HWFailure && DSPtr) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftS;
        }
        break;
    case SVT_DFP:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        if (DraftIndicationAtPP) {
            MyRetValue = DftFwdP;
        } else {
            MyRetValue = DftFwdMarkP;
        }
        if (HWFailure) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftFwdP;
        }
        break;
    case SVT_DFS:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        if (DraftIndicationAtPP) {
            MyRetValue = DftFwdS;
        } else {
            MyRetValue = DftFwdMarkS;
        }
        if (HWFailure) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftFwdS;
        }
        break;
    case SVT_DAP:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        if (DraftIndicationAtPP) {
            MyRetValue = DftAftP;
        } else {
            MyRetValue = DftAftMarkP;
        }
        if (HWFailure) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftAftP;
        }
        break;
    case SVT_DAS:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        if (DraftIndicationAtPP) {
            MyRetValue = DftAftS;
        } else {
            MyRetValue = DftAftMarkS;
        }
        if (HWFailure) {
            Status = GETVAL_HW_ALARM;
        } else {
            Status     = StatusDftAftS;
        }
        break;
    case SVT_DEFLECTION:
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        MyRetValue = Deflection;
        Status     = HasDeflection;
        break;
    case SVT_MAX_DRAFT :
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = MaxDraft;
        if (HWFailure) {
            Status     = GETVAL_HW_ALARM;
        }
        break;
    case SVT_DRAFT_MID:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        if (StatusDftMean != GETVAL_HW_ALARM) {
            MyRetValue = MeanDraft;
        }
        Status     = StatusDftMean;
        break;
    case SVT_FREEBOARD:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        if (StatusDftMean != GETVAL_HW_ALARM) {
            MyRetValue = MaxSummerDraft - MeanDraft;
        }
        Status     = StatusDftMean;
        break;
    case SVT_DENSITY:
        DecPnt     = 4;
        Unit       = DENSITY_UNIT;
        MyRetValue = PROSystemData::SeaWaterDensity;
        break;
    case SVT_TRIM_MARKS_M:
        if ((StatusDftFwd == GETVAL_NO_ERR) && (StatusDftAft == GETVAL_NO_ERR)) {
            DecPnt     = 1;
            Unit       = LENGTH_UNIT;
            MyRetValue = DftFwdMark - DftAftMark;
        } else {
            return  GETVAL_ERROR;
        }
        break;
    default:
        Status = PRogramObject::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int PRODraftSystem::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    default:
        Status = PRogramObject::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int PRODraftSystem::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_DRAFT_POINT:
        {
            bool Value = (bool)ConvertToSi(NewValue, NO_UNIT, Status, 0, 1, 0.0);
            if (Status == E_NO_ERR) {
                DraftIndicationAtPP = Value;
            }
        }
        break;
    case SVT_DA:
        if (DraftIndicationAtPP) {
            ValueId = SVT_DA_PP;
        } else {
            ValueId = SVT_DA_MARK;
        }
    case SVT_DA_MARK:
    case SVT_DA_PP:
        switch (DraftSystem) {
        case DftFwdAft:
        case DftFwdMidShipAft:
            //DAPtr
            if (ValueId == SVT_DA_MARK) {
                Status = DAPtr->PutValue(SVT_DRAFT, Index, NewValue, Local, &ValUnitId);
            } else {
                Status = DAPtr->PutValue(SVT_DRAFT_PP, Index, NewValue, Local, &ValUnitId);
            }
            break;
        case DftFwdAPortAStbd:
            {
                float NewDftA = (float)ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, 0.0, MaxSummerDraft, 0.0);
                if (Status == E_NO_ERR) {
                    float Diff = NewDftA;
                    if (ValueId == SVT_DA_MARK) {
                        Diff -= DftAftMark;
                    } else {
                        Diff -= DftAft;
                    }
                    Diff /= 2.0;  // Only half correction to midship
                    float DraftOffsetP =  DAPPtr->DraftOffset - Diff;
                    float DraftOffsetS =  DASPtr->DraftOffset - Diff;

                    char DftOffsetBuf[BUF_SIZE];
                    sprintf(DftOffsetBuf, "%f", DraftOffsetP);
                    Status = DAPPtr->PutValue(SVT_LEVEL_OFFSET, Index, (AnsiString)DftOffsetBuf, Local);
                    if (Status == E_NO_ERR) {
                        sprintf(DftOffsetBuf, "%f", DraftOffsetS);
                        Status = DASPtr->PutValue(SVT_LEVEL_OFFSET, Index, (AnsiString)DftOffsetBuf, Local);
                    }
                }
            }
            break;
        case DftNoDef:
        default:
            Status = E_NOT_ADJUSTABLE;
            break;
        }
        break;
    case SVT_DF:
        if (DraftIndicationAtPP) {
            ValueId = SVT_DF_PP;
        } else {
            ValueId = SVT_DF_MARK;
        }
    case SVT_DF_MARK:
    case SVT_DF_PP:
        switch (DraftSystem) {
        case DftFwdAft:
        case DftFwdMidShipAft:
        case DftFwdAPortAStbd:
            if (ValueId == SVT_DF_MARK) {
                Status = DFPtr->PutValue(SVT_DRAFT, Index, NewValue, Local, &ValUnitId);
            } else {
                Status = DFPtr->PutValue(SVT_DRAFT_PP, Index, NewValue, Local, &ValUnitId);
            }
            break;
        case DftNoDef:
        default:
            Status = E_NOT_ADJUSTABLE;
            break;
        }
        break;
    case SVT_DP:
        switch (DraftSystem) {
        case DftFwdMidShipAftPS:
        case DftFwdMidShipAft:
            Status = DPPtr->PutValue(SVT_DRAFT, Index, NewValue, Local, &ValUnitId);
            break;
        case DftFwdAPortAStbd:
            {
                float NewDftP = (float)ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, 0.0, MaxSummerDraft, 0.0);
                if (Status == E_NO_ERR) {
                    NewDftP -= DAPPtr->TrimListCorrectionFC();
                    char Buf[BUF_SIZE];
                    sprintf(Buf, "%f", NewDftP);
                    Status = DAPPtr->PutValue(SVT_DRAFT_PP, Index, (AnsiString)Buf, Local);
                }
            }
            break;
        case DftFwdAft:
        case DftNoDef:
        default:
            Status = E_NOT_ADJUSTABLE;
            break;
        }
        break;
    case SVT_DS:
        switch (DraftSystem) {
        case DftFwdMidShipAftPS:
        case DftFwdMidShipAft:
            //DSPtr
            if (DSPtr) {
                Status = DSPtr->PutValue(SVT_DRAFT, Index, NewValue, Local, &ValUnitId);
            } else {
                Status = E_INVALID_POINTER;
            }
            break;
        case DftFwdAPortAStbd:
            {
                float NewDftS = (float)ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, 0.0, MaxSummerDraft, 0.0);
                if (Status == E_NO_ERR) {
                    NewDftS -= DASPtr->TrimListCorrectionFC();
                    char Buf[BUF_SIZE];
                    sprintf(Buf, "%f", NewDftS);
                    Status = DASPtr->PutValue(SVT_DRAFT_PP, Index, (AnsiString)Buf, Local);
                }
            }
            break;
        case DftFwdAft:
        case DftNoDef:
        default:
            Status = E_NOT_ADJUSTABLE;
            break;
        }
        break;

    case SVT_DFP:
        if (DFPPtr) {
            if (DraftIndicationAtPP) {
                Status = DFPPtr->PutValue(SVT_DRAFT_PP, Index, NewValue, Local, &ValUnitId);
            } else {
                Status = DFPPtr->PutValue(SVT_DRAFT, Index, NewValue, Local, &ValUnitId);
            }
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_DFS:
        if (DFSPtr) {
            if (DraftIndicationAtPP) {
                Status = DFSPtr->PutValue(SVT_DRAFT_PP, Index, NewValue, Local, &ValUnitId);
            } else {
                Status = DFSPtr->PutValue(SVT_DRAFT, Index, NewValue, Local, &ValUnitId);
            }
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_DAP:
        if (DAPPtr) {
            if (DraftIndicationAtPP) {
                Status = DAPPtr->PutValue(SVT_DRAFT_PP, Index, NewValue, Local, &ValUnitId);
            } else {
                Status = DAPPtr->PutValue(SVT_DRAFT, Index, NewValue, Local, &ValUnitId);
            }
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_DAS:
        if (DASPtr) {
            if (DraftIndicationAtPP) {
                Status = DASPtr->PutValue(SVT_DRAFT_PP, Index, NewValue, Local, &ValUnitId);
            } else {
                Status = DASPtr->PutValue(SVT_DRAFT, Index, NewValue, Local, &ValUnitId);
            }
        } else {
            Status = E_INVALID_POINTER;
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

int PRODraftSystem::GetFloatValue(int ValueId, int Index, float &MyValue) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_DA:
        if (DraftIndicationAtPP) {
            MyValue = DftAft;
        } else {
            MyValue = DftAftMark;
        }
        Status     = StatusDftAft;
        break;
    case SVT_DA_MARK:
        MyValue = DftAftMark;
        Status     = StatusDftAft;
        break;
    case SVT_DA_PP:
        MyValue = DftAft;
        Status     = StatusDftAft;
        break;
    case SVT_DF:
        if (DraftIndicationAtPP) {
            MyValue = DftFwd;
        } else {
            MyValue = DftFwdMark;
        }
        Status     = StatusDftFwd;
        break;
    case SVT_DF_MARK:
        MyValue = DftFwdMark;
        Status     = StatusDftFwd;
        break;
    case SVT_DF_PP:
        MyValue = DftFwd;
        Status     = StatusDftFwd;
        break;
    case SVT_DP:
        MyValue = DftP;
        Status     = StatusDftP;
        break;
    case SVT_DS:
        MyValue = DftS;
        Status     = StatusDftS;
        break;
    case SVT_DFP:
        if (DraftIndicationAtPP) {
            MyValue = DftFwdP;
        } else {
            MyValue = DftFwdMarkP;
        }
        Status     = StatusDftFwdP;
        break;
    case SVT_DFS:
        if (DraftIndicationAtPP) {
            MyValue = DftFwdS;
        } else {
            MyValue = DftFwdMarkS;
        }
        Status     = StatusDftFwdS;
        break;
    case SVT_DAP:
        if (DraftIndicationAtPP) {
            MyValue = DftAftP;
        } else {
            MyValue = DftAftMarkP;
        }
        Status     = StatusDftAftP;
        break;
    case SVT_DAS:
        if (DraftIndicationAtPP) {
            MyValue = DftAftS;
        } else {
            MyValue = DftAftMarkS;
        }
        Status     = StatusDftAftS;
        break;
    case SVT_DEFLECTION:
        MyValue = Deflection;
        Status     = HasDeflection;
        break;
    case SVT_MAX_DRAFT :
        MyValue = MaxDraft;
        if (HWFailure) {
            Status     = GETVAL_HW_ALARM;
        }
        break;
    case SVT_DENSITY:
        MyValue = PROSystemData::SeaWaterDensity;
        break;
    default:
        Status = PRogramObject::GetFloatValue(ValueId, Index, MyValue);
        break;
    }
    return (Status);
}
int PRODraftSystem::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_DA_MARK:
        DftAftMark   = NewValue;
        StatusDftAft = GETVAL_NO_ERR;
        break;
    case SVT_DA_PP:
        DftAft       = NewValue;
        StatusDftAft = GETVAL_NO_ERR;
        break;
    case SVT_DF_MARK:
        DftFwdMark   = NewValue;
        StatusDftFwd = GETVAL_NO_ERR;
        break;
    case SVT_DF_PP:
        DftFwd       = NewValue;
        StatusDftFwd = GETVAL_NO_ERR;
        break;
    case SVT_DP:
        DftP         = NewValue;
        StatusDftP   = GETVAL_NO_ERR;
        break;
    case SVT_DS:
        DftS         = NewValue;
        StatusDftS   = GETVAL_NO_ERR;
        break;
    default:
        Status = PRogramObject::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);
}

ValueList* PRODraftSystem::GetValueInfoTableStatic(int &Entries, int Index) {
    Entries = NELEMENTS(DraftSystemValueList);
    return (DraftSystemValueList);
}


int PRODraftSystem::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch (pCH->CommandNo) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2730  *pData = (ANPRO10_COMMAND_2730 *)data;
            HasTrimValue        = pData->HasTrimValue;
            HasListValue        = pData->HasListValue;
            HasDeflection       = pData->HasDeflection;
            TrimValue           = pData->TrimValue;
            ListValue           = pData->ListValue;
            DftFwdMark          = pData->DftFwdMark;
            DftAftMark          = pData->DftAftMark;
            DftFwd              = pData->DftFwd;
            DftAft              = pData->DftAft;
            DftP                = pData->DftP;
            DftS                = pData->DftS;
            Deflection          = pData->Deflection;
            MaxDraft            = pData->MaxDraft;
            MeanDraft           = pData->MeanDraft;
            StatusDftFwd        = pData->StatusDftFwd;
            StatusDftAft        = pData->StatusDftAft;
            StatusDftP          = pData->StatusDftP;
            StatusDftS          = pData->StatusDftS;
            DraftIndicationAtPP = pData->DraftAtPP;
            DftAftP             = pData->DftAftP;
            DftAftS             = pData->DftAftS;
            DftFwdP             = pData->DftFwdP;
            DftFwdS             = pData->DftFwdS;
            DftFwdMarkP         = pData->DftFwdMarkP;
            DftFwdMarkS         = pData->DftFwdMarkS;
            DftAftMarkP         = pData->DftAftMarkP;
            DftAftMarkS         = pData->DftAftMarkS;
            StatusDftAftP       = pData->StatusDftAftP;
            StatusDftAftS       = pData->StatusDftAftS;
            StatusDftFwdP       = pData->StatusDftFwdP;
            StatusDftFwdS       = pData->StatusDftFwdS;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            //ANPRO10_COMMAND_2731  *pData = (ANPRO10_COMMAND_2731*) data;
            ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}


int PRODraftSystem::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch (cmd) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            QueueANPRO10_COMMAND_2730 Cmd;
            Cmd.TxInfo.Port        = NULL;
            Cmd.TxInfo.rxAddr      = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId        = DEVICE_BROADCAST_TXU;

            Cmd.Data.ObjectId      = IDNumber;
            Cmd.Data.ndb           = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo     = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.HasTrimValue  = HasTrimValue;
            Cmd.Data.HasListValue  = HasListValue;
            Cmd.Data.HasDeflection = HasDeflection;
            Cmd.Data.TrimValue     = TrimValue;
            Cmd.Data.ListValue     = ListValue;
            Cmd.Data.DftFwdMark    = DftFwdMark;
            Cmd.Data.DftAftMark    = DftAftMark;
            Cmd.Data.DftFwd        = DftFwd;
            Cmd.Data.DftAft        = DftAft;
            Cmd.Data.DftP          = DftP;
            Cmd.Data.DftS          = DftS;
            Cmd.Data.Deflection    = Deflection;
            Cmd.Data.MaxDraft      = MaxDraft;
            Cmd.Data.MeanDraft     = MeanDraft;
            Cmd.Data.StatusDftFwd  = StatusDftFwd;
            Cmd.Data.StatusDftAft  = StatusDftAft;
            Cmd.Data.StatusDftP    = StatusDftP;
            Cmd.Data.StatusDftS    = StatusDftS;
            Cmd.Data.DraftAtPP     = DraftIndicationAtPP;

            Cmd.Data.DftAftP        = DftAftP;
            Cmd.Data.DftAftS        = DftAftS;
            Cmd.Data.DftFwdP        = DftFwdP;
            Cmd.Data.DftFwdS        = DftFwdS;
            Cmd.Data.DftFwdMarkP    = DftFwdMarkP;
            Cmd.Data.DftFwdMarkS    = DftFwdMarkS;
            Cmd.Data.DftAftMarkP    = DftAftMarkP;
            Cmd.Data.DftAftMarkS    = DftAftMarkS;
            Cmd.Data.StatusDftAftP  = StatusDftAftP;
            Cmd.Data.StatusDftAftS  = StatusDftAftS;
            Cmd.Data.StatusDftFwdP  = StatusDftFwdP;
            Cmd.Data.StatusDftFwdS  = StatusDftFwdS;

            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        //case CMD_GENERIC_STATIC_DATA:
        //{
        //  QueueANPRO10_COMMAND_2731 Cmd;
        //  Cmd.TxInfo.Port           = NULL;
        //  Cmd.TxInfo.rxAddr         = DEVICE_BROADCAST_ADDR;
        //  Cmd.TxInfo.rxId           = DEVICE_BROADCAST_TXU;
        //  Cmd.Data.ObjectId         = IDNumber;
        //  Cmd.Data.ndb              = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
        //  Cmd.Data.CommandNo        = CMD_GENERIC_STATIC_DATA;
        //  bool sent = ANPRO10SendNormal(&Cmd);
        //  if ( !sent )
        //      ErrorStatus =  E_QUEUE_FULL;
        //  else
        //      ErrorStatus =  E_OK;
        //}
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}


ValueList* PRODraftSystem::GetValueInfoTable(int &Entries, int Index) {
    return GetValueInfoTableStatic(Entries, Index);
}


int PRODraftSystem::LCWriteXML(char *StrBuf) {
    int  tmpPtr = sprintf(StrBuf, "\t<Packet>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<PacketID>Drafts</PacketID>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<TagID>%s</TagID>\r\n", TagName.c_str());
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<DF>%0.3f meter</DF>\r\n", DftFwd);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<DP>%0.3f meter</DP>\r\n", DftP);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<DS>%0.3f meter</DS>\r\n", DftS);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<DA>%0.3f meter</DA>\r\n", DftAft);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t</Packet>\r\n");
    return tmpPtr;
}

int PRODraftSystem::WriteXMLSingle(char *StrBuf, bool IncAlarms, int pValKey, PRODraft *DftPtr) {
#ifdef ANWIN
    if (DftPtr) {
        AnsiString UnitStr;
        AnsiString DraftStr = LibGetValue(pValKey, this, 0);
        AnsiString AlMessageStr = "No alarm";
        int LEDStatus = TPC_LED_OFF;
        if (!DftPtr->CompleteAlarmInfoList.empty()) {
            bool ActiveAlarm = false;
            time_t NewestAlarmAct = 0;
            time_t NewestAlarmAck = 0;
            set<AlarmBasic *>::iterator pBIt;
            for (pBIt = DftPtr->AlarmSet.begin(); pBIt != DftPtr->AlarmSet.end(); pBIt++) {
                AlarmBasic *Element = *pBIt;
                if (Element) {
                    switch (Element->State) {
                    case AlarmBasic::AlIdle :
                        break;
                    case AlarmBasic::AlActive :
                        if (Element->Time_Rised > NewestAlarmAct) {
                            NewestAlarmAct = Element->Time_Rised;
                            ActiveAlarm = true;
                            AlMessageStr = Element->Get_TPCMessage();
                            LEDStatus = TPC_LED_FLASH;
                        }
                        break;
                    case AlarmBasic::AlAknowledged :
                        if (!ActiveAlarm && (Element->Time_Acknowledged > NewestAlarmAck)) {
                            NewestAlarmAck = Element->Time_Acknowledged;
                            AlMessageStr = Element->Get_TPCMessage();
                            LEDStatus = TPC_LED_ON;
                        }
                        break;
                    }
                }
            }
        }

        int  tmpPtr = sprintf(StrBuf, "\t<Packet>\r\n");
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<PacketID>Freevalue</PacketID>\r\n");
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<TagID>%s</TagID>\r\n", DftPtr->TagName.c_str());
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Value>%s</Value>\r\n", DraftStr);
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Alarm>%i</Alarm>\r\n", LEDStatus);
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t</Packet>\r\n");
        return tmpPtr;
    }
    return 0;
#else
    return 0;
#endif
}


int PRODraftSystem::WriteXML(char *StrBuf, bool IncAlarms) {
#ifdef ANWIN
    int  tmpPtr = 0;
    tmpPtr += WriteXMLSingle(&StrBuf[tmpPtr], IncAlarms, SVT_DF, DFPtr);
    tmpPtr += WriteXMLSingle(&StrBuf[tmpPtr], IncAlarms, SVT_DA, DAPtr);
    tmpPtr += WriteXMLSingle(&StrBuf[tmpPtr], IncAlarms, SVT_DP, DPPtr);
    tmpPtr += WriteXMLSingle(&StrBuf[tmpPtr], IncAlarms, SVT_DS, DSPtr);
    tmpPtr += WriteXMLSingle(&StrBuf[tmpPtr], IncAlarms, SVT_DFP, DFPPtr);
    tmpPtr += WriteXMLSingle(&StrBuf[tmpPtr], IncAlarms, SVT_DFS, DFSPtr);
    tmpPtr += WriteXMLSingle(&StrBuf[tmpPtr], IncAlarms, SVT_DAP, DAPPtr);
    tmpPtr += WriteXMLSingle(&StrBuf[tmpPtr], IncAlarms, SVT_DAS, DASPtr);
    return tmpPtr;
#else
    return 0;
#endif
}

int PRODraftSystem::GetStatus(int ValueKey) {
    int Status = GETVAL_NOT_AVAILABLE;
    switch (ValueKey) {
    case SVT_DF:
        Status = StatusDftFwd;
        break;
    case SVT_DFP:
        Status = StatusDftFwdP;
        break;
    case SVT_DFS:
        Status = StatusDftFwdS;
        break;
    case SVT_DP:
        Status = StatusDftP;
        break;
    case SVT_DS:
        Status = StatusDftS;
        break;
    case SVT_DAP:
        Status = StatusDftAftP;
        break;
    case SVT_DA:
        Status = StatusDftAft;
        break;
    case SVT_DAS:
        Status = StatusDftAftS;
        break;
    }
    return Status;
}

TColor PRODraftSystem::GetColor(int ValueKey) {
    return GetStatusColor(GetStatus(ValueKey));
}


TColor PRODraftSystem::GetStatusColor(int Status) {
    TColor tmpColor; // = (TColor)0x1fffffff;
    switch (Status) {
    case GETVAL_NOT_MEASURED    :
        tmpColor = (TColor)0xFACE87; //clBlue
        break;
    case GETVAL_DRY_SENSOR      :
        tmpColor = (TColor)0x00D7FF; //clYellow;
        break;
    case GETVAL_ERROR           :
        tmpColor = (TColor)0x00D7FF; //clYellow;
        break;
    case GETVAL_NOT_AVAILABLE   :
    case GETVAL_HW_ALARM        :
        tmpColor = (TColor)0x3C14DC; //clRed;
        break;
    case GETVAL_NO_ERR          :
        tmpColor = clWindow; //0x9AFA00;//clGreen;
        break;
    case GETVAL_UNKNOWN_ERROR   :
    default                     :
        tmpColor = (TColor)0x8080F0; //clFuchsia;
        break;
    }
    return tmpColor;
}

