#include "TSNIncludes.h"

#pragma hdrstop
//---------------------------------------------------------------------------


float PROTank::GravityCorrection          = 1.00000;
int PROTank::LevelDifferenceFilterDegree  = FILTER_LEVEL_DIFFERENCE;
int PROTank::LevelChangeFilterDegree      = FILTER_LEVEL_CHANGE;
bool PROTank::HasTankWashingMachines       = false;

vector<PROTank              *>PROTank::TankVector;
set<PRogramObjectBase       *>PROTank::ObjectSet;
ANCriticalSection PROTank::LogSema;


///////////////////////////////////////////////////////////
//
//	 Menu definitions for GUIs
//
///////////////////////////////////////////////////////////

ValueList PROTank ::TankValueList[] = {
    { L_WORD304, L_WORD237, SVT_BLANK },                       // {"Unused"    ,"",SVT_BLANK},
    { L_WORD305, L_WORD329, SVT_LEVEL_SENSOR },                  // {"LevelSns"  ,"LevS" ,SVT_LEVEL},
    { L_WORD306, L_WORD330, SVT_LEVEL_REF },               // {"LevelRef"  ,"LevR",SVT_LEVEL_REF},
    { L_WORD307, L_WORD331, SVT_LEVEL_FC },                // {"LevelFC"   ,"LevF",SVT_LEVEL_FC},
    { L_WORD308, L_WORD332, SVT_SOUNDING },              // {"Sounding"  ,"Snd" ,SVT_SOUNDING},
    { L_WORD309, L_WORD333, SVT_ULLAGE },                // {"Ullage"    ,"Ull" ,SVT_ULLAGE},
    { L_WORD916, L_WORD917, SVT_ULLAGE_UTI },            // {"Ullage UTI" ,"UTI" ,SVT_ULLAGE},
    { L_WORD1064, L_WORD1065, SVT_ULLAGE_RADAR },                             // {"Ullage Radar" ,"URad",SVT_ULLAGE_RADAR},
    { L_WORD310, L_WORD335, SVT_VOLPERCENT },              // {"Volume%"   ,"Vol%",SVT_VOLPERCENT},
    { L_WORD44, L_WORD334, SVT_VOLUME },                // {"Volume"    ,"Vol" ,SVT_VOLUME},
    { L_WORD776, L_WORD777, SVT_CAPACITY },              // {"Capacity"    ,"Cap" ,SVT_CAPACITY},
    { L_WORD45, L_WORD336, SVT_WEIGHT },                // {"Weight"    ,"Wgt" ,SVT_WEIGHT},
    { L_WORD83, L_WORD337, SVT_DENSITY },                 // {"Density"   ,"Dens",SVT_DENSITY},
    { L_WORD1010, L_WORD237, SVT_MEAS_DNS_RAW },            // {"Meas. Density","",SVT_MEAS_DNS_RAW},  //Raw measured density on the TDU
    { L_WORD338, L_WORD338, SVT_TEMP },                    // {"Temp"      ,"Temp",SVT_TEMP},
    { L_WORD1049,  L_WORD1049, SVT_VAPOR_TEMP },           // {"VaporTemp"      ,"VaporTemp",SVT_TEMP},
    { L_WORD311, L_WORD339, SVT_PRESSURE },                // {"Pressure"  ,"Pres",SVT_PRESSURE},
    { L_WORD112, L_WORD340, SVT_HI_TEMP_LIMIT },           // {"High Temp" ,"HTmp",SVT_HI_TEMP_LIMIT},
    { L_WORD113, L_WORD341, SVT_LO_TEMP_LIMIT },           // {"Low Temp"  ,"LTmp",SVT_LO_TEMP_LIMIT},
    { L_WORD312, L_WORD342, SVT_HI_PRESS_LIMIT },          // {"High Press","HiPr",SVT_HI_PRESS_LIMIT},
    { L_WORD313, L_WORD343, SVT_LO_PRESS_LIMIT },          // {"Low Press" ,"LoPr",SVT_LO_PRESS_LIMIT},
    { L_WORD1051, L_WORD1053, SVT_HI_PRESS_VAC_LIMIT },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1052, L_WORD1054, SVT_LO_PRESS_VAC_LIMIT },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1099, L_WORD1101, SVT_HI_IGP_LIMIT },               //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1100, L_WORD1102, SVT_LO_IGP_LIMIT },               //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1055, L_WORD1057, SVT_HI_VAP_RET_LIMIT   },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1056, L_WORD1058, SVT_LO_VAP_RET_LIMIT   },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},

    { L_WORD899, L_WORD901, SVT_XTRA_HI_PRESS_LIMIT1 },     // {"XHigh Press1","XHiPr1",SVT_XTRA_HI_PRESS_LIMIT1},
    { L_WORD900, L_WORD902, SVT_XTRA_LO_PRESS_LIMIT1 },     // {"XLow Press1" ,"XLoPr1",SVT_XTRA_LO_PRESS_LIMIT1},
    { L_WORD1018, L_WORD1020, SVT_XTRA_HI_PRESS_LIMIT2 },     // {"XHigh Press2","XHiPr2",SVT_XTRA_HI_PRESS_LIMIT1},
    { L_WORD1019, L_WORD1021, SVT_XTRA_LO_PRESS_LIMIT2 },     // {"XLow Press2" ,"XLoPr2",SVT_XTRA_LO_PRESS_LIMIT1},
    { L_WORD247, L_WORD344, SVT_LOADRATE },               // {"Loadrate"  ,"LRate",SVT_LOADRATE},
    { L_WORD314, L_WORD345, SVT_FINISH_TIME },             // {"FinishTime","FTim",SVT_FINISH_TIME},
    { L_WORD315, L_WORD346, SVT_REMAINING_TIME },          // {"RemTime"   ,"RTim",SVT_REMAINING_TIME},
    { L_WORD316, L_WORD347, SVT_CARGO_TYPE_NAME },         // {"CargoType" ,"Ctyp",SVT_CARGO_TYPE_NAME},
    { L_WORD744, L_WORD745, SVT_VOL_AT_REFTMP },            // {"Volume At reftermp","VRef",SVT_VOL_AT_REFTMP},
    { L_WORD848, L_WORD849, SVT_INTERFACE },                // {"Interface","Intrf",SVT_INTERFACE},
    { L_WORD856, L_WORD857, SVT_TANK_STATE_STR },          // {"Operation mode","Op Mode",SVT_TANK_STATE_STR},
    { L_WORD943, L_WORD945, SVT_VAP_WEIGHT },             // {"VapWeight"    ,"VapWgt" ,SVT_VAP_WEIGHT},
    { L_WORD944, L_WORD946, SVT_GAS_WEIGHT },             // {"GasWeight"    ,"GasW" ,SVT_GAS_WEIGHT},
    { L_WORD390, L_WORD237, SVT_AI_SERIAL_NUMBER },        // {"Serial number","",SVT_AI_SERIAL_NUMBER},
    { L_WORD317, L_WORD348, SVT_BP },                      // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD318, L_WORD349, SVT_MP },                      // {"Mid Press" ,"MP"  ,SVT_MP},
    { L_WORD319, L_WORD350, SVT_UP },                      // {"Upp Press" ,"UP"  ,SVT_UP},
    { L_WORD320, L_WORD351, SVT_TP },                      // {"Top Press" ,"TP"  ,SVT_TP},
    { L_WORD321, L_WORD352, SVT_BP_GAIN },                 // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD322, L_WORD353, SVT_MP_GAIN },                 // {"MP Gain"   ,"MPGn",SVT_MP_GAIN},
    { L_WORD323, L_WORD354, SVT_UP_GAIN },                 // {"UP Gain"   ,"UPGn",SVT_UP_GAIN},
    { L_WORD324, L_WORD355, SVT_TP_GAIN },                 // {"TP Gain"   ,"TPGn",SVT_TP_GAIN},
    { L_WORD325, L_WORD356, SVT_BP_OFFSET },               // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD326, L_WORD357, SVT_MP_OFFSET },               // {"MP Offset" ,"MPOf",SVT_MP_OFFSET},
    { L_WORD327, L_WORD358, SVT_UP_OFFSET },               // {"UP Offset" ,"UPOf",SVT_UP_OFFSET},
    { L_WORD328, L_WORD359, SVT_TP_OFFSET },               // {"TP Offset" ,"TPOf",SVT_TP_OFFSET},


    { L_WORD830, L_WORD830, SVT_T1 },                      // {"Bot Temp" ,"BT"  ,SVT_BT},
    { L_WORD1039, L_WORD1039, SVT_T2 },                      // {"Mid Temp" ,"MT"  ,SVT_MT},
    { L_WORD831, L_WORD831, SVT_T3 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD832, L_WORD832, SVT_T4 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD1040, L_WORD1040, SVT_T5 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD363, L_WORD367, SVT_TT },                      // {"Top Temp" ,"TT"  ,SVT_TT},
    { L_WORD822, L_WORD834, SVT_T1_GAIN },                 // {"BT Gain"   ,"BTGn",SVT_T1_GAIN},
    { L_WORD1035, L_WORD1041, SVT_T2_GAIN },                 // {"MT Gain"   ,"MTGn",SVT_T3_GAIN},
    { L_WORD823, L_WORD835, SVT_T3_GAIN },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD824, L_WORD835, SVT_T4_GAIN },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD1036, L_WORD1042, SVT_T5_GAIN },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD825, L_WORD837, SVT_TT_GAIN },                 // {"TT Gain"   ,"TTGn",SVT_TT_GAIN},
    { L_WORD826, L_WORD838, SVT_T1_OFFSET },               // {"BT Offset" ,"BTOf",SVT_T1_OFFSET},
    { L_WORD1037, L_WORD1043, SVT_T2_OFFSET },               // {"MT Offset" ,"MTOf",SVT_T3_OFFSET},
    { L_WORD827, L_WORD839, SVT_T3_OFFSET },               // {"UT Offset" ,"UTOf",SVT_T4_OFFSET},
    { L_WORD828, L_WORD840, SVT_T4_OFFSET },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD1038, L_WORD1044, SVT_T5_OFFSET },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD829, L_WORD841, SVT_TT_OFFSET },               // {"TT Offset" ,"TTOf",SVT_TT_OFFSET},
};

ValueList   PROTank::RedTankValueList[] = {
    { L_WORD304, L_WORD237, SVT_BLANK },                       // {"Unused"    ,"",SVT_BLANK},
    { L_WORD305, L_WORD329, SVT_LEVEL_SENSOR },                  // {"LevelSns"  ,"LevS" ,SVT_LEVEL},
    { L_WORD306, L_WORD330, SVT_LEVEL_REF },               // {"LevelRef"  ,"LevR",SVT_LEVEL_REF},
    { L_WORD307, L_WORD331, SVT_LEVEL_FC },                // {"LevelFC"   ,"LevF",SVT_LEVEL_FC},
    { L_WORD308, L_WORD332, SVT_SOUNDING },              // {"Sounding"  ,"Snd" ,SVT_SOUNDING},
    { L_WORD309, L_WORD333, SVT_ULLAGE },                // {"Ullage"    ,"Ull" ,SVT_ULLAGE},
    { L_WORD916, L_WORD917, SVT_ULLAGE_UTI },            // {"Ullage UTI" ,"UTI" ,SVT_ULLAGE},
    { L_WORD1064, L_WORD1065, SVT_ULLAGE_RADAR },                             // {"Ullage Radar" ,"URad",SVT_ULLAGE_RADAR},
    { L_WORD310, L_WORD335, SVT_VOLPERCENT },              // {"Volume%"   ,"Vol%",SVT_VOLPERCENT},
    { L_WORD44, L_WORD334, SVT_VOLUME },                // {"Volume"    ,"Vol" ,SVT_VOLUME},
    { L_WORD776, L_WORD777, SVT_CAPACITY },              // {"Capacity"    ,"Cap" ,SVT_CAPACITY},
    { L_WORD45, L_WORD336, SVT_WEIGHT },                // {"Weight"    ,"Wgt" ,SVT_WEIGHT},
    { L_WORD83, L_WORD337, SVT_DENSITY },                 // {"Density"   ,"Dens",SVT_DENSITY},
    { L_WORD338, L_WORD338, SVT_TEMP },                    // {"Temp"      ,"Temp",SVT_TEMP},
    { L_WORD1049, L_WORD1049, SVT_VAPOR_TEMP },             // {"VaporTemp"      ,"VaporTemp",SVT_TEMP},
    { L_WORD311, L_WORD339, SVT_PRESSURE },                // {"Pressure"  ,"Pres",SVT_PRESSURE},
    { L_WORD112, L_WORD340, SVT_HI_TEMP_LIMIT },           // {"High Temp" ,"HTmp",SVT_HI_TEMP_LIMIT},
    { L_WORD113, L_WORD341, SVT_LO_TEMP_LIMIT },           // {"Low Temp"  ,"LTmp",SVT_LO_TEMP_LIMIT},
    { L_WORD312, L_WORD342, SVT_HI_PRESS_LIMIT },          // {"High Press","HiPr",SVT_HI_PRESS_LIMIT},
    { L_WORD313, L_WORD343, SVT_LO_PRESS_LIMIT },          // {"Low Press" ,"LoPr",SVT_LO_PRESS_LIMIT},
    { L_WORD1051, L_WORD1053, SVT_HI_PRESS_VAC_LIMIT },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1052, L_WORD1054, SVT_LO_PRESS_VAC_LIMIT },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1099, L_WORD1101, SVT_HI_IGP_LIMIT },               //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1100, L_WORD1102, SVT_LO_IGP_LIMIT },               //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1055, L_WORD1057, SVT_HI_VAP_RET_LIMIT   },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1056, L_WORD1058, SVT_LO_VAP_RET_LIMIT   },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},

    { L_WORD899, L_WORD901, SVT_XTRA_HI_PRESS_LIMIT1 },     // {"XHigh Press","XHiPr",SVT_XTRA_HI_PRESS_LIMIT1},
    { L_WORD900, L_WORD902, SVT_XTRA_LO_PRESS_LIMIT1 },     // {"XLow Press" ,"XLoPr",SVT_XTRA_LO_PRESS_LIMIT1},
    { L_WORD247, L_WORD344, SVT_LOADRATE },               // {"Loadrate"  ,"LRate",SVT_LOADRATE},
    { L_WORD314, L_WORD345, SVT_FINISH_TIME },             // {"FinishTime","FTim",SVT_FINISH_TIME},
    { L_WORD315, L_WORD346, SVT_REMAINING_TIME },          // {"RemTime"   ,"RTim",SVT_REMAINING_TIME},
    { L_WORD316, L_WORD347, SVT_CARGO_TYPE_NAME },         // {"CargoType" ,"Ctyp",SVT_CARGO_TYPE_NAME},
    { L_WORD744, L_WORD745, SVT_VOL_AT_REFTMP },            // {"Volume At reftermp","VRef",SVT_VOL_AT_REFTMP},
    { L_WORD848, L_WORD849, SVT_INTERFACE },                // {"Interface","Intrf",SVT_INTERFACE},
    { L_WORD856, L_WORD857, SVT_TANK_STATE_STR },          // {"Operation mode","Op Mode",SVT_TANK_STATE_STR},
    { L_WORD943, L_WORD945, SVT_VAP_WEIGHT },             // {"GasWeight"    ,"GWgt" ,SVT_VAP_WEIGHT},
    { L_WORD944, L_WORD946, SVT_GAS_WEIGHT },             // {"LPGWeight"    ,"LPGW" ,SVT_GAS_WEIGHT},

    { L_WORD390, L_WORD237, SVT_AI_SERIAL_NUMBER },        // {"Serial number","",SVT_AI_SERIAL_NUMBER},
    { L_WORD754, L_WORD754, SVT_BP1 },                    // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD755, L_WORD755, SVT_BP2 },                    // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD756, L_WORD756, SVT_BP3 },                    // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD317, L_WORD348, SVT_BP },                      // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD318, L_WORD349, SVT_MP },                      // {"Mid Press" ,"MP"  ,SVT_MP},
    { L_WORD319, L_WORD350, SVT_UP },                      // {"Upp Press" ,"UP"  ,SVT_UP},
    { L_WORD320, L_WORD351, SVT_TP },                      // {"Top Press" ,"TP"  ,SVT_TP},
    { L_WORD757, L_WORD757, SVT_BP_GAIN1 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD758, L_WORD758, SVT_BP_GAIN2 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD759, L_WORD759, SVT_BP_GAIN3 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD321, L_WORD352, SVT_BP_GAIN },                 // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD322, L_WORD353, SVT_MP_GAIN },                 // {"MP Gain"   ,"MPGn",SVT_MP_GAIN},
    { L_WORD323, L_WORD354, SVT_UP_GAIN },                 // {"UP Gain"   ,"UPGn",SVT_UP_GAIN},
    { L_WORD324, L_WORD355, SVT_TP_GAIN },                 // {"TP Gain"   ,"TPGn",SVT_TP_GAIN},
    { L_WORD760, L_WORD760, SVT_BP_OFFSET1 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD761, L_WORD761, SVT_BP_OFFSET2 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD762, L_WORD762, SVT_BP_OFFSET3 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD325, L_WORD356, SVT_BP_OFFSET },               // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD326, L_WORD357, SVT_MP_OFFSET },               // {"MP Offset" ,"MPOf",SVT_MP_OFFSET},
    { L_WORD327, L_WORD358, SVT_UP_OFFSET },               // {"UP Offset" ,"UPOf",SVT_UP_OFFSET},
    { L_WORD328, L_WORD359, SVT_TP_OFFSET },               // {"TP Offset" ,"TPOf",SVT_TP_OFFSET},

    { L_WORD830, L_WORD830, SVT_T1 },                      // {"Bot Temp" ,"BT"  ,SVT_BT},
    { L_WORD1039, L_WORD1039, SVT_T2 },                      // {"Mid Temp" ,"MT"  ,SVT_MT},
    { L_WORD831, L_WORD831, SVT_T3 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD832, L_WORD832, SVT_T4 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD1040, L_WORD1040, SVT_T5 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD363, L_WORD367, SVT_TT },                      // {"Top Temp" ,"TT"  ,SVT_TT},
    { L_WORD822, L_WORD834, SVT_T1_GAIN },                 // {"BT Gain"   ,"BTGn",SVT_T1_GAIN},
    { L_WORD1035, L_WORD1041, SVT_T2_GAIN },                 // {"MT Gain"   ,"MTGn",SVT_T3_GAIN},
    { L_WORD823, L_WORD835, SVT_T3_GAIN },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD824, L_WORD835, SVT_T4_GAIN },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD1036, L_WORD1042, SVT_T5_GAIN },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD825, L_WORD837, SVT_TT_GAIN },                 // {"TT Gain"   ,"TTGn",SVT_TT_GAIN},
    { L_WORD826, L_WORD838, SVT_T1_OFFSET },               // {"BT Offset" ,"BTOf",SVT_T1_OFFSET},
    { L_WORD1037, L_WORD1043, SVT_T2_OFFSET },               // {"MT Offset" ,"MTOf",SVT_T3_OFFSET},
    { L_WORD827, L_WORD839, SVT_T3_OFFSET },               // {"UT Offset" ,"UTOf",SVT_T4_OFFSET},
    { L_WORD828, L_WORD840, SVT_T4_OFFSET },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD1038, L_WORD1044, SVT_T5_OFFSET },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD829, L_WORD841, SVT_TT_OFFSET },               // {"TT Offset" ,"TTOf",SVT_TT_OFFSET},

};

ValueList PROTank::AllTankValueList[] = {
    { L_WORD304, L_WORD237, SVT_BLANK },                       // {"Unused"    ,"",SVT_BLANK},
    { L_WORD305, L_WORD329, SVT_LEVEL_SENSOR },             // {"LevelSns"  ,"LevS" ,SVT_LEVEL_SENSOR},
    { L_WORD306, L_WORD330, SVT_LEVEL_REF },               // {"LevelRef"  ,"LevR",SVT_LEVEL_REF},
    { L_WORD307, L_WORD331, SVT_LEVEL_FC },                // {"LevelFC"   ,"LevF",SVT_LEVEL_FC},
    { L_WORD308, L_WORD332, SVT_SOUNDING },              // {"Sounding"  ,"Snd" ,SVT_SOUNDING},
    { L_WORD309, L_WORD333, SVT_ULLAGE },                // {"Ullage"    ,"Ull" ,SVT_ULLAGE},
    { L_WORD916, L_WORD917, SVT_ULLAGE_UTI },            // {"Ullage UTI" ,"UTI" ,SVT_ULLAGE},
    { L_WORD1069, L_WORD1070, SVT_ULLAGE_FC },            // {"Ullage FC" ,"UFC" ,SVT_ULLAGE},

    { L_WORD1064, L_WORD1065, SVT_ULLAGE_RADAR },                             // {"Ullage Radar" ,"URad",SVT_ULLAGE_RADAR},
    { L_WORD44, L_WORD334, SVT_VOLUME },                // {"Volume"    ,"Vol" ,SVT_VOLUME},
    { L_WORD310, L_WORD335, SVT_VOLPERCENT },                 // {"Volume%"   ,"Vol%",SVT_VOLPERCENT},
    //   {L_WORD776      ,L_WORD777 ,SVT_CAPACITY},             // {"Capacity"    ,"Cap" ,SVT_CAPACITY},
    { L_WORD744, L_WORD745, SVT_VOL_AT_REFTMP },            // {"Volume At reftermp","VRef",SVT_VOL_AT_REFTMP},
    { L_WORD885, L_WORD887, SVT_CAPACITY98 },            // {"Capacity98%"    ,"Cap" ,SVT_CAPACITY},
    { L_WORD886, L_WORD888, SVT_CAPACITY100 },           // {"Capacity100%"    ,"Cap" ,SVT_CAPACITY},
    { L_WORD45, L_WORD336, SVT_WEIGHT },                // {"Weight"    ,"Wgt" ,SVT_WEIGHT},
    { L_WORD83, L_WORD337, SVT_DENSITY },                 // {"Density"   ,"Dens",SVT_DENSITY},
    { L_WORD338, L_WORD338, SVT_TEMP },                    // {"Temp"      ,"Temp",SVT_TEMP},
    { L_WORD1049, L_WORD1049, SVT_VAPOR_TEMP },             // {"VaporTemp"      ,"VaporTemp",SVT_TEMP},
    { L_WORD311, L_WORD339, SVT_PRESSURE },                // {"Pressure"  ,"Pres",SVT_PRESSURE},
    { L_WORD247, L_WORD344, SVT_LOADRATE },               // {"Loadrate"  ,"LRate",SVT_LOADRATE},
    { L_WORD314, L_WORD345, SVT_FINISH_TIME },             // {"FinishTime","FTim",SVT_FINISH_TIME},
    { L_WORD315, L_WORD346, SVT_REMAINING_TIME },          // {"RemTime"   ,"RTim",SVT_REMAINING_TIME},
    { L_WORD848, L_WORD849, SVT_INTERFACE },                // {"Interface","Intrf",SVT_INTERFACE},
    { L_WORD856, L_WORD857, SVT_TANK_STATE_STR },          // {"Operation mode","Op Mode",SVT_TANK_STATE_STR},

    { L_WORD943, L_WORD945, SVT_VAP_WEIGHT },             // {"GasWeight"    ,"GWgt" ,SVT_VAP_WEIGHT},
    { L_WORD944, L_WORD946, SVT_GAS_WEIGHT },             // {"LPGWeight"    ,"LPGW" ,SVT_GAS_WEIGHT},

    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD807, L_WORD807, SVT_SUBMENU },
//    { L_WORD744, L_WORD745, SVT_VOL_AT_REFTMP },            // Moved to top level next to SVT_VOLUME {"Volume At reftermp","VRef",SVT_VOL_AT_REFTMP},
    // Cargo type
    { L_WORD316, L_WORD347, SVT_CARGO_TYPE_NAME },        // {"CargoType" ,"Ctyp",SVT_CARGO_TYPE_NAME},
    { L_WORD102, L_WORD237, SVT_API },                    // {"API"          ,"",SVT_API},
    { L_WORD394, L_WORD237, SVT_VCF },                    // {"VolCorrFactor","",SVT_VCF},
    { L_WORD395, L_WORD237, SVT_VCF_AT_TEMP },            // {"VCF@Temp"     ,"",SVT_VCF_AT_TEMP},
    { L_WORD396, L_WORD237, SVT_MEASURED_API },           // {"Measured API" ,"",SVT_MEASURED_API},
    { L_WORD397, L_WORD237, SVT_COMP_DNS },               // {"Comp. Density","",SVT_COMP_DNS},
    { L_WORD446, L_WORD237, SVT_MEAS_DNS },               // {"Meas. Density","",SVT_MEAS_DNS},
    { L_WORD1010, L_WORD237, SVT_MEAS_DNS_RAW },           // {"Meas. Dns(Raw)","",SVT_MEAS_DNS_RAW},
    { L_WORD864, L_WORD237, SVT_USE_MSRD_DNS },           // {"MsrdDnsStat","",SVT_USE_MSRD_DNS},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD398, L_WORD237, SVT_REF_DNS1 },               // {"Ref.Density1" ,"",SVT_REF_DNS1},
    { L_WORD399, L_WORD237, SVT_REF_DNS2 },               // {"Ref.Density2" ,"",SVT_REF_DNS2},
    { L_WORD400, L_WORD237, SVT_REF_TMP1 },               // {"Ref. Temp1"   ,"",SVT_REF_TMP1},
    { L_WORD401, L_WORD237, SVT_REF_TMP2 },               // {"Ref. Temp2"   ,"",SVT_REF_TMP2},
    { L_WORD108, L_WORD237, SVT_COEFF },                  // {"Coefficient"  ,"",SVT_COEFF},
    { L_WORD995, L_WORD237, SVT_MOLMASS },                // {"MolMass"      ,"",SVT_MOLMASS},
    { L_WORD1087, L_WORD237, SVT_VISCOSITY },               // {"Viscosity"    ,"",SVT_VISCOSITY},
    { L_WORD1096, L_WORD237, SVT_CARGO_COLOR },             //   {"Cargo color"  ,"",SVT_CARGO_COLOR},
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },

    { L_WORD810, L_WORD810, SVT_SUBMENU },
    { L_WORD587, L_WORD587, SVT_SUBMENU },
    { L_WORD317, L_WORD348, SVT_BP },                      // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD325, L_WORD356, SVT_BP_OFFSET },               // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD321, L_WORD352, SVT_BP_GAIN },                 // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD817, L_WORD817, SVT_BP_ENABLE_TEXT },
    { L_WORD1076, L_WORD237, SVT_BP_SERIAL_NO },             // {"Serial number","",SVT_BP_SERIAL_NO},

    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD985, L_WORD364, SVT_T1 },                      // {"Bot Temp" ,"BTP"  ,SVT_BT},
    { L_WORD822, L_WORD834, SVT_T1_GAIN },                 // {"BT Gain"   ,"BTGn",SVT_T1_GAIN},
    { L_WORD826, L_WORD838, SVT_T1_OFFSET },               // {"BT Offset" ,"BTOf",SVT_T1_OFFSET},
    { L_WORD842, L_WORD842, SVT_T1_ENABLE },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD882, L_WORD882, SVT_SUBMENU },
    { L_WORD754, L_WORD754, SVT_BP1 },                     // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD755, L_WORD755, SVT_BP2 },                     // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD756, L_WORD756, SVT_BP3 },                     // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD757, L_WORD757, SVT_BP_GAIN1 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD758, L_WORD758, SVT_BP_GAIN2 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD759, L_WORD759, SVT_BP_GAIN3 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD760, L_WORD760, SVT_BP_OFFSET1 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD761, L_WORD761, SVT_BP_OFFSET2 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD762, L_WORD762, SVT_BP_OFFSET3 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD814, L_WORD814, SVT_BP_ENABLE1_TEXT },
    { L_WORD815, L_WORD815, SVT_BP_ENABLE2_TEXT },
    { L_WORD816, L_WORD816, SVT_BP_ENABLE3_TEXT },
    { L_WORD1077, L_WORD237, SVT_BP_SERIAL_NO1 },             // {"Serial number","",SVT_BP_SERIAL_NO1},
    { L_WORD1078, L_WORD237, SVT_BP_SERIAL_NO2 },             // {"Serial number","",SVT_BP_SERIAL_NO2},
    { L_WORD1079, L_WORD237, SVT_BP_SERIAL_NO3 },             // {"Serial number","",SVT_BP_SERIAL_NO3},
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD1033, L_WORD1033, SVT_SUBMENU },               // Lower
    { L_WORD986, L_WORD1039, SVT_T2 },                      // {"Lower Temp" ,"LT"  ,SVT_LT},
    { L_WORD1035, L_WORD1041, SVT_T2_GAIN },                 // {"LT Gain"   ,"LTGn",SVT_T1_GAIN},
    { L_WORD1037, L_WORD1043, SVT_T2_OFFSET },               // {"LT Offset" ,"LTOf",SVT_T1_OFFSET},
    { L_WORD1045, L_WORD1045, SVT_T2_ENABLE },
    { L_WORD1033, L_WORD1033, SVT_SUBMENU_END },

    { L_WORD588, L_WORD588, SVT_SUBMENU },
    { L_WORD318, L_WORD349, SVT_MP },                      // {"Mid Press" ,"MP"  ,SVT_MP},
    { L_WORD326, L_WORD357, SVT_MP_OFFSET },               // {"MP Offset" ,"MPOf",SVT_MP_OFFSET},
    { L_WORD322, L_WORD353, SVT_MP_GAIN },                 // {"MP Gain"   ,"MPGn",SVT_MP_GAIN},
    { L_WORD818, L_WORD818, SVT_MP_ENABLE_TEXT },
    { L_WORD1080, L_WORD237, SVT_MP_SERIAL_NO },             // {"Serial number","",SVT_MP_SERIAL_NO},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD987, L_WORD365, SVT_T3 },                      // {"Mid Temp" ,"MT"  ,SVT_MT},
    { L_WORD823, L_WORD835, SVT_T3_GAIN },                 // {"MT Gain"   ,"MTGn",SVT_T3_GAIN},
    { L_WORD827, L_WORD839, SVT_T3_OFFSET },               // {"MT Offset" ,"MTOf",SVT_T3_OFFSET},
    { L_WORD843, L_WORD843, SVT_T3_ENABLE },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD589, L_WORD589, SVT_SUBMENU },
    { L_WORD319, L_WORD350, SVT_UP },                      // {"Upp Press" ,"UP"  ,SVT_UP},
    { L_WORD327, L_WORD358, SVT_UP_OFFSET },               // {"UP Offset" ,"UPOf",SVT_UP_OFFSET},
    { L_WORD323, L_WORD354, SVT_UP_GAIN },                 // {"UP Gain"   ,"UPGn",SVT_UP_GAIN},
    { L_WORD819, L_WORD819, SVT_UP_ENABLE_TEXT },
    { L_WORD1081, L_WORD237, SVT_UP_SERIAL_NO },             // {"Serial number","",SVT_UP_SERIAL_NO},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD988, L_WORD366, SVT_T4 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD824, L_WORD836, SVT_T4_GAIN },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD828, L_WORD840, SVT_T4_OFFSET },               // {"UT Offset" ,"UTOf",SVT_T4_OFFSET},
    { L_WORD844, L_WORD844, SVT_T4_ENABLE },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD1034, L_WORD1034, SVT_SUBMENU },               // Higher
    { L_WORD989, L_WORD1040, SVT_T5 },                      // {"Higher Temp" ,"HT"  ,SVT_BT},
    { L_WORD1036, L_WORD1042, SVT_T5_GAIN },                 // {"HT Gain"   ,"HTGn",SVT_T1_GAIN},
    { L_WORD1038, L_WORD1044, SVT_T5_OFFSET },               // {"HT Offset" ,"HTOf",SVT_T1_OFFSET},
    { L_WORD1046, L_WORD1046, SVT_T5_ENABLE },
    { L_WORD1034, L_WORD1034, SVT_SUBMENU_END },

    { L_WORD590, L_WORD590, SVT_SUBMENU },
    { L_WORD320, L_WORD351, SVT_TP },                      // {"Top Press" ,"TP"  ,SVT_TP},
    { L_WORD324, L_WORD355, SVT_TP_GAIN },                 // {"TP Gain"   ,"TPGn",SVT_TP_GAIN},
    { L_WORD328, L_WORD359, SVT_TP_OFFSET },               // {"TP Offset" ,"TPOf",SVT_TP_OFFSET},
    { L_WORD820, L_WORD820, SVT_TP_ENABLE_TEXT },
    { L_WORD1082, L_WORD237, SVT_TP_SERIAL_NO },             // {"Serial number","",SVT_TP_SERIAL_NO},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD363, L_WORD367, SVT_TT },                      // {"Top Temp" ,"TT"  ,SVT_TT},
    { L_WORD825, L_WORD837, SVT_TT_GAIN },                 // {"TT Gain"   ,"TTGn",SVT_TT_GAIN},
    { L_WORD829, L_WORD841, SVT_TT_OFFSET },               // {"TT Offset" ,"TTOf",SVT_TT_OFFSET},
    { L_WORD845, L_WORD845, SVT_TT_ENABLE },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },




    { L_WORD883, L_WORD884, SVT_RADAR_THRESHOLD },        // {"Radar Threshold" ,"RTrH",SVT_RADAR_THRESHOLD},
    { L_WORD918, L_WORD919, SVT_DISTANCE_SNS_UTI },       // {"DistSnsUTI" ,"DUTI",SVT_DISTANCE_SNS_UTI},
    { L_WORD1084, L_WORD1085, SVT_LEVEL_OFFSET     },       // {"Level offset" ,"LOff",SVT_LEVEL_OFFSET},


    { L_WORD813, L_WORD813, SVT_SUBMENU_END },

// Alarm limits
    { L_WORD808, L_WORD808, SVT_SUBMENU },
    { L_WORD778, L_WORD778, SVT_HIHI_VOLPCNT_LIM },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD779, L_WORD779, SVT_HI_LEVEL_LIM },
    { L_WORD780, L_WORD780, SVT_HI_VOLUME_LIM },
    { L_WORD781, L_WORD781, SVT_HI_VOLPCNT_LIM },
    { L_WORD782, L_WORD782, SVT_HI_WEIGHT_LIM },
    { L_WORD783, L_WORD783, SVT_HI_ULLAGE_LIM },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD784, L_WORD784, SVT_LO_LEVEL_LIM },
    { L_WORD785, L_WORD785, SVT_LO_VOLUME_LIM },
    { L_WORD786, L_WORD786, SVT_LO_VOLPCNT_LIM },
    { L_WORD787, L_WORD787, SVT_LO_WEIGHT_LIM },
    { L_WORD788, L_WORD788, SVT_LO_ULLAGE_LIM },
    { L_WORD1108, L_WORD1108, SVT_LOLO_LEVEL_LIM },
    { L_WORD1109, L_WORD1109, SVT_LOLO_VOLUME_LIM },
    { L_WORD1110, L_WORD1110, SVT_LOLO_VOLPCNT_LIM },
    { L_WORD1111, L_WORD1111, SVT_LOLO_WEIGHT_LIM },
    { L_WORD1112, L_WORD1112, SVT_LOLO_ULLAGE_LIM },

    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD789, L_WORD789, SVT_HI_TEMP_LIMIT },           // {"High Temp" ,"HTmp",SVT_HI_TEMP_LIMIT},
    { L_WORD790, L_WORD790, SVT_LO_TEMP_LIMIT },           // {"Low Temp"  ,"LTmp",SVT_LO_TEMP_LIMIT},
    { L_WORD1060, L_WORD1062, SVT_HI_BOT_TEMP_LIMIT },       // {"High Temp" ,"HTmp",SVT_HI_TEMP_LIMIT},
    { L_WORD1061, L_WORD1063, SVT_LO_BOT_TEMP_LIMIT },       // {"Low Temp"  ,"LTmp",SVT_LO_TEMP_LIMIT},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },

    { L_WORD911, L_WORD915, SVT_AL_LIMIT_TYPE_PRESS },     // {"Press Al State","PAlStat",SVT_HI_PRESS_LIMIT},
    { L_WORD791, L_WORD342, SVT_HI_PRESS_LIMIT },          // {"High Press","HiPr",SVT_HI_PRESS_LIMIT},
    { L_WORD792, L_WORD343, SVT_LO_PRESS_LIMIT },          // {"Low Press" ,"LoPr",SVT_LO_PRESS_LIMIT},
    { L_WORD1051, L_WORD1053, SVT_HI_PRESS_VAC_LIMIT },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1052, L_WORD1054, SVT_LO_PRESS_VAC_LIMIT },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1099, L_WORD1101, SVT_HI_IGP_LIMIT },               //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1100, L_WORD1102, SVT_LO_IGP_LIMIT },               //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1055, L_WORD1057, SVT_HI_VAP_RET_LIMIT   },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1056, L_WORD1058, SVT_LO_VAP_RET_LIMIT   },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD903, L_WORD901, SVT_XTRA_HI_PRESS_LIMIT1 },     // {"XHigh Press","XHiPr",SVT_XTRA_HI_PRESS_LIMIT1},
    { L_WORD904, L_WORD902, SVT_XTRA_LO_PRESS_LIMIT1 },     // {"XLow Press" ,"XLoPr",SVT_XTRA_LO_PRESS_LIMIT1},
    { L_WORD1018, L_WORD1020, SVT_XTRA_HI_PRESS_LIMIT2 },     // {"XHigh Press2","XHiPr2",SVT_XTRA_HI_PRESS_LIMIT1},
    { L_WORD1019, L_WORD1021, SVT_XTRA_LO_PRESS_LIMIT2 },     // {"XLow Press2" ,"XLoPr2",SVT_XTRA_LO_PRESS_LIMIT1},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD793, L_WORD793, SVT_DNS_DIFF_LIM },
    { L_WORD794, L_WORD794, SVT_LEV_CHANGE_LIM },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD795, L_WORD795, SVT_HI_LR_LIM },
    { L_WORD796, L_WORD796, SVT_LO_LR_LIM },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD962, L_WORD962, SVT_SUBMENU },
    { L_WORD956, L_WORD957, SVT_OFFSET_VOLUME },              // {"NetVolume"   ,"NVol" ,SVT_OFFSET_VOLUME        },
    { L_WORD958, L_WORD958, SVT_OFFSET_VOL_AT_REF_TMP },      // {"NVol@Ref"     ,"NVolR" ,SVT_OFFSET_VOL_AT_REF_TMP},
    { L_WORD960, L_WORD961, SVT_OFFSET_WEIGHT },              // {"NetWeight"    ,"NWgt" ,SVT_OFFSET_WEIGHT        },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD954, L_WORD955, SVT_VOLUME_OFFSET },              // {"Vol.Offset"   ,"VOff" ,SVT_VOLUME_OFFSET},
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD1032, L_WORD1032, SVT_SUBMENU },
    { L_WORD1026, L_WORD1026, SVT_CUSTODY_TRF_LEVEL1 },         // {"Level1"  ,"Level1"   ,SVT_CUSTODY_TRF_LEVEL1},
    { L_WORD1027, L_WORD1027, SVT_CUSTODY_TRF_LEVEL2 },         // {"Level2"  ,"Level2"   ,SVT_CUSTODY_TRF_LEVEL1},
    { L_WORD1028, L_WORD1028, SVT_CUSTODY_TRF_LEVEL3 },         // {"Level3"  ,"Level3"   ,SVT_CUSTODY_TRF_LEVEL1},
    { L_WORD1029, L_WORD1029, SVT_CUSTODY_TRF_LEVEL4 },         // {"Level4"  ,"Level4"   ,SVT_CUSTODY_TRF_LEVEL1},
    { L_WORD1030, L_WORD1030, SVT_CUSTODY_TRF_LEVEL5 },         // {"Level5"  ,"Level5"   ,SVT_CUSTODY_TRF_LEVEL1},
    { L_WORD1031, L_WORD1031, SVT_CUSTODY_TRF_AVG_LEVEL },      // {"AvgLevel","AvgLevel" ,SVT_CUSTODY_TRF_AVG_LEVEL},
    { L_WORD1047, L_WORD1047, SVT_CUSTODY_TRF_TRIM_CORR },      // {"TrimCorr","TrimCorr" ,SVT_CUSTODY_TRF_TRIM_CORR},
    { L_WORD1048, L_WORD1048, SVT_CUSTODY_TRF_LIST_CORR },      // {"ListCorr","ListCorr" ,SVT_CUSTODY_TRF_LIST_CORR},
    { L_WORD1050, L_WORD1050, SVT_CUSTODY_TRF_CORR_LEVEL },      // {"ListCorr","ListCorr" ,SVT_CUSTODY_TRF_LIST_CORR},


    { L_WORD1032, L_WORD1032, SVT_SUBMENU_END },
};

ValueList PROTank::AllTankValueList2[] = {
    { L_WORD304, L_WORD237, SVT_BLANK },                       // {"Unused"    ,"",SVT_BLANK},
    { L_WORD305, L_WORD329, SVT_LEVEL_SENSOR },             // {"LevelSns"  ,"LevS" ,SVT_LEVEL_SENSOR},
    { L_WORD306, L_WORD330, SVT_LEVEL_REF },               // {"LevelRef"  ,"LevR",SVT_LEVEL_REF},
    { L_WORD307, L_WORD331, SVT_LEVEL_FC },                // {"LevelFC"   ,"LevF",SVT_LEVEL_FC},
    { L_WORD308, L_WORD332, SVT_SOUNDING },              // {"Sounding"  ,"Snd" ,SVT_SOUNDING},
    { L_WORD309, L_WORD333, SVT_ULLAGE },                // {"Ullage"    ,"Ull" ,SVT_ULLAGE},
    { L_WORD916, L_WORD917, SVT_ULLAGE_UTI },            // {"Ullage UTI" ,"UTI" ,SVT_ULLAGE},
    { L_WORD1069, L_WORD1070, SVT_ULLAGE_FC },            // {"Ullage FC" ,"UFC" ,SVT_ULLAGE},

    { L_WORD1064, L_WORD1065, SVT_ULLAGE_RADAR },                             // {"Ullage Radar" ,"URad",SVT_ULLAGE_RADAR},
    { L_WORD44, L_WORD334, SVT_VOLUME },                // {"Volume"    ,"Vol" ,SVT_VOLUME},
    { L_WORD310, L_WORD335, SVT_VOLPERCENT },                 // {"Volume%"   ,"Vol%",SVT_VOLPERCENT},
    //   {L_WORD776      ,L_WORD777 ,SVT_CAPACITY},             // {"Capacity"    ,"Cap" ,SVT_CAPACITY},
    { L_WORD744, L_WORD745, SVT_VOL_AT_REFTMP },            // {"Volume At reftermp","VRef",SVT_VOL_AT_REFTMP},
    { L_WORD885, L_WORD887, SVT_CAPACITY98 },            // {"Capacity98%"    ,"Cap" ,SVT_CAPACITY},
    { L_WORD886, L_WORD888, SVT_CAPACITY100 },           // {"Capacity100%"    ,"Cap" ,SVT_CAPACITY},
    { L_WORD45, L_WORD336, SVT_WEIGHT },                // {"Weight"    ,"Wgt" ,SVT_WEIGHT},
    { L_WORD83, L_WORD337, SVT_DENSITY },                 // {"Density"   ,"Dens",SVT_DENSITY},
    { L_WORD338, L_WORD338, SVT_TEMP },                    // {"Temp"      ,"Temp",SVT_TEMP},
    { L_WORD1049, L_WORD1049, SVT_VAPOR_TEMP },             // {"VaporTemp"      ,"VaporTemp",SVT_TEMP},
    { L_WORD311, L_WORD339, SVT_PRESSURE },                // {"Pressure"  ,"Pres",SVT_PRESSURE},
    { L_WORD247, L_WORD344, SVT_LOADRATE },               // {"Loadrate"  ,"LRate",SVT_LOADRATE},
    { L_WORD314, L_WORD345, SVT_FINISH_TIME },             // {"FinishTime","FTim",SVT_FINISH_TIME},
    { L_WORD315, L_WORD346, SVT_REMAINING_TIME },          // {"RemTime"   ,"RTim",SVT_REMAINING_TIME},
    { L_WORD848, L_WORD849, SVT_INTERFACE },                // {"Interface","Intrf",SVT_INTERFACE},
    { L_WORD856, L_WORD857, SVT_TANK_STATE_STR },          // {"Operation mode","Op Mode",SVT_TANK_STATE_STR},

    { L_WORD943, L_WORD945, SVT_VAP_WEIGHT },             // {"GasWeight"    ,"GWgt" ,SVT_VAP_WEIGHT},
    { L_WORD944, L_WORD946, SVT_GAS_WEIGHT },             // {"LPGWeight"    ,"LPGW" ,SVT_GAS_WEIGHT},

    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD807, L_WORD807, SVT_SUBMENU },
//    { L_WORD744, L_WORD745, SVT_VOL_AT_REFTMP },            // Moved to top level next to SVT_VOLUME {"Volume At reftermp","VRef",SVT_VOL_AT_REFTMP},
    // Cargo type
    { L_WORD316, L_WORD347, SVT_CARGO_TYPE_NAME },         // {"CargoType" ,"Ctyp",SVT_CARGO_TYPE_NAME},
    { L_WORD102, L_WORD237, SVT_API },                     // {"API"          ,"",SVT_API},
    { L_WORD394, L_WORD237, SVT_VCF },                    // {"VolCorrFactor","",SVT_VCF},
    { L_WORD395, L_WORD237, SVT_VCF_AT_TEMP },            // {"VCF@Temp"     ,"",SVT_VCF_AT_TEMP},
    { L_WORD396, L_WORD237, SVT_MEASURED_API },           // {"Measured API" ,"",SVT_MEASURED_API},
    { L_WORD397, L_WORD237, SVT_COMP_DNS },               // {"Comp. Density","",SVT_COMP_DNS},
    { L_WORD446, L_WORD237, SVT_MEAS_DNS },               // {"Meas. Density","",SVT_MEAS_DNS},
    { L_WORD1010, L_WORD237, SVT_MEAS_DNS_RAW },           // {"Meas. Dns(Raw)","",SVT_MEAS_DNS_RAW},
    { L_WORD864, L_WORD237, SVT_USE_MSRD_DNS },           // {"MsrdDnsStat","",SVT_USE_MSRD_DNS},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD398, L_WORD237, SVT_REF_DNS1 },               // {"Ref.Density1" ,"",SVT_REF_DNS1},
    { L_WORD399, L_WORD237, SVT_REF_DNS2 },               // {"Ref.Density2" ,"",SVT_REF_DNS2},
    { L_WORD400, L_WORD237, SVT_REF_TMP1 },               // {"Ref. Temp1"   ,"",SVT_REF_TMP1},
    { L_WORD401, L_WORD237, SVT_REF_TMP2 },               // {"Ref. Temp2"   ,"",SVT_REF_TMP2},
    { L_WORD108, L_WORD237, SVT_COEFF },                  // {"Coefficient"  ,"",SVT_COEFF},
    { L_WORD995, L_WORD237, SVT_MOLMASS },                // {"MolMass"      ,"",SVT_MOLMASS},
    { L_WORD1087, L_WORD237, SVT_VISCOSITY },               // {"Viscosity"    ,"",SVT_VISCOSITY},
    { L_WORD1096, L_WORD237, SVT_CARGO_COLOR },             //   {"Cargo color"  ,"",SVT_CARGO_COLOR},
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },

    { L_WORD810, L_WORD810, SVT_SUBMENU },
    { L_WORD587, L_WORD587, SVT_SUBMENU },
    { L_WORD317, L_WORD348, SVT_BP },                      // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD325, L_WORD356, SVT_BP_OFFSET },               // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD321, L_WORD352, SVT_BP_GAIN },                 // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD817, L_WORD817, SVT_BP_ENABLE_TEXT },
    { L_WORD1076, L_WORD237, SVT_BP_SERIAL_NO },             // {"Serial number","",SVT_BP_SERIAL_NO},

    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD360, L_WORD364, SVT_T1 },                      // {"Bot Temp" ,"BTP"  ,SVT_BT},
    { L_WORD822, L_WORD834, SVT_T1_GAIN },                 // {"BT Gain"   ,"BTGn",SVT_T1_GAIN},
    { L_WORD826, L_WORD838, SVT_T1_OFFSET },               // {"BT Offset" ,"BTOf",SVT_T1_OFFSET},
    { L_WORD842, L_WORD842, SVT_T1_ENABLE },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD882, L_WORD882, SVT_SUBMENU },
    { L_WORD754, L_WORD754, SVT_BP1 },                     // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD755, L_WORD755, SVT_BP2 },                     // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD756, L_WORD756, SVT_BP3 },                     // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD757, L_WORD757, SVT_BP_GAIN1 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD758, L_WORD758, SVT_BP_GAIN2 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD759, L_WORD759, SVT_BP_GAIN3 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD760, L_WORD760, SVT_BP_OFFSET1 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD761, L_WORD761, SVT_BP_OFFSET2 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD762, L_WORD762, SVT_BP_OFFSET3 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD814, L_WORD814, SVT_BP_ENABLE1_TEXT },
    { L_WORD815, L_WORD815, SVT_BP_ENABLE2_TEXT },
    { L_WORD816, L_WORD816, SVT_BP_ENABLE3_TEXT },
    { L_WORD1077, L_WORD237, SVT_BP_SERIAL_NO1 },             // {"Serial number","",SVT_BP_SERIAL_NO1},
    { L_WORD1078, L_WORD237, SVT_BP_SERIAL_NO2 },             // {"Serial number","",SVT_BP_SERIAL_NO2},
    { L_WORD1079, L_WORD237, SVT_BP_SERIAL_NO3 },             // {"Serial number","",SVT_BP_SERIAL_NO3},
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD1033, L_WORD1033, SVT_SUBMENU },               // Lower
    { L_WORD361, L_WORD1039, SVT_T2 },                      // {"Lower Temp" ,"LT"  ,SVT_LT},
    { L_WORD1035, L_WORD1041, SVT_T2_GAIN },                 // {"LT Gain"   ,"LTGn",SVT_T1_GAIN},
    { L_WORD1037, L_WORD1043, SVT_T2_OFFSET },               // {"LT Offset" ,"LTOf",SVT_T1_OFFSET},
    { L_WORD1045, L_WORD1045, SVT_T2_ENABLE },
    { L_WORD1033, L_WORD1033, SVT_SUBMENU_END },

    { L_WORD588, L_WORD588, SVT_SUBMENU },
    { L_WORD318, L_WORD349, SVT_MP },                      // {"Mid Press" ,"MP"  ,SVT_MP},
    { L_WORD326, L_WORD357, SVT_MP_OFFSET },               // {"MP Offset" ,"MPOf",SVT_MP_OFFSET},
    { L_WORD322, L_WORD353, SVT_MP_GAIN },                 // {"MP Gain"   ,"MPGn",SVT_MP_GAIN},
    { L_WORD818, L_WORD818, SVT_MP_ENABLE_TEXT },
    { L_WORD1080, L_WORD237, SVT_MP_SERIAL_NO },             // {"Serial number","",SVT_MP_SERIAL_NO},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD362, L_WORD365, SVT_T3 },                      // {"Mid Temp" ,"MT"  ,SVT_MT},
    { L_WORD823, L_WORD835, SVT_T3_GAIN },                 // {"MT Gain"   ,"MTGn",SVT_T3_GAIN},
    { L_WORD827, L_WORD839, SVT_T3_OFFSET },               // {"MT Offset" ,"MTOf",SVT_T3_OFFSET},
    { L_WORD843, L_WORD843, SVT_T3_ENABLE },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD589, L_WORD589, SVT_SUBMENU },
    { L_WORD319, L_WORD350, SVT_UP },                      // {"Upp Press" ,"UP"  ,SVT_UP},
    { L_WORD327, L_WORD358, SVT_UP_OFFSET },               // {"UP Offset" ,"UPOf",SVT_UP_OFFSET},
    { L_WORD323, L_WORD354, SVT_UP_GAIN },                 // {"UP Gain"   ,"UPGn",SVT_UP_GAIN},
    { L_WORD819, L_WORD819, SVT_UP_ENABLE_TEXT },
    { L_WORD1081, L_WORD237, SVT_UP_SERIAL_NO },             // {"Serial number","",SVT_UP_SERIAL_NO},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD988, L_WORD366, SVT_T4 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD824, L_WORD836, SVT_T4_GAIN },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD828, L_WORD840, SVT_T4_OFFSET },               // {"UT Offset" ,"UTOf",SVT_T4_OFFSET},
    { L_WORD844, L_WORD844, SVT_T4_ENABLE },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD1034, L_WORD1034, SVT_SUBMENU },               // Higher
    { L_WORD989, L_WORD1040, SVT_T5 },                      // {"Higher Temp" ,"HT"  ,SVT_BT},
    { L_WORD1036, L_WORD1042, SVT_T5_GAIN },                 // {"HT Gain"   ,"HTGn",SVT_T1_GAIN},
    { L_WORD1038, L_WORD1044, SVT_T5_OFFSET },               // {"HT Offset" ,"HTOf",SVT_T1_OFFSET},
    { L_WORD1046, L_WORD1046, SVT_T5_ENABLE },
    { L_WORD1034, L_WORD1034, SVT_SUBMENU_END },

    { L_WORD590, L_WORD590, SVT_SUBMENU },
    { L_WORD320, L_WORD351, SVT_TP },                      // {"Top Press" ,"TP"  ,SVT_TP},
    { L_WORD324, L_WORD355, SVT_TP_GAIN },                 // {"TP Gain"   ,"TPGn",SVT_TP_GAIN},
    { L_WORD328, L_WORD359, SVT_TP_OFFSET },               // {"TP Offset" ,"TPOf",SVT_TP_OFFSET},
    { L_WORD820, L_WORD820, SVT_TP_ENABLE_TEXT },
    { L_WORD1082, L_WORD237, SVT_TP_SERIAL_NO },             // {"Serial number","",SVT_TP_SERIAL_NO},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD363, L_WORD367, SVT_TT },                      // {"Top Temp" ,"TT"  ,SVT_TT},
    { L_WORD825, L_WORD837, SVT_TT_GAIN },                 // {"TT Gain"   ,"TTGn",SVT_TT_GAIN},
    { L_WORD829, L_WORD841, SVT_TT_OFFSET },               // {"TT Offset" ,"TTOf",SVT_TT_OFFSET},
    { L_WORD845, L_WORD845, SVT_TT_ENABLE },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },

    { L_WORD52 , L_WORD52 , SVT_SUBMENU },
    { L_WORD883, L_WORD884, SVT_RADAR_THRESHOLD },        // {"Radar Threshold" ,"RTrH",SVT_RADAR_THRESHOLD},
    { L_WORD918, L_WORD919, SVT_DISTANCE_SNS_UTI },       // {"DistSnsUTI" ,"DUTI",SVT_DISTANCE_SNS_UTI},
    { L_WORD1084, L_WORD1085, SVT_LEVEL_OFFSET     },       // {"Level offset" ,"LOff",SVT_LEVEL_OFFSET},
    { L_WORD1122, L_WORD1123, SVT_PRO_SORTNO     },       // {"Tank num" ,"TNum",SVT_PRO_SORTNO},
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },

// Alarm limits
    { L_WORD808, L_WORD808, SVT_SUBMENU },
    { L_WORD778, L_WORD778, SVT_HIHI_VOLPCNT_LIM },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD779, L_WORD779, SVT_HI_LEVEL_LIM },
    { L_WORD780, L_WORD780, SVT_HI_VOLUME_LIM },
    { L_WORD781, L_WORD781, SVT_HI_VOLPCNT_LIM },
    { L_WORD782, L_WORD782, SVT_HI_WEIGHT_LIM },
    { L_WORD783, L_WORD783, SVT_HI_ULLAGE_LIM },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD784, L_WORD784, SVT_LO_LEVEL_LIM },
    { L_WORD785, L_WORD785, SVT_LO_VOLUME_LIM },
    { L_WORD786, L_WORD786, SVT_LO_VOLPCNT_LIM },
    { L_WORD787, L_WORD787, SVT_LO_WEIGHT_LIM },
    { L_WORD788, L_WORD788, SVT_LO_ULLAGE_LIM },
    { L_WORD1108, L_WORD1108, SVT_LOLO_LEVEL_LIM },
    { L_WORD1109, L_WORD1109, SVT_LOLO_VOLUME_LIM },
    { L_WORD1110, L_WORD1110, SVT_LOLO_VOLPCNT_LIM },
    { L_WORD1111, L_WORD1111, SVT_LOLO_WEIGHT_LIM },
    { L_WORD1112, L_WORD1112, SVT_LOLO_ULLAGE_LIM },

    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD789, L_WORD789, SVT_HI_TEMP_LIMIT },           // {"High Temp" ,"HTmp",SVT_HI_TEMP_LIMIT},
    { L_WORD790, L_WORD790, SVT_LO_TEMP_LIMIT },           // {"Low Temp"  ,"LTmp",SVT_LO_TEMP_LIMIT},
    { L_WORD1060, L_WORD1062, SVT_HI_BOT_TEMP_LIMIT },       // {"High Temp" ,"HTmp",SVT_HI_TEMP_LIMIT},
    { L_WORD1061, L_WORD1063, SVT_LO_BOT_TEMP_LIMIT },       // {"Low Temp"  ,"LTmp",SVT_LO_TEMP_LIMIT},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },

    { L_WORD911, L_WORD915, SVT_AL_LIMIT_TYPE_PRESS },     // {"Press Al State","PAlStat",SVT_HI_PRESS_LIMIT},
    { L_WORD791, L_WORD342, SVT_HI_PRESS_LIMIT },          // {"High Press","HiPr",SVT_HI_PRESS_LIMIT},
    { L_WORD792, L_WORD343, SVT_LO_PRESS_LIMIT },          // {"Low Press" ,"LoPr",SVT_LO_PRESS_LIMIT},
    { L_WORD1051, L_WORD1053, SVT_HI_PRESS_VAC_LIMIT },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1052, L_WORD1054, SVT_LO_PRESS_VAC_LIMIT },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1099, L_WORD1101, SVT_HI_IGP_LIMIT },               //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1100, L_WORD1102, SVT_LO_IGP_LIMIT },               //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1055, L_WORD1057, SVT_HI_VAP_RET_LIMIT   },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1056, L_WORD1058, SVT_LO_VAP_RET_LIMIT   },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD903, L_WORD901, SVT_XTRA_HI_PRESS_LIMIT1 },     // {"XHigh Press","XHiPr",SVT_XTRA_HI_PRESS_LIMIT1},
    { L_WORD904, L_WORD902, SVT_XTRA_LO_PRESS_LIMIT1 },     // {"XLow Press" ,"XLoPr",SVT_XTRA_LO_PRESS_LIMIT1},
    { L_WORD1018, L_WORD1020, SVT_XTRA_HI_PRESS_LIMIT2 },     // {"XHigh Press2","XHiPr2",SVT_XTRA_HI_PRESS_LIMIT1},
    { L_WORD1019, L_WORD1021, SVT_XTRA_LO_PRESS_LIMIT2 },     // {"XLow Press2" ,"XLoPr2",SVT_XTRA_LO_PRESS_LIMIT1},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD793, L_WORD793, SVT_DNS_DIFF_LIM },
    { L_WORD794, L_WORD794, SVT_LEV_CHANGE_LIM },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD795, L_WORD795, SVT_HI_LR_LIM },
    { L_WORD796, L_WORD796, SVT_LO_LR_LIM },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD962, L_WORD962, SVT_SUBMENU },
    { L_WORD956, L_WORD957, SVT_OFFSET_VOLUME },              // {"NetVolume"   ,"NVol" ,SVT_OFFSET_VOLUME        },
    { L_WORD958, L_WORD958, SVT_OFFSET_VOL_AT_REF_TMP },      // {"NVol@Ref"     ,"NVolR" ,SVT_OFFSET_VOL_AT_REF_TMP},
    { L_WORD960, L_WORD961, SVT_OFFSET_WEIGHT },              // {"NetWeight"    ,"NWgt" ,SVT_OFFSET_WEIGHT        },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD954, L_WORD955, SVT_VOLUME_OFFSET },              // {"Vol.Offset"   ,"VOff" ,SVT_VOLUME_OFFSET},
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD1032, L_WORD1032, SVT_SUBMENU },
    { L_WORD1026, L_WORD1026, SVT_CUSTODY_TRF_LEVEL1 },         // {"Level1"  ,"Level1"   ,SVT_CUSTODY_TRF_LEVEL1},
    { L_WORD1027, L_WORD1027, SVT_CUSTODY_TRF_LEVEL2 },         // {"Level2"  ,"Level2"   ,SVT_CUSTODY_TRF_LEVEL1},
    { L_WORD1028, L_WORD1028, SVT_CUSTODY_TRF_LEVEL3 },         // {"Level3"  ,"Level3"   ,SVT_CUSTODY_TRF_LEVEL1},
    { L_WORD1029, L_WORD1029, SVT_CUSTODY_TRF_LEVEL4 },         // {"Level4"  ,"Level4"   ,SVT_CUSTODY_TRF_LEVEL1},
    { L_WORD1030, L_WORD1030, SVT_CUSTODY_TRF_LEVEL5 },         // {"Level5"  ,"Level5"   ,SVT_CUSTODY_TRF_LEVEL1},
    { L_WORD1031, L_WORD1031, SVT_CUSTODY_TRF_AVG_LEVEL },      // {"AvgLevel","AvgLevel" ,SVT_CUSTODY_TRF_AVG_LEVEL},
    { L_WORD1047, L_WORD1047, SVT_CUSTODY_TRF_TRIM_CORR },      // {"TrimCorr","TrimCorr" ,SVT_CUSTODY_TRF_TRIM_CORR},
    { L_WORD1048, L_WORD1048, SVT_CUSTODY_TRF_LIST_CORR },      // {"ListCorr","ListCorr" ,SVT_CUSTODY_TRF_LIST_CORR},
    { L_WORD1050, L_WORD1050, SVT_CUSTODY_TRF_CORR_LEVEL },      // {"ListCorr","ListCorr" ,SVT_CUSTODY_TRF_LIST_CORR},


    { L_WORD1032, L_WORD1032, SVT_SUBMENU_END },
};


ValueList PROTank::TankAlarmValueList[] = {
    { L_WORD304, L_WORD237, SVT_BLANK },                       // {"Unused"    ,"",SVT_BLANK},

    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD778, L_WORD778, SVT_HIHI_VOLPCNT_LIM },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD779, L_WORD779, SVT_HI_LEVEL_LIM },
    { L_WORD780, L_WORD780, SVT_HI_VOLUME_LIM },
    { L_WORD781, L_WORD781, SVT_HI_VOLPCNT_LIM },
    { L_WORD782, L_WORD782, SVT_HI_WEIGHT_LIM },
    { L_WORD783, L_WORD783, SVT_HI_ULLAGE_LIM },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD784, L_WORD784, SVT_LO_LEVEL_LIM },
    { L_WORD785, L_WORD785, SVT_LO_VOLUME_LIM },
    { L_WORD786, L_WORD786, SVT_LO_VOLPCNT_LIM },
    { L_WORD787, L_WORD787, SVT_LO_WEIGHT_LIM },
    { L_WORD788, L_WORD788, SVT_LO_ULLAGE_LIM },
    { L_WORD1108, L_WORD1108, SVT_LOLO_LEVEL_LIM },
    { L_WORD1109, L_WORD1109, SVT_LOLO_VOLUME_LIM },
    { L_WORD1110, L_WORD1110, SVT_LOLO_VOLPCNT_LIM },
    { L_WORD1111, L_WORD1111, SVT_LOLO_WEIGHT_LIM },
    { L_WORD1112, L_WORD1112, SVT_LOLO_ULLAGE_LIM },

    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD789, L_WORD789, SVT_HI_TEMP_LIMIT },           // {"High Temp" ,"HTmp",SVT_HI_TEMP_LIMIT},
    { L_WORD790, L_WORD790, SVT_LO_TEMP_LIMIT },           // {"Low Temp"  ,"LTmp",SVT_LO_TEMP_LIMIT},
    { L_WORD1060, L_WORD1062, SVT_HI_BOT_TEMP_LIMIT },       // {"High Temp" ,"HTmp",SVT_HI_TEMP_LIMIT},
    { L_WORD1061, L_WORD1063, SVT_LO_BOT_TEMP_LIMIT },       // {"Low Temp"  ,"LTmp",SVT_LO_TEMP_LIMIT},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },

    { L_WORD911, L_WORD915, SVT_AL_LIMIT_TYPE_PRESS },     // {"Press Al State","PAlStat",SVT_HI_PRESS_LIMIT},
    { L_WORD791, L_WORD342, SVT_HI_PRESS_LIMIT },          // {"High Press","HiPr",SVT_HI_PRESS_LIMIT},
    { L_WORD792, L_WORD343, SVT_LO_PRESS_LIMIT },          // {"Low Press" ,"LoPr",SVT_LO_PRESS_LIMIT},
    { L_WORD1051, L_WORD1053, SVT_HI_PRESS_VAC_LIMIT },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1052, L_WORD1054, SVT_LO_PRESS_VAC_LIMIT },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1099, L_WORD1101, SVT_HI_IGP_LIMIT },               //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1100, L_WORD1102, SVT_LO_IGP_LIMIT },               //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1055, L_WORD1057, SVT_HI_VAP_RET_LIMIT   },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1056, L_WORD1058, SVT_LO_VAP_RET_LIMIT   },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD903, L_WORD901, SVT_XTRA_HI_PRESS_LIMIT1 },     // {"XHigh Press1","XHiPr1",SVT_XTRA_HI_PRESS_LIMIT1},
    { L_WORD904, L_WORD902, SVT_XTRA_LO_PRESS_LIMIT1 },     // {"XLow Press1" ,"XLoPr1",SVT_XTRA_LO_PRESS_LIMIT1},
    { L_WORD1018, L_WORD1020, SVT_XTRA_HI_PRESS_LIMIT2 },     // {"XHigh Press2","XHiPr2",SVT_XTRA_HI_PRESS_LIMIT1},
    { L_WORD1019, L_WORD1021, SVT_XTRA_LO_PRESS_LIMIT2 },     // {"XLow Press2" ,"XLoPr2",SVT_XTRA_LO_PRESS_LIMIT1},

    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD793, L_WORD793, SVT_DNS_DIFF_LIM },
    { L_WORD794, L_WORD794, SVT_LEV_CHANGE_LIM },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD795, L_WORD795, SVT_HI_LR_LIM },
    { L_WORD796, L_WORD796, SVT_LO_LR_LIM                                        },
};



ValueList PROTank::TankCargoValueList[] = {
    // Cargo type
    { L_WORD304, L_WORD237, SVT_BLANK },                  // {"Unused"    ,"",SVT_BLANK},
    { L_WORD316, L_WORD347, SVT_CARGO_TYPE_NAME },        // {"CargoType" ,"Ctyp",SVT_CARGO_TYPE_NAME},
    { L_WORD102, L_WORD237, SVT_API },                    // {"API"          ,"",SVT_API},
    { L_WORD394, L_WORD237, SVT_VCF },                    // {"VolCorrFactor","",SVT_VCF},
    { L_WORD395, L_WORD237, SVT_VCF_AT_TEMP },            // {"VCF@Temp"     ,"",SVT_VCF_AT_TEMP},
    { L_WORD744, L_WORD745, SVT_VOL_AT_REFTMP },          // Moved to top level next to SVT_VOLUME {"Volume At reftermp","VRef",SVT_VOL_AT_REFTMP},
    { L_WORD396, L_WORD237, SVT_MEASURED_API },           // {"Measured API" ,"",SVT_MEASURED_API},
    { L_WORD397, L_WORD237, SVT_COMP_DNS },               // {"Comp. Density","",SVT_COMP_DNS},
    { L_WORD446, L_WORD237, SVT_MEAS_DNS },               // {"Meas. Density","",SVT_MEAS_DNS},
    { L_WORD1010, L_WORD237, SVT_MEAS_DNS_RAW },           // {"Meas. Dns(Raw)","",SVT_MEAS_DNS_RAW},
    { L_WORD864, L_WORD237, SVT_USE_MSRD_DNS },           // {"MsrdDnsStat","",SVT_USE_MSRD_DNS},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD398, L_WORD237, SVT_REF_DNS1 },               // {"Ref.Density1" ,"",SVT_REF_DNS1},
    { L_WORD399, L_WORD237, SVT_REF_DNS2 },               // {"Ref.Density2" ,"",SVT_REF_DNS2},
    { L_WORD400, L_WORD237, SVT_REF_TMP1 },               // {"Ref. Temp1"   ,"",SVT_REF_TMP1},
    { L_WORD401, L_WORD237, SVT_REF_TMP2 },               // {"Ref. Temp2"   ,"",SVT_REF_TMP2},
    { L_WORD108, L_WORD237, SVT_COEFF },                  // {"Coefficient"  ,"",SVT_COEFF},
    { L_WORD995, L_WORD237, SVT_MOLMASS },                // {"MolMass"      ,"",SVT_MOLMASS},
    { L_WORD1087, L_WORD237, SVT_VISCOSITY },               // {"Viscosity"    ,"",SVT_VISCOSITY},
    { L_WORD1096, L_WORD237, SVT_CARGO_COLOR },             //   {"Cargo color"  ,"",SVT_CARGO_COLOR},
};

ValueList PROTank::TankSensorValueList[] = {
    { L_WORD304, L_WORD237, SVT_BLANK },                       // {"Unused"    ,"",SVT_BLANK},
    { L_WORD587, L_WORD587, SVT_SUBMENU },
    { L_WORD317, L_WORD348, SVT_BP },                      // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD325, L_WORD356, SVT_BP_OFFSET },               // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD321, L_WORD352, SVT_BP_GAIN },                 // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD817, L_WORD817, SVT_BP_ENABLE_TEXT },
    { L_WORD1076, L_WORD237, SVT_BP_SERIAL_NO },             // {"Serial number","",SVT_BP_SERIAL_NO},

    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD360, L_WORD364, SVT_T1 },                      // {"Bot Temp" ,"BTP"  ,SVT_BT},
    { L_WORD822, L_WORD834, SVT_T1_GAIN },                 // {"BT Gain"   ,"BTGn",SVT_T1_GAIN},
    { L_WORD826, L_WORD838, SVT_T1_OFFSET },               // {"BT Offset" ,"BTOf",SVT_T1_OFFSET},
    { L_WORD842, L_WORD842, SVT_T1_ENABLE },
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD882, L_WORD882, SVT_SUBMENU },
    { L_WORD754, L_WORD754, SVT_BP1 },                     // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD755, L_WORD755, SVT_BP2 },                     // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD756, L_WORD756, SVT_BP3 },                     // {"Bot Press" ,"BP"  ,SVT_BP},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD757, L_WORD757, SVT_BP_GAIN1 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD758, L_WORD758, SVT_BP_GAIN2 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD759, L_WORD759, SVT_BP_GAIN3 },                // {"BP Gain"   ,"BPGn",SVT_BP_GAIN},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD760, L_WORD760, SVT_BP_OFFSET1 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD761, L_WORD761, SVT_BP_OFFSET2 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD762, L_WORD762, SVT_BP_OFFSET3 },              // {"BP Offset" ,"BPOf",SVT_BP_OFFSET},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD814, L_WORD814, SVT_BP_ENABLE1_TEXT },
    { L_WORD815, L_WORD815, SVT_BP_ENABLE2_TEXT },
    { L_WORD816, L_WORD816, SVT_BP_ENABLE3_TEXT },
    { L_WORD1077, L_WORD237, SVT_BP_SERIAL_NO1 },             // {"Serial number","",SVT_BP_SERIAL_NO1},
    { L_WORD1078, L_WORD237, SVT_BP_SERIAL_NO2 },             // {"Serial number","",SVT_BP_SERIAL_NO2},
    { L_WORD1079, L_WORD237, SVT_BP_SERIAL_NO3 },             // {"Serial number","",SVT_BP_SERIAL_NO3},
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD1033, L_WORD1033, SVT_SUBMENU },               // Lower
    { L_WORD361, L_WORD1039, SVT_T2 },                      // {"Lower Temp" ,"LT"  ,SVT_LT},
    { L_WORD1035, L_WORD1041, SVT_T2_GAIN },                 // {"LT Gain"   ,"LTGn",SVT_T1_GAIN},
    { L_WORD1037, L_WORD1043, SVT_T2_OFFSET },               // {"LT Offset" ,"LTOf",SVT_T1_OFFSET},
    { L_WORD1045, L_WORD1045, SVT_T2_ENABLE },
    { L_WORD1033, L_WORD1033, SVT_SUBMENU_END },

    { L_WORD588, L_WORD588, SVT_SUBMENU },
    { L_WORD318, L_WORD349, SVT_MP },                      // {"Mid Press" ,"MP"  ,SVT_MP},
    { L_WORD326, L_WORD357, SVT_MP_OFFSET },               // {"MP Offset" ,"MPOf",SVT_MP_OFFSET},
    { L_WORD322, L_WORD353, SVT_MP_GAIN },                 // {"MP Gain"   ,"MPGn",SVT_MP_GAIN},
    { L_WORD818, L_WORD818, SVT_MP_ENABLE_TEXT },
    { L_WORD1080, L_WORD237, SVT_MP_SERIAL_NO },             // {"Serial number","",SVT_MP_SERIAL_NO},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD362, L_WORD365, SVT_T3 },                      // {"Mid Temp" ,"MT"  ,SVT_MT},
    { L_WORD823, L_WORD835, SVT_T3_GAIN },                 // {"MT Gain"   ,"MTGn",SVT_T3_GAIN},
    { L_WORD827, L_WORD839, SVT_T3_OFFSET },               // {"MT Offset" ,"MTOf",SVT_T3_OFFSET},
    { L_WORD843, L_WORD843, SVT_T3_ENABLE },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD589, L_WORD589, SVT_SUBMENU },
    { L_WORD319, L_WORD350, SVT_UP },                      // {"Upp Press" ,"UP"  ,SVT_UP},
    { L_WORD327, L_WORD358, SVT_UP_OFFSET },               // {"UP Offset" ,"UPOf",SVT_UP_OFFSET},
    { L_WORD323, L_WORD354, SVT_UP_GAIN },                 // {"UP Gain"   ,"UPGn",SVT_UP_GAIN},
    { L_WORD819, L_WORD819, SVT_UP_ENABLE_TEXT },
    { L_WORD1081, L_WORD237, SVT_UP_SERIAL_NO },             // {"Serial number","",SVT_UP_SERIAL_NO},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD988, L_WORD366, SVT_T4 },                      // {"Upp Temp" ,"UT"  ,SVT_UT},
    { L_WORD824, L_WORD836, SVT_T4_GAIN },                 // {"UT Gain"   ,"UTGn",SVT_T4_GAIN},
    { L_WORD828, L_WORD840, SVT_T4_OFFSET },               // {"UT Offset" ,"UTOf",SVT_T4_OFFSET},
    { L_WORD844, L_WORD844, SVT_T4_ENABLE },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
    { L_WORD1034, L_WORD1034, SVT_SUBMENU },               // Higher
    { L_WORD989, L_WORD1040, SVT_T5 },                      // {"Higher Temp" ,"HT"  ,SVT_BT},
    { L_WORD1036, L_WORD1042, SVT_T5_GAIN },                 // {"HT Gain"   ,"HTGn",SVT_T1_GAIN},
    { L_WORD1038, L_WORD1044, SVT_T5_OFFSET },               // {"HT Offset" ,"HTOf",SVT_T1_OFFSET},
    { L_WORD1046, L_WORD1046, SVT_T5_ENABLE },
    { L_WORD1034, L_WORD1034, SVT_SUBMENU_END },

    { L_WORD590, L_WORD590, SVT_SUBMENU },
    { L_WORD320, L_WORD351, SVT_TP },                      // {"Top Press" ,"TP"  ,SVT_TP},
    { L_WORD324, L_WORD355, SVT_TP_GAIN },                 // {"TP Gain"   ,"TPGn",SVT_TP_GAIN},
    { L_WORD328, L_WORD359, SVT_TP_OFFSET },               // {"TP Offset" ,"TPOf",SVT_TP_OFFSET},
    { L_WORD820, L_WORD820, SVT_TP_ENABLE_TEXT },
    { L_WORD1082, L_WORD237, SVT_TP_SERIAL_NO },             // {"Serial number","",SVT_TP_SERIAL_NO},
    { L_WORD812, L_WORD812, SVT_SEPARATOR },
    { L_WORD363, L_WORD367, SVT_TT },                      // {"Top Temp" ,"TT"  ,SVT_TT},
    { L_WORD825, L_WORD837, SVT_TT_GAIN },                 // {"TT Gain"   ,"TTGn",SVT_TT_GAIN},
    { L_WORD829, L_WORD841, SVT_TT_OFFSET },               // {"TT Offset" ,"TTOf",SVT_TT_OFFSET},
    { L_WORD845, L_WORD845, SVT_TT_ENABLE },
    { L_WORD813, L_WORD813, SVT_SUBMENU_END },

    { L_WORD883, L_WORD884, SVT_RADAR_THRESHOLD },        // {"Radar Threshold" ,"RTrH",SVT_RADAR_THRESHOLD},
    { L_WORD918, L_WORD919, SVT_DISTANCE_SNS_UTI },       // {"DistSnsUTI" ,"DUTI",SVT_DISTANCE_SNS_UTI},
    { L_WORD1084, L_WORD1085, SVT_LEVEL_OFFSET     },       // {"Level offset" ,"LOff",SVT_LEVEL_OFFSET},


    { L_WORD813, L_WORD813, SVT_SUBMENU_END },
};


ValueList PROTank::ServiceReportTankValueList[] = {
    { L_WORD304, L_WORD237, SVT_BLANK },                     // {"Unused"    ,"",SVT_BLANK},
    { L_WORD677, L_WORD445, SVT_LEVEL_REF },                 // {"Level"     ,"Lev" ,SVT_LEVEL_REF},
    { L_WORD308, L_WORD332, SVT_SOUNDING },                  // {"Sounding"  ,"Snd" ,SVT_SOUNDING},
    { L_WORD309, L_WORD333, SVT_ULLAGE },                    // {"Ullage"    ,"Ull" ,SVT_ULLAGE},
    { L_WORD916, L_WORD917, SVT_ULLAGE_UTI },                // {"Ullage UTI" ,"UTI" ,SVT_ULLAGE},
    { L_WORD1064, L_WORD1065, SVT_ULLAGE_RADAR },                             // {"Ullage Radar" ,"URad",SVT_ULLAGE_RADAR},
    { L_WORD44, L_WORD334, SVT_VOLUME },                     // {"Volume"    ,"Vol" ,SVT_VOLUME},
    { L_WORD310, L_WORD335, SVT_VOLPERCENT },                // {"Volume%"   ,"Vol%",SVT_VOLPERCENT},
    { L_WORD776, L_WORD777, SVT_CAPACITY },                  // {"Capacity"  ,"Cap" ,SVT_CAPACITY},
    { L_WORD45, L_WORD336, SVT_WEIGHT },                     // {"Weight"    ,"Wgt" ,SVT_WEIGHT},
    { L_WORD83, L_WORD337, SVT_DENSITY },                    // {"Density"   ,"Dens",SVT_DENSITY},
    { L_WORD338, L_WORD338, SVT_TEMP },                      // {"Temp"      ,"Temp",SVT_TEMP},
    { L_WORD1049, L_WORD1049, SVT_VAPOR_TEMP },               // {"VaporTemp"      ,"VaporTemp",SVT_TEMP},
    { L_WORD311, L_WORD339, SVT_PRESSURE },                  // {"Pressure"  ,"Pres",SVT_PRESSURE},
    { L_WORD247, L_WORD344, SVT_LOADRATE },                  // {"Loadrate"  ,"LRate",SVT_LOADRATE},
    { L_WORD314, L_WORD345, SVT_FINISH_TIME },               // {"FinishTime","FTim",SVT_FINISH_TIME},
    { L_WORD315, L_WORD346, SVT_REMAINING_TIME },            // {"RemTime"   ,"RTim",SVT_REMAINING_TIME},
    { L_WORD316, L_WORD347, SVT_CARGO_TYPE_NAME },           // {"CargoType" ,"Ctyp",SVT_CARGO_TYPE_NAME},
    { L_WORD848, L_WORD849, SVT_INTERFACE },                 // {"Interface","Intrf",SVT_INTERFACE},
    { L_WORD102, L_WORD237, SVT_API },                       // {"API"          ,"",SVT_API},
    { L_WORD394, L_WORD237, SVT_VCF },                       // {"VolCorrFactor","",SVT_VCF},
    { L_WORD395, L_WORD237, SVT_VCF_AT_TEMP },               // {"VCF@Temp"     ,"",SVT_VCF_AT_TEMP},
    { L_WORD396, L_WORD237, SVT_MEASURED_API },              // {"Measured API" ,"",SVT_MEASURED_API},
    { L_WORD397, L_WORD237, SVT_COMP_DNS },                  // {"Comp. Density","",SVT_COMP_DNS},
    { L_WORD446, L_WORD237, SVT_MEAS_DNS },                  // {"Meas. Density","",SVT_MEAS_DNS},
    { L_WORD1010, L_WORD237, SVT_MEAS_DNS_RAW },             // {"Meas. Dns(Raw)","",SVT_MEAS_DNS_RAW},
    { L_WORD398, L_WORD237, SVT_REF_DNS1 },                  // {"Ref.Density1" ,"",SVT_REF_DNS1},
    { L_WORD399, L_WORD237, SVT_REF_DNS2 },                  // {"Ref.Density2" ,"",SVT_REF_DNS2},
    { L_WORD400, L_WORD237, SVT_REF_TMP1 },                  // {"Ref. Temp1"   ,"",SVT_REF_TMP1},
    { L_WORD401, L_WORD237, SVT_REF_TMP2 },                  // {"Ref. Temp2"   ,"",SVT_REF_TMP2},
    { L_WORD108, L_WORD237, SVT_COEFF },                     // {"Coefficient"  ,"",SVT_COEFF},
                                                             //
    { L_WORD404, L_WORD237, SVT_ATM_PRESSURE },              // {"AtmPress"         ,"",SVT_ATM_PRESSURE},
    { L_WORD425, L_WORD237, SVT_TRIM_ANGLE_NOSIGN },         // {"Trim in deg"      ,"",SVT_TRIM_ANGLE},
    { L_WORD426, L_WORD237, SVT_TRIM_M_NOSIGN },             // {"Trim in meter"    ,"",SVT_TRIM_M},
    { L_WORD427, L_WORD237, SVT_LIST_ANGLE_NOSIGN },         // {"List in deg"      ,"",SVT_LIST_ANGLE},
    { L_WORD447, L_WORD237, SVT_LIST_M_NOSIGN },             // {"List in meter"    ,"",SVT_LIST_M},
    { L_WORD448, L_WORD237, SVT_LATITUDE },                  // {"Latitude"        ,"",SVT_LATITUDE},


    { L_WORD1084, L_WORD1085, SVT_LEVEL_OFFSET     },       // {"Level offset" ,"LOff",SVT_LEVEL_OFFSET},

};


///////////////////////////////////////////////////////////
//
//	 Function defintions
//
///////////////////////////////////////////////////////////


PROTank::PROTank(int LNumber, bool AddToList) : PROXRefObject(AddToList) {
    LineNumber = LNumber;
    Initiate(AddToList);

//Only set IDNumber if new() from config program
    SetIdNumber(this, 0, C_PRO_TANK, ObjectSet);
    Type = C_PRO_TANK;
}

PROTank::PROTank(int number, int LNumber, bool AddToList) : PROXRefObject(AddToList) {
LineNumber = LNumber;
Initiate(AddToList);
SetIdNumber(this, number, C_PRO_TANK, ObjectSet);
Type = C_PRO_TANK;
}

PROTank::PROTank(int TType, int number, int LNumber, bool AddToList) : PROXRefObject(AddToList) {
    LineNumber = LNumber;
    Type = TType;
    SetTankType(TType);
    if ( TankType != TANKTYPE_CARGO ) {
        SetIdNumber(this, number, C_PRO_TANK, ObjectSet);
    }
    Initiate(AddToList);
}

//---------------------------------------------------------------------------

void PROTank::Initiate(bool AddToList) {
    if ( AddToList ) {
        MyIndex = TankVector.size();
        TankVector.push_back(this);
        ObjectSet.insert(this);
        AddToIOObjectList();
        AddToScratchPageVector();
    } else {
        MyIndex = -1;
    }
    HasRedundancy       = false;
    HasRadarAndPressure = false;
    HasWater            = WSENSOR_NO_SENSOR;
    LevelDifference     = 0.0;
    CargoType           = new CargoTypeObject(false, AddToList);
    HasLevelSensors     = false;
    NotEmptyTank         = false;

    WaterSns            = NULL;
    MetriTapeSns        = NULL;
    HSH_FloatSns        = NULL;
    GlobalRefSystem     = false;
    UseCFTable          = false;
    HasDVManMsrPntToSns = false;
    HasDVSnsToUTI       = false;

    DBotUllRefPnt       = 0.00;
    AdjustedDBU         = 0.00;
    SteelExp            = 1.0;
    DBotManMsrPnt       = 0.00;
    DSnsToMid           = 0.00;
    DSnsToCL            = 0.00;
    DManMsrPntToMid     = 0.00;
    DManMsrPntToCL      = 0.00;
    DFltCntToMid        = 0.00;
    DFltCntToCL         = 0.00;
    DLManMsrPntToSns    = 0.00;
    DTManMsrPntToSns    = 0.00;
    DVManMsrPntToSns    = 0.00;
    DVSnsToUTI          = 0.00;
    DLFltCntToSns       = 0.00;
    DTFltCntToSns       = 0.00;
    cDTR                = 0.0;
    cDLR                = 0.0;
    cDLFC               = 0.0;
    cDTFC               = 0.0;
    cRadarDTR           = 0.0;
    cRadarDLR           = 0.0;
    LevelOffset         = 0.0;
    TableOffset         = 0.0;
    DBU_IsConfigured    = false;
    LevVolumeTab        = NULL;
    UllVolumeTab        = NULL;
    VolumeTab           = NULL;
    SoundingTab         = NULL; // Volume table based on the sounding pipe
    CenterOfFlotTab     = NULL;
    TrimCorrectionTable = NULL;
    ListCorrectionTable = NULL;
    TempCorrectionTable = NULL;
    DensityCorrectionTab = NULL;
    UllageRef           = 0.0;
    UllageFC            = 0.0;
    UllageAtSns         = 0.0;
    Level               = 0.0;
    LevelAtRef          = Level;
    LevelFC             = Level;
    Sounding            = Level;
    LoadRate            = 0.0;
    RemainingTime       = 0.0;
    StartVolPercent     = 0.0;
    Volume              = 0.0;
    VolumePercent       = 0.0;
    Weight              = 0.0;
    LCWeight            = 0.0;
    LCVolume            = 0.0;
    FilteredVolPercent  = 0.0;
    StartLevelMsrdDns   = DEFAULT_LEVEL_MSRD_DNS;

    NoiseLimitR         = PROProjectInfo::NoiseLimDefaultR;

    //CargoType ;       // CTY_Linear, Crude, Lub, ballst, ASTM 54B etc
    switch ( TankType ) {
    default:
        CargoType->InputBasicCargoType(CTY_SIMPLE_LIN);
        break;
    case TANKTYPE_CARGO:
        CargoType->InputBasicCargoType(CTY_LINEAR);
        break;
    case TANKTYPE_BALLAST:
    case TANKTYPE_VOIDSPACE:
        CargoType->InputBasicCargoType(CTY_BALLAST);
        break;
    case TANKTYPE_HFO:
        CargoType->InputBasicCargoType(CTY_HFO);
        break;
    case TANKTYPE_DO:
        CargoType->InputBasicCargoType(CTY_DO);
        break;
    case TANKTYPE_LUB:
        CargoType->InputBasicCargoType(CTY_LUB);
        break;
    case TANKTYPE_FW:
        CargoType->InputBasicCargoType(CTY_FW);
        break;
    case TANKTYPE_MISC:
        CargoType->InputBasicCargoType(CTY_SIMPLE_LIN);
        break;
    }
    Temperature         = CargoType->RefTmp1;
    CompDns             = CargoType->Comp_Density(Temperature);
    Density             = CompDns;
    MeasuredDns         = 0.0;
    FilteredMsrdDns     = Density;
    UsePrevCalcDns      = false;
    UseMeasuredDensity  = false;
    HasMeasuredDensity  = false;
    UseTempFromOtherId  = 0;
    UsePressFromOtherId = 0;
    for ( int i = 0; i < 5; i++ ) {
        TempLog[i] = NULL;
    }
    Pressure        = 0.0;
    VapourLog       = NULL;

    PressurePtr     = NULL;
    LPressurePtr    = NULL;
    TemperaturePtr  = NULL;
    OverfillPtr     = NULL;
    HighLevelPtr    = NULL;
    LowLevelPtr     = NULL;
    LoLoLevelPtr    = NULL;
    VoidSpaceAPtr   = NULL;
    LevelDiffAPtr   = NULL;
    LevelChangeAPtr = NULL;

    OverfillLimit               = PROProjectInfo::OverfillLimit;
    HighLevelLimit              = PROProjectInfo::HighLevelLimit;
    LowLevelLimit               = PROProjectInfo::LowLevelLimit;
    LoLoLevelLimit              = PROProjectInfo::LoLoLevelLimit;
    VoidSpaceLimit              = PROProjectInfo::VoidSpaceLimit;
    LevelDiffLimit              = PROProjectInfo::LevelDiffLimit;

    HighTempLimit               = PROProjectInfo::HighTempLimit;
    LowTempLimit                = PROProjectInfo::LowTempLimit;
    OverfillLocked              = PROProjectInfo::OverfillLocked;
    HighLevelLocked             = PROProjectInfo::HighLevelLocked;
    LowLevelLocked              = PROProjectInfo::LowLevelLocked;
    LowLowLevelLocked           = PROProjectInfo::LowLowLevelLocked;
    HighTempLocked              = PROProjectInfo::HighTempLocked;
    LowTempLocked               = PROProjectInfo::LowTempLocked;
    HighTankPressLocked         = PROProjectInfo::HighTankPressLocked;
    LowTankPressLocked          = PROProjectInfo::LowTankPressLocked;
    HighIGP_Locked              = PROProjectInfo::HighIGP_Locked;
    LowIGP_Locked               = PROProjectInfo::LowIGP_Locked;

    HighTankPressLimit          = PROProjectInfo::HighTankPressLimit;
    LowTankPressLimit           = PROProjectInfo::LowTankPressLimit;
    HighPressVacLimit           = PROProjectInfo::HighPressVacLimit;
    LowPressVacLimit            = PROProjectInfo::LowPressVacLimit;
    HighIGP_Limit                = PROProjectInfo::HighIGP_Limit;
    LowIGP_Limit                 = PROProjectInfo::LowIGP_Limit;
    HighVapourReturnLimit       = PROProjectInfo::HighVapourRetLimit;
    LowVapourReturnLimit        = PROProjectInfo::LowVapourRetLimit;
    IntHighTankPressLimit1      = PROProjectInfo::IntHighTankPressLimit1;
    IntLowTankPressLimit1       = PROProjectInfo::IntLowTankPressLimit1;
    IntHighTankPressLimit2      = PROProjectInfo::IntHighTankPressLimit2;
    IntLowTankPressLimit2       = PROProjectInfo::IntLowTankPressLimit2;

    hasLowPressVacLimit         = PROProjectInfo::hasLowPressVacLimit;
    hasHighPressVacLimit        = PROProjectInfo::hasHighPressVacLimit;
    hasLowIGP_Limit              = PROProjectInfo::hasLowIGP_Limit;
    hasHighIGP_Limit             = PROProjectInfo::hasHighIGP_Limit;
    hasLowVapourReturnLimit     = PROProjectInfo::hasLowVapourRetLimit;
    hasHighVapourReturnLimit    = PROProjectInfo::hasHighVapourRetLimit;
    hasLoLoLevelLimit           = PROProjectInfo::hasLoLoLevelLimit;
    HasIntHighTankPressLimit1   = false;
    HasIntLowTankPressLimit1    = false;
    HasIntHighTankPressLimit2   = false;
    HasIntLowTankPressLimit2    = false;

    LCDataTime                  = 0;


    ///////////////////////////////////////////////////////
    // Init structures for loadrate calculation
    ///////////////////////////////////////////////////////
    LrCalcTime = clock();
    for ( int i = 0; i < LR_BUFSIZE; i++ ) {
        LR_Buffer[i] = 0.0;
    }
    Prev_Volume = 0.0;
    LR_Volume   = 0.0;
    LR_Weight   = 0.0;
    LR_Cnt      = 0;
    LR_Limit    = 0.0;

    OutsideCnt      = MAX_OUTSIDE_WIN_CNT;          // Accept first reading
    VolumeOffset    = 0.0;
    VolCorrFactor   = 1.0;
    TDUTankPlacement.xpos = 0;
    TDUTankPlacement.ypos = 0;
    TDUTankPlacement.page = 0;
    TDUTankPlacement.initialized = false;
    for ( int i = 0; i < LEVEL_HISTORY_ENTRIES; i++ ) {
        LevelHistory[i] = 0.0;
    }

}
//---------------------------------------------------------------------------

PROTank::~PROTank(void) {
    delete CargoType;
    //Only increase: NumberOfPRO--;
    if ( LevVolumeTab ) {
        delete LevVolumeTab; LevVolumeTab = NULL;
    }
    if ( UllVolumeTab ) {
        delete UllVolumeTab; UllVolumeTab = NULL;
    }
    if ( SoundingTab ) {
        delete SoundingTab; SoundingTab = NULL;
    }
    if ( CenterOfFlotTab ) {
        delete CenterOfFlotTab; CenterOfFlotTab = NULL;
    }
    if ( TrimCorrectionTable ) {
        delete TrimCorrectionTable; TrimCorrectionTable = NULL;
    }
    if ( ListCorrectionTable ) {
        delete ListCorrectionTable; ListCorrectionTable = NULL;
    }
    if ( TempCorrectionTable ) {
        delete TempCorrectionTable; TempCorrectionTable = NULL;
    }
    if ( DensityCorrectionTab ) {
        delete DensityCorrectionTab; DensityCorrectionTab = NULL;
    }

    set<PRogramObjectBase *>::iterator it = ObjectSet.find(this);
    if ( it != ObjectSet.end() ) {
        ObjectSet.erase(this);
    }

    vector<PROTankWashingMachine *>::iterator twmIter = TankWashingMachineVector.begin();

    while ( twmIter != TankWashingMachineVector.end() ) {
        delete(*twmIter);
            ++twmIter;
    }
    TankWashingMachineVector.clear();


}
//---------------------------------------------------------------------------
int PROTank::GetTankType(void) {
    int TType;
    switch ( TankType ) {
    default:
        TType = C_PRO_TANK;
        break;
    case TANKTYPE_CARGO:
        TType = C_PRO_CARGO;
        break;
    case TANKTYPE_BALLAST:
        TType = C_PRO_BALLAST;
        break;
    case TANKTYPE_HFO:
        TType = C_PRO_HFO;
        break;
    case TANKTYPE_DO:
        TType = C_PRO_DO;
        break;
    case TANKTYPE_LUB:
        TType = C_PRO_LUB;
        break;
    case TANKTYPE_FW:
        TType = C_PRO_FW;
        break;
    case TANKTYPE_MISC:
        TType = C_PRO_MISC;
        break;
    }
    return (TType);
}
//---------------------------------------------------------------------------

void PROTank::SetTankType(int TType) {
    switch ( TType ) {
    default:
        TankType = TANKTYPE_NONE;
        break;
    case C_PRO_CARGO :
        TankType = TANKTYPE_CARGO;
        break;
    case C_PRO_BALLAST:
        TankType = TANKTYPE_BALLAST;
        break;
    case C_PRO_HFO:
        TankType = TANKTYPE_HFO;
        break;
    case C_PRO_DO:
        TankType = TANKTYPE_DO;
        break;
    case C_PRO_LUB:
        TankType = TANKTYPE_LUB;
        break;
    case C_PRO_FW:
        TankType = TANKTYPE_FW;
        break;
    case C_PRO_MISC:
        TankType = TANKTYPE_MISC;
        break;
    case C_PRO_VOIDSPACE:
        TankType = TANKTYPE_VOIDSPACE;
        break;
    }
}
//---------------------------------------------------------------------------

void PROTank::CheckForTPAndTemp(void) { //If tank has pressure mesurements or temperature messurements:
    bool HasTP   = false;
    bool HasTemp = false;
    for ( unsigned j = 0; j < AnalogInList.size(); j++ ) {
        switch ( AnalogInList[j]->Type ) {
        case C_AI_P906_0110         :
        case C_AI_P906_0111         :
            HasTemp = true;
        case C_AI_1728              :
        case C_AI_ATM_N_Ex          :
        case C_AI_ATM_Ex            :
        case C_AI_ATM_Ex_H          :
        case C_AI_ATM_N_Ex_0_1      :
        case C_AI_APT500		    :
        case C_AI_SPT900		    :
        case C_AI_Gen_4_20mA        :
        case C_AI_DIFF_PRESSURE_mA  :
        case C_AI_AirPurge          :
        case C_AI_MB_Press_mA       :
        case C_AI_MB_DiffPre_mA     :
            if ( ((AIPressSensor *)AnalogInList[j])->GetIsPressureSns() ) {
                AIPressSensor *tPSensor = (AIPressSensor *)AnalogInList[j];
                tankPressures.push_back(tPSensor);
                tPSensor->Location = C_AI_LOC_VAPOUR;
                HasTP = true;
                tPSensor->AddTempRefSensor(&Temperature);
            }
            break;
        case C_AI_Pt100 :
        case C_AI_Pt1000 :
        case C_AI_TEMP_mA :
        case C_AI_WATERINGR_TEMP:
        case C_AI_TEMP_AD590 :
            HasTemp = true;
            break;
        case C_AI_Radar_4_20mA :
        case C_AI_Radar_Hart   :
        case C_AI_Float_4_20mA :
        case C_AI_WashTrackSensor :
        default:
            break;
        }
    }
    if ( HasTP ) {
        float           MaxPressureRange = 0.0;
        PressurePtr = new PROTankPressure(0, this);

        PressurePtr->Name = Name;
        PressurePtr->LongName = LongName;
        PressurePtr->TagName = TagName;
        PressurePtr->SortNo = SortNo;
        PressurePtr->ReadPermissionSet = ReadPermissionSet;
        PressurePtr->WritePermissionSet = WritePermissionSet;
        for ( unsigned i = 0; i < tankPressures.size(); i++ ) {
            MaxPressureRange = MAX(tankPressures[i]->MaxRange, MaxPressureRange);
            PressurePtr->AnalogInList.push_back((AnalogInput *)tankPressures[i]);
            PressurePtr->tankPressures.push_back(tankPressures[i]);
            tankPressures[i]->Location = C_AI_LOC_VAPOUR;
        }
        PressurePtr->MaxPressureRange = MaxPressureRange;

        if ( hasHighPressVacLimit ) {
            PressurePtr->AddHighPressVacAlarm(HighPressVacLimit, true);
        }
        if ( hasLowPressVacLimit ) {
            PressurePtr->AddLowPressVacAlarm(LowPressVacLimit, true);
        }

        if ( hasHighIGP_Limit ) {
            PressurePtr->AddHighIGP_Alarm(HighIGP_Limit, true);
        }
        if ( hasLowIGP_Limit ) {
            PressurePtr->AddLowIGP_Alarm(LowIGP_Limit, true);
        }
        if ( hasHighVapourReturnLimit ) {
            PressurePtr->AddHighPressVapRetAlarm(HighVapourReturnLimit, true);
        }
        if ( hasLowVapourReturnLimit ) {
            PressurePtr->AddLowPressVapRetAlarm(LowVapourReturnLimit, true);
        }

        // Use the other limits when assuming LPG/LNG tanks
        if ( MaxPressureRange >= 15.0 ) {
            PressurePtr->SetAlarmLimits(LIMIT_HIGH_LPG_PRESS, LIMIT_LOW_LPG_PRESS, LIMIT_HIGH_LPG_PRESS, LIMIT_LOW_LPG_PRESS, LIMIT_HIGH_LPG_PRESS, LIMIT_LOW_LPG_PRESS);
        } else {
            PressurePtr->SetAlarmLimits(HighVapourReturnLimit, LowVapourReturnLimit, HighPressVacLimit, LowPressVacLimit, HighTankPressLimit, LowTankPressLimit);
        }
        if ( HasIntHighTankPressLimit1 ) {
            PressurePtr->AddHighPressInternalAlarm1(IntHighTankPressLimit1, true);
        }
        if ( HasIntLowTankPressLimit1 ) {
            PressurePtr->AddLowPressInternalAlarm1(IntLowTankPressLimit1, true);
        }
        if ( HasIntHighTankPressLimit2 ) {
            PressurePtr->AddHighPressInternalAlarm2(IntHighTankPressLimit2, true);
        }
        if ( HasIntLowTankPressLimit2 ) {
            PressurePtr->AddLowPressInternalAlarm2(IntLowTankPressLimit2, true);
        }
        PressurePtr->SetPressureAlarmMode(pLimitAdjustable);
        PressurePtr->HighPressurePtr->Locked    = HighTankPressLocked;
        PressurePtr->LowPressurePtr->Locked     = LowTankPressLocked;
        PressurePtr->SetHighIGP_Locked(HighIGP_Locked);
        PressurePtr->SetLowIGP_Locked(LowIGP_Locked);

        // Remove from the other list tank pressure sensor(s)
        for ( int i = (int)AnalogInList.size() - 1; i >= 0; i-- ) {
            switch ( AnalogInList[i]->Type ) {
            case C_AI_P906_0110       :
            case C_AI_P906_0111       :
            case C_AI_ATM_N_Ex        :
            case C_AI_ATM_Ex          :
            case C_AI_ATM_Ex_H        :
            case C_AI_ATM_N_Ex_0_1    :
            case C_AI_APT500          :
            case C_AI_SPT900          :
            case C_AI_Gen_4_20mA      :
            case C_AI_DIFF_PRESSURE_mA:
            case C_AI_1728 :
                if ( AnalogInList[i]->GetIsPressureSns() ) {
                    AnalogInList.erase(AnalogInList.begin() + i);
                }
                break;
            default:
                break;
            }
        }

        SetChildUserRights(PressurePtr);
    }
    if ( HasTemp ) {
        PROTemperature *Temp = new PROTemperature(0, this);
        TemperaturePtr = Temp;
        Temp->Name = Name;
        Temp->LongName = LongName;
        Temp->TagName = TagName;
        Temp->SortNo = SortNo;

        Temp->ReadPermissionSet = ReadPermissionSet;
        Temp->WritePermissionSet = WritePermissionSet;
        unsigned AISize = AnalogInList.size();
        for ( unsigned i = 0; i < AnalogInList.size(); i++ ) {
            switch ( AnalogInList[i]->Type ) {
            case C_AI_Pt100 :
            case C_AI_Pt1000 :
            case C_AI_TEMP_mA :
            case C_AI_WATERINGR_TEMP:
            case C_AI_TEMP_AD590 :
                Temp->AnalogInList.push_back(AnalogInList[i]);
                break;
            default:
                break;
            }
        }
        {
            unsigned i = 0;
            while ( i < AnalogInList.size() ) {
                switch ( AnalogInList[i]->Type ) {
                default:
                    i++;
                    break;
                case C_AI_Pt100 :
                case C_AI_Pt1000 :
                case C_AI_TEMP_mA :
                case C_AI_WATERINGR_TEMP:
                case C_AI_TEMP_AD590 :
                    AnalogInList.erase(AnalogInList.begin() + i);
                    break;
                }
            }
        }

        Temp->SortAnalogInputs();
        Temp->AddSensorAlarms();
        Temp->CreateAlarms();
        // Must create the alarms before locking
        Temp->HighTempPtr->Limit     = HighTempLimit;
        Temp->LowTempPtr->Limit      = LowTempLimit;
        //Temp->HighBotTempPtr->Locked = HighTempLocked;
        //Temp->LowBotTempPtr->Locked  = LowTempLocked;

        SetChildUserRights(Temp);
    }

    for ( unsigned i = 0; i < AnalogInList.size(); i++ ) {
        switch ( AnalogInList[i]->Type ) {
        case C_AI_1728              :
        case C_AI_P906_0110         :
        case C_AI_P906_0111         :
        case C_AI_ATM_N_Ex          :
        case C_AI_Gen_4_20mA        :
        case C_AI_ATM_Ex            :
        case C_AI_ATM_Ex_H          :
        case C_AI_ATM_N_Ex_0_1      :
        case C_AI_APT500		    :
        case C_AI_SPT900		    :
        case C_AI_DIFF_PRESSURE_mA  :
        case C_AI_AirPurge          :
        case C_AI_MB_Press_mA       :
        case C_AI_MB_DiffPre_mA     :
            {
                AIPressSensor *SnsPtr = (AIPressSensor *)AnalogInList[i];
                if ( !SnsPtr->GetIsPressureSns() ) {
                    if ( HasRedundancy ) {
                        SnsPtr->Location = C_AI_LOC_REDUNDANCY1 + LevelPressures.size();
                    } else {
                        SnsPtr->Location = C_AI_LOC_BOTTOM + LevelPressures.size();
                    }
                    LevelPressures.push_back(SnsPtr);

                }
            }
            break;
        case C_AI_Radar_4_20mA :
        case C_AI_Radar_Hart :
        case C_AI_Float_4_20mA :
        case C_AI_Pt100 :
        case C_AI_Pt1000 :
        case C_AI_TEMP_mA :
        case C_AI_TEMP_AD590 :
            break;
        }
    }
    for ( unsigned i = 0; i < LevelPressures.size(); i++ ) {
        AIPressSensor *tmpPtr = LevelPressures[i];
        for ( unsigned j = 0; j < LevelPressures.size(); j++ ) {
            //if (j != i) {
            tmpPtr->AddLevelPressSensor(LevelPressures[j]);
            //}
        }
        for ( unsigned k = 0; k < tankPressures.size(); k++ ) {
            tmpPtr->SetRefSnsPtr(tankPressures[k]);
        }
    }
    for ( unsigned i = 0; i < tankPressures.size(); i++ ) {
        AIPressSensor *tmpPtr = tankPressures[i];
        for ( unsigned j = 0; j < tankPressures.size(); j++ ) {
            tmpPtr->SetRefSnsPtr(tankPressures[j]);
        }
        for ( unsigned k = 0; k < LevelPressures.size(); k++ ) {
            tmpPtr->AddLevelPressSensor(LevelPressures[k]);
        }
    }
    if ( !RadarSensors.empty() && !LevelPressures.empty() ) {
        HasRadarAndPressure = true;
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
void PROTank::WriteConfigToFile(TSNConfigString &ConfigString) {
    int        TType       = GetTankType();
    AnsiString LocalString;
    AnsiString IdNumStr;
    IdNumStr.cat_sprintf("0x%0x", IDNumber);
    LocalString += KeyWord(TType) + IdNumStr + CrLfStr;
    LocalString += MakeConfigString();   //common
    /*
    if (ANPro3Id != -1 ) {
            LocalString +=TabStr1+KeyWord(C_XREF_ANPRO3)+(AnsiString)ANPro3Id+CrLfStr;
    }
    if (SaabId != -1 ) {
            LocalString +=TabStr1+KeyWord(C_XREF_SAAB)+(AnsiString)SaabId+CrLfStr;
    }
    */
    if ( HasRedundancy ) {
        LocalString += TabStr1 + KeyWord(C_REDUNDANCY) + CrLfStr;
    }
    if ( !RadarSensors.empty() && (NoiseLimitR != PROProjectInfo::NoiseLimDefaultR) ) {
        LocalString += TabStr1 + KeyWord(C_NOISE_LIM_RADAR) + FloatToAnsiString(NoiseLimitR) + CrLfStr;
    }
    if ( UseTempFromOtherId ) {
        LocalString += TabStr1 + KeyWord(C_COMMON_TEMPERATURE) + AnsiString(UseTempFromOtherId) + CrLfStr;
    }
    if ( UsePressFromOtherId ) {
        LocalString += TabStr1 + KeyWord(C_COMMON_PRESSURE) + AnsiString(UsePressFromOtherId) + CrLfStr;
    }
    switch ( TankType ) {
    default:
    case TANKTYPE_CARGO:
    case TANKTYPE_BALLAST:
    case TANKTYPE_HFO:
    case TANKTYPE_DO:
    case TANKTYPE_LUB:
    case TANKTYPE_FW:
        if ( PROProjectInfo::OverfillLimit != OverfillLimit ) {
            LocalString += TabStr1 + KeyWord(AL_LIM_OVERFILL) + FloatToAnsiString(OverfillLimit) + CrLfStr;
        }
        if ( PROProjectInfo::HighLevelLimit != HighLevelLimit ) {
            LocalString += TabStr1 + KeyWord(AL_LIM_HIGHLEVEL) + FloatToAnsiString(HighLevelLimit) + CrLfStr;
        }
        if ( PROProjectInfo::LowLevelLimit != LowLevelLimit ) {
            LocalString += TabStr1 + KeyWord(AL_LIM_LOWLEVEL) + FloatToAnsiString(LowLevelLimit) + CrLfStr;
        }
        if ( PROProjectInfo::LoLoLevelLimit != LoLoLevelLimit ) {
            LocalString += TabStr1 + KeyWord(AL_LIM_LOWLOW_LEVEL) + FloatToAnsiString(LoLoLevelLimit) + CrLfStr;
        }
        if ( PROProjectInfo::LevelDiffLimit != LevelDiffLimit ) {
            LocalString += TabStr1 + KeyWord(AL_LIM_LEVELDIFF) + FloatToAnsiString(PROProjectInfo::LevelDiffLimit) + CrLfStr;
        }
        if ( PROProjectInfo::HighTempLimit != HighTempLimit ) {
            LocalString += TabStr1 + KeyWord(AL_LIM_HIGHTEMP) + FloatToAnsiString(HighTempLimit) + CrLfStr;
        }
        if ( PROProjectInfo::LowTempLimit != LowTempLimit ) {
            LocalString += TabStr1 + KeyWord(AL_LIM_LOWTEMP) + FloatToAnsiString(LowTempLimit) + CrLfStr;
        }
        if ( hasLoLoLevelLimit && ( hasLoLoLevelLimit != PROProjectInfo::hasLoLoLevelLimit)) {
            LocalString += TabStr1 + KeyWord(AL_LIM_HAS_LOLO_LEVEL)  + CrLfStr;
        }

        if ( PROProjectInfo::PressLim_mBar ) {
            if ( PROProjectInfo::HighTankPressLimit != HighTankPressLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGHTANK_PRESS) + FloatToAnsiString(HighTankPressLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if ( PROProjectInfo::LowTankPressLimit != LowTankPressLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOWTANK_PRESS) + FloatToAnsiString(LowTankPressLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if ( PROProjectInfo::HighPressVacLimit != HighPressVacLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_PV_PRESS) + FloatToAnsiString(HighPressVacLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if ( PROProjectInfo::LowPressVacLimit != LowPressVacLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOW_PV_PRESS) + FloatToAnsiString(LowPressVacLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if ( PROProjectInfo::HighIGP_Limit != HighIGP_Limit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_IG_PRESS) + FloatToAnsiString(HighIGP_Limit * MH2O_TO_MBAR) + CrLfStr;
            }
            if ( PROProjectInfo::LowIGP_Limit != LowIGP_Limit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOW_IG_PRESS) + FloatToAnsiString(LowIGP_Limit * MH2O_TO_MBAR) + CrLfStr;
            }
            if ( PROProjectInfo::HighVapourRetLimit != HighVapourReturnLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGHVAPOUR_RET) + FloatToAnsiString(HighVapourReturnLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if ( PROProjectInfo::LowVapourRetLimit != LowVapourReturnLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOWVAPOUR_RET) + FloatToAnsiString(LowVapourReturnLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if ( PROProjectInfo::IntHighTankPressLimit1 != IntHighTankPressLimit1 ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS1) + FloatToAnsiString(IntHighTankPressLimit1 * MH2O_TO_MBAR) + CrLfStr;
            }
            if ( PROProjectInfo::IntLowTankPressLimit1 != IntLowTankPressLimit1 ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS2) + FloatToAnsiString(IntLowTankPressLimit1 * MH2O_TO_MBAR) + CrLfStr;
            }
            if ( PROProjectInfo::IntLowTankPressLimit2 != IntLowTankPressLimit2 ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS1) + FloatToAnsiString(IntLowTankPressLimit2 * MH2O_TO_MBAR) + CrLfStr;
            }
            if ( PROProjectInfo::IntHighTankPressLimit2 != IntHighTankPressLimit2 ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS2) + FloatToAnsiString(IntHighTankPressLimit2 * MH2O_TO_MBAR) + CrLfStr;
            }
        } else {
            if ( PROProjectInfo::HighTankPressLimit != HighTankPressLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGHTANK_PRESS) + FloatToAnsiString(HighTankPressLimit) + CrLfStr;
            }
            if ( PROProjectInfo::LowTankPressLimit != LowTankPressLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOWTANK_PRESS) + FloatToAnsiString(LowTankPressLimit) + CrLfStr;
            }
            if ( PROProjectInfo::HighPressVacLimit != HighPressVacLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_PV_PRESS) + FloatToAnsiString(HighPressVacLimit) + CrLfStr;
            }
            if ( PROProjectInfo::LowPressVacLimit != LowPressVacLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOW_PV_PRESS) + FloatToAnsiString(LowPressVacLimit) + CrLfStr;
            }
            if ( PROProjectInfo::HighIGP_Limit != HighIGP_Limit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_IG_PRESS) + FloatToAnsiString(HighIGP_Limit) + CrLfStr;
            }
            if ( PROProjectInfo::LowIGP_Limit != LowIGP_Limit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOW_IG_PRESS) + FloatToAnsiString(LowIGP_Limit) + CrLfStr;
            }
            if ( PROProjectInfo::HighVapourRetLimit != HighVapourReturnLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGHVAPOUR_RET) + FloatToAnsiString(HighVapourReturnLimit) + CrLfStr;
            }
            if ( PROProjectInfo::LowVapourRetLimit != LowVapourReturnLimit ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOWVAPOUR_RET) + FloatToAnsiString(LowVapourReturnLimit) + CrLfStr;
            }
            if ( PROProjectInfo::IntHighTankPressLimit1 != IntHighTankPressLimit1 ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS1) + FloatToAnsiString(IntHighTankPressLimit1) + CrLfStr;
            }
            if ( PROProjectInfo::IntLowTankPressLimit1 != IntLowTankPressLimit1 ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS2) + FloatToAnsiString(IntLowTankPressLimit1) + CrLfStr;
            }
            if ( PROProjectInfo::IntLowTankPressLimit2 != IntLowTankPressLimit2 ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS1) + FloatToAnsiString(IntLowTankPressLimit2) + CrLfStr;
            }
            if ( PROProjectInfo::IntHighTankPressLimit2 != IntHighTankPressLimit2 ) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS2) + FloatToAnsiString(IntHighTankPressLimit2) + CrLfStr;
            }
        }
		if ( HasIntHighTankPressLimit1 ) {
            LocalString += TabStr1 + KeyWord(AL_LIM_HAS_HI_TNK_PR1) + CrLfStr;
        }
		if ( HasIntLowTankPressLimit1 ) {
			LocalString += TabStr1 + KeyWord(AL_LIM_HAS_LO_TNK_PR1) + CrLfStr;
		}
		if ( HasIntHighTankPressLimit2 ) {
            LocalString += TabStr1 + KeyWord(AL_LIM_HAS_HI_TNK_PR2) + CrLfStr;
		}
		if ( HasIntLowTankPressLimit2 ) {
            LocalString += TabStr1 + KeyWord(AL_LIM_HAS_LO_TNK_PR2) + CrLfStr;
        }

        if ( OverfillLocked      && !PROProjectInfo::OverfillLocked     )  LocalString += TabStr1 + KeyWord(AL_LOCK_OVERFILL) + CrLfStr;
        if ( HighLevelLocked     && !PROProjectInfo::HighLevelLocked    )  LocalString += TabStr1 + KeyWord(AL_LOCK_HIGHLEVEL) + CrLfStr;
        if ( LowLevelLocked      && !PROProjectInfo::LowLevelLocked     )  LocalString += TabStr1 + KeyWord(AL_LOCK_LOWLEVEL) + CrLfStr;
        if ( LowLowLevelLocked   && !PROProjectInfo::LowLowLevelLocked  )  LocalString += TabStr1 + KeyWord(AL_LOCK_LOWLOWLEVEL) + CrLfStr;
        if ( HighTempLocked      && !PROProjectInfo::HighTempLocked     )  LocalString += TabStr1 + KeyWord(AL_LOCK_HIGHTEMP) + CrLfStr;
        if ( LowTempLocked       && !PROProjectInfo::LowTempLocked      )  LocalString += TabStr1 + KeyWord(AL_LOCK_LOWTEMP) + CrLfStr;
        if ( LowTankPressLocked  && !PROProjectInfo::HighTankPressLocked)  LocalString += TabStr1 + KeyWord(AL_LOCK_LOWTANK_PRESS) + CrLfStr;
        if ( HighTankPressLocked && !PROProjectInfo::LowTankPressLocked )  LocalString += TabStr1 + KeyWord(AL_LOCK_HIGHTANK_PRESS) + CrLfStr;
        if ( LowIGP_Locked       && !PROProjectInfo::HighIGP_Locked     )  LocalString += TabStr1 + KeyWord(AL_LOCK_LOW_IGP) + CrLfStr;
        if ( HighIGP_Locked      && !PROProjectInfo::LowIGP_Locked      )  LocalString += TabStr1 + KeyWord(AL_LOCK_HIGH_IGP) + CrLfStr;
        break;
    case TANKTYPE_VOIDSPACE:
        LocalString += TabStr1 + KeyWord(AL_LIM_VOIDSPACE) + FloatToAnsiString(PROProjectInfo::VoidSpaceLimit) + CrLfStr;
        break;
    }
    for ( unsigned i = 0; i < AllAnalogInList.size(); i++ ) {
        LocalString += AllAnalogInList[i]->MakeConfigString();          //common
    }
    if ( !TankWashingMachineVector.empty() ) {
        for ( unsigned i = 0; i < TankWashingMachineVector.size(); i++ ) {
            TankWashingMachineVector[i]->WriteConfigToFile(ConfigString);
        }
    }
    if ( GlobalRefSystem ) LocalString += TabStr1 + KeyWord(C_GLOBAL_REFSYS) + CrLfStr;
    if ( StartLevelMsrdDns != DEFAULT_LEVEL_MSRD_DNS ) {
        LocalString += TabStr1 + KeyWord(C_MIN_DNS_DIST) + FloatToAnsiString(StartLevelMsrdDns) + CrLfStr;
    }
    if ( UseCFTable ) LocalString += TabStr1 + KeyWord(C_USE_CF_TAB) + CrLfStr;
    if ( DBU_IsConfigured ) {
        LocalString += TabStr1 + KeyWord(C_D_BOT_ULL_REF) + FloatToAnsiString(DBotUllRefPnt) + CrLfStr;
    }
    if ( DBotManMsrPnt ) {
        LocalString += TabStr1 + KeyWord(C_D_BOT_MAN_MSR) + FloatToAnsiString(DBotManMsrPnt) + CrLfStr;
    }
    if ( GlobalRefSystem ) {
        LocalString += TabStr1 + KeyWord(C_D_SNS_MID) + FloatToAnsiString(DSnsToMid) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_D_SNS_CL) + FloatToAnsiString(DSnsToCL) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_D_MAN_MSR_MID) + FloatToAnsiString(DManMsrPntToMid) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_D_MAN_MSR_CL) + FloatToAnsiString(DManMsrPntToCL) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_D_FC_MID) + FloatToAnsiString(DFltCntToMid) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_D_FC_CL) + FloatToAnsiString(DFltCntToCL) + CrLfStr;
    } else {
        LocalString += TabStr1 + KeyWord(C_D_L_MAN_MSR_SNS) + FloatToAnsiString(DLManMsrPntToSns) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_D_T_MAN_MSR_SNS) + FloatToAnsiString(DTManMsrPntToSns) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_D_L_FC_SNS) + FloatToAnsiString(DLFltCntToSns) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_D_T_FC_SNS) + FloatToAnsiString(DTFltCntToSns) + CrLfStr;
    }
    if ( cRadarDLR || cRadarDTR ) {
        LocalString += TabStr2 + KeyWord(C_D_L_SENSOR_TO_RADAR) + FloatToAnsiString(cRadarDLR) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_D_T_SENSOR_TO_RADAR) + FloatToAnsiString(cRadarDTR) + CrLfStr;
    }

    if ( HasDVManMsrPntToSns ) {
        LocalString += TabStr1 + KeyWord(C_D_V_MAN_MSR_SNS) + FloatToAnsiString(DVManMsrPntToSns) + CrLfStr;
    }
    if ( HasDVSnsToUTI ) {
        LocalString += TabStr1 + KeyWord(C_D_V_ULL_REF_TO_UTI) + FloatToAnsiString(DVSnsToUTI) + CrLfStr;
    }

    if ( LevVolumeTab ) {
        LocalString += LevVolumeTab->MakeConfigString();
    }
    if ( UllVolumeTab ) {
        LocalString += UllVolumeTab->MakeConfigString();
    }
    if ( SoundingTab ) {
        LocalString += SoundingTab->MakeConfigString();
    }
    if ( CenterOfFlotTab ) {
        LocalString += CenterOfFlotTab->MakeConfigString();
    }
    if ( TrimCorrectionTable ) {
        LocalString += TrimCorrectionTable->MakeConfigString();
    }
    if ( ListCorrectionTable ) {
        LocalString += ListCorrectionTable->MakeConfigString();
    }
    if ( TempCorrectionTable ) {
        LocalString += TempCorrectionTable->MakeConfigString();
    }
    if ( DensityCorrectionTab ) {
        LocalString += DensityCorrectionTab->MakeConfigString();
    }

    if ( TDUTankPlacement.initialized ) {
        LocalString += TabStr1 + KeyWord(C_TDU_TANK_PLAN_POS) + CrLfStr;
        LocalString += TabStr1 + TabStr1 + KeyWord(C_XPOS) + AnsiString(TDUTankPlacement.xpos) + CrLfStr;
        LocalString += TabStr1 + TabStr1 + KeyWord(C_YPOS) + AnsiString(TDUTankPlacement.ypos) + CrLfStr;
        LocalString += TabStr1 + TabStr1 + KeyWord(C_PAGE) + AnsiString(TDUTankPlacement.page) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_TDU_TANK_PLAN_POS_END) + CrLfStr;
    }

    LocalString += CrLfStr;
    LocalString += KeyWord(C_PRO_END) + CrLfStr;
    LocalString += CrLfStr;
    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------


int PROTank::LoadConfigFromFile(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    bool HasDLManMsrPntToSns = false;
    bool HasDTManMsrPntToSns = false;
    bool HasDLFltCntToSns    = false;
    bool HasDTFltCntToSns    = false;

    bool NoError             = true;
    int  ErrorLine           = 0;
    int  Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)"Tank " + Name, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning((AnsiString)"Tank " + Name, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_END:          // If AI type not found can continue with this
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
            case C_REDUNDANCY:
                HasRedundancy = true;
                NoiseLimitR = LEVEL_NOISE_LIMIT_RADAR_COMBI;
                switch ( TankType ) {
                case TANKTYPE_CARGO:
                    PROCargoTank::Redundancy = true;
                    break;
                case TANKTYPE_BALLAST:
                    PROBallastTank::Redundancy = true;
                    break;
                case TANKTYPE_HFO:
                case TANKTYPE_DO:
                case TANKTYPE_LUB:
                case TANKTYPE_FW:
                case TANKTYPE_MISC:
                    PROServiceTank::Redundancy = true;
                    break;
                case TANKTYPE_VOIDSPACE:
                    PROVoidSpace::Redundancy = true;
                    break;
                }
                break;
            case C_NOISE_LIM_RADAR:
                NoiseLimitR = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_COMMON_TEMPERATURE:
                UseTempFromOtherId = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_COMMON_PRESSURE:
                UsePressFromOtherId = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_D_BOT_ULL_REF:
            case C_D_BOT_ULL_REF2:
                DBotUllRefPnt = ConfigString.ReadDouble(ErrorLine);
                AdjustedDBU = DBotUllRefPnt;
                DBU_IsConfigured = true;
                NoError = !ErrorLine;
                break;
            case C_D_BOT_MAN_MSR:
            case C_D_BOT_MAN_MSR2:
                DBotManMsrPnt = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_SNS_MID :
            case C_D_SNS_MID2:
                DSnsToMid = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_SNS_CL :
            case C_D_SNS_CL2:
                DSnsToCL = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_MAN_MSR_MID:
            case C_D_MAN_MSR_MID2:
                DManMsrPntToMid = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_MAN_MSR_CL :
            case C_D_MAN_MSR_CL2:
                DManMsrPntToCL = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_FC_MID :
            case C_D_FC_MID2:
                DFltCntToMid = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_FC_CL:
            case C_D_FC_CL2:
                DFltCntToCL = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_L_MAN_MSR_SNS:
            case C_D_L_MAN_MSR_SNS2:
                DLManMsrPntToSns = ConfigString.ReadDouble(ErrorLine);
                if ( !ErrorLine ) {
                    HasDLManMsrPntToSns = true;
                } else {
                    NoError = false;
                }
                break;
            case C_D_T_MAN_MSR_SNS :
            case C_D_T_MAN_MSR_SNS2:
                DTManMsrPntToSns = ConfigString.ReadDouble(ErrorLine);
                if ( !ErrorLine ) {
                    HasDTManMsrPntToSns = true;
                } else {
                    NoError = false;
                }
                break;
            case C_D_V_MAN_MSR_SNS :
            case C_D_V_MAN_MSR_SNS2:
                DVManMsrPntToSns = ConfigString.ReadDouble(ErrorLine);
                if ( !ErrorLine ) {
                    HasDVManMsrPntToSns = true;
                } else {
                    NoError = false;
                }
                break;
            case C_D_V_ULL_REF_TO_UTI :
                DVSnsToUTI = ConfigString.ReadDouble(ErrorLine);
                if ( !ErrorLine ) {
                    HasDVSnsToUTI = true;
                } else {
                    NoError = false;
                }
                break;

            case C_D_L_FC_SNS :
            case C_D_L_FC_SNS2:
                DLFltCntToSns = ConfigString.ReadDouble(ErrorLine);
                if ( !ErrorLine ) {
                    HasDLFltCntToSns = true;
                } else {
                    NoError = false;
                }
                break;
            case C_D_T_FC_SNS:
            case C_D_T_FC_SNS2:
                DTFltCntToSns = ConfigString.ReadDouble(ErrorLine);
                if ( !ErrorLine ) {
                    HasDTFltCntToSns = true;
                } else {
                    NoError = false;
                }
                break;
            case C_MIN_DNS_DIST:
                StartLevelMsrdDns = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_T_P_AT_SENSOR:
            case C_T_P_AT_CF:
            case C_T_P_AT_REFPT:
                // Dummy entries
                break;
            case C_GLOBAL_REFSYS:
                GlobalRefSystem = true;
                break;
            case C_D_L_SENSOR_TO_RADAR:
                cRadarDLR = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_T_SENSOR_TO_RADAR:
                cRadarDTR = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_D_V_SENSOR_TO_RADAR:
                ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_USE_CF_TAB:
                UseCFTable = true;
                break;
            case C_T_TABLE_OBJ_END:
                break;
            case C_T_LEVEL_VOL_TABLE:
                LevVolumeTab = new TSNTable1Degree(Key);
                VolumeTab = LevVolumeTab;
                if ( LevVolumeTab ) LevVolumeTab->LoadConfigString(ConfigString, this);
                break;
            case C_T_ULLAGE_VOL_TABLE:
                UllVolumeTab = new TSNTable1Degree(Key);
                VolumeTab = UllVolumeTab;
                if ( UllVolumeTab ) UllVolumeTab->LoadConfigString(ConfigString, this);
                break;
            case C_T_SOUNDING_TABLE:
                SoundingTab = new TSNTable1Degree(Key);
                if ( SoundingTab ) SoundingTab->LoadConfigString(ConfigString, this);
                break;
            case C_T_COF_TABLE:
                CenterOfFlotTab = new TSNTableCenterOfFlotation(C_T_COF_TABLE);
                if ( CenterOfFlotTab ) CenterOfFlotTab->LoadConfigString(ConfigString, this);
                break;
            case C_T_VCORR_TABLE_TRIM:
                TrimCorrectionTable = new TSNTableLevelCorrection(C_T_VCORR_TABLE_TRIM);
                if ( TrimCorrectionTable ) TrimCorrectionTable->LoadConfigString(ConfigString, this);
                break;
            case C_T_VCORR_TABLE_LIST:
                ListCorrectionTable = new TSNTableLevelCorrection(C_T_VCORR_TABLE_LIST);
                if ( ListCorrectionTable ) ListCorrectionTable->LoadConfigString(ConfigString, this);
                break;
            case C_T_VCORR_TABLE_TEMP:
                TempCorrectionTable = new TSNTableLevelCorrection(C_T_VCORR_TABLE_LIST);
                if ( TempCorrectionTable ) TempCorrectionTable->LoadConfigString(ConfigString, this);
                break;
            case C_T_DENSITY_CORR_TABLE:
                DensityCorrectionTab = new TSNTable1Degree(Key);
                if ( DensityCorrectionTab ) DensityCorrectionTab->LoadConfigString(ConfigString, this);
                break;
            case C_T_COG_TABLE:
                CenterOfFlotTab = new TSNTableCenterOfFlotation(C_T_COG_TABLE);
                if ( CenterOfFlotTab ) CenterOfFlotTab->LoadConfigString(ConfigString, this);
                break;
            case AL_LIM_OVERFILL:
                OverfillLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGHLEVEL:
                HighLevelLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWLEVEL :
                LowLevelLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWLOW_LEVEL :
                hasLoLoLevelLimit = true;
                LoLoLevelLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_LEVELDIFF :
                LevelDiffLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_VOIDSPACE :
                VoidSpaceLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGHTEMP :
                HighTempLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWTEMP :
                LowTempLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGHTANK_PRESS:
                HighTankPressLimit = ConfigString.ReadDouble(ErrorLine);
                if ( PROProjectInfo::PressLim_mBar ) {
                    HighTankPressLimit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWTANK_PRESS :
                LowTankPressLimit = ConfigString.ReadDouble(ErrorLine);
                if ( PROProjectInfo::PressLim_mBar ) {
                    LowTankPressLimit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGHVAPOUR_RET:
                HighVapourReturnLimit    = ConfigString.ReadDouble(ErrorLine);
                hasHighVapourReturnLimit = true;
                if ( PROProjectInfo::PressLim_mBar ) {
                    HighVapourReturnLimit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWVAPOUR_RET:
                LowVapourReturnLimit    = ConfigString.ReadDouble(ErrorLine);
                hasLowVapourReturnLimit = true;
                if ( PROProjectInfo::PressLim_mBar ) {
                    LowVapourReturnLimit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGH_PV_PRESS:
                HighPressVacLimit    = ConfigString.ReadDouble(ErrorLine);
                hasHighPressVacLimit = true;
                if ( PROProjectInfo::PressLim_mBar ) {
                    HighPressVacLimit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOW_PV_PRESS :
                LowPressVacLimit    = ConfigString.ReadDouble(ErrorLine);
                hasLowPressVacLimit = true;
                NoError = !ErrorLine;
                if ( PROProjectInfo::PressLim_mBar ) {
                    LowPressVacLimit  /= MH2O_TO_MBAR;
                }
                break;
            case AL_LIM_HIGH_IG_PRESS:
                HighIGP_Limit    = ConfigString.ReadDouble(ErrorLine);
                hasHighIGP_Limit = true;
                if ( PROProjectInfo::PressLim_mBar ) {
                    HighIGP_Limit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOW_IG_PRESS :
                LowIGP_Limit    = ConfigString.ReadDouble(ErrorLine);
                hasLowIGP_Limit = true;
                NoError = !ErrorLine;
                if ( PROProjectInfo::PressLim_mBar ) {
                    LowIGP_Limit  /= MH2O_TO_MBAR;
                }
                break;
            case AL_LIM_X_HI_TNK_PRESS1:
                IntHighTankPressLimit1 = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                if ( PROProjectInfo::PressLim_mBar ) {
                    IntHighTankPressLimit1  /= MH2O_TO_MBAR;
                }
                break;
            case AL_LIM_X_HI_TNK_PRESS2:
                IntHighTankPressLimit2 = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                if ( PROProjectInfo::PressLim_mBar ) {
                    IntHighTankPressLimit2  /= MH2O_TO_MBAR;
                }
                break;
            case AL_LIM_X_LO_TNK_PRESS1 :
                IntLowTankPressLimit1 = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                if ( PROProjectInfo::PressLim_mBar ) {
                    IntLowTankPressLimit1  /= MH2O_TO_MBAR;
                }
                break;
            case AL_LIM_X_LO_TNK_PRESS2 :
                IntLowTankPressLimit2 = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                if ( PROProjectInfo::PressLim_mBar ) {
                    IntLowTankPressLimit2  /= MH2O_TO_MBAR;
                }
                break;
            case AL_LIM_HAS_HI_TNK_PR1:
                HasIntHighTankPressLimit1 = true;
                break;
            case AL_LIM_HAS_LO_TNK_PR1:
                HasIntLowTankPressLimit1  = true;
                break;
            case AL_LIM_HAS_HI_TNK_PR2:
                HasIntHighTankPressLimit2 = true;
                break;
            case AL_LIM_HAS_LO_TNK_PR2:
                HasIntLowTankPressLimit2  = true;
                break;
            case AL_LIM_HAS_LOLO_LEVEL:
                hasLoLoLevelLimit = true;
                break;
            case AL_LOCK_OVERFILL :
                OverfillLocked = true;
                break;
            case AL_UNLOCK_OVERFILL     :
                OverfillLocked = false;
                break;
            case AL_LOCK_HIGHLEVEL:
                HighLevelLocked = true;
                break;
            case AL_LOCK_LOWLEVEL:
                LowLevelLocked = true;
                break;
            case AL_LOCK_LOWLOWLEVEL:
                LowLowLevelLocked = true;
                break;
            case AL_LOCK_HIGHTEMP:
                HighTempLocked = true;
                break;
            case AL_LOCK_LOWTEMP:
                LowTempLocked = true;
                break;
            case AL_LOCK_HIGHTANK_PRESS:
                LowTankPressLocked = true;
                break;
            case AL_LOCK_LOWTANK_PRESS :
                HighTankPressLocked = true;
                break;
            case AL_LOCK_HIGH_IGP      :
                HighIGP_Locked = true;
                break;
            case AL_LOCK_LOW_IGP      :
                LowIGP_Locked = true;
                break;

            case C_AI_DIFF_PRESSURE_mA:
                {
                    AIDiffPressSensor_mA *AnalogInPtr = new AIDiffPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_P906_0110:
            case C_AI_P906_0111:
                {
                    AIPressSensor_mV *AnalogInPtr = new AIPressSensor_mV(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
#ifndef ANCONF
                    AITempSensor_Pt1000 *tmpTemp = new AITempSensor_Pt1000(AnalogInPtr);
                    AnalogInList.push_back((AnalogInput *)tmpTemp);
#endif
                }
                break;
            case C_AI_1728:
                {
                    AIPressSensor_mV *AnalogInPtr = new AIPressSensor_mV(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_ATM_N_Ex:
            case C_AI_ATM_Ex:
            case C_AI_ATM_Ex_H:
            case C_AI_ATM_N_Ex_0_1:
            case C_AI_APT500	  :
            case C_AI_SPT900	  :
            case C_AI_Gen_4_20mA:
                {
                    AIPressSensor_mA *AnalogInPtr = new AIPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_Radar_4_20mA:
                {
                    AIRadarSensor_mA *AnalogInPtr = new AIRadarSensor_mA();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    RadarSensors.push_back((AnalogInput *)AnalogInPtr);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_Radar_Hart :
                {
                    AIRadarSensorHart *AnalogInPtr = new AIRadarSensorHart();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    RadarSensors.push_back((AnalogInput *)AnalogInPtr);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    ModbusSensorSet.insert(AnalogInPtr);
                }
                break;
            case C_AI_MB_Press_mA   :
                {
                    AIModbusPressSensor_mA *AnalogInPtr = new AIModbusPressSensor_mA();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    ModbusSensorSet.insert(AnalogInPtr);
                }
                break;
            case C_AI_MB_DiffPre_mA :
                {
                    AIModbusDiffPressSensor_mA *AnalogInPtr = new AIModbusDiffPressSensor_mA();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    ModbusSensorSet.insert(AnalogInPtr);
                }
                break;
            case C_AI_AirPurge :
                {
                    AIAirPurgePressSensor *AirPurgeSns = new AIAirPurgePressSensor();
                    AirPurgeSns->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AirPurgeSns);
                    ModbusSensorSet.insert(AirPurgeSns);
                }
                break;
            case C_AI_Float_4_20mA :
                {
                    AIFloatSensor_mA *AnalogInPtr = new AIFloatSensor_mA();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    RadarSensors.push_back((AnalogInput *)AnalogInPtr);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_MetriTape:
                MetriTapeSns = new AIMetriTapeSensor();
                MetriTapeSns->LoadConfigString(ConfigString);
                AnalogInList.push_back((AnalogInput *)MetriTapeSns);
                ModbusSensorSet.insert(MetriTapeSns);
                break;
            case C_AI_HSH_LNG_Float:
                HSH_FloatSns = new AILNGFloat();
                HSH_FloatSns->LoadConfigString(ConfigString);
                AnalogInList.push_back((AnalogInput *)HSH_FloatSns);
                ModbusSensorSet.insert(HSH_FloatSns);
                break;
            case C_AI_Pt100:
                {
                    float rDistance = 0.0;
                    if ( !RadarSensors.empty() ) {
                        rDistance = MAX(RadarSensors[0]->MinRange, RadarSensors[0]->MaxRange);
                    }
                    AITempSensor_Pt100 *AnalogInPtr = new AITempSensor_Pt100(rDistance);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_Pt1000:
                {
                    float rDistance = 0.0;
                    if ( !RadarSensors.empty() ) {
                        rDistance = MAX(RadarSensors[0]->MinRange, RadarSensors[0]->MaxRange);
                    }
                    AITempSensor_Pt1000 *AnalogInPtr = new AITempSensor_Pt1000(rDistance);
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
            case C_AI_TEMP_AD590:
                {
                    AITempSensor_AD590 *AnalogInPtr = new AITempSensor_AD590();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_WashTrackSensor:
            case C_AI_WashTrackSensor2:
                {
                    AiWashTrackSensor *AnalogInPtr = new AiWashTrackSensor();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_WATERINGRESS:
                {
                    WaterSns = new AIWaterIngressSensor(Key);
                    WaterSns->LoadConfigString(ConfigString);
                    AIWIngressTempSensor *TempSensorPtr = new AIWIngressTempSensor(WaterSns);
                    AnalogInList.push_back((AnalogInput *)WaterSns);
                    AnalogInList.push_back((AnalogInput *)TempSensorPtr);

                    AlarmWaterDetectPtr = new AlarmWaterDetect(this);
                    AlarmSet.insert(AlarmWaterDetectPtr);
                }
                break;
                /*
            case TWM_TANK_WASHING_MACHINE_LIST:
                {
                    TankWashingAPI twmAPI;
                    bool success = twmAPI.LoadConfigStringForTank(ConfigString, IDNumber, PROTank::TankWashingMachineVector);

                    if (!success) {
                        GiveConfigWarning((AnsiString)InputKeyWord);
                    }
                }
                break;
                */
            case TWM_TANK_WASHING_MACHINE:
                {
                    PROTankWashingMachine *WashingMachinePtr = new PROTankWashingMachine(IDNumber, Name);
					if ( WashingMachinePtr->LoadConfigFromFile(ConfigString) ) {
                        TankWashingMachineVector.push_back(WashingMachinePtr);
						// Important init:
						TankWashingAPI::InitTWMMapping(this->IDNumber, WashingMachinePtr->IDNumber);
                    }
                }
                break;
            case C_TDU_TANK_PLAN_POS:
                LoadTDUTankPlanPosition(ConfigString);
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_PRO_END) );
    /*
    // Check the extra pressure alarms. HighLim2 > HighLim1, LowLim2 < LowLim1
    if ( IntHighTankPressLimit1 > IntHighTankPressLimit2 ) {
        swap(IntHighTankPressLimit1, IntHighTankPressLimit2);
        //GiveConfigWarning("ExtraHighTankPressLimit1 > ExtraHighTankPressLimit2, line " + AnsiString(ConfigString.LineCount));
    }
    if ( IntLowTankPressLimit1  < IntLowTankPressLimit2 ) {
        swap(IntLowTankPressLimit1, IntLowTankPressLimit2);
        //GiveConfigWarning("ExtraHighTankPressLimit1 < ExtraHighTankPressLimit2, line " + AnsiString(ConfigString.LineCount));
    }
    */
    CopyAnalogList();
#ifndef ANCONF
    SortAnalogInputs();
    CheckForTPAndTemp();
#endif

    switch ( TankType ) {
    case TANKTYPE_CARGO:
        if ( VolumeTab ) {
            OverfillPtr = new AlarmOverfill(this, OverfillLimit, OverfillLocked);
            if ( !DBU_IsConfigured ) {
                DBotUllRefPnt = VolumeTab->MaxX;
            }
        } else {
            OverfillPtr = NULL;

            if ( !DBU_IsConfigured ) {
                if ( !RadarSensors.empty() ) {
                    for ( unsigned i = 0; i < RadarSensors.size(); i++ ) {
                        if ( RadarSensors[i]->Distance >= 0.0 ) {
                            DBotUllRefPnt = max(DBotUllRefPnt, RadarSensors[i]->Distance);
                        }
                    }
                } else {
                    DBotUllRefPnt = 100.0; // Just make a guess
                }
            }
        }
        if ( OverfillPtr ) AlarmSet.insert(OverfillPtr);
        HighLevelPtr = new AlarmHighLevel(this, HighLevelLimit, HighLevelLocked);
        LowLevelPtr  = new AlarmLowLevel(this, LowLevelLimit, LowLevelLocked);
        if ( hasLoLoLevelLimit ) {
            LoLoLevelPtr = new AlarmLoLoLevel(this, LoLoLevelLimit, LowLowLevelLocked);
            AlarmSet.insert(LoLoLevelPtr);
        }
        AlarmSet.insert(HighLevelPtr);
        AlarmSet.insert(LowLevelPtr);
        if ( VolumeTab ) {
            LevelChangeAPtr = new AlarmLevelChange(this, LIMIT_LEVEL_CHANGE);
            AlarmSet.insert(LevelChangeAPtr);
        }
        if ( PressurePtr ) {
            PressurePtr->AddCompleteList(CompleteAlarmInfoList);
        }
        if ( TemperaturePtr ) {
            TemperaturePtr->AddCompleteList(CompleteAlarmInfoList);
        }
        break;
    default:
    case TANKTYPE_HFO:
    case TANKTYPE_DO:
    case TANKTYPE_LUB:
    case TANKTYPE_FW:
    case TANKTYPE_MISC:
        if ( VolumeTab ) {
            OverfillPtr = new AlarmOverfill(this, OverfillLimit, OverfillLocked);
            AlarmSet.insert(OverfillPtr);
            if ( !DBU_IsConfigured ) {
                DBotUllRefPnt = VolumeTab->MaxX;
            }
        }
    case TANKTYPE_BALLAST:
        /*
        // EHSMark. Workaround as PVCS will display ullage if DBU_IsConfigured== true
        if (!DBU_IsConfigured) {
            if (VolumeTab) {
                DBotUllRefPnt = VolumeTab->MaxX;
            } else {
                DBotUllRefPnt = 100.0;
            }
        }
        */
        HighLevelPtr = new AlarmHighLevel(this, HighLevelLimit, HighLevelLocked);
        LowLevelPtr  = new AlarmLowLevel(this, LowLevelLimit, LowLevelLocked);
        if ( hasLoLoLevelLimit ) {
            LoLoLevelPtr = new AlarmLoLoLevel(this, LoLoLevelLimit, LowLowLevelLocked);
            AlarmSet.insert(LoLoLevelPtr);
        }
        AlarmSet.insert(HighLevelPtr);
        AlarmSet.insert(LowLevelPtr);
        if ( VolumeTab ) {
            LevelChangeAPtr = new AlarmLevelChange(this, LIMIT_LEVEL_CHANGE);
            AlarmSet.insert(LevelChangeAPtr);
        }
        if ( PressurePtr ) {
            PressurePtr->AddCompleteList(CompleteAlarmInfoList);
        }
        if ( TemperaturePtr ) {
            TemperaturePtr->AddCompleteList(CompleteAlarmInfoList);
        }
        break;
    case TANKTYPE_VOIDSPACE:
        // EHSMark. Workaround as PVCS will display ullage if DBU_IsConfigured== true
        /*
        if (!DBU_IsConfigured) {
            if (VolumeTab) {
                DBotUllRefPnt = VolumeTab->MaxX;
            } else {
                DBotUllRefPnt = 100.0;
            }
        }
        */
        VoidSpaceAPtr = new AlarmVoidSpace(this, VoidSpaceLimit, true);
        AlarmSet.insert(VoidSpaceAPtr);
        break;
    }
    if ( HasRedundancy ) {
        LevelDiffAPtr = new AlarmLevelDifference(this, LevelDiffLimit, true);
        AlarmSet.insert(LevelDiffAPtr);
    }
    //AdjustedDBU = DBotUllRefPnt;
    AddAlarms(CompleteAlarmInfoList);
    AddSensorAlarms();
    if ( CenterOfFlotTab ) {
        CenterOfFlotTab->ConvertCGtoCF(VolumeTab);
    }
    // Set up internal distances based on reference system
    if ( GlobalRefSystem ) {
        // If DLU(DTU/DLFC/DTFC not configured, set to sensor location
        if ( !HasDLManMsrPntToSns ) {
            DLManMsrPntToSns = DSnsToMid;
        }
        if ( !HasDTManMsrPntToSns ) {
            DTManMsrPntToSns = DSnsToCL;
        }
        if ( !HasDLFltCntToSns ) {
            DLFltCntToSns = DSnsToMid;
        }
        if ( !HasDTFltCntToSns ) {
            DTFltCntToSns = DSnsToCL;
        }
        if ( UseCFTable && CenterOfFlotTab ) {
            float tableDLFC, tableDTFC;
            CenterOfFlotTab->Calculate(0.0, &tableDLFC, &tableDTFC);
            cDLFC = tableDLFC - DSnsToMid;
            cDTFC = tableDTFC - DSnsToCL;
        } else {
            cDLFC = DFltCntToMid - DSnsToMid;
            cDTFC = DFltCntToCL - DSnsToCL;
        }
        cDLR = DManMsrPntToMid - DSnsToMid;
        cDTR = DManMsrPntToCL - DSnsToCL;
    } else {
        if ( UseCFTable && CenterOfFlotTab ) {
            float tableDLFC, tableDTFC;
            CenterOfFlotTab->Calculate(0.0, &tableDLFC, &tableDTFC);
            cDLFC = tableDLFC - DSnsToMid;
            cDTFC = tableDTFC - DSnsToCL;
        } else {
            cDLFC = DLFltCntToSns;
            cDTFC = DTFltCntToSns;
        }
        cDLR = DLManMsrPntToSns;
        cDTR = DTManMsrPntToSns;
    }
    SetChildUserRights();
    int tmpentries;
    GetValueInfoTableStatic(tmpentries);

	// Important initialization of tankwashing subsystem:
	if ( !TankWashingMachineVector.empty()){
		TankWashingAPI twApi;
		vector<int>    createdTwmRunIds;
		twApi.PrepareWholeTank(this->IDNumber, twmr_type_unknown, twcm_type_unknown, createdTwmRunIds);
	}
return ErrorLine;
}

//---------------------------------------------------------------------------


void PROTank::SetProList(void) {
    if ( TemperaturePtr ) {
        TemperaturePtr->AddCompleteList(CompleteAlarmInfoList);
    } else if ( UseTempFromOtherId ) {
        TemperaturePtr = (PROTemperature *)FindPROFromIDNumber(UseTempFromOtherId);
        if ( !TemperaturePtr ) {
            AnsiString InfoStr;
            InfoStr.cat_sprintf("Temp from other IDNumber 0x%0x is incorrect. Line number: %i", UseTempFromOtherId, GetLineNumber());
            GiveConfigWarning(InfoStr);
        }
    }
    if ( PressurePtr ) {
        PressurePtr->AddCompleteList(CompleteAlarmInfoList);
    } else if ( UsePressFromOtherId ) {
        PressurePtr = (PROTankPressure *)FindPROFromIDNumber(UsePressFromOtherId);
        if ( !PressurePtr ) {
            AnsiString InfoStr;
            InfoStr.cat_sprintf("Press from other IDNumber 0x%0x is incorrect. Line number: %i", UsePressFromOtherId, GetLineNumber());
            GiveConfigWarning(InfoStr);
        }
    }
}

void PROTank::SetAllProList(void) {
    for ( unsigned i = 0; i < TankVector.size(); i++ ) {
        TankVector[i]->SetProList();
    }
}

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PROTank::SaveSettings(TSNConfigString *SettingsString) {

    if ( IsModified || WriteAll ) {
        IsModified = false;
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", IDNumber);
        LocalString += KeyWord(Type) + IdNumStr + CrLfStr;
        if ( UseMeasuredDensity ) LocalString += TabStr1 + KeyWord(C_CT_USEMEAS_DENS) + CrLfStr;
        if ( LevelOffset ) {
            LocalString += TabStr1 + KeyWord(C_ADJUST_LEVEL_OFFSET) + FloatToAnsiString(LevelOffset) + CrLfStr;
        }
        if ( TableOffset ) {
            LocalString += TabStr1 + KeyWord(C_ADJUST_TABLE_OFFSET) + FloatToAnsiString(TableOffset) + CrLfStr;
        }
        LocalString += TabStr1 + KeyWord(C_RADAR_THRESHOLD) + FloatToAnsiString(NoiseLimitR) + CrLfStr;
        set<AlarmBasic *>::iterator pBIt;
        for ( pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++ ) {
            AlarmBasic *element = *pBIt;
            if ( element && !element->Locked ) LocalString += (AnsiString)element->SaveSettings();
        }
        for ( unsigned j = 0; j < AnalogInList.size(); j++ ) {
            LocalString += AnalogInList[j]->SaveAISettings();
        }
        LocalString += CargoType->SaveSettings(0);
        LocalString += TabStr1 + KeyWord(C_ADJUST_VOLUME_OFFSET) + FloatToAnsiString(VolumeOffset) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_VOLUME_CORR_FACTOR) + FloatToAnsiString(VolCorrFactor) + CrLfStr;


        LocalString += KeyWord(C_PRO_END) + CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PROTank::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError   = true;
    int  ErrorLine = 0;
    int  Key;
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                RestoreSettingsWarning((AnsiString)"Tank " + Name + ":\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"Tank " + Name + ":\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_CT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case C_RADAR_THRESHOLD:
                NoiseLimitR = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_USEMEAS_DENS:
                UseMeasuredDensity = true;
                break;
            case C_ADJUST_LEVEL_OFFSET:
            case C_ADJUST_LEVEL_OFFSET1:
                LevelOffset = SettingsString->ReadDouble(ErrorLine);
                break;
            case C_ADJUST_TABLE_OFFSET:
                TableOffset = SettingsString->ReadDouble(ErrorLine);
                break;
            case C_ADJUST_VOLUME_OFFSET:
            case C_ADJUST_VOLUME_OFFSET1:
                VolumeOffset = SettingsString->ReadDouble(ErrorLine);
                break;
            case C_VOLUME_CORR_FACTOR:
                VolCorrFactor = SettingsString->ReadDouble(ErrorLine);
                break;
            case ID_AL_OVERFILL:
                if ( OverfillPtr ) {
                    OverfillPtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case ID_AL_HIGH_LEVEL:
                if ( HighLevelPtr ) {
                    HighLevelPtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case ID_AL_LOW_LEVEL:
                if ( LowLevelPtr ) {
                    LowLevelPtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case ID_AL_LOWLOW_LEVEL:
                if ( LoLoLevelPtr ) {
                    LoLoLevelPtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case ID_AL_LEVEL_CHANGE:
                if ( LevelChangeAPtr ) {
                    LevelChangeAPtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case C_AI_1728              :
            case C_AI_P906_0110         :
            case C_AI_P906_0111         :
            case C_AI_ATM_N_Ex          :
            case C_AI_ATM_Ex            :
            case C_AI_ATM_Ex_H          :
            case C_AI_ATM_N_Ex_0_1      :
            case C_AI_APT500		    :
            case C_AI_SPT900		    :
            case C_AI_Gen_4_20mA        :
            case C_AI_Radar_4_20mA      :
            case C_AI_Radar_Hart        :
            case C_AI_AirPurge          :
            case C_AI_MB_Press_mA       :
            case C_AI_MB_DiffPre_mA     :
            case C_AI_Float_4_20mA      :
            case C_AI_Pt100             :
            case C_AI_Pt1000            :
            case C_AI_TEMP_mA           :
            case C_AI_TEMP_AD590        :
            case C_AI_DIFF_PRESSURE_mA  :
            case C_AI_MetriTape         :
            case C_AI_HSH_LNG_Float     :
            case C_AI_WashTrackSensor   :
                {
                    int         AIIDNumber   = SettingsString->ReadInteger(ErrorLine);
                    AnalogInput *AnalogInPtr = (AnalogInput *)FindObject(AIIDNumber);
                    if ( AnalogInPtr ) {
                        AnalogInPtr->RestoreAISettings(SettingsString);
                    } else {
                        RestoreSettingsWarning((AnsiString)"Temperature " + Name + ":\nSensor Id " + AnsiString(AIIDNumber) + " is not found!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                    }
                }
                break;
            case C_CARGO_TYPE:
                CargoType->RestoreSettings(SettingsString);
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_PRO_END) );
    if ( Master && NoError ) {
        SendData(CMD_GENERIC_STATIC_DATA);
    }

    return (NoError);
}

AnsiString PROTank::ZeroSetTankPressureSensor(bool Local) {
    AnsiString TmpString;
    if ( PressurePtr ) {
        TmpString = PressurePtr->ZeroSetTankPressureSensor(Local);
    }
    return (TmpString);
}

AnsiString PROTank::ZeroSetLevelSensors(bool Local) {
    AnsiString TmpString;
    for ( unsigned i = 0; i < LevelPressures.size(); i++ ) {
        int ErrorStatus = LevelPressures[i]->AdjustSensorF(0.0, Local);
        if ( Local && ErrorStatus != E_NO_ERR ) {
            TmpString += Name + ": " + GetErrorMsg(ErrorStatus) + '\n';
        }
    }
    return (TmpString);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

bool PROTank::HasLCData(void) {
    return (PROSystemData::ReceiveWeightVolume && TSNElapsedTime(LCDataTime) < 90);
}


int PROTank::FindPROStatus(AnsiString &MyString) {
    int PROStatus1 = ST_OK;
    int PROStatus2 = ST_OK;
    if ( GetNumberOfHWAlarms() ) {
        PROStatus1 = ST_ERROR;
    }
    if ( PROStatus1 != ST_ERROR ) {
        switch ( State ) {
        case tSeaGoing :
        case tTankCleaning :
            PROStatus1 = ST_WARNING;
            break;
        default:
            break;
        }
        /*
        if (PROStatus2 > PROStatus1){
          PROStatus1 = PROStatus2;
        }
        */
    }
    if ( (PROStatus1 != ST_ERROR) && TemperaturePtr ) {
        PROStatus2 = TemperaturePtr->FindPROStatus(MyString);
        if ( PROStatus2 > PROStatus1 ) {
            PROStatus1 = PROStatus2;
        }

    }
    if ( (PROStatus1 != ST_ERROR) && PressurePtr ) {
        PROStatus2 = PressurePtr->FindPROStatus(MyString);
        if ( PROStatus2 > PROStatus1 ) {
            PROStatus1 = PROStatus2;
        }
    }
    if ( PROStatus1 != ST_ERROR ) {
        for ( unsigned i = 0; i < AnalogInList.size() && (PROStatus1 != ST_ERROR); i++ ) {
            PROStatus2 = AnalogInList[i]->FindPROStatus(MyString);
            if ( PROStatus2 > PROStatus1 ) {
                PROStatus1 = PROStatus2;
            }
        }
    }
    if ( PROStatus1 != ST_ERROR ) {
        bool                        AlActive = false;
        set<AlarmBasic *>::iterator pBIt;
        for ( pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++ ) {
            AlarmBasic *Element = *pBIt;
            if ( Element && (Element->State != AlarmBasic::AlIdle) ) AlActive = true;
        }
        if ( AlActive ) PROStatus2 = ST_ALARM;
        if ( PROStatus2 > PROStatus1 ) {
            PROStatus1 = PROStatus2;
        }
    }
    if ( PROStatus1 == ST_OK && HasLCData() ) {
        PROStatus1 = ST_LOADCALC;
    }
    MyString = FindStatusChar(PROStatus1);
    return (PROStatus1);
}

int PROTank::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    //IsNewData = true;
    //HasLevelSensors = true;
    switch ( ValueId ) {
    case SVT_VOLUME_SETPOINT:
        DecPnt = 1;
        Unit = PERCENT_UNIT;
        MyRetValue = StartVolPercent;
        break;
    case SVT_LC_WEIGHT:
    case SVT_WEIGHT:
        DecPnt = PROProjectInfo::DecimalPointWeight;
        Unit = WEIGHT_UNIT;
        if ( HasLCData() ) {
            // Handle the case where we only receive the volume
            if ( LCWeight ) {
                MyRetValue = LCWeight;
            } else {
                MyRetValue = Density * LCVolume;
            }
        } else if ( VolumeTab ) {
            if ( IsOnline ) {
                if ( HasLevelSensors && IsNewData ) {
                    MyRetValue = GetCorrectedWeight(Weight, Density);
                } else {
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                }
            } else {
                MyRetValue = GetCorrectedWeight(Weight, Density);
                Status = GETVAL_OFFLINE;
            }
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_VAP_WEIGHT:
        DecPnt = PROProjectInfo::DecimalPointWeight;
        Unit = WEIGHT_UNIT;
        if ( VolumeTab ) {
            if ( IsOnline ) {
                if ( HasLevelSensors && IsNewData ) {
                    MyRetValue = GetWeightFromGas();
                } else {
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                }
            } else {
                MyRetValue = GetWeightFromGas();
                Status = GETVAL_OFFLINE;
            }
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_GAS_WEIGHT:
        DecPnt = PROProjectInfo::DecimalPointWeight;
        Unit = WEIGHT_UNIT;
        if ( VolumeTab ) {
            if ( IsOnline ) {
                if ( HasLevelSensors && IsNewData ) {
                    MyRetValue = GetWeightFromLPG();
                } else {
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                }
            } else {
                MyRetValue = GetWeightFromLPG();
                Status = GETVAL_OFFLINE;
            }
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_LC_VOLUME:
    case SVT_VOLUME:
        DecPnt = PROProjectInfo::DecimalPointVolume;
        Unit = VOLUME_UNIT;
        if ( IsOnline ) {
            if ( HasLCData() ) {
                if ( IsNewData ) {
                    MyRetValue = LCVolume;
                } else {
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                }
            } else if ( VolumeTab ) {
                if ( IsNewData && HasLevelSensors ) {
                    MyRetValue = Volume;
                } else {
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                }
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        } else {
            MyRetValue = Volume;
            Status = GETVAL_OFFLINE;
        }
        break;
    case SVT_VOL_AT_REFTMP:
        DecPnt = PROProjectInfo::DecimalPointVolume;
        Unit = VOLUME_UNIT;
        if ( VolumeTab ) {
            if ( IsNewData && HasLevelSensors ) {
                MyRetValue = VolumeAtRefTmp();
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_VOLPERCENT:
        DecPnt = 1;
        Unit = PERCENT_UNIT;
        if ( IsOnline ) {
            if ( HasLCData() ) {
                if ( IsNewData ) {
                    if ( VolumeTab ) {
                        MyRetValue = LCVolume / VolumeTab->MaxY * 100.0;;
                    } else {
                        Status = GETVAL_NOT_AVAILABLE;
                    }
                } else {
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                }
            } else if ( VolumeTab ) {
                if ( IsNewData && HasLevelSensors ) {
                    MyRetValue = VolumePercent;
                } else {
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                }
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        } else {
            MyRetValue =  VolumePercent;
            Status = GETVAL_OFFLINE;
        }
        break;
    case SVT_CAPACITY:
        DecPnt = 1;
        Unit = VOLUME_UNIT;
        if ( VolumeTab ) {
            switch ( TankType ) {
            case TANKTYPE_CARGO:
                MyRetValue = VolumeTab->MaxY * 0.98;
                break;
            default:
                MyRetValue = VolumeTab->MaxY;
                break;
            }
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_CAPACITY98:
        DecPnt = 1;
        Unit = VOLUME_UNIT;
        if ( VolumeTab ) {
            MyRetValue = VolumeTab->MaxY * 0.98;
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_CAPACITY100:
        DecPnt = 1;
        Unit = VOLUME_UNIT;
        if ( VolumeTab ) {
            MyRetValue = VolumeTab->MaxY;
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_VOLUME_OFFSET:
        DecPnt = PROProjectInfo::DecimalPointVolume;
        Unit = VOLUME_UNIT;
        MyRetValue = VolumeOffset;
        break;
    case SVT_OFFSET_VOLUME :
        DecPnt = PROProjectInfo::DecimalPointVolume;
        Unit = VOLUME_UNIT;
        if ( VolumeTab ) {
            if ( IsNewData && HasLevelSensors ) {
                MyRetValue = Volume - VolumeOffset;
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_VOLUME_CORRECTION:
        DecPnt = 5;
        Unit = NO_UNIT;
        MyRetValue = VolCorrFactor;
        break;
    case SVT_OFFSET_VOL_AT_REF_TMP :
        DecPnt = 1;
        Unit = VOLUME_UNIT;
        if ( VolumeTab ) {
            if ( IsNewData && HasLevelSensors ) {
                MyRetValue = VolumeAtRefTmp();
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_OFFSET_WEIGHT :
        DecPnt = PROProjectInfo::DecimalPointWeight;
        Unit = WEIGHT_UNIT;
        if ( VolumeTab ) {
            float NetVolume = Volume - VolumeOffset;
            if ( HasLevelSensors && IsNewData ) {
                MyRetValue = GetCorrectedWeight(NetVolume * Density, Density);
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_SOUNDING:   // Sounding table!!!
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( IsOnline ) {
            if ( HasLevelSensors && IsNewData ) {
                if ( Sounding && NotEmptyTank ) {
                    MyRetValue = Sounding;
                } else {
                    Status = GETVAL_TANK_EMPTY;
                }
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            MyRetValue =  Sounding;
            Status = GETVAL_OFFLINE;
        }
        break;
    case SVT_LEVEL_FC:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( IsOnline ) {
            if ( HasLevelSensors && IsNewData ) {
                if ( LevelFC && NotEmptyTank ) {
                    MyRetValue = LevelFC;
                } else {
                    Status = GETVAL_TANK_EMPTY;
                }
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            MyRetValue =  LevelFC;
            Status = GETVAL_OFFLINE;
        }
        break;
    case SVT_LEVEL_REF:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( IsOnline ) {
            if ( HasLevelSensors && IsNewData ) {
                if ( LevelAtRef && NotEmptyTank ) {
                    MyRetValue = LevelAtRef;
                } else {
                    Status = GETVAL_TANK_EMPTY;
                }
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            MyRetValue =  LevelAtRef;
            Status = GETVAL_OFFLINE;
        }
        break;
    case SVT_LEVEL_PERCENT:
        DecPnt = 1;
        Unit = PERCENT_UNIT;
        if ( IsOnline ) {
            if ( HasLevelSensors && IsNewData ) {
                if ( LevelAtRef && NotEmptyTank ) {
                    if ( AdjustedDBU ) {
                        MyRetValue = LevelAtRef / AdjustedDBU * 100.0;
                    } else {
                        MyRetValue = 0.0;
                        Status = GETVAL_NO_DISPLAY;
                    }
                } else {
                    Status = GETVAL_TANK_EMPTY;
                }
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            if ( AdjustedDBU ) {
                MyRetValue = LevelAtRef / AdjustedDBU * 100.0;
            } else {
                MyRetValue = 0.0;
                Status = GETVAL_NO_DISPLAY;
            }
            Status = GETVAL_OFFLINE;
        }
        break;
    case SVT_LEVEL_SENSOR:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( IsOnline ) {
            if ( HasLevelSensors && IsNewData ) {
                if ( Level && NotEmptyTank ) {
                    MyRetValue = Level;
                } else {
                    Status = GETVAL_TANK_EMPTY;
                }
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            MyRetValue = Level;
            Status = GETVAL_OFFLINE;
        }
        break;
    case SVT_CUSTODY_TRF_LEVEL1    :
    case SVT_CUSTODY_TRF_LEVEL2    :
    case SVT_CUSTODY_TRF_LEVEL3    :
    case SVT_CUSTODY_TRF_LEVEL4    :
    case SVT_CUSTODY_TRF_LEVEL5    :
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( HasLevelSensors && IsNewData ) {
            if ( Level && NotEmptyTank ) {
                MyRetValue = LevelHistory[ValueId - SVT_CUSTODY_TRF_LEVEL1];
            } else {
                Status = GETVAL_TANK_EMPTY;
            }
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_CUSTODY_TRF_AVG_LEVEL :
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( HasLevelSensors && IsNewData ) {
            if ( Level && NotEmptyTank ) {
                float AvgLevel = 0.0;
                for ( int i = 0; i < LEVEL_HISTORY_ENTRIES; i++ ) {
                    AvgLevel += LevelHistory[i];
                }
                AvgLevel /= LEVEL_HISTORY_ENTRIES;
                MyRetValue = AvgLevel;
            } else {
                Status = GETVAL_TANK_EMPTY;
            }
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_CUSTODY_TRF_TRIM_CORR:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( TrimCorrectionTable ) {
            MyRetValue = TrimCorrectionTable->GetCorrection(Level, PROSystemData::TrimValue * PROProjectInfo::LengthBetweenPP);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_CUSTODY_TRF_LIST_CORR:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( ListCorrectionTable ) {
            MyRetValue = ListCorrectionTable->GetCorrection(Level, PROSystemData::ListValue * RAD_FACTOR);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_CUSTODY_TRF_CORR_LEVEL :
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( HasLevelSensors && IsNewData ) {
            if ( Level && NotEmptyTank ) {
                float TrimCorrection = 0.0;
                float ListCorrection = 0.0;
                if ( TrimCorrectionTable ) {
                    TrimCorrection = TrimCorrectionTable->GetCorrection(Level, PROSystemData::TrimValue * PROProjectInfo::LengthBetweenPP);
                }
                if ( ListCorrectionTable ) {
                    ListCorrection = ListCorrectionTable->GetCorrection(Level, PROSystemData::ListValue * RAD_FACTOR);
                }
                float tmpLevel = Level + TrimCorrection + ListCorrection;
                if ( tmpLevel < 0.0 ) {
                    tmpLevel = 0.0;
                }
                MyRetValue = tmpLevel;
            } else {
                Status = GETVAL_TANK_EMPTY;
            }
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;

    case SVT_ULLAGE_FC:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( DBU_IsConfigured || (TankType == TANKTYPE_CARGO) ) {
            if ( IsOnline ) {
                if ( IsNewData && HasLevelSensors ) {
                    MyRetValue = UllageFC;
                } else {
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                }
            } else {
                MyRetValue = UllageFC;
                Status = GETVAL_OFFLINE;
            }
        } else {
            Status = GETVAL_NO_DISPLAY;
        }
        break;

    case SVT_ULLAGE:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( DBU_IsConfigured || (TankType == TANKTYPE_CARGO) ) {
            if ( IsOnline ) {
                if ( IsNewData && HasLevelSensors ) {
                    MyRetValue = UllageRef;
                } else {
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                }
            } else {
                MyRetValue = UllageRef;
                Status = GETVAL_OFFLINE;
            }
        } else {
            Status = GETVAL_NO_DISPLAY;
        }
        break;
    case SVT_ULLAGE_UTI:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( DBU_IsConfigured || (TankType == TANKTYPE_CARGO) ) {
            if ( IsOnline ) {
                if ( IsNewData && HasLevelSensors ) {
                    MyRetValue = UllageRef + DVSnsToUTI;
                } else {
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                }
            } else {
                MyRetValue = UllageRef + DVSnsToUTI;
                Status = GETVAL_OFFLINE;
            }
        } else {
            Status = GETVAL_NO_DISPLAY;
        }
        break;
    case SVT_ULLAGE_RADAR:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        if ( DBU_IsConfigured || (TankType == TANKTYPE_CARGO) ) {
            if ( IsOnline ) {
                if ( IsNewData && HasLevelSensors ) {
                    MyRetValue = UllageAtSns;
                } else {
                    Status = GETVAL_FLOAT_NOT_LEGAL;
                }
            } else {
                MyRetValue = UllageAtSns;
                Status = GETVAL_OFFLINE;
            }
        } else {
            Status = GETVAL_NO_DISPLAY;
        }
        break;
    case SVT_LEVEL_OFFSET:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        MyRetValue = LevelOffset;
        break;
    case SVT_TABLE_OFFSET:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        MyRetValue = TableOffset;
        break;
    case SVT_DISTANCE_SNS_UTI:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        MyRetValue = DVSnsToUTI;
        break;
    case SVT_LOADRATE:
        DecPnt = 1;
        Unit = LOADRATE_UNIT;
        if ( IsNewData ) {
            if ( LoadRate ) {} else {
                Status = GETVAL_NO_DISPLAY;
            }
            MyRetValue = LoadRate;
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_COMP_DNS:
        DecPnt = 4;
        Unit = DENSITY_UNIT;
        // Get the temperature from the PROTemp object if we have one!!
        {
            float LocTemp;
            if ( TemperaturePtr ) {
                if ( TemperaturePtr->HasTemp ) {
                    LocTemp = TemperaturePtr->GetTemperature();
                } else {
                    LocTemp = CargoType->RefTmp1;   // Default to ref temp 1 if temp failure
                }
            } else {
                LocTemp = PROSystemData::SeaWaterTemp;
            }
            MyRetValue = CargoType->Comp_Density(LocTemp);
        }
        break;
    case SVT_MEAS_DNS:
        MyRetValue  = MeasuredDns;
        DecPnt      = 4;
        Unit        = DENSITY_UNIT;
        if ( UseMeasuredDensity ) {
            if ( IsNewData ) {
                Status = GETVAL_MEASURED_DENSITY_ON;
            } else {
                Status = GETVAL_FLOAT_NOT_LEGAL;
            }
        } else {
            Status      = GETVAL_MEASURED_DENSITY_OFF;
        }
        break;
    case SVT_MEAS_DNS_RAW:
        MyRetValue = MeasuredDns;
        DecPnt = 4;
        Unit = DENSITY_UNIT;
        if ( IsNewData ) {
            if ( !MeasuredDns ) {
                Status = GETVAL_NOT_AVAILABLE;
            }
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_MEASURED_API :
        if ( !HasMeasuredDensity ) {
            Status = GETVAL_NOT_AVAILABLE;
        }
        MyRetValue = CargoType->MeasDns_to_API(Temperature, Density);
        DecPnt = 4;
        Unit = NO_UNIT;
        break;
    case SVT_VCF_AT_TEMP :
        Status = CargoType->GetVCF_AtTemp(Density, Temperature, MyRetValue,  DecPnt, Unit);
        break;
    case SVT_LC_DENSITY:
    case SVT_DENSITY:
        DecPnt = 4;
        Unit = DENSITY_UNIT;
        MyRetValue = Density;
        break;
    case SVT_BASIC_TYPE :
    case SVT_CARGO_TYPE :
    case SVT_REF_DNS1   :
    case SVT_REF_DNS2   :
    case SVT_REF_TMP1   :
    case SVT_REF_TMP2   :
    case SVT_COEFF      :
    case SVT_API        :
    case SVT_VCF        :
    case SVT_MOLMASS    :
    case SVT_VISCOSITY  :
    case SVT_CARGO_COLOR:
        Status = CargoType->GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    case SVT_HIHI_LEVEL_ENABLE  :
    case SVT_HI_LEVEL_ENABLE    :
    case SVT_LO_LEVEL_ENABLE    :
    case SVT_LOLO_LEVEL_ENABLE  :
    case SVT_LEV_CHANGE_ENA     :
    case SVT_HIHI_VOLPCNT_LIM   :
    case SVT_HI_LEVEL_LIMIT     :
    case SVT_LO_LEVEL_LIMIT     :
    case SVT_LOLO_LEVEL_LIMIT   :
    case SVT_LEV_CHANGE_LIM     :
    case SVT_HI_VOLPCNT_LIM     :
    case SVT_HI_VOLUME_LIM      :
    case SVT_HI_WEIGHT_LIM      :
    case SVT_HI_ULLAGE_LIM      :
    case SVT_HI_LEVEL_LIM       :
    case SVT_LO_VOLPCNT_LIM     :
    case SVT_LO_VOLUME_LIM      :
    case SVT_LO_WEIGHT_LIM      :
    case SVT_LO_ULLAGE_LIM      :
    case SVT_LO_LEVEL_LIM       :
    case SVT_LOLO_VOLPCNT_LIM   :
    case SVT_LOLO_VOLUME_LIM    :
    case SVT_LOLO_WEIGHT_LIM    :
    case SVT_LOLO_ULLAGE_LIM    :
    case SVT_LOLO_LEVEL_LIM     :
    case SVT_HIHI_VOLPCNT_STATE :
    case SVT_HI_VOLPCNT_STATE   :
    case SVT_LO_VOLPCNT_STATE   :
    case SVT_LOLO_VOLPCNT_STATE :
    case SVT_LEV_CHANGE_STATE   :
    case SVT_OVERFILL_VALUE     :
    case SVT_HI_LEVEL_VALUE     :
    case SVT_LO_LEVEL_VALUE     :
    case SVT_LOLO_LEVEL_VALUE   :
    case SVT_LEV_CHANGE_VALUE   :
        {
            int        tmpValKey;
            AlarmBasic *tmpPtr;
            switch ( ValueId ) {
            case SVT_HIHI_LEVEL_ENABLE:
                tmpValKey = SVT_AL_ENABLE;
                tmpPtr = (AlarmBasic *)OverfillPtr;
                break;
            case SVT_HI_LEVEL_ENABLE:
                tmpValKey = SVT_AL_ENABLE;
                tmpPtr = (AlarmBasic *)HighLevelPtr;
                break;
            case SVT_LO_LEVEL_ENABLE:
                tmpValKey = SVT_AL_ENABLE;
                tmpPtr = (AlarmBasic *)LowLevelPtr;
                break;
            case SVT_LOLO_LEVEL_ENABLE:
                tmpValKey = SVT_AL_ENABLE;
                tmpPtr = (AlarmBasic *)LoLoLevelPtr;
                break;
            case SVT_LEV_CHANGE_ENA:
                tmpValKey = SVT_AL_ENABLE;
                tmpPtr = (AlarmBasic *)LevelChangeAPtr;
                break;
            case SVT_HIHI_VOLPCNT_LIM:
                tmpValKey = SVT_AL_LIMIT;
                tmpPtr = (AlarmBasic *)OverfillPtr;
                break;
            case SVT_HI_LEVEL_LIMIT:
                tmpValKey = SVT_HI_VOLPCNT_LIM;
                tmpPtr = (AlarmBasic *)HighLevelPtr;
                break;
            case SVT_LO_LEVEL_LIMIT:
                tmpValKey = SVT_LO_VOLPCNT_LIM;
                tmpPtr = (AlarmBasic *)LowLevelPtr;
                break;
            case SVT_LOLO_LEVEL_LIMIT:
                tmpValKey = SVT_LOLO_VOLPCNT_LIM;
                tmpPtr = (AlarmBasic *)LoLoLevelPtr;
                break;
            case SVT_LEV_CHANGE_LIM:
                tmpValKey = SVT_AL_LIMIT;
                tmpPtr = (AlarmBasic *)LevelChangeAPtr;
                break;
            case SVT_HI_VOLPCNT_LIM :
            case SVT_HI_VOLUME_LIM  :
            case SVT_HI_WEIGHT_LIM  :
            case SVT_HI_ULLAGE_LIM  :
            case SVT_HI_LEVEL_LIM   :
                tmpValKey = ValueId;
                tmpPtr = (AlarmBasic *)HighLevelPtr;
                break;
            case SVT_LO_VOLPCNT_LIM :
            case SVT_LO_VOLUME_LIM  :
            case SVT_LO_WEIGHT_LIM  :
            case SVT_LO_ULLAGE_LIM  :
            case SVT_LO_LEVEL_LIM   :
                tmpValKey = ValueId;
                tmpPtr = (AlarmBasic *)LowLevelPtr;
                break;
            case SVT_LOLO_VOLPCNT_LIM :
            case SVT_LOLO_VOLUME_LIM  :
            case SVT_LOLO_WEIGHT_LIM  :
            case SVT_LOLO_ULLAGE_LIM  :
            case SVT_LOLO_LEVEL_LIM   :
                tmpValKey = ValueId;
                tmpPtr = (AlarmBasic *)LoLoLevelPtr;
                break;
            case SVT_HIHI_VOLPCNT_STATE:
                tmpValKey = SVT_AL_STATE;
                tmpPtr = (AlarmBasic *)OverfillPtr;
                break;
            case SVT_HI_VOLPCNT_STATE:
                tmpValKey = SVT_AL_STATE;
                tmpPtr = (AlarmBasic *)HighLevelPtr;
                break;
            case SVT_LO_VOLPCNT_STATE:
                tmpValKey = SVT_AL_STATE;
                tmpPtr = (AlarmBasic *)LowLevelPtr;
                break;
            case SVT_LOLO_VOLPCNT_STATE:
                tmpValKey = SVT_AL_STATE;
                tmpPtr = (AlarmBasic *)LoLoLevelPtr;
                break;
            case SVT_LEV_CHANGE_STATE:
                tmpValKey = SVT_AL_STATE;
                tmpPtr = (AlarmBasic *)LevelChangeAPtr;
                break;
            case SVT_OVERFILL_VALUE:
                tmpValKey = SVT_AL_VALUE;
                tmpPtr = (AlarmBasic *)OverfillPtr;
                break;
            case SVT_HI_LEVEL_VALUE:
                tmpValKey = SVT_AL_VALUE;
                tmpPtr = (AlarmBasic *)HighLevelPtr;
                break;
            case SVT_LO_LEVEL_VALUE:
                tmpValKey = SVT_AL_VALUE;
                tmpPtr = (AlarmBasic *)LowLevelPtr;
                break;
            case SVT_LOLO_LEVEL_VALUE:
                tmpValKey = SVT_AL_VALUE;
                tmpPtr = (AlarmBasic *)LoLoLevelPtr;
                break;
            case SVT_LEV_CHANGE_VALUE:
                tmpValKey = SVT_AL_VALUE;
                tmpPtr = (AlarmBasic *)LevelChangeAPtr;
                break;

            }
            if ( tmpPtr ) {
                Status = tmpPtr->GetValue(tmpValKey, 0, MyRetValue,  DecPnt, Unit);
            } else {
                Status = GETVAL_NO_DISPLAY;
            }
        }
        break;
    case SVT_TEMP               :
    case SVT_VAPOR_TEMP         :
    case SVT_HI_TEMP_LIMIT      :
    case SVT_LO_TEMP_LIMIT      :
    case SVT_HI_TEMP_VALUE      :
    case SVT_LO_TEMP_VALUE      :
    case SVT_HI_TEMP_STATE      :
    case SVT_LO_TEMP_STATE      :
    case SVT_HI_TEMP_ENABLE     :
    case SVT_LO_TEMP_ENABLE     :
    case SVT_HI_BOT_TEMP_ENABLE :
    case SVT_LO_BOT_TEMP_ENABLE :
    case SVT_HI_BOT_TEMP_LIMIT  :
    case SVT_LO_BOT_TEMP_LIMIT  :
    case SVT_HI_BOT_TEMP_VALUE  :
    case SVT_LO_BOT_TEMP_VALUE  :
    case SVT_HI_BOT_TEMP_STATE  :
    case SVT_LO_BOT_TEMP_STATE  :
        if ( TemperaturePtr ) {
            Status = TemperaturePtr->GetValue(ValueId, 0, MyRetValue, DecPnt, Unit);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_HART_MA :
    case SVT_HART_RADAR :
    case SVT_HART_STATUS :
    case SVT_HART_OPEN_LOOP :
    case SVT_HART_SHORT_CIRCUIT :
        if ( !RadarSensors.empty() ) {
            AIRadarSensorHart *tmpPtr = (AIRadarSensorHart *)RadarSensors[0];
            Status = tmpPtr->GetValue(ValueId, 0, MyRetValue, DecPnt, Unit);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_AP_TPRESS_SNS_FAIL    :
    case SVT_AP_TANK_PRESSURE_MB :
        if ( !tankPressures.empty() ) {
            Status = tankPressures[0]->GetValue(ValueId, 0, MyRetValue, DecPnt, Unit);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_AP_LPRESS_SNS_FAIL    :
    case SVT_AP_LEVEL_PRESSURE_MB  :
    case SVT_AP_LEVEL_PRESSURE_MH2O:
        if ( !LevelPressures.empty() ) {
            Status = LevelPressures[0]->GetValue(ValueId, 0, MyRetValue, DecPnt, Unit);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_BP1 :
    case SVT_BP2 :
    case SVT_BP3 :
    case SVT_BP_OFFSET1:
    case SVT_BP_OFFSET2:
    case SVT_BP_OFFSET3:
    case SVT_BP_GAIN1 :
    case SVT_BP_GAIN2 :
    case SVT_BP_GAIN3 :
    case SVT_UP :
    case SVT_MP :
    case SVT_BP :
    case SVT_TP :
    case SVT_BP_OFFSET :
    case SVT_MP_OFFSET :
    case SVT_UP_OFFSET :
    case SVT_TP_OFFSET :
    case SVT_BP_GAIN :
    case SVT_MP_GAIN :
    case SVT_UP_GAIN :
    case SVT_TP_GAIN :
    case SVT_BP_ENABLE1:
    case SVT_BP_ENABLE2:
    case SVT_BP_ENABLE3:
    case SVT_BP_ENABLE :
    case SVT_MP_ENABLE :
    case SVT_UP_ENABLE :
    case SVT_TP_ENABLE :
        {
            Unit = PRESSURE_UNIT1;
            DecPnt = 3;
            AnalogInput *SnsPtr = NULL;
            switch ( ValueId ) {
            case SVT_BP :
            case SVT_BP_GAIN :
            case SVT_BP_OFFSET :
            case SVT_BP_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_BOTTOM);
                break;
            case SVT_MP :
            case SVT_MP_GAIN :
            case SVT_MP_OFFSET :
            case SVT_MP_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_MIDDLE);
                break;
            case SVT_UP :
            case SVT_UP_GAIN :
            case SVT_UP_OFFSET :
            case SVT_UP_ENABLE :
                SnsPtr = FindAnalogInput(C_AI_LOC_UPPER);
                break;
            case SVT_TP :
            case SVT_TP_GAIN :
            case SVT_TP_OFFSET :
            case SVT_TP_ENABLE :
                Unit = PRESSURE_UNIT2;
                SnsPtr = FindAllAnalogInput(C_AI_LOC_VAPOUR, AI_SENSOR_PRESS);
                if ( !SnsPtr ) {
                    SnsPtr = FindAllAnalogInput(C_AI_LOC_DECK, AI_SENSOR_PRESS);
                }
                break;
            case SVT_BP1 :
            case SVT_BP_GAIN1 :
            case SVT_BP_OFFSET1 :
            case SVT_BP_ENABLE1:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY1);
                break;
            case SVT_BP2 :
            case SVT_BP_GAIN2 :
            case SVT_BP_OFFSET2 :
            case SVT_BP_ENABLE2:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY2);
                break;
            case SVT_BP3 :
            case SVT_BP_GAIN3 :
            case SVT_BP_OFFSET3 :
            case SVT_BP_ENABLE3:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY3);
                break;
            }
            int SnsValId = SVT_NOT_DEFINED;
            switch ( ValueId ) {
            case SVT_BP_GAIN1 :
            case SVT_BP_GAIN2 :
            case SVT_BP_GAIN3 :
            case SVT_BP_GAIN :
            case SVT_MP_GAIN :
            case SVT_UP_GAIN :
            case SVT_TP_GAIN :
                SnsValId = SVT_AI_GAIN;
                break;
            case SVT_BP_OFFSET1 :
            case SVT_BP_OFFSET2 :
            case SVT_BP_OFFSET3 :
            case SVT_BP_OFFSET :
            case SVT_MP_OFFSET :
            case SVT_UP_OFFSET :
            case SVT_TP_OFFSET :
                SnsValId = SVT_AI_OFFSET;
                break;
            case SVT_BP1 :
            case SVT_BP2 :
            case SVT_BP3 :
            case SVT_BP :
            case SVT_MP :
            case SVT_UP :
            case SVT_TP :
                SnsValId = SVT_AI_CALC_VAL;
                break;
            case SVT_BP_ENABLE1:
            case SVT_BP_ENABLE2:
            case SVT_BP_ENABLE3:
            case SVT_BP_ENABLE :
            case SVT_MP_ENABLE :
            case SVT_UP_ENABLE :
            case SVT_TP_ENABLE :
                SnsValId = SVT_AI_ENABLE;
                break;
            }
            if ( SnsPtr ) {
                Status = SnsPtr->GetValue(SnsValId, Index, MyRetValue, DecPnt, Unit);
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_TT :
    case SVT_T1 :
    case SVT_T2 :
    case SVT_T3 :
    case SVT_T4 :
    case SVT_T5 :
    case SVT_T1_OFFSET :
    case SVT_T2_OFFSET :
    case SVT_T5_OFFSET :
    case SVT_T3_OFFSET :
    case SVT_T4_OFFSET :
    case SVT_TT_OFFSET :
    case SVT_T1_GAIN :
    case SVT_T2_GAIN :
    case SVT_T5_GAIN :
    case SVT_T3_GAIN :
    case SVT_T4_GAIN :
    case SVT_TT_GAIN :
    case SVT_T1_ENABLE :
    case SVT_T2_ENABLE :
    case SVT_T5_ENABLE :
    case SVT_T3_ENABLE :
    case SVT_T4_ENABLE :
    case SVT_TT_ENABLE :
        {
            AnalogInput *SnsPtr = NULL;
            switch ( ValueId ) {
            case SVT_T1 :
            case SVT_T1_GAIN :
            case SVT_T1_OFFSET :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP1, AI_SENSOR_TEMP);
                break;
            case SVT_T2 :
            case SVT_T2_GAIN :
            case SVT_T2_OFFSET :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP2, AI_SENSOR_TEMP);
                break;
            case SVT_T3 :
            case SVT_T3_GAIN :
            case SVT_T3_OFFSET :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP3, AI_SENSOR_TEMP);
                break;
            case SVT_T4 :
            case SVT_T4_GAIN :
            case SVT_T4_OFFSET :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP4, AI_SENSOR_TEMP);
                break;
            case SVT_T5 :
            case SVT_T5_GAIN :
            case SVT_T5_OFFSET :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP5, AI_SENSOR_TEMP);
                break;
            case SVT_TT :
            case SVT_TT_GAIN :
            case SVT_TT_OFFSET :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_VAPOUR, AI_SENSOR_TEMP);
                if ( !SnsPtr ) {
                    SnsPtr = FindAllAnalogInput(C_AI_LOC_DECK, AI_SENSOR_TEMP);
                    if ( !SnsPtr ) {
                        SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP6, AI_SENSOR_TEMP);
                    }
                }
                break;
            }
            int SnsValId = SVT_NOT_DEFINED;
            switch ( ValueId ) {
            case SVT_T1_GAIN :
            case SVT_T2_GAIN :
            case SVT_T5_GAIN :
            case SVT_T3_GAIN :
            case SVT_T4_GAIN :
            case SVT_TT_GAIN :
                SnsValId = SVT_AI_GAIN;
                break;
            case SVT_T1_OFFSET :
            case SVT_T2_OFFSET :
            case SVT_T5_OFFSET :
            case SVT_T3_OFFSET :
            case SVT_T4_OFFSET :
            case SVT_TT_OFFSET :
                SnsValId = SVT_AI_OFFSET;
                break;
            case SVT_T1 :
            case SVT_T2 :
            case SVT_T5 :
            case SVT_T3 :
            case SVT_T4 :
            case SVT_TT :
                SnsValId = SVT_AI_CALC_VAL;
                break;
            case SVT_T1_ENABLE :
            case SVT_T2_ENABLE :
            case SVT_T5_ENABLE :
            case SVT_T3_ENABLE :
            case SVT_T4_ENABLE :
            case SVT_TP_ENABLE :
                SnsValId = SVT_AI_ENABLE;
                break;

            }
            if ( SnsPtr ) {
                if ( SnsValId == SVT_AI_CALC_VAL ) {
                    if ( !SnsPtr->CanCalculate() || !SnsPtr->ResultOK ) {
                        DecPnt = 1;
                        Unit   = TEMP_UNIT;
                        Status = GETVAL_FLOAT_NOT_LEGAL;
                    } else {
                        Status = SnsPtr->GetValue(SnsValId, Index, MyRetValue,  DecPnt, Unit);
                    }
                } else {
                    Status = SnsPtr->GetValue(SnsValId, Index, MyRetValue,  DecPnt, Unit);
                }
            } else {
                DecPnt     = 1;
                Unit       = TEMP_UNIT;
                Status     = GETVAL_NOT_AVAILABLE;
            }
        }
        break;

    case SVT_PRESSURE :
    case SVT_HI_PRESS_LIMIT         :
    case SVT_LO_PRESS_LIMIT         :
    case SVT_HI_PRESS_VAC_LIMIT     :
    case SVT_LO_PRESS_VAC_LIMIT     :
    case SVT_HI_VAP_RET_LIMIT       :
    case SVT_LO_VAP_RET_LIMIT       :
    case SVT_HI_IGP_LIMIT           :
    case SVT_LO_IGP_LIMIT           :
    case SVT_XTRA_HI_PRESS_LIMIT1   :
    case SVT_XTRA_LO_PRESS_LIMIT1   :
    case SVT_XTRA_HI_PRESS_LIMIT2   :
    case SVT_XTRA_LO_PRESS_LIMIT2   :
    case SVT_HI_PRESS_STATE         :
    case SVT_LO_PRESS_STATE         :
    case SVT_HI_PRESS_VAC_STATE     :
    case SVT_LO_PRESS_VAC_STATE     :
    case SVT_HI_VAP_RET_STATE       :
    case SVT_LO_VAP_RET_STATE       :
    case SVT_HI_IGP_STATE           :
    case SVT_LO_IGP_STATE           :
    case SVT_XTRA_HI_PRESS_STATE1   :
    case SVT_XTRA_LO_PRESS_STATE1   :
    case SVT_XTRA_HI_PRESS_STATE2   :
    case SVT_XTRA_LO_PRESS_STATE2   :
    case SVT_HI_PRESS_VALUE         :
    case SVT_LO_PRESS_VALUE         :
    case SVT_HI_PRESS_VAC_VALUE     :
    case SVT_LO_PRESS_VAC_VALUE     :
    case SVT_HI_IGP_VALUE           :
    case SVT_LO_IGP_VALUE           :
    case SVT_HI_VAP_RET_VALUE       :
    case SVT_LO_VAP_RET_VALUE       :
    case SVT_XTRA_HI_PRESS_VALUE1   :
    case SVT_XTRA_LO_PRESS_VALUE1   :
    case SVT_XTRA_HI_PRESS_VALUE2   :
    case SVT_XTRA_LO_PRESS_VALUE2   :
    case SVT_HI_PRESS_ENABLE        :
    case SVT_LO_PRESS_ENABLE        :
    case SVT_HI_PRESS_VAC_ENABLE    :
    case SVT_LO_PRESS_VAC_ENABLE    :
    case SVT_HI_IGP_ENABLE          :
    case SVT_LO_IGP_ENABLE          :
    case SVT_HI_VAP_RET_ENABLE      :
    case SVT_LO_VAP_RET_ENABLE      :
    case SVT_XTRA_HI_PRESS_ENABLE1  :
    case SVT_XTRA_LO_PRESS_ENABLE1  :
    case SVT_XTRA_HI_PRESS_ENABLE2  :
    case SVT_XTRA_LO_PRESS_ENABLE2  :
    case SVT_AL_LIMIT_TYPE_PRESS    :
        if ( PressurePtr ) {
            Status = PressurePtr->GetValue(ValueId, 0, MyRetValue, DecPnt, Unit);
        } else {
            // Set a decimal point even when not used
            switch ( ValueId ) {
            case SVT_PRESSURE :
            case SVT_HI_PRESS_ENABLE        :
            case SVT_LO_PRESS_ENABLE        :
            case SVT_HI_PRESS_VAC_ENABLE    :
            case SVT_LO_PRESS_VAC_ENABLE    :
            case SVT_HI_IGP_ENABLE          :
            case SVT_LO_IGP_ENABLE          :
            case SVT_HI_VAP_RET_ENABLE      :
            case SVT_LO_VAP_RET_ENABLE      :
            case SVT_XTRA_HI_PRESS_ENABLE1  :
            case SVT_XTRA_LO_PRESS_ENABLE1  :
            case SVT_XTRA_HI_PRESS_ENABLE2  :
            case SVT_XTRA_LO_PRESS_ENABLE2  :
            case SVT_HI_PRESS_STATE         :
            case SVT_LO_PRESS_STATE         :
            case SVT_HI_PRESS_VAC_STATE     :
            case SVT_LO_PRESS_VAC_STATE     :
            case SVT_HI_IGP_STATE           :
            case SVT_LO_IGP_STATE           :
            case SVT_HI_VAP_RET_STATE       :
            case SVT_LO_VAP_RET_STATE       :
            case SVT_XTRA_HI_PRESS_STATE1   :
            case SVT_XTRA_LO_PRESS_STATE1   :
            case SVT_XTRA_HI_PRESS_STATE2   :
            case SVT_XTRA_LO_PRESS_STATE2   :
                DecPnt = 0;
                Unit = NO_UNIT;
                break;
            case SVT_HI_PRESS_LIMIT         :
            case SVT_LO_PRESS_LIMIT         :
            case SVT_HI_PRESS_VAC_LIMIT     :
            case SVT_LO_PRESS_VAC_LIMIT     :
            case SVT_HI_IGP_LIMIT           :
            case SVT_LO_IGP_LIMIT           :
            case SVT_HI_VAP_RET_LIMIT       :
            case SVT_LO_VAP_RET_LIMIT       :
            case SVT_XTRA_HI_PRESS_LIMIT1   :
            case SVT_XTRA_LO_PRESS_LIMIT1   :
            case SVT_XTRA_HI_PRESS_LIMIT2   :
            case SVT_XTRA_LO_PRESS_LIMIT2   :
            case SVT_HI_PRESS_VALUE         :
            case SVT_LO_PRESS_VALUE         :
            case SVT_HI_PRESS_VAC_VALUE     :
            case SVT_LO_PRESS_VAC_VALUE     :
            case SVT_HI_IGP_VALUE           :
            case SVT_LO_IGP_VALUE           :
            case SVT_HI_VAP_RET_VALUE       :
            case SVT_LO_VAP_RET_VALUE       :
            case SVT_XTRA_HI_PRESS_VALUE1   :
            case SVT_XTRA_LO_PRESS_VALUE1   :
            case SVT_XTRA_HI_PRESS_VALUE2   :
            case SVT_XTRA_LO_PRESS_VALUE2   :
                DecPnt = 1;
                Unit = PRESSURE_UNIT1;
                break;
            }
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_LEVEL_PRESSURE:
        if ( HasLevelSensors && IsNewData ) {
            if ( Density ) {
                MyRetValue = Level / Density;
            } else {
                MyRetValue = Level;
            }
            DecPnt = 3;
            Unit = PRESSURE_UNIT2;
        } else {
            Status = GETVAL_HW_ALARM;
        }
        break;
    case SVT_LINE_PRESSURE:
        if ( LPressurePtr ) {
            Status = PressurePtr->GetValue(ValueId, 0, MyRetValue, DecPnt, Unit);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_RADAR_THRESHOLD:
        DecPnt = 3;
        Unit = LENGTH_UNIT;
        MyRetValue = NoiseLimitR;
        break;
    case SVT_MB_MA_PRESSURE:
        // Assume only one Modbus level sensor for one tank
        if ( !LevelPressures.empty() ) {
            Status = LevelPressures[0]->GetValue(SVT_AI_CALC_VAL, 0, MyRetValue, DecPnt, Unit);
        }
        break;
    default:
        Status = PROXRefObject::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}

int PROTank::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_REMAINING_TIME :
        if ( IsNewData && HasLevelSensors ) {
            if ( RemainingTime ) {
                int  Hour = (int)RemainingTime;
                int  Min  = (int)((RemainingTime - Hour) * 60.0);
                char Buf[BUF_SIZE];
                sprintf(Buf, "%i:%02i", Hour, Min);
                MyString = Buf;
            } else {
                MyString = "";
            }
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_FINISH_TIME :
        if ( IsNewData && HasLevelSensors ) {
            if ( RemainingTime ) {
                int          Hour  = (int)RemainingTime;
                int          Min   = (int)((RemainingTime - Hour) * 60);
                const time_t t     = time(NULL);
                struct tm    *tBuf;
                tBuf = localtime(&t);
                Min += tBuf->tm_min;
                if ( Min >= 60 ) Min -= 60,Hour++;
                Hour += tBuf->tm_hour;
                if ( Hour >= 24 ) Hour -= 24;
                char Buf[BUF_SIZE];
                sprintf(Buf, "%i:%02i", Hour, Min);
                MyString = Buf;
            } else {
                MyString = "";
            }
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_PRO_STATUS:
        FindPROStatus(MyString);
        break;
    case SVT_COLOUR :
    case SVT_BASIC_TYPE_NAME:
    case SVT_CARGO_TYPE_NAME:
        Status = CargoType->GetStringValue(ValueId, Index, MyString);
        break;
    case SVT_INTERFACE:
        switch ( HasWater ) {
        case WSENSOR_NO_SENSOR:
            MyString = FindDictionaryWord(L_WORD851); break;
        case WSENSOR_CARGO :
            MyString = FindDictionaryWord(L_WORD896); break; // Oil
        case WSENSOR_WATER :
            MyString = FindDictionaryWord(L_WORD46); break;
        case WSENSOR_EMPTY :
            MyString = FindDictionaryWord(L_WORD473); break;
        case WSENSOR_LOW_LEVEL:
            MyString = FindDictionaryWord(L_WORD518); break;
        case WSENSOR_DISABLE :
            MyString = FindDictionaryWord(L_WORD852); break;
        case WSENSOR_FAILURE :
            MyString = FindDictionaryWord(L_WORD528); break;
        }
        break;
    case SVT_USE_MSRD_DNS:
        if ( UseMeasuredDensity ) {
            MyString = FindDictionaryWord(L_WORD1);
        } else {
            MyString = FindDictionaryWord(L_WORD2);
        }
        break;
    case SVT_TANK_TYPE:
        switch ( TankType ) {
        case TANKTYPE_CARGO :
            MyString = FindDictionaryWord(L_WORD870); break;
        case TANKTYPE_BALLAST :
            MyString = FindDictionaryWord(L_WORD871); break;
        case TANKTYPE_VOIDSPACE :
            MyString = FindDictionaryWord(L_WORD872); break;
        case TANKTYPE_HFO :
            MyString = FindDictionaryWord(L_WORD873); break;
        case TANKTYPE_DO :
            MyString = FindDictionaryWord(L_WORD874); break;
        case TANKTYPE_LUB :
            MyString = FindDictionaryWord(L_WORD875); break;
        case TANKTYPE_FW :
            MyString = FindDictionaryWord(L_WORD876); break;
        case TANKTYPE_MISC :
            MyString = FindDictionaryWord(L_WORD877); break;
        }
        break;
    case SVT_AL_LIMIT_TYPE_PRESS :
        if ( PressurePtr ) {
            Status = PressurePtr->GetStringValue(ValueId, Index, MyString);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_BP_SERIAL_NO :
    case SVT_BP_SERIAL_NO1:
    case SVT_BP_SERIAL_NO2:
    case SVT_BP_SERIAL_NO3:
    case SVT_MP_SERIAL_NO :
    case SVT_UP_SERIAL_NO :
    case SVT_TP_SERIAL_NO :
    case SVT_BP_ENABLE1_TEXT:
    case SVT_BP_ENABLE2_TEXT:
    case SVT_BP_ENABLE3_TEXT:
    case SVT_BP_ENABLE_TEXT :
    case SVT_MP_ENABLE_TEXT :
    case SVT_UP_ENABLE_TEXT :
    case SVT_TP_ENABLE_TEXT :
        {
            AnalogInput *SnsPtr = NULL;
            switch ( ValueId ) {
            case SVT_BP_ENABLE_TEXT :
                SnsPtr = FindAnalogInput(C_AI_LOC_BOTTOM);
                break;
            case SVT_BP_SERIAL_NO :
                SnsPtr = FindAnalogInput(C_AI_LOC_BOTTOM);
                break;
            case SVT_MP_ENABLE_TEXT :
            case SVT_MP_SERIAL_NO :
                SnsPtr = FindAnalogInput(C_AI_LOC_MIDDLE);
                break;
            case SVT_UP_ENABLE_TEXT :
            case SVT_UP_SERIAL_NO :
                SnsPtr = FindAnalogInput(C_AI_LOC_UPPER);
                break;
            case SVT_TP_SERIAL_NO :
            case SVT_TP_ENABLE_TEXT :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_VAPOUR, AI_SENSOR_PRESS);
                if ( !SnsPtr ) {
                    SnsPtr = FindAllAnalogInput(C_AI_LOC_DECK, AI_SENSOR_PRESS);
                }
                break;
            case SVT_BP_ENABLE1_TEXT:
            case SVT_BP_SERIAL_NO1:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY1);
                break;
            case SVT_BP_ENABLE2_TEXT:
            case SVT_BP_SERIAL_NO2:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY2);
                break;
            case SVT_BP_ENABLE3_TEXT:
            case SVT_BP_SERIAL_NO3:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY3);
                break;
            }
            int SnsValId = SVT_NOT_DEFINED;
            switch ( ValueId ) {
            case SVT_BP_ENABLE1_TEXT:
            case SVT_BP_ENABLE2_TEXT:
            case SVT_BP_ENABLE3_TEXT:
            case SVT_BP_ENABLE_TEXT :
            case SVT_MP_ENABLE_TEXT :
            case SVT_UP_ENABLE_TEXT :
            case SVT_TP_ENABLE_TEXT :
                SnsValId = SVT_AI_ENABLE_TEXT;
                break;

            case SVT_BP_SERIAL_NO :
            case SVT_BP_SERIAL_NO1:
            case SVT_BP_SERIAL_NO2:
            case SVT_BP_SERIAL_NO3:
            case SVT_MP_SERIAL_NO :
            case SVT_UP_SERIAL_NO :
            case SVT_TP_SERIAL_NO :
                SnsValId = SVT_AI_SERIAL_NUMBER;
                break;
            }
            if ( SnsPtr ) {
				Status = SnsPtr->GetStringValue(SnsValId, Index, MyString);
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_AP_LPRESS_SNS_FAIL     :
    case SVT_AP_TPRESS_SNS_FAIL     :
        if ( !LevelPressures.empty() ) {
			Status = LevelPressures[0]->GetStringValue(ValueId,  Index, MyString);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
    default:
        Status = PROXRefObject::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int PROTank::GetBitValue(int ValueId, int Index, bool &MyBit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_HI_PRESS_ENABLE        :
    case SVT_LO_PRESS_ENABLE        :
    case SVT_HI_PRESS_VAC_ENABLE    :
    case SVT_LO_PRESS_VAC_ENABLE    :
    case SVT_HI_IGP_ENABLE          :
    case SVT_LO_IGP_ENABLE          :
    case SVT_HI_VAP_RET_ENABLE      :
    case SVT_LO_VAP_RET_ENABLE      :
    case SVT_XTRA_HI_PRESS_ENABLE1  :
    case SVT_XTRA_LO_PRESS_ENABLE1  :
    case SVT_XTRA_HI_PRESS_ENABLE2  :
    case SVT_XTRA_LO_PRESS_ENABLE2  :
        if ( PressurePtr ) {
            Status = PressurePtr->GetBitValue(ValueId, 0, MyBit);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    case SVT_HI_TEMP_ENABLE     :
    case SVT_LO_TEMP_ENABLE     :
    case SVT_HI_BOT_TEMP_ENABLE :
    case SVT_LO_BOT_TEMP_ENABLE :
        if ( TemperaturePtr ) {
            Status = TemperaturePtr->GetBitValue(ValueId, 0, MyBit);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;

    case SVT_HIHI_LEVEL_ENABLE  :
    case SVT_HI_LEVEL_ENABLE    :
    case SVT_LO_LEVEL_ENABLE    :
    case SVT_LOLO_LEVEL_ENABLE  :
    case SVT_LEV_CHANGE_ENA     :
		{
			int        tmpValKey;
			AlarmBasic *tmpPtr;
			switch (ValueId) {
			case SVT_HIHI_LEVEL_ENABLE:
				tmpValKey = SVT_AL_ENABLE;
				tmpPtr = (AlarmBasic *)OverfillPtr;
				break;
			case SVT_HI_LEVEL_ENABLE:
				tmpValKey = SVT_AL_ENABLE;
				tmpPtr = (AlarmBasic *)HighLevelPtr;
				break;
			case SVT_LO_LEVEL_ENABLE:
				tmpValKey = SVT_AL_ENABLE;
				tmpPtr = (AlarmBasic *)LowLevelPtr;
				break;
			case SVT_LOLO_LEVEL_ENABLE:
				tmpValKey = SVT_AL_ENABLE;
				tmpPtr = (AlarmBasic *)LoLoLevelPtr;
				break;
			case SVT_LEV_CHANGE_ENA:
				tmpValKey = SVT_AL_ENABLE;
				tmpPtr = (AlarmBasic *)LevelChangeAPtr;
				break;
			}
			if (tmpPtr) {
				Status = tmpPtr->GetBitValue(tmpValKey, 0, MyBit);
			} else {
				Status = GETVAL_NO_DISPLAY;
			}
		}
        break;
	default:
		Status = PROXRefObject::GetBitValue(ValueId, Index, MyBit);
		break;

	}
    return (Status);
}



int PROTank::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status    = E_NO_ERR,
		ValUnitId = NO_UNIT;
		AnsiString strCpy = NewValue;
    switch ( ValueId ) {
    case SVT_TWM_LOW_SPEED_ENABLE   :
    case SVT_TWM_PRESET_TIME_ENABLE :
    case SVT_TWM_PRESET_TIME        :
        {
			for ( unsigned i = 0; i < TankWashingMachineVector.size(); i++ ) {
                int tmpStatus = TankWashingMachineVector[i]->PutValue(ValueId, Index, strCpy, Local);
                if ( tmpStatus != E_NO_ERR ) {
                    Status = tmpStatus;
                }
            }
        }
        break;
    case SVT_VOLUME_SETPOINT:
        {
            float NewStartVolPercent = ConvertToSi(NewValue, ValUnitId = PERCENT_UNIT, Status, LEVEL_NOISE_LIMIT_RADAR, AdjustedDBU, LEVEL_NOISE_LIMIT_RADAR_COMBI);
            if ( !Local && Status == E_NO_ERR ) {
                StartVolPercent = NewStartVolPercent;
            }
        }
        break;
    case SVT_RADAR_THRESHOLD:
        {
            float NewThreshold = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, LEVEL_NOISE_LIMIT_RADAR, AdjustedDBU, LEVEL_NOISE_LIMIT_RADAR_COMBI);
            if ( !Local && Status == E_NO_ERR ) {
                NoiseLimitR = NewThreshold;
            }
        }
        break;
    case SVT_CARGO_TYPE_NAME:
        {
            int Index = CTOUser::FindCargoIndex(NewValue);
            if ( Index != -1 ) {
                GetCargoTypeSettings(Index);
            } else {
                Index = CargoTypeObject::FindCargoIndex(NewValue);
                if ( Index != -1 ) {
                    Status = CargoType->PutValue(SVT_BASIC_TYPE, Index, (AnsiString)Index);
                } else {
                    unsigned CargoId = GetUnsigned(NewValue, Status);
                    if ( Status == E_NO_ERR ) {
                        // First check if Simple cargo type input
                        int tmpCargoType = CargoId >> 16;
                        int tmpBaseCargo = CargoId & 0xffff;
                        if ( tmpCargoType == CTY_NOT_DEFINED ) {
                            Status = CargoType->PutValue(SVT_BASIC_TYPE, Index, (AnsiString)tmpBaseCargo);
                        } else {
                            GetCargoTypeSettings(tmpCargoType);
                        }
                    }
                }
            }
        }
        break;
    case SVT_CARGO_TYPE:
        {
            int Value = GetInt(NewValue, Status);
            if ( Status == E_NO_ERR ) {
                if ( Value == CTY_NOT_DEFINED ) {
                    Status = CargoType->PutValue(SVT_BASIC_TYPE, Index, (AnsiString)CargoType->BaseCargoType);
                    //CargoType->CargoTypeKey = CTY_NOT_DEFINED;
                    //CargoType->Name = "Not defined";
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
    case SVT_VISCOSITY:
        Status = CargoType->PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    case SVT_MEAS_DNS:
    case SVT_USE_MSRD_DNS:
        {
            int Key = FindConfigKey(NewValue);
            switch ( Key ) {
            case C_ON:
            case C_OPEN:
            case C_ENABLE:
                UseMeasuredDensity = true;
                break;
            case C_OFF:
            case C_CLOSE:
            case C_DISABLE:
                UseMeasuredDensity = false;
                break;
            default:
                {
                    bool Value = (bool)GetUnsigned(NewValue, Status);
                    if ( Status == E_NO_ERR ) {
                        UseMeasuredDensity = Value;
					}
                }
                break;
            }
        }
        break;
	case SVT_HIHI_LEVEL_ENABLE:
		if ( OverfillPtr ) {
			Status = OverfillPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
	case SVT_HI_LEVEL_ENABLE:
        if ( HighLevelPtr ) {
            Status = HighLevelPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_LEVEL_ENABLE:
        if ( LowLevelPtr ) {
            Status = LowLevelPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LOLO_LEVEL_ENABLE:
        if ( LoLoLevelPtr ) {
            Status = LoLoLevelPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LEV_CHANGE_ENA:
        if ( LevelChangeAPtr ) {
            Status = LevelChangeAPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_HIHI_VOLPCNT_LIM:
        if ( OverfillPtr ) {
            Status = OverfillPtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_HI_LEVEL_LIMIT:
        if ( HighLevelPtr ) {
            Status = HighLevelPtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_HI_VOLPCNT_LIM :
    case SVT_HI_VOLUME_LIM :
    case SVT_HI_WEIGHT_LIM :
    case SVT_HI_ULLAGE_LIM :
    case SVT_HI_LEVEL_LIM :
        if ( HighLevelPtr ) {
            Status = HighLevelPtr->PutValue(ValueId, 0, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_LEVEL_LIMIT:
        if ( LowLevelPtr ) {
            Status = LowLevelPtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LOLO_LEVEL_LIMIT:
        if ( LoLoLevelPtr ) {
            Status = LoLoLevelPtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_VOLPCNT_LIM :
    case SVT_LO_VOLUME_LIM :
    case SVT_LO_WEIGHT_LIM :
    case SVT_LO_ULLAGE_LIM :
    case SVT_LO_LEVEL_LIM :
        if ( LowLevelPtr ) {
            Status = LowLevelPtr->PutValue(ValueId, 0, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LOLO_VOLPCNT_LIM :
    case SVT_LOLO_VOLUME_LIM :
    case SVT_LOLO_WEIGHT_LIM :
    case SVT_LOLO_ULLAGE_LIM :
    case SVT_LOLO_LEVEL_LIM :
        if ( LoLoLevelPtr ) {
            Status = LoLoLevelPtr->PutValue(ValueId, 0, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LEV_CHANGE_LIM :
        if ( LevelChangeAPtr ) {
            Status = LevelChangeAPtr->PutValue(ValueId, 0, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_TEMP              :
    case SVT_HI_TEMP_ENABLE    :
    case SVT_LO_TEMP_ENABLE    :
    case SVT_HI_TEMP_LIMIT     :
    case SVT_LO_TEMP_LIMIT     :
    case SVT_HI_BOT_TEMP_ENABLE:
    case SVT_LO_BOT_TEMP_ENABLE:
    case SVT_HI_BOT_TEMP_LIMIT :
    case SVT_LO_BOT_TEMP_LIMIT :
        if ( TemperaturePtr ) {
            Status = TemperaturePtr->PutValue(ValueId, 0, NewValue, Local, &ValUnitId);
            if ( !TemperaturePtr->GetIsOnline() ) {
                CompDns = CargoType->Comp_Density(Temperature);
                Density = CompDns;
                Weight = Density * Volume;
            }
        }
        break;
    case SVT_HI_PRESS_ENABLE        :
    case SVT_HI_PRESS_LIMIT         :
    case SVT_HI_PRESS_VALUE         :
    case SVT_LO_PRESS_ENABLE        :
    case SVT_LO_PRESS_LIMIT         :
    case SVT_LO_PRESS_VALUE         :
    case SVT_HI_PRESS_VAC_LIMIT     :
    case SVT_LO_PRESS_VAC_LIMIT     :
    case SVT_HI_IGP_LIMIT           :
    case SVT_LO_IGP_LIMIT           :
    case SVT_HI_VAP_RET_LIMIT       :
    case SVT_LO_VAP_RET_LIMIT       :
    case SVT_HI_PRESS_VAC_VALUE     :
    case SVT_LO_PRESS_VAC_VALUE     :
    case SVT_HI_IGP_VALUE           :
    case SVT_LO_IGP_VALUE           :
    case SVT_HI_VAP_RET_VALUE       :
    case SVT_LO_VAP_RET_VALUE       :
    case SVT_HI_PRESS_VAC_ENABLE    :
    case SVT_LO_PRESS_VAC_ENABLE    :
    case SVT_HI_IGP_ENABLE          :
    case SVT_LO_IGP_ENABLE          :
    case SVT_HI_VAP_RET_ENABLE      :
    case SVT_LO_VAP_RET_ENABLE      :
    case SVT_XTRA_HI_PRESS_ENABLE1  :
    case SVT_XTRA_HI_PRESS_LIMIT1   :
    case SVT_XTRA_HI_PRESS_VALUE1   :
    case SVT_XTRA_LO_PRESS_ENABLE1  :
    case SVT_XTRA_LO_PRESS_LIMIT1   :
    case SVT_XTRA_LO_PRESS_VALUE1   :
    case SVT_XTRA_HI_PRESS_ENABLE2  :
    case SVT_XTRA_HI_PRESS_LIMIT2   :
    case SVT_XTRA_HI_PRESS_VALUE2   :
    case SVT_XTRA_LO_PRESS_ENABLE2  :
    case SVT_XTRA_LO_PRESS_LIMIT2   :
    case SVT_XTRA_LO_PRESS_VALUE2   :
    case SVT_AL_LIMIT_TYPE_PRESS    :
        if ( PressurePtr ) {
            Status = PressurePtr->PutValue(ValueId, 0, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_ADJUST_WEIGHT:
        if ( VolumeTab ) {
            float MaxValue = Weight * 1.1;
            float MinValue = Weight * 0.9;
            if ( MinValue < 0.0 ) {
                MinValue = 0.0;
            }
            if ( MaxValue > VolumeTab->MaxY * Density ) {
                MaxValue = VolumeTab->MaxY * Density;
            }
            float NewWeight = ConvertToSi(NewValue, ValUnitId = WEIGHT_UNIT, Status, MinValue, MaxValue, 0.0);
            if ( !Local && Status == E_NO_ERR ) {
                float NewVol = NewWeight / Density;
                if ( LevVolumeTab || UllVolumeTab ) {
                    float newLevFC = LevVolumeTab->Calc_X(NewVol);
                    TableOffset -= newLevFC - LevelFC;
                } else {
                    float newUllFC = UllVolumeTab->Calc_X(NewVol);
                    TableOffset += newUllFC - UllageFC;
                }
            }
        } else {
            Status = E_INPUT_ERR;
        }
        break;
    case SVT_ADJUST_VOLUME:
        if ( VolumeTab ) {
            float MaxValue = Volume * 1.1;
            float MinValue = Volume * 0.9;
            if ( MinValue < 0.0 ) {
                MinValue = 0.0;
            }
            if ( VolumeTab ) {
                if ( MaxValue > VolumeTab->MaxY ) {
                    MaxValue = VolumeTab->MaxY;
                }
            }
            float NewVol = ConvertToSi(NewValue, ValUnitId = VOLUME_UNIT, Status, MinValue, MaxValue, 0.0);
            if ( !Local && Status == E_NO_ERR ) {
                if ( LevVolumeTab ) {
                    float newLevFC = LevVolumeTab->Calc_X(NewVol);
                    TableOffset -= newLevFC - LevelFC;
                } else {
                    float newUllFC = UllVolumeTab->Calc_X(NewVol);
                    TableOffset += newUllFC - UllageFC;
                }
            }
        } else {
            Status = E_INPUT_ERR;
        }
        break;
    case SVT_ADJUST_SOUNDING:    // Sounding table!!!
        if ( (VolumeTab) && SoundingTab ) {
            float MaxLevel = Sounding + 1.0;
            float MinLevel = Sounding - 1.0;
            if ( MinLevel < 0.0 ) {
                MinLevel = 0.0;
            }
            // Should maybe also check agains max sounding in the table
            // from SoundingTab->MaxX;
            float NewSnd = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, MinLevel, MaxLevel, 0.0);
            if ( !Local && Status == E_NO_ERR ) {
                // Make trim and list correction

                NewSnd += PROSystemData::TrimValue * (cDLFC - cDLR) + PROSystemData::ListValue * (cDTFC - cDTR);
                if ( NewSnd < 0.0 ) {
                    NewSnd = 0.0;
                }


                float NewVol = SoundingTab->Calc_Y(NewSnd);
                if ( LevVolumeTab ) {
                    float newLevFC = LevVolumeTab->Calc_X(NewVol - TableOffset);
                    LevelOffset -= newLevFC - LevelFC;
                } else {
                    float newUllFC = UllVolumeTab->Calc_X(NewVol + TableOffset);
                    LevelOffset += newUllFC - UllageFC;
                }
            }
        } else {
            Status = E_INPUT_ERR;
        }
        break;
    case SVT_ADJUST_ULLAGE:
        {
            float MaxLevel = UllageRef + 1.0;
            float MinLevel = UllageRef - 1.0;
            if ( MinLevel < 0.0 ) {
                MinLevel = 0.0;
            }

            float NewUllageRef = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, MinLevel, MaxLevel, 0.0);
            if ( !Local && Status == E_NO_ERR ) {
                LevelOffset += NewUllageRef - UllageRef;
            }
        }
        break;
    case SVT_ADJUST_ULLAGE_UTI:
        {
            float UllageUTI = UllageRef + DVSnsToUTI;
            float MaxLevel = UllageUTI + 1.0;
            float MinLevel = UllageUTI - 1.0;
            if ( MinLevel < 0.0 ) {
                MinLevel = 0.0;
            }

            float NewUllageUTI = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, MinLevel, MaxLevel, 0.0);
            if ( !Local && Status == E_NO_ERR ) {
                LevelOffset += NewUllageUTI - UllageUTI;
            }
        }
        break;
    case SVT_ADJUST_LEVEL:
        {
            float MaxLevel = LevelAtRef + 1.0;
            float MinLevel = LevelAtRef - 1.0;
            if ( MinLevel < 0.0 ) {
                MinLevel = 0.0;
            }
            float NewLevRef = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, MinLevel, MaxLevel, 0.0);
            if ( !Local && Status == E_NO_ERR ) {
                LevelOffset -= NewLevRef - LevelAtRef;
                SetModifiedFlag();
            }
        }
        break;
    case SVT_LEVEL_OFFSET:
        LevelOffset = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, -1.0, 1.0, LevelOffset);
        break;
    case SVT_TABLE_OFFSET:
        TableOffset = ConvertToSi(NewValue, ValUnitId = LENGTH_UNIT, Status, -1.0, 1.0, TableOffset);
        break;
    case SVT_ZEROSET_LEVEL:
        if ( !LevelPressures.empty() ) {
            AnsiString TmpString = ZeroSetLevelSensors(Local);
#ifndef BORLAND
            if ( Local && TmpString.Length() ) {
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
            //Status = LevelPressures[0]->PutValue(SVT_AI_CALC_VAL, Index, "0.0", Local);
        }
        break;
    case SVT_ZEROSET_PRESS:
        if ( PressurePtr ) {
            Status = PressurePtr->PutValue(SVT_PRESSURE, Index, "0.0", Local);
        }
        break;
    case SVT_LC_VOLUME:
        if ( PROSystemData::ReceiveWeightVolume ) {
            int Cnt = sscanf(NewValue.c_str(), "%f", &LCVolume);
            if ( Cnt == 1 ) {
                LCDataTime = time(NULL);
            } else {
                Status = E_INPUT_ERR;
            }
        }
        break;
    case SVT_LC_WEIGHT:
        if ( PROSystemData::ReceiveWeightVolume ) {
            int Cnt = sscanf(NewValue.c_str(), "%f", &LCWeight);
            if ( Cnt == 1 ) {
                LCDataTime = time(NULL);
            } else {
                Status = E_INPUT_ERR;
            }
        }
        break;
	case SVT_PRESSURE:
		 ValueId = SVT_TP;
	case SVT_TP :
	case SVT_UP :
	case SVT_MP :
	case SVT_BP :
    case SVT_BP1 :
    case SVT_BP2 :
    case SVT_BP3 :
    case SVT_BP_GAIN :
    case SVT_BP_GAIN1 :
    case SVT_BP_GAIN2 :
    case SVT_BP_GAIN3 :
    case SVT_MP_GAIN :
    case SVT_UP_GAIN :
    case SVT_TP_GAIN :
    case SVT_BP_OFFSET :
    case SVT_BP_OFFSET1 :
    case SVT_BP_OFFSET2 :
    case SVT_BP_OFFSET3 :
    case SVT_MP_OFFSET :
    case SVT_UP_OFFSET :
    case SVT_TP_OFFSET :
    case SVT_TP_ENABLE :
    case SVT_UP_ENABLE :
    case SVT_MP_ENABLE :
    case SVT_BP_ENABLE :
    case SVT_BP_ENABLE1 :
    case SVT_BP_ENABLE2 :
    case SVT_BP_ENABLE3 :

        {
            AnalogInput *SnsPtr = NULL;
			switch ( ValueId ) {
            case SVT_BP :
            case SVT_BP_GAIN :
            case SVT_BP_OFFSET :
            case SVT_BP_ENABLE :
            case SVT_BP_SERIAL_NO :
                SnsPtr = FindAnalogInput(C_AI_LOC_BOTTOM);
                break;
            case SVT_MP :
            case SVT_MP_GAIN :
            case SVT_MP_OFFSET :
            case SVT_MP_ENABLE :
            case SVT_MP_SERIAL_NO :
                SnsPtr = FindAnalogInput(C_AI_LOC_MIDDLE);
                break;
            case SVT_UP :
            case SVT_UP_GAIN :
            case SVT_UP_OFFSET :
            case SVT_UP_ENABLE :
            case SVT_UP_SERIAL_NO :
                SnsPtr = FindAnalogInput(C_AI_LOC_UPPER);
                break;
            case SVT_BP1 :
            case SVT_BP_GAIN1 :
            case SVT_BP_OFFSET1 :
            case SVT_BP_ENABLE1 :
            case SVT_BP_SERIAL_NO1:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY1);
                break;
            case SVT_BP2 :
            case SVT_BP_GAIN2 :
            case SVT_BP_OFFSET2 :
            case SVT_BP_ENABLE2 :
            case SVT_BP_SERIAL_NO2:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY2);
                break;
            case SVT_BP3 :
            case SVT_BP_GAIN3 :
            case SVT_BP_OFFSET3 :
            case SVT_BP_ENABLE3 :
            case SVT_BP_SERIAL_NO3:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY3);
                break;
            case SVT_TP:
            case SVT_TP_GAIN :
            case SVT_TP_OFFSET :
            case SVT_TP_ENABLE :
            case SVT_TP_SERIAL_NO :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_VAPOUR, AI_SENSOR_PRESS);
                if ( !SnsPtr ) {
                    SnsPtr = FindAllAnalogInput(C_AI_LOC_DECK, AI_SENSOR_PRESS);
                }
                break;
            }
            int SnsValId = SVT_NOT_DEFINED;
            switch ( ValueId ) {
            case SVT_BP_GAIN1 :
            case SVT_BP_GAIN2 :
            case SVT_BP_GAIN3 :
            case SVT_BP_GAIN :
            case SVT_MP_GAIN :
            case SVT_UP_GAIN :
            case SVT_TP_GAIN :
                SnsValId = SVT_AI_GAIN;
                break;
            case SVT_BP_OFFSET1:
            case SVT_BP_OFFSET2:
            case SVT_BP_OFFSET3:
            case SVT_BP_OFFSET :
            case SVT_MP_OFFSET :
            case SVT_UP_OFFSET :
            case SVT_TP_OFFSET :
                SnsValId = SVT_AI_OFFSET;
                break;
            case SVT_BP1 :
            case SVT_BP2 :
            case SVT_BP3 :
            case SVT_BP :
            case SVT_MP :
            case SVT_UP :
            case SVT_TP :
                SnsValId = SVT_AI_CALC_VAL;
                break;
            case SVT_BP_ENABLE1:
            case SVT_BP_ENABLE2:
            case SVT_BP_ENABLE3:
            case SVT_BP_ENABLE :
            case SVT_MP_ENABLE :
            case SVT_UP_ENABLE :
            case SVT_TP_ENABLE :
                SnsValId = SVT_AI_ENABLE_TEXT;
                break;
            }
            if ( SnsPtr ) {
                Status = SnsPtr->PutValue(SnsValId, Index, NewValue, Local, &ValUnitId);
            } else {
                Status = E_ILLEGAL;
            }
        }
        break;
    case SVT_T1  :
    case SVT_T1_GAIN :
    case SVT_T1_OFFSET :
    case SVT_T2  :
    case SVT_T2_GAIN :
    case SVT_T2_OFFSET :
    case SVT_T3  :
    case SVT_T3_GAIN :
    case SVT_T3_OFFSET :
    case SVT_T4  :
    case SVT_T4_GAIN :
    case SVT_T4_OFFSET :
    case SVT_T5  :
    case SVT_T5_GAIN :
    case SVT_T5_OFFSET :
    case SVT_TT  :
    case SVT_TT_GAIN :
    case SVT_TT_OFFSET :
    case SVT_T1_ENABLE :
    case SVT_T2_ENABLE :
    case SVT_T5_ENABLE :
    case SVT_T3_ENABLE :
    case SVT_T4_ENABLE :
    case SVT_TT_ENABLE :
        {
            AnalogInput *SnsPtr = NULL;
            switch ( ValueId ) {
            case SVT_T1 :
            case SVT_T1_GAIN :
            case SVT_T1_OFFSET :
            case SVT_T1_ENABLE :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP1, AI_SENSOR_TEMP);
                break;
            case SVT_T2 :
            case SVT_T2_GAIN :
            case SVT_T2_OFFSET :
            case SVT_T2_ENABLE :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP2, AI_SENSOR_TEMP);
                break;
            case SVT_T3 :
            case SVT_T3_GAIN :
            case SVT_T3_OFFSET :
            case SVT_T3_ENABLE :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP3, AI_SENSOR_TEMP);
                break;
            case SVT_T4 :
            case SVT_T4_GAIN :
            case SVT_T4_OFFSET :
            case SVT_T4_ENABLE :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP4, AI_SENSOR_TEMP);
                break;
            case SVT_T5 :
            case SVT_T5_GAIN :
            case SVT_T5_OFFSET :
            case SVT_T5_ENABLE :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP5, AI_SENSOR_TEMP);
                break;
            case SVT_TT :
            case SVT_TT_GAIN :
            case SVT_TT_OFFSET :
            case SVT_TT_ENABLE :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_VAPOUR, AI_SENSOR_TEMP);
                if ( !SnsPtr ) {
                    SnsPtr = FindAllAnalogInput(C_AI_LOC_DECK, AI_SENSOR_TEMP);
                    if ( !SnsPtr ) {
                        SnsPtr = FindAllAnalogInput(C_AI_LOC_TEMP6, AI_SENSOR_TEMP);
                    }
                }
                break;
            }
            int SnsValId = SVT_NOT_DEFINED;
            switch ( ValueId ) {
            case SVT_T1_GAIN :
            case SVT_T2_GAIN :
            case SVT_T5_GAIN :
            case SVT_T3_GAIN :
            case SVT_T4_GAIN :
            case SVT_TT_GAIN :
                SnsValId = SVT_AI_GAIN;
                break;
            case SVT_T1_OFFSET :
            case SVT_T2_OFFSET :
            case SVT_T5_OFFSET :
            case SVT_T3_OFFSET :
            case SVT_T4_OFFSET :
            case SVT_TT_OFFSET :
                SnsValId = SVT_AI_OFFSET;
                break;
            case SVT_T1 :
            case SVT_T2 :
            case SVT_T5 :
            case SVT_T3 :
            case SVT_T4 :
            case SVT_TT :
                SnsValId = SVT_AI_CALC_VAL;
                break;
            case SVT_T1_ENABLE :
            case SVT_T2_ENABLE :
            case SVT_T5_ENABLE :
            case SVT_T3_ENABLE :
            case SVT_T4_ENABLE :
            case SVT_TT_ENABLE :
                SnsValId = SVT_AI_ENABLE;
                break;

            }
            if ( SnsPtr ) {
                Status = SnsPtr->PutValue(SnsValId, Index, NewValue, Local, &ValUnitId);
            } else {
                Status     = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_VOLUME_OFFSET:
        VolumeOffset = Volume;      // Ignore input. Only set offset
        break;

    case SVT_VOLUME_CORRECTION:
        VolCorrFactor = ConvertToSi(NewValue, ValUnitId = NO_UNIT, Status, 0.9, 1.1, VolCorrFactor);
        break;
/*--------------------------------------------------------------------------------
* From the Loading calculator
*/

    case SVT_WEIGHT:
        if ( VolumeTab ) {
            float MaxWgt = VolumeTab->MaxY * Density;
            float tmpWgt = (float)ConvertToSi(NewValue, ValUnitId = WEIGHT_UNIT, Status, 0.0, MaxWgt, Weight);
            if ( Status == E_NO_ERR ) {
                InputWeight(tmpWgt);
                if ( !Master ) {
                    IsOnline = false;
                }
            }
        }
        break;
    case SVT_VOLUME:
        if ( VolumeTab ) {
            float MaxVol = VolumeTab->MaxY;
            float tmpVol = (float)ConvertToSi(NewValue, ValUnitId = VOLUME_UNIT, Status, 0.0, MaxVol, Volume);
            if ( Status == E_NO_ERR ) {
                InputVolume(tmpVol);
                if ( !Master ) {
                    IsOnline = false;
                }
            }
        }
        break;
    case SVT_VOLPERCENT:
        if ( VolumeTab ) {
            float MaxPercent = 100.0;
            ValUnitId = PERCENT_UNIT;
            float tmpVolP = (float)ConvertToSi(NewValue, PERCENT_UNIT, Status, 0.0, MaxPercent, VolumePercent);
            if ( Status == E_NO_ERR ) {
                InputVolumePercent(tmpVolP);
                if ( !Master ) {
                    IsOnline = false;
                }
            }
        }
        break;
    case SVT_LEVEL_FC:
        if ( VolumeTab ) {
            float MaxLev = VolumeTab->MaxX;
            float MaxVol = VolumeTab->MaxY;
            ValUnitId = LENGTH_UNIT;
            float tmpLev = (float)ConvertToSi(NewValue, LENGTH_UNIT, Status, 0.0, MaxLev, LevelFC);
            if ( Status == E_NO_ERR ) {
                InputLevelFC(tmpLev);
                if ( !Master ) {
                    IsOnline = false;
                }
            }
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
            float tmpLev = (float)ConvertToSi(NewValue, LENGTH_UNIT, Status, 0.0, MaxLev, LevelAtRef);
            if ( Status == E_NO_ERR ) {
                InputLevelAtRef(tmpLev);
                if ( !Master ) {
                    IsOnline = false;
                }
            }
        }
        break;
    case SVT_LEVEL_SENSOR:
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
            float tmpLev = (float)ConvertToSi(NewValue, LENGTH_UNIT, Status, 0.0, MaxLev, LevelAtRef);
            if ( Status == E_NO_ERR ) {
                InputLevelAtSensor(tmpLev);
                if ( !Master ) {
                    IsOnline = false;
                }
            }
        }
        break;
    case SVT_ULLAGE:
        if ( VolumeTab ) {
            float MinUll = 0.0;
            float MaxVol = VolumeTab->MaxY;
            ValUnitId = LENGTH_UNIT;
            float tmpUll = (float)ConvertToSi(NewValue, LENGTH_UNIT, Status, MinUll, DBotUllRefPnt, UllageRef);
            if ( Status == E_NO_ERR ) {
                InputUllageAtRef(tmpUll);
                if ( !Master ) {
                    IsOnline = false;
                }
            }
        }
        break;
    case SVT_ULLAGE_RADAR:
        if ( VolumeTab ) {
            float MinUll = 0.0;
            float MaxVol = VolumeTab->MaxY;
            ValUnitId = LENGTH_UNIT;
            float tmpUll = (float)ConvertToSi(NewValue, LENGTH_UNIT, Status, MinUll, DBotUllRefPnt, UllageRef);
            if ( Status == E_NO_ERR ) {
                InputUllageAtSensor(tmpUll);
                if ( !Master ) {
                    IsOnline = false;
                }
            }
        }
        break;
    case SVT_ULLAGE_FC:
        if ( VolumeTab ) {
            float MinUll = 0.0;
            float MaxVol = VolumeTab->MaxY;
            ValUnitId = LENGTH_UNIT;
            float tmpUll = (float)ConvertToSi(NewValue, LENGTH_UNIT, Status, MinUll, DBotUllRefPnt, UllageRef);
            if ( Status == E_NO_ERR ) {
                InputUllageFC(tmpUll);
                if ( !Master ) {
                    IsOnline = false;
                }
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

int PROTank::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch ( ValueId ) {
    case SVT_LEVEL_SENSOR:
        {
            float tmpLevel = NewValue;
            if ( tmpLevel <= 0.0 ) {
                Level = 0.0;
                LevelFC = 0.0;
                LevelAtRef = 0.0;
                NotEmptyTank = false;
                HasLevelSensors = false;
                IsNewData = false;
            } else {
                float tmpLevelFC    = Level + PROSystemData::TrimListCorrection(cDLFC, cDTFC) - DBotManMsrPnt;
                float tmpLevelAtRef = Level + PROSystemData::TrimListCorrection(cDLR, cDTR) - DBotManMsrPnt;
                if ( tmpLevelFC <= 0.0 ) {
                    tmpLevelFC = 0.0;
                }
                if ( tmpLevelAtRef <= 0.0 ) {
                    tmpLevelAtRef = 0.0;
                }
                Level = tmpLevel;
                LevelFC = tmpLevelFC;
                LevelAtRef = tmpLevelAtRef;
                NotEmptyTank = true;
                HasLevelSensors = true;
                IsNewData = true;
            }
            //Always update ullage
            if ( AdjustedDBU ) {
                UllageRef   = AdjustedDBU - LevelAtRef;
                UllageFC    = AdjustedDBU - LevelFC;
                UllageAtSns = AdjustedDBU - Level;
                if ( UllageRef < 0.0 ) {
                    UllageRef = 0.0;
                }
                if ( UllageFC < 0.0 ) {
                    UllageFC = 0.0;
                }
                if ( UllageAtSns < 0.0 ) {
                    UllageAtSns = 0.0;
                }
            }
        }
        break;
    case SVT_LEVEL_FC:
        {
            float tmpLevelFC = NewValue;
            if ( tmpLevelFC <= 0.0 ) {
                Level = 0.0;
                LevelFC = 0.0;
                LevelAtRef = 0.0;
                HasLevelSensors = false;
                IsNewData = false;
            } else {
                float tmpLevel = LevelFC - PROSystemData::TrimListCorrection(cDLFC, cDTFC) + DBotManMsrPnt;
                if ( tmpLevel <= 0.0 ) {
                    tmpLevel = 0.0;
                }
                float tmpLevelAtRef = LevelFC + PROSystemData::TrimListCorrection(cDLR - cDLFC, cDTR - cDTFC);
                if ( tmpLevelAtRef <= 0.0 ) {
                    tmpLevelAtRef = 0.0;
                }
                Level = tmpLevel;
                LevelFC = tmpLevelFC;
                LevelAtRef = tmpLevelAtRef;
                HasLevelSensors = true;
                IsNewData = true;
            }
            //Always update ullage
            if ( AdjustedDBU ) {
                UllageRef = AdjustedDBU - LevelAtRef;
                UllageFC = AdjustedDBU - LevelFC;
                if ( UllageRef < 0.0 ) {
                    UllageRef = 0.0;
                }
                if ( UllageFC < 0.0 ) {
                    UllageFC = 0.0;
                }
            }
        }
        break;
    case SVT_LEVEL_REF:
        {
            float tmpLevelAtRef = NewValue;
            if ( tmpLevelAtRef <= 0.0 ) {
                Level = 0.0;
                LevelFC = 0.0;
                LevelAtRef = 0.0;
                HasLevelSensors = false;
                IsNewData = false;
            } else {
                float tmpLevel = tmpLevelAtRef - PROSystemData::TrimListCorrection(cDLR, cDTR) + DBotManMsrPnt;
                if ( tmpLevel <= 0.0 ) {
                    tmpLevel = 0.0;
                }
                float tmpLevelFC = tmpLevelAtRef + PROSystemData::TrimListCorrection(cDLFC - cDLR, cDTFC - cDTR);
                if ( tmpLevelFC <= 0.0 ) {
                    tmpLevelFC = 0.0;
                }
                Level = tmpLevel;
                LevelFC = tmpLevelFC;
                LevelAtRef = tmpLevelAtRef;
                HasLevelSensors = true;
                IsNewData = true;
            }
            //Always update ullage
            if ( AdjustedDBU ) {
                UllageRef = AdjustedDBU - LevelAtRef;
                UllageFC = AdjustedDBU - LevelFC;
                if ( UllageRef < 0.0 ) {
                    UllageRef = 0.0;
                }
                if ( UllageFC < 0.0 ) {
                    UllageFC = 0.0;
                }
            }
        }
        break;
    case SVT_ULLAGE:
        {
            if ( AdjustedDBU ) {
                if ( NewValue < 0.0 ) {
                    NewValue = 0.0;
                }
                PutFloatValue(SVT_LEVEL_REF, AdjustedDBU - NewValue);
            } else {
                UllageRef = NewValue;
                float tUllageFC = NewValue - PROSystemData::TrimListCorrection(cDLFC - cDLR, cDTFC - cDTR);
                if ( tUllageFC < 0.0 ) {
                    tUllageFC = 0.0;
                }
                UllageFC = tUllageFC;
            }

        }
        break;
    case SVT_ULLAGE_UTI:
        {
            if ( AdjustedDBU ) {
                if ( NewValue < 0.0 ) {
                    NewValue = 0.0;
                }
                PutFloatValue(SVT_LEVEL_REF, AdjustedDBU + DVSnsToUTI - NewValue);
            } else {
                UllageRef = NewValue - DVSnsToUTI;
                float tUllageFC = NewValue - PROSystemData::TrimListCorrection(cDLFC - cDLR, cDTFC - cDTR);
                if ( tUllageFC < 0.0 ) {
                    tUllageFC = 0.0;
                }
                UllageFC = tUllageFC;
            }

        }
        break;
    case SVT_ULLAGE_FC:
        {
            if ( AdjustedDBU ) {
                if ( NewValue < 0.0 ) {
                    NewValue = 0.0;
                }
                PutFloatValue(SVT_LEVEL_FC, AdjustedDBU - NewValue);
            } else {
                UllageFC = NewValue;
                float tUllageRef = NewValue + PROSystemData::TrimListCorrection(cDLFC - cDLR, cDTFC - cDTR);
                if ( tUllageRef < 0.0 ) {
                    tUllageRef = 0.0;
                }
                UllageRef = tUllageRef;
            }

        }
        break;
    case SVT_ULLAGE_RADAR:
        {
            if ( AdjustedDBU ) {
                if ( NewValue < 0.0 ) {
                    NewValue = 0.0;
                }
                PutFloatValue(SVT_LEVEL_SENSOR, AdjustedDBU - NewValue);
            } else {
                UllageAtSns = NewValue;
                float tUllageRef = NewValue - PROSystemData::TrimListCorrection(cDLR  - cRadarDLR, cDTR - cRadarDTR);
                float tUllageFC  = NewValue - PROSystemData::TrimListCorrection(cDLFC - cRadarDLR, cDTR - cRadarDTR);

                if ( tUllageRef < 0.0 ) {
                    tUllageRef = 0.0;
                }
                if ( tUllageFC < 0.0 ) {
                    tUllageFC = 0.0;
                }
                UllageRef = tUllageRef;
                UllageFC  = tUllageFC;
            }

        }
        break;
    case SVT_LC_DENSITY:
        LCDataTime = time(NULL);
        if ( CargoType->OD1 != NewValue ) {
            if ( CargoType->BaseCargoType != CTY_SIMPLE_LIN ) {
                CargoType->InputBasicCargoType(CTY_SIMPLE_LIN);
            }
            Status = CargoType->OD1_Input(NewValue);
        }
        break;
    case SVT_DENSITY:
        if ( CargoType->OD1 != NewValue ) {
            if ( CargoType->BaseCargoType != CTY_SIMPLE_LIN ) {
                CargoType->InputBasicCargoType(CTY_SIMPLE_LIN);
            }
            Status = CargoType->OD1_Input(NewValue);
            if ( Status == E_NO_ERR ) {
                SetModifiedFlag();
            }
        }
        break;
    case SVT_REF_DNS1 :
        if ( CargoType->OD1 != NewValue ) {
            Status = CargoType->OD1_Input(NewValue);
            if ( Status == E_NO_ERR ) {
                SetModifiedFlag();
            }
        }
        break;
    case SVT_REF_DNS2 :
        if ( CargoType->OD2 != NewValue ) {
            Status = CargoType->OD2_Input(NewValue);
            if ( Status == E_NO_ERR ) {
                SetModifiedFlag();
            }
        }
        break;
    case SVT_REF_TMP2 :
        if ( CargoType->RefTmp2 != NewValue ) {
            Status = CargoType->RefTmp2_Input(NewValue);
            if ( Status == E_NO_ERR ) {
                SetModifiedFlag();
            }
        }
        break;
    case SVT_METRI_TAPE_SNS:
        if ( MetriTapeSns ) {
            MetriTapeSns->NewValue(NewValue);
            MetriTapeSns->Calculate();
            MetriTapeSns->ActiveAlarms = CheckAlarms(MetriTapeSns->AlarmSet, &MetriTapeSns->HWFailure);
            MetriTapeSns->SendData();
        }
        break;
    case SVT_HSH_FLOAT_SNS:
        if ( HSH_FloatSns ) {
            HSH_FloatSns->NewValue(NewValue);
            HSH_FloatSns->Calculate();
            HSH_FloatSns->ActiveAlarms = CheckAlarms(HSH_FloatSns->AlarmSet, &HSH_FloatSns->HWFailure);
            HSH_FloatSns->SendData();
        }
        break;
    case SVT_HART_MA :
    case SVT_HART_RADAR :
    case SVT_HART_STATUS :
    case SVT_HART_OPEN_LOOP :
    case SVT_HART_SHORT_CIRCUIT :
        if ( !RadarSensors.empty() ) {
            AIRadarSensorHart *tmpPtr = (AIRadarSensorHart *)RadarSensors[0];
            tmpPtr->PutFloatValue(ValueId, NewValue);
            //tmpPtr->ActiveAlarms = CheckAlarms(tmpPtr->AlarmSet,&tmpPtr->HWFailure);
            if ( ValueId == SVT_HART_RADAR ) {
                tmpPtr->SendData();
            }
        }
        break;
    case SVT_AP_TPRESS_SNS_FAIL    :
        if ( PressurePtr ) {
            PressurePtr->PutFloatValue(ValueId, NewValue);
        }
        break;
    case SVT_AP_TANK_PRESSURE_MB  :
        if ( PressurePtr ) {
            PressurePtr->PutFloatValue(ValueId, NewValue);
        }
        break;
    case SVT_AP_LPRESS_SNS_FAIL  :
        // Assume only one airpurge level sensor for one tank
        if ( !LevelPressures.empty() ) {
            LevelPressures[0]->PutFloatValue(ValueId, NewValue);
        }
        break;
    case SVT_MB_MA_PRESSURE:
        // Assume only one Modbus level sensor for one tank
        if ( !LevelPressures.empty() ) {
            LevelPressures[0]->NewValue(NewValue);
            LevelPressures[0]->SendData();
            LevelPressures[0]->ActiveAlarms = CheckAlarms(LevelPressures[0]->AlarmSet, &LevelPressures[0]->HWFailure);
        }
        break;
    case SVT_AP_LEVEL_PRESSURE_MB   :
    case SVT_AP_LEVEL_PRESSURE_MH2O :
        // Assume only one airpurge level sensor for one tank
        // If no sensor give level directly
        if ( LevelPressures.empty() ) {
            PutFloatValue(SVT_LEVEL_SENSOR, NewValue);
        } else {
            LevelPressures[0]->PutFloatValue(ValueId, NewValue);
            LevelPressures[0]->SendData();
        }
        break;
    case SVT_LC_VOLUME:
    case SVT_VOLUME:
        LCVolume = NewValue;
        LCDataTime = time(NULL);
        break;
    case SVT_VOLPERCENT:
        VolumePercent = NewValue;
        break;
    case SVT_WEIGHT:
    case SVT_LC_WEIGHT:
        LCWeight = GetCorrectedWeight(NewValue, Density);
        LCDataTime = time(NULL);
        break;
    case SVT_TEMP:
        if ( TemperaturePtr ) {
            Status = TemperaturePtr->PutFloatValue(ValueId, NewValue);
        }
        break;
    case SVT_LO_VOLPCNT_LIM     :
    case SVT_LOLO_VOLPCNT_LIM   :
    case SVT_HI_VOLPCNT_LIM     :
    case SVT_HIHI_VOLPCNT_LIM   :
    case SVT_LO_LEVEL_AL_ACK    :
    case SVT_LOLO_LEVEL_AL_ACK  :
    case SVT_HI_LEVEL_AL_ACK    :
    case SVT_HIHI_LEVEL_AL_ACK  :
        {
            AlarmBasic *AlPtr = NULL;
            int        ValKey = SVT_NOT_DEFINED;

            switch ( ValueId ) {
            case SVT_LOLO_VOLPCNT_LIM:
                AlPtr  = (AlarmBasic *)LoLoLevelPtr;
                ValKey = SVT_LOLO_VOLPCNT_LIM;
                break;
            case SVT_LO_VOLPCNT_LIM:
                AlPtr  = (AlarmBasic *)LowLevelPtr;
                ValKey = SVT_LO_VOLPCNT_LIM;
                break;
            case SVT_HI_VOLPCNT_LIM:
                AlPtr  = (AlarmBasic *)HighLevelPtr;
                ValKey = SVT_HI_VOLPCNT_LIM;
                break;
            case SVT_HIHI_VOLPCNT_LIM:
                AlPtr  = (AlarmBasic *)OverfillPtr;
                ValKey = SVT_HIHI_VOLPCNT_LIM;
                break;
            case SVT_LO_LEVEL_AL_ACK:
                AlPtr  = (AlarmBasic *)LowLevelPtr;
                ValKey = SVT_AL_ACKNOWLEDGE;
                break;
            case SVT_LOLO_LEVEL_AL_ACK:
                AlPtr  = (AlarmBasic *)LoLoLevelPtr;
                ValKey = SVT_AL_ACKNOWLEDGE;
                break;
            case SVT_HI_LEVEL_AL_ACK:
                AlPtr  = (AlarmBasic *)HighLevelPtr;
                ValKey = SVT_AL_ACKNOWLEDGE;
                break;
            case SVT_HIHI_LEVEL_AL_ACK:
                AlPtr  = (AlarmBasic *)OverfillPtr;
                ValKey = SVT_AL_ACKNOWLEDGE;
                break;
            }
            if ( AlPtr ) {
                Status = AlPtr->PutFloatValue(ValKey, NewValue);
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_HI_TEMP_LIMIT     :
    case SVT_LO_TEMP_LIMIT     :
    case SVT_HI_BOT_TEMP_LIMIT :
    case SVT_LO_BOT_TEMP_LIMIT :
    case SVT_HI_TEMP_AL_ACK    :
    case SVT_LO_TEMP_AL_ACK    :
    case SVT_HI_BOT_TEMP_AL_ACK:
    case SVT_LO_BOT_TEMP_AL_ACK:
        if ( TemperaturePtr ) {
            Status = TemperaturePtr->PutFloatValue(ValueId, NewValue);
        }
        break;
    case SVT_HI_PRESS_LIMIT         :
    case SVT_LO_PRESS_LIMIT         :
    case SVT_HI_IGP_LIMIT           :
    case SVT_LO_IGP_LIMIT           :

    case SVT_HI_PRESS_AL_ACK        :
    case SVT_LO_PRESS_AL_ACK        :
    case SVT_HI_PRESS_VAC_AL_ACK    :
    case SVT_LO_PRESS_VAC_AL_ACK    :
    case SVT_HI_IGP_AL_ACK          :
    case SVT_LO_IGP_AL_ACK          :
    case SVT_HI_VAP_RET_AL_ACK      :
    case SVT_LO_VAP_RET_AL_ACK      :
    case SVT_XTRA_HI_PRESS_AL_ACK1  :
    case SVT_XTRA_LO_PRESS_AL_ACK1  :
    case SVT_XTRA_HI_PRESS_AL_ACK2  :
    case SVT_XTRA_LO_PRESS_AL_ACK2  :
    case SVT_AL_LIMIT_TYPE_PRESS    :
        if ( PressurePtr ) {
            Status = PressurePtr->PutFloatValue(ValueId, NewValue);
        }
        break;
    default:
        Status = PRogramObject::PutFloatValue(ValueId, NewValue);
        break;
    }

    return (Status);

}

int PROTank::PutBitValue(int ValueId, int Index, bool NewValue) {
    int Status = E_NO_ERR;
    switch ( ValueId ) {
    case SVT_HIHI_LEVEL_ENABLE  :
    case SVT_HI_LEVEL_ENABLE    :
    case SVT_LO_LEVEL_ENABLE    :
    case SVT_LOLO_LEVEL_ENABLE  :
    case SVT_LEV_CHANGE_ENA     :
        {
            AlarmBasic *AlPtr = NULL;
            switch ( ValueId ) {
            case SVT_LO_LEVEL_ENABLE       :
                AlPtr = (AlarmBasic *)LowLevelPtr;
                break;
            case SVT_LOLO_LEVEL_ENABLE       :
                AlPtr = (AlarmBasic *)LoLoLevelPtr;
                break;
            case SVT_HI_LEVEL_ENABLE  :
                AlPtr = (AlarmBasic *)HighLevelPtr;
                break;
            case SVT_HIHI_LEVEL_ENABLE  :
                AlPtr = (AlarmBasic *)OverfillPtr;
                break;
            }
            if ( AlPtr ) {
                Status = AlPtr->PutBitValue(SVT_AL_ENABLE, 0, NewValue);
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_HIHI_LEVEL_AL_ACK  :
    case SVT_HI_LEVEL_AL_ACK    :
    case SVT_LO_LEVEL_AL_ACK    :
    case SVT_LOLO_LEVEL_AL_ACK  :
    case SVT_LEV_CHANGE_AL_ACK  :
        {
            AlarmBasic *AlPtr = NULL;
            switch ( ValueId ) {
            case SVT_LO_LEVEL_AL_ACK       :
                AlPtr = (AlarmBasic *)LowLevelPtr;
                break;
            case SVT_LOLO_LEVEL_AL_ACK       :
                AlPtr = (AlarmBasic *)LoLoLevelPtr;
                break;
            case SVT_HI_LEVEL_AL_ACK  :
                AlPtr = (AlarmBasic *)HighLevelPtr;
                break;
            case SVT_HIHI_LEVEL_AL_ACK  :
                AlPtr = (AlarmBasic *)OverfillPtr;
                break;
            }
            if ( AlPtr ) {
                Status = AlPtr->PutBitValue(SVT_AL_ACKNOWLEDGE, 0, NewValue);
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_HI_TEMP_ENABLE     :
    case SVT_LO_TEMP_ENABLE     :
    case SVT_HI_BOT_TEMP_ENABLE :
    case SVT_LO_BOT_TEMP_ENABLE :
    case SVT_HI_TEMP_AL_ACK     :
    case SVT_LO_TEMP_AL_ACK     :
    case SVT_HI_BOT_TEMP_AL_ACK :
    case SVT_LO_BOT_TEMP_AL_ACK :
        if ( TemperaturePtr ) {
            Status = TemperaturePtr->PutBitValue(ValueId, Index, NewValue);
        }
        break;
    case SVT_HI_PRESS_ENABLE        :
    case SVT_LO_PRESS_ENABLE        :
    case SVT_HI_PRESS_VAC_ENABLE    :
    case SVT_LO_PRESS_VAC_ENABLE    :
    case SVT_HI_IGP_ENABLE          :
    case SVT_LO_IGP_ENABLE          :
    case SVT_HI_VAP_RET_ENABLE      :
    case SVT_LO_VAP_RET_ENABLE      :
    case SVT_XTRA_HI_PRESS_ENABLE1  :
    case SVT_XTRA_LO_PRESS_ENABLE1  :
    case SVT_XTRA_HI_PRESS_ENABLE2  :
    case SVT_XTRA_LO_PRESS_ENABLE2  :
    case SVT_HI_PRESS_AL_ACK        :
    case SVT_LO_PRESS_AL_ACK        :
    case SVT_HI_PRESS_VAC_AL_ACK    :
    case SVT_LO_PRESS_VAC_AL_ACK    :
    case SVT_HI_IGP_AL_ACK          :
    case SVT_LO_IGP_AL_ACK          :
    case SVT_HI_VAP_RET_AL_ACK      :
    case SVT_LO_VAP_RET_AL_ACK      :
    case SVT_XTRA_HI_PRESS_AL_ACK1  :
    case SVT_XTRA_LO_PRESS_AL_ACK1  :
    case SVT_XTRA_HI_PRESS_AL_ACK2  :
    case SVT_XTRA_LO_PRESS_AL_ACK2  :
        if ( PressurePtr ) {
            Status = PressurePtr->PutBitValue(ValueId, Index, NewValue);
        }
        break;
    default:
        Status = PRogramObject::PutBitValue(ValueId, Index, NewValue);
        break;
    }
    return (Status);
}


ValueList* PROTank::GetValueInfoTable(int &Entries, int Index) {
    bool HasRedundancy = false;
    switch ( TankType ) {
    case TANKTYPE_CARGO:
        HasRedundancy = PROCargoTank::Redundancy;
        break;
    case TANKTYPE_BALLAST:
        HasRedundancy = PROBallastTank::Redundancy;
        break;
    case TANKTYPE_HFO:
    case TANKTYPE_DO:
    case TANKTYPE_LUB:
    case TANKTYPE_FW:
    case TANKTYPE_MISC:
        HasRedundancy = PROServiceTank::Redundancy;
        break;
    case TANKTYPE_VOIDSPACE:
        HasRedundancy = PROVoidSpace::Redundancy;
        break;
    }
    return GetValueInfoTableStatic(Entries, Index, HasRedundancy);
}

ValueList* PROTank::GetServiceValueInfoTable(int &Entries) {
    return GetServiceValueInfoTableStatic(Entries);
}

ValueList* PROTank::GetValueInfoTableStatic(int &Entries, int Index, bool Redundancy) {
    ValueList *tmpPtr;
    switch ( Index ) {
    case TAB_TANK_VALUES:
#ifdef ANWIN
        if ( PROTemperature::GetMaxTempSensors() < 4 ) {
            Entries = NELEMENTS(AllTankValueList2);
            tmpPtr = AllTankValueList2;
        } else {
            Entries = NELEMENTS(AllTankValueList);
            tmpPtr = AllTankValueList;
        }
#else
        if ( Redundancy ) {
            Entries = NELEMENTS(RedTankValueList);
            tmpPtr = RedTankValueList;
        } else {
            Entries = NELEMENTS(TankValueList);
            tmpPtr = TankValueList;
        }
#endif
        break;
    case TAB_ALARM_LIMITS:
        Entries = NELEMENTS(TankAlarmValueList);
        tmpPtr = TankAlarmValueList;
        break;
    case TAB_CARGO_INFO:
        Entries = NELEMENTS(TankCargoValueList);
        tmpPtr = TankCargoValueList;
        break;
    case TAB_SENSOR_VALUES:
        Entries = NELEMENTS(TankSensorValueList);
        tmpPtr = TankSensorValueList;
        break;
    }
    return (tmpPtr);

}

ValueList* PROTank::GetServiceValueInfoTableStatic(int &Entries) {
    Entries = NELEMENTS(ServiceReportTankValueList);
    return (ServiceReportTankValueList);
}



///////////////////////////////////////////////////////////////////
//
// CargoData object routines
//
///////////////////////////////////////////////////////////////////

float PROTank::VolumeAtRefTmp(void) {
    float Vol;
    if ( VolumeTab ) {
        Vol = CargoType->VolumeAtRefTmp(Weight, Volume, Density, Temperature);
    } else {
        Vol = 0.0;
    }
    return (Vol);
}

float PROTank::NetVolumeAtRefTmp(void) {
    float Vol;
    if ( VolumeTab ) {
        float Wgt = (Volume - VolumeOffset) * Density;
        Vol = CargoType->VolumeAtRefTmp(Wgt, Volume - VolumeOffset, Density, Temperature);
    } else {
        Vol = 0.0;
    }
    return (Vol);
}


void PROTank::InputSounding(float Snd) {
}

void PROTank::CalculateSounding(void) {
    if ( SoundingTab && VolumeTab && (LevelAtRef > 0.0) ) {
        float tmpSounding = SoundingTab->Calc_X(Volume);
        tmpSounding -= PROSystemData::TrimValue * (cDLFC - cDLR) + PROSystemData::ListValue * (cDTFC - cDTR);
        if ( tmpSounding > 0.0 ) {
            Sounding = tmpSounding;
        } else {
            Sounding = 0.0;
        }
    } else {
        Sounding = LevelAtRef;
    }
}


void PROTank::LR_Calc(float LRTime) {
    LrCalcTime = clock();
    float Volume  = LR_Volume / LR_Cnt;
    float dVolume = Volume - Prev_Volume;
    float NewLR   = dVolume * SECS_PR_HR / LRTime;

    // total all load rates with the same sign
    int   i       = LR_BUFSIZE - 1;
    int   j       = 0;
    float Tot     = 0.0;

    if ( NewLR > 0.0 ) {
        while ( i >= 0 && LR_Buffer[i] > 0.0 ) {
            Tot += LR_Buffer[i--];
            j++;
        }
    } else {
        while ( i >= 0 && LR_Buffer[i] < 0.0 ) {
            Tot += LR_Buffer[i--];
            j++;
        }
    }
    // Only calculate a load rate if we find minimum 4 LR in buffer
    if ( j >= 4 ) {
        j++;                                                                                                 // Add the last LR
        Tot += NewLR;
        float TmpLoadRate = Tot / j;

        LR_Limit = VolumeTab->MaxY / PROProjectInfo::TankMaxLoadTime;

        if ( fabs(TmpLoadRate) < LR_Limit ) {
            LoadRate = 0.0;
        } else {
            LoadRate = TmpLoadRate;

        }
    } else {
        LoadRate = 0.0;                  // If no load rate in buffer, set LR to 0
    }


    // shuffle oldest element out make space for newest
    memmove(&LR_Buffer[0], &LR_Buffer[1], sizeof(float) * (LR_BUFSIZE - 1));

    LR_Buffer[LR_BUFSIZE - 1] = NewLR;                // add newest element
    Prev_Volume = Volume;
    LR_Volume = 0.0;
    LR_Cnt = 0;

    // Cheat to get the LCD baclight on again if we have a load rate!!
    //if( LoadRate ) UserActivity.give();

}


float PROTank::CalcRemainingVolume(void) {
    float Limit = 0.0;
    if ( VolumeTab && LowLevelPtr && HighLevelPtr ) {
        if ( LoadRate < -1.0 ) {
            if ( LowLevelPtr->Enable ) {
                Limit = LowLevelPtr->Limit;
            } else {
                Limit = 0.0;
            }
        } else if ( LoadRate > 1.0 ) {
            switch ( TankType ) {
            case TANKTYPE_CARGO:
                if ( OverfillPtr ) {
                    if ( HighLevelPtr->Enable && fabs(OverfillPtr->Limit - HighLevelPtr->Limit) > (LIMIT_OVERFILL - LIMIT_HIGH_LEVEL) ) {
                        Limit = HighLevelPtr->Limit;
                    } else if ( OverfillPtr->Enable ) {
                        Limit = OverfillPtr->Limit;
                    } else {
                        Limit = LIMIT_OVERFILL;
                    }
                    if ( Limit > LIMIT_OVERFILL ) {
                        Limit = LIMIT_OVERFILL;
                    }
                }
                break;
            default:
            case TANKTYPE_BALLAST:
            case TANKTYPE_HFO:
            case TANKTYPE_DO:
            case TANKTYPE_LUB:
            case TANKTYPE_FW:
            case TANKTYPE_MISC:
                if ( HighLevelPtr->Enable ) {
                    Limit = HighLevelPtr->Limit;
                } else {
                    Limit = LIMIT_OVERFILL;
                }
                if ( Limit > LIMIT_OVERFILL ) {
                    Limit = LIMIT_OVERFILL;
                }
                break;
            case TANKTYPE_VOIDSPACE:
                break;
            } // End switch
        }
    }
    if ( LoadRate ) {
        float VolLimit = VolumeTab->MaxY * Limit / 100.0;
        return fabs(VolLimit - Volume);
    } else {
        return  0.0;
    }
}

void PROTank::CalcRemainingTime(void) {
    if ( LoadRate ) {
        RemainingVolume = CalcRemainingVolume();
        RemainingTime   = fabs(RemainingVolume / LoadRate);
    } else {
        RemainingTime = 0.0;
        RemainingVolume = 0.0;
    }
}


void PROTank::SetOutsideCountToMax(void) {
    OutsideCnt = MAX_OUTSIDE_WIN_CNT;
}

bool PROTank::IsLevelInsideWindow(float NewValue, float OldValue) {
    bool AcceptValue = true;
    if ( fabs(NewValue - OldValue) > MAX_OUTSIDE_LEVEL_LIM ) {
        if ( ++OutsideCnt > MAX_OUTSIDE_WIN_CNT ) {
            OutsideCnt = 0;
            AcceptValue = true;
        } else {
            AcceptValue = false;
        }
    } else {
        OutsideCnt = 0;
        AcceptValue = true;
    }
    return (AcceptValue);
}

float PROTank::GetNoiseLimitB(void) {
    return (PROProjectInfo::NoiseLimDefaultB);
}
float PROTank::GetNoiseLimitU(void) {
    return (PROProjectInfo::NoiseLimDefaultU);
}

void PROTank::Calculate(void) {
    if ( DataFromOther ) {
        HasLevelSensors = true;
        NotEmptyTank    = true;
    } else {
        // Do this to make the system accept level immideately when start filling an empty tank
        if ( !NotEmptyTank ) {
            SetOutsideCountToMax();
        }
        // Get the temperature from the PROTemp object if we have one!!
        HWFailure = false;
        if ( TemperaturePtr ) {
            if ( TemperaturePtr->HasTemp ) {
                Temperature = TemperaturePtr->GetTemperature();
            } else {
                Temperature = CargoType->RefTmp1;   // Default to ref temp 1 if temp failure
            }
        } else {
            Temperature = PROSystemData::SeaWaterTemp;
        }
        if ( PressurePtr && PressurePtr->HasPressure ) {
            Pressure = PressurePtr->Pressure;
        } else {
            Pressure = 0.0;
        }
        // Calculate density now. Next round will have the correct temperature
        CompDns = CargoType->Comp_Density(Temperature);
        if ( MetriTapeSns ) {
            CalculateMetriTape();
        } else if ( HSH_FloatSns ) {
            CalculateHSH_LNG_Float();
        } else if ( HasRadarAndPressure ) {
            CalculateOtherSns();
        } else if ( !RadarSensors.empty() && HasDVManMsrPntToSns ) {
            CalculateRadarUllage();
        } else {
            CalculateOtherSns();
        }
    }
    CalculateSounding();
    // Inform the PROTemp object about the current level
    if ( TemperaturePtr ) {
        TemperaturePtr->UpdateLevelInfo(Level, NotEmptyTank);
    }
    if ( UseCFTable && CenterOfFlotTab ) {
        //if ( PRODraftSystem::PRODraftSysPtr->GlobalRefSystem ) {
        if ( GlobalRefSystem ) {
            float tableDLFC, tableDTFC;
            CenterOfFlotTab->Calculate(Level, &tableDLFC, &tableDTFC);
            cDLFC = tableDLFC - DSnsToMid;
            cDTFC = tableDTFC - DSnsToCL;
        } else {
            CenterOfFlotTab->Calculate(Level, &cDLFC, &cDTFC);
        }
    }
    // See if we have a reason for further volume related calculations
    // Take care of values used for load rate calculation and
    // leakage detection. Check if it is anything in the tank for load
    // rate calculations and see if it is time for a new calculation of
    // load rate
    memmove(&LevelHistory[1], &LevelHistory[0], sizeof(float) * (LEVEL_HISTORY_ENTRIES - 1));
    LevelHistory[0] = Level;
    if ( NotEmptyTank && Level > 0.0 && (TrimCorrectionTable || ListCorrectionTable || TempCorrectionTable || DensityCorrectionTab) ) {
        float TrimCorrection = 0.0;
        float ListCorrection = 0.0;
        float TempCorrection = 0.0;
        float DensCorrection = 0.0;
        if ( TrimCorrectionTable ) {
            TrimCorrection = TrimCorrectionTable->GetCorrection(Level, PROSystemData::TrimValue * PROProjectInfo::LengthBetweenPP);
        }
        if ( ListCorrectionTable ) {
            ListCorrection = ListCorrectionTable->GetCorrection(Level, PROSystemData::ListValue * RAD_FACTOR);
        }
        if ( TempCorrectionTable ) {
            TempCorrection = TempCorrectionTable->GetCorrection(Level, Temperature);
        }
        if ( DensityCorrectionTab ) {
            DensCorrection = DensityCorrectionTab->Calc_Y(Density);
        }
        float tmpLevel     = Level + TrimCorrection + ListCorrection; // + TempCorrection + DensCorrection;
        float tmpUllageRef = UllageAtSns - (TrimCorrection + ListCorrection + TempCorrection + DensCorrection);
        if ( tmpLevel < 0.0 ) {
            tmpLevel = 0.0;
        }
        if ( tmpUllageRef < 0.0 ) {
            tmpUllageRef = 0.0;
        }
        if ( LevVolumeTab ) {
            Volume = VolCorrFactor * LevVolumeTab->Calc_Y(tmpLevel  - TableOffset);
        } else {
            Volume = VolCorrFactor * UllVolumeTab->Calc_Y(tmpUllageRef + TableOffset);
        }
        VolumePercent = Volume / VolumeTab->MaxY * 100.0;
        Weight = Density * Volume;
        LR_Cnt++;
        LR_Volume += Volume;
        LR_Weight += Weight;
        clock_t ElapsedLRTime = TSNElapsedTicks(LrCalcTime) / TICS_PER_SEC;
        if ( Volume && (ElapsedLRTime >= LR_PERIOD) ) {
            LR_Calc(ElapsedLRTime);
        }
        CalcRemainingTime();
    } else if ( NotEmptyTank && (LevelFC > 0.0) ) {
        if ( VolumeTab ) {
            if ( LevVolumeTab ) {
                Volume = VolCorrFactor * LevVolumeTab->Calc_Y(LevelFC - TableOffset);
            } else {
                Volume = VolCorrFactor * UllVolumeTab->Calc_Y(UllageFC + TableOffset);
            }
            VolumePercent = Volume / VolumeTab->MaxY * 100.0;
            Weight = Density * Volume;
            LR_Cnt++;
            LR_Volume += Volume;
            LR_Weight += Weight;
            clock_t ElapsedLRTime = TSNElapsedTicks(LrCalcTime) / TICS_PER_SEC;
            if ( Volume && (ElapsedLRTime >= LR_PERIOD) ) {
                LR_Calc(ElapsedLRTime);
            }
            CalcRemainingTime();
        }
    } else { // It seems that we can assume that the weight and % is 0.0 !!
        UllageRef = DBotUllRefPnt;
        UllageFC = DBotUllRefPnt;
        UllageAtSns = DBotUllRefPnt;
        Volume = 0.0;
        Weight = 0.0;
        VolumePercent = 0.0;
        LR_Cnt = 0;
        LR_Volume = 0.0;
        LR_Weight = 0.0;
        LoadRate = 0.0;
        RemainingTime = 0.0;
        RemainingVolume = 0.0;
        LrCalcFlag = false;
        LrCalcTime = clock();
        LevelDifference = 0.0;
    }

    FilteredVolPercent = FilterVal(FilteredVolPercent, VolumePercent, LevelChangeFilterDegree);

    // Special requirement from Dutch autorities
    if ( PROProjectInfo::IsInlandVessel && PressurePtr ) {
        if ( LoadRate ) {
            if ( PressurePtr->IntHighPressurePtr1 ) PressurePtr->IntHighPressurePtr1->SetEnable(EnableFalse);
            if ( PressurePtr->IntLowPressurePtr1 ) PressurePtr->IntLowPressurePtr1->SetEnable(EnableFalse);
        } else {
            if ( PressurePtr->IntHighPressurePtr1 ) PressurePtr->IntHighPressurePtr1->SetEnable(EnableTrue);
            if ( PressurePtr->IntLowPressurePtr1 ) PressurePtr->IntLowPressurePtr1->SetEnable(EnableTrue);
        }
    }
    if ( WaterSns ) {
        if ( WaterSns->Enable ) {
            float SensorStatus = WaterSns->Calculate();
            if ( WaterSns->ResultOK ) {
                if ( SensorStatus ) {
                    if ( LevelFC > WaterSns->Distance ) {
                        HasWater = WSENSOR_WATER;
                    } else {
                        HasWater = WSENSOR_LOW_LEVEL;
                    }
                } else {
                    if ( LevelFC > WaterSns->Distance ) {
                        HasWater = WSENSOR_CARGO;
                    } else {
                        HasWater = WSENSOR_EMPTY;
                    }
                }
            } else {
                HasWater = WSENSOR_FAILURE;
            }
        } else {
            HasWater = WSENSOR_DISABLE;
        }

        /*if (TemperaturePtr) {
            if (TemperaturePtr->IsAvailableNewData()) {
                //TemperaturePtr->Calculate();
                //TemperaturePtr->IsNewData = true;
                //CheckAlarms(TemperaturePtr->AlarmInfoList);
            } else {
                //TemperaturePtr->IsNewData = false;
                //SetAlarmsToNormal(TemperaturePtr->AlarmInfoList);
                //TemperaturePtr->SendData();
            }
        }
        */

    }
    SendData();

}

void PROTank::SimCalculate(void) {
    IsNewData = true;
    HWFailure = false;
    NotEmptyTank = true;


    if ( PROProjectInfo::SimulateFixedValues ) {
        Density = CargoType->Comp_Density(Temperature);
        float TempLevel    = (IDNumber & 0xFFFF) / 10.0;
        float tmpUllageRef = DBotUllRefPnt - Level;
        if ( tmpUllageRef < 0.0 ) {
            UllageRef = 0.0;
            UllageFC = 0.0;
        } else {
            UllageRef = tmpUllageRef;
            UllageFC = tmpUllageRef;
        }
        Level = TempLevel;
        LevelAtRef = TempLevel;
        LevelFC = TempLevel;
        Sounding = TempLevel;

    } else {
        //float Levels[4] ={0.489,1.268,0.698,1.302};
        float Levels[4] = { 25.891, 26.019, 25.107, 25.094 };
        float TempLevel = Levels[(IDNumber & 0xFF) - 1]; //Level + SimulatorSign * (rand() % 10) / 100.0;
        Level = TempLevel;
        float tmpUllageRef = DBotUllRefPnt - Level;
        if ( tmpUllageRef < 0.0 ) {
            UllageRef = 0.0;
            UllageFC = 0.0;
        } else {
            UllageRef = tmpUllageRef;
            UllageFC = tmpUllageRef;
        }
        Level = TempLevel;
        LevelAtRef = TempLevel;
        LevelFC = TempLevel;
        Sounding = TempLevel;
    }
    HasLevelSensors = (bool)Level;
    memmove(&LevelHistory[1], &LevelHistory[0], sizeof(float) * (LEVEL_HISTORY_ENTRIES - 1));
    LevelHistory[0] = Level;
    if ( TemperaturePtr ) {
        TemperaturePtr->Level = Level;
    }

    // See if we have a reason for further volume related calculations
    // Take care of values used for load rate calculation and
    // leakage detection. Check if it is anything in the tank for load
    // rate calculations and see if it is time for a new calculation of
    // load rate
    if ( NotEmptyTank && Level > 0.0 && (TrimCorrectionTable || ListCorrectionTable || TempCorrectionTable || DensityCorrectionTab) ) {
        float TrimCorrection = 0.0;
        float ListCorrection = 0.0;
        float TempCorrection = 0.0;
        float DensCorrection = 0.0;
        if ( TrimCorrectionTable ) {
            TrimCorrection = TrimCorrectionTable->GetCorrection(Level, PROSystemData::TrimValue * PROProjectInfo::LengthBetweenPP);
        }
        if ( ListCorrectionTable ) {
            ListCorrection = ListCorrectionTable->GetCorrection(Level, PROSystemData::ListValue * RAD_FACTOR);
        }
        if ( TempCorrectionTable ) {
            TempCorrection = TempCorrectionTable->GetCorrection(Level, Temperature);
        }
        if ( DensityCorrectionTab ) {
            DensCorrection = DensityCorrectionTab->Calc_Y(Density);
        }
        float tmpLevel     = Level + TrimCorrection + ListCorrection + TempCorrection + DensCorrection;
        float tmpUllageRef = UllageAtSns - (TrimCorrection + ListCorrection + TempCorrection + DensCorrection);
        if ( tmpLevel < 0.0 ) {
            tmpLevel = 0.0;
        }
        if ( tmpUllageRef < 0.0 ) {
            tmpUllageRef = 0.0;
        }
        if ( LevVolumeTab ) {
            Volume = VolCorrFactor * LevVolumeTab->Calc_Y(tmpLevel  - TableOffset);
        } else {
            Volume = VolCorrFactor * UllVolumeTab->Calc_Y(tmpUllageRef + TableOffset);
        }
        VolumePercent = Volume / VolumeTab->MaxY * 100.0;
        Weight = Density * Volume;
        LR_Cnt++;
        LR_Volume += Volume;
        LR_Weight += Weight;
        clock_t ElapsedLRTime = TSNElapsedTicks(LrCalcTime) / TICS_PER_SEC;
        if ( Volume && (ElapsedLRTime >= LR_PERIOD) ) {
            LR_Calc(ElapsedLRTime);
        }
        CalcRemainingTime();
    } else if ( LevelFC > 0.0 ) {
        if ( VolumeTab ) {
            if ( LevVolumeTab ) {
                Volume = LevVolumeTab->Calc_Y(LevelFC);
            } else {
                Volume = UllVolumeTab->Calc_Y(UllageFC);
            }
            VolumePercent = Volume / VolumeTab->MaxY * 100.0;
            Weight = Density * Volume;
            LR_Cnt++;
            LR_Volume += Volume;
            LR_Weight += Weight;
            clock_t ElapsedLRTime = TSNElapsedTicks(LrCalcTime) / TICS_PER_SEC;
            if ( Volume && (ElapsedLRTime >= LR_PERIOD) ) {
                LR_Calc(ElapsedLRTime);
            }
            CalcRemainingTime();
        }
    } else { // It seems that we can assume that the weight and % is 0.0 !!
        Volume = 0.0;
        Weight = 0.0;
        VolumePercent = 0.0;
        LR_Cnt = 0;
        LR_Volume = 0.0;
        LR_Weight = 0.0;
        LoadRate = 0.0;
        RemainingTime = 0.0;
        LrCalcFlag = false;
        LrCalcTime = clock();
        LevelDifference = 0.0;
    }
    if ( VolumePercent > 90.0 ) {
        SimulatorSign = -1.0;
    } else if ( VolumePercent < 10.0 ) {
        SimulatorSign = 1.0;
    }
    if ( TemperaturePtr ) {
        Temperature = TemperaturePtr->GetTemperature();
    } else {
        Temperature = 15.0;
    }
    Density = CargoType->Comp_Density(Temperature);
    if ( PressurePtr && PressurePtr->HasPressure ) {
        Pressure = PressurePtr->Pressure;
    } else {
        Pressure = 0.0;
    }

}

void PROTank::GetHorisontalDistances(float *LDist, float *TDist) {
    *LDist = cDLFC - cDLR;
    *TDist = cDTFC - cDTR;
}

bool PROTank::GetOnlineValues(float *PtrLevelFC, float *PtrSounding, float *PtrLevelAtRef, float *PtrUllage, float *PtrUllageFC, float *PtrVolume, float *PtrVolumePercent, float *PtrDensity, float *PtrTemperature) {
    *PtrLevelFC = LevelFC;
    *PtrSounding = Sounding;
    *PtrLevelAtRef = LevelAtRef;
    *PtrUllage = UllageRef;
    *PtrUllageFC = UllageFC;
    *PtrVolume = Volume;
    *PtrVolumePercent = VolumePercent;
    *PtrDensity = Density;
    *PtrTemperature = Temperature;
    return (IsNewData);
}

int PROTank::ReceiveData(U8 *data) {
    int                    ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH        = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            ANPRO10_COMMAND_2100 *pData = (ANPRO10_COMMAND_2100 *)data;
            // pData->NotEmptyTank #### check
            HWFailure = pData->HWFailure;
            IsNewData = pData->IsNewData;
            HasLevelSensors = pData->HasLevelSensors;
            NotEmptyTank = pData->NotEmptyTank;
            Level = pData->Level;
            LevelFC = pData->LevelFC;
            LevelAtRef = pData->LevelRef;
            Sounding = pData->Sounding;
            UllageRef = pData->UllageRef;
            UllageFC = pData->UllageFC;
            UllageAtSns = pData->UllageAtSns;
            Volume = pData->Volume;
            VolumePercent = pData->VolumePercent;
            LevelDifference = pData->LevelDifference;

            Density = pData->Density;
            MeasuredDns = pData->MeasuredDens;
            LoadRate = pData->LoadRate;
            RemainingTime = pData->RemainingTime;
            RemainingVolume = pData->RemainingVolume;
            LCWeight = pData->LCWeight;
            LCVolume = pData->LCVolume;
            LCDataTime = pData->LCDataTime;
            Weight = Density * Volume;
            HasWater = pData->HasWater;
            FilteredVolPercent = pData->FilteredVolPercent;
            memmove(&LevelHistory[1], &LevelHistory[0], sizeof(float) * (LEVEL_HISTORY_ENTRIES - 1));
            LevelHistory[0] = Level;
            IsOnline  = pData->IsOnline;
            ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            ANPRO10_COMMAND_2102 *pData = (ANPRO10_COMMAND_2102 *)data;
            AdjustedDBU = pData->AdjustedDBU;
            SteelExp = pData->SteelExp;
            LevelOffset = pData->LevelOffset;
            TableOffset = pData->TableOffset;
            State = TankState(pData->State);
            UseMeasuredDensity = pData->UseMeasuredDensity;
            StartVolPercent = pData->StartVolPercent;
            NoiseLimitR = pData->NoiseLimitR;
            VolumeOffset = pData->VolumeOffset;
            VolCorrFactor = pData->VolCorrFactor;
            ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_MODBUS_RT_DATA:
        {
            ANPRO10_COMMAND_2751 *pData = (ANPRO10_COMMAND_2751 *)data;
            //SetTimeStamp();
            PutFloatValue(pData->ValueKey, pData->Value);
            ErrorStatus = E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int PROTank::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2100 Cmd;
            Cmd.TxInfo.Port = NULL;
            Cmd.TxInfo.rxAddr = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId = IDNumber;
            Cmd.Data.ndb = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.HWFailure = HWFailure;
            Cmd.Data.IsNewData = IsAvailableNewData();
            Cmd.Data.HasLevelSensors = HasLevelSensors;
            Cmd.Data.NotEmptyTank = NotEmptyTank;
            Cmd.Data.Level = Level;
            Cmd.Data.LevelFC = LevelFC;
            Cmd.Data.LevelRef = LevelAtRef;
            Cmd.Data.UllageRef = UllageRef;
            Cmd.Data.UllageFC = UllageFC;
            Cmd.Data.UllageAtSns = UllageAtSns;

            Cmd.Data.Volume             = Volume;
            Cmd.Data.VolumePercent      = VolumePercent;
            Cmd.Data.Sounding           = Sounding;
            Cmd.Data.LevelDifference    = LevelDifference;
            Cmd.Data.Density            = Density;
            Cmd.Data.MeasuredDens       = MeasuredDns;
            Cmd.Data.LoadRate           = LoadRate;
            Cmd.Data.RemainingTime      = RemainingTime;
            Cmd.Data.RemainingVolume    = RemainingVolume;
            Cmd.Data.LCWeight           = LCWeight;
            Cmd.Data.LCVolume           = LCVolume;
            Cmd.Data.LCDataTime         = LCDataTime;
            Cmd.Data.HasWater           = HasWater;
            Cmd.Data.FilteredVolPercent = FilteredVolPercent;
            Cmd.Data.IsOnline           = IsOnline;

            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2102 Cmd;
            Cmd.TxInfo.Port = NULL;
            Cmd.TxInfo.rxAddr = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId = IDNumber;
            Cmd.Data.ndb = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo = CMD_GENERIC_STATIC_DATA;
            Cmd.Data.AdjustedDBU = AdjustedDBU;
            Cmd.Data.SteelExp = SteelExp;
            Cmd.Data.LevelOffset = LevelOffset;
            Cmd.Data.TableOffset = TableOffset;
            Cmd.Data.State = (U8)State;
            Cmd.Data.UseMeasuredDensity = UseMeasuredDensity;
            Cmd.Data.StartVolPercent = StartVolPercent;
            Cmd.Data.NoiseLimitR = NoiseLimitR;
            Cmd.Data.VolumeOffset = VolumeOffset;
            Cmd.Data.VolCorrFactor = VolCorrFactor;


            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

void PROTank::GetCargoTypeSettings(int Key) {
    if ( Key != CTY_NOT_DEFINED && Key < MAX_CARGOTYPES ) {
        CTOUser         *UsrCargoPtr = CTOUser::Find(Key );
        // Must be defined, if not, ignore
        if ( UsrCargoPtr && UsrCargoPtr->IsTheCargoDefined() ) {
            *CargoType = *(CargoTypeObject*)UsrCargoPtr;
            /*
            CargoType->BaseCargoType = UsrCargoPtr->BaseCargoType;
            CargoType->CargoTypeKey  = UsrCargoPtr->CargoTypeKey ;
            CargoType->Name          = UsrCargoPtr->Name         ;
            CargoType->OD1           = UsrCargoPtr->OD1          ;
            CargoType->OD2           = UsrCargoPtr->OD2          ;
            CargoType->RefTmp1       = UsrCargoPtr->RefTmp1      ;
            CargoType->RefTmp2       = UsrCargoPtr->RefTmp2      ;
            CargoType->Coeff         = UsrCargoPtr->Coeff        ;
            CargoType->MolMass       = UsrCargoPtr->MolMass      ;
            CargoType->Colour        = UsrCargoPtr->Colour       ;
            */
            if ( TemperaturePtr ) {
                if ( UsrCargoPtr->HighTempEnable && TemperaturePtr->HighTempPtr ) {
                    TemperaturePtr->HighTempPtr->Limit = UsrCargoPtr->HighTempLimit;
                    TemperaturePtr->HighTempPtr->Enable = true;
                }
                if ( UsrCargoPtr->LowTempEnable && TemperaturePtr->LowTempPtr ) {
                    TemperaturePtr->LowTempPtr->Limit = UsrCargoPtr->LowTempLimit;
                    TemperaturePtr->LowTempPtr->Enable = true;
                }
            }
        }
    }
}


//////////////////////////////////////////////////////////////
//
// Static routines
//
//

int PROTank::WriteXML(char *StrBuf, bool IncAlarms) {
    AnsiString UnitStr;
    AnsiString LevelIDStr;
    AnsiString LevelStr;
    if ( DBU_IsConfigured || (TankType == TANKTYPE_CARGO) ) {
        LevelIDStr = "Ullage>";
        LevelStr = LibGetValue(SVT_ULLAGE_UTI, this, &UnitStr) + SpaceStr + UnitStr;
    } else {
        LevelIDStr = "Level>";
        LevelStr = LibGetValue(SVT_LEVEL_SENSOR, this, &UnitStr) + SpaceStr + UnitStr;
    }
    AnsiString VolumeStr    = LibGetValue(SVT_VOLUME, this, 0, &UnitStr) + SpaceStr;
    if ( UnitStr == "m³" ) {
        UnitStr = "m3"; // PVCS does not support some fonts
    }
    VolumeStr += UnitStr;
    AnsiString VolPCntStr   = LibGetValue(SVT_VOLPERCENT, this, 0, &UnitStr) + SpaceStr + UnitStr;
    AnsiString WeightStr    = LibGetValue(SVT_WEIGHT, this, 0, &UnitStr) + SpaceStr + UnitStr;
    AnsiString TempStr      = LibGetValue(SVT_TEMP, this, 0, &UnitStr) + SpaceStr;
    if ( UnitStr == "°C" ) {
        UnitStr = "^C";
    } else {
        UnitStr = "^F";
    }
    TempStr += UnitStr;
    AnsiString TPressureStr = LibGetValue(SVT_PRESSURE, this, 0, &UnitStr) + SpaceStr + UnitStr;
    AnsiString LPressureStr = LibGetValue(SVT_LINE_PRESSURE, this, 0, &UnitStr) + SpaceStr + UnitStr;
    AnsiString CargoStr     = LibGetValue(SVT_CARGO_TYPE_NAME, this, 0);
    // Cargo colour
    AnsiString ColorStr     = LibGetValue(SVT_COLOUR, this, 0);
    AnsiString LoadRateStr  = LibGetValue(SVT_LOADRATE, 0, 0, this, 0, SVT_FLAG_ONLY_NUMBER, &UnitStr) + SpaceStr + "m3/h";

    // Alarm status and text
    //
    AnsiString AlMessageStr = "No alarm";
    int        LEDStatus    = TPC_LED_OFF;
    if ( IncAlarms ) {
        if ( !CompleteAlarmInfoList.empty() ) {
            bool                        ActiveAlarm    = false;
            time_t                      NewestAlarmAct = 0;
            time_t                      NewestAlarmAck = 0;
            set<AlarmBasic *>::iterator pBIt;
            for ( pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++ ) {
                AlarmBasic *Element = *pBIt;
                if ( Element ) {
                    switch ( Element->State ) {
                    case AlarmBasic::AlIdle :
                        break;
                    case AlarmBasic::AlActive :
                        if ( Element->Time_Rised > NewestAlarmAct ) {
                            NewestAlarmAct = Element->Time_Rised;
                            ActiveAlarm = true;
                            AlMessageStr = Element->Get_TPCMessage();
                            LEDStatus = TPC_LED_FLASH;
                        }
                        break;
                    case AlarmBasic::AlAknowledged :
                        if ( !ActiveAlarm && (Element->Time_Acknowledged > NewestAlarmAck) ) {
                            NewestAlarmAck = Element->Time_Acknowledged;
                            AlMessageStr = Element->Get_TPCMessage();
                            LEDStatus = TPC_LED_ON;
                        }
                        break;
                    }
                }
            }
        }
    }
    int tmpPtr = sprintf(StrBuf, "\t<Packet>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<PacketID>Tank</PacketID>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<TagID>%s</TagID>\r\n", TagName.c_str());

    if ( !LevelIDStr.IsEmpty() ) {
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<%s%s</%s\r\n", LevelIDStr.c_str(), LevelStr.c_str(), LevelIDStr.c_str());
    }
    if ( VolumeTab ) {
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Volume>%s</Volume>\r\n", VolumeStr.c_str());
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Volumepercent>%s</Volumepercent>\r\n", VolPCntStr.c_str());
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Weight>%s</Weight>\r\n", WeightStr.c_str());
    }
    if ( TemperaturePtr ) {
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Temperature>%s</Temperature>\r\n", TempStr.c_str());
    }
    if ( PressurePtr ) {
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Tankpressure>%s</Tankpressure>\r\n", TPressureStr.c_str());
    }
    if ( LPressurePtr ) {
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Linepressure>%s</Linepressure>\r\n", LPressureStr.c_str());
    }
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Cargotype>%s</Cargotype>\r\n", CargoStr.c_str());
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Cargocolor>%s</Cargocolor>\r\n", ColorStr.c_str());
    if ( VolumeTab ) {
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Loadrate>%s</Loadrate>\r\n", LoadRateStr.c_str());
    }
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Alarmstatus>%i</Alarmstatus>\r\n", LEDStatus);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Alarmtext>%s</Alarmtext>\r\n", AlMessageStr.c_str());
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t</Packet>\r\n");
    return tmpPtr;
}


void PROTank::SetState(TankState newState) {
    switch ( newState ) {
    case tSeaGoing :
    case tLoad :
    case tDischarge :
    case tTankCleaning :
    case tUndefined :
        State = newState;
        break;
    default:
        break;
    }
    if ( !ExcludeState && newState != tUndefined ) {
        const AlarmBasic::StateAlarmTable myAlarmSet[] = {
            //                                  tSeaGoing   , tLoad         , tDischarge    , tTankCleaning, tUndefined
            { (AlarmBasic *)OverfillPtr     , { EnableFalse , EnableTrue    , EnableFalse   , EnableFalse } },
            { (AlarmBasic *)HighLevelPtr    , { EnableFalse , EnableTrue    , EnableFalse   , EnableFalse } },
            { (AlarmBasic *)LowLevelPtr     , { EnableFalse , EnableFalse   , EnableTrue    , EnableFalse } },
         // { (AlarmBasic *)LoLoLevelPtr    , { EnableTrue  , EnableFalse   , EnableTrue    , EnableFalse } },  // Exlude LoLo alarm
            {(AlarmBasic * )LevelChangeAPtr , { EnableTrue  , EnableFalse   , EnableFalse   , EnableFalse } },
        };
        for ( unsigned i = 0; i < NELEMENTS(myAlarmSet); i++ ) {
            AlarmBasic *AlPtr = myAlarmSet[i].AlarmPtr;
            if ( AlPtr && !AlPtr->Locked ) {
                myAlarmSet[i].AlarmPtr->SetEnable(myAlarmSet[i].Enable[State]);
            }
        }
        if ( PressurePtr ) {
            PressurePtr->SetState(newState);
        }
        if ( TemperaturePtr ) {
            TemperaturePtr->SetState(newState);
        }
    }
}
int PROTank::LCWriteXML(char *StrBuf) {
    int tmpPtr = sprintf(StrBuf, "\t<Packet>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<PacketID>Tank</PacketID>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<TagID>%s</TagID>\r\n", TagName.c_str());
    if ( DBU_IsConfigured || (TankType == TANKTYPE_CARGO) ) {
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Ullage>%0.3f</Ullage>\r\n", UllageRef);
    }
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Level>%0.3f</Level>\r\n", LevelAtRef);
    if ( VolumeTab ) {
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Volume>%0.1f</Volume>\r\n", Volume);
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Volumepercent>%0.1f</Volumepercent>\r\n", VolumePercent);
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Weight>%0.1f</Weight>\r\n", Weight);
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Loadrate>%0.1f</Loadrate>\r\n", LoadRate);
    }
    if ( TemperaturePtr ) {
        tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Temperature>%0.1f</Temperature>\r\n", TemperaturePtr->GetTemperature());
    }
    AnsiString CargoName;
    CargoType->GetStringValue(SVT_CARGO_TYPE_NAME, 0, CargoName);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Cargotype>%s</Cargotype>\r\n", CargoName.c_str());
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<ObservedDensity>%0.5f</ObservedDensity>\r\n", Density);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Density>%0.5f</Density>\r\n", CargoType->OD1);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<BaseTemperature>%0.1f</BaseTemperature>\r\n", CargoType->RefTmp1);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Cargocolor>0x%0x</Cargocolor>\r\n", CargoType->Colour);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t</Packet>\r\n");
    return tmpPtr;
}


bool PROTank::CalculateMetriTape(void) {
    Density = CompDns;
    float tmpLevel = MetriTapeSns->Calculate();
    if ( MetriTapeSns->ResultOK ) {
        HasLevelSensors = true;
        if ( tmpLevel > LEVEL_NOISE_LIMIT_METRI_TAPE ) {
            tmpLevel += MetriTapeSns->AdjustedDistance;
            tmpLevel -= LevelOffset;
            if ( tmpLevel < 0.0 ) {
                tmpLevel = 0.0;
            }
            float tmpLevelFC    = tmpLevel + PROSystemData::TrimListCorrection(cDLFC, cDTFC) - DBotManMsrPnt;
            float tmpLevelAtRef = tmpLevel + PROSystemData::TrimListCorrection(cDLR, cDTR) - DBotManMsrPnt;

            if ( tmpLevelFC < 0.0 ) {
                tmpLevelFC = 0.0;
            }
            if ( tmpLevelAtRef < 0.0 ) {
                tmpLevelAtRef = 0.0;
            }
            Level = tmpLevel;
            LevelFC = tmpLevelFC;
            LevelAtRef = tmpLevelAtRef;
            float tmpUllageRef   = AdjustedDBU - LevelAtRef;
            float tmpUllageFC    = AdjustedDBU - LevelFC;
            float tmpUllageAtSns = AdjustedDBU - Level - DVManMsrPntToSns;
            if ( tmpUllageRef < 0.0 ) {
                tmpUllageRef = 0.0;
            }
            if ( tmpUllageFC < 0.0 ) {
                tmpUllageFC = 0.0;
            }
            if ( tmpUllageAtSns < 0.0 ) {
                tmpUllageAtSns = 0.0;
            }
            UllageRef   = tmpUllageRef;
            UllageFC    = tmpUllageFC;
            UllageAtSns = tmpUllageAtSns;
            if ( tmpLevel > NoiseLimitR ) {
                NotEmptyTank = true;
            } else {
                NotEmptyTank = false;
            }
        } else {
            HasLevelSensors = false;
            NotEmptyTank = false;
        }
    } else {
        HasLevelSensors = false;
        NotEmptyTank = false;
    }
    return NotEmptyTank;
}

bool PROTank::CalculateHSH_LNG_Float(void) {
    Density = CompDns;
    float tmpLevel = HSH_FloatSns->Calculate();
    if ( HSH_FloatSns->ResultOK ) {
        HasLevelSensors = true;
        if ( tmpLevel > LEVEL_NOISE_LIMIT_HSH_LNG_SWITCH ) {
            tmpLevel -= LevelOffset;
            if ( tmpLevel < 0.0 ) {
                tmpLevel = 0.0;
            }
            float tmpLevelFC    = tmpLevel + PROSystemData::TrimListCorrection(cDLFC, cDTFC) - DBotManMsrPnt;
            float tmpLevelAtRef = tmpLevel + PROSystemData::TrimListCorrection(cDLR, cDTR) - DBotManMsrPnt;

            if ( tmpLevelFC < 0.0 ) {
                tmpLevelFC = 0.0;
            }
            if ( tmpLevelAtRef < 0.0 ) {
                tmpLevelAtRef = 0.0;
            }
            Level = tmpLevel;
            LevelFC = tmpLevelFC;
            LevelAtRef = tmpLevelAtRef;
            float tmpUllageRef    = AdjustedDBU - LevelAtRef;
            float tmpUllageFC     = AdjustedDBU - LevelFC;
            float tmpUllageAtSns  = AdjustedDBU - Level - DVManMsrPntToSns;
            if ( tmpUllageRef < 0.0 ) {
                tmpUllageRef = 0.0;
            }
            if ( tmpUllageFC < 0.0 ) {
                tmpUllageFC = 0.0;
            }
            if ( tmpUllageAtSns < 0.0 ) {
                tmpUllageAtSns = 0.0;
            }
            UllageRef   = tmpUllageRef;
            UllageFC    = tmpUllageFC;
            UllageAtSns = tmpUllageAtSns;
            if ( tmpLevel > NoiseLimitR ) {
                NotEmptyTank = true;
            } else {
                NotEmptyTank = false;
            }
        } else {
            HasLevelSensors = false;
            NotEmptyTank = false;
        }
    } else {
        HasLevelSensors = false;
        NotEmptyTank = false;
    }
    return NotEmptyTank;
}

bool PROTank::CalculateRadarUllage(void) {
    Density = CompDns;
    float tmpUllageSum = 0.0;
    float tmpLevelSum  = 0.0;
    int   RadarCnt     = 0;
    int   RadarOKCnt   = 0;

    for ( unsigned i = 0; i < RadarSensors.size(); i++ ) {
        float tmpUllageAtSns = RadarSensors[i]->Calculate();
        if ( RadarSensors[i]->ResultOK ) {
            RadarOKCnt++;
            float tmpLevel = RadarSensors[i]->Distance - tmpUllageAtSns;
            // For ullage measurement, must use level to check for NoiseLimitR
            if ( tmpLevel > NoiseLimitR ) {
                RadarCnt++;
                tmpUllageSum += tmpUllageAtSns;
                tmpLevelSum  += tmpLevel;
            }
        }
    }
    if ( RadarOKCnt ) {
        HasLevelSensors = true;
        if ( RadarCnt ) {
            float tmpUllageRef;
            float tmpUllageFC;
            float tmpLevel;
            float tmpLevelFC;
            float tmpLevelAtRef;
            if ( tmpLevelSum ) {
                NotEmptyTank = true;
                float tmpUllageAtSns = tmpUllageSum / float(RadarCnt);
                tmpUllageAtSns += LevelOffset;
                if ( tmpUllageAtSns <= 0.0 ) {
                    UllageAtSns = 0.0;
                } else if ( tmpUllageAtSns > AdjustedDBU - DVManMsrPntToSns ) {
                    UllageAtSns = AdjustedDBU - DVManMsrPntToSns;
                } else {
                    UllageAtSns = tmpUllageAtSns;
                }
                if ( UllageAtSns <= 0.0 ) {
                    tmpUllageRef  = 0.0;
                    tmpUllageFC   = 0.0;
                    tmpLevel      = AdjustedDBU;
                    tmpLevelFC    = AdjustedDBU;
                    tmpLevelAtRef = AdjustedDBU;
                } else if ( UllageAtSns >= AdjustedDBU - DVManMsrPntToSns ) {
                    tmpUllageRef  = AdjustedDBU;
                    tmpUllageFC   = AdjustedDBU;
                    tmpLevel      = 0.0;
                    tmpLevelFC    = 0.0;
                    tmpLevelAtRef = 0.0;
                } else {
                    tmpUllageRef = tmpUllageAtSns - PROSystemData::TrimListCorrection(cDLR, cDTR) + DVManMsrPntToSns;
                    tmpUllageFC  = tmpUllageAtSns - PROSystemData::TrimListCorrection(cDLFC, cDTFC) + DVManMsrPntToSns;
                    if ( tmpUllageRef < 0.0 ) {
                        tmpUllageRef = 0.0;
                    } else if ( tmpUllageRef > AdjustedDBU ) {
                        tmpUllageRef = AdjustedDBU;
                    }
                    if ( tmpUllageFC < 0.0 ) {
                        tmpUllageFC = 0.0;
                    } else if ( tmpUllageFC > AdjustedDBU ) {
                        tmpUllageFC = AdjustedDBU;
                    }

                    tmpLevel      = tmpLevelSum / float(RadarCnt);
                    tmpLevel     -= LevelOffset;
                    tmpLevelFC    = tmpLevel + PROSystemData::TrimListCorrection(cDLFC, cDTFC) - DBotManMsrPnt;
                    tmpLevelAtRef = tmpLevel + PROSystemData::TrimListCorrection(cDLR, cDTR) - DBotManMsrPnt;
                }
                if ( tmpLevelFC < 0.0 ) {
                    tmpLevelFC = 0.0;
                }
                if ( tmpLevelAtRef < 0.0 ) {
                    tmpLevelAtRef = 0.0;
                }
            } else {
                NotEmptyTank   = false;
                tmpUllageRef  = AdjustedDBU;
                tmpUllageFC   = AdjustedDBU;
                tmpLevel      = 0.0;
                tmpLevelFC    = 0.0;
                tmpLevelAtRef = 0.0;

            }
            UllageRef  = tmpUllageRef;
            UllageFC   = tmpUllageFC;
            Level      = tmpLevel;
            LevelAtRef = tmpLevelAtRef;
            LevelFC    = tmpLevelFC;
        } else {
            NotEmptyTank = false;
        }
    } else {
        HasLevelSensors = false;
        NotEmptyTank = false;
    }
    return NotEmptyTank;
}

bool PROTank::CalculateOtherSns(void) {
    float tmpLevel = 0.0;
    if ( !RadarSensors.empty() ) {
        if ( HasRadarAndPressure ) {
            float LevelFromRadar    = 0.0;
            float LevelFromPress    = 0.0;
            bool  HasLevelFromPress = false;
            bool  HasPressureSensor = false;
            bool  HasRadarSensor    = false;
            bool  HasLevelFromRadar = false;

            float tmpLevelSum       = 0.0;
            int   RadarCnt          = 0;
            for ( unsigned i = 0; i < RadarSensors.size(); i++ ) {
                // Most likely a hybrid system or very old.
                // Include trim and list correction for radar with level calculation
                // Radar should give distance, not level 
                float RawLevel = RadarSensors[i]->AdjustedDistance - RadarSensors[i]->Calculate();
                if ( RawLevel < 0.0 ) {
                    RawLevel = 0.0;
                }
                float tmpLevel = AdjustedDBU - RadarSensors[i]->AdjustedDistance + RawLevel;
                if ( RadarSensors[i]->ResultOK ) {
                    RadarCnt++;
                    // RawLevel only used to control noise limit and use of pressure sensor
                    if ( RawLevel  > NoiseLimitR ) {
                        tmpLevel += PROSystemData::TrimListCorrection(cRadarDLR, cRadarDTR);
                        if ( RawLevel < 0.0 ) {
                            RawLevel = 0.0;
                        }
                        tmpLevelSum += tmpLevel;
                    }
                }
            }
            if ( RadarCnt ) {
                LevelFromRadar = tmpLevelSum / float(RadarCnt) ;
                if ( LevelFromRadar ) {
                    HasRadarSensor = true;
                    HasLevelFromRadar = true;
                } else {
                    HasRadarSensor = true;
                }
            }
            float SnsPress         = 0.0;
            float AdjustedDistance = 0.0;
            if ( !LevelPressures.empty() ) {
                AIPressSensor *SnsPtr = LevelPressures[0];
                AdjustedDistance = SnsPtr->AdjustedDistance;
                SnsPress = SnsPtr->Calculate();
                if ( SnsPtr->ResultOK ) {
                    HasPressureSensor = true;
                    if ( SnsPress >= GetNoiseLimitB() ) {
                        LevelFromPress = SnsPress / (CompDns - D_AIR_ADJ) * GravityCorrection + AdjustedDistance;
                        LevelDifference = FilterVal(LevelDifference, fabs(LevelFromPress - LevelFromRadar), LevelDifferenceFilterDegree);
                        HasLevelFromPress = true;
                    } else {
                        LevelFromPress  = 0.0;
                        LevelDifference = 0.0;
                    }
                } else {
                    LevelDifference = 0.0;
                }
            }
            HasLevelSensors = HasRadarSensor || HasPressureSensor;
            NotEmptyTank = HasLevelFromRadar || HasLevelFromPress;
            if ( HasLevelFromRadar ) {
                tmpLevel = LevelFromRadar;
            } else if ( HasLevelFromPress ) {
                tmpLevel = LevelFromPress;
            }
            if ( HasLevelFromPress && HasLevelFromRadar ) {
                /*
                if ( fabs(LevelFromPress-LevelFromRadar)>MAX_RADAR_PRESS_SNS_DIFF ) {
                    tmpLevel = LevelFromPress;
                } else {
                    tmpLevel = LevelFromRadar;
                }
                */
                // Level must be more then a defined limit StartLevelMsrdDns which defaults to 2.0 meters before calculation of measured density
                if ( tmpLevel > StartLevelMsrdDns ) {
                    float MsrdDns = GravityCorrection * SnsPress / (LevelFromRadar - AdjustedDistance) + D_AIR_ADJ;

                    if ( (MsrdDns >= MIN_DENSITY) && (MsrdDns <= MAX_DENSITY) ) {
                        // Filter the measured density
                        if ( HasMeasuredDensity ) {
                            FilteredMsrdDns = (FilteredMsrdDns * 10 + MsrdDns) / 11;
                        } else {
                            HasMeasuredDensity = true;
                            FilteredMsrdDns = MsrdDns;
                        }
                        MeasuredDns = FilteredMsrdDns;
                    } else {
                        HasMeasuredDensity = false;
                        MeasuredDns = 0.0;
                    }

                    if ( UseMeasuredDensity ) {
                        if ( HasMeasuredDensity ) {
                            Density = FilteredMsrdDns;
                            UsePrevCalcDns = true;
                        } else {
                            Density = CompDns;
                            UsePrevCalcDns = false;
                        }
                    } else {                // Measured density is off
                        Density = CompDns;
                        UsePrevCalcDns = false;
                    }
                } else {                // Measured density is off
                    Density = CompDns;
                    UsePrevCalcDns = false;
                }
            } else {
                Density = CompDns;
                UsePrevCalcDns = false;
                /*
                if ( HasLevelFromRadar ) {
                    tmpLevel = LevelFromRadar;
                } else if ( HasLevelFromPress ) {
                    tmpLevel = LevelFromPress;
                }
                */
            }
        } else {
            Density = CompDns;

            float tmpLevelSum = 0.0;
            int   RadarCnt    = 0;
            for ( unsigned i = 0; i < RadarSensors.size(); i++ ) {
                float tmpRawLevel = RadarSensors[i]->Calculate();
                if ( RadarSensors[i]->ResultOK ) {
                    RadarCnt++;
                    // Make sure that we don't get a negative value!
                    if ( tmpRawLevel < 0.0 ) {
                        tmpRawLevel = 0.0;
                    }
                    // For backward compatibility. Radar noise limit will not work correctly
                    // when distance is 0.
                    // When distance above limit it will use the adjusted distance in the
                    // calculation.
                    // NOTE: C00247 has Distance set to 0.001!
                    if ( RadarSensors[i]->Distance > RADAR_MIN_DISTANCE_SETTING ) {
                        float tmpLevel = RadarSensors[i]->AdjustedDistance - tmpRawLevel;
                        if ( tmpLevel > 0.0 ) {
                            tmpLevelSum += tmpLevel;
                        }
                    } else {
                        float tmpLevel = tmpRawLevel - RadarSensors[i]->AdjustedDistance;
                        if ( tmpLevel < 0.0 ) {
                            tmpLevel = 0.0;
                        }
                        tmpLevelSum += tmpLevel;
                    }
                }
            }
            if ( RadarCnt ) {
                tmpLevel = tmpLevelSum / float(RadarCnt);
                if ( tmpLevel > NoiseLimitR ) {
                    HasLevelSensors = true;
                    NotEmptyTank = true;
                } else {
                    HasLevelSensors = true;
                    NotEmptyTank = false;
                }
            } else {
                HasLevelSensors = false;
                NotEmptyTank = false;
            }
        }
    } else {
        float PrevMaxDB                = 0.0, MaxDB = -1000.0;
        float PrevMaxDBSnsPress        = 0.0, MaxDBSnsPress = 0.0;
        int   NumberOfSubmergedSensors = 0;
        int   NumberOfUseableSensors   = 0;
        if ( HasRedundancy ) {
            float LevelSum = 0.0;
            float MaxLevel = 0.0;
            float MinLevel = MAXFLOAT;
            for ( unsigned i = 0; i < LevelPressures.size(); i++ ) {
                AIPressSensor *SnsPtr = LevelPressures[i];
                float         Value   = SnsPtr->Calculate();
                if ( SnsPtr->ResultOK ) {
                    NumberOfUseableSensors++;
                    if ( Value >= GetNoiseLimitB() ) {
                        NumberOfSubmergedSensors++;
                        // Calculate the level at the sensor location
                        float tmpLevel = Value / (CompDns - D_AIR_ADJ) * GravityCorrection + SnsPtr->AdjustedDistance;
                        MaxLevel = MAX(MaxLevel, tmpLevel);
                        MinLevel = MIN(MinLevel, tmpLevel);
                        LevelSum += tmpLevel;
                    }
                }
            }
            if ( NumberOfSubmergedSensors ) {
                tmpLevel = LevelSum / NumberOfSubmergedSensors;
                LevelDifference = FilterVal(LevelDifference, MaxLevel - MinLevel, LevelDifferenceFilterDegree);
            } else {
                tmpLevel = 0.0;
                LevelDifference = 0.0;
            }
            Density = CompDns;
            MeasuredDns = 0.0;   // No density to calculate
            UsePrevCalcDns = false;
        } else {
            for ( unsigned i = 0; i < LevelPressures.size(); i++ ) {
                AIPressSensor *SnsPtr    = LevelPressures[i];
                float         NoiseLimit;
                if ( i ) {
                    NoiseLimit = GetNoiseLimitU();
                } else {
                    NoiseLimit = GetNoiseLimitB();
                }
                float Value = SnsPtr->Calculate();
                if ( SnsPtr->ResultOK ) {
                    NumberOfUseableSensors++;
                    if ( Value >= NoiseLimit ) {
                        NumberOfSubmergedSensors++;
                        if ( SnsPtr->AdjustedDistance > MaxDB ) {
                            PrevMaxDBSnsPress = MaxDBSnsPress;
                            PrevMaxDB = MaxDB;
                            MaxDBSnsPress = Value;
                            MaxDB = SnsPtr->AdjustedDistance;
                            //SnsPtr->Offset   -= 0.005; // Simple load rate test
                        }
                    }
                }
            }
            switch ( NumberOfSubmergedSensors ) {
            default:
                //  Correct the density for gravity and vacuum
                if ( fabs(MaxDB - PrevMaxDB) > StartLevelMsrdDns ) {
                    float MsrdDns = GravityCorrection * (PrevMaxDBSnsPress - MaxDBSnsPress) / (MaxDB - PrevMaxDB) + D_AIR_ADJ;

                    if ( (MsrdDns >= MIN_DENSITY) && (MsrdDns <= MAX_DENSITY) ) {
                        // Filter the measured density
                        if ( HasMeasuredDensity ) {
                            FilteredMsrdDns = (FilteredMsrdDns * 10 + MsrdDns) / 11;
                        } else {
                            HasMeasuredDensity = true;
                            FilteredMsrdDns = MsrdDns;
                        }
                        MeasuredDns = FilteredMsrdDns;
                    } else {
                        HasMeasuredDensity = false;
                        MeasuredDns = 0.0;
                    }

                    if ( UseMeasuredDensity ) {
                        if ( HasMeasuredDensity ) {
                            Density = FilteredMsrdDns;
                            UsePrevCalcDns = true;
                        } else {
                            Density = CompDns;
                            UsePrevCalcDns = false;
                        }
                    } else {                // Measured density is off
                        Density = CompDns;
                        UsePrevCalcDns = false;
                    }
                } else {                // Measured density is off
                    Density = CompDns;
                    UsePrevCalcDns = false;
                }
                // Calculate the level at the sensor location
                tmpLevel = MaxDBSnsPress / (Density - D_AIR_ADJ) * GravityCorrection + MaxDB;
                break;
            case 1:
                //  Only bottom or middle sensor found. Use operator density
                // Not sensors available for density calculation
                HasMeasuredDensity = false;
                if ( UsePrevCalcDns && UseMeasuredDensity
                     && ((FilteredMsrdDns >= MIN_DENSITY) && (FilteredMsrdDns <= MAX_DENSITY)) ) {
                    Density = FilteredMsrdDns;
                } else {
                    Density = CompDns;
                    MeasuredDns = 0.0; // No density to calculate
                    UsePrevCalcDns = false;
                }
                // Calculate the level at the sensor location
                tmpLevel = MaxDBSnsPress / (Density - D_AIR_ADJ) * GravityCorrection + MaxDB;
                break;
            case 0:
                tmpLevel = 0.0;
                Density = CompDns;
                MeasuredDns = 0.0;   // No density to calculate
                UsePrevCalcDns = false;
                break;
            }
        } // End if
        HasLevelSensors = (bool)NumberOfUseableSensors;
        NotEmptyTank = (bool)NumberOfSubmergedSensors;
    }
    tmpLevel -= LevelOffset;
    if ( tmpLevel < 0.0 ) {
        tmpLevel = 0.0;
    }
    if ( IsLevelInsideWindow(tmpLevel, Level) ) {
        Level = tmpLevel;
    }
    // See if we have a level
    if ( NotEmptyTank ) {
        //float TrimVal = PROSystemData::TrimValue;
        //float Correction = TrimVal*cDLFC;
        float tmpLevelFC    = Level + PROSystemData::TrimListCorrection(cDLFC, cDTFC) - DBotManMsrPnt;
        float TmpLevelAtRef = Level + PROSystemData::TrimListCorrection(cDLR, cDTR) - DBotManMsrPnt;
        if ( AdjustedDBU ) {
            if ( tmpLevelFC > AdjustedDBU ) {
                LevelFC = AdjustedDBU;
            } else if ( tmpLevelFC < 0.0 ) {
                LevelFC = 0.0;
            } else {
                LevelFC = tmpLevelFC;
            }
            if ( TmpLevelAtRef > AdjustedDBU ) {
                LevelAtRef = AdjustedDBU;
            } else if ( TmpLevelAtRef < 0.0 ) {
                LevelAtRef = 0.0;
            } else {
                LevelAtRef = TmpLevelAtRef;
            }
            float tmpUllage      = AdjustedDBU - LevelAtRef;
            float tmpUllageFC    = AdjustedDBU - LevelFC;
            float tmpUllageAtSns = AdjustedDBU - Level;
            if ( tmpUllage <= 0.0 ) {
                tmpUllage = 0.0;
            }
            if ( tmpUllageFC <= 0.0 ) {
                tmpUllageFC = 0.0;
            }
            if ( tmpUllageAtSns <= 0.0 ) {
                tmpUllageAtSns = 0.0;
            }
            UllageRef   = tmpUllage;
            UllageFC    = tmpUllageFC;
            UllageAtSns = tmpUllageAtSns;

        } else {
            LevelFC = tmpLevelFC;
            LevelAtRef = TmpLevelAtRef;
        }
    } else {
        Level = 0.0;
        LevelFC = 0.0;
        LevelAtRef = 0.0;
        Sounding = 0.0;
        if ( AdjustedDBU ) {
            UllageRef = AdjustedDBU;
            UllageFC = AdjustedDBU;
            UllageAtSns = AdjustedDBU;
        }
    }
    return NotEmptyTank;
}
float PROTank::GetCorrectWeight(void) {
    float Wgt;
    if ( HasLCData() ) {
        Wgt = LCWeight;
    } else if ( VolumeTab ) {
        Wgt = GetCorrectedWeight(Weight, Density);
    } else {
        Wgt = 0.0;
    }
    return Wgt;
}

bool PROTank::HasInstalledLevelPressureSensors(void) {
    return !LevelPressures.empty();
}

AnsiString PROTank::ZeroSetAllTankPressureSensor(set<PRogramObjectBase *>TankSet, bool Local) {
    AnsiString                         TmpString;
    set<PRogramObjectBase *>::iterator pBIt;
    for ( pBIt = TankSet.begin(); pBIt != TankSet.end(); pBIt++ ) {
        TmpString += ((PROTank *)(*pBIt))->ZeroSetTankPressureSensor(Local);
    }
    return (TmpString);
}

AnsiString PROTank::ZeroSetAllLevelSensors(set<PRogramObjectBase *>TankSet, bool Local) {
    AnsiString                         TmpString;
    set<PRogramObjectBase *>::iterator pBIt;
    for ( pBIt = TankSet.begin(); pBIt != TankSet.end(); pBIt++ ) {
        TmpString += ((PROTank *)(*pBIt))->ZeroSetLevelSensors(Local);
    }

    return (TmpString);
}

void PROTank::CalcSteelCorrection(void) {
    if ( TemperaturePtr ) {
        SteelExp = 1.0 + STEEL_EXPANSION / 100.0 * (Temperature - 20.0);   // calculate steel exp.
        AdjustedDBU = DBotUllRefPnt * SteelExp;
    }
    // Adjust DB
    for ( unsigned i = 0; i < LevelPressures.size(); i++ ) {
        LevelPressures[i]->AdjustedDistance = LevelPressures[i]->Distance * SteelExp;
    }
}

float PROTank::GetTemperature(void) {
    return Temperature;
}

void PROTank::SetTemperature(float NewTemp) {
    Temperature = NewTemp;
}

float PROTank::GetPressure(void) {
    return Pressure;
}
void PROTank::SetPressure(float NewPress) {
    Pressure = NewPress;
}

float PROTank::GetWeightFromGas(void) {
    double TotalGasWeight;
    if ( VolumeTab ) {
        double TotalVolume = VolumeTab->MaxY;
        double GasVolume   = TotalVolume - Volume; //VolumeAtRefTmp();
        double GasDensity  = CargoType->GasDensity(Temperature, Pressure);
        double GasWeight   = GasVolume * GasDensity;
        TotalGasWeight = GasWeight;
    } else {
        TotalGasWeight = 0.0;
    }
    return TotalGasWeight;
}
float PROTank::GetWeightFromLPG(void) {
    return GetCorrectedWeight(Weight, Density) + GetWeightFromGas();
}



PROTank* PROTank::FindTankById(int tankId) {
    PROTank                     *pTank = NULL;
    vector<PROTank *>::iterator iter   = PROTank::TankVector.begin();

    while ( iter != PROTank::TankVector.end() ) {
        if ( *iter != NULL && ((int)(*iter)->IDNumber) == tankId ) {
            pTank = *iter;
            break;
        } else {
            ++iter;
        }
    }
    return pTank;
}


void PROTank::LoadTDUTankPlanPosition(TSNConfigString &ConfigString) {
    AnsiString ConfigName = "TDUTankPlanPos";
    bool       NoError    = true;
    int        ErrorLine  = 0;
    int        Key;
    int        xpos       = 0;
    int        ypos       = 0;
    int        page       = 0;
    const int  maxX       = 12;
    const int  maxY       = 60;
    const int  maxPages   = maxY / 10;

    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)ConfigName, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            case C_XPOS:
                xpos = (unsigned)ConfigString.ReadInteger(ErrorLine) - 1;
                if ( xpos < maxX ) {
                    TDUTankPlacement.xpos = xpos;
                }
                break;
            case C_YPOS:
                ypos = (unsigned)ConfigString.ReadInteger(ErrorLine) - 1;
                if ( ypos < maxY ) {
                    TDUTankPlacement.ypos = ypos;
                }
                break;
            case C_PAGE:
                page = (unsigned)ConfigString.ReadInteger(ErrorLine) - 1;
                if ( page < maxPages ) {
                    TDUTankPlacement.page = page;
                }
                break;
            case C_TDU_TANK_PLAN_POS_END:
                TDUTankPlacement.initialized = true;
                break;
            default:
                GiveConfigWarning((AnsiString)ConfigName, InputKeyWord, ConfigString.LineCount);
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_TDU_TANK_PLAN_POS_END) );
}


/*
void PROTank::FilterTankWashingMachinesByTank(PROTank* tank, vector<PROTankWashingMachine *> &destination)
{
    vector<PROTankWashingMachine*>::iterator twmIter = PROTank::TankWashingMachineVector.begin();
    vector<PROTankWashingMachine*>::iterator endIt = PROTank::TankWashingMachineVector.end();

    for (;twmIter != endIt; twmIter++)
    {
        PROTankWashingMachine* pTWM = *twmIter;

        if (pTWM->TankId == tank->IDNumber)
        {
            destination.push_back(pTWM);
        }
    }
}
*/

bool PROTank::IsStaticValue(int ValueKey) {
    switch ( ValueKey ) {
    case SVT_LC_VOLUME      :
    case SVT_LC_WEIGHT      :
    case SVT_LC_DENSITY     :
    case SVT_VOLUME         :
    case SVT_WEIGHT         :
    case SVT_VOLPERCENT     :
    case SVT_DENSITY        :
    case SVT_REF_DNS1       :
    case SVT_REF_DNS2       :
    case SVT_REF_TMP2       :
    case SVT_TEMP           :
    case SVT_LO_ULLAGE_LIM  :
    case SVT_LOLO_ULLAGE_LIM:
    case SVT_HI_ULLAGE_LIM  :
    case SVT_LO_LEVEL_LIMIT :
    case SVT_HI_LEVEL_LIMIT :
        return true;
    default:
        return false;

    }

}

bool PROTank::UTIUllageAvailable(void) {
    return HasDVSnsToUTI;
}

int PROTank::GetSensorEEPROM_Status(int ValueKey) {
	int Status = AD_NOT_USED;
    switch ( ValueKey ) {
    case SVT_BP_SERIAL_NO :
    case SVT_BP_SERIAL_NO1:
    case SVT_BP_SERIAL_NO2:
    case SVT_BP_SERIAL_NO3:
    case SVT_MP_SERIAL_NO :
    case SVT_UP_SERIAL_NO :
    case SVT_TP_SERIAL_NO :
        {
            AnalogInput *SnsPtr = NULL;
			switch ( ValueKey ) {
            case SVT_BP_SERIAL_NO :
                SnsPtr = FindAnalogInput(C_AI_LOC_BOTTOM);
                break;
            case SVT_MP_SERIAL_NO :
                SnsPtr = FindAnalogInput(C_AI_LOC_MIDDLE);
                break;
            case SVT_UP_SERIAL_NO :
                SnsPtr = FindAnalogInput(C_AI_LOC_UPPER);
                break;
            case SVT_TP_SERIAL_NO :
                SnsPtr = FindAllAnalogInput(C_AI_LOC_VAPOUR, AI_SENSOR_PRESS);
				if ( !SnsPtr ) {
                    SnsPtr = FindAllAnalogInput(C_AI_LOC_DECK, AI_SENSOR_PRESS);
                }
                break;
            case SVT_BP_SERIAL_NO1:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY1);
                break;
            case SVT_BP_SERIAL_NO2:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY2);
                break;
            case SVT_BP_SERIAL_NO3:
                SnsPtr = FindAnalogInput(C_AI_LOC_REDUNDANCY3);
                break;
            }

            if ( SnsPtr ) {
				Status = SnsPtr->GetEEPROM_Status();
            }
        }
        break;
    }
    return Status;
}



/*--------------------------------------------------
  From the loading calculator

*/

void PROTank::InputUllageAtRef(float UllageRef) {
    float Level = DBotUllRefPnt - UllageRef;
    Level -= PROSystemData::TrimListCorrection(cDLFC - cDLR, cDTFC - cDTR);
    InputLevelFC(Level);
}

void PROTank::InputUllageAtSensor(float pUllageAtSns) {
    Level = DBotUllRefPnt - pUllageAtSns;
    Level -= PROSystemData::TrimListCorrection(cDLFC, cDTFC);
    InputLevelFC(Level);
}

void PROTank::InputUllageFC(float Ullage) {
    float Level = DBotUllRefPnt - Ullage;
    if ( Level < 0.0 ) {
        Level = 0.0;
    }
    InputLevelFC(Level);
}

void PROTank::InputLevelAtRef(float pLevel) {
    Level  -= PROSystemData::TrimListCorrection(cDLR, cDTR);
    pLevel -= PROSystemData::TrimListCorrection(cDLFC - cDLR, cDTFC - cDTR);
    InputLevelFC(pLevel);
}

void PROTank::InputLevelAtSensor(float pLevel) {
    Level = pLevel;
    pLevel -= PROSystemData::TrimListCorrection(cDLFC, cDTFC);
    InputLevelFC(pLevel);
}


void PROTank::InputLevelFC(float pLevel) {
    if ( pLevel ) {
        LevelFC     = pLevel + 0.0005;
        LevelAtRef  = pLevel + PROSystemData::TrimListCorrection(cDLFC - cDLR, cDTFC - cDTR) + 0.0005;
        Level       = pLevel + PROSystemData::TrimListCorrection(cDLFC, cDTFC) + 0.0005;
        UllageRef   = DBotUllRefPnt - LevelAtRef + 0.0005;
        UllageFC    = DBotUllRefPnt - LevelFC + 0.0005;
        UllageAtSns = DBotUllRefPnt - Level + 0.0005;
        if ( LevVolumeTab ) {
            Volume          = LevVolumeTab->Calc_Y(LevelFC) + 0.00005;
            VolumePercent   = Volume / LevVolumeTab->MaxY * 100.0 + 0.0005;
        } else if ( UllVolumeTab ) {
            Volume          = UllVolumeTab->Calc_Y(UllageFC) + 0.00005;
            VolumePercent   = Volume / UllVolumeTab->MaxY * 100.0 + 0.0005;
        }
        Weight          = Density * Volume;
        if ( SoundingTab ) {
            float tmpSounding = SoundingTab->Calc_X(Volume);
            tmpSounding += PROSystemData::TrimListCorrection(cDLFC - cDLR, cDTFC - cDTR);
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
        Level           = 0.0;
        Volume          = 0.0;
        VolumePercent   = 0.0;
        Weight          = 0.0;
        Sounding        = 0.0;
    }
}

void PROTank::InputVolumePercent(float VolPercent) {
    if ( LevVolumeTab ) {
        float tmpLevelFC =  LevVolumeTab->Calc_XPercent(VolPercent);
        if ( tmpLevelFC < 0.0 ) {
            tmpLevelFC = 0.0;
        }
        InputLevelFC(tmpLevelFC);
    } else if ( UllVolumeTab ) {
        float tmpUllageFC =  UllVolumeTab->Calc_XPercent(VolPercent);
        if ( tmpUllageFC < 0.0 ) {
            tmpUllageFC = 0.0;
        }
        InputUllageFC(tmpUllageFC);
    }
    VolumePercent = VolPercent;
}

void PROTank::InputVolume(float Vol) {
    if ( LevVolumeTab ) {
        float tmpLevelFC =  LevVolumeTab->Calc_X(Vol);
        if ( tmpLevelFC < 0.0 ) {
            tmpLevelFC = 0.0;
        }
        InputLevelFC(tmpLevelFC);
    } else if ( UllVolumeTab ) {
        float tmpUllageFC =  UllVolumeTab->Calc_X(Vol);
        if ( tmpUllageFC < 0.0 ) {
            tmpUllageFC = 0.0;
        }
        InputUllageFC(tmpUllageFC);
    }
    Volume = Vol;
}

void PROTank::InputWeight(float Wgt) {
    Wgt = CorrectToWeightInVacuum(Wgt, Density);
    if ( LevVolumeTab ) {
        float tmpLevelFC =  LevVolumeTab->Calc_X(Wgt / Density);
        if ( tmpLevelFC < 0.0 ) {
            tmpLevelFC = 0.0;
        }
        InputLevelFC(tmpLevelFC);
    } else if ( UllVolumeTab ) {
        float tmpUllageFC =  UllVolumeTab->Calc_X(Wgt / Density);
        if ( tmpUllageFC < 0.0 ) {
            tmpUllageFC = 0.0;
        }
        InputUllageFC(tmpUllageFC);
    }
    Weight = Wgt;
}


