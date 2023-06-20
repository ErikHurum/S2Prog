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
File        : TREEVIEW.c
Purpose     : Implementation of treeview widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "TREEVIEW_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/
/* Define default fonts */
#ifndef   TREEVIEW_FONT_DEFAULT
  #if   WIDGET_USE_SCHEME_SMALL
    #define TREEVIEW_FONT_DEFAULT &GUI_Font13_1
  #elif WIDGET_USE_SCHEME_MEDIUM
    #define TREEVIEW_FONT_DEFAULT &GUI_Font16_1
  #elif WIDGET_USE_SCHEME_LARGE
    #define TREEVIEW_FONT_DEFAULT &GUI_Font24_1
  #endif
#endif

/* Define colors */
#ifndef   TREEVIEW_BKCOLOR0_DEFAULT
  #define TREEVIEW_BKCOLOR0_DEFAULT GUI_WHITE               /* Not selected */
#endif

#ifndef   TREEVIEW_BKCOLOR1_DEFAULT
  #define TREEVIEW_BKCOLOR1_DEFAULT GUI_BLUE                /* Selected */
#endif

#ifndef   TREEVIEW_BKCOLOR2_DEFAULT
  #define TREEVIEW_BKCOLOR2_DEFAULT 0xC0C0C0                /* Disabled */
#endif

#ifndef   TREEVIEW_TEXTCOLOR0_DEFAULT
  #define TREEVIEW_TEXTCOLOR0_DEFAULT GUI_BLACK             /* Not selected */
#endif

#ifndef   TREEVIEW_TEXTCOLOR1_DEFAULT
  #define TREEVIEW_TEXTCOLOR1_DEFAULT GUI_WHITE             /* Selected */
#endif

#ifndef   TREEVIEW_TEXTCOLOR2_DEFAULT
  #define TREEVIEW_TEXTCOLOR2_DEFAULT GUI_GRAY              /* Disabled */
#endif

#ifndef   TREEVIEW_LINECOLOR0_DEFAULT
  #define TREEVIEW_LINECOLOR0_DEFAULT GUI_BLACK             /* Not selected */
#endif

#ifndef   TREEVIEW_LINECOLOR1_DEFAULT
  #define TREEVIEW_LINECOLOR1_DEFAULT GUI_WHITE             /* Selected */
#endif

#ifndef   TREEVIEW_LINECOLOR2_DEFAULT
  #define TREEVIEW_LINECOLOR2_DEFAULT GUI_GRAY              /* Disabled */
#endif

#ifndef   TREEVIEW_FOCUSCOLOR_DEFAULT
  #define TREEVIEW_FOCUSCOLOR_DEFAULT GUI_WHITE             /* Focus rectangle */
#endif

/* Define default images */
#ifndef   TREEVIEW_IMAGE_PLUS_DEFAULT
  #define TREEVIEW_IMAGE_PLUS_DEFAULT &TREEVIEW__bmPlus     /* Plus sign */
#endif

#ifndef   TREEVIEW_IMAGE_MINUS_DEFAULT
  #define TREEVIEW_IMAGE_MINUS_DEFAULT &TREEVIEW__bmMinus   /* Minus sign */
#endif

#ifndef   TREEVIEW_IMAGE_CLOSED_DEFAULT
  #define TREEVIEW_IMAGE_CLOSED_DEFAULT &TREEVIEW__bmClosed /* Closed image */
#endif

#ifndef   TREEVIEW_IMAGE_OPEN_DEFAULT
  #define TREEVIEW_IMAGE_OPEN_DEFAULT &TREEVIEW__bmOpen     /* Open image */
#endif

#ifndef   TREEVIEW_IMAGE_LEAF_DEFAULT
  #define TREEVIEW_IMAGE_LEAF_DEFAULT &TREEVIEW__bmLeaf     /* Leaf image */
#endif

#ifndef   TREEVIEW_INDENT_DEFAULT
  #define TREEVIEW_INDENT_DEFAULT 16                        /* Item indent value */
#endif

#ifndef   TREEVIEW_TEXT_INDENT_DEFAULT
  #define TREEVIEW_TEXT_INDENT_DEFAULT 20                   /* Text indent value */
#endif

#ifndef   TREEVIEW_MIN_ITEM_HEIGHT_DEFAULT
  #define TREEVIEW_MIN_ITEM_HEIGHT_DEFAULT 16               /* Minimum item height */
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
TREEVIEW_PROPS TREEVIEW__DefaultProps = {
  TREEVIEW_FONT_DEFAULT,
  TREEVIEW_BKCOLOR0_DEFAULT,
  TREEVIEW_BKCOLOR1_DEFAULT,
  TREEVIEW_BKCOLOR2_DEFAULT,
  TREEVIEW_TEXTCOLOR0_DEFAULT,
  TREEVIEW_TEXTCOLOR1_DEFAULT,
  TREEVIEW_TEXTCOLOR2_DEFAULT,
  TREEVIEW_LINECOLOR0_DEFAULT,
  TREEVIEW_LINECOLOR1_DEFAULT,
  TREEVIEW_LINECOLOR2_DEFAULT,
  TREEVIEW_FOCUSCOLOR_DEFAULT,
  TREEVIEW_IMAGE_CLOSED_DEFAULT,
  TREEVIEW_IMAGE_OPEN_DEFAULT,
  TREEVIEW_IMAGE_LEAF_DEFAULT,
  TREEVIEW_IMAGE_PLUS_DEFAULT,
  TREEVIEW_IMAGE_MINUS_DEFAULT,
  TREEVIEW_INDENT_DEFAULT,
  TREEVIEW_TEXT_INDENT_DEFAULT,
  TREEVIEW_MIN_ITEM_HEIGHT_DEFAULT,
};

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       Private routines
*
**********************************************************************
*/
/*********************************************************************
*
*       TREEVIEW_h2p
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
TREEVIEW_OBJ * TREEVIEW_h2p(TREEVIEW_Handle h) {
  TREEVIEW_OBJ * p = (TREEVIEW_OBJ *)GUI_ALLOC_h2p(h);
  if (p) {
    if (p->DebugId != TREEVIEW_ID) {
      GUI_DEBUG_ERROROUT("TREEVIEW.c: Wrong handle type or Object not init'ed");
      return 0;
    }
  }
  return p;
}
#endif

/*********************************************************************
*
*       _GetBitmapPointer
*/
static const GUI_BITMAP ** _GetBitmapPointer(const TREEVIEW_OBJ * pObj, TREEVIEW_ITEM_OBJ * pItem) {
  const GUI_BITMAP ** apBm;
  if (pItem->hData) {
    TREEVIEW_ITEM_DATA * pItemData;
    pItemData = (TREEVIEW_ITEM_DATA *)GUI_ALLOC_h2p(pItem->hData);
    apBm       = pItemData->apBm;
  } else {
    apBm       = (const GUI_BITMAP **)&pObj->Props.apBm;
  }
  return apBm;
}

/*********************************************************************
*
*       _GetBitmap
*/
static const GUI_BITMAP GUI_UNI_PTR * _GetBitmap(const TREEVIEW_OBJ * pObj, const GUI_BITMAP GUI_UNI_PTR ** apBm, int Index) {
  const GUI_BITMAP GUI_UNI_PTR * pBm;
  if ((Index == TREEVIEW_BI_PLUS) || (Index == TREEVIEW_BI_MINUS)) {
    pBm = pObj->Props.apBm[Index];
  } else {
    if (apBm[Index]) {
      pBm = apBm[Index];
    } else {
      pBm = pObj->Props.apBm[Index];
    }
  }
  return pBm;
}

/*********************************************************************
*
*       _GetItemBitmapSizeY
*/
static int _GetItemBitmapSizeY(const TREEVIEW_OBJ * pObj, TREEVIEW_ITEM_OBJ * pItem) {
  int BitmapSizeItem;
  int BitmapSizeButton;
  const GUI_BITMAP GUI_UNI_PTR ** apBm;
  const GUI_BITMAP GUI_UNI_PTR  *  pBm;
  apBm = _GetBitmapPointer(pObj, pItem);
  if (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) {
    int IndexItem;
    BitmapSizeItem = 0;
    if (pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) {
      IndexItem   = TREEVIEW_BI_OPEN;
    } else {
      IndexItem   = TREEVIEW_BI_CLOSED;
    }
    pBm = _GetBitmap(pObj, apBm, IndexItem);
    BitmapSizeButton = pBm->YSize;
  } else {
    BitmapSizeButton = 0;
    pBm = _GetBitmap(pObj, apBm, TREEVIEW_BI_LEAF);
    BitmapSizeItem = pBm->YSize;
  }
  return (BitmapSizeButton > BitmapSizeItem) ? BitmapSizeButton : BitmapSizeItem;
}

/*********************************************************************
*
*       _CallOwnerDraw
*/
static int _CallOwnerDraw(TREEVIEW_Handle hObj, const TREEVIEW_OBJ * pObj, TREEVIEW_ITEM_Handle hItem, int Cmd) {
  WIDGET_ITEM_DRAW_INFO ItemInfo;
  int r;
  ItemInfo.Cmd       = Cmd;
  ItemInfo.hWin      = hObj;
  ItemInfo.p         = (void *)&hItem;
  if (pObj->pfDrawItem) {
    r = pObj->pfDrawItem(&ItemInfo);
  }
  return r;
}

/*********************************************************************
*
*       _SkipClosedItems
*
* Purpose:
*   Returns the next visible item
*/
static TREEVIEW_ITEM_Handle _SkipClosedItems(TREEVIEW_ITEM_OBJ * pItem) {
  TREEVIEW_ITEM_Handle hItem;
  if (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) {
    if ((pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) == 0) {
      int Level;
      Level = pItem->Level;
      do {
        hItem = pItem->hNext;
        if (hItem) {
          pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
          if (pItem->Level <= Level) {
            break;
          }
        }
      } while (hItem);
    } else {
      hItem = pItem->hNext;
    }
  } else {
    hItem = pItem->hNext;
  }
  return hItem;
}

