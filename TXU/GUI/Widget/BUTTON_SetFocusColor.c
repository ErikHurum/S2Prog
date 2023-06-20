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
File        : BUTTON_SetFocusColor.c
Purpose     : Implementation of BUTTON_SetFocusColor
---------------------------END-OF-HEADER------------------------------
*/

#include "BUTTON_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_SetFocusColor
*/
GUI_COLOR BUTTON_SetFocusColor(BUTTON_Handle hObj, GUI_COLOR Color) {
  GUI_COLOR OldColor = 0;
  if (hObj) {
    BUTTON_Obj* pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    if (Color != pObj->Props.FocusColor) {
      OldColor = pObj->Props.FocusColor;
      pObj->Props.FocusColor = Color;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
  return OldColor;
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_SetFocusColor_C(void);
  void BUTTON_SetFocusColor_C(void) {}
#endif
