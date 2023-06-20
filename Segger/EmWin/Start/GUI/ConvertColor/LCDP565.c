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
File        : LCDP565.C
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
#define G_BITS 6
#define R_BITS 5

#define R_MASK ((1 << R_BITS) -1)
#define G_MASK ((1 << G_BITS) -1)
#define B_MASK ((1 << B_BITS) -1)

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/

#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       LCD_API_ColorConv_565
*
* Purpose
*   API table for this color conversion mode. Only used by memory
*   devices in this mode.
*/
const LCD_API_COLOR_CONV LCD_API_ColorConv_565 = {
  LCD_Color2Index_565,
  LCD_Index2Color_565,
  LCD_GetIndexMask_565
};

#endif

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 565, 65536 colors, BBBBBGGGGGGRRRRR
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_565
*/
unsigned LCD_Color2Index_565(LCD_COLOR Color) {
  int r,g,b;
  r = (Color>> (8  - R_BITS)) & R_MASK;
  g = (Color>> (16 - G_BITS)) & G_MASK;
  b = (Color>> (24 - B_BITS)) & B_MASK;
  return r + (g << R_BITS) + (b << (G_BITS + R_BITS));
}

/*********************************************************************
*
*       LCD_GetIndexMask_565
*/
unsigned LCD_GetIndexMask_565(void) {
  return 0xffff;
}

/*************************** End of file ****************************/