/*********************************************************************
*
*       _ConnectLines
*
* Purpose:
*   Makes a 'connection' between the given item and the previous
*   item of the same level.
*/
static void _ConnectLines(TREEVIEW_ITEM_OBJ * pItem, TREEVIEW_ITEM_OBJ * apIndent[], int OldLevel, int Level) {
  TREEVIEW_ITEM_Handle hItem;
  TREEVIEW_ITEM_OBJ * pIndent;
  U16 Mask;
  do {
    pIndent = apIndent[OldLevel];
    if (pIndent) {
      pIndent->Flags |= TREEVIEW_ITEM_STATE_ISLAST;
    }
  } while (--OldLevel > Level);
  Level = pItem->Level;
  Mask  = 1 << (Level - 1);
  while ((hItem = pItem->hPrev) != 0) {
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    if (pItem->Level > Level) {
      pItem->Connectors |= Mask;
    } else {
      break;
    }
  }
}

/*********************************************************************
*
*       _CalcParams
*
* Purpose:
*   Calculates the following things:
*   1. Number of visible items
*   2. Maximum size of visible items in x
*   3. Required size in y for all visible items
*   4. Connectors between items
*/
static void _CalcParams(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj) {
  TREEVIEW_ITEM_Handle hItem;
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_OBJ  * pItemOld;
  TREEVIEW_ITEM_OBJ  * apIndent[16] = {0};
  int Level, OldLevel;
  pObj->xSizeItems  = 0;
  pObj->ySizeItems  = 0;
  pObj->NumVisItems = 0;
  OldLevel = Level = -1;
  pItemOld = NULL;
  hItem = pObj->hFirst;
  while (hItem) {
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    pItem->Connectors = 0;
    Level = pItem->Level;
    apIndent[Level] = pItem;
    pItem->Flags &= ~TREEVIEW_ITEM_STATE_ISLAST;
    if (pObj->xSizeItems < pItem->xSize) {
      pObj->xSizeItems = pItem->xSize;
    }
    if (Level < OldLevel) {
      _ConnectLines(pItem, apIndent, OldLevel, Level);
    }
    pObj->ySizeItems += _CallOwnerDraw(hObj, pObj, hItem, WIDGET_ITEM_GET_YSIZE);
    pObj->NumVisItems++;
    OldLevel = Level;
    pItemOld = pItem;
    hItem    = _SkipClosedItems(pItem);
  }
  if (pItemOld) {
    _ConnectLines(pItem, apIndent, OldLevel, 0);
  }
}

/*********************************************************************
*
*       _GetNumVisItems
*
* Purpose:
*   Returns the number of fully or partially visible items
*/
static unsigned _GetNumVisItems(const TREEVIEW_OBJ * pObj, TREEVIEW_Handle hObj) {
  int NumItems, r = 0;
  NumItems = pObj->NumVisItems;
  if (NumItems > 1) {
    int ySize, DistY = 0;
    TREEVIEW_ITEM_Handle hItem;
    TREEVIEW_ITEM_OBJ  * pItem;
    GUI_RECT Rect;
    WM_GetInsideRectExScrollbar(hObj, &Rect);
    ySize = Rect.y1 - Rect.y0 + 1;
    hItem = pObj->hFirst;
    while (hItem) {
      r++;
      pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
      DistY += _CallOwnerDraw(hObj, pObj, hItem, WIDGET_ITEM_GET_YSIZE);
      /* Skip closed items */
      hItem = _SkipClosedItems(pItem);
      if (DistY >= ySize) {
        break;
      }
    }
  }
  return r;
}

/*********************************************************************
*
*       _ManageAutoScroll
*/
static void _ManageAutoScroll(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj) {
  GUI_RECT Rect;
  int IsRequiredV;
  int IsRequiredH;
  static int IsActive;
  if (IsActive == 0) {
    IsActive = 1;
    WM_GetInsideRectExScrollbar(hObj, &Rect);
    /*
    * Manage vertical scroll bar
    */
    IsRequiredV = (pObj->ySizeItems > (Rect.y1 - Rect.y0 + 1)) ? 1 : 0;
    if (IsRequiredV) {
      pObj->ScrollStateV.NumItems = pObj->NumVisItems + 1;
      pObj->ScrollStateV.PageSize = _GetNumVisItems(pObj, hObj);
    } else {
      pObj->ScrollStateV.v = 0;
    }
    if (pObj->Flags & TREEVIEW_SF_AUTOSCROLLBAR_V) {
      WM_SetScrollbarV(hObj, IsRequiredV);
    } else {
      WM_HWIN hWin;
      hWin = WM_GetScrollbarV(hObj);
      if (hWin) {
        if (IsRequiredV == 0) {
          pObj->ScrollStateV.NumItems = 1;
          pObj->ScrollStateV.PageSize = 1;
          IsRequiredV                 = 1;
        }
      }
    }
    /*
    * Manage horizontal scroll bar
    */
    IsRequiredH = (pObj->xSizeItems > (Rect.x1 - Rect.x0 + 1)) ? 1 : 0;
    if (IsRequiredH) {
      pObj->ScrollStateH.NumItems = pObj->xSizeItems;
      pObj->ScrollStateH.PageSize = Rect.x1 - Rect.x0 + 1;
    } else {
      pObj->ScrollStateH.v = 0;
    }
    if (pObj->Flags & TREEVIEW_SF_AUTOSCROLLBAR_H) {
      WM_SetScrollbarH(hObj, IsRequiredH);
    } else {
      WM_HWIN hWin;
      hWin = WM_GetScrollbarH(hObj);
      if (hWin) {
        if (IsRequiredH == 0) {
          pObj->ScrollStateH.NumItems = 1;
          pObj->ScrollStateH.PageSize = 1;
          IsRequiredH                 = 1;
        }
      }
    }
    /*
    * Set scroll state
    */
    if (IsRequiredV || IsRequiredH) {
      WIDGET__SetScrollState(hObj, &pObj->ScrollStateV, &pObj->ScrollStateH);
    }
  }
  IsActive = 0;
}

