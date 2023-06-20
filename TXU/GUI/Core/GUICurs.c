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
File        : GUICurs.c
Purpose     : Cursor routines of the graphics library
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"

#ifndef GUI_CURSOR_SUPPORT_ALPHA
  #define GUI_CURSOR_SUPPORT_ALPHA 0
#endif

#if (GUI_SUPPORT_CURSOR) && (GUI_SUPPORT_SPRITE == 0)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  GUI_HMEM          hBuffer;
  GUI_RECT          Rect;
  char              CursorIsVis;        /* Currently visible ? */
  char              CursorOn;
  const GUI_CURSOR GUI_UNI_PTR * pCursor;
  int               AllocSize;
  int               x, y;              /* Position of hot spot */
  GUI_RECT          ClipRect;
  LCD_PIXELINDEX    ColorIndex[4];      /* Color-Cache */
} CURSOR_CONTEXT;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static CURSOR_CONTEXT _aContext[GUI_NUM_CURSORS];

/*********************************************************************
*
*       static code, helper functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetPixelIndex
*
* Purpose
*   Sets the pixel index for the Cursor.
*   Note the following:
*   - We do the clipping in this routine
*   - We do NOT call the driver directly, but thru its API table.
*     This allows others (e.g. the VNC server) to be in the loop-
*/
static void _SetPixelIndex(int x, int y, int Index, int Layer) {
  if ((y >= _aContext[Layer].ClipRect.y0) && (y <= _aContext[Layer].ClipRect.y1)) {
    if ((x >= _aContext[Layer].ClipRect.x0) && (x <= _aContext[Layer].ClipRect.x1)) {
      LCD_aAPI[Layer]->pfSetPixelIndex(x, y, Index);
    }
  }
}

/*********************************************************************
*
*       _GetPixelIndex
*
* Purpose
*   Gets a pixel index for the Cursor.
*/
static int _GetPixelIndex(int x, int y, int Layer) {
  if ((y >= _aContext[Layer].ClipRect.y0) && (y <= _aContext[Layer].ClipRect.y1)) {
    if ((x >= _aContext[Layer].ClipRect.x0) && (x <= _aContext[Layer].ClipRect.x1)) {
      return LCD_aAPI[Layer]->pfGetPixelIndex(x, y);
    }
  }
  return 0;
}

/*********************************************************************
*
*       _XorPixelIndex
*
* Purpose
*   Inverts a pixel
*/
static void _XorPixelIndex(int x, int y, int Layer) {
  if ((y >= _aContext[Layer].ClipRect.y0) && (y <= _aContext[Layer].ClipRect.y1)) {
    if ((x >= _aContext[Layer].ClipRect.x0) && (x <= _aContext[Layer].ClipRect.x1)) {
      LCD_aAPI[Layer]->pfXorPixel(x, y);
    }
  }
}

/*********************************************************************
*
*       _Undraw
*
* Purpose
*   Remove the cursors
*/
static void _Undraw(int Layer) {
  int x, y, xSize, ySize;
  LCD_PIXELINDEX* pData;
  /* Save bitmap data */
  GUI_LOCK();
  if (_aContext[Layer].hBuffer) {
    pData = (LCD_PIXELINDEX*)GUI_ALLOC_h2p(_aContext[Layer].hBuffer);
    xSize = _aContext[Layer].Rect.x1 - _aContext[Layer].Rect.x0 + 1;
    ySize = _aContext[Layer].Rect.y1 - _aContext[Layer].Rect.y0 + 1;
    for (y = 0; y < ySize; y++) {
      for (x = 0; x < xSize; x++) {
        _SetPixelIndex(x + _aContext[Layer].Rect.x0, y + _aContext[Layer].Rect.y0, *(pData + x), Layer);
      }
      pData += _aContext[Layer].pCursor->pBitmap->XSize;
    }
  }
  GUI_UNLOCK();
}

/*********************************************************************
*
*       _Log2Phys
*/
static int _Log2Phys(int Index, int Layer) {
  if (Index < 4) {
    return _aContext[Layer].ColorIndex[Index];
  } else {
    LCD_COLOR Color = *(_aContext[Layer].pCursor->pBitmap->pPal->pPalEntries + Index);
    return LCD_aAPI[Layer]->pfColor2Index(Color);
  }
}

