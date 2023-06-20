/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2004  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LISTVIEW.c
Purpose     : Implementation of listview widget
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_ARRAY.h"
#include <stdlib.h>
#include <string.h>
#include "LISTVIEW_Private.h"
#include "HEADER.h"
#include "WIDGET.h"
#include "SCROLLBAR.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default fonts */
#ifndef LISTVIEW_FONT_DEFAULT
  #define LISTVIEW_FONT_DEFAULT &GUI_Font13_1
#endif

/* Define colors */
#ifndef LISTVIEW_BKCOLOR0_DEFAULT
  #define LISTVIEW_BKCOLOR0_DEFAULT GUI_WHITE       /* Not selected */
#endif

#ifndef LISTVIEW_BKCOLOR1_DEFAULT
  #define LISTVIEW_BKCOLOR1_DEFAULT GUI_GRAY        /* Selected, no focus */
#endif

#ifndef LISTVIEW_BKCOLOR2_DEFAULT
  #define LISTVIEW_BKCOLOR2_DEFAULT GUI_BLUE        /* Selected, focus */
#endif

#ifndef LISTVIEW_BKCOLOR3_DEFAULT
  #define LISTVIEW_BKCOLOR3_DEFAULT GUI_LIGHTGRAY   /* Disabled */
#endif

#ifndef LISTVIEW_TEXTCOLOR0_DEFAULT
  #define LISTVIEW_TEXTCOLOR0_DEFAULT GUI_BLACK     /* Not selected */
#endif

#ifndef LISTVIEW_TEXTCOLOR1_DEFAULT
  #define LISTVIEW_TEXTCOLOR1_DEFAULT GUI_WHITE     /* Selected, no focus */
#endif

#ifndef LISTVIEW_TEXTCOLOR2_DEFAULT
  #define LISTVIEW_TEXTCOLOR2_DEFAULT GUI_WHITE     /* Selected, focus */
#endif

#ifndef LISTVIEW_TEXTCOLOR3_DEFAULT
  #define LISTVIEW_TEXTCOLOR3_DEFAULT GUI_GRAY  /* Disabled */
#endif

#ifndef LISTVIEW_GRIDCOLOR_DEFAULT
  #define LISTVIEW_GRIDCOLOR_DEFAULT GUI_LIGHTGRAY
#endif

/* Define default alignment */
#ifndef LISTVIEW_ALIGN_DEFAULT
  #define LISTVIEW_ALIGN_DEFAULT (GUI_TA_VCENTER | GUI_TA_HCENTER)
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
LISTVIEW_PROPS LISTVIEW_DefaultProps = {
  LISTVIEW_BKCOLOR0_DEFAULT,
  LISTVIEW_BKCOLOR1_DEFAULT,
  LISTVIEW_BKCOLOR2_DEFAULT,
  LISTVIEW_BKCOLOR3_DEFAULT,
  LISTVIEW_TEXTCOLOR0_DEFAULT,
  LISTVIEW_TEXTCOLOR1_DEFAULT,
  LISTVIEW_TEXTCOLOR2_DEFAULT,
  LISTVIEW_TEXTCOLOR3_DEFAULT,
  LISTVIEW_GRIDCOLOR_DEFAULT,
  LISTVIEW_FONT_DEFAULT
};

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTVIEW__GetNumRows
*/
unsigned LISTVIEW__GetNumRows(LISTVIEW_Obj* pObj) {
  return GUI_ARRAY_GetNumItems(&pObj->RowArray);
}

/*********************************************************************
*
*       LISTVIEW__GetNumColumns
*/
unsigned LISTVIEW__GetNumColumns(LISTVIEW_Obj* pObj) {
  return GUI_ARRAY_GetNumItems(&pObj->ColumnArray);
}

/*********************************************************************
*
*       LISTVIEW__GetSel
*/
int LISTVIEW__GetSel(LISTVIEW_Obj* pObj) {
  return pObj->Sel;
}

