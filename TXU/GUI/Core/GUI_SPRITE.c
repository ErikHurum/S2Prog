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
File        : GUI_SPRITE.c
Purpose     : Contains sprite support
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include <string.h>
#include "GUI_Private.h"

#if GUI_SUPPORT_DEVICES

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
/* Context used by rectangle calculating */
typedef struct {
  GUI_HSPRITE hSprite;
  GUI_RECT ClientRect;
  GUI_RECT CurRect;
  int Cnt;
} CLIP_CONTEXT;

/* Context used by sprite drawing */
typedef struct {
  int Layer;
  GUI_HSPRITE hFirstSprite; /* Handle of first sprite object */
  GUI_RECT ClipRect;
} SPRITE_CONTEXT;

/* The sprite object */
typedef struct {
  GUI_RECT Rect;
  GUI_HMEM hColors;
  GUI_HSPRITE hNext;
  GUI_HSPRITE hPrev;
  U16 Flags;
  const GUI_BITMAP GUI_UNI_PTR * pBM;
  SPRITE_CONTEXT * pSpriteContext;
} GUI_SPRITE_OBJ;

/* Bitmap clipping context */
typedef struct {
  int Diff_;
  int x0_;
  int y0_;
  int xSize_;
  int ySize_;
  const U8 GUI_UNI_PTR * pData_;
} CLIP_PARAM;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static SPRITE_CONTEXT _aSpriteContext[GUI_NUM_LAYERS] = {
  {0},
  #if (GUI_NUM_LAYERS > 1)
  {1},
  #if (GUI_NUM_LAYERS > 2)
  {2},
  #if (GUI_NUM_LAYERS > 3)
  {3},
  #if (GUI_NUM_LAYERS > 4)
  {4},
  #if (GUI_NUM_LAYERS > 5)
  {5},
  #endif
  #endif
  #endif
  #endif
  #endif
};

/*********************************************************************
*
*       Static code: Rectangle search...
*
**********************************************************************
*/
/*********************************************************************
*
*       _Findy1
*/
static void _Findy1(GUI_HSPRITE hSprite, GUI_RECT * pRect) {
  GUI_SPRITE_OBJ * pSprite;
  GUI_RECT rSpriteClipped;               /* Sprite rect, clipped to part inside of ancestors */
  for (; hSprite; hSprite = pSprite->hNext) { 
    pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
    rSpriteClipped = pSprite->Rect;
    /* Check if this window affects us at all */    
    if (GUI_RectsIntersect(pRect, &rSpriteClipped)) {
      if (pSprite->Rect.y0 > pRect->y0) {
        if (pRect->y1 >= (rSpriteClipped.y0 - 1)) {
          pRect->y1 = rSpriteClipped.y0 - 1;
        }
      } else {
        if (pRect->y1 >= rSpriteClipped.y1) {
          pRect->y1 = rSpriteClipped.y1;
        }
      }
    }
  }
}

/*********************************************************************
*
*       _Findx0
*/
static int _Findx0(GUI_HSPRITE hSprite, GUI_RECT * pRect) {
  GUI_RECT rSpriteClipped;               /* Sprite rect, clipped to part inside of ancestors */
  GUI_SPRITE_OBJ * pSprite;
  int r = 0;
  for (; hSprite; hSprite = pSprite->hNext) { 
    pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
    rSpriteClipped = pSprite->Rect;
    /* Check if this window affects us at all */    
    if (GUI_RectsIntersect(pRect, &rSpriteClipped)) {
      pRect->x0 = rSpriteClipped.x1 + 1;
      r = 1;
    }
  }
  return r;
}

/*********************************************************************
*
*       _Findx1
*/
static void _Findx1(GUI_HSPRITE hSprite, GUI_RECT * pRect) {
  GUI_RECT rSpriteClipped;               /* Sprite rect, clipped to part inside of ancestors */
  GUI_SPRITE_OBJ * pSprite;
  for (; hSprite; hSprite = pSprite->hNext) { 
    pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
    rSpriteClipped = pSprite->Rect;
    /* Check if this window affects us at all */    
    if (GUI_RectsIntersect(pRect, &rSpriteClipped)) {
      pRect->x1 = rSpriteClipped.x0 - 1;
    }
  }
}

