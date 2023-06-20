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
File        : HEADER.c
Purpose     : Implementation of header widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>

#include "HEADER_Private.h"
#include "SCROLLBAR.h"
#include "GUI.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

#ifndef HEADER_SUPPORT_DRAG
  #define HEADER_SUPPORT_DRAG 1
#endif

#ifndef HEADER_BORDER_V_DEFAULT
  #define HEADER_BORDER_V_DEFAULT 0
#endif

#ifndef HEADER_BORDER_H_DEFAULT
  #define HEADER_BORDER_H_DEFAULT 2
#endif

/* Define default fonts */
#ifndef HEADER_FONT_DEFAULT
  #if   WIDGET_USE_SCHEME_SMALL
    #define HEADER_FONT_DEFAULT &GUI_Font13_1
  #elif WIDGET_USE_SCHEME_MEDIUM
    #define HEADER_FONT_DEFAULT &GUI_Font16_1
  #elif WIDGET_USE_SCHEME_LARGE
    #define HEADER_FONT_DEFAULT &GUI_Font24_1
  #endif
#endif

/* Define colors */
#ifndef HEADER_BKCOLOR_DEFAULT
  #define HEADER_BKCOLOR_DEFAULT 0xAAAAAA
#endif

#ifndef HEADER_TEXTCOLOR_DEFAULT
  #define HEADER_TEXTCOLOR_DEFAULT GUI_BLACK
#endif

#ifndef HEADER_ARROWCOLOR_DEFAULT
  #define HEADER_ARROWCOLOR_DEFAULT GUI_BLACK
#endif

/* Define cursors */
#ifndef HEADER_CURSOR_DEFAULT
  #define HEADER_CURSOR_DEFAULT &GUI_CursorHeaderM
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

HEADER_PROPS HEADER_DefaultProps = {
  HEADER_FONT_DEFAULT,
  HEADER_BKCOLOR_DEFAULT,
  HEADER_TEXTCOLOR_DEFAULT,
  HEADER_ARROWCOLOR_DEFAULT
};

/* Remember the old cursor */
static const GUI_CURSOR GUI_UNI_PTR * _pOldCursor;

/* Default values */
const GUI_CURSOR GUI_UNI_PTR * HEADER__pDefaultCursor   = HEADER_CURSOR_DEFAULT;
int                            HEADER__DefaultBorderH   = HEADER_BORDER_H_DEFAULT;
int                            HEADER__DefaultBorderV   = HEADER_BORDER_V_DEFAULT;

/*********************************************************************
*
*       static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawTriangle
*/
static void _DrawTriangle(int x, int y, int Size, int Inc) {
  for (; Size >= 0; Size--, y += Inc) {
    GUI_DrawHLine(y, x - Size, x + Size);
  }
}

