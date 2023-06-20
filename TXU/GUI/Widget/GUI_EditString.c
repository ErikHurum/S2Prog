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
File        : GUI_EditString.c
Purpose     : Widget, add. module
----------------------------------------------------------------------
*/

#include "EDIT.h"
#include "GUI_Protected.h"
#include "EDIT_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*             Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_EditString
*/
void GUI_EditString(char * pString, int Len, int xsize) {
  int Key, x, y, ysize, Id;
  EDIT_Handle hEdit;
  EDIT_Obj* pObj;
  const GUI_FONT GUI_UNI_PTR * pOldFont;
  WM_LOCK();
  pOldFont = GUI_SetFont(EDIT_GetDefaultFont());
  x = GUI_GetDispPosX();
  y = GUI_GetDispPosY();
  if (xsize == 0) {
    xsize = GUI_GetCharDistX('X') * Len + 6;
  }
  ysize = GUI_GetFontSizeY();
  Id = 0x1234;
  hEdit = EDIT_Create(x, y, xsize, ysize, Id, Len, 0);
  EDIT_SetText(hEdit, pString);
  WM_SetFocus(hEdit);
  do {
    Key = GUI_WaitKey();
  } while ((Key != GUI_KEY_ESCAPE) && (Key != GUI_KEY_ENTER) && (Key != 0));
  pObj = EDIT_H2P(hEdit);
  if (Key == GUI_KEY_ENTER) {
    EDIT_GetText(hEdit, pString, pObj->MaxLen);
  }
  GUI_SetFont(pOldFont);
  EDIT_Delete(hEdit);
  WM_UNLOCK();
}

#else /* avoid empty object files */

void GUI_EditString_C(void);
void GUI_EditString_C(void){}

#endif
