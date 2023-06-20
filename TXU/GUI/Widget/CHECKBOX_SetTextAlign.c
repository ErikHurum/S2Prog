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
File        : CHECKBOX_SetTextAlign.c
Purpose     : Implementation of CHECKBOX_SetAlign
---------------------------END-OF-HEADER------------------------------
*/

#include "CHECKBOX_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       CHECKBOX_SetTextAlign
*/
void CHECKBOX_SetTextAlign(CHECKBOX_Handle hObj, int Align) {
  CHECKBOX_Obj * pObj;
  if (hObj) {
    WM_LOCK();
    pObj = CHECKBOX_H2P(hObj);
    if (pObj->Props.Align != Align) {
      pObj->Props.Align = Align;
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_SetTextAlign_C(void);
  void CHECKBOX_SetTextAlign_C(void) {}
#endif