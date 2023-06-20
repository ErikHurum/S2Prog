//---------------------------------------------------------------------------
#include <algorithm>
#ifdef BORLAND
#include "ANWinInc.h"
#include <Dialogs.hpp>
#pragma hdrstop
#ifdef ANCONF
#include <ConfigWarningsForm.h>
#endif
#ifdef ANWIN
	#include "MainUnit.h"
#endif
#pragma package(smart_init)
#else
#include "TDUIncludes.h"
#endif
//---------------------------------------------------------------------------

ConfigKeyWord SurvConfigKey[] =
{
// Common, used in several objects, Range: 100 -> 199
    { "Enabled"                     , C_ENABLE },
    { "Disabled"                    , C_DISABLE },
    { "On"                          , C_ON },
    { "Off"                         , C_OFF },
    { "Open"                        , C_OPEN },
    { "Closed"                      , C_CLOSE },
    { "None"                        , C_NONE },
    { "ScratchPage"                 , C_SCRATCH_PAGE },
    { "isVolatile"                  , C_VOLATILE },
    { "PreviousEnable"              , C_PREVIOUS_ENABLE },
    { "PreviousDisable"             , C_PREVIOUS_DISABLE },


    { "PressLim_mBar"               , C_PRESS_LIM_MBAR },
    { "XPos"                        , C_XPOS },
    { "YPos"                        , C_YPOS },
    { "ZPos"                        , C_ZPOS },
    { "Page"                        , C_PAGE },
    { "Description"                 , C_DESCRIPTION },
    { "Unsigned"                    , C_UNSIGNED },
    { "Signed"                      , C_SIGNED },
    { "Range"                       , C_RANGE },
    { "BitOffset"                   , C_BIT_OFFSET },
    { "DecimalPoint"                , C_DECIMAL_POINT },
    { "FloatingPoint"               , C_FLOATING_POINT     },
    { "FloatingPointReversed"       , C_FLOATING_POINT_REV },

    { "FloatBigEndian"              , C_FLOAT_BIG_ENDIAN        },
    { "FloatLittleEndian"           , C_FLOAT_LITTLE_ENDIAN     },
    { "FloatBigEndianByteSwap"      , C_FLOAT_B_END_BYTE_SWAP   },
    { "FloatLittleEndianByteSwap"   , C_FLOAT_L_END_BYTE_SWAP   },
    { "Int32BigEndian"              , C_INT_BIG_ENDIAN          },
    { "Int32LittleEndian"           , C_INT_LITTLE_ENDIAN       },
    { "Int32BigEndianByteSwap"      , C_INT_B_END_BYTE_SWAP     },
    { "Int32LittleEndianByteSwap"   , C_INT_L_END_BYTE_SWAP     },

    { "ObjectId"                    , C_OBJECT_ID },
    { "ObjectIdList"                , C_OBJECT_ID_LIST },
    { "MyObjectId"                  , C_MY_OBJECT_ID },
    { "RefObjectId"                 , C_REF_OBJECT_ID },
    { "ValueKey"                    , C_VALUE_KEY },
    { "Online"                      , C_ONLINE },
    { "Offline"                     , C_OFFLINE },
    { "Delay"                       , C_DELAY },
    { "Relaxed"                     , C_RELAXED },
    { "TimeOut"                     , C_TIMEOUT },
    { "LogPeriod"                   , C_LOG_PERIOD },
    { "LogEntries"                  , C_LOG_ENTRIES },
    { "IsWarning"                   , C_WARNING },
    { "RequestConfig"               , C_REQUEST_CONFIG },
    { "NumberOfCopies"              , C_NUMBER_OF_COPIES     },
    { "RegisterStepsIn"             , C_REGISTER_STEPS_IN },
    { "RegisterStepsOut"            , C_REGISTER_STEPS_OUT },
    { "CoilStepsIn"                 , C_COIL_STEPS_IN  },
    { "CoilStepsOut"                , C_COIL_STEPS_OUT },
    { "ExcludeIdList"               , C_OBJECT_ID_IGNORE_LIST },
    { "String10"                    , C_STRING10 },
    { "String20"                    , C_STRING20 },

    { "AutoReset"                   , C_AUTORESET },


// Sensor location
    { "Bottom"                      , C_AI_LOC_BOTTOM },
    { "Middle"                      , C_AI_LOC_MIDDLE },
    { "Upper"                       , C_AI_LOC_UPPER },
    { "TankPress"                   , C_AI_LOC_VAPOUR },
    { "PumpRm"                      , C_AI_LOC_PUMP_ROOM },
    { "EngRm"                       , C_AI_LOC_ENGINE_ROOM },
    { "Deck"                        , C_AI_LOC_DECK },
    { "System"                      , C_AI_LOC_SYSTEM },
    { "NotDef"                      , C_AI_LOC_NOT_DEFINED },
    { "Main"                        , C_AI_LOC_WI_MAIN },
    { "Pre"                         , C_AI_LOC_WI_PRE },
    { "Trim"                        , C_AI_LOC_INC_TRIM },
    { "List"                        , C_AI_LOC_INC_LIST },
    { "Temp"                        , C_AI_LOC_TEMP },
    { "Temp1"                       , C_AI_LOC_TEMP1        },
    { "Temp2"                       , C_AI_LOC_TEMP2        },
    { "Temp3"                       , C_AI_LOC_TEMP3        },
    { "Temp4"                       , C_AI_LOC_TEMP4        },
    { "Temp5"                       , C_AI_LOC_TEMP5        },
    { "Temp6"                       , C_AI_LOC_TEMP6        },
    { "Temp7"                       , C_AI_LOC_TEMP7        },
    { "Temp8"                       , C_AI_LOC_TEMP8        },
    { "Temp9"                       , C_AI_LOC_TEMP9        },
    { "Temp10"                      , C_AI_LOC_TEMP10       },
    { "TempIn"                      , C_AI_LOC_TEMP_IN      },
    { "TempOut"                     , C_AI_LOC_TEMP_OUT     },
    { "TankCleanLine"               , C_AI_LOC_TANK_CLEAN   },

// Main PRogramObjects, Range: 1000 -> 1199
    {   "PROEnd"                    , C_PRO_END },
    {   "PROStartCommon"            , C_PRO_START_COMMON },
    {   "PROEndCommon"              , C_PRO_END_COMMON },
    {   "PROStartPRO"               , C_PRO_START_PRO },
    {   "PROEndPRO"                 , C_PRO_END_PRO },

    {   "ConfigInfo"             , C_CONFIG_INFO },
    {   "PROProjectInfo"         , C_PRO_PROJINFO },
    {   "PROSystemData"          , C_PRO_SYSDATA },
    {   "PROAtmReference"        , C_PRO_ATMREFSENS },
    {   "PROInclinometer"        , C_PRO_INC },
    {   "PRODraftSystem"         , C_PRO_DRAFT_SYSTEM },
    {   "PRODraft"               , C_PRO_DRAFT },
    {   "PROTank"                , C_PRO_TANK },
    {   "PROCargoTank"           , C_PRO_CARGO },
    {   "PROBallastTank"         , C_PRO_BALLAST },
    {   "PROHFOTank"             , C_PRO_HFO },
    {   "PRODOTank"              , C_PRO_DO },
    {   "PROLUBTank"             , C_PRO_LUB },
    {   "PROFWTank"              , C_PRO_FW },
    {   "PROMISCTank"            , C_PRO_MISC },
    {   "PROVoidSpace"           , C_PRO_VOIDSPACE },
    {   "PROTankPressure"        , C_PRO_TANKPRESS },
    {   "PROTemperature"         , C_PRO_TEMP },
    {   "PROLevelSwitch"         , C_PRO_LEVSWITCH },
    {   "PROWaterIngress"        , C_PRO_WATERINGRESS },
    {   "PROLinePressure"        , C_PRO_LINEPRESS },
    {   "PROTanksystemUnit"      , C_PRO_TANKSYS_UNIT },
    {   "PROPrinter"             , C_PRO_PRINTER },
    {   "PROTankPanelContr"      , C_PRO_T_PANEL_CONTR },
    {   "PROTPC140"              , C_PRO_TPC140 },
    {   "PROTPC350"              , C_PRO_TPC350 },
    {   "PROTPC196"              , C_PRO_TPC196 },
    {   "PROControl"             , C_PRO_CONTROL },
    {   "PROCtrlAlRelay"         , C_PRO_CTRL_AL_RELAY },
    {   "PROCtrlBuzzer"          , C_PRO_CTRL_BUZZER },
    {   "PROCtrlLight"           , C_PRO_CTRL_LIGHT },
    {   "PROCtrlHorn"            , C_PRO_CTRL_HORN },
    {   "PROCtrlLamp"            , C_PRO_CTRL_LAMP },
    {   "PROANPro3"              , C_PRO_ANPRO3 },
    {   "PROSaab"                , C_PRO_SAAB_PROTOCOL },
    {   "SaabExtraLPress"        , C_SAAB_EXPORT_LPRESS },
    {   "SaabExtraTPress"        , C_SAAB_EXPORT_TPRESS },
    {   "SaabExtraAtmPress"      , C_SAAB_EXPORT_ATM_PRESS },
    {   "SaabExtraTemp"          , C_SAAB_EXPORT_TEMP },

    {   "ModbusCoilIn"           , C_PRO_MODBUS_COIL_IN    },
    {   "ModbusCoilOut"          , C_PRO_MODBUS_COIL_OUT   },
    {   "ModbusCoilHistory"      , C_PRO_MODBUS_COIL_HIST  },
    {   "ModbusRegIn"            , C_PRO_MODBUS_REG_IN     },
    {   "ModbusWago473In"        , C_PRO_MBUS_WAGO473_RIN  },
    {   "ModbusWago479In"        , C_PRO_MBUS_WAGO479_RIN  },
    {   "ModbusWago482In"        , C_PRO_MBUS_WAGO482_RIN  },
    {   "ModbusWago485In"        , C_PRO_MBUS_WAGO485_RIN  },
    {   "ModbusWago487In"        , C_PRO_MBUS_WAGO487_RIN  },
    {   "ModbusRegBitIn"         , C_PRO_MODBUS_REG_BIT_IN },
    {   "ModbusRegBitOut"        , C_PRO_MODBUS_REG_BIT_OUT},
    {   "ModbusRegOut"           , C_PRO_MODBUS_REG_OUT    },
    {   "ModbusRegHistory"       , C_PRO_MODBUS_REG_HIST   },

    {   "ModbusMultiple"         , C_PRO_MODBUS_MULTIPLE    },

    {   "PROUser"                , C_PRO_USER },
    {   "UserName"               , C_PRO_USER_NAME },
    {   "UserPassword"           , C_PRO_USER_PASSWORD },
    {   "UserIdNumber"           , C_PRO_USER_ID_NUMBER },
    {   "NumberOfHanheldUnits"   , C_PRO_NUMBER_OF_HANHELD },

    {   "PROWaterHeater"         , C_PRO_WATER_HEATER },
    {   "PROTankWashingMachine"  , C_PRO_TANK_WASH_MACHINE },
    {   "PROVOCTrack"            , C_PRO_WOCTRACK },


// Project Info, Range: 1200 -> 1299
    {   "ProjectName"            , C_PROJ_NAME                      },
    {   "NumberOfTCU"            , C_PROJ_NUM_TCU                   },
    {   "NumberOfTDU"            , C_PROJ_NUM_TDU                   },
    {   "ProjectType"            , C_PROJ_TYPE                      },

    {   "ProjectTypeName"        , C_PROJ_TYPE_NAME                 },
    {   "ProjTypeName"           , C_PROJ_TYPE_NAME2                },
    {   "CallSign"               , C_PROJ_CALLSIGN                  },
    {   "IMONumber"              , C_PROJ_IMO_NUM                   },
    {   "LengthBetweenPP"        , C_PROJ_LENGTH_BETWEEN_PP         },
    {   "LengthBetweenMarks"     , C_PROJ_LENGTH_BETWEEN_MARKS      },
    {   "Width"                  , C_PROJ_TOT_WITH                  },
    {   "LoadingComputer"        , C_PROJ_LOADING_COMPUTER          },
    {   "LoadRateMaxLoadTime"    , C_PROJ_LOADRATE_LOAD_TIME        },
    {   "IsInlandVessel"         , C_PROJ_IS_INLAND_VESSEL          },
    {   "IsCustodyTransferSys"   , C_PROJ_IS_CUSTODY_TRANSFER_SYS   },
    {   "AutoAlarmAcknowledge"   , C_PROJ_AUTO_ALARM_ACKN           },
    {   "AlarmSystemDelay"       , C_PROJ_ALARMSYS_DELAY            },

    {   "IsHSHVessel"            , C_PROJ_IS_HSH_VESSEL             },
    {   "IP_AddressRange"        , C_PROJ_IP_ADDRESS                },
    {   "IP_AddressGateWay"      , C_PROJ_IP_ADDRESS_GATEWAY        },
    {   "IP_AddressTCUMaster"    , C_PROJ_IP_ADDRESS_TCU_MASTER     },
    {   "IP_AddressTCUSlaveStart", C_PROJ_IP_ADDRESS_TCU_SLAVE_START},
    {   "IP_AddressTCUSlaveEnd"  , C_PROJ_IP_ADDRESS_TCU_SLAVE_END  },
    {   "IP_AddressTDUStart"     , C_PROJ_IP_ADDRESS_TDU_START      },
    {   "IP_AddressTDUEnd"       , C_PROJ_IP_ADDRESS_TDU_END        },
    {   "IP_AddressPCStart"      , C_PROJ_IP_ADDRESS_PC_START       },
    {   "IP_AddressPCEnd"        , C_PROJ_IP_ADDRESS_PC_END         },
    {   "IP_TCP_ServerPort"      , C_PROJ_IP_TCP_SERVER_PORT        },
    {   "IP_UDP_NetPort"         , C_PROJ_IP_UDP_NET_PORT           },
 //   {   "IP_TCP_FlashPort"       , C_PROJ_IP_TCP_FLASH_PORT         },
    {   "SnsNoiseLimitCargoB"    , C_NOISE_LIM_CARGO_B },
    {   "SnsNoiseLimitCargoU"    , C_NOISE_LIM_CARGO_U },
    {   "SnsNoiseLimitBallastB"  , C_NOISE_LIM_BALLAST_B },
    {   "SnsNoiseLimitBallastU"  , C_NOISE_LIM_BALLAST_U },
    {   "SnsNoiseLimitServiceB"  , C_NOISE_LIM_SERVICE_B },
    {   "SnsNoiseLimitServiceU"  , C_NOISE_LIM_SERVICE_U },
    {   "SnsNoiseLimitRadar"     , C_NOISE_LIM_RADAR },
    {   "SnsNoiseLimitVoidSpace" , C_NOISE_LIM_VOIDSPACE },

    {   "LanguageEnglish"        , C_L_ENGLISH },
    {   "LanguageNorwegian"      , C_L_NORWEGIAN },
    {   "LanguageGerman"         , C_L_GERMAN },
    {   "LanguageDutch"          , C_L_DUTCH },

    {   "LanguageFrench"         , C_L_FRENCH },
    {   "LanguageSpanish"        , C_L_SPANISH },
    {   "LanguagePortuguese"     , C_L_PORTUGUESE },
    {   "DecimalPointVolume"     , C_DEC_P_VOLUME },
    {   "DecimalPointWeight"     , C_DEC_P_WEIGHT },

    {   "PressureUnit1"          , C_UNIT_PRESSURE1 },
    {   "PressureUnit2"          , C_UNIT_PRESSURE2 },
    {   "PressureUnit3"          , C_UNIT_PRESSURE3 },

    {   "MeterH2O"               , C_U_METERH2O },
    {   "mmH2O"                  , C_U_MMH2O    },
    {   "mBar"                   , C_U_MBAR     },
    {   "Bar"                    , C_U_BAR      },
    {   "PSI"                    , C_U_PSI      },
    {   "KPA"                    , C_U_KPA      },
    {   "InchH2O"                , C_U_INCH_H2O },
    {   "InchHg"                 , C_U_INCH_HG  },

    {   "LengthUnit"             , C_UNIT_LENGTH },

    {   "meter"                  , C_U_METER     },
    {   "feet"                   , C_U_FEET      },
    {   "DecimalFeet"            , C_U_DEC_FEET  },

    {   "VolumeUnit"             , C_UNIT_VOLUME },

    {   "meter3"                 , C_U_METER3    },
    {   "liter"                  , C_U_LITER     },
    {   "USGallons"              , C_U_USGALLON  },
    {   "USBarrels"              , C_U_USBARRELS },

    {   "AlarmSettingsPINLock"   , C_ALARM_SETTINGS_PIN_LOCK },

// PRO common, Range: 1300 -> 13 49
    {   "Name"                   , C_PRO_NAME },
    {   "LongName"               , C_PRO_LONGNAME },
    {   "TagName"                , C_PRO_TAGNAME },
    {   "SortNo"                 , C_PRO_SORTNO },
    {   "ReadPermission"         , C_PRO_READ_PERMISSION },
    {   "WritePermission"        , C_PRO_WRITE_PERMISSION },
    {   "IDNumber"               , C_PRO_ID_NUMBER },
// Shared, Range: 1350 -> 1359
    {   "PROListStart"           , C_PROLIST_START },
    {   "PROListTable"           , C_PROLIST_TABLE },
    {   "PROListEnd"             , C_PROLIST_END },
    {   "HasPotection"           , C_WIS_HAS_PROT },      // EHSMark Spell error
    {   "HasNoPotection"         , C_WIS_HAS_NO_PROT }, // EHSMark Spell error
    {   "HasProtection"          , C_WIS_HAS_PROT },
    {   "HasNoProtection"        , C_WIS_HAS_NO_PROT },


// Tank, Range: 1360 -> 1499

    {   "UseTempFromOtherId", C_COMMON_TEMPERATURE },
    {   "UsePressFromOtherId", C_COMMON_PRESSURE },
    {   "DBotUllRefPnt", C_D_BOT_ULL_REF },
    {   "DBU", C_D_BOT_ULL_REF2 },
    {   "DBotManMsrPnt", C_D_BOT_MAN_MSR },
    {   "SMID", C_D_SNS_MID },
    {   "SCL", C_D_SNS_CL2 },
    {   "DSnsToMid", C_D_SNS_MID2 },
    {   "DSnsToCL", C_D_SNS_CL },
    {   "RMID", C_D_MAN_MSR_MID2 },
    {   "RCL", C_D_MAN_MSR_CL2 },
    {   "DManMsrPntToMid", C_D_MAN_MSR_MID },
    {   "DManMsrPntToCL", C_D_MAN_MSR_CL },
    {   "FMID", C_D_FC_MID2 },
    {   "FCL", C_D_FC_CL2 },
    {   "DFltCntToMid", C_D_FC_MID },
    {   "DFltCntToCL", C_D_FC_CL },
    {   "DLU", C_D_L_MAN_MSR_SNS2 },
    {   "DTU", C_D_T_MAN_MSR_SNS2 },
    {   "DVU", C_D_V_MAN_MSR_SNS2 },
    {   "DLManMsrPntToSns", C_D_L_MAN_MSR_SNS },
    {   "DTManMsrPntToSns", C_D_T_MAN_MSR_SNS },
    {   "DVManMsrPntToSns", C_D_V_MAN_MSR_SNS },
    {   "DVUllRefToUTI", C_D_V_ULL_REF_TO_UTI },

    {   "DLFC", C_D_L_FC_SNS2 },
    {   "DTFC", C_D_T_FC_SNS2 },
    {   "DLFltCntToSns", C_D_L_FC_SNS },
    {   "DTFltCntToSns", C_D_T_FC_SNS },

    {   "DLSensorToRadar", C_D_L_SENSOR_TO_RADAR },
    {   "DTSensorToRadar", C_D_T_SENSOR_TO_RADAR },
    {   "DVSensorToRadar", C_D_V_SENSOR_TO_RADAR },
    {   "MinMsrdDnsDist", C_MIN_DNS_DIST },

    {   "Redundancy", C_REDUNDANCY },

    {   "LevelOffset", C_ADJUST_LEVEL_OFFSET1 },
    {   "AdjustLevelOffset", C_ADJUST_LEVEL_OFFSET },
    {   "AdjustTableOffset", C_ADJUST_TABLE_OFFSET },

    {   "VolumeOffset", C_ADJUST_VOLUME_OFFSET1 },
    {   "AdjustVolumeOffset", C_ADJUST_VOLUME_OFFSET },
    {   "VolumeVolCorrFactor", C_VOLUME_CORR_FACTOR },


    {   "GlobalRefSystem"               , C_GLOBAL_REFSYS },
    {   "UseCFTab"                      , C_USE_CF_TAB },
    {   "DataFromOther"                 , C_DATA_FROM_OTHER },
    {   "RadarThreshold"                , C_RADAR_THRESHOLD },


    {   "TableOffset"                   , C_T_TABLEOFFSET },
    {   "UllageVolTable"                , C_T_ULLAGE_VOL_TABLE },
    {   "LevelVolTable"                 , C_T_LEVEL_VOL_TABLE },
    {   "SoundingTable"                 , C_T_SOUNDING_TABLE },
    {   "CenterOfFlotationTable"        , C_T_COF_TABLE },
    {   "CorrectionTableTrim"           , C_T_VCORR_TABLE_TRIM },
    {   "CorrectionTableList"           , C_T_VCORR_TABLE_LIST },
    {   "CorrectionTableTemp"           , C_T_VCORR_TABLE_TEMP },
    {   "CorrectionTableDensity"        , C_T_DENSITY_CORR_TABLE },
    {   "CorrectionEntries"             , C_T_CORRECTION_ENTRIES },
    {   "CorrectionFactor"              , C_T_CORRECTION_FACTOR },
    {   "TempWindowCount"               , C_T_TEMP_WINDOW_COUNT },
    {   "TempWindowLimit"               , C_T_TEMP_WINDOW_LIMIT },



    {   "CenterOfGravityTable"          , C_T_COG_TABLE },
    {   "StartTable"                    , C_T_TABLE_START },
    {   "EndTable"                      , C_T_TABLE_END },
    {   "EndTableObject"                , C_T_TABLE_OBJ_END },

    {   "PresentAtSensor"               , C_T_P_AT_SENSOR },
    {   "PresentAtCF"                   , C_T_P_AT_CF },
    {   "PresentAtRefPt"                , C_T_P_AT_REFPT },


    {   "CargoType"                     , C_CARGO_TYPE },
    {   "UserCargoType"                 , C_PRO_USER_CARGO_TYPE },
    {   "CargoTypeKey"                  , C_CT_CARGO_TYPE_KEY },
    {   "BasicCargoType"                , C_CT_BASIC_CARGO_TYPE },
    {   "CargoEnd"                      , C_CT_END },
    {   "OD1"                           , C_CT_OD1 },
    {   "OD2"                           , C_CT_OD2 },
    {   "RefTemp1"                      , C_CT_REFTEMP1 },
    {   "RefTemp2"                      , C_CT_REFTEMP2 },
    {   "Coeff"                         , C_CT_COEFF },
    {   "MolMass"                       , C_CT_MOLMASS },
    {   "Viscosity"                     , C_CT_VISCOSITY },
    {   "DB_IdNumber"                   , C_CT_DB_IDNUMBER },

    {   "UseMeasDens"                   , C_CT_USEMEAS_DENS },
    {   "CargoColour"                   , C_CT_COLOUR },
    {   "CargoName"                     , C_CT_NAME },
    {   "CargoIsDefined"                , C_CT_IS_DEFINED },
    {   "CargoHighTempLimit"            , C_CT_HIGH_TEMP },
    {   "CargoLowTempLimit"             , C_CT_LOW_TEMP },
    {   "CargoHighTempEnable"           , C_CT_HIGH_TEMP_ENABLE },
    {   "CargoLowTempEnable"            , C_CT_LOW_TEMP_ENABLE },
// Inclinometer, Range: 1500 -> 1599
    {   "MountedOn"                     , C_INC_MOUNTED },
    {   "Forward"                       , C_INC_FORWARD },
    {   "Aft"                           , C_INC_AFT },
    {   "Port"                          , C_INC_PORT },
    {   "Starboard"                     , C_INC_STARBOARD },
// AtmReference, Range: 1550 -> 1599
    {   "SensorOnTCU"                   , C_ATM_ON_TCU },
    {   "UseManual"                     , C_ATM_USEMANUAL },
    {   "NotUseManual"                  , C_ATM_NOT_USEMANUAL },
    {   "ManPress"                      , C_ATM_MAN_PRESS },
    {   "ManualTrim"                    , C_SD_MANUAL_TRIM },
    {   "ManualList"                    , C_SD_MANUAL_LIST },
    {   "AmbientTemp"                   , C_SD_AMBIENT_TEMP },
    {   "SeaWaterTemp"                  , C_SD_SEAWATER_TEMP },
    {   "SeaWaterDensity"               , C_SD_SEAWATER_DNS },
    {   "BallastDensity"                , C_SD_BALLAST_DNS },
    {   "FreshWaterDensity"             , C_SD_FRESHWATER_DNS },
    {   "HeavyFuelDensity"              , C_SD_HEAVY_FUEL_DNS },
    {   "DieselDensity"                 , C_SD_DIESEL_DNS },
    {   "LubricantsDensity"             , C_SD_LUBRICANTS_DNS },
// Draft, Range: 1600 -> 1699
    {   "DraftEnd"                      , C_DRAFT_END },
    {   "DraftFore"                     , C_DRAFT_DF },
    {   "DraftPort"                     , C_DRAFT_DP },
    {   "DraftStarboard"                , C_DRAFT_DS },
    {   "DraftAft"                      , C_DRAFT_DA },
    {   "DraftAftPort"                  , C_DRAFT_DAP },
    {   "DraftAftStarboard"             , C_DRAFT_DAS },
    {   "DraftFwdPort"                  , C_DRAFT_DFP },
    {   "DraftFwdStarboard"             , C_DRAFT_DFS },
//  {   "GlobalRefSystem"               , C_DRAFT_GLOBAL_REF },
    {   "DLMark"                        , C_D_L_MARK },
    {   "DTMark"                        , C_D_T_MARK },
    {   "DLPerp"                        , C_D_L_PERP },
    {   "DTPerp"                        , C_D_T_PERP },
    {   "DraftOffset"                   , C_DRAFT_OFFSET },
    {   "DPerpToMid"                    , C_D_PERP_MID },
    {   "DMarkToMid"                    , C_D_MARK_MID },
    {   "DMarkToMid1"                   , C_D_MARK_MID },
    {   "DMarkToMid2"                   , C_D_MARK_MID2 },
    {   "MaxSummerDraft"                , C_MAX_SUMMER_DRAFT },
// TPCxObject, Range: 1700 -> 1799
    {   "TPCStartCommon"                , C_TPC_START_COMMON },
    {   "TPCEndCommon"                  , C_TPC_END_COMMON },
    {   "TPCType"                       , C_TPC_TYPE },
    {   "TPC140"                        , C_TPC_140 },
    {   "TPC350"                        , C_TPC_350 },
    {   "TPC196"                        , C_TPC_196 },
    {   "PrimaryAddress"                , C_TPC_PRI_ADDR },
    {   "SecondaryAddress"              , C_TPC_SEC_ADDR },
    {   "OnePROPtrOnly"                 , C_TCU_ONE_PROPTR },
    {   "TPCWindow"                     , C_TPC_WINDOW },
    {   "TPCWindowEnd"                  , C_TPC_END_WINDOW },
    {   "UpperDisplay"                  , C_TPC_UPPER_DISP },
    {   "MainDisplay"                   , C_TPC_MAIN_DISP },
    {   "LowerDisplay"                  , C_TPC_MAIN_DISP },
    {   "TopDisplay"                    , C_TPC_TOP_DISP },
    {   "BottomDisplay"                 , C_TPC_BOTTOM_DISP },
    {   "MainGraph"                     , C_TPC_MAIN_GRAPH },
    {   "WindowPROIDNo"                 , C_TPC_WINDOW_PRO_ID },
    // {   "TPCAlarmWindow"                 , C_TPC_ALARM_WINDOW},
// Config info, Range: 1800 -> 1899
    {   "ConfigVersion"                 , C_CONFIG_VERSION },
    {   "ConfigDate"                    , C_CONFIG_DATE },
    {   "ConfigDataRevision"            , C_CONFIG_DATA_REV },
    {   "ConfigRevisePerson"            , C_CONFIG_REV_PERSON },
    {   "ConfigRevisionText"            , C_CONFIG_REV_TEXT },
    {   "ConfigCompatibilityNo"         , C_CONFIG_COMPATI_NO },
    {   "ConfigWritePermission"         , C_CONFIG_CAN_WRITE },

    {   "HighestCargoNo"                , C_HIGH_CARGO_NO },
    {   "HighestTankNo"                 , C_HIGH_TANK_NO },
    {   "HighestTempNo"                 , C_HIGH_TEMP_NO },
    {   "HighestTPressNo"               , C_HIGH_TPRESS_NO },
    {   "HighestWIngressNo"             , C_HIGH_WINGRESS_NO },
// Ctrl, Range: 1900 -> 1999
    {   "CtrlEnd"                       , C_CTRL_END },
    {   "CtrlStartCommon"               , C_CTRL_START_COMMON },
    {   "CtrlEndCommon"                 , C_CTRL_END_COMMON },
    {   "AlarmAlternative"              , C_CTRL_ALTERNATIVE },
    {   "AllAlarms"                     , C_CTRL_ALT_ALL },
    {   "AlarmTypes"                    , C_CTRL_ALT_AL_TYPES },
    {   "PROList"                       , C_CTRL_ALT_PRO_LIST },
    {   "AlarmTypePROList"              , C_CTRL_ALT_TYPE_PRO },
    {   "CtrlAlType"                    , C_CTRL_AL_TYPE },

    {   "NormalState"                   , C_CTRL_NORMAL_STATE },
    {   "NormallyClosed"                , C_CTRL_NS_POWERED },
    {   "Powered"                       , C_CTRL_NS_POWERED2 },
    {   "NormallyOpen"                  , C_CTRL_NS_UNPOWERED },
    {   "UnPowered"                     , C_CTRL_NS_UNPOWERED2 },
    {   "AlarmDelay"                    , C_CTRL_AL_DELAY },
    {   "DeactivateBy"                  , C_CTRL_DEACTIVATE },
    {   "Acknowledge"                   , C_CTRL_DE_ACKNOW },
    {   "Idle"                          , C_CTRL_DE_IDLE },
    {   "Value"                         , C_CTRL_DE_VALUE },
    {   "ValueEnabled"                  , C_CTRL_DE_VAL_ENABLED },
    {   "Silence"                       , C_CTRL_DE_SILENCE },
    {   "PulseWidth"                    , C_CTRL_PULSE_WIDTH },

// IOComponent, Range: 2000 -> 2099
    {   "IOComponent"                   , C_IO_COMPONENT },
    {   "AnalogInput"                   , C_IOC_ANALOG_IN },
    {   "AnalogOutput"                  , C_IOC_ANALOG_OUT },
    {   "DigitalInput"                  , C_IOC_DIGITAL_IN },
    {   "DigitalOutput"                 , C_IOC_DIGITAL_OUT },
    {   "TCUAddress"                    , C_TCU_ADDRESS },
    {   "TCUPort"                       , C_TCU_PORT },
    {   "TCUPortNo"                     , C_TCU_PORT_NO },
    {   "IOType"                        , C_IO_TYPE },
    {   "IOAddress"                     , C_IO_ADDRESS },
    {   "IOChannel"                     , C_IO_CHANNEL },
    {   "ADCardChannel"                 , C_ADCARD_CH },
    {   "IO_NONE"                       , C_IO_NONE },
    {   "AN_ZBANA"                      , C_IO_AN_ZBANA },
    {   "AN_ZB485"                      , C_IO_AN_ZB485 },
    {   "AN_ZBHART"                     , C_IO_AN_ZBHART },
    {   "Modbus"                        , C_IO_MODBUS },
// Analog input types, Range: 2100 -> 2199
    {   "P906-0110"                     , C_AI_P906_0110 },
    {   "P906-0111"                     , C_AI_P906_0111 },
    {   "ATM/N/Ex"                      , C_AI_ATM_N_Ex },
    {   "ATM/Ex"                        , C_AI_ATM_Ex },
    {   "ATM/Ex/H"                      , C_AI_ATM_Ex_H },
    {   "ATM/N/Ex/0.1"                  , C_AI_ATM_N_Ex_0_1 },
	{   "APT500"          		        , C_AI_APT500 },
	{   "SPT900"          		        , C_AI_SPT900 },
    {   "Generic_4_20mA"                , C_AI_Gen_4_20mA },
    {   "DiffPress_4_20mA"              , C_AI_DIFF_PRESSURE_mA },
    {   "Radar_4_20mA"                  , C_AI_Radar_4_20mA },
    {   "Radar_Hart"                    , C_AI_Radar_Hart },
    {   "AirPurge_Hart"                 , C_AI_AirPurge2 },
    {   "AirPurgeSensor"                , C_AI_AirPurge },
    {   "MB_Press_mA"                   , C_AI_MB_Press_mA      },
    {   "MB_Press_0_20mA"               , C_AI_MB_Press_0_20mA  },
    {   "MB_Press_4_20mA"               , C_AI_MB_Press_4_20mA  },
    {   "MB_DiffPress_mA"               , C_AI_MB_DiffPre_mA    },
    {   "MB_DiffPress_0_20mA"           , C_AI_MB_DiffPre_0_20mA},
    {   "MB_DiffPress_4_20mA"           , C_AI_MB_DiffPre_4_20mA},

    {   "Float_4_20mA"                  , C_AI_Float_4_20mA },
    {   "Pt100"                         , C_AI_Pt100 },
    {   "Pt1000"                        , C_AI_Pt1000 },
    {   "Temp_mA"                       , C_AI_TEMP_mA },
    {   "Temp_AD590"                    , C_AI_TEMP_AD590 },
    {   "Level_switch_ADCard"           , C_AI_LeSw_ADCard },
    {   "Level_switch_Valcom"           , C_AI_LeSw_Valcom },
    {   "Level_switch_API"              , C_AI_LeSw_API },
    {   "Level_switch_Vega"             , C_AI_LeSw_Vega },
    {   "Level_switch_Vega62"           , C_AI_LeSw_Vega62 },
    {   "Level_switch_Vega64"           , C_AI_LeSw_Vega64 },
    {   "Level_switch_Optical"          , C_AI_LeSw_HS },
    {   "Level_switch_mA"               , C_AI_LeSw_mA },
    {   "WashTrackSensor"               , C_AI_WashTrackSensor },
    {   "WashTrack_mV"                  , C_AI_WashTrackSensor2 },
    {   "CoilIn"                        , C_AI_COIL_IN },
    {   "Inclinometer"                  , C_AI_INCLINOMETER },
    {   "Inc1N2"                        , C_AI_INC1_N2 },
    {   "Inc2N2"                        , C_AI_INC2_N2 },
    {   "Inc1Macron"                    , C_AI_INC1_MACRON },
    {   "Inc2Macron"                    , C_AI_INC2_MACRON },
    {   "P1728"                         , C_AI_1728 },

    {   "WISensor"                      , C_AI_WATERINGRESS },
    {   "WIS_Main"                      , C_AI_WATERINGR_MAIN },
    {   "WIS_Pre"                       , C_AI_WATERINGR_PRE },
    {   "WIS_Temp"                      , C_AI_WATERINGR_TEMP },
    {   "GODA_Radar"                    , C_AI_GODA_RADAR },
    {   "Voltage"                       , C_AI_VOLTAGE },
    {   "MetriTape"                     , C_AI_MetriTape },
    {   "HSH_Float"                     , C_AI_HSH_LNG_Float },
    {   "WIS_Temperature"               , C_AI_WATERINGR_TEMP   },
    {   "WIS_TemperaturePre"            , C_AI_WATERINGR_TEMP_P },
    {   "WIS_TemperatureMid"            , C_AI_WATERINGR_TEMP_M },
// Analog input variables, Range        : 2200 -> 2299
    {   "AIEnd"                         , C_AI_END },
    {   "AIStartCommon"                 , C_AI_START_COMMON },
    {   "AIEndCommon"                   , C_AI_END_COMMON },
    {   "Type"                          , C_AI_TYPE },
    {   "SerialNo"                      , C_AI_SERIALNO },
    {   "Distance"                      , C_AI_DISTANCE },
    {   "Gain"                          , C_AI_GAIN },
    {   "Offset"                        , C_AI_OFFSET },
    {   "MinRange"                      , C_AI_MIN_RANGE },
    {   "MaxRange"                      , C_AI_MAX_RANGE },
    {   "CableLength"                   , C_AI_CABLE_LENGTH_SENS2},
    {   "CableLengthShipBoard"          , C_AI_CABLE_LENGTH_SHIP},
    {   "CableLengthSensor"             , C_AI_CABLE_LENGTH_SENS},
    {   "CableResistShipBoard"          , C_AI_CABLE_RES_SHIP   },
    {   "CableResistSensor"             , C_AI_CABLE_RES_SENS   },
    {   "CableResistance"               , C_AI_CABLE_RES_MSRD   },






    {   "NoShorCircuitAlarm"            , C_AI_NO_SHORT_CIRC_AL2 },
    {   "NoShortCircuitAlarm"           , C_AI_NO_SHORT_CIRC_AL },
    {   "IsTankPress"                   , C_AI_TANK_PRESS },
    {   "NL1"                           , C_AI_NL1 },
    {   "NL2"                           , C_AI_NL2 },
    {   "TZS"                           , C_AI_TZS },
    {   "TSS"                           , C_AI_TSS },

    {   "CalData"                       , C_AI_CAL_DATA },
    {   "FRO"                           , C_AI_FRO },
    {   "G1"                            , C_AI_G1 },
    {   "G2"                            , C_AI_G2 },
    {   "G3"                            , C_AI_G3 },

    {   "MinResistance"                 , C_AI_RESISTANCE_MIN },
    {   "MaxResistance"                 , C_AI_RESISTANCE_MAX },
    {   "Resistance"                    , C_AI_RESISTANCE_CONST },
    {   "SupplyVoltage"                 , C_AI_VOLTAGE_CONST },

    {   "EEPROM_Gain"                   , C_AI_EEPROM_GAIN },
    {   "EEPROM_Offset"                 , C_AI_EEPROM_OFFSET },

    {   "mALevelSwitch_On"              , C_AI_MA_LEV_SWITCH_ON },
    {   "mALevelSwitch_Off"             , C_AI_MA_LEV_SWITCH_OFF },
    {   "mALevelSwitch_Window"          , C_AI_MA_LEV_SWITCH_WIN },
    {   "mALevelSwitch_Max_mA"          , C_AI_MA_LEV_SWITCH_MAX },


    {   "ModConfig"             , C_MOD_CONFIG },
    {   "ModSystem"             , C_MOD_SYSTEM },
    {   "ModUser"               , C_MOD_USER },
// Wago types, Range: 2400 -> 2499
    {   "ModbusStartCommon"     , C_MODBUS_START_COMMON },
    {   "ModbusEnd"             , C_MODBUS_END },
    {   "ModbusEndCommon"       , C_MODBUS_END_COMMON },
    {   "ModbusAddress"         , C_MODBUS_ADDRESS },
    {   "ModbusChannel"         , C_MODBUS_CHANNEL },

    {   "ModbusAverage"         , C_MODBUS_AVERAGE },
    {   "ModbusMin"             , C_MODBUS_MIN },
    {   "ModbusMax"             , C_MODBUS_MAX },
    {   "ModbusSum"             , C_MODBUS_SUM },
    {   "ModbusAnd"             , C_MODBUS_AND },
    {   "ModbusOr"              , C_MODBUS_OR },
    {   "ModbusXor"             , C_MODBUS_XOR },
    {   "ModbusNand"            , C_MODBUS_NAND },

    {   "ModbusCmdInputStatus"  , C_MODBUS_CMD_INP_STAT },
    {   "ModbusCmdInputRegister", C_MODBUS_CMD_INP_REG },


// Digital input types, Range: 2500 -> 2599
// Digital input variables, Range: 2600 -> 2699
    {   "DIEnd"                 , C_DI_END },
    {   "DIStartCommon"         , C_DI_START_COMMON },
    {   "DIEndCommon"           , C_DI_END_COMMON },
    {   "DIType"                , C_DI_TYPE },
    {   "DISerialNo"            , C_DI_SERIALNO },
// Alarm, Range: 3000 -> 3999
// ID,  Range: 3000 -> 3199
    {   "AlEnd"                 , C_AL_END },
    {   "AlLimit"               , C_AL_LIMIT },
    {   "AlLocked"              , C_AL_LOCKED },
    {   "AlNotLocked"           , C_AL_NOT_LOCKED },
    {   "AlNotLoced"            , C_AL_NOT_LOCKED2 },
    {   "AlVisible"             , C_AL_VISIBLE },
    {   "AlDescription"         , C_AL_DESCRIPTION },
    {   "AlTPCDescription"      , C_AL_TCP_DESCRIPTION },

    {   "Overfill"              , ID_AL_OVERFILL },
    {   "HighLevel"             , ID_AL_HIGH_LEVEL },
    {   "LowLevel"              , ID_AL_LOW_LEVEL },
    {   "LowLowLevel"           , ID_AL_LOWLOW_LEVEL },
    {   "HighTemp"              , ID_AL_HIGH_TEMP },
    {   "LowTemp"               , ID_AL_LOW_TEMP },
    {   "HighBotTemp"           , ID_AL_HIGH_BOT_TEMP },
    {   "LowBotTemp"            , ID_AL_LOW_BOT_TEMP },
    {   "MainWaterIngr"         , ID_AL_MAIN_WATERINGR },
    {   "PreWaterIngr"          , ID_AL_PRE_WATERINGR },
    {   "LowTankPress"          , ID_AL_LOW_T_PRESS },
    {   "HighInertGasPress"     , ID_AL_HIGH_INERT_GAS_PRESS },
    {   "LowInertGasPress"      , ID_AL_LOW_INERT_GAS_PRESS },
    {   "HighTankPress"         , ID_AL_HIGH_T_PRESS },
    {   "LowPressVac"           , ID_AL_LOW_PRESS_VAC },
    {   "HighPressVac"          , ID_AL_HIGH_PRESS_VAC },
    {   "LowVapourReturn"       , ID_AL_LOW_VAPOUR_RETURN },
    {   "HighVapourReturn"      , ID_AL_HIGH_VAPOUR_RETURN },
    {   "LowLoadrate"           , ID_AL_LOW_LOADRATE },
    {   "HighLoadrate"          , ID_AL_HIGH_LOADRATE },
    {   "LevelChange"           , ID_AL_LEVEL_CHANGE },
    {   "DensDiff"              , ID_AL_DENS_DIFF },
    {   "LowLinePress"          , ID_AL_LOW_LINE_PRESS },
    {   "HighLinePress"         , ID_AL_HIGH_LINE_PRESS },
    {   "HighHighLinePress"     , ID_AL_HIGHHIGH_LINE_PRESS },

    {   "ExtraLowTankPress"     , ID_AL_X_LOW_T_PRESS1 },
    {   "ExtraLowTankPress2"    , ID_AL_X_LOW_T_PRESS2 },
    {   "ExtraHighTankPress"    , ID_AL_X_HIGH_T_PRESS1 },
    {   "ExtraHighTankPress2"   , ID_AL_X_HIGH_T_PRESS2 },
    {   "LevelSwitch"           , ID_AL_LEVEL_SWITCH },
    {   "LevelSwitchTest"       , ID_AL_LSWITCH_TEST },
    {   "WaterDetect"           , ID_AL_WATER_DETECT },
    {   "Fuse"                  , ID_AL_FUSE },
    {   "AC_Voltage"            , ID_AL_AC_VOLTAGE },
    {   "TCM_ElapsedTime"       , ID_AL_TWM_ELAPSED_TIME },
    {   "TCM_LowSpeed"          , ID_AL_TWM_LOW_SPEED },

    {   "OP_ModeAdjustable"     , C_OP_MODE_ADJUSTABLE },
    {   "OP_ModePressVac"       , C_OP_MODE_PRES_VAC },
    {   "OP_ModeVapRet"         , C_OP_MODE_VAP_RET  },
    {   "OP_ModePO"             , C_OP_MODE_PO       },
    {   "OP_ModeIGP"            , C_OP_MODE_IGP       },


// HW Alarms  Range 3200 -> 3399
    {   "SnsOpenLoop"           , ID_AL_SNS_OPEN_LOOP },
    {   "SnsClosedLoop"         , ID_AL_SNS_SHORT_CIRCUIT },
    {   "AtmSnsOutOfRange"      , ID_AL_ATM_OUT_OF_RANGE },
    {   "HartSnsComError"       , ID_AL_SNS_HART_COM_ERROR },
    {   "HartSnsOpenLoop"       , ID_AL_SNS_HART_OPEN_LOOP },
    {   "HartSnsShortCircuit"   , ID_AL_SNS_HART_SHORT_CIRCUIT },
    {   "AirPurgeSnsFailure"    , ID_AL_SNS_AIR_PURGE_FAILURE },

    {   "SnsFailure"            , ID_AL_SNS_ERROR },
    {   "SnsConCalError"        , ID_AL_SNS_CONCAL_ERROR },
    {   "SnsConvError"          , ID_AL_SNS_CONV_ERROR },
    {   "IOComFailure"          , ID_AL_IO_COM_ERROR },
    {   "ADComFailure"          , ID_AL_SC_COM_ERROR },
    {   "ModbusFailure"         , ID_AL_MODBUS_COM_ERROR },

    {   "CoilActive"            , ID_AL_MODBUS_INPUT_STATUS2},
    {   "InputStatus"           , ID_AL_MODBUS_INPUT_STATUS },
    {   "LowVoltage"            , ID_AL_LOW_VOLTAGE         },
    {   "LowVoltage1"           , ID_AL_LOW_VOLTAGE_1       },
    {   "LowVoltage2"           , ID_AL_LOW_VOLTAGE_2       },
    {   "HighVoltage"           , ID_AL_HI_VOLTAGE          },
    {   "HighVoltage1"          , ID_AL_HI_VOLTAGE_1        },
    {   "HighVoltage2"          , ID_AL_HI_VOLTAGE_2        },

// Alarm Limit type   Range 3500 -> 3599
    {   "VolPercentLimit"       , AL_LIM_VOLPERCENT         },
    {   "LevelLimit"            , AL_LIM_LEVEL              },
    {   "VolumeLimit"           , AL_LIM_VOLUME             },
    {   "WeightLimit"           , AL_LIM_WEIGHT             },
    {   "UllageLimit"           , AL_LIM_ULLAGE             },
// Alarm Limits   Range 3600 -> 3699                        
    {   "OverfillLimit"         , AL_LIM_OVERFILL           },
    {   "HighLevelLimit"        , AL_LIM_HIGHLEVEL          },
    {   "LowLevelLimit"         , AL_LIM_LOWLEVEL           },
    {   "LowLowLevelLimit"      , AL_LIM_LOWLOW_LEVEL       },
    {   "VoidSpaceLevelLimit"   , AL_LIM_VOIDSPACE          },
    {   "LevelDiffLimit"        , AL_LIM_LEVELDIFF          },

    {   "HighTempLimit"         , AL_LIM_HIGHTEMP           },
    {   "LowTempLimit"          , AL_LIM_LOWTEMP            },
    {   "HighTankPressLimit"    , AL_LIM_HIGHTANK_PRESS     },
    {   "LowTankPressLimit"     , AL_LIM_LOWTANK_PRESS      },
    {   "HighVapourRetLimit"    , AL_LIM_HIGHVAPOUR_RET     },
    {   "LowVapourRetLimit"     , AL_LIM_LOWVAPOUR_RET      },
    {   "HighPressVacLimit"     , AL_LIM_HIGH_PV_PRESS      },
    {   "HighPresVacLimit"      , AL_LIM_HIGH_PV_PRESS2     },
    {   "LowPressVacLimit"      , AL_LIM_LOW_PV_PRESS       },
    {   "LowPresVacLimit"       , AL_LIM_LOW_PV_PRESS3      },
    {   "LowVPresVacLimit"      , AL_LIM_LOW_PV_PRESS2      },

    {   "HighIGPressLimit"      , AL_LIM_HIGH_IG_PRESS      },
    {   "LowIGPressLimit"       , AL_LIM_LOW_IG_PRESS       },


    {   "ExtraHighTankPressLimit1"      , AL_LIM_X_HI_TNK_PRESS1 },
    {   "ExtraLowTankPressLimit1"       , AL_LIM_X_LO_TNK_PRESS1 },
    {   "ExtraHighTankPressLimit2"      , AL_LIM_X_HI_TNK_PRESS2 },
    {   "ExtraLowTankPressLimit2"       , AL_LIM_X_LO_TNK_PRESS2 },
    {   "HasExtraHighTankPressLimit1"   , AL_LIM_HAS_HI_TNK_PR1 },
    {   "HasExtraHighTankPressLimit2"   , AL_LIM_HAS_HI_TNK_PR2 },
    {   "HasHighTankPressLimit1"        , AL_LIM_HAS_HI_TNK_PR1 },
    {   "HasExtraLowTankPressLimit1"    , AL_LIM_HAS_LO_TNK_PR1 },
    {   "HasExtraLowTankPressLimit2"    , AL_LIM_HAS_LO_TNK_PR2 },
    {   "HasLowTankPressLimit1"         , AL_LIM_HAS_LO_TNK_PR1 },
    {   "HasLowLowLevelLimit"           , AL_LIM_HAS_LOLO_LEVEL },
    
    {   "HighTankPressLimit"            , AL_LIM_HIGHTANK_PRESS },
    {   "LowTankPressLimit"             , AL_LIM_LOWTANK_PRESS },
    {   "HighHighLinePressLimit"        , AL_LIM_HIGHHIGHLINE_PRESS },
    {   "HighLinePressLimit"            , AL_LIM_HIGHLINE_PRESS },
    {   "LowLinePressLimit"             , AL_LIM_LOWLINE_PRESS },

    {   "OverfillLocked"                , AL_LOCK_OVERFILL },
    {   "HighLevelLocked"               , AL_LOCK_HIGHLEVEL },
    {   "LowLevelLocked"                , AL_LOCK_LOWLEVEL },
    {   "LowLowLevelLocked"             , AL_LOCK_LOWLOWLEVEL },
    {   "HighTempLocked"                , AL_LOCK_HIGHTEMP },
    {   "LowTempLocked"                 , AL_LOCK_LOWTEMP },
    {   "HighTankPressLocked"           , AL_LOCK_HIGHTANK_PRESS },
    {   "LowTankPressLocked"            , AL_LOCK_LOWTANK_PRESS },
    {   "HighIGPLocked"                 , AL_LOCK_HIGH_IGP },
    {   "LowIGPLocked"                  , AL_LOCK_LOW_IGP },
    {   "HighLinePressLocked"           , AL_LOCK_HIGHLINE_PRESS },
    {   "LowLinePressLocked"            , AL_LOCK_LOWLINE_PRESS },

    {   "OverfillUnlocked"              , AL_UNLOCK_OVERFILL },
    {   "HighLevelUnlocked"             , AL_UNLOCK_HIGHLEVEL },
    {   "LowLevelUnlocked"              , AL_UNLOCK_LOWLEVEL },
    {   "LowLowLevelUnlocked"           , AL_UNLOCK_LOWLOWLEVEL },
    {   "HighTempUnlocked"              , AL_UNLOCK_HIGHTEMP },
    {   "LowTempUnlocked"               , AL_UNLOCK_LOWTEMP },
    {   "HighTankPressUnlocked"         , AL_UNLOCK_HIGHTANK_PRESS },
    {   "LowTankPressUnlocked"          , AL_UNLOCK_LOWTANK_PRESS },
    {   "HighIGPUnlocked"               , AL_UNLOCK_HIGH_IGP },
    {   "LowIGPUnlocked"                , AL_UNLOCK_LOW_IGP },
    {   "HighLinePressUnlocked"         , AL_UNLOCK_HIGHLINE_PRESS },
    {   "LowLinePressUnlocked"          , AL_UNLOCK_LOWLINE_PRESS },
    // ANPRo3 : Range 6000 -> 6100
    {   "ANPRO3ValDefEnd"               , C_ANPRO3_VALDEF_END },
    {   "ANPRO3VelDefEnd"               , C_ANPRO3_VALDEF_END2 }, // Spelling mistake, keep for backward compatibility
    {   "ANPRO3SyncStr"                 , C_ANPRO3_SYNC_STR },
    {   "ANPRO3CheckSum"                , C_ANPRO3_CHECKSUM },
    {   "ANPRO3RequestMode"             , C_ANPRO3_REQUEST },
    {   "ANPRO3Separator"               , C_ANPRO3_SEPARATOR },
    {   "ANPRO3IncHWStatus"             , C_ANPRO3_INC_HW_STATUS },
    {   "ANPRO3IncAlarm"                , C_ANPRO3_INC_ALARM },
    //   {   "ANPRO3Description"            , C_ANPRO3_DESCRIPTION},
    {   "ANPRO3Value_Error_Action"      , C_ANPRO3_VAL_ERR_ACT },
    {   "ANPRO3ClearRxBufAfterRx"       , C_ANPRO3_CLEAR_RX_BUF },
    {   "ANPRO3SOAllExtraSpace"         , C_ANPRO3_SOALL_EXTRA_SPC },
    {   "ANPRO3Delay"                   , C_ANPRO3_DELAY },
    {   "ANPRO3SendAlarmsOnly"          , C_ANPRO3_SEND_ALARMS_ONLY },
    {   "ANPRO3NEMA"                    , C_ANPRO3_NEMA },
    // TDU windows: Range 7000 -> 7999
    {   "TDUWinEnd"                     , C_TDU_WIN_END },
    {   "CurrentWin"                    , C_TDU_CURRENT_WIN },
    {   "CurrentSysWin"                 , C_TDU_CURRENT_SYSWIN },
    {   "TDUSystemWin"                  , C_TDU_SYSTEM_WIN },
    {   "TDUCargoWin"                   , C_TDU_CARGO_WIN },
    {   "TDUBallastWin"                 , C_TDU_BALLAST_WIN },
    {   "TDUServiceWin"                 , C_TDU_SERVICE_WIN },
    {   "TDUTankPressWin"               , C_TDU_TANKPRESS_WIN },
    {   "TDUCargoLineWin"               , C_TDU_LINEPRESS_WIN },
    {   "TDUTampWin"                    , C_TDU_TEMP_WIN },
    {   "TDUTempWin"                    , C_TDU_TEMP_WIN2 },
    {   "TDULevelSwitchWin"             , C_TDU_LEVELSWITCH_WIN },
    {   "TDUWaterIngressWin"            , C_TDU_WATERINGR_WIN },
    {   "TDUVoidSpaceWin"               , C_TDU_VOIDSPACE_WIN },

    {   "TDUValueTab"                   , C_TDU_VALUE_TAB },
    {   "BackColor"                     , C_TDU_BACK_COLOR },
    {   "TextColor"                     , C_TDU_TEXT_COLOR },

    {	"TDUTankPlanPos", C_TDU_TANK_PLAN_POS },
    {	"EndTDUTankPlanPos", C_TDU_TANK_PLAN_POS_END },

// Uart ( TCU ), Range: 8000 -> 8199
    {   "TSNUart"                       , C_UART },
    {   "TSNUartEnd"                    , C_UART_END },
    {   "PortNumber"                    , C_UART_PORTNUMBER },
    {   "BaudRate"                      , C_UART_BAUDRATE },
    {   "Parity"                        , C_UART_PARITY },
    {   "StopBits"                      , C_UART_STOPBITS },
    {   "Wordlength"                    , C_UART_WORDLENGTH },
    {   "MaxTimeBetweenChar"            , C_UART_MAX_TIME_BETWEEN_CHAR },

//  {   "UartType"                  , C_UART_UARTTYPE           },

    {   "HWProtocol"                , C_UART_HWPRO },
    {   "HWProtocol232"             , C_UART_HWPRO_232 },
    {   "HWProtocol485"             , C_UART_HWPRO_485 },
    {   "SWProtocol"                , C_UART_SWPRO },
    {   "SWProtocolANPRO1"          , C_UART_SWPRO_ANPRO1 },
    {   "SWProtocolANPRO3"          , C_UART_SWPRO_ANPRO3 },
    {   "SWProtocolANPRO10"         , C_UART_SWPRO_ANPRO10 },
    {   "SWProtocolModBus"          , C_UART_SWPRO_MODBUS },
    {   "SWProtocolPrinter"         , C_UART_SWPRO_PRINTER },
    {   "SWProtocolSaab"            , C_UART_SWPRO_SAAB },

    {   "Device"                    , C_UART_DEVICE },
    {   "DeviceTDU"                 , C_UART_DEVICE_TDU },
    {   "DevicePC"                  , C_UART_DEVICE_PC },
    {   "DeviceTCU"                 , C_UART_DEVICE_TCU },
    {   "DeviceANPRO3"              , C_UART_DEVICE_ANPRO3 },
    {   "DeviceANPRO10"             , C_UART_DEVICE_ANPRO10 },
    {   "DeviceZB"                  , C_UART_DEVICE_ZB },
    {   "DeviceZBRed"               , C_UART_DEVICE_ZB_RED },
    {   "DeviceModBusMaster"        , C_UART_DEVICE_MODBUS_MASTER },
    {   "DeviceModBusMasterInverted", C_UART_DEVICE_MODBUS_MASTER_INV },
    {   "DeviceModBusMasterTCP"     , C_UART_DEVICE_MODBUS_MASTER_TCP },
    {   "DeviceModBusSlave"         , C_UART_DEVICE_MODBUS_SLAVE_INV },
    {   "DeviceModBusSlaveTCP"      , C_UART_DEVICE_MODBUS_SLAVE_TCP },
    {   "DeviceModBusSlaveInverted" , C_UART_DEVICE_MODBUS_SLAVE },

    {   "DeviceModiconMaster"       , C_UART_DEVICE_MODICON_MASTER       },
    {   "DeviceModiconSlave"        , C_UART_DEVICE_MODICON_SLAVE        },
    {   "DeviceModiconMasterTCP"    , C_UART_DEVICE_MODICON_MASTER_TCP   },
    {   "DeviceModiconSlaveTCP"     , C_UART_DEVICE_MODICON_SLAVE_TCP    },







    {   "DeviceTPC", C_UART_DEVICE_TPC },
    {   "DevicePrinter", C_UART_DEVICE_PRINTER },
    {   "DeviceSaab", C_UART_DEVICE_SAAB },

    {   "ModbusCmdInputStatus", C_MODBUS_CMD_INP_STAT },
    {   "ModbusCmdInputRegister", C_MODBUS_CMD_INP_REG },

    {   "TDU      (RS232)", C_TCU_COM_232_TDU },
    {   "PC       (RS232)", C_TCU_COM_232_PC },
    {   "TCU      (RS232)", C_TCU_COM_232_TCU },
    {   "ANPro 3  (RS232)", C_TCU_COM_232_PROT3 },
    {   "ANPro 10 (RS232)", C_TCU_COM_232_PROT10 },
    {   "Printer  (RS232)", C_TCU_COM_232_PRINTER },
    {   "Modbus   (RS232)", C_TCU_COM_232_MODBUS_MASTER },
    {   "Modbus inv(RS232)", C_TCU_COM_232_MODBUS_MASTER_INV },
    {   "Modbus tcp(RS232)", C_TCU_COM_232_MODBUS_MASTER_TCP },
    {   "Modbus sl(RS232)", C_TCU_COM_232_MODBUS_SLAVE },
    {   "Modbus sl inv(RS232)", C_TCU_COM_232_MODBUS_SLAVE_INV },
    {   "Modbus sl tcp(RS232)", C_TCU_COM_232_MODBUS_SLAVE_TCP },
    {   "Saab     (RS232)", C_TCU_COM_232_SAAB },
    {   "TCU      (RS485)", C_TCU_COM_485_TCU },
    {   "TDU      (RS485)", C_TCU_COM_485_TDU },
    {   "ANPro 3  (RS485)", C_TCU_COM_485_PROT3 },
    {   "ANPro 10 (RS485)", C_TCU_COM_485_PROT10 },
    {   "IO ZB    (RS485)", C_TCU_COM_485_ZB },
    {   "IO ZB redundancy", C_TCU_COM_485_ZB_RED },
    {   "Modbus   (RS485)", C_TCU_COM_485_MODBUS_MASTER },
    {   "Modbus inv(RS485)", C_TCU_COM_485_MODBUS_MASTER_INV },
    {   "Modbus tcp(RS485)", C_TCU_COM_485_MODBUS_MASTER_TCP },
    {   "Modbus sl(RS485)", C_TCU_COM_485_MODBUS_SLAVE },
    {   "Modbus sl inv(RS485)", C_TCU_COM_485_MODBUS_SLAVE_INV },
    {   "Modbus sl tcp(RS485)", C_TCU_COM_485_MODBUS_SLAVE_TCP },
    {   "TPCx     (RS485)", C_TCU_COM_485_TPC },
    {   "SAAB     (RS485)", C_TCU_COM_485_SAAB },

// Tanksystem unit, Range: 8200 -> 8299
    {   "UnitID"                    , C_TU_ID               },
    {   "UnitAddress"               , C_TU_ADDRESS          },
    {   "TUnitID"                   , C_TU_ID2              },
    {   "TUnitAddress"              , C_TU_ADDRESS2         },

    {   "PowerVoltage"              , C_TU_POWER_VOLTAGE    },
    {   "PowerSource"               , C_TU_POWER_SOURCE     },
    {   "Power1"                    , C_TU_POWER_1          },
    {   "Power2"                    , C_TU_POWER_2          },
    {   "PowerBoth"                 , C_TU_POWER_BOTH       },
// SystemData, Range: 8400 -> 8499
    {   "ScreenOffTime", C_SD_SCREEN_OFF_TIME },
    {   "AlarmOffDelay", C_SD_ALARM_OFF_DELAY },
    {   "UserPinCode", C_SD_USER_PIN_CODE },
    {   "UnitSystem", C_SD_UNITSYSTEM },
    {   "Language", C_SD_LANGUAGE },
    {   "TimeFromGMT", C_SD_TIME_GMT },
    {   "DayLighSavingTime", C_SD_DAYLIGH_SAVING },

    {   "ManualSource", C_SD_MAN_SOURCE },
    {   "IncSource", C_SD_INC_SOURCE },
    {   "DraftSource", C_SD_DRAFT_SOURCE },

    {   "LCOnlineSource", C_SD_LC_SOURCE_ONL },
    {   "LCManualSource", C_SD_LC_SOURCE_MAN },
    {   "LCLoadCalcSource", C_SD_LC_SOURCE    },

    {   "TrimSource", C_SD_TRIM_SOURCE  },
    {   "ListSource", C_SD_LIST_SOURCE  },
    {   "TouchScreenCal", C_SD_SCREEN_CAL   },

    {   "LogTime", C_SD_LOG_TIME         },
    {   "LogToFile", C_SD_LOG_TO_FILE      },
    {   "LogAlarms", C_SD_LOG_ALARMS       },
    {   "LogBallastExchange", C_SD_LOG_BALLAST_EXCH },
    {   "LogCargo", C_SD_LOG_CARGO        },
    {   "LogService", C_SD_LOG_SERVICE      },
    {   "LogTemperature", C_SD_LOG_TEMPERATURE  },
    {   "LogTankPressure", C_SD_LOG_TANK_PRESSURE },
    {   "PrinterOnThisTXU", C_SD_PRINTER_ON_TDU   },
    {   "ReceiveVolumeWeightFrmLC", C_SD_RECEIVE_VOL_WGT  },
    {   "SimulateIO", C_SD_SIMULATE_IO      },
    {   "SimulateStaticValues", C_SD_SIMULATE_STATIC  },

// Washtrack data
    {  "Is Active"             , SVT_TWM_SPEED                  },
    {  "Pressure"              , SVT_TWM_PRESSURE               },
    {  "HeaterTemp In"         , SVT_TWM_HEATER_INPUT_TEMP      },
    {  "HeaterTemp Out"        , SVT_TWM_HEATER_OUTPUT_TEMP     },
    {  "ManualPressure"        , SVT_TWM_MAN_PRESSURE           },
    {  "ManualHeaterTemp In"   , SVT_TWM_MAN_HEATER_INPUT_TEMP  },
    {  "ManualHeaterTemp Out"  , SVT_TWM_MAN_HEATER_OUTPUT_TEMP },
    {  "Efficiency"            , SVT_TWM_HEATER_EFFICIENCY      },
    {  "Fuel_Ton_per_kWh"      , SVT_TWM_FUEL_TON_PER_KWH       },





// Applications, Range: 9000 -> 9099
    {   "Not_set", TSN_NONE_APP          },
	{   "Cargo", TSN_CARGO_APP         },
    {   "Ballast", TSN_BALLAST_APP       },
    {   "Service", TSN_SERVICE_APP       },
    {   "Tank_Pressure", TSN_TANKPRESS_APP     },
    {   "Cargo_Line", TSN_LINEPRESS_APP     },
    {   "Temperature", TSN_TEMP_APP          },
    //{   "Level_Switch_Alarm"            , TSN_LEVELSWITCH_APP},
    {   "Water Detection", TSN_LEVELSWITCH_APP   },
    {   "Water_Ingress_Alarm", TSN_WATERINGR_APP     },
    {   "VoidSpace", TSN_VOIDSPACE_APP     },
    {   "TankFarm", TSN_TANKFARM_APP      },

    {   "XRef", C_XREF_START          },
    {   "XRef_End", C_XREF_END            },
    {   "ANPro3_Id", C_XREF_ANPRO3         },
    {   "SAAB_Id", C_XREF_SAAB           },
    {   "ExcludeState", C_XREF_EXCLUDE_STATE  },

    {   "Disable_WI_Override", C_WIS_OVERIDE_LOC     },

// For loading calculator
    {   "ShipData"                  , C_LC_SHIPDATA },
    {   "End"                       , C_LC_END },
    {   "Class_Unknown"             , C_LC_CLASS_UNKNOWN },
    {   "Class_DNV"                 , C_LC_CLASS_DNV },
    {   "Class_LR"                  , C_LC_CLASS_LLOYDS },
    {   "Class_GL"                  , C_LC_CLASS_GL },
    {   "Class_MRS"                 , C_LC_CLASS_MRS },
    {   "Class_BV"                  , C_LC_CLASS_BV },
    {   "Class_NK"                  , C_LC_CLASS_NK },
    {   "Class_RINA"                , C_LC_CLASS_RINA },
    {   "Class_ABS"                 , C_LC_CLASS_ABS },
    {   "Class_KR"                  , C_LC_CLASS_KR },
    {   "Class_USC"                 , C_LC_CLASS_USC },

    {   "CargoTank"                 , C_LC_TANK_CARGO },
    {   "BallastTank"               , C_LC_TANK_BALLAST },
    {   "HFOTank"                   , C_LC_TANK_HFO },
    {   "DieselOilTank"             , C_LC_TANK_DO },
    {   "LubricantsTank"            , C_LC_TANK_LUB },
    {   "FreshWaterTank"            , C_LC_TANK_FW },
    {   "MiscTank"                  , C_LC_TANK_MISC },
    {   "VoidSpaceTank"             , C_LC_TANK_VOIDSPACE },

    {   "Order"                     , C_LC_TABLE_ORDER },
    {   "CG_Table"                  , C_LC_TABLE_CG },
    {   "CG_Ullage_Table"           , C_LC_TABLE_CG_ULL },
    {   "Area"                      , C_LC_TABLE_AREA },
    {   "TFS_Table"                 , C_LC_TABLE_TFS },
    {   "TFS_Ullage_Table"          , C_LC_TABLE_TFS_ULL },
    {   "Graph_Frame_List"          , C_LC_FRAME_LIST },
    {   "Constant_Solid"            , C_LC_SOLID_CONSTANT },
    {   "Variable_Solid"            , C_LC_SOLID_VARIABLE },
    {   "BuoyancyTable"             , C_LC_TABLE_BUOYANCY },
    {   "GZTable"                   , C_LC_TABLE_GZ },
    {   "KY_Table"                  , C_LC_TABLE_KY },
    {   "Opening"                   , C_LC_OPENING },
    {   "SteelWeightDistribution"   , C_LC_WEIGHT_DISTRIBUTION },
    {   "SteelWeightDistributionRefMid", C_LC_WEIGHT_DISTR_REF_MID },
    {   "Max_VCG"               , C_LC_MAX_VCG },
    {   "Damage_max_KG"         , C_LC_DAMAGE_MAX_VCG },
    {   "FloodingAngle"         , C_LC_FLOODING_ANGLE },
    {   "BM_Hog_Harbour_Limit"  , C_LC_BMHOGHRBLIM },
    {   "BM_Hog_Sea_Limit"      , C_LC_BMHOGSEALIM },
    {   "BM_Sag_Harbour_Limit"  , C_LC_BMSAGHRBLIM },
    {   "BM_Sag_Sea_Limit"      , C_LC_BMSAGSEALIM },
    {   "SF_Hog_Harbour_Limit"  , C_LC_SFHOGHRBLIM },
    {   "SF_Hog_Sea_Limit"      , C_LC_SFHOGSEALIM },
    {   "SF_Sag_Harbour_Limit"  , C_LC_SFSAGHRBLIM },
    {   "SF_Sag_Sea_Limit"      , C_LC_SFSAGSEALIM },
    {   "Stability_Tables"      , C_LC_STABILITY_TABLES },
    {   "Steel_Weight"          , C_LC_STEEL_WEIGHT },
    {   "Reference_APP"         , C_LC_REF_APP },
    {   "No_Buoyancy_Correction", C_LC_NO_BUOYANCY_CORR },
    {   "GZ_Scale"              , C_LC_GZ_SCALE },
    {   "Stability_Only"        , C_LC_STABILITY_ONLY },
    {   "SimpleLoadCalcOnly"    , C_LC_SIMPLE_LC_ONLY },
    {   "Trim_by_stern_positive", C_LC_TRIM_BY_STERN_POS },
    {   "LoadCalcVersion"       , C_LC_LOAD_CALC_VERSION },
    {   "Data_Version"          , C_LC_DATA_VERSION },
    {   "Section"               , C_LC_SECTION },
    {   "Max_Section_Draft"     , C_LC_MAX_SECTION_DRAFT },
    {   "Frame"                 , C_LC_FRAME },
    {   "OverrideFrame"         , C_LC_OVERRIDE_FRAME },
    {   "Hydrostatic_Tables"    , C_LC_TABLE_HYDROSTATIC },
    {   "KY_Curves"             , C_LC_KY_CURVES },
    {   "DraftCF_KY_Curves"     , C_LC_KY_CURVES_CF },
    {   "Displ_KY_Curves"       , C_LC_DISP_KY_CURVES },
    {   "Length"                , C_LC_LENGTH },
  //{   "Distance"              , C_LC_DISTANCE},// Defined as C_AI_DISTANCE
    {   "Profile"               , C_LC_FRAME_PROFILE },
    {   "Copy_Profile"          , C_LC_COPY_FRAME_PROFILE },
    {   "Draft"                 , C_LC_DRAFT },
    {   "List"                  , C_LC_LIST },
    {   "List_Entries"          , C_LC_LIST_ENTRIES },
    {   "Heel"                  , C_LC_LIST },
    {   "KY_Entry"              , C_LC_KY_ENTRY },
 // {   "Trim"                  , C_LC_TRIM},// To avoid duplicate name
    {   "Trim_Entries"          , C_LC_TRIM_ENTRIES },

    {   "VCG_Cases"             , C_LC_VCG_CASES },
    {   "Displ"                 , C_LC_DISPLACEMENT },
    {   "VCG"                   , C_LC_VCG },
    {   "LCG"                   , C_LC_LCG },
    {   "TCG"                   , C_LC_TCG },
    {   "Midship_To_Aft_PP"     , C_LC_MS_TO_APP },
    {   "Aft_PP_to_Mark"        , C_LC_APP_TO_MARK },
    {   "Weight"                , C_LC_WEIGHT },
    {   "Max_Draft"             , C_LC_MAX_DRAFT },
    {   "GZ_VCG_Constant"       , C_LC_GZ_VCG_CONSTANT },
    {   "Keel_Thickness"        , C_LC_KEEL_THICKNESS },
    {   "HullDraftCorrection"   , C_LC_HULL_DRAFT_CORRECTION },

    {   "Bm_Calc_Fwd_To_Aft"    , C_LC_BM_CALC_F_TO_A },
    {   "LCF"                   , C_LC_LCF },
    {   "TCF"                   , C_LC_TCF },
    {   "LCB"                   , C_LC_LCB },
    {   "KMT"                   , C_LC_KMT },
    {   "MCT"                   , C_LC_MCT },
    {   "TPM"                   , C_LC_TPM },
    {   "FreshWater"            , C_LC_FRESH_WATER },
    {   "SeaWater"              , C_LC_SEA_WATER },
    {   "LocationInfo"          , C_LC_LOCATION },
    {   "LOCEnd"                , C_LC_LOC_END },
    {   "MaxWeight"             , C_LC_MAX_WEIGHT },
    {   "MaxDensity"            , C_LC_MAX_DENSITY },
    {   "Volume"                , C_LC_VOLUME },
    {   "Ullage"                , C_LC_ULLAGE },
    {   "UllageFC"              , C_LC_ULLAGE_FC },
    {   "LevelFC"               , C_LC_LEVELFC },
    {   "Sounding"              , C_LC_SOUNDING },
    {   "LevelAtRef"            , C_LC_LEVEL_AT_REF },
    {   "VolumePercent"         , C_LC_VOLUME_PERCENT },
    //{   "Temperature"           , C_LC_TEMPERATURE },

    {   "FirstStrengthLimitCheck"   , C_LC_FIRST_STR_LIM_CHECK },
    {   "LastStrengthLimitCheck"    , C_LC_LAST_STR_LIM_CHECK },

    {   "Density"               , C_LC_DENSITY },
    {   "TrimListSource"        , C_LC_TRIM_LIST_SOURCE },
    {   "LC_ManualTrim"         , C_LC_MANUAL_TRIM },
    {   "LC_ManualList"         , C_LC_MANUAL_LIST },
    {   "Adjustable"            , C_PRESS_LIM_ADJUST },
    {   "PressVac"              , C_PRESS_LIM_PRESS_VAC },
    {   "VapRet"                , C_PRESS_LIM_VAP_RET },
    {   "POMode"                , C_PRESS_LIM_PO_MODE },
    {   "InertMode"             , C_PRESS_LIM_IGP_MODE},
 //{   "SnsNoiseLimBottom"      , C_SNS_NOISE_LIM_BOT},
 //{   "SnsNoiseLimUpper"       , C_SNS_NOISE_LIM_UPP},
//Value types for communication to i.e TPC Range: 5000 -> 5999

    {  "VT_NAME"                , SVT_NAME                      + C_SVT_OFFSET },
    {  "VT_NAME"                , SVT_PRO_NAME                  + C_SVT_OFFSET },
    {  "VT_VALUE_NAME"          , SVT_VALUE_NAME                + C_SVT_OFFSET },
    {  "VT_VALUE_SHORT_NAME"    , SVT_VALUE_SHORT_NAME          + C_SVT_OFFSET },
    {  "VT_LEVEL@SENSOR"        , SVT_LEVEL_SENSOR              + C_SVT_OFFSET },
    {  "VT_LEVEL"               , SVT_LEVEL_SENSOR2             + C_SVT_OFFSET },
    {  "VT_LEVEL_FC"            , SVT_LEVEL_FC                  + C_SVT_OFFSET },
    {  "VT_LEVEL_REF"           , SVT_LEVEL_REF                 + C_SVT_OFFSET },
    {  "VT_LEVPERCENT"          , SVT_LEVEL_PERCENT             + C_SVT_OFFSET },
    {  "VT_SOUNDING"            , SVT_SOUNDING                  + C_SVT_OFFSET },

    {  "VT_ULLAGE"              , SVT_ULLAGE                    + C_SVT_OFFSET },
    {  "VT_ULLAGE_UTI"          , SVT_ULLAGE_UTI                + C_SVT_OFFSET },
    {  "VT_ULLAGE_FC"           , SVT_ULLAGE_FC                 + C_SVT_OFFSET },
    {  "VT_ULLAGE@RADAR"        , SVT_ULLAGE_RADAR              + C_SVT_OFFSET },

    {  "VT_VOLPERCENT"          , SVT_VOLPERCENT                + C_SVT_OFFSET },
    {  "VT_VOLUME"              , SVT_VOLUME                    + C_SVT_OFFSET },
    {  "VT_VOL_AT_REFTMP"       , SVT_VOL_AT_REFTMP             + C_SVT_OFFSET },
    {  "VT_WEIGHT"              , SVT_WEIGHT                    + C_SVT_OFFSET },
    {  "VT_LPG_WEIGHT"          , SVT_GAS_WEIGHT                + C_SVT_OFFSET },
    {  "VT_GAS_WEIGHT"          , SVT_VAP_WEIGHT                + C_SVT_OFFSET },
    {  "VT_CARGOTYPENAME"       , SVT_CARGO_TYPE_NAME           + C_SVT_OFFSET },
    {  "VT_VISCOSITY"           , SVT_VISCOSITY                 + C_SVT_OFFSET },
    {  "VT_CARGOCOLOR"          , SVT_CARGO_COLOR               + C_SVT_OFFSET },

    {  "VT_BP"                  , SVT_BP                        + C_SVT_OFFSET },
    {  "VT_MP"                  , SVT_MP                        + C_SVT_OFFSET },
    {  "VT_UP"                  , SVT_UP                        + C_SVT_OFFSET },
    {  "VT_TP"                  , SVT_TP                        + C_SVT_OFFSET },
    {  "VT_TEMP"                , SVT_TEMP                      + C_SVT_OFFSET },
    {  "VT_BT"                  , SVT_T1                        + C_SVT_OFFSET },
    {  "VT_MT"                  , SVT_T2                        + C_SVT_OFFSET },
    {  "VT_UT"                  , SVT_T3                        + C_SVT_OFFSET },
    // To be fixed included in future release EHSMark           
    {  "VT_T1"                  , SVT_TMP1                      + C_SVT_OFFSET },
    {  "VT_T2"                  , SVT_TMP2                      + C_SVT_OFFSET },
    {  "VT_T3"                  , SVT_TMP3                      + C_SVT_OFFSET },
    {  "VT_T4"                  , SVT_TMP4                      + C_SVT_OFFSET },
    {  "VT_T5"                  , SVT_TMP5                      + C_SVT_OFFSET },
   // {  "VT_TT"                  , SVT_TT                      + C_SVT_OFFSET },
    {  "VT_DENSITY"             , SVT_DENSITY                   + C_SVT_OFFSET },
    {  "VT_MEAS_DNS_RAW"        , SVT_MEAS_DNS_RAW              + C_SVT_OFFSET },
    {  "VT_REF_DNS1"            , SVT_REF_DNS1                  + C_SVT_OFFSET },
    {  "VT_REF_DNS2"            , SVT_REF_DNS2                  + C_SVT_OFFSET },
    {  "VT_REF_TMP1"            , SVT_REF_TMP1                  + C_SVT_OFFSET },
    {  "VT_REF_TMP2"            , SVT_REF_TMP2                  + C_SVT_OFFSET },
    {  "VT_PRESSURE"            , SVT_PRESSURE                  + C_SVT_OFFSET },
    {  "VT_Level_Pressure"      , SVT_LEVEL_PRESSURE            + C_SVT_OFFSET },

    {  "VT_LOADRATE"            , SVT_LOADRATE                  + C_SVT_OFFSET },
    {  "VT_DRAFT"               , SVT_DRAFT                     + C_SVT_OFFSET },
    {  "VT_DF"                  , SVT_DF                        + C_SVT_OFFSET },
    {  "VT_DA"                  , SVT_DA                        + C_SVT_OFFSET },
    {  "VT_DF@Mark"             , SVT_DF_MARK                   + C_SVT_OFFSET },
    {  "VT_DA@Mark"             , SVT_DA_MARK                   + C_SVT_OFFSET },
    {  "VT_DF@PP"               , SVT_DF_PP                     + C_SVT_OFFSET },
    {  "VT_DA@PP"               , SVT_DA_PP                     + C_SVT_OFFSET },
    {  "VT_DP"                  , SVT_DP                        + C_SVT_OFFSET },
    {  "VT_DS"                  , SVT_DS                        + C_SVT_OFFSET },
    {  "VT_DFP"                 , SVT_DFP                       + C_SVT_OFFSET },
    {  "VT_DFS"                 , SVT_DFS                       + C_SVT_OFFSET },
    {  "VT_DAP"                 , SVT_DAP                       + C_SVT_OFFSET },
    {  "VT_DAS"                 , SVT_DAS                       + C_SVT_OFFSET },
    {  "VT_ATM_PRESSURE"        , SVT_ATM_PRESSURE              + C_SVT_OFFSET },
    {  "VT_TRIM_ANGLE"          , SVT_TRIM_ANGLE                + C_SVT_OFFSET },
    {  "VT_TRIM_DEG"            , SVT_TRIM_DEG                  + C_SVT_OFFSET },
    {  "VT_TRIM_M"              , SVT_TRIM_M                    + C_SVT_OFFSET },
    {  "VT_LIST_ANGLE"          , SVT_LIST_ANGLE                + C_SVT_OFFSET },
    {  "VT_LIST_DEG"            , SVT_LIST_DEG                  + C_SVT_OFFSET },
    {  "VT_LIST_M"              , SVT_LIST_M                    + C_SVT_OFFSET },
    {  "VT_LIST_ROLL_FILTER"    , SVT_LIST_ROLL_FILTER          + C_SVT_OFFSET },
    {  "VT_LIST_MAX_P"          , SVT_LIST_MAX_P                + C_SVT_OFFSET },
    {  "VT_LIST_MAX_S"          , SVT_LIST_MAX_S                + C_SVT_OFFSET },
    {  "VT_ROLLING_FREQUENCY"   , SVT_ROLLING_FREQUENCY         + C_SVT_OFFSET },
    {  "VT_ROLLING_PERIOD"      , SVT_ROLLING_PERIOD            + C_SVT_OFFSET },

    {  "VT_RESET_MAX_LIST"      , SVT_RESET_MAX_LIST            + C_SVT_OFFSET },

    {  "VT_SEAWATER_TEMP"       , SVT_SEAWATER_TEMP             + C_SVT_OFFSET },
    {  "VT_AMBIENT_TEMP"        , SVT_AMBIENT_TEMP              + C_SVT_OFFSET },

    {  "VT_VOLTAGE_IN2"         , SVT_AIN3                      + C_SVT_OFFSET },
    {  "VT_METRI_TAPE"          , SVT_METRI_TAPE_SNS            + C_SVT_OFFSET },
    {  "VT_HSH_LNG_FLOAT"       , SVT_HSH_FLOAT_SNS             + C_SVT_OFFSET },
    {  "VT_HART_RADAR"          , SVT_HART_RADAR                + C_SVT_OFFSET },
    {  "VT_HART_MA"             , SVT_HART_MA 		            + C_SVT_OFFSET },
    {  "VT_HART_STATUS"         , SVT_HART_STATUS	            + C_SVT_OFFSET },
    {  "VT_HART_OPEN_LOOP"      , SVT_HART_OPEN_LOOP	        + C_SVT_OFFSET },
    {  "VT_HART_SHORT_CIRCUIT"  , SVT_HART_SHORT_CIRCUIT        + C_SVT_OFFSET },
    {  "VT_Air_Purge_Level"     , SVT_AP_LEVEL2                 + C_SVT_OFFSET },
    {  "VT_AirPurge_Level"      , SVT_AP_LEVEL                  + C_SVT_OFFSET },
    {  "VT_AirPurge_LPress_mB"  , SVT_AP_LEVEL_PRESSURE_MB      + C_SVT_OFFSET },
    {  "VT_AirPurge_LPress_mH2O", SVT_AP_LEVEL_PRESSURE_MH2O    + C_SVT_OFFSET },
    {  "VT_AirPurge_TPress_mB"  , SVT_AP_TANK_PRESSURE_MB       + C_SVT_OFFSET },
    {  "VT_AirPurge_TPrStatus"  , SVT_AP_TPRESS_SNS_FAIL        + C_SVT_OFFSET },
    {  "VT_AirPurge_LPrStatus"  , SVT_AP_LPRESS_SNS_FAIL        + C_SVT_OFFSET },
    {  "VT_AirPurge_Status"     , SVT_AP_LPRESS_SNS_FAIL2       + C_SVT_OFFSET },
    {  "VT_AirPurge_SysFail"    , SVT_AP_SYS_FAIL               + C_SVT_OFFSET },
    {  "VT_AirPurge_PowFail"    , SVT_AP_POWER_FAIL             + C_SVT_OFFSET },
    {  "VT_AirPurge_CommonAlm"  , SVT_AP_COMMON_ALM             + C_SVT_OFFSET },
    {  "VT_AirPurge_LowPress"   , SVT_AP_LOW_PRESS              + C_SVT_OFFSET },

    {  "VT_ModBus_mA_Pressure"  , SVT_MB_MA_PRESSURE            + C_SVT_OFFSET },

    {  "VT_AlarmValue"          , SVT_AL_VALUE                  + C_SVT_OFFSET },
    {  "VT_AlarmState"          , SVT_AL_STATE                  + C_SVT_OFFSET },
                                                                

    {  "VT_TWM_Speed"           , SVT_TWM_SPEED                 + C_SVT_OFFSET },
    {  "VT_TWM_Pressure"        , SVT_TWM_PRESSURE              + C_SVT_OFFSET },
    {  "VT_TWM_HeaterTempIn"    , SVT_TWM_HEATER_INPUT_TEMP     + C_SVT_OFFSET },
    {  "VT_TWM_HeaterTempOut"   , SVT_TWM_HEATER_OUTPUT_TEMP    + C_SVT_OFFSET },
    {  "VT_TWM_ManPressure"     , SVT_TWM_MAN_PRESSURE          + C_SVT_OFFSET },
    {  "VT_TWM_ManHeaterTempIn" , SVT_TWM_MAN_HEATER_INPUT_TEMP + C_SVT_OFFSET },
    {  "VT_TWM_ManHeaterTempOut", SVT_TWM_MAN_HEATER_OUTPUT_TEMP+ C_SVT_OFFSET },
    {  "VT_TWM_Efficiency"      , SVT_TWM_HEATER_EFFICIENCY     + C_SVT_OFFSET },
    {  "VT_TWM_EnergyDensity"   , SVT_TWM_FUEL_TON_PER_KWH      + C_SVT_OFFSET },

    {  "VT_Level_Switch_Status" , SVT_LEVEL_SWITCH_STATUS   + C_SVT_OFFSET },
    {  "VT_LSW_Is_Active"       , SVT_LEVEL_SWITCH_STATUS2  + C_SVT_OFFSET },

    {  "VT_LC_Volume"           , SVT_LC_VOLUME             + C_SVT_OFFSET },
    {  "VT_LC_Weight"           , SVT_LC_WEIGHT             + C_SVT_OFFSET },
    {  "VT_LC_Density"          , SVT_LC_DENSITY            + C_SVT_OFFSET },

    {  "VT_Seconds"             , SVT_SECONDS               + C_SVT_OFFSET },

    {  "VT_HI_Temp_Limit"       , SVT_HI_TEMP_LIMIT         + C_SVT_OFFSET },
    {  "VT_LO_Temp_Limit"       , SVT_LO_TEMP_LIMIT         + C_SVT_OFFSET },
    {  "VT_HI_Temp_Enable"      , SVT_HI_TEMP_ENABLE        + C_SVT_OFFSET },
    {  "VT_LO_Temp_Enable"      , SVT_LO_TEMP_ENABLE        + C_SVT_OFFSET },
    {  "VT_HI_Temp_AlAck"       , SVT_HI_TEMP_AL_ACK        + C_SVT_OFFSET },
    {  "VT_LO_Temp_AlAck"       , SVT_LO_TEMP_AL_ACK        + C_SVT_OFFSET },
    {  "VT_HI_Temp_State"       , SVT_HI_TEMP_STATE         + C_SVT_OFFSET },
    {  "VT_LO_Temp_State"       , SVT_LO_TEMP_STATE         + C_SVT_OFFSET },
    {  "VT_HI_Bot_Temp_Limit"   , SVT_HI_BOT_TEMP_LIMIT     + C_SVT_OFFSET },
    {  "VT_LO_Bot_Temp_Limit"   , SVT_LO_BOT_TEMP_LIMIT     + C_SVT_OFFSET },
    {  "VT_HI_Bot_Temp_Enable"  , SVT_HI_BOT_TEMP_ENABLE    + C_SVT_OFFSET },
    {  "VT_LO_Bot_Temp_Enable"  , SVT_LO_BOT_TEMP_ENABLE    + C_SVT_OFFSET },
    {  "VT_HI_Bot_Temp_AlAck"   , SVT_HI_BOT_TEMP_AL_ACK    + C_SVT_OFFSET },
    {  "VT_LO_Bot_Temp_AlAck"   , SVT_LO_BOT_TEMP_AL_ACK    + C_SVT_OFFSET },
    {  "VT_HI_Bot_Temp_State"   , SVT_HI_BOT_TEMP_STATE     + C_SVT_OFFSET },
    {  "VT_LO_Bot_Temp_State"   , SVT_LO_BOT_TEMP_STATE     + C_SVT_OFFSET },


    {  "VT_Press_Limit_Mode"    , SVT_AL_LIMIT_TYPE_PRESS   + C_SVT_OFFSET },

    {  "VT_HIHI_Press_Limit"    , SVT_HI_PRESS_LIMIT        + C_SVT_OFFSET },
    {  "VT_HI_Press_Limit"      , SVT_HI_PRESS_LIMIT        + C_SVT_OFFSET },
    {  "VT_LO_Press_Limit"      , SVT_LO_PRESS_LIMIT        + C_SVT_OFFSET },
    {  "VT_HIHI_Press_Enable"   , SVT_HIHI_PRESS_ENABLE     + C_SVT_OFFSET },
    {  "VT_HI_Press_Enable"     , SVT_HI_PRESS_ENABLE       + C_SVT_OFFSET },
    {  "VT_LO_Press_Enable"     , SVT_LO_PRESS_ENABLE       + C_SVT_OFFSET },
    {  "VT_HI_Press_AlAck"      , SVT_HI_PRESS_AL_ACK       + C_SVT_OFFSET },
    {  "VT_LO_Press_AlAck"      , SVT_LO_PRESS_AL_ACK       + C_SVT_OFFSET },
    {  "VT_HIHI_Press_State"    , SVT_HIHI_PRESS_STATE      + C_SVT_OFFSET },
    {  "VT_HI_Press_State"      , SVT_HI_PRESS_STATE        + C_SVT_OFFSET },
    {  "VT_LO_Press_State"      , SVT_LO_PRESS_STATE        + C_SVT_OFFSET },

    {  "VT_HI_PressVac_Limit"   , SVT_HI_PRESS_VAC_LIMIT    + C_SVT_OFFSET },
    {  "VT_LO_PressVac_Limit"   , SVT_LO_PRESS_VAC_LIMIT    + C_SVT_OFFSET },
    {  "VT_HI_PressVac_Enable"  , SVT_HI_PRESS_VAC_ENABLE   + C_SVT_OFFSET },
    {  "VT_LO_PressVac_Enable"  , SVT_LO_PRESS_VAC_ENABLE   + C_SVT_OFFSET },
    {  "VT_HI_PressVac_AlAck"   , SVT_HI_PRESS_VAC_AL_ACK   + C_SVT_OFFSET },
    {  "VT_LO_PressVac_AlAck"   , SVT_LO_PRESS_VAC_AL_ACK   + C_SVT_OFFSET },
    {  "VT_HI_PressVac_State"   , SVT_HI_PRESS_VAC_STATE    + C_SVT_OFFSET },
    {  "VT_LO_PressVac_State"   , SVT_LO_PRESS_VAC_STATE    + C_SVT_OFFSET },

    {  "VT_HI_IGP_Limit"        , SVT_HI_IGP_LIMIT          + C_SVT_OFFSET },
    {  "VT_LO_IGP_Limit"        , SVT_LO_IGP_LIMIT          + C_SVT_OFFSET },
    {  "VT_HI_IGP_Enable"       , SVT_HI_IGP_ENABLE         + C_SVT_OFFSET },
    {  "VT_LO_IGP_Enable"       , SVT_LO_IGP_ENABLE         + C_SVT_OFFSET },
    {  "VT_HI_IGP_AlAck"        , SVT_HI_IGP_AL_ACK         + C_SVT_OFFSET },
    {  "VT_LO_IGP_AlAck"        , SVT_LO_IGP_AL_ACK         + C_SVT_OFFSET },
    {  "VT_HI_IGP_State"        , SVT_HI_IGP_STATE          + C_SVT_OFFSET },
    {  "VT_LO_IGP_State"        , SVT_LO_IGP_STATE          + C_SVT_OFFSET },

    {  "VT_HI_VAP_Ret_Limit"    , SVT_HI_VAP_RET_LIMIT      + C_SVT_OFFSET },
    {  "VT_LO_VAP_Ret_Limit"    , SVT_LO_VAP_RET_LIMIT      + C_SVT_OFFSET },
    {  "VT_HI_VAP_Ret_Enable"   , SVT_HI_VAP_RET_ENABLE     + C_SVT_OFFSET },
    {  "VT_LO_VAP_Ret_Enable"   , SVT_LO_VAP_RET_ENABLE     + C_SVT_OFFSET },
    {  "VT_HI_VAP_Ret_AlAck"    , SVT_HI_VAP_RET_AL_ACK     + C_SVT_OFFSET },
    {  "VT_LO_VAP_Ret_AlAck"    , SVT_LO_VAP_RET_AL_ACK     + C_SVT_OFFSET },
    {  "VT_HI_VAP_Ret_State"    , SVT_HI_VAP_RET_STATE      + C_SVT_OFFSET },
    {  "VT_LO_VAP_Ret_State"    , SVT_LO_VAP_RET_STATE      + C_SVT_OFFSET },

    {  "VT_XTRA1_HI_Pr_Enable"  , SVT_XTRA_HI_PRESS_ENABLE1 + C_SVT_OFFSET },
    {  "VT_XTRA1_LO_Pr_Enable"  , SVT_XTRA_LO_PRESS_ENABLE1 + C_SVT_OFFSET },
    {  "VT_XTRA1_HI_Pr_AlAck"   , SVT_XTRA_HI_PRESS_AL_ACK1 + C_SVT_OFFSET },
    {  "VT_XTRA1_LO_Pr_AlAck"   , SVT_XTRA_LO_PRESS_AL_ACK1 + C_SVT_OFFSET },
    {  "VT_XTRA1_HI_Pr_Limit"   , SVT_XTRA_HI_PRESS_LIMIT1  + C_SVT_OFFSET },
    {  "VT_XTRA1_LO_Pr_Limit"   , SVT_XTRA_LO_PRESS_LIMIT1  + C_SVT_OFFSET },
    {  "VT_XTRA1_HI_Pr_State"   , SVT_XTRA_HI_PRESS_STATE1  + C_SVT_OFFSET },
    {  "VT_XTRA1_LO_Pr_State"   , SVT_XTRA_LO_PRESS_STATE1  + C_SVT_OFFSET },

    {  "VT_XTRA2_HI_Pr_Enable"  , SVT_XTRA_HI_PRESS_ENABLE2 + C_SVT_OFFSET },
    {  "VT_XTRA2_LO_Pr_Enable"  , SVT_XTRA_LO_PRESS_ENABLE2 + C_SVT_OFFSET },
    {  "VT_XTRA2_HI_Pr_AlAck"   , SVT_XTRA_HI_PRESS_AL_ACK2 + C_SVT_OFFSET },
    {  "VT_XTRA2_LO_Pr_AlAck"   , SVT_XTRA_LO_PRESS_AL_ACK2 + C_SVT_OFFSET },
    {  "VT_XTRA2_HI_Pr_Limit"   , SVT_XTRA_HI_PRESS_LIMIT2  + C_SVT_OFFSET },
    {  "VT_XTRA2_LO_Pr_Limit"   , SVT_XTRA_LO_PRESS_LIMIT2  + C_SVT_OFFSET },
    {  "VT_XTRA2_HI_Pr_State"   , SVT_XTRA_HI_PRESS_STATE2  + C_SVT_OFFSET },
    {  "VT_XTRA2_LO_Pr_State"   , SVT_XTRA_LO_PRESS_STATE2  + C_SVT_OFFSET },

    {  "VT_HiHi_Vol%_Enable"    , SVT_HIHI_LEVEL_ENABLE     + C_SVT_OFFSET },
    {  "VT_HI_Vol%_Enable"      , SVT_HI_LEVEL_ENABLE       + C_SVT_OFFSET },
    {  "VT_LO_Vol%_Enable"      , SVT_LO_LEVEL_ENABLE       + C_SVT_OFFSET },
    {  "VT_LOLO_Vol%_Enable"    , SVT_LOLO_LEVEL_ENABLE     + C_SVT_OFFSET },
    {  "VT_HiHi_Vol%_AlAck"     , SVT_HIHI_LEVEL_AL_ACK     + C_SVT_OFFSET },
    {  "VT_HI_Vol%_AlAck"       , SVT_HI_LEVEL_AL_ACK       + C_SVT_OFFSET },
    {  "VT_LO_Vol%_AlAck"       , SVT_LO_LEVEL_AL_ACK       + C_SVT_OFFSET },
    {  "VT_LOLO_Vol%_AlAck"     , SVT_LOLO_LEVEL_AL_ACK     + C_SVT_OFFSET },
    {  "VT_HiHi_Vol%_Limit"     , SVT_HIHI_VOLPCNT_LIM     + C_SVT_OFFSET },
    {  "VT_HIHI_Vol%_Limit"     , SVT_HIHI_VOLPCNT_LIM      + C_SVT_OFFSET },
    {  "VT_HI_Vol%_Limit"       , SVT_HI_VOLPCNT_LIM        + C_SVT_OFFSET },
    {  "VT_LO_Vol%_Limit"       , SVT_LO_VOLPCNT_LIM        + C_SVT_OFFSET },
    {  "VT_LOLO_Vol%_Limit"     , SVT_LOLO_VOLPCNT_LIM      + C_SVT_OFFSET },
    {  "VT_HiHi_Vol%_State"     , SVT_HIHI_VOLPCNT_STATE    + C_SVT_OFFSET },
    {  "VT_HI_Vol%_State"       , SVT_HI_VOLPCNT_STATE      + C_SVT_OFFSET },
    {  "VT_LO_Vol%_State"       , SVT_LO_VOLPCNT_STATE      + C_SVT_OFFSET },
    {  "VT_LOLO_Vol%_State"     , SVT_LOLO_VOLPCNT_STATE    + C_SVT_OFFSET },

    {  "VT_Level_Change_Enable" , SVT_LEV_CHANGE_ENA        + C_SVT_OFFSET },
    {  "VT_Level_Change_AlAck"  , SVT_LEV_CHANGE_AL_ACK     + C_SVT_OFFSET },
    {  "VT_Level_Change_Limit"  , SVT_LEV_CHANGE_LIM        + C_SVT_OFFSET },
    {  "VT_Level_Change_State"  , SVT_LEV_CHANGE_STATE      + C_SVT_OFFSET },

    {  "VT_Alarm_Silence"       , SVT_ALARM_SILENCE         + C_SVT_OFFSET },
    {  "VT_Alarm_Acknowlegde"   , SVT_AL_ACKNOWLEDGE        + C_SVT_OFFSET },
    {  "VT_Alarm_AcknowlegdeAll", SVT_ACKNOWLEGDE_ALL       + C_SVT_OFFSET },



    // Scanjet tank washing machine tokens
    //{   "EndTankWashingMachineList" , TWM_END_TANK_WASHING_MACHINE_LIST},
    {   "TankWashingMachine"    , TWM_TANK_WASHING_MACHINE              },
    {   "EndTankWashingMachine" , TWM_END_TANK_WASHING_MACHINE          },
    {   "Identifier"            , TWM_IDENTIFIER                        },
    {   "NozzleDiameterMM"      , TWM_NOZZLE_DIAMETER_MM                },
    {   "SerialId"              , TWM_SERIAL_ID                         },
    {	"MachineTypeId"         , TWM_MACHINE_TYPE_ID                   },
    {   "NumberOfNozzles"       , TWM_NUMBER_OF_NOZZLES                 },


    // Scanjet tank cleaning media tokens                               
    {   "TankCleaningMediaList" , TWM_CLEANING_MEDIA_LIST               },
    {   "EndTankCleaningMediaList", TWM_END_CLEANING_MEDIA_LIST         },
    {   "CleaningMedia"         , TWM_CLEANING_MEDIA                    },
    {   "EndCleaningMedia"      , TWM_END_CLEANING_MEDIA                },

    // Water heater tokens (related to wash track)
    {   "HeaterInputTemp"       , C_PRO_WATER_HEATER_INPUT_TEMP         },
    {   "HeaterOutputTemp"      , C_PRO_WATER_HEATER_OUTPUT_TEMP        },
    {   "HeaterPressure"        , C_PRO_WATER_HEATER_PRESSURE           },
    {   "HeaterEfficiency"      , C_PRO_WATER_HEATER_EFFICIENCY         },
    {   "Fuel_kWh_per_ton"      , C_PRO_WATER_HEATER_FUEL_KWH_PER_TON   },

    {   "TSNNetworkStart"       , C_NETWORK                             },
    {   "TSNNetworkEnd"         , C_NETWORK_END                         },
};
//---------------------------------------------------------------------------

