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
File        : BUTTON_Color.c
Purpose     : Implementation of button widget
---------------------------END-OF-HEADER------------------------------
*/

#include "BUTTON_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_GetBkColor  
*/
GUI_COLOR BUTTON_GetBkColor(BUTTON_Handle hObj,unsigned int Index) {
  GUI_COLOR Color = 0;
  if (hObj) {
    BUTTON_Obj * pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.aBkColor)) {
      Color = pObj->Props.aBkColor[Index];
    }
    WM_UNLOCK();
  }
  return Color;
}

/*********************************************************************
*
*       BUTTON_SetBkColor
*/
void BUTTON_SetBkColor(BUTTON_Handle hObj,unsigned int Index, GUI_COLOR Color) {
  if (hObj) {
    BUTTON_Obj* pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.aBkColor)) {
      pObj->Props.aBkColor[Index] = Color;
    }
    BUTTON_Invalidate(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       BUTTON_GetTextColor  
*/
GUI_COLOR BUTTON_GetTextColor(BUTTON_Handle hObj,unsigned int Index) {
  GUI_COLOR Color = 0;
  if (hObj) {
    BUTTON_Obj * pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.aTextColor)) {
      Color = pObj->Props.aTextColor[Index];
    }
    WM_UNLOCK();
  }
  return Color;
}

/*********************************************************************
*
*       BUTTON_SetTextColor
*/
void BUTTON_SetTextColor(BUTTON_Handle hObj,unsigned int Index, GUI_COLOR Color) {
  if (hObj) {
    BUTTON_Obj* pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.aTextColor)) {
      pObj->Props.aTextColor[Index] = Color;
    }
    BUTTON_Invalidate(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       BUTTON_GetFrameColor
*/
GUI_COLOR BUTTON_GetFrameColor(BUTTON_Handle hObj) {
  GUI_COLOR Color = 0;
  if (hObj) {
    BUTTON_Obj * pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    Color = pObj->Props.FrameColor;
    WM_UNLOCK();
  }
  return Color;
}

/*********************************************************************
*
*       BUTTON_SetFrameColor
*/
void BUTTON_SetFrameColor(BUTTON_Handle hObj, GUI_COLOR Color) {
  if (hObj) {
    BUTTON_Obj* pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    pObj->Props.FrameColor = Color;
    BUTTON_Invalidate(hObj);
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_Color_C(void);
  void BUTTON_Color_C(void) {}
#endif /* GUI_WINSUPPORT */
