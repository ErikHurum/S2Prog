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
File        : MULTIPAGE.c
Purpose     : Implementation of MULTIPAGE widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_Protected.h"
#include "MULTIPAGE_Private.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define MAX(a, b)	((a > b) ? a : b)

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/
 
/* Define default fonts */
#ifndef MULTIPAGE_FONT_DEFAULT
  #define MULTIPAGE_FONT_DEFAULT        &GUI_Font13_1
#endif

#ifndef MULTIPAGE_ALIGN_DEFAULT
  #define MULTIPAGE_ALIGN_DEFAULT       (MULTIPAGE_ALIGN_LEFT | MULTIPAGE_ALIGN_TOP)
#endif

#ifndef MULTIPAGE_BKCOLOR0_DEFAULT
  #define MULTIPAGE_BKCOLOR0_DEFAULT    0xD0D0D0 /* disabled page */
#endif

#ifndef MULTIPAGE_BKCOLOR1_DEFAULT
  #define MULTIPAGE_BKCOLOR1_DEFAULT    0xC0C0C0 /* enabled page */
#endif

#ifndef MULTIPAGE_TEXTCOLOR0_DEFAULT
  #define MULTIPAGE_TEXTCOLOR0_DEFAULT  0x808080 /* disabled page */
#endif

#ifndef MULTIPAGE_TEXTCOLOR1_DEFAULT
  #define MULTIPAGE_TEXTCOLOR1_DEFAULT  0x000000 /* enabled page */
#endif

/*********************************************************************
*
*       Private data
*
**********************************************************************
*/
GUI_COLOR MULTIPAGE__aEffectColor[] = {
  0xFFFFFF, 0x555555
};

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
MULTIPAGE_PROPS MULTIPAGE__DefaultProps = {
  MULTIPAGE_FONT_DEFAULT,
  MULTIPAGE_ALIGN_DEFAULT,
  MULTIPAGE_BKCOLOR0_DEFAULT,
  MULTIPAGE_BKCOLOR1_DEFAULT,
  MULTIPAGE_TEXTCOLOR0_DEFAULT,
  MULTIPAGE_TEXTCOLOR1_DEFAULT
};

/*********************************************************************
*
*       Static code, helper functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _AddScrollbar
*/
static void _AddScrollbar(MULTIPAGE_Handle hObj, MULTIPAGE_Obj* pObj, int x, int y, int w, int h) {
  SCROLLBAR_Handle hScroll;
  if ((hScroll = WM_GetScrollbarH(hObj)) == 0) {
    if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
      hScroll = SCROLLBAR_Create(x, y, w, h, hObj, GUI_ID_HSCROLL, WM_CF_SHOW, SCROLLBAR_CF_VERTICAL);
    } else {
      hScroll = SCROLLBAR_Create(x, y, w, h, hObj, GUI_ID_HSCROLL, WM_CF_SHOW, 0);
    }
    pObj = (MULTIPAGE_Obj *)GUI_ALLOC_h2p(hObj); /* Pointer recalculation required */
    WIDGET_SetEffect(hScroll, pObj->Widget.pEffect);
  } else {
    WM_MoveChildTo(hScroll, x, y);
    WM_SetSize(hScroll, w, h);
  }
  pObj->Widget.State |= MULTIPAGE_STATE_SCROLLMODE;
}

/*********************************************************************
*
*       _SetScrollbar
*/
static void _SetScrollbar(MULTIPAGE_Handle hObj, MULTIPAGE_Obj* pObj, int NumItems) {
  SCROLLBAR_Handle hScroll;
  hScroll = WM_GetScrollbarH(hObj);
  SCROLLBAR_SetNumItems(hScroll, NumItems);
  SCROLLBAR_SetPageSize(hScroll, 1);
  if (pObj->ScrollState >= NumItems) {
    pObj->ScrollState = 0;
  }
  SCROLLBAR_SetValue(hScroll, pObj->ScrollState);
}

/*********************************************************************
*
*       _ShowPage
*/
static void _ShowPage(MULTIPAGE_Obj* pObj, unsigned Index) {
  WM_HWIN hWin = 0;
  WM_HWIN hChild;
  WM_Obj* pChild;
  WM_Obj* pClient = WM_H2P(pObj->hClient);
  if (Index < (unsigned)pObj->Handles.NumItems) {
    MULTIPAGE_PAGE* pPage;
    pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
    hWin = pPage->hWin;
  }
  for (hChild = pClient->hFirstChild; hChild; hChild = pChild->hNext) {
    pChild = WM_H2P(hChild);
    if (hChild == hWin) {
      WM_ShowWindow(hChild);
      WM_SetFocus(hChild);
    } else {
      WM_HideWindow(hChild);
    }
  }
}

/*********************************************************************
*
*       _SetEnable
*/
static void _SetEnable(MULTIPAGE_Obj* pObj, unsigned Index, int State) {
  if (Index < (unsigned)pObj->Handles.NumItems) {
    MULTIPAGE_PAGE* pPage;
    pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
    if (State) {
      pPage->Status |= MULTIPAGE_STATE_ENABLED;
    } else {
      pPage->Status &= ~MULTIPAGE_STATE_ENABLED;
    }
  }
}

