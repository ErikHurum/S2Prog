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
File        : MENU_SetItem.c
Purpose     : Implementation of menu widget
---------------------------END-OF-HEADER------------------------------
*/

#include "MENU.h"
#include "MENU_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MENU_SetItem
*/
void MENU_SetItem(MENU_Handle hObj, U16 ItemId, const MENU_ITEM_DATA* pItemData) {
  if (hObj && pItemData) {
    int Index;
    WM_LOCK();
    Index = MENU__FindItem(hObj, ItemId, &hObj);
    if (Index >= 0) {
      MENU_Obj* pObj;
      pObj = MENU_H2P(hObj);
      if (MENU__SetItem(hObj, pObj, Index, pItemData) != 0) {
        MENU__ResizeMenu(hObj, pObj);
      }
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */
  void MENU_SetItem_C(void) {}
#endif

/*************************** End of file ****************************/
