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
File        : LISTBOX_ItemSpacing.c
Purpose     : Implementation of LISTBOX_SetItemSpacing & LISTBOX_GetItemSpacing
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>
#include "LISTBOX_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/

/*********************************************************************
*
*       LISTBOX_SetItemSpacing
*/
void LISTBOX_SetItemSpacing(LISTBOX_Handle hObj, unsigned Value) {
  if (hObj) {
    LISTBOX_Obj* pObj;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    pObj->ItemSpacing = Value;
    LISTBOX_InvalidateItem(hObj, LISTBOX_ALL_ITEMS);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       LISTBOX_GetItemSpacing
*/
unsigned LISTBOX_GetItemSpacing(LISTBOX_Handle hObj) {
  unsigned Value = 0;
  if (hObj) {
    LISTBOX_Obj* pObj;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    Value = pObj->ItemSpacing;
    WM_UNLOCK();
  }
  return Value;
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_SetItemSpacing_C(void);
  void LISTBOX_SetItemSpacing_C(void) {}
#endif
