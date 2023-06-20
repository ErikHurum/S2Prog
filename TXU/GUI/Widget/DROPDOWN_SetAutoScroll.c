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
File        : DROPDOWN_SetAutoScroll.c
Purpose     : Implementation of dropdown widget
---------------------------END-OF-HEADER------------------------------
*/

#include "DROPDOWN_Private.h"
#include "LISTBOX.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/

/*********************************************************************
*
*       DROPDOWN_SetAutoScroll
*/
void DROPDOWN_SetAutoScroll(DROPDOWN_Handle hObj, int OnOff) {
  if (hObj) {
    DROPDOWN_Obj* pObj;
    char Flags;
    WM_LOCK();
    pObj = DROPDOWN_H2P(hObj);
    Flags = pObj->Flags & (~DROPDOWN_SF_AUTOSCROLLBAR);
    if (OnOff) {
      Flags |= DROPDOWN_SF_AUTOSCROLLBAR;
    }
    if (pObj->Flags != Flags) {
      pObj->Flags = Flags;
      if (pObj->hListWin) {
        LISTBOX_SetAutoScrollV(pObj->hListWin, (Flags & DROPDOWN_SF_AUTOSCROLLBAR) ? 1 : 0);
      }
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void DROPDOWN_SetAutoScroll_C(void);
  void DROPDOWN_SetAutoScroll_C(void) {}
#endif
