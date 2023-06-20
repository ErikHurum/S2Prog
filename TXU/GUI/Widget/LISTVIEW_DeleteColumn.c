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
File        : LISTVIEW_DeleteColumn.c
Purpose     : Implementation of LISTVIEW_DeleteColumn
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
*       LISTVIEW_DeleteColumn
*/
void LISTVIEW_DeleteColumn(LISTVIEW_Handle hObj, unsigned Index) {
  if (hObj) {
    LISTVIEW_Obj* pObj;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    if (Index < LISTVIEW__GetNumColumns(pObj)) {
      LISTVIEW_ROW* pRow;
      unsigned NumRows, i;
      HEADER_DeleteItem(pObj->hHeader, Index);
      GUI_ARRAY_DeleteItem(&pObj->ColumnArray, Index);
      NumRows = LISTVIEW__GetNumRows(pObj);
      for (i = 0; i < NumRows; i++) {
        LISTVIEW_CELL* pCell;
        pRow = (LISTVIEW_ROW*) GUI_ARRAY_GetpItem(&pObj->RowArray, i);
        /* Delete attached info items */
        pCell = (LISTVIEW_CELL*) GUI_ARRAY_GetpItem(&pRow->CellArray, Index);
        if (pCell->hCellInfo) {
          GUI_ALLOC_Free(pCell->hCellInfo);
        }
        /* Delete cell */
        GUI_ARRAY_DeleteItem(&pRow->CellArray, Index);
      }
      LISTVIEW__UpdateScrollParas(hObj, pObj);
      LISTVIEW__InvalidateInsideArea(hObj, pObj);
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_DeleteColumn_C(void);
  void LISTVIEW_DeleteColumn_C(void) {}
#endif

/*************************** End of file ****************************/
