#ifndef TSNVERSION_H
#define TSNVERSION_H
/********************************************************************
*
*  Program versions: 2.x.y.z
* Surveyor product number, Packet compatibility,
* Major change (i.e. new objects), Minor change (i.e. Bug fix)
*
**********************************************************************/

// Commond:
#define VERSION_PACKET          6  // Packet compatibility, Must be same for all program

// Spesified:
//#define VERSION_PROD_NO         0  // Tanksystem product number
//#define VERSION_TXU_NEW_FUNC    3  // Major change (i.e. new objects)
//#define VERSION_TXU_BUG_FIX     2 // Minor change (i.e. Bug fix)
                                                                            //
#define VERSION_PROD_NO         2  // Tanksystem product number
#if 0 // hkim
#define VERSION_TXU_NEW_FUNC    7  // Major change (i.e. new objects)
#define VERSION_TXU_BUG_FIX     40   // Minor change (i.e. Bug fix)
#else
#define VERSION_TXU_NEW_FUNC    8  // Major change (i.e. new objects)
#define VERSION_TXU_BUG_FIX     9   // Minor change (i.e. Bug fix)
#endif

#define VERSION_BOOT_NEW_FUNC   0  // Major change (i.e. new objects)
#define VERSION_BOOT_BUG_FIX    1  // Minor change (i.e. Bug fix)

#define VERSION_FLASH_NEW_FUNC  7  // Major change (i.e. new objects)
#define VERSION_FLASH_BUG_FIX   2  // Minor change (i.e. Bug fix)

#define VERSION_CONFIG_NEW_FUNC 3  // Major change (i.e. new objects)
#define VERSION_CONFIG_BUG_FIX  0  // Minor change (i.e. Bug fix)

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
***********************************************************/
#define VERSION_ANZB_PROG       40
#define VERSION_ANZB_COMP       1
#define VERSION_ANZB_EEPROM     2
#endif
