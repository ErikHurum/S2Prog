#pragma once
//---------------------------------------------------------------------------
#ifndef TSNConstantsH
#define TSNConstantsH
#include "LanguageConstants.h"
#define TCU_R1      0
#define TCU_R2      1       // With network controller and 16 MB flash
#define TDU_R1      2
#define TDU_R2      3       // With network controller and 16 MB flash
#define TXU_IS_PC   4       // With network controller and 16 MB flash
#define TXU_IS_PC   4       // With network controller and 16 MB flash
/*
#ifdef S2K
#ifdef CLOCKS_PER_SEC
#undef CLOCKS_PER_SEC
#endif
#define CLOCKS_PER_SEC  1000
#endif
*/

////////////////////////////////////////////////////////////////////////////////
//
//Configuration key
//
////////////////////////////////////////////////////////////////////////////////
#define C_UNDEFINED             0
// Common, used in several objects, Range: 100 -> 199
#define C_ENABLE                100
#define C_DISABLE               101
#define C_ON                    102
#define C_OFF                   103
#define C_OPEN                  104
#define C_CLOSE                 105
#define C_NONE                  106
#define C_SCRATCH_PAGE          107
#define C_VOLATILE              108
#define C_PREVIOUS_ENABLE       109
#define C_PREVIOUS_DISABLE      110

#define C_PRESS_LIM_MBAR        111
#define C_PRESS_LIM_ADJUST      112
#define C_PRESS_LIM_PRESS_VAC   113
#define C_PRESS_LIM_VAP_RET     114
#define C_PRESS_LIM_PO_MODE     115
#define C_PRESS_LIM_IGP_MODE    116

#define C_PRESS_
#define C_XPOS                  200
#define C_YPOS                  201
#define C_ZPOS                  202

#define C_PAGE                  203
#define C_DESCRIPTION           204
#define C_UNSIGNED              205
#define C_SIGNED                206
#define C_RANGE                 207
#define C_BIT_OFFSET            208
#define C_OBJECT_ID             209
#define C_OBJECT_ID_LIST        210
#define C_MY_OBJECT_ID          211
#define C_REF_OBJECT_ID         212
#define C_VALUE_KEY             213
#define C_OFFLINE               214
#define C_ONLINE                215
#define C_DECIMAL_POINT         216
#define C_FLOATING_POINT        217
#define C_FLOATING_POINT_REV    218
#define C_FLOAT_BIG_ENDIAN      219
#define C_FLOAT_LITTLE_ENDIAN   220
#define C_FLOAT_B_END_BYTE_SWAP 221
#define C_FLOAT_L_END_BYTE_SWAP 222
#define C_INT_BIG_ENDIAN        223
#define C_INT_LITTLE_ENDIAN     224
#define C_INT_B_END_BYTE_SWAP   225
#define C_INT_L_END_BYTE_SWAP   226
#define C_DELAY                 227
#define C_RELAXED               228
#define C_TIMEOUT               229
#define C_LOG_PERIOD            230
#define C_LOG_ENTRIES           231
#define C_WARNING               232
#define C_REQUEST_CONFIG        233
#define C_NUMBER_OF_COPIES      234
#define C_REGISTER_STEPS_IN     235
#define C_REGISTER_STEPS_OUT    236
#define C_COIL_STEPS_IN         237
#define C_COIL_STEPS_OUT        238
#define C_OBJECT_ID_IGNORE_LIST 239
#define C_STRING10              240
#define C_STRING20              241
#define C_AUTORESET             242

#define C_OP_MODE_ADJUSTABLE    250
#define C_OP_MODE_PRES_VAC      251
#define C_OP_MODE_VAP_RET       252
#define C_OP_MODE_PO            253
#define C_OP_MODE_IGP           254




#define C_PRO_BASIC             999
// Main PRogramObjects, Range: 1000 -> 1199
#define C_PRO_END               1000
#define C_PRO_START_COMMON      1001
#define C_PRO_END_COMMON        1002
#define C_PRO_START_PRO         1003
#define C_PRO_END_PRO           1004
// The following Constants can not be changed to maintain backward compatibility!
// The range is C_CONFIG_INFO to C_PRO_WOCTRACK
#define C_CONFIG_INFO           1009
#define C_PRO_PROJINFO          1010
#define C_PRO_SYSDATA           1015
#define C_PRO_ATMREFSENS        1020
#define C_PRO_INC               1030
#define C_PRO_DRAFT_SYSTEM      1040
#define C_PRO_DRAFT             1041 // Up to 1049 are reserved for draft
#define C_PRO_TANK              1050
#define C_PRO_CARGO             1051
#define C_PRO_BALLAST           1052
#define C_PRO_HFO               1053
#define C_PRO_DO                1054
#define C_PRO_LUB               1055
#define C_PRO_FW                1056
#define C_PRO_MISC              1057
#define C_PRO_TANK_SUM          1058
#define C_PRO_TANK_EMPTY        1059
#define C_PRO_TANKPRESS         1060
#define C_PRO_TANKPRESS_SUM     1061
#define C_PRO_TANKPRESS_EMPTY   1062
#define C_PRO_TEMP              1070
#define C_PRO_TEMP_SUM          1071
#define C_PRO_TEMP_EMPTY        1072
#define C_PRO_VOIDSPACE         1073

#define C_PRO_LEVSWITCH         1080
#define C_PRO_WATERINGRESS      1100
#define C_PRO_LINEPRESS         1120
#define C_PRO_LINEPRESS_SUM     1121
#define C_PRO_LINEPRESS_EMPTY   1122
#define C_PRO_LOADREPORT        1140
#define C_PRO_TANK_WASH_MACHINE 1141
#define C_PRO_WATER_HEATER      1142
#define C_PRO_WOCTRACK          1143

//Do not use constant 1111
#define C_PRO_TANKSYS_UNIT      1150
#define C_PRO_PRINTER           1151
#define C_PRO_T_PANEL_CONTR     1160
#define C_PRO_TPC140            1161
#define C_PRO_TPC350            1162
#define C_PRO_TPC196            1163
#define C_PRO_CONTROL           1170
#define C_PRO_CTRL_AL_RELAY     1171
#define C_PRO_CTRL_BUZZER       1172
#define C_PRO_CTRL_LIGHT        1173
#define C_PRO_CTRL_HORN         1174
#define C_PRO_CTRL_LAMP         1175
#define C_PRO_ANPRO3            1176
#define C_PRO_MODBUS_COIL_IN2   1183    // Dummy ID as this ID has been used incorrectly in some projects.
#define C_PRO_USER              1190
#define C_PRO_USER_NAME         1191
#define C_PRO_USER_PASSWORD     1192
#define C_PRO_USER_ID_NUMBER    1193
#define C_PRO_NUMBER_OF_HANHELD 1194


// Project Info, Range: 1200 -> 1249
#define C_PROJ_NAME                         1201
#define C_PROJ_NUM_TCU                      1202
#define C_PROJ_NUM_TDU                      1203
#define C_PROJ_TYPE                         1204
#define C_PROJ_TYPE_NAME                    1205
#define C_PROJ_TYPE_NAME2                   1206  
#define C_PROJ_CALLSIGN                     1207  
#define C_PROJ_IMO_NUM                      1208  
#define C_PROJ_LENGTH_BETWEEN_PP            1209  
#define C_PROJ_LENGTH_BETWEEN_MARKS         1210  
#define C_PROJ_TOT_WITH                     1211  
#define C_PROJ_LOADING_COMPUTER             1212  
#define C_PROJ_LOADRATE_LOAD_TIME           1213  
#define C_PROJ_IS_INLAND_VESSEL             1214  
#define C_PROJ_IS_CUSTODY_TRANSFER_SYS      1215  
#define C_PROJ_FORCE_MAX_ULLAGE             1216  
#define C_PROJ_AUTO_ALARM_ACKN              1217  
#define C_PROJ_ALARMSYS_DELAY               1218  
#define C_PROJ_IS_HSH_VESSEL                1219  
#define C_PROJ_IP_ADDRESS                   1220  
#define C_PROJ_IP_ADDRESS_GATEWAY           1221  
#define C_PROJ_IP_ADDRESS_TCU_MASTER        1222  
#define C_PROJ_IP_ADDRESS_TCU_SLAVE_START   1223  
#define C_PROJ_IP_ADDRESS_TCU_SLAVE_END     1224  
#define C_PROJ_IP_ADDRESS_TDU_START         1225  
#define C_PROJ_IP_ADDRESS_TDU_END           1226  
#define C_PROJ_IP_ADDRESS_PC_START          1227  
#define C_PROJ_IP_ADDRESS_PC_END            1228  
#define C_PROJ_IP_TCP_SERVER_PORT           1229  
#define C_PROJ_IP_UDP_NET_PORT              1230
//#define C_PROJ_IP_TCP_FLASH_PORT          1231


#define C_ALARM_SETTINGS_PIN_LOCK		1231
#define C_NOISE_LIM_CARGO_B             1232
#define C_NOISE_LIM_CARGO_U             1233
#define C_NOISE_LIM_BALLAST_B           1234
#define C_NOISE_LIM_BALLAST_U           1235
#define C_NOISE_LIM_SERVICE_B           1236
#define C_NOISE_LIM_SERVICE_U           1237
#define C_NOISE_LIM_RADAR               1238
#define C_NOISE_LIM_VOIDSPACE           1239

#define C_L_ENGLISH                     1250
#define C_L_NORWEGIAN                   1251
#define C_L_GERMAN                      1252
#define C_L_DUTCH                       1253
#define C_L_FRENCH                      1254
#define C_L_SPANISH                     1255
#define C_L_PORTUGUESE                  1256

#define C_DEC_P_VOLUME                  1260
#define C_DEC_P_WEIGHT                  1261



// PRO common, Range: 1300 -> 1349
#define C_PRO_NAME             1301
#define C_PRO_LONGNAME         1302
#define C_PRO_TAGNAME          1303
#define C_PRO_SORTNO           1304
#define C_PRO_READ_PERMISSION  1305
#define C_PRO_WRITE_PERMISSION 1306
#define C_PRO_ID_NUMBER        1307
// Control, Range: 1350 -> 1399
#define C_PROLIST_START         1351
#define C_PROLIST_TABLE         1352
#define C_PROLIST_END           1353

#define C_COMMON_TEMPERATURE    1360
#define C_COMMON_PRESSURE       1361

#define C_D_BOT_ULL_REF         1380
#define C_D_BOT_ULL_REF2        1381
#define C_D_BOT_MAN_MSR         1382
#define C_D_BOT_MAN_MSR2        1383
#define C_D_SNS_MID             1384
#define C_D_SNS_MID2            1385
#define C_D_SNS_CL              1386
#define C_D_SNS_CL2             1387
#define C_D_MAN_MSR_MID         1388
#define C_D_MAN_MSR_MID2        1390
#define C_D_MAN_MSR_CL          1391
#define C_D_MAN_MSR_CL2         1392
#define C_D_FC_MID              1393
#define C_D_FC_MID2             1394
#define C_D_FC_CL               1395
#define C_D_FC_CL2              1396
#define C_D_L_MAN_MSR_SNS       1397
#define C_D_L_MAN_MSR_SNS2      1398
#define C_D_T_MAN_MSR_SNS       1399
#define C_D_T_MAN_MSR_SNS2      1400
#define C_D_L_FC_SNS            1401
#define C_D_L_FC_SNS2           1402
#define C_D_T_FC_SNS            1403
#define C_D_T_FC_SNS2           1404
#define C_D_V_MAN_MSR_SNS       1405
#define C_D_V_MAN_MSR_SNS2      1406
#define C_D_V_ULL_REF_TO_UTI    1407

#define C_D_L_SENSOR_TO_RADAR   1408
#define C_D_T_SENSOR_TO_RADAR   1409
#define C_D_V_SENSOR_TO_RADAR   1410
#define C_MIN_DNS_DIST          1411
#define C_REDUNDANCY            1412
#define C_ADJUST_LEVEL_OFFSET   1413
#define C_ADJUST_LEVEL_OFFSET1  1418
#define C_ADJUST_TABLE_OFFSET   1419
#define C_ADJUST_VOLUME_OFFSET  1420
#define C_ADJUST_VOLUME_OFFSET1 1421
#define C_VOLUME_CORR_FACTOR    1422
#define C_GLOBAL_REFSYS         1423
#define C_USE_CF_TAB            1424
#define C_DATA_FROM_OTHER       1425
#define C_RADAR_THRESHOLD       1426
#define C_T_TABLEOFFSET         1427
#define C_T_ULLAGE_VOL_TABLE    1428
#define C_T_LEVEL_VOL_TABLE     1429
#define C_T_SOUNDING_TABLE      1430
#define C_T_COF_TABLE           1431
#define C_T_COG_TABLE           1432
#define C_T_VCORR_TABLE_TRIM    1433
#define C_T_VCORR_TABLE_LIST    1434
#define C_T_VCORR_TABLE_TEMP    1435
#define C_T_DENSITY_CORR_TABLE  1436
#define C_T_TABLE_START         1437
#define C_T_TABLE_END           1438
#define C_T_TABLE_OBJ_END       1441
#define C_T_P_AT_SENSOR         1442
#define C_T_P_AT_CF             1443
#define C_T_P_AT_REFPT          1444
#define C_T_CORRECTION_ENTRIES  1445
#define C_T_CORRECTION_FACTOR   1446
#define C_T_TEMP_WINDOW_COUNT   1447
#define C_T_TEMP_WINDOW_LIMIT   1448

#define C_CARGO_TYPE            1450
#define C_PRO_USER_CARGO_TYPE   1451  // Do not change for backward compatibility
#define C_TANK_CARGOTYPE        1452
#define C_CT_CARGO_TYPE_KEY     1453
#define C_CT_BASIC_CARGO_TYPE   1454
#define C_CT_END                1455
#define C_CT_OD1                1456
#define C_CT_OD2                1457
#define C_CT_REFTEMP1           1458
#define C_CT_REFTEMP2           1459
#define C_CT_COEFF              1460
#define C_CT_USEMEAS_DENS       1461
#define C_CT_COLOUR             1462
#define C_CT_NAME               1463
#define C_CT_IS_DEFINED         1464
#define C_CT_HIGH_TEMP          1465
#define C_CT_LOW_TEMP           1466
#define C_CT_HIGH_TEMP_ENABLE   1467
#define C_CT_LOW_TEMP_ENABLE    1468
#define C_CT_MOLMASS            1469
#define C_CT_VISCOSITY          1470
#define C_CT_DB_IDNUMBER        1471

//////////////////////////////////
// Water ingress  1480 -1499
#define C_WIS_OVERIDE_LOC       1480
#define C_WIS_HAS_PROT          1481
#define C_WIS_HAS_NO_PROT       1482


// Inclinometer, Range: 1500 -> 1549
#define C_INC_MOUNTED          1501
#define C_INC_FORWARD          1502
#define C_INC_AFT              1503
#define C_INC_PORT             1504
#define C_INC_STARBOARD        1505

// AtmReference, Range: 1550 -> 1599
#define C_ATM_ON_TCU           1551
#define C_ATM_USEMANUAL        1552
#define C_ATM_NOT_USEMANUAL    1553
#define C_ATM_MAN_PRESS        1554

// Draft, Range: 1600 -> 1699
#define C_DRAFT_END            1600
#define C_DRAFT_DF             1611
#define C_DRAFT_DP             1612
#define C_DRAFT_DS             1613
#define C_DRAFT_DA             1614
#define C_DRAFT_DAP            1615
#define C_DRAFT_DAS            1616
#define C_DRAFT_DFP            1617
#define C_DRAFT_DFS            1618
//#define C_DRAFT_GLOBAL_REF     1650 // C_USE_GLOBAL_REF

#define C_D_L_MARK             1651
#define C_D_T_MARK             1652
#define C_D_L_PERP             1653
#define C_D_T_PERP             1654
#define C_DRAFT_OFFSET         1655
#define C_D_PERP_MID           1657
#define C_D_MARK_MID           1658

#define C_MAX_SUMMER_DRAFT     1659
#define C_D_L_MARK2            1660
#define C_D_T_MARK2            1661
#define C_D_MARK_MID2          1662

// TPCxObject, Range: 1700 -> 1799
// #define C_TPC_END              1700
#define C_TPC_START_COMMON     1701
#define C_TPC_END_COMMON       1702
#define C_TPC_TYPE             1710
#define C_TPC_140              1711
#define C_TPC_350              1712
#define C_TPC_196              1713
#define C_TPC_PRI_ADDR         1720
#define C_TPC_SEC_ADDR         1721
#define C_TCU_ONE_PROPTR       1722
#define C_TPC_WINDOW           1730
#define C_TPC_END_WINDOW       1731
#define C_TPC_UPPER_DISP       1732
#define C_TPC_MAIN_DISP        1733
#define C_TPC_MAIN_GRAPH       1734
#define C_TPC_TOP_DISP               1735
#define C_TPC_BOTTOM_DISP            1736
#define C_TPC_WINDOW_PRO_ID    1740
#define C_TPC_ALARM_WINDOW     1750

// Config info, Range: 1800 -> 1899
#define C_CONFIG_VERSION       1801
#define C_CONFIG_PROD_NO       1802
#define C_CONFIG_NEW_FUNC      1803
#define C_CONFIG_BUG_FIX       1804
#define C_CONFIG_COMPATI_NO    1805
#define C_CONFIG_DATE          1810
#define C_CONFIG_DAY           1811
#define C_CONFIG_MONTH         1812
#define C_CONFIG_YEAR          1813
#define C_CONFIG_DATA_REV      1820
#define C_CONFIG_REV_PERSON    1821
#define C_CONFIG_REV_TEXT      1822
#define C_CONFIG_CAN_WRITE     1823

#define C_HIGH_CARGO_NO        1850
#define C_HIGH_TANK_NO         1851
#define C_HIGH_TEMP_NO         1852
#define C_HIGH_TPRESS_NO       1853
#define C_HIGH_WINGRESS_NO     1854

// Ctrl, Range: 1900 -> 1999
//C_PRO_CTRL_AL_RELAY
#define C_CTRL_END             1900
#define C_CTRL_START_COMMON    1901
#define C_CTRL_END_COMMON      1902
#define C_CTRL_ALTERNATIVE     1910
#define C_CTRL_ALT_ALL         1911
#define C_CTRL_ALT_AL_TYPES    1912
#define C_CTRL_ALT_PRO_LIST    1913
#define C_CTRL_ALT_TYPE_PRO    1914

#define C_CTRL_AL_TYPE         1920

#define C_CTRL_NORMAL_STATE    1950
#define C_CTRL_NS_POWERED      1951
#define C_CTRL_NS_POWERED2     1952
#define C_CTRL_NS_UNPOWERED    1953
#define C_CTRL_NS_UNPOWERED2   1954
#define C_CTRL_AL_DELAY        1960
#define C_CTRL_DEACTIVATE      1970
#define C_CTRL_DE_ACKNOW       1971
#define C_CTRL_DE_SILENCE      1972
#define C_CTRL_DE_IDLE         1973
#define C_CTRL_DE_VALUE        1974
#define C_CTRL_DE_VAL_ENABLED  1975

#define C_CTRL_PULSE_WIDTH     1976


