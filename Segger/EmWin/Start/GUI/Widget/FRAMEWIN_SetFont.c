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
File        : FRAMEWIN_SetFont.c
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
*       FRAMEWIN_SetFont
*/
void FRAMEWIN_SetFont(FRAMEWIN_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont) {
  GUI_LOCK();
  if (hObj) {
    int OldHeight;
    FRAMEWIN_Obj * pObj;
    pObj = FRAMEWIN_LOCK_H(hObj);
    OldHeight = FRAMEWIN__CalcTitleHeight(pObj);
    pObj->Props.pFont = pFont;
    FRAMEWIN__UpdatePositions(hObj);
    FRAMEWIN__UpdateButtons(pObj, OldHeight);
    FRAMEWIN_Invalidate(hObj);
    GUI_UNLOCK_H(pObj);
  }
  GUI_UNLOCK();
}

#else
  void FRAMEWIN_SetFont_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
