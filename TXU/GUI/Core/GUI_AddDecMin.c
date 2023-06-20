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
File        : GUI_AddDecMin.c
Purpose     : Routines to display values in decimal form
----------------------------------------------------------------------
*/

#include "GUI_Protected.h"
#include "GUIDebug.h"
#include "string.h"

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_AddDecMin
*/
void GUI_AddDecMin(I32 v, char**ps) {
  U8 Len = GUI_Long2Len(v);
  GUI_AddDecShift(v, Len, 0, ps);
}

/*************************** End of file ****************************/
