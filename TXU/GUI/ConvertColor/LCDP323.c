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
File        : LCDP323.C
Purpose     : Color conversion routines for 323 mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 323, 256 colors, BBBGGRRR
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_323
*/
unsigned LCD_Color2Index_323(LCD_COLOR Color) {
  int r, g, b;
  r = Color & 255;
  g = (Color >> 8 ) & 255;
  b = Color >> 16;
  r = (r * 7 + 127) / 255;
  g = (g + 42) / 85;
  b = (b * 7 + 127) / 255;
  return r + (g << 3) + (b << 5);
}

/*********************************************************************
*
*       LCD_Index2Color_323
*/
LCD_COLOR LCD_Index2Color_323(int Index) {
  int r, g, b;
  r = (Index & 7) * 255 / 7;
  g = ((Index >> 3) & 3) * 85;
  b = ((Index >> 5) & 7) * 255 / 7;
  return r + (g << 8) + (((U32)b) << 16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_323
*/
unsigned LCD_GetIndexMask_323(void) {
  return 0xff;
}

/*************************** End of file ****************************/
