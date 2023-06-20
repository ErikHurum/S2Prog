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
File        : LISTBOX_SetOwner.c
Purpose     : Implementation of LISTBOX_SetOwner
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTBOX_Private.h"


#if GUI_WINSUPPORT


/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/

/*********************************************************************
*
*       LISTBOX_SetOwner
*/
void LISTBOX_SetOwner(LISTBOX_Handle hObj, WM_HWIN hOwner) {
  if (hObj) {
    LISTBOX_Obj* pObj;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    pObj->hOwner = hOwner;
    LISTBOX__InvalidateInsideArea(hObj);
    WM_UNLOCK();
  }
}



#else                            /* Avoid problems with empty object modules */
  void LISTBOX_SetOwner_C(void) {}
#endif
