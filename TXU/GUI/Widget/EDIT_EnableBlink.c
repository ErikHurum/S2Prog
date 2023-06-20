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
File        : EDIT_EnableBlink.c
Purpose     : Implementation of edit widget
---------------------------END-OF-HEADER------------------------------
*/

#include "EDIT.h"
#include "EDIT_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*             Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       EDIT_EnableBlink
*/
void EDIT_EnableBlink(EDIT_Handle hObj, int Period, int OnOff) {
  if (hObj) {
    EDIT_Obj * pObj;
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    if (OnOff) {
      pObj->hTimer = WM_CreateTimer(hObj, 0, Period, 0);
    } else {
      WM_DeleteTimer(pObj->hTimer);
      pObj->hTimer = 0;
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */

void EDIT_EnableBlink_C(void);
void EDIT_EnableBlink_C(void) {}

#endif /* GUI_WINSUPPORT */
