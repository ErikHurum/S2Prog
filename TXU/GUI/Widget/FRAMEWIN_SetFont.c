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
    FRAMEWIN_Obj* pObj;
    pObj = FRAMEWIN_H2P(hObj);
    OldHeight = FRAMEWIN__CalcTitleHeight(pObj);
    pObj->Props.pFont = pFont;
    FRAMEWIN__UpdatePositions(pObj);
    FRAMEWIN__UpdateButtons(pObj, OldHeight);
    FRAMEWIN_Invalidate(hObj);
  }
  GUI_UNLOCK();
}

#else
  void FRAMEWIN_SetFont_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */