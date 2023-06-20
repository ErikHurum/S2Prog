/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2008  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.18 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_GetBlankCols
Purpose     : Calculating of leading and trailing blank columns
              of a character
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#include "GUI_Private.h"

#if GUI_SUPPORT_DEVICES

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define XY2PTR(x, y, pDevice) ((LCD_PIXELINDEX *)GUI_ALLOC_h2p(pDevice->hData) + y * pDevice->xSize + x)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  GUI_MEMDEV_Handle hMemPrev;
  tLCDDEV_Color2Index  * pfColor2Index;
  tLCDDEV_Index2Color  * pfIndex2Color;
  int xSize;
  int ySize;
  GUI_HMEM hData;
} DEVICE;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _Color2Index
*/
static unsigned int _Color2Index(LCD_COLOR Color) {
  DEVICE * pDevice;
  pDevice = (DEVICE *)GUI_ALLOC_h2p(GUI_Context.hDevData);
  return pDevice->pfColor2Index(Color);
}

/*********************************************************************
*
*       _Index2Color
*/
static LCD_COLOR _Index2Color(int Index) {
  DEVICE * pDevice;
  pDevice = (DEVICE *)GUI_ALLOC_h2p(GUI_Context.hDevData);
  return pDevice->pfIndex2Color(Index);
}

/*********************************************************************
*
*       _DrawBitLine1BPP
*/
static void _DrawBitLine1BPP(const U8 GUI_UNI_PTR * p, int Diff, unsigned int xsize,
                             const LCD_PIXELINDEX * pTrans, LCD_PIXELINDEX * pDest)
{
  unsigned Pixels;
  unsigned PixelCnt;
  PixelCnt = 8 - Diff;
  Pixels = LCD_aMirror[*p] >> Diff;

  do {
    /* Prepare loop */
    if (PixelCnt > xsize) {
      PixelCnt = xsize;
    }
    xsize -= PixelCnt;
    /* Write as many pixels as we are allowed to and have loaded in this inner loop */
    do {
      *pDest++ = *(pTrans + (Pixels & 1));
      Pixels >>= 1;
    } while (--PixelCnt);
    /* Check if an other Source byte needs to be loaded */
    if (xsize == 0) {
      return;
    }
    PixelCnt = 8;
    Pixels = LCD_aMirror[*++p];
  } while (1);
}

/*********************************************************************
*
*       _DrawBitLine2BPP
*/
static void _DrawBitLine2BPP(const U8 GUI_UNI_PTR * p, int Diff, unsigned int xsize,
                             const LCD_PIXELINDEX * pTrans, LCD_PIXELINDEX * pDest)
{
  U8 pixels;
  U8  PixelCnt;
  PixelCnt = 4 - Diff;
  pixels = (*p) << (Diff << 1);
  do {
    if ((unsigned)PixelCnt > xsize) {
      PixelCnt = xsize;
    }
    xsize -= PixelCnt;
    do {
      *pDest++ = *(pTrans + (pixels >> 6));
      pixels <<= 2;
    } while (--PixelCnt);
    if (xsize == 0) {
      break;
    }
    PixelCnt = 4;
    pixels = *(++p);
  } while (xsize);
}

/*********************************************************************
*
*             _DrawBitmap
*/
static void _DrawBitmap(int x0, int y0, int xsize, int ysize,
                       int BitsPerPixel, int BytesPerLine,
                       const U8 GUI_UNI_PTR * pData, int Diff,
                       const LCD_PIXELINDEX * pTrans)
{
  int i;
  DEVICE * pDevice;
  LCD_PIXELINDEX * pDest;

  pDevice = (DEVICE *)GUI_ALLOC_h2p(GUI_Context.hDevData);
  x0 += Diff;
  pDest = XY2PTR(x0, y0, pDevice);
  for (i = 0; i < ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      _DrawBitLine1BPP(pData, Diff, xsize, pTrans, pDest);
      break;
    case 2:
      _DrawBitLine2BPP(pData, Diff, xsize, pTrans, pDest);
      break;
    }
    pData += BytesPerLine;
    pDest = (LCD_PIXELINDEX *)((LCD_PIXELINDEX *)pDest + pDevice->xSize); 
  }
}

/*********************************************************************
*
*       _GetRect
*/
static void _GetRect(LCD_RECT* pRect) {
  pRect->x0 = pRect->y0 = -4095;
  pRect->x1 = pRect->y1 =  4095;
}

/*********************************************************************
*
*       _SetPixelIndex
*/
static void _SetPixelIndex(int x, int y, int Index) {
  DEVICE * pDevice;
  LCD_PIXELINDEX * pDest;

  pDevice = (DEVICE *)GUI_ALLOC_h2p(GUI_Context.hDevData);
  pDest = XY2PTR(x, y, pDevice);
  *pDest = Index;
}

/*********************************************************************
*
*       Device structure
*/
static const tLCDDEV_APIList _APIList = {
  _Color2Index,
  _Index2Color,
  NULL,
  (tLCDDEV_DrawBitmap*)_DrawBitmap,
  NULL,
  NULL,
  NULL,
  NULL,
  _GetRect,
  _SetPixelIndex,
};

