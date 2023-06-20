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
File        : GUI_JPEG_DrawScaled.c
Purpose     : Implementation of GUI_JPEG... functions
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI_Private.h"
#include "GUI_JPEG_Private.h"

#if (GUI_SELECT_JPEG == 0)

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawScanlineScaled
*
* Parameters
*   pContext   - Pointer to decompression context
*   x0, y0     - Drawing position of leftmost pixel
*   xSize      - Number of origilal pixels in color buffer
*   pfGetColor - Function pointer for getting color information
*   Num        - Numerator for scaling
*   Denom      - Denominator for scaling
*   NumLines   - Number of repetitions the line needs to be drawn
*/
static void _DrawScanlineScaled(GUI_JPEG_DCONTEXT * pContext, int x0, int y0, int xSize, GUI_COLOR (* pfGetColor)(const U8 ** ppData, unsigned SkipCnt), int Num, int Denom, unsigned NumLines) {
  const U8 * p;
  unsigned Compare, Current;
  int SkipCnt, NumReps;
  Current = Denom / 2;
  Compare = Denom;
  if (pContext->BufferIndex == 0) {
    p = (U8 *)GUI_ALLOC_h2p(pContext->hScanLine0);
  } else {
    p = (U8 *)GUI_ALLOC_h2p(pContext->hScanLine1);
  }
  /*
   * Iterate over the original pixels
   */
  do {
    GUI_COLOR Color;
    SkipCnt = 0;
    /*
     * Find out how many source pixels can be skipped
     */
    while (Current += Num, Current < Compare) {
      SkipCnt++;
      if (xSize-- == 0) {
        return;
      }
    }
    /*
     * Skip the number of pixels that are irrelevant
     */
    Color = pfGetColor(&p, SkipCnt + 1);
    LCD_SetColor(Color);
    /*
     * Find out how many times this pixel needs to be repeated
     */
    NumReps = 1;
    while (Compare += Denom, Current >= Compare) {
      NumReps++;
    }
    /*
     * Draw the pixel
     */
    if ((NumReps == 1) && (NumLines == 1)) {
      LCD_DrawPixel(x0, y0);
    } else {
      LCD_FillRect(x0, y0, x0 + NumReps - 1, y0 + NumLines - 1);
    }
    x0 += NumReps;
  } while (xSize--);
}

/*********************************************************************
*
*       _DrawScanlinesScaledAtOnce
*
* Parameters
*   pContext   - Pointer to decompression context
*   x0, y0     - Drawing position of leftmost pixel
*   pfGetColor - Function pointer for getting color information
*   Num        - Numerator for scaling
*   Denom      - Denominator for scaling
*/
static int _DrawScanlinesScaledAtOnce(GUI_JPEG_DCONTEXT * pContext, int x0, int y0, GUI_COLOR (* pfGetColor)(const U8 ** ppData, unsigned SkipCnt), int Num, int Denom) {
  unsigned Compare, Current;
  int SkipCnt, NumReps;
  Current = Denom / 2;
  Compare = Denom;
  /*
   * Iterate over the original pixels
   */
  do {
    SkipCnt = 0;
    /*
     * Find out how many source lines can be skipped
     */
    while (Current += Num, Current < Compare) {
      SkipCnt++;
    }
    /*
     * Skip the number of lines that are irrelevant
     */
    do {
      if (SkipCnt == 0) {
        if (GUI_JPEG__DecodeLine(pContext)) {
          return 1;
        }
      } else {
        if (pContext->IsProgressive) {
          if (GUI_JPEG__DecodeLine(pContext)) {
            return 1;
          }
        } else {
          if (GUI_JPEG__SkipLine(pContext)) {
            return 1;
          }
        }
      }
      if (pContext->TotalLinesLeft == 0) {
        break;
      }
    } while (--SkipCnt >= 0);
    if (pContext->TotalLinesLeft == 0) {
      break;
    }
    /*
     * Find out how many times this line needs to be repeated
     */
    NumReps = 1;
    while (Compare += Denom, Current >= Compare) {
      NumReps++;
    }
    /*
     * Draw the line
     */
    _DrawScanlineScaled(pContext, x0, y0, pContext->xSize, pfGetColor, Num, Denom, NumReps);
    y0 += NumReps;
  } while (pContext->TotalLinesLeft);
  return 0;
}

