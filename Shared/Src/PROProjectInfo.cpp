#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif
//#include "lwip/inet.h"
#ifndef ANTDUSIM
#include "anpro_net.h"
#else
#define ANPRO_NET_GATEWAY               1
#define ANPRO_NET_TCU_MASTER            30
#define ANPRO_NET_TCU_MASTER_END        49  // Not in use
#define ANPRO_NET_TCU_SLAVE_START       50
#define ANPRO_NET_TCU_SLAVE_END         69
#define ANPRO_NET_PC_START              80
#define ANPRO_NET_PC_END                149
#define ANPRO_NET_TDU_START             150
#define ANPRO_NET_TDU_END               199

#endif

#define ANPRO_TCP_SERVER_PORT           15533
#define ANPRO_NET_UDP_PORT              15534
#define ANPRO_TCP_FLASH_PROG_PORT       16000

//---------------------------------------------------------------------------
PROProjectInfo *PROProjectInfo::PROProjectInfoPtr = NULL;
int PROProjectInfo::AlarmSystemStartUpDelay     = ALARM_SYSTEM_DELAY;
bool PROProjectInfo::isChemGasProject           = false;

float PROProjectInfo::LengthBetweenPP           = 0.0;
float PROProjectInfo::LengthBetweenMarks        = 0.0;
float PROProjectInfo::Width                     = 0.0;
int PROProjectInfo::NumberOfPRO                 = 0;
int PROProjectInfo::DecimalPointVolume          = 1;
int PROProjectInfo::DecimalPointWeight          = 1;
AnsiString PROProjectInfo::ProjOwner;
AnsiString PROProjectInfo::ProjTypeName;
AnsiString PROProjectInfo::ProjectName;
AnsiString PROProjectInfo::CallSign;
AnsiString PROProjectInfo::IMONumber;
float PROProjectInfo::NoiseLimCargoB            = LEVEL_NOISE_LIMIT_CARGO_B;
float PROProjectInfo::NoiseLimCargoU            = LEVEL_NOISE_LIMIT_CARGO_U;
float PROProjectInfo::NoiseLimBallastB          = LEVEL_NOISE_LIMIT_BALLAST_B;
float PROProjectInfo::NoiseLimBallastU          = LEVEL_NOISE_LIMIT_BALLAST_U;
float PROProjectInfo::NoiseLimServiceB          = LEVEL_NOISE_LIMIT_SERVICE_B;
float PROProjectInfo::NoiseLimServiceU          = LEVEL_NOISE_LIMIT_SERVICE_U;
float PROProjectInfo::NoiseLimDefaultB          = LEVEL_NOISE_LIMIT_DEFAULT_B;
float PROProjectInfo::NoiseLimDefaultU          = LEVEL_NOISE_LIMIT_DEFAULT_U;
float PROProjectInfo::NoiseLimDefaultR          = LEVEL_NOISE_LIMIT_RADAR;
float PROProjectInfo::NoiseLimVoidSpace         = LEVEL_NOISE_LIMIT_VOIDSPACE;

float PROProjectInfo::OverfillLimit             = LIMIT_OVERFILL;
float PROProjectInfo::HighLevelLimit            = LIMIT_HIGH_LEVEL;
float PROProjectInfo::LowLevelLimit             = LIMIT_LOW_LEVEL;
float PROProjectInfo::LoLoLevelLimit            = LIMIT_LOLO_LEVEL;
float PROProjectInfo::VoidSpaceLimit            = LIMIT_VOIDSPACE;
float PROProjectInfo::LevelDiffLimit            = LIMIT_LEVEL_DIFF;

float PROProjectInfo::HighTempLimit             = LIMIT_HIGH_TEMP;
float PROProjectInfo::LowTempLimit              = LIMIT_LOW_TEMP;
float PROProjectInfo::HighTankPressLimit        = LIMIT_HIGH_TANKPRESS;
float PROProjectInfo::IntLowTankPressLimit1     = LIMIT_LOW_TANKPRESS;
float PROProjectInfo::IntHighTankPressLimit1    = LIMIT_HIGH_TANKPRESS;
float PROProjectInfo::IntLowTankPressLimit2     = LIMIT_LOW_TANKPRESS;
float PROProjectInfo::IntHighTankPressLimit2    = LIMIT_HIGH_TANKPRESS;
float PROProjectInfo::LowTankPressLimit         = LIMIT_LOW_TANKPRESS;
float PROProjectInfo::HighVapourRetLimit     	= LIMIT_HIGH_VAPOUR;   // Should be 90% of PV
float PROProjectInfo::LowVapourRetLimit      	= LIMIT_LOW_VAPOUR;    // Should be 90% of PV
float PROProjectInfo::HighPressVacLimit         = LIMIT_HIGH_TANKPRESS; // Should be 110% of PV
float PROProjectInfo::LowPressVacLimit          = LIMIT_LOW_TANKPRESS;  // Should be 110% of PV
float PROProjectInfo::HighIGP_Limit             = LIMIT_HIGH_INERT_GAS_PRESS; // Should be 90% of PV
float PROProjectInfo::LowIGP_Limit              = LIMIT_LOW_INERT_GAS_PRESS ; // should be 100 mm H2O
float PROProjectInfo::HiHiLinePressLimit        = LIMIT_HIHI_LINEPRESS;  // Should be set according to max allowed pressure
float PROProjectInfo::HighLinePressLimit        = LIMIT_HIGH_LINEPRESS;  // Should be set according to max allowed pressure intially
float PROProjectInfo::LowLinePressLimit         = LIMIT_LOW_LINEPRESS;


bool PROProjectInfo::hasHighVapourRetLimit   	= false;
bool PROProjectInfo::hasLowVapourRetLimit   	= false;
bool PROProjectInfo::hasHighPressVacLimit       = false;
bool PROProjectInfo::hasLowPressVacLimit        = false;
bool PROProjectInfo::hasHighIGP_Limit           = false;
bool PROProjectInfo::hasLowIGP_Limit            = false;
bool PROProjectInfo::hasLoLoLevelLimit          = false;


