#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

LoadReport *LoadReport::LoadReportPtr = NULL;

LoadReport::LoadReport(void):PRogramObject( false ) {
    IDNumber = (C_PRO_LOADREPORT << 16) + 1;

    BillLoading         = 0.0;
    BillOfLadingVolume  = 0.0;
    DraftFore           = 0.0;
    DraftMid            = 0.0;
    DraftAft            = 0.0;
    /*
    LoadPort 		= "";
    DestPort 		= "";
    Voyage 			= "";
    Start 			= "";
    Stop 				= "";
    Inspection	= "";
    ShipName 		= "";
    ShipTitle 	= "";
    SurvName 		= "";
    SurvTitle   = "";
    Remark1 		= "";
    DraftFore 	= "";
    DraftMid 		= "";
    DraftAft 		= "";
    */
}
//---------------------------------------------------------------------------

LoadReport::~LoadReport(void) {
    //Only increase: NumberOfPRO--;
/*  if(HighPressurePtr){
        delete HighPressurePtr;
        HighPressurePtr = NULL;
    }   */
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////
void LoadReport::SaveSettings(TSNConfigString *SettingsString) {
}

bool LoadReport::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    return NoError;
}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////
int LoadReport::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_LR_BILL_LOADING:
        DecPnt     = 1;
        Unit       = WEIGHT_UNIT;
        MyRetValue = BillLoading;
        break;
    case SVT_LR_BILL_LOADING_VOL:
        DecPnt     = 1;
        Unit       = VOLUME_UNIT;
        MyRetValue = BillOfLadingVolume;
        break;
    case SVT_LR_DF   :
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = DraftFore;
        break;
    case SVT_LR_DMID            :
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = DraftMid;
        break;
    case SVT_LR_DA              :
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = DraftAft;
        break;
    case SVT_LR_SHIP_FIGURES:
        DecPnt     = 1;
        Unit       = WEIGHT_UNIT;
        MyRetValue = GetTotalWeight();
        break;
    case SVT_LR_SHIP_VOL_FIGURES:
        DecPnt     = 1;
        Unit       = VOLUME_UNIT;
        MyRetValue = GetTotalVolume();
        break;
    case SVT_LR_DIFFERENCE_WGT  :
        DecPnt     = 1;
        Unit       = WEIGHT_UNIT;
        MyRetValue = GetTotalWeight() - BillLoading;
        break;
    case SVT_LR_DIFFERENCE_VOL  :
        DecPnt     = 1;
        Unit       = VOLUME_UNIT;
        if ( BillOfLadingVolume ) {
            MyRetValue = GetTotalVolume() - BillOfLadingVolume;
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_LR_DIFFERENCE_WGT_PCT  :
        DecPnt     = 2;
        Unit       = PERCENT_UNIT;
        if ( BillLoading ) {
            MyRetValue = (GetTotalWeight() - BillLoading) / BillLoading * 100.0;
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_LR_DIFFERENCE_VOL_PCT  :
        DecPnt     = 2;
        Unit       = PERCENT_UNIT;
        if ( BillOfLadingVolume ) {
            MyRetValue = (GetTotalVolume() - BillOfLadingVolume) / BillOfLadingVolume * 100.0;
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_LR_TRIM:
        Status = PROSystemData::TXUSystemData->GetValue(SVT_TRIM_M, Index, MyRetValue,  DecPnt, Unit);
        break;
    case SVT_LR_LIST:
        Status = PROSystemData::TXUSystemData->GetValue(SVT_LIST_ANGLE_NOSIGN, Index, MyRetValue,  DecPnt, Unit);
        break;
    default:
        Status = PRogramObject::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int LoadReport::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_LR_LOADPORT        :
        MyString = LoadPort;
        break;
    case SVT_LR_DESTPORT        :
        MyString = DestPort;
        break;
    case SVT_LR_VOYAGE        :
        MyString = Voyage;
        break;
    case SVT_LR_START         :
        MyString = Start;
        break;
    case SVT_LR_STOP            :
        MyString = Stop;
        break;
    case SVT_LR_INSPECTION  :
        MyString = Inspection;
        break;
    case SVT_LR_SHIP_NAME   :
        MyString = ShipName;
        break;
    case SVT_LR_SHIP_TITLE  :
        MyString = ShipTitle;
        break;
    case SVT_LR_SURV_NAME   :
        MyString = SurvName;
        break;
    case SVT_LR_SURV_TITLE  :
        MyString = SurvTitle;
        break;
    case SVT_LR_REMARK1     :
        MyString = Remark1;
        break;
    default:
        Status = PRogramObject::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int LoadReport::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;

    switch ( ValueId ) {
    case SVT_LR_LOADPORT        :
        LoadPort = NewValue;
        break;
    case SVT_LR_DESTPORT        :
        DestPort = NewValue;
        break;
    case SVT_LR_VOYAGE        :
        Voyage = NewValue;
        break;
    case SVT_LR_START         :
        Start = NewValue;
        break;
    case SVT_LR_STOP            :
        Stop = NewValue;
        break;
    case SVT_LR_INSPECTION  :
        Inspection = NewValue;
        break;
    case SVT_LR_SHIP_NAME   :
        ShipName = NewValue;
        break;
    case SVT_LR_SHIP_TITLE  :
        ShipTitle = NewValue;
        break;
    case SVT_LR_SURV_NAME   :
        SurvName = NewValue;
        break;
    case SVT_LR_SURV_TITLE  :
        SurvTitle = NewValue;
        break;
    case SVT_LR_REMARK1     :
        Remark1 = NewValue;
        break;
    case SVT_LR_DF          :
        DraftFore   = ConvertToSi(NewValue, LENGTH_UNIT, Status, 0.0, 30.0, DraftFore);
        break;
    case SVT_LR_DMID            :
        DraftMid    = ConvertToSi(NewValue, LENGTH_UNIT, Status, 0.0, 30.0, DraftMid);
        break;
    case SVT_LR_DA              :
        DraftAft    = ConvertToSi(NewValue, LENGTH_UNIT, Status, 0.0, 30.0, DraftAft);
        break;
    case SVT_LR_BILL_LOADING:
        BillLoading = ConvertToSi(NewValue, WEIGHT_UNIT, Status, 0.0, 100000, BillLoading);
        break;
    case SVT_LR_BILL_LOADING_VOL:
        BillOfLadingVolume = ConvertToSi(NewValue, VOLUME_UNIT, Status, 0.0, 100000, BillOfLadingVolume);
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

int LoadReport::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = PRogramObject::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return (Status);

}
ValueList LoadReport::ServiceReportTankValueList[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },                                               // {"Unused"    ,"",SVT_BLANK},
    { L_WORD677, L_WORD445, SVT_LEVEL_REF },                                     // {"Level"     ,"Lev" ,SVT_LEVEL_REF},
    { L_WORD308, L_WORD332, SVT_SOUNDING },                                      // {"Sounding"  ,"Snd" ,SVT_SOUNDING},
    { L_WORD309, L_WORD333, SVT_ULLAGE },                                        // {"Ullage"    ,"Ull" ,SVT_ULLAGE},
    { L_WORD916, L_WORD917, SVT_ULLAGE_UTI },                                    // {"Ullage UTI" ,"UTI" ,SVT_ULLAGE},
    { L_WORD1064,L_WORD1065, SVT_ULLAGE_RADAR },                             // {"Ullage Radar" ,"URad",SVT_ULLAGE_RADAR},
    { L_WORD44, L_WORD334, SVT_VOLUME },                                        // {"Volume"    ,"Vol" ,SVT_VOLUME},
    { L_WORD310, L_WORD335, SVT_VOLPERCENT },                                    // {"Volume%"   ,"Vol%",SVT_VOLPERCENT},
    { L_WORD776, L_WORD777, SVT_CAPACITY },                                      // {"Capacity"  ,"Cap" ,SVT_CAPACITY},
    { L_WORD45, L_WORD336, SVT_WEIGHT },                                        // {"Weight"    ,"Wgt" ,SVT_WEIGHT},
    { L_WORD83, L_WORD337, SVT_DENSITY },                                       // {"Density"   ,"Dens",SVT_DENSITY},
    { L_WORD338, L_WORD338, SVT_TEMP },                                          // {"Temp"      ,"Temp",SVT_TEMP},
    { L_WORD311, L_WORD339, SVT_PRESSURE },                                      // {"Pressure"  ,"Pres",SVT_PRESSURE},
    { L_WORD247, L_WORD344, SVT_LOADRATE },                                       // {"Loadrate"  ,"LRate",SVT_LOADRATE},
    { L_WORD314, L_WORD345, SVT_FINISH_TIME },                                   // {"FinishTime","FTim",SVT_FINISH_TIME},
    { L_WORD315, L_WORD346, SVT_REMAINING_TIME },                                // {"RemTime"   ,"RTim",SVT_REMAINING_TIME},
    { L_WORD316, L_WORD347, SVT_CARGO_TYPE_NAME },                               // {"CargoType" ,"Ctyp",SVT_CARGO_TYPE_NAME},
    { L_WORD848, L_WORD849, SVT_INTERFACE },                                      // {"Interface","Intrf",SVT_INTERFACE},
    { L_WORD102, L_WORD237, SVT_API },                                             // {"API"          ,"",SVT_API},
    { L_WORD394, L_WORD237, SVT_VCF },                                             // {"VolCorrFactor","",SVT_VCF},
    { L_WORD395, L_WORD237, SVT_VCF_AT_TEMP },                                     // {"VCF@Temp"     ,"",SVT_VCF_AT_TEMP},
    { L_WORD396, L_WORD237, SVT_MEASURED_API },                                    // {"Measured API" ,"",SVT_MEASURED_API},
    { L_WORD397, L_WORD237, SVT_COMP_DNS },                                        // {"Comp. Density","",SVT_COMP_DNS},
    { L_WORD446, L_WORD237, SVT_MEAS_DNS },                                        // {"Meas. Density","",SVT_MEAS_DNS},
                                                                                   //
    { L_WORD398, L_WORD237, SVT_REF_DNS1 },                                        // {"Ref.Density1" ,"",SVT_REF_DNS1},
    { L_WORD399, L_WORD237, SVT_REF_DNS2 },                                        // {"Ref.Density2" ,"",SVT_REF_DNS2},
    { L_WORD400, L_WORD237, SVT_REF_TMP1 },                                        // {"Ref. Temp1"   ,"",SVT_REF_TMP1},
    { L_WORD401, L_WORD237, SVT_REF_TMP2 },                                        // {"Ref. Temp2"   ,"",SVT_REF_TMP2},
    { L_WORD108, L_WORD237, SVT_COEFF },                                           // {"Coefficient"  ,"",SVT_COEFF},
                                                                                   //
    { L_WORD404, L_WORD237, SVT_ATM_PRESSURE },                                // {"AtmPress"         ,"",SVT_ATM_PRESSURE},
    { L_WORD425, L_WORD237, SVT_TRIM_ANGLE_NOSIGN },                                  // {"Trim in deg"      ,"",SVT_TRIM_ANGLE},
    { L_WORD426, L_WORD237, SVT_TRIM_M_NOSIGN },                                      // {"Trim in meter"    ,"",SVT_TRIM_M},
    { L_WORD427, L_WORD237, SVT_LIST_ANGLE_NOSIGN },                                  // {"List in deg"      ,"",SVT_LIST_ANGLE},
    { L_WORD447, L_WORD237, SVT_LIST_M_NOSIGN },                                      // {"List in meter"    ,"",SVT_LIST_M},
    { L_WORD448, L_WORD237, SVT_LATITUDE },                                    // {"Latitude"        ,"",SVT_LATITUDE},


    { L_WORD430, L_WORD237, SVT_DF_MARK },        // {"DF@Mark"          ,"",SVT_DF_MARK},
    { L_WORD431, L_WORD237, SVT_DA_MARK },        // {"DA@Mark"          ,"",SVT_DA_MARK},
    { L_WORD432, L_WORD237, SVT_DF_PP },          // {"DF@PP"            ,"",SVT_DF_PP},
    { L_WORD433, L_WORD237, SVT_DA_PP },          // {"DA@PP"            ,"",SVT_DA_PP},
    { L_WORD421, L_WORD237, SVT_DP },             // {"DP"               ,"",SVT_DP},
    { L_WORD422, L_WORD237, SVT_DS },             // {"DS"               ,"",SVT_DS},
    { L_WORD1066, L_WORD237, SVT_DFP },           // {"DFP"              ,"",SVT_DFP},
    { L_WORD1067, L_WORD237, SVT_DFS },           // {"DFS"              ,"",SVT_DFS},
    { L_WORD1066, L_WORD237, SVT_DAP },           // {"DAP"              ,"",SVT_DAP
    { L_WORD1067, L_WORD237, SVT_DAS },           // {"DAS"              ,"",SVT_DAS},
};


ValueList* LoadReport::GetValueInfoTableStatic(int &Entries, int Index) {
    Entries = NELEMENTS(ServiceReportTankValueList);
    return (ServiceReportTankValueList);
}

int LoadReport::ReceiveData(U8 *data) {
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    default:
        return (E_UNKNOWN_COMMAND);
    };

}

int LoadReport::SendData(U16 cmd) {
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            return (E_OK);
        }
    default:
        return (E_UNKNOWN_COMMAND);
    };
}