/*********************************************************************
*
*       LISTVIEW__SetSel
*/
void LISTVIEW__SetSel(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, int NewSel) {
  int NumRows = LISTVIEW__GetNumRows(pObj);
  if (NewSel >= NumRows) {
    NewSel = NumRows - 1;
  }
  if (NewSel < 0) {
    NewSel = -1;
  }
  if (NewSel != pObj->Sel) {
    LISTVIEW_ROW* pRow = (LISTVIEW_ROW*) GUI_ARRAY_GetpItem(&pObj->RowArray, NewSel);
		// Segger bug. Must check that the pointer is valid
		char pRowDisabeled = 0;
		if (pRow ) {
			 pRowDisabeled = pRow->Disabled;
		}
    if (pRowDisabeled == 0) {
      int OldSel;
      OldSel    = pObj->Sel;
      pObj->Sel = NewSel;
      if (LISTVIEW__UpdateScrollPos(hObj, pObj)) {
        LISTVIEW__InvalidateInsideArea(hObj, pObj);
      } else {
        LISTVIEW__InvalidateRow(hObj, pObj, OldSel);
        LISTVIEW__InvalidateRow(hObj, pObj, NewSel);
      }
      WM_NotifyParent(hObj, WM_NOTIFICATION_SEL_CHANGED);
    }
  }
}

/*********************************************************************
*
*       LISTVIEW__MoveSel
*
*  Moves the selection to the next valid item.
*/
void LISTVIEW__MoveSel(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, int Dir) {
  int Index, NewSel = -1, NumRows;
  Index   = LISTVIEW__GetSel(pObj);
  NumRows = LISTVIEW__GetNumRows(pObj);
  do {
    LISTVIEW_ROW* pRow;
    Index += Dir;
    if ((Index < 0) || (Index >= NumRows)) {
      break;
    }
    pRow = (LISTVIEW_ROW*) GUI_ARRAY_GetpItem(&pObj->RowArray, Index);
    if (pRow->Disabled == 0) {
      NewSel = Index;
    }
  } while (NewSel < 0);
  if (NewSel >= 0) {
    LISTVIEW__SetSel(hObj, pObj, NewSel);
  }
}

/*********************************************************************
*
*       LISTVIEW__GetRowDistY
*/
unsigned LISTVIEW__GetRowDistY(const LISTVIEW_Obj* pObj) {
  unsigned RowDistY;
  if (pObj->RowDistY) {
    RowDistY = pObj->RowDistY;
  } else {
    RowDistY = GUI_GetYDistOfFont(pObj->Props.pFont);
    if (pObj->ShowGrid) {
      RowDistY++;
    }
  }
  return RowDistY;
}

/*********************************************************************
*
*       _GetNumVisibleRows
*
* Purpose:
*   Returns the number of visible rows according the header
*   and (if exist) horizontal scrollbar.
*
* Return value:
*   Number of visible rows. If no entire row can be displayed, this
*   function will return one.
*/
static unsigned _GetNumVisibleRows(LISTVIEW_Handle hObj, const LISTVIEW_Obj* pObj) {
  unsigned RowDistY, ySize, r = 1;
  GUI_RECT Rect;
  WM_GetInsideRectExScrollbar(hObj, &Rect);
  ySize    = Rect.y1 - Rect.y0 + 1 - HEADER_GetHeight(pObj->hHeader);
  RowDistY = LISTVIEW__GetRowDistY(pObj);
  if (RowDistY) {
    r = ySize / RowDistY;
    r = (r == 0) ? 1 : r;
  }
  return r;
}

