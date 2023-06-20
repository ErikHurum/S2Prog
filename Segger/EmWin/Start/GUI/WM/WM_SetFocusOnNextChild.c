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
File        : WM_SetFocusOnNextChild.c
Purpose     : Implementation of WM_SetFocusOnNextChild
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetNextChild
*
* Purpose:
*   Returns a handle to the next child of a window.
*
* Parameters:
*   hParent:  handle of parent window.
*   hChild:   handle of child to begin our search to its next sibling.
*
* Return value:
*   Handle to next child if we found one.
*   0 if window has no other children.
*/
static WM_HWIN _GetNextChild(WM_HWIN hParent, WM_HWIN hChild) {
  WM_HWIN hObj = 0;
  WM_Obj* pObj;
  if (hChild) {
    pObj = WM_HANDLE2PTR(hChild);
    hObj = pObj->hNext;
  }
  if (!hObj) {
    pObj = WM_HANDLE2PTR(hParent);
    hObj = pObj->hFirstChild;
  }
  if (hObj != hChild) {
    return hObj;
  }
  return 0;
}

/*********************************************************************
*
*       _SetFocusOnNextChild
*
* Purpose:
*   Sets the focus on next focussable child of a window.
*
* Return value:
*   Handle of focussed child, if we found an other focussable child
*   as the current. Otherwise the return value is zero.
*/
static WM_HWIN _SetFocusOnNextChild(WM_HWIN hParent) {
  WM_HWIN hChild, hWin;
  hChild = WM__GetFocussedChild(hParent);
  hChild = _GetNextChild(hParent, hChild);
  hWin   = hChild;
  while ((WM_IsFocussable(hWin) == 0) && hWin) {
    hWin = _GetNextChild(hParent, hWin);
    if (hWin == hChild) {
      break;
    }
  }
  if (hWin) {
    int r;
    #if (GUI_NUM_LAYERS > 1)
      int OldTouchedLayer;
      OldTouchedLayer  = WM__TouchedLayer;
      WM__TouchedLayer = WM__GetTopLevelLayer(hWin);
    #endif
    r = WM_SetFocus(hWin);
    #if (GUI_NUM_LAYERS > 1)
      WM__TouchedLayer = OldTouchedLayer;
    #endif
    if (r == 0) {
      return hWin;
    }
  }
  return 0;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetFocusOnNextChild
*/
WM_HWIN WM_SetFocusOnNextChild(WM_HWIN hParent) {
  WM_HWIN r = 0;
  if (hParent) {
    WM_LOCK();
    r = _SetFocusOnNextChild(hParent);
    WM_UNLOCK();
  }
  return r;
}

#else
  void WM_SetFocusOnNextChild_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/