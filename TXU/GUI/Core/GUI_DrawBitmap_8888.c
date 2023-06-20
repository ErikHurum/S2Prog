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
File        : GUI_DrawBitmap_8888.c
Purpose     : Drawing routine for drawing a 16bpp bitmap
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"
#include "LCD_Private.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetPixelAlpha
*/
/*
static void _SetPixelAlpha(int x, int y, U8 Alpha, LCD_COLOR Color) {
  LCD_COLOR BkColor;
  LCD_PIXELINDEX Index;
  BkColor = LCD_GetPixelColor(x, y);
  Color   = GUI__MixColors(Color, BkColor, Alpha);
  Index   = LCD_Color2Index(Color);
  LCDDEV_L0_SetPixelIndex(x, y, Index);
}
*/

/*********************************************************************
*
*       _FillRectAlpha
*/
static void _FillRectAlpha(int x0, int y0, int x1, int y1, U8 Alpha, LCD_COLOR Color) {
  do {
    int x;
    for (x = x0; x <= x1; x++) {
      GUI__SetPixelAlpha(x, y0, Alpha, Color);
    }
  } while (++y0 <= y1);
}

/*********************************************************************
*
*       _GetDistToNextAlpha
*/
static int _GetDistToNextAlpha(const U32 GUI_UNI_PTR * pPixel, U32 RemPixels) {
  U32 Cnt = 0;
  do {
    if (*(pPixel++) & 0xff000000) {
      break;
    }
    Cnt++;
  } while (--RemPixels);
  return Cnt;
}

/*********************************************************************
*
*       _DoClipping
*/
static int _DoClipping(int * px0, int * py0, int * pxsize, int * pysize, const U32 ** ppData, int BytesPerLine) {
  int x1, y1, Diff;
  const U32 * pData;
  pData = *ppData;
  /* Perform clipping */
  y1 = *py0 + *pysize - 1;
  x1 = *px0 + *pxsize - 1;
  /* Clip Y */
  if (*py0 < GUI_Context.ClipRect.y0) {
    Diff = GUI_Context.ClipRect.y0 - *py0;
    *py0   = GUI_Context.ClipRect.y0;
    #if GUI_SUPPORT_LARGE_BITMAPS                       /* Required only for 16 bit CPUs if some bitmaps are >64kByte */
      pData += (U32)Diff * (U32)BytesPerLine / 4;
    #else
      pData += (unsigned)Diff * (unsigned)BytesPerLine / 4;
    #endif
    *pysize -= Diff;
  }
  Diff = y1 - GUI_Context.ClipRect.y1;
  if (Diff > 0) {
    *pysize -= Diff;
  }
  if (*pysize <=0) {
		return 1;
  }
  /* Clip right side */
  Diff = x1 - GUI_Context.ClipRect.x1;
  if (Diff > 0) {
    *pxsize -= Diff;
  }
  /* Clip left side */
  if (*px0 < GUI_Context.ClipRect.x0) {
    Diff = GUI_Context.ClipRect.x0 - *px0;
		*pxsize -= Diff;
    pData += Diff; 
    *px0 += Diff; 
  }
  if (*pxsize <=0) {
		return 1;
  }
  *ppData = pData;
  return 0;
}