/*********************************************************************
*
*       _Paint
*/
static void _Paint(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, WM_MESSAGE* pMsg) {
  const LISTVIEW_ROW* pRow;
  GUI_RECT ClipRect, Rect;
  int NumRows, NumVisRows, NumColumns;
  int LBorder, RBorder, EffectSize;
  int xPos, yPos, Width, RowDistY;
  int Align, i, j, EndRow;
  /* Init some values */
  NumColumns = LISTVIEW__GetNumColumns(pObj);
  NumRows    = LISTVIEW__GetNumRows(pObj);
  NumVisRows = _GetNumVisibleRows(hObj, pObj);
  RowDistY   = LISTVIEW__GetRowDistY(pObj);
  LBorder    = pObj->LBorder;
  RBorder    = pObj->RBorder;
  EffectSize = pObj->Widget.pEffect->EffectSize;
  yPos       = HEADER_GetHeight(pObj->hHeader) + EffectSize;
  EndRow     = pObj->ScrollStateV.v + (((NumVisRows + 1) > NumRows) ? NumRows : NumVisRows + 1);
  /* Calculate clipping rectangle */
  ClipRect = *(const GUI_RECT*)pMsg->Data.p;
  GUI_MoveRect(&ClipRect, -pObj->Widget.Win.Rect.x0, -pObj->Widget.Win.Rect.y0);
  WM_GetInsideRectExScrollbar(hObj, &Rect);
  GUI__IntersectRect(&ClipRect, &Rect);
  /* Set drawing color, font and text mode */
  LCD_SetColor(pObj->Props.aTextColor[0]);
  GUI_SetFont(pObj->Props.pFont);
  GUI_SetTextMode(GUI_TM_TRANS);
  /* Do the drawing */
  for (i = pObj->ScrollStateV.v; i < EndRow; i++) {
    pRow = (const LISTVIEW_ROW*) GUI_ARRAY_GetpItem(&pObj->RowArray, i);
    if (pRow) {
      Rect.y0 = yPos;
      /* Break when all other rows are outside the drawing area */
      if (Rect.y0 > ClipRect.y1) {
        break;
      }
      Rect.y1 = yPos + RowDistY - 1;
      /* Make sure that we draw only when row is in drawing area */
      if (Rect.y1 >= ClipRect.y0) {
        int ColorIndex;
        /* Set background color */
        if (pRow->Disabled) {
          ColorIndex = LISTVIEW_CI_DISABLED;
        } else if (i == pObj->Sel) {
          ColorIndex = (pObj->Widget.State & WIDGET_STATE_FOCUS) ? LISTVIEW_CI_SELFOCUS : LISTVIEW_CI_SEL;
        } else {
          ColorIndex = LISTVIEW_CI_UNSEL;
        }
        LCD_SetBkColor(pObj->Props.aBkColor[ColorIndex]);
        /* Iterate over all columns */
        if (pObj->ShowGrid) {
          Rect.y1--;
        }
        xPos = EffectSize - pObj->ScrollStateH.v;
        for (j = 0; j < NumColumns; j++) {
          Width   = HEADER_GetItemWidth(pObj->hHeader, j);
          Rect.x0 = xPos;
          /* Break when all other columns are outside the drawing area */
          if (Rect.x0 > ClipRect.x1) {
            break;
          }
          Rect.x1 = xPos + Width - 1;
          /* Make sure that we draw only when column is in drawing area */
          if (Rect.x1 >= ClipRect.x0) {
            LISTVIEW_COLUMN* pColumn;
            LISTVIEW_CELL* pCell;
            pCell = (LISTVIEW_CELL*)GUI_ARRAY_GetpItem(&pRow->CellArray, j);
            if (pCell->hCellInfo) {
              LISTVIEW_CELL_INFO* pCellInfo;
              pCellInfo = (LISTVIEW_CELL_INFO*) GUI_ALLOC_h2p(pCell->hCellInfo);
              LCD_SetBkColor(pCellInfo->aBkColor[ColorIndex]);
              LCD_SetColor(pCellInfo->aTextColor[ColorIndex]);
            } else {
              LCD_SetColor(pObj->Props.aTextColor[ColorIndex]);
            }
            /* Clear background */
            GUI_ClearRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1);
            /* Draw text */
            Rect.x0 += LBorder;
            Rect.x1 -= RBorder;
            pColumn = (LISTVIEW_COLUMN*) GUI_ARRAY_GetpItem(&pObj->ColumnArray, j);
            Align = pColumn->Align;
            GUI_DispStringInRect(pCell->acText, &Rect, Align);
            if (pCell->hCellInfo) {
              LCD_SetBkColor(pObj->Props.aBkColor[ColorIndex]);
            }
          }
          xPos += Width;
        }
        /* Clear unused area to the right of items */
        if (xPos <= ClipRect.x1) {
          GUI_ClearRect(xPos, Rect.y0, ClipRect.x1, Rect.y1);
        }
      }
      yPos += RowDistY;
    }
  }
  /* Clear unused area below items */
  if (yPos <= ClipRect.y1) {
    LCD_SetBkColor(pObj->Props.aBkColor[0]);
    GUI_ClearRect(ClipRect.x0, yPos, ClipRect.x1, ClipRect.y1);
  }
  /* Draw grid */
  if (pObj->ShowGrid) {
    LCD_SetColor(pObj->Props.GridColor);
    yPos = HEADER_GetHeight(pObj->hHeader) + EffectSize - 1;
    for (i = 0; i < NumVisRows; i++) {
      yPos += RowDistY;
      /* Break when all other rows are outside the drawing area */
      if (yPos > ClipRect.y1) {
        break;
      }
      /* Make sure that we draw only when row is in drawing area */
      if (yPos >= ClipRect.y0) {
        GUI_DrawHLine(yPos, ClipRect.x0, ClipRect.x1);
      }
    }
    xPos = EffectSize - pObj->ScrollStateH.v;
    for (i = 0; i < NumColumns; i++) {
      xPos += HEADER_GetItemWidth(pObj->hHeader, i);
      /* Break when all other columns are outside the drawing area */
      if (xPos > ClipRect.x1) {
        break;
      }
      /* Make sure that we draw only when column is in drawing area */
      if (xPos >= ClipRect.x0) {
        GUI_DrawVLine(xPos, ClipRect.y0, ClipRect.y1);
      }
    }
  }
  /* Draw the effect */
  WIDGET__EFFECT_DrawDown(&pObj->Widget);
}

