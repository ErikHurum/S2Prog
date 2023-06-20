#include <TSNIncludes.h>
#pragma hdrstop

vector<LCLocationData*>LCTankData::OnlineTable;
vector<LCLocationData*>LCTankData::OfflineTable;

vector<LCTankData*>LCTankData::LCTankVector;

LCTankData::LCTankData(int TType):LCLocationData(TType)
{
    Initialize();
}

LCTankData::~LCTankData()
{
    if ( !OnlineTank ) {
        if ( LevVolumeTab ) delete LevVolumeTab    ;
        if ( UllVolumeTab ) delete UllVolumeTab    ;
        if ( SoundingTab ) delete SoundingTab     ;
        if ( CenterOfFlotTab ) delete CenterOfFlotTab ;
    }
    if ( CG_Table ) delete CG_Table        ;
    if ( TFS_Table ) delete TFS_Table       ;
    if ( CG_UllTable ) delete CG_UllTable        ;
    if ( TFS_UllTable ) delete TFS_UllTable       ;
    //  if ( OnlineTank       ) delete OnlineTank      ;

}

void LCTankData::Initialize(void)
{
    LCTankVector.push_back(this);
    IsOnline            = false;
    HWFailure           = false;
    Temperature         = 0.0;
    Density             = 1.0;
    UllageRef              = 0.0;
    UllageFC            = 0.0;
    LevelFC             = 0.0;
    Sounding            = 0.0;
    LevelAtRef          = 0.0;
    Volume              = 0.0;
    VolumePercent       = 0.0;
    Density             = 0.0;
    TFS_Moment          = 0.0;
    TFreeSurf           = 0.0;
    LDist               = 0.0;
    TDist               = 0.0;
    DBotUllRefPnt       = 0.0;
    DManMsrPntToMid     = 0.0;
    DManMsrPntToCL      = 0.0;
    DFltCntToMid        = 0.0;
    DFltCntToCL         = 0.0;

    cDTR                = 0.0;
    cDLR                = 0.0;
    cDLFC               = 0.0;
    cDTFC               = 0.0;
    LevelOffset         = 0.0;
    TableOffset         = 0.0;

    MeasuredDns         = 0.0;
    LoadRate            = 0.0;
    RemainingTime       = 0.0;
    MaxWeight           = MAX_WEIGHT;
    MaxDensity          = MAX_DENSITY;
    HasMaxWeight        = false;
    HasMeasuredDensity  = false;
    DBU_IsConfigured    = false;


    CG_Table            = NULL;
    CG_UllTable         = NULL;
    TFS_Table           = NULL;
    TFS_UllTable        = NULL;
    LevVolumeTab        = NULL;
    UllVolumeTab        = NULL;
    VolumeTab           = NULL;
    OnlineTank          = NULL;
    SoundingTab         = NULL;
    CenterOfFlotTab     = NULL;

}