// IOComponent, Range: 2000 -> 2099
#define C_IO_COMPONENT         2000
#define C_IOC_ANALOG_IN        2010
#define C_IOC_ANALOG_OUT       2020
#define C_IOC_DIGITAL_IN       2030
#define C_IOC_DIGITAL_OUT      2040
#define C_TCU_ADDRESS          2053
#define C_TCU_PORT             2054
#define C_IO_TYPE              2055
#define C_IO_ADDRESS           2056
#define C_IO_CHANNEL           2057
#define C_ADCARD_CH            2058
#define C_TCU_PORT_NO          2059
#define C_IO_NONE              2070
#define C_IO_AN_ZBANA          2071
#define C_IO_AN_ZB485          2072
#define C_IO_AN_ZBHART         2073
#define C_IO_MODBUS            2074

#define C_SC_TYPE              2080
#define C_SC_ADCARD            2081
#define C_SC_W_INGRESS         2082
#define C_SC_RADAR             2083

// Analog input types, Range: 2100 -> 2199
#define C_AI_P906_0110          2110    // Pressure & Temp
#define C_AI_P906_0111          2111    // Pressure & Temp
#define C_AI_ATM_N_Ex           2120    // Pressure
#define C_AI_ATM_Ex             2121    // Pressure
#define C_AI_ATM_Ex_H           2122    // Pressure
#define C_AI_ATM_N_Ex_0_1       2123    // Pressure
#define C_AI_APT500         	2124    // Pressure
#define C_AI_SPT900	         	2125    // Pressure
#define C_AI_Gen_4_20mA         2130    // Pressure
#define C_AI_DIFF_PRESSURE_mA   2131    // Pressure
#define C_AI_1728               2132    // Pressure
#define C_AI_Radar_4_20mA       2135    // Radar
#define C_AI_Radar_Hart         2140    // Radar via Wago, Hart
#define C_AI_Float_4_20mA       2141    // HSH float
#define C_AI_Pt100              2142    // Temp
#define C_AI_Pt1000             2143    // Temp
#define C_AI_TEMP_mA            2150    // Temp
#define C_AI_TEMP_AD590         2152    // Temp
#define C_AI_LeSw_ADCard        2153    // Level switch
#define C_AI_LeSw_Valcom        2154    // Level switch
#define C_AI_LeSw_API           2155    // Level switch
#define C_AI_LeSw_Vega          2156    // Level switch
#define C_AI_LeSw_Vega62        2160    // Level switch
#define C_AI_LeSw_Vega64        2161    // Level switch
#define C_AI_LeSw_HS            2162    // Level switch
#define C_AI_LeSw_mA            2163    // Level switch
#define C_AI_INCLINOMETER       2164    // Inclinometer
#define C_AI_INC1_N2            2165
#define C_AI_INC2_N2            2166
#define C_AI_INC1_MACRON        2167
#define C_AI_INC2_MACRON        2168
//
#define C_AI_COIL_IN            2170
#define C_AI_MetriTape          2171
#define C_AI_HSH_LNG_Float      2172
#define C_AI_AirPurge           2173
#define C_AI_AirPurge2          2174
#define C_AI_WashTrackSensor    2175
#define C_AI_WashTrackSensor2   2176
#define C_AI_MB_Press_mA        2177
#define C_AI_MB_Press_0_20mA    2178
#define C_AI_MB_Press_4_20mA    2179
#define C_AI_MB_DiffPre_mA      2180
#define C_AI_MB_DiffPre_0_20mA  2181
#define C_AI_MB_DiffPre_4_20mA  2182
#define C_AI_WATERINGRESS       2183    // Water ingress
#define C_AI_WATERINGR_MAIN     2184    // Water ingress main
#define C_AI_WATERINGR_PRE      2185    // Water ingress pre
#define C_AI_WATERINGR_TEMP     2186    // Water ingress Temp
#define C_AI_WATERINGR_TEMP_M   2187    // Water ingress Temp
#define C_AI_WATERINGR_TEMP_P   2188    // Water ingress Temp
#define C_AI_GODA_RADAR         2189    // Goda radar
#define C_AI_VOLTAGE            2190
#define C_AI_FUSE               2191

// Analog input variables, Range: 2200 -> 2299
#define C_AI_END                2200
#define C_AI_START_COMMON       2201
#define C_AI_END_COMMON         2202

#define C_AI_TYPE               2207
#define C_AI_SERIALNO           2208
#define C_AI_DISTANCE           2209
#define C_AI_GAIN               2210
#define C_AI_OFFSET             2211
#define C_AI_MIN_RANGE          2212
#define C_AI_MAX_RANGE          2213
#define C_AI_CABLE_LENGTH_SHIP  2214
#define C_AI_CABLE_LENGTH_SENS2 2215
#define C_AI_CABLE_LENGTH_SENS  2216
#define C_AI_CABLE_RES_SHIP     2217
#define C_AI_CABLE_RES_SENS     2218
#define C_AI_CABLE_RES_MSRD     2219

#define C_AI_NO_SHORT_CIRC_AL   2220
#define C_AI_NO_SHORT_CIRC_AL2  2221
#define C_AI_TANK_PRESS         2222
#define C_AI_NL1                2223
#define C_AI_NL2                2224
#define C_AI_TZS                2225
#define C_AI_TSS                2226

#define C_AI_CAL_DATA           2229
#define C_AI_FRO                2230
#define C_AI_G1                 2231
#define C_AI_G2                 2232
#define C_AI_G3                 2233

#define C_AI_RESISTANCE_MIN     2234
#define C_AI_RESISTANCE_MAX     2235
#define C_AI_RESISTANCE_CONST   2236
#define C_AI_VOLTAGE_CONST      2237

#define C_AI_EEPROM_GAIN        2238
#define C_AI_EEPROM_OFFSET      2239

#define C_AI_MA_LEV_SWITCH_ON   2240
#define C_AI_MA_LEV_SWITCH_OFF  2241
#define C_AI_MA_LEV_SWITCH_WIN  2242
#define C_AI_MA_LEV_SWITCH_MAX  2243


#define C_MOD_CONFIG            2251
#define C_MOD_SYSTEM            2252
#define C_MOD_USER              2253

#define C_AI_LOC_NOT_DEFINED    2270
#define C_AI_LOC_BOTTOM         2271
#define C_AI_LOC_MIDDLE         2272
#define C_AI_LOC_UPPER          2273
#define C_AI_LOC_VAPOUR         2274
#define C_AI_LOC_PUMP_ROOM      2275
#define C_AI_LOC_ENGINE_ROOM    2276
#define C_AI_LOC_SYSTEM         2277
#define C_AI_LOC_WI_MAIN        2278
#define C_AI_LOC_WI_PRE         2279
#define C_AI_LOC_INC_TRIM       2280
#define C_AI_LOC_INC_LIST       2281
#define C_AI_LOC_DECK           2282
#define C_AI_LOC_LINE           2283
#define C_AI_LOC_ATM            2284
#define C_AI_LOC_POWER1         2285
#define C_AI_LOC_POWER2         2286
#define C_AI_LOC_POWER_AC       2287
#define C_AI_LOC_POWER_DC       2288
#define C_AI_LOC_AC_OK          2289
#define C_AI_LOC_FUSES          2290
#define C_AI_LOC_TRIM           2291
#define C_AI_LOC_LIST           2292
#define C_AI_LOC_TANK_CLEAN     2293

#define C_AI_LOC_TEMP           2300
#define C_AI_LOC_TEMP1          2301
#define C_AI_LOC_TEMP2          2302
#define C_AI_LOC_TEMP3          2303
#define C_AI_LOC_TEMP4          2304
#define C_AI_LOC_TEMP5          2305
#define C_AI_LOC_TEMP6          2306
#define C_AI_LOC_TEMP7          2307
#define C_AI_LOC_TEMP8          2308
#define C_AI_LOC_TEMP9          2309
#define C_AI_LOC_TEMP10         2310

#define C_AI_LOC_TEMP_IN        2311
#define C_AI_LOC_TEMP_OUT       2312

#define C_AI_LOC_REDUNDANCY1     2351
#define C_AI_LOC_REDUNDANCY2     2352
#define C_AI_LOC_REDUNDANCY3     2353

// Modbus, Range: 2400 -> 2499
#define C_MODBUS_START_COMMON    2400
#define C_MODBUS_END             2401
#define C_MODBUS_END_COMMON      2402
#define C_MODBUS_ADDRESS         2403
#define C_MODBUS_CHANNEL         2404

#define C_MODBUS_VALUE_KEY       2405
#define C_MODBUS_PRO_ID          2406
#define C_MODBUS_PRO_ID_END      2407

#define C_MODBUS_AVERAGE         2409
#define C_MODBUS_MIN             2410
#define C_MODBUS_MAX             2411
#define C_MODBUS_SUM             2412
#define C_MODBUS_AND             2413
#define C_MODBUS_OR              2414
#define C_MODBUS_XOR             2415
#define C_MODBUS_NAND            2416
#define C_MODBUS_DATABITS        2417

#define C_MODBUS_CMD_INP_STAT    2418
#define C_MODBUS_CMD_INP_REG     2419

// Digital input types, Range: 2500 -> 2599

// Digital input variables, Range: 2600 -> 2699
#define C_DI_END               2600
#define C_DI_START_COMMON      2601
#define C_DI_END_COMMON        2602

#define C_DI_TYPE              2610
#define C_DI_SERIALNO          2611

#define C_DI_LOC_NOT_DEFINED     2680


#define C_PRO_MODBUS_UNIT           2800
#define C_PRO_MODBUS_OBJ            2801
#define C_PRO_MODBUS_REG            2802
#define C_PRO_MODBUS_REG_OUT        2803
#define C_PRO_MODBUS_REG_IN         2804
#define C_PRO_MODBUS_REG_HIST       2805
#define C_PRO_MODBUS_COIL           2806
#define C_PRO_MODBUS_COIL_OUT       2807
#define C_PRO_MODBUS_COIL_IN        2808
#define C_PRO_MODBUS_COIL_HIST      2809
#define C_PRO_MODBUS_REG_BIT_IN     2810
#define C_PRO_MODBUS_REG_BIT_OUT    2811
#define C_PRO_MODBUS_STRING_OUT     2812

#define C_PRO_MODBUS_MULTIPLE       2820


#define C_PRO_MBUS_WAGO473_RIN      2850
#define C_PRO_MBUS_WAGO479_RIN      2851
#define C_PRO_MBUS_WAGO482_RIN      2852
#define C_PRO_MBUS_WAGO485_RIN      2853
#define C_PRO_MBUS_WAGO487_RIN      2854


#define C_PRO_MULTI_MODBUS          2890

// Digital output types
// Range: 2700 -> 2799

// Digital output variables
// Range: 2800 -> 2899


// Alarm, Range: 3000 -> 3799
#define C_AL_END               3001
#define C_AL_LIMIT             3002
#define C_AL_LOCKED            3003
#define C_AL_NOT_LOCKED        3004
#define C_AL_NOT_LOCKED2       3005
#define C_AL_VISIBLE           3006
#define C_AL_DESCRIPTION       3007
#define C_AL_TCP_DESCRIPTION   3008

#define ID_AL_BASIC                  3009
#define ID_AL_OVERFILL               3010
#define ID_AL_HIGH_LEVEL             3011
#define ID_AL_LOW_LEVEL              3012
#define ID_AL_LOWLOW_LEVEL           3013
#define ID_AL_HIGH_TEMP              3014
#define ID_AL_LOW_TEMP               3015
#define ID_AL_HIGH_BOT_TEMP          3016
#define ID_AL_LOW_BOT_TEMP           3017
#define ID_AL_LEVEL_DIFFERENCE       3018
#define ID_AL_SNS_LEVEL_DIFFERENCE   3020
#define ID_AL_MAIN_WATERINGR         3021
#define ID_AL_PRE_WATERINGR          3022
#define ID_AL_LOW_T_PRESS            3023
#define ID_AL_HIGH_T_PRESS           3024
#define ID_AL_LOW_PRESS_VAC          3025
#define ID_AL_HIGH_PRESS_VAC         3026
#define ID_AL_LOW_INERT_GAS_PRESS    3027
#define ID_AL_HIGH_INERT_GAS_PRESS   3028
#define ID_AL_LOW_VAPOUR_RETURN      3029
#define ID_AL_HIGH_VAPOUR_RETURN     3030
#define ID_AL_LOW_LOADRATE           3031
#define ID_AL_HIGH_LOADRATE          3032
#define ID_AL_LEVEL_CHANGE           3033
#define ID_AL_DENS_DIFF              3034
#define ID_AL_LOW_LINE_PRESS         3035
#define ID_AL_HIGH_LINE_PRESS        3036
#define ID_AL_HIGHHIGH_LINE_PRESS    3037
#define ID_AL_LOW_VOLTAGE            3038       // Config Rev0 support 
#define ID_AL_LOW_VOLTAGE_1          3039
#define ID_AL_LOW_VOLTAGE_2          3040
#define ID_AL_HI_VOLTAGE             3041
#define ID_AL_HI_VOLTAGE_1           3042
#define ID_AL_HI_VOLTAGE_2           3043
#define ID_AL_X_LOW_T_PRESS1         3044
#define ID_AL_X_HIGH_T_PRESS1        3045
#define ID_AL_X_LOW_T_PRESS2         3046
#define ID_AL_X_HIGH_T_PRESS2        3047
#define ID_AL_VOIDSPACE              3048
#define ID_AL_WATER_DETECT           3049
#define ID_AL_FUSE                   3050
#define ID_AL_AC_VOLTAGE             3051
#define ID_AL_TWM_LOW_SPEED          3052 
#define ID_AL_TWM_ELAPSED_TIME       3053
// HW Alarms  Range 3200 -> 3399
#define ID_AL_SNS_OPEN_LOOP          3210
#define ID_AL_SNS_SHORT_CIRCUIT      3211
#define ID_AL_ATM_OUT_OF_RANGE       3212
#define ID_AL_SNS_ERROR              3213
#define ID_AL_SNS_CONV_ERROR         3214
#define ID_AL_SNS_CONCAL_ERROR       3215
#define ID_AL_SNS_HART_COM_ERROR     3216
#define ID_AL_SNS_HART_OPEN_LOOP     3217
#define ID_AL_SNS_HART_SHORT_CIRCUIT 3218
#define ID_AL_SNS_AIR_PURGE_FAILURE  3219
#define ID_AL_CRITICAL_COM_ERR       3230
#define ID_AL_IO_COM_ERROR           3231
#define ID_AL_SC_COM_ERROR           3232
#define ID_AL_MODBUS_COM_ERROR       3233
#define ID_AL_MODBUS_INPUT_STATUS    3234
#define ID_AL_MODBUS_INPUT_STATUS2   3235
#define ID_AL_TDU_COM_ERROR          3236
#define ID_AL_LEVEL_SWITCH           3237
#define ID_AL_LSWITCH_FAILURE        3238
#define ID_AL_LSWITCH_TEST           3239
#define ID_AL_LSWITCH_LIGHT          3240
#define ID_AL_LSWITCH_DEAD           3241
#define ID_AL_INCLINOMETER           3242

// Alarm Limit type   Range 3500 -> 3599
#define AL_LIM_VOLPERCENT           3510
#define AL_LIM_LEVEL                3511
#define AL_LIM_VOLUME               3512
#define AL_LIM_WEIGHT               3513
#define AL_LIM_ULLAGE               3514

// Alarm Limits   Range 3600 -> 3699
#define AL_LIM_OVERFILL             3610
#define AL_LIM_HIGHLEVEL            3611
#define AL_LIM_LOWLEVEL             3612
#define AL_LIM_LOWLOW_LEVEL         3613
#define AL_LIM_HIGHTEMP             3614
#define AL_LIM_LOWTEMP              3615
#define AL_LIM_HIGHTANK_PRESS       3616
#define AL_LIM_LOWTANK_PRESS        3617
#define AL_LIM_HIGHVAPOUR_RET       3618
#define AL_LIM_LOWVAPOUR_RET        3619
#define AL_LIM_HIGHHIGHLINE_PRESS   3620
#define AL_LIM_HIGHLINE_PRESS       3621
#define AL_LIM_LOWLINE_PRESS        3622
#define AL_LIM_HIGH_PV_PRESS        3623
#define AL_LIM_HIGH_PV_PRESS2       3624
#define AL_LIM_LOW_PV_PRESS         3625
#define AL_LIM_LOW_PV_PRESS2        3626
#define AL_LIM_LOW_PV_PRESS3        3627
#define AL_LIM_HIGH_IG_PRESS        3628
#define AL_LIM_LOW_IG_PRESS         3629
#define AL_LIM_X_HI_TNK_PRESS1      3630
#define AL_LIM_X_LO_TNK_PRESS1      3631
#define AL_LIM_X_HI_TNK_PRESS2      3632
#define AL_LIM_X_LO_TNK_PRESS2      3633
#define AL_LIM_HAS_HI_TNK_PR1       3634
#define AL_LIM_HAS_LO_TNK_PR1       3635
#define AL_LIM_HAS_HI_TNK_PR2       3636
#define AL_LIM_HAS_LO_TNK_PR2       3637
#define AL_LIM_HAS_LOLO_LEVEL       3638
#define AL_LIM_VOIDSPACE            3639
#define AL_LIM_LEVELDIFF            3640
#define AL_LOCK_OVERFILL            3641
#define AL_LOCK_HIGHLEVEL           3642
#define AL_LOCK_LOWLEVEL            3643
#define AL_LOCK_LOWLOWLEVEL         3644
#define AL_LOCK_HIGHTEMP            3645
#define AL_LOCK_LOWTEMP             3646
#define AL_LOCK_HIGHTANK_PRESS      3647
#define AL_LOCK_LOWTANK_PRESS       3648
#define AL_LOCK_HIGH_IGP            3649
#define AL_LOCK_LOW_IGP             3650
#define AL_LOCK_HIGHVAPOUR_RET      3651
#define AL_LOCK_LOWVAPOUR_RET       3652
#define AL_LOCK_HI_PO_MODE_PRESS    3653
#define AL_LOCK_LO_PO_MODE_PRESS    3654
#define AL_LOCK_HIGHLINE_PRESS      3655
#define AL_LOCK_LOWLINE_PRESS       3656

#define AL_UNLOCK_OVERFILL          3657
#define AL_UNLOCK_HIGHLEVEL         3658
#define AL_UNLOCK_LOWLEVEL          3659
#define AL_UNLOCK_LOWLOWLEVEL       3660
#define AL_UNLOCK_HIGHTEMP          3661
#define AL_UNLOCK_LOWTEMP           3662
#define AL_UNLOCK_HIGHTANK_PRESS    3663
#define AL_UNLOCK_LOWTANK_PRESS     3664
#define AL_UNLOCK_HIGH_IGP          3665
#define AL_UNLOCK_LOW_IGP           3666
#define AL_UNLOCK_HIGHVAPOUR_RET    3667
#define AL_UNLOCK_LOWVAPOUR_RET     3668
#define AL_UNLOCK_HI_PO_MODE_PRESS  3669
#define AL_UNLOCK_LO_PO_MODE_PRESS  3670
#define AL_UNLOCK_HIGHLINE_PRESS    3671
#define AL_UNLOCK_LOWLINE_PRESS     3672


#define AL_DESCRIPTION              3657
#define AL_TCP_DESCRIPTION          3658


// Status on PRogramObject: Range 3900 -> 3999
#define ST_NONE                3900
#define ST_OK                  3901
#define ST_LOADCALC                 3902
#define ST_WARNING                  3903
#define ST_ALARM                    3904
#define ST_ERROR                    3905

