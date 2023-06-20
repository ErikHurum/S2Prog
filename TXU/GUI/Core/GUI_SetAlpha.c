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
File        : GUI_SetAlpha.c
Purpose     : Implementation of GUI_SetAlpha
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include <string.h>

#include "GUI_Private.h"

#if GUI_SUPPORT_DEVICES

#define GUI_SET_ALPHA_OPTIMIZE 1
#define GUI_ALPHA_USE_STACK    0

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const tLCDDEV_APIList * _pAPIListOld;
static U8 _Alpha;

#if (GUI_SET_ALPHA_OPTIMIZE == 1) && (GUI_ALPHA_USE_STACK == 0)
  static LCD_PIXELINDEX _aIndex[LCD_XSIZE];
  static LCD_COLOR      _aColor[LCD_XSIZE];
#endif

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _MixColors
*/
static LCD_COLOR _MixColors(LCD_COLOR Color, LCD_COLOR BkColor) {
  U32 r, g, b, a;
  U8 Intens;
  Intens = 255 - _Alpha;
  /* Calc Color seperations for FgColor first */
  r = (Color & 0x000000ff) * Intens;
  g = (Color & 0x0000ff00) * Intens;
  b = (Color & 0x00ff0000) * Intens;
  a = ((Color & 0xff000000) >> 24) * Intens;
  /* Add Color seperations for BkColor */
  Intens = 255 - Intens;
  r += (BkColor & 0x000000ff) * Intens;
  g += (BkColor & 0x0000ff00) * Intens;
  b += (BkColor & 0x00ff0000) * Intens;
  a += ((BkColor & 0xff000000) >> 24) * Intens;
  r = (r >>  8) & 0x000000ff;
  g = (g >>  8) & 0x0000ff00;
  b = (b >>  8) & 0x00ff0000;
  a = (a << 16) & 0xff000000;
  Color = r + g + b + a;
  return Color;
}

/*********************************************************************
*
*       _ReadRect
*
* Purpose:
*   Reads the data from a memory device
*/
#if (GUI_SET_ALPHA_OPTIMIZE) && (GUI_SUPPORT_MEMDEV)
static void _ReadRect(int x0, int y0, int x1, int y1, LCD_PIXELINDEX * pBuffer) {
  LCD_PIXELINDEX * p;
  int x0m, y0m, xSize;
  GUI_USE_PARA(y1);
  x0m = GUI_MEMDEV_GetXPos(GUI_Context.hDevData);
  y0m = GUI_MEMDEV_GetYPos(GUI_Context.hDevData);
  xSize = GUI_MEMDEV_GetXSize(GUI_Context.hDevData);
  p = (LCD_PIXELINDEX *)GUI_MEMDEV_GetDataPtr(GUI_Context.hDevData);
  if (y0 < y0m) {
    return;
  }
  if (x0 < x0m) {
    return;
  }
  p += ((y0 - y0m) * xSize) + (x0 - x0m);
  GUI_MEMCPY(pBuffer, p, (x1 - x0 + 1) * sizeof(LCD_PIXELINDEX));
}
#endif

/*********************************************************************
*
*       _GetPointers
*/
#if (GUI_SET_ALPHA_OPTIMIZE)
static void _GetPointers(tLCDDEV_Index2Color ** ppfIndex2Color, tLCDDEV_Color2Index ** ppfColor2Index) {
  *ppfIndex2Color = GUI_GetpfIndex2ColorEx(GUI_Context.SelLayer);
  *ppfColor2Index = GUI_GetpfColor2IndexEx(GUI_Context.SelLayer);
}

