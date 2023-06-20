/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2008  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.18 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_MEMDEV_MarkDirty.c
Purpose     : Implementation of GUI_MEMDEV_MarkDirty
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_MEMDEV_MarkDirty
*/
void GUI_MEMDEV_MarkDirty(GUI_MEMDEV_Handle hMem, int x0, int y0, int x1, int y1) {
  GUI_MEMDEV * pDev;
  GUI_LOCK();                   /* Needed so the memory management does not complain */
  pDev   = GUI_MEMDEV_H2P(hMem);
  if (pDev->hUsage) {
    GUI_USAGE  * pUsage;
    pUsage = GUI_USAGE_H2P(pDev->hUsage);
    GUI_USAGE_AddRect(pUsage, x0, y0, x1 - x0 + 1, y1 - y0 + 1);
  }
  GUI_UNLOCK();
}

#else

void GUI_MEMDEV_MarkDirty_C(void);
void GUI_MEMDEV_MarkDirty_C(void) {}

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
