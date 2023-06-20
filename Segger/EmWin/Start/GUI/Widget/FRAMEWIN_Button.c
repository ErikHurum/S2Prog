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
File        : FRAMEWIN_Button.c
Purpose     : 
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "FRAMEWIN_Private.h"
#include "BUTTON.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*        Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_AddButton
*/
WM_HWIN FRAMEWIN_AddButton(FRAMEWIN_Handle hObj, int Flags, int Off, int Id) {
  WM_HWIN r = 0;
  if (hObj) {
    POSITIONS Pos;
    int Size       = FRAMEWIN_GetTitleHeight(hObj);
    int BorderSize = FRAMEWIN_GetBorderSize(hObj);
    int WinFlags, x;
    WM_LOCK();
    FRAMEWIN__CalcPositions(hObj, &Pos);
    if (Flags & FRAMEWIN_BUTTON_RIGHT) {
      x = Pos.rTitleText.x1 - (Size - 1) - Off;
      WinFlags = WM_CF_SHOW | WM_CF_ANCHOR_RIGHT;
    } else {
      x = Pos.rTitleText.x0 + Off;
      WinFlags = WM_CF_SHOW;
    }
    r = BUTTON_CreateAsChild(x, BorderSize, Size, Size, hObj, Id, WinFlags);
    BUTTON_SetFocussable(r, 0);
    WM_UNLOCK();
  }
  return r;
}

#else
  void FRAMEWIN_Button_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