/*********************************************************************
*
*       LISTVIEW__InvalidateInsideArea
*/
void LISTVIEW__InvalidateInsideArea(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj) {
  GUI_RECT Rect;
  int HeaderHeight;
  HeaderHeight = HEADER_GetHeight(pObj->hHeader);
  WM_GetInsideRectExScrollbar(hObj, &Rect);
  Rect.y0 += HeaderHeight;
  WM_InvalidateRect(hObj, &Rect);
}

/*********************************************************************
*
*       LISTVIEW__InvalidateRow
*/
void LISTVIEW__InvalidateRow(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, int Sel) {
  if (Sel >= 0) {
    GUI_RECT Rect;
    int HeaderHeight, RowDistY;
    HeaderHeight = HEADER_GetHeight(pObj->hHeader);
    RowDistY     = LISTVIEW__GetRowDistY(pObj);
    WM_GetInsideRectExScrollbar(hObj, &Rect);
    Rect.y0 += HeaderHeight + (Sel - pObj->ScrollStateV.v) * RowDistY;
    Rect.y1  = Rect.y0 + RowDistY - 1;
    WM_InvalidateRect(hObj, &Rect);
  }
}

/*********************************************************************
*
*       _SetSelFromPos
*/
static void _SetSelFromPos(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, const GUI_PID_STATE* pState) {
  GUI_RECT Rect;
  int x, y, HeaderHeight;
  HeaderHeight = HEADER_GetHeight(pObj->hHeader);
  WM_GetInsideRectExScrollbar(hObj, &Rect);
  x = pState->x - Rect.x0;
  y = pState->y - Rect.y0 - HeaderHeight;
  Rect.x1 -= Rect.x0;
  Rect.y1 -= Rect.y0;
  if ((x >= 0) && (x <= Rect.x1) && (y >= 0) && (y <= (Rect.y1 - HeaderHeight))) {
    unsigned Sel;
    Sel = (y / LISTVIEW__GetRowDistY(pObj)) + pObj->ScrollStateV.v;
    if (Sel < LISTVIEW__GetNumRows(pObj)) {
      LISTVIEW__SetSel(hObj, pObj, Sel);
    }
  }
}