bool PROProjectInfo::OverfillLocked             = false;     // Changed by EHS from false 26.01.2022
bool PROProjectInfo::HighLevelLocked            = false;
bool PROProjectInfo::LowLevelLocked             = false;
bool PROProjectInfo::LowLowLevelLocked          = false;
bool PROProjectInfo::HighTempLocked             = false;
bool PROProjectInfo::LowTempLocked              = false;
bool PROProjectInfo::HighTankPressLocked        = false;
bool PROProjectInfo::LowTankPressLocked         = false;
bool PROProjectInfo::HighIGP_Locked             = false;
bool PROProjectInfo::LowIGP_Locked              = false;
bool PROProjectInfo::HighLinePressLocked        = false;
bool PROProjectInfo::LowLinePressLocked         = false;
bool PROProjectInfo::IntegratedLoadingComputer  = false;

bool PROProjectInfo::IsInlandVessel             = false;
bool PROProjectInfo::IsCustodyTransferSys       = false;
int  PROProjectInfo::RequestConfig              = FLASH_RET_MODE_NONE;
bool PROProjectInfo::L_English                  = true;    // Assume always true
bool PROProjectInfo::L_Norwegian                = false;
bool PROProjectInfo::L_German                   = false;
bool PROProjectInfo::L_French                   = false;
bool PROProjectInfo::L_Spanish                  = false;
bool PROProjectInfo::L_Portuguese               = false;
bool PROProjectInfo::L_Dutch                    = false;


float    PROProjectInfo::TankMaxLoadTime          = DEFAULT_LOAD_TIME;
int      PROProjectInfo::NumberOfHandheldUnits    = 0;
bool     PROProjectInfo::AutoAcknowledge          = false;
int      PROProjectInfo::ProjectType              = 0;


bool     PROProjectInfo::SimulateIO               = false;
bool     PROProjectInfo::SimulateFixedValues      = false;

float    PROProjectInfo::Default_SwitchOn_mA      = LEVELSWITCH_VALCOM_MA_ON;
float    PROProjectInfo::Default_SwitchOff_mA     = LEVELSWITCH_VALCOM_MA_OFF;
float    PROProjectInfo::Default_SwitchWindow     = LEVELSWITCH_VALCOM_MA_WIN;

float    PROProjectInfo::CableResistanceShip      = SHIP_BOARD_CABLE_RES;
float    PROProjectInfo::CableResistanceSensor    = TEMP_SENS_CABLE_RES;
bool     PROProjectInfo::hasCableResistanceShip   = false;
bool     PROProjectInfo::hasCableResistanceSensor = false;

bool     PROProjectInfo::UseTemperatureWindow     = false;
unsigned PROProjectInfo::TemperatureWindowMaxCnt  = MAX_OUTSIDE_WIN_CNT;
float    PROProjectInfo::TemperatureWindowTmpLim  = MAX_OUTSIDE_TEMP_LIM;

AnsiString PROProjectInfo::IP_Address("192.168.227.0");
U32  PROProjectInfo::IP_AddressMain            = 0;
U8   PROProjectInfo::IP_AddressGateWay         = ANPRO_NET_GATEWAY;
U8   PROProjectInfo::IP_AddressTCU_Master      = ANPRO_NET_TCU_MASTER;
U8   PROProjectInfo::IP_AddressTCUSlaveStart   = ANPRO_NET_TCU_SLAVE_START;
U8   PROProjectInfo::IP_AddressTCUSlaveEnd     = ANPRO_NET_TCU_SLAVE_END;
U8   PROProjectInfo::IP_AddressTDUStart        = ANPRO_NET_TDU_START;
U8   PROProjectInfo::IP_AddressTDUEnd          = ANPRO_NET_TDU_END;
U8   PROProjectInfo::IP_AddressPCStart         = ANPRO_NET_PC_START;
U8   PROProjectInfo::IP_AddressPCEnd           = ANPRO_NET_PC_END;
U32  PROProjectInfo::IP_TCP_ServerPort         = ANPRO_TCP_SERVER_PORT;
U32  PROProjectInfo::IP_UDP_NetPort            = ANPRO_NET_UDP_PORT;
//U32  PROProjectInfo::IP_TCP_FlashPort          = ANPRO_TCP_FLASH_PROG_PORT;

bool PROProjectInfo::PressLim_mBar = false;


int PROProjectInfo::UserUnits[UNIT_SETS] = {
    U_NO_UNIT,
    U_METER,
    U_METER3,
    U_TON,
    U_M3_HOUR,
    U_CELCIUS,
    U_MMH2O, // PRESSURE_UNIT1
    U_MMH2O, // PRESSURE_UNIT2
    U_BAR,
    U_TON_M3_VAC,
    U_DEGREES,
    U_TON_M3_C,
    U_METER4,
    U_TON_METER,
    U_TON_PER_CM,
    U_METER_RAD,
    U_PERCENT,
    U_MAMPERE,
    U_VOLT,
    U_HZ,
    U_SECONDS,
    U_MSECONDS,
    U_SECONDS,
    U_MINUTES,
    U_HOURS,
    U_DAYS,
};




PROProjectInfo::PROProjectInfo(void):PRogramObjectBase(false) {
    PROProjectInfoPtr = this;
    NumberOfPRO++;
    IDNumber = (C_PRO_PROJINFO << 16) + NumberOfPRO;
    NumberOfApp = 0;
    for (int i = 0; i < MAX_APPL; i++) {
        ApplicationList[i] = NULL;
    }
    ProjTypeName    = "Ship";
    CallSign        = "None";
    IMONumber       = "None";

    AlarmSettingsPINLock = false;

}

