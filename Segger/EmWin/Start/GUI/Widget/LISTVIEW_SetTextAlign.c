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
File        : LISTVIEW_SetTextAlign.c
Purpose     : Implementation of LISTVIEW_SetTextAlign
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
*       LISTVIEW_SetTextAlign
*/
void LISTVIEW_SetTextAlign(LISTVIEW_Handle hObj, unsigned int Index, int Align) {
  if (hObj) {
    LISTVIEW_Obj * pObj;
    WM_LOCK();
    pObj = LISTVIEW_LOCK_H(hObj);
    if (Index < LISTVIEW__GetNumColumns(pObj)) {
      LISTVIEW_COLUMN* pColumn;
      pColumn = (LISTVIEW_COLUMN *)GUI_ARRAY_GetpItemLocked(pObj->ColumnArray, Index);
      if (Align != pColumn->Align) {
        pColumn->Align = Align;
        LISTVIEW__InvalidateInsideArea(hObj, pObj);
      }
      GUI_UNLOCK_H(pColumn);
    }
    GUI_UNLOCK_H(pObj);
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_SetTextAlign_C(void);
  void LISTVIEW_SetTextAlign_C(void) {}
#endif

/*************************** End of file ****************************/
