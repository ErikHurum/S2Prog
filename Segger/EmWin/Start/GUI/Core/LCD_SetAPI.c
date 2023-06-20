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
File        : LCD_SetAPI.c
Purpose     : Implementation of said function
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */

#include "GUI_Private.h"

#if GUI_SUPPORT_DEVICES

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_SetAPI
*
* Purpose:
*   Sets the API table for a layer.
*   Some high level software (such as the VNC server, but maybe also the mouse "Cursor" module)
*   may need to override these pointers in order to link itself into the chain
*   of drawing routines.
*/
const tLCDDEV_APIList* LCD_SetAPI(const tLCDDEV_APIList* pAPI, int Index) {
  const tLCDDEV_APIList* pOldAPI;
  pOldAPI = LCD_aAPI[Index];
  /* Also aplly changes to current context if LCD of this layer is selected */
  if ((GUI_Context.SelLayer == Index) && (GUI_Context.hDevData == 0)) {
    GUI_Context.pDeviceAPI = pAPI;
  }
  LCD_aAPI[Index] = pAPI;
  return pOldAPI;
}

#if GUI_OS

const tLCDDEV_APIList* LCD_SetAPIForAll(const tLCDDEV_APIList* pAPI, int Index) {
  GUI_CONTEXT * pContext;
  int i = 0;
  while ((pContext = GUITASK_GetpContext(i++)) != NULL) {
    pContext->pDeviceAPI = pAPI;
  }
  return LCD_SetAPI(pAPI, Index);
}

#endif

#else

void LCD_SetAPI_C(void);
void LCD_SetAPI_C(void) {}

#endif

/*************************** End of file ****************************/