/*********************************************************************
*
*       _NotifyOwner
*
* Purpose:
*   Notify owner of the window.
*   If no owner is registered, the parent is considered owner.
*/
static void _NotifyOwner(WM_HWIN hObj, int Notification) {
  WM_MESSAGE Msg = {0};
  WM_HWIN hOwner;
  LISTVIEW_Obj* pObj    = LISTVIEW_H2P(hObj);
  hOwner = pObj->hOwner ? pObj->hOwner : WM_GetParent(hObj);
  Msg.MsgId   = WM_NOTIFY_PARENT;
  Msg.Data.v  = Notification;
  Msg.hWinSrc = hObj;
  WM__SendMessage(hOwner, &Msg);
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, WM_MESSAGE*pMsg) {
  int Notification;
  const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
  GUI_USE_PARA(pObj);
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      _SetSelFromPos(hObj, pObj, pState);
      Notification = WM_NOTIFICATION_CLICKED;
      WM_SetFocus(hObj);
    } else {
      Notification = WM_NOTIFICATION_RELEASED;
    }
  } else {
    Notification = WM_NOTIFICATION_MOVED_OUT;
  }
  _NotifyOwner(hObj, Notification);
}

/*********************************************************************
*
*       _GetXSize
*
* Purpose:
*   Returns the width of the inside listview area.
*/
static int _GetXSize(LISTVIEW_Handle hObj) {
  GUI_RECT Rect;
  WM_GetInsideRectExScrollbar(hObj, &Rect);
  return Rect.x1 + 1;
}

/*********************************************************************
*
*       _GetHeaderWidth
*
* Purpose:
*   Returns the width of all items in header.
*
* Return value:
*   NumItems > 0:  width of all items.
*   NumItems = 0:  1 (to avoid problem with horizontal scrollbar)
*/
static int _GetHeaderWidth(LISTVIEW_Obj* pObj, HEADER_Handle hHeader) {
  int NumItems, i, r = 1;
  NumItems = HEADER_GetNumItems(hHeader);
  if (NumItems) {
    for (i = 0, r = 0; i < NumItems; i++) {
      r += HEADER_GetItemWidth(hHeader, i);
    }
  }
  if (pObj->ScrollStateH.v > (r - pObj->ScrollStateH.PageSize)) {
    r += pObj->ScrollStateH.PageSize - (r - pObj->ScrollStateH.v);
  }
  return r;
}

/*********************************************************************
*
*       LISTVIEW__UpdateScrollPos
*
* Purpose:
*   Checks whether if we must scroll up or scroll down to ensure
*   that selection is in the visible area. This function also
*   makes sure that scroll positions are in valid ranges.
*
* Return value:
*   Difference between old and new vertical scroll pos.
*/
int LISTVIEW__UpdateScrollPos(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj) {
  int PrevScrollStateV;
  PrevScrollStateV = pObj->ScrollStateV.v;
  if (pObj->Sel >= 0) {
    WM_CheckScrollPos(&pObj->ScrollStateV, pObj->Sel, 0, 0);
  } else {
    WM_CheckScrollBounds(&pObj->ScrollStateV);
  }
  WM_CheckScrollBounds(&pObj->ScrollStateH);
  WIDGET__SetScrollState(hObj, &pObj->ScrollStateV, &pObj->ScrollStateH);
  return pObj->ScrollStateV.v - PrevScrollStateV;
}

