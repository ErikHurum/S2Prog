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
File        : WM_SetId.c
Purpose     : Implementation of WM_SetId
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*        Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetId
*/
void WM_SetId(WM_HWIN hObj, int Id) {
  WM_MESSAGE Msg;
  Msg.MsgId  = WM_SET_ID;
  Msg.Data.v = Id;
  WM_SendMessage(hObj, &Msg);
}

#else
  void WM_SetId_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
