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
File        : DROPDOWN_SetScrollbarColor.c
Purpose     : Implementation of dropdown widget
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTBOX.h"
#include "DROPDOWN_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       DROPDOWN_SetScrollbarColor
*/
void DROPDOWN_SetScrollbarColor(DROPDOWN_Handle hObj, unsigned Index, GUI_COLOR Color) {
  DROPDOWN_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = DROPDOWN_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.aScrollbarColor)) {
      if (pObj->Props.aScrollbarColor[Index] != Color) {
        pObj->Props.aScrollbarColor[Index] = Color;
        if (pObj->hListWin) {
          LISTBOX_SetScrollbarColor(pObj->hListWin, Color, Index);
        }
      }
    }
    WM_UNLOCK();
  }  
}

#else                            /* Avoid problems with empty object modules */
  void DROPDOWN_SetScrollbarColor_C(void);
  void DROPDOWN_SetScrollbarColor_C(void) {}
#endif
