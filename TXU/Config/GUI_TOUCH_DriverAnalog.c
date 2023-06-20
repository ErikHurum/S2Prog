/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2006  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.06 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUITOUCH.C
Purpose     : Touch screen manager
----------------------------------------------------------------------
This module handles the touch screen. It is configured in the file
GUITouch.conf.h (Should be located in the Config\ directory).
----------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LCD_Private.h"      /* private modul definitions & config */
//#include "GUI_Protected.h"
#include "2410addr.h"       // inserted by TSN
#include "TSNVersion.h"
#include "FixedVariables.h"


/////////////////////////////////////////////////////////
//
// From TXU_TROSINIT.c
//
/////////////////////////////////////////////////////////
extern volatile unsigned char TouchKeyPressed ;	 //key status
unsigned volatile char PhysKeyPressed=0;

extern volatile U16  TXUADData[];

/* Generate code only if configuration says so ! */
#if GUI_SUPPORT_TOUCH

	#include "GUITouchConf.h"    /* Located in GUIx, will include GUITouchConf.h */

/*********************************************************************
*
*       Defines, config defaults
*
**********************************************************************
*/
	#ifndef GUI_TOUCH_AD_MAX_DIFF
		#define GUI_TOUCH_AD_MAX_DIFF 30
	#endif

	#ifndef GUI_TOUCH_MIRROR_Y
		#define GUI_TOUCH_MIRROR_Y 0
	#endif

	#ifndef GUI_TOUCH_YSIZE
		#define GUI_TOUCH_YSIZE LCD_YSIZE
	#endif

	#ifndef GUI_TOUCH_XSIZE
		#define GUI_TOUCH_XSIZE LCD_XSIZE
	#endif


/*********************************************************************
*
*       Types
*
**********************************************************************
*/

typedef struct {
	int Min; int Max;
} tMinMax;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static int xPhys, yPhys;

static tMinMax xyMinMax[ 2 ][ 2 ] = {
#if ((GUI_TOUCH_SWAP_XY==0) && (GUI_TOUCH_MIRROR_X==0)) || ((GUI_TOUCH_SWAP_XY) && (GUI_TOUCH_MIRROR_Y==0))
    {{ GUI_TOUCH_AD_LEFT1, GUI_TOUCH_AD_RIGHT1 },{ GUI_TOUCH_AD_LEFT2, GUI_TOUCH_AD_RIGHT2 } },
#else
    {{ GUI_TOUCH_AD_RIGHT1, GUI_TOUCH_AD_LEFT1 },{ GUI_TOUCH_AD_RIGHT2, GUI_TOUCH_AD_LEFT2 } },
#endif
#if ((GUI_TOUCH_SWAP_XY==0) && (GUI_TOUCH_MIRROR_Y==0)) || ((GUI_TOUCH_SWAP_XY) && (GUI_TOUCH_MIRROR_X==0))
    {{ GUI_TOUCH_AD_TOP1,  GUI_TOUCH_AD_BOTTOM1 },{ GUI_TOUCH_AD_TOP2,  GUI_TOUCH_AD_BOTTOM2 }}
#else
    {{ GUI_TOUCH_AD_BOTTOM1,  GUI_TOUCH_AD_TOP1 }, {GUI_TOUCH_AD_BOTTOM2,  GUI_TOUCH_AD_TOP2 }}
#endif
};
static tMinMax xyMinMaxDefault[2][2] = {
#if ((GUI_TOUCH_SWAP_XY==0) && (GUI_TOUCH_MIRROR_X==0)) || ((GUI_TOUCH_SWAP_XY) && (GUI_TOUCH_MIRROR_Y==0))
    {{ GUI_TOUCH_AD_LEFT1, GUI_TOUCH_AD_RIGHT1 },{ GUI_TOUCH_AD_LEFT2, GUI_TOUCH_AD_RIGHT2 } },
#else
    {{ GUI_TOUCH_AD_RIGHT1, GUI_TOUCH_AD_LEFT1 },{ GUI_TOUCH_AD_RIGHT2, GUI_TOUCH_AD_LEFT2 } },
#endif
#if ((GUI_TOUCH_SWAP_XY==0) && (GUI_TOUCH_MIRROR_Y==0)) || ((GUI_TOUCH_SWAP_XY) && (GUI_TOUCH_MIRROR_X==0))
    {{ GUI_TOUCH_AD_TOP1,  GUI_TOUCH_AD_BOTTOM1 },{ GUI_TOUCH_AD_TOP2,  GUI_TOUCH_AD_BOTTOM2 } }
#else
    {{ GUI_TOUCH_AD_BOTTOM1,  GUI_TOUCH_AD_TOP1 },{ GUI_TOUCH_AD_BOTTOM2,  GUI_TOUCH_AD_TOP2 } }
#endif
};


	#ifndef WIN32