/*********************************************************************
*
*       _OnPaint
*/
static void _OnPaint(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj, WM_MESSAGE * pMsg) {
  TREEVIEW_ITEM_Handle hItem;
  TREEVIEW_ITEM_OBJ  * pItem;
  WIDGET_ITEM_DRAW_INFO ItemInfo;
  GUI_RECT RectInside, RectItem, ClipRect;
  int i;
  int xSize;
  GUI_SetFont(pObj->Props.pFont);
  /* Calculate clipping rectangle */
  ClipRect = *(const GUI_RECT*)pMsg->Data.p;
  GUI_MoveRect(&ClipRect, -pObj->Widget.Win.Rect.x0, -pObj->Widget.Win.Rect.y0);
  WM_GetInsideRectExScrollbar(hObj, &RectInside);
  GUI__IntersectRect(&ClipRect, &RectInside);
  xSize = RectInside.x1 - RectInside.x0 + 1;
  if (xSize < pObj->xSizeItems) {
    xSize = pObj->xSizeItems;
  }
  RectItem.x0 = ClipRect.x0;
  RectItem.x1 = ClipRect.x1;
  /* Fill item info structure */
  ItemInfo.Cmd  = WIDGET_ITEM_DRAW;
  ItemInfo.hWin = hObj;
  ItemInfo.x0   = RectInside.x0 - pObj->ScrollStateH.v;
  ItemInfo.y0   = RectInside.y0;
  ItemInfo.x1   = ItemInfo.x0 + xSize;
  hItem = pObj->hFirst;
  /* Goto scroll position */
  i = pObj->ScrollStateV.v;
  while (i--) {
    if (!hItem) {
      break;
    }
    /* Skip closed items */
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    hItem = _SkipClosedItems(pItem);
  }
  /* Do the drawing */
  while (hItem) {
    int ItemDistY;
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    RectItem.y0 = ItemInfo.y0;
    /* Break when all other rows are outside the drawing area */
    if (RectItem.y0 > ClipRect.y1) {
      break;
    }
    ItemDistY = _CallOwnerDraw(hObj, pObj, hItem, WIDGET_ITEM_GET_YSIZE);
    RectItem.y1 = RectItem.y0 + ItemDistY - 1;
    /* Make sure that we draw only when row is in drawing area */
    if (RectItem.y1 >= ClipRect.y0) {
      /* Set user clip rect */
      WM_SetUserClipArea(&RectItem);
      /* Fill item info structure */
      ItemInfo.p = (TREEVIEW_ITEM_Handle *)&hItem;
      ItemInfo.y1  = ItemInfo.y0 + ItemDistY - 1;
      /* Draw item */
      if (pObj->pfDrawItem) {
        pObj->pfDrawItem(&ItemInfo);
      }
    }
    ItemInfo.y0 += ItemDistY;
    /* Skip closed items */
    hItem = _SkipClosedItems(pItem);
  }
  WM_SetUserClipArea(NULL);
  /* Calculate & clear 'data free' area */
  #if WM_SUPPORT_TRANSPARENCY
  if (!WM_GetHasTrans(hObj)) {
  #else
  {
  #endif
    RectItem.y0 = ItemInfo.y0;
    RectItem.y1 = RectInside.y1;
    LCD_SetBkColor(GUI_WHITE);
    GUI_ClearRectEx(&RectItem);
  }
  WIDGET__EFFECT_DrawDown(&pObj->Widget);
}

/*********************************************************************
*
*       _GetItemFromPos
*/
static TREEVIEW_ITEM_Handle _GetItemFromPos(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj, int y) {
  TREEVIEW_ITEM_Handle hItem;
  TREEVIEW_ITEM_OBJ  * pItem;
  int i, yPos;
  hItem = pObj->hFirst;
  /* 
  * Goto scroll position
  */
  i = pObj->ScrollStateV.v;
  while (i--) {
    if (!hItem) {
      break;
    }
    /*
    * Skip closed items
    */
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    hItem = _SkipClosedItems(pItem);
  }
  yPos = 0;
  while (hItem) {
    int ItemDistY;
    pItem     = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    ItemDistY = _CallOwnerDraw(hObj, pObj, hItem, WIDGET_ITEM_GET_YSIZE);
    if ((yPos <= y) && ((yPos + ItemDistY) >= y)) {
      return hItem;
    }
    yPos += ItemDistY;
    /*
    * Skip closed items
    */
    hItem = _SkipClosedItems(pItem);
  }
  return 0;
}

/*********************************************************************
*
*       _ExpandItem
*/
static void _ExpandItem(TREEVIEW_ITEM_OBJ * pItem) {
  if ((pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) && ((pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) == 0)) {
    pItem->Flags |= TREEVIEW_ITEM_STATE_EXPANDED;
    if (pItem->hParent) {
      TREEVIEW_OBJ * pObj;
      pObj = TREEVIEW_H2P(pItem->hParent);
      _CalcParams(pItem->hParent, pObj);
      _ManageAutoScroll(pItem->hParent, pObj);
      WM_InvalidateWindow(pItem->hParent);
    }
  }
}

/*********************************************************************
*
*       _CollapseItem
*/
static void _CollapseItem(TREEVIEW_ITEM_OBJ * pItem) {
  if ((pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) && (pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED)) {
    pItem->Flags &= ~TREEVIEW_ITEM_STATE_EXPANDED;
    if (pItem->hParent) {
      TREEVIEW_OBJ * pObj;
      pObj = TREEVIEW_H2P(pItem->hParent);
      _CalcParams(pItem->hParent, pObj);
      _ManageAutoScroll(pItem->hParent, pObj);
      WM_InvalidateWindow(pItem->hParent);
    }
  }
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj, WM_MESSAGE * pMsg) {
  const GUI_PID_STATE * pState = (const GUI_PID_STATE *)pMsg->Data.p;
  if (pState) {  /* Something happened in our area (pressed or released) */
    TREEVIEW_ITEM_Handle hItem;
    TREEVIEW_ITEM_OBJ  * pItem;
    if (pState->Pressed) {
      if (!WM_HasCaptured(hObj)) {
        WM_SetCapture(hObj, 1);
        hItem = _GetItemFromPos(hObj, pObj, pState->y);
        if (hItem) {
          int x0_Button, x1_Button;
          pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
          x0_Button = (pItem->Level + 0) * pObj->Props.Indent;
          x1_Button = x0_Button + pObj->Props.Indent - 1;
          /*
          * Check if +/- button has been pressed
          */
          if ((pState->x >= x0_Button) && (pState->x <= x1_Button) && (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE)) {
            /*
            * Open/close node when clicking on '+' or '-'
            */
            if (pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) {
              _CollapseItem(pItem);
            } else {
              _ExpandItem(pItem);
            }
          } else {
            int x0_Row, x1_Row;
            if (pObj->Flags & TREEVIEW_CF_ROWSELECT) {
              GUI_RECT Rect;
              WM_GetInsideRectExScrollbar(hObj, &Rect);
              x0_Row = Rect.x0;
              x1_Row = Rect.x1;
            } else {
              x0_Row = (pItem->Level + 1) * pObj->Props.Indent;
              x1_Row = x0_Row + pObj->Props.TextIndent + GUI_GetStringDistX(pItem->acText);
            }
            if ((pState->x >= x0_Row) && (pState->x <= x1_Row)) {
              if (pObj->hTimer) {
                /*
                * Double click
                */
                if (pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) {
                  _CollapseItem(pItem);
                } else {
                  _ExpandItem(pItem);
                }
              } else {
                /*
                * Change selection when clicking on text or bitmap
                */
                pObj->hSel = hItem;
                WM_InvalidateWindow(hObj);
                /*
                * Start timer to be able to manage doubleclick
                */
                pObj->hTimer = WM_CreateTimer(hObj, 0, 300, 0);
              }
            }
          }
        }
      }
      WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
    } else {
      WM_NotifyParent(hObj, WM_NOTIFICATION_RELEASED);
    }
  } else {     /* Mouse moved out */
    WM_NotifyParent(hObj, WM_NOTIFICATION_MOVED_OUT);
  }
}

/*********************************************************************
*
*       _OnOwnerdraw_GetXSize
*
* Purpose:
*   Returns the xSize of the requested item
*/
static int _OnOwnerdraw_GetXSize(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  TREEVIEW_ITEM_OBJ  * pItem;
  pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(*(TREEVIEW_ITEM_Handle *)pDrawItemInfo->p);
  return pItem->xSize;
}

/*********************************************************************
*
*       _OnOwnerdraw_GetYSize
*
* Purpose:
*   Returns the ySize of the requested item
*/
static int _OnOwnerdraw_GetYSize(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  TREEVIEW_Handle      hObj;
  const TREEVIEW_OBJ * pObj;
  TREEVIEW_ITEM_OBJ  * pItem;
  int                  FontSizeY;
  int                  BitmapSizeY;
  int                  SizeY;
  hObj     = pDrawItemInfo->hWin;
  pObj     = TREEVIEW_H2P(hObj);
  pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(*(TREEVIEW_ITEM_Handle *)pDrawItemInfo->p);
  if (pItem->ySize) {
    return pItem->ySize;
  }
  FontSizeY   = pObj->Props.pFont->YSize;
  BitmapSizeY = _GetItemBitmapSizeY(pObj, pItem);
  SizeY       = (BitmapSizeY > FontSizeY) ? BitmapSizeY : FontSizeY;
  return (pObj->Props.MinItemHeight > SizeY) ? pObj->Props.MinItemHeight : SizeY;
}

/*********************************************************************
*
*       _OnOwnerdraw_Paint
*
* Purpose:
*   Draws the requested item
*/
static int _OnOwnerdraw_Paint(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  TREEVIEW_Handle      hObj;
  const TREEVIEW_OBJ * pObj;
  TREEVIEW_ITEM_Handle hItem;
  TREEVIEW_ITEM_OBJ  * pItem;
  const GUI_BITMAP GUI_UNI_PTR  ** apBm;
  const GUI_BITMAP GUI_UNI_PTR   * pBm;
  GUI_RECT rText, rFill;
  int xPos, xMid, yMid, xEnd;
  int xSizeBm, ySizeBm;
  int Index, Index0, Index1;
  int FontHeight;
  int HasChild;
  U16 Connectors;
  hObj       = pDrawItemInfo->hWin;
  pObj       = TREEVIEW_H2P(hObj);
  hItem      = *(TREEVIEW_ITEM_Handle *)pDrawItemInfo->p;
  pItem      = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
  /*
  * Draw background on left side
  */
  if (pObj->Flags & TREEVIEW_CF_ROWSELECT) {
    if (WM__IsEnabled(hObj)) {
      if (pObj->Flags & TREEVIEW_CF_ROWSELECT) {
        if (pObj->hSel == hItem) {
          Index = TREEVIEW_CI_SEL;
        } else {
          Index = TREEVIEW_CI_UNSEL;
        }
      } else {
        Index = TREEVIEW_CI_UNSEL;
      }
    } else {
      Index = TREEVIEW_CI_DISABLED;
    }
    rFill.x0   = pDrawItemInfo->x0;
    rFill.y0   = pDrawItemInfo->y0;
    rFill.x1   = pDrawItemInfo->x0 + (pItem->Level + 1) * pObj->Props.Indent + pObj->Props.TextIndent - 1;
    rFill.y1   = pDrawItemInfo->y1;
    GUI_SetColor(pObj->Props.aBkColor[Index]);
    GUI_FillRectEx(&rFill);
  }
  /*
  * Draw item text
  */
  if (WM__IsEnabled(hObj)) {
    if (pObj->hSel == hItem) {
      Index = TREEVIEW_CI_SEL;
    } else {
      Index = TREEVIEW_CI_UNSEL;
    }
  } else {
    Index = TREEVIEW_CI_DISABLED;
  }
  GUI_SetFont(pObj->Props.pFont);
  FontHeight = GUI_GetFontSizeY();
  if (pObj->Flags & TREEVIEW_CF_ROWSELECT) {
    rFill.x0   = pDrawItemInfo->x0 + (pItem->Level + 1) * pObj->Props.Indent + pObj->Props.TextIndent;
  } else {
    rFill.x0   = pDrawItemInfo->x0;
  }
  rFill.y0   = pDrawItemInfo->y0;
  rFill.x1   = pDrawItemInfo->x1;
  rFill.y1   = pDrawItemInfo->y1;
  rText.x0   = pDrawItemInfo->x0 + (pItem->Level + 1) * pObj->Props.Indent + pObj->Props.TextIndent;
  rText.x1   = rText.x0 + GUI_GetStringDistX(pItem->acText) - 1;
  rText.y0   = pDrawItemInfo->y0 + (pDrawItemInfo->y1 - pDrawItemInfo->y0 + 1 - FontHeight) / 2;
  rText.y1   = rText.y0 + FontHeight - 1;
  GUI_SetColor(pObj->Props.aTextColor[Index]);
  GUI_SetBkColor(pObj->Props.aBkColor[Index]);
  GUI_DispStringInRectEx(pItem->acText, &rText, 0, strlen(pItem->acText), 0);
  /*
  * Draw background
  */
  if (WM__IsEnabled(hObj)) {
    if (pObj->Flags & TREEVIEW_CF_ROWSELECT) {
      if (pObj->hSel == hItem) {
        Index = TREEVIEW_CI_SEL;
      } else {
        Index = TREEVIEW_CI_UNSEL;
      }
    } else {
      Index = TREEVIEW_CI_UNSEL;
    }
  } else {
    Index = TREEVIEW_CI_DISABLED;
  }
  GUI_SetBkColor(pObj->Props.aBkColor[Index]);
  GUI_ClearRect(rFill.x0,      rFill.y0,      rFill.x1,      rText.y0 - 1); /* Top */
  GUI_ClearRect(rFill.x0,      rText.y0,      rText.x0 - 1 , rText.y1);     /* Left */
  GUI_ClearRect(rText.x1 + 1,  rText.y0,      rFill.x1,      rText.y1);     /* Right */
  GUI_ClearRect(rFill.x0,      rText.y1 + 1,  rFill.x1,      rFill.y1);     /* Bottom */
  /*
  * Check if item has childs
  */
  HasChild = 0;
  if (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) {
    if (pItem->hNext) {
      TREEVIEW_ITEM_OBJ  * pNext;
      pNext = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(pItem->hNext);
      if (pNext->Level > pItem->Level) {
        HasChild = 1;
      }
    }
  }
  /*
  * Draw lines
  */
  if ((pObj->Flags & TREEVIEW_CF_HIDELINES) == 0) {
    if (WM__IsEnabled(hObj)) {
      if (pObj->Flags & TREEVIEW_CF_ROWSELECT) {
        if (pObj->hSel == hItem) {
          Index = TREEVIEW_CI_SEL;
        } else {
          Index = TREEVIEW_CI_UNSEL;
        }
      } else {
        Index = TREEVIEW_CI_UNSEL;
      }
    } else {
      Index = TREEVIEW_CI_DISABLED;
    }
    GUI_SetColor(pObj->Props.aLineColor[Index]);
    xEnd = pDrawItemInfo->x0 + pItem->Level * pObj->Props.Indent - 1;
    xMid = xEnd - pObj->Props.Indent / 2;
    yMid = (pDrawItemInfo->y1 + pDrawItemInfo->y0) / 2;
    if (pItem->Level >= 1) {
      /* Draw vertical line */
      if (pItem->Flags & TREEVIEW_ITEM_STATE_ISLAST) {
        GUI_DrawVLine(xMid, pDrawItemInfo->y0, yMid);
      } else {
        GUI_DrawVLine(xMid, pDrawItemInfo->y0, pDrawItemInfo->y1);
      }
      if (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) {
        xEnd += pObj->Props.Indent / 2;
        if (HasChild) {
          if ((pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) && HasChild) {
            GUI_DrawVLine(xEnd, yMid, pDrawItemInfo->y1);
          }
        } else {
          xEnd += pObj->Props.Indent / 2;
        }
      } else {
        xEnd += (pObj->Props.Indent + pObj->Props.Indent + pObj->Props.Indent) >> 1; /* Avoid multiplication */
      }
      /* Draw vertical line */
      GUI_DrawHLine(yMid, xMid, xEnd);
      /* Vertical connectors */
      Connectors = pItem->Connectors;
      xMid = pDrawItemInfo->x0 + pObj->Props.Indent / 2 - 1;
      while (Connectors) {
        if (Connectors & 1) {
          GUI_DrawVLine(xMid, pDrawItemInfo->y0, pDrawItemInfo->y1);
        }
        Connectors >>= 1;
        xMid += pObj->Props.Indent;
      }
    } else {
      if (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) {
        xEnd += pObj->Props.Indent / 2;
        if ((pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) && HasChild) {
          GUI_DrawVLine(xEnd, yMid, pDrawItemInfo->y1);
        }
      }
    }
  }
  /*
  * Draw bitmaps
  */
  xPos = pDrawItemInfo->x0 + pItem->Level * pObj->Props.Indent - 1;
  apBm  = _GetBitmapPointer(pObj, pItem);
  if (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) {
    if ((pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) && HasChild) {
      Index0 = TREEVIEW_BI_MINUS;
      Index1 = TREEVIEW_BI_OPEN;
    } else {
      Index0 = TREEVIEW_BI_PLUS;
      Index1 = TREEVIEW_BI_CLOSED;
    }
    /*
    * Plus/minus bitmap
    */
    if (HasChild) {
      pBm = _GetBitmap(pObj, apBm, Index0);
      xSizeBm = pBm->XSize;
      ySizeBm = pBm->YSize;
      GUI_DrawBitmap(pBm,
                     xPos + (pObj->Props.Indent - xSizeBm) / 2,
                     pDrawItemInfo->y0 + ((pDrawItemInfo->y1 - pDrawItemInfo->y0) - ySizeBm) / 2);
    }
    /*
    * Node bitmap
    */
    pBm = _GetBitmap(pObj, apBm, Index1);
    xSizeBm = pBm->XSize;
    ySizeBm = pBm->YSize;
    GUI_DrawBitmap(pBm,
                   xPos + pObj->Props.Indent + (pObj->Props.Indent - xSizeBm) / 2,
                   pDrawItemInfo->y0 + ((pDrawItemInfo->y1 - pDrawItemInfo->y0) - ySizeBm) / 2);
  } else {
    /*
    * Leaf bitmap
    */
    pBm = _GetBitmap(pObj, apBm, TREEVIEW_BI_LEAF);
    xSizeBm = pBm->XSize;
    ySizeBm = pBm->YSize;
    GUI_DrawBitmap(pBm,
                   xPos + pObj->Props.Indent + (pObj->Props.Indent - xSizeBm) / 2,
                   pDrawItemInfo->y0 + ((pDrawItemInfo->y1 - pDrawItemInfo->y0) - ySizeBm) / 2);
  }
  return 0;
}

/*********************************************************************
*
*       _IncSel
* Purpose:
*   Simply moves the selection to the next item without any check
*/
static void _IncSel(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj) {
  TREEVIEW_ITEM_Handle hItem;
  TREEVIEW_ITEM_OBJ  * pItem;
  hItem = pObj->hSel;
  pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
  if (pItem->hNext) {
    pObj->hSel = pItem->hNext;
    WM_InvalidateWindow(hObj);
  }
}

/*********************************************************************
*
*       _GetPrevVisibleItem
*
* Purpose:
*   Returns the previous visible item. Used by moving the cursor 'UP'.
*   If there is no previous item it returns the given item.
*/
static TREEVIEW_ITEM_Handle _GetPrevVisibleItem(TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_Handle hItemNew;
  TREEVIEW_ITEM_Handle hItemOld;
  int Level;
  hItemNew = 0;
  hItemOld = hItem;
  pItem    = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
  Level    = pItem->Level;
  do {
    hItem = pItem->hPrev;
    if (hItem) {
      pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
      if (hItemNew == 0) {
        hItemNew = hItem;
        Level    = pItem->Level;
      }
      if (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) {
        if (pItem->Level < Level) {
          if ((pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) == 0) {
            hItemNew = hItem;
          }
          Level = pItem->Level;
        }
      }
    }
  } while (hItem);
  return hItemNew ? hItemNew : hItemOld;
}

/*********************************************************************
*
*       _GetNextVisibleItem
*
* Purpose:
*   Returns the next visible item (node or leaf). Used by moving the cursor 'DOWN'.
*   If there is no previous item it returns the given item.
*/
static TREEVIEW_ITEM_Handle _GetNextVisibleItem(TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_Handle hItemNew;
  TREEVIEW_ITEM_Handle hItemOld;
  int Level;
  hItemNew = 0;
  hItemOld = hItem;
  pItem    = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
  if ((pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) == 0) {
    Level = pItem->Level;
    do {
      hItem = pItem->hNext;
      if (hItem) {
        pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
        if (pItem->Level <= Level) {
          hItemNew = hItem;
          break;
        }
      }
    } while (hItem);
  } else {
    hItemNew = pItem->hNext;
  }
  return hItemNew ? hItemNew : hItemOld;
}

/*********************************************************************
*
*       _GetPrevVisibleNode
*
* Purpose:
*   Returns the previous visible node. Used by moving the cursor 'LEFT'
*   if the current selection is a leaf.
*   If there is no previous node it returns the given item.
*/
static TREEVIEW_ITEM_Handle _GetPrevVisibleNode(TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_Handle hItemNew;
  do {
    hItemNew = hItem;
    hItem    = _GetPrevVisibleItem(hItem);
    pItem    = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    if (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) {
      return hItem;
    }
  } while (hItem != hItemNew);
  return hItem;
}

/*********************************************************************
*
*       _GetPrevVisibleParent
*
* Purpose:
*   Returns the previous visible parent node of the given item. Used by moving the cursor 'LEFT'
*   if the current selection is a node.
*   If there is no previous visible parent it returns the given item.
*/
static TREEVIEW_ITEM_Handle _GetPrevVisibleParent(TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_Handle hItemOld;
  int Level;
  hItemOld = hItem;
  pItem    = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
  Level    = pItem->Level;
  do {
    hItem = _GetPrevVisibleNode(hItem);
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    if (pItem->Level < Level) {
      return hItem;
    }
  } while (pItem->Level);
  return hItemOld;
}

/*********************************************************************
*
*       _GetLastNodeItem
*/
static TREEVIEW_ITEM_Handle _GetLastNodeItem(TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_ITEM_OBJ * pItemNode;
  int Level;
  pItemNode = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
  Level     = pItemNode->Level;
  if (pItemNode->Flags & TREEVIEW_ITEM_TYPE_NODE) {
    TREEVIEW_ITEM_OBJ  * pItem;
    TREEVIEW_ITEM_Handle hItemI;
    hItemI = pItemNode->hNext;
    if (hItemI) {
      pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemI);
      while (hItemI && (pItem->Level > Level)) {
        hItemI = pItem->hNext;
        if (hItemI) {
          pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemI);
          if (pItem->Level > Level) {
            hItem = hItemI;
          }
        }
      }
    }
  }
  return hItem;
}