/*********************************************************************
*
*       _FindNextRect
*/
static int _FindNextRect(CLIP_CONTEXT * pContext) {
  GUI_RECT r;
  GUI_HSPRITE hSprite;
  r = pContext->CurRect;  /* temps  so we do not have to work with pointers too much */
  /*
     STEP 1:
       Set the next position which could be part of the next rectangle.
       This will be the first unhandle pixel in reading order, i.e. next one to the right
       or next one down if we are at the right border.
  */
  if (pContext->Cnt == 0) {       /* First rectangle starts in upper left */
    r.x0 = pContext->ClientRect.x0;
    r.y0 = pContext->ClientRect.y0;
  } else {
    r.x0 = pContext->CurRect.x1 + 1;
    r.y0 = pContext->CurRect.y0;
    if (r.x0 > pContext->ClientRect.x1) {
NextStripe:  /* go down to next stripe */
      r.x0 = pContext->ClientRect.x0;
      r.y0 = pContext->CurRect.y1 + 1;
    }
  }
  /*
     STEP 2:
       Check if we are done completely.
  */
  if (r.y0 > pContext->ClientRect.y1) {
    return 0;
  }
  /* STEP 3:
       Find out the max. height (r.y1) if we are at the left border.
       Since we are using the same height for all rectangles at the same y0,
       we do this only for the leftmost one.
  */
  if (r.x0 == pContext->ClientRect.x0) {
    r.y1 = pContext->ClientRect.y1;
    r.x1 = pContext->ClientRect.x1;
    /* Iterate over all sprites */
    for (hSprite = _aSpriteContext[GUI_Context.SelLayer].hFirstSprite; hSprite; hSprite = ((GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite))->hNext) {
      _Findy1(hSprite, &r);
    }
  }
  /* 
    STEP 4
      Find out x0 for the given y0, y1 by iterating over windows above.
      if we find one that intersects, adjust x0 to the right.
  */
Find_x0:
  r.x1 = r.x0;
  for (hSprite = _aSpriteContext[GUI_Context.SelLayer].hFirstSprite; hSprite; hSprite = ((GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite))->hNext) {
    if (_Findx0(hSprite, &r)) {
      goto Find_x0;
    }
  }
  /* 
   STEP 5:
     If r.x0 out of right border, this stripe is done. Set next stripe and goto STEP 2
     Find out x1 for the given x0, y0, y1
  */
  r.x1 = pContext->ClientRect.x1;
  if (r.x1 < r.x0) {/* horizontal border reached ? */
    pContext->CurRect = r;
    goto NextStripe;
  }    
  /* 
   STEP 6:
     Find r.x1. We have to Iterate over all windows which are above
  */
  for (hSprite = _aSpriteContext[GUI_Context.SelLayer].hFirstSprite; hSprite; hSprite = ((GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite))->hNext) {
    _Findx1(hSprite, &r);
  }
  /* We are done. Return the rectangle we found in the pContext-> */
  if (pContext->Cnt > 200) {
    return 0;  /* error !!! This should not happen !*/
  }
  pContext->CurRect = r;
  if (memcmp(&pContext->CurRect, &pContext->ClientRect, sizeof(GUI_RECT))) {
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       _GetNextRect
*
* Purpose:
*   Breaks down the drawing area into rectangular areas around the cursor
*   areas.
*/
static int  _GetNextRect(CLIP_CONTEXT * pContext) {
  ++pContext->Cnt;
  /* Find next rectangle and use it as ClipRect */
  if (!_FindNextRect(pContext)) {
    return 0;        /* Could not find an other one ! */
  }
  return 1;
}

/*********************************************************************
*
*       _InitRectSearch
*
* Purpose:
*   Initializes the rectangle search.
*
* Return value:
*   0 - No rectangle found, nothing to be drawn
*   1 - First rectangle outside of the sprite area has been found and is
*       available in pContext->CurRect
*   2 - No rectangle outside of the sprites but drawing operation is within 
*       the sprite areas
*/
static int _InitRectSearch(CLIP_CONTEXT * pContext, int x0, int y0, int x1, int y1) {
  pContext->ClientRect.x0 = x0;
  pContext->ClientRect.y0 = y0;
  pContext->ClientRect.x1 = x1;
  pContext->ClientRect.y1 = y1;
  pContext->Cnt        = -1;
  pContext->CurRect    = pContext->ClientRect;
  pContext->hSprite    = _aSpriteContext[GUI_Context.SelLayer].hFirstSprite;
  if (_GetNextRect(pContext) == 0) {
    GUI_HSPRITE hSprite;
    GUI_SPRITE_OBJ * pSprite;
    /* At this point we need to check if the drawing operation is completely 
       'covered' or completely 'outside' of the sprite areas.
       Because _FindNextRect() has already made sure that the drawing operation 
       is completely 'outside' or completely 'covered' we have to find out
       if the drawing operation is covered at least by one sprite
    */
    for (hSprite = _aSpriteContext[GUI_Context.SelLayer].hFirstSprite; hSprite; hSprite = ((GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite))->hNext) {
      pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
      if (GUI_RectsIntersect(&pSprite->Rect, &pContext->ClientRect)) {
        return 2;
      }
    }
    return 0;        /* Could not find an other one ! */
  }
  return 1; /* Found the first rectangle */
}

/*********************************************************************
*
*       _IsInRect
*
* Purpose:
*   Obvios
*/
static int _IsInRect(int x, int y, GUI_RECT * pRect) {
  return ((pRect->x0 <= x) && (pRect->x1 >= x) && (pRect->y0 <= y) && (pRect->y1 >= y)) ? 1 : 0;
}

/*********************************************************************
*
*       _DrawPixelLL
*/
static void _DrawPixelLL(int x, int y, int Index, GUI_SPRITE_OBJ * pSprite) {
  GUI_RECT * pRect;
  SPRITE_CONTEXT * pSpriteContext;
  pSpriteContext = pSprite->pSpriteContext;
  pRect = &pSpriteContext->ClipRect;
  if (x > pRect->x1) {
    return;
  }
  if (x < pRect->x0) {
    return;
  }
  if (y > pRect->y1) {
    return;
  }
  if (y < pRect->y0) {
    return;
  }
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    LCD_aAPI[pSpriteContext->Layer]->pfXorPixel(x, y);
  } else {
    LCD_aAPI[pSpriteContext->Layer]->pfSetPixelIndex(x, y, Index);
  }
}

/*********************************************************************
*
*       _GetPixelIndexLL
*/
static int _GetPixelIndexLL(int x, int y, GUI_SPRITE_OBJ * pSprite) {
  GUI_RECT * pRect;
  SPRITE_CONTEXT * pSpriteContext;
  pSpriteContext = pSprite->pSpriteContext;
  pRect = &pSpriteContext->ClipRect;
  if (x > pRect->x1) {
    return 0;
  }
  if (x < pRect->x0) {
    return 0;
  }
  if (y > pRect->y1) {
    return 0;
  }
  if (y < pRect->y0) {
    return 0;
  }
  return LCD_aAPI[pSpriteContext->Layer]->pfGetPixelIndex(x, y);
}

/*********************************************************************
*
*       _CheckCoveredByLowerLevelSprite
*
* Purpose:
*   Checks if the given position is covered by a lower level sprite
*/
static int _CheckCoveredByLowerLevelSprite(int x, int y, GUI_SPRITE_OBJ * pSprite) {
  GUI_HSPRITE hSprite;
  GUI_SPRITE_OBJ * pSpriteNext;
  for (hSprite = pSprite->hNext; hSprite; hSprite = ((GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite))->hNext) {
    pSpriteNext = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
    if (_IsInRect(x, y, &pSpriteNext->Rect)) {
      if (GUI_GetBitmapPixelIndex(pSpriteNext->pBM, x - pSpriteNext->Rect.x0, y - pSpriteNext->Rect.y0) != 0) {
        return 1; /* Pixel is covered by lower level sprite */
      }
    }
  }
  return 0; /* Pixel is not covered by lower level sprite */
}

/*********************************************************************
*
*       _SetBkPixel
*
* Purpose:
*   This routine is used for drawing operations in the sprite area. 
*   It first checks if the given position of the given sprite is covered
*   by a higher level sprite. If so it passes the pixel to be drawn to 
*   the sprite above. If the position is not covered by a higher level 
*   sprite it first checks if the given sprite position is transparent 
*   or not. If it is transparent the pixel is drawn only if it is not 
*   over a lower level sprite. If it is not transparent the given pixel 
*   is saved in the background data.
*
* Return value:
*   1 if pixel data has been managed
*   0 if pixel data has not been managed
*/
static int _SetBkPixel(int x, int y, int Index, GUI_SPRITE_OBJ * pSprite, int IsSprite) {
  const GUI_BITMAP GUI_UNI_PTR * pBM;
  GUI_HSPRITE hSprite;
  GUI_SPRITE_OBJ * pSpritePrev;
  pBM = pSprite->pBM;
  /* Check if the given position is covered by a higer level sprite */
  for (hSprite = pSprite->hPrev; hSprite; hSprite = ((GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite))->hPrev) {
    pSpritePrev = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
    if (_IsInRect(x, y, &pSpritePrev->Rect)) {
      /* Passing the pixel to higher level sprites should only be done for
       * transparent pixels. If the current sprite pixel is not transparent,
       * nothing else should be done */
      if (GUI_GetBitmapPixelIndex(pBM, x - pSprite->Rect.x0, y - pSprite->Rect.y0) != 0) {
        goto StoreData;
      }
      /* Pass to higer level sprite and return */
      return _SetBkPixel(x, y, Index, pSpritePrev, IsSprite);
    }
  }
  /* Manage pixel data */
  if (GUI_GetBitmapPixelIndex(pBM, x - pSprite->Rect.x0, y - pSprite->Rect.y0) == 0) {
    /* The given position of the given sprite pixel is transparent. 
     * Now make sure we do not overwrite a non transparent sprite pixel of a lower level sprite */
    if (_CheckCoveredByLowerLevelSprite(x, y, pSprite)) {
      return 1; /* Pixel of covered sprite not transparent, so nothing to do */
    }
    /* Transparent pixels: Draw on hardware */
    _DrawPixelLL(x, y, Index, pSprite);
  } else {
    /* Non transparent pixels: Store into sprite background */
    int xSize;
    LCD_PIXELINDEX * pData;
StoreData:
    /* Save only if there is no other non transparent sprite pixel behind  */
    if (IsSprite == 0) {
      if (_CheckCoveredByLowerLevelSprite(x, y, pSprite)) {
        return 1; /* Pixel of covered sprite not transparent, so nothing to do */
      }
    }
    /* Non transparent pixels: Store into sprite background */
    xSize = pSprite->Rect.x1 - pSprite->Rect.x0 + 1;
    pData = (LCD_PIXELINDEX *)((U8 *)pSprite + sizeof(GUI_SPRITE_OBJ));
    pData += xSize * (y - pSprite->Rect.y0) + (x - pSprite->Rect.x0);
    *pData = Index;
  }
  return 0;
}

/*********************************************************************
*
*       _SetSpriteBkPixel
*
* Purpose:
*   This routine is used to draw the sprite pixels itself. It temporary
*   removes the bitmap of the given sprite and uses _SetBkPixel() for the 
*   drawing operation. This makes sure that the background will be managed 
*   in exact the same manner as in normal drawing operations.
*/
static void _SetSpriteBkPixel(int x, int y, int Index, GUI_SPRITE_OBJ * pSprite) {
  const GUI_BITMAP GUI_UNI_PTR * pBM;
  pBM = pSprite->pBM;
  pSprite->pBM = NULL; /* Temporary remove of bitmap pointer */
  if (_SetBkPixel(x, y, Index, pSprite, 1)) {
    _DrawPixelLL(x, y, Index, pSprite);
  }
  pSprite->pBM = pBM;  /* Restore pointer to bitmap */
}

/*********************************************************************
*
*       _GetBkPixel
*
* Purpose:
*   Returns the background value of the given position.
*/
static int _GetBkPixel(int x, int y, GUI_SPRITE_OBJ * pSprite) {
  GUI_HSPRITE      hSprite;
  GUI_SPRITE_OBJ * pSpritePrev;
  int Pixel;
  LCD_PIXELINDEX * pData;
  /* First check if the given position is within the current sprite */
  if (_IsInRect(x, y, &pSprite->Rect)) {
    /* If the pixel is not transparent, we found it */
    Pixel = GUI_GetBitmapPixelIndex(pSprite->pBM, x - pSprite->Rect.x0, y - pSprite->Rect.y0);
    if (Pixel != 0) {
      pData = (LCD_PIXELINDEX *)((U8 *)pSprite + sizeof(GUI_SPRITE_OBJ));
      pData += (pSprite->Rect.x1 - pSprite->Rect.x0 + 1) * (y - pSprite->Rect.y0) + (x - pSprite->Rect.x0);
      return *pData;
    }
  }
  /* Check if the position is covered by a higher level sprite */
  for (hSprite = pSprite->hPrev; hSprite; hSprite = ((GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite))->hPrev) {
    pSpritePrev = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
    if (_IsInRect(x, y, &pSpritePrev->Rect)) {
      /* Check if the pixel of the covering sprite is not transparent */
      Pixel = GUI_GetBitmapPixelIndex(pSpritePrev->pBM, x - pSpritePrev->Rect.x0, y - pSpritePrev->Rect.y0);
      if (Pixel != 0) {
        pData = (LCD_PIXELINDEX *)((U8 *)pSpritePrev + sizeof(GUI_SPRITE_OBJ));
        pData += (pSpritePrev->Rect.x1 - pSpritePrev->Rect.x0 + 1) * (y - pSpritePrev->Rect.y0) + (x - pSpritePrev->Rect.x0);
        return *pData;
      }
    }
  }
  /* No sprite above, so get the background from the physical display */
  Pixel = _GetPixelIndexLL(x, y, pSprite);
  return Pixel;
}

/*********************************************************************
*
*       _DrawPixel
*/
static void _DrawPixel(int x, int y) {
  int r;
  CLIP_CONTEXT Context = {0};
  r = _InitRectSearch(&Context, x, y, x, y);
  if (r) {
    if (r == 1) {
      /* Drawing operation outside, so pass to HW level */
      if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
        LCDDEV_L0_XorPixel(x, y);
      } else {
        LCDDEV_L0_SetPixelIndex(x, y, LCD_COLORINDEX);
      }
    } else {
      /* Draw pixel inside the sprite areas */
      GUI_SPRITE_OBJ * pSprite;
      pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(_aSpriteContext[GUI_Context.SelLayer].hFirstSprite);
      if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
        int Index;
        Index = _GetBkPixel(x, y, pSprite);
        Index ^= LCD_aAPI[GUI_Context.SelLayer]->pfGetIndexMask();
        _SetBkPixel(x, y, Index, pSprite, 0);
      } else {
        _SetBkPixel(x, y, LCD_COLORINDEX, pSprite, 0);
      }
    }
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
*       _GetLastSprite
*/
static GUI_HSPRITE _GetLastSprite(void) {
  GUI_HSPRITE hSprite;
  GUI_SPRITE_OBJ * pSprite;
  hSprite = _aSpriteContext[GUI_Context.SelLayer].hFirstSprite;
  while (1) {
    pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
    if (pSprite->hNext == 0) {
      break;
    }
    hSprite = pSprite->hNext;
  };
  return hSprite;
}

/*********************************************************************
*
*       _FillRect
*
* Purpose:
*   The function first breaks down the area outside of the sprites into
*   rectangles and fills them with the current background color.
*   Then all affected sprite areas will be managed pixel by pixel.
*/
static void _FillRect(int x0, int y0, int x1, int y1) {
  int r;
  CLIP_CONTEXT Context = {0};
  r = _InitRectSearch(&Context, x0, y0, x1, y1);
  if (r) {
    GUI_HSPRITE hSprite;
    /* Draw all pixels outside of the sprites */
    if (r == 1) {
      do {
        LCDDEV_L0_FillRect(Context.CurRect.x0, Context.CurRect.y0, Context.CurRect.x1, Context.CurRect.y1);
      } while (_GetNextRect(&Context));
    }
    /* Draw all pixels inside the sprite areas */
    for (hSprite = _GetLastSprite(); hSprite; hSprite = ((GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite))->hPrev) {
      int x, y;
      GUI_SPRITE_OBJ * pSprite;
      GUI_RECT Rect;
      pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
      Rect    = pSprite->Rect;
      if (GUI_RectsIntersect(&Rect, &Context.ClientRect)) {
        GUI__IntersectRect(&Rect, &Context.ClientRect);
        for (y = Rect.y0; y <= Rect.y1; y++) {
          for (x = Rect.x0; x <= Rect.x1; x++) {
            if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
              _SetBkPixel(x, y, LCD_COLORINDEX ^ LCD_aAPI[GUI_Context.SelLayer]->pfGetIndexMask(), pSprite, 0);
            } else {
              _SetBkPixel(x, y, LCD_COLORINDEX, pSprite, 0);
            }
          }
        }
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
*       _GetClipParam
*/
static int _GetClipParam(int x0, int y0,
                         int xSize, int ySize,
                         int BitsPerPixel, 
                         int BytesPerLine,
                         const U8 GUI_UNI_PTR * pData, 
                         int Diff,
                         const GUI_RECT * pRect,
                         CLIP_PARAM * p)
{
  int x1, y1;
  p->x0_    = x0;
  p->y0_    = y0;
  p->xSize_ = xSize;
  p->ySize_ = ySize;
  p->pData_ = pData;
  y1 = y0 + ySize - 1;
  x1 = x0 + xSize - 1;
  /* Clip y0 (top) */
  p->Diff_ = pRect->y0 - y0;
  if (p->Diff_ > 0) {
    p->ySize_ -= p->Diff_;
    if (p->ySize_ <= 0) {
		  return 1;
    }
    p->y0_     = pRect->y0;
    #if GUI_SUPPORT_LARGE_BITMAPS /* Required only for 16 bit CPUs if some bitmaps are >64kByte */
      p->pData_ += (U32)     p->Diff_ * (U32)     BytesPerLine;
    #else
      p->pData_ += (unsigned)p->Diff_ * (unsigned)BytesPerLine;
    #endif
  }
  /* Clip y1 (bottom) */
  p->Diff_ = y1 - pRect->y1;
  if (p->Diff_ > 0) {
    p->ySize_ -= p->Diff_;
    if (p->ySize_ <= 0) {
		  return 1;
    }
  }
  /* Clip right side */
  p->Diff_ = x1 - pRect->x1;
  if (p->Diff_ > 0) {
    p->xSize_ -= p->Diff_;
  }
  /* Clip left side */
  p->Diff_ = Diff;
  if (p->x0_ < pRect->x0) {
    p->Diff_ = pRect->x0 - p->x0_;
		p->xSize_ += Diff;
		p->xSize_ -= p->Diff_;
		switch (BitsPerPixel) {
		case 1:
  		p->pData_ += (p->Diff_ >> 3); p->x0_ += (p->Diff_ >> 3) << 3; p->Diff_ &= 7;
			break;
		case 2:
	  	p->pData_ += (p->Diff_ >> 2); p->x0_ += (p->Diff_ >> 2) << 2; p->Diff_ &= 3;
			break;
		case 4:
			p->pData_ += (p->Diff_ >> 1); p->x0_ += (p->Diff_ >> 1) << 1; p->Diff_ &= 1;
			break;
		case 8:
			p->pData_ +=  p->Diff_;       p->x0_ +=  p->Diff_; p->Diff_ = 0;
			break;
		case 16:
			p->pData_ += (p->Diff_ << 1); p->x0_ +=  p->Diff_; p->Diff_ = 0;
			break;
		case 24:
    case 32:
			p->pData_ += (p->Diff_ << 2); p->x0_ +=  p->Diff_; p->Diff_ = 0;
			break;
		}
  }
  if ((p->x0_ + p->Diff_ + p->xSize_) > pRect->x1) {
    p->xSize_ = pRect->x1 - (p->x0_ + p->Diff_) + 1;
  }
  if (p->xSize_ <= 0) {
		return 1;
  }
  return 0;
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
                       const void * pvTrans)
{
  const LCD_PIXELINDEX * pTrans;
  int r;
  CLIP_CONTEXT Context = {0};
  LCD_PIXELINDEX IndexMask;
  pTrans = (const LCD_PIXELINDEX *)pvTrans;
  r = _InitRectSearch(&Context, x0 + Diff, y0, x0 + xSize - 1 + Diff, y0 + ySize - 1);
  if (r) {
    GUI_HSPRITE hSprite;
    /* Draw all pixels outside of the sprites */
    if (r == 1) {
      do {
        CLIP_PARAM Param;
        const GUI_RECT * pRect;
        pRect  = &Context.CurRect;
        if (_GetClipParam(x0, y0, xSize, ySize, BitsPerPixel, BytesPerLine, pData, Diff, pRect, &Param)) {
          continue;
        }
        LCDDEV_L0_DrawBitmap(Param.x0_, Param.y0_, Param.xSize_, Param.ySize_, BitsPerPixel, BytesPerLine, Param.pData_, Param.Diff_, pTrans);
      } while (_GetNextRect(&Context));
    }
    /* Draw all pixels inside the sprite areas */
    IndexMask = LCD_L0_GetIndexMask();
    for (hSprite = _GetLastSprite(); hSprite; hSprite = ((GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite))->hPrev) {
      int x, y;
      GUI_SPRITE_OBJ * pSprite;
      GUI_RECT Rect;
      pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
      Rect    = pSprite->Rect;
      if (GUI_RectsIntersect(&Rect, &Context.ClientRect)) {
        CLIP_PARAM Param;
        const GUI_RECT * pRect;
        GUI__IntersectRect(&Rect, &Context.ClientRect);
        pRect  = &Rect;
        if (_GetClipParam(x0, y0, xSize, ySize, BitsPerPixel, BytesPerLine, pData, Diff, pRect, &Param)) {
          continue;
        }
        for (y = pRect->y0; y <= pRect->y1; y++) {
          for (x = pRect->x0; x <= pRect->x1; x++) {
            LCD_PIXELINDEX Index;
            Index = GUI_GetBitmapPixelIndexEx(BitsPerPixel, BytesPerLine, Param.pData_, x - Param.x0_, y - Param.y0_);
            if (pTrans) {
              switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
              case 0:
                _SetBkPixel(x, y, *(pTrans + Index), pSprite, 0);
                break;
              case LCD_DRAWMODE_TRANS:
                if (Index) {
                  _SetBkPixel(x, y, *(pTrans + Index), pSprite, 0);
                }
                break;
              case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
              case LCD_DRAWMODE_XOR:
                _SetBkPixel(x, y, *(pTrans + Index) ^ IndexMask, pSprite, 0);
                break;
              }
            } else {
              switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
              case 0:
                _SetBkPixel(x, y, Index, pSprite, 0);
                break;
              case LCD_DRAWMODE_TRANS:
                if (Index) {
                  _SetBkPixel(x, y, Index, pSprite, 0);
                }
                break;
              case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
              case LCD_DRAWMODE_XOR:
                _SetBkPixel(x, y, Index ^ IndexMask, pSprite, 0);
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
  _DrawBitmap
};

/*********************************************************************
*
*       _Undraw
*
* Purpose:
*   This routine removes the drawing of the sprite from the screen. It
*   replaces the non transparent sprite pixels with the background stored
*   in the sprite data area. If a non transparent sprite pixel is covered
*   by a further sprite the routine makes sure that the background data
*   is passed to the right sprite.
*/
static void _Undraw(GUI_SPRITE_OBJ * pSprite) {
  int x, y;
  GUI_RECT Rect;
  const GUI_BITMAP GUI_UNI_PTR * pBM;
  LCD_PIXELINDEX * pData;

  pBM   = pSprite->pBM;
  pData = (LCD_PIXELINDEX *)((U8 *)pSprite + sizeof(GUI_SPRITE_OBJ));
  Rect  = pSprite->Rect;
  for (y = Rect.y0; y <= Rect.y1; y++) {
    for (x = Rect.x0; x <= Rect.x1; x++) {
      if (GUI_GetBitmapPixelIndex(pBM, x - pSprite->Rect.x0, y - pSprite->Rect.y0) != 0) {
        LCD_PIXELINDEX Data;
        Data = *pData;
        _SetSpriteBkPixel(x, y, Data, pSprite);
      }
      pData++;
    }
  }
  pSprite->pBM = pBM;
}

/*********************************************************************
*
*       _SetPosition
*
* Purpose:
*   Sets the new position of the given sprite and restores the background
*   on demand.
*/
static void _SetPosition(GUI_SPRITE_OBJ * pSprite, int xNewPos, int yNewPos) {
  int x, xPos, xStart, xStep, xEnd, xOff, xOverlapMin, xOverlapMax;
  int y, yPos, yStart, yStep, yEnd, yOff, yOverlapMin, yOverlapMax;
  int xSize, ySize;
  LCD_PIXELINDEX * pData;
  LCD_PIXELINDEX * pColors;
  const GUI_BITMAP GUI_UNI_PTR * pBM;

  if ((xNewPos == pSprite->Rect.x0) && (yNewPos == pSprite->Rect.y0)) {
    return;
  }
  xPos  = pSprite->Rect.x0;
  yPos  = pSprite->Rect.y0;
  xSize = pSprite->Rect.x1 - xPos + 1;
  ySize = pSprite->Rect.y1 - yPos + 1;
  if (pSprite->Flags & GUI_SPRITE_CF_SHOW) {
    pBM   = pSprite->pBM;
    pData = (LCD_PIXELINDEX *)((U8 *)pSprite + sizeof(GUI_SPRITE_OBJ));
    xOff  = xNewPos - xPos;
    yOff  = yNewPos - yPos;
    pColors = (LCD_PIXELINDEX *)GUI_ALLOC_h2p(pSprite->hColors);
    if (xOff > 0) {
      xStep  = 1;
      xStart = 0;
      xEnd   = xSize;
      xOverlapMax = xEnd - 1;
      xOverlapMin = xOff;
    } else {
      xStep  = -1;
      xStart = xSize - 1;
      xEnd   = -1;
      xOverlapMin = 0;
      xOverlapMax = xStart + xOff;
    }
    if (yOff > 0) {
      yStep  = 1;
      yStart = 0;
      yEnd   = ySize;
      yOverlapMax = yEnd - 1;
      yOverlapMin = yOff;
    } else {
      yStep  = -1;
      yStart = ySize - 1;
      yEnd   = -1;
      yOverlapMin = 0;
      yOverlapMax = yStart + yOff;
    }
    for (y = yStart; y != yEnd; y += yStep) {
      char yOverlaps;
      int yNew = y + yOff;
      yOverlaps    = (y >= yOverlapMin) && (y <= yOverlapMax);
      for (x = xStart; x != xEnd; x += xStep) {
        char xyOverlaps;
        int BitmapPixel;
        int BkPixel;
        LCD_PIXELINDEX * pSave;
        int xNew;
        BitmapPixel = GUI_GetBitmapPixelIndex(pBM, x, y);
        /* Manage pixel only if it is not transparent */
        if (BitmapPixel) {
          LCD_PIXELINDEX NewPixel;
          pSave      = pData + x + y * xSize;
          xNew       = x + xOff;
          xyOverlaps = (x >= xOverlapMin) && (x <= xOverlapMax) && yOverlaps;
          /* Get background pixel of new position */
          BkPixel = _GetBkPixel(xPos + xNew, yPos + yNew, pSprite);
          /* Restore old pixel if it was not transparent */
          if (!xyOverlaps || (GUI_GetBitmapPixelIndex(pBM, x - xOff, y - yOff) == 0)) {
            _SetSpriteBkPixel(x + xPos, y + yPos, *(pSave), pSprite);
          }
          /* Draw new pixel */
          NewPixel = *(pColors + BitmapPixel);
          _SetSpriteBkPixel(xPos + xNew, yPos + yNew, NewPixel, pSprite);
          /* Save background pixel */
          *pSave = BkPixel;
        }
      }
    }
  }
  /* Adjust position of sprite */
  pSprite->Rect.x0 = xNewPos;
  pSprite->Rect.y0 = yNewPos;
  pSprite->Rect.x1 = xNewPos + xSize - 1;
  pSprite->Rect.y1 = yNewPos + ySize - 1;
}

/*********************************************************************
*
*       _SetBitmap
*/
static void _SetBitmap(GUI_SPRITE_OBJ * pSprite, const GUI_BITMAP GUI_UNI_PTR * pBM) {
  int xPos, yPos, x, y, Index;
  int PixelOld, PixelNew;
  LCD_PIXELINDEX * pData;
  LCD_PIXELINDEX * pColors;
  pData   = (LCD_PIXELINDEX *)((U8 *)pSprite + sizeof(GUI_SPRITE_OBJ));
  pColors = (LCD_PIXELINDEX *)GUI_ALLOC_h2p(pSprite->hColors);
  xPos = pSprite->Rect.x0;
  yPos = pSprite->Rect.y0;
  for (y = 0; y < pBM->YSize; y++) {
    for (x = 0; x < pBM->XSize; x++) {
      PixelOld = GUI_GetBitmapPixelIndex(pSprite->pBM, x, y);
      PixelNew = GUI_GetBitmapPixelIndex(pBM, x, y);
      if (PixelNew == 0) {
        if (PixelOld) {
          /* Restore background */
          Index = *(pData + y * pBM->XSize + x);                 /* Get old value from background pixel buffer */
          _SetSpriteBkPixel(xPos + x, yPos + y, Index, pSprite); /* Draw it */
        }
      } else {
        /* Save background */
        *(pData + y * pBM->XSize + x) = _GetBkPixel(xPos + x, yPos + y, pSprite);
        /* Draw new pixel */
        Index = *(pColors + PixelNew);                           /* Get new index from color conversion buffer */
        _SetSpriteBkPixel(xPos + x, yPos + y, Index, pSprite);   /* Draw it */
      }
    }
  }
  pSprite->pBM = pBM;
}

/*********************************************************************
*
*       _SetBitmapAndPosition
*/
static void _SetBitmapAndPosition(GUI_SPRITE_OBJ * pSprite, const GUI_BITMAP GUI_UNI_PTR * pBM_New, int xOff, int yOff) {
  int xSize, ySize;
  int x, y;
  int xStart, xEnd, xInc, yStart, yEnd, yInc;
  const GUI_BITMAP GUI_UNI_PTR * pBM_Old;
  LCD_PIXELINDEX * pData;
  LCD_PIXELINDEX * pColors;

  pBM_Old   = pSprite->pBM;
  pData = (LCD_PIXELINDEX *)((U8 *)pSprite + sizeof(GUI_SPRITE_OBJ));
  pColors = (LCD_PIXELINDEX *)GUI_ALLOC_h2p(pSprite->hColors);
  xSize = pSprite->Rect.x1 - pSprite->Rect.x0 + 1;
  ySize = pSprite->Rect.y1 - pSprite->Rect.y0 + 1;
  if (yOff < 0) {
    yStart = ySize - 1;
    yEnd   = -1;
    yInc   = -1;
  } else {
    yStart = 0;
    yEnd   = ySize;
    yInc   = 1;
  }
  if (xOff < 0) {
    xStart = xSize - 1;
    xEnd   = -1;
    xInc   = -1;
  } else {
    xStart = 0;
    xEnd   = xSize;
    xInc   = 1;
  }
  for (y = yStart; y != yEnd; y += yInc) {
    for (x = xStart; x != xEnd; x += xInc) {
      int xPos, yPos;
      int Pixel, Overlap, Undraw;
      int PixelOld, PixelNew;
      Undraw = 1;
      PixelOld = GUI_GetBitmapPixelIndex(pBM_Old, x, y);
      PixelNew = GUI_GetBitmapPixelIndex(pBM_New, x, y);
      xPos = x - xOff;
      yPos = y - yOff;
      Overlap = (xPos >= 0) && (yPos >= 0) && (xPos < pBM_New->XSize) && (yPos < pBM_New->YSize);
      /* Restore background */
      if (PixelOld) {
        if (Overlap) {
          Pixel = GUI_GetBitmapPixelIndex(pBM_New, xPos, yPos);
          if (Pixel) {
            Undraw = 0;
          }
        }
        if (Undraw) {
          LCD_PIXELINDEX Data;
          Data = *(pData + y * xSize + x);
          _SetSpriteBkPixel(pSprite->Rect.x0 + x, pSprite->Rect.y0 + y, Data, pSprite);
        }
      }
      /* Draw new pixel and save background data */
      if (PixelNew) {
        int Index, BkIndex;
        BkIndex = _GetBkPixel(pSprite->Rect.x0 + x + xOff, pSprite->Rect.y0 + y + yOff, pSprite);
        Index = *(pColors + PixelNew);
        _SetSpriteBkPixel(pSprite->Rect.x0 + x + xOff, pSprite->Rect.y0 + y + yOff, Index, pSprite);
        *(pData + y * xSize + x) = BkIndex;
      }
    }
  }
  pSprite->pBM = pBM_New;
  pSprite->Rect.x0 += xOff;
  pSprite->Rect.x1 += xOff;
  pSprite->Rect.y0 += yOff;
  pSprite->Rect.y1 += yOff;
}

/*********************************************************************
*
*       _SpriteDraw
*/
static void _SpriteDraw(GUI_SPRITE_OBJ * pSprite) {
  int xPos, yPos, x, y, Index;
  int PixelNew;
  LCD_PIXELINDEX * pData;
  LCD_PIXELINDEX * pColors;
  const GUI_BITMAP GUI_UNI_PTR * pBM;
  pBM = pSprite->pBM;
  pData = (LCD_PIXELINDEX *)((U8 *)pSprite + sizeof(GUI_SPRITE_OBJ));
  pColors = (LCD_PIXELINDEX *)GUI_ALLOC_h2p(pSprite->hColors);
  xPos = pSprite->Rect.x0;
  yPos = pSprite->Rect.y0;
  pSprite->pBM = NULL; /* Temporary remove bitmap to make sure not the background of the sprite itself will be saved */
  for (y = 0; y < pBM->YSize; y++) {
    for (x = 0; x < pBM->XSize; x++) {
      PixelNew = GUI_GetBitmapPixelIndex(pBM, x, y);
      if (PixelNew) {
        /* Save background */
        *(pData + y * pBM->XSize + x) = _GetBkPixel(xPos + x, yPos + y, pSprite);
        /* Draw new pixel */
        Index = *(pColors + PixelNew);
        _SetSpriteBkPixel(xPos + x, yPos + y, Index, pSprite);
      }
    }
  }
  pSprite->pBM = pBM;
}

/*********************************************************************
*
*       _Link
*
* Purpose:
*   Inserts the given sprite into the list. Sprites with non STAYONTOP attribute
*   are placed directly after the last sprite with STAYONTOP attribute. New
*   sprites with STAYONTOP attribute are placed at the top of the list.
*/
static void _Link(GUI_HSPRITE hSpriteNew, GUI_SPRITE_OBJ * pSpriteNew) {
  GUI_HSPRITE hSprite;
  GUI_SPRITE_OBJ * pSprite;
  hSprite = pSpriteNew->pSpriteContext->hFirstSprite;
  /* If the sprite to be linked is not a top level sprite get the right position first */
  if ((pSpriteNew->Flags & GUI_SPRITE_CF_STAYONTOP) == 0) {
    GUI_HSPRITE hSpriteNext;
    /* Iterate over all sprites */
    while (hSprite) {
      pSprite     = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
      hSpriteNext = pSprite->hNext;
      if (hSpriteNext == 0) {
        break; /* No more sprites */
      }
      if ((pSprite->Flags & GUI_SPRITE_CF_STAYONTOP) == 0) {
        break; /* No more top level sprites  */
      }
      hSprite = hSpriteNext;
    }
  }
  if (hSprite) {
    pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
    if (pSprite->Flags & GUI_SPRITE_CF_STAYONTOP) {
      /* Insert after last stay on top sprite */
      if (pSprite->hNext) {
        GUI_SPRITE_OBJ * pSpriteNext;
        pSpriteNext = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(pSprite->hNext);
        pSpriteNew->hNext  = pSprite->hNext;
        pSpriteNext->hPrev = hSpriteNew;
      }
      pSprite->hNext    = hSpriteNew;
      pSpriteNew->hPrev = hSprite;
    } else {
      /* Insert before last non stay on top sprite */
      if (pSprite->hPrev) {
        GUI_SPRITE_OBJ * pSpritePrev;
        pSpritePrev = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(pSprite->hPrev);
        pSpriteNew->hPrev  = pSprite->hPrev;
        pSpritePrev->hNext = hSpriteNew;
      } else {
        pSprite->pSpriteContext->hFirstSprite = hSpriteNew;
      }
      pSprite->hPrev    = hSpriteNew;
      pSpriteNew->hNext = hSprite;
    }
  } else {
    #if GUI_SUPPORT_CURSOR
      LCD_SetAPIList(&_APIList);
    #endif
    pSpriteNew->pSpriteContext->hFirstSprite = hSpriteNew;
  }
}

/*********************************************************************
*
*       _Unlink
*/
static void _Unlink(GUI_HSPRITE hSprite, GUI_SPRITE_OBJ * pSprite) {
  SPRITE_CONTEXT * pSpriteContext;
  pSpriteContext = pSprite->pSpriteContext;
  if (pSpriteContext->hFirstSprite == hSprite) {
    pSpriteContext->hFirstSprite = pSprite->hNext;
    #if GUI_SUPPORT_CURSOR
      if (pSpriteContext->hFirstSprite == 0) {
        LCD_SetAPIList(NULL);
      }
    #endif
  }
  if (pSprite->hPrev) {
    GUI_SPRITE_OBJ * pSpritePrev;
    pSpritePrev = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(pSprite->hPrev);
    pSpritePrev->hNext = pSprite->hNext;
  }
  if (pSprite->hNext) {
    GUI_SPRITE_OBJ * pSpriteNext;
    pSpriteNext = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(pSprite->hNext);
    pSpriteNext->hPrev = pSprite->hPrev;
  }
}

/*********************************************************************
*
*       _DoColorConversion
*/
static int _DoColorConversion(GUI_SPRITE_OBJ * pSprite, const GUI_BITMAP GUI_UNI_PTR * pBM) {
  LCD_PIXELINDEX * pColors;
  int i;
  if (pSprite->hColors) {
    GUI_ALLOC_Free(pSprite->hColors);
  }
  pSprite->hColors = GUI_ALLOC_AllocZero(sizeof(LCD_PIXELINDEX) * pBM->pPal->NumEntries);
  if (pSprite->hColors == 0) {
    return 1;
  }
  pColors = (LCD_PIXELINDEX *)GUI_ALLOC_h2p(pSprite->hColors);
  for (i = 0; i < pBM->pPal->NumEntries; i++) {
    LCD_COLOR Color;
    LCD_PIXELINDEX Index;
    Color = *(pBM->pPal->pPalEntries + i);
    Index = LCD_aAPI[pSprite->pSpriteContext->Layer]->pfColor2Index(Color);
    *(pColors++) = Index;
  }
  return 0;
}

/*********************************************************************
*
*       _Delete
*/
static void _Delete(GUI_HSPRITE hSprite, GUI_SPRITE_OBJ * pSprite) {
  GUI_ALLOC_Free(pSprite->hColors); /* Remove colors from memory */
  GUI_ALLOC_Free(hSprite);          /* Remove sprite from memory */
}

/*********************************************************************
*
*       Private code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_SPRITE__CreateEx
*/
GUI_HSPRITE GUI_SPRITE__CreateEx(const GUI_BITMAP GUI_UNI_PTR * pBM, int x, int y, int Layer, U16 Flags) {
  GUI_HSPRITE      hSpriteNew; /* Handle of new sprite */
  GUI_SPRITE_OBJ * pSpriteNew; /* Pointer to new sprite object */
  SPRITE_CONTEXT * pSpriteContext;
  int AllocSize;

  if ((pBM->XSize == 0) || (pBM->YSize == 0)) {
    return 0; /* Zerosized sprites make no sense... */
  }
  if (pBM->BitsPerPixel > 8) {
    return 0; /* Only pallete based bitmaps are currently supported... */
  }
  if (pBM->pPal->pPalEntries == NULL) {
    return 0; /* Only device independent bitmaps are currently supported... */
  }
  AllocSize = sizeof(LCD_PIXELINDEX) * pBM->XSize * pBM->YSize; /* Memory area for saving background data */
  GUI_LOCK();
  /* Create sprite object */
  hSpriteNew = GUI_ALLOC_AllocZero(sizeof(GUI_SPRITE_OBJ) + AllocSize);
  if (hSpriteNew == 0) {
    GUI_UNLOCK();
    return 0; /* Allocation failed... */
  }
  pSpriteContext = &_aSpriteContext[Layer];
  /* Create and initialize object */
  pSpriteNew = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSpriteNew);
  pSpriteNew->Flags   = Flags;
  pSpriteNew->pBM     = pBM;
  pSpriteNew->Rect.x0 = x;
  pSpriteNew->Rect.y0 = y;
  pSpriteNew->Rect.x1 = pSpriteNew->Rect.x0 + pBM->XSize - 1;
  pSpriteNew->Rect.y1 = pSpriteNew->Rect.y0 + pBM->YSize - 1;
  pSpriteNew->pSpriteContext = &_aSpriteContext[Layer];
  /* Do the color conversion */
  if (_DoColorConversion(pSpriteNew, pBM)) { /* Set bitmap data */
    GUI_UNLOCK();
    return 0; /* Allocation failed... */
  };
  /* Initialize clipping rectangle for sprite drawing operations */
  if (_aSpriteContext[Layer].hFirstSprite == 0) {
    LCD_aAPI[pSpriteContext->Layer]->pfGetRect(&pSpriteContext->ClipRect);
  }
  if (Flags & GUI_SPRITE_CF_SHOW) {
    _Link(hSpriteNew, pSpriteNew); /* Put it into linked list */
    _SpriteDraw(pSpriteNew);       /* Draw it */
  }
  GUI_UNLOCK();
  return hSpriteNew;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_SPRITE_CreateEx
*/
GUI_HSPRITE GUI_SPRITE_CreateEx(const GUI_BITMAP GUI_UNI_PTR * pBM, int x, int y, int Layer) {
  return GUI_SPRITE__CreateEx(pBM, x, y, Layer, GUI_SPRITE_CF_SHOW);
}

/*********************************************************************
*
*       GUI_SPRITE_Create
*/
GUI_HSPRITE GUI_SPRITE_Create(const GUI_BITMAP GUI_UNI_PTR * pBM, int x, int y) {
  return GUI_SPRITE_CreateEx(pBM, x, y, GUI_Context.SelLayer);
}

/*********************************************************************
*
*       GUI_SPRITE_Delete
*/
void GUI_SPRITE_Delete(GUI_HSPRITE hSprite) {
  GUI_SPRITE_OBJ * pSprite;
  GUI_LOCK();
  pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
  _Undraw(pSprite);                 /* Remove from screen */
  _Unlink(hSprite, pSprite);        /* Remove from linked list */
  _Delete(hSprite, pSprite);        /* Remove from memory */
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_SPRITE_SetPosition
*/
void GUI_SPRITE_SetPosition(GUI_HSPRITE hSprite, int x, int y) {
  GUI_SPRITE_OBJ * pSprite;
  GUI_LOCK();
  pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
  _SetPosition(pSprite, x, y);
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_SPRITE_SetBitmap
*/
int GUI_SPRITE_SetBitmap(GUI_HSPRITE hSprite, const GUI_BITMAP GUI_UNI_PTR * pBM) {
  int r = 1;
  GUI_SPRITE_OBJ * pSprite;
  GUI_LOCK();
  pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
  /* Only bitmaps of the same size are supported by this function */
  if ((pSprite->pBM->XSize == pBM->XSize) && (pSprite->pBM->YSize == pBM->YSize)) {
    /* Do the color conversion */
    if (_DoColorConversion(pSprite, pBM) == 0) {
      /* Set new image */
      _SetBitmap(pSprite, pBM);
      r = 0;
    }
  }
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_SPRITE_SetBitmapAndPosition
*/
int GUI_SPRITE_SetBitmapAndPosition(GUI_HSPRITE hSprite, const GUI_BITMAP GUI_UNI_PTR * pBM, int x, int y) {
  int r = 1;
  GUI_SPRITE_OBJ * pSprite;
  GUI_LOCK();
  pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
  /* Only bitmaps of the same size are supported by this function */
  if ((pSprite->pBM->XSize == pBM->XSize) && (pSprite->pBM->YSize == pBM->YSize)) {
    /* Do the color conversion */
    if (_DoColorConversion(pSprite, pBM) == 0) {
      /* Set new image */
      _SetBitmapAndPosition(pSprite, pBM, x - pSprite->Rect.x0, y - pSprite->Rect.y0);
      r = 0;
    }
  }
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_SPRITE_Hide
*/
void GUI_SPRITE_Hide(GUI_HSPRITE hSprite) {
  GUI_SPRITE_OBJ * pSprite;
  if (hSprite == 0) {
    return;
  }
  GUI_LOCK();
  pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
  if ((pSprite->Flags & GUI_SPRITE_CF_SHOW) != 0) {
    _Undraw(pSprite);          /* Remove from screen */
    _Unlink(hSprite, pSprite); /* Remove from linked list */
    pSprite->Flags &= ~GUI_SPRITE_CF_SHOW;
  }
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_SPRITE_Show
*/
void GUI_SPRITE_Show(GUI_HSPRITE hSprite) {
  GUI_SPRITE_OBJ * pSprite;
  if (hSprite == 0) {
    return;
  }
  GUI_LOCK();
  pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
  if ((pSprite->Flags & GUI_SPRITE_CF_SHOW) == 0) {
    _Link(hSprite, pSprite);   /* Put it into linked list */
    _SpriteDraw(pSprite);      /* Draw it */
    pSprite->Flags |= GUI_SPRITE_CF_SHOW;
  }
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_SPRITE_GetState
*/
int GUI_SPRITE_GetState(GUI_HSPRITE hSprite) {
  int r;
  GUI_SPRITE_OBJ * pSprite;
  if (hSprite == 0) {
    return 0;
  }
  GUI_LOCK();
  pSprite = (GUI_SPRITE_OBJ *)GUI_ALLOC_h2p(hSprite);
  r = (pSprite->Flags & GUI_SPRITE_CF_SHOW) ? 1 : 0;
  GUI_UNLOCK();
  return r;
}

#endif

/*************************** End of file ****************************/
