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
File        : RADIO_SetText.c
Purpose     : Implementation of RADIO_SetText
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>
#include "RADIO_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       RADIO_SetText
*/
void RADIO_SetText(RADIO_Handle hObj, const char* pText, unsigned Index) {
  if (hObj) {
    RADIO_Obj* pObj;
    WM_LOCK();
    pObj = RADIO_H2P(hObj);
    if (Index < (unsigned)pObj->NumItems) {
      GUI_ARRAY_SetItem(&pObj->TextArray, Index, pText, pText ? (GUI__strlen(pText) + 1) : 0);
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */

void RADIO_SetText_c(void);
void RADIO_SetText_c(void) {}

#endif  /* #if GUI_WINSUPPORT */

/************************* end of file ******************************/
