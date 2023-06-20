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
File        : LISTBOX_Font.c
Purpose     : Implementation of listbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "LISTBOX_Private.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTBOX_SetFont
*/
void LISTBOX_SetFont(LISTBOX_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont) {
  LISTBOX_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    pObj->Props.pFont = pFont;
    LISTBOX_InvalidateItem(hObj, LISTBOX_ALL_ITEMS);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       LISTBOX_GetFont
*/
const GUI_FONT GUI_UNI_PTR * LISTBOX_GetFont(LISTBOX_Handle hObj) {
  const GUI_FONT GUI_UNI_PTR * pFont = NULL;
  LISTBOX_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    pFont = pObj->Props.pFont;
    WM_UNLOCK();
  }
  return pFont;
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_Font_C(void) {}
#endif
