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
File        : GUI_IsInFont.c
Purpose     : Implementation of optional routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_IsInFont
*/
char GUI_IsInFont(const GUI_FONT GUI_UNI_PTR *pFont, U16 c) {
  if (pFont == NULL) {
    pFont = GUI_Context.pAFont;
  }
  return pFont->pfIsInFont(pFont, c);
}

/*************************** End of file ****************************/