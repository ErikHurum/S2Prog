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
File        : LCD_Curs.c
Purpose     : Manages hardware drawing operations when cursor is visible

A rectangle is divided in up to 5 rectangles as follows:

Rect0:  Rectangular area on top of the cursor
Rect1:  Rectangular area on the left of the cursor
Rect2:  Rectangular area on the right of the cursor
Rect3:  Rectangular area on bottom of the cursor
RectC:  Rectangular cursor area

              0000000000000000000000000
              0000000000000000000000000
              0000000000000000000000000
              0000000000000000000000000
              11111CCCCCCCCCCC222222222
              11111CCCCCCCCCCC222222222
              11111CCCCCCCCCCC222222222
              11111CCCCCCCCCCC222222222
              11111CCCCCCCCCCC222222222
              11111CCCCCCCCCCC222222222
              3333333333333333333333333
              3333333333333333333333333
              3333333333333333333333333
              3333333333333333333333333

---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#include "GUI_Private.h"

#if (GUI_SUPPORT_CURSOR) && (GUI_SUPPORT_SPRITE == 0)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  GUI_RECT rTotal;
  GUI_RECT rDraw;
  GUI_RECT rCursor;
} RECT_INFO;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _Init
*/
static int _Init(RECT_INFO * pRI, int x0, int y0, int x1, int y1) {
  pRI->rTotal.x0 = x0;
  pRI->rTotal.y0 = y0;
  pRI->rTotal.x1 = x1;
  pRI->rTotal.y1 = y1;
  GUI_CURSOR_GetCursorRectEx(&pRI->rCursor, GUI_Context.SelLayer);
  if (GUI_RectsIntersect(&pRI->rTotal, &pRI->rCursor) == 0) {
    return 0;                   /* No intersection, cursor does not overlap drawing area */
  }
  GUI__IntersectRect(&pRI->rCursor, &pRI->rTotal);
  return 1;                    /* Cursor overlaps drawing area */
}

/*********************************************************************
*
*       _CalcRect0
*
* Purpose:
*   Calculates the rectangle on the top of the cursor
*
* Return value:
*   0 if there is no rectangle
*   1 if there is a rectangle
*/
static int _CalcRect0(RECT_INFO * pRI) {
  if (pRI->rTotal.y0 >= pRI->rCursor.y0) {
    return 0;        /* Nothing to do */
  }
  pRI->rDraw.x0 = pRI->rTotal.x0;
  pRI->rDraw.x1 = pRI->rTotal.x1;
  pRI->rDraw.y0 = pRI->rTotal.y0;
  pRI->rDraw.y1 = pRI->rCursor.y0 - 1;
  return 1;        /* Rectangle needs to be drawn */
}

/*********************************************************************
*
*       _CalcRect1
*
* Purpose:
*   Calculates the rectangle on the left of the cursor
*
* Return value:
*   0 if there is no rectangle
*   1 if there is a rectangle
*/
static int _CalcRect1(RECT_INFO * pRI) {
  if (pRI->rTotal.x0 >= pRI->rCursor.x0) {
    return 0;        /* Nothing to do */
  }
  pRI->rDraw.y0 = (pRI->rTotal.y0 < pRI->rCursor.y0) ? pRI->rCursor.y0 : pRI->rTotal.y0;
  pRI->rDraw.y1 = (pRI->rTotal.y1 > pRI->rCursor.y1) ? pRI->rCursor.y1 : pRI->rTotal.y1;
  pRI->rDraw.x0 = pRI->rTotal.x0;
  pRI->rDraw.x1 = pRI->rCursor.x0 - 1;
  return 1;        /* Rectangle needs to be drawn */
}

/*********************************************************************
*
*       _CalcRect2
*
* Purpose:
*   Calculates the rectangle on the right of the cursor
*
* Return value:
*   0 if there is no rectangle
*   1 if there is a rectangle
*/
static int _CalcRect2(RECT_INFO * pRI) {
  if (pRI->rTotal.x1 <= pRI->rCursor.x1) {
    return 0;        /* Nothing to do */
  }
  pRI->rDraw.y0 = (pRI->rTotal.y0 < pRI->rCursor.y0) ? pRI->rCursor.y0 : pRI->rTotal.y0;
  pRI->rDraw.y1 = (pRI->rTotal.y1 > pRI->rCursor.y1) ? pRI->rCursor.y1 : pRI->rTotal.y1;
  pRI->rDraw.x0 = pRI->rCursor.x1 + 1;
  pRI->rDraw.x1 = pRI->rTotal.x1;
  return 1;        /* Rectangle needs to be drawn */
}

