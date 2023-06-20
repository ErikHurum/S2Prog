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
File        : LCD_ReadRect.c
Purpose     : Implementation of LCD_ReadRect
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"
#include "LCD_Private.h"      /* Required for configuration, APIList */

#if GUI_SUPPORT_DEVICES

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_ReadRectEx
*/
void LCD_ReadRectEx(int x0, int y0, int x1, int y1, LCD_PIXELINDEX * pBuffer, void * (* pfGetDevFunc)(int Index), unsigned (* pfGetPixelIndex)(int x, int y)) {
  void (* pfReadRect)(int x0, int y0, int x1, int y1, LCD_PIXELINDEX * pBuffer);
  pfReadRect = (void (*)(int, int, int, int, LCD_PIXELINDEX *))pfGetDevFunc(LCD_DEVFUNC_READRECT);
  if (!pfReadRect) {
    while (y0 <= y1) {
      int x;
      for (x = x0; x <= x1; x++) {
        *pBuffer++ = pfGetPixelIndex(x, y0);
      }
      y0++;
    }
  } else {
    pfReadRect(x0, y0, x1, y1, pBuffer);
  }
}

/*********************************************************************
*
*       LCD_ReadRect
*/
void LCD_ReadRect(int x0, int y0, int x1, int y1, LCD_PIXELINDEX * pBuffer, const tLCDDEV_APIList * pAPI) {
  LCD_ReadRectEx(x0, y0, x1, y1, pBuffer, pAPI->pfGetDevFunc, pAPI->pfGetPixelIndex);
}

#else
  void LCD_ReadRect_C(void);
  void LCD_ReadRect_C(void) {}
#endif

/*************************** End of file ****************************/
