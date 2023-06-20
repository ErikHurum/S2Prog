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
File        : TEXT_SetText.c
Purpose     : Implementation of TEXT_SetText
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
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
*       TEXT_SetText
*/
void TEXT_SetText(TEXT_Handle hObj, const char* s) {
  if (hObj) {
    TEXT_Obj* pObj;
    WM_LOCK();
    pObj = TEXT_H2P(hObj);
    if (GUI__SetText(&pObj->hpText, s)) {
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */

void TEXT_SetText_c(void);
void TEXT_SetText_c(void){}

#endif  /* #if GUI_WINSUPPORT */


