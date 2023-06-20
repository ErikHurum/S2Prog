/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2007  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.14 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : PROGBAR_SetBarColor.c
Purpose     : Implementation of progbar widget
---------------------------END-OF-HEADER------------------------------
*/

#include "PROGBAR_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       PROGBAR_SetBarColor
*/
void PROGBAR_SetBarColor(PROGBAR_Handle hObj, unsigned int Index, GUI_COLOR color) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.aBarColor)) {
      pObj->Props.aBarColor[Index] = color;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */
  void PROGBAR_SetBarColor_C(void);
  void PROGBAR_SetBarColor_C(void) {}
#endif