bool LCTankData::LoadConfigString(TSNConfigString &ConfigString)
{
    PROTank *OnlineTnkPtr = NULL;
    int ErrorLine           = 0;
    int Key                 = 0;
    do {
        AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)"LCTank",ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning((AnsiString)"LCTank",InputKeyWord,ConfigString.LineCount);
                break;
            case C_LC_END           :
                break;
            case C_LC_LOCATION      :
                if ( !LCLocationData::LoadConfigString(ConfigString) ) {
                    ErrorLine = ConfigString.LineCount;
                }
                break;
            case C_PRO_NAME :
                Name = ConfigString.GetRemainingLine(ErrorLine);
                ConfigLog((AnsiString)"The tank name is "+Name);
                break;
            case C_PRO_LONGNAME:
                LongName = ConfigString.GetRemainingLine(ErrorLine);
                ConfigLog((AnsiString)"The tank long name is "+LongName);
                break;
            case C_LC_OVERRIDE_FRAME :
                ConfigWeightDistribution(ConfigString,ErrorLine,true);
                break;
            case C_LC_FRAME :
                ConfigWeightDistribution(ConfigString,ErrorLine);
                break;
            case C_PRO_TANK         :
                {
                    int tnkId = ConfigString.ReadInteger(ErrorLine);
                    if ( !ErrorLine ) {
                        OnlineTnkPtr = (PROTank*)FindObject(tnkId);
                        IsOnline     = true;
                    }
                }
                break;
            case C_D_BOT_ULL_REF:
            case C_D_BOT_ULL_REF2:
                DBotUllRefPnt = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_D_MAN_MSR_MID:
            case C_D_MAN_MSR_MID2:
                DManMsrPntToMid = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_D_MAN_MSR_CL :
            case C_D_MAN_MSR_CL2:
                DManMsrPntToCL = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_D_FC_MID :
            case C_D_FC_MID2:
                DFltCntToMid = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_D_FC_CL:
            case C_D_FC_CL2:
                DFltCntToCL = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_T_LEVEL_VOL_TABLE:
                LevVolumeTab = new TSNTable1Degree(Key);
                VolumeTab    = LevVolumeTab;
                if ( LevVolumeTab )LevVolumeTab->ReadTable(ConfigString,ErrorLine);
                break;
            case C_T_ULLAGE_VOL_TABLE:
                UllVolumeTab = new TSNTable1Degree(Key);
                VolumeTab    = UllVolumeTab;
                if ( UllVolumeTab )UllVolumeTab->ReadTable(ConfigString,ErrorLine);
                break;
            case C_T_SOUNDING_TABLE:
                SoundingTab = new TSNTable1Degree(Key);
                if ( SoundingTab )SoundingTab->ReadTable(ConfigString,ErrorLine);
                break;
            case C_T_COF_TABLE:
                CenterOfFlotTab = new TSNTableCenterOfFlotation(C_T_COF_TABLE);
                if ( CenterOfFlotTab )CenterOfFlotTab->ReadTable(ConfigString,ErrorLine);
                break;
            case C_T_COG_TABLE:
                CenterOfFlotTab = new TSNTableCenterOfFlotation(C_T_COG_TABLE);
                if ( CenterOfFlotTab )CenterOfFlotTab->ReadTable(ConfigString,ErrorLine);
                break;
            case C_LC_TABLE_CG:
                CG_Table = new TSNTableCenterOfGravity();
                if ( CG_Table )CG_Table->ReadTable(ConfigString,ErrorLine);
                break;
            case C_LC_TABLE_TFS:
                TFS_Table = new TSNTable1Degree(C_LC_TABLE_TFS);
                if ( TFS_Table )TFS_Table->ReadTable(ConfigString,ErrorLine);
                break;
            case C_LC_TABLE_CG_ULL:
                CG_UllTable = new TSNTableCenterOfGravity();
                if ( CG_UllTable )CG_UllTable->ReadTable(ConfigString,ErrorLine);
                break;
            case C_LC_TABLE_TFS_ULL:
                TFS_UllTable = new TSNTable1Degree(C_LC_TABLE_TFS);
                if ( TFS_UllTable )TFS_UllTable->ReadTable(ConfigString,ErrorLine);
                break;

            case C_LC_MAX_WEIGHT:
                MaxWeight = ConfigString.ReadDouble(ErrorLine);
                HasMaxWeight = (bool)(!ErrorLine);
                break;
            case C_LC_MAX_DENSITY:
                MaxDensity = ConfigString.ReadDouble(ErrorLine);
                break;
            }
        }
    }while ( !ErrorLine && ( ErrorLine != EOF )&& ( Key != C_LC_END ) );
    SetOnlineTank(OnlineTnkPtr);

    if ( !HasMaxWeight ) {
        if ( VolumeTab ) {
            MaxWeight = MaxDensity*VolumeTab->MaxY;
            if (!DBotUllRefPnt){
                DBotUllRefPnt = VolumeTab->MaxX;
            }
        }
    }
    UllageRef   = DBotUllRefPnt;
    UllageFC = DBotUllRefPnt;
    SetCargoType();
    // Check the load calc configuration
    if ( !CG_Table && !CG_UllTable ) {
        ConfigLog("**********************************************");
        ConfigLog((AnsiString)"Error. Center of gravity table not linked for tank "+(AnsiString)Name);
    }
    if ( !TFS_Table && !TFS_UllTable ) {
        ConfigLog("**********************************************");
        ConfigLog((AnsiString)"Error. Transverse free surface table not linked for tank "+(AnsiString)Name);
    }
    if ( OnlineTank ) {
        OnlineTable.push_back(this);
    } else {
        OfflineTable.push_back(this);
    }

    return(!ErrorLine);
}

void LCTankData::LoadConditionString(TSNConfigString &ConfigString, int &ErrorLine)
{
    int Key;
    do {
        AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)"Loading Condition",ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning((AnsiString)"Loading Condition",InputKeyWord,ConfigString.LineCount);
                break;
            case C_LC_END:
                break;
            case C_LC_VOLUME:
                Volume = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_WEIGHT:
                Weight = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_ULLAGE:
                UllageRef = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_ULLAGE_FC:
                UllageFC = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_LEVELFC:
                LevelFC = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_SOUNDING:
                Sounding = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_LEVEL_AT_REF:
                LevelAtRef = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_LC_VOLUME_PERCENT:
                VolumePercent = ConfigString.ReadDouble(ErrorLine);
                break;
            case TSN_TEMP_APP:
                Temperature = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_CARGO_TYPE:
                CargoType.RestoreSettings(&ConfigString);
                break;
            case C_OFFLINE:
                IsOnline = false;
                break;
            case C_ONLINE:
                IsOnline = true;
                break;
            }
        }
    }  while ( !ErrorLine && ErrorLine != EOF && Key != C_LC_END );
}
AnsiString LCTankData::SaveConditionString(int ExtraTabs)
{
    AnsiString LocalString,tmpStr;
    AnsiString IdNumStr;
    IdNumStr.cat_sprintf("0x%0x",IDNumber);

    LocalString +=TabStr1+KeyWord(Type)+IdNumStr+CrLfStr;

    LocalString +=TabStr2+KeyWord(C_LC_ULLAGE        )+TabStr1+tmpStr.sprintf("%8.2f",UllageRef )+CrLfStr;
    LocalString +=TabStr2+KeyWord(C_LC_ULLAGE_FC     )+tmpStr.sprintf("%8.2f",UllageFC       )+CrLfStr;
    LocalString +=TabStr2+KeyWord(C_LC_LEVELFC       )+TabStr1+tmpStr.sprintf("%8.2f",LevelFC)+CrLfStr;
    LocalString +=TabStr2+KeyWord(C_LC_SOUNDING      )+tmpStr.sprintf("%8.2f",Sounding       )+CrLfStr;
    LocalString +=TabStr2+KeyWord(C_LC_LEVEL_AT_REF  )+tmpStr.sprintf("%8.2f",LevelAtRef     )+CrLfStr;
    LocalString +=TabStr2+KeyWord(C_LC_VOLUME_PERCENT)+tmpStr.sprintf("%8.2f",VolumePercent  )+CrLfStr;

    LocalString +=TabStr2+KeyWord(C_LC_VOLUME        )+TabStr1+tmpStr.sprintf("%8.1f",Volume )+CrLfStr;
    LocalString +=TabStr2+KeyWord(C_LC_WEIGHT        )+TabStr1+tmpStr.sprintf("%8.1f",Weight )+CrLfStr;
    LocalString +=TabStr2+KeyWord(C_LC_DENSITY       )+TabStr1+tmpStr.sprintf("%8.5f",Density)+CrLfStr;
    LocalString +=TabStr2+KeyWord(TSN_TEMP_APP       )+TabStr1+tmpStr.sprintf("%8.2f",Temperature)+CrLfStr;
    if ( IsOnline ) {
        LocalString +=TabStr2+KeyWord(C_ONLINE )+CrLfStr;
    } else {
        LocalString +=TabStr2+KeyWord(C_OFFLINE)+CrLfStr;
    }
    LocalString += CargoType.SaveSettings(1);
    LocalString +=TabStr1+KeyWord(C_LC_END)+CrLfStr;
    LocalString += CrLfStr;
    return(LocalString);
}


