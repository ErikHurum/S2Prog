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
File        : LISTBOX_SetScrollbarWidth.c
Purpose     : Implementation of listbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTBOX_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTBOX_SetScrollbarWidth
*/
void LISTBOX_SetScrollbarWidth(LISTBOX_Handle hObj, unsigned Width) {
  LISTBOX_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    if (Width != (unsigned)pObj->ScrollbarWidth) {
      pObj->ScrollbarWidth = Width;
      LISTBOX__SetScrollbarWidth(hObj, pObj);
      LISTBOX_Invalidate(hObj);
    }
    WM_UNLOCK();
  }  
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_SetScrollbarWidth_C(void) {}
#endif

/*************************** End of file ****************************/
