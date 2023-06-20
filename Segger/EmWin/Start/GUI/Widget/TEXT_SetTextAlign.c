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
File        : TEXT_SetTextAlign.c
Purpose     : Implementation of TEXT_SetTextAlign
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "TEXT_Private.h"
#include "GUI_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       TEXT_SetTextAlign
*/
void TEXT_SetTextAlign(TEXT_Handle hObj, int Align) {
  if (hObj) {
    TEXT_Obj * pObj;
    WM_LOCK();
    pObj = TEXT_LOCK_H(hObj);
    pObj->Align = Align;
    GUI_UNLOCK_H(pObj);
    WM_Invalidate(hObj);
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */

void TEXT_SetTextAlign_c(void);
void TEXT_SetTextAlign_c(void){}

#endif  /* #if GUI_WINSUPPORT */


