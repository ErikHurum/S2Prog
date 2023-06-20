//---------------------------------------------------------------------------

#include "TSNIncludes.h"

#pragma hdrstop

//---------------------------------------------------------------------------
#ifdef ANWIN
#pragma package(smart_init)
#endif


// Refactoring: Used in several units, keep it here for now
ValueList StatusText[] = {
	{L_WORD186  ,L_WORD187   , ST_TXT_0_1},         // {"0"        ,"1"         , ST_TXT_0_1},
	{L_WORD4    ,L_WORD3     , ST_TXT_ON_OFF},      // {"Off"      ,"On"        , ST_TXT_ON_OFF},
	{L_WORD2    ,L_WORD1     , ST_TXT_EN_DIS},      // {"Disable"  ,"Enable"    , ST_TXT_EN_DIS},
	{L_WORD18   ,L_WORD17    , ST_TXT_OP_CLO},      // {"Close"    ,"Open"      , ST_TXT_OP_CLO},
	{L_WORD163  ,L_WORD162   , ST_TXT_NO_YES},      // {"No"       ,"Yes"       , ST_TXT_NO_YES},
	{L_WORD189  ,L_WORD190   , ST_TXT_AUTO_MAN},    // {"Auto"     ,"Manual"    , ST_TXT_AUTO_MAN},
	{L_WORD96   ,L_WORD68    , ST_TXT_CAL_SELECT},// {"SYSTEM"   ,"EEPROM"    , ST_TXT_CAL_SELECT},
	{L_WORD161  ,L_WORD188   , ST_TXT_ERROR_STAT},// {"OK"           ,"Error" , ST_TXT_ERROR_STAT},
};

const int SizeofStatusText = NELEMENTS(StatusText);


// Refactoring: Used in several units, keep it here for now
UnitControlStruct System_Unit[UNIT_SETS]=
{
	{L_WORD236   ,{L_WORD237},1,0}  ,                                                                           //  0{"No Unit"                 ,{""},1,0}  ,
	{L_WORD238   ,{L_WORD32,L_WORD255,L_WORD256},3,U_METER},                                                    //  1{"Length"                  ,{"meter","feet","d.feet"},3,U_METER},
	{L_WORD44    ,{L_WORD257,L_WORD258,L_WORD259,L_WORD260},4,U_METER3},                                        //  2{"Volume"                  ,{"m³","liter","US g.","US bls"},4,U_METER3},
	{L_WORD45    ,{L_WORD261,L_WORD262,L_WORD263},3,U_TON},                                                     //  3{"Weight"                  ,{"ton","l.ton","kN"},3,U_TON},
	{L_WORD247   ,{L_WORD264,L_WORD265},2,U_M3_HOUR},                                                           //  4{"Loadrate"                ,{"m³/h","USb/h"},2,U_M3_HOUR},
	{L_WORD11    ,{L_WORD266,L_WORD267},2,U_CELCIUS},                                                           //  5{"Temperature"             ,{"°C","°F"},2,U_CELCIUS},
	{L_WORD239   ,{L_WORD268,L_WORD269,L_WORD270,L_WORD271,L_WORD272,L_WORD273,L_WORD274,L_WORD275},8,U_MBAR},  //  6{"Atm/Vapour pressure"     ,{"mH2O","mmH2O","mBar","Bar","Psi","kPa","InH2O","InHg"},8,U_MBAR},
	{L_WORD240   ,{L_WORD268,L_WORD269,L_WORD270,L_WORD271,L_WORD272,L_WORD273,L_WORD274,L_WORD275},8,U_MMH2O}, //  7{"Cargo/Ballast press"     ,{"mH2O","mmH2O","mBar","Bar","Psi","kPa","InH2O","InHg"},8,U_MMH2O},
	{L_WORD241   ,{L_WORD268,L_WORD269,L_WORD270,L_WORD271,L_WORD272,L_WORD273,L_WORD274,L_WORD275},8,U_BAR},   //  8{"Line pressure"           ,{"mH2O","mmH2O","mBar","Bar","Psi","kPa","InH2O","InHg"},8,U_BAR},
	{L_WORD83    ,{L_WORD276,L_WORD277,L_WORD278},3,U_TON_M3_VAC},                                              //  9{"Density"                 ,{"t/m³ vac","t/m³ air","lb/usg"},3,U_TON_M3_VAC},
	{L_WORD243   ,{L_WORD279,L_WORD280},2,U_DEGREES},                                                           // 10{"Angle"                   ,{"Deg","Rad"},2,U_DEGREES},
	{L_WORD242   ,{L_WORD281,L_WORD282,L_WORD283,L_WORD284},4,U_TON_M3_C},                                      // 11{"Density coef."           ,{"t/m³°C","t/m³°F","l/g/°C","l/g/°F"},4,U_TON_M3_C},
	{L_WORD244   ,{L_WORD285,L_WORD286},2,U_METER4},                                                            // 12{"Free surface"            ,{"m^4","Feet^4"},2,U_METER4},
	{L_WORD245   ,{L_WORD287,L_WORD288,L_WORD289},3,U_TON_METER},                                               // 13{"Moment"                  ,{"t*m","lton*Ft","kNm"},3,U_TON_METER},
	{L_WORD246   ,{L_WORD290,L_WORD291},2,U_TON_PER_CM},                                                        // 14{"Immersion"               ,{"t/cm","lton/in"},2,U_TON_PER_CM},
	{L_WORD249   ,{L_WORD292},1,U_METER_RAD},                                                                   // 15{"GZ area"                 ,{"m*Rad"},1,U_METER_RAD},
	{L_WORD248   ,{L_WORD293,L_WORD294},2,U_PERCENT},                                                           // 16{"Percent"                 ,{"%","‰"},2,U_PERCENT},
	{L_WORD250   ,{L_WORD295,L_WORD296},2,U_MAMPERE},                                                           // 17{"Current"                 ,{"mAmp","Amp"},2,U_MAMPERE},
	{L_WORD251   ,{L_WORD297,L_WORD298},2,U_VOLT},                                                              // 18{"Voltage"                 ,{"Volt","mVolt"},2,U_VOLT},
	{L_WORD909   ,{L_WORD910},1,U_HZ},                                                                          // 19{"Frequency"               ,{"Hz"},1,U_VOLT},
	{L_WORD252   ,{L_WORD299,L_WORD300,L_WORD301,L_WORD302},4,U_SECONDS },                                      // 20{"Time"                    ,{"mSec","Sec","Min","Hours"},4,U_SECONDS},
	{L_WORD58    ,{L_WORD299,L_WORD300,L_WORD301,L_WORD302},4,U_MSECONDS},                                      // 21{"mSeconds"                ,{"mSec","Sec","Min","Hours"},4,U_SECONDS},
	{L_WORD253   ,{L_WORD299,L_WORD300,L_WORD301,L_WORD302},4,U_SECONDS },                                      // 22{"Seconds"                 ,{"mSec","Sec","Min","Hours"},4,U_MSECONDS},
	{L_WORD56    ,{L_WORD299,L_WORD300,L_WORD301,L_WORD302},4,U_MINUTES },                                      // 23{"Minutes"                 ,{"mSec","Sec","Min","Hours"},4,U_MINUTES},
	{L_WORD15    ,{L_WORD299,L_WORD300,L_WORD301,L_WORD302, L_WORD1121, L_WORD303 },6,U_TIME_HOURS},            // 24{"Hours"                   ,{"mSec","Sec","Min","Hours","H:M:S"},5,U_TIME},
	{L_WORD254   ,{L_WORD299,L_WORD300,L_WORD301,L_WORD302, L_WORD1121, L_WORD303 },6,U_DAYS},                  // 25{"Days"                    ,{"mSec","Sec","Min","Hours","Days"},5,U_DAYS},
	{L_WORD995   ,{L_WORD997,L_WORD300},1,U_ATOMIC_M_UNIT},                                                     // 26{"MolMass"                 ,{"u"},
    {L_WORD1012  ,{L_WORD1013,L_WORD1014 }, 1, U_RPM },                                                         // 27{"Revolutions"             ,{"RPM","RPS"},2,U_RPM, 3 _U_RPH},
	{L_WORD1087  ,{L_WORD1093,L_WORD1094, L_WORD1095 }, 3, U_PASCAL_SECONDS },                                  // 28{"Voscosity"               ,{"Pa*s","P", "cP"},3,U_PASCAL_SECONDS},
};                                                                                                                  