int CompareKeywordInTable(const void *KWEntry1, const void *KWEntry2) {
    char *Str1 = ((ConfigKeyWord *)KWEntry1)->KWord;
    char *Str2 = ((ConfigKeyWord *)KWEntry2)->KWord;
    char la, lb;

    for (;;) {
        la = *Str1; lb = *Str2;
        if (isupper(la)) la = tolower(la);
        if (isupper(lb)) lb = tolower(lb);
        if (la != lb || !la || !lb) break;
        Str1++; Str2++;
    }
    return (la - lb);
}

static int CompareKeyInTable(const void *KWEntry1, const void *KWEntry2) {
    int Val1 = ((ConfigKeyWord *)KWEntry1)->Key;
    int Val2 = ((ConfigKeyWord *)KWEntry2)->Key;
    return (Val1 - Val2);
}

//---------------------------------------------------------------------------
int CheckAndCorrectObjectIdTypeKey(int Key){

    switch (Key) {
    case C_AI_MB_Press_0_20mA   :
    case C_AI_MB_Press_4_20mA   :
        Key = C_AI_MB_Press_mA;
        break;
    case C_AI_MB_DiffPre_0_20mA :
    case C_AI_MB_DiffPre_4_20mA :
        Key = C_AI_MB_DiffPre_mA;
        break;
    case SVT_TMP1+ C_SVT_OFFSET:
        Key = SVT_T1 + C_SVT_OFFSET;
        break;
    case SVT_TMP2+ C_SVT_OFFSET:
        Key = SVT_T2 + C_SVT_OFFSET;
        break;
    case SVT_TMP3+ C_SVT_OFFSET:
        Key = SVT_T3 + C_SVT_OFFSET;
        break;
    case SVT_TMP4+ C_SVT_OFFSET:
        Key = SVT_T4 + C_SVT_OFFSET;
        break;
    case SVT_TMP5+ C_SVT_OFFSET:
        Key = SVT_T5 + C_SVT_OFFSET;
        break;
    case SVT_LEVEL_SENSOR2 + C_SVT_OFFSET:
        Key = SVT_LEVEL_SENSOR + C_SVT_OFFSET;
        break;
    case SVT_LEVEL_SWITCH_STATUS2 + C_SVT_OFFSET:
        Key = SVT_LEVEL_SWITCH_STATUS + C_SVT_OFFSET;
        break;
    case C_AI_AirPurge2   :
        Key = C_AI_AirPurge;
        break;
    case ID_AL_MODBUS_INPUT_STATUS2 :
        Key = ID_AL_MODBUS_INPUT_STATUS;
        break;
    case SVT_AP_LEVEL  + C_SVT_OFFSET:
    case SVT_AP_LEVEL2 + C_SVT_OFFSET:
        Key = SVT_AP_LEVEL_PRESSURE_MH2O;
        break;
    case C_TDU_TEMP_WIN2:
        Key = C_TDU_TEMP_WIN;
        break;
    case SVT_LEVEL_SWITCH_STATUS2:
        Key = SVT_LEVEL_SWITCH_STATUS;
        break;
    case C_FLOATING_POINT    :
        Key = C_FLOAT_BIG_ENDIAN;
        break;
    case C_FLOATING_POINT_REV:
        Key = C_FLOAT_L_END_BYTE_SWAP;
        break;
    case C_AI_NO_SHORT_CIRC_AL2:
        Key = C_AI_NO_SHORT_CIRC_AL;
        break;
    case AL_LIM_LOW_PV_PRESS2   :
    case AL_LIM_LOW_PV_PRESS3   :
        Key = AL_LIM_LOW_PV_PRESS;
        break;
    case AL_LIM_HIGH_PV_PRESS2  :
        Key = AL_LIM_HIGH_PV_PRESS;
        break;
    case C_PRO_MODBUS_COIL_IN2  :
        Key = C_PRO_MODBUS_COIL_IN;
        break;
    case C_CTRL_NS_POWERED2:
        Key = C_CTRL_NS_POWERED;
        break;
    case C_CTRL_NS_UNPOWERED2:
        Key = C_CTRL_NS_UNPOWERED;
        break;
    case C_PROJ_TYPE_NAME2:
        Key = C_PROJ_TYPE_NAME;
        break;
    case C_TU_ID2:
        Key = C_TU_ID;
        break;
    case C_TU_ADDRESS2:
        Key = C_TU_ADDRESS;
        break;
    }
    return Key;
}
//---------------------------------------------------------------------------


