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
File        : FRAMEWIN_Get.c
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
*       FRAMEWIN_GetFont
*/
const GUI_FONT GUI_UNI_PTR * FRAMEWIN_GetFont(FRAMEWIN_Handle hObj) {
  const GUI_FONT GUI_UNI_PTR * r = NULL;
  GUI_LOCK();
  if (hObj) {
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    r = pObj->Props.pFont;
    FRAMEWIN_Invalidate(hObj);
  }
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       FRAMEWIN_GetTitleHeight
*/
int FRAMEWIN_GetTitleHeight(FRAMEWIN_Handle hObj) {
  int r = 0;
  POSITIONS Pos;
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    WM_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    FRAMEWIN__CalcPositions(pObj, &Pos);
    r = pObj->Props.TitleHeight;
    if (r == 0) {
      r = Pos.TitleHeight;
    }
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       FRAMEWIN_GetBorderSize
*/
int FRAMEWIN_GetBorderSize(FRAMEWIN_Handle hObj) {
  int r = 0;
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    WM_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    r = pObj->Props.BorderSize;
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       FRAMEWIN_GetTextAlign
*/
int FRAMEWIN_GetTextAlign(FRAMEWIN_Handle hObj) {
  int r = 0;
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    WM_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    r = pObj->Props.TextAlign;
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       FRAMEWIN_GetText
*/
void FRAMEWIN_GetText(FRAMEWIN_Handle hObj, char * pBuffer, int MaxLen) {
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    WM_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    if (pObj->hText) {
      int Len;
      const char * pText;
      pText = (const char *)GUI_ALLOC_h2p(pObj->hText);
      Len = strlen(pText);
      if (Len > (MaxLen - 1)) {
        Len = MaxLen - 1;
      }
      GUI_MEMCPY((void *)pBuffer, (const void *)pText, Len);
      *(pBuffer + Len) = 0;
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       FRAMEWIN_GetBarColor
*/
GUI_COLOR FRAMEWIN_GetBarColor(FRAMEWIN_Handle hObj, unsigned Index) {
  GUI_COLOR r = 0;
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    WM_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.aBarColor)) {
      r = pObj->Props.aBarColor[Index];
    }
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       FRAMEWIN_GetActive
*/
int FRAMEWIN_GetActive(FRAMEWIN_Handle hObj) {
  int r = 0;
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    WM_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    if (pObj->Flags & FRAMEWIN_CF_ACTIVE) {
      r = 1;
    }
    WM_UNLOCK();
  }
  return r;
}

#else
  void FRAMEWIN_Get_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
