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
File        : LCDPM666.C
Purpose     : Color conversion routines for 666 mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 666, 262144 colors, RRRRRRGGGGGGBBBBBB
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_M666
*/
unsigned LCD_Color2Index_M666(LCD_COLOR Color) {
  unsigned r, g, b;
  b = (Color >>  2) & 0x3f;
  g = (Color >> 10) & 0x3f;
  r = (Color >> 18) & 0x3f;
  return r + (g << 6) + (b << 12);
}

/*********************************************************************
*
*       LCD_Index2Color_M666
*/
LCD_COLOR LCD_Index2Color_M666(int Index) {
  unsigned r, g, b;
  b = (Index & 0x00003f) <<  2;
  g = (Index & 0x000fc0) >>  4; 
  r = (Index & 0x03f000) >> 10; 
  return r + (g << 8) + (((U32)b) << 16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_M666
*/
unsigned LCD_GetIndexMask_M666(void) {
  return (unsigned)0x3ffff;
}

/*************************** End of file ****************************/
