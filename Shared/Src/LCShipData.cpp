#include "TSNIncludes.h"
#pragma hdrstop
#pragma package(smart_init)

bool    LCShipData::IsOnline                = false;
bool    LCShipData::Stability_Only          = false;
bool    LCShipData::SimpleLoadCalcOnly      = false;
bool    LCShipData::BMCalcAftToFore         = true;
bool    LCShipData::Ref_APP                 = false;
bool    LCShipData::SharingForceLimit       = false;
bool    LCShipData::No_BuoyancyCorrection   = false;
bool    LCShipData::TrimBySternPositive     = false;
float   LCShipData::Trim                    = 0.0;
float   LCShipData::List                    = 0.0;
int     LCShipData::TrimListSource          = C_SD_LC_SOURCE_MAN;
int     LCShipData::ClassificationSociety   = C_LC_CLASS_UNKNOWN;
int     LCShipData::LoadCalcVersion         = LC_CALC_VERSION1;
int     LCShipData::DataVersion             = 0;
float   LCShipData::GZScale                 = 5.0;
float   LCShipData::MS_to_APP_Corr          = 0.0;
float   LCShipData::MaxSectionDraft         = 0.0;
int     LCShipData::CondWarning             = 0;
float   LCShipData::HydrostaticsDns         = 1.025;
float   LCShipData::MaxSummerDraft          = 0.0;


LCShipData *LCShipData::LCShip              = NULL;
vector<LCFrameData *>LCShipData::GraphFrameList;




LCShipData::LCShipData(void)	{
    LCShip              = this;
    LMarks              = 0.0;
    LOA                 = 0.0;
    MaxSummerDraft      = 0.0;
    KeelThikness        = 0.0;
    HullDraftCorrection = 0.0;
    GZ_VCG_Constant     = 0.0;
    ManualTrim          = 0.0;
    ManualList          = 0.0;
    LCShip->MaxSfHogHrb = 0.0;
    LCShip->MaxSfSagHrb = 0.0;
    LCShip->MaxSfHogSea = 0.0;
    LCShip->MaxSfSagSea = 0.0;

    LCShip->MaxBmHogHrb = 0.0;
    LCShip->MaxBmSagHrb = 0.0;
    LCShip->MaxBmHogSea = 0.0;
    LCShip->MaxBmSagSea = 0.0;
}

LCShipData::~LCShipData(void)	{
}


