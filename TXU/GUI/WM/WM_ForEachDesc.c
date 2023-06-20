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
File        : WM_ForEachDesc.c
Purpose     : Implementation of WM_ForEachDesc
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*         Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       WM_ForEachDesc
*/
void WM_ForEachDesc(WM_HWIN hWin, WM_tfForEach * pcb, void * pData) {
  WM_LOCK();
  WM__ForEachDesc(hWin, pcb, pData);
  WM_UNLOCK();
}

#else
  void WM_ForEachDesc_C(void);
  void WM_ForEachDesc_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/