PROProjectInfo::~PROProjectInfo(void) {

}

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PROProjectInfo::SaveSettings(TSNConfigString *SettingsString) {
    if (IsModified || WriteAll) {
        IsModified = false;
        AnsiString LocalString;
        // We don't need the IdNumber for this object, so it's not saved!
        LocalString += KeyWord(C_PRO_PROJINFO) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PROJ_NAME) + ProjectName + CrLfStr;
        LocalString += KeyWord(C_PRO_END) + CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PROProjectInfo::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;

    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                RestoreSettingsWarning((AnsiString)"Project Info:\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"Project Info:\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_CT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case C_PROJ_NAME:
                {
                    AnsiString TmpStr = SettingsString->GetRemainingLine(ErrorLine);
                    if (ProjectName.AnsiCompareIC(TmpStr)) {
                        WriteAll = true;
                        SignalSaveSettings(FLASH_SAVE_SETTINGS);
                        NoError  = false;
                    } else {
                        WriteAll = false;
                    }
                }
                //WriteAll = true;
                break;
            case C_REQUEST_CONFIG:
                RequestConfig = FLASH_RET_MODE_SETT;
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    return (NoError);
}


//---------------------------------------------------------------------------


void PROProjectInfo::WriteConfigToFile(TSNConfigString &ConfigString) {
    AnsiString LocalString;
    LocalString += KeyWord(C_PRO_PROJINFO) + CrLfStr;

    LocalString += TabStr1 + KeyWord(C_PROJ_NAME) + ProjectName + CrLfStr;

    LocalString += TabStr1;
    for (int i = 0; i < NumberOfApp; i++) {
        LocalString += KeyWord(ApplicationList[i]);
    }
    LocalString += CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PROJ_TYPE) + (AnsiString)ProjectType + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PRO_NAME) + Name + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PROJ_TYPE_NAME) + ProjTypeName + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PROJ_CALLSIGN) + CallSign + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PROJ_IMO_NUM) + IMONumber + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PROJ_LENGTH_BETWEEN_PP   ) + FloatToAnsiString(LengthBetweenPP) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PROJ_LENGTH_BETWEEN_MARKS) + FloatToAnsiString(LengthBetweenMarks) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_PROJ_TOT_WITH) + FloatToAnsiString(Width) + CrLfStr;
    LocalString += MakeIdTableString();
    if (IntegratedLoadingComputer) {
        LocalString += TabStr1 + KeyWord(C_PROJ_LOADING_COMPUTER) + CrLfStr;
    }
    if (IsInlandVessel) {
        LocalString += TabStr1 + KeyWord(C_PROJ_IS_INLAND_VESSEL) + CrLfStr;
    }
    if (IsCustodyTransferSys) {
        LocalString += TabStr1 + KeyWord(C_PROJ_IS_CUSTODY_TRANSFER_SYS) + CrLfStr;
    }

    if (PressLim_mBar) {
        LocalString += TabStr1 + KeyWord(C_PRESS_LIM_MBAR) + AnsiString(int(PressLim_mBar)) + CrLfStr;
    }
    /*
    // Skal resettes, ikke lagres
    if ( RequestConfig ) {
        LocalString +=TabStr1+KeyWord(C_REQUEST_CONFIG)+CrLfStr;
    }
    */
    if (AutoAcknowledge) {
        LocalString += TabStr1 + KeyWord(C_PROJ_AUTO_ALARM_ACKN) + CrLfStr;
    }

    if (TankMaxLoadTime != DEFAULT_LOAD_TIME) {
        LocalString += TabStr1 + KeyWord(C_PROJ_LOADRATE_LOAD_TIME) + FloatToAnsiString(TankMaxLoadTime) + CrLfStr;
    }
    if (AlarmSystemStartUpDelay != ALARM_SYSTEM_DELAY) {
        LocalString += TabStr1 + KeyWord(C_PROJ_ALARMSYS_DELAY) + AnsiString(AlarmSystemStartUpDelay) + CrLfStr;
    }
    if (isChemGasProject) {
        LocalString += TabStr1 + KeyWord(C_PROJ_IS_HSH_VESSEL) + CrLfStr;
    }

    LocalString += TabStr1 + KeyWord(AL_LIM_OVERFILL) + FloatToAnsiString(OverfillLimit) + CrLfStr;
    LocalString += TabStr1 + KeyWord(AL_LIM_HIGHLEVEL) + FloatToAnsiString(HighLevelLimit) + CrLfStr;
    LocalString += TabStr1 + KeyWord(AL_LIM_LOWLEVEL) + FloatToAnsiString(LowLevelLimit) + CrLfStr;
    LocalString += TabStr1 + KeyWord(AL_LIM_LOWLOW_LEVEL) + FloatToAnsiString(LoLoLevelLimit) + CrLfStr;
    LocalString += TabStr1 + KeyWord(AL_LIM_LEVELDIFF) + FloatToAnsiString(LevelDiffLimit) + CrLfStr;
    LocalString += TabStr1 + KeyWord(AL_LIM_VOIDSPACE) + FloatToAnsiString(VoidSpaceLimit) + CrLfStr;
    LocalString += TabStr1 + KeyWord(AL_LIM_HIGHTEMP) + FloatToAnsiString(HighTempLimit) + CrLfStr;
    LocalString += TabStr1 + KeyWord(AL_LIM_LOWTEMP) + FloatToAnsiString(LowTempLimit) + CrLfStr;
    if ( hasLoLoLevelLimit ) {
        LocalString += TabStr1 + KeyWord(AL_LIM_HAS_LOLO_LEVEL)  + CrLfStr;
    }

    if (PressLim_mBar) {
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGHTANK_PRESS) + FloatToAnsiString(HighTankPressLimit * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_LOWTANK_PRESS) + FloatToAnsiString(LowTankPressLimit * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_PV_PRESS) + FloatToAnsiString(HighPressVacLimit * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_LOW_PV_PRESS) + FloatToAnsiString(LowPressVacLimit * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_IG_PRESS) + FloatToAnsiString(HighIGP_Limit * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_LOW_IG_PRESS) + FloatToAnsiString(LowIGP_Limit * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGHVAPOUR_RET) + FloatToAnsiString(HighVapourRetLimit * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_LOWVAPOUR_RET) + FloatToAnsiString(LowVapourRetLimit * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS1) + FloatToAnsiString(IntHighTankPressLimit1 * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS1) + FloatToAnsiString(IntLowTankPressLimit2 * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS2) + FloatToAnsiString(IntHighTankPressLimit2 * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS2) + FloatToAnsiString(IntLowTankPressLimit1 * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGHHIGHLINE_PRESS) + FloatToAnsiString(HiHiLinePressLimit * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGHLINE_PRESS) + FloatToAnsiString(HighLinePressLimit * MH2O_TO_MBAR) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_LOWLINE_PRESS) + FloatToAnsiString(LowLinePressLimit * MH2O_TO_MBAR) + CrLfStr;
    } else {
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGHTANK_PRESS) + FloatToAnsiString(HighTankPressLimit) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_LOWTANK_PRESS) + FloatToAnsiString(LowTankPressLimit) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_PV_PRESS) + FloatToAnsiString(HighPressVacLimit) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_LOW_PV_PRESS) + FloatToAnsiString(LowPressVacLimit) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_IG_PRESS) + FloatToAnsiString(HighIGP_Limit) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_LOW_IG_PRESS) + FloatToAnsiString(LowIGP_Limit) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGHVAPOUR_RET) + FloatToAnsiString(HighVapourRetLimit) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_LOWVAPOUR_RET) + FloatToAnsiString(LowVapourRetLimit) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS1) + FloatToAnsiString(IntHighTankPressLimit1) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS1) + FloatToAnsiString(IntLowTankPressLimit2) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS2) + FloatToAnsiString(IntHighTankPressLimit2) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS2) + FloatToAnsiString(IntLowTankPressLimit1) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGHHIGHLINE_PRESS) + FloatToAnsiString(HiHiLinePressLimit) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_HIGHLINE_PRESS) + FloatToAnsiString(HighLinePressLimit) + CrLfStr;
        LocalString += TabStr1 + KeyWord(AL_LIM_LOWLINE_PRESS) + FloatToAnsiString(LowLinePressLimit) + CrLfStr;
    }
    if (PROProjectInfo::OverfillLocked      ) LocalString += TabStr1 + KeyWord(AL_LOCK_OVERFILL) + CrLfStr;
    if (PROProjectInfo::HighLevelLocked     ) LocalString += TabStr1 + KeyWord(AL_LOCK_HIGHLEVEL) + CrLfStr;
    if (PROProjectInfo::LowLevelLocked      ) LocalString += TabStr1 + KeyWord(AL_LOCK_LOWLEVEL) + CrLfStr;
    if (PROProjectInfo::LowLowLevelLocked   ) LocalString += TabStr1 + KeyWord(AL_LOCK_LOWLOWLEVEL) + CrLfStr;
    if (PROProjectInfo::HighTempLocked      ) LocalString += TabStr1 + KeyWord(AL_LOCK_HIGHTEMP) + CrLfStr;
    if (PROProjectInfo::LowTempLocked       ) LocalString += TabStr1 + KeyWord(AL_LOCK_LOWTEMP) + CrLfStr;
    if (PROProjectInfo::HighTankPressLocked ) LocalString += TabStr1 + KeyWord(AL_LOCK_HIGHTANK_PRESS) + CrLfStr;
    if (PROProjectInfo::LowTankPressLocked  ) LocalString += TabStr1 + KeyWord(AL_LOCK_LOWTANK_PRESS) + CrLfStr;
    if (PROProjectInfo::HighIGP_Locked      ) LocalString += TabStr1 + KeyWord(AL_LOCK_HIGH_IGP) + CrLfStr;
    if (PROProjectInfo::LowIGP_Locked       ) LocalString += TabStr1 + KeyWord(AL_LOCK_LOW_IGP) + CrLfStr;
    if (PROProjectInfo::HighLinePressLocked ) LocalString += TabStr1 + KeyWord(AL_LOCK_HIGHLINE_PRESS) + CrLfStr;
    if (PROProjectInfo::LowLinePressLocked  ) LocalString += TabStr1 + KeyWord(AL_LOCK_LOWLINE_PRESS) + CrLfStr;

    if (NoiseLimCargoB != (float)LEVEL_NOISE_LIMIT_CARGO_B) {
        LocalString += TabStr1 + KeyWord(C_NOISE_LIM_CARGO_B) + FloatToAnsiString(NoiseLimCargoB, 6, 3) + CrLfStr;
    }
    if (NoiseLimCargoU != (float)LEVEL_NOISE_LIMIT_CARGO_U) {
        LocalString += TabStr1 + KeyWord(C_NOISE_LIM_CARGO_U) + FloatToAnsiString(NoiseLimCargoU, 6, 3) + CrLfStr;
    }
    if (NoiseLimCargoB != (float)LEVEL_NOISE_LIMIT_BALLAST_B) {
        LocalString += TabStr1 + KeyWord(C_NOISE_LIM_BALLAST_B) + FloatToAnsiString(NoiseLimBallastB, 6, 3) + CrLfStr;
    }
    if (NoiseLimCargoB != (float)LEVEL_NOISE_LIMIT_BALLAST_U) {
        LocalString += TabStr1 + KeyWord(C_NOISE_LIM_BALLAST_U) + FloatToAnsiString(NoiseLimBallastU, 6, 3) + CrLfStr;
    }
    if (NoiseLimCargoB != (float)LEVEL_NOISE_LIMIT_SERVICE_B) {
        LocalString += TabStr1 + KeyWord(C_NOISE_LIM_SERVICE_B) + FloatToAnsiString(NoiseLimServiceB, 6, 3) + CrLfStr;
    }
    if (NoiseLimCargoB != (float)LEVEL_NOISE_LIMIT_SERVICE_U) {
        LocalString += TabStr1 + KeyWord(C_NOISE_LIM_SERVICE_U) + FloatToAnsiString(NoiseLimServiceU, 6, 3) + CrLfStr;
    }
    if (NoiseLimDefaultR != LEVEL_NOISE_LIMIT_RADAR) {
        LocalString += TabStr1 + KeyWord(C_NOISE_LIM_RADAR) + FloatToAnsiString(NoiseLimDefaultR, 6, 3) + CrLfStr;
    }
    if (hasCableResistanceShip) {
        LocalString += TabStr2 + KeyWord(C_AI_CABLE_RES_SHIP) + FloatToAnsiString(CableResistanceShip) + CrLfStr;
    }
    if (hasCableResistanceSensor) {
        LocalString += TabStr2 + KeyWord(C_AI_CABLE_RES_SENS) + FloatToAnsiString(CableResistanceSensor) + CrLfStr;
    }
    if (UseTemperatureWindow) {
        LocalString += TabStr2 + KeyWord(C_T_TEMP_WINDOW_COUNT) + AnsiString(TemperatureWindowMaxCnt) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_T_TEMP_WINDOW_LIMIT) + FloatToAnsiString(TemperatureWindowTmpLim) + CrLfStr;
    }
    if (DecimalPointVolume != VOLUME_UNIT_DEC_P) {
        LocalString += TabStr1 + KeyWord(C_DEC_P_VOLUME) + AnsiString(DecimalPointVolume) + CrLfStr;
    }
    if (DecimalPointWeight != WEIGHT_UNIT_DEC_P) {
        LocalString += TabStr1 + KeyWord(C_DEC_P_WEIGHT) + AnsiString(DecimalPointWeight) + CrLfStr;
    }


    //if ( L_English    ) LocalString +=TabStr1+KeyWord(C_L_ENGLISH   )+CrLfStr;
    if (L_Norwegian)  LocalString += TabStr1 + KeyWord(C_L_NORWEGIAN) + CrLfStr;
    if (L_German)     LocalString += TabStr1 + KeyWord(C_L_GERMAN) + CrLfStr;
    if (L_Dutch)      LocalString += TabStr1 + KeyWord(C_L_DUTCH) + CrLfStr;
    if (L_French)     LocalString += TabStr1 + KeyWord(C_L_FRENCH) + CrLfStr;
    if (L_Spanish)    LocalString += TabStr1 + KeyWord(C_L_SPANISH) + CrLfStr;
    if (L_Portuguese) LocalString += TabStr1 + KeyWord(C_L_PORTUGUESE) + CrLfStr;
    if (UserUnits[VOLUME_UNIT] != U_METER3) {
        LocalString += TabStr1 + KeyWord(C_UNIT_VOLUME) + KeyWord(UserUnits[VOLUME_UNIT] + C_U_METER3) + CrLfStr;
    }
    if (UserUnits[LENGTH_UNIT] != U_METER) {
        LocalString += TabStr1 + KeyWord(C_UNIT_LENGTH) + KeyWord(UserUnits[LENGTH_UNIT] + C_U_METER) + CrLfStr;
    }
    if (UserUnits[PRESSURE_UNIT1] != U_MBAR) {
        LocalString += TabStr1 + KeyWord(C_UNIT_PRESSURE1) + KeyWord(UserUnits[PRESSURE_UNIT1] + C_U_METERH2O) + CrLfStr;
    }
    if (UserUnits[PRESSURE_UNIT2] != U_MMH2O) {
        LocalString += TabStr1 + KeyWord(C_UNIT_PRESSURE1) + KeyWord(UserUnits[PRESSURE_UNIT2] + C_U_METERH2O) + CrLfStr;
    }
    if (UserUnits[PRESSURE_UNIT3] != U_BAR) {
        LocalString += TabStr1 + KeyWord(C_UNIT_PRESSURE1) + KeyWord(UserUnits[PRESSURE_UNIT3] + C_U_METERH2O) + CrLfStr;
    }
    LocalString += TabStr1 + KeyWord(C_PRO_NUMBER_OF_HANHELD) + (AnsiString)NumberOfHandheldUnits + CrLfStr;

    if (SimulateIO)   LocalString += TabStr1 + KeyWord(C_SD_SIMULATE_IO) + CrLfStr;
    if (SimulateFixedValues)   LocalString += TabStr1 + KeyWord(C_SD_SIMULATE_STATIC) + CrLfStr;
    if (PROProjectInfo::PROProjectInfoPtr->AlarmSettingsPINLock) {
        LocalString += TabStr1 + KeyWord(C_ALARM_SETTINGS_PIN_LOCK) + KeyWord(C_ENABLE) + CrLfStr;
    } else {
        LocalString += TabStr1 + KeyWord(C_ALARM_SETTINGS_PIN_LOCK) + KeyWord(C_DISABLE) + CrLfStr;
    }
    if (!IP_Address.IsEmpty()) {
        LocalString += TabStr1 + KeyWord(C_PROJ_IP_ADDRESS) + IP_Address + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PROJ_IP_ADDRESS_GATEWAY) + AnsiString(unsigned(IP_AddressGateWay)) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PROJ_IP_ADDRESS_TCU_MASTER) + AnsiString(unsigned(IP_AddressTCU_Master)) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PROJ_IP_ADDRESS_TCU_SLAVE_START) + AnsiString(unsigned(IP_AddressTCUSlaveStart)) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PROJ_IP_ADDRESS_TCU_SLAVE_END) + AnsiString(unsigned(IP_AddressTCUSlaveEnd)) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PROJ_IP_ADDRESS_TDU_START) + AnsiString(unsigned(IP_AddressTDUStart)) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PROJ_IP_ADDRESS_TDU_END) + AnsiString(unsigned(IP_AddressTDUEnd)) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PROJ_IP_ADDRESS_PC_START) + AnsiString(unsigned(IP_AddressPCStart)) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PROJ_IP_ADDRESS_PC_END) + AnsiString(unsigned(IP_AddressPCEnd)) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PROJ_IP_TCP_SERVER_PORT) + AnsiString(IP_TCP_ServerPort) + CrLfStr;
        LocalString += TabStr1 + KeyWord(C_PROJ_IP_UDP_NET_PORT) + AnsiString(IP_UDP_NetPort) + CrLfStr;
        //LocalString += TabStr1 + KeyWord(C_PROJ_IP_TCP_FLASH_PORT) + AnsiString(IP_TCP_FlashPort) + CrLfStr;
    }
    LocalString += KeyWord(C_PRO_END) + CrLfStr;
    LocalString += CrLfStr;


    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