bool LCShipData::ReadLimitTables(TSNConfigString &ConfigString) {
    bool TurnTable = false;
    vector<float>TrimTable;
    float xVal = 0.0;
    bool NoError = true;

    ConfigLog("********************************************************");
    ConfigLog("** Max KG & Damage max KG tables");


    short Key;
    bool DraftTab = true;
    int ErrorLine = 0;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning((AnsiString)"Unknown error started at line:" + (AnsiString)ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                {
                    TSNTableDamageCase *DamageCase = TSNTableDamageCase::FindCase((char *)InputKeyWord.c_str());
                    if (DamageCase) {
                        NoError = DamageCase->ReadEntry(ConfigString, xVal, 1.0, ErrorLine);
                        ConfigLog((AnsiString)"Reading Damage case " + InputKeyWord);
                    } else {
                        GiveConfigWarning((AnsiString)"The keyword " + InputKeyWord + (AnsiString)" is not allowed here!! Line:" + (AnsiString)ConfigString.LineCount);
                    }

                }
                break;
            case C_LC_TRIM_ENTRIES:
                do {
                    float  Trim = ConfigString.ReadDouble(ErrorLine, C_T_TABLE_END);
                    if (!ErrorLine) {
                        if (TrimBySternPositive) {
                            Trim = -Trim;
                        }
                        TrimTable.push_back(Trim);
                    }
                } while (!ErrorLine);
                if (ErrorLine == END_FOUND) {
                    // End found, Permitted in this case, so ErrorStatus set to 0
                    ErrorLine = 0;
                } else {
                    GiveConfigWarning((AnsiString)"Error in limit tables. Line:" + (AnsiString)ConfigString.LineCount);
                }

                if (TrimTable.front() > TrimTable.back()) {
                    TurnTable = true;
                    reverse(TrimTable.begin(), TrimTable.end());
                }

                break;
            case C_LC_MAX_VCG:
                if (!TSNTableHydrostatic::MaxVCG_Tab) {
                    TSNTableHydrostatic::MaxVCG_Tab  = new TSNTableHydrostatic(C_LC_MAX_VCG, DraftTab, TrimTable);
                }
                NoError = TSNTableHydrostatic::MaxVCG_Tab->ReadEntry(ConfigString, xVal, 1.0, ErrorLine);
                break;
            case C_LC_DAMAGE_MAX_VCG:
                if (!TSNTableHydrostatic::DamageMaxVCG_Tab) {
                    TSNTableHydrostatic::DamageMaxVCG_Tab  = new TSNTableHydrostatic(C_LC_MAX_VCG, DraftTab, TrimTable);
                }
                NoError = TSNTableHydrostatic::DamageMaxVCG_Tab->ReadEntry(ConfigString, xVal, 1.0, ErrorLine);
                break;
            case C_LC_VCG_CASES:
                {
                    AnsiString Name;
                    bool NewCond = false;
                    do {
                        Name = ConfigString.NextWord(ErrorLine);
                        ConfigLog((AnsiString)"Reading Damage case " + (AnsiString)Name + (AnsiString)". Number of cases=" + (AnsiString)TSNTableDamageCase::DamageCondTable.size());
                        short tempKey = FindConfigKey(Name);

                        NewCond = (tempKey != C_LC_END);
                        if (!ErrorLine && NewCond) {
                            TSNTableDamageCase::DamageCaseTable = new TSNTableDamageCase(Name, DraftTab, TrimTable);
                            ConfigLog((AnsiString)"Reading Damage case " + Name);
                        }
                    }while (NewCond);
                }
                break;
            case C_LC_DRAFT:
                xVal = ConfigString.ReadDouble(ErrorLine);
                DraftTab = true;
                break;
            case C_LC_DISPLACEMENT:
                xVal = ConfigString.ReadDouble(ErrorLine);
                xVal /= HydrostaticsDns;
                DraftTab = false;
                break;
            case C_LC_FRESH_WATER   :
                HydrostaticsDns = 1.0;
                break;
            case C_LC_SEA_WATER     :
                HydrostaticsDns = 1.025;
                break;
            case C_LC_FLOODING_ANGLE:
                if (!TSNTableHydrostatic::FloodinAngle_Tab) {
                    TSNTableHydrostatic::FloodinAngle_Tab  = new TSNTableHydrostatic(C_LC_FLOODING_ANGLE, DraftTab, TrimTable);
                }
                NoError = TSNTableHydrostatic::FloodinAngle_Tab->ReadEntry(ConfigString, xVal, 1.0, ErrorLine);
                break;
            case C_LC_END:
                break;
            } // End of Key switch
        } // End if not EOF
    }while (NoError && (ErrorLine != EOF) && (Key != C_LC_END));
    return (NoError);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Purpose: Read the loading calculator configuration file.
//
//  Returns NoError status.
//
//////////////////////////////////////////////////////////////////////////////

bool LCShipData::LoadConfigString(TSNConfigString &ConfigString) {
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning((AnsiString)"Loadcalc", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning((AnsiString)"Loadcalc", InputKeyWord, ConfigString.LineCount);
                break;
            case C_LC_END:
                break;
            case C_LC_VCG :
                VCG = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_LCG :
                LCG = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_TCG :
                TCG = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_MS_TO_APP :
                MS_to_APP = ConfigString.ReadDouble(ErrorLine);
                if (Ref_APP) {
                    MS_to_APP_Corr = MS_to_APP;
                }
                break;
            case C_LC_APP_TO_MARK :
                APP_to_Mark = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_WEIGHT :
                Weight = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_MAX_DRAFT:
                MaxSummerDraft = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_GZ_VCG_CONSTANT:
                GZ_VCG_Constant = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_KEEL_THICKNESS:
                KeelThikness = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_HULL_DRAFT_CORRECTION:
                HullDraftCorrection = ConfigString.ReadDouble(ErrorLine);
                break;
            }
        }
    }while (!ErrorLine && (ErrorLine != EOF) && (Key != C_LC_END));
    LCG -= MS_to_APP_Corr;
    LTrimMoment = Weight * LCG;
    TTrimMoment = Weight * TCG;
    VTrimMoment = Weight * VCG;
    return (ErrorLine);
}

