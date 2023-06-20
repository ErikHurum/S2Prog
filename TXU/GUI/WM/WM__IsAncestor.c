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
File        : WM__IsAncestor.c
Purpose     : Implementation of WM__IsAncestor
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
*       WM__IsAncestor
*
* Return value:
*   if hChild is indeed a descendent (Child or child of child etc.) : 1
*   Else: 0
*
*
*/
int WM__IsAncestor(WM_HWIN hChild, WM_HWIN hParent) {
  int r = 0;
  if (hChild && hParent) {
    while(hChild) {
      WM_Obj *pChild = WM_H2P(hChild);
      if (pChild->hParent == hParent) {
        r = 1;
        break;
      }
      hChild = pChild->hParent;
    }
  }
  return r;
}

/*********************************************************************
*
*       WM__IsAncestor
*
* Return value:
*   if hChild is indeed a descendent (Child or child of child etc.) : 1
*   Else: 0
*
*
*/
int WM__IsAncestorOrSelf(WM_HWIN hChild, WM_HWIN hParent) {
  if (hChild == hParent) {
    return 1;
  }
  return WM__IsAncestor(hChild, hParent);
}
#else
  void WM__IsAncestor_c(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
