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
File        : GUIDEMO_Speed.c
Purpose     : Speed demo
----------------------------------------------------------------------
*/

#include <stdlib.h>  /* for rand */
#include "GUI.h"
#include "GUIDEMO.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const GUI_COLOR _aColor[8] = {
  0x000000, 
  0x0000FF, 
  0x00FF00, 
  0x00FFFF, 
  0xFF0000, 
  0xFF00FF, 
  0xFFFF00, 
  0xFFFFFF
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetPixelsPerSecond
*/
static U32 _GetPixelsPerSecond(void) {
  GUI_COLOR Color, BkColor;
  int x0, y0, x1, y1, xSize, ySize;
  U32 TimeStart, TimeMin, TimeEnd, Cnt, PixelsPerSecond;
  xSize = LCD_GetXSize() / 2;
  ySize = LCD_GetYSize() / 3;
  Cnt = 0;
  x0 = 0;
  y0 = ySize * 2;
  x1 = x0 + xSize - 1;
  y1 = y0 + ySize - 1;
  Color = GUI_GetColor();
  BkColor = GUI_GetBkColor();
  GUI_SetColor(BkColor);
  TimeStart = GUI_GetTime();
  TimeMin = TimeStart + 100;
  do {
    GUI_FillRect(x0, y0, x1, y1);
    TimeEnd = GUI_GetTime();
    Cnt++;
  } while (TimeEnd < TimeMin);
  PixelsPerSecond = (1000 * (U32)xSize * ySize * Cnt) / (TimeEnd - TimeStart + 1);
  GUI_SetColor(Color);
  return PixelsPerSecond;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIDEMO_Speed
*/
void GUIDEMO_Speed(void) {
  int t, i;
  U32 PixelsPerSecond;
  unsigned aColorIndex[8];
  GUIDEMO_ShowIntro("High speed",
                    "\nmulti layer clipping"
                    "\nhighly optimized drivers"
                    );
  for (i = 0; i< 8; i++) {
    aColorIndex[i] = GUI_Color2Index(_aColor[i]);
  }  
  t = GUI_GetTime();
  for (i = 0; ((GUI_GetTime() - t) < 8000) && !GUIDEMO_CheckCancel(); i++) {
    GUI_RECT r;
    GUI_SetColorIndex(aColorIndex[i&7]);
    /* Calculate random positions */
    r.x0 = rand() % LCD_XSIZE - LCD_XSIZE / 2;
    r.y0 = rand() % LCD_YSIZE - LCD_YSIZE / 2;
    r.x1 = r.x0 + 20 + rand() % LCD_XSIZE;
    r.y1 = r.y0 + 20 + rand() % LCD_YSIZE;
    GUI_FillRect(r.x0, r.y0, r.x1, r.y1);
    /* Clip rectangle to visible area and add the number of pixels (for speed computation) */
    if (r.x1 >= LCD_XSIZE) {
      r.x1 = LCD_XSIZE - 1;
    }
    if (r.y1 >= LCD_YSIZE) {
      r.y1 = LCD_YSIZE - 1;
    }
    if (r.x0 < 0 ) {
      r.x0 = 0;
    }
    if (r.y1 < 0) {
      r.y1 = 0;
    }
    /* Allow short breaks so we do not use all available CPU time ... */
  }
  GUI_Clear();
  GUIDEMO_NotifyStartNext();
  #if GUIDEMO_LARGE
    GUI_SetFont(&GUI_FontComic24B_ASCII);
  #elif !(GUIDEMO_TINY)
    GUI_SetFont(&GUI_Font16B_ASCII);
  #else
    GUI_SetFont(&GUI_Font13B_ASCII);
  #endif
  PixelsPerSecond = _GetPixelsPerSecond();
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringAt("Pixels/sec: ", 5, (LCD_YSIZE - GUI_GetFontSizeY()) / 2);
  GUI_DispDecMin(PixelsPerSecond);
  GUIDEMO_Wait();
}