int CheckAndCorrectId(int IDNumber){
	IDNumber = (IDNumber & 0xFFFF) | (CheckAndCorrectObjectIdTypeKey(IDNumber>>16) << 16);
    return IDNumber;
}
//---------------------------------------------------------------------------
void SortKeywordList(void) {
    void *Base = (void *)SurvConfigKey;
    size_t Num = NELEMENTS(SurvConfigKey);
    size_t Width = sizeof(ConfigKeyWord);
#ifdef ANTDUSIM
    qsort(Base, Num, Width, CompareKeywordInTable);
#else
    qsort(Base, Num, Width, CompareKeywordInTable);
#endif
}
//---------------------------------------------------------------------------

static bool ConfKwdTableIsSorted = false;
int FindConfigKey(AnsiString KWord) {
    if (!ConfKwdTableIsSorted) {
        ConfKwdTableIsSorted = true;
        SortKeywordList();
    }
    void *Base = (void *)SurvConfigKey;
    size_t Num = NELEMENTS(SurvConfigKey);
    size_t Width = sizeof(ConfigKeyWord);
    ConfigKeyWord tmpKwd;
    strcpy(tmpKwd.KWord, KWord.c_str());
#ifdef ANTDUSIM
    ConfigKeyWord *KWPtr = (ConfigKeyWord *)lfind(&tmpKwd, Base, &Num, Width, CompareKeywordInTable);
#else
    ConfigKeyWord *KWPtr = (ConfigKeyWord *)bsearch(&tmpKwd, Base, Num, Width, CompareKeywordInTable);
#endif

    if (KWPtr) {
        // Change old to new Key.
        KWPtr->Key = CheckAndCorrectObjectIdTypeKey(KWPtr->Key);
        return (KWPtr->Key);
    } else {
        return (NOT_FOUND);
    }
}
//---------------------------------------------------------------------------