/*********************************************************************
*
*       _GetLastVisibleItem
*/
static TREEVIEW_ITEM_Handle _GetLastVisibleItem(TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_ITEM_Handle hItemNew;
  do {
    hItemNew = hItem;
    hItem    = _GetNextVisibleItem(hItem);
  } while (hItem != hItemNew);
  return hItem;
}

/*********************************************************************
*
*       _GetPrevItem
*/
static TREEVIEW_ITEM_Handle _GetPrevItem(TREEVIEW_ITEM_Handle hItem, int Level) {
  TREEVIEW_ITEM_OBJ  * pItem;
  int IsLeaf;
  pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
  hItem = pItem->hPrev;
  IsLeaf = (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) ? 0 : 1;
  while (hItem) {
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    if (pItem->Level == Level) {
      return hItem;
    }
    if ((pItem->Level < Level) && (IsLeaf)) {
      break;
    }
    hItem = pItem->hPrev;
  }
  return 0;
}

/*********************************************************************
*
*       _GetVisibility
*
* Purpose:
*   Checks if the given item is completely visible or not and fills
*   the optional GUI_RECT structure with the item rectangle.
*
* Return value:
*  -1 if above inside area
*   0 if completely in inside area
*   1 if at the bottom and partly visible
*   2 if below inside area
*/
static int _GetVisibility(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj, TREEVIEW_ITEM_Handle hItem, GUI_RECT * pRect) {
  TREEVIEW_ITEM_Handle hItemI;
  TREEVIEW_ITEM_OBJ  * pItemI;
  GUI_RECT RectInside;
  int i, yPos, ItemDistY;
  WM_GetInsideRectExScrollbar(hObj, &RectInside);
  yPos = RectInside.y0;
  hItemI = pObj->hFirst;
  
  i = pObj->ScrollStateV.v;
  while (i--) {
    if (!hItemI) {
      break;
    }
    if (hItemI == hItem) {
      return -1; /* Above inside area */
    }
    /* Skip closed items */
    pItemI = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemI);
    hItemI = _SkipClosedItems(pItemI);
  }
  /* Inside area */
  while (hItemI) {
    pItemI    = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemI);
    ItemDistY = _CallOwnerDraw(hObj, pObj, hItemI, WIDGET_ITEM_GET_YSIZE);
    yPos     += ItemDistY;
    /*
    if (yPos > RectInside.y1) {
      break;
    }
    */
    if (hItemI == hItem) {
      if (pRect) {
        pRect->x0 = RectInside.x0;
        pRect->x1 = RectInside.x1;
        pRect->y0 = yPos - ItemDistY;
        pRect->y1 = pRect->y0 + ItemDistY - 1;
      }
      if (yPos > (RectInside.y1 + 1)) {
        return 1;
      } else {
        return 0;
      }
    }
    if (yPos > RectInside.y1) {
      break;
    }
    hItemI = _SkipClosedItems(pItemI);
  }
  /* Below inside area */
  return 2;
}

