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
File        : WM_Timer.c
Purpose     : Implementetion of WM_CreateTimer, WM_DeleteTimer
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "WM_Intern.h"


/* Typical configuration: */

#if GUI_WINSUPPORT && !defined(GUI_X_CREATE_TIMER)   /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbTimer
*/
static void _cbTimer(GUI_TIMER_MESSAGE * pTM) {
  WM_TIMER_OBJ * pObj;
  if (pTM->Context) {
    WM_MESSAGE Msg = {0};
    pObj = (WM_TIMER_OBJ *)GUI_ALLOC_h2p((WM_HTIMER)pTM->Context);
    Msg.MsgId  = WM_TIMER;
    Msg.Data.v = pTM->Context; /* Handle of timer */
    WM_SendMessage(pObj->hWin, &Msg);
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_DeleteTimer
*
* Purpose:
*   API function (optional).
*   Allows the application to delete a timer. 
*/
void WM_DeleteTimer(WM_HTIMER hTimer) {
  if (hTimer) {
    WM_TIMER_OBJ * pTimer;
    WM_LOCK();
    pTimer = (WM_TIMER_OBJ *) GUI_ALLOC_h2p(hTimer);
    GUI_TIMER_Delete(pTimer->hTimer);
    GUI_ALLOC_Free(hTimer);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       WM_CreateTimer
*
*  Returns:    0 if failed, else handle of timer
*  Parameters:
*                hWin        Window handle of the window to receive the WM_TIMER message
*                UserId      User defined Id. If not needed, use 0.
*                Period      Number of time units (ticks)
*                Mode        0: one-shot
*
*/
WM_HTIMER WM_CreateTimer(WM_HWIN hWin, int UserId, int Period, int Mode) {
  WM_HTIMER hTimer;
  GUI_USE_PARA(Mode);
  WM_LOCK();
  hTimer = GUI_ALLOC_AllocZero(sizeof(WM_TIMER_OBJ));
  if (hTimer) {
    WM_TIMER_OBJ * pTimer;
    pTimer = (WM_TIMER_OBJ *) GUI_ALLOC_h2p(hTimer);
    pTimer->hWin    = hWin;
    pTimer->UserId  = UserId;
#ifndef GUI_X_CREATE_TIMER
    pTimer->hTimer  = GUI_TIMER_Create(_cbTimer, GUI_GetTime() + Period, hTimer, 0);
#else
    pTimer->hTimer  = GUI_TIMER_Create(_cbTimer, 0, hTimer, 0);
#endif
    if (pTimer->hTimer) {
      GUI_TIMER_SetPeriod(pTimer->hTimer, Period);
    } else {
      GUI_ALLOC_Free(hTimer);
      hTimer = 0;
    }
  }
  WM_UNLOCK();
  return hTimer;
}

/*********************************************************************
*
*       WM_RestartTimer
*/
void WM_RestartTimer(WM_HTIMER hTimer, int Period) {
  if (hTimer) {
    WM_TIMER_OBJ * pTimer;
    WM_LOCK();
    pTimer = (WM_TIMER_OBJ *)GUI_ALLOC_h2p(hTimer);
    if (Period) {
      GUI_TIMER_SetPeriod(pTimer->hTimer, Period);
    }
    GUI_TIMER_Restart  (pTimer->hTimer);
    WM_UNLOCK();
  }
}

#else
  void WM_Timer_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