bool LCShipData::LoadConfig(TSNConfigString &ConfigString) {
    float BmHogHrbLimit = MAXFLOAT,
        BmHogSeaLimit = MAXFLOAT,
        BmSagHrbLimit = MAXFLOAT,
        BmSagSeaLimit = MAXFLOAT,
        SfHogHrbLimit = MAXFLOAT,
        SfHogSeaLimit = MAXFLOAT,
        SfSagHrbLimit = MAXFLOAT,
        SfSagSeaLimit = MAXFLOAT;
    bool NoError = true;

    ConfigLog("********************************************************");
    ConfigLog("** Loading calculator configuration");


    AnsiString FirstFrameCheckStr;
    AnsiString LastFrameCheckStr;

    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning((AnsiString)"LoadCalc", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning((AnsiString)"LoadCalc", InputKeyWord, ConfigString.LineCount);
                break;
            case C_LC_END:
                break;
            case C_LC_DATA_VERSION:
                LCShipData::DataVersion = ConfigString.ReadLong(ErrorLine);
                break;
            case C_LC_LOAD_CALC_VERSION:
                LoadCalcVersion = ConfigString.ReadLong(ErrorLine);
                break;
            case C_LC_CLASS_UNKNOWN :
            case C_LC_CLASS_DNV     :
            case C_LC_CLASS_LLOYDS  :
            case C_LC_CLASS_GL      :
            case C_LC_CLASS_MRS     :
            case C_LC_CLASS_BV      :
            case C_LC_CLASS_NK      :
            case C_LC_CLASS_RINA    :
            case C_LC_CLASS_ABS     :
            case C_LC_CLASS_KR      :
            case C_LC_CLASS_USC     :
                ClassificationSociety = Key;
                break;
            case C_LC_TRIM_BY_STERN_POS:
                TrimBySternPositive = true;
                break;
            case C_LC_STABILITY_ONLY:
                Stability_Only = true;
                break;
            case C_LC_SIMPLE_LC_ONLY:
                SimpleLoadCalcOnly = true;
                break;
            case C_LC_GZ_SCALE:
                GZScale = ConfigString.ReadDouble(ErrorLine);
                ConfigLog((AnsiString)"GZ scale is set to " + (AnsiString)(GZScale,2));
                break;
            case C_LC_NO_BUOYANCY_CORR:
                No_BuoyancyCorrection = true;
                ConfigLog("No buoyancy correction");
                break;
            case C_LC_REF_APP:
                Ref_APP = true;
                break;
            case C_LC_SHIPDATA:
                new LCShipData;
                LCShip->LoadConfigString(ConfigString);
                break;
            case C_LC_MAX_SECTION_DRAFT :
                MaxSectionDraft = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_KY_CURVES:
                TSNTableKY::KY_Table = new TSNTableKY(ConfigString, TTypeDraftMS);
                break;
            case C_LC_DISP_KY_CURVES:
                TSNTableKY::KY_Table = new TSNTableKY(ConfigString, TTypeDispl);
                break;
            case C_LC_KY_CURVES_CF:
                TSNTableKY::KY_Table = new TSNTableKY(ConfigString, TTypeDraftCF);
                break;
            case C_LC_TABLE_HYDROSTATIC :
                NoError = TSNTableHydrostatic::ReadHydrostaticTables(ConfigString);
                break;
            case C_LC_SECTION :
                {
                    int FNum = LCFrameData::Table.size();
                    LCFrameData *F;
                    if (FNum) {
                        F = LCFrameData::Table[FNum - 1];
                    } else {
                        F = NULL;
                    }
                    new LCSectionData(ConfigString, F,
                                      BmHogHrbLimit, BmHogSeaLimit,
                                      BmSagHrbLimit, BmSagSeaLimit,
                                      SfHogHrbLimit, SfHogSeaLimit,
                                      SfSagHrbLimit, SfSagSeaLimit, ErrorLine);
                }
                break;
            case C_LC_TANK_CARGO     :
            case C_LC_TANK_BALLAST   :
            case C_LC_TANK_HFO       :
            case C_LC_TANK_DO        :
            case C_LC_TANK_LUB       :
            case C_LC_TANK_FW        :
            case C_LC_TANK_MISC      :
            case C_LC_TANK_VOIDSPACE :
                {
                    LCTankData *tmpPtr = new LCTankData(Key);
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                }
                break;
            case C_LC_SOLID_CONSTANT:
                {
                    LCSolidData *tmpPtr = new LCSolidData(C_LC_SOLID_CONSTANT);
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                }
                break;
            case C_LC_SOLID_VARIABLE:
                {
                    int Number_of_VSol = ConfigString.ReadLong(ErrorLine);
                    if (!ErrorLine) {
                        for (int i = 0; i < Number_of_VSol; i++) {
                            new LCVariableSolidData;
                        }
                    }
                }
                break;
            case C_LC_BMHOGHRBLIM:
                BmHogHrbLimit = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_BMHOGSEALIM:
                BmHogSeaLimit = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_BMSAGHRBLIM:
                BmSagHrbLimit = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_BMSAGSEALIM:
                BmSagSeaLimit = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_SFHOGHRBLIM:
                SfHogHrbLimit = ConfigString.ReadDouble(ErrorLine);
                SharingForceLimit = true;
                break;
            case C_LC_SFHOGSEALIM:
                SfHogSeaLimit = ConfigString.ReadDouble(ErrorLine);
                SharingForceLimit = true;
                break;
            case C_LC_SFSAGHRBLIM:
                SfSagHrbLimit = ConfigString.ReadDouble(ErrorLine);
                SharingForceLimit = true;
                break;
            case C_LC_SFSAGSEALIM:
                SfSagSeaLimit = ConfigString.ReadDouble(ErrorLine);
                SharingForceLimit = true;
                break;
            case C_LC_STABILITY_TABLES :
                NoError = ReadLimitTables(ConfigString);
                break;
            case C_LC_BM_CALC_F_TO_A:
                BMCalcAftToFore = false;
                break;
            case C_LC_FRAME_LIST:
                {
                    do {
                        AnsiString FName = ConfigString.NextWord(ErrorLine, C_T_TABLE_END);
                        if (!ErrorLine) {
                            LCFrameData *tmpPtr = LCFrameData::FindFrame(FName);
                            if (tmpPtr) {
                                GraphFrameList.push_back(tmpPtr);
                            }
                        }
                    } while (!ErrorLine);
                    if (ErrorLine == END_FOUND) {
                        // End found, Permitted in this case, so ErrorStatus set to 0
                        ErrorLine = 0;
                    } else {
                        GiveConfigWarning((AnsiString)"Error in definition of frame numbers. Line:" + (AnsiString)ConfigString.LineCount);
                    }
                }
                break;
            case C_LC_WEIGHT_DISTRIBUTION:
                LCSteelWeight::SteelWeightDistibution = new LCSteelWeight();
                ErrorLine = LCSteelWeight::SteelWeightDistibution->LoadConfigString(ConfigString);
                break;
            case C_LC_WEIGHT_DISTR_REF_MID:
                LCSteelWeight::SteelWeightDistibution = new LCSteelWeight(-PROProjectInfo::LengthBetweenPP / 2.0);
                ErrorLine = LCSteelWeight::SteelWeightDistibution->LoadConfigString(ConfigString);
                break;
            case C_LC_OPENING:
                {
                    LCOpeningData *tmpPtr = new LCOpeningData();
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                }
                break;
            case C_LC_FIRST_STR_LIM_CHECK:
                FirstFrameCheckStr = ConfigString.NextWord(ErrorLine);
                break;
            case C_LC_LAST_STR_LIM_CHECK:
                LastFrameCheckStr = ConfigString.NextWord(ErrorLine);
                break;
            }
        }
    }  while (!ErrorLine && ErrorLine != EOF);


    if (!Stability_Only && !SimpleLoadCalcOnly) {
        if (!FirstFrameCheckStr.IsEmpty()) LCFrameData::StrengthFirstFrameNum = LCFrameData::FindFrameNum(FirstFrameCheckStr);
        if (!LastFrameCheckStr.IsEmpty())  LCFrameData::StrengthLastFrameNum  = LCFrameData::FindFrameNum(LastFrameCheckStr);

        // Set index to our last section to calculate;
        if (!LCSectionData::FppSection) LCSectionData::FppSection = LCSectionData::Table.size() - 1;
        LCSectionData::CorrectBuoyancy();

        LCFrameData::FixFrameLimits();
        for (int i = 0; i < int(LCFrameData::Table.size()); i++) {
            LCFrameData *F = LCFrameData::Table[i];
            LCShip->MaxSfHogHrb = max(F->Limit[SFHOGHRB], LCShip->MaxSfHogHrb);
            LCShip->MaxSfSagHrb = max(F->Limit[SFSAGHRB], LCShip->MaxSfSagHrb);
            LCShip->MaxSfHogSea = max(F->Limit[SFHOGSEA], LCShip->MaxSfHogSea);
            LCShip->MaxSfSagSea = max(F->Limit[SFSAGSEA], LCShip->MaxSfSagSea);

            LCShip->MaxBmHogHrb = max(F->Limit[BMHOGHRB], LCShip->MaxBmHogHrb);
            LCShip->MaxBmSagHrb = max(F->Limit[BMSAGHRB], LCShip->MaxBmSagHrb);
            LCShip->MaxBmHogSea = max(F->Limit[BMHOGSEA], LCShip->MaxBmHogSea);
            LCShip->MaxBmSagSea = max(F->Limit[BMSAGSEA], LCShip->MaxBmSagSea);
            if (i >= LCFrameData::StrengthFirstFrameNum && i <= LCFrameData::StrengthLastFrameNum) {
                F->HasStrengthCheck = true;
            } else {
                F->HasStrengthCheck = false;
            }
        }
    }
    new LCStabCalc;
    LCStabCalc::StabCalc->Calculate();
    if (!Stability_Only && !SimpleLoadCalcOnly) {
        LCStabCalc::StabCalc->Strength();
    }
    LCStabCalc::StabCalc->CheckResult();
    return (true);
};