// FREE: Range 4000 -> 4999
#define C_PRO_SAAB_PROTOCOL         4000
#define C_SAAB_EXPORT_LPRESS        4001
#define C_SAAB_EXPORT_TPRESS        4002
#define C_SAAB_EXPORT_ATM_PRESS     4003
#define C_SAAB_EXPORT_TEMP          4004

#define C_ANPRO3_VALDEF_END         4101
#define C_ANPRO3_VALDEF_END2        4102
#define C_ANPRO3_CHECKSUM           4103
#define C_ANPRO3_REQUEST            4104
#define C_ANPRO3_SEPARATOR          4105
#define C_ANPRO3_INC_HW_STATUS      4106
#define C_ANPRO3_INC_ALARM          4107
#define C_ANPRO3_SYNC_STR           4108
//#define C_ANPRO3_DESCRIPTION      4109
#define C_ANPRO3_VAL_ERR_ACT        4110
#define C_ANPRO3_CLEAR_RX_BUF       4111
#define C_ANPRO3_SOALL_EXTRA_SPC    4112
#define C_ANPRO3_DELAY              4113
#define C_ANPRO3_SEND_ALARMS_ONLY   4114
#define C_ANPRO3_NEMA               4115

// Physical Units   4500 -
#define C_UNIT_LENGTH           4562
#define C_UNIT_VOLUME           4563
#define C_UNIT_WEIGHT           4564
#define C_UNIT_LOADRATE         4565
#define C_UNIT_TEMP             4566
#define C_UNIT_PRESSURE1        4567
#define C_UNIT_PRESSURE2        4568
#define C_UNIT_PRESSURE3        4569
#define C_UNIT_DENSITY          4570
#define C_UNIT_ANGLE            4571
#define C_UNIT_DNS_COEFF        4572
#define C_UNIT_FREE_SURF        4573
#define C_UNIT_MOMENT           4574
#define C_UNIT_IMMERSION        4575
#define C_UNIT_GZ_AREA          4576
#define C_UNIT_PERCENT          4577
#define C_UNIT_CURRENT          4578
#define C_UNIT_VOLTAGE          4579
#define C_UNIT_FREQUENCY        4580
#define C_UNIT_TIME             4581
#define C_UNIT_MSECOND          4582
#define C_UNIT_SECOND           4583
#define C_UNIT_MINUTE           4584
#define C_UNIT_HOUR             4585
#define C_UNIT_DAY              4586
#define C_UNIT_MOLMASS          4587

#define C_U_METERH2O            (4600+U_METERH2O     )
#define C_U_MMH2O               (4600+U_MMH2O        )
#define C_U_MBAR                (4600+U_MBAR         )
#define C_U_BAR                 (4600+U_BAR          )
#define C_U_PSI                 (4600+U_PSI          )
#define C_U_KPA                 (4600+U_KPA          )
#define C_U_INCH_H2O            (4600+U_INCH_H2O     )
#define C_U_INCH_HG             (4600+U_INCH_HG      )


#define C_U_METER               (4600+U_METER        )
#define C_U_FEET                (4600+U_FEET         )
#define C_U_DEC_FEET            (4600+U_DECIMAL_FEET )


#define C_U_METER3              (4600+U_METER3       )
#define C_U_LITER               (4600+U_LITER        )
#define C_U_USGALLON            (4600+U_USGALLON     )
#define C_U_USBARRELS           (4600+U_USBARRELS    )






// TDU windows: Range 7000 -> 7999
#define C_TDU_WIN_END           7000
#define C_TDU_CURRENT_WIN       7001
#define C_TDU_CURRENT_SYSWIN    7002
//#define C_TDU_END_COMMON      7003
#define C_TDU_SYSTEM_WIN        7010
#define C_TDU_CARGO_WIN         7020
#define C_TDU_BALLAST_WIN       7021
#define C_TDU_SERVICE_WIN       7022
#define C_TDU_TANKPRESS_WIN     7023
#define C_TDU_LINEPRESS_WIN     7024
#define C_TDU_TEMP_WIN          7026
#define C_TDU_TEMP_WIN2         7027
#define C_TDU_LEVELSWITCH_WIN   7028
#define C_TDU_OVERFILL_WIN      7029
#define C_TDU_BILGE_WIN         7031
#define C_TDU_WATERINGR_WIN     7032
#define C_TDU_VOIDSPACE_WIN     7033

#define C_TDU_VALUE_TAB         7101
#define C_TDU_BACK_COLOR        7102
#define C_TDU_TEXT_COLOR        7103

#define C_TDU_TANK_PLAN_POS        7104
#define C_TDU_TANK_PLAN_POS_END    7105


// Uart ( TCU ), Range: 8000 -> 8199
#define C_UART                              8000
#define C_UART_END                          8001
#define C_UART_PORTNUMBER                   8002
#define C_UART_BAUDRATE                     8003
#define C_UART_PARITY                       8004
#define C_UART_STOPBITS                     8005
#define C_UART_WORDLENGTH                   8006
//#define C_UART_UARTTYPE                   8007
#define C_UART_MAX_TIME_BETWEEN_CHAR        8008
#define C_UART_HWPRO                        8010
#define C_UART_HWPRO_232                    8011
#define C_UART_HWPRO_485                    8012

#define C_UART_SWPRO                        8020
#define C_UART_SWPRO_ANPRO1                 8021
#define C_UART_SWPRO_ANPRO3                 8022
#define C_UART_SWPRO_ANPRO10                8023
#define C_UART_SWPRO_MODBUS                 8024
#define C_UART_SWPRO_PRINTER                8025
#define C_UART_SWPRO_SAAB                   8026

#define C_UART_DEVICE                       8032
#define C_UART_DEVICE_TDU                   8033
#define C_UART_DEVICE_PC                    8034
#define C_UART_DEVICE_TCU                   8035
#define C_UART_DEVICE_ANPRO3                8036
#define C_UART_DEVICE_ANPRO10               8037
#define C_UART_DEVICE_ZB                    8038
#define C_UART_DEVICE_ZB_RED                8039
#define C_UART_DEVICE_MODBUS_MASTER         8040
#define C_UART_DEVICE_MODBUS_MASTER_INV     8041
#define C_UART_DEVICE_MODBUS_MASTER_TCP     8042
#define C_UART_DEVICE_MODBUS_SLAVE          8043
#define C_UART_DEVICE_MODBUS_SLAVE_INV      8044
#define C_UART_DEVICE_MODBUS_SLAVE_TCP      8045

#define C_UART_DEVICE_MODICON_MASTER        8046
#define C_UART_DEVICE_MODICON_SLAVE         8047
#define C_UART_DEVICE_MODICON_MASTER_TCP    8048
#define C_UART_DEVICE_MODICON_SLAVE_TCP     8049

#define C_UART_DEVICE_TPC                   8050
#define C_UART_DEVICE_PRINTER               8051
#define C_UART_DEVICE_SAAB                  8052
// Do not change this key's
#define C_TCU_COM_232_TDU                   8120
#define C_TCU_COM_232_PC                    8121
#define C_TCU_COM_232_TCU                   8122
#define C_TCU_COM_232_PROT3                 8123
#define C_TCU_COM_232_PROT10                8124
#define C_TCU_COM_232_PRINTER               8125
#define C_TCU_COM_232_MODBUS_MASTER         8126
#define C_TCU_COM_232_MODBUS_MASTER_INV     8127
#define C_TCU_COM_232_MODBUS_MASTER_TCP     8128
#define C_TCU_COM_232_MODBUS_SLAVE          8129
#define C_TCU_COM_232_MODBUS_SLAVE_TCP      8130
#define C_TCU_COM_232_MODBUS_SLAVE_INV      8131
#define C_TCU_COM_232_MODICON_MASTER        8132
#define C_TCU_COM_232_MODICON_MASTER_TCP    8133
#define C_TCU_COM_232_MODICON_SLAVE         8134
#define C_TCU_COM_232_MODICON_SLAVE_TCP     8135
#define C_TCU_COM_232_SAAB                  8136
#define C_TCU_COM_485_TCU                   8137
#define C_TCU_COM_485_PROT3                 8138
#define C_TCU_COM_485_PROT10                8139
#define C_TCU_COM_485_ZB                    8140
#define C_TCU_COM_485_ZB_RED                8141
#define C_TCU_COM_485_MODBUS_MASTER         8142
#define C_TCU_COM_485_MODBUS_MASTER_INV     8143
#define C_TCU_COM_485_MODBUS_MASTER_TCP     8144
#define C_TCU_COM_485_MODBUS_SLAVE          8145
#define C_TCU_COM_485_MODBUS_SLAVE_TCP      8146
#define C_TCU_COM_485_MODBUS_SLAVE_INV      8147
#define C_TCU_COM_485_MODICON_MASTER        8148
#define C_TCU_COM_485_MODICON_MASTER_TCP    8149
#define C_TCU_COM_485_MODICON_SLAVE         8150
#define C_TCU_COM_485_MODICON_SLAVE_TCP     8151

#define C_TCU_COM_485_TPC                   8152
#define C_TCU_COM_485_TDU                   8153
#define C_TCU_COM_485_SAAB                  8154


// Tanksystem unit, Range: 8200 -> 8299
#define C_TU_ID                8201
#define C_TU_ID2               8202
#define C_TU_ADDRESS           8203
#define C_TU_ADDRESS2          8204
#define C_TU_POWER_VOLTAGE     8209
#define C_TU_POWER_SOURCE      8210
#define C_TU_POWER_1           8211
#define C_TU_POWER_2           8212
#define C_TU_POWER_BOTH        8213
#define C_TU_POWER_ACDC        8214 

#define C_NETWORK              8300
#define C_NETWORK_END          8301





// SystemData, Range: 8400 -> 8499
#define DEFAULT_PIN_CODE    1111
#define UNLOCK_PIN_CODE    12345
#define SECRET_PIN_CODE    65535 // DO NOT SHOW THIS TO ANYONE

#define C_SD_SCREEN_OFF_TIME   8401
#define C_SD_ALARM_OFF_DELAY   8402
#define C_SD_USER_PIN_CODE     8403
#define C_SD_UNITSYSTEM        8404
#define C_SD_LANGUAGE          8405
#define C_SD_TIME_GMT          8406
#define C_SD_DAYLIGH_SAVING     8407

#define C_SD_MAN_SOURCE         8410
#define C_SD_INC_SOURCE         8411
#define C_SD_DRAFT_SOURCE       8412
#define C_SD_LC_SOURCE_ONL      8413
#define C_SD_LC_SOURCE_MAN      8414
#define C_SD_LC_SOURCE          8415
#define C_SD_TRIM_SOURCE        8416
#define C_SD_LIST_SOURCE        8417
#define C_SD_MANUAL_TRIM        8420
#define C_SD_MANUAL_LIST        8421
#define C_SD_SEAWATER_TEMP      8422
#define C_SD_SEAWATER_DNS       8423
#define C_SD_AMBIENT_TEMP       8424

#define C_SD_BALLAST_DNS        8425
#define C_SD_FRESHWATER_DNS     8426
#define C_SD_HEAVY_FUEL_DNS     8427
#define C_SD_DIESEL_DNS         8428
#define C_SD_LUBRICANTS_DNS     8429


#define C_SD_SCREEN_CAL         8430
#define C_SD_LOG_TIME           8431
#define C_SD_LOG_TO_FILE        8432
#define C_SD_LOG_ALARMS         8433
#define C_SD_LOG_BALLAST_EXCH   8434
#define C_SD_LOG_CARGO          8435
#define C_SD_LOG_SERVICE        8436
#define C_SD_LOG_TEMPERATURE    8437
#define C_SD_LOG_TANK_PRESSURE  8438
#define C_SD_PRINTER_ON_TDU     8439
#define C_SD_RECEIVE_VOL_WGT    8440
#define C_SD_SIMULATE_IO        8441
#define C_SD_SIMULATE_STATIC    8442


// XRef info 8500~8550
#define C_XREF_START           8500
#define C_XREF_END             8501
#define C_XREF_ANPRO3          8502
#define C_XREF_SAAB            8503
#define C_XREF_EXCLUDE_STATE   8504

// Applications, Range: 9000 -> 9099
#define TSN_NONE_APP           9000
#define TSN_CARGO_APP          9001
#define TSN_BALLAST_APP        9002
#define TSN_SERVICE_APP        9003
#define TSN_TANKPRESS_APP      9004
#define TSN_LINEPRESS_APP      9005
#define TSN_TEMP_APP           9006
#define TSN_LEVELSWITCH_APP    9007
#define TSN_WATERINGR_APP      9008
#define TSN_VOIDSPACE_APP      9009
#define TSN_TANKFARM_APP       9010
#define TSN_TANK_CLEANING_APP  9011
#define TSN_TANK_CLEANING_DETAILS_APP 9012








// Load calc
// Range: 10000 -> 10500
#define C_LC_SHIPDATA               10000
#define C_LC_END                    10001
#define C_LC_CLASS_UNKNOWN          10002
#define C_LC_CLASS_DNV              10003
#define C_LC_CLASS_LLOYDS           10004
#define C_LC_CLASS_GL               10005
#define C_LC_CLASS_MRS              10006
#define C_LC_CLASS_BV               10007
#define C_LC_CLASS_NK               10008
#define C_LC_CLASS_RINA             10009
#define C_LC_CLASS_ABS              10010
#define C_LC_CLASS_KR               10011
#define C_LC_CLASS_USC              10012
#define C_LC_TABLE_ORDER            10049
#define C_LC_TABLE_CG               10050

#define C_LC_TABLE_AREA             10052
#define C_LC_TABLE_TFS              10053
#define C_LC_FRAME_LIST             10054
#define C_LC_TANK                   10055
#define C_LC_TANK_CARGO             10056
#define C_LC_TANK_BALLAST           10057
#define C_LC_TANK_HFO               10058
#define C_LC_TANK_DO                10059
#define C_LC_TANK_LUB               10060
#define C_LC_TANK_FW                10061
#define C_LC_TANK_MISC              10062
#define C_LC_TANK_VOIDSPACE         10063
#define C_LC_SOLID_CONSTANT         10064
#define C_LC_SOLID_VARIABLE         10065
#define C_LC_TABLE_BUOYANCY         10066
#define C_LC_TABLE_GZ               10067
#define C_LC_TABLE_KY               10068
#define C_LC_OPENING                10069
#define C_LC_WEIGHT_DISTRIBUTION    10080
#define C_LC_MAX_VCG                10081
#define C_LC_DAMAGE_MAX_VCG         10082
#define C_LC_BMHOGHRBLIM            10083
#define C_LC_BMHOGSEALIM            10084
#define C_LC_BMSAGHRBLIM            10085
#define C_LC_BMSAGSEALIM            10086
#define C_LC_SFHOGHRBLIM            10087
#define C_LC_SFHOGSEALIM            10088
#define C_LC_SFSAGHRBLIM            10089
#define C_LC_SFSAGSEALIM            10090
#define C_LC_STABILITY_TABLES       10091
#define C_LC_STEEL_WEIGHT           10092
#define C_LC_REF_APP                10094
#define C_LC_NO_BUOYANCY_CORR       10095
#define C_LC_GZ_SCALE               10096
#define C_LC_STABILITY_ONLY         10097
#define C_LC_SIMPLE_LC_ONLY         10098
#define C_LC_TRIM_BY_STERN_POS      10099
#define C_LC_LOAD_CALC_VERSION      10100
#define C_LC_DATA_VERSION           10101
#define C_LC_SECTION                10103
#define C_LC_MAX_SECTION_DRAFT      10104
#define C_LC_FRAME                  10110
#define C_LC_OVERRIDE_FRAME         10111
#define C_LC_TABLE_HYDROSTATIC      10112
#define C_LC_KY_CURVES              10113
#define C_LC_DISP_KY_CURVES         10114
#define C_LC_LENGTH                 10115
#define C_LC_FLOODING_ANGLE         10116
#define C_LC_DISTANCE               C_AI_DISTANCE       // T10115 To avoid duplicate name

#define C_LC_FRAME_PROFILE          10117
#define C_LC_COPY_FRAME_PROFILE     10118
#define C_LC_KY_CURVES_CF           10119
#define C_LC_DRAFT                  10120
#define C_LC_LIST                   10122
#define C_LC_LIST_ENTRIES           10123
#define C_LC_KY_ENTRY               10124

#define C_LC_TRIM                   C_AI_LOC_INC_TRIM  // T10124 To avoid duplicate name
#define C_LC_TRIM_ENTRIES           10125

#define C_LC_VCG_CASES              10128
#define C_LC_DISPLACEMENT           10129
#define C_LC_VCG                    10130
#define C_LC_LCG                    10131
#define C_LC_TCG                    10132
#define C_LC_MS_TO_APP              10133
#define C_LC_APP_TO_MARK            10134
#define C_LC_WEIGHT                 10135
#define C_LC_MAX_DRAFT              10136
#define C_LC_FREEBOARD              10137
#define C_LC_GZ_VCG_CONSTANT        10138
#define C_LC_KEEL_THICKNESS         10139
#define C_LC_HULL_DRAFT_CORRECTION  10140
#define C_LC_BM_CALC_F_TO_A         10141
#define C_LC_LCF                    10142
#define C_LC_TCF                    10143
#define C_LC_LCB                    10144
#define C_LC_KMT                    10145
#define C_LC_MCT                    10146
#define C_LC_TPM                    10147
#define C_LC_FRESH_WATER            10148
#define C_LC_SEA_WATER              10149
#define C_LC_LOCATION               10150
#define C_LC_LOC_END                10151
#define C_LC_MAX_WEIGHT             10152
#define C_LC_MAX_DENSITY            10153
#define C_LC_VOLUME                 10154
#define C_LC_DENSITY                10155
#define C_LC_ULLAGE                 10156
#define C_LC_ULLAGE_FC              10157
#define C_LC_LEVELFC                10158
#define C_LC_SOUNDING               10159
#define C_LC_LEVEL_AT_REF           10160
#define C_LC_VOLUME_PERCENT         10161
#define C_LC_TRIM_LIST_SOURCE       10162
#define C_LC_MANUAL_TRIM            10163
#define C_LC_MANUAL_LIST            10164
#define C_LC_TEMPERATURE            10165

#define C_LC_FIRST_STR_LIM_CHECK    10165
#define C_LC_LAST_STR_LIM_CHECK     10166
#define C_LC_WEIGHT_DISTR_REF_MID   10177

#define C_LC_TABLE_CG_ULL           10178
#define C_LC_TABLE_TFS_ULL          10179


// Tank washing machines, range 11000 -> 11100
#define TWM_TANK_WASHING_MACHINE_LIST		11000
#define TWM_END_TANK_WASHING_MACHINE_LIST 	11001
#define TWM_TANK_WASHING_MACHINE   			11002
#define TWM_END_TANK_WASHING_MACHINE		11003
#define TWM_IDENTIFIER   					11004
#define TWM_NOZZLE_DIAMETER_MM				11005
#define TWM_SERIAL_ID						11006
#define TWM_MACHINE_TYPE_ID					11007
#define TWM_NUMBER_OF_NOZZLES               11008
#define TWM_GEAR_RATIO                      11009

// Tank washing cleaning medias range 11100 -> 11150
#define TWM_CLEANING_MEDIA_LIST				11100
#define TWM_END_CLEANING_MEDIA_LIST			11101
#define TWM_CLEANING_MEDIA 					11102
#define TWM_END_CLEANING_MEDIA				11103


