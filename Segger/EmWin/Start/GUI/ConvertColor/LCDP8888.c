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
File        : LCDP8888.C
Purpose     : Color conversion routines for 8888 mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 8888, 4294967296 colors + 8 bit transparency, TTTTTTTTBBBBBBBBGGGGGGGGRRRRRRRR
*
**********************************************************************
*/
#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       LCD_API_ColorConv_8888
*
* Purpose
*   API table for this color conversion mode. Only used by memory
*   devices in this mode.
*/
const LCD_API_COLOR_CONV LCD_API_ColorConv_8888 = {
  LCD_Color2Index_8888,
  LCD_Index2Color_8888,
  LCD_GetIndexMask_8888
};

#endif

/*********************************************************************
*
*       LCD_Color2Index_8888
*/
unsigned LCD_Color2Index_8888(LCD_COLOR Color) {
  return Color;
}

/*********************************************************************
*
*       LCD_GetIndexMask_8888
*/
unsigned LCD_GetIndexMask_8888(void) {
  return (unsigned)0xffffffff;
}

/*************************** End of file ****************************/
