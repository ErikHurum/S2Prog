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
File        : MENU_SetBkColor.c
Purpose     : Implementation of menu widget
---------------------------END-OF-HEADER------------------------------
*/

#include "MENU.h"
#include "MENU_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MENU_SetBkColor
*/
void MENU_SetBkColor(MENU_Handle hObj, unsigned ColorIndex, GUI_COLOR Color) {
  if (hObj) {
    MENU_Obj* pObj;
    WM_LOCK();
    pObj = MENU_H2P(hObj);
    if (pObj) {
      if (ColorIndex < GUI_COUNTOF(pObj->Props.aBkColor)) {
        if (Color != pObj->Props.aBkColor[ColorIndex]) {
          pObj->Props.aBkColor[ColorIndex] = Color;
          WM_InvalidateWindow(hObj);
        }
      }
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */
  void MENU_SetBkColor_C(void) {}
#endif

/*************************** End of file ****************************/