/*********************************************************************
*
*       _GetLine
*/
static void _GetLine(int x, int y, int NumPixels, LCD_PIXELINDEX * pBuffer, LCD_COLOR * pColor, tLCDDEV_Index2Color * pfIndex2Color) {
  int i, x1;
  void (* pReadRect)(int x0, int y0, int x1, int y1, LCD_PIXELINDEX * pBuffer);
  if (GUI_Context.pDeviceAPI->pfGetDevFunc) {
    pReadRect = (void (*)(int x0, int y0, int x1, int y1, LCD_PIXELINDEX * pBuffer))GUI_Context.pDeviceAPI->pfGetDevFunc(LCD_DEVFUNC_READRECT);
  } else {
    #if GUI_SUPPORT_MEMDEV
    if (GUI_Context.hDevData) {
      pReadRect = _ReadRect;
    } else {
    #else
    {
    #endif
      pReadRect = NULL;
    }
  }
  x1 = x + NumPixels - 1;
  if (pReadRect) {
    pReadRect(x, y, x1, y, pBuffer);
  } else {
    LCD_PIXELINDEX * p;
    p = pBuffer;
    for (i = x; i <= x1; i++) {
      *(p++) = _pAPIListOld->pfGetPixelIndex(i, y);
    }
  }
  for (i = 0; i < NumPixels; i++) {
    *(pColor + i) = pfIndex2Color(*(pBuffer + i));
  }
}
#endif

/*********************************************************************
*
*       _SetPixelIndex
*
* Purpose:
*   Sets the index of the given pixel. The upper layers
*   calling this routine make sure that the coordinates are in range, so
*   that no check on the parameters needs to be performed.
*/
static void _SetPixelIndex(int x, int y, int PixelIndex) {
  LCD_PIXELINDEX IndexOld, IndexNew;
  LCD_COLOR      ColorOld, ColorNew, Color;
  /* Write into hardware */
  IndexOld = _pAPIListOld->pfGetPixelIndex(x, y);
  ColorOld = _pAPIListOld->pfIndex2Color(IndexOld);
  Color    = _pAPIListOld->pfIndex2Color(PixelIndex);
  ColorNew = _MixColors(Color, ColorOld);
  IndexNew = _pAPIListOld->pfColor2Index(ColorNew);
  _pAPIListOld->pfSetPixelIndex(x, y, IndexNew);
}

/*********************************************************************
*
*       _GetPixelIndex
*
* Purpose:
*   Returns the index of the given pixel. The upper layers
*   calling this routine make sure that the coordinates are in range, so
*   that no check on the parameters needs to be performed.
*/
static unsigned int _GetPixelIndex(int x, int y) {
  LCD_PIXELINDEX PixelIndex;
  /* Read from hardware */
  PixelIndex = _pAPIListOld->pfGetPixelIndex(x, y);
  return PixelIndex;
}

/*********************************************************************
*
*       _XorPixel
*/
static void _XorPixel(int x, int y) {
  LCD_PIXELINDEX PixelIndex = _GetPixelIndex(x, y);
  _SetPixelIndex(x, y, LCD_NUM_COLORS - PixelIndex - 1);
}

/*********************************************************************
*
*       Draw Bitmap 1 BPP, optimized
*/
#if (GUI_SET_ALPHA_OPTIMIZE)
static void  _DrawBitLine1BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  #if (GUI_ALPHA_USE_STACK)
    LCD_PIXELINDEX _aIndex[LCD_XSIZE];
    LCD_COLOR      _aColor[LCD_XSIZE];
  #endif
  LCD_PIXELINDEX Index0 = *(pTrans + 0);
  LCD_PIXELINDEX Index1 = *(pTrans + 1);
  LCD_COLOR      Color0;
  LCD_COLOR      Color1;
  int i, NumPixels;
  tLCDDEV_Index2Color * pfIndex2Color;
  tLCDDEV_Color2Index * pfColor2Index;
  LCD_COLOR Color, ColorNew;

  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    NumPixels = xsize;
    _GetPointers(&pfIndex2Color, &pfColor2Index);
    _GetLine(x, y, xsize, _aIndex, _aColor, pfIndex2Color);
    Color0 = pfIndex2Color(Index0);
    Color1 = pfIndex2Color(Index1);
    i = 0;
    do {
      Color      = (*p & (0x80 >> Diff)) ? Color1 : Color0;
      ColorNew   = _MixColors(Color, _aColor[i]);
      _aIndex[i] = pfColor2Index(ColorNew);
			if (++Diff == 8) {
        Diff = 0;
				p++;
			}
      i++;
		} while (--xsize);
    _pAPIListOld->pfDrawBitmap(x, y, NumPixels, 1, LCD_GetBitsPerPixelEx(GUI_Context.SelLayer), 0, (U8 *)_aIndex, 0, 0);
    break;
  case LCD_DRAWMODE_TRANS:
    NumPixels = xsize;
    _GetPointers(&pfIndex2Color, &pfColor2Index);
    _GetLine(x, y, xsize, _aIndex, _aColor, pfIndex2Color);
    Color1 = pfIndex2Color(Index1);
    i = 0;
    do {
  		if (*p & (0x80 >> Diff)) {
        ColorNew   = _MixColors(Color1, _aColor[i]);
        _aIndex[i] = pfColor2Index(ColorNew);
      }
      i++;
			if (++Diff == 8) {
        Diff = 0;
				p++;
			}
		} while (--xsize);
    _pAPIListOld->pfDrawBitmap(x, y, NumPixels, 1, LCD_GetBitsPerPixelEx(GUI_Context.SelLayer), 0, (U8 *)_aIndex, 0, 0);
    break;
  case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
  case LCD_DRAWMODE_XOR:
    do {
  		if (*p & (0x80 >> Diff)) {
        int Pixel = _GetPixelIndex(x, y);
        _SetPixelIndex(x, y, LCD_NUM_COLORS - 1 - Pixel);
      }
      x++;
			if (++Diff == 8) {
        Diff = 0;
				p++;
			}
		} while (--xsize);
    return;
	}
}

