#ifndef TSNVERSION_H
#define TSNVERSION_H
/********************************************************************
*
*  Program versions: 2.x.y.z
* Surveyor product number, Packet compatibility,
* Major change (i.e. new objects), Minor change (i.e. Bug fix)
*
**********************************************************************/
/* Versions
   2: Changes are:
    - compiler settings for CS8900 interface code to optimize for speed
    - Bottom temperature alarm added
   4: Changes are: compiler settings for CS8900 interface code to no optimze
   */
// Commond:
#define VERSION_PACKET          14  // Packet compatibility, Must be same for all program, now also used as 2nd number in program version number

// Spesified:
//#define VERSION_PROD_NO         0  // Tanksystem product number
//#define VERSION_TXU_NEW_FUNC    3  // Major change (i.e. new objects)
//#define VERSION_TXU_BUILD_NO     2 // Minor change (i.e. Bug fix)
                                                                            //
#define VERSION_PROD_NO         2  // Major version number, Tanksystem product number
#define VERSION_TXU_NEW_FUNC    10  // Minor version number and/or change of packet format (i.e. new objects)
#define VERSION_TXU_BUILD_NO    38 // Build number

#define VERSION_BOOT_NEW_FUNC   9  // Minor version number and/or change of packet format (i.e. new objects)
#define VERSION_BOOT_BUG_FIX    1  // Build number

#define VERSION_FLASH_NEW_FUNC  0  // Minor version number and/or change of packet format (i.e. new objects)
#define VERSION_FLASH_BUG_FIX   1  // Minor change (i.e. Bug fix)

#define VERSION_CONFIG_NEW_FUNC 3  // Minor version number and/or change of packet format (i.e. new objects)
#define VERSION_CONFIG_BUG_FIX  0  // Build number
 
// Note that the version numbers for ANWin is set via the "Project options" in the
// C++ builder
#define VERSION_WIN_NEW_FUNC        3  // Major change (i.e. new objects)
#define VERSION_WIN_BUG_FIX         2  // Minor change (i.e. Bug fix)

/***********************************************************************
* Config Compatibility Number
* in Config info, used for compatibility check between
* units in the system
***********************************************************************/
#define CONFIG_COMPATIBILITY_NO   0

/***********************************************************************
*
***********************************************************************/

/*********************************************************
*
*   ZBANA and ZB485 version numbers
* This number should match the verion number for ANZB_x_Bin.c
* x is the version number
*
* Boot versions AN-ZBANA and AN-ZB485
* Atmega 128    : Up to 40
* AtMega 1281   : 40 and upwards
*
* Program version AN-ZBANA and AN-ZB485:
* Atmega 128    : Up to 40
* Atmega 1281   : 40 to 79 for current revision of PCB
***********************************************************/
#define VERSION_ANZB_1281_BOOT          40      // 
#define VERSION_ANZB_1281_PROG_FIRST    100
#define VERSION_ANZB_1281_PROG          (VERSION_ANZB_1281_PROG_FIRST+1)     // Various fixes for stability
#define VERSION_ANZB_1281_PROG_NO_BOOT_START  41
#define VERSION_ANZB_1281_PROG_NO_BOOT_END    45
#define VERSION_ANZB_128_BOOT           12      // 
#define VERSION_ANZB_128_PROG           40

#define VERSION_ANZB_COMP           1
#define VERSION_ANZB_EEPROM         2

/*********************************************************
*
*   ZBHART version numbers
* This number should match the verion number for ANZB_x_Bin.c
* x is the version number
*
***********************************************************/
#define VERSION_ANZBHART_1280_PROG  16
#define VERSION_ANZBHART_COMP       2
#define VERSION_ANZBHART_EEPROM     3

#endif

