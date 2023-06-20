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
File        : MENU_Attach.c
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
*       MENU_Attach
*/
void MENU_Attach(MENU_Handle hObj, WM_HWIN hDestWin, int x, int y, int xSize, int ySize, int Flags) {
  GUI_USE_PARA(Flags);
  if (hObj) {
    MENU_Obj* pObj;
    WM_LOCK();
    pObj = MENU_H2P(hObj);
    if (pObj) {
      pObj->Width  = ((xSize > 0) ? xSize : 0);
      pObj->Height = ((ySize > 0) ? ySize : 0);
      WM_AttachWindowAt(hObj, hDestWin, x, y);
      MENU__ResizeMenu(hObj, pObj);
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */
  void MENU_Attach_C(void) {}
#endif

/*************************** End of file ****************************/
