/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2009  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.00 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI__SetPixelAlpha.c
Purpose     : Implementation of said function
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

/*********************************************************************
*
*       _MixColors
*/
LCD_COLOR GUI__MixColors(LCD_COLOR Color, LCD_COLOR BkColor, U8 Intens) {
  U32 r, g, b;
  U8 Alpha;
  /* Calc Color seperations for FgColor first */
  r = (Color & 0x0000ff) * Intens;
  g = (Color & 0x00ff00) * Intens;
  b = (Color & 0xff0000) * Intens;
  /* Add Color seperations for BkColor */
  Intens = 255 - Intens;
  r += (BkColor & 0x0000ff) * Intens;
  g += (BkColor & 0x00ff00) * Intens;
  b += (BkColor & 0xff0000) * Intens;
  r = (r >> 8) & 0x0000ff;
  g = (g >> 8) & 0x00ff00;
  b = (b >> 8) & 0xff0000;
  Color = r + g + b;
  Alpha = BkColor >> 24;
  if (Alpha == 0xFF) {
    Color |= (U32)Intens << 24;
  } else {
    Color |= (U32)((Alpha + Intens) >> 1) << 24;
  }
  return Color;
}

/*********************************************************************
*
*       GUI__SetPixelAlpha
*/
void GUI__SetPixelAlpha(int x, int y, U8 Alpha, LCD_COLOR Color) {
  if ((y >= GUI_Context.ClipRect.y0) && (y <= GUI_Context.ClipRect.y1)) {
    if ((x >= GUI_Context.ClipRect.x0) && (x <= GUI_Context.ClipRect.x1)) {
      LCD_COLOR BkColor;
      LCD_PIXELINDEX Index;
      BkColor = LCD_GetPixelColor(x, y);
      Color   = GUI__MixColors(Color, BkColor, Alpha);
      Index   = LCD_Color2Index(Color);
      //LCDDEV_L0_SetPixelIndex(x, y, Index);
      LCDDEV_L0_SetPixelIndex(GUI_Context.apDevice[GUI_Context.SelLayer], x, y, Index);
      //GUI_Context.apDevice[GUI_Context.SelLayer]->pDeviceAPI->pfSetPixelIndex(GUI_Context.apDevice[GUI_Context.SelLayer], x, y, Index);
    }
  }
}

/*************************** End of file ****************************/