/*********************************************************************
*
*       _GetEnable
*/
static int _GetEnable(MULTIPAGE_Obj* pObj, unsigned Index) {
  int r = 0;
  if (Index < (unsigned)pObj->Handles.NumItems) {
    MULTIPAGE_PAGE* pPage;
    pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
    r = (pPage->Status & MULTIPAGE_STATE_ENABLED) ? 1 : 0;
  }
  return r;
}

/*********************************************************************
*
*       _AdjustRect
*/
static void _AdjustRect(MULTIPAGE_Obj * pObj, GUI_RECT * pRect) {
  if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
    if (pObj->Props.Align & MULTIPAGE_ALIGN_BOTTOM) {
      pRect->x0 += GUI_GetYSizeOfFont(pObj->Props.pFont) + 6;
    } else {
      pRect->x1 -= GUI_GetYSizeOfFont(pObj->Props.pFont) + 6;
    }
  } else {
    if (pObj->Props.Align & MULTIPAGE_ALIGN_BOTTOM) {
      pRect->y1 -= GUI_GetYSizeOfFont(pObj->Props.pFont) + 6;
    } else {
      pRect->y0 += GUI_GetYSizeOfFont(pObj->Props.pFont) + 6;
    }
  }
}

/*********************************************************************
*
*       _CalcBorderRect
*
*  Calculates the border rect of the client area.
*/
static void _CalcBorderRect(MULTIPAGE_Obj* pObj, GUI_RECT* pRect) {
  WM__GetClientRectWin(&pObj->Widget.Win, pRect);
  _AdjustRect(pObj, pRect);
}

/*********************************************************************
*
*       _GetPageSizeX
*
*  Returns the width of a page item.
*/
static int _GetPageSizeX(MULTIPAGE_Obj* pObj, unsigned Index) {
  int r = 0;
  if (Index < (unsigned)pObj->Handles.NumItems) {
    MULTIPAGE_PAGE* pPage;
    GUI_SetFont(pObj->Props.pFont);
    pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
    r = GUI_GetStringDistX(&pPage->acText) + 10;
  }
  return r;
}

/*********************************************************************
*
*       _GetPagePosX
*
*  Returns the x-position of a page item.
*/
static int _GetPagePosX(MULTIPAGE_Obj* pObj, unsigned Index) {
  unsigned i, r = 0;
  for (i = 0; i < Index; i++) {
    r += _GetPageSizeX(pObj, i);
  }
  return r;
}

/*********************************************************************
*
*       _GetTextWidth
*
*  Returns the width of all text items.
*/
static int _GetTextWidth(MULTIPAGE_Obj* pObj) {
  return _GetPagePosX(pObj, pObj->Handles.NumItems);
}

/*********************************************************************
*
*       _GetTextRect
*/
static void _GetTextRect(MULTIPAGE_Obj* pObj, GUI_RECT* pRect) {
  GUI_RECT rBorder;
  int Width, Height;
  Height = GUI_GetYSizeOfFont(pObj->Props.pFont) + 6;
  _CalcBorderRect(pObj, &rBorder);
  if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
    /* Calculate X-Position of text item */
    if (pObj->Props.Align & MULTIPAGE_ALIGN_BOTTOM) {
      pRect->x0 = 0;
    } else {
      pRect->x0 = rBorder.x1;
    }
    pRect->x1 = pRect->x0 + Height;
    /* Calculate width of text items */
    if (pObj->Widget.State & MULTIPAGE_STATE_SCROLLMODE) {
      Width = rBorder.y1 - ((Height * 3) >> 1) - 3;
    } else {
      Width = _GetTextWidth(pObj);
    }
    /* Calculate Y-Position of text item */
    if (pObj->Props.Align & MULTIPAGE_ALIGN_RIGHT) {
      pRect->y0 = rBorder.y1 - Width;
      pRect->y1 = rBorder.y1;
    } else {
      pRect->y0 = 0;
      pRect->y1 = Width;
    }
  } else {
    /* Calculate Y-Position of text item */
    if (pObj->Props.Align & MULTIPAGE_ALIGN_BOTTOM) {
      pRect->y0 = rBorder.y1;
    } else {
      pRect->y0 = 0;
    }
    pRect->y1 = pRect->y0 + Height;
    /* Calculate width of text items */
    if (pObj->Widget.State & MULTIPAGE_STATE_SCROLLMODE) {
      Width = rBorder.x1 - ((Height * 3) >> 1) - 3;
    } else {
      Width = _GetTextWidth(pObj);
    }
    /* Calculate X-Position of text item */
    if (pObj->Props.Align & MULTIPAGE_ALIGN_RIGHT) {
      pRect->x0 = rBorder.x1 - Width;
      pRect->x1 = rBorder.x1;
    } else {
      pRect->x0 = 0;
      pRect->x1 = Width;
    }
  }
}