/*********************************************************************
*
*       _IsParentPathOpen
*
* Purpose:
*   Returns if complete parent path is open or not. If it is not open
*   the item is not visible.
*
* Return value:
*   1 if it is visible
*   0 if not
*/
static int _IsParentPathOpen(TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_ITEM_Handle hItemI;
  TREEVIEW_ITEM_OBJ  * pItemI;
  TREEVIEW_ITEM_OBJ  * pItem;
  int Level;
  pItem  = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
  Level  = pItem->Level;
  pItemI = pItem;
  do {
    hItemI = pItemI->hPrev;
    if (hItemI) {
      pItemI = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemI);
      if (Level > pItemI->Level) {
        Level = pItemI->Level;
        if ((pItemI->Flags & TREEVIEW_ITEM_STATE_EXPANDED) == 0) {
          return 0;
        }
      }
    }
  } while (hItemI);
  return 1;
}

/*********************************************************************
*
*       _UpdateScrollPos
*
* Purpose:
*   The routine updates the position of the scrollbars if required.
*
* Return value:
*   0 if scroll position has not changed
*   1 if scroll position has changed
*/
static int _UpdateScrollPos(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj) {
  TREEVIEW_ITEM_Handle hItem;
  int Visibility;
  int r = 0;
  hItem = pObj->hSel;
  if (_IsParentPathOpen(hItem) == 0) {
    return 0;
  }
  do {
    Visibility = _GetVisibility(hObj, pObj, hItem, NULL);
    switch (Visibility) {
    case -1:
      pObj->ScrollStateV.v--;
      r = 1;
      break;
    case +1:
    case +2:
      pObj->ScrollStateV.v++;
      r = 1;
      break;
    }
  } while (Visibility);
  WIDGET__SetScrollState(hObj, &pObj->ScrollStateV, &pObj->ScrollStateH);
  return r;
}

/*********************************************************************
*
*       _SetSel
*/
static void _SetSel(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj, TREEVIEW_ITEM_Handle hItem) {
  #if 1
  /*
  * Optimized, invalidates only the rectangles of the previous and current selected items
  */
  TREEVIEW_ITEM_Handle hItemOld;
  hItemOld = pObj->hSel;
  pObj->hSel = hItem;
  if (_UpdateScrollPos(hObj, pObj)) {
    /*
    * Invalidate complete window
    */
    WM_InvalidateWindow(hObj);
  } else {
    GUI_RECT Rect;
    int Visibility;
    /*
    * Invalidate only 2 items
    */
    Visibility = _GetVisibility(hObj, pObj, hItemOld, &Rect);
    if ((Visibility == 0) || (Visibility == 1)) {
      WM_InvalidateRect(hObj, &Rect);
    }
    Visibility = _GetVisibility(hObj, pObj, hItem, &Rect);
    if ((Visibility == 0) || (Visibility == 1)) {
      WM_InvalidateRect(hObj, &Rect);
    }
  }
  WM_NotifyParent(hObj, WM_NOTIFICATION_SEL_CHANGED);
  #else
  /*
  * Not optimized, invalidates the complete widget
  */
  pObj->hSel = hItem;
  _UpdateScrollPos(hObj, pObj);
  WM_InvalidateWindow(hObj);
  WM_NotifyParent(hObj, WM_NOTIFICATION_SEL_CHANGED);
  #endif
}