/*********************************************************************
*
*       LISTVIEW__UpdateScrollParas
*
* Purpose:
*   Calculates number of items and page size of both vertical
*   and horizontal scrollbar. After this LISTVIEW__UpdateScrollPos will
*   be called to ensure scroll positions are in valid ranges.
*/
int LISTVIEW__UpdateScrollParas(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj) {
  int NumRows;
  NumRows = LISTVIEW__GetNumRows(pObj);
  /* update vertical scrollbar */
  pObj->ScrollStateV.PageSize = _GetNumVisibleRows(hObj, pObj);
  pObj->ScrollStateV.NumItems = (NumRows) ? NumRows : 1;
  /* update horizontal scrollbar */
  pObj->ScrollStateH.PageSize = _GetXSize(hObj);
  pObj->ScrollStateH.NumItems = _GetHeaderWidth(pObj, pObj->hHeader);
  return LISTVIEW__UpdateScrollPos(hObj, pObj);
}

/*********************************************************************
*
*       _FreeAttached
*
* Purpose:
*   Delete attached objects (if any).
*/
static void _FreeAttached(LISTVIEW_Obj * pObj) {
  int i, j, NumRows, NumColumns;
  NumRows    = LISTVIEW__GetNumRows(pObj);
  NumColumns = LISTVIEW__GetNumColumns(pObj);
  for (i = 0; i < NumRows; i++) {
    LISTVIEW_ROW* pRow;
    pRow = (LISTVIEW_ROW*) GUI_ARRAY_GetpItem(&pObj->RowArray, i);
    /* Delete attached info items */
    for (j = 0; j < NumColumns; j++) {
      LISTVIEW_CELL* pCell;
      pCell = (LISTVIEW_CELL*) GUI_ARRAY_GetpItem(&pRow->CellArray, j);
      if (pCell->hCellInfo) {
        GUI_ALLOC_Free(pCell->hCellInfo);
      }
    }
    /* Delete row */
    GUI_ARRAY_Delete(&pRow->CellArray);
  }
  GUI_ARRAY_Delete(&pObj->ColumnArray);
  GUI_ARRAY_Delete(&pObj->RowArray);
}

/*********************************************************************
*
*       _AddKey
*
* Returns: 1 if Key has been consumed
*          0 else
*/
static int _AddKey(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, int Key) {
  switch (Key) {
  case GUI_KEY_DOWN:
    LISTVIEW__MoveSel(hObj, pObj, 1);
    return 1;               /* Key has been consumed */
  case GUI_KEY_UP:
    LISTVIEW__MoveSel(hObj, pObj, -1);
    return 1;               /* Key has been consumed */
  }
  return 0;                 /* Key has NOT been consumed */
}