void LCTankData::SetCargoType(void)
{
    switch ( TankType ) {
    default:
        CargoType.InputBasicCargoType(CTY_SIMPLE_LIN);
        break;
    case TANKTYPE_CARGO:
        CargoType.InputBasicCargoType(CTY_LINEAR);
        break;
    case TANKTYPE_BALLAST:
    case TANKTYPE_VOIDSPACE:
        CargoType.InputBasicCargoType(CTY_BALLAST);
        break;
    case TANKTYPE_HFO:
        CargoType.InputBasicCargoType(CTY_HFO);
        break;
    case TANKTYPE_DO:
        CargoType.InputBasicCargoType(CTY_DO);
        break;
    case TANKTYPE_LUB:
        CargoType.InputBasicCargoType(CTY_LUB);
        break;
    case TANKTYPE_FW:
        CargoType.InputBasicCargoType(CTY_FW);
        break;
    case TANKTYPE_MISC:
        CargoType.InputBasicCargoType(CTY_SIMPLE_LIN);
        break;
    }
    Temperature = CargoType.RefTmp1;
    Density     = CargoType.Comp_Density(Temperature);
}
void LCTankData::CalculateMoments(float *LMoment, float *TMoment, float *VMoment,float *TFSMoment)
{
    if ( LCShipData::IsOnline && IsOnline ) {
        GetOnlineValues();
    } else {
        Density = CargoType.Comp_Density(Temperature);

        HWFailure   = false;
        LevelAtRef  = LevelFC - LCShipData::TrimListCorrection(LDist,TDist);
        UllageRef      = DBotUllRefPnt-LevelAtRef+0.0005;
        // Make correction from FC to the reference point when offline condition
        // In Loadcalc we always will use the density in air
        //Density   = Density; // Should maybe use cargo type here?
    }
    Weight    = Volume*Density;//DnsInVac_to_DnsInAir(Density);
    if ( CG_Table ) {
        CG_Table->Calculate(LevelFC,&LCG,&TCG,&VCG);
    } else {
        CG_UllTable->Calculate(UllageFC,&LCG,&TCG,&VCG);
    }
    LCG -= LCShipData::MS_to_APP_Corr;
    if ( LevelFC ) {
        *LMoment    += Weight*LCG;
        *TMoment    += Weight*TCG;
        *VMoment    += Weight*VCG;
        WeightSum[TankType] += Weight;
        Liquid_Weight       += Weight;
        if ( TFS_Table || TFS_UllTable ) {
            switch ( LCShipData::ClassificationSociety ) {
            case C_LC_CLASS_BV   :
                switch ( LCShipData::LoadCalcVersion ) {
                default:
                    // Ref BV,Roger
                    if ( VolumePercent ) {
                        if ( TFS_Table ) {
                            TFreeSurf   = TFS_Table->Calc_Y(LevelFC);
                        } else {
                            TFreeSurf   = TFS_UllTable->Calc_Y(UllageFC);
                        }
                        TFS_Moment  = TFreeSurf*Density;
                        *TFSMoment += TFS_Moment;
                    } else {
                        TFreeSurf   = 0.0;
                        TFS_Moment  = 0.0;
                    }
                    break;
                case LC_CALC_VERSION2:
                    // Ref BV,Roger
                    if ( VolumePercent && VolumePercent < 99.95  ) {
                        if ( TFS_Table ) {
                            TFreeSurf   = TFS_Table->Calc_Y(LevelFC);
                        } else {
                            TFreeSurf   = TFS_UllTable->Calc_Y(UllageFC);
                        }
                        TFS_Moment  = TFreeSurf*Density;
                        *TFSMoment += TFS_Moment;
                    } else {
                        TFreeSurf   = 0.0;
                        TFS_Moment  = 0.0;
                    }
                    break;
                }
                break;
            case C_LC_CLASS_DNV :
                if ( LCShipData::LoadCalcVersion>= LC_CALC_VERSION1 ) {
                    if ( VolumePercent && VolumePercent < 98.05 ) {
                        if ( TFS_Table ) {
                            TFreeSurf   = TFS_Table->Calc_Y(LevelFC);
                        } else {
                            TFreeSurf   = TFS_UllTable->Calc_Y(UllageFC);
                        }
                        TFS_Moment  = TFreeSurf*Density;
                        *TFSMoment += TFS_Moment;
                    } else {
                        TFreeSurf   = 0.0;
                        TFS_Moment  = 0.0;
                    }
                }
                break;
            case C_LC_CLASS_UNKNOWN:
            default                :
                if ( LCShipData::LoadCalcVersion>= LC_CALC_VERSION1 ) {
                    if ( VolumePercent ) {
                        if ( TFS_Table ) {
                            TFreeSurf   = TFS_Table->Calc_Y(LevelFC);
                        } else {
                            TFreeSurf   = TFS_UllTable->Calc_Y(UllageFC);
                        }
                        TFS_Moment  = TFreeSurf*Density;
                        *TFSMoment += TFS_Moment;
                    } else {
                        TFreeSurf   = 0.0;
                        TFS_Moment  = 0.0;
                    }
                }
                break;
            }
        }

        // Add weight to each section
        if ( !LCShipData::Stability_Only ) {
            for ( unsigned i=0; i < Section.size(); i++ ) {
                Section[i]->DeadWeight += PercentageInSection[i]*Weight;
            }
        }
    } else {
        TFreeSurf  = 0.0;
        TFS_Moment = 0.0;
    }
}