/*********************************************************************
*
*       Draw Bitmap 1 BPP, not optimized
*/
#else
static void  _DrawBitLine1BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Index0 = *(pTrans + 0);
  LCD_PIXELINDEX Index1 = *(pTrans + 1);
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      do {
        _SetPixelIndex(x++, y, (*p & (0x80 >> Diff)) ? Index1 : Index0);
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
    case LCD_DRAWMODE_TRANS:
      do {
  		  if (*p & (0x80 >> Diff)) {
          _SetPixelIndex(x, y, Index1);
        }
        x++;
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
    case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
    case LCD_DRAWMODE_XOR:
      do {
  		  if (*p & (0x80 >> Diff)) {
          int Pixel = _GetPixelIndex(x, y);
          _SetPixelIndex(x, y, LCD_NUM_COLORS - 1 - Pixel);
        }
        x++;
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
	}
}
#endif

/*********************************************************************
*
*       Draw Bitmap 2 BPP
*/
static void  _DrawBitLine2BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          _SetPixelIndex(x++, y, PixelIndex);
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          _SetPixelIndex(x++, y, Index);
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          if (Index) {
            LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
            _SetPixelIndex(x, y, PixelIndex);
          }
          x++;
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          if (Index) {
            _SetPixelIndex(x, y, Index);
          }
          x++;
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
  }
}

/*********************************************************************
*
*       Draw Bitmap 4 BPP
*/
static void  _DrawBitLine4BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          _SetPixelIndex(x++, y, PixelIndex);
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          _SetPixelIndex(x++, y, Index);
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          if (Index) {
            LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
            _SetPixelIndex(x, y, PixelIndex);
          }
          x++;
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          if (Index) {
            _SetPixelIndex(x, y, Index);
          }
          x++;
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
  }
}

/*********************************************************************
*
*       Draw Bitmap 8 BPP
*/
static void  _DrawBitLine8BPP(int x, int y, U8 const GUI_UNI_PTR * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixel;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          _SetPixelIndex(x, y, *(pTrans + Pixel));
        }
      } else {
        for (; xsize > 0; xsize--, x++, p++) {
          _SetPixelIndex(x, y, *p);
        }
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          if (Pixel) {
            _SetPixelIndex(x, y, *(pTrans + Pixel));
          }
        }
      } else {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          if (Pixel) {
            _SetPixelIndex(x, y, Pixel);
          }
        }
      }
      break;
  }
}

/*********************************************************************
*
*       Draw Bitmap 16 BPP
*/
static void  _DrawBitLine16BPP(int x, int y, U16 const GUI_UNI_PTR * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) == 0) {
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        _SetPixelIndex(x, y, *(pTrans + pixel));
      }
    } else {
      for (;xsize > 0; xsize--, x++, p++) {
        _SetPixelIndex(x, y, *p);
      }
    }
  } else {
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          _SetPixelIndex(x, y, *(pTrans + pixel));
        }
      }
    } else {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          _SetPixelIndex(x, y, pixel);
        }
      }
    }
  }
}