#define C_PRO_WATER_HEATER_INPUT_TEMP       11150
#define C_PRO_WATER_HEATER_OUTPUT_TEMP      11151
#define C_PRO_WATER_HEATER_PRESSURE         11152
#define C_PRO_WATER_HEATER_EFFICIENCY       11153
#define C_PRO_WATER_HEATER_FUEL_KWH_PER_TON 11154


#define C_SVT_OFFSET                        0x10000  // Used to correct value keys to config keys
/////////////////////////////////////////////////////////////////
//
// Misc constants
//
//
/////////////////////////////////////////////////////////////////
#define TICS_PER_SEC     1000
#define TICS_PER_MIN     (60*TICS_PER_SEC)

// For Write and Load to/from file
#define CONFIG_FILE_SIZE     (0x7ffff-4)  // Include space in the last config sector
#define FLASH_FILE_SIZE      (0x3ffff-4)  // Should follow actual size of flash according to TCU revision number
#ifndef ANWIN
#define MAXDOUBLE   1.797693E+308
#endif
#define MAXFLOAT    3.37E+38F
#define MINDOUBLE   2.225074E-308
#define MINFLOAT    8.43E-37F


// Max values
#define MAX_TCU          16
#define MAX_APPL          6
#define MAX_PRO_AI        6
#define MAX_MA_CALDATA   10
#define MAX_MV_CALDATA    4
// Relay on TCU
//#define MAX_CTRL_ALARM_TYPES 15
// IO related constants
#define POWER_ON_ZBANA_START_DELAY  5
#define POWER_ON_ZB485_START_DELAY  10
#define RS485_IO_PERIODE            2000
#define MIN_IO_DELAY                10
#define MAX_IO_RESPONSE_TIME        50
#define MAX_AN_ZBANA_CHANNELS       12
#define MAX_AN_ZB485_CHANNELS        8
#define MAX_TCU_AD_CHANNELS          8
#define MAX_AN_SGCNV_CHANNELS       14
#define MAX_W_INGR_CHANNELS          2
#define MAX_RADAR_CHANNELS           2
#define MAX_ID_ADDRESSES            16
#define MAX_SENSORS_ON_AD_CARD      16
#define MAX_WASHTRACK_CHANNELS      4
#define MAX_LEVEL_SWITCH_CHANNELS   8

#define RS485_DELAY                 200
#define RS485_ON_DELAY              2
#define RS485_EXTRA_DELAY           2


// Max values for TPC
#define TPC_MAX_DISPLAY_WINDOWS     7      // 6 windows + Alarm window
#define TPC_FIRST_ADDRESS          30
#define TPC_LAST_ADDRESS           45
#define TPC_MAX_PRIM_ADRESSES      (1+TPC_LAST_ADDRESS-TPC_FIRST_ADDRESS) // Ref ANPRO1 doc
#define TPC_MAX_TREND_ENTRIES      20
#define TPC_MAX_DISPLAYS                 50
#define TPC_DISPLAY_BUF_SIZE           200     // Was 240
#define TPC_LOWER_DISP_WIDTH         5
#define TPC_UPPER_DISP_WIDTH         4
#define TPC_EXTRA_DISP_WIDTH       4
#define TPC_GRAPH_SIZE                 3
#define TPC_MAIN_GRAPH_INDEX         0
#define TPC_SEC_GRAPH_INDEX        1
#define TPC_MAX_GRAPHS                 2


// Constants related to Load Rate

#define LR_BUFSIZE 5
#define LR_PERIOD  (1*60)
#define SECS_PR_HR 3600

//ANWIn data log clean interval
#ifdef ANWIN
#define NEXT_CLEAN_TIME ( 24*3600)
#endif


////////////////////////////////////////////////////////////////////////////////
 ///Modbus related constants 
 /// 
 /// 
//////////////////////////////////////////////////////////////////////////////// 
#define MODBUS_MAX_REGISTERS	0x4000
#define MODBUS_MAX_COILS		0x4000
#define MODBUS_MAX_UNITS		16




////////////////////////////////////////////////////////////////////////////////
//
// Configuration program
//
////////////////////////////////////////////////////////////////////////////////

#define TCU_DISPLAY_UNIT  1
#define TCU_ALARM_UNIT    2
#define TCU_AL_ACK_UNIT   3

// Tank Types for window
#define TANKTYPE_SUM            -2
#define TANKTYPE_EMPTY          -1
#define TANKTYPE_NONE            0
#define TANKTYPE_CARGO           1
#define TANKTYPE_BALLAST         2
#define TANKTYPE_HFO             3
#define TANKTYPE_DO              4
#define TANKTYPE_LUB             5
#define TANKTYPE_FW              6
#define TANKTYPE_MISC            7
#define TANKTYPE_VOIDSPACE       8
#define TANKTYPE_CSOLID          9
#define TANKTYPE_VSOLID         10
#define TANKTYPE_TANK_PRESS     11
#define TANKTYPE_LEVEL_SWITCH   12
#define TANKTYPE_TEMPERATURE    13
#define TANKTYPE_MAX            13

////////////////////////////////////////////////////////////////////////////////
//
// TDU window
//
////////////////////////////////////////////////////////////////////////////////

// Buttons in config main window
#define B_NEWPROJECT      0
#define B_EDITPROJECT     1
#define B_NEWCOMPONENT    2
#define B_EDITCOMPONENT   3
#define B_NEWPROTOCOL     4
#define B_EDITROTOCOL     5
#define B_SAVEPROJECT     6
#define B_CANSEL          7

#define TDU_WIN_COL         5

#define TDU_NO_WIN              0
#define TDU_SYSWIN1             1
#define TDU_SYSWIN2             2
#define TDU_SYSWIN3             3
#define TDU_SYSWIN4             4
#define TDU_SYSWIN5             5

#define TDU_CALWIN              6

#define MAX_TDU_ALARMS  1000

// TDU windows
// GUI_ID_USER = 2048
#define TDU_MAIN_WIN            (GUI_ID_USER+101)
#define TDU_HEAD_WIN            (GUI_ID_USER+102)
#define TDU_BUT_WIN             (GUI_ID_USER+103)
#define TDU_PRESENT_WIN         (GUI_ID_USER+104)
#define TDU_SYSTEM_WIN          (GUI_ID_USER+105)
#define TDU_ALARM_WIN           (GUI_ID_USER+106)
#define TDU_NOTCONF_WIN         (GUI_ID_USER+107)

// Application window (listview)
#define TDU_CARGO_WIN           (GUI_ID_USER+111)
#define TDU_BALLAST_WIN         (GUI_ID_USER+112)
#define TDU_SERVICE_WIN         (GUI_ID_USER+113)
#define TDU_TANKPRESS_WIN       (GUI_ID_USER+114)
#define TDU_LINEPRESS_WIN       (GUI_ID_USER+115)
#define TDU_TEMP_WIN            (GUI_ID_USER+116)
#define TDU_LEVELSWITCH_WIN     (GUI_ID_USER+117)
#define TDU_GASSAMPL_WIN        (GUI_ID_USER+118)
#define TDU_WATERINGR_WIN       (GUI_ID_USER+119)
#define TDU_VOIDSPACE_WIN       (GUI_ID_USER+120)
#define TDU_TANKFARM_WIN        (GUI_ID_USER+121)


#define TDU_CONFIG_MAIN_WIN     (GUI_ID_USER+130)
#define TDU_CALIBRATE_WIN       (GUI_ID_USER+140)
#define TDU_SYSTEM1_WIN         (GUI_ID_USER+141)
#define TDU_SYSTEM2_WIN         (GUI_ID_USER+142)
#define TDU_SYSTEM3_WIN         (GUI_ID_USER+143)
#define TDU_SYSTEM4_WIN         (GUI_ID_USER+144)
#define TDU_LOG_SETUP_WIN       (GUI_ID_USER+145)
#define TDU_SYSTEM5_WIN         (GUI_ID_USER+146)
#define TDU_SYSSETUP_WIN        (GUI_ID_USER+147)
#define TDU_USERMAN_WIN         (GUI_ID_USER+148)
#define TDU_APPBALLAST_WIN      (GUI_ID_USER+149)
#define TDU_APPCARGO_WIN        (GUI_ID_USER+150)
#define TDU_APPSERVICE_WIN      (GUI_ID_USER+151)
#define TDU_APPTANKPRESS_WIN    (GUI_ID_USER+152)
#define TDU_APPTEMP_WIN         (GUI_ID_USER+153)
#define TDU_APPSETUP_WIN        (GUI_ID_USER+154)
#define TDU_CONFWARNING_WIN     (GUI_ID_USER+155)
#define TDU_WARNING_WIN         (GUI_ID_USER+156)
#define TDU_MESSAGE_WIN         (GUI_ID_USER+157)
#define TDU_MESSAGE_CAN_WIN     (GUI_ID_USER+158)
#define TDU_CALDATA_WIN         (GUI_ID_USER+159)
#define TDU_MULTIPAGE_D1_WIN    (GUI_ID_USER+160)
#define TDU_MULTIPAGE_D2_WIN    (GUI_ID_USER+161)
#define TDU_MULTIPAGE_D3_WIN    (GUI_ID_USER+162)
#define TDU_MULTIPAGE_D4_WIN    (GUI_ID_USER+163)
#define TDU_MULTIPAGE_D5_WIN    (GUI_ID_USER+164)
#define TDU_TANK_CLEANING_WIN	(GUI_ID_USER+165)
#define TDU_TANK_CLEANING_DETAILS_WIN (GUI_ID_USER+166)

// TDU buttons
#define TDU_BUTTON_ID_MW0       (GUI_ID_USER+201)
#define TDU_BUTTON_ID_MW1       (GUI_ID_USER+202)
#define TDU_BUTTON_ID_MW2       (GUI_ID_USER+203)
#define TDU_BUTTON_ID_MW3       (GUI_ID_USER+204)
#define TDU_BUTTON_ID_MW4       (GUI_ID_USER+205)
#define TDU_BUTTON_ID_MW5       (GUI_ID_USER+206)
#define TDU_BUTTON_ID_MW6       (GUI_ID_USER+207)
#define TDU_BUTTON_ID_MW7       (GUI_ID_USER+208)
#define CLOSE_BUT_ID_CONFIG     (GUI_ID_USER+209)
#define CLOSE_BUT_ID_CALIBRATE  (GUI_ID_USER+210)

// TDU buttons for
#define TDU_BUTTON_ID_PW1       (GUI_ID_USER+209)
#define TDU_BUTTON_ID_PW2       (GUI_ID_USER+210)
#define TDU_BUTTON_ID_PW3       (GUI_ID_USER+211)
#define TDU_BUTTON_ID_PW4       (GUI_ID_USER+212)
#define TDU_BUTTON_ID_PW5       (GUI_ID_USER+213)


// From simulator:
#define MAX_INITIAL_TAB_ENTRIES 200

// Help constants used several places
#define NPOS                    -1
#define NOT_FOUND           -1
//  #define CONFEND             -2
#define END_FOUND           (EOF-1)
#define BUF_SIZE            80


#define E_ERR_F_SIZE 70     // Size of error messages

#define NELEMENTS(array)        /* number of elements in an array */ \
        (sizeof(array) / sizeof((array) [0]))

#define FOREVER while(true)

#define CONFIG_WORD_SIZE 30

#define UNIT_SYS_SI         0
#define UNIT_SYS_US         1
#define UNIT_SYS_USER       2

////////////////////////////////////////////////////////////////////////////////
//
// Librarian:
//
////////////////////////////////////////////////////////////////////////////////
#define VALUE_NAME_SIZE        14
#define SVT_NOT_DEFINED            0
#define SVT_SEPARATOR            100
#define SVT_SUBMENU              101
#define SVT_SUBMENU_END          102

//PRogramObject Values, Range 1000->1100
#define SVT_BLANK                   1000
#define SVT_LEVEL_SENSOR            1001
#define SVT_LEVEL_SENSOR2           1002
#define SVT_ULLAGE                  1003
#define SVT_TEMP                    1004
#define SVT_VAPOR_TEMP              1005
#define SVT_DENSITY                 1006
#define SVT_ULLAGE_FC               1007
#define SVT_ULLAGE_UTI              1008
#define SVT_ULLAGE_RADAR            1009

#define SVT_TANK_NAM                1010
#define SVT_VALUE                   1011
#define SVT_UNIT                    1012
#define SVT_EMPTYTANK               1013
#define SVT_DATE                    1014
#define SVT_TIME                    1015
#define SVT_SECONDS                 1016

#define SVT_VOLUME                  1020
#define SVT_WEIGHT                  1021
#define SVT_VOLPERCENT              1022
#define SVT_LOADRATE                1023
#define SVT_PRESSURE                1024
#define SVT_LINE_PRESSURE           1025
#define SVT_LEVEL_PRESSURE          1026
#define SVT_SOUNDING                1027
#define SVT_VOL_AT_REFTMP           1028
#define SVT_CAPACITY98              1029
#define SVT_CAPACITY100             1030
#define SVT_CAPACITY                1031
#define SVT_INTERFACE               1032
#define SVT_LC_VOLUME               1033
#define SVT_LC_WEIGHT               1034
#define SVT_LC_DENSITY              1040
#define SVT_VOLUME_SETPOINT         1041
#define SVT_LEVEL_FC                1042
#define SVT_LEVEL_REF               1043
#define SVT_LEVEL_PERCENT           1044

#define SVT_TANK_TYPE               1045

#define SVT_VAP_WEIGHT              1046
#define SVT_GAS_WEIGHT              1050
#define SVT_MAN_LEVEL               1051
#define SVT_MAN_ULLAGE              1052
#define SVT_FINISH_TIME             1053
#define SVT_REMAINING_TIME          1054

#define SVT_ZEROSET_LEVEL           1055
#define SVT_ZEROSET_TANK_PRESS      1056  // Not used
#define SVT_ZEROSET_PRESS           1057
#define SVT_ADJUST_LEVEL            1058
#define SVT_ADJUST_SOUNDING         1059
#define SVT_ADJUST_ULLAGE           1060
#define SVT_ADJUST_ULLAGE_UTI       1061
#define SVT_ADJUST_VOLUME           1062
#define SVT_ADJUST_WEIGHT           1063
#define SVT_LEVEL_OFFSET            1064
#define SVT_TABLE_OFFSET            1065
#define SVT_DISTANCE_SNS_UTI        1066
#define SVT_RADAR_THRESHOLD         1067

#define SVT_BP                      1068
#define SVT_MP                      1069
#define SVT_UP                      1070
#define SVT_TP                      1071
#define SVT_T1                      1072
#define SVT_T2                      1073
#define SVT_T3                      1074
#define SVT_T4                      1075
#define SVT_T5                      1076
#define SVT_TT                      1077
#define SVT_TMP1					1078
#define SVT_TMP2					1079
#define SVT_TMP3                    1081
#define SVT_TMP4                    1082
#define SVT_TMP5                    1083
#define SVT_BP_OFFSET               1084
#define SVT_MP_OFFSET               1085
#define SVT_UP_OFFSET               1086
#define SVT_TP_OFFSET               1087
#define SVT_T2_OFFSET               1088
#define SVT_T5_OFFSET               1089
#define SVT_T1_OFFSET               1090
#define SVT_T3_OFFSET               1091
#define SVT_T4_OFFSET               1092
#define SVT_TT_OFFSET               1093
#define SVT_BP_GAIN                 1094
#define SVT_MP_GAIN                 1095
#define SVT_UP_GAIN                 1096
#define SVT_TP_GAIN                 1097
#define SVT_BP1                     1098
#define SVT_BP2                     1099
#define SVT_BP3                     1100
#define SVT_BP_OFFSET1              1101
#define SVT_BP_OFFSET2              1102
#define SVT_BP_OFFSET3              1103
#define SVT_BP_GAIN1                1104
#define SVT_BP_GAIN2                1105
#define SVT_BP_GAIN3                1106
#define SVT_BP_ENABLE               1107
#define SVT_BP_ENABLE1              1108
#define SVT_BP_ENABLE2              1109
#define SVT_BP_ENABLE3              1110
#define SVT_MP_ENABLE               1111
#define SVT_UP_ENABLE               1112
#define SVT_TP_ENABLE               1113
#define SVT_BP_ENABLE_TEXT          1114
#define SVT_BP_ENABLE1_TEXT         1115
#define SVT_BP_ENABLE2_TEXT         1116
#define SVT_BP_ENABLE3_TEXT         1117
#define SVT_MP_ENABLE_TEXT          1118
#define SVT_UP_ENABLE_TEXT          1119
#define SVT_TP_ENABLE_TEXT          1120
#define SVT_BP_SERIAL_NO            1121
#define SVT_BP_SERIAL_NO1           1122
#define SVT_BP_SERIAL_NO2           1123
#define SVT_BP_SERIAL_NO3           1124
#define SVT_MP_SERIAL_NO            1125
#define SVT_UP_SERIAL_NO            1126
#define SVT_TP_SERIAL_NO            1127
#define SVT_T1_GAIN                 1128
#define SVT_T2_GAIN                 1129
#define SVT_T3_GAIN                 1130
#define SVT_T4_GAIN                 1131
#define SVT_T5_GAIN                 1132
#define SVT_TT_GAIN                 1133
#define SVT_T1_ENABLE               1134
#define SVT_T2_ENABLE               1135
#define SVT_T3_ENABLE               1136
#define SVT_T4_ENABLE               1137
#define SVT_T5_ENABLE               1138
#define SVT_TT_ENABLE               1139
#define SVT_LP                      1140
#define SVT_LP_OFFSET               1141
#define SVT_LP_GAIN                 1142
#define SVT_LP_ENABLE               1143
#define SVT_LP_ENABLE_TEXT          1144
#define SVT_METRI_TAPE_SNS          1145
#define SVT_HSH_FLOAT_SNS           1146
#define SVT_HART_RADAR              1147
#define SVT_HART_MA				    1148
#define SVT_HART_STATUS             1149
#define SVT_HART_ERROR_CNT          1150
#define SVT_HART_OPEN_LOOP          1151
#define SVT_HART_SHORT_CIRCUIT      1152
#define SVT_AP_LEVEL                1153
#define SVT_AP_LEVEL2               1154
#define SVT_AP_LEVEL_PRESSURE_MH2O  1155
#define SVT_AP_TANK_PRESSURE_MB     1156
#define SVT_AP_LEVEL_PRESSURE_MB    1157
#define SVT_AP_LPRESS_SNS_FAIL      1158
#define SVT_AP_LPRESS_SNS_FAIL2     1159
#define SVT_AP_TPRESS_SNS_FAIL      1160
#define SVT_AP_SYS_FAIL             1161
#define SVT_AP_POWER_FAIL           1162
#define SVT_AP_COMMON_ALM           1163
#define SVT_AP_LOW_PRESS            1164
#define SVT_MB_MA_PRESSURE    		1165
#define SVT_LEVEL_SWITCH_STATUS     1167
#define SVT_LEVEL_SWITCH_STATUS2    1168
#define SVT_VOLUME_OFFSET           1169
#define SVT_OFFSET_VOLUME           1170
#define SVT_OFFSET_VOL_AT_REF_TMP   1171
#define SVT_OFFSET_WEIGHT           1172
#define SVT_VOLUME_CORRECTION       1173
#define SVT_CUSTODY_TRF_LEVEL1      1174
#define SVT_CUSTODY_TRF_LEVEL2      1175
#define SVT_CUSTODY_TRF_LEVEL3      1176
#define SVT_CUSTODY_TRF_LEVEL4      1177
#define SVT_CUSTODY_TRF_LEVEL5      1178
#define SVT_CUSTODY_TRF_AVG_LEVEL   1179
#define SVT_CUSTODY_TRF_TRIM_CORR   1180
#define SVT_CUSTODY_TRF_LIST_CORR   1181
#define SVT_CUSTODY_TRF_CORR_LEVEL  1182