bool LCShipData::LoadCondition(TSNConfigString &ConfigString) {
    bool NoError = true;

    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning((AnsiString)"Loading Condition", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning((AnsiString)"Loading Condition", InputKeyWord, ConfigString.LineCount);
                break;
            case C_LC_END:
                break;
            case C_LC_SHIPDATA:
                LCShip->LoadConditionString(ConfigString, ErrorLine);
                break;
            case C_LC_TANK_CARGO        :
            case C_LC_TANK_BALLAST      :
            case C_LC_TANK_HFO          :
            case C_LC_TANK_DO           :
            case C_LC_TANK_LUB          :
            case C_LC_TANK_FW           :
            case C_LC_TANK_MISC         :
            case C_LC_TANK_VOIDSPACE    :
            case C_LC_SOLID_CONSTANT    :
            case C_LC_SOLID_VARIABLE    :
                {
                    unsigned IDNum = (unsigned)ConfigString.ReadInteger(ErrorLine);
                    LCLocationData *tmpPtr = LCLocationData::FindLocation(IDNum);
                    if (tmpPtr) {
                        tmpPtr->LoadConditionString(ConfigString, ErrorLine);
                    }
                }
                break;
            }
        }
    }  while (!ErrorLine && ErrorLine != EOF);
    return ErrorLine;
}

