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
File        : LISTBOX_ScrollStep.c
Purpose     : Implementation of listbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "LISTBOX_Private.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       LISTBOX_SetScrollStepH
*/
void LISTBOX_SetScrollStepH(LISTBOX_Handle hObj, int Value) {
  if (hObj) {
    LISTBOX_Obj * pObj;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    pObj->Props.ScrollStepH = Value;
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       LISTBOX_GetScrollStepH
*/
int LISTBOX_GetScrollStepH(LISTBOX_Handle hObj) {
  int Value = 0;
  if (hObj) {
    LISTBOX_Obj * pObj;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    Value = pObj->Props.ScrollStepH;
    WM_UNLOCK();
  }
  return Value;
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_ScrollStep_C(void) {}
#endif
