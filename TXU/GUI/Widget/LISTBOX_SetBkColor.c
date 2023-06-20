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
File        : LISTBOX_SetBkColor.c
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
*       LISTBOX_SetBkColor
*/
void LISTBOX_SetBkColor(LISTBOX_Handle hObj, unsigned Index, GUI_COLOR color) {
  LISTBOX_Obj* pObj;
  if (hObj) {
    if ((unsigned int)Index < GUI_COUNTOF(pObj->Props.aBackColor)) {
      WM_LOCK();
      pObj = LISTBOX_H2P(hObj);
      pObj->Props.aBackColor[Index] = color;
      LISTBOX__InvalidateInsideArea(hObj);
      WM_UNLOCK();
    }
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_SetBkColor_C(void) {}
#endif

/*************************** End of file ****************************/