int FindValueConfigKey(AnsiString KWord) {
    int TmpKey = FindConfigKey(KWord);
    if (TmpKey != NOT_FOUND) {
        TmpKey &= ~C_SVT_OFFSET;
    }
    return (TmpKey);

}
//---------------------------------------------------------------------------

AnsiString KeyWord(int Key) {
    void *Base   = (void *)SurvConfigKey;
    size_t Num   = NELEMENTS(SurvConfigKey);
    size_t Width = sizeof(ConfigKeyWord);
    ConfigKeyWord tmpKwd;
    tmpKwd.Key = Key;
    ConfigKeyWord *KWPtr = (ConfigKeyWord *)lfind((void *)&tmpKwd, Base, &Num, Width, CompareKeyInTable);

    AnsiString KWd;
    if (KWPtr) {
        KWd = KWPtr->KWord;
    } else {
        KWd = (AnsiString)"Error";
    }
    KWd += TabStr1;
    return (KWd);
}
//---------------------------------------------------------------------------
AnsiString ValueKeyWord(int Key) {
    Key |= C_SVT_OFFSET;
    AnsiString KWord = KeyWord(Key);
    while (KWord.Length() < 15) {
        KWord += " ";
    }
    return KWord;
}
//---------------------------------------------------------------------------

AnsiString FindKeyWord(int Key) {
    void *Base   = (void *)SurvConfigKey;
    size_t Num   = NELEMENTS(SurvConfigKey);
    size_t Width = sizeof(ConfigKeyWord);
    ConfigKeyWord tmpKwd;
    tmpKwd.Key   = Key;
    ConfigKeyWord *KWPtr = (ConfigKeyWord *)lfind((void *)&tmpKwd, Base, &Num, Width, CompareKeyInTable);

    AnsiString KWd;
    if (KWPtr) {
        KWd = KWPtr->KWord;
    }
    return (KWd);
}
//---------------------------------------------------------------------------
AnsiString FindValueKeyWord(int Key) {
    Key |= C_SVT_OFFSET;
    return (FindKeyWord(Key));
}
//---------------------------------------------------------------------------