/*********************************************************************
*
*       _Paint
*/
static void _Paint(HEADER_Obj* pObj) {
  GUI_RECT Rect;
  GUI_RECT RectItem;
  GUI_RECT RectNonFixedArea;
  unsigned i;
  int xPos;
  unsigned NumItems;
  int EffectSize;
  int ArrowSize;
  int ArrowPos;
  xPos = -pObj->ScrollPos;
  NumItems = GUI_ARRAY_GetNumItems(&pObj->Columns);
  EffectSize = pObj->Widget.pEffect->EffectSize;
  LCD_SetBkColor(pObj->Props.BkColor);
  GUI_SetFont(pObj->Props.pFont);
  GUI_Clear();
  GUI_GetClientRect(&RectNonFixedArea);
  for (i = 0; i < NumItems; i++) {
    int Subtract = 0;
    HEADER_COLUMN * pColumn = (HEADER_COLUMN*)GUI_ARRAY_GetpItem(&pObj->Columns, i);
    GUI_GetClientRect(&Rect);
    xPos += (i < pObj->Fixed) ? pObj->ScrollPos : 0;
    Rect.x0 = xPos;
    Rect.x1 = Rect.x0 + pColumn->Width;
    RectItem = Rect;
    ArrowSize = ((RectItem.y1 - RectItem.y0 - EffectSize * 2) / 3) - 1;
    ArrowPos = RectItem.x1 - 4 - ArrowSize;
    WM_SetUserClipRect(&RectNonFixedArea);
    if (pColumn->hDrawObj) {
      int xOff = 0, yOff = 0;
      switch (pColumn->Align & GUI_TA_HORIZONTAL) {
        case GUI_TA_RIGHT:
          xOff = (pColumn->Width - GUI_DRAW__GetXSize(pColumn->hDrawObj));
          break;
        case GUI_TA_HCENTER:
          xOff = (pColumn->Width - GUI_DRAW__GetXSize(pColumn->hDrawObj)) / 2;
          break;
      }
      switch (pColumn->Align & GUI_TA_VERTICAL) {
	      case GUI_TA_BOTTOM:
          yOff = ((Rect.y1 - Rect.y0 + 1) - GUI_DRAW__GetYSize(pColumn->hDrawObj));
          break;
	      case GUI_TA_VCENTER:
          yOff = ((Rect.y1 - Rect.y0 + 1) - GUI_DRAW__GetYSize(pColumn->hDrawObj)) / 2;
          break;
      }
      WM_SetUserClipRect(&Rect);
      GUI_DRAW__Draw(pColumn->hDrawObj, xPos + xOff, yOff);
      WM_SetUserClipRect(NULL);
    }
    WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &Rect);
    xPos += Rect.x1 - Rect.x0;
    Rect.x0 += EffectSize + HEADER__DefaultBorderH;
    Rect.x1 -= EffectSize + HEADER__DefaultBorderH;
    Rect.y0 += EffectSize + HEADER__DefaultBorderV;
    Rect.y1 -= EffectSize + HEADER__DefaultBorderV;
    LCD_SetColor(pObj->Props.TextColor);
    if ((pObj->DirIndicatorColumn == (int)i) && ((pColumn->Align & GUI_TA_HORIZONTAL) == GUI_TA_RIGHT)) {
      Subtract = (ArrowSize << 1) + 1;
    }
    Rect.x1 -= Subtract;
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_DispStringInRect(pColumn->acText, &Rect, pColumn->Align);
    Rect.x1 += Subtract;
    if (pObj->DirIndicatorColumn == (int)i) {
      LCD_SetColor(pObj->Props.ArrowColor);
      WM_SetUserClipRect(&RectNonFixedArea);
      if (pObj->DirIndicatorReverse == 0) {
        _DrawTriangle(ArrowPos, ((Rect.y1 - Rect.y0) >> 1), ArrowSize, 1);
      } else {
        _DrawTriangle(ArrowPos, ((Rect.y1 - Rect.y0) >> 1) + ArrowSize, ArrowSize, -1);
      }
      WM_SetUserClipRect(NULL);
    }
    if (i < pObj->Fixed) {
      RectNonFixedArea.x0 = RectItem.x1 + 1;
      xPos -= pObj->ScrollPos;
    }
  }
  WM_SetUserClipRect(NULL);
  GUI_GetClientRect(&Rect);
  Rect.x0 = xPos;
  Rect.x1 = 0xfff;
  WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &Rect);
}

/*********************************************************************
*
*       _RestoreOldCursor
*/
static void _RestoreOldCursor(void) {
  if (_pOldCursor) {
    #if GUI_SUPPORT_CURSOR
      if (GUI_CURSOR_GetStateEx(WM__TOUCHED_LAYER)) {
        GUI_CURSOR_SelectEx(_pOldCursor, WM__TOUCHED_LAYER);
      }
    #endif
    _pOldCursor = 0;
  }
}

/*********************************************************************
*
*       _FreeAttached
*
* Delete attached objects (if any)
*/
static void _FreeAttached(HEADER_Obj * pObj) {
  int i, NumItems;
  NumItems = GUI_ARRAY_GetNumItems(&pObj->Columns);
  for (i = 0; i < NumItems; i++) {
    HEADER_COLUMN * pColumn = (HEADER_COLUMN*)GUI_ARRAY_GetpItem(&pObj->Columns, i);
    if (pColumn->hDrawObj) {
      GUI_ALLOC_Free(pColumn->hDrawObj);
    }
  }
  /* Delete attached objects (if any) */
  GUI_ARRAY_Delete(&pObj->Columns);
  _RestoreOldCursor();
}

