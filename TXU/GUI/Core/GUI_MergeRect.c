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
File        : GUI_MergeRect.c
Purpose     : Implementation of GUI_MergeRect
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "GUIDebug.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define Min(v0,v1) ((v0>v1) ? v1 : v0)
#define Max(v0,v1) ((v0>v1) ? v0 : v1)

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_MergeRect
*
* Purpose:
*   Calc smalles rectangles containing both rects.
*/
void GUI_MergeRect(GUI_RECT* pDest, const GUI_RECT* pr0, const GUI_RECT* pr1) {
  if (pDest) {
    if (pr0 && pr1) {
      pDest->x0 = Min(pr0->x0, pr1->x0);
      pDest->y0 = Min(pr0->y0, pr1->y0);
      pDest->x1 = Max(pr0->x1, pr1->x1);
      pDest->y1 = Max(pr0->y1, pr1->y1);
      return;
    }
    *pDest = *(pr0 ? pr0 : pr1);
  }
}

/*************************** End of file ****************************/
