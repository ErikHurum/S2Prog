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
File        : LCDPM8888.C
Purpose     : Color conversion routines for 8888 mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 8888, 4294967296 colors + 8 bit transparency, TTTTTTTTRRRRRRRRGGGGGGGGBBBBBBBB
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Index2Color_M8888
*/
LCD_COLOR LCD_Index2Color_M8888(int Index) {
  U32 r, g, b;
  b = Index & 0xff;
  g = (Index & 0xff00) >> 8;
  r = (Index & 0xff0000) >> 16;
  return (Index & 0xff000000) | (b << 16) | (g << 8) | r;
}

/*********************************************************************
*
*       LCD_Color2Index_M8888
*/
unsigned LCD_Color2Index_M8888(LCD_COLOR Color) {
  U32 r, g, b;
  b = Color & 0xff;
  g = (Color & 0xff00) >> 8;
  r = (Color & 0xff0000) >> 16;
  return (Color & 0xff000000) | (b << 16) | (g << 8) | r;
}

/*********************************************************************
*
*       LCD_GetIndexMask_M8888
*/
unsigned LCD_GetIndexMask_M8888(void) {
  return (unsigned)0xffffffff;
}

/*************************** End of file ****************************/