static int xMin;
static int xMax;
static int yMin;
static int yMax;
	#endif

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _AD2X
*
* Purpose:
*   Convert physical value into (logical) coordinates.
*/
	#ifndef WIN32
static int _AD2X(int adx) {
    int VIndex;
    switch (BootVersion.NewFunctions) {
    default:
        VIndex = 0;
        break;
    case VERSION_BOOT_NEW_FUNC:
        VIndex = 1;
        break;
    }
    I32 r = adx - xyMinMax[GUI_COORD_X][VIndex].Min;
    r *= GUI_TOUCH_XSIZE - 1;
    return r / ( xyMinMax[GUI_COORD_X][VIndex].Max - xyMinMax[GUI_COORD_X][VIndex].Min );
}

/*********************************************************************
*
*       _AD2Y
*
* Purpose:
*   Convert physical value into (logical) coordinates.
*/
static int _AD2Y(int ady) {
    int VIndex;
    switch (BootVersion.NewFunctions) {
    default:
        VIndex = 0;
        break;
    case VERSION_BOOT_NEW_FUNC:
        VIndex = 1;
        break;
    }
    I32 r = ady - xyMinMax[GUI_COORD_Y][VIndex].Min;
    r *= GUI_TOUCH_YSIZE - 1;
    return r / ( xyMinMax[GUI_COORD_Y][VIndex].Max - xyMinMax[GUI_COORD_Y][VIndex].Min );
}
	#endif