/*********************************************************************
*
*       _DrawBitmap
*/
static void _DrawBitmap(int x0, int y0, int xsize, int ysize, const U8 GUI_UNI_PTR * pPixel, int xMag, int yMag, tLCDDEV_Index2Color * pfIndex2Color) {
  const U32 * pData;
  int y, OldIndex, Mag, BytesPerLine, UseDrawBitmap = 0;
  U32 PrevColor;
  OldIndex = LCD_GetColorIndex();
  PrevColor = GUI_INVALID_COLOR;
  pData = (const U32 *)pPixel;
  Mag = (xMag | yMag);
  BytesPerLine = xsize * 4;
  /* Check if bitmaps color format fits to the current color conversion */
  if (Mag == 1) {
    tLCDDEV_Index2Color * pfIndex2ColorCompare;
    pfIndex2ColorCompare = GUI_GetpfIndex2ColorEx(GUI_Context.SelLayer); /* Get pointer to color conversion routine */
    if (pfIndex2ColorCompare == pfIndex2Color) {                         /* Check if color conversion routine fits  */
      UseDrawBitmap = 1;
    }
  }
  if (UseDrawBitmap) {
    do {
      int xRem, x, Diff;
      /* Perform vertical clipping */
      Diff = GUI_Context.ClipRect.y0 - y0;
      if (Diff > ysize) {
        break;
      }
      if (Diff > 0) {
        y0    += Diff;
        pData += Diff * xsize;
      }
      if (y0 > GUI_Context.ClipRect.y1) {
        break;
      }
      /* Perform horizontal clipping */
      xRem = xsize;
      x = x0;
      Diff = GUI_Context.ClipRect.x0 - x0;
      if (Diff > 0) {
        x     += Diff;
        pData += Diff;
        xRem  -= Diff;
      }
      if (x > GUI_Context.ClipRect.x1) {
        break;
      }
      if (xRem < 0) {
        break;
      }
      /* Iterate */
      do {
        int Dist;
        Dist = _GetDistToNextAlpha(pData, xRem);
        if (Dist) {
          /* Use fast LCD_DrawBitmap() for pixels without alpha value */
          LCD_DrawBitmap(x, y0, Dist, 1, 1, 1, 32, BytesPerLine, (const U8 GUI_UNI_PTR *)pData, 0);
          x     += Dist;
          pData += Dist;
          xRem  -= Dist;
        } else {
          /* Handle single pixels */
          U32 Color;
          U8  Alpha;
          Color = *pData++;
          Alpha = Color >> 24;
          if (Alpha < 255) {
            if (Color != PrevColor) {
              LCD_SetColor(Color);
              PrevColor = Color;
            }
            GUI__SetPixelAlpha(x, y0, 255 - Alpha, Color);
          }
          x    ++;
          xRem --;
        }
      } while (xRem);
      y0++;
    } while (--ysize);
  } else {
    if (Mag == 1) {
      if (_DoClipping(&x0, &y0, &xsize, &ysize, &pData, BytesPerLine)) {
        return;
      }
      /* Simple, non magnified output using LCD_L0_SetPixel() */
      for (y = 0; y < ysize; y++) {
        int x;
        const U32 * p = pData;
        for (x = 0; x < xsize; x++) {
          U32 Color;
          U8 Alpha;
          Color = *p++;
          Alpha = Color >> 24;
          if (Alpha < 255) {
            if (Color != PrevColor) {
              LCD_SetColor(pfIndex2Color(Color));
              PrevColor = Color;
            }
            if (Alpha) {
              GUI__SetPixelAlpha(x + x0, y + y0, 255 - Alpha, Color);
            } else {
              LCDDEV_L0_SetPixelIndex(x + x0, y + y0, LCD_COLORINDEX);
            }
          }
        }
        pData += BytesPerLine / 4;
      }
    } else {
      /* Magnified output using LCD_FillRect() */
      int x,y;
      int yi;
      for (y = y0, yi = 0; yi < ysize; yi++, y += yMag, pPixel += BytesPerLine) {
        int yMax;
        yMax = y + yMag - 1;
        /* Draw if within clip area */
        if ((yMax >= GUI_Context.ClipRect.y0) && (y <= GUI_Context.ClipRect.y1)) {
          int xi;
          const U32 GUI_UNI_PTR * p = pData;
          for (x = x0, xi = 0; xi < xsize; xi++, x += xMag) {
            U32 Color;
            U8 Alpha;
            Color = *p++;
            Alpha = Color >> 24;
            if (Color != PrevColor) {
              LCD_SetColor(Color);
              PrevColor = Color;
            }
            if (Alpha < 255) {
              if (Alpha) {
                _FillRectAlpha(x, y, x + xMag - 1, yMax, 255 - Alpha, Color);
              } else {
                LCD_FillRect(x, y, x + xMag - 1, yMax);
              }
            }
          }
        }
        pData += BytesPerLine / 4;
      }
    }
    GUI_SetColorIndex(OldIndex);
  }
}

/*********************************************************************
*
*       _DrawBitmapHW
*/
static void _DrawBitmapHW(int x0, int y0, int xsize, int ysize, const U8 GUI_UNI_PTR * pPixel) {
  const U32 * pData;
  int y, OldIndex, BytesPerLine;
  OldIndex = LCD_GetColorIndex();
  pData = (const U32 *)pPixel;
  BytesPerLine = xsize * 4;
  if (_DoClipping(&x0, &y0, &xsize, &ysize, &pData, BytesPerLine)) {
    return;
  }
  /* Simple, non magnified output using LCD_L0_SetPixel() */
  for (y = 0; y < ysize; y++) {
    int x;
    const U32 * p = pData;
    for (x = 0; x < xsize; x++) {
      U32 Index, Color;
      Color = *p++;
      Index = LCD_Color2Index(Color);
      LCDDEV_L0_SetPixelIndex(x + x0, y + y0, Index);
    }
    pData += BytesPerLine / 4;
  }
  GUI_SetColorIndex(OldIndex);
}

/*********************************************************************
*
*       _DrawBitmap_8888
*/
static void _DrawBitmap_8888(int x0, int y0, int xsize, int ysize, const U8 GUI_UNI_PTR * pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, int xMag, int yMag) {
  GUI_USE_PARA(pLogPal);
  _DrawBitmap(x0, y0, xsize, ysize, pPixel, /*pLogPal, */xMag, yMag, GUI_BitmapMethods8888.pfIndex2Color);
}

/*********************************************************************
*
*       _DrawBitmapHW_8888
*/
static void _DrawBitmapHW_8888(int x0, int y0, int xsize, int ysize, const U8 GUI_UNI_PTR * pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, int xMag, int yMag) {
  GUI_USE_PARA(pLogPal);
  GUI_USE_PARA(xMag);
  GUI_USE_PARA(yMag);
  _DrawBitmapHW(x0, y0, xsize, ysize, pPixel);
}

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_BitmapMethods8888
*/
const GUI_BITMAP_METHODS GUI_BitmapMethods8888 = {
  _DrawBitmap_8888,
  LCD_Index2Color_8888,
  _DrawBitmapHW_8888,
};

/*************************** End of file ****************************/