AnsiString LCShipData::SaveCondition(void) {
    AnsiString tmpStr;
    tmpStr += LCShip->SaveConditionString();
    return tmpStr;
}

void LCShipData::LoadConditionString(TSNConfigString &ConfigString, int &ErrorLine) {
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning((AnsiString)"Loading Condition", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning((AnsiString)"Loading Condition", InputKeyWord, ConfigString.LineCount);
                break;
            case C_LC_END:
                break;
            case C_LC_MANUAL_TRIM:
                ManualTrim = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_MANUAL_LIST:
                ManualList = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_TRIM_LIST_SOURCE:
                TrimListSource = ConfigString.ReadLong(ErrorLine);
                break;
            case C_SD_SEAWATER_DNS:
                PROSystemData::SeaWaterDensity = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_SD_BALLAST_DNS    :
                PROSystemData::BallastDensity = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_SD_FRESHWATER_DNS :
                PROSystemData::FreshWaterDensity = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_SD_HEAVY_FUEL_DNS :
                PROSystemData::HeavyFuelDensity = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_SD_DIESEL_DNS     :
                PROSystemData::DieselDensity = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_SD_LUBRICANTS_DNS :
                PROSystemData::LubricantsDensity = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_SD_SEAWATER_TEMP:
                PROSystemData::SeaWaterTemp    = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_SD_AMBIENT_TEMP:
                PROSystemData::AmbientTemp = ConfigString.ReadDouble(ErrorLine);
                break;
            }
        }
    }  while (!ErrorLine && ErrorLine != EOF && Key != C_LC_END);
}