void LoadReport::SetTankVector(vector<PRogramObjectBase *>TVector) {
    TankVector = TVector;
}

float LoadReport::GetTotalWeight(void) {
    float Weight = 0.0;
    AnsiString WgtStr = "0.0";
    if ( !TankVector.empty() ) {
        for ( unsigned Row = 0; Row < TankVector.size(); Row++ ) {
            PROTank *tmpPtr = (PROTank *)TankVector[Row];
            if ( tmpPtr ) {
                switch ( tmpPtr->TankType ) {
                default:
                case TANKTYPE_SUM		:
                    break;
                case TANKTYPE_CARGO		:
                case TANKTYPE_BALLAST	:
                case TANKTYPE_HFO    	:
                case TANKTYPE_DO     	:
                case TANKTYPE_LUB    	:
                case TANKTYPE_FW     	:
                case TANKTYPE_MISC   	:
                case TANKTYPE_VOIDSPACE	:
                    Weight += tmpPtr->GetCorrectWeight();
                    break;
                }
            }
        }
    }
    return Weight;
}

float LoadReport::GetTotalVolume(void) {
    float Volume = 0.0;
    AnsiString VolStr = "0.0";
    if ( !TankVector.empty() ) {
        for ( unsigned Row = 0; Row < TankVector.size(); Row++ ) {
            PROTank *tmpPtr = (PROTank *)TankVector[Row];
            if ( tmpPtr ) {
                switch ( tmpPtr->TankType ) {
                default:
                case TANKTYPE_SUM		:
                    break;
                case TANKTYPE_CARGO		:
                case TANKTYPE_BALLAST	:
                case TANKTYPE_HFO    	:
                case TANKTYPE_DO     	:
                case TANKTYPE_LUB    	:
                case TANKTYPE_FW     	:
                case TANKTYPE_MISC   	:
                case TANKTYPE_VOIDSPACE	:
                    Volume += tmpPtr->VolumeAtRefTmp();
                    break;
                }
            }
        }
    }
    return Volume;
}
