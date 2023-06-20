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
File        : GRAPH_DATA_YT.c
Purpose     : Implementation of YT graph
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>

#include "GRAPH_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  GRAPH_DATA_OBJ GraphDataObj;
  WM_HMEM        hData;
  U8             Align;
  U8             MirrorX;
} GRAPH_DATA_YT_OBJ;

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _OnPaint
*/
static void _OnPaint(GRAPH_DATA_Handle hDataObj, GUI_RECT * pRect) {
  int xPos, yPos, Diff;
  I16               * pData;
  GRAPH_OBJ         * pObj;
  GRAPH_DATA_YT_OBJ * pDataYtObj;
  GUI_USE_PARA(pRect);
  pDataYtObj = (GRAPH_DATA_YT_OBJ *)GUI_ALLOC_h2p(hDataObj);
  pData = (I16 *)GUI_ALLOC_h2p(pDataYtObj->hData);
  if (pData) {
    GUI_RECT Rect;
    int NumItems, NumVisItems, BorderL, BorderT, BorderR, BorderB;
    pObj = GRAPH_H2P(pDataYtObj->GraphDataObj.PaintObj.hGraph);
    BorderL = pObj->Props.BorderL;
    BorderT = pObj->Props.BorderT;
    BorderR = pObj->Props.BorderR;
    BorderB = pObj->Props.BorderB;
    WM_GetInsideRectExScrollbar(pDataYtObj->GraphDataObj.PaintObj.hGraph, &Rect);
    Rect.x0 += BorderL;
    Rect.y0 += BorderT;
    Rect.x1 -= BorderR;
    Rect.y1 -= BorderB;
    NumItems = pDataYtObj->GraphDataObj.NumItems;
    yPos     = Rect.y1                        /* Bottom of data area */
             - pDataYtObj->GraphDataObj.OffY  /* - Y-offset of data object */
             + pObj->ScrollStateV.v;          /* + Y-offset of graph object */
    NumVisItems = NumItems - pObj->ScrollStateH.v;
    if (pDataYtObj->Align == GRAPH_ALIGN_LEFT) {
      xPos = Rect.x0;
    } else {
      xPos = Rect.x1 - NumVisItems;
      if (Rect.x0 > xPos) {
        Diff         = Rect.x0 - xPos;
        xPos        += Diff;
        pData       += Diff;
        NumVisItems -= Diff;
      }
    }
    if (NumVisItems > 0) {
      GUI_SetColor(pDataYtObj->GraphDataObj.Color);
      GUI_DrawGraphEx(pData, NumVisItems, xPos, yPos, -1, 1, pDataYtObj->MirrorX);
    }
  }
}

/*********************************************************************
*
*       _OnDelete
*/
static void _OnDelete(GRAPH_DATA_Handle hDataObj) {
  GRAPH_DATA_YT_OBJ * pDataYtObj;
  pDataYtObj = (GRAPH_DATA_YT_OBJ *)GUI_ALLOC_h2p(hDataObj);
  if (pDataYtObj->hData) {
    GUI_ALLOC_Free(pDataYtObj->hData);
    pDataYtObj->hData = 0;
  }
  GUI_ALLOC_Free(hDataObj);
}

