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
File        : LCDPM8565.C
Purpose     : Color conversion routines for 8565 mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define B_BITS 5
#define G_BITS 6
#define R_BITS 5

#define R_MASK ((1 << R_BITS) -1)
#define G_MASK ((1 << G_BITS) -1)
#define B_MASK ((1 << B_BITS) -1)

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 8565, 65536 colors + 8 bit transparency, TTTTTTTTxxxxxxxxRRRRRGGGGGGBBBBB
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_M8565
*/
unsigned LCD_Color2Index_M8565(LCD_COLOR Color) {
  unsigned r, g, b;
  U32 Alpha;
  Alpha = ((U32)Color & 0xFF000000) ^ 0xFF000000;
  r = (Color >> (8  - R_BITS)) & R_MASK;
  g = (Color >> (16 - G_BITS)) & G_MASK;
  b = (Color >> (24 - B_BITS)) & B_MASK;
  return (U32)(Alpha | (b + (g << B_BITS) + (r << (G_BITS + B_BITS))));
}

/*********************************************************************
*
*       LCD_Index2Color_M8565
*/
LCD_COLOR LCD_Index2Color_M8565(int Index) {
  unsigned r, g, b;
  U32 Alpha;
  Alpha = ((U32)Index & 0xFF000000) ^ 0xFF000000;
  /* Seperate the color masks */
  b = Index                                  & B_MASK;
  g = (Index >> B_BITS)                      & G_MASK;
  r = ((unsigned)Index >> (B_BITS + G_BITS)) & R_MASK;
  /* Convert the color masks */
  r = r * 255 / R_MASK;
  g = g * 255 / G_MASK;
  b = b * 255 / B_MASK;
  return (U32)(Alpha | (r + (g << 8) + (((U32)b) << 16)));
}

/*********************************************************************
*
*       LCD_GetIndexMask_M8565
*/
unsigned LCD_GetIndexMask_M8565(void) {
  return (unsigned)0xffffffff;
}

/*************************** End of file ****************************/
