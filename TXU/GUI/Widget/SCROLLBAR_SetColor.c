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
File        : SCROLLBAR_SetColor.c
Purpose     : Implementation of SCROLLBAR_SetColor
---------------------------END-OF-HEADER------------------------------
*/

#include "SCROLLBAR_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       SCROLLBAR_SetColor
*/
GUI_COLOR SCROLLBAR_SetColor(SCROLLBAR_Handle hObj, int Index, GUI_COLOR Color) {
  GUI_COLOR OldColor = 0;
  SCROLLBAR_Obj * pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SCROLLBAR_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.aColor)) {
      OldColor = pObj->Props.aColor[Index];
      if (OldColor != Color) {
        pObj->Props.aColor[Index] = Color;
        WM_InvalidateWindow(hObj);
      }
    }
    WM_UNLOCK();
  }
  return OldColor;
}

#else
  void SCROLLBAR_SetColor_c(void) {}    /* Avoid empty object files */
#endif  /* #if GUI_WINSUPPORT */