/*********************************************************************
*
*       _DeviceGetDataPtr
*
* Purpose:
*   Returns the data pointer of the given device
*/
static LCD_PIXELINDEX * _DeviceGetDataPtr(GUI_HMEM hDevice) {
  LCD_PIXELINDEX * r;
  DEVICE * pDevice;
  
  r = NULL;
  pDevice = (DEVICE *)GUI_ALLOC_h2p(hDevice);
  if (pDevice->hData) {
    r = (LCD_PIXELINDEX *)GUI_ALLOC_h2p(pDevice->hData);
  }
  return r;
}

/*********************************************************************
*
*       _DeviceCreate
*
* Purpose:
*   Creates a new device and selects it for drawing operations
*/
static GUI_HMEM _DeviceCreate(int xSize, int ySize) {
  GUI_HMEM hDevice;
  DEVICE * pDevice;

  /* Create the device object */
  hDevice = GUI_ALLOC_AllocZero(sizeof(DEVICE));
  if (hDevice) {
    pDevice = (DEVICE *)GUI_ALLOC_h2p(hDevice);
    pDevice->hData = GUI_ALLOC_AllocZero(xSize * ySize * sizeof(LCD_PIXELINDEX));
    if (pDevice->hData) {
      pDevice->xSize = xSize;
      pDevice->ySize = ySize;
      /* Save previously settings */
      pDevice->hMemPrev      = GUI_Context.hDevData;
      pDevice->pfColor2Index = GUI_Context.pDeviceAPI->pfColor2Index;    
      pDevice->pfIndex2Color = GUI_Context.pDeviceAPI->pfIndex2Color;
      /* Select new device for drawing operations */
      GUI_Context.hDevData   = hDevice;
      GUI_Context.pDeviceAPI = &_APIList;
      LCD_SetClipRectMax();
    }
  }
  return hDevice;
}

/*********************************************************************
*
*       _DeviceDelete
*
* Purpose:
*   Deletes the device and restores the previous settings
*/
static void _DeviceDelete(GUI_HMEM hDevice) {
  DEVICE * pDevice;

  if (hDevice) {
    /* Get object pointer */
    pDevice = (DEVICE *)GUI_ALLOC_h2p(hDevice);
    /* Restore previous device */
    if (pDevice->hMemPrev == 0) {
      GUI_SelectLCD();
    } else {
      #if GUI_SUPPORT_MEMDEV
        GUI_MEMDEV_Select(pDevice->hMemPrev);
      #endif
    }
    /* Delete object and attached data */
    if (pDevice->hData) {
      GUI_ALLOC_Free(pDevice->hData);
    }
    GUI_ALLOC_Free(hDevice);
  }
}

/*********************************************************************
*
*       _GetBlanks
*
* Purpose:
*   Returns the leading or trailing blank columns of the given character.
*
* Parameters:
*   c        - Character
*   Trailing - 1 for trailing columns, 1 for leading columns
*
* Return value:
*   >= 0 - Number of blank columns
*   -1   - Error
*/
static int _GetBlanks(U16 c, unsigned Trailing) {
  GUI_HMEM hDevice;
  int xSize;
  int ySize;
  int i;
  int j;
  int r;
  LCD_PIXELINDEX BkColorIndex;
  LCD_PIXELINDEX * pData;

  GUI_LOCK();
  r = -1;
  /* Calculate required dimension of device */
  xSize = GUI_GetCharDistX(c);
  ySize = GUI_GetFontSizeY();
  /* Create and select device */
  hDevice = _DeviceCreate(xSize, ySize);
  if (hDevice) {
    /* Get the data pointer to the device */
    pData = _DeviceGetDataPtr(hDevice);
    if (pData) {
      /* Draw character (into device) */
      GUI_DispCharAt(c, 0, 0);
      BkColorIndex = GUI_GetBkColorIndex();
      if (Trailing) {
        pData += xSize - 1;
      }
      r = -1;
      /* Iterate over columns */
      for (i = 0; i < xSize; i++) {
        LCD_PIXELINDEX * pDataOld;
        pDataOld = pData;
        /* Iterate over rows */
        for (j = 0; j < ySize; j++) {
          if (*pData != BkColorIndex) {
            /* If one pixel has been found, remember column and break */
            r = i;
            break;
          }
          pData += xSize;
        }
        if (r >= 0) {
          break;
        }
        pData = pDataOld;
        if (Trailing) {
          pData--;
        } else {
          pData++;
        }
      }
    }
  }
  /* Delete and restore previous device */
  _DeviceDelete(hDevice);
  GUI_UNLOCK();
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
*       GUI_GetLeadingBlankCols
*
* Purpose:
*   Returns the leading blank columns of the given character.
*
* Parameters:
*   c - Character
*
* Return value:
*   >= 0 - Number of blank columns
*   -1   - Error
*/
int GUI_GetLeadingBlankCols(U16 c) {
  return _GetBlanks(c, 0);
}

/*********************************************************************
*
*       GUI_GetTrailingBlankCols
*
* Purpose:
*   Returns the leading blank columns of the given character.
*
* Parameters:
*   c - Character
*
* Return value:
*   >= 0 - Number of blank columns
*   -1   - Error
*/
int GUI_GetTrailingBlankCols(U16 c) {
  return _GetBlanks(c, 1);
}

#else
  void GUI_GetBlankCols_C(void);   /* Avoid empty object files */
  void GUI_GetBlankCols_C(void) {}
#endif

/*************************** End of file ****************************/
