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
File        : LISTVIEW_GetHeader.c
Purpose     : Implementation of LISTVIEW_GetHeader
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTVIEW_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTVIEW_GetHeader
*/
HEADER_Handle LISTVIEW_GetHeader(LISTVIEW_Handle hObj) {
  HEADER_Handle hHeader = 0;
  if (hObj) {
    LISTVIEW_Obj* pObj;
    WM_LOCK();
    pObj = LISTVIEW_LOCK_H(hObj);
    hHeader = pObj->hHeader;
    GUI_UNLOCK_H(pObj);
    WM_UNLOCK();
  }
  return hHeader;
}


#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_GetHeader_C(void);
  void LISTVIEW_GetHeader_C(void) {}
#endif

/*************************** End of file ****************************/