/*********************************************************************
*
*       _GetDividerIndex
*/
#if (HEADER_SUPPORT_DRAG)
static int _GetDividerIndex(HEADER_Handle hObj, HEADER_Obj * pObj, int x, int y) {
  int Item;
  int LastFixedPos;
  Item = -1;
  LastFixedPos = 0;
  if ((y >= 0) && (y < WM_GetWindowSizeY(hObj))) {
    if (hObj) {
      int xPos;
      unsigned Index, NumColumns;
      NumColumns = GUI_ARRAY_GetNumItems(&pObj->Columns);
      if (pObj->Fixed) {
        xPos = pObj->ScrollPos;
      } else {
        xPos = 0;
      }
      for (Index = 0; Index < NumColumns; Index++) {
        HEADER_COLUMN * pColumn;
        pColumn = (HEADER_COLUMN *)GUI_ARRAY_GetpItem(&pObj->Columns, Index);
        xPos += pColumn->Width;
        if (Index < pObj->Fixed) {
          LastFixedPos = xPos;
        } else if (pObj->Fixed && (Index == pObj->Fixed)) {
          xPos -= pObj->ScrollPos;
        }
        if (xPos >= LastFixedPos) {
          if ((xPos >= (x - 4)) && (xPos <= (x + 4))) {
            Item = Index;
            if ((Index < (NumColumns - 1)) && (x < xPos)) {
              pColumn = (HEADER_COLUMN *)GUI_ARRAY_GetpItem(&pObj->Columns, Index + 1);
              if (pColumn->Width == 0) {
                break;
              }
            }
          }
        }
      }
    }
  }
  return Item;
}
#endif

/*********************************************************************
*
*       _LimitDragWitdh
*
* Purpose:
*   Limits dragging of the captured header item to the right border of the window.
*
* Return value:
*   1 - If function has limitted the clipped header item
*   0 - If function has not limitted the clipped header item
*/
static int _LimitDragWitdh(HEADER_Handle hObj, HEADER_Obj * pObj) {
  if (pObj->DragLimit) {
    int DragLimit, i, SumX;
    GUI_RECT Rect;
    WM_HWIN hVScroll, hParent;
    /* Take the x-size of the widgets client rectangle as limit */
    WM_GetClientRectEx(hObj, &Rect);
    DragLimit = Rect.x1;
    /* If the parent window has a vertical scrollbar, reduce the drag limit by the xsize of the scrollbar */
    hParent = WM_GetParent(hObj);
    if (hParent) {
      hVScroll = WM_GetScrollbarV(WM_GetParent(hObj));
      if (hVScroll) {
        DragLimit -= WM_GetWindowSizeX(hVScroll);
      }
    }
    /* Calculate the sum of the width of all header items */
    for (SumX = i = 0; i <= pObj->CaptureItem; i++) {
      SumX += HEADER_GetItemWidth(hObj, i);
    }
    /* If the sum of the width of all header items exeeds the limit, limit the captured item */
    if (SumX > DragLimit) {
      for (SumX = i = 0; i < pObj->CaptureItem; i++) {
        SumX += HEADER_GetItemWidth(hObj, i);
      }
      HEADER_SetItemWidth(hObj, pObj->CaptureItem, DragLimit - SumX);
      return 1;
    }
  }
  return 0;
}

