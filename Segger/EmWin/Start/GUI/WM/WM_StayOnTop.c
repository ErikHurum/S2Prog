/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2009  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.00 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : WM_StayOnTop.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       WM_SetStayOnTop
*/
void WM_SetStayOnTop(WM_HWIN hWin, int OnOff) {
  WM_Obj * pWin;
  if (hWin) {
    U16 OldStatus;
    WM_LOCK();
    pWin = WM_H2P(hWin);
    OldStatus = pWin->Status;
    if (OnOff) {
      if ((pWin->Status & WM_SF_STAYONTOP) == 0) {  /* First check if this is necessary at all */
        pWin->Status |= WM_SF_STAYONTOP;
      }
    } else {
      if ((pWin->Status & WM_SF_STAYONTOP) != 0) {  /* First check if this is necessary at all */
        pWin->Status &= ~WM_SF_STAYONTOP;
      }
    }
    if (pWin->Status != OldStatus) {
      WM_AttachWindow(hWin, WM_GetParent(hWin));
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       WM_GetStayOnTop
*/
int WM_GetStayOnTop(WM_HWIN hWin) {
  int Result = 0;
  WM_Obj * pWin;
  if (hWin) {
    WM_LOCK();
    pWin = WM_H2P(hWin);
    if ((pWin->Status & WM_SF_STAYONTOP) != 0) {
      Result = 1;
    }
    WM_UNLOCK();
  }
  return Result;
}

#else
  void WM_StayOnTop_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
