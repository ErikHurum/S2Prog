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
File        : WM_OnKey.c
Purpose     : Implementation of WM_OnKey
---------------------------END-OF-HEADER------------------------------
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
*       WM_OnKey

  Returns:
    0 if message could not be handled
*/
int WM_OnKey(int Key, int Pressed) {
  int r = 0;
  WM_MESSAGE Msg;
  WM_LOCK();
  if (WM__ahWinFocus[WM__TOUCHED_LAYER] != 0) {
    WM_KEY_INFO Info;
    Info.Key = Key;
    Info.PressedCnt = Pressed;
    Msg.MsgId = WM_KEY;
    Msg.Data.p = &Info;
    WM__SendMessage(WM__ahWinFocus[WM__TOUCHED_LAYER] , &Msg);
    r = 1;
  }
  WM_UNLOCK();
  return r;
}

#else
  void WM_OnKey_c(void);
  void WM_OnKey_c(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/