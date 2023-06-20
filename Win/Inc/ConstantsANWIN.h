#ifndef CONSTANTS_ANWIN_H
#define CONSTANTS_ANWIN_H
//Constants for ANWIN gui

#define PROJECT             00
#define ALARM               01

#define CARGO_APPL                  20
#define CARGO_TANKPLAN      21
#define CARGO_GROUP             22
#define CARGO_BARGRAPH          23
#define CARGO_DETAIL                24
#define CARGO_SELECT                25
#define CARGO_REPORT                26
#define CARGO_TYPE          27

#define BALLAST_APPL            30
#define BALLAST_TANKPLAN        31
#define BALLAST_GROUP           32
#define BALLAST_BARGRAPH        33
#define BALLAST_DETAIL          34
#define BALLAST_SELECT          35
#define BALLAST_REPORT          36

#define SERVICE_APPL            40
#define SERVICE_TANKPLAN        41
#define SERVICE_GROUP           42
#define SERVICE_BARGRAPH        43
#define SERVICE_DETAIL          44
#define SERVICE_SELECT          45
#define SERVICE_REPORT          46

#define TANKPRESS_APPL          50
#define TANKPRESS_TANKPLAN      51
#define TANKPRESS_GROUP         52

#define TEMP_APPL               60
#define TEMP_TANKPLAN           61
#define TEMP_GROUP              62

#define LPRESS_APPL             70
#define LPRESS_TANKPLAN         71
#define LPRESS_GROUP            72

#define VOIDSPACE_APPL          80
#define VOIDSPACE_TANKPLAN      81
#define VOIDSPACE_GROUP         82
#define VOIDSPACE_BARGRAPH      83
#define VOIDSPACE_DETAIL        84
#define VOIDSPACE_SELECT        85
#define VOIDSPACE_REPORT        86

#define LOADCALC_APPL           90
#define LOADCALC_WIN            91

#define WASHINGMACHINES_APPL    100
#define WASHINGMACHINES_GROUP	101
#define WASHINGMACHINES_LOG		102
#define WASHINGMACHINES_TANKPLAN 103

#define VAPOUR                  14
#define LINE_PRESSURE           15
#define LOAD_CALC               16
#define VALVE_CONTROLL          17
#define PUMP_CONTROLL           18
#define HIGH_HIGH_ALARM         19
#define HIGH_ALARM              13



#define GRID_COLUMNS        20
#define GRID_REPORT_COLS    16

#define MAX_TANK_TABLE_SIZE   100
#define MAX_TANK_OBJ_ACKTIVE    100
#define MAX_COLOR_CARGO_TYPES 110

//#define MAXDOUBLE   1.797693E+308
#define MAXFLOAT    3.37E+38F
#define MINDOUBLE   2.225074E-308
#define MINFLOAT    8.43E-37F

#define MAX_UDP_SIZE 1400
#define PACKET_INFO_SIZE (3*sizeof(int))
#define MAXDIR 256

#define TAG_VALUE       0
#define TAG_VALUE_NAME  1
#define TAG_UNIT_NAME   2
#endif
