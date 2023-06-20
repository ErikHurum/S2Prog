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
File        : LCDPM332.C
Purpose     : Color conversion routines for -332 mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == -332, 256 colors, RRRGGGBB
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_M332
*/
unsigned LCD_Color2Index_M332(LCD_COLOR Color) {
  unsigned r, g, b;
  r = Color & 255;
  g = (Color >> 8 ) & 255;
  b = Color >> 16;
  r = (r * 7 + 127) / 255;
  g = (g * 7 + 127) / 255;
  b = (b + 42) / 85;
  return b + (g << 2) + (r << 5);
}

/*********************************************************************
*
*       LCD_Index2Color_M332
*/
LCD_COLOR LCD_Index2Color_M332(int Index) {
  unsigned r, g, b;
  b = (Index & 3) * 85;
  g = ((Index >> 2) & 7) * 255 / 7;
  r = ((Index >> 5) & 7) * 255 / 7;
  return r + (g << 8) + (((U32)b) << 16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_M332
*/
unsigned LCD_GetIndexMask_M332(void) {
  return 0xff;
}

/*************************** End of file ****************************/