/*********************************************************************
*
*       _DrawHLine, optimized
*/
#if (GUI_SET_ALPHA_OPTIMIZE)
static void _DrawHLine  (int x0, int y,  int x1) {
  #if (GUI_ALPHA_USE_STACK)
    LCD_PIXELINDEX _aIndex[LCD_XSIZE];
    LCD_COLOR      _aColor[LCD_XSIZE];
  #endif
  
  int i, NumPixels;
  tLCDDEV_Index2Color * pfIndex2Color;
  tLCDDEV_Color2Index * pfColor2Index;
  LCD_COLOR Color, ColorNew;
  /*
   * Get function pointers and read pixels of current device
   */
  NumPixels = x1 - x0 + 1;
  _GetPointers(&pfIndex2Color, &pfColor2Index);
  _GetLine(x0, y, NumPixels, _aIndex, _aColor, pfIndex2Color);
  /*
   * Mix up buffer with current foreground color
   */
  Color = LCD_Index2Color(LCD_COLORINDEX);
  for (i = 0; i < NumPixels; i++) {
    ColorNew   = _MixColors(Color, _aColor[i]);
    _aIndex[i] = pfColor2Index(ColorNew);
  }
  /*
   * Write data to current device
   */
  _pAPIListOld->pfDrawBitmap(x0, y, NumPixels, 1, LCD_GetBitsPerPixelEx(GUI_Context.SelLayer), 0, (U8 *)_aIndex, 0, 0);
}

/*********************************************************************
*
*       _DrawHLine, not optimized
*/
#else
static void _DrawHLine  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; x0 <= x1; x0++) {
      _XorPixel(x0, y);
    }
  } else {
    for (; x0 <= x1; x0++) {
      _SetPixelIndex(x0, y, LCD_COLORINDEX);
    }
  }
}
#endif

/*********************************************************************
*
*       _DrawVLine
*/
static void _DrawVLine  (int x, int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; y0 <= y1; y0++) {
      _XorPixel(x, y0);
    }
  } else {
    for (; y0 <= y1; y0++) {
      _SetPixelIndex(x, y0, LCD_COLORINDEX);
    }
  }
}

/*********************************************************************
*
*       _FillRect
*/
static void _FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    _DrawHLine(x0, y0, x1);
  }
}

/*********************************************************************
*
*       _DrawBitmap
*/
static void _DrawBitmap(int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8 GUI_UNI_PTR * pData, int Diff,
                       const LCD_PIXELINDEX* pTrans)
{
  int i;
  /* Use _DrawBitLineXBPP */
  for (i = 0; i < ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      _DrawBitLine1BPP(x0, i + y0, pData, Diff, xsize, pTrans);
      break;
    case 2:
      _DrawBitLine2BPP(x0, i + y0, pData, Diff, xsize, pTrans);
      break;
    case 4:
      _DrawBitLine4BPP(x0, i + y0, pData, Diff, xsize, pTrans);
      break;
    case 8:
      _DrawBitLine8BPP(x0, i + y0, pData, xsize, pTrans);
      break;
    case 16:
      _DrawBitLine16BPP(x0, i + y0, (const U16 *)pData, xsize, pTrans);
      break;
    }
    pData += BytesPerLine;
  }
}

/*********************************************************************
*
*       _Color2Index
*/
static unsigned _Color2Index(GUI_COLOR Color) {
  return _pAPIListOld->pfColor2Index(Color);
}

/*********************************************************************
*
*       _Index2Color
*/
static LCD_COLOR _Index2Color(int Index) {
  return _pAPIListOld->pfIndex2Color(Index);
}

/*********************************************************************
*
*       _GetIndexMask
*/
static unsigned _GetIndexMask(void) {
  return _pAPIListOld->pfGetIndexMask();
}

/*********************************************************************
*
*       _GetRect
*/
static void _GetRect(LCD_RECT * pRect) {
  _pAPIListOld->pfGetRect(pRect);
}

/*********************************************************************
*
*       _APIList
*/
static const tLCDDEV_APIList _APIList = {
  _Color2Index,
  _Index2Color,
  _GetIndexMask,
  (tLCDDEV_DrawBitmap*)_DrawBitmap,
  _DrawHLine,
  _DrawVLine,
  _FillRect,
  _GetPixelIndex,
  _GetRect,
  _SetPixelIndex,
  _XorPixel,
};

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_SetAlpha
*/
unsigned GUI_SetAlpha(U8 Alpha) {
  unsigned OldAlpha;
  OldAlpha = _Alpha;
  if (Alpha == 0) {
    if (_pAPIListOld) {
      GUI_Context.pDeviceAPI = _pAPIListOld;
      _pAPIListOld = NULL;
    }
  } else {
    if (_pAPIListOld == NULL) {
      _pAPIListOld = GUI_Context.pDeviceAPI;
      GUI_Context.pDeviceAPI = &_APIList;
    }
    _Alpha = Alpha;
  }
  return OldAlpha;
}

#else

void GUI_SetAlpha_C(void);
void GUI_SetAlpha_C(void) {}

#endif

/*************************** End of file ****************************/