/*********************************************************************
*
*       Exported routines:  Create
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTVIEW_Callback
*/
void LISTVIEW_Callback (WM_MESSAGE *pMsg) {
  LISTVIEW_Handle hObj;
  LISTVIEW_Obj* pObj;
  WM_SCROLL_STATE ScrollState;
  hObj = pMsg->hWin;
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  pObj = LISTVIEW_H2P(hObj);
  switch (pMsg->MsgId) {
  case WM_NOTIFY_CLIENTCHANGE:
  case WM_SIZE:
    LISTVIEW__UpdateScrollParas(hObj, pObj);
    return;
  case WM_NOTIFY_PARENT:
    switch (pMsg->Data.v) {
    case WM_NOTIFICATION_CHILD_DELETED:
      /* make sure we do not send any messages to the header child once it has been deleted */
      if (pMsg->hWinSrc == pObj->hHeader) {
        pObj->hHeader = 0;
      }
      break;
    case WM_NOTIFICATION_VALUE_CHANGED:
      if (pMsg->hWinSrc == WM_GetScrollbarV(hObj)) {
        WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
        pObj->ScrollStateV.v = ScrollState.v;
        LISTVIEW__InvalidateInsideArea(hObj, pObj);
        _NotifyOwner(hObj, WM_NOTIFICATION_SCROLL_CHANGED);
      } else if (pMsg->hWinSrc == WM_GetScrollbarH(hObj)) {
        WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
        pObj->ScrollStateH.v = ScrollState.v;
        LISTVIEW__UpdateScrollParas(hObj, pObj);
        HEADER_SetScrollPos(pObj->hHeader, pObj->ScrollStateH.v);
        _NotifyOwner(hObj, WM_NOTIFICATION_SCROLL_CHANGED);
      }
      break;
    case WM_NOTIFICATION_SCROLLBAR_ADDED:
      LISTVIEW__UpdateScrollParas(hObj, pObj);
      break;
    }
    return;
  case WM_PAINT:
    _Paint(hObj, pObj, pMsg);
    return;
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    return;        /* Important: message handled ! */
  case WM_KEY:
    if (((const WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt > 0) {
      int Key;
      Key = ((const WM_KEY_INFO*)(pMsg->Data.p))->Key;
      if (_AddKey(hObj, pObj, Key)) {
        return;
      }
    }
    break;  /* No return here ... WM_DefaultProc needs to be called */
  case WM_DELETE:
    _FreeAttached(pObj);
    break;  /* No return here ... WM_DefaultProc needs to be called */
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       Exported routines:  Create
*
**********************************************************************
*/

/* Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions */

/*********************************************************************
*
*       LISTVIEW_CreateEx
*/
LISTVIEW_Handle LISTVIEW_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                  int WinFlags, int ExFlags, int Id)
{
  LISTVIEW_Handle hObj;
  GUI_USE_PARA(ExFlags);
  /* Create the window */
  if ((xsize == 0) && (ysize == 0) && (x0 == 0) && (y0 == 0)) {
    GUI_RECT Rect;
    WM_GetClientRectEx(hParent, &Rect);
    xsize = Rect.x1 - Rect.x0 + 1;
    ysize = Rect.y1 - Rect.y0 + 1;
  }
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, &LISTVIEW_Callback,
                                sizeof(LISTVIEW_Obj) - sizeof(WM_Obj));
  if (hObj) {
    LISTVIEW_Obj* pObj;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    /* Init sub-classes */
    GUI_ARRAY_CREATE(&pObj->RowArray);
    GUI_ARRAY_CREATE(&pObj->ColumnArray);
    /* Init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
    /* Init member variables */
    LISTVIEW_INIT_ID(pObj);
    pObj->Props     = LISTVIEW_DefaultProps;
    pObj->ShowGrid  = 0;
    pObj->RowDistY  = 0;
    pObj->Sel       = -1;
    pObj->LBorder   = 1;
    pObj->RBorder   = 1;
    pObj->hHeader   = HEADER_CreateEx(0, 0, 0, 0, hObj, WM_CF_SHOW, 0, 0);
    LISTVIEW__UpdateScrollParas(hObj, pObj);
    WM_UNLOCK();
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "LISTVIEW_Create failed")
  }
  return hObj;
}

/*********************************************************************
*
*       Exported routines: Member functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTVIEW_IncSel
*/
void LISTVIEW_IncSel(LISTVIEW_Handle hObj) {
  if (hObj) {
    LISTVIEW_Obj* pObj;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    LISTVIEW__MoveSel(hObj, pObj, 1);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       LISTVIEW_DecSel
*/
void LISTVIEW_DecSel(LISTVIEW_Handle hObj) {
  if (hObj) {
    LISTVIEW_Obj* pObj;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    LISTVIEW__MoveSel(hObj, pObj, -1);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       LISTVIEW_AddColumn
*/
void LISTVIEW_AddColumn(LISTVIEW_Handle hObj, int Width, const char * s, int Align) {
  if (hObj) {
    LISTVIEW_Obj* pObj;
    LISTVIEW_COLUMN Column;
    unsigned NumRows;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    HEADER_AddItem(pObj->hHeader, Width, s, Align);
    Column.Align = Align;
    GUI_ARRAY_AddItem(&pObj->ColumnArray, &Column, sizeof(LISTVIEW_COLUMN));
    NumRows = LISTVIEW__GetNumRows(pObj);
    if (NumRows) {
      LISTVIEW_ROW* pRow;
      unsigned i;
      for (i = 0; i < NumRows; i++) {
        pRow = (LISTVIEW_ROW*) GUI_ARRAY_GetpItem(&pObj->RowArray, i);
        GUI_ARRAY_AddItem(&pRow->CellArray, NULL, sizeof(LISTVIEW_CELL));
      }
    }
    LISTVIEW__UpdateScrollParas(hObj, pObj);
    LISTVIEW__InvalidateInsideArea(hObj, pObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       LISTVIEW_AddRow
*/
void LISTVIEW_AddRow(LISTVIEW_Handle hObj, const GUI_ConstString* ppText) {
  if (hObj) {
    LISTVIEW_Obj* pObj;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    /* Add row item to the GUI_ARRAY */
    if (GUI_ARRAY_AddItem(&pObj->RowArray, NULL, sizeof(LISTVIEW_ROW)) == 0) {
      LISTVIEW_ROW* pRow;
      int i, RowIndex, NumColumns, NumBytes;
      const char* s;
      RowIndex   = LISTVIEW__GetNumRows(pObj) - 1;
      NumColumns = LISTVIEW__GetNumColumns(pObj);
      pRow       = (LISTVIEW_ROW*) GUI_ARRAY_GetpItem(&pObj->RowArray, RowIndex);
      GUI_ARRAY_CREATE(&pRow->CellArray);
      /* Add columns for the new row */
      for (i = 0; i < NumColumns; i++) {
        LISTVIEW_CELL* pCell;
        s = (ppText) ? *ppText++ : 0;
        if (s == 0) {
          ppText = 0;
        }
        NumBytes = GUI__strlen(s) + 1;     /* 0 if no string is specified (s == NULL) */
        GUI_ARRAY_AddItem(&pRow->CellArray, NULL, sizeof(LISTVIEW_CELL) + NumBytes);
        pCell = (LISTVIEW_CELL*) GUI_ARRAY_GetpItem(&pRow->CellArray, i);
        if (NumBytes > 1) {
          strcpy(pCell->acText, s);
        }
      }
      LISTVIEW__UpdateScrollParas(hObj, pObj);
      LISTVIEW__InvalidateRow(hObj, pObj, RowIndex);
    }
    WM_UNLOCK();
  }
}

#else
  void LISTVIEW_C(void);
  void LISTVIEW_C(void) {}
#endif  /* #if GUI_WINSUPPORT */
/*********************************************************************
*				Added by EHS 5/11/03
*       LISTVIEW_SetItemTextWithColor
*/
void LISTVIEW_SetItemTextWithColor(LISTVIEW_Handle hObj, unsigned Column, unsigned Row, const char *MyStr, GUI_COLOR FgColor, GUI_COLOR BkColor)
{
	if ( hObj ) {
		LISTVIEW_SetItemText(hObj, Column, Row, MyStr);
		LISTVIEW_SetItemTextColor(hObj,Column, Row, 0, FgColor);
    LISTVIEW_SetItemBkColor(hObj,Column,Row, 0, BkColor);
		LISTVIEW_SetItemTextColor(hObj,Column, Row, 2, BkColor);
    LISTVIEW_SetItemBkColor(hObj,Column,Row, 2, FgColor);
	}
}



/*************************** End of file ****************************/