/*********************************************************************
*
*       _HandlePID
*/
#if (HEADER_SUPPORT_DRAG)
static void _HandlePID(HEADER_Handle hObj, HEADER_Obj * pObj, int x, int y, int Pressed) {
  int Hit = _GetDividerIndex(hObj, pObj, x, y);
  /* set capture position */
  if ((Pressed == 1) && (Hit >= 0) && (pObj->CapturePosX == -1)) {
    pObj->CapturePosX = x;
    pObj->CaptureItem = Hit;
  }
  if (Pressed <= 0) {
    pObj->CapturePosX = -1;
  }
  /* set mouse cursor and capture */
  if (Hit >= 0) {
    WM_SetCapture(hObj, 1);
    #if GUI_SUPPORT_CURSOR
      if (!_pOldCursor) {
        if (GUI_CURSOR_GetStateEx(WM__TOUCHED_LAYER)) {
          _pOldCursor = GUI_CURSOR_SelectEx(HEADER__pDefaultCursor, WM__TOUCHED_LAYER);
        }
      }
    #endif
  }
  /* modify header */
  if ((pObj->CapturePosX >= 0) && (x != pObj->CapturePosX) && (Pressed == 1)) {
    int NewSize = HEADER_GetItemWidth(hObj, pObj->CaptureItem) + x - pObj->CapturePosX;
    if (NewSize >= 0) {
      HEADER_SetItemWidth(hObj, pObj->CaptureItem, NewSize);
      if (!_LimitDragWitdh(hObj, pObj)) {
        pObj->CapturePosX = x;
      }
    }
  }
  /* release capture & restore cursor */
  if (Pressed <= 0) {
    #if (GUI_SUPPORT_MOUSE)
    if (Hit == -1)
    #endif
    {
      _RestoreOldCursor();
      pObj->CapturePosX = -1;
      WM_ReleaseCapture();
    }
  }
}
#endif

/*********************************************************************
*
*       _OnMouseOver
*/
#if (HEADER_SUPPORT_DRAG & GUI_SUPPORT_MOUSE)
static void _OnMouseOver(HEADER_Handle hObj, HEADER_Obj * pObj, WM_MESSAGE * pMsg) {
  const GUI_PID_STATE * pState = (const GUI_PID_STATE *)pMsg->Data.p;
  if (pState) {
    _HandlePID(hObj, pObj, pState->x + pObj->ScrollPos, pState->y, -1);
  }
}
#endif

/*********************************************************************
*
*       _GetItemIndex
*/
static int _GetItemIndex(HEADER_Handle hObj, HEADER_Obj * pObj, int x, int y) {
  int Item;
  int LastFixedPos;
  Item = -1;
  LastFixedPos = 0;
  if ((y >= 0) && (y < WM_GetWindowSizeY(hObj))) {
    if (hObj) {
      int xPos;
      unsigned Index, NumColumns;
      NumColumns = GUI_ARRAY_GetNumItems(&pObj->Columns);
      if (pObj->Fixed) {
        xPos = pObj->ScrollPos;
      } else {
        xPos = 0;
      }
      for (Index = 0; Index < NumColumns; Index++) {
        HEADER_COLUMN * pColumn;
        pColumn = (HEADER_COLUMN *)GUI_ARRAY_GetpItem(&pObj->Columns, Index);
        if (xPos >= LastFixedPos) {
          if ((x > (xPos + 4)) && (x < (xPos + pColumn->Width - 4))) {
            Item = Index;
            break;
          }
        }
        if (Index < pObj->Fixed) {
          LastFixedPos = xPos;
        } else if (pObj->Fixed && (Index == pObj->Fixed)) {
          xPos -= pObj->ScrollPos;
        }
        xPos += pColumn->Width;
      }
    }
  }
  return Item;
}

/*********************************************************************
*
*       _OnTouch
*/
#if (HEADER_SUPPORT_DRAG)
static void _OnTouch(HEADER_Handle hObj, HEADER_Obj * pObj, WM_MESSAGE * pMsg) {
  int Notification;
  const GUI_PID_STATE * pState = (const GUI_PID_STATE *)pMsg->Data.p;
  if (pState) {
    _HandlePID(hObj, pObj, pState->x + pObj->ScrollPos, pState->y, pState->Pressed);
    if (pState->Pressed) {
      Notification = WM_NOTIFICATION_CLICKED;
    } else {
      Notification = WM_NOTIFICATION_RELEASED;
    }
  } else {
    Notification = WM_NOTIFICATION_MOVED_OUT;
  }
  WM_NotifyParent(hObj, Notification);
}
#endif

