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
File        : WM_SetDesktopColor.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern_ConfDep.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetDesktopColorEx
*/
GUI_COLOR WM_SetDesktopColorEx(GUI_COLOR Color, unsigned int LayerIndex) {
  GUI_COLOR r = GUI_INVALID_COLOR;
  if (LayerIndex <  GUI_NUM_LAYERS) {
    r = WM__aBkColor[LayerIndex];
    WM__aBkColor[LayerIndex] = Color;
    WM_InvalidateWindow(WM__ahDesktopWin[LayerIndex]);
  }
  return r;
}

/*********************************************************************
*
*       WM_SetDesktopColor
*/
GUI_COLOR WM_SetDesktopColor(GUI_COLOR Color) {
  return WM_SetDesktopColorEx(Color, GUI_Context.SelLayer);
}

/*********************************************************************
*
*       WM_SetDesktopColors
*/
void WM_SetDesktopColors(GUI_COLOR Color) {
  int i;
  for (i = 0; i < GUI_NUM_LAYERS; i++) {
    WM_SetDesktopColorEx(Color, i);
  }
}

#else
  void WM_SetDesktopColor_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
