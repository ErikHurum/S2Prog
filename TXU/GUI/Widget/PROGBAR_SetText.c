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
File        : PROGBAR_SetText.c
Purpose     : Implementation of progbar widget
---------------------------END-OF-HEADER------------------------------
*/

#include "PROGBAR_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       PROGBAR_SetText
*/
void PROGBAR_SetText(PROGBAR_Handle hObj, const char* s) {
  if (hObj) {
    PROGBAR_Obj* pObj;
    const GUI_FONT GUI_UNI_PTR * pOldFont;
    GUI_RECT r1;
    char acBuffer[5];
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    pOldFont = GUI_SetFont(pObj->Props.pFont);
    PROGBAR__GetTextRect(pObj, &r1, PROGBAR__GetText(pObj, acBuffer));
    if (!s) {
      PROGBAR__FreeText(hObj);
      WM_InvalidateRect(hObj, &r1);
    } else {
      if (GUI__SetText(&pObj->hpText, s)) {
        GUI_RECT r2;
        PROGBAR__GetTextRect(pObj, &r2, PROGBAR__GetText(pObj, acBuffer));
        GUI_MergeRect(&r1, &r1, &r2);
        WM_InvalidateRect(hObj, &r1);
      }
    }
    GUI_SetFont(pOldFont);
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */
  void PROGBAR_SetText_C(void);
  void PROGBAR_SetText_C(void) {}
#endif
