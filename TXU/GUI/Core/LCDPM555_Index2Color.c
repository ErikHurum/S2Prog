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
File        : LCDPM555_Index2Color.c
Purpose     : Color conversion routines
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
#define G_BITS 5
#define R_BITS 5

#define R_MASK ((1 << R_BITS) -1)
#define G_MASK ((1 << G_BITS) -1)
#define B_MASK ((1 << B_BITS) -1)

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 555, 32768 colors, 0RRRRRGGGGGBBBBB
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Index2Color_M555
*/
LCD_COLOR LCD_Index2Color_M555(int Index) {
  unsigned int r,g,b;
  /* Seperate the color masks */
  b = Index                                  & B_MASK;
  g = (Index >> B_BITS)                      & G_MASK;
  r = ((unsigned)Index >> (B_BITS + G_BITS)) & R_MASK;
  /* Convert the color masks */
  r = r * 255 / R_MASK;
  g = g * 255 / G_MASK;
  b = b * 255 / B_MASK;
  return r + (g<<8) + (((U32)b)<<16);
}

/*************************** End of file ****************************/