void LCTankData::SetOnlineTank(PROTank *TankPtr)
{
    OnlineTank = TankPtr;
    if ( OnlineTank ) {
        OnlineTank->GetHorisontalDistances(&LDist,&TDist);
        // EHSMark: To be added logic to know which tables which can be deleted on destruct
        if ( LevVolumeTab    /*&& OnlineTank->LevVolumeTab    */ ) {
            delete LevVolumeTab    ;
            LevVolumeTab = NULL;
        }
        if ( UllVolumeTab    /*&& OnlineTank->UllVolumeTab    */ ) {
            delete UllVolumeTab    ;
            UllVolumeTab = NULL;
        }
        if ( SoundingTab     /*&& OnlineTank->SoundingTab     */ ) {
            delete SoundingTab     ;
            SoundingTab = NULL;
        }
        if ( CenterOfFlotTab /*&& OnlineTank->CenterOfFlotTab */ ) {
            delete CenterOfFlotTab ;
            CenterOfFlotTab = NULL;
        }
        //TankType      = OnlineTank->TankType       ;
        LevVolumeTab    = OnlineTank->LevVolumeTab   ;
        UllVolumeTab    = OnlineTank->UllVolumeTab   ;
        VolumeTab       = OnlineTank->VolumeTab      ;
        SoundingTab     = OnlineTank->SoundingTab    ;
        CenterOfFlotTab = OnlineTank->CenterOfFlotTab;
        DBotUllRefPnt   = OnlineTank->DBotUllRefPnt;
    }
}