/*********************************************************************
*
*       _CalcRect3
*
* Purpose:
*   Calculates the rectangle on the bottom of the cursor
*
* Return value:
*   0 if there is no rectangle
*   1 if there is a rectangle
*/
static int _CalcRect3(RECT_INFO * pRI) {
  if (pRI->rTotal.y1 <= pRI->rCursor.y1) {
    return 0;        /* Nothing to do */
  }
  pRI->rDraw.x0 = pRI->rTotal.x0;
  pRI->rDraw.x1 = pRI->rTotal.x1;
  pRI->rDraw.y0 = pRI->rCursor.y1 + 1;
  pRI->rDraw.y1 = pRI->rTotal.y1;
  return 1;        /* Rectangle needs to be drawn */
}

/*********************************************************************
*
*       _apfCalcRect
*/
static int (* const _apfCalcRect[])(RECT_INFO * pRI) = {
  _CalcRect0,
  _CalcRect1,
  _CalcRect2,
  _CalcRect3,
};

/*********************************************************************
*
*       _DrawPixel
*/
static void _DrawPixel(int x, int y) {
  RECT_INFO ri;
  if (_Init(&ri, x, y, x, y)) {
    GUI_CURSOR_SetPixelIndexEx(x, y, LCD_COLORINDEX, GUI_Context.SelLayer);
  } else {
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
      LCDDEV_L0_XorPixel(x, y);
    } else {
      LCDDEV_L0_SetPixelIndex(x, y, LCD_COLORINDEX);
    }
  }
}

/*********************************************************************
*
*       _FillRect
*/
static void _FillRect(int x0, int y0, int x1, int y1) {
  RECT_INFO ri;
  if (_Init(&ri, x0, y0, x1, y1)) {
    int x, y;
    unsigned i;
    /* Perform drawing operation for top and left part */
    for (i = 0; i < 2; i++) {
      if (_apfCalcRect[i](&ri)) {
        LCDDEV_L0_FillRect(ri.rDraw.x0, ri.rDraw.y0, ri.rDraw.x1, ri.rDraw.y1);
      }
    }
    /* Draw cursor area pixel by pixel */
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
      for (y = ri.rCursor.y0; y <= ri.rCursor.y1; y++) {
        for (x = ri.rCursor.x0; x <= ri.rCursor.x1; x++) {
          GUI_CURSOR_XorPixelIndexEx(x, y, GUI_Context.SelLayer);
        }
      }
    } else {
      for (y = ri.rCursor.y0; y <= ri.rCursor.y1; y++) {
        for (x = ri.rCursor.x0; x <= ri.rCursor.x1; x++) {
          GUI_CURSOR_SetPixelIndexEx(x, y, LCD_COLORINDEX, GUI_Context.SelLayer);
        }
      }
    }
    /* Perform drawing operation for right and bottom part */
    for (i = 2; i < 4; i++) {
      if (_apfCalcRect[i](&ri)) {
        LCDDEV_L0_FillRect(ri.rDraw.x0, ri.rDraw.y0, ri.rDraw.x1, ri.rDraw.y1);
      }
    }
  } else {
    LCDDEV_L0_FillRect(x0, y0, x1, y1);
  }
}

/*********************************************************************
*
*       _DrawHLine
*/
static void _DrawHLine(int x0, int y0, int x1) {
  _FillRect(x0, y0, x1, y0);
}

/*********************************************************************
*
*       _DrawVLine
*/
static void _DrawVLine(int x0, int y0, int y1) {
  _FillRect(x0, y0, x0, y1);
}