/*********************************************************************
*
*       _OnKey
*/
static void _OnKey(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj, WM_MESSAGE * pMsg) {
  TREEVIEW_ITEM_Handle hItem;
  TREEVIEW_ITEM_OBJ  * pItem;
  const WM_KEY_INFO  * pInfo;
  int Key;
  pInfo = (const WM_KEY_INFO *)pMsg->Data.p;
  if (pInfo->PressedCnt == 0) {
    return;
  }
  Key   = pInfo->Key;
  switch (Key) {
  case GUI_KEY_RIGHT:
    hItem = pObj->hSel;
    if (hItem) {
      pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
      if (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) {
        if (pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) {
          _IncSel(hObj, pObj);
          _UpdateScrollPos(hObj, pObj);
        } else {
          TREEVIEW_ITEM_Expand(hItem);
        }
      }
    }
    break;
  case GUI_KEY_LEFT:
    hItem = pObj->hSel;
    if (hItem) {
      pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
      if (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) {
        if (pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) {
          TREEVIEW_ITEM_Collapse(hItem);
        } else {
          _SetSel(hObj, pObj, _GetPrevVisibleParent(pObj->hSel));
        }
      } else {
        _SetSel(hObj, pObj, _GetPrevVisibleNode(pObj->hSel));
      }
    }
    break;
  case GUI_KEY_DOWN:
    if (pObj->hSel) {
      _SetSel(hObj, pObj, _GetNextVisibleItem(pObj->hSel));
    }
    break;
  case GUI_KEY_UP:
    if (pObj->hSel) {
      _SetSel(hObj, pObj, _GetPrevVisibleItem(pObj->hSel));
    }
    break;
  case GUI_KEY_HOME:
    if (pObj->hFirst) {
      _SetSel(hObj, pObj, pObj->hFirst);
    }
    break;
  case GUI_KEY_END:
    if (pObj->hSel) {
      _SetSel(hObj, pObj, _GetLastVisibleItem(pObj->hSel));
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _SetAutoScroll
*/
static void _SetAutoScroll(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj, int State, int Mask) {
  char Flags;
  Flags = pObj->Flags & (~Mask);
  if (State) {
    Flags |= Mask;
  } else {
    WM_SetScrollbarH(hObj, 0);
  }
  if (pObj->Flags != Flags) {
    pObj->Flags = Flags;
    _CalcParams(hObj, pObj);
    _ManageAutoScroll(hObj, pObj);
    WM_InvalidateWindow(hObj);
  }
}

/*********************************************************************
*
*       _OnDelete
*/
static void _OnDelete(TREEVIEW_OBJ * pObj) {
  TREEVIEW_ITEM_Handle hFree;
  TREEVIEW_ITEM_Handle hItem;
  TREEVIEW_ITEM_OBJ  * pItem;
  hItem = pObj->hFirst;
  while (hItem) {
    hFree = hItem;
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    if (pItem->hData) {
      GUI_ALLOC_Free(pItem->hData);
    }
    hItem = pItem->hNext;
    GUI_ALLOC_Free(hFree);
  }
}

/*********************************************************************
*
*       _LinkItem
*/
static int _LinkItem(TREEVIEW_Handle hObj, TREEVIEW_OBJ * pObj, TREEVIEW_ITEM_Handle hItemNew, TREEVIEW_ITEM_OBJ * pItemNew, TREEVIEW_ITEM_Handle hItemAt, int Position) {
  TREEVIEW_ITEM_Handle hItemPrev;
  TREEVIEW_ITEM_OBJ  * pItemPrev;
  TREEVIEW_ITEM_Handle hItemNext;
  TREEVIEW_ITEM_OBJ  * pItemNext;
  int Level;
  int r = 0;
  pObj     = TREEVIEW_H2P(hObj);
  pItemNew = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemNew);
  if (pObj->NumItems) {
    /*
    * Manage inteding
    */
    if (hItemAt) {
      if (Position == TREEVIEW_INSERT_FIRST_CHILD) {
        hItemPrev = hItemAt;
        pItemPrev = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemPrev);
        if (pItemPrev->Flags & TREEVIEW_ITEM_TYPE_NODE) {
          hItemNext = pItemPrev->hNext;
          if (hItemNext) {
            pItemNext = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemNext);
            pItemNext->hPrev = hItemNew;
          } else {
            pObj->hLast = hItemNew;
          }
          pItemPrev->hNext = hItemNew;
          pItemNew->hNext  = hItemNext;
          pItemNew->hPrev  = hItemPrev;
          pItemNew->Level  = pItemPrev->Level + 1;
        } else {
          GUI_DEBUG_ERROROUT("_LinkItem: Can not be indented at a leaf!");
          r = 1;
        }
      } else if (Position == TREEVIEW_INSERT_ABOVE) {
        /*
        * Insert item above the given item
        */
        hItemNext = hItemAt;
        pItemNext = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemNext);
        hItemPrev = pItemNext->hPrev;
        if (hItemPrev) {
          pItemPrev = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemPrev);
          pItemPrev->hNext  = hItemNew;
        } else {
          pObj->hFirst = hItemNew;
        }
        pItemNext->hPrev = hItemNew;
        pItemNew->hNext  = hItemNext;
        pItemNew->hPrev  = hItemPrev;
        pItemNew->Level  = pItemNext->Level;
      } else if (Position == TREEVIEW_INSERT_BELOW) {
        /*
        * Insert item below the given item
        */
        hItemPrev = hItemAt;
        pItemPrev = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemPrev);
        Level     = pItemPrev->Level;
        hItemPrev = _GetLastNodeItem(hItemAt);
        pItemPrev = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemPrev);
        hItemNext = pItemPrev->hNext;
        if (hItemNext) {
          pItemNext = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemNext);
          pItemNext->hPrev = hItemNew;
        } else {
          pObj->hLast = hItemNew;
        }
        pItemPrev->hNext = hItemNew;
        pItemNew->hNext  = hItemNext;
        pItemNew->hPrev  = hItemPrev;
        pItemNew->Level  = Level;
      }
    } else {
      GUI_DEBUG_ERROROUT("_LinkItem: Position has not been defined!");
      r = 1;
    }
  } else {
    /*
    * Manage the first item
    */
    if (pObj->hFirst == 0) {
      pObj = TREEVIEW_H2P(hObj);
      pObj->hFirst = pObj->hLast = pObj->hSel = hItemNew;
      pItemNew->hNext = 0;
      pItemNew->hPrev = 0;
    } else {
      GUI_DEBUG_ERROROUT("_LinkItem: First item already exists!");
      r = 1;
    }
  }
  if (r == 0) {
    pObj->NumItems++;
    pItemNew->hParent = hObj;
    _CalcParams(hObj, pObj);
    _ManageAutoScroll(hObj, pObj);
    WM_InvalidateWindow(hObj);
  }
  return r;
}

