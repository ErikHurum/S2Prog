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
File        : HEADER_Private.h
Purpose     : Private HEADER include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef HEADER_PRIVATE_H
#define HEADER_PRIVATE_H


#include "WIDGET.h"
#include "HEADER.h"
#include "WM.h"
#include "GUI_ARRAY.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  int Width;
  I16 Align;
  WM_HMEM hDrawObj;
  char acText[1];
} HEADER_COLUMN;

typedef struct {
  const GUI_FONT GUI_UNI_PTR * pFont;
  GUI_COLOR BkColor;
  GUI_COLOR TextColor;
  GUI_COLOR ArrowColor;
} HEADER_PROPS;


typedef struct {
  WIDGET Widget;
  HEADER_PROPS Props;
  GUI_ARRAY Columns;
  int CapturePosX;
  int CaptureItem;
  int ScrollPos;
  int Sel;
  int DirIndicatorColumn;
  int DirIndicatorReverse;
  unsigned Fixed;
  #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
    int DebugId;
  #endif
  U8 DragLimit;
} HEADER_Obj;

/*********************************************************************
*
*       Private (module internal) data
*
**********************************************************************
*/

extern HEADER_PROPS HEADER_DefaultProps;
extern const GUI_CURSOR GUI_UNI_PTR * HEADER__pDefaultCursor;
extern int                            HEADER__DefaultBorderH;
extern int                            HEADER__DefaultBorderV;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  HEADER_Obj * HEADER_h2p(HEADER_Handle h);
  #define HEADER_H2P(h) HEADER_h2p(h)
  #define HEADER_INIT_ID(p) p->DebugId = HEADER_ID
#else
  #define HEADER_H2P(h) (HEADER_Obj *)GUI_ALLOC_h2p(h)
  #define HEADER_INIT_ID(p)
#endif

void HEADER__SetDrawObj(HEADER_Handle hObj, unsigned Index, GUI_DRAW_HANDLE hDrawObj);


#endif /* GUI_WINSUPPORT */
#endif /* Avoid multiple inclusion */
