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
File        : WM_SetSize.c
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
*       WM_SetScrollState
*/
void WM_SetScrollState(WM_HWIN hWin, const WM_SCROLL_STATE* pState) {
  if (hWin && pState) {
    WM_MESSAGE Msg;
    Msg.MsgId = WM_SET_SCROLL_STATE;
    Msg.Data.p = (const void*)pState;
    WM_SendMessage(hWin, &Msg);
  }
}

#else
  void WM_SetScrollSize_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