/*********************************************************************
*
*       _SetColor
*/
static void _SetColor(TREEVIEW_Handle hObj, int Index, GUI_COLOR Color, int ArrayIndex) {
  TREEVIEW_OBJ * pObj;
  if (hObj) {
    WM_LOCK();
    pObj = TREEVIEW_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.aBkColor)) {
      switch (ArrayIndex) {
      case TREEVIEW_COLORS_BK:
        pObj->Props.aBkColor[Index] = Color;
        break;
      case TREEVIEW_COLORS_TEXT:
        pObj->Props.aTextColor[Index] = Color;
        break;
      case TREEVIEW_COLORS_LINE:
        pObj->Props.aLineColor[Index] = Color;
        break;
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       _MoveSel
*/
static void _MoveSel(TREEVIEW_Handle hObj, int Off) {
  TREEVIEW_OBJ * pObj;
  if (Off) {
    WM_LOCK();
    pObj  = TREEVIEW_H2P(hObj);
    if (Off < 0) {
      do {
        if (pObj->hSel) {
          _SetSel(hObj, pObj, _GetPrevVisibleItem(pObj->hSel));
        }
      } while (++Off);
    } else {
      do {
        if (pObj->hSel) {
          _SetSel(hObj, pObj, _GetNextVisibleItem(pObj->hSel));
        }
      } while (--Off);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       Exported routines, common
*
**********************************************************************
*/
/*********************************************************************
*
*       TREEVIEW_Callback
*/
void TREEVIEW_Callback(WM_MESSAGE * pMsg) {
  TREEVIEW_Handle hObj = pMsg->hWin;
  TREEVIEW_OBJ * pObj = (TREEVIEW_OBJ *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
  WM_SCROLL_STATE ScrollState;
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_DELETE:
    _OnDelete(pObj);
    break;
  case WM_TIMER:
    WM_DeleteTimer(pObj->hTimer);
    pObj->hTimer = 0;
    break;
  case WM_PAINT:
    _OnPaint(hObj, pObj, pMsg);
    break;
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    break;
  case WM_KEY:
    if (pObj->hTimer == 0) {
      _OnKey(hObj, pObj, pMsg);
    }
    break;
  case WM_NOTIFY_PARENT:
    switch (pMsg->Data.v) {
    case WM_NOTIFICATION_VALUE_CHANGED:
      if (pMsg->hWinSrc  == WM_GetScrollbarV(hObj)) {
        WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
        pObj->ScrollStateV.v = ScrollState.v;
      } else if (pMsg->hWinSrc == WM_GetScrollbarH(hObj)) {
        WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
        pObj->ScrollStateH.v = ScrollState.v;
      }
      WM_InvalidateWindow(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_SCROLL_CHANGED);
      break;
    case WM_NOTIFICATION_SCROLLBAR_ADDED:
      #if WIDGET_USE_PARENT_EFFECT
        WIDGET_SetEffect(pMsg->hWinSrc, pObj->Widget.pEffect);
      #endif
      _CalcParams(hObj, pObj);
      _ManageAutoScroll(hObj, pObj);
      break;
    }
    break;
  }
}

/*********************************************************************
*
*       TREEVIEW_OwnerDraw
*/
int TREEVIEW_OwnerDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_GET_XSIZE:
    return _OnOwnerdraw_GetXSize(pDrawItemInfo);
  case WIDGET_ITEM_GET_YSIZE:
    return _OnOwnerdraw_GetYSize(pDrawItemInfo);
  case WIDGET_ITEM_DRAW:
    return _OnOwnerdraw_Paint(pDrawItemInfo);
  }
  return 0;
}

/*********************************************************************
*
*       TREEVIEW_CreateEx
*/
TREEVIEW_Handle TREEVIEW_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id) {
  TREEVIEW_Handle hObj;
  WM_LOCK();
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, TREEVIEW_Callback,
                                sizeof(TREEVIEW_OBJ) - sizeof(WM_Obj));
  if (hObj) {
    TREEVIEW_OBJ * pObj = (TREEVIEW_OBJ *)GUI_ALLOC_h2p(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
    /* init member variables */
    TREEVIEW_INIT_ID(pObj);
    pObj->Props      = TREEVIEW__DefaultProps;
    pObj->pfDrawItem = TREEVIEW_OwnerDraw;
    pObj->Flags      = ExFlags;
  }
  WM_UNLOCK();
  return hObj;
}

/*********************************************************************
*
*       TREEVIEW_ITEM_Create
*/
TREEVIEW_ITEM_Handle TREEVIEW_ITEM_Create(int IsNode, const char * s, U32 UserData) {
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_Handle hItem;
  hItem = GUI_ALLOC_AllocZero(sizeof(TREEVIEW_ITEM_OBJ) + strlen(s));
  if (hItem) {
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    pItem->UserData = UserData;
    strcpy(pItem->acText, s);
    if (IsNode) {
      pItem->Flags |= TREEVIEW_ITEM_TYPE_NODE;
    }
  }
  return hItem;
}

/*********************************************************************
*
*       TREEVIEW_AttachItem
*/
int TREEVIEW_AttachItem(TREEVIEW_Handle hObj, TREEVIEW_ITEM_Handle hItem, TREEVIEW_ITEM_Handle hItemAt, int Position) {
  TREEVIEW_OBJ       * pObj;
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_Handle hItemNext;
  TREEVIEW_ITEM_OBJ  * pItemNext;
  TREEVIEW_ITEM_Handle hItemLast;
  TREEVIEW_ITEM_OBJ  * pItemLast;
  TREEVIEW_ITEM_Handle hItemTemp;
  int LevelOld, LevelNew;
  int r = 0;
  if (hObj && hItem) {
    WM_LOCK();
    pObj  = TREEVIEW_H2P(hObj);
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    hItemTemp = pItem->hNext;     /* Backup next pointer */
    if (hItemTemp) {
      hItemLast = _GetLastNodeItem(hItem);
      LevelOld  = pItem->Level;
    }
    if (pItem->hPrev == 0) {
      r = _LinkItem(hObj, pObj, hItem, pItem, hItemAt, Position);
      LevelNew = pItem->Level;
      GUI_SetFont(pObj->Props.pFont);
      pItem->xSize = (pItem->Level + 1) * pObj->Props.Indent 
                   + pObj->Props.TextIndent
                   + GUI_GetStringDistX(pItem->acText);
      if (hItemTemp && (r == 0)) {
        hItemNext = pItem->hNext;
        pItem->hNext = hItemTemp; /* Restore next pointer */
        pItem->hParent = hObj;
        do {
          pObj->NumItems++;
          hItem = pItem->hNext;
          if (hItem) {
            pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
            pItem->Level += (LevelNew - LevelOld);
            pItem->hParent = hObj;
          }
        } while (hItem != hItemLast);
        pItemLast = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemLast);
        pItemLast->hNext = hItemNext;
        if (hItemNext) {
          pItemNext = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemNext);
          pItemNext->hPrev = hItemLast;
        }
      }
      _CalcParams(hObj, pObj);
      _ManageAutoScroll(hObj, pObj);
      WM_InvalidateWindow(hObj);
    } else {
      GUI_DEBUG_ERROROUT("TREEVIEW_AttachItem: Item is not allowed to have previous items!");
    }
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       TREEVIEW_InsertItem
*/
TREEVIEW_ITEM_Handle TREEVIEW_InsertItem(TREEVIEW_Handle hObj, int IsNode, TREEVIEW_ITEM_Handle hItemPrev, int Position, const char * s) {
  TREEVIEW_ITEM_Handle hItemNew;
  WM_LOCK();
  hItemNew = TREEVIEW_ITEM_Create(IsNode, s, 0);
  if (hItemNew) {
    if (TREEVIEW_AttachItem(hObj, hItemNew, hItemPrev, Position)) {
      GUI_ALLOC_Free(hItemNew);
    }
  } else {
    GUI_DEBUG_ERROROUT("TREEVIEW_InsertItem: Allocation failed!");
  }
  WM_UNLOCK();
  return hItemNew;
}

/*********************************************************************
*
*       TREEVIEW_SetAutoScrollH
*/
void TREEVIEW_SetAutoScrollH(TREEVIEW_Handle hObj, int State) {
  if (hObj) {
    TREEVIEW_OBJ * pObj;
    WM_LOCK();
    pObj = TREEVIEW_H2P(hObj);
    _SetAutoScroll(hObj, pObj, State, TREEVIEW_SF_AUTOSCROLLBAR_H);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_SetAutoScrollV
*/
void TREEVIEW_SetAutoScrollV(TREEVIEW_Handle hObj, int State) {
  if (hObj) {
    TREEVIEW_OBJ * pObj;
    WM_LOCK();
    pObj = TREEVIEW_H2P(hObj);
    _SetAutoScroll(hObj, pObj, State, TREEVIEW_SF_AUTOSCROLLBAR_V);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_SetHasLines
*/
void TREEVIEW_SetHasLines(TREEVIEW_Handle hObj, int State) {
  if (hObj) {
    TREEVIEW_OBJ * pObj;
    WM_LOCK();
    pObj = TREEVIEW_H2P(hObj);
    if (State) {
      if (pObj->Flags & TREEVIEW_SF_HIDELINES) {
        pObj->Flags &= ~TREEVIEW_SF_HIDELINES;
        WM_InvalidateWindow(hObj);
      }
    } else {
      if ((pObj->Flags & TREEVIEW_SF_HIDELINES) == 0) {
        pObj->Flags |= TREEVIEW_SF_HIDELINES;
        WM_InvalidateWindow(hObj);
      }
    }
    _SetAutoScroll(hObj, pObj, State, TREEVIEW_SF_AUTOSCROLLBAR_V);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_GetItem
*/
TREEVIEW_ITEM_Handle TREEVIEW_GetItem(TREEVIEW_Handle hObj, TREEVIEW_ITEM_Handle hItem, int Flags) {
  TREEVIEW_OBJ * pObj;
  TREEVIEW_ITEM_Handle hItemNext;
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_Handle hItemTemp;
  TREEVIEW_ITEM_OBJ  * pItemTemp;
  hItemNext = 0;
  if (hItem == 0) {
    if ((Flags != TREEVIEW_GET_FIRST) && (Flags != TREEVIEW_GET_LAST)) {
      GUI_DEBUG_ERROROUT("TREEVIEW_GetItem: Zero handle not allowed!");
      return 0;
    }
  }
  if (hObj) {
    WM_LOCK();
    pObj  = TREEVIEW_H2P(hObj);
    if (hItem) {
      pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    }
    switch (Flags) {
    case TREEVIEW_GET_FIRST:
      hItemNext = pObj->hFirst;
      break;
    case TREEVIEW_GET_LAST:
      hItemNext = pObj->hLast;
      break;
    case TREEVIEW_GET_NEXT_SIBLING:
      hItemTemp = _GetLastNodeItem(hItem);
      pItemTemp = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemTemp);
      hItemTemp = pItemTemp->hNext;
      if (hItemTemp) {
        pItemTemp = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemTemp);
        if (pItemTemp->Level == pItem->Level) {
          hItemNext = hItemTemp;
        }
      }
      break;
    case TREEVIEW_GET_PREV_SIBLING:
      hItemNext = _GetPrevItem(hItem, pItem->Level);
      break;
    case TREEVIEW_GET_FIRST_CHILD:
      if (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE) {
        hItemNext = pItem->hNext;
      } else {
        GUI_DEBUG_WARN("TREEVIEW_GetItem: Item is not a node!");
      }
      break;
    case TREEVIEW_GET_PARENT:
      if (pItem->Level) {
        hItemNext = _GetPrevItem(hItem, pItem->Level - 1);
      } else {
        GUI_DEBUG_WARN("TREEVIEW_GetItem: Illegal level!");
      }
      break;
    }
    WM_UNLOCK();
  }
  return hItemNext;
}

/*********************************************************************
*
*       TREEVIEW_GetSel
*/
TREEVIEW_ITEM_Handle TREEVIEW_GetSel(TREEVIEW_Handle hObj) {
  TREEVIEW_ITEM_Handle hItem = 0;
  TREEVIEW_OBJ       * pObj;
  if (hObj) {
    WM_LOCK();
    pObj  = TREEVIEW_H2P(hObj);
    hItem = pObj->hSel;
    WM_UNLOCK();
  }
  return hItem;
}

/*********************************************************************
*
*       TREEVIEW_SetImage
*/
void TREEVIEW_SetImage(TREEVIEW_Handle hObj, int Index, const GUI_BITMAP * pBitmap) {
  TREEVIEW_OBJ * pObj;
  if (hObj) {
    WM_LOCK();
    pObj = TREEVIEW_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.apBm)) {
      pObj->Props.apBm[Index] = pBitmap;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_SetSelMode
*/
void TREEVIEW_SetSelMode(TREEVIEW_Handle hObj, int Mode) {
  TREEVIEW_OBJ * pObj;
  if (hObj) {
    WM_LOCK();
    pObj = TREEVIEW_H2P(hObj);
    if        (Mode == TREEVIEW_SELMODE_ROW) {
      if ((pObj->Flags & TREEVIEW_CF_ROWSELECT) == 0) {
        pObj->Flags |= TREEVIEW_CF_ROWSELECT;
        WM_InvalidateWindow(hObj);
      }
    } else if (Mode == TREEVIEW_SELMODE_TEXT) {
      if (pObj->Flags & TREEVIEW_CF_ROWSELECT) {
        pObj->Flags &= ~TREEVIEW_CF_ROWSELECT;
        WM_InvalidateWindow(hObj);
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_SetBkColor
*/
void TREEVIEW_SetBkColor(TREEVIEW_Handle hObj, int Index, GUI_COLOR Color) {
  _SetColor(hObj, Index, Color, TREEVIEW_COLORS_BK);
}

/*********************************************************************
*
*       TREEVIEW_SetTextColor
*/
void TREEVIEW_SetTextColor(TREEVIEW_Handle hObj, int Index, GUI_COLOR Color) {
  _SetColor(hObj, Index, Color, TREEVIEW_COLORS_TEXT);
}

/*********************************************************************
*
*       TREEVIEW_SetLineColor
*/
void TREEVIEW_SetLineColor(TREEVIEW_Handle hObj, int Index, GUI_COLOR Color) {
  _SetColor(hObj, Index, Color, TREEVIEW_COLORS_LINE);
}

/*********************************************************************
*
*       TREEVIEW_SetFont
*/
void TREEVIEW_SetFont(TREEVIEW_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont) {
  TREEVIEW_OBJ * pObj;
  TREEVIEW_ITEM_Handle hItem;
  TREEVIEW_ITEM_OBJ  * pItem;
  if (hObj && pFont) {
    WM_LOCK();
    pObj = TREEVIEW_H2P(hObj);
    if (pObj->Props.pFont != pFont) {
      pObj->Props.pFont = pFont;
      GUI_SetFont(pObj->Props.pFont);
      hItem = pObj->hFirst;
      while (hItem) {
        pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
        pItem->xSize = (pItem->Level + 1) * pObj->Props.Indent 
                     + pObj->Props.TextIndent
                     + GUI_GetStringDistX(pItem->acText);
        hItem = pItem->hNext;
      }
      _CalcParams(hObj, pObj);
      _ManageAutoScroll(hObj, pObj);
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_IncSel
*/
void TREEVIEW_IncSel(TREEVIEW_Handle hObj) {
  _MoveSel(hObj, 1);
}

/*********************************************************************
*
*       TREEVIEW_DecSel
*/
void TREEVIEW_DecSel(TREEVIEW_Handle hObj) {
  _MoveSel(hObj, -1);
}

/*********************************************************************
*
*       TREEVIEW_SetSel
*/
void TREEVIEW_SetSel(TREEVIEW_Handle hObj, TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_OBJ * pObj;
  if (hObj) {
    WM_LOCK();
    pObj  = TREEVIEW_H2P(hObj);
    _SetSel(hObj, pObj, hItem);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       Exported routines, item related
*
**********************************************************************
*/
/*********************************************************************
*
*       TREEVIEW_ITEM_Detach
*/
void TREEVIEW_ITEM_Detach(TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_Handle      hObj;
  TREEVIEW_OBJ       * pObj;
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_Handle hItemPrev;
  TREEVIEW_ITEM_OBJ  * pItemPrev;
  TREEVIEW_ITEM_Handle hItemNext;
  TREEVIEW_ITEM_OBJ  * pItemNext;
  TREEVIEW_ITEM_Handle hItemLast;
  TREEVIEW_ITEM_OBJ  * pItemLast;
  int Level;
  if (hItem) {
    WM_LOCK();
    pItem     = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    if (pItem->hParent) {
      hObj      = pItem->hParent;
      pObj      = TREEVIEW_H2P(hObj);
      hItemLast = _GetLastNodeItem(hItem);
      pItemLast = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemLast);
      hItemPrev = pItem->hPrev;
      hItemNext = pItemLast->hNext;
      Level     = pItem->Level;
      if (hItemPrev) {
        pItemPrev = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemPrev);
        pItemPrev->hNext = hItemNext;
      } else {
        if (pObj->hFirst == hItem) {
          pObj->hFirst = hItemNext;
        } else {
          GUI_DEBUG_ERROROUT("TREEVIEW_ITEM_Detach: Illegal handle!");
        }
      }
      if (hItemNext) {
        pItemNext = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemNext);
        pItemNext->hPrev = hItemPrev;
      }
      /*
      * Manage selection
      */
      if (pObj->hSel == hItem) {
        TREEVIEW_ITEM_Handle hItemNewSel;
        hItemNewSel = _GetNextVisibleItem(hItemLast);
        if (hItemNewSel == hItemLast) {
          hItemNewSel = _GetPrevVisibleItem(hItem);
          if (hItemNewSel == hItem) {
            pObj->hSel = 0;
          } else {
            pObj->hSel = hItemNewSel;
          }
        } else {
          pObj->hSel = hItemNewSel;
        }
      }
      /*
      * Remove items
      */
      pItem->hPrev     = 0;
      pItemLast->hNext = 0;
      pItem->Level     = 0;
      pItem->hParent   = 0;
      do {
        pObj->NumItems--;
        hItem = pItem->hNext;
        if (hItem) {
          pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
          pItem->hParent = 0;
          pItem->Level  -= Level;
        }
      } while (hItem);
      _CalcParams(hObj, pObj);
      _ManageAutoScroll(hObj, pObj);
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_ITEM_Delete
*
* Purpose:
*   Deletes the given item. If the item is a node, it also deletes all children of the node
*/
void TREEVIEW_ITEM_Delete(TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_Handle      hObj;
  TREEVIEW_OBJ       * pObj;
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_Handle hItemFree;
  if (hItem) {
    TREEVIEW_ITEM_Detach(hItem);
    WM_LOCK();
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    hObj  = pItem->hParent;
    while (hItem) {
      hItemFree = hItem;
      pItem     = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
      hItem     = pItem->hNext;
      if (pItem->hData) {
        GUI_ALLOC_Free(pItem->hData);
      }
      GUI_ALLOC_Free(hItemFree);
    }
    if (hObj) {
      pObj = TREEVIEW_H2P(hObj);
      _CalcParams(hObj, pObj);
      _ManageAutoScroll(hObj, pObj);
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_ITEM_Expand
*/
void TREEVIEW_ITEM_Expand(TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_ITEM_OBJ * pItem;
  if (hItem) {
    WM_LOCK();
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    _ExpandItem(pItem);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_ITEM_Collapse
*/
void TREEVIEW_ITEM_Collapse(TREEVIEW_ITEM_Handle hItem) {
  TREEVIEW_ITEM_OBJ * pItem;
  if (hItem) {
    WM_LOCK();
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    _CollapseItem(pItem);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_ITEM_SetImage
*/
void TREEVIEW_ITEM_SetImage(TREEVIEW_ITEM_Handle hItem, int Index, const GUI_BITMAP * pBitmap) {
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_DATA * pData;
  if (Index < GUI_COUNTOF(pData->apBm)) {
    WM_LOCK();
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    if (pItem->hData == 0) {
      pItem->hData = GUI_ALLOC_AllocZero(sizeof(TREEVIEW_ITEM_DATA));
      pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    }
    if (pItem->hData) {
      pData = (TREEVIEW_ITEM_DATA *)GUI_ALLOC_h2p(pItem->hData);
      pData->apBm[Index] = pBitmap;
      if (pItem->hParent) {
        WM_InvalidateWindow(pItem->hParent);
      }
    } else {
      GUI_DEBUG_ERROROUT("TREEVIEW_ITEM_SetImage: Allocation failed!");
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_ITEM_SetText
*/
TREEVIEW_ITEM_Handle TREEVIEW_ITEM_SetText(TREEVIEW_ITEM_Handle hItem, const char * s) {
  TREEVIEW_ITEM_OBJ  * pItem;
  TREEVIEW_ITEM_Handle hItemNew = 0;
  TREEVIEW_ITEM_OBJ  * pItemNew;
  TREEVIEW_ITEM_OBJ  * pItemPrev;
  TREEVIEW_ITEM_OBJ  * pItemNext;
  if (s) {
    WM_LOCK();
    hItemNew = TREEVIEW_ITEM_Create(0, s, 0);
    if (hItemNew) {
      pItem     = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
      pItemNew  = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItemNew);
      pItemNew->UserData= pItem->UserData;
      pItemNew->hNext   = pItem->hNext;
      pItemNew->hPrev   = pItem->hPrev;
      pItemNew->Flags   = pItem->Flags;
      pItemNew->hData   = pItem->hData;
      pItemNew->Level   = pItem->Level;
      pItemNew->hParent = pItem->hParent;
      if (pItemNew->hPrev) {
        pItemPrev = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(pItemNew->hPrev);
        pItemPrev->hNext = hItemNew;
      }
      if (pItemNew->hNext) {
        pItemNext = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(pItemNew->hNext);
        pItemNext->hPrev = hItemNew;
      }
      GUI_ALLOC_Free(hItem);
      if (pItemNew->hParent) {
        TREEVIEW_OBJ * pObj;
        pObj = TREEVIEW_H2P(pItemNew->hParent);
        _CalcParams(pItemNew->hParent, pObj);
        _ManageAutoScroll(pItemNew->hParent, pObj);
        WM_InvalidateWindow(pItemNew->hParent);
      }
    } else {
      GUI_DEBUG_ERROROUT("TREEVIEW_ITEM_SetText: Allocation failed!");
    }
    WM_UNLOCK();
  }
  return hItemNew;
}

/*********************************************************************
*
*       TREEVIEW_ITEM_GetText
*/
void TREEVIEW_ITEM_GetText(TREEVIEW_ITEM_Handle hItem, U8 * pBuffer, int MaxNumBytes) {
  TREEVIEW_ITEM_OBJ  * pItem;
  int NumBytes;
  if (hItem && pBuffer && MaxNumBytes) {
    WM_LOCK();
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    NumBytes = strlen(pItem->acText) + 1;
    if (NumBytes > MaxNumBytes) {
      NumBytes = MaxNumBytes;
    }
    GUI_MEMCPY(pBuffer, pItem->acText, NumBytes);
    *(pBuffer + NumBytes - 1) = 0;
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_ITEM_GetInfo
*/
void TREEVIEW_ITEM_GetInfo(TREEVIEW_ITEM_Handle hItem, TREEVIEW_ITEM_INFO * pInfo) {
  TREEVIEW_ITEM_OBJ  * pItem;
  if (hItem) {
    WM_LOCK();
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    pInfo->IsNode       = (pItem->Flags & TREEVIEW_ITEM_TYPE_NODE)      ? 1 : 0;
    pInfo->IsExpanded   = (pItem->Flags & TREEVIEW_ITEM_STATE_EXPANDED) ? 1 : 0;
    pInfo->HasLines     = (pItem->Flags & TREEVIEW_SF_HIDELINES)        ? 0 : 1;
    pInfo->HasRowSelect = (pItem->Flags & TREEVIEW_CF_ROWSELECT)        ? 1 : 0;
    pInfo->Level        = pItem->Level;
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_ITEM_SetUserData
*/
void TREEVIEW_ITEM_SetUserData(TREEVIEW_ITEM_Handle hItem, U32 UserData) {
  TREEVIEW_ITEM_OBJ * pItem;
  if (hItem) {
    WM_LOCK();
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    pItem->UserData = UserData;
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       TREEVIEW_ITEM_GetUserData
*/
U32 TREEVIEW_ITEM_GetUserData(TREEVIEW_ITEM_Handle hItem) {
  U32 UserData;
  TREEVIEW_ITEM_OBJ * pItem;
  UserData = 0;
  if (hItem) {
    WM_LOCK();
    pItem = (TREEVIEW_ITEM_OBJ *)GUI_ALLOC_h2p(hItem);
    UserData = pItem->UserData;
    WM_UNLOCK();
  }
  return UserData;
}

#else                            /* Avoid problems with empty object modules */
  void TREEVIEW_C(void);
  void TREEVIEW_C(void) {}
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