int PROProjectInfo::LoadConfigFromFile(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    bool NoError = true;
    int ErrorLine = 0;
    int Key;

    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning("Project info", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning("Project info", InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_PROJ_NAME:
                ProjectName = ConfigString.NextWord(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PROJ_NUM_TCU:
                {
                    /*int Dummy = */ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_PROJ_NUM_TDU:
                // Just to be backward compatible
                {
                    /* int NumberOfTDU = */ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case TSN_NONE_APP   :
            case TSN_CARGO_APP:
            case TSN_BALLAST_APP:
            case TSN_SERVICE_APP:
            case TSN_TANKPRESS_APP:
            case TSN_LINEPRESS_APP:
            case TSN_TEMP_APP:
            case TSN_LEVELSWITCH_APP:
            case TSN_WATERINGR_APP:
                ApplicationList[NumberOfApp++] = Key;
                break;
            case C_PROJ_TYPE:
                ProjectType = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                if (NoError) {
                    if (ProjectType == 2) {
                        switch (GlobalDeviceHWId) {
                        case TDU_R1:
                        case TDU_R2:
                            break;
                        case TCU_R1:
                        case TCU_R2:
                            break;
                        }
                    } else {
                        switch (GlobalDeviceHWId) {
                        case TDU_R1:
                        case TDU_R2:
                            break;
                        case TCU_R1:
                        case TCU_R2:
                            // Activate interrupts for PWM inclinometer
#ifdef S2TXU
                            rEINTMASK  &= ~(BIT_SUB_EINT5 | BIT_SUB_EINT6 | BIT_SUB_EINT7 | BIT_SUB_EINT8);
#endif
                            break;
                        }
                    }
                }
                break;
            case C_PRO_NAME:
                Name = ConfigString.GetRemainingLine(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PROJ_TYPE_NAME:
                ProjTypeName = ConfigString.GetRemainingLine(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PROJ_CALLSIGN:
                CallSign = ConfigString.NextWord(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PROJ_IMO_NUM:
                IMONumber = ConfigString.NextWord(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PROJ_LENGTH_BETWEEN_PP:
                LengthBetweenPP = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PROJ_LENGTH_BETWEEN_MARKS:
                LengthBetweenMarks = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PROJ_TOT_WITH:
                Width = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PROJ_LOADING_COMPUTER    :
                IntegratedLoadingComputer = true;
                break;
            case C_PROJ_IS_INLAND_VESSEL    :
                IsInlandVessel = true;
                break;
            case C_PROJ_IS_CUSTODY_TRANSFER_SYS:
                IsCustodyTransferSys = true;
                break;
            case C_PROJ_AUTO_ALARM_ACKN :
                AutoAcknowledge = true;
                break;
            case C_PROJ_LOADRATE_LOAD_TIME:
                TankMaxLoadTime = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_OVERFILL     :
                OverfillLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGHLEVEL    :
                HighLevelLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWLEVEL     :
                LowLevelLimit  = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWLOW_LEVEL     :
                LoLoLevelLimit  = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_VOIDSPACE     :
                VoidSpaceLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_LEVELDIFF     :
                LevelDiffLimit = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGHTEMP     :
                HighTempLimit  = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWTEMP      :
                LowTempLimit   = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGHTANK_PRESS:
                HighTankPressLimit = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    HighTankPressLimit        /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWTANK_PRESS :
                LowTankPressLimit = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    LowTankPressLimit         /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGHVAPOUR_RET:
                HighVapourRetLimit = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    HighVapourRetLimit        /= MH2O_TO_MBAR;
                }
                hasHighVapourRetLimit = true;
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWVAPOUR_RET :
                LowVapourRetLimit = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    LowVapourRetLimit         /= MH2O_TO_MBAR;
                }
                hasLowVapourRetLimit  = true;
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGH_PV_PRESS   :
                HighPressVacLimit = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    HighPressVacLimit         /= MH2O_TO_MBAR;
                }
                hasHighPressVacLimit   = true;
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOW_PV_PRESS    :
                LowPressVacLimit = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    LowPressVacLimit          /= MH2O_TO_MBAR;
                }
                hasLowPressVacLimit    = true;
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGH_IG_PRESS   :
                HighIGP_Limit = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    HighIGP_Limit             /= MH2O_TO_MBAR;
                }
                hasHighIGP_Limit   = true;
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOW_IG_PRESS    :
                LowIGP_Limit = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    LowIGP_Limit              /= MH2O_TO_MBAR;
                }
                hasLowIGP_Limit    = true;
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGHHIGHLINE_PRESS:
                HiHiLinePressLimit = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    HiHiLinePressLimit        /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGHLINE_PRESS:
                HighLinePressLimit = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    HighLinePressLimit        /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWLINE_PRESS :
                LowLinePressLimit = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    LowLinePressLimit         /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_X_HI_TNK_PRESS1:
                IntHighTankPressLimit1 = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    IntHighTankPressLimit1    /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_X_LO_TNK_PRESS1 :
                IntLowTankPressLimit1 = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    IntLowTankPressLimit1     /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_X_HI_TNK_PRESS2:
                IntHighTankPressLimit2 = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    IntHighTankPressLimit2    /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_X_LO_TNK_PRESS2 :
                IntLowTankPressLimit2 = ConfigString.ReadDouble(ErrorLine);
                if (PressLim_mBar) {
                    IntLowTankPressLimit2     /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_HAS_LOLO_LEVEL:
                hasLoLoLevelLimit = true;
                break;
            case AL_LOCK_OVERFILL     :
                OverfillLocked = true;
                break;
            case AL_UNLOCK_OVERFILL     :
                OverfillLocked = false;
                break;
            case AL_LOCK_HIGHLEVEL    :
                HighLevelLocked = true;
                break;
            case AL_LOCK_LOWLEVEL     :
                LowLevelLocked = true;
                break;
            case AL_LOCK_LOWLOWLEVEL     :
                LowLowLevelLocked = true;
                break;
            case AL_LOCK_HIGHTEMP     :
                HighTempLocked = true;
                break;
            case AL_LOCK_LOWTEMP      :
                LowTempLocked = true;
                break;
            case AL_LOCK_HIGHTANK_PRESS:
                HighTankPressLocked = true;
                break;
            case AL_LOCK_LOWTANK_PRESS :
                LowTankPressLocked = true;
                break;
            case AL_LOCK_HIGH_IGP      :
                HighIGP_Locked = true;
                break;
            case AL_LOCK_LOW_IGP       :
                LowIGP_Locked = true;
                break;
            case AL_LOCK_HIGHLINE_PRESS:
                HighLinePressLocked = true;
                break;
            case AL_LOCK_LOWLINE_PRESS :
                LowLinePressLocked = true;
                break;
            case C_NOISE_LIM_CARGO_B    :
                NoiseLimCargoB = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_NOISE_LIM_CARGO_U    :
                NoiseLimCargoU = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_NOISE_LIM_BALLAST_B  :
                NoiseLimBallastB = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_NOISE_LIM_BALLAST_U  :
                NoiseLimBallastU = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_NOISE_LIM_SERVICE_B  :
                NoiseLimServiceB = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_NOISE_LIM_SERVICE_U  :
                NoiseLimServiceU = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_NOISE_LIM_RADAR      :
                NoiseLimDefaultR  = ConfigString.ReadDouble(ErrorLine);
                break;
            case C_NOISE_LIM_VOIDSPACE  :
                NoiseLimVoidSpace = ConfigString.ReadDouble(ErrorLine);
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
            case C_T_TEMP_WINDOW_COUNT  :
                UseTemperatureWindow     = true;
                TemperatureWindowMaxCnt  = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_T_TEMP_WINDOW_LIMIT  :
                UseTemperatureWindow     = true;
                TemperatureWindowTmpLim    = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_L_ENGLISH    :
                L_English   = true;
                EnableLanguage(L_ENGLISH);
                break;
            case C_L_NORWEGIAN  :
                L_Norwegian = true;
                EnableLanguage(L_NORWEGIAN);
                break;
            case C_L_GERMAN     :
                L_German    = true;
                EnableLanguage(L_GERMAN);
                break;
            case C_L_DUTCH     :
                L_Dutch    = true;
                EnableLanguage(L_DUTCH);
                break;
            case C_L_FRENCH     :
                L_French    = true;
                EnableLanguage(L_FRENCH);
                break;
            case C_L_SPANISH    :
                L_Spanish   = true;
                EnableLanguage(L_SPANISH);
                break;
            case C_L_PORTUGUESE :
                L_Portuguese = true;
                EnableLanguage(L_PORTUGUESE);
                break;
            case C_PRO_READ_PERMISSION:
                ReadPermissionSet = ReadIdTable(ConfigString, ErrorLine, C_PROLIST_END);
                if (ErrorLine) {
                    NoError = false;
                }
                break;
            case C_PRO_WRITE_PERMISSION:
                WritePermissionSet = ReadIdTable(ConfigString, ErrorLine, C_PROLIST_END);
                if (ErrorLine) {
                    NoError = false;
                }
                break;
            case C_PRO_NUMBER_OF_HANHELD:
                NumberOfHandheldUnits = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_DEC_P_VOLUME:
                DecimalPointVolume = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_DEC_P_WEIGHT:
                DecimalPointWeight = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_PROJ_ALARMSYS_DELAY:
                AlarmSystemStartUpDelay = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_PROJ_IS_HSH_VESSEL:
                isChemGasProject        = true;
                BasicCargoNameList      = ChemGasCargoNameList;
                SizeofBasicCargoNameList = SizeofChemGasCargoNameList;
                break;
            case C_SD_SIMULATE_IO       :
                SimulateIO          = true;
                break;
            case C_SD_SIMULATE_STATIC   :
                SimulateFixedValues = true;
                break;
            case C_PRESS_LIM_MBAR:
                PressLim_mBar = bool(ConfigString.ReadInteger(ErrorLine));
                NoError = !ErrorLine;
                break;
            case C_UNIT_LENGTH   :
            case C_UNIT_VOLUME   :
            case C_UNIT_PRESSURE1:
            case C_UNIT_PRESSURE2:
            case C_UNIT_PRESSURE3:
                {
                    AnsiString UnitName = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                    if (NoError) {
                        int UnitCode = FindConfigKey(UnitName);
                        if (UnitCode != NOT_FOUND) {
                            switch (Key) {
                            case C_UNIT_VOLUME   :
                                UnitCode -= C_U_METER3; // This is the first Unit code.
                                UserUnits[VOLUME_UNIT] = UnitCode;
                                break;
                            case C_UNIT_LENGTH   :
                                UnitCode -= C_U_METER; // This is the first Unit code.
                                UserUnits[LENGTH_UNIT] = UnitCode;
                                break;
                            case C_UNIT_PRESSURE1:
                                UnitCode -= C_U_METERH2O; // This is the first Unit code.
                                UserUnits[PRESSURE_UNIT1] = UnitCode;
                                break;
                            case C_UNIT_PRESSURE2:
                                UnitCode -= C_U_METERH2O; // This is the first Unit code.
                                UserUnits[PRESSURE_UNIT2] = UnitCode;
                                break;
                            case C_UNIT_PRESSURE3:
                                UnitCode -= C_U_METERH2O; // This is the first Unit code.
                                UserUnits[PRESSURE_UNIT3] = UnitCode;
                                break;
                            }
                        }
                    }
                }
                break;
            case C_ALARM_SETTINGS_PIN_LOCK:
                {
                    AnsiString alarmSettingsEnabled = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;

                    if (NoError) {
                        int localKey = FindConfigKey(alarmSettingsEnabled);
                        bool Enable = true;
                        switch (localKey) {
                        case C_ENABLE:
                            Enable = true;
                            break;
                        case C_DISABLE:
                            Enable = false;
                            break;
                        }
                        PROProjectInfo::PROProjectInfoPtr->AlarmSettingsPINLock = Enable;
                    }
                }
                break;
            case C_REQUEST_CONFIG:
                RequestConfig = FLASH_RET_MODE_CONF;
                break;
            case C_PROJ_IP_ADDRESS    :
                {
                    AnsiString tmpIP_Address = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                    if (NoError) {
                        IP_Address = tmpIP_Address + ".0";
                    }
                    IP_AddressMain = inet_addr(IP_Address.c_str());
                }
                break;
            case C_PROJ_IP_ADDRESS_GATEWAY         :
                IP_AddressGateWay = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_PROJ_IP_ADDRESS_TCU_MASTER      :
                IP_AddressTCU_Master = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_PROJ_IP_ADDRESS_TCU_SLAVE_START :
                IP_AddressTCUSlaveStart = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_PROJ_IP_ADDRESS_TCU_SLAVE_END   :
                IP_AddressTCUSlaveEnd = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_PROJ_IP_ADDRESS_TDU_START       :
                IP_AddressTDUStart = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_PROJ_IP_ADDRESS_TDU_END         :
                IP_AddressTDUEnd = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_PROJ_IP_ADDRESS_PC_START        :
                IP_AddressPCStart = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_PROJ_IP_ADDRESS_PC_END          :
                IP_AddressPCEnd = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_PROJ_IP_TCP_SERVER_PORT:
                IP_TCP_ServerPort = ConfigString.ReadInteger(ErrorLine);
                break;
            case C_PROJ_IP_UDP_NET_PORT   :
                IP_UDP_NetPort = ConfigString.ReadInteger(ErrorLine);
                break;
                /*
            case C_PROJ_IP_TCP_FLASH_PORT :
                IP_TCP_FlashPort = ConfigString.ReadInteger(ErrorLine);
                break;
                */
            case TWM_CLEANING_MEDIA_LIST:
                {
                    TankWashingAPI twApi;
                    NoError = twApi.LoadTankCleaningMediaList(ConfigString);
                    ErrorLine = 0;

                    if (NoError == false) {

                        AnsiString errorMsg("Failed to read tank cleaning media list");
                        GiveConfigWarning(errorMsg, InputKeyWord, ConfigString.LineCount);
                    }
                }
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
	//if (!LengthBetweenMarks) {
	//    LengthBetweenMarks = LengthBetweenPP;
    //}
    /*
    // Check the extra pressure alarms. HighLim2 > HighLim1, LowLim2 < LowLim1
    if (IntHighTankPressLimit1 > IntHighTankPressLimit2 ) {
        swap(IntHighTankPressLimit1, IntHighTankPressLimit2);
        //GiveConfigWarning("ExtraHighTankPressLimit1 > ExtraHighTankPressLimit2, line " + AnsiString(ConfigString.LineCount));
    }
    if ( IntLowTankPressLimit1  < IntLowTankPressLimit2 ) {
        swap(IntLowTankPressLimit1, IntLowTankPressLimit2);
        //GiveConfigWarning("ExtraHighTankPressLimit1 < ExtraHighTankPressLimit2, line " + AnsiString(ConfigString.LineCount));
    }
    */
    if ( HighLinePressLimit > LIMIT_HIHI_LINEPRESS) {
        HiHiLinePressLimit = HighLinePressLimit;
    }
    return ErrorLine;
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int PROProjectInfo::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_SHIP_LPP:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = LengthBetweenPP;
        break;
    case SVT_SHIP_WIDTH:
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        MyRetValue = Width;
        break;
    default:
        Status = PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int PROProjectInfo::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_CALL_SIGN:
        MyString =  CallSign;
        break;
    case SVT_SHIP_OWNER:
        MyString =  ProjOwner;
        break;
    case SVT_SYSTEM_ID:
        MyString =  ProjectName;
        break;
    case SVT_SHIP_NAME:
        MyString =  Name;
        break;
    default:
        Status = PRogramObjectBase::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int PROProjectInfo::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    //switch ( ValueId ) {
    //  default:
    Status = PRogramObjectBase::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
    //     break;
    //}
    if (Status == E_NO_ERR) {
        SetModifiedFlag();
    }
    if (UnitId) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int PROProjectInfo::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = PRogramObjectBase::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return (Status);
}

ValueList* PROProjectInfo::GetValueInfoTableStatic(int &Entries, int Index) {
    Entries = 0;
    return (NULL);
}