// Refactoring: Don't move, it's used both in ANWin and TxU
ValueList MainObjectList[] ={
	{L_WORD435      ,L_WORD237,C_PRO_SYSDATA},                                   // {"System data"      ,"",C_PRO_SYSDATA},
	{L_WORD436      ,L_WORD237,C_PRO_DRAFT_SYSTEM},                              // {"Drafts"           ,"",C_PRO_DRAFT_SYSTEM},
	{L_WORD437      ,L_WORD237,C_PRO_CARGO},                                     // {"Cargo tank"       ,"",C_PRO_CARGO},
	{L_WORD47       ,L_WORD237,C_PRO_BALLAST},                                       // {"Ballast"        ,"",C_PRO_BALLAST},
	{L_WORD48       ,L_WORD237,C_PRO_HFO},                                       // {"Heavy fuel oil"   ,"",C_PRO_HFO},
	{L_WORD49       ,L_WORD237,C_PRO_DO},                                        // {"Diesel oil"       ,"",C_PRO_DO},
	{L_WORD50       ,L_WORD237,C_PRO_LUB},                                       // {"Lubricants"       ,"",C_PRO_LUB},
	{L_WORD51       ,L_WORD237,C_PRO_FW},                                        // {"Fresh water"      ,"",C_PRO_FW},
	{L_WORD52       ,L_WORD237,C_PRO_MISC},                                      // {"Miscellanous"     ,"",C_PRO_MISC},
	{L_WORD438      ,L_WORD237,C_PRO_TANK},                                      // {"Other tank"       ,"",C_PRO_TANK},
	{L_WORD12       ,L_WORD237,C_PRO_TANKPRESS},                                 // {"Tank pressure"    ,"",C_PRO_TANKPRESS},
	{L_WORD241      ,L_WORD237,C_PRO_LINEPRESS},                                 // {"Line pressure"    ,"",C_PRO_LINEPRESS},
	{L_WORD11       ,L_WORD237,C_PRO_TEMP},                                      // {"Temperature"      ,"",C_PRO_TEMP},
	{L_WORD94       ,L_WORD237,C_PRO_WATERINGRESS},                              // {"Water ingress"    ,"",C_PRO_WATERINGRESS},
	{L_WORD95       ,L_WORD237,C_PRO_LEVSWITCH},                                 // {"Level switch"     ,"",C_PRO_LEVSWITCH},

};

int SizeofMainObjectList                = NELEMENTS(MainObjectList);


