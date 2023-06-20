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
File        : GUIStream.c
Purpose     : Support for streamed bitmaps
----------------------------------------------------------------------
*/

#include "GUI_Private.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static GUI_BITMAPSTREAM_CALLBACK _pfStreamedBitmapHook;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetData
*/
static int _GetData(GUI_GET_DATA_FUNC * pfGetData, const void * p, const U8 ** ppData, int NumBytes, U32 * pOff) {
  int NumBytesRead;

  NumBytesRead = pfGetData((void *)p, ppData, NumBytes, *pOff);
  if (NumBytesRead != NumBytes) {
    return 1;
  }
  *pOff += NumBytesRead;
  return 0;
}

/*********************************************************************
*
*       _ReadHeader
*/
static void _ReadHeader(const U8 * pData, GUI_BITMAP_STREAM * pHeader) {
  pHeader->ID           = GUI__Read16(&pData);
  pHeader->Version      = GUI__Read16(&pData);
  pHeader->XSize        = GUI__Read16(&pData);
  pHeader->YSize        = GUI__Read16(&pData);
  pHeader->BytesPerLine = GUI__Read16(&pData);
  pHeader->BitsPerPixel = GUI__Read16(&pData);
  pHeader->NumColors    = GUI__Read16(&pData);
  pHeader->HasTrans     = GUI__Read16(&pData);
}

