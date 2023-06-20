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
File        : FRAMEWIN_SetTitleHeight.c
Purpose     : 
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "FRAMEWIN_Private.h"

#if GUI_WINSUPPORT


/*********************************************************************
*
*        Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_SetTitleHeight
*/
int FRAMEWIN_SetTitleHeight(FRAMEWIN_Handle hObj, int Height) {
  int r = 0;
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    int OldHeight;
    WM_LOCK();
    pObj = FRAMEWIN_LOCK_H(hObj);
    r = pObj->Props.TitleHeight;
    if (Height != r) {
      OldHeight = FRAMEWIN__CalcTitleHeight(pObj);
      pObj->Props.TitleHeight = Height;
      FRAMEWIN__UpdatePositions(hObj);
      FRAMEWIN__UpdateButtons(pObj, OldHeight);
      FRAMEWIN_Invalidate(hObj);
    }
    GUI_UNLOCK_H(pObj);
    WM_UNLOCK();
  }
  return r;
}


#else
  void FRAMEWIN_SetTitleHeight_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