/*********************************************************************
*
*       _DrawScanlinesScaledBanding
*
* Parameters
*   pContext   - Pointer to decompression context
*   x0, y0     - Drawing position of leftmost pixel
*   pfGetColor - Function pointer for getting color information
*   Num        - Numerator for scaling
*   Denom      - Denominator for scaling
*/
static int _DrawScanlinesScaledBanding(GUI_JPEG_DCONTEXT * pContext, int x0, int y0, GUI_COLOR (* pfGetColor)(const U8 ** ppData, unsigned SkipCnt), int Num, int Denom) {
  unsigned Band;
  int r;
  int yPos;
  r = 0;
  /*
   * Allocate coefficient buffer
   */
  if (GUI_JPEG__AllocBandingCoeffBuffer(pContext) != 0) {
    return 1;
  }
  for (Band = 0; Band < pContext->NumBands; Band++) {
    unsigned Compare, Current;
    int SkipCnt, NumReps;
    int BlockY;
    Current = Denom / 2;
    Compare = Denom;
    /*
     * Start reading and process markers until SOF marker
     */
    if (Band) {
      GUI_JPEG__ReadUntilSOF(pContext);
    }
    /*
     * Decode one band of data
     */
    GUI_JPEG__DecodeProgressiveBanding(pContext);
    /*
     * Iterate over the original pixels
     */
    yPos = y0;
    do {
      SkipCnt = 0;
      /*
       * Find out how many source lines can be skipped
       */
      while (Current += Num, Current < Compare) {
        SkipCnt++;
      }
      /*
       * Skip the number of lines that are irrelevant
       */
      while (SkipCnt-- >= 0) {
        if (GUI_JPEG__DecodeLine(pContext)) {
          return 1;
        }
        if (pContext->TotalLinesLeft == 0) {
          break;
        }
      }
      if (pContext->TotalLinesLeft == 0) {
        break;
      }
      /*
       * Find out how many times this line needs to be repeated
       */
      NumReps = 1;
      while (Compare += Denom, Current >= Compare) {
        NumReps++;
      }
      BlockY = Current >> 3;
      if ((BlockY >= pContext->FirstBlockOfBand) && (BlockY <= (pContext->FirstBlockOfBand + pContext->NumBlocksPerBand - 1))) {
        /*
         * Draw the line
         */
        _DrawScanlineScaled(pContext, x0, y0, pContext->xSize, pfGetColor, Num, Denom, NumReps);
      }
      y0 += NumReps;
    } while (pContext->TotalLinesLeft);
    y0 = yPos;
    /*
     * Set parameters for next band
     */
    GUI_JPEG__SetNextBand(pContext);
  }
  return r;
}

/*********************************************************************
*
*       _Draw
*/
static int _Draw(GUI_JPEG_GET_DATA_FUNC * pfGetData, void * p, int x0, int y0, int Num, int Denom) {
  #if (GUI_WINSUPPORT)
    GUI_RECT Rect;
  #endif
  GUI_JPEG_INFO Info;
  GUI_COLOR (* pfGetColor)(const U8 ** ppData, unsigned SkipCnt);
  int r;
  int OldIndex;

  /* Remember old foreground color */
  OldIndex = LCD_GetColorIndex();
  /* Get size of image */
  if (GUI_JPEG_GetInfoEx(pfGetData, p, &Info)) {
    return 1;
  }
  /* Iterate over all windows */
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    Rect.x1 = (Rect.x0 = x0) + (U32)Info.XSize * (U32)Num / Denom - 1;
    Rect.y1 = (Rect.y0 = y0) + (U32)Info.YSize * (U32)Num / Denom - 1;
    WM_ITERATE_START(&Rect) {
  #endif
    GUI_MEMSET((U8 *)&GUI_JPEG__DContext, 0, sizeof(GUI_JPEG__DContext));
    GUI_JPEG__DContext.pParam = p;
    GUI_JPEG__DContext.pfGetData = pfGetData;
    /* Initialize drawing and allocate memory */
    r = GUI_JPEG__InitDraw(&GUI_JPEG__DContext);
    if (GUI_JPEG__DContext.ScanType == GRAYSCALE) {
      pfGetColor = GUI_JPEG__GetColorGray;
    } else {
      pfGetColor = GUI_JPEG__GetColorRGB;
    }
    /* Draw the lines */
    if (r == 0) {
      if (GUI_JPEG__DContext.BandingRequired == 0) {
        r = _DrawScanlinesScaledAtOnce(&GUI_JPEG__DContext, x0, y0, pfGetColor, Num, Denom);
      } else {
        r = _DrawScanlinesScaledBanding(&GUI_JPEG__DContext, x0, y0, pfGetColor, Num, Denom);
      }
    }
    /* Free allocated memory */
    GUI_JPEG__Free(&GUI_JPEG__DContext);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  /* Restore foreground color */
  LCD_SetColor(LCD_Index2Color(OldIndex));
  return r;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_JPEG_DrawScaledEx
*/
int  GUI_JPEG_DrawScaledEx(GUI_JPEG_GET_DATA_FUNC * pfGetData, void * p, int x0, int y0, int Num, int Denom) {
  int r;
  GUI_LOCK();
  r = _Draw(pfGetData, p, x0, y0, Num, Denom);
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_JPEG_DrawScaled
*/
int  GUI_JPEG_DrawScaled(const void * pFileData, int DataSize, int x0, int y0, int Num, int Denom) {
  int r;
  GUI_JPEG_PARAM Param;
  GUI_LOCK();
  Param.FileSize  = DataSize;
  Param.pFileData = (const U8 *)pFileData;
  r = GUI_JPEG_DrawScaledEx(GUI_JPEG__GetData, &Param, x0, y0, Num, Denom);
  GUI_UNLOCK();
  return r;
}

#endif /* (GUI_SELECT_JPEG == 0) */

/*************************** End of file ****************************/
