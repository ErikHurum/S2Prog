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
File        : WIDGET_Effect_None.c
Purpose     : Effect routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>

#include "WIDGET.h"
#include "GUIDebug.h"
#include "GUI.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define WIDGET_H2P(hWin)        ((WIDGET*)GUI_ALLOC_h2p(hWin))

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawDown
*/
static void _DrawDown(void) {
}

/*********************************************************************
*
*       _DrawUp
*/
static void _DrawUp(void) {
}

/*********************************************************************
*
*       _DrawDownRect
*/
static void _DrawDownRect(const GUI_RECT* pRect) {
  GUI_USE_PARA(pRect);
}

/*********************************************************************
*
*       _DrawUpRect
*/
static void _DrawUpRect(const GUI_RECT* pRect) {
  GUI_USE_PARA(pRect);
}

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WIDGET_Effect_None
*
* Purpose:
*   Structure of type WIDGET_EFFECT which contains the function pointers
*   used to draw the effect. It also contains the effect size
*   which specifies the number of pixels used by the effect frame.
*/
const WIDGET_EFFECT WIDGET_Effect_None = {
  0,
  _DrawUp,
  _DrawUpRect,
  _DrawDown,
  _DrawDownRect,
};

#else                            /* Avoid problems with empty object modules */
  void WIDGET_Effect_None_C(void) {}
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