// AnalogInput, Range: 1200 -> 1249
#define SVT_AI_TYPE                 1200
#define SVT_AI_TYPE_TEXT            1201
#define SVT_AI_ENABLE_TEXT          1202
#define SVT_AI_ENABLE               1203
#define SVT_AI_GAIN                 1204
#define SVT_AI_OFFSET               1205
#define SVT_AI_DB                   1206
#define SVT_AI_PLACING              1207
#define SVT_AI_CALC_VAL             1208
#define SVT_AI_LOCATION             1209
#define SVT_AI_PRONAME              1211
#define SVT_AI_SERIAL_NUMBER        1212
#define SVT_AI_MIN_RANGE            1213
#define SVT_AI_MAX_RANGE            1214
#define SVT_AI_RANGE                1215
#define SVT_AI_UNIT                 1216
#define SVT_AI_CABLE_LENGTH         1217
#define SVT_AI_CAL_DATA_FRO         1220
#define SVT_AI_CAL_DATA_G1          1221
#define SVT_AI_CAL_DATA_G2          1222
#define SVT_AI_CAL_DATA_G3          1223
#define SVT_AI_CAL_DATA_NL1         1224
#define SVT_AI_CAL_DATA_NL2         1225
#define SVT_AI_CAL_DATA_TZS         1226
#define SVT_AI_CAL_DATA_TSS         1227
#define SVT_AI_CAL_DATA_ENTRY       1228
#define SVT_AI_CAL_DATA_ENTRIES     1229
#define SVT_AI_CAL_DATA_PERCENT     1230

#define SVT_MA_ON                   1240
#define SVT_MA_OFF                  1241
#define SVT_MA_WINDOW               1242
// PROIOComponent object, Range     1250 1299
#define SVT_IOC_TCU_ADDRES          1250
#define SVT_IOC_TCU_PORT            1251
#define SVT_IOC_IO_TYPE_TEXT        1252
#define SVT_IOC_IO_ADDRESS          1253
#define SVT_IOC_IO_CHANNEL          1254
#define SVT_IOC_ADCARD_CHANNEL      1255

#define SVT_IO_CH_NAME              1260
#define SVT_IO_CH_LOCATION          1261
#define SVT_IO_CH_TYPE_TEXT         1262
#define SVT_IO_CH_RAW_VAL           1263
#define SVT_IO_CH_CAL_VAL           1264
#define SVT_IO_CH_VALUE             1265
#define SVT_IO_CH_STATUS            1266

#define SVT_IO_CH_WT_SPEED          1267
#define SVT_IO_CH_WT_COUNT          1268
#define SVT_IO_CH_LEVEL_SWITCH      1269

#define SVT_IO_CH_HART_FAIL_COUNT1  1270
#define SVT_IO_CH_HART_FAIL_COUNT2  1271

//EEPromStatus PRogram Objects,     Range: 1300 -> 1500
#define SVT_PRO_NAME                1301
#define SVT_PRO_LONGNAME            1302
#define SVT_PRO_TAGNAME             1303
#define SVT_PRO_SORTNO              1304
#define SVT_PRO_STATUS              1305
#define SVT_PRO_TIMESTAMP           1306

// PROSystemData, Range: 1400 -> 1450
#define SVT_ATM_PRESSURE            1351
#define SVT_ATM_P_ENABLE            1352
#define SVT_ATM_TEMP                1353
#define SVT_ATM_T_ENABLE            1354
#define SVT_TRIM_M                  1355
#define SVT_TRIM_MARKS_M            1356
#define SVT_TRIM_ANGLE              1357
#define SVT_TRIM_M_NOSIGN           1358
#define SVT_TRIM_ANGLE_NOSIGN       1359
#define SVT_TRIM_SOURCE             1360
#define SVT_LIST_M                  1361
#define SVT_LIST_ANGLE              1362
#define SVT_LIST_M_NOSIGN           1363
#define SVT_LIST_ANGLE_NOSIGN       1364
#define SVT_TRIM_DEG                1365
#define SVT_LIST_DEG                1366
#define SVT_LIST_ROLL_FILTER        1367
#define SVT_ROLLING_PERIOD          1368
#define SVT_LIST_MAX_P              1369
#define SVT_LIST_MAX_S              1370
#define SVT_LIST_BUF_MAX_P          1371
#define SVT_LIST_BUF_MAX_S          1372
#define SVT_ROLLING_FREQUENCY       1373
#define SVT_RESET_MAX_LIST          1374




#define SVT_LIST_SOURCE             1415
#define SVT_CURRENT_UNIT_SYSTEM     1420
#define SVT_CURRENT_LANGUAGE        1421
#define SVT_ALARM_OFF_DELAY         1422
#define SVT_ALARM_SOUND_SLEEP       1423
#define SVT_TOUCH_SCREEN_TIMEOUT    1424
#define SVT_USER_PIN_CODE           1425
#define SVT_FORCE_WRITE_CONFIG      1426
//Density
#define SVT_AMBIENT_TEMP            1439
#define SVT_SEAWATER_TEMP           1440
#define SVT_SEAWATER_DNS            1441
#define SVT_BALLAST_DNS             1442
#define SVT_FRESHWATER_DNS          1443
#define SVT_HEAVY_FUEL_DNS          1444
#define SVT_DIESEL_DNS              1445
#define SVT_LUBRICANTS_DNS          1446
#define SVT_CARGO_VOLUME            1450
#define SVT_CARGO_WEIGHT            1451
#define SVT_BALLAST_VOLUME          1452
#define SVT_BALLAST_WEIGHT          1453
#define SVT_HEAVY_FUEL_VOLUME       1454
#define SVT_HEAVY_FUEL_WEIGHT       1455
#define SVT_DIESEL_OIL_VOLUME       1456
#define SVT_DIESEL_OIL_WEIGHT       1457
#define SVT_LUBRICANTS_VOLUME       1458
#define SVT_LUBRICANTS_WEIGHT       1459
#define SVT_FRESH_WATER_VOLUME      1460
#define SVT_FRESH_WATER_WEIGHT      1461
#define SVT_MISC_VOLUME             1462
#define SVT_MISC_WEIGHT             1463
#define SVT_VOID_SPACE_WEIGHT       1464
#define SVT_VOID_SPACE_VOLUME       1465
#define SVT_SOLIDS_WEIGHT           1466
#define SVT_TOTAL_VOLUME            1467
#define SVT_TOTAL_WEIGHT            1468
#define SVT_LOG_TO_FILE             1469
#define SVT_LOG_TIME                1470
#define SVT_LOG_ALARMS              1471
#define SVT_LOG_BALLAST_EXCH        1472
#define SVT_LOG_CARGO               1473
#define SVT_LOG_SERVICE             1474
#define SVT_LOG_TEMPERATURE         1475
#define SVT_LOG_TANK_PRESSURE       1476
#define SVT_PRINTER_ON_TXU          1477
#define SVT_TANK_STATE              1478
#define SVT_TANK_STATE_STR          1479
#define SVT_TANK_STATE_STR_CGO      1480
#define SVT_TANK_STATE_STR_BAL      1481
#define SVT_TANK_STATE_STR_SER      1482
#define SVT_TANK_STATE_STR_LSW      1483
#define SVT_TANK_STATE_STR_PRE      1484


//Draft system, Range: 1500 -> 1550
#define SVT_DRAFT_PP              1501
#define SVT_MAX_DRAFT             1502
#define SVT_DRAFT_MID             1503
#define SVT_DF                    1504
#define SVT_DF_MARK               1505
#define SVT_DF_PP                 1506
#define SVT_DA                    1507
#define SVT_DA_MARK               1508
#define SVT_DA_PP                 1509
#define SVT_DS                    1510
#define SVT_DP                    1511
#define SVT_DFP                   1512
#define SVT_DFS                   1513
#define SVT_DFP_PP                1514
#define SVT_DFS_PP                1515
#define SVT_DAP                   1516
#define SVT_DAS                   1517
#define SVT_DAP_PP                1518
#define SVT_DAS_PP                1519
#define SVT_LATITUDE              1530
#define SVT_DRAFT                 1531
#define SVT_DRAFT_POINT           1540
#define SVT_DEFLECTION            1541
#define SVT_DRAFT_ALL             1542
#define SVT_FREEBOARD             1543



//LoadReport, Range: 1600 -> 1650
#define SVT_LR_BILL_LOADING       1601
#define SVT_LR_LOADPORT           1602
#define SVT_LR_DESTPORT           1603
#define SVT_LR_VOYAGE             1604
#define SVT_LR_START              1605
#define SVT_LR_STOP               1606
#define SVT_LR_INSPECTION         1607
#define SVT_LR_SHIP_NAME          1608
#define SVT_LR_SHIP_TITLE         1609
#define SVT_LR_SURV_NAME          1610
#define SVT_LR_SURV_TITLE         1611
#define SVT_LR_REMARK1            1612
#define SVT_LR_DF                 1613
#define SVT_LR_DMID               1614
#define SVT_LR_DA                 1615
#define SVT_LR_SHIP_FIGURES       1616
#define SVT_LR_SHIP_VOL_FIGURES   1617
#define SVT_LR_DIFFERENCE_WGT     1618
#define SVT_LR_DIFFERENCE_VOL     1619
#define SVT_LR_DIFFERENCE_WGT_PCT 1620
#define SVT_LR_DIFFERENCE_VOL_PCT 1621
#define SVT_LR_BILL_LOADING_VOL   1622
#define SVT_LR_TRIM               1623
#define SVT_LR_LIST               1624
//Cargo type Range: 2000 -> 2100
#define SVT_BASIC_TYPE                2000
#define SVT_BASIC_TYPE_NAME           2001
#define SVT_CARGO_TYPE                2002
#define SVT_CARGO_TYPE_NAME           2003
#define SVT_API                       2004
#define SVT_VCF                       2005
#define SVT_VCF_AT_TEMP               2006
#define SVT_MEASURED_API              2007
#define SVT_COMP_DNS                  2008
#define SVT_MEAS_DNS                  2009
#define SVT_MEAS_DNS_RAW              2010
#define SVT_REF_DNS1                  2011
#define SVT_REF_DNS2                  2012
#define SVT_REF_TMP1                  2013
#define SVT_REF_TMP2                  2014
#define SVT_COEFF                     2015
#define SVT_MOLMASS                   2016
#define SVT_COLOUR                    2017
#define SVT_VISCOSITY                 2018
#define SVT_CARGO_COLOR               2019
#define SVT_UPDATE_TANK_CT            2050
#define SVT_USE_MSRD_DNS              2051
#define SVT_IS_DEFINED                2052
#define SVT_DELETE_CT                 2053
#define SVT_DB_IDNUMBER               2054  
#define SVT_CARGO_TYPE_KEY            2055
#define SVT_COPY_CT                   2056
#define SVT_COPY_CT_TO_BUFFER         2057
#define SVT_COPY_CT_FROM_BUFFER       2058
//Name, Range 3000 ->3100
#define SVT_NAME                      3000
#define SVT_VALUE_NAME                3001
#define SVT_VALUE_NAME_UNIT           3002
#define SVT_VALUE_SHORT_NAME          3003
#define SVT_REPORT_VALUE_NAME         3004
#define SVT_REPORT_VALUE_SNAME        3005
//System, Range 3100 ->3200
#define SVT_PROG_VERSION            3101
#define SVT_SHIP_NAME               3102
#define SVT_SHIP_OWNER              3103
#define SVT_SHIP_LENGTH             3104
#define SVT_SHIP_WIDTH              3105
#define SVT_DATA_VERSION            3106
#define SVT_SYSTEM_ID               3107
#define SVT_CALL_SIGN               3108
#define SVT_SHIP_LPP                3109

#define SVT_TASK_NAME               3110
#define SVT_TASK_STACK_USED         3111
#define SVT_TASK_STACK_SPACE        3112
#define SVT_TASK_NUMBER             3113
#define SVT_TASK_LOAD               3114
// TCU, TDU units Range 4000 -> 4500
#define SVT_AIN1                    4001
#define SVT_AIN2                    4002
#define SVT_AIN3                    4003
#define SVT_AIN4                    4004
#define SVT_AIN5                    4005
#define SVT_AIN6                    4006
#define SVT_LAST_OS_ERROR           4007
#define SVT_FLASH_ERROR_STATUS      4008
#define SVT_LAST_OS_ERROR_TASK      4009
#define SVT_RUNNING_HOURS           4010
#define SVT_UNIT_PROGRAM_VERSION    4011
#define SVT_UNIT_BOOTLOADER_VERSION 4012
#define SVT_DEVICE                  4013
#define SVT_PROTOCOL                4014
#define SVT_RXERR_ID                4015
#define SVT_RXERR_CMD               4016
#define SVT_RXERR_MSG               4017
#define SVT_RXERR_CNT               4018
#define SVT_RXERR_TIME              4019
#define SVT_ERROR_ADDRESS           4020
#define SVT_IO_SYSTEM_DELAY         4021
#define SVT_CPU_LOAD_RAW            4022
#define SVT_CPU_LOAD_AVG            4023
#define SVT_CPU_LOAD_MAX            4024


#define SVT_TXU_RX_BYTES            4100
#define SVT_TXU_RX_LOAD             4101
#define SVT_TXU_TX_BYTES            4102
#define SVT_TXU_TX_LOAD             4103


// IOUnit Range 4500 -> 5000
#define SVT_IO_COM_CHANNEL          4501
#define SVT_IO_PROG_VERSION         4502
#define SVT_IO_COM_VERSION          4503
#define SVT_IO_STORE_VERSION        4504
#define SVT_IO_RXBUF_SIZE           4505
#define SVT_IO_TXBUF_SIZE           4506
#define SVT_IO_RESET_STATUS         4507
#define SVT_IO_P_TYPE_RUNNING       4508
#define SVT_IO_CARD_VOLTAGE         4509
#define SVT_IO_NEW_SENSOR           4510
#define SVT_IO_TOTAL_RESTARTS       4511

#define SVT_IO_CH_CONV_ERROR          4610
#define SVT_IO_CH_CAL_ERROR           4611
#define SVT_IO_CH_CNV_CAL_ERROR     4612
#define SVT_IO_CH_FROM_PC_SENSOR    4613
#define SVT_IO_CH_USE_PC_SETUP    4614
#define SVT_IO_CH_AD_SENSOR         4615
#define SVT_IO_CH_NEW_SENSOR          4616
#define SVT_IO_CH_EEP_USE_PCDATA    4617
#define SVT_IO_CH_EEP_PC_STAT       4618
#define SVT_IO_CH_EEP_SNS_STAT      4619

#define SVT_IO_SERIAL_NUMBER          4650
#define SVT_IO_CAL_NULL                 4651
#define SVT_IO_CAL_GAIN                 4652

#define SVT_IO_UNIT_STATUS        4653
#define SVT_IO_CARD_STATUS        4654
#define SVT_IO_FAIL_CNT_CHK       4655
#define SVT_IO_FAIL_CNT_TOT       4656

// Alarms Range: 9000 -> 9500
#define SVT_AL_ACT_ALARMS         9001
#define SVT_AL_LIMIT              9010
#define SVT_AL_VALUE              9011
#define SVT_AL_AKN_DATE_TIME      9012
#define SVT_AL_AKN_TIME           9013
#define SVT_AL_ACT_DATE_TIME      9014
#define SVT_AL_ACT_TIME           9015
#define SVT_AL_DIS_DATE_TIME      9016
#define SVT_AL_DIS_TIME           9017
#define SVT_AL_LOCATION           9018
#define SVT_AL_DESCRIPTION        9019
#define SVT_AL_MESSAGE            9020
#define SVT_AL_PRIORITY           9021
#define SVT_AL_ENABLE             9022
#define SVT_AL_ENABLE_TXT         9023
#define SVT_AL_ACKNOWLEDGE        9024
#define SVT_AL_UNIT               9025
#define SVT_AL_SET_MODE           9026
#define SVT_AL_STATE              9027
#define SVT_AL_LOG_ENABLE         9028
#define SVT_AL_LOG_ENABLE_TXT     9029

#define SVT_HI_TEMP_LIMIT         9100
#define SVT_LO_TEMP_LIMIT         9101
#define SVT_HI_TEMP_ENABLE        9102
#define SVT_LO_TEMP_ENABLE        9103
#define SVT_HI_TEMP_VALUE         9104
#define SVT_LO_TEMP_VALUE         9105
#define SVT_HI_TEMP_STATE         9106
#define SVT_LO_TEMP_STATE         9107
#define SVT_HI_BOT_TEMP_LIMIT     9108
#define SVT_LO_BOT_TEMP_LIMIT     9109
#define SVT_HI_BOT_TEMP_ENABLE    9110
#define SVT_LO_BOT_TEMP_ENABLE    9111
#define SVT_HI_BOT_TEMP_VALUE     9112
#define SVT_LO_BOT_TEMP_VALUE     9113
#define SVT_HI_BOT_TEMP_STATE     9114
#define SVT_LO_BOT_TEMP_STATE     9115

