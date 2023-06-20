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
File        : GUI__AddSpaceHex.C
Purpose     : Internal function
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code (module internal)
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__AddSpaceHex
*/
void GUI__AddSpaceHex(U32 v, U8 Len, char** ps) {
  char* s = *ps;
  *s++ = ' ';
  *ps = s;
  GUI_AddHex(v, Len, ps);
}

/*************************** End of file ****************************/