/*********************************************************************
*
*       Static code, drawing functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _Paint
*/
static void _Paint(MULTIPAGE_Obj* pObj) {
  GUI_RECT rBorder;
  GUI_RECT rText;
  #if (!WM_SUPPORT_TRANSPARENCY)
    int y0_Clear, y1_Clear, x0_Clear, x1_Clear;
  #endif
  /* Get rectangle of text items */
  _GetTextRect(pObj, &rText);
  #if (!WM_SUPPORT_TRANSPARENCY)
    /* Calculate the y-positions of the rectangle which needs to
     * to be cleared if the widget is non transparent. Note that 
     * these positions are not the same as the text item positions,
     * because the text rectangle overlaps the border by 1 pixel
     * to make sure, the text items are joined with the inner part.
     */
    if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
      if (pObj->Props.Align & MULTIPAGE_ALIGN_BOTTOM) {
        x0_Clear = rText.x0;
        x1_Clear = rText.x1 - 1;
      } else {
        x0_Clear = rText.x0 + 1;
        x1_Clear = rText.x1;
      }
    } else {
      if (pObj->Props.Align & MULTIPAGE_ALIGN_BOTTOM) {
        y0_Clear = rText.y0 + 1;
        y1_Clear = rText.y1;
      } else {
        y0_Clear = rText.y0;
        y1_Clear = rText.y1 - 1;
      }
    }
  #endif
  /* Draw border of multipage */
  _CalcBorderRect(pObj, &rBorder);
  pObj->Widget.pEffect->pfDrawUpRect(&rBorder);
  /* Draw text items */
  if (pObj->Handles.NumItems > 0) {
    MULTIPAGE_PAGE* pPage;
    GUI_RECT rClip;
    int i, w = 0, TextPos = 0;
    if (pObj->Widget.State & MULTIPAGE_STATE_SCROLLMODE) {
      if (pObj->Props.Align & MULTIPAGE_ALIGN_RIGHT) {
        TextPos = -_GetPagePosX(pObj, pObj->ScrollState);
      } else {
        TextPos = -_GetPagePosX(pObj, pObj->ScrollState);
      }
    }
    #if (!WM_SUPPORT_TRANSPARENCY)
      /* Clear the area between text rectangle and widget border */
      GUI_SetColor(WM_GetBkColor(pObj->Widget.Win.hParent));
      if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
        if (pObj->Props.Align & MULTIPAGE_ALIGN_RIGHT) {
          GUI_FillRect(x0_Clear, 0, x1_Clear, rText.y0 - 1);
        } else {
          GUI_FillRect(x0_Clear, rText.y1 + 1, x1_Clear, pObj->Widget.Win.Rect.y1);
        }
      } else {
        if (pObj->Props.Align & MULTIPAGE_ALIGN_RIGHT) {
          GUI_FillRect(0, y0_Clear, rText.x0 - 1, y1_Clear);
        } else {
          GUI_FillRect(rText.x1 + 1, y0_Clear, pObj->Widget.Win.Rect.x1, y1_Clear);
        }
      }
    #endif
    rClip = rText;
    if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
      rClip.x0 = rText.x0 - 1;
      rClip.x1 = rText.x1 + 1;
    } else {
      rClip.y0 = rText.y0 - 1;
      rClip.y1 = rText.y1 + 1;
    }
    WM_SetUserClipRect(&rClip);
    GUI_SetFont(pObj->Props.pFont);
    for (i = 0; i < pObj->Handles.NumItems; i++) {
      pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, i);
      TextPos += w;
      w   = GUI_GetStringDistX(&pPage->acText) + 10;
      pObj->pfDrawTextItem(pObj, &pPage->acText, i, &rText, TextPos, w, (pPage->Status & MULTIPAGE_STATE_ENABLED) ? 1 : 0);
    }    
    #if (!WM_SUPPORT_TRANSPARENCY)
      /* Clear the area between last text item and widget border */
      GUI_SetColor(WM_GetBkColor(pObj->Widget.Win.hParent));
      if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
        GUI_FillRect(x0_Clear, rText.y0 + TextPos + w + 1, x1_Clear, pObj->Widget.Win.Rect.y1);
      } else {
        GUI_FillRect(rText.x0 + TextPos + w + 1, y0_Clear, pObj->Widget.Win.Rect.x1, y1_Clear);
      }
    #endif
    WM_SetUserClipRect(NULL);
  #if (!WM_SUPPORT_TRANSPARENCY)
  } else {
    /* Clear the unused text item area */
    GUI_SetColor(WM_GetBkColor(pObj->Widget.Win.hParent));
    if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
      GUI_FillRect(x0_Clear, 0, x1_Clear, pObj->Widget.Win.Rect.y1);
    } else {
      GUI_FillRect(0, y0_Clear, pObj->Widget.Win.Rect.x1, y1_Clear);
    }
  #endif
  }
}