AnsiString KWrdEnableDisable(bool Enable, int KWTrue, int KWFalse) {
    if (Enable) {
        return (KeyWord(KWTrue));
    } else {
        return (KeyWord(KWFalse));
    }

}

void GiveConfigWarning(AnsiString Message) {
    ConfigWarningsString += Message + NewLineStr;
}

void GiveConfigWarning(AnsiString Name, int ErrorLine) {
    GiveConfigWarning(Name + (AnsiString)":\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
}

void GiveConfigWarning(AnsiString Name, AnsiString InputKeyWord, int ErrLine) {
    GiveConfigWarning(Name + (AnsiString)":\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)ErrLine + NewLineStr);
}

//---------------------------------------------------------------------------

void InputErrorMessage(AnsiString Message) {
#ifdef BORLAND
    MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
#else
    switch (CurrentDeviceId) {
    case DEVICE_TCU:
        break;
    case DEVICE_TDU:
    case DEVICE_TDU_SIMULATOR:
        AnsiString Text1 =  "Input message!";
        OKMessageBox->Exec(NULL, Text1, Message);
        break;
    }
#endif
}
//---------------------------------------------------------------------------

void HardwareSetupWarning(AnsiString Message) {
    HWOverviewWarningsString += (AnsiString)"Warning:\n";
    HWOverviewWarningsString += (AnsiString)Message + CrLfStr;
    // MessageDlg(Message, mtConfirmation, TMsgDlgButtons() << mbOK ,0);
/*
#else
    switch ( CurrentDeviceId ) {
        case DEVICE_TCU:
            break;
        case DEVICE_TDU:
            AnsiString Text1 =  "Config message!";
            OKMessageBox->Exec(NULL,Text1 , Message);
            break;
    }

#endif  */
}

AnsiString TabStrX(int StartTab, int Tabs) {
    AnsiString tmpStr = AnsiString::StringOfChar('\t', StartTab + Tabs);
    return tmpStr;
}
//---------------------------------------------------------------------------

#ifdef ANWIN
////////////////////////////////////////////////////////
//
// Config Stream system
// HISTORY:
// Created 31/10/06 EHS
//
////////////////////////////////////////////////////////
//ofstream     ConfigReportStream;
bool DebugReport = false;
AnsiString ReportStr;
void  ConfigLog(AnsiString Message) {
    //ReportStr += Message;
    if (DebugReport) {
        //ConfigReportStream << Message.c_str() << endl;
    }
}

void  ConfigLog(char *Fmt, ...) {
/*
    va_list ArgPtr;
    char Buf[2*BUF_SIZE];
    va_start(ArgPtr, Fmt);
    vsprintf(Buf,Fmt, ArgPtr);
    va_end(ArgPtr);
    ConfigLog((AnsiString)Buf);
    */
}
#endif

//////////////////////////////////////////////////////////////////////////////
//
// Pin Code / Security functions
//
//////////////////////////////////////////////////////////////////////////////
bool CheckPinCode(AnsiString PinCodeStr) {
    bool PinCodeOK = false;
//  int length = PinCodeStr.Length();
    int pin = atoi(PinCodeStr.c_str());
    if (pin > 0) {
        if ((PinCodeStr.AnsiCompareIC(PROSystemData::TXUSystemData->UserPinCode) == 0) || (pin == SECRET_PIN_CODE)) {
            PinCodeOK = true;
            PinUnlock = true;
        } else {
            PinCodeOK = false;
        }
    } else {
        PinCodeOK = false;
    }
    if (!PinCodeOK) {
        AnsiString Text1("Message!");
        AnsiString Text2("Invalid pin code.");
#ifdef BORLAND
        MessageDlg(Text2, mtConfirmation, TMsgDlgButtons() << mbOK, 0);
#else
        OKMessageBox->Exec(NULL, Text1, Text2);
#endif
    }
    return (PinCodeOK);
}
//---------------------------------------------------------------------------


int FindIndexIntegerList(int *IntList, int Value) {
    int Index = NOT_FOUND;
    unsigned i = 0;
    while ((i < sizeof(IntList)) && (Index == NOT_FOUND)) {
        if (IntList[i] == Value) Index = i;
        i++;
    }
    if (Index > NOT_FOUND) {
        return (Index);
    } else {
        return (NOT_FOUND);
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

bool DeleteValueIntegerList(int *IntList, int Value) {
    int Index = FindIndexIntegerList(IntList, Value);
    if (Index != NOT_FOUND) {
        for (unsigned j = Index; j < sizeof(IntList) - 1; j++) {
            IntList[j] = IntList[j + 1];
        }
        return (true);
    } else {
        return (false);
    }
}
//---------------------------------------------------------------------------
#define FIND_TAGNAME  0
#define FIND_NAME     1
#define FIND_ID       2
PRogramObjectBase* FindComponent(int Command, int CurrentType, AnsiString Name, bool CheckReadPermission, unsigned IDNumber) {
    PRogramObjectBase *CurrentPRO = NULL;
	set<PRogramObjectBase *>LocalSet;
    CurrentType = CheckAndCorrectObjectIdTypeKey(CurrentType);
	IDNumber    = CheckAndCorrectId(IDNumber);
	switch (CurrentType) {
    case C_PRO_SYSDATA:
        if (PROSystemData::TXUSystemData) {
            CurrentPRO = (PRogramObjectBase *)PROSystemData::TXUSystemData;   // This is dangerous
        }
        break;
    case C_PRO_ATMREFSENS:
        if (PROAtmReference::PROAtmRefPtr) {
            CurrentPRO = (PRogramObjectBase *)PROAtmReference::PROAtmRefPtr;
        }
		break;
    case C_PRO_INC:
        if (PROInclinometer::PROInclinPtr) {
            CurrentPRO = (PRogramObjectBase *)PROInclinometer::PROInclinPtr;
        }
        break;
    case C_PRO_DRAFT_SYSTEM:
        if (PRODraftSystem::PRODraftSysPtr) {
            CurrentPRO = (PRogramObjectBase *)PRODraftSystem::PRODraftSysPtr;
        }
        break;
    case C_PRO_TANKSYS_UNIT     :
    case C_PRO_DRAFT            :
    case C_PRO_CARGO            :
    case C_PRO_TANK             :
    case C_PRO_BALLAST          :
    case C_PRO_HFO              :
    case C_PRO_DO               :
    case C_PRO_LUB              :
    case C_PRO_FW               :
    case C_PRO_MISC             :
    case C_PRO_TANKPRESS        :
    case C_PRO_TEMP             :
    case C_PRO_LEVSWITCH        :
    case C_PRO_WATERINGRESS     :
    case C_PRO_T_PANEL_CONTR    :
    case C_PRO_ANPRO3           :
    case C_PRO_SAAB_PROTOCOL    :
    case C_PRO_LINEPRESS        :
    case C_PRO_VOIDSPACE        :
    case C_IOC_ANALOG_IN        :
	case C_PRO_MODBUS_COIL_IN   :
	case C_PRO_WATER_HEATER		:
	case C_PRO_TANK_WASH_MACHINE:
    case C_PRO_MODBUS_UNIT      :
    case C_PRO_MODBUS_REG_BIT_IN:

        {
			switch (CurrentType) {
            case C_PRO_TANKSYS_UNIT:
                LocalSet = PROTanksystemUnit::TanksystemUnitSet;
                break;
            case C_IOC_ANALOG_IN:
                break;
            case C_PRO_CARGO:
                LocalSet = PROCargoTank::ObjectSet;
                break;
            case C_PRO_TANK:
                LocalSet = PROTank::ObjectSet;
                break;
            case C_PRO_BALLAST:
                LocalSet = PROBallastTank::ObjectSet;
                break;
            case C_PRO_HFO:
            case C_PRO_DO:
            case C_PRO_LUB:
            case C_PRO_FW:
            case C_PRO_MISC:
                LocalSet = PROServiceTank::ObjectSet;
                break;
            case C_PRO_VOIDSPACE:
                LocalSet = PROVoidSpace::ObjectSet;
                break;
            case C_PRO_TANKPRESS:
                LocalSet = PROTankPressure::ObjectSet;
                break;
            case C_PRO_TEMP:
                LocalSet = PROTemperature::ObjectSet;
                break;
            case C_PRO_LEVSWITCH:
                LocalSet = PROLevelSwitch::ObjectSet;
                break;
            case C_PRO_WATERINGRESS:
                LocalSet = PROWaterIngress::ObjectSet;
                break;
            case C_PRO_T_PANEL_CONTR:
                LocalSet = TPCxObject::ObjectSet;
                break;
            case C_PRO_ANPRO3:
                LocalSet = AnPro3object::ObjectSet;
                break;
            case C_PRO_SAAB_PROTOCOL:
                LocalSet = SaabProtcol::ObjectSet;
                break;
            case C_PRO_LINEPRESS:
                LocalSet = PROLinePressure::ObjectSet;
                break;
            case C_PRO_MODBUS_COIL_IN:
                LocalSet = ModbusCoilIn::ModbusSet;
                break;
			case C_PRO_MODBUS_COIL_OUT:
				LocalSet = ModbusCoilOut::ModbusSet;
                break;
			case C_PRO_DRAFT:
                if (PRODraftSystem::PRODraftSysPtr) {
                    LocalSet = PRODraftSystem::PRODraftSysPtr->DraftList;
                }
                break;
            case C_PRO_TANK_WASH_MACHINE:
                LocalSet = PROTankWashingMachine::ObjectSet;
                break;
            case C_PRO_WATER_HEATER:
                LocalSet = PROWaterHeater::ObjectSet;
                break;
            case C_PRO_MODBUS_UNIT      :
                LocalSet = ModbusUnit::ObjectSet;
                break;
            case C_PRO_MODBUS_REG_BIT_IN:
                LocalSet = ModbusRegBitIn::ModbusSet;
                break;
            }
            if (!LocalSet.empty()) {
                PRogramObjectBase *tmpPROPtr = NULL;
				set<PRogramObjectBase *>::iterator pBIt;
				for (pBIt = LocalSet.begin(); !tmpPROPtr && pBIt != LocalSet.end(); pBIt++) {
					switch (Command) {
					case FIND_TAGNAME:
						if ((*pBIt)->TagName == Name) {
							tmpPROPtr = (*pBIt);
						}
						break;
					case FIND_NAME   :
						if ((*pBIt)->Name == Name) {
							tmpPROPtr = (*pBIt);
						}
						break;
					case FIND_ID     :
						{
							int ObjIDNumber = (*pBIt)->IDNumber;
							if ((*pBIt)->IDNumber == IDNumber) {
								tmpPROPtr = (*pBIt);
							}
						}
						break;
					}
                }
				if (tmpPROPtr && (!CheckReadPermission || (CheckReadPermission &&  tmpPROPtr->ReadPermission()))) {
					CurrentPRO =  tmpPROPtr;
				}
			}
		}
		break;
	case C_PRO_USER_CARGO_TYPE:
		{
			for (int i = 0; !CurrentPRO && i < MAX_CARGOTYPES; i++) {
                switch (Command) {
                case FIND_TAGNAME:
                    if (CTOUser::CargoTable[i]->TagName == Name) {
                        CurrentPRO = (PRogramObjectBase *)CTOUser::CargoTable[i];
                    }
                    break;
                case FIND_NAME   :
                    if (CTOUser::CargoTable[i]->Name == Name) {
                        CurrentPRO = (PRogramObjectBase *)CTOUser::CargoTable[i];
                    }
                    break;
                case FIND_ID     :
                    if (CTOUser::CargoTable[i]->IDNumber == IDNumber) {
                        CurrentPRO = (PRogramObjectBase *)CTOUser::CargoTable[i];
                    }
                    break;
                }
            }
        }
        break;
    default:
        break;
    }
	return (CurrentPRO);
}
//---------------------------------------------------------------------------
PRogramObject* FindCompFromTagName(int CurrentType, AnsiString CompTagName, bool CheckReadPermission) {
    return ((PRogramObject *)FindComponent(FIND_TAGNAME, CurrentType, CompTagName, CheckReadPermission));
}

PRogramObject* FindCompFromName(int CurrentType, AnsiString ComponentName, bool CheckReadPermission) {
	return ((PRogramObject *)FindComponent(FIND_NAME, CurrentType, ComponentName, CheckReadPermission));
}
PRogramObjectBase* FindPROFromIDNumber(unsigned IDNumber, bool CheckReadPermission) {
	PRogramObjectBase *PROPtr = NULL;
    int ObjectId = IDNumber >> 16;
    if (ObjectId >= C_PRO_PROJINFO && ObjectId < 10000) { //only to strip of fault
		PROPtr = FindComponent(FIND_ID, ObjectId, "", CheckReadPermission, IDNumber);
	}
	return (PROPtr);
}

bool ConvertToInt(int *value, AnsiString ValueString) {
    bool Error = false;
    int tempValue = 0;
#ifdef ANCONF
    if (ValueString.data()) {
        DecimalSeparator = '.';
        try {
            tempValue = ValueString.ToInt();
        } catch (.../*const exception& e*/) {
            Error = true;
        }
        if (Error) {
            Error = false;
            DecimalSeparator = ',';
            try {
                tempValue = ValueString.ToInt();
            } catch (.../*const exception& e*/) {
                Error = true;
            }
        }
        if (Error) {
            AnsiString Message = (AnsiString)"The text: \"" + ValueString + "\" is not a valid number";
            MessageDlg(Message, mtConfirmation, TMsgDlgButtons() << mbOK, 0);
            tempValue = *value;
        }
        DecimalSeparator = '.';
    }
#else
    tempValue = atoi(ValueString.c_str());
#endif
    *value =  tempValue;
    return (!Error);
}
//---------------------------------------------------------------------------


bool ConvertToShort(short *value, AnsiString ValueString) {
    bool Error = false;
    short tempValue = 0;
#ifdef ANCONF
    if (ValueString.data()) {
        DecimalSeparator = '.';
        try {
            tempValue = (short)ValueString.ToInt();
        } catch (.../*const exception& e*/) {
            Error = true;
        }
        if (Error) {
            Error = false;
            DecimalSeparator = ',';
            try {
                tempValue = (short)ValueString.ToInt();
            } catch (.../*const exception& e*/) {
                Error = true;
            }
        }
        if (Error) {
            AnsiString Message = (AnsiString)"The text: \"" + ValueString + "\" is not a valid number";
            MessageDlg(Message, mtConfirmation, TMsgDlgButtons() << mbOK, 0);
            tempValue = *value;
        }
        DecimalSeparator = '.';
    }
#else
    int status = E_NO_ERR;
    int tempV = int(ConvertToSi(ValueString, NO_UNIT, status, -1000000.0, 1000000.0, 0.0));
    if (status == E_NO_ERR) {
        tempValue = tempV;
    } else {
        Error = true;
    }
#endif
    *value =  tempValue;
    return (!Error);
}
//---------------------------------------------------------------------------

bool ConvertToFloat(float *value, AnsiString ValueString) {
    bool Error = false;
    float tempValue = 0.00;
#ifdef ANCONF
    if (ValueString.data()) {
        DecimalSeparator = '.';
        try {
            tempValue = (float)ValueString.ToDouble();
        } catch (.../*const exception& e*/) {
            Error = true;
        }
        if (Error) {
            Error = false;
            DecimalSeparator = ',';
            try {
                tempValue = (float)ValueString.ToDouble();
            } catch (.../*const exception& e*/) {
                Error = true;
            }
        }
        if (Error) {
            AnsiString Message = (AnsiString)"The text: \"" + ValueString + "\" is not a valid number";
            MessageDlg(Message, mtConfirmation, TMsgDlgButtons() << mbOK, 0);
            tempValue = *value;
        }
        DecimalSeparator = '.';
    }
#else
    int status = E_NO_ERR;
    float tempV = ConvertToSi(ValueString, NO_UNIT, status, -1000000.0, 1000000.0, 0.0);
    if (status == E_NO_ERR) {
        tempValue = tempV;
    } else {
        Error = true;
    }
#endif
    *value =  tempValue;
    return (!Error);
}
//---------------------------------------------------------------------------

AnsiString FloatToAnsiString(float Value, int Width, int DecimalPoint) {
    AnsiString TmpStr;
//#ifdef BORLAND
//    TmpStr = TmpStr.FormatFloat("0.###", Value);
//#else
	if (IsNan(Value)) {
		TmpStr = "NaN";
	} else if (IsInfinite(Value)) {
        TmpStr = "Inf";
	} else {
        char tmpBuf[BUF_SIZE];
        sprintf(tmpBuf, "%*.*f",Width,DecimalPoint, Value);
        TmpStr = (AnsiString)tmpBuf;
    }
//#endif
    return (TmpStr);
}
//---------------------------------------------------------------------------

AnsiString DivideString(AnsiString Message, int Length) {
    AnsiString TempStr;
    char *MsgPtr = (char *)Message.c_str();
    while (*MsgPtr) {
        char *TmpPtr = MsgPtr;
        if (strlen(MsgPtr) > (unsigned)Length) {
            int EndIndex = Length - 1;
            while (EndIndex && !iswspace(MsgPtr[EndIndex])) EndIndex--;
            MsgPtr[EndIndex] = 0;
            TmpPtr += EndIndex + 1;
        } else {
            TmpPtr += strlen(MsgPtr);
        }
        TempStr = TempStr + MsgPtr + CrLfStr;
        MsgPtr = TmpPtr;
    }
    return (TempStr);
}
//---------------------------------------------------------------------------

void WriteConfigToFile(char *fileName) {
    // Be sure that all sensors have ID numbers
    AnalogInput::CreateIdNum();

    if (PROProjectInfo::PROProjectInfoPtr && PROProjectInfo::PROProjectInfoPtr->ProjectName.data()) {
        TSNConfigString ConfigString(CONFIG_FILE_SIZE);
// Config Info
        if (TSNConfigInfo::ConfigInfoPtr) {
            TSNConfigInfo::ConfigInfoPtr->WriteConfigToFile(ConfigString);
        }
// Project Info
        if (PROProjectInfo::PROProjectInfoPtr) {
            PROProjectInfo::PROProjectInfoPtr->WriteConfigToFile(ConfigString);
        }
// TCU Info
        PROTanksystemUnit::MyTCUPtr->WriteConfigToFile(ConfigString);
        ConfigString.AddString(MakeConfigStringFromList(ModbusObject::GetModbusObjectSet()));
        ConfigString.AddString(MakeConfigStringFromList(ModbusMultiple::GetModbusObjectSet()));


// Atmospheric reference
        if (PROAtmReference::PROAtmRefPtr) PROAtmReference::PROAtmRefPtr->WriteConfigToFile(ConfigString);
// Inclinometers
        if (PROInclinometer::PROInclinPtr) PROInclinometer::PROInclinPtr->WriteConfigToFile(ConfigString);
// Draft measurements
        if (PRODraftSystem::PRODraftSysPtr) PRODraftSystem::PRODraftSysPtr->WriteConfigToFile(ConfigString);
// for all types of PRogramObject
//
//
//

        set<PRogramObjectBase *>PROListTable[] = {
            PROCargoTank::ObjectSet,
            PROBallastTank::ObjectSet,
            PROServiceTank::ObjectSet,
            PROLevelSwitch::ObjectSet,
            PROTankPressure::ObjectSet,
            PROLinePressure::ObjectSet,
            PROTemperature::ObjectSet,
            PROWaterIngress::ObjectSet,
            PROVoidSpace::ObjectSet,
            TPCxObject::ObjectSet,
            AnPro3object::ObjectSet,
            SaabProtcol::ObjectSet,
        };

        for (unsigned i = 0; i < NELEMENTS(PROListTable); i++) {
            set<PRogramObjectBase *>::iterator pBIt;
            for (pBIt = PROListTable[i].begin(); pBIt != PROListTable[i].end(); pBIt++) {
                (*pBIt)->WriteConfigToFile(ConfigString);
            }
        }
        ConfigString.WriteFile(fileName, false);
    } else {
#ifdef ANCONF
        AnsiString Message = "You must write a Project Name,\n to be able to save!";
        MessageDlg(Message, mtConfirmation, TMsgDlgButtons() << mbOK, 0);
#endif
    }
}
//---------------------------------------------------------------------------

PROTanksystemUnit* FindTCUFromAddress(int Addr) {
    PROTanksystemUnit *FoundElement = NULL;
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = PROTanksystemUnit::TanksystemUnitSet.begin(); !FoundElement && pBIt != PROTanksystemUnit::TanksystemUnitSet.end(); pBIt++) {
        PROTanksystemUnit *UnitPtr = (PROTanksystemUnit *)(*pBIt);
        if (UnitPtr->UnitID == DEVICE_TCU &&  UnitPtr->Address == Addr) {
            FoundElement = UnitPtr;
        }
    }
    return (FoundElement);
}
//---------------------------------------------------------------------------

void AddToIOUnits(PROIOComponent *CompPtr, PRogramObject *TElement) {
    if (CompPtr && TElement) {
        switch (CompPtr->IOType) {
        default:
            break;
        case C_IO_AN_ZBHART:
        case C_IO_AN_ZBANA :
        case C_IO_AN_ZB485 :
            {

                PROTanksystemUnit *TCUElement = FindTCUFromAddress(CompPtr->TCUAddress);
                int IOType = CompPtr->IOType;
                if (TCUElement) {
                    int PortNo = CompPtr->TCUPortNo;
                    if (((IOType == C_IO_AN_ZBANA) || (IOType == C_IO_AN_ZB485) || (IOType == C_IO_AN_ZBHART))
                        && ((TCUElement->PortKey[PortNo] == C_TCU_COM_485_ZB) ||
                            (TCUElement->PortKey[PortNo] == C_TCU_COM_485_ZB_RED) ||
                            (TCUElement->PortKey[PortNo] == C_TCU_COM_485_MODBUS_MASTER))) {
                        IOUnit *IOElement = NULL;
                        bool Error = false;

                        set<PRogramObjectBase *>::iterator pBIt;
                        for (pBIt = TCUElement->UnitPortList[PortNo].begin(); !IOElement && pBIt != TCUElement->UnitPortList[PortNo].end(); pBIt++) {
                            IOUnit *tmpIOElement = (IOUnit *)(*pBIt);
                            if ((tmpIOElement->TCUAddress == CompPtr->TCUAddress) //Not necessary
                                && (tmpIOElement->TCUPortNo == CompPtr->TCUPortNo)
                                && (tmpIOElement->IOAddress == CompPtr->IOAddress)
                                && (tmpIOElement->IOType == IOType)) {
                                if (tmpIOElement->Add(CompPtr, TElement)) {
                                    IOElement = tmpIOElement;
                                } else {
                                    Error = true;   //Error handled on lower level
                                }
                            }
                        }

                        if (!IOElement && !Error) {
                            switch (IOType) {
                            case C_IO_AN_ZBANA:
                                IOElement = new IOUnitZBAna(CompPtr, TElement);
                                break;
                            case C_IO_AN_ZB485:
                                IOElement = new IOUnitZB485(CompPtr, TElement);
                                break;
                            case C_IO_AN_ZBHART:
                                IOElement = new IOUnitZBHart(CompPtr, TElement);
                                break;
                            default:
                                IOElement = NULL;
                                Error = true;
                                AnsiString Message = (AnsiString)"TCU " + (AnsiString)CompPtr->TCUAddress;
                                Message += (AnsiString)" com-port " + (AnsiString)CompPtr->TCUPortNo + ".\n";
                                Message += (AnsiString)"Not known IO addr." + (AnsiString)CompPtr->IOAddress;
                                Message += (AnsiString)" on com-port.\nTry to set sensor for ";
                                Message += (AnsiString)TElement->Name + ".\n";
                                HardwareSetupWarning(Message);
                                break;
                            }
                            if (IOElement && !Error) {
                                TCUElement->UnitPortList[PortNo].insert(IOElement);
                            } else {
                                //Warning "No IO on this Com port!"
                            }
                        }
                        if (Error) {
                            // warning "Something wrong with IO on this Com port!"
                        }
                    } else {
                        AnsiString Message = (AnsiString)"TCU " + (AnsiString)CompPtr->TCUAddress;
                        Message += (AnsiString)" com-port " + (AnsiString)CompPtr->TCUPortNo + ".\n";
                        Message += (AnsiString)"Wrong IO type (" + KeyWord(IOType) + ") with addr." + (AnsiString)CompPtr->IOAddress;
                        Message += (AnsiString)" on com-port.\nTry to set sensor for ";
                        Message += (AnsiString)TElement->Name + ".\n";
                        HardwareSetupWarning(Message);
                    }
                } else {
                    AnsiString Message = (AnsiString)"TCU " + (AnsiString)CompPtr->TCUAddress;
                    Message += (AnsiString)" com-port " + (AnsiString)CompPtr->TCUPortNo + ".\n";
                    Message += (AnsiString)"No TCU with addr." + (AnsiString)CompPtr->TCUAddress + CrLfStr;
                    Message += (AnsiString)"For IO " + KeyWord(IOType) + " addr." + (AnsiString)CompPtr->IOAddress;
                    Message += (AnsiString)" \non com-port: " + (AnsiString)CompPtr->TCUPortNo;
                    Message += (AnsiString)".\nTry to set sensor for ";
                    Message += (AnsiString)TElement->Name + ".\n";
                    HardwareSetupWarning(Message);
                }
            }
            break;
        }
    }
#ifdef S2TXU
    if (PROAtmReference::PROAtmRefPtr && PROAtmReference::PROAtmRefPtr->SensorOnTCU) {
        PROTanksystemUnit::MySelf->AddAtmReferenceSensor(PROAtmReference::PROAtmRefPtr->AtmRefSensors[0]);
    }
#endif
}

void LateBinding(void) {
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = PROTanksystemUnit::TanksystemUnitSet.begin(); pBIt != PROTanksystemUnit::TanksystemUnitSet.end(); pBIt++) {
        ((PROTanksystemUnit *)(*pBIt))->SetProList();
    }
    ModbusObject::SetGlobalProList();
    ModbusUnit::SetGlobalProList();
    AnPro3object::SetGlobalProList();
}
void CreateIOUnits(void) {
//Use table of all PRO
    HWOverviewWarningsString = "";
//#endif
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = PROTanksystemUnit::TanksystemUnitSet.begin(); pBIt != PROTanksystemUnit::TanksystemUnitSet.end(); pBIt++) {
        PROTanksystemUnit *ElementPtr = ((PROTanksystemUnit *)(*pBIt));
        // clear old to avoid resource leak
        for (int i = 0; i < MAX_COM_PORTS; i++) {
            ElementPtr->UnitPortList[i].clear();
        }
        if (ElementPtr->CtrlAlarmRelayPtr1) {
            ElementPtr->CtrlAlarmRelayPtr1->SetProList();
#ifndef ANCONF
            ElementPtr->CtrlAlarmRelayPtr1->SetAlarmList();
#endif
        }
        if (ElementPtr->CtrlAlarmRelayPtr2) {
            ElementPtr->CtrlAlarmRelayPtr2->SetProList();
#ifndef ANCONF
            ElementPtr->CtrlAlarmRelayPtr2->SetAlarmList();
#endif
        }
        if (ElementPtr->CtrlHornPtr) {
            ElementPtr->CtrlHornPtr->SetProList();
#ifndef ANCONF
            ElementPtr->CtrlHornPtr->SetAlarmList();
#endif
        }
        if (ElementPtr->CtrlLampPtr) {
            ElementPtr->CtrlLampPtr->SetProList();
#ifndef ANCONF
            ElementPtr->CtrlLampPtr->SetAlarmList();
#endif
        }
        if ( !ElementPtr->Address || (ElementPtr->Address == CurrentDeviceAddress) ){
            for (int uart = 0; uart < MAX_COM_PORTS; uart++) {
                //         (*pBIt)->UnitPortList[uart] = NULL; // for WinConfig prog
                switch (ElementPtr->PortKey[uart]) {
                case C_TCU_COM_485_TCU:
                case C_TCU_COM_232_TCU:
                case C_TCU_COM_485_TDU:
                case C_TCU_COM_232_TDU:
                case C_TCU_COM_232_PC :
                    {
                        //Is the TCU, TDU or PC defined separately with e.g. address?
                        // The keywords DeviceTCU, DeviceTDU or DevicePC in separate context in config file will result in entry
                        // in the DeviceDataVector.
                        if (ElementPtr->DeviceDataVector[uart].empty()) {
                            int DevKey;
                            switch (ElementPtr->PortKey[uart]) {
                            case C_TCU_COM_485_TDU:
                            case C_TCU_COM_232_TDU:
                                DevKey = DEVICE_TDU;
                                break;
                            case C_TCU_COM_485_TCU:
                            case C_TCU_COM_232_TCU:
                                DevKey = DEVICE_TCU;
                                break;
                            case C_TCU_COM_232_PC:
                                DevKey = DEVICE_PCSW;
                                break;
                            }
                            PROTanksystemUnit *DevPtr = new PROTanksystemUnit(uart, 0  , DevKey, ElementPtr);
                            if (DevPtr) {
                                ElementPtr->UnitPortList[uart].insert(DevPtr);
                            }
                        } else {
                            for (unsigned i = 0; i < ElementPtr->DeviceDataVector[uart].size(); i++) {
                                int Address = ElementPtr->DeviceDataVector[uart][i].Address;
                                switch (ElementPtr->PortKey[uart]) {
                                case C_TCU_COM_485_TCU:
                                case C_TCU_COM_232_TCU:
                                    {
                                        PROTanksystemUnit *LocalTCUElement = PROTanksystemUnit::FindTCU(Address);

                                        if (LocalTCUElement) {
                                            LocalTCUElement->MyPortNumberonTCU = uart;
                                            LocalTCUElement->SetId();
                                            ElementPtr->UnitPortList[uart].insert(LocalTCUElement);
                                        }
                                    }
                                    break;
                                case C_TCU_COM_485_TDU:
                                case C_TCU_COM_232_TDU:
                                case C_TCU_COM_232_PC:
                                    {
                                        int DevKey;
                                        switch (ElementPtr->PortKey[uart]) {
                                        case C_TCU_COM_485_TDU:
                                        case C_TCU_COM_232_TDU:
                                            DevKey = DEVICE_TDU;
                                            break;
                                        case C_TCU_COM_232_PC:
                                            DevKey = DEVICE_PCSW;
                                            break;
                                        }
                                        PROTanksystemUnit *DevPtr = new PROTanksystemUnit(uart, Address, DevKey, ElementPtr);
                                        if (DevPtr) {
                                            ElementPtr->UnitPortList[uart].insert(DevPtr);
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    break;
                    /*
                case C_TCU_COM_232_TCU:
                    {

                        if (!PROTanksystemUnit::TanksystemUnitSet.empty()) {
                            set<PRogramObjectBase *>::iterator pBIt2;
                            for (pBIt2 = PROTanksystemUnit::TanksystemUnitSet.begin(); pBIt2 != PROTanksystemUnit::TanksystemUnitSet.end(); pBIt2++) {
                                PROTanksystemUnit *LocalTCUElement = ((PROTanksystemUnit *)(*pBIt2));
                                if ((*pBIt) != (*pBIt2)) {
                                    ElementPtr->UnitPortList[uart].insert(LocalTCUElement);
                                }
                                if (!Master) {
                                    LocalTCUElement->MyPortNumberonTCU = uart;
                                    LocalTCUElement->SetId();
                                }
                            }
                        }
                    }
                    break;
                    */
                case C_TCU_COM_232_PRINTER:
                    /*PROPrinter *PrinterPtr = */new PROPrinter(uart, ElementPtr->UnitID, ElementPtr->Address);
                    break;
                case C_TCU_COM_232_SAAB:
                    break;
                case C_TCU_COM_485_TPC:
                    if (!TPCxObject::ObjectSet.empty()) {
                        set<PRogramObjectBase *>::iterator pBIt;
                        for (pBIt = TPCxObject::ObjectSet.begin(); pBIt != TPCxObject::ObjectSet.end(); pBIt++) {
                            ElementPtr->UnitPortList[uart].insert((*pBIt));
                        }
                    }
                    break;
                case C_TCU_COM_485_PROT3:
                case C_TCU_COM_232_PROT3:
                    if (!AnPro3object::AnPro3objectVector.empty()) {
                        for (unsigned count = 0; count < AnPro3object::AnPro3objectVector.size(); count++) {
                            ElementPtr->UnitPortList[uart].insert(AnPro3object::AnPro3objectVector[count]);
                        }
                    }
                    break;

                }
            }
        }

    }

	// hkim. for network entry
	for(vector<NetworkedDevice>::iterator itr = PROTanksystemUnit::_net_devices.begin();
		itr != PROTanksystemUnit::_net_devices.end(); itr++)
	{
	  struct NetworkedDevice nd = *itr;

	  //
	  // create a networked entry
	  // only if there is no existing entry for the address/devid pair.
	  //
	  if(PROTanksystemUnit::FindUnit(nd.device_address, nd.device_id) == NULL)
	  {
		new PROTanksystemUnit(nd.device_address, nd.device_id);
	  }

	}
	// end of hkim

	if (PROAtmReference::PROAtmRefPtr) {
        if (!PROAtmReference::PROAtmRefPtr->SensorOnTCU) {
            for (unsigned i = 0; i < PROAtmReference::PROAtmRefPtr->AnalogInList.size(); i++) {
                AddToIOUnits(PROAtmReference::PROAtmRefPtr->AnalogInList[i], PROAtmReference::PROAtmRefPtr);
            }
        }
    }
    if (PROInclinometer::PROInclinPtr) {
        AddToIOUnits(PROInclinometer::PROInclinPtr->Inc1Sensor,PROInclinometer::PROInclinPtr);
        AddToIOUnits(PROInclinometer::PROInclinPtr->Inc2Sensor,PROInclinometer::PROInclinPtr);
    }
    if (PRODraftSystem::PRODraftSysPtr) {
        if (PRODraftSystem::PRODraftSysPtr->DFPtr ) AddToIOUnits(PRODraftSystem::PRODraftSysPtr->DFPtr->DraftSensor , PRODraftSystem::PRODraftSysPtr->DFPtr );
        if (PRODraftSystem::PRODraftSysPtr->DSPtr ) AddToIOUnits(PRODraftSystem::PRODraftSysPtr->DSPtr->DraftSensor , PRODraftSystem::PRODraftSysPtr->DSPtr );
        if (PRODraftSystem::PRODraftSysPtr->DPPtr ) AddToIOUnits(PRODraftSystem::PRODraftSysPtr->DPPtr->DraftSensor , PRODraftSystem::PRODraftSysPtr->DPPtr );
        if (PRODraftSystem::PRODraftSysPtr->DAPtr ) AddToIOUnits(PRODraftSystem::PRODraftSysPtr->DAPtr->DraftSensor , PRODraftSystem::PRODraftSysPtr->DAPtr );
        if (PRODraftSystem::PRODraftSysPtr->DFPPtr) AddToIOUnits(PRODraftSystem::PRODraftSysPtr->DFPPtr->DraftSensor, PRODraftSystem::PRODraftSysPtr->DFPPtr);
        if (PRODraftSystem::PRODraftSysPtr->DFSPtr) AddToIOUnits(PRODraftSystem::PRODraftSysPtr->DFSPtr->DraftSensor, PRODraftSystem::PRODraftSysPtr->DFSPtr);
        if (PRODraftSystem::PRODraftSysPtr->DAPPtr) AddToIOUnits(PRODraftSystem::PRODraftSysPtr->DAPPtr->DraftSensor, PRODraftSystem::PRODraftSysPtr->DAPPtr);
        if (PRODraftSystem::PRODraftSysPtr->DASPtr) AddToIOUnits(PRODraftSystem::PRODraftSysPtr->DASPtr->DraftSensor, PRODraftSystem::PRODraftSysPtr->DASPtr);
    }

	vector<PRogramObjectBase *>PROListTable[] = {
		PROCargoTank::AllObjVector,
		PROBallastTank::AllObjVector,
		PROServiceTank::AllObjVector,
		PROLevelSwitch::AllObjVector,
		PROTankPressure::AllObjVector,
		PROLinePressure::AllObjVector,
		PROTemperature::AllObjVector,
		PROWaterIngress::AllObjVector,
		PROVoidSpace::AllObjVector,
		//TPCxObject::AllObjVector,
		//AnPro3object::AllObjVector,
		//SaabProtcol::AllObjVector,
		PROTankWashingMachine::AllObjVector,
		PROWaterHeater::AllObjVector,
	};

	for (unsigned i = 0; i < NELEMENTS(PROListTable); i++) {
		vector<PRogramObjectBase *>::iterator pBIt;
		for (pBIt = PROListTable[i].begin(); pBIt != PROListTable[i].end(); pBIt++) {
			PRogramObject *Element = (PRogramObject *)(*pBIt);
			for (unsigned j = 0; j < Element->AnalogInList.size(); j++) {
				AddToIOUnits(Element->AnalogInList[j], Element);
			}
		}
	}
	PROTank::SetAllProList();
    // Update alarm lists for the following:
    // - ModbusCoilOut

    set<ModbusObject *>::iterator pMBIt;
    for (pMBIt = ModbusObject::ModbusSet.begin(); pMBIt != ModbusObject::ModbusSet.end(); pMBIt++) {
       (*pMBIt)->SetAlarmList();
    }

}

bool LoadConfig(TSNConfigString &ConfigString) {
    //ConfigWarningsString = "";
    PRogramObject *CurrentPRO = NULL;
    unsigned IDNumber;
    bool NoError = true;
    int ErrorLine = 0;
    //SortDictionary();
    SortDictionary();
#ifdef S2TXU
    ReadLocalSettings();
#endif
	int Cnt=0;
	do {
		AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
		if (ErrorLine) {
			if (ErrorLine != EOF) {
				GiveConfigWarning("Basic level", ErrorLine);
			}
		} else {
			Cnt++;
            int Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning("Basic level", InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_CONFIG_INFO:
                {
                    if (!TSNConfigInfo::ConfigInfoPtr)    TSNConfigInfo::ConfigInfoPtr = new TSNConfigInfo();
                    TSNConfigInfo::ConfigInfoPtr->LoadConfigFromFile(ConfigString);
                }
                break;
            case C_PRO_PROJINFO:
                {
                    if (!PROProjectInfo::PROProjectInfoPtr) new PROProjectInfo();
                    PROProjectInfo::PROProjectInfoPtr->LoadConfigFromFile(ConfigString);
                }
                break;
            case C_PRO_TANKSYS_UNIT:
                {
                    PROTanksystemUnit *PROPtr = new PROTanksystemUnit();
                    PROPtr->LoadConfigFromFile(ConfigString);

                    PROTanksystemUnit::TanksystemUnitSet.insert(PROPtr);
                }
                break;
            case C_PRO_ATMREFSENS:
                if (!PROAtmReference::PROAtmRefPtr)  new PROAtmReference(true);
                PROAtmReference::PROAtmRefPtr->LoadConfigFromFile(ConfigString);
                break;
            case C_PRO_INC:
                if (!PROInclinometer::PROInclinPtr) new PROInclinometer();
                PROInclinometer::PROInclinPtr->LoadConfigFromFile(ConfigString);
                break;
            case C_PRO_DRAFT_SYSTEM:
                if (!PRODraftSystem::PRODraftSysPtr)   new PRODraftSystem();
                PRODraftSystem::PRODraftSysPtr->LoadConfigFromFile(ConfigString);
                break;
			case C_PRO_CARGO:
                IDNumber = ConfigString.ReadInteger(ErrorLine);
                CurrentPRO = new PROCargoTank(Key, IDNumber,ConfigString.GetCurrentLine());
				CurrentPRO->LoadConfigFromFile(ConfigString);
                break;
            case C_PRO_USER:
                {
                    IDNumber = ConfigString.ReadInteger(ErrorLine);
                    PROUser *tmpPtr = new PROUser();
                    tmpPtr->SetLineNumber(ConfigString.GetCurrentLine());
                    tmpPtr->LoadConfigFromFile(ConfigString);
                }
                break;
#ifdef ANCONF
            case C_PRO_TANK:
            case C_PRO_BALLAST:
            case C_PRO_HFO:
            case C_PRO_DO:
            case C_PRO_LUB:
            case C_PRO_FW:
            case C_PRO_MISC:
                IDNumber = ConfigString.ReadInteger(ErrorLine);
                CurrentPRO = new PROTank(Key, IDNumber,ConfigString.GetCurrentLine());
                CurrentPRO->LoadConfigFromFile(ConfigString);
                break;
#else
            case C_PRO_TANK:    //must be something wrong if this
            case C_PRO_BALLAST:
                IDNumber = ConfigString.ReadInteger(ErrorLine);
                CurrentPRO = new PROBallastTank(Key, IDNumber,ConfigString.GetCurrentLine());
                CurrentPRO->LoadConfigFromFile(ConfigString);
                break;
            case C_PRO_HFO:
            case C_PRO_DO:
            case C_PRO_LUB:
            case C_PRO_FW:
            case C_PRO_MISC:
                IDNumber = ConfigString.ReadInteger(ErrorLine);
                CurrentPRO = new PROServiceTank(Key, IDNumber,ConfigString.GetCurrentLine());
                CurrentPRO->LoadConfigFromFile(ConfigString);
                break;
#endif
            case C_PRO_TANKPRESS:
                IDNumber = ConfigString.ReadInteger(ErrorLine);
                CurrentPRO = new PROTankPressure(IDNumber, NULL, true, ConfigString.GetCurrentLine());
                CurrentPRO->LoadConfigFromFile(ConfigString);
#ifndef ANCONF
                CurrentPRO->SortAnalogInputs();
#endif
                break;
			case C_PRO_TEMP:
                IDNumber = ConfigString.ReadInteger(ErrorLine);
                CurrentPRO = new PROTemperature(IDNumber, NULL, true, ConfigString.GetCurrentLine());
				CurrentPRO->LoadConfigFromFile(ConfigString);
#ifndef ANCONF
                CurrentPRO->SortAnalogInputs();
#endif
                break;
            case C_PRO_LINEPRESS:
                IDNumber = ConfigString.ReadInteger(ErrorLine);
                CurrentPRO = new PROLinePressure((int)IDNumber,ConfigString.GetCurrentLine());
                CurrentPRO->LoadConfigFromFile(ConfigString);
#ifndef ANCONF
                CurrentPRO->SortAnalogInputs();
#endif
                break;
            case C_PRO_ANPRO3:
                {
                    IDNumber = ConfigString.ReadInteger(ErrorLine);
                    AnPro3object *tempPRO = new AnPro3object(IDNumber);
                    tempPRO->LoadConfigFromFile(ConfigString);
                }
                break;
            case C_PRO_SAAB_PROTOCOL:
                {
                    IDNumber = ConfigString.ReadInteger(ErrorLine);
                    SaabProtcol *tempPRO = new SaabProtcol(-1, IDNumber);
                    tempPRO->LoadConfigFromFile(ConfigString);
                }
                break;
            case C_PRO_LEVSWITCH            :
                IDNumber = ConfigString.ReadInteger(ErrorLine);
                CurrentPRO = new PROLevelSwitch(IDNumber);
                CurrentPRO->LoadConfigFromFile(ConfigString);
                break;
            case C_PRO_WATERINGRESS:
                IDNumber = ConfigString.ReadInteger(ErrorLine);
                CurrentPRO = new PROWaterIngress(IDNumber);
                CurrentPRO->LoadConfigFromFile(ConfigString);
                break;
            case C_PRO_VOIDSPACE:
                IDNumber = ConfigString.ReadInteger(ErrorLine);
                CurrentPRO = new PROVoidSpace(IDNumber);
                CurrentPRO->LoadConfigFromFile(ConfigString);
                break;
            case C_PRO_T_PANEL_CONTR:    //must be something wrong if this
            case C_PRO_TPC140:
            case C_PRO_TPC350:
            case C_PRO_TPC196:
                IDNumber = ConfigString.ReadInteger(ErrorLine);
				CurrentPRO = new TPCxObject(IDNumber);
                CurrentPRO->LoadConfigFromFile(ConfigString);
                break;
			case C_PRO_MODBUS_MULTIPLE:
                {
                    ModbusMultiple *tmpPtr = new ModbusMultiple;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_COIL_IN:
                {
                    ModbusCoilIn *tmpPtr = new ModbusCoilIn;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_COIL_OUT:
                {
                    ModbusCoilOut *tmpPtr = new ModbusCoilOut;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_COIL_HIST:
                {
                    ModbusCoilHistory *tmpPtr = new ModbusCoilHistory;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_REG_IN:
                {
                    ModbusRegisterIn *tmpPtr = new ModbusRegisterIn;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
					}
                }
                break;
			case C_PRO_MBUS_WAGO473_RIN  :
                {
                    ModbusWago473RegisterIn *tmpPtr = new ModbusWago473RegisterIn;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MBUS_WAGO479_RIN  :
                {
                    ModbusWago479RegisterIn *tmpPtr = new ModbusWago479RegisterIn;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MBUS_WAGO482_RIN  :
                {
                    ModbusWago482RegisterIn *tmpPtr = new ModbusWago482RegisterIn;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MBUS_WAGO485_RIN  :
                {
                    ModbusWago485RegisterIn *tmpPtr = new ModbusWago485RegisterIn;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MBUS_WAGO487_RIN  :
                {
                    ModbusWago487RegisterIn *tmpPtr = new ModbusWago487RegisterIn;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
					}
                }
                break;
			case C_PRO_MODBUS_REG_OUT:
                {
                    ModbusRegisterOut *tmpPtr = new ModbusRegisterOut;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_REG_HIST:
                {
                    ModbusRegisterHistory *tmpPtr = new ModbusRegisterHistory;
                    NoError = tmpPtr->LoadConfigString(ConfigString);
                    if (!NoError) {
                        delete tmpPtr;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_REG_BIT_IN:
                {
					ModbusRegBitIn *tmpPtr = new ModbusRegBitIn;
					NoError = tmpPtr->LoadConfigString(ConfigString);
					if (!NoError) {
						delete tmpPtr;
						NoError = true; // Non-critical?
					}
				}
				break;
			case C_PRO_MODBUS_REG_BIT_OUT:
				{
					ModbusRegBitOut *tmpPtr = new ModbusRegBitOut;
					NoError = tmpPtr->LoadConfigString(ConfigString);
					if (!NoError) {
						delete tmpPtr;
						NoError = true; // Non-critical?
					}
				}
				break;
			case C_PRO_WATER_HEATER:
				IDNumber = ConfigString.ReadInteger(ErrorLine);
				CurrentPRO = new PROWaterHeater(IDNumber);
				CurrentPRO->LoadConfigFromFile(ConfigString);
#ifndef ANCONF
				CurrentPRO->SortAnalogInputs();
#endif
			}
		}
#ifdef ANWIN
		MainForm->UpdateSplashProgress(5);
#endif
	}while (NoError && (ErrorLine != EOF));
#ifdef ANWIN
	MainForm->UpdateSplashProgress(500,"<b>Sorting objects</b>");
#endif
	sort (PROTank::TankVector.begin(), PROTank::TankVector.end(), PRogramObjectBase::Compare);
	sort (PROCargoTank::AllObjVector.begin(), PROCargoTank::AllObjVector.end(), PRogramObjectBase::Compare);
	sort (PROBallastTank::AllObjVector.begin(), PROBallastTank::AllObjVector.end(), PRogramObjectBase::Compare);

	sort (PROServiceTank::AllObjVector         .begin(), PROServiceTank::AllObjVector         .end(), PRogramObjectBase::Compare);
	sort (PROServiceTank::AllHeavyFuelOilVector.begin(), PROServiceTank::AllHeavyFuelOilVector.end(), PRogramObjectBase::Compare);
	sort (PROServiceTank::AllDieselVector      .begin(), PROServiceTank::AllDieselVector      .end(), PRogramObjectBase::Compare);
	sort (PROServiceTank::AllLubricantsVector  .begin(), PROServiceTank::AllLubricantsVector  .end(), PRogramObjectBase::Compare);
	sort (PROServiceTank::AllFreshWaterVector  .begin(), PROServiceTank::AllFreshWaterVector  .end(), PRogramObjectBase::Compare);
	sort (PROServiceTank::AllMiscVector        .begin(), PROServiceTank::AllMiscVector        .end(), PRogramObjectBase::Compare);
	sort (PROServiceTank::ObjVector            .begin(), PROServiceTank::ObjVector            .end(), PRogramObjectBase::Compare);
	sort (PROServiceTank::HeavyFuelOilVector   .begin(), PROServiceTank::HeavyFuelOilVector   .end(), PRogramObjectBase::Compare);
	sort (PROServiceTank::DieselVector         .begin(), PROServiceTank::DieselVector         .end(), PRogramObjectBase::Compare);
	sort (PROServiceTank::LubricantsVector     .begin(), PROServiceTank::LubricantsVector     .end(), PRogramObjectBase::Compare);
	sort (PROServiceTank::FreshWaterVector     .begin(), PROServiceTank::FreshWaterVector     .end(), PRogramObjectBase::Compare);
	sort (PROServiceTank::MiscVector           .begin(), PROServiceTank::MiscVector           .end(), PRogramObjectBase::Compare);
	sort (PRogramObject::ScratchPageVector     .begin(), PRogramObject::ScratchPageVector     .end(), PRogramObjectBase::Compare);
#ifdef ANWIN
	MainForm->UpdateSplashProgress(500,"<b>Finalizing</b>");
#endif
	LateBinding();
#ifdef ANCONF
	ConfigWarningForm->CheckConfigWarnings(false);
#else
	CreateIOUnits();
	//CreateIOUnits();

#if NETWORK == 1
	if(PROTanksystemUnit::MySelf == NULL)
	{
	  // means it has no entry in project config.
	  // adding this case for networked slave-tcu and tdu
	  new PROTanksystemUnit(CurrentDeviceAddress, CurrentDeviceId);
	}
#endif

	if (!PROAtmReference::PROAtmRefPtr) {
		PROAtmReference::PROAtmRefPtr = new PROAtmReference(false);

	}
#endif
	AnalogInput::CreateIdNum();
    //PRogramObjectBase::CorrectIds();
    PRogramObjectBase::InitMap();
    PROCargoTank::ObjVector             = PRogramObjectBase::GetReadPermissionVector(PROCargoTank::AllObjVector             );
    PROBallastTank::ObjVector           = PRogramObjectBase::GetReadPermissionVector(PROBallastTank::AllObjVector           );
    PROServiceTank::ObjVector           = PRogramObjectBase::GetReadPermissionVector(PROServiceTank::AllObjVector           );
    PROServiceTank::HeavyFuelOilVector  = PRogramObjectBase::GetReadPermissionVector(PROServiceTank::AllHeavyFuelOilVector  );
    PROServiceTank::DieselVector        = PRogramObjectBase::GetReadPermissionVector(PROServiceTank::AllDieselVector        );
    PROServiceTank::LubricantsVector    = PRogramObjectBase::GetReadPermissionVector(PROServiceTank::AllLubricantsVector    );
    PROServiceTank::MiscVector          = PRogramObjectBase::GetReadPermissionVector(PROServiceTank::AllMiscVector          );
    PROServiceTank::FreshWaterVector    = PRogramObjectBase::GetReadPermissionVector(PROServiceTank::AllFreshWaterVector    );
    PROTemperature::ObjVector           = PRogramObjectBase::GetReadPermissionVector(PROTemperature::AllObjVector           );
    PROTankPressure::ObjVector          = PRogramObjectBase::GetReadPermissionVector(PROTankPressure::AllObjVector          );
    PROLinePressure::ObjVector          = PRogramObjectBase::GetReadPermissionVector(PROLinePressure::AllObjVector          );
    PROVoidSpace::ObjVector             = PRogramObjectBase::GetReadPermissionVector(PROVoidSpace::AllObjVector             );
    PROWaterIngress::ObjVector          = PRogramObjectBase::GetReadPermissionVector(PROWaterIngress::AllObjVector          );
    PROLevelSwitch::ObjVector           = PRogramObjectBase::GetReadPermissionVector(PROLevelSwitch::AllObjVector           );
	for (unsigned i = 0; i < PROUser::UsersVector.size(); i++) {
		PROUser::UsersVector[i]->SetReadVectors();
	}
	set<PRogramObjectBase *>::iterator pBIt;
	for (pBIt = PROTanksystemUnit::TanksystemUnitSet.begin(); pBIt != PROTanksystemUnit::TanksystemUnitSet.end(); pBIt++) {
		PROTanksystemUnit *UnitPtr = (PROTanksystemUnit*)*pBIt;
		UnitPtr->PROCargoTankVector             = PRogramObjectBase::GetWritePermissionVector(PROCargoTank::AllObjVector           ,UnitPtr->IDNumber);
		UnitPtr->PROBallastTankVector           = PRogramObjectBase::GetWritePermissionVector(PROBallastTank::AllObjVector         ,UnitPtr->IDNumber);
		UnitPtr->PROServiceTankVector           = PRogramObjectBase::GetWritePermissionVector(PROServiceTank::AllObjVector         ,UnitPtr->IDNumber);
		UnitPtr->PROServiceTankvyFuelOilVector  = PRogramObjectBase::GetWritePermissionVector(PROServiceTank::AllHeavyFuelOilVector,UnitPtr->IDNumber);
		UnitPtr->PROServiceTankselVector        = PRogramObjectBase::GetWritePermissionVector(PROServiceTank::AllDieselVector      ,UnitPtr->IDNumber);
		UnitPtr->PROServiceTankricantsVector    = PRogramObjectBase::GetWritePermissionVector(PROServiceTank::AllLubricantsVector  ,UnitPtr->IDNumber);
		UnitPtr->PROServiceTankcVector          = PRogramObjectBase::GetWritePermissionVector(PROServiceTank::AllMiscVector        ,UnitPtr->IDNumber);
		UnitPtr->PROServiceTankshWaterVector    = PRogramObjectBase::GetWritePermissionVector(PROServiceTank::AllFreshWaterVector  ,UnitPtr->IDNumber);
		UnitPtr->PROTemperatureVector           = PRogramObjectBase::GetWritePermissionVector(PROTemperature::AllObjVector         ,UnitPtr->IDNumber);
		UnitPtr->PROTankPressureVector          = PRogramObjectBase::GetWritePermissionVector(PROTankPressure::AllObjVector        ,UnitPtr->IDNumber);
		UnitPtr->PROLinePressureVector          = PRogramObjectBase::GetWritePermissionVector(PROLinePressure::AllObjVector        ,UnitPtr->IDNumber);
		UnitPtr->PROVoidSpaceVector             = PRogramObjectBase::GetWritePermissionVector(PROVoidSpace::AllObjVector           ,UnitPtr->IDNumber);
		UnitPtr->PROWaterIngressVector          = PRogramObjectBase::GetWritePermissionVector(PROWaterIngress::AllObjVector        ,UnitPtr->IDNumber);
		UnitPtr->PROLevelSwitchVector           = PRogramObjectBase::GetWritePermissionVector(PROLevelSwitch::AllObjVector         ,UnitPtr->IDNumber);
#ifdef ANWIN
		MainForm->UpdateSplashProgress(10);
#endif
	}
	AlarmBasic::SetRWPermissions(); 
	//AlarmBasic::AddToDataBaseTable();      //EHSMark


	return NoError;
}
//---------------------------------------------------------------------------

bool LoadConfigFromFile(char *fileName) {
    bool ReadOK = true;
    TSNConfigString ConfigString(CONFIG_FILE_SIZE );
    if (ConfigString.ReadFile(fileName)) {
        if (LoadConfig(ConfigString)) {
#ifdef ANWIN
            if (PROProjectInfo::IntegratedLoadingComputer) {
                AnsiString FName = fileName;
                FName = FName.SetLength(FName.LastDelimiter(".")) + "LC2";
                if (ConfigString.ReadFile(FName.c_str())) {
                    ReadOK = LCShipData::LoadConfig(ConfigString);
                }else{
                    GiveConfigWarning("LoadCalc Config file not found!");
                }

            }
#endif
        }
    } else {
        ReadOK = false;
        GiveConfigWarning("LoadCalc Config file problem!");
    }
    return (ReadOK);
}
//---------------------------------------------------------------------------

void LoadConfigFromFlash(void) {
//#define SEGGER_DEBUG
#ifdef SEGGER_DEBUG
#include "Demo.c"
    TSNConfigString ConfigString((const char *)ConfigData);
    LoadConfig(ConfigString);
#else
#ifndef WIN32
    U8 *ConfigMemPtr    = NULL;
    U32 Size            = 0;
    U32 SConfigStart    = 0;
    U32 SConfigEnd      = 0;
    U32 SConfigBakStart = 0;
    U32 SConfigBakEnd   = 0;
    bool FlashOK        = false;
    // First, check if it is the main or backup which exist
    if ( GetBlockInfoMX29LV(SectorConfigStart,SectorConfigEnd,(U8**)&ConfigMemPtr, &Size ) ) {
        SConfigStart    = SectorConfigStart;
        SConfigEnd      = SectorConfigEnd;
        SConfigBakStart = SectorConfigBakStart;
        SConfigBakEnd   = SectorConfigBakEnd;
        FlashOK         = true;
    } else if ( GetBlockInfoMX29LV(SectorConfigBakStart,SectorConfigBakEnd, (U8**)&ConfigMemPtr, &Size) ) {
        SConfigStart    = SectorConfigBakStart;
        SConfigEnd      = SectorConfigBakEnd;
        SConfigBakStart = SectorConfigStart;
        SConfigBakEnd   = SectorConfigEnd;
        FlashOK         = true;
    } else {
        GiveConfigWarning((AnsiString)"FATAL ERROR!\n Could not find configuration.\n");
    }
    if ( FlashOK ) {
        TSNConfigString ConfigString((char*)ConfigMemPtr,/*CONFIG_FILE_SIZE*/Size,true);
        LoadConfig(ConfigString);
        SectorConfigStart    = SConfigStart;
        SectorConfigEnd      = SConfigEnd;
        SectorConfigBakStart = SConfigBakStart;
        SectorConfigBakEnd   = SConfigBakEnd;
    }
#endif
#endif
}