AnsiString LCShipData::SaveConditionString(void) {
    AnsiString tmpStr, tmpStr2;
    tmpStr += TabStr1 + KeyWord(C_LC_SHIPDATA) + CrLfStr;

    tmpStr += TabStr2 + KeyWord(C_LC_TRIM_LIST_SOURCE)  + (AnsiString)TrimListSource + CrLfStr;
    tmpStr += TabStr2 + KeyWord(C_LC_MANUAL_TRIM)       + tmpStr2.sprintf("%8.4f", ManualTrim) + CrLfStr;
    tmpStr += TabStr2 + KeyWord(C_LC_MANUAL_LIST)       + tmpStr2.sprintf("%8.4f", ManualList) + CrLfStr;
    tmpStr += TabStr1 + KeyWord(C_SD_BALLAST_DNS)       + tmpStr2.sprintf("%8.5f", PROSystemData::BallastDensity) + CrLfStr;
    tmpStr += TabStr2 + KeyWord(C_SD_FRESHWATER_DNS)    + tmpStr2.sprintf("%8.5f", PROSystemData::FreshWaterDensity) + CrLfStr;
    tmpStr += TabStr2 + KeyWord(C_SD_HEAVY_FUEL_DNS)    + tmpStr2.sprintf("%8.5f", PROSystemData::HeavyFuelDensity) + CrLfStr;
    tmpStr += TabStr2 + KeyWord(C_SD_DIESEL_DNS)        + tmpStr2.sprintf("%8.5f", PROSystemData::DieselDensity) + CrLfStr;
    tmpStr += TabStr2 + KeyWord(C_SD_LUBRICANTS_DNS)    + tmpStr2.sprintf("%8.5f", PROSystemData::LubricantsDensity) + CrLfStr;
    tmpStr += TabStr2 + KeyWord(C_SD_SEAWATER_TEMP)     + tmpStr2.sprintf("%8.2f", PROSystemData::SeaWaterTemp) + CrLfStr;
    tmpStr += TabStr2 + KeyWord(C_SD_SEAWATER_DNS)      + tmpStr2.sprintf("%8.5f", PROSystemData::SeaWaterDensity) + CrLfStr;
    tmpStr += TabStr2 + KeyWord(C_SD_AMBIENT_TEMP)  + tmpStr2.sprintf("%8.2f", PROSystemData::AmbientTemp) + CrLfStr;
    tmpStr += TabStr1 + KeyWord(C_LC_END) + CrLfStr;

    tmpStr += LCLocationData::SaveCondition();
    return tmpStr;
}