/*********************************************************************
*
*       _ClickedOnMultipage
*/
static int _ClickedOnMultipage(MULTIPAGE_Handle hObj, MULTIPAGE_Obj* pObj, int x, int y) {
  GUI_RECT rText;
  _GetTextRect(pObj, &rText);
  if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
    if ((x >= rText.x0) && (x <= rText.x1)) {
      if ((pObj->Handles.NumItems > 0) && (y >= rText.y0) && (y <= rText.y1)) {
        int i, w = 0, y0 = rText.y0;
        /* Check if another page must be selected */
        if (pObj->Widget.State & MULTIPAGE_STATE_SCROLLMODE) {
          y0 -= _GetPagePosX(pObj, pObj->ScrollState);
        }
        for (i = 0; i < pObj->Handles.NumItems; i++) {
          y0 += w;
          w   = _GetPageSizeX(pObj, i);
          if (y >= y0 && y <= (y0 + w - 1)) {
            MULTIPAGE_SelectPage(hObj, i);
            WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
            return 1;
          }
        }
      }
      return 0;
    }
  } else {
    if ((y >= rText.y0) && (y <= rText.y1)) {
      if ((pObj->Handles.NumItems > 0) && (x >= rText.x0) && (x <= rText.x1)) {
        int i, w = 0, x0 = rText.x0;
        /* Check if another page must be selected */
        if (pObj->Widget.State & MULTIPAGE_STATE_SCROLLMODE) {
          x0 -= _GetPagePosX(pObj, pObj->ScrollState);
        }
        for (i = 0; i < pObj->Handles.NumItems; i++) {
          x0 += w;
          w   = _GetPageSizeX(pObj, i);
          if (x >= x0 && x <= (x0 + w - 1)) {
            MULTIPAGE_SelectPage(hObj, i);
            WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
            return 1;
          }
        }
      }
      return 0;
    }
  }
  return 1;
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(MULTIPAGE_Handle hObj, MULTIPAGE_Obj* pObj, WM_MESSAGE*pMsg) {
  GUI_PID_STATE* pState;
  int Notification;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    pState = (GUI_PID_STATE*)pMsg->Data.p;
    if (pState->Pressed) {
      int x = pState->x;
      int y = pState->y;
      if (!_ClickedOnMultipage(hObj, pObj, x, y)) {
        WM_HWIN hBelow;
        x += WM_GetWindowOrgX(hObj);
        y += WM_GetWindowOrgY(hObj);
        hBelow = WM_Screen2hWinEx(hObj, x, y);
        if ((hBelow) && (hBelow != hObj)) {
          pState->x = x - WM_GetWindowOrgX(hBelow);
          pState->y = y - WM_GetWindowOrgY(hBelow);
          pMsg->hWin = hBelow;
          (*WM_H2P(hBelow)->cb)(pMsg);
        }
      } else {
        WM_BringToTop(hObj);
      }
      Notification = WM_NOTIFICATION_CLICKED;
    } else {
      Notification = WM_NOTIFICATION_RELEASED;
    }
  } else {
    Notification = WM_NOTIFICATION_MOVED_OUT;
  }
  WM_NotifyParent(hObj, Notification);
}

/*********************************************************************
*
*       _MoveSel
*
* Purpose:
*   Moves the selection into the given direction.
*
* Parameters:
*   hObj, pObj - Obvious
*   Dir        - +1 moves the selection to the next selectable page
*                -1 moves the selection to the previous selectable page
*/
static void _MoveSel(MULTIPAGE_Handle hObj, MULTIPAGE_Obj * pObj, int Dir) {
  int Sel, NewSel, ScrollPos, NumItems;
  SCROLLBAR_Handle hScroll;
  hScroll  = WM_GetScrollbarH(hObj);
  NewSel   = ScrollPos = -1;
  NumItems = pObj->Handles.NumItems;
  for (Sel = pObj->Selection + Dir; (Sel >= 0) && (Sel < NumItems) && (NewSel == -1); Sel += Dir) {
    if (_GetEnable(pObj, Sel)) {
      NewSel = Sel;
    }
  }
  if (NewSel >= 0) {
    MULTIPAGE_SelectPage(hObj, NewSel);
    ScrollPos = NewSel;
  } else {
    ScrollPos = pObj->ScrollState + Dir;
  }
  if (hScroll) {
    if ((ScrollPos >= 0) && (ScrollPos < NumItems)) {
      SCROLLBAR_SetValue(hScroll, ScrollPos);
    }
  }
}

/*********************************************************************
*
*       _AddKey
*
* Returns: 1 if Key has been consumed
*          0 else 
*/
static int _AddKey(MULTIPAGE_Handle hObj, MULTIPAGE_Obj * pObj, int Key) {
  switch (Key) {
  case GUI_KEY_PGUP:
    _MoveSel(hObj, pObj, -1);
    return 1;               /* Key has been consumed */
  case GUI_KEY_PGDOWN:
    _MoveSel(hObj, pObj, +1);
    return 1;               /* Key has been consumed */
  }
  return 0;                 /* Key has NOT been consumed */
}