#define SVT_HIHI_PRESS_ENABLE     9119
#define SVT_HI_PRESS_ENABLE       9120
#define SVT_LO_PRESS_ENABLE       9121
#define SVT_HIHI_PRESS_LIMIT      9122
#define SVT_HI_PRESS_LIMIT        9123
#define SVT_LO_PRESS_LIMIT        9124
#define SVT_HIHI_PRESS_VALUE      9125
#define SVT_HI_PRESS_VALUE        9126
#define SVT_LO_PRESS_VALUE        9127
#define SVT_HIHI_PRESS_STATE      9128
#define SVT_HI_PRESS_STATE        9129
#define SVT_LO_PRESS_STATE        9130
#define SVT_HI_PRESS_VAC_ENABLE   9131
#define SVT_LO_PRESS_VAC_ENABLE   9132
#define SVT_HI_PRESS_VAC_LIMIT    9133
#define SVT_LO_PRESS_VAC_LIMIT    9134
#define SVT_HI_PRESS_VAC_VALUE    9135
#define SVT_LO_PRESS_VAC_VALUE    9136
#define SVT_HI_PRESS_VAC_STATE    9137
#define SVT_LO_PRESS_VAC_STATE    9138
#define SVT_HI_IGP_ENABLE         9139
#define SVT_LO_IGP_ENABLE         9140
#define SVT_HI_IGP_LIMIT          9141
#define SVT_LO_IGP_LIMIT          9142
#define SVT_HI_IGP_VALUE          9143
#define SVT_LO_IGP_VALUE          9144
#define SVT_HI_IGP_STATE          9145
#define SVT_LO_IGP_STATE          9146
#define SVT_HI_VAP_RET_ENABLE     9147
#define SVT_LO_VAP_RET_ENABLE     9148
#define SVT_HI_VAP_RET_LIMIT      9149
#define SVT_LO_VAP_RET_LIMIT      9150
#define SVT_HI_VAP_RET_VALUE      9151
#define SVT_LO_VAP_RET_VALUE      9152
#define SVT_HI_VAP_RET_STATE      9153
#define SVT_LO_VAP_RET_STATE      9154
#define SVT_AL_LIMIT_TYPE_LEV     9155
#define SVT_AL_LIMIT_TYPE_PRESS   9156
#define SVT_XTRA_HI_PRESS_ENABLE1 9157
#define SVT_XTRA_LO_PRESS_ENABLE1 9158
#define SVT_XTRA_HI_PRESS_LIMIT1  9159
#define SVT_XTRA_LO_PRESS_LIMIT1  9160
#define SVT_XTRA_HI_PRESS_VALUE1  9161
#define SVT_XTRA_LO_PRESS_VALUE1  9162
#define SVT_XTRA_HI_PRESS_STATE1  9163
#define SVT_XTRA_LO_PRESS_STATE1  9164
#define SVT_XTRA_HI_PRESS_ENABLE2 9165
#define SVT_XTRA_LO_PRESS_ENABLE2 9166
#define SVT_XTRA_HI_PRESS_LIMIT2  9167
#define SVT_XTRA_LO_PRESS_LIMIT2  9168
#define SVT_XTRA_HI_PRESS_VALUE2  9169
#define SVT_XTRA_LO_PRESS_VALUE2  9170
#define SVT_XTRA_HI_PRESS_STATE2  9171
#define SVT_XTRA_LO_PRESS_STATE2  9172
#define SVT_WI_OVERRIDE           9173
#define SVT_WI_MAIN_ENABLE        9174
#define SVT_WI_PRE_ENABLE         9175
#define SVT_WI_MAIN_LIMIT         9176
#define SVT_WI_PRE_LIMIT          9177
#define SVT_WI_MAIN_VALUE         9178
#define SVT_WI_PRE_VALUE          9179
#define SVT_WI_PROTECTION         9180
#define SVT_HIHI_LEVEL_ENABLE     9181
#define SVT_HI_LEVEL_ENABLE       9182
#define SVT_LO_LEVEL_ENABLE       9183
#define SVT_LOLO_LEVEL_ENABLE     9184
#define SVT_HI_LEVEL_LIMIT        9191
#define SVT_LO_LEVEL_LIMIT        9192
#define SVT_LOLO_LEVEL_LIMIT      9193
#define SVT_OVERFILL_VALUE        9194
#define SVT_HI_LEVEL_VALUE        9195
#define SVT_LO_LEVEL_VALUE        9196
#define SVT_LOLO_LEVEL_VALUE      9197
#define SVT_HIHI_VOLPCNT_STATE    9198
#define SVT_HI_VOLPCNT_STATE      9199
#define SVT_LO_VOLPCNT_STATE      9200
#define SVT_LOLO_VOLPCNT_STATE    9201
#define SVT_HIHI_VOLPCNT_LIM      9202
#define SVT_HI_VOLPCNT_LIM        9203
#define SVT_HI_VOLUME_LIM         9204
#define SVT_HI_WEIGHT_LIM         9205
#define SVT_HI_ULLAGE_LIM         9206
#define SVT_HI_LEVEL_LIM          9207
#define SVT_LO_VOLPCNT_LIM        9208
#define SVT_LO_VOLUME_LIM         9209
#define SVT_LO_WEIGHT_LIM         9210
#define SVT_LO_ULLAGE_LIM         9211
#define SVT_LO_LEVEL_LIM          9212
#define SVT_LOLO_VOLPCNT_LIM      9213
#define SVT_LOLO_VOLUME_LIM       9214
#define SVT_LOLO_WEIGHT_LIM       9215
#define SVT_LOLO_ULLAGE_LIM       9216
#define SVT_LOLO_LEVEL_LIM        9217
#define SVT_LO_LR_LIM             9218
#define SVT_HI_LR_LIM             9220
#define SVT_LEV_CHANGE_ENA        9221
#define SVT_LEV_CHANGE_LIM        9222
#define SVT_LEV_CHANGE_VALUE      9223
#define SVT_LEV_CHANGE_STATE      9224
#define SVT_DNS_DIFF_LIM          9225
                                  
//#define SVT_LO_LR_ENA             9226
//#define SVT_HI_LR_ENA             9227
//#define SVT_DNS_DIFF_ENA          9228

#define SVT_HI_TEMP_AL_ACK        9230
#define SVT_LO_TEMP_AL_ACK        9231
#define SVT_HI_BOT_TEMP_AL_ACK    9232
#define SVT_LO_BOT_TEMP_AL_ACK    9233
#define SVT_HIHI_PRESS_AL_ACK     9234
#define SVT_HI_PRESS_AL_ACK       9235
#define SVT_LO_PRESS_AL_ACK       9236
#define SVT_HI_PRESS_VAC_AL_ACK   9237
#define SVT_LO_PRESS_VAC_AL_ACK   9238
#define SVT_HI_IGP_AL_ACK         9239
#define SVT_LO_IGP_AL_ACK         9240
#define SVT_HI_VAP_RET_AL_ACK     9241
#define SVT_LO_VAP_RET_AL_ACK     9242
#define SVT_XTRA_HI_PRESS_AL_ACK1 9243
#define SVT_XTRA_LO_PRESS_AL_ACK1 9244
#define SVT_XTRA_HI_PRESS_AL_ACK2 9245
#define SVT_XTRA_LO_PRESS_AL_ACK2 9246
#define SVT_HIHI_LEVEL_AL_ACK     9247
#define SVT_HI_LEVEL_AL_ACK       9248
#define SVT_LO_LEVEL_AL_ACK       9249
#define SVT_LOLO_LEVEL_AL_ACK     9250
#define SVT_LEV_CHANGE_AL_ACK     9251


#define SVT_ALARM_SILENCE         9300
#define SVT_ACKNOWLEGDE_ALL       9301


// Tank wash values 9310 - 9350
#define SVT_TWM_SPEED                       9310
#define SVT_TWM_PRESSURE                    9311
#define SVT_TWM_SERIAL_ID				    9312
#define SVT_TWM_ON_OFF_STATUS		        9313
#define SVT_TWM_PRESET_TIME		            9314
#define SVT_TWM_REMAINING_TIME		        9315
#define SVT_TWM_PRESET_TIME_ENABLE          9316
#define SVT_TWM_LOW_SPEED_ENABLE	        9317
#define SVT_TWM_LOW_SPEED_STATUS	        9318
#define SVT_TWM_HEATER_INPUT_TEMP           9319
#define SVT_TWM_HEATER_OUTPUT_TEMP          9320
#define SVT_TWM_HEATER_EFFICIENCY           9321
#define SVT_TWM_FUEL_TON_PER_KWH            9322
#define SVT_TWM_MAN_PRESSURE                9323
#define SVT_TWM_MAN_HEATER_INPUT_TEMP       9324
#define SVT_TWM_MAN_HEATER_OUTPUT_TEMP      9325



// Stabcalc values                         10000
#define SVT_S_DISPLACEMENT                 10001
#define SVT_S_VCG                          10002
#define SVT_S_LIST                         10003
#define SVT_S_TRIM                         10004
#define SVT_S_LIST_ANGLE                   10005
#define SVT_S_TRIM_ANGLE                   10006
#define SVT_S_DFT_MS                       10007
#define SVT_S_LIQ_WGT                      10008
#define SVT_S_SOL_WGT                      10009
#define SVT_S_DFT_MS_P                     10011
#define SVT_S_DFT_MS_S                     10012
#define SVT_S_DFT_F                        10013
#define SVT_S_DFT_A                        10014
#define SVT_S_DFT_MRK                      10015
#define SVT_S_TFS_MOM                      10016
#define SVT_S_TOTAL_L_MOM                  10017
#define SVT_S_TOTAL_T_MOM                  10018
#define SVT_S_TOTAL_V_MOM                  10019
#define SVT_S_VCG_SOL                      10020
#define SVT_S_VCG_ADJ                      10021
#define SVT_S_MAX_VCG                      10022
#define SVT_S_VCG_MARGIN                   10023
#define SVT_S_DAM_MAX_VCG                  10024
#define SVT_S_DAM_VCG_MARGIN               10025
#define SVT_S_IMMERSION                    10026
#define SVT_S_KM                           10027
#define SVT_S_GM_SOL                       10028
#define SVT_S_GM_LIQ                       10029
#define SVT_S_TCF                          10030
#define SVT_S_LCF                          10031
#define SVT_S_LCB                          10032
#define SVT_S_TCG                          10033
#define SVT_S_LCG                          10034
#define SVT_S_GZ                           10035
#define SVT_S_GZ_30                        10036
#define SVT_S_GZ_MAX                       10037
#define SVT_S_GZ_ANGLE                     10038
#define SVT_S_GZ_A0_30                     10039
#define SVT_S_GZ_A30_40                    10040
#define SVT_S_GZ_A0_40                     10041
#define SVT_S_FLOODING_ANGLE               10042
#define SVT_S_DEADWEIGHT                   10043
#define SVT_S_MAX_BM_FRAME_NAME            10044
#define SVT_S_MAX_BM                       10045
#define SVT_S_MAX_SF_FRAME_NAME            10046
#define SVT_S_MAX_SF                       10047
#define SVT_S_REM_TO_FLOODING              10048

// Section values
#define SVT_SEC_DIST_TO_APP                10148
#define SVT_SEC_STEELW                     10149
#define SVT_SEC_LENGTH                     10150
#define SVT_SEC_DEADWEIGHT                 10151
#define SVT_SEC_BUOYANCY                   10152
#define SVT_SEC_DRAFT                      10153
#define SVT_SEC_LOAD                       10154
#define SVT_SEC_MOM_CHANGE                 10155
#define SVT_SEC_AVG_BM                     10156
#define SVT_SEC_AVG_SF                     10157
#define SVT_F_BM                           10160
#define SVT_F_SF                           10161
#define SVT_F_CORR_BM                      10162
#define SVT_F_DIST_TO_FRAME0               10163
#define SVT_F_DIST_TO_PREV                 10164
#define SVT_F_DIST_TO_MIDSHIP              10165
#define SVT_F_BMHRBPRCNT                   10166
#define SVT_F_BMSEAPRCNT                   10167
#define SVT_F_SFHRBPRCNT                   10168
#define SVT_F_SFSEAPRCNT                   10170
#define SVT_L_LCG                          10171
#define SVT_L_TCG                          10172
#define SVT_L_VCG                          10173
#define SVT_L_TFS                          10174
#define SVT_L_FSM                          10175
#define SVT_L_ONLINE_STATUS                10176
#define SVT_L_LENGTH                       10177
#define SVT_LS_L_MOM                       10178
#define SVT_LS_T_MOM                       10179
#define SVT_LS_V_MOM                       10180
#define SVT_LS_WEIGHT                      10181
#define SVT_LS_TRIM_LIST_SOURCE            10182
#define SVT_LS_MANUAL_TRIM                 10183
#define SVT_LS_MANUAL_LIST_DEG             10184
#define SVT_LS_MAX_SUMMER_DRAFT            10185
#define SVT_LS_MAX_SUMMER_DRAFT            10185

#define SVT_IGNORE_VOL_VGT_MESSAGE         10101


#define TAB_TANK_VALUES                     0
#define TAB_ALARM_LIMITS                    1
#define TAB_CARGO_INFO                      2
#define TAB_SENSOR_VALUES                   3
// End Librarian
//
//
//
#define E_LOCAL_ONLY                -1
#define E_NO_ERR                    0
#define E_INPUT_ERR                 1
#define E_DENSITY                   2
#define E_REFTMP                    3
#define E_RT1                       4
#define E_COEFF                     5
#define E_HIGH                      6
#define E_LOW                       7
#define E_USE_API                   8
//#define E_VAL_BIG                 9
//#define E_VAL_SMALL               10
#define E_INVALID_POINTER           11
#define E_ILLEGAL                   12
#define E_UNKNOWN_TANK              13
#define E_AD_NOT_FOUND              14
#define E_NO_TEMP_SENSOR            15
#define E_OUT_OF_RANGE              16
#define E_NO_USE_SYS_SEAW           17
#define E_NO_USE_SYS_BALW           18
#define E_LO_EQ_HI_TMP              19
#define E_USE_OD1                   20
#define E_SELECT_API_TABLE          21
#define E_WRONG_INPUT_FIELD         22
#define E_UNDEFINED_CARGO           23
#define E_RETRY_INPUT               24
#define E_REF_DNS1_TOO_LOW          25
#define E_REF_DNS1_TOO_HIGH         26
#define E_REF_DNS2_TOO_LOW          27
#define E_REF_DNS2_TOO_HIGH         28
#define E_API_OUT_OF_RANGE          29
//#define E_TERMINAL_OFFLINE        30
#define E_SENSOR_ERROR              31
#define E_GAIN_OUT_OF_RANGE         32
#define E_COMMON_INPUT_ERR          33
#define E_NO_USE_SYS_FW             34
#define E_NO_USE_SYS_HFO            35
#define E_NO_USE_SYS_DIESEL         36
#define E_NO_USE_SYS_LUB            37
#define E_LOW_LIMIT_GT_HIGH         38
#define E_HIGH_LIMIT_LS_LOW         39
#define E_HIGH_LIMIT_EQ_LOW         40
#define E_NOT_ADJUSTABLE            41
#define E_NO_INPUT_PERMISSION       42
#define E_SENSOR_IS_DISABELED       43
#define E_NO_OVERRIDE_PERMISSION    44
#define E_USE_API53_TABLE           45
#define E_USE_API54_TABLE           46
#define E_USE_OD2                   47
#define E_NOT_COMMON_INPUT          48
#define E_PLEASE_WAIT               49
#define E_DUPLICATE_NAME            50
#define E_USE_API59_TABLE           51
#define E_USE_API60_TABLE           52

/////////////////////////////////////////////////////////////////
//
// API related constants
// Ref: API Volume X
//
/////////////////////////////////////////////////////////////////

#define D_AIR_ADJ   0.0011

#define API_CONST1      141.5
#define API_CONST2      131.5
#define API_W_DNS60  0.999012   // Water density at 60 fahrenheit
#define API_CONST      (API_CONST1*API_W_DNS60)

#define SI_REFTMP       15.0
#define IP_REFTMP       20.0
#define API_REFTMP      FAHRENHEIT_TO_C(60.0) // 60 Fahrenheit

#define MIN_API             -10.0
#define MAX_API             85.0


#define MIN_MOLMASS     1.0
#define MAX_MOLMASS     100.0

#define MIN_VISCOSITY     0.0
#define MAX_VISCOSITY     100.0

#define A53A_MIN_DNS    0.611
#define A53A_MAX_DNS    1.075
#define A53B_MIN_DNS    0.653
#define A53B_MAX_DNS    1.075
#define A53D_MIN_DNS    0.800
#define A53D_MAX_DNS    1.164
#define A53E_MIN_DNS    0.3517
#define A53E_MAX_DNS    0.6878

#define A54A_MIN_DNS    A53A_MIN_DNS
#define A54A_MAX_DNS    A53A_MAX_DNS
#define A54B_MIN_DNS    A53B_MIN_DNS
#define A54B_MAX_DNS    A53B_MAX_DNS
#define A54D_MIN_DNS    A53D_MIN_DNS
#define A54D_MAX_DNS    A53D_MAX_DNS
#define A54E_MIN_DNS    A53E_MIN_DNS
#define A54E_MAX_DNS    A53E_MAX_DNS

#define A54B_DNS_RANGE1 0.770
#define A54B_DNS_RANGE2 0.788
#define A54B_DNS_RANGE3 0.839


#define A59A_MIN_DNS    0.610
#define A59A_MAX_DNS    1.075
#define A59B_MIN_DNS    0.653
#define A59B_MAX_DNS    1.075
#define A59D_MIN_DNS    0.800
#define A59D_MAX_DNS    1.164
#define A59E_MIN_DNS    0.3317
#define A59E_MAX_DNS    0.6836

#define A60A_MIN_DNS    A59A_MIN_DNS
#define A60A_MAX_DNS    A59A_MAX_DNS
#define A60B_MIN_DNS    A59B_MIN_DNS
#define A60B_MAX_DNS    A59B_MAX_DNS
#define A60D_MIN_DNS    A59D_MIN_DNS
#define A60D_MAX_DNS    A59D_MAX_DNS
#define A60E_MIN_DNS    A59E_MIN_DNS
#define A60E_MAX_DNS    A59E_MAX_DNS


#define A59B_DNS_RANGE1 0.770
#define A59B_DNS_RANGE2 0.788
#define A59B_DNS_RANGE3 0.839

///////////////////////////////////////////////////////////////
//
// Cargo type constants
//
///////////////////////////////////////////////////////////////
#define DEFAULT_SEA_TEMP    15.0

#define DNS_HEAVY_FUEL_OIL  0.95
#define DNS_DIESEL_OIL      0.87
#define DNS_LUBRICANTS      0.92
#define DNS_FRESH_WATER     1.00
#define DNS_SEA_WATER       1.025

#define CTY_NOT_DEFINED         -1
#define CTY_SIMPLE_LIN           0
#define CTY_LINEAR              1
#define CTY_BALLAST             2
#define CTY_HFO                 3
#define CTY_DO                  4
#define CTY_LUB                 5
#define CTY_FW                  6
#define CTY_SEA                 7
#define CTY_API_6A              8
#define CTY_API_6B              9
#define CTY_API_6D              10
#define CTY_API_53A             11
#define CTY_API_53B             12
#define CTY_API_53D             13
#define CTY_API_54A             14
#define CTY_API_54B             15
#define CTY_API_54D             16
#define CTY_API_59A             17
#define CTY_API_59B             18
#define CTY_API_59D             19
#define CTY_API_60A             20
#define CTY_API_60B             21
#define CTY_API_60D             22
#define CTY_API_53E             23
#define CTY_API_54E             24
#define CTY_API_59E             25
#define CTY_API_60E             26

#define CTY_GAS_AMMONIA         27
#define CTY_GAS_BUTADIEN        28
#define CTY_GAS_ISOBUTYLENE     29
#define CTY_GAS_PROPYLENE       30
#define CTY_GAS_PROPENOXIDE     31
#define CTY_GAS_VYNILCHLORIDE   32
#define CTY_GAS_BUTANE          33
#define CTY_GAS_PROPANE         34
#define CTY_GAS_N_BUTANE        35
#define CTY_GAS_ISO_BUTANE      36
#define CTY_GAS_1_BUTANE        37
#define CTY_GAS_CRUDE_C4        38
#define CTY_GAS_RAFFINATE_1     39
#define CTY_GAS_RAFFINATE_2     40
#define CTY_GAS_PROPYLENE_REF   41
#define CTY_GAS_GASOLIE         42
#define CTY_GAS_FLEXICOKER_LPG  43
#define CTY_GAS_SULPHUR_1       44
#define CTY_GAS_SULPHUR_2       45
#define CTY_GAS_SULPHUR_3       46
#define CTY_GAS_SULPHUR_4       47
#define CTY_GAS_SULPHUR_5       48
#define CTY_GAS_SULPHUR_6       49


#define MAX_CARGOTYPES      200
#define CTY_MAX_NAME_LENGTH 40

///////////////////////////////////////////////////////////
//
// Errors related to GetValue
// Primarily used to catch/handle exceptions
//
///////////////////////////////////////////////////////////
#define GETVAL_NO_ERR                0
#define GETVAL_NOT_AVAILABLE         1
#define GETVAL_TANK_EMPTY            2
#define GETVAL_NO_DISPLAY            3
#define GETVAL_ERROR                 4
#define GETVAL_FLOAT_NOT_LEGAL       5
#define GETVAL_INT_NOT_LEGAL         6
#define GETVAL_STRING_NOT_LEGAL      7
#define GETVAL_DRY_SENSOR            8
#define GETVAL_DISABLED              9
#define GETVAL_FWD_AFT              10
#define GETVAL_PORT_STBD            11
#define GETVAL_SHIP_UPRIGHT         12
#define GETVAL_MEASURED_DENSITY_ON  13
#define GETVAL_MEASURED_DENSITY_OFF 14
#define GETVAL_HW_ALARM             15
#define GETVAL_OFFLINE              16
#define GETVAL_NOT_MEASURED         17
#define GETVAL_UNKNOWN_ERROR        18


