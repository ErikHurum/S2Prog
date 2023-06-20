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
File        : GUITime.C
Purpose     : Time related routines
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
*       GUI_GetTime
*/
int GUI_GetTime(void) {
  return GUI_X_GetTime();
}

/*********************************************************************
*
*       GUI_Delay
*/
void GUI_Delay(int Period) {
  int EndTime = GUI_GetTime()+Period;
  int tRem; /* remaining Time */
  #if (GUI_OS)
    GUI_ASSERT_NO_LOCK();
  #endif
  while (tRem = EndTime- GUI_GetTime(), tRem>0) {
    GUI_Exec();
    GUI_X_Delay((tRem >5) ? 5 : tRem);
  }
}

/*************************** End of file ****************************/