/*********************************************************************
*
*       _DrawBitmap
*/
static void _DrawBitmap(int x0, int y0,
                       int xSize, int ySize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8 GUI_UNI_PTR * pData, int Diff,
                       const void * pVoid)
{
  RECT_INFO ri;
  const LCD_PIXELINDEX * pTrans;
  pTrans = (const LCD_PIXELINDEX *)pVoid;
  if (_Init(&ri, x0, y0, x0 + xSize - 1, y0 + ySize - 1)) {
    unsigned i;
    for (i = 0; i < 5; i++) {    /* Iterate over all 4 possible rectangles and over the cursor area (1. loop) */
      int Diff_, x0_, y0_, x1, y1, xSize_, ySize_;
      const U8 GUI_UNI_PTR * pData_;
      const GUI_RECT * pRect;
      if (i) {
        if (_apfCalcRect[i - 1](&ri) == 0) {
          continue;
        }
        pRect = &ri.rDraw;
      } else {
        pRect = &ri.rCursor;
      }
      x0_    = x0;
      y0_    = y0;
      xSize_ = xSize;
      ySize_ = ySize;
      pData_ = pData;
      y1 = y0 + ySize - 1;
      x1 = x0 + xSize - 1;
      /* Clip y0 (top) */
      Diff_ = pRect->y0 - y0;
      if (Diff_ > 0) {
        ySize_ -= Diff_;
        if (ySize_ <= 0) {
		      continue;
        }
        y0_     = pRect->y0;
        #if GUI_SUPPORT_LARGE_BITMAPS /* Required only for 16 bit CPUs if some bitmaps are >64kByte */
          pData_ += (U32)     Diff_ * (U32)     BytesPerLine;
        #else
          pData_ += (unsigned)Diff_ * (unsigned)BytesPerLine;
        #endif
      }
      /* Clip y1 (bottom) */
      Diff_ = y1 - pRect->y1;
      if (Diff_ > 0) {
        ySize_ -= Diff_;
        if (ySize_ <= 0) {
		      continue;
        }
      }
      /* Clip right side */
      Diff_ = x1 - pRect->x1;
      if (Diff_ > 0) {
        xSize_ -= Diff_;
      }
      /* Clip left side */
      Diff_ = Diff;
      if (x0_ < pRect->x0) {
        Diff_ = pRect->x0 - x0_;
			  xSize_ += Diff;
			  xSize_ -= Diff_;
			  switch (BitsPerPixel) {
			  case 1:
  			  pData_ += (Diff_ >> 3); x0_ += (Diff_ >> 3) << 3; Diff_ &= 7;
				  break;
			  case 2:
	  		  pData_ += (Diff_ >> 2); x0_ += (Diff_ >> 2) << 2; Diff_ &= 3;
				  break;
			  case 4:
				  pData_ += (Diff_ >> 1); x0_ += (Diff_ >> 1) << 1; Diff_ &= 1;
				  break;
			  case 8:
				  pData_ +=  Diff_;       x0_ +=  Diff_; Diff_ = 0;
				  break;
			  case 16:
				  pData_ += (Diff_ << 1); x0_ +=  Diff_; Diff_ = 0;
				  break;
			  case 24:
        case 32:
				  pData_ += (Diff_ << 2); x0_ +=  Diff_; Diff_ = 0;
				  break;
			  }
      }
      if ((x0_ + Diff_ + xSize_) > pRect->x1) {
        xSize_ = pRect->x1 - (x0_ + Diff_) + 1;
      }
      if (xSize_ <= 0) {
		    continue;
      }
      if (i) {
        /* Draw bitmap */
        LCDDEV_L0_DrawBitmap(x0_, y0_, xSize_, ySize_, BitsPerPixel, BytesPerLine, pData_, Diff_, pTrans);
      } else {
        /* Draw cursor area pixel by pixel */
        int x, y;
        LCD_PIXELINDEX IndexMask;
        IndexMask = LCD_L0_GetIndexMask();
        for (y = pRect->y0; y <= pRect->y1; y++) {
          for (x = pRect->x0; x <= pRect->x1; x++) {
            LCD_PIXELINDEX Index;
            Index = GUI_GetBitmapPixelIndexEx(BitsPerPixel, BytesPerLine, pData_, x - x0_, y - y0_);
            if (pTrans) {
              switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
              case 0:
                GUI_CURSOR_SetPixelIndexEx(x, y, *(pTrans + Index), GUI_Context.SelLayer);
                break;
              case LCD_DRAWMODE_TRANS:
                if (Index) {
                  GUI_CURSOR_SetPixelIndexEx(x, y, *(pTrans + Index), GUI_Context.SelLayer);
                }
                break;
              case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
              case LCD_DRAWMODE_XOR:
                GUI_CURSOR_SetPixelIndexEx(x, y, *(pTrans + Index) ^ IndexMask, GUI_Context.SelLayer);
                break;
              }
            } else {
              switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
              case 0:
                GUI_CURSOR_SetPixelIndexEx(x, y, Index, GUI_Context.SelLayer);
                break;
              case LCD_DRAWMODE_TRANS:
                if (Index) {
                  GUI_CURSOR_SetPixelIndexEx(x, y, Index, GUI_Context.SelLayer);
                }
                break;
              case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
              case LCD_DRAWMODE_XOR:
                GUI_CURSOR_SetPixelIndexEx(x, y, Index ^ IndexMask, GUI_Context.SelLayer);
                break;
              }
            }
          }
        }
      }
    }
  } else {
    LCDDEV_L0_DrawBitmap(x0, y0, xSize, ySize, BitsPerPixel, BytesPerLine, pData, Diff, pTrans);
  }
}

/*********************************************************************
*
*       _APIList
*/
static const LCD_API_LIST _APIList = {
  _DrawPixel,
  _DrawHLine,
  _DrawVLine,
  _FillRect,
  _DrawBitmap,
};

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
void LCD_EnableCursor(int OnOff);
void LCD_EnableCursor(int OnOff) {
  if (OnOff) {
    LCD_SetAPIList(&_APIList);
  } else {
    LCD_SetAPIList(NULL);
  }
}

#else

void LCD_Curs_C(void);
void LCD_Curs_C(void) {} /* avoid empty object files */

#endif   /* (GUI_SUPPORT_CURSOR) && (GUI_SUPPORT_SPRITE == 0) */

/*************************** End of file ****************************/
