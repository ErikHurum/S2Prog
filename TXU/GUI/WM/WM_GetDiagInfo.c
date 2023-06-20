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
File        : WM_GetDiagInfo.c
Purpose     : Implementation of diagnostics info
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_GetNumWindows
*
*/

int WM_GetNumWindows(void) {
  return WM__NumWindows;
}

/*********************************************************************
*
*       WM_GetNumInvalidWindows
*
*/
int WM_GetNumInvalidWindows(void) {
  return WM__NumInvalidWindows;
}




#else
  void WM_GetDiagInfo_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