void LCTankData::GetOnlineValues(void)
{
    if ( OnlineTank ) {
        CargoType = *OnlineTank->CargoType;
        HWFailure = OnlineTank->GetOnlineValues(&LevelFC,&Sounding,&LevelAtRef, &UllageRef, &UllageFC,
                                                &Volume,&VolumePercent,&Density,&Temperature);
        Weight  = Volume*Density;
    }
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int LCTankData::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_WEIGHT:
        DecPnt     = 1;
        Unit       = WEIGHT_UNIT;
        if ( VolumeTab ) {
            MyRetValue = GetCorrectedWeight(Weight,Density);
        } else {
            Status     = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_VOLUME:
        DecPnt     = 1;
        Unit       = VOLUME_UNIT;
        if ( VolumeTab ) {
            MyRetValue = Volume;
        } else {
            Status     = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_VOL_AT_REFTMP:
        DecPnt     = 1;
        Unit       = VOLUME_UNIT;
        if ( VolumeTab ) {
            MyRetValue = VolumeAtRefTmp();
        } else {
            Status     = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_VOLPERCENT:
        DecPnt     = 2;
        Unit       = PERCENT_UNIT;
        if ( VolumeTab ) {
            MyRetValue = VolumePercent;
        } else {
            Status     = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_SOUNDING:   // Sounding table!!!
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        MyRetValue = Sounding;
        break;
    case SVT_LEVEL_FC:
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        MyRetValue = LevelFC;
        break;
    case SVT_LEVEL_REF:
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        MyRetValue = LevelAtRef;
        break;
    case SVT_ULLAGE:
        DecPnt     = 3;
        Unit       = LENGTH_UNIT;
        if ( DBU_IsConfigured || ( TankType == TANKTYPE_CARGO ) ) {
            MyRetValue = UllageRef;
        } else {
            Status = GETVAL_NO_DISPLAY;
        }
        break;
    case SVT_TEMP:
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        MyRetValue = Temperature;
        break;
    case SVT_LOADRATE:
        DecPnt     = 1;
        Unit       = LOADRATE_UNIT;
        if ( !LoadRate ) {
            Status = GETVAL_NO_DISPLAY;
        }
        MyRetValue = LoadRate;
        break;
    case SVT_MEAS_DNS:
        MyRetValue = MeasuredDns;
        DecPnt     = 4;
        Unit       = DENSITY_UNIT;
        if ( !HasMeasuredDensity ) {
            Status  = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_MEASURED_API :
        if ( !HasMeasuredDensity ) {
            Status  = GETVAL_NOT_AVAILABLE;
        }
        MyRetValue = CargoType.MeasDns_to_API(Temperature,Density);
        DecPnt     = 4;
        Unit       = NO_UNIT;
        break;
    case SVT_VCF_AT_TEMP :
        MyRetValue = CargoType.DensityToVcfAtTemp(Density,Temperature);
        DecPnt     = 4;
        Unit       = NO_UNIT;
        break;
    case SVT_DENSITY:
        DecPnt     = 4;
        Unit       = DENSITY_UNIT;
        MyRetValue = Density;
        break;
    case SVT_BASIC_TYPE:
    case SVT_CARGO_TYPE:
    case SVT_REF_DNS1  :
    case SVT_REF_DNS2  :
    case SVT_REF_TMP1 :
    case SVT_REF_TMP2 :
    case SVT_COEFF    :
    case SVT_API      :
    case SVT_VCF      :
        Status = CargoType.GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    case SVT_L_TFS:
        DecPnt     = 1;
        Unit       = FREE_SURF_UNIT;
        MyRetValue = TFreeSurf;
        break;
    case SVT_L_FSM:
        DecPnt     = 1;
        Unit       = MOMENT_UNIT;
        MyRetValue = TFS_Moment;
        break;
    default:
        Status = LCLocationData::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
        break;
    }
    return(Status);
}

int LCTankData::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_REMAINING_TIME :
        if ( !HWFailure ) {
            if ( RemainingTime ) {
                int Hour = (int)RemainingTime;
                int Min  = (int)((RemainingTime-Hour)*60.0);
                char Buf[BUF_SIZE];
                sprintf(Buf,"%i:%02i",Hour,Min);
                MyString = Buf;
            } else {
                MyString = "";
            }
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_FINISH_TIME  :
        if ( !HWFailure ) {
            if ( RemainingTime ) {
                int Hour = (int)RemainingTime;
                int Min  = (int)((RemainingTime-Hour)*60);
                const time_t t = time(NULL);
                struct tm *tBuf;
                tBuf =localtime(&t);
                Min += tBuf->tm_min;
                if ( Min >= 60 ) Min -= 60,Hour++;
                Hour += tBuf->tm_hour;
                if ( Hour >= 24 )       Hour -= 24;
                char Buf[BUF_SIZE];
                sprintf(Buf,"%i:%02i",Hour,Min);
                MyString = Buf;
            } else {
                MyString = "";
            }
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_COLOUR         :
    case SVT_BASIC_TYPE_NAME:
    case SVT_CARGO_TYPE_NAME:
        Status = CargoType.GetStringValue(ValueId,Index, MyString);
        break;
    case SVT_L_ONLINE_STATUS:
        if ( IsOnline ) {
            MyString = FindKeyWord(C_ONLINE);
        } else {
            MyString = FindKeyWord(C_OFFLINE);
        }
    default:
        Status = LCLocationData::GetStringValue(ValueId,Index, MyString);
        break;
    }
    return(Status);
}

int LCTankData::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status=E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_WEIGHT:
        if ( VolumeTab ) {
            float MaxWgt = VolumeTab->MaxY*Density;
            if ( HasMaxWeight ) {
                MaxWgt = min(MaxWeight,MaxWgt);
            }
            float tmpWgt =(float)ConvertToSi(NewValue, ValUnitId = WEIGHT_UNIT, Status,0.0 ,MaxWgt,Weight);
            if ( Status == E_NO_ERR ) InputWeight(tmpWgt);
        }
        break;
    case SVT_VOLUME:
        if ( VolumeTab ) {
            float MaxVol = VolumeTab->MaxY;
            if ( HasMaxWeight ) {
                MaxVol = min(MaxVol,MaxWeight/Density);
            }
            float tmpVol =(float)ConvertToSi(NewValue, ValUnitId = VOLUME_UNIT, Status,0.0 ,MaxVol,Volume);
            if ( Status == E_NO_ERR ) InputVolume(tmpVol);
        }
        break;
    case SVT_VOLPERCENT:
        if ( VolumeTab ) {
            float MaxPercent = 100.0;
            if ( HasMaxWeight ) {
                float MaxVolP = MaxWeight/Density/VolumeTab->MaxY*100.0;
                MaxPercent = min(MaxPercent,MaxVolP);
            }
            ValUnitId = PERCENT_UNIT;
            float tmpVolP =(float)ConvertToSi(NewValue, PERCENT_UNIT, Status,0.0 ,MaxPercent,VolumePercent);
            if ( Status == E_NO_ERR ) InputVolumePercent(tmpVolP);
        }
        break;
    case SVT_LEVEL_FC:
        if ( VolumeTab ) {
            float MaxLev = VolumeTab->MaxX;
            float MaxVol = VolumeTab->MaxY;
            if ( HasMaxWeight ) {
                MaxVol = min(MaxVol,MaxWeight/Density);
                if ( LevVolumeTab ) {
                    MaxLev = LevVolumeTab->Calc_X(MaxVol);
                } else {
                    float MinUll = UllVolumeTab->Calc_X(MaxVol);
                    MaxLev = DBotUllRefPnt - MinUll;
                }
            }
            ValUnitId = LENGTH_UNIT;
            float tmpLev =(float)ConvertToSi(NewValue, LENGTH_UNIT, Status,0.0 ,MaxLev,LevelFC);
            if ( Status == E_NO_ERR ) InputLevelFC(tmpLev);
        }
        break;
    case SVT_LEVEL_REF:
        if ( VolumeTab ) {
            float MaxLev = VolumeTab->MaxX;
            float MaxVol = VolumeTab->MaxY;
            if ( LevVolumeTab ) {
                MaxLev = LevVolumeTab->Calc_X(MaxVol);
            } else {
                float MinUll = UllVolumeTab->Calc_X(MaxVol);
                MaxLev = DBotUllRefPnt - MinUll;
            }
            ValUnitId = LENGTH_UNIT;
            float tmpLev =(float)ConvertToSi(NewValue, LENGTH_UNIT, Status,0.0 ,MaxLev,LevelAtRef);
            if ( Status == E_NO_ERR ) InputLevelAtRef(tmpLev);
        }
        break;
    case SVT_ULLAGE:
        if ( VolumeTab ) {
            float MinUll = 0.0;
            float MaxVol = VolumeTab->MaxY;
            if ( HasMaxWeight ) {
                MaxVol = min(MaxVol,MaxWeight/Density);
                MinUll = DBotUllRefPnt - LevVolumeTab->Calc_X(MaxVol);
            }
            ValUnitId = LENGTH_UNIT;
            float tmpUll =(float)ConvertToSi(NewValue, LENGTH_UNIT, Status,MinUll ,DBotUllRefPnt,UllageRef);
            if ( Status == E_NO_ERR ) InputUllageAtRef(tmpUll);
        }
        break;
    case SVT_TEMP:
        Temperature = ConvertToSi(NewValue, TEMP_UNIT, Status,MIN_TEMP ,MAX_TEMP,Temperature);
        break;
    case SVT_CARGO_TYPE_NAME:
        {
            unsigned CargoId = GetUnsigned(NewValue, Status);
            if ( Status== E_NO_ERR ) {
                short tmpCargoType = CargoId >> 16;
                short tmpBaseCargo = CargoId & 0xffff;
                if ( tmpCargoType == CTY_NOT_DEFINED ) {
                    Status = CargoType.PutValue(SVT_BASIC_TYPE, Index, (AnsiString)tmpBaseCargo);
                } else {
                    GetCargoTypeSettings(tmpCargoType);
                }
            }
        }
        break;
    case SVT_CARGO_TYPE:
        {
            int Value = GetInt(NewValue, Status);
            if ( Status== E_NO_ERR ) {
                if ( Value == CTY_NOT_DEFINED ) {
                    CargoType.CargoTypeKey = CTY_NOT_DEFINED;
                } else {
                    GetCargoTypeSettings(Value);
                }
            }
        }
        break;
    case SVT_REF_DNS1 :
    case SVT_REF_DNS2 :
    case SVT_REF_TMP1 :
    case SVT_REF_TMP2 :
    case SVT_COEFF :
    case SVT_DENSITY:
    case SVT_BASIC_TYPE:
    case SVT_API :
        Status = CargoType.PutValue( ValueId, Index,NewValue,Local,&ValUnitId);
        break;
    case SVT_L_ONLINE_STATUS:
        {
            int Key = FindConfigKey(NewValue);
            switch ( Key ) {
            case C_ONLINE:
            case C_ENABLE:
                IsOnline = true;
                break;
            case C_OFFLINE:
            case C_DISABLE:
                IsOnline = false;
                break;
            default:
                {
                    bool Value = (bool)GetUnsigned(NewValue, Status);
                    if ( Status== E_NO_ERR ) {
                        IsOnline = Value;
                    }
                }
                break;
            }
        }
        break;
    default:
        Status = LCLocationData::PutValue( ValueId, Index,NewValue,Local,&ValUnitId);
        break;
    }
    if ( Status == E_NO_ERR ) {
        Status = E_LOCAL_ONLY;
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return(Status);
}

int LCTankData::PutFloatValue( int ValueId, float NewValue)
{
    return(LCLocationData::PutFloatValue(ValueId,NewValue));
}

void LCTankData::InputUllageAtRef(float UllageRef)
{
    float Level = DBotUllRefPnt - UllageRef;
    Level -= LCShipData::Trim*(cDLFC-cDLR) + LCShipData::List*(cDTFC-cDTR);
    InputLevelFC(Level);
}

void LCTankData::InputUllageFC(float Ullage)
{
    float Level = DBotUllRefPnt - Ullage;
    if ( Level < 0.0 ) {
        Level = 0.0;
    }
    InputLevelFC(Level);
}

void LCTankData::InputLevelAtRef(float Level)
{
    Level -= LCShipData::Trim*(cDLFC-cDLR) + LCShipData::List*(cDTFC-cDTR);
    InputLevelFC(Level);
}

void LCTankData::InputLevelFC(float Level)
{
    if ( Level ) {
        LevelFC     = Level+0.0005;
        LevelAtRef  = Level + LCShipData::Trim*(cDLFC-cDLR) + LCShipData::List*(cDTFC-cDTR)+0.0005;
        UllageRef      = DBotUllRefPnt-LevelAtRef+0.0005;
        UllageFC    = DBotUllRefPnt -LevelFC+0.0005;
        if ( LevVolumeTab ) {
            Volume          = LevVolumeTab->Calc_Y(LevelFC)+0.00005;
            VolumePercent   = Volume / LevVolumeTab->MaxY*100.0+0.0005;
        } else if ( UllVolumeTab ) {
            Volume          = UllVolumeTab->Calc_Y(UllageFC)+0.00005;
            VolumePercent   = Volume / UllVolumeTab->MaxY*100.0+0.0005;
        }
        Weight          = Density * Volume;
        if ( SoundingTab ) {
            float tmpSounding = SoundingTab->Calc_X(Volume);
            tmpSounding += LCShipData::Trim*(cDLFC-cDLR) + LCShipData::List*(cDTFC-cDTR); // Was -, corrected to +
            if ( tmpSounding > 0.0 ) {
                Sounding = tmpSounding;
            } else {
                Sounding = 0.0;
            }
        } else {
            Sounding = LevelAtRef;
        }
    } else {
        LevelFC         = 0.0;
        LevelAtRef      = 0.0;
        Volume          = 0.0;
        VolumePercent   = 0.0;
        Weight          = 0.0;
        Sounding        = 0.0;
    }
}

void LCTankData::InputVolumePercent(float VolPercent)
{
    if ( LevVolumeTab ) {
        float tmpLevelFC=  LevVolumeTab->Calc_XPercent(VolPercent);
        if ( tmpLevelFC< 0.0 ) {
            tmpLevelFC = 0.0;
        }
        InputLevelFC(tmpLevelFC);
    } else if ( UllVolumeTab ) {
        float tmpUllageFC=  UllVolumeTab->Calc_XPercent(VolPercent);
        if ( tmpUllageFC< 0.0 ) {
            tmpUllageFC = 0.0;
        }
        InputUllageFC(tmpUllageFC);
    }
    VolumePercent = VolPercent;
}

void LCTankData::InputVolume(float Vol)
{
    if ( LevVolumeTab ) {
        float tmpLevelFC=  LevVolumeTab->Calc_X(Vol);
        if ( tmpLevelFC< 0.0 ) {
            tmpLevelFC = 0.0;
        }
        InputLevelFC(tmpLevelFC);
    } else if ( UllVolumeTab ) {
        float tmpUllageFC=  UllVolumeTab->Calc_X(Vol);
        if ( tmpUllageFC< 0.0 ) {
            tmpUllageFC = 0.0;
        }
        InputUllageFC(tmpUllageFC);
    }
    Volume = Vol;
}

void LCTankData::InputWeight(float Wgt)
{
    Wgt = CorrectToWeightInVacuum(Wgt,Density);
    if ( LevVolumeTab ) {
        float tmpLevelFC=  LevVolumeTab->Calc_X(Wgt/Density);
        if ( tmpLevelFC< 0.0 ) {
            tmpLevelFC = 0.0;
        }
        InputLevelFC(tmpLevelFC);
    } else if ( UllVolumeTab ) {
        float tmpUllageFC=  UllVolumeTab->Calc_X(Wgt/Density);
        if ( tmpUllageFC< 0.0 ) {
            tmpUllageFC = 0.0;
        }
        InputUllageFC(tmpUllageFC);
    }
    Weight = Wgt;
}
void LCTankData::GetCargoTypeSettings(int Key)
{
    if ( Key!= CTY_NOT_DEFINED && Key < MAX_CARGOTYPES ) {
        CTOUser *UsrCargoPtr = CTOUser::CargoTable[Key];
        // Must be defined, if not, ignore
        if ( UsrCargoPtr && UsrCargoPtr->IsTheCargoDefined() ) {
            CargoType.BaseCargoType = UsrCargoPtr->BaseCargoType;
            CargoType.CargoTypeKey  = UsrCargoPtr->CargoTypeKey ;
            CargoType.Name          = UsrCargoPtr->Name         ;
            CargoType.OD1           = UsrCargoPtr->OD1          ;
            CargoType.OD2           = UsrCargoPtr->OD2          ;
            CargoType.RefTmp1       = UsrCargoPtr->RefTmp1      ;
            CargoType.RefTmp2       = UsrCargoPtr->RefTmp2      ;
            CargoType.Coeff         = UsrCargoPtr->Coeff        ;
            CargoType.Colour        = UsrCargoPtr->Colour       ;
        }
    }
}

float LCTankData::VolumeAtRefTmp(void)
{
    float Vol;
    if ( VolumeTab ) {
        Vol = CargoType.VolumeAtRefTmp(Weight, Volume,Density,Temperature);
    } else {
        Vol = 0.0;
    }
    return(Vol);
}

ValueList LCTankData::SelectLCTankValueList[] =  {
	{L_WORD677          ,L_WORD237,SVT_LEVEL_SENSOR},
	{L_WORD307          ,L_WORD237,SVT_LEVEL_FC},
	{L_WORD306          ,L_WORD237,SVT_LEVEL_REF},
	{L_WORD316          ,L_WORD237,SVT_SOUNDING},
	{L_WORD309          ,L_WORD237,SVT_ULLAGE},
	{L_WORD44           ,L_WORD237,SVT_VOLUME},
	{L_WORD310          ,L_WORD237,SVT_VOLPERCENT},
	{L_WORD776          ,L_WORD777 ,SVT_CAPACITY},                              // {"Capacity"    ,"Cap" ,SVT_CAPACITY},
	{L_WORD45           ,L_WORD237,SVT_WEIGHT},
	{L_WORD83           ,L_WORD237,SVT_DENSITY},
	{L_WORD338          ,L_WORD237,SVT_TEMP},
	{L_WORD247          ,L_WORD237,SVT_LOADRATE},
	{L_WORD314          ,L_WORD237,SVT_FINISH_TIME},
	{L_WORD315          ,L_WORD237,SVT_REMAINING_TIME},
	{L_WORD393          ,L_WORD237,SVT_CARGO_TYPE_NAME},                         //   {"Cargo Name"   ,"",SVT_CARGO_TYPE_NAME},
	{L_WORD102          ,L_WORD237,SVT_API},                                     //   {"API"          ,"",SVT_API},
	{L_WORD316          ,L_WORD237,SVT_CARGO_TYPE},
	{L_WORD398          ,L_WORD237,SVT_REF_DNS1},                                //   {"Ref.Density1" ,"",SVT_REF_DNS1},
	{L_WORD399          ,L_WORD237,SVT_REF_DNS2},                                //   {"Ref.Density2" ,"",SVT_REF_DNS2},
	{L_WORD400          ,L_WORD237,SVT_REF_TMP1},                                //   {"Ref. Temp1"   ,"",SVT_REF_TMP1},
	{L_WORD401          ,L_WORD237,SVT_REF_TMP2},                                //   {"Ref. Temp2"   ,"",SVT_REF_TMP2},
	{L_WORD108          ,L_WORD237,SVT_COEFF},                                   //   {"Coefficient"  ,"",SVT_COEFF},
	{L_WORD743          ,L_WORD237,SVT_VCF},                                     //   {"Coefficient"  ,"",SVT_COEFF},
	{L_WORD705          ,L_WORD237,SVT_L_LCG},
	{L_WORD704          ,L_WORD237,SVT_L_TCG},
	{L_WORD682          ,L_WORD237,SVT_L_VCG},
	{L_WORD738          ,L_WORD237,SVT_L_TFS},
	{L_WORD739          ,L_WORD237,SVT_L_FSM},
	{L_WORD739          ,L_WORD237,SVT_L_FSM},
	{L_WORD238          ,L_WORD237,SVT_L_LENGTH},
	{L_WORD766          ,L_WORD237,SVT_L_ONLINE_STATUS},

};


ValueList *LCTankData::GetValueInfoTable(int &Entries, int Index)
{
	return GetValueInfoTableStatic(Entries,Index);
}

ValueList *LCTankData::GetValueInfoTableStatic(int &Entries, int Index, bool Redundancy)
{
    Entries = NELEMENTS(SelectLCTankValueList);
    return(SelectLCTankValueList);
}

float LCTankData::GetFSMoments(int TType)
{
    vector<LCLocationData*>CurrentTable;
    switch ( TType ) {
    case TANKTYPE_CARGO    :
        CurrentTable = CargoTable;
        break;
    case TANKTYPE_BALLAST  :
        CurrentTable = BallastTable;
        break;
    case TANKTYPE_HFO      :
        CurrentTable = HFOTable;
        break;
    case TANKTYPE_DO       :
        CurrentTable = DieselTable;
        break;
    case TANKTYPE_LUB      :
        CurrentTable = LubricantsTable;
        break;
    case TANKTYPE_FW       :
        CurrentTable = FreshWaterTable;
        break;
    case TANKTYPE_MISC     :
        CurrentTable = MiscTable;
        break;
    case TANKTYPE_VOIDSPACE:
        CurrentTable = VoidSpaceTable;
        break;
    }
    float FSMom = 0.0;
    for ( unsigned i=0; i < CurrentTable.size(); i++ ) {
        LCTankData *Tnk = (LCTankData*)CurrentTable[i];
        FSMom += Tnk->TFS_Moment;
    }
    return FSMom;
}

TColor LCTankData::GetCargoColor(void)
{
    return CargoType.Colour;
}

bool LCTankData::IsOnlineTank(void)
{
    return bool(OnlineTank);
}