/*********************************************************************
*
*       _Draw
*/
static void _Draw(int Layer) {
  int x, y, xSize, ySize;
  LCD_PIXELINDEX* pData;
  const GUI_BITMAP GUI_UNI_PTR * pBM;
  GUI_LOCK();
  if (_aContext[Layer].hBuffer) {
    /* Save bitmap data */
    pBM = _aContext[Layer].pCursor->pBitmap;
    pData = (LCD_PIXELINDEX*)GUI_ALLOC_h2p(_aContext[Layer].hBuffer);
    xSize = _aContext[Layer].Rect.x1 - _aContext[Layer].Rect.x0 + 1;
    ySize = _aContext[Layer].Rect.y1 - _aContext[Layer].Rect.y0 + 1;
    #if GUI_CURSOR_SUPPORT_ALPHA
    if (pBM->BitsPerPixel == 32) {
      for (y = 0; y < ySize; y++) {
        for (x = 0; x < xSize; x++) {
          int BitmapPixel;
          U8 Alpha;
          *(pData + x) = _GetPixelIndex(_aContext[Layer].Rect.x0 + x, _aContext[Layer].Rect.y0 + y, Layer);
          BitmapPixel = GUI_GetBitmapPixelIndex(pBM, x, y);
          Alpha = BitmapPixel >> 24;
          BitmapPixel &= 0xFFFFFF;
          if (Alpha == 0) {
            _SetPixelIndex(_aContext[Layer].Rect.x0 + x, _aContext[Layer].Rect.y0 + y, BitmapPixel, Layer);
          } else {
            if (Alpha < 255) {
              GUI__SetPixelAlpha(_aContext[Layer].Rect.x0 + x, _aContext[Layer].Rect.y0 + y, 255 - Alpha, BitmapPixel);
            }
          }
        }
        pData += pBM->XSize;
      }
    } else {
    #else
    {
    #endif
      for (y = 0; y < ySize; y++) {
        for (x = 0; x < xSize; x++) {
          int BitmapPixel;
          *(pData + x) = _GetPixelIndex(_aContext[Layer].Rect.x0 + x, _aContext[Layer].Rect.y0 + y, Layer);
          BitmapPixel = GUI_GetBitmapPixelIndex(pBM, x, y);
          if (BitmapPixel) {
            int Index;
            Index = _Log2Phys(BitmapPixel, Layer);
            _SetPixelIndex(_aContext[Layer].Rect.x0 + x, _aContext[Layer].Rect.y0 + y, Index, Layer);
          }
        }
        pData += pBM->XSize;
      }
    }
  }
  GUI_UNLOCK();
}

/*********************************************************************
*
*       _CalcRect
*/
static void _CalcRect(int Layer) {
  if (_aContext[Layer].pCursor) {
    _aContext[Layer].Rect.x0 = _aContext[Layer].x - _aContext[Layer].pCursor->xHot;
    _aContext[Layer].Rect.y0 = _aContext[Layer].y - _aContext[Layer].pCursor->yHot;
    _aContext[Layer].Rect.x1 = _aContext[Layer].Rect.x0 + _aContext[Layer].pCursor->pBitmap->XSize - 1;
    _aContext[Layer].Rect.y1 = _aContext[Layer].Rect.y0 + _aContext[Layer].pCursor->pBitmap->YSize - 1;
  }
}

/*********************************************************************
*
*       _Hide
*/
static void _Hide(int Layer) {
  unsigned CursorLayer;
  CursorLayer = GUI_GetCursorLayer(Layer);
  if (CursorLayer) {
    GUI_SetLayerVisEx(CursorLayer, 0);
    _aContext[Layer].CursorIsVis = 0;
  } else {
    if (_aContext[Layer].CursorIsVis) {
      _Undraw(Layer);
      _aContext[Layer].CursorIsVis = 0;
    }
  }
}

/*********************************************************************
*
*       _Show
*/
static void _Show(int Layer) {
  unsigned CursorLayer;
  CursorLayer = GUI_GetCursorLayer(Layer);
  if (CursorLayer) {
    GUI_SetLayerVisEx(CursorLayer, 1);
  } else {
    if (_aContext[Layer].CursorOn) {
      _aContext[Layer].CursorIsVis = 1;
      _Draw(Layer);
    }
  }
}

/*********************************************************************
*
*       _TempHide
*
* Purpose:
*   Hide cursor if a part of the given rectangle is located in the
*   rectangle used for the cursor. This routine is called automatically
*   by the window manager. This way the window manager can
*   automatically make sure that the cursor is always displayed
*   correctly.
*
* Params:
*   pRect   Rectangle under consideration
*
* Return value:
*   0:      No action taken
*           Cursor was not visible or not affected because rectangles
*           did not overlap
*   1:      Cursor hidden -> WM needs to restore cursor after
*           drawing operation
*/
static char _TempHide(const GUI_RECT* pRect, int Layer) {
  if (GUI_GetCursorLayer(Layer)) {
    return 0;
  }
  if (!_aContext[Layer].CursorIsVis) {
    return 0;             /* Cursor not visible -> nothing to do */
  }
  if ((pRect == NULL) || GUI_RectsIntersect(pRect, &_aContext[Layer].Rect)) {
    _Hide(Layer);              /* Cursor needs to be hidden */
    return 1;
  }
  return 0;               /* Cursor not affected -> nothing to do */
}

/*********************************************************************
*
*       _TempUnhide
*/
static void _TempUnhide(int Layer) {
  if (GUI_GetCursorLayer(Layer)) {
    return;
  }
  _Show(Layer);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_CURSOR_SetPixelIndexEx
*/
void GUI_CURSOR_SetPixelIndexEx(int x, int y, int Index, int Layer) {
  int BitmapPixel, xPos, yPos;
  const GUI_BITMAP GUI_UNI_PTR * pBM;
  LCD_PIXELINDEX * pData;
  if (_aContext[Layer].hBuffer) {
    BitmapPixel = 0;
    /* Store background data */
    xPos = x - _aContext[Layer].Rect.x0;
    yPos = y - _aContext[Layer].Rect.y0;
    pBM  = _aContext[Layer].pCursor->pBitmap;
    BitmapPixel = GUI_GetBitmapPixelIndex(pBM, xPos, yPos);
    pData = (LCD_PIXELINDEX*)GUI_ALLOC_h2p(_aContext[Layer].hBuffer);
    *(pData + pBM->XSize * yPos + xPos) = Index;
    /* Draw pixel if it is not part of the cursor */
    if (!BitmapPixel) {
      _SetPixelIndex(x, y, Index, Layer);
    }
  }
}

/*********************************************************************
*
*       GUI_CURSOR_XorPixelIndexEx
*/
void GUI_CURSOR_XorPixelIndexEx(int x, int y, int Layer) {
  int BitmapPixel, xPos, yPos;
  const GUI_BITMAP GUI_UNI_PTR * pBM;
  LCD_PIXELINDEX * pData;
  if (_aContext[Layer].hBuffer) {
    BitmapPixel = 0;
    /* Store background data */
    xPos = x - _aContext[Layer].Rect.x0;
    yPos = y - _aContext[Layer].Rect.y0;
    pBM  = _aContext[Layer].pCursor->pBitmap;
    BitmapPixel = GUI_GetBitmapPixelIndex(pBM, xPos, yPos);
    pData = (LCD_PIXELINDEX*)GUI_ALLOC_h2p(_aContext[Layer].hBuffer);
    *(pData + pBM->XSize * yPos + xPos) ^= LCD_aAPI[Layer]->pfGetIndexMask();
    /* Invert pixel if it is not part of the cursor */
    if (!BitmapPixel) {
      _XorPixelIndex(x, y, Layer);/**/
    }
  }
}

/*********************************************************************
*
*       GUI_CURSOR_SelectEx
*/
const GUI_CURSOR GUI_UNI_PTR * GUI_CURSOR_SelectEx(const GUI_CURSOR GUI_UNI_PTR * pCursor, int Layer) {
  int AllocSize;
  unsigned CursorLayer;
  const GUI_BITMAP GUI_UNI_PTR * pBM;
  const GUI_CURSOR GUI_UNI_PTR * pOldCursor;
  GUI_LOCK();
  GUI_DEBUG_ASSERT((Layer < GUI_NUM_CURSORS));
  CursorLayer = GUI_GetCursorLayer(Layer);
  pOldCursor = _aContext[Layer].pCursor;
  if (CursorLayer) {
    unsigned OldLayer;
    OldLayer = GUI_SelectLayer(CursorLayer);
    GUI_SetBkColor(GUI_TRANSPARENT);
    GUI_Clear();
    GUI_DrawBitmap(pCursor->pBitmap, 0, 0);
    GUI_SetLayerSizeEx(CursorLayer, pCursor->pBitmap->XSize, pCursor->pBitmap->YSize);
    _aContext[Layer].pCursor  = pCursor;
    _aContext[Layer].CursorOn = 1;
    GUI_SelectLayer(OldLayer);
    _Show(Layer);
  } else {
    if (pCursor != _aContext[Layer].pCursor) {
      int i;
      pBM = pCursor->pBitmap;
      if (pBM->pPal) {
        i = pBM->pPal->NumEntries > 4 ? 4 : pBM->pPal->NumEntries;
        while (i--) {
          LCD_COLOR Color = *(pBM->pPal->pPalEntries + i);
          _aContext[Layer].ColorIndex[i] = LCD_aAPI[Layer]->pfColor2Index(Color);
        }
      }
      _Hide(Layer);
      AllocSize = pBM->XSize * pBM->YSize * sizeof(LCD_PIXELINDEX);
      if (AllocSize != _aContext[Layer].AllocSize) {
        GUI_ALLOC_Free(_aContext[Layer].hBuffer);
        _aContext[Layer].hBuffer = 0;
      }
      _aContext[Layer].hBuffer = GUI_ALLOC_AllocZero(AllocSize);
      _aContext[Layer].CursorOn = 1;
      LCDDEV_L0_GetRect(&_aContext[Layer].ClipRect);
      _aContext[Layer].pCursor = pCursor;
      _CalcRect(Layer);
      _Show(Layer);
    }
  }
  GUI_UNLOCK();
  return pOldCursor;
}

/*********************************************************************
*
*       GUI_CURSOR_HideEx
*/
void GUI_CURSOR_HideEx(int Layer) {
  GUI_LOCK();
  GUI_DEBUG_ASSERT((Layer < GUI_NUM_CURSORS));
  _aContext[Layer].CursorOn = 0;
  _Hide(Layer);
  /* Set function pointer which window manager can use */
  GUI_CURSOR__apfTempHide[Layer]   = NULL;
  GUI_CURSOR__apfTempUnhide[Layer] = NULL;
  GUI_UNLOCK();
  LCD_EnableCursor(0);/**/
}

/*********************************************************************
*
*       GUI_CURSOR_ShowEx
*/
void GUI_CURSOR_ShowEx(int Layer) {
  GUI_LOCK();
  GUI_DEBUG_ASSERT((Layer < GUI_NUM_CURSORS));
  _aContext[Layer].CursorOn = 1;
  LCDDEV_L0_GetRect(&_aContext[Layer].ClipRect);
  _Hide(Layer);
  /* Set function pointer which window manager can use */
  GUI_CURSOR__apfTempHide[Layer]   = _TempHide;
  GUI_CURSOR__apfTempUnhide[Layer] = _TempUnhide;
  if (!_aContext[Layer].pCursor) {
    GUI_CURSOR_SelectEx(GUI_DEFAULT_CURSOR, Layer);
  } else {
    _Show(Layer);
  }
  LCD_EnableCursor(1);/**/
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_CURSOR_GetStateEx
*/
int GUI_CURSOR_GetStateEx(int Layer) {
  int r;
  GUI_LOCK();
  GUI_DEBUG_ASSERT((Layer < GUI_NUM_CURSORS));
  r = _aContext[Layer].CursorOn;
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_CURSOR_SetPositionEx
*/
void GUI_CURSOR_SetPositionEx(int xNewPos, int yNewPos, int Layer) {
  unsigned CursorLayer;
  int x, xStart, xStep, xEnd, xOff, xOverlapMin, xOverlapMax;
  int y, yStart, yStep, yEnd, yOff, yOverlapMin, yOverlapMax;
  int xSize;
  LCD_PIXELINDEX* pData;
  GUI_LOCK();
  GUI_DEBUG_ASSERT((Layer < GUI_NUM_CURSORS));
  CursorLayer = GUI_GetCursorLayer(Layer);
  if (CursorLayer) {
    xNewPos -= _aContext[Layer].pCursor->xHot;
    yNewPos -= _aContext[Layer].pCursor->yHot;
    GUI_SetLayerPosEx(CursorLayer, xNewPos, yNewPos);
  } else {
    if (_aContext[Layer].hBuffer) {
      if ((_aContext[Layer].x != xNewPos) | (_aContext[Layer].y != yNewPos)) {
        if (_aContext[Layer].CursorOn) {
          const GUI_BITMAP GUI_UNI_PTR * pBM = _aContext[Layer].pCursor->pBitmap;
          /* Save & set clip rect */
          /* Compute helper variables */
          pData = (LCD_PIXELINDEX*)GUI_ALLOC_h2p(_aContext[Layer].hBuffer);
          xSize = _aContext[Layer].pCursor->pBitmap->XSize;
          xOff = xNewPos - _aContext[Layer].x;
          if (xOff > 0) {
            xStep  = 1;
            xStart = 0;
            xEnd   = _aContext[Layer].pCursor->pBitmap->XSize;
            xOverlapMax = xEnd -1;
            xOverlapMin = xOff;
          } else {
            xStep  = -1;
            xStart = xSize - 1;
            xEnd   = -1;
            xOverlapMin = 0;
            xOverlapMax = xStart + xOff;
          }
          yOff = yNewPos - _aContext[Layer].y;
          if (yOff > 0) {
            yStep  = 1;
            yStart = 0;
            yEnd   = _aContext[Layer].pCursor->pBitmap->YSize;
            yOverlapMax = yEnd -1;
            yOverlapMin = yOff;
          } else {
            yStep  = -1;
            yStart = _aContext[Layer].pCursor->pBitmap->YSize - 1;
            yEnd   = -1;
            yOverlapMin = 0;
            yOverlapMax = yStart + yOff;
          }
          /* Restore & Draw */
          #if GUI_CURSOR_SUPPORT_ALPHA
          if (pBM->BitsPerPixel == 32) {
            for (y = yStart; y != yEnd; y += yStep) {
              char yOverlaps;
              char yNewOverlaps;
              int yNew = y + yOff;
              yOverlaps    = (y >= yOverlapMin) && (y <= yOverlapMax);
              yNewOverlaps = (yNew >= yOverlapMin) && (yNew <= yOverlapMax);
              for (x= xStart; x != xEnd; x += xStep) {
                U8 Alpha;
                char xyOverlaps, xyNewOverlaps;
                U32 BitmapPixel;
                LCD_PIXELINDEX Pixel;
                LCD_PIXELINDEX* pSave = pData + x + y * xSize;
                int xNew = x + xOff;
                BitmapPixel = GUI_GetBitmapPixelIndex(pBM, x, y);
                Alpha = BitmapPixel >> 24;
                BitmapPixel &= 0xFFFFFF;
                xyOverlaps    = (x    >= xOverlapMin) && (x    <= xOverlapMax) && yOverlaps;
                xyNewOverlaps = (xNew >= xOverlapMin) && (xNew <= xOverlapMax) && yNewOverlaps;
                /* Restore old pixel if it was not transparent */
                if (Alpha < 255) {
                  U8 OldAlpha;
                  OldAlpha = GUI_GetBitmapPixelIndex(pBM, x - xOff, y - yOff) >> 24;
                  if (!xyOverlaps || (OldAlpha == 255)) {
                    _SetPixelIndex(x + _aContext[Layer].Rect.x0, y + _aContext[Layer].Rect.y0, *(pSave), Layer);
                  }
                }
                /* Save */
                if (xyNewOverlaps) {
                  Pixel = *(pData + xNew + yNew * xSize);
                } else {
                  Pixel = _GetPixelIndex(_aContext[Layer].Rect.x0 + xNew, _aContext[Layer].Rect.y0 + yNew, Layer);
                }
                *pSave = Pixel;
                /* Write new  ... We could write pixel by pixel here */
                if (Alpha < 255) {
                  if (Alpha == 0) {
                    _SetPixelIndex(_aContext[Layer].Rect.x0 + xNew, _aContext[Layer].Rect.y0 + yNew, BitmapPixel, Layer);
                  } else {
                    LCD_COLOR Color;
                    LCD_PIXELINDEX Index;
                    Color = GUI__MixColors(BitmapPixel, Pixel, 255 - Alpha);
                    Index = LCD_Color2Index(Color);
                    _SetPixelIndex(_aContext[Layer].Rect.x0 + xNew, _aContext[Layer].Rect.y0 + yNew, Index, Layer);
                  }
                }
              }
            }
          } else {
          #else
          {
          #endif
            for (y = yStart; y != yEnd; y += yStep) {
              char yOverlaps;
              char yNewOverlaps;
              int yNew = y + yOff;
              yOverlaps    = (y >= yOverlapMin) && (y <= yOverlapMax);
              yNewOverlaps = (yNew >= yOverlapMin) && (yNew <= yOverlapMax);
              for (x= xStart; x != xEnd; x += xStep) {
                char xyOverlaps, xyNewOverlaps;
                int BitmapPixel;
                LCD_PIXELINDEX Pixel;
                LCD_PIXELINDEX* pSave = pData + x + y * xSize;
                int xNew = x + xOff;
                BitmapPixel = GUI_GetBitmapPixelIndex(pBM, x, y);
                xyOverlaps    = (x    >= xOverlapMin) && (x    <= xOverlapMax) && yOverlaps;
                xyNewOverlaps = (xNew >= xOverlapMin) && (xNew <= xOverlapMax) && yNewOverlaps;
                /* Restore old pixel if it was not transparent */
                if (BitmapPixel) {
                  if (!xyOverlaps || (GUI_GetBitmapPixelIndex(pBM, x - xOff, y - yOff) == 0)) {
                    _SetPixelIndex(x + _aContext[Layer].Rect.x0, y + _aContext[Layer].Rect.y0, *(pSave), Layer);
                  }
                }
                /* Save */
                if (xyNewOverlaps) {
                  Pixel = *(pData + xNew + yNew * xSize);
                } else {
                  Pixel = _GetPixelIndex(_aContext[Layer].Rect.x0 + xNew, _aContext[Layer].Rect.y0 + yNew, Layer);
                }
                *pSave = Pixel;
                /* Write new  ... We could write pixel by pixel here */
                if (BitmapPixel) {
                  LCD_PIXELINDEX NewPixel = _Log2Phys(BitmapPixel, Layer);
                  _SetPixelIndex(_aContext[Layer].Rect.x0 + xNew, _aContext[Layer].Rect.y0 + yNew, NewPixel, Layer);
                }
              }
            }
          }
        }
        _aContext[Layer].x = xNewPos;
        _aContext[Layer].y = yNewPos;
        _CalcRect(Layer);
      }
    }
  }
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_CURSOR_GetCursorRectEx
*/
void GUI_CURSOR_GetCursorRectEx(GUI_RECT * pRect, int Layer) {
  pRect->x0 = _aContext[Layer].x - _aContext[Layer].pCursor->xHot;
  pRect->y0 = _aContext[Layer].y - _aContext[Layer].pCursor->yHot;
  pRect->x1 = pRect->x0 + _aContext[Layer].pCursor->pBitmap->XSize - 1;
  pRect->y1 = pRect->y0 + _aContext[Layer].pCursor->pBitmap->YSize - 1;
}

/*********************************************************************
*
*       GUI_CURSOR_Select
*/
const GUI_CURSOR GUI_UNI_PTR * GUI_CURSOR_Select(const GUI_CURSOR GUI_UNI_PTR * pCursor) {
  return GUI_CURSOR_SelectEx(pCursor, GUI_CURSOR_LAYER);
}

/*********************************************************************
*
*       GUI_CURSOR_Hide
*/
void GUI_CURSOR_Hide(void) {
  GUI_CURSOR_HideEx(GUI_CURSOR_LAYER);
}

/*********************************************************************
*
*       GUI_CURSOR_Show
*/
void GUI_CURSOR_Show(void) {
  GUI_CURSOR_ShowEx(GUI_CURSOR_LAYER);
}

/*********************************************************************
*
*       GUI_CURSOR_GetState
*/
int GUI_CURSOR_GetState(void) {
  return GUI_CURSOR_GetStateEx(GUI_CURSOR_LAYER);
}

/*********************************************************************
*
*       GUI_CURSOR_SetPosition
*/
void GUI_CURSOR_SetPosition(int xNewPos, int yNewPos) {
  GUI_CURSOR_SetPositionEx(xNewPos, yNewPos, GUI_CURSOR_LAYER);
}

/*********************************************************************
*
*       GUI_CURSOR_GetCursorRect
*/
void GUI_CURSOR_GetCursorRect(GUI_RECT * pRect) {
  GUI_CURSOR_GetCursorRectEx(pRect, GUI_CURSOR_LAYER);
}

#else

void GUICurs_C(void);
void GUICurs_C(void) {} /* avoid empty object files */

#endif   /* (GUI_SUPPORT_CURSOR) && (GUI_SUPPORT_SPRITE == 0) */

/*************************** End of file ****************************/
