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
File        : LCDInfo0.c
Purpose     : Routines returning info at runtime
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

int LCD_GetXSize       (void) { return LCD_GetXSizeEx       (GUI_Context.SelLayer);}
int LCD_GetYSize       (void) { return LCD_GetYSizeEx       (GUI_Context.SelLayer);}
int LCD_GetVXSize      (void) { return LCD_GetVXSizeEx      (GUI_Context.SelLayer);}
int LCD_GetVYSize      (void) { return LCD_GetVYSizeEx      (GUI_Context.SelLayer);}
int LCD_GetBitsPerPixel(void) { return LCD_GetBitsPerPixelEx(GUI_Context.SelLayer);}
U32 LCD_GetNumColors   (void) { return LCD_GetNumColorsEx   (GUI_Context.SelLayer);}
int LCD_GetYMag        (void) { return LCD_GetYMagEx        (GUI_Context.SelLayer);}
int LCD_GetXMag        (void) { return LCD_GetXMagEx        (GUI_Context.SelLayer);}
int LCD_GetFixedPalette(void) { return LCD_GetFixedPaletteEx(GUI_Context.SelLayer);}

/*************************** End of file ****************************/
