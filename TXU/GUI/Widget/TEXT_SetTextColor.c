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
File        : TEXT_SetTextColor.c
Purpose     : Implementation of TEXT_SetTextColor
---------------------------END-OF-HEADER------------------------------
*/

#include "TEXT_Private.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       TEXT_SetTextColor
*/
void TEXT_SetTextColor(TEXT_Handle hObj, GUI_COLOR Color) {
  if (hObj) {
    TEXT_Obj* pObj;
    WM_LOCK();
    pObj = TEXT_H2P(hObj);
    if (pObj->Props.TextColor != Color) {
      pObj->Props.TextColor = Color;
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}


#else  /* avoid empty object files */

void TEXT_SetTextColor_c(void);
void TEXT_SetTextColor_c(void){}

#endif  /* #if GUI_WINSUPPORT */