/*********************************************************************
*
*       _ClientCallback
*/
static void _ClientCallback(WM_MESSAGE* pMsg) {
  WM_HWIN hObj = pMsg->hWin;
  WM_HWIN hParent = WM_GetParent(hObj);
  MULTIPAGE_Obj* pParent;
  WM_LOCK();
  pParent = (MULTIPAGE_Obj *)GUI_ALLOC_h2p(hParent); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
  switch (pMsg->MsgId) {
  case WM_PAINT:
    LCD_SetBkColor(pParent->Props.aBkColor[1]);
    GUI_Clear();
    break;
  case WM_TOUCH:
    WM_SetFocus(hParent);
    WM_BringToTop(hParent);
    break;
  case WM_GET_CLIENT_WINDOW:
    pMsg->Data.v = (int)hObj;
    break;
  case WM_KEY:
    if (((const WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt > 0) {
      int Key;
      Key = ((const WM_KEY_INFO*)(pMsg->Data.p))->Key;
      if (_AddKey(hParent, pParent, Key)) {
        break;
      }
    }
    /* No break here ... WM_DefaultProc needs to be called */
  default:
    WM_DefaultProc(pMsg);
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       Private routines
*
**********************************************************************
*/
/*********************************************************************
*
*       MULTIPAGE__DrawTextItemH
*/
void MULTIPAGE__DrawTextItemH(MULTIPAGE_Obj * pObj, const char * pText, unsigned Index,
                              const GUI_RECT * pRect, int x0, int w, int ColorIndex) {
  GUI_RECT r;
  r = *pRect;
  r.x0 += x0;
  r.x1  = r.x0 + w;
  pObj->Widget.pEffect->pfDrawUpRect(&r);
  GUI__ReduceRect(&r, &r, pObj->Widget.pEffect->EffectSize);
  if (pObj->Selection == Index) {
    if (pObj->Props.Align & MULTIPAGE_ALIGN_BOTTOM) {
      r.y0 -= pObj->Widget.pEffect->EffectSize + 1;
	    if (pObj->Widget.pEffect->EffectSize > 1) {
		    LCD_SetColor(MULTIPAGE__aEffectColor[0]);
		    GUI_DrawVLine(r.x0 - 1, r.y0, r.y0 + 1);
		    LCD_SetColor(MULTIPAGE__aEffectColor[1]);
		    GUI_DrawVLine(r.x1 + 1, r.y0, r.y0 + 1);
	    }
    } else {
      r.y1 += pObj->Widget.pEffect->EffectSize + 1;
	    if (pObj->Widget.pEffect->EffectSize > 1) {
		    LCD_SetColor(MULTIPAGE__aEffectColor[0]);
		    GUI_DrawVLine(r.x0 - 1, r.y1 - 2, r.y1 - 1);
		    LCD_SetColor(MULTIPAGE__aEffectColor[1]);
		    GUI_DrawVLine(r.x1 + 1, r.y1 - 2, r.y1 - 1);
	    }
    }
  }
  LCD_SetColor(pObj->Props.aBkColor[ColorIndex]);
  WIDGET__FillRectEx(&pObj->Widget, &r);
  LCD_SetBkColor(pObj->Props.aBkColor[ColorIndex]);
  LCD_SetColor(pObj->Props.aTextColor[ColorIndex]);
  GUI_DispStringAt(pText, r.x0 + 4, pRect->y0 + 3);
}

/*********************************************************************
*
*       MULTIPAGE__UpdatePositions
*/
void MULTIPAGE__UpdatePositions(MULTIPAGE_Handle hObj, MULTIPAGE_Obj * pObj) {
  GUI_RECT rBorder;
  int Width;
  Width = _GetTextWidth(pObj);
  _CalcBorderRect(pObj, &rBorder);
  /* Set scrollmode according to the text width */
  if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
    if (Width > rBorder.y1) {
      GUI_RECT rText;
      int Size, x0, y0, NumItems = 0;
      Size   = ((GUI_GetYSizeOfFont(pObj->Props.pFont) + 6) * 3) >> 2;
      y0     = (pObj->Props.Align & MULTIPAGE_ALIGN_RIGHT)  ? (rBorder.y0) : (rBorder.y1 - 2 * Size + 1);
      x0     = (pObj->Props.Align & MULTIPAGE_ALIGN_BOTTOM) ? (rBorder.x0 -     Size + 1) : (rBorder.x1);
      /* A scrollbar is required so we add one to the multipage */
      _AddScrollbar(hObj, pObj, x0, y0, Size, 2 * Size);
      pObj = (MULTIPAGE_Obj *)GUI_ALLOC_h2p(hObj); /* Pointer recalculation required */
      _GetTextRect(pObj, &rText);
      while (Width >= MAX((rText.y1 - rText.y0 + 1), 1)) {
        Width -= _GetPageSizeX(pObj, NumItems++);
      }
      _SetScrollbar(hObj, pObj, NumItems + 1);
      pObj = (MULTIPAGE_Obj *)GUI_ALLOC_h2p(hObj); /* Pointer recalculation required */
    } else {
      /* Scrollbar is no longer required. We delete it if there was one */
      MULTIPAGE__DeleteScrollbar(hObj, pObj);
    }
  } else {
    if (Width > rBorder.x1) {
      GUI_RECT rText;
      int Size, x0, y0, NumItems = 0;
      Size   = ((GUI_GetYSizeOfFont(pObj->Props.pFont) + 6) * 3) >> 2;
      x0     = (pObj->Props.Align & MULTIPAGE_ALIGN_RIGHT)  ? (rBorder.x0) : (rBorder.x1 - 2 * Size + 1);
      y0     = (pObj->Props.Align & MULTIPAGE_ALIGN_BOTTOM) ? (rBorder.y1) : (rBorder.y0 -     Size + 1);
      /* A scrollbar is required so we add one to the multipage */
      _AddScrollbar(hObj, pObj, x0, y0, 2 * Size, Size);
      pObj = (MULTIPAGE_Obj *)GUI_ALLOC_h2p(hObj); /* Pointer recalculation required */
      _GetTextRect(pObj, &rText);
      while (Width >= MAX((rText.x1 - rText.x0 + 1), 1)) {
        Width -= _GetPageSizeX(pObj, NumItems++);
      }
      _SetScrollbar(hObj, pObj, NumItems + 1);
      pObj = (MULTIPAGE_Obj *)GUI_ALLOC_h2p(hObj); /* Pointer recalculation required */
    } else {
      /* Scrollbar is no longer required. We delete it if there was one */
      MULTIPAGE__DeleteScrollbar(hObj, pObj);
    }
  }
  /* Move and resize the client area to the updated positions */
  MULTIPAGE__CalcClientRect(pObj, &rBorder);
  WM_MoveChildTo(pObj->hClient, rBorder.x0, rBorder.y0);
  WM_SetSize(pObj->hClient, rBorder.x1 - rBorder.x0 + 1, rBorder.y1 - rBorder.y0 + 1);
  WM_InvalidateWindow(hObj);
}

/*********************************************************************
*
*       MULTIPAGE__CalcClientRect
*
*  Calculates the rect of the client area.
*/
void MULTIPAGE__CalcClientRect(MULTIPAGE_Obj* pObj, GUI_RECT* pRect) {
  WIDGET__GetInsideRect(&pObj->Widget, pRect);
  _AdjustRect(pObj, pRect);
}

/*********************************************************************
*
*       MULTIPAGE__DeleteScrollbar
*/
void MULTIPAGE__DeleteScrollbar(MULTIPAGE_Handle hObj, MULTIPAGE_Obj* pObj) {
  WM_DeleteWindow(WM_GetScrollbarH(hObj));
  pObj->Widget.State &= ~MULTIPAGE_STATE_SCROLLMODE;
}

/*********************************************************************
*
*       MULTIPAGE_h2p
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
MULTIPAGE_Obj * MULTIPAGE_h2p(MULTIPAGE_Handle h) {
  MULTIPAGE_Obj * p = (MULTIPAGE_Obj *)GUI_ALLOC_h2p(h);
  if (p) {
    if (p->DebugId != MULTIPAGE_ID) {
      GUI_DEBUG_ERROROUT("MULTIPAGE.c: Wrong handle type or Object not init'ed");
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
*       MULTIPAGE_Callback
*/
void MULTIPAGE_Callback(WM_MESSAGE *pMsg) {
  MULTIPAGE_Handle hObj = pMsg->hWin;
  MULTIPAGE_Obj* pObj;
  int Handled;
  WM_LOCK();
  pObj = (MULTIPAGE_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
  Handled = WIDGET_HandleActive(hObj, pMsg);
  switch (pMsg->MsgId) {
  case WM_PAINT:
    _Paint(pObj);
    break;
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    break;
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_VALUE_CHANGED) {
      if (WM_GetId(pMsg->hWinSrc) == GUI_ID_HSCROLL) {
        pObj->ScrollState = SCROLLBAR_GetValue(pMsg->hWinSrc);
        WM_InvalidateWindow(hObj);
      }
    }
    break;
  case WM_GET_CLIENT_WINDOW:
    pMsg->Data.v = (int)pObj->hClient;
    break;
  case WM_GET_INSIDE_RECT:
    MULTIPAGE__CalcClientRect(pObj, (GUI_RECT*)(pMsg->Data.p));
    break;
  case WM_WIDGET_SET_EFFECT:
    WIDGET_SetEffect(WM_GetScrollbarH(hObj), (WIDGET_EFFECT const *)pMsg->Data.p);
  case WM_SIZE:
    MULTIPAGE__UpdatePositions(hObj, pObj);
    break;
  case WM_DELETE:
    GUI_ARRAY_Delete(&pObj->Handles);
    /* No break here ... WM_DefaultProc needs to be called */
  default:
    /* Let widget handle the standard messages */
    if (Handled) {
      WM_DefaultProc(pMsg);
    }
  }
  WM_UNLOCK();
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
*       MULTIPAGE_CreateEx
*/
MULTIPAGE_Handle MULTIPAGE_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                    int WinFlags, int ExFlags, int Id)
{
  MULTIPAGE_Handle hObj;
  /* Create the window */
  #if WM_SUPPORT_TRANSPARENCY
    WinFlags |= WM_CF_HASTRANS;
  #endif
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, &MULTIPAGE_Callback,
                                sizeof(MULTIPAGE_Obj) - sizeof(WM_Obj));
  if (hObj) {
    U16 InitState;
    MULTIPAGE_Obj* pObj;
    GUI_RECT rClient;
    int Flags;
    WM_LOCK();
    pObj = (MULTIPAGE_Obj *)GUI_ALLOC_h2p(hObj); /* Don't use use WIDGET_H2P because WIDGET_INIT_ID() has not be called at this point */
    /* Handle SpecialFlags */
    InitState = 0;
    if (ExFlags & WIDGET_STATE_VERTICAL) {
      InitState |= WIDGET_STATE_VERTICAL;
    }
    /* Init sub-classes */
    GUI_ARRAY_CREATE(&pObj->Handles);
    /* Init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, InitState);
    /* Init member variables */
    MULTIPAGE_INIT_ID(pObj);
    pObj->Props           = MULTIPAGE__DefaultProps;
    pObj->Selection       = 0xffff;
    pObj->ScrollState     = 0;
    pObj->pfDrawTextItem  = MULTIPAGE__DrawTextItemH;
    MULTIPAGE__CalcClientRect(pObj, &rClient);
    Flags = WM_CF_SHOW | WM_CF_ANCHOR_LEFT | WM_CF_ANCHOR_RIGHT | WM_CF_ANCHOR_TOP | WM_CF_ANCHOR_BOTTOM;
    pObj->hClient = WM_CreateWindowAsChild(rClient.x0, rClient.y0,
                                           rClient.x1 - rClient.x0 + 1,
                                           rClient.y1 - rClient.y0 + 1,
                                           hObj, Flags, &_ClientCallback, 0);
    MULTIPAGE__UpdatePositions(hObj, pObj);
    WM_UNLOCK();
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "MULTIPAGE_Create failed")
  }
  return hObj;
}

/*********************************************************************
*
*       Exported routines:  Page management
*
**********************************************************************
*/
/*********************************************************************
*
*       MULTIPAGE_AddPage
*/
void MULTIPAGE_AddPage(MULTIPAGE_Handle hObj, WM_HWIN hWin ,const char* pText) {
  MULTIPAGE_Obj* pObj;
  GUI_USE_PARA(hWin);
  if (hObj) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (!hWin) {
      /* If we get no handle we must find it. To do this, we search      */
      /* all children until we found one that has not yet become a page. */
      MULTIPAGE_PAGE* pPage;
      WM_HWIN hChild;
      WM_Obj* pChild;
      WM_Obj* pClient = WM_H2P(pObj->hClient);
      int i;
      for (hChild = pClient->hFirstChild; hChild && !hWin; hChild = pChild->hNext) {
        pChild = WM_H2P(hChild);
        hWin = hChild;
        for (i = 0; i < pObj->Handles.NumItems; i++) {
          pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, i);
          if (pPage->hWin == hChild) {
            hWin = 0;
            break;
          }
        }
      }
    } else {
      /* If we get a handle we must ensure that it was attached to the multipage */
      WM_AttachWindowAt(hWin, pObj->hClient, 0, 0);
    }
    if (hWin) {
      MULTIPAGE_PAGE Page;
      char NullByte = 0;
      if (!pText) {
        pText = &NullByte;
      }
      Page.hWin   = hWin;
      Page.Status = MULTIPAGE_STATE_ENABLED;
      if (GUI_ARRAY_AddItem(&pObj->Handles, &Page, sizeof(MULTIPAGE_PAGE) + strlen(pText)) == 0) {
        MULTIPAGE_PAGE* pPage;
        pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, pObj->Handles.NumItems - 1);
        GUI_MEMCPY(&pPage->acText, pText, strlen(pText) + 1);
      }
      MULTIPAGE_SelectPage(hObj, pObj->Handles.NumItems - 1);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_DeletePage
*/
void MULTIPAGE_DeletePage(MULTIPAGE_Handle hObj, unsigned Index, int Delete) {
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      if (Index < (unsigned)pObj->Handles.NumItems) {
        WM_HWIN hWin;
        MULTIPAGE_PAGE* pPage;
        pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
        hWin = pPage->hWin;
        /* Remove the page from the multipage object */
        if (Index == pObj->Selection) {
          if (Index == ((unsigned)pObj->Handles.NumItems - 1)) {
            _ShowPage(pObj, Index - 1);
            pObj->Selection--;
          } else {
            _ShowPage(pObj, Index + 1);
          }
        } else {
          if (Index < pObj->Selection) {
            pObj->Selection--;
          }
        }
        GUI_ARRAY_DeleteItem(&pObj->Handles, Index);
        MULTIPAGE__UpdatePositions(hObj, pObj);
        /* Delete the window of the page */
        if (Delete) {
          WM_DeleteWindow(hWin);
        }
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_SelectPage
*/
void MULTIPAGE_SelectPage(MULTIPAGE_Handle hObj, unsigned Index) {
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      if (Index < (unsigned)pObj->Handles.NumItems) {
        if (_GetEnable(pObj, Index)) {
          if (Index != pObj->Selection) {
            /* Switch to page */
            _ShowPage(pObj, Index);
            pObj->Selection = Index;
            MULTIPAGE__UpdatePositions(hObj, pObj);
          } else {
            /* Page is already visible, so move at least the input focus to the page */
            MULTIPAGE_PAGE * pPage;
            pPage = (MULTIPAGE_PAGE *)GUI_ARRAY_GetpItem(&pObj->Handles, Index);
            WM_SetFocus(pPage->hWin);
          }
        }
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_DisablePage
*/
void MULTIPAGE_DisablePage(MULTIPAGE_Handle hObj, unsigned Index) {
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      _SetEnable(pObj, Index, 0);
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_EnablePage
*/
void MULTIPAGE_EnablePage(MULTIPAGE_Handle hObj, unsigned Index) {
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      _SetEnable(pObj, Index, 1);
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
/*********************************************************************
*
*       MULTIPAGE_SetText
*/
void MULTIPAGE_SetText(MULTIPAGE_Handle hObj, const char* pText, unsigned Index) {
  MULTIPAGE_Obj* pObj;
  if (hObj && pText) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      if (Index < (unsigned)pObj->Handles.NumItems) {
        MULTIPAGE_PAGE* pPage;
        MULTIPAGE_PAGE Page;
        pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
        Page.hWin   = pPage->hWin;
        Page.Status = pPage->Status;
        if (GUI_ARRAY_SetItem(&pObj->Handles, Index, &Page, sizeof(MULTIPAGE_PAGE) + strlen(pText))) {
          pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
          GUI_MEMCPY(&pPage->acText, pText, strlen(pText) + 1);          
          MULTIPAGE__UpdatePositions(hObj, pObj);
        }
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_SetBkColor
*/
void MULTIPAGE_SetBkColor(MULTIPAGE_Handle hObj, GUI_COLOR Color, unsigned Index) {
  MULTIPAGE_Obj* pObj;
  if (hObj && ((int)Index < MULTIPAGE_NUMCOLORS)) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      pObj->Props.aBkColor[Index] = Color;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_SetTextColor
*/
void MULTIPAGE_SetTextColor(MULTIPAGE_Handle hObj, GUI_COLOR Color, unsigned Index) {
  MULTIPAGE_Obj* pObj;
  if (hObj && ((int)Index < MULTIPAGE_NUMCOLORS)) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      pObj->Props.aTextColor[Index] = Color;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_SetFont
*/
void MULTIPAGE_SetFont(MULTIPAGE_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont) {
  MULTIPAGE_Obj* pObj;
  if (hObj && pFont) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      pObj->Props.pFont = pFont;
      MULTIPAGE__UpdatePositions(hObj, pObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_SetAlign
*/
void MULTIPAGE_SetAlign(MULTIPAGE_Handle hObj, unsigned Align) {
  MULTIPAGE_Obj* pObj;
  GUI_RECT rClient;
  if (hObj) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      pObj->Props.Align = Align;
      MULTIPAGE__CalcClientRect(pObj, &rClient);
      WM_MoveTo(pObj->hClient, rClient.x0 + pObj->Widget.Win.Rect.x0,
                               rClient.y0 + pObj->Widget.Win.Rect.y0);
      MULTIPAGE__UpdatePositions(hObj, pObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_GetSelection
*/
int MULTIPAGE_GetSelection(MULTIPAGE_Handle hObj) {
  int r = 0;
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      r = pObj->Selection;
    }
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       MULTIPAGE_GetWindow
*/
WM_HWIN MULTIPAGE_GetWindow(MULTIPAGE_Handle hObj, unsigned Index) {
  WM_HWIN r = 0;
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      if (Index < (unsigned)pObj->Handles.NumItems) {
        MULTIPAGE_PAGE* pPage;
        pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
        r = pPage->hWin;
      }
    }
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       MULTIPAGE_IsPageEnabled
*/
int MULTIPAGE_IsPageEnabled(MULTIPAGE_Handle hObj, unsigned Index) {
  int r = 0;
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    if (pObj) {
      r = _GetEnable(pObj, Index);
    }
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       MULTIPAGE_SetEffectColor
*/
void MULTIPAGE_SetEffectColor(unsigned Index, GUI_COLOR Color) {
  if (Index < GUI_COUNTOF(MULTIPAGE__aEffectColor)) {
    MULTIPAGE__aEffectColor[Index] = Color;
  }
}

/*********************************************************************
*
*       MULTIPAGE_GetEffectColor
*/
GUI_COLOR MULTIPAGE_GetEffectColor(unsigned Index) {
  GUI_COLOR Color;
  Color = 0;
  if (Index < GUI_COUNTOF(MULTIPAGE__aEffectColor)) {
    Color = MULTIPAGE__aEffectColor[Index];
  }
  return Color;
}

/*********************************************************************
*
*       MULTIPAGE_GetNumEffectColors
*/
int MULTIPAGE_GetNumEffectColors(void) {
  return GUI_COUNTOF(MULTIPAGE__aEffectColor);
}

#else /* avoid empty object files */

void MULTIPAGE_C(void);
void MULTIPAGE_C(void){}

#endif  /* #if GUI_WINSUPPORT */



