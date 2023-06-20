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
File        : LCD5.C
Purpose     : Color conversion routines for 5 bpp gray LCDs
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_5
*/
unsigned LCD_Color2Index_5(LCD_COLOR Color) {
  unsigned r, g, b;
  r =  (Color        & 0xff) * 31;
  g = ((Color >>  8) & 0xff) * 31;
  b = ((Color >> 16) & 0xff) * 31;
  return (r + g + b) / (255 * 3);
}

/*********************************************************************
*
*       LCD_Index2Color_5
*/
LCD_COLOR LCD_Index2Color_5(int Index) {
  U32 g;
  g = (Index * 31 * 255) / (31 * 31);
  return g | (g << 8) | (g << 16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_5
*/
unsigned LCD_GetIndexMask_5(void) {
  return 0x1f;
}

/*************************** End of file ****************************/