/*********************************************************************
*
*       _Log2Phys
*/
static int _Log2Phys(int l, I32 l0, I32 l1, I32 p0, I32 p1) {
	return p0+ ((p1 - p0) * (l - l0)) / (l1 - l0);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_TOUCH_GetxPhys
*/
int  GUI_TOUCH_GetxPhys(void) {
	return xPhys;
}

/*********************************************************************
*
*       GUI_TOUCH_GetyPhys
*/
int  GUI_TOUCH_GetyPhys(void) {
	return yPhys;
}

/*********************************************************************
*
*       GUI_TOUCH_SetDefaultCalibration
*/
void GUI_TOUCH_SetDefaultCalibration(void) {
    int VIndex;
    switch (BootVersion.NewFunctions) {
    default:
        VIndex = 0;
        break;
    case VERSION_BOOT_NEW_FUNC:
        VIndex = 1;
        break;
    }
    xyMinMax[0][VIndex ].Min = xyMinMaxDefault[0][VIndex ].Min;
    xyMinMax[0][VIndex ].Max = xyMinMaxDefault[0][VIndex ].Max;
    xyMinMax[1][VIndex ].Min = xyMinMaxDefault[1][VIndex ].Min;
    xyMinMax[1][VIndex ].Max = xyMinMaxDefault[1][VIndex ].Max;
}

/*********************************************************************
*
*       GUI_TOUCH_Calibrate
*/
int GUI_TOUCH_Calibrate(int Coord, int Log0, int Log1, int Phys0, int Phys1) {
	int l0 = 0;
	int l1 = (Coord == GUI_COORD_X) ? LCD_XSIZE - 1 : LCD_YSIZE - 1;
	if (labs(Phys0 - Phys1) < 100) {
		return 1;
	}
	if (labs(Log0 - Log1) < 100) {
		return 1;
	}
    int VIndex;
    switch (BootVersion.NewFunctions) {
    default:
        VIndex = 0;
        break;
    case VERSION_BOOT_NEW_FUNC:
        VIndex = 1;
        break;
    }
    xyMinMax[Coord][VIndex].Min = _Log2Phys( l0, Log0, Log1, Phys0, Phys1 );
    xyMinMax[Coord][VIndex].Max = _Log2Phys( l1, Log0, Log1, Phys0, Phys1 );
	return 0;
}

/*********************************************************************
*
*       GUI_TOUCH_GetCalData
*/
void GUI_TOUCH_GetCalData(int Coord, int* pMin,int* pMax) {
    int VIndex;
    switch (BootVersion.NewFunctions) {
    default:
        VIndex = 0;
        break;
    case VERSION_BOOT_NEW_FUNC:
        VIndex = 1;
        break;
    }
    *pMin = xyMinMax[Coord][VIndex].Min;
    *pMax = xyMinMax[Coord][VIndex].Max;
}

/*********************************************************************
*
*       GUI_TOUCH_SetCalData
*/
void GUI_TOUCH_SetCalData(int Coord, int pMin,int pMax) {
    int VIndex;
    switch (BootVersion.NewFunctions) {
    default:
        VIndex = 0;
        break;
    case VERSION_BOOT_NEW_FUNC:
        VIndex = 1;
        break;
    }
    if (abs( pMin - xyMinMaxDefault[Coord][VIndex].Min ) > GUI_TOUCH_AD_MAX_DIFF) {
        pMin = xyMinMaxDefault[Coord][VIndex].Min;
    }
    if (abs( pMax - xyMinMaxDefault[Coord][VIndex].Max ) > GUI_TOUCH_AD_MAX_DIFF) {
        pMax = xyMinMaxDefault[Coord][VIndex].Max;
    }
    xyMinMax[Coord][VIndex].Min = pMin;
    xyMinMax[Coord][VIndex].Max = pMax;
}

/*********************************************************************
*
*       GUI_TOUCH_Exec
*/
void GUI_TOUCH_Exec(void) {
#ifndef WIN32
    int VIndex;
    switch (BootVersion.NewFunctions) {
    default:
        VIndex = 0;
        break;
    case VERSION_BOOT_NEW_FUNC:
        VIndex = 1;
        break;
    }

    //GUI_TOUCH_SetDefaultCalibration();
    int  x, y;
    /* calculate Min / Max values */
    if (xyMinMax[GUI_COORD_X][VIndex].Min < xyMinMax[GUI_COORD_X][VIndex].Max) {
        xMin = xyMinMax[GUI_COORD_X][VIndex].Min;
        xMax = xyMinMax[GUI_COORD_X][VIndex].Max;
    } else {                                
        xMax = xyMinMax[GUI_COORD_X][VIndex].Min;
        xMin = xyMinMax[GUI_COORD_X][VIndex].Max;
    }
    if (xyMinMax[GUI_COORD_Y][VIndex].Min < xyMinMax[GUI_COORD_Y][VIndex].Max) {
        yMin = xyMinMax[GUI_COORD_Y][VIndex].Min;
        yMax = xyMinMax[GUI_COORD_Y][VIndex].Max;
    } else {                                
        yMax = xyMinMax[GUI_COORD_Y][VIndex].Min;
        yMin = xyMinMax[GUI_COORD_Y][VIndex].Max;
    }
    if (!TouchKeyPressed) {        // touched release (finger off)
        xPhys = -1;    // Was 0
        yPhys = -1;
    } else {
        xPhys = TXUADData[7]; // XP
        yPhys = TXUADData[5]; // YP
        PhysKeyPressed = 0xff;
    }
    /* Convert values into logical values */
#if !GUI_TOUCH_SWAP_XY   /* Is X/Y swapped ? */
    x = xPhys;
    y = yPhys;
#else
    x = yPhys;
    y = xPhys;
#endif

    if (( x < xMin ) | ( x > xMax ) | ( y < yMin ) | ( y > yMax )) {
        GUI_TOUCH_StoreUnstable( -1, -1 );
    } else {
        x = _AD2X( x );
        y = _AD2Y( y );
        GUI_TOUCH_StoreUnstable( x, y );
    }
    /* Reset state machine */
#endif /* WIN32 */
}


#else

void GUI_TOUCH_DriverAnalog_C(void);	/* Avoid "no prototype" warnings */
void GUI_TOUCH_DriverAnalog_C(void) {}

#endif    /* defined(GUI_SUPPORT_TOUCH) && GUI_SUPPORT_TOUCH */


/*************************** End of file ****************************/