// Physical constants
#define GRAVITY_AT_LUCAS 981.198      //Sensors calibrated here !!
#define GRAVITY          9.80665      // Was 9.81 // Standard gravity for unit conversion

#define GAS_CONSTANT_HS    22.7
#define GAS_CONSTANT    8.31446        // J/mol Kelvin
#define GAS_MEAN_MOL_WGT 0.028964      // kg mol-1

#define MIN_ATM         (800/MH2O_TO_MBAR)
#define MAX_ATM         (1160/MH2O_TO_MBAR)
#define NORMAL_ATM      (1013/MH2O_TO_MBAR)
#define NORMAL_ATM_MA    8.3
#ifndef PIConst
    #define PIConst 3.1415926535897932385
#endif
#define RAD_FACTOR   (180/PIConst)  // 57.29577951

#define SNS_DEFAULT_WINDOW     0.15
#define SNS_DEFAULT_WINDOW_CNT 2
// Constants for trim, list alarms
#define MAX_TRIM_DIFFERENCE (1/RAD_FACTOR) //0.006981317
#define MAX_LIST_DIFFERENCE (5/RAD_FACTOR) //0.0052359877

// Max range for Seika inclinometers
#define MAX_TRIM    (10/RAD_FACTOR)
#define MAX_LIST    (10/RAD_FACTOR)

///////////////////////////////////////////////////////////
//
// Unit system
//
// DO NOT FORGET:
// UNIT_SETS must be maintained!
//

#define MAX_UNITS       9 // Number of units for for one unit type
#define UNIT_GROUP_NAME_SIZE 20
#define UNIT_NAME_SIZE  9 // Name length

#define NO_UNIT         0
#define U_NO_UNIT       0

///////////////////////////////
// Length
#define LENGTH_UNIT       1
#define U_METER         0
#define U_FEET          1
#define U_DECIMAL_FEET  2

#define FEET_TO_METER       0.3048
#define INCH_TO_METER       0.0254
#define EIGHTS_TO_METER     0.003175

////////////////////////////////
// Volume
#define VOLUME_UNIT       2
#define U_METER3          0
#define U_LITER           1
#define U_USGALLON        2
#define U_USBARRELS       3

#define M3_TO_LITER         1000.0
#define M3_TO_USGALL            264.1720524
#define M3_TO_USBARR            6.289810772
#define VOLUME_UNIT_DEC_P 1

////////////////////////////////
// Weight
#define WEIGHT_UNIT           3
#define U_TON             0
#define U_LONGTON           1
#define U_KNEWTON               2

#define TON_TO_LONGTON      1.0160469088
#define WEIGHT_UNIT_DEC_P 1

////////////////////////////////
// Loadrate
// Uses volume conversion factor
#define LOADRATE_UNIT     4
#define U_M3_HOUR         0
#define U_USBARRELS_HOUR  1

/////////////////////////////////
// Temperature
#define TEMP_UNIT         5
#define U_CELCIUS         0
#define U_FARENHEIT       1

#define FAHRENHEIT_TO_C(TempF) ((TempF-32)/1.8)
#define C_TO_FAHRENHEIT(TempC) (1.8*TempC+32.0)
#define TEMP_ZERO       273.15


///////////////////////////////////////
// Pressure units.
// Pressure is separated into 3 main unit groups, one for Atmospheric
// and vapour pressure, one for liquid pressure and one for line pressure
// This, because it is natural to select different presentation units
// because of different pressure ranges

#define PRESSURE_UNIT1    6
#define PRESSURE_UNIT2    7
#define PRESSURE_UNIT3    8
#define U_METERH2O        0
#define U_MMH2O           1
#define U_MBAR            2
#define U_BAR             3
#define U_PSI             4
#define U_KPA             5
#define U_INCH_H2O        6
#define U_INCH_HG         7

#define MH2O_TO_MMH2O       1000.0
#define MH2O_TO_MBAR        98.0665
#define MH2O_TO_BAR         0.0980665
#define MH2O_TO_PSI         1.422334331
#define MH2O_TO_KPA         9.80665
#define MH2O_TO_INCH_H2O    39.37007874
#define MH2O_TO_INCH_HG     2.89590252

//////////////////////////////////////
// Density
#define DENSITY_UNIT      9
#define U_TON_M3_VAC      0
#define U_TON_M3_AIR      1
#define U_LB_USG          2

#define TM3_TO_LBUSG        8.34523     // ton/m3 to pound/usgallon

///////////////////////////////////////
// Angle unit
#define ANGLE_UNIT        10
#define U_DEGREES         0
#define U_RADIANS         1

///////////////////////////////////////
// Expansion coefficient
#define DNS_COEFF_UNIT    11
#define U_TON_M3_C        0
#define U_TON_M3_F        1
#define U_LBUSG_C         2
#define U_LBUSG_F         3

#define COEFF_C_TO_F    0.555555555555

/////////////////////////////////////////
// Free surface unit
#define FREE_SURF_UNIT  12
#define U_METER4                0
#define U_FEET4               1

/////////////////////////////////////////
// Moment unit
#define MOMENT_UNIT       13
#define U_TON_METER         0
#define U_LTON_FEET         1
#define U_KNEWTON_METER  2

//////////////////////////////////////////
// Immersion unit
#define IMMERSION_UNIT  14
#define U_TON_PER_CM        0
#define U_L_TON_PER_INCH    1

//////////////////////////////////////////
// GZ area unit
#define GZ_AREA_UNIT     15
#define U_METER_RAD         0

//////////////////////////////////////////
// Percent unit
#define PERCENT_UNIT   16
#define U_PERCENT       0
#define U_PROMIL        1

//////////////////////////////////////////
// Current unit
#define CURRENT_UNIT     17
#define U_MAMPERE           0
#define U_AMPERE            1
//////////////////////////////////////////
///
/// Current conversion
#define CNV_MILIAMP_TO_AMP  (1e-3)

//////////////////////////////////////////
// Voltage unit
#define VOLTAGE_UNIT     18
#define U_VOLT            0
#define U_MVOLT           1





//////////////////////////////////////////
// Frequency unit
#define FREQUENCY_UNIT   19
#define U_HZ              0

//////////////////////////////////////////
// Time unit
#define TIME_UNIT        20
#define MSECOND_UNIT     21
#define SECOND_UNIT      22
#define MINUTE_UNIT      23
#define HOUR_UNIT        24
#define DAY_UNIT         25
#define U_MSECONDS       0
#define U_SECONDS        1
#define U_MINUTES        2
#define U_HOURS          3
#define U_TIME_HOURS     4  
#define U_DAYS           5

//////////////////////////////////////////
// Time unit

#define MSEC_TO_SEC      1000.0
#define MIN_TO_MSEC     60000.0
#define SEC_TO_MINUTES     60.0
#define SEC_TO_HOURS     3600.0
#define SEC_TO_DAYS     86400.0

//////////////////////////////////////////
// Molecular mass unit
#define MOL_WEIGHT_UNIT     26
#define U_ATOMIC_M_UNIT     0
// Revolution unit
#define REVOLUTIONS_UNIT	27
#define U_RPM		        0
#define U_RPS		        1
#define U_RPH		        2

// Voscosity unit
#define VISCOSITY_UNIT      28
#define U_PASCAL_SECONDS    0
#define U_POISE             1
#define U_CENTIPOISE        2


#define UNIT_SETS      29 // Number of unit sets

#define LOC_UNIT        0
#define EXTERN_UNIT1    1     //predifined unit set
#define REPORT_UNIT     2
#define UNIT_GROUPS     3

#define STEEL_EXPANSION             0.0012            //  %/^C
#define PT100_OHM_DEG        0.39
#define PT1000_OHM_DEG       3.9
#define TEMP_SENS_CABLE_RES  (2*0.5)       // ohm per meter sensor cable ( MRC Teatrade)
#define SHIP_BOARD_CABLE_RES (2*0.026)     // 26 ohm per km cable

#define BOT_TEMP_DISTANCE_LIMIT 0.5
////////////////////////////////////////////////////////////
//
// MAX MIN limits
//
////////////////////////////////////////////////////////////
#define MAX_DENSITY     3.2
#define MIN_DENSITY     0.4
#define MAX_SW_DENSITY  1.035
#define MIN_SW_DENSITY  0.95
#define MAX_WEIGHT      (MAX_DENSITY*2000.0)
#define DEFAULT_LEVEL_MSRD_DNS 2.0

#define MAX_TEMP        200.0
#define MIN_TEMP        -180.0
#define MAX_WATER_TEMP  45.0
#define MIN_WATER_TEMP  -5.0
#define MAX_ENVIRONMENT_TEMP   70.0
#define MIN_ENVIRONMENT_TEMP  -40.0
#define MAX_GAIN        1.5
#define MIN_GAIN        0.5

#define MAX_COEFF       0.01
#define MIN_COEFF       -0.01

#define LEVEL_NOISE_LIMIT_CARGO_B           0.035
#define LEVEL_NOISE_LIMIT_CARGO_U           0.30
#define LEVEL_NOISE_LIMIT_BALLAST_B         0.10
#define LEVEL_NOISE_LIMIT_BALLAST_U         0.10
#define LEVEL_NOISE_LIMIT_SERVICE_B         0.10
#define LEVEL_NOISE_LIMIT_SERVICE_U         0.10
#define LEVEL_NOISE_LIMIT_DRAFT             0.10
#define LEVEL_NOISE_LIMIT_VOIDSPACE         0.15
#define LEVEL_NOISE_LIMIT_DEFAULT_B         LEVEL_NOISE_LIMIT_BALLAST_B
#define LEVEL_NOISE_LIMIT_DEFAULT_U         LEVEL_NOISE_LIMIT_BALLAST_U
#define LEVEL_NOISE_LIMIT_RADAR             0.020
#define LEVEL_NOISE_LIMIT_RADAR_COMBI       0.200
#define LEVEL_NOISE_LIMIT_METRI_TAPE        0.05
#define LEVEL_NOISE_LIMIT_HSH_LNG_SWITCH    0.01


#define MAX_REF_PRESS_DIFFERENCE            0.15
#define MAX_RADAR_PRESS_SNS_DIFF            0.3
#define RADAR_MIN_DISTANCE_SETTING          0.5

#define MIN_TWM_PRESET_TIME                 0.2
#define MAX_TWM_PRESET_TIME                 24.0
#define DEFAULT_TWM_PRESET_TIME             2.0
#define MIN_TWM_SPEED                       0.2 // RPM
#define MAX_TWM_SPEED                       10.0

/////////////////////////////////////////////////////////////// 
/// 
/// Various constants for energy calculations
/// 
////////////////////////////////////////////////////////////// 
 
#define WATER_HEAT_CAPACITY                 (4.2*1000/3600.0) //1.16418182          //   Average heat capacity from 0°C to 100 °C  kWh/ton
#define MDO_KWH_PER_TON                     11890.0             //   KWH/TON  MGO https://www.engineeringtoolbox.com/fuels-higher-calorific-values-d_169.html
#define WATER_HEATER_DEFAULT_EFFICIENCY     80.0


//Calculate the kilowatt-hours (kWh) required to heat the water using the following formula: 
//Pt = (4.2 × L × T ) ÷ 3600. Pt is the power used to heat the water, in kWh. 
//L is the number of liters of water that is being heated and T is the difference in temperature 
//from what you started with, listed in degrees Celsius
/// 
/// 
/// 
////////////////////////////////////////////////////////////////////////
//
// Alarm limits
//
////////////////////////////////////////////////////////////////////////
#define DEFAULT_ALARM_ON_DELAY  60000
#define DEFAULT_ALARM_OFF_DELAY 60000
#define MIN_ALARM_OFF_DELAY     1000
#define MAX_ALARM_OFF_DELAY     (10*60000)
#define ALARM_SYSTEM_DELAY      (2*60)      // Delay when system starts

#define ALARM_ANPRO10_SYNC_TIMEOUT  20000
// MAX & Min IGP according to NK

#define LIMIT_OVERFILL              98.0
#define LIMIT_HIGH_LEVEL            95.0
#define LIMIT_LOW_LEVEL              5.0
#define LIMIT_LOLO_LEVEL             2.0
#define LIMIT_VOIDSPACE              0.3
#define LIMIT_LEVEL_DIFF             0.3

#define LIMIT_HIGH_TEMP             60.0
#define LIMIT_LOW_TEMP               5.0

#define LIMIT_LEVEL_CHANGE             5

#define LIMIT_HIGH_TANKPRESS        (245.0/MH2O_TO_MBAR)    //245 mBar
#define LIMIT_LOW_TANKPRESS         (-70.0/MH2O_TO_MBAR)    //-70 mBar

#define LIMIT_HIGH_INERT_GAS_PRESS  (100.0 /MH2O_TO_MBAR)    //245 mBar
#define LIMIT_LOW_INERT_GAS_PRESS   (0.1)                   //


#define LIMIT_HIGH_VAPOUR           (100.0/MH2O_TO_MBAR)    // 100  mBar
#define LIMIT_LOW_VAPOUR            (-30.0/MH2O_TO_MBAR)    // -30 mBar

#define LIMIT_HIGH_LINEPRESS        (10.0/MH2O_TO_BAR)
#define LIMIT_HIHI_LINEPRESS        LIMIT_HIGH_LINEPRESS
#define LIMIT_LOW_LINEPRESS         (-1.0/MH2O_TO_BAR)

#define LIMIT_MA_OPEN_LOOP         0.0035
#define LIMIT_MA_SHORT_CIRCUIT    0.0203

#define AL_OFF_DELAY_HIGH_LEVEL       60 // Seconds
#define AL_OFF_DELAY_WATER_INGRESS    60 // Seconds

#define LIMIT_HIGH_LPG_PRESS       (15.0/MH2O_TO_BAR)
#define LIMIT_LOW_LPG_PRESS        (-0.5/MH2O_TO_BAR)


#define HART_STATUS_COM_ERROR_BIT       1
#define HART_STATUS_SHORT_CIRCUIT_BIT   2
#define HART_STATUS_OPEN_LOOP_BIT       4

#define AIR_PURGE_SNS_FAIL              1
#define AIR_PURGE_SYS_FAIL              1
#define AIR_PURGE_FAILURE               2
#define AIR_PURGE_POWER_FAIL            4
#define AIR_PURGE_COMMON_ALM            8
#define AIR_PURGE_LOW_PRESS             16

////////////////////////////////////////////////////////////////
//
// Michellaneous constants for gas calculations
//
////////////////////////////////////////////////////////////////

#define GAS_NONE            -1
#define GAS_AMMONIA         0
#define GAS_BUTADIEN        1
#define GAS_ISOBUTYLENE     2
#define GAS_PROPYLENE       3
#define GAS_PROPENOXIDE     4
#define GAS_VYNILCHLORIDE   5
#define GAS_BUTANE          6
#define GAS_PROPANE         7
#define GAS_N_BUTANE        8
#define GAS_ISO_BUTANE      9
#define GAS_1_BUTANE        10
#define GAS_CRUDE_C4        11
#define GAS_RAFFINATE_1     12
#define GAS_RAFFINATE_2     13
#define GAS_PROPYLENE_REF   14
#define GAS_GASOLIE         15
#define GAS_FLEXICOKER_LPG  16
#define GAS_SULPHUR_1       17
#define GAS_SULPHUR_2       18
#define GAS_SULPHUR_3       19
#define GAS_SULPHUR_4       20
#define GAS_SULPHUR_5       21
#define GAS_SULPHUR_6       22




////////////////////////////////////////////////////////////////
//
//  Constants for Sensor adjust input system
//  Created 24/10/02 EHS/RB
//
////////////////////////////////////////////////////////////////
#define SNS_ADJUST_ABORT                    0
#define SNS_ADJUST_ONLY_INP                 1
#define SNS_ADJUST_GAIN                     2
#define SNS_ADJUST_OFFSET                   3

#define SNS_ADJUST_GAIN_THRESHOLD           2.5
#define SNS_ADJUST_MAX_GAIN                 1.01
#define SNS_ADJUST_MIN_GAIN                 0.99
#define SNS_ADJUST_MAX_OFFSET_CHANGE        0.1
#define SNS_ADJUST_ATM_MAX_OFFSET_CHANGE    0.2
#define SNS_ADJUST_VAPOR_MAX_OFFSET_CHANGE  10.0


#define SNS_ADJUST_LP_GAIN_THRESHOLD        75.0
#define SNS_ADJUST_LP_MAX_GAIN              1.05
#define SNS_ADJUST_LP_MIN_GAIN              0.95
#define SNS_ADJUST_LP_MAX_OFFSET_CHANGE     5.0

#define SNS_ADJUST_INC_MAX_OFFSET_CHANGE    10.0


///////////////////////////////////////////////////////////
//
//  Constants for status text
//
///////////////////////////////////////////////////////////
// Constants used in the librarian
#define ST_TXT_0_1              0
#define ST_TXT_ON_OFF       1
#define ST_TXT_EN_DIS       2
#define ST_TXT_OP_CLO       3
#define ST_TXT_NO_YES       4
#define ST_TXT_AUTO_MAN     5
#define ST_TXT_CAL_SELECT   6
#define ST_TXT_ERROR_STAT   7

///////////////////////////////////////////////////////////
//
//  Saab protocol constants
//
///////////////////////////////////////////////////////////


#define SAAB_ENTRIES        25
#define SAAB_BUF_SIZE       512
#define SAAB_MIN_PACKET     8
#define SAAB_MAX_TANKS      100
#define SAAB_INT_INDEX      0
#define SAAB_EXT_INDEX      1
#define SAAB_OBJ_INFO       2
#define SAAB_OBJ_ERROR      -1
#define SAAB_TANKVAL        0
#define SAAB_TPRESSVAL      1
#define SAAB_LPRESSVAL      2
#define SAAB_TEMPERATURE    3
#define SAAB_SPECIAL        4
#define SAAB_ACT_NORMAL     0
#define SAAB_ACT_SPECIAL    1
#define SAAB_ACT_ERROR      -1



/////////////////////////////////////////////////////////////
//
// AnsiString related constants
//
/////////////////////////////////////////////////////////////

#ifdef WIN32
#define ANSI_STRING_START_INDEX 1
#else
#define ANSI_STRING_START_INDEX 0
#endif



/////////////////////////////////////////////////////
//
// Water sensor(Water ingress) related
// constants
//
/////////////////////////////////////////////////////

#define WSENSOR_NO_SENSOR   0
#define WSENSOR_CARGO   1
#define WSENSOR_WATER       2
#define WSENSOR_EMPTY       3
#define WSENSOR_LOW_LEVEL       4
#define WSENSOR_DISABLE     5
#define WSENSOR_FAILURE     6

//////////////////////////////////////////////////////////
//
// Sensor related constants
//
//

#define AI_SENSOR_NOT_DEFINED   0
#define AI_SENSOR_PRESS         1
#define AI_SENSOR_TEMP          2
#define AI_SENSOR_RADAR         3
#define AI_SENSOR_FLOAT         4
#define AI_SENSOR_VOLT          5
#define AI_SENSOR_WATER_INGRESS 6
#define AI_SENSOR_FUSE          7
#define AI_SENSOR_AC_AVALABLE   8
#define AI_SENSOR_LEVEL         9
#define AI_SENSOR_INCLINOMETER 10
#define AI_SENSOR_REVOLUTIONS  11


