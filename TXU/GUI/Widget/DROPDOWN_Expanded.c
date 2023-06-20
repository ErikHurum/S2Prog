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
File        : DROPDOWN_Expanded.c
Purpose     : Implementation of dropdown widget
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>
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
*       DROPDOWN_IncSelExp
*/
void DROPDOWN_IncSelExp(DROPDOWN_Handle hObj) {
  if (hObj) {
    DROPDOWN_Obj * pObj;
    WM_LOCK();
    pObj = DROPDOWN_H2P(hObj);
    if (pObj->hListWin) {
      LISTBOX_IncSel(pObj->hListWin);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       DROPDOWN_DecSelExp
*/
void DROPDOWN_DecSelExp(DROPDOWN_Handle hObj) {
  if (hObj) {
    DROPDOWN_Obj * pObj;
    WM_LOCK();
    pObj = DROPDOWN_H2P(hObj);
    if (pObj->hListWin) {
      LISTBOX_DecSel(pObj->hListWin);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       DROPDOWN_GetSelExp
*/
int  DROPDOWN_GetSelExp(DROPDOWN_Handle hObj) {
  int r = 0;
  if (hObj) {
    DROPDOWN_Obj * pObj;
    WM_LOCK();
    pObj = DROPDOWN_H2P(hObj);
    if (pObj->hListWin) {
      r = LISTBOX_GetSel(pObj->hListWin);
    }
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       DROPDOWN_SetSelExp
*/
void DROPDOWN_SetSelExp(DROPDOWN_Handle hObj, int Sel) {
  if (hObj) {
    DROPDOWN_Obj * pObj;
    WM_LOCK();
    pObj = DROPDOWN_H2P(hObj);
    if (pObj->hListWin) {
      LISTBOX_SetSel(pObj->hListWin, Sel);
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void DROPDOWN_Expanded_C(void);
  void DROPDOWN_Expanded_C(void) {}
#endif

/*************************** End of file ****************************/
