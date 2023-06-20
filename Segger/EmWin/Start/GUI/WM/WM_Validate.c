/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2009  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.00 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : WM_Validate.C
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "WM_Intern.h"
#include "Global.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__SubRect       

  The result is the smallest rectangle which includes the entire
  remaining area.

  *pDest = *pr0- *pr1;
*/
static void _SubRect(GUI_RECT* pDest, const GUI_RECT* pr0, const GUI_RECT* pr1) {
  if ((pDest == NULL) || (pr0 == NULL))
    return;
  *pDest = *pr0;	 
  if (pr1 == NULL)
    return;
  /* Check left/right sides */
  if (  (pr1->y0 <= pr0->y0)
      &&(pr1->y1 >= pr0->y1)) {
    pDest->x0 = GUI_MAX(pr0->x0, pr1->x1);
    pDest->x1 = GUI_MIN(pr0->x1, pr1->x0);
  }
  /* Check top/bottom sides */
  if (  (pr1->x0 <= pr0->x0)
      &&(pr1->x1 >= pr0->x1)) {
    pDest->y0 = GUI_MAX(pr0->y0, pr1->y1);
    pDest->y1 = GUI_MIN(pr0->y1, pr1->y0);
  }
}

/*********************************************************************
*
*       WM_ValidateRect
*
  Use this function with great care ! It should under most circumstances not
  be necessary to use it, as validation is done automatically as soon as
  a window has been redrawn. If you validate a section of a window, this
  part will not be included in the paint-command and could therefor not
  be updated.
*/
void WM_ValidateRect(WM_HWIN hWin, const GUI_RECT*pRect) {
  WM_Obj* pWin;
  if (hWin) {
    WM_LOCK();
    pWin = WM_HANDLE2PTR(hWin);
    if (pWin->Status & WM_SF_INVALID) {
      if (pRect) {
        _SubRect(&pWin->InvalidRect, &pWin->InvalidRect, pRect);
        if (WM__RectIsNZ(&pWin->InvalidRect))
          goto Done;
      }
      pWin->Status &= ~WM_SF_INVALID;
      WM__NumInvalidWindows--;
    }
  Done:
    WM_UNLOCK();
  }
}

#else
  void WM_Validate(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/