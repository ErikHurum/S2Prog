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
File        : GUIAlloc.C
Purpose     : Dynamic memory management
----------------------------------------------------------------------
*/

#include <string.h>           /* for memcpy, memset */

#include "GUI_Private.h"

/*********************************************************************
*
*       Internal memory management
*
**********************************************************************
*/

/*********************************************************************
*
*       GUI_ALLOC_AllocZero
*/
GUI_HMEM GUI_ALLOC_AllocZero(GUI_ALLOC_DATATYPE Size) {
  GUI_HMEM hMem;
  GUI_LOCK();
  GUI_DEBUG_LOG2("\nGUI_ALLOC_Alloc... requesting %d, %d avail", Size, GUI_ALLOC_GetMaxSize());
  hMem = GUI_ALLOC_AllocNoInit(Size);
  if (hMem) {
    GUI_MEMSET((U8*)GUI_ALLOC_h2p(hMem), 0, Size);   /* Zeroinit ! */
  }
  GUI_UNLOCK();
  return hMem;
}

/*************************** End of file ****************************/