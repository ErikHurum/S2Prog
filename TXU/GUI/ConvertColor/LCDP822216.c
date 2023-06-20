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
File        : LCDP822216.c
Purpose     : Color conversion routines for 822216 mode
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
*       LCD_Color2Index_822216
*/
unsigned LCD_Color2Index_822216(LCD_COLOR Color) {
  U8 r;
  U8 g;
  U8 b;
  U8 Alpha;
  /* Calculate color components (8 bit info) */
  r = (Color & 0xff)     >>  0;
  g = (Color & 0xff00)   >>  8;
  b = (Color & 0xff0000) >> 16;
  /* Calculate alpha component */
  Alpha = (((Color & 0xff000000) >> 24) ^ 0xff) / 0x11;
  if ((r == g) && (g == b)) {
    /* Return gray */
    return (r >> 5) | (Alpha << 4);
  }
  /* Reduce color information to 1 bit */
  r >>= 7;
  g >>= 7;
  b >>= 7;
  /* Return color */
  return (r << 0) | (g << 1) | (b << 2) | (1 << 3) | (Alpha << 4);
}

/*********************************************************************
*
*       LCD_Index2Color_822216
*/
LCD_COLOR LCD_Index2Color_822216(int Index) {
  U32 r;
  U32 g;
  U32 b;
  U32 Alpha;
  /* Calculate alpha factor */
  Alpha = (U32)((((Index & 0xf0) >> 4) ^ 0xf) * 0x11) << 24;
  if ((Index & (1 << 3)) == 0) {
    /* Return gray */
    Index &= 7;
    return Alpha | ((Index * (255 / 7) + (Index >> 1)) * 0x010101);
  }
  /* Calculate color components */
  r = (Index & (1 << 0)) ? 0x0000ff : 0;
  g = (Index & (1 << 1)) ? 0x00ff00 : 0;
  b = (Index & (1 << 2)) ? 0xff0000 : 0;
  /* Return color */
  return Alpha | r | g | b;
}

/*********************************************************************
*
*       LCD_GetIndexMask_822216
*/
unsigned LCD_GetIndexMask_822216(void) {
  return 0xff;
}

/*************************** End of file ****************************/