/*********************************************************************
*
*       _OnPidStateChange
*/
static void _OnPidStateChange(HEADER_Handle hObj, HEADER_Obj * pObj, WM_MESSAGE * pMsg) {
  const WM_PID_STATE_CHANGED_INFO * pState = (const WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
  if ((pState->StatePrev == 1) && (pState->State == 0)) {
    pObj->Sel = _GetItemIndex(hObj, pObj, pState->x + pObj->ScrollPos, pState->y);
  }
}

/*********************************************************************
*
*       Private routines
*
**********************************************************************
*/
/*********************************************************************
*
*       HEADER_h2p
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
HEADER_Obj * HEADER_h2p(HEADER_Handle h) {
  HEADER_Obj * p = (HEADER_Obj *)GUI_ALLOC_h2p(h);
  if (p) {
    if (p->DebugId != HEADER_ID) {
      GUI_DEBUG_ERROROUT("HEADER.c: Wrong handle type or Object not init'ed");
      return 0;
    }
  }
  return p;
}
#endif

/*********************************************************************
*
*       Exported routines:  Callback
*
**********************************************************************
*/
/*********************************************************************
*
*       HEADER_Callback
*/
void HEADER_Callback (WM_MESSAGE *pMsg) {
  HEADER_Handle hObj;
  HEADER_Obj * pObj;
  hObj = pMsg->hWin;
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  WM_LOCK();
  pObj = (HEADER_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
  switch (pMsg->MsgId) {
  case WM_PAINT:
    _Paint(pObj);
    break;
  case WM_PID_STATE_CHANGED:
    _OnPidStateChange(hObj, pObj, pMsg);
    break;
#if (HEADER_SUPPORT_DRAG)
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    break;
#endif
#if (HEADER_SUPPORT_DRAG & GUI_SUPPORT_MOUSE)
  case WM_MOUSEOVER:
    _OnMouseOver(hObj, pObj, pMsg);
    break;
#endif
  case WM_DELETE:
    _FreeAttached(pObj); /* No return here ... WM_DefaultProc needs to be called */
  default:
    WM_DefaultProc(pMsg);
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       Exported routines:  Create
*
**********************************************************************
*/
/*********************************************************************
*
*       HEADER_Create
*/
HEADER_Handle HEADER_Create(int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags, int ExFlags) {
  return HEADER_CreateEx(x0, y0, xsize, ysize, hParent, Flags, ExFlags, Id);
}

/*********************************************************************
*
*       HEADER_CreateEx
*/
HEADER_Handle HEADER_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                              int WinFlags, int ExFlags, int Id)
{
  HEADER_Handle hObj;
  GUI_USE_PARA(ExFlags);
  /* Create the window */
  WM_LOCK();
  if ((xsize == 0) && (x0 == 0) && (y0 == 0)) {
    GUI_RECT Rect;
    WM_GetInsideRectEx(hParent, &Rect);
    xsize = Rect.x1 - Rect.x0 + 1;
    x0    = Rect.x0;
    y0    = Rect.y0;
  }
  if (ysize == 0) {
    const WIDGET_EFFECT* pEffect = WIDGET_GetDefaultEffect();
    ysize  = GUI_GetYDistOfFont(HEADER_DefaultProps.pFont);
    ysize += 2 * HEADER__DefaultBorderV;
    ysize += 2 * (unsigned)pEffect->EffectSize;
  }
  WinFlags |= WM_CF_ANCHOR_LEFT | WM_CF_ANCHOR_RIGHT;
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, &HEADER_Callback,
                                sizeof(HEADER_Obj) - sizeof(WM_Obj));
  if (hObj) {
    HEADER_Obj * pObj;
    pObj = (HEADER_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
    /* Init sub-classes */
    GUI_ARRAY_CREATE(&pObj->Columns);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, 0);
    /* init member variables */
    HEADER_INIT_ID(pObj);
    pObj->Props       = HEADER_DefaultProps;
    pObj->CapturePosX = -1;
    pObj->CaptureItem = -1;
    pObj->ScrollPos   = 0;
    pObj->DirIndicatorColumn = -1;
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "HEADER_Create failed")
  }
  WM_UNLOCK();
  return hObj;
}

/*********************************************************************
*
*       Exported routines: Global functions
*
**********************************************************************
*/
/*********************************************************************
*
*       Exported routines: Member functions
*
**********************************************************************
*/
/*********************************************************************
*
*       HEADER_SetFont
*/
void HEADER_SetFont(HEADER_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont) {
  if (hObj) {
    HEADER_Obj * pObj;
    WM_LOCK();
    pObj = HEADER_H2P(hObj);
    pObj->Props.pFont = pFont;
    HEADER_SetHeight(hObj, GUI_GetYDistOfFont(pFont) + 2 * HEADER_BORDER_V_DEFAULT + 2 * pObj->Widget.pEffect->EffectSize);
    WM_InvalidateWindow(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       HEADER_SetHeight
*/
void HEADER_SetHeight(HEADER_Handle hObj, int Height) {
  if (hObj) {
    GUI_RECT Rect;
    WM_GetClientRectEx(hObj, &Rect);
    WM_SetSize(hObj, Rect.x1 - Rect.x0 + 1, Height);
    WM_InvalidateWindow(WM_GetParent(hObj));
  }
}

/*********************************************************************
*
*       HEADER_SetTextAlign
*/
void HEADER_SetTextAlign(HEADER_Handle hObj, unsigned int Index, int Align) {
  if (hObj) {
    HEADER_Obj * pObj;
    WM_LOCK();
    pObj = HEADER_H2P(hObj);
    if (Index <= GUI_ARRAY_GetNumItems(&pObj->Columns)) {
      HEADER_COLUMN * pColumn;
      pColumn = (HEADER_COLUMN *)GUI_ARRAY_GetpItem(&pObj->Columns, Index);
      pColumn->Align = Align;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       HEADER_SetScrollPos
*/
void HEADER_SetScrollPos(HEADER_Handle hObj, int ScrollPos) {
  if (hObj && (ScrollPos >= 0)) {
    HEADER_Obj* pObj;
    WM_LOCK();
    pObj = HEADER_H2P(hObj);
    if (ScrollPos != pObj->ScrollPos) {
      pObj->ScrollPos = ScrollPos;
      WM_Invalidate(hObj);
      WM_InvalidateWindow(WM_GetParent(hObj));
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       HEADER_AddItem
*/
void HEADER_AddItem(HEADER_Handle hObj, int Width, const char * s, int Align) {
  if (hObj) {
    HEADER_Obj * pObj;
    HEADER_COLUMN Column;
    int Index;
    WM_LOCK();
    pObj = HEADER_H2P(hObj);
    if (!Width) {
      const GUI_FONT GUI_UNI_PTR * pFont = GUI_SetFont(pObj->Props.pFont);
      Width = GUI_GetStringDistX(s) + 2 * (pObj->Widget.pEffect->EffectSize + HEADER__DefaultBorderH);
      GUI_SetFont(pFont);
    }
    Column.Width    = Width;
    Column.Align    = Align;
    Column.hDrawObj = 0;
    Index = GUI_ARRAY_GetNumItems(&pObj->Columns);
    if (GUI_ARRAY_AddItem(&pObj->Columns, &Column, sizeof(HEADER_COLUMN) + strlen(s) + 1) == 0) {
      HEADER_COLUMN * pColumn;
      pObj = HEADER_H2P(hObj);
      pColumn = (HEADER_COLUMN *)GUI_ARRAY_GetpItem(&pObj->Columns, Index);
      strcpy(pColumn->acText, s);
      WM_InvalidateWindow(hObj);
      WM_InvalidateWindow(WM_GetParent(hObj));
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       HEADER_DeleteItem
*/
void HEADER_DeleteItem(HEADER_Handle hObj, unsigned Index) {
  if (hObj) {
    HEADER_Obj* pObj;
    WM_LOCK();
    pObj = HEADER_H2P(hObj);
    if (Index < GUI_ARRAY_GetNumItems(&pObj->Columns)) {
      GUI_ARRAY_DeleteItem(&pObj->Columns, Index);
      WM_InvalidateWindow(hObj);
      WM_InvalidateWindow(WM_GetParent(hObj));
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       HEADER_SetItemText
*/
void HEADER_SetItemText(HEADER_Handle hObj, unsigned int Index, const char* s) {
  if (hObj) {
    HEADER_Obj* pObj;
    WM_LOCK();
    pObj = HEADER_H2P(hObj);
    if (Index < GUI_ARRAY_GetNumItems(&pObj->Columns)) {
      HEADER_COLUMN* pColumn;
      pColumn = (HEADER_COLUMN*)GUI_ARRAY_ResizeItem(&pObj->Columns, Index, sizeof(HEADER_COLUMN) + strlen(s));
      if (pColumn) {
        strcpy(pColumn->acText, s);
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       HEADER_SetItemWidth
*/
void HEADER_SetItemWidth(HEADER_Handle hObj, unsigned int Index, int Width) {
  if (hObj && (Width >= 0)) {
    HEADER_Obj * pObj;
    WM_LOCK();
    pObj = HEADER_H2P(hObj);
    if (Index <= GUI_ARRAY_GetNumItems(&pObj->Columns)) {
      HEADER_COLUMN * pColumn;
      pColumn = (HEADER_COLUMN *)GUI_ARRAY_GetpItem(&pObj->Columns, Index);
      if (pColumn) {
        WM_MESSAGE Msg;
        pColumn->Width = Width;
        Msg.hWin  = WM_GetParent(hObj);
        Msg.MsgId = WM_NOTIFY_CLIENTCHANGE;
        Msg.hWinSrc = hObj;
        WM_InvalidateWindow(hObj);
        WM__SendMessage(Msg.hWin, &Msg);
        //WM__SendMsgNoData(WM_GetParent(hObj), WM_NOTIFY_CLIENTCHANGE);
        WM_InvalidateWindow(WM_GetParent(hObj));
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       HEADER_GetHeight
*/
int HEADER_GetHeight(HEADER_Handle hObj) {
  int Height = 0;
  if (hObj) {
    GUI_RECT Rect;
    WM_GetClientRectEx(hObj, &Rect);
    GUI_MoveRect(&Rect, -Rect.x0, -Rect.y0);
    Height = Rect.y1 - Rect.y0 + 1;
  }
  return Height;
}

/*********************************************************************
*
*       HEADER_GetItemWidth
*/
int HEADER_GetItemWidth(HEADER_Handle hObj, unsigned int Index) {
  int Width = 0;
  if (hObj) {
    HEADER_Obj * pObj;
    WM_LOCK();
    pObj = HEADER_H2P(hObj);
    if (Index <= GUI_ARRAY_GetNumItems(&pObj->Columns)) {
      HEADER_COLUMN * pColumn;
      pColumn = (HEADER_COLUMN *)GUI_ARRAY_GetpItem(&pObj->Columns, Index);
      Width = pColumn->Width;
    }
    WM_UNLOCK();
  }
  return Width;
}

/*********************************************************************
*
*       HEADER_GetNumItems
*/
int  HEADER_GetNumItems(HEADER_Handle hObj) {
  int NumCols = 0;
  if (hObj) {
    HEADER_Obj * pObj;
    WM_LOCK();
    pObj = HEADER_H2P(hObj);
    NumCols = GUI_ARRAY_GetNumItems(&pObj->Columns);
    WM_UNLOCK();
  }
  return NumCols;
}

/*********************************************************************
*
*       HEADER_SetDirIndicator
*/
void HEADER_SetDirIndicator(HEADER_Handle hObj, int Column, int Reverse) {
  if (hObj) {
    HEADER_Obj * pObj;
    WM_LOCK();
    pObj = HEADER_H2P(hObj);
    if ((pObj->DirIndicatorColumn != Column) || (pObj->DirIndicatorReverse != Reverse)) {
      pObj->DirIndicatorColumn = Column;
      pObj->DirIndicatorReverse = Reverse;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

#else /* avoid empty object files */

void HEADER_C(void);
void HEADER_C(void){}

#endif  /* #if GUI_WINSUPPORT */