///////////////////////////////////////////////////////////
//
//  Watchdog constants
//
///////////////////////////////////////////////////////////
#define WATCHDOG_RELOAD_DELAY       100
#define WATCHDOG_TASK_DELAY         1000
#define WD_NO_SIGNAL                0x0
#define WD_SYSTEM_RUNNING           0x01
#define WD_SYSTEM_KILL              0x02
#define WD_STOP                     0x04
#define WD_START                    0x08
#define WD_RESTART                  0x10
#define WD_FACTORY_DEFAULT          0x20
#define WD_FLASH_WRITE		        0x40
#define WD_ANY_SIGNAL               0x3f

#define WD_BOOTLOADER_START         0x01
#define WD_BOOT_START_MAIN          0x02
#define WD_BOOT_START_OS            0x03
#define WD_BOOT_INIT_COMPORTS       0x04
#define WD_BOOT_START_COM_TASKS     0x05
#define WD_BOOTLOADER_COPY          0x06
#define WD_BOOT_MMU_INIT            0x07
#define WD_BOOT_INIT_KERNEL         0x08
#define WD_MAIN_START               0x10
#define WD_START_OS                 0x11
#define WD_START_EMWIN              0x12
#define WD_READ_CONFIG              0x13
#define WD_START_TASKS              0x14
#define WD_CONFIG_WARNING           0x15
#define WD_INIT_TDU_COMPORTS        0x16
#define WD_START_WIN_TASKS          0x17
#define WD_START_COM_TASKS          0x18
#define WD_START_MISC_TASKS         0x19
#define WD_START_INT_AD_TASKS       0x1a
#define WD_START_SYSINFO_TASKS      0x1b
#define WD_START_STATIC_TASKS       0x1c
#define WD_START_TPCX_TASKS         0x1d
#define WD_MMU_INIT                 0x1e
#define WD_INIT_KERNEL              0x1f
#define WD_START_AGAIN              0x20
#define WD_START_OK                 0x21
#define WD_ERASE_FLASH              0x22
#define WD_WRITE_FLASH              0x23
#define WD_POWER_ON                 0x00

#define WD_SETTINGS_OK              0x00
#define WD_SETTINGS_READ            0x01
#define WD_SETTINGS_WRITE           0x02
#define WD_CONFIG_WRITE             0x03
#define WD_OTHER_WRITE              0x04

#ifdef ANBOOTLOADER
    #define WD_OK_STATUS   WD_BOOT_START_OS
#else
    #define WD_OK_STATUS     WD_START_OK
#endif



///////////////////////////////////////////////////////////
//
// Save settings/config Signal constants
//
///////////////////////////////////////////////////////////
#define FLASH_WRITE_CONFIG_DELAY    0x01
#define FLASH_WRITE_CONFIG_NO_DELAY 0x02
#define FLASH_SAVE_SETTINGS         0x01
//#define FLASH_SAVE_OTHER            0x02


///////////////////////////////////////////////////////////
//
//  Alarm constants
//
///////////////////////////////////////////////////////////
#define AL_MODE_DEFAULT             0

#define AL_STAT_IN_NORMAL           0
#define AL_STAT_IN_ALARM            1
#define AL_STAT_IN_DEADBAND         2


///////////////////////////////////////////////////////////
//
//  Level switch constants
//
// Valcom
// API
//
///////////////////////////////////////////////////////////
#define LEVELSWITCH_VOLT_LIMIT  1.0 // Volt
#define LEVELSWITCH_API_MA_ON       0.007
#define LEVELSWITCH_API_MA_OFF      0.014
#define LEVELSWITCH_API_MA_WIN      0.002

#define LEVELSWITCH_VALCOM_MA_ON    0.005
#define LEVELSWITCH_VALCOM_MA_OFF   0.013
#define LEVELSWITCH_VALCOM_MA_WIN   0.002

#define LEVELSWITCH_VEGA62_MA_ON    0.0010
#define LEVELSWITCH_VEGA62_MA_OFF   0.0035
#define LEVELSWITCH_VEGA62_MA_WIN   0.0005
#define LEVELSWITCH_VEGA62_MA_TEST  0.000

#define LEVELSWITCH_VEGA64_MA_ON    0.0158
#define LEVELSWITCH_VEGA64_MA_OFF   0.0058
#define LEVELSWITCH_VEGA64_MA_WIN   0.0005
#define LEVELSWITCH_VEGA64_MA_TEST  0.000

#define LEVELSWITCH_HS_MA_ON        0.01961
#define LEVELSWITCH_HS_MA_OFF       0.01475
#define LEVELSWITCH_HS_MA_WIN       0.0022
#define LEVELSWITCH_HS_MA_TEST      0.0055
#define LEVELSWITCH_HS_MA_LIGHT     0.01039
#define LEVELSWITCH_HS_MA_DEAD      0.0001



#define LEVELSWITCH_OFF             0
#define LEVELSWITCH_ON              1
#define LEVELSWITCH_ERROR           2
#define LEVELSWITCH_HW_ERROR        3
#define LEVELSWITCH_TEST            4
#define LEVELSWITCH_LIGHT           5
#define LEVELSWITCH_ERROR_CNT       12

///////////////////////////////////////////////////////////
//
// Filters
//
///////////////////////////////////////////////////////////
#define FILTER_DEFAULT          1
#define FILTER_LEVEL_SWITCH     0
#define FILTER_MA_PRESS         1
#define FILTER_MA_PRESS_PSM     3
#define FILTER_MA_TEMP          1
#define FILTER_MA_RADAR         1
#define FILTER_METRIC_TAPE      4
#define FILTER_DRAFT            15
#define FILTER_LEVEL_DIFFERENCE 15
#define FILTER_LEVEL_CHANGE     15

/////////////////////////////////////////////////////////
//
// Sensor value window system
//
//////////////////////////////////////////////////////////

#define MAX_OUTSIDE_WIN_CNT     20
#define MAX_OUTSIDE_LEVEL_LIM   0.25
#define MAX_OUTSIDE_TEMP_LIM    5.0


///////////////////////////////////////////////////////////
//
//  Misc constants
//
///////////////////////////////////////////////////////////


#define BUZZER_TEST_PRESSED     1
#define BUZZER_TEST_RELEASED    2

#define BUZZER_NO_TEST              0
#define BUZZER_TEST_ON              1
#define BUZZER_TEST_OFF             2

#define START_DELAY                         10000

#define IO_STATUS_REQ_DELAY     15
#define INT_AD_CON_WAIT_CYCLES  20

// UART related constants

#define UART_BYTE_COUNT_TIME        30000

#define MAX_COM_PORTS                   7
#define FIRST_ST16554_PORT          3
#define PRINTER_BAUDRATE        19200

#define FILTER_INTERNAL_VOLTAGE 5.0

#define GSTAT_PWRST  0x01
#define GSTAT_OFFRST 0x02
#define GSTAT_WDTRST 0x04

#define FLASH_UPLOAD_MAX_MSGS      10             // Max number of concurrent upload requests

#define SVT_FLAG_NORMAL             0
#define SVT_FLAG_ONLY_NUMBER        1
#define SVT_FLAG_NO_VAL_NO_VAL      2   // If no value return no value
#define SVT_FLAG_MARK_NO_VAL        3   // If no value return *****

#define DEFAULT_LOAD_TIME   24.0

#define ANPRO3_DEFAULT_DELAY    1000
#define EXTERNAL_ALARM_SILENCE      1

#define DATA_EXPIRATION_TIME    (5*RS485_IO_PERIODE)
#define SEND_MIN_INTERVAL       250
#define MODBUS_UPDATE_INTERVAL  2000

/////////////////////////////////////////////////////
//
//  Internal AD-converter and voltage adjust
//
/////////////////////////////////////////////////////

#define INT_ATM_REF_FILTER          100.0
#define TCU_MIN_ADJUST_VOLTAGE  20.0
#define TCU_MAX_ADJUST_VOLTAGE  27.0
#define TCU_TARGET_VOLTAGE          24.0
#define TCU_VOLTAGE_WINDOW          0.15
#define TCU_AL_LO_VOLTAGE           (TCU_MIN_ADJUST_VOLTAGE -0.5)
#define TCU_AL_HI_VOLTAGE           (TCU_MAX_ADJUST_VOLTAGE +0.5)


/////////////////////////////////////////////////////
//
// Logging constants
//
/////////////////////////////////////////////////////

#define LOG_MAX_TIME        24.0
#define LOG_MIN_TIME        5.0/60.0

/////////////////////////////////////////////////////
//
// Report constants
//
/////////////////////////////////////////////////////
#define REPORT_BALLAST          0
#define REPORT_CARGO            1
#define REPORT_SERVICE          2
#define REPORT_TEMPERATURE      3
#define REPORT_T_PRESSURE       4
#define REPORT_L_PRESSURE       5
#define REPORT_VOIDSPACE        6
/////////////////////////////////////////////////////
//
// Touch screen control
//
/////////////////////////////////////////////////////

#define TOUCH_PRESWIN_FLAG 0x01
#define TOUCH_ALARMWIN_FLAG 0x02

#define TOUCH_SCREEN_UP         0x01
#define TOUCH_SCREEN_DOWN   0x02
#define TOUCH_SCREEN_DOWN_UP (TOUCH_SCREEN_DOWN | TOUCH_SCREEN_UP)
#define CONVERT_COMPLETE    0x04

#define DEFAULT_SCREEN_OFF_DELAY (30*MIN_TO_MSEC)
#define TOUCH_MAX_TIMEOUT       120
#define TOUCH_MIN_TIMEOUT       1





////////////////////////////////////////////////////////
//
// Boot loader constants
//
////////////////////////////////////////////////////////
#define BOOTLOADER_START_APP      0x0
#define BOOTLOADER_NO_START       0x1
#define BOOTLOADER_DELAY          5000



/////////////////////////////////////////////////////////////
//
//  Task priorities
//
/////////////////////////////////////////////////////////////
#define WATCHDOG_TASK_PRIORITY      5
#define TPCX_TASK_PRIORITY          50
#define ANPRO10_TASK_PRIORITY       95
#define SAAB_TASK_PRIORITY          130
#define COM_SEND_TASK_PRIORITY      140
#define MODBUS_TASK_PRIORITY        170
#define CALCULATE_OBJ_TASK_PRIORITY 90



/////////////////////////////////////////////////////////////
//
//  Network related constants
//
/////////////////////////////////////////////////////////////
#define NETWORK_TASK_PRIORITY      190
#define NETWORK_IRQ_SIGNAL          1

/////////////////////////////////////////////////////////////
//
// Screen colours
//
/////////////////////////////////////////////////////////////
#if (defined(S2TXU)||defined(ANTDUSIM)) && defined(__cplusplus)
namespace Graphics
{
    enum TColor {
        clMin=-0x7fffffff-1, clMax=0x7fffffff
    };
}

    #if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Graphics;
    #endif

static const TColor clScrollBar                     = (TColor)0x80000000;
static const TColor clBackground                    = (TColor)0x80000001;
static const TColor clActiveCaption             = (TColor)0x80000002;
static const TColor clInactiveCaption       = (TColor)0x80000003;
static const TColor clMenu                              = (TColor)0x80000004;
static const TColor clWindow                            = (TColor)0x80000005;
static const TColor clWindowFrame               = (TColor)0x80000006;
static const TColor clMenuText                      = (TColor)0x80000007;
static const TColor clWindowText                    = (TColor)0x80000008;
static const TColor clCaptionText               = (TColor)0x80000009;
static const TColor clActiveBorder              = (TColor)0x8000000a;
static const TColor clInactiveBorder            = (TColor)0x8000000b;
static const TColor clAppWorkSpace              = (TColor)0x8000000c;
static const TColor clHighlight                     = (TColor)0x8000000d;
static const TColor clHighlightText             = (TColor)0x8000000e;
static const TColor clBtnFace                       = (TColor)0x8000000f;
static const TColor clBtnShadow                     = (TColor)0x80000010;
static const TColor clGrayText                      = (TColor)0x80000011;
static const TColor clBtnText                       = (TColor)0x80000012;
static const TColor clInactiveCaptionText   = (TColor)0x80000013;
static const TColor clBtnHighlight              = (TColor)0x80000014;
static const TColor cl3DDkShadow                    = (TColor)0x80000015;
static const TColor cl3DLight                       = (TColor)0x80000016;
static const TColor clInfoText                      = (TColor)0x80000017;
static const TColor clInfoBk                            = (TColor)0x80000018;

static const TColor clBlack                         = (TColor)0x0;
static const TColor clWhite                         = (TColor)0xffffff;
static const TColor clMaroon                        = (TColor)0x80;
static const TColor clGreen                         = (TColor)0x8000;
static const TColor clOlive                         = (TColor)0x8080;
static const TColor clNavy                          = (TColor)0x800000;
static const TColor clPurple                        = (TColor)0x800080;
static const TColor clTeal                          = (TColor)0x808000;
static const TColor clGray                          = (TColor)0x808080;
static const TColor clSilver                        = (TColor)0xc0c0c0;
static const TColor clRed                           = (TColor)0xff;
static const TColor clLime                          = (TColor)0xff00;
static const TColor clYellow                        = (TColor)0xffff;
static const TColor clBlue                          = (TColor)0xff0000;
static const TColor clFuchsia                       = (TColor)0xff00ff;
static const TColor clAqua                          = (TColor)0xffff00;
static const TColor clLtGray                        = (TColor)0xc0c0c0;
static const TColor clDkGray                        = (TColor)0x808080;

#endif


/////////////////////////////////////////////////////////////////
//
// Calibration data, Constants related to sensor EEProm
//
/////////////////////////////////////////////////////////////////
#define ID_LENGTH               11
#define MAX_CALDATA             4
#define APREG_SIZE              8
#define EEPROM_SIZE             40


#define SO_P0                   0
#define SO_P40                  1
#define SO_P60                  2
#define SO_P100                 3

#define AD_NO_EEPROM            0
#define AD_EEPROM_OK            1
#define AD_EEPROM_ERROR         2
#define AD_NOT_USED             3


#define AD_OK_FROM_PC           1
#define AD_ERROR_FROM_PC        2

// Constants defined in ANPROT1, command 20
#define AD_USE_PC_INFO          4
#define AD_NO_SNS               0
#define AD_TEMP_SNS             1
#define AD_OTHER_SNS            2
#define AD_PRESS_SNS            3
#define AD_SNS_TYPES            4


////////////////////////////////////////////////////////////////////
//
//      ANPRO3 related constants
//
////////////////////////////////////////////////////////////////////

#define ANPRO3_MAX_SIZE                 1024 // Buffer size
#define ANPRO3_NO_CHECKSUM              0
#define ANPRO3_CHECKSUM                     1
#define ANPRO3_CHECKSUM_INC_SYNC        2

#define ANPRO3_CMD_TANK_OUT         1
#define ANPRO3_CMD_SYSTEM_OUT       2
#define ANPRO3_CMD_LINE_OUT         3
#define ANPRO3_CMD_OP_DNS1          4
#define ANPRO3_CMD_REF_TMP1         5
#define ANPRO3_CMD_OP_DNS2          6
#define ANPRO3_CMD_REF_TMP2         7
#define ANPRO3_CMD_COEFF            8
#define ANPRO3_CMD_DENSITY_IN       9
#define ANPRO3_CMD_DENSITY_OUT      10
#define ANPRO3_CMD_CARGO_TYPE       11
#define ANPRO3_CMD_LEVEL_FC         12
#define ANPRO3_CMD_LEVEL            13
#define ANPRO3_CMD_ULLAGE_FC        14
#define ANPRO3_CMD_ULLAGE           15
#define ANPRO3_CMD_VOLUME           16
#define ANPRO3_CMD_WEIGHT           17
//#define ANPRO3_CMD_DENSITY          18
#define ANPRO3_CMD_TEMP             19
#define ANPRO3_CMD_VAPOUR           20
#define ANPRO3_CMD_ACT_ALARMS       21
#define ANPRO3_CMD_SEAWATER_DNS     22
#define ANPRO3_CMD_BALLAST_DNS      23
#define ANPRO3_CMD_TRIM_DEG         24
#define ANPRO3_CMD_LIST_DEG         25
#define ANPRO3_CMD_DF               26
#define ANPRO3_CMD_DP               27
#define ANPRO3_CMD_DS               28
#define ANPRO3_CMD_DA               29
#define ANPRO3_CMD_LPRESS           30
#define ANPRO3_CMD_TEMP_OUT         31
#define ANPRO3_CMD_SYSALL           32
#define ANPRO3_CMD_LC_VOLUME        33
#define ANPRO3_CMD_LC_WEIGHT        34
#define ANPRO3_CMD_SOUNDING         35
#define ANPRO3_CMD_ULLAGE_UTI       36





////////////////////////////////////////////////////////////
//
//  Internal Relay control related constants
//
/////////////////////////////////////////////////////////////
#define NUMBER_OF_RELAY_TASKS   6

#define RELAY_MSG_OFF           0
#define RELAY_MSG_ON            1
#define RELAY_MSG_FREQUENCY     2
#define RELAY_MSG_DELAYED       3

#define RELAY_BUZZER            0
#define RELAY_LIGHT             1
#define RELAY_LAMP              2
#define RELAY_HORN              3
#define RELAY_1                 4
#define RELAY_2                 5

///////////////////////////////////////////////////////////////////
//
//  Constants related to the flash file system
//  Used primarely in FlashFileSystem.cpp
//
///////////////////////////////////////////////////////////////////
#define BLOCK_IS_UNUSED     0xffffffff
#define BLOCK_IS_RESERVED   0xfffffffe
#define BLOCK_IS_OK         0xfffffffc



///////////////////////////////////////////////////////////////////
//
//  Memory
//
///////////////////////////////////////////////////////////////////
#define _RAM_STARTADDRESS       0x30000000
//#define _NONCACHE_STARTADDRESS    0x31000000 // Not used in TXU
//#define _ISR_STARTADDRESS       0x33ffff00   // Not used in TXU
#define _MMUTT_STARTADDRESS     0x31ff8000
//#define _STACK_BASEADDRESS    0x33ff8000   // Not used in TXU
//#define HEAPEND               0x33ff0000   // Not used in TXU
#define LCD_RAM_SIZE            0x400000      // 4 MB RAM
// LCD start address must be on a 4 MB boundry, 0x400000
#define LCD_STARTADDRESS        0x31b00000
#define LCD_STARTADDRESS_PHY    (0x31b00000+0x1800000)



///////////////////////////////////////////////////////////////////
//
//  Inclinometers
//
///////////////////////////////////////////////////////////////////

#define ROL_MAX_INCLINOMETER_BUFFERS    8
#define ROL_MIN_FREQ_CALC_ANGLE         (0.2/RAD_FACTOR)
#define ROL_LIST_LOG_INTERVAL           500
#define ROL_LIST_ENTRIES                (256)


///////////////////////////////////////////////////////////////////
//
//  Windows related constants
//
///////////////////////////////////////////////////////////////////
#if defined(S2TXU) | defined(ANBOOTLOADER)
#define IGNORE              0       // Ignore signal
#define INFINITE            0xFFFFFFFF  // Infinite timeout
#endif

//---------------------------------------------------------------------------
#endif





