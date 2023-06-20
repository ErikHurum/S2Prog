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
File        : LCD_NextPixelAPI.c
Purpose     : Bitmap drawing via LCD_API_NEXT_PIXEL
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"

#if GUI_SUPPORT_DEVICES

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  int x0, xPos, yPos;
  GUI_HMEM hMem;            /* Handle of buffer */
  LCD_PIXELINDEX * pBuffer; /* Pointer to allocated buffer */
  LCD_PIXELINDEX * pDst;    /* Pointer for storing next pixel */
  int BitsPerPixel;
  int BufferSizeInPixels;
  int NumPixelsInBuffer;
  tLCDDEV_DrawBitmap * pfDrawBitmap;
} NEXT_PIXEL_CONTEXT;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static NEXT_PIXEL_CONTEXT _Context;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _NextPixel_FlushBuffer
*/
static void _NextPixel_FlushBuffer(void) {
  _Context.pfDrawBitmap(_Context.xPos, _Context.yPos, _Context.NumPixelsInBuffer, 1, _Context.BitsPerPixel, 0, (const U8 *)_Context.pBuffer, 0, NULL);
  _Context.xPos += _Context.NumPixelsInBuffer;
  _Context.NumPixelsInBuffer = 0;
  _Context.pDst = _Context.pBuffer;
}

/*********************************************************************
*
*       _NextPixel_Start
*/
static void _NextPixel_Start(int x0, int y0, int x1, int y1) {
  U32 BufferSizeAvailable; /* Number of available bytes */
  int BufferSize;          /* Buffer size in bytes */
  int BytesPerPixel;       /* Size of LCD_PIXELINDEX */
  int BytesPerLineDest;
  int xSize;
  GUI_USE_PARA(y1);
  xSize = x1 - x0 + 1;
  /*
   * Calculate buffer size
   */
  _Context.BitsPerPixel = LCD_GetBitsPerPixelEx(GUI_Context.SelLayer);
  BytesPerPixel         = (_Context.BitsPerPixel <= 8) ? 1 : (_Context.BitsPerPixel <= 16) ? 2 : 4;
  BytesPerLineDest      = BytesPerPixel * xSize;
  BufferSizeAvailable   = GUI_ALLOC_GetMaxSize();
  if (BufferSizeAvailable < (U32)BytesPerLineDest) {
    BufferSize = (BufferSizeAvailable / BytesPerPixel) * BytesPerPixel;
  } else {
    BufferSize = BytesPerLineDest;
  }
  _Context.pfDrawBitmap       = LCD_GetpfDrawBitmap();
  _Context.BufferSizeInPixels = BufferSize / BytesPerPixel;
  _Context.NumPixelsInBuffer  = 0;
  _Context.xPos = _Context.x0 = x0;
  _Context.yPos = y0;
  /*
   * Allocate buffer
   */
  _Context.hMem    = GUI_ALLOC_AllocNoInit(BytesPerLineDest);
  _Context.pBuffer = (LCD_PIXELINDEX *)GUI_ALLOC_h2p(_Context.hMem);
  _Context.pDst    = _Context.pBuffer;
}

/*********************************************************************
*
*       _NextPixel_SetPixel
*/
static void _NextPixel_SetPixel(int PixelIndex) {
  *_Context.pDst++ = PixelIndex;
  if (++_Context.NumPixelsInBuffer == _Context.BufferSizeInPixels) {
    _NextPixel_FlushBuffer();
  }
}

/*********************************************************************
*
*       _NextPixel_NextLine
*/
static void _NextPixel_NextLine(void) {
  if (_Context.NumPixelsInBuffer) {
    _NextPixel_FlushBuffer();
  }
  _Context.xPos = _Context.x0;
  _Context.yPos++;
}

/*********************************************************************
*
*       _NextPixel_End
*/
static void _NextPixel_End(void) {
  if (_Context.NumPixelsInBuffer) {
    _NextPixel_FlushBuffer();
  }
  GUI_ALLOC_Free(_Context.hMem);
}

/*********************************************************************
*
*       _NextPixel_API
*/
static LCD_API_NEXT_PIXEL _NextPixel_API = {
  _NextPixel_Start,
  _NextPixel_SetPixel,
  _NextPixel_NextLine,
  _NextPixel_End
};

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_GetNextPixelAPI
*/
LCD_API_NEXT_PIXEL * LCD_GetNextPixelAPI(void) {
  #if 1
  LCD_API_NEXT_PIXEL * pNextPixel_API;
  if (LCD_PassingBitmapsAllowed()) {
    pNextPixel_API = (LCD_API_NEXT_PIXEL *)LCD_L0_GetDevFunc(LCD_DEVFUNC_NEXT_PIXEL);
  } else {
    pNextPixel_API = NULL;
  }
  if (!pNextPixel_API) {
    pNextPixel_API = &_NextPixel_API;
  }
  return pNextPixel_API;
  #else
  LCD_API_NEXT_PIXEL * pNextPixel_API;
  pNextPixel_API = (LCD_API_NEXT_PIXEL *)LCD_L0_GetDevFunc(LCD_DEVFUNC_NEXT_PIXEL);
  if (!pNextPixel_API) {
    pNextPixel_API = &_NextPixel_API;
  }
  return pNextPixel_API;
  #endif
}

#endif

/*************************** End of file ****************************/
