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
File        : TEXT_SetBkColor.c
Purpose     : Implementation of TEXT_SetBkColor
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
*       TEXT_SetBkColor
*/
void TEXT_SetBkColor(TEXT_Handle hObj, GUI_COLOR Color) {
  if (hObj) {
    TEXT_Obj* pObj;
    WM_LOCK();
    pObj = TEXT_H2P(hObj);
    if (pObj->Props.BkColor != Color) {
      pObj->Props.BkColor = Color;
      #if TEXT_SUPPORT_TRANSPARENCY
        if (Color <= 0xFFFFFF) {
          WM_ClrHasTrans(hObj);
        } else {
          WM_SetHasTrans(hObj);
        }
      #endif
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}


#else  /* avoid empty object files */

void TEXT_SetBkColor_c(void);
void TEXT_SetBkColor_c(void){}

#endif  /* #if GUI_WINSUPPORT */