/*********************************************************************
*
*       _FillInfo
*/
static void _FillInfo(GUI_BITMAP_STREAM * pHeader, GUI_BITMAPSTREAM_INFO * pInfo) {
  pInfo->BitsPerPixel = pHeader->BitsPerPixel;
  pInfo->HasTrans     = pHeader->HasTrans;
  pInfo->NumColors    = pHeader->NumColors;
  pInfo->XSize        = pHeader->XSize;
  pInfo->YSize        = pHeader->YSize;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawStreamedBitmap
*/
void GUI_DrawStreamedBitmap(const void * p, int x, int y) {
  GUI_BITMAP        Bitmap = {0};
  GUI_LOGPALETTE    Palette;
  GUI_BITMAP_STREAM BitmapHeader;
  
  //
  // Read header data
  //
  _ReadHeader((U8 *)p, &BitmapHeader);
  //
  // Initialize bitmap structure
  //
  Bitmap.BitsPerPixel = BitmapHeader.BitsPerPixel;
  Bitmap.BytesPerLine = BitmapHeader.BytesPerLine;
  Bitmap.pData        = ((const U8 *)p) + 16 + 4 * BitmapHeader.NumColors;
  Bitmap.pPal         = &Palette;
  Bitmap.XSize        = BitmapHeader.XSize;
  Bitmap.YSize        = BitmapHeader.YSize;
  //
  // Initialize palette structure
  //
  Palette.HasTrans    = BitmapHeader.HasTrans;
  Palette.NumEntries  = BitmapHeader.NumColors;
  Palette.pPalEntries = (const LCD_COLOR *)((const U8 *)p + 16);
  //
  // Draw bitmap
  //
  GUI_DrawBitmap(&Bitmap, x, y);
}

/*********************************************************************
*
*       GUI_SetStreamedBitmapHook
*/
void GUI_SetStreamedBitmapHook(GUI_BITMAPSTREAM_CALLBACK pfStreamedBitmapHook) {
  _pfStreamedBitmapHook = pfStreamedBitmapHook;
}

/*********************************************************************
*
*       GUI_DrawStreamedBitmapEx
*/
int GUI_DrawStreamedBitmapEx(GUI_GET_DATA_FUNC * pfGetData, const void * p, int x, int y) {
  GUI_BITMAP        Bitmap = {0};
  GUI_LOGPALETTE    Palette;
  GUI_BITMAP_STREAM BitmapHeader;
  U8                acBuffer[sizeof(GUI_BITMAP_STREAM)];
  U8              * pBuffer;
  U8              * pData;
  U8              * pPalette;
  GUI_HMEM          hPalette, hData;
  int               SizeOfPalette, i, r;
  U32               Off, Color, NumFreeBytes, NumDataBytes, SizeOfDataBuffer, RemBytes, BytesInBuffer;
  GUI_BITMAPSTREAM_PARAM Param;

  GUI_LOCK();
  pBuffer  = acBuffer;
  hPalette = 0;
  pPalette = NULL;
  Off      = 0;
  r        = 0;
  if (_GetData(pfGetData, p, (const U8 **)&pBuffer, 16, &Off) == 0) {
    //
    // Read header data
    //
    _ReadHeader(acBuffer, &BitmapHeader);
    //
    // Calculate number of bytes for palette data
    //
    SizeOfPalette = BitmapHeader.NumColors * 4;
    //
    // Fill bitmap structure except pointer to pixel data and ySize
    //
    Bitmap.BitsPerPixel = BitmapHeader.BitsPerPixel;
    Bitmap.BytesPerLine = BitmapHeader.BytesPerLine;
    Bitmap.pPal         = &Palette;
    Bitmap.XSize        = BitmapHeader.XSize;
    //
    // Fill palette structure except pointer to palette data
    //
    Palette.HasTrans    = BitmapHeader.HasTrans;
    Palette.NumEntries  = BitmapHeader.NumColors;
    Palette.pPalEntries = (const LCD_COLOR *)pPalette;
    //
    // Allocate palette buffer
    //
    if (_pfStreamedBitmapHook) {
      //
      // In case of having a callback function the application can spend a memory area for the palette data
      //
      Param.Cmd = GUI_BITMAPSTREAM_GET_BUFFER;   // Command
      Param.v   = SizeOfPalette;                 // Number of bytes requested
      pPalette  = (U8 *)_pfStreamedBitmapHook(&Param); // Call hook function
    }
    if (pPalette == NULL) {
      //
      // If there is no buffer use the emWin memory manager to get a buffer
      //
      hPalette = GUI_ALLOC_AllocNoInit(SizeOfPalette);
      if (hPalette) {
        pPalette = (U8 *)GUI_LOCK_H(hPalette);
      }
    }
    if (pPalette) {
      if (_GetData(pfGetData, p, (const U8 **)&pPalette, SizeOfPalette, &Off) == 0) {
        pBuffer = pPalette;
        for (i = 0; i < BitmapHeader.NumColors; i++) {
          Color = GUI__Read32((const U8 **)&pBuffer);
          *((U32 *)pPalette + i) = Color;
        }
        if (_pfStreamedBitmapHook) {
          //
          // Call hook function to be able to change the palette by the application
          //
          Param.Cmd = GUI_BITMAPSTREAM_MODIFY_PALETTE; // Command
          Param.p   = pPalette;                        // Pointer to palette data
          Param.v   = BitmapHeader.NumColors;          // Number of colors
          _pfStreamedBitmapHook(&Param);               // Call hook function
        }
        if (hPalette) {
          GUI_UNLOCK_H(pPalette);
        }
        //
        // Get buffer for at least one line of data
        //
        NumFreeBytes = GUI_ALLOC_GetNumFreeBytes();
        NumDataBytes = BitmapHeader.BytesPerLine * BitmapHeader.YSize;
        if (NumFreeBytes >= BitmapHeader.BytesPerLine) {
          //
          // Calculate size of data buffer
          //
          if (NumFreeBytes >= NumDataBytes) {
            SizeOfDataBuffer = NumDataBytes;
          } else {
            SizeOfDataBuffer = (NumFreeBytes / BitmapHeader.BytesPerLine) * BitmapHeader.BytesPerLine;
          }
          //
          // Get data buffer
          //
          hData = GUI_ALLOC_AllocNoInit(SizeOfDataBuffer);
          pData = (U8 *)GUI_LOCK_H(hData);
          if (hPalette) {
            pPalette = (U8 *)GUI_LOCK_H(hPalette);
          }
          //
          // Set palette and pixel data pointer of bitmap structure
          //
          Bitmap.pData        = (const U8 *)pData;
          Palette.pPalEntries = (const LCD_COLOR *)pPalette;
          //
          // Draw bitmap
          //
          for (RemBytes = NumDataBytes; RemBytes; RemBytes -= BytesInBuffer) {
            if (RemBytes >= SizeOfDataBuffer) {
              BytesInBuffer = SizeOfDataBuffer;
            } else {
              BytesInBuffer = RemBytes;
            }
            if (_GetData(pfGetData, p, (const U8 **)&pData, BytesInBuffer, &Off)) {
              break;
            }
            //
            // Draw all lines which are currently in the buffer
            //
            Bitmap.YSize = BytesInBuffer / BitmapHeader.BytesPerLine;
            GUI_DrawBitmap(&Bitmap, x, y);
            y += Bitmap.YSize;
          }
          //
          // Release data buffer
          //
          GUI_UNLOCK_H(pData);
          GUI_ALLOC_Free(hData);
        }
      } else {
        r = 1;
      }
      //
      // Release palette buffer
      //
      if (hPalette == 0) {
        //
        // Tell the application to release the buffer
        //
        Param.Cmd = GUI_BITMAPSTREAM_RELEASE_BUFFER; // Command
        Param.p   = pPalette;                        // Pointer to palette data
        _pfStreamedBitmapHook(&Param);               // Call hook function
      } else {
        //
        // Release memory
        //
        GUI_UNLOCK_H(pPalette);
        GUI_ALLOC_Free(hPalette);
      }
    } else {
      r = 1;
    }
  } else {
    r = 1;
  }
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_GetStreamedBitmapInfo
*/
void GUI_GetStreamedBitmapInfo(const void * p, GUI_BITMAPSTREAM_INFO * pInfo) {
  GUI_BITMAP_STREAM BitmapHeader;
  
  //
  // Read header data
  //
  _ReadHeader((const U8 *)p, &BitmapHeader);
  //
  // Fill info structure
  //
  _FillInfo(&BitmapHeader, pInfo);
}

/*********************************************************************
*
*       GUI_GetStreamedBitmapInfoEx
*/
int GUI_GetStreamedBitmapInfoEx(GUI_GET_DATA_FUNC * pfGetData, const void * p, GUI_BITMAPSTREAM_INFO * pInfo) {
  GUI_BITMAP_STREAM BitmapHeader;
  U8                acBuffer[sizeof(GUI_BITMAP_STREAM)];
  U8              * pBuffer;
  U32               Off;
  int               r;

  GUI_LOCK();
  pBuffer = acBuffer;
  Off     = 0;
  if ((r = _GetData(pfGetData, p, (const U8 **)&pBuffer, 16, &Off)) == 0) {
    //
    // Read header data
    //
    _ReadHeader(pBuffer, &BitmapHeader);
    //
    // Fill info structure
    //
    _FillInfo(&BitmapHeader, pInfo);
  }
  return r;
}

/*************************** End of file ****************************/
