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
File        : LCDP84444.c
Purpose     : Color conversion routines for 84444 mode
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
*       LCD_Color2Index_84444
*/
unsigned LCD_Color2Index_84444(LCD_COLOR Color) {
  U8 r;
  U8 g;
  U8 b;
  U8 Alpha;
  /* Calculate color components (8 bit info) */
  r = (Color & 0xff)       >>  0;
  g = (Color & 0xff00)     >>  8;
  b = (Color & 0xff0000)   >> 16;
  /* Calculate alpha component */
  Alpha = 3 - ((Color & 0xff000000) >> 24) / 0x40;
  if (Alpha == 0) {
    return 0;
  }
  if ((r == g) && (g == b)) {
    /* Return gray */
    return (Alpha * 0x10) + (r >> 4);
  }
  /* Reduce color information */
  r = r / 0x40;
  g = g / 0x40;
  b = b / 0x40;
  /* Return color */
  return r | (g << 2) | (b << 4) | (Alpha << 6);
}

/*********************************************************************
*
*       LCD_Index2Color_84444
*/
LCD_COLOR LCD_Index2Color_84444(int Index) {
  U32 r;
  U32 g;
  U32 b;
  U32 Alpha;
  if (Index < 0x40) {
    /* Gray */
    if (Index < 0x10) {
      return 0xff000000;
    }
    /* Calculate alpha factor */
    Alpha = (3 - ((Index & 0x30) >> 4)) * 0x55;
    return (Alpha << 24) | (Index & 0xf) * 0x111111;
  }
  /* Calculate alpha factor */
  Alpha = (3 - (Index >> 6)) * 0x55;
  /* Calculate color components */
  r = ((Index & 0x03) >> 0) * 0x55;
  g = ((Index & 0x0c) >> 2) * 0x55;
  b = ((Index & 0x30) >> 4) * 0x55;
  /* Return color */
  return r | (g << 8) | (b << 16) | (Alpha << 24);
}

/*********************************************************************
*
*       LCD_GetIndexMask_84444
*/
unsigned LCD_GetIndexMask_84444(void) {
  return 0xff;
}

/*************************** End of file ****************************/