float LCShipData::TrimListCorrection(float LongitudinalDist, float TransverceDist) {
    float TrimValue, ListValue;
    if (IsOnline) {
        TrimValue = PROSystemData::TrimValue;
        ListValue = PROSystemData::ListValue;
    } else {
        TrimValue = Trim;
        ListValue = List;
    }
    return TrimValue * LongitudinalDist + ListValue * TransverceDist;
}



///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int LCShipData::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_LS_WEIGHT   :
        DecPnt     = 1;
        Unit       = WEIGHT_UNIT;
        MyRetValue = Weight;
        break;
    case SVT_LS_L_MOM    :
        DecPnt     = 1;
        Unit       = MOMENT_UNIT;
        MyRetValue = Weight * LCG;
        break;
    case SVT_LS_T_MOM    :
        DecPnt     = 1;
        Unit       = MOMENT_UNIT;
        MyRetValue = Weight * TCG;
        break;
    case SVT_LS_V_MOM    :
        DecPnt     = 1;
        Unit       = MOMENT_UNIT;
        MyRetValue = Weight * VCG;
        break;
    case SVT_LS_MANUAL_TRIM:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = ManualTrim * PROProjectInfo::LengthBetweenPP;
        break;
    case SVT_LS_MANUAL_LIST_DEG:
        DecPnt     = 1;
        Unit       = ANGLE_UNIT;
        MyRetValue = ManualList;
        break;
    case SVT_LS_MAX_SUMMER_DRAFT:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = MaxSummerDraft;
        break;
    case C_LC_FREEBOARD:
        DecPnt     = 2;
		Unit       = LENGTH_UNIT;
		if (LCStabCalc::StabCalc) {
			MyRetValue = MaxSummerDraft-LCStabCalc::StabCalc->DraftMS;
		}else{
		   Status = GETVAL_NOT_AVAILABLE;
        }
		break;
    default:
        Status = PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int LCShipData::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
	int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_LS_TRIM_LIST_SOURCE:
        MyString = KeyWord(TrimListSource);
        break;
    default:
        Status = PRogramObjectBase::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int LCShipData::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_LS_TRIM_LIST_SOURCE:
        {
            int Key = GetInt(NewValue, Status);
            if (Status == E_NO_ERR) {
                TrimListSource = Key;
            }
        }
        break;
    case SVT_LS_MANUAL_TRIM:
        {
            float tmpTrim = ConvertToSi(NewValue, LENGTH_UNIT, Status, -10.0, 5.0, ManualTrim * PROProjectInfo::LengthBetweenPP);
            ManualTrim = tmpTrim / PROProjectInfo::LengthBetweenPP;
        }
        break;
    case SVT_LS_MANUAL_LIST_DEG:
        ManualList = ConvertToSi(NewValue, ANGLE_UNIT, Status, -10.0, 10.0, ManualList);
        break;
    default:
        Status = PRogramObjectBase::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    if (UnitId) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int LCShipData::PutFloatValue(int ValueId, float NewValue) {
    return (PRogramObjectBase::PutFloatValue(ValueId, NewValue));
}


void LCShipData::GetOnlineData(void) {

}

void LCShipData::GetTrimListData(void) {

    switch (TrimListSource) {
    case C_SD_LC_SOURCE_MAN  :
        Trim = ManualTrim;
        List = ManualList;
        break;
    case C_SD_LC_SOURCE_ONL:
        Trim = PROSystemData::TrimValue;
        List = PROSystemData::ListValue;
        break;
    case C_SD_LC_SOURCE:
        Trim = LCStabCalc::StabCalc->Trim_in_rad;
        List = LCStabCalc::StabCalc->List_in_rad;
        break;
    }
}

