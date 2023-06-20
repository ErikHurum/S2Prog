/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2009  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.00 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIDEV_Banding.c
Purpose     : Implementation of banding memory devices
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>

#include "GUI_Private.h"

/* Memory device capabilities are compiled only if support for them is enabled. */

#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _Min
*/
static int _Min(int v0, int v1) {
  if (v0 <= v1) {
    return v0;
  }
  return v1;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_MEMDEV_DrawStatic
*/
int GUI_MEMDEV_DrawStatic(GUI_RECT * pRect, GUI_CALLBACK_VOID_P * pfDraw, void * pData, GUI_MEMDEV_Handle * phMem, int Flags) {
  GUI_MEMDEV_Handle hMem;
  int x0, y0, x1, y1, xSizeReq, ySizeReq, xPosMem, yPosMem, xSizeMem, ySizeMem;

  if (pRect == NULL) {
    return 1;
  }
  //
  // Always draw the complete window
  //
  x0       = pRect->x0;
  y0       = pRect->y0;
  x1       = pRect->x1;
  y1       = pRect->y1;
  xSizeReq = x1 - x0 + 1;
  ySizeReq = y1 - y0 + 1;
  //
  // Check if there is something to do
  //
  if ((xSizeReq <= 0) || (ySizeReq <= 0)) {
    return 0; // Nothing to do ...
  }
  //
  // Check if there is already a memory device of the required size
  //
  hMem = *phMem;
  if (hMem) {
    xPosMem = GUI_MEMDEV_GetXPos(hMem);
    yPosMem = GUI_MEMDEV_GetYPos(hMem);
    xSizeMem = GUI_MEMDEV_GetXSize(hMem);
    ySizeMem = GUI_MEMDEV_GetYSize(hMem);
    if ((xSizeMem == xSizeReq) && (ySizeMem == ySizeReq)) {
      if ((xPosMem != x0) || (yPosMem != y0)) {
        GUI_MEMDEV_SetOrg(hMem, x0, y0);
      }
    } else {
      //
      // Delete old memory device
      //
      GUI_MEMDEV_Delete(hMem);
      hMem = 0;
      *phMem = 0;
    }
  }
  //
  // Create memory device
  //
  if (hMem == 0) {
    hMem = GUI_MEMDEV_CreateEx(x0, y0, xSizeReq, ySizeReq, Flags);
    if (!hMem) {
      GUI_DEBUG_ERROROUT("GUI_MEMDEV_DrawStatic() Not enough memory ...");
      pfDraw(pData);
      return 1; // Not enough memory !
    }
  }
  //
  // Draw contents into memory device
  //
  GUI_MEMDEV_Select(hMem);
  pfDraw(pData);
  GUI_MEMDEV_Select(0);
  //
  // Draw memory device to screen
  //
  GUI_MEMDEV_CopyToLCD(hMem);
  //
  // Pass handle of memory device to calling function
  //
  *phMem = hMem;
  return 0;
}

/*********************************************************************
*
*       GUI_MEMDEV_Draw
*
*  This routine uses a banding memory device to draw the
*  given area flicker free. It not only draws, but also
*  automatically calculates the size of, creates, moves
*  and then destroys the memory device.
*/
int GUI_MEMDEV_Draw(GUI_RECT * pRect, GUI_CALLBACK_VOID_P * pfDraw, void * pData, int NumLines, int Flags) {
  int x0, y0, x1, y1, xsize, ysize, i, xOrg, yOrg;
  GUI_MEMDEV_Handle hMD;

  if (pRect) {
    GUI_GetOrg(&xOrg, &yOrg);
    x0 = (pRect->x0 < 0) ? 0 : pRect->x0;
    y0 = (pRect->y0 < 0) ? 0 : pRect->y0;
    x1 = _Min(pRect->x1, xOrg + LCD_GetXSizeEx(GUI_Context.SelLayer) - 1);
    y1 = _Min(pRect->y1, yOrg + LCD_GetYSizeEx(GUI_Context.SelLayer) - 1);
    xsize = x1 - x0 + 1;
    ysize = y1 - y0 + 1;
  } else {
    x0 = 0;
    y0 = 0;
    xsize = LCD_GetXSizeEx(GUI_Context.SelLayer);
    ysize = LCD_GetYSizeEx(GUI_Context.SelLayer);
  }
  if (NumLines == 0) {
    NumLines = -ysize;   /* Request <ysize> lines ... Less is o.k. */
  }
  if ((xsize <= 0) || (ysize <= 0)) {
    return 0;           /* Nothing to do ... */
  }
  //
  // Create memory device
  //
  hMD = GUI_MEMDEV_CreateEx(x0, y0, xsize, NumLines, Flags);
  if (!hMD) {
    GUI_DEBUG_ERROROUT("GUI_MEMDEV_Draw() Not enough memory ...");
    pfDraw(pData);
    return 1;
  }
  NumLines = GUI_MEMDEV_GetYSize(hMD);
  GUI_MEMDEV_Select(hMD);
  //
  // Start drawing
  //
  for (i = 0; i < ysize; i += NumLines) {
    int RemLines = ysize - i;
    if (RemLines < NumLines) {
      GUI_MEMDEV_ReduceYSize(hMD, RemLines);
    }
    if (i) {
      GUI_MEMDEV_SetOrg(hMD, x0, y0 + i);
      GUI_MEMDEV_Clear(hMD);
    }
    pfDraw(pData);
    GUI_MEMDEV_CopyToLCD(hMD);
  }
  GUI_MEMDEV_Delete(hMD);
  GUI_MEMDEV_Select(0);
  return 0;             /* Success ! */
}

#else

void GUIDEV_Banding(void);
void GUIDEV_Banding(void) {} /* avoid empty object files */

#endif /* GUI_MEMDEV_SUPPORT */

/*************************** end of file ****************************/