/*********************************************************************
*
*       _SetOffY
*/
static void _SetOffY(GRAPH_DATA_OBJ * pDataObj, int Value) {
  if (pDataObj) {
    if (pDataObj->OffY != Value) {
      pDataObj->OffY = Value;
      WM_Invalidate(pDataObj->PaintObj.hGraph);
    }
  }
}

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GRAPH_DATA_YT_Create
*/
GRAPH_DATA_Handle GRAPH_DATA_YT_Create(GUI_COLOR Color, unsigned MaxNumItems, I16 * pItems, unsigned NumItems) {
  GRAPH_DATA_Handle  hDataObj;
  WM_LOCK();
  hDataObj = GUI_ALLOC_AllocZero(sizeof(GRAPH_DATA_YT_OBJ));
  if (hDataObj) {
    GRAPH_DATA_YT_OBJ * pDataYtObj;
    WM_HMEM             hData;
    int                 BufferSize;
    BufferSize = sizeof(I16) * MaxNumItems;
    hData = GUI_ALLOC_AllocZero(BufferSize);
    if (hData && pItems && NumItems) {
      void * p;
      p = GUI_ALLOC_h2p(hData);
      GUI_MEMCPY(p, pItems, sizeof(I16) * NumItems);
    }
    pDataYtObj = (GRAPH_DATA_YT_OBJ *)GUI_ALLOC_h2p(hDataObj);
    pDataYtObj->hData = hData;
    pDataYtObj->GraphDataObj.Color               = Color;
    pDataYtObj->GraphDataObj.MaxNumItems         = MaxNumItems;
    pDataYtObj->GraphDataObj.NumItems            = NumItems;
    pDataYtObj->GraphDataObj.PaintObj.pfOnPaint  = _OnPaint;
    pDataYtObj->GraphDataObj.PaintObj.pfOnDelete = _OnDelete;
  }
  WM_UNLOCK();
  return hDataObj;
}

/*********************************************************************
*
*       GRAPH_DATA_YT_Delete
*/
void GRAPH_DATA_YT_Delete(GRAPH_DATA_Handle hDataObj) {
  WM_LOCK();
  _OnDelete(hDataObj);
  WM_UNLOCK();
}

/*********************************************************************
*
*       GRAPH_DATA_YT_AddValue
*/
void GRAPH_DATA_YT_AddValue(GRAPH_DATA_Handle hDataObj, I16 Value) {
  GRAPH_DATA_YT_OBJ * pDataYtObj;
  WM_LOCK();
  pDataYtObj = (GRAPH_DATA_YT_OBJ *)GUI_ALLOC_h2p(hDataObj);
  if (pDataYtObj) {
    I16 * pData;
    pData = (I16 *)GUI_ALLOC_h2p(pDataYtObj->hData);
    GRAPH__AddValue(&pDataYtObj->GraphDataObj, pData, &Value, sizeof(I16));
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       GRAPH_DATA_YT_SetOffY
*/
void GRAPH_DATA_YT_SetOffY(GRAPH_DATA_Handle hDataObj, int Off) {
  WM_LOCK();
  _SetOffY((GRAPH_DATA_OBJ *)GUI_ALLOC_h2p(hDataObj), Off);
  WM_UNLOCK();
}

/*********************************************************************
*
*       GRAPH_DATA_YT_SetAlign
*/
void GRAPH_DATA_YT_SetAlign(GRAPH_DATA_Handle hDataObj, int Align) {
  GRAPH_DATA_YT_OBJ * pDataYtObj;
  WM_LOCK();
  pDataYtObj = (GRAPH_DATA_YT_OBJ *)GUI_ALLOC_h2p(hDataObj);
  if (pDataYtObj) {
    if (pDataYtObj->Align != Align) {
      pDataYtObj->Align = Align;
      WM_Invalidate(pDataYtObj->GraphDataObj.PaintObj.hGraph);
    }
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       GRAPH_DATA_YT_MirrorX
*/
void GRAPH_DATA_YT_MirrorX(GRAPH_DATA_Handle hDataObj, int OnOff) {
  GRAPH_DATA_YT_OBJ * pDataYtObj;
  WM_LOCK();
  pDataYtObj = (GRAPH_DATA_YT_OBJ *)GUI_ALLOC_h2p(hDataObj);
  if (pDataYtObj) {
    if (pDataYtObj->MirrorX != OnOff) {
      pDataYtObj->MirrorX = OnOff;
      WM_Invalidate(pDataYtObj->GraphDataObj.PaintObj.hGraph);
    }
  }
  WM_UNLOCK();
}

#else                            /* Avoid problems with empty object modules */
  void GRAPH_DATA_YT_C(void);
  void GRAPH_DATA_YT_C(void) {}
#endif  /* #if GUI_WINSUPPORT */
