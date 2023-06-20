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
File        : RADIO_Create.c
Purpose     : Implementation of radio widget
---------------------------END-OF-HEADER------------------------------
*/

#include "RADIO.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       RADIO_Create
*/
RADIO_Handle RADIO_Create(int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags, unsigned Para) {
  return RADIO_CreateEx(x0, y0, xsize, ysize, hParent, Flags, 0, Id, Para & 0xFF, (Para >> 8) & 0xFF);
}

#else  /* avoid empty object files */
  void RADIO_Create_C(void) {}
#endif

/************************* end of file ******************************/