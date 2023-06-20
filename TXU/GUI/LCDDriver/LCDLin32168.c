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
File        : LCDLin32168.c
Purpose     : Driver for accessing linear video memory
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"

#if (LCD_CONTROLLER == 32168) \
    && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/* Mappings for multi layer configurations */
#if GUI_NUM_LAYERS > 1 /* Use single display macros */
  #if   LCD_DISPLAY_INDEX == 0
    #ifdef LCD_VRAM_ADR_0
      #define LCD_VRAM_ADR   LCD_VRAM_ADR_0
    #endif
  #elif LCD_DISPLAY_INDEX == 1
    #ifdef LCD_VRAM_ADR_1
      #define LCD_VRAM_ADR   LCD_VRAM_ADR_1
    #endif
  #elif LCD_DISPLAY_INDEX == 2
    #ifdef LCD_VRAM_ADR_2
      #define LCD_VRAM_ADR   LCD_VRAM_ADR_2
    #endif
  #elif LCD_DISPLAY_INDEX == 3
    #ifdef LCD_VRAM_ADR_3
      #define LCD_VRAM_ADR   LCD_VRAM_ADR_3
    #endif
  #elif LCD_DISPLAY_INDEX == 4
    #ifdef LCD_VRAM_ADR_4
      #define LCD_VRAM_ADR   LCD_VRAM_ADR_4
    #endif
  #elif LCD_DISPLAY_INDEX == 5
    #ifdef LCD_VRAM_ADR_5
      #define LCD_VRAM_ADR   LCD_VRAM_ADR_5
    #endif
  #endif
#endif

#ifndef LCD_VRAM_ADR
  #error Please define the address of the video RAM!
#endif

#ifndef   LCD_INIT_CONTROLLER
  #define LCD_INIT_CONTROLLER()
#endif

#ifndef   LCD_SET_ORG
  #define LCD_SET_ORG(x, y) GUI_USE_PARA(x); GUI_USE_PARA(y)
#endif

#ifndef   LCD_DEVFUNC_ISHW
  #define LCD_DEVFUNC_ISHW 0xff
#endif

/* Error for unsupported modes */
#if (LCD_BITSPERPIXEL != 16)
#error This mode is currently not supported! Please contact support!
#endif

/* Mappings for multi layer configurations */
#if   LCD_DISPLAY_INDEX == 1
  #define SIM_WriteMem16 SIM_WriteMem16_1
  #define SIM_WriteMem32 SIM_WriteMem32_1
  #define SIM_ReadMem16  SIM_ReadMem16_1
  #define SIM_ReadMem32  SIM_ReadMem32_1
#elif LCD_DISPLAY_INDEX == 2
  #define SIM_WriteMem16 SIM_WriteMem16_2
  #define SIM_WriteMem32 SIM_WriteMem32_2
  #define SIM_ReadMem16  SIM_ReadMem16_2
  #define SIM_ReadMem32  SIM_ReadMem32_2
#elif LCD_DISPLAY_INDEX == 3
  #define SIM_WriteMem16 SIM_WriteMem16_3
  #define SIM_WriteMem32 SIM_WriteMem32_3
  #define SIM_ReadMem16  SIM_ReadMem16_3
  #define SIM_ReadMem32  SIM_ReadMem32_3
#elif LCD_DISPLAY_INDEX == 4
  #define SIM_WriteMem16 SIM_WriteMem16_4
  #define SIM_WriteMem32 SIM_WriteMem32_4
  #define SIM_ReadMem16  SIM_ReadMem16_4
  #define SIM_ReadMem32  SIM_ReadMem32_4
#elif LCD_DISPLAY_INDEX == 5
  #define SIM_WriteMem16 SIM_WriteMem16_5
  #define SIM_WriteMem32 SIM_WriteMem32_5
  #define SIM_ReadMem16  SIM_ReadMem16_5
  #define SIM_ReadMem32  SIM_ReadMem32_5
#endif

#ifdef WIN32
  U16  SIM_ReadMem16 (unsigned int Off);
  U32  SIM_ReadMem32 (unsigned int Off);
  void SIM_WriteMem16(unsigned int Off, U16 Data);
  void SIM_WriteMem32(unsigned int Off, U32 Data);
  void SIM_WriteMem16p(U16 * p, U16 Data);
  void SIM_memcpy(void * pDst, const void * pSrc, int Len);
  #undef  LCD_SET_ORG
  #define LCD_SET_ORG(x, y)          GUI_USE_PARA(x); GUI_USE_PARA(y)
  #define LCD_READ_MEM16(Off)        SIM_ReadMem16(Off)
  #define LCD_READ_MEM32(Off)        SIM_ReadMem32(Off)
  #define LCD_WRITE_MEM16(Off, Data) SIM_WriteMem16(Off, Data)
  #define LCD_WRITE_MEM32(Off, Data) SIM_WriteMem32(Off, Data)
  #define LCD_WRITE_MEM16P(p, Data)  SIM_WriteMem16p(p, Data)
  #undef  GUI_MEMCPY
  #define GUI_MEMCPY(pDst, pSrc, Len) SIM_memcpy(pDst, pSrc, Len)
#else
  #define LCD_READ_MEM16(Off)        (*((U16 *)LCD_VRAM_ADR + (U32)Off))
  #define LCD_READ_MEM32(Off)        (*((U32 *)LCD_VRAM_ADR + (U32)Off))
  #define LCD_WRITE_MEM16(Off, Data)  *((U16 *)LCD_VRAM_ADR + (U32)Off) = Data
  #define LCD_WRITE_MEM32(Off, Data)  *((U32 *)LCD_VRAM_ADR + (U32)Off) = Data
  #define LCD_WRITE_MEM16P(p, Data)   *((U16 *)p                      ) = Data
#endif

#define WRITE_MEM16(Off, Data) LCD_WRITE_MEM16(Off, Data)
#define WRITE_MEM32(Off, Data) LCD_WRITE_MEM32(Off, Data)
#define READ_MEM16(Off)        LCD_READ_MEM16(Off)
#define READ_MEM32(Off)        LCD_READ_MEM32(Off)
#define WRITE_MEM16P(p, Data)  LCD_WRITE_MEM16P(p, Data)

#define PIXELS_PER_DWORD (32 / LCD_BITSPERPIXEL)
#define PIXELS_PER_WORD  (16 / LCD_BITSPERPIXEL)
#define DWORDS_PER_LINE  (LCD_VXSIZE_PHYS * LCD_BITSPERPIXEL / 32)
#define WORDS_PER_LINE   (LCD_VXSIZE_PHYS * LCD_BITSPERPIXEL / 16)

#define XY2OFF32(x,y)    ((U32)y * DWORDS_PER_LINE + ((U32)x >> 1))
#define XY2OFF16(x,y)    ((U32)y * WORDS_PER_LINE  + x)

/* Macros for MIRROR_, SWAP_ and LUT_ */
#if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
  #define LOG2PHYS_X(x, y) x
  #define LOG2PHYS_Y(x, y) y
#elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
  #define LOG2PHYS_X(x, y) y
  #define LOG2PHYS_Y(x, y) x
#elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
  #define LOG2PHYS_X(x, y) x
  #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
#elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
  #define LOG2PHYS_X(x, y) y
  #define LOG2PHYS_Y(x, y) LCD_XSIZE - 1 - (x)
#elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
  #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
  #define LOG2PHYS_Y(x, y) y
#elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
  #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
  #define LOG2PHYS_Y(x, y) x
#elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
  #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
  #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
#elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
  #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
  #define LOG2PHYS_Y(x, y) LCD_XSIZE - 1 - (x)
#endif

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
/*********************************************************************
*
*       Draw Bitmap 1 BPP, optimized for LCD_BITSPERPIXEL == 16
*/
#if (LCD_BITSPERPIXEL == 16) && \
    (LCD_MIRROR_X == 0)      && \
    (LCD_SWAP_XY == 0)
static void _DrawBitLine1BPP(unsigned x, unsigned y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  unsigned Pixels, PixelCnt;
  LCD_PIXELINDEX Index, Index0, Index1, IndexMask;
  U32 Off;
  #if LCD_MIRROR_Y
    y = (LCD_YSIZE - 1 - (y));
  #endif
  Index0   = *(pTrans + 0);
  Index1   = *(pTrans + 1);
  x       += Diff;
  Off      = XY2OFF16(x, y);
  PixelCnt = 8 - Diff;
  Pixels   = LCD_aMirror[*p] >> Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    do {
      Index = (Pixels & 1) ? Index1 : Index0;
      WRITE_MEM16(Off, Index);
      Off++;
      PixelCnt--;
      Pixels >>= 1;
      if (PixelCnt == 0) {
        Pixels   = LCD_aMirror[*(++p)];
        PixelCnt = 8;
      }
    } while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
      if (Pixels & 1) {
        WRITE_MEM16(Off, Index1);
      }
      Off++;
      PixelCnt--;
      Pixels >>= 1;
      if (PixelCnt == 0) {
        Pixels   = LCD_aMirror[*(++p)];
        PixelCnt = 8;
      }
    } while (--xsize);
    break;
  case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
  case LCD_DRAWMODE_XOR:
    IndexMask = LCD_L0_GetIndexMask();
    do {
      if (Pixels & 1) {
        Index = READ_MEM16(Off);
        Index ^= IndexMask;
        WRITE_MEM16(Off, Index);
      }
      Off++;
      PixelCnt--;
      Pixels >>= 1;
      if (PixelCnt == 0) {
        Pixels   = LCD_aMirror[*(++p)];
        PixelCnt = 8;
      }
    } while (--xsize);
    break;
  }
}

/*********************************************************************
*
*       Draw Bitmap 1 BPP, not optimized
*/
#else
static void  _DrawBitLine1BPP(int x, int y, U8 const GUI_UNI_PTR *p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      do {
        LCD_L0_SetPixelIndex(x++, y, (*p & (0x80 >> Diff)) ? Index1 : Index0);
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
    case LCD_DRAWMODE_TRANS:
      do {
  		  if (*p & (0x80 >> Diff))
          LCD_L0_SetPixelIndex(x, y, Index1);
        x++;
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
    case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
    case LCD_DRAWMODE_XOR:
      do {
  		  if (*p & (0x80 >> Diff)) {
          int Pixel = LCD_L0_GetPixelIndex(x, y);
          LCD_L0_SetPixelIndex(x, y, LCD_NUM_COLORS - 1 - Pixel);
        }
        x++;
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
	}
}
#endif

/*********************************************************************
*
*       Draw Bitmap 2 BPP
*/
#if (LCD_MAX_LOG_COLORS > 2)
static void  _DrawBitLine2BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          LCD_L0_SetPixelIndex(x++, y, PixelIndex);
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          LCD_L0_SetPixelIndex(x++, y, Index);
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          if (Index) {
            LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
            LCD_L0_SetPixelIndex(x, y, PixelIndex);
          }
          x++;
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (3 - CurrentPixel) << 1;
          int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
          if (Index) {
            LCD_L0_SetPixelIndex(x, y, Index);
          }
          x++;
          if (++CurrentPixel == 4) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
  }
}
#endif

/*********************************************************************
*
*       Draw Bitmap 4 BPP
*/
#if (LCD_MAX_LOG_COLORS > 4)
static void  _DrawBitLine4BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          LCD_L0_SetPixelIndex(x++, y, PixelIndex);
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          LCD_L0_SetPixelIndex(x++, y, Index);
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          if (Index) {
            LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
            LCD_L0_SetPixelIndex(x, y, PixelIndex);
          }
          x++;
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      } else {
        do {
          int Shift = (1 - CurrentPixel) << 2;
          int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
          if (Index) {
            LCD_L0_SetPixelIndex(x, y, Index);
          }
          x++;
          if (++CurrentPixel == 2) {
            CurrentPixel = 0;
            Pixels = *(++p);
          }
		    } while (--xsize);
      }
      break;
  }
}
#endif

/*********************************************************************
*
*       Draw Bitmap 8 BPP, optimized for LCD_BITSPERPIXEL == 16
*/
#if (LCD_MAX_LOG_COLORS > 16)
#if (LCD_BITSPERPIXEL == 16) && \
    (LCD_MIRROR_X == 0)      && \
    (LCD_SWAP_XY == 0)
static void  _DrawBitLine8BPP(int x, int y, U8 const GUI_UNI_PTR * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixel;
  register U32 Off;
  U16 * pDest;
  if (!pTrans) {
    return; /* No translation from 8bpp BMP to 16bpp device makes no sense */
  }
  #if LCD_MIRROR_Y
    y = (LCD_YSIZE - 1 - (y));
  #endif
  Off   = XY2OFF16(x,y);
  pDest = (U16 *)(LCD_VRAM_ADR + Off * 2);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      #if 1
        while (xsize >= 8) {
          WRITE_MEM16P(pDest + 0, *(pTrans + *(p + 0)));
          WRITE_MEM16P(pDest + 1, *(pTrans + *(p + 1)));
          WRITE_MEM16P(pDest + 2, *(pTrans + *(p + 2)));
          WRITE_MEM16P(pDest + 3, *(pTrans + *(p + 3)));
          WRITE_MEM16P(pDest + 4, *(pTrans + *(p + 4)));
          WRITE_MEM16P(pDest + 5, *(pTrans + *(p + 5)));
          WRITE_MEM16P(pDest + 6, *(pTrans + *(p + 6)));
          WRITE_MEM16P(pDest + 7, *(pTrans + *(p + 7)));
          xsize -= 8;
          p     += 8;
          pDest += 8;
        }
        while (xsize >= 4) {
          WRITE_MEM16P(pDest + 0, *(pTrans + *(p + 0)));
          WRITE_MEM16P(pDest + 1, *(pTrans + *(p + 1)));
          WRITE_MEM16P(pDest + 2, *(pTrans + *(p + 2)));
          WRITE_MEM16P(pDest + 3, *(pTrans + *(p + 3)));
          xsize -= 4;
          p     += 4;
          pDest += 4;
        }
        while (xsize) {
          WRITE_MEM16P(pDest + 0, *(pTrans + *(p + 0)));
          xsize--;
          p++;
          pDest++;
        }
      #else
        for (; xsize > 0; xsize--, p++, pDest++) {
          WRITE_MEM16P(pDest, *(pTrans + *p));
        }
      #endif
      break;
    case LCD_DRAWMODE_TRANS:
      for (; xsize > 0; xsize--, p++, pDest++) {
        Pixel = *p;
        if (Pixel) {
          WRITE_MEM16P(pDest, *(pTrans + *p));
        }
      }
      break;
  }
}

/*********************************************************************
*
*       Draw Bitmap 8 BPP, not optimized
*/
#else
static void  _DrawBitLine8BPP(int x, int y, U8 const GUI_UNI_PTR * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixel;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          LCD_L0_SetPixelIndex(x, y, *(pTrans + Pixel));
        }
      } else {
        for (; xsize > 0; xsize--, x++, p++) {
          LCD_L0_SetPixelIndex(x, y, *p);
        }
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          if (Pixel) {
            LCD_L0_SetPixelIndex(x, y, *(pTrans + Pixel));
          }
        }
      } else {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          if (Pixel) {
            LCD_L0_SetPixelIndex(x, y, Pixel);
          }
        }
      }
      break;
  }
}
#endif
#endif

/*********************************************************************
*
*       Draw Bitmap 16 BPP, optimized for LCD_BITSPERPIXEL == 16
*/
#if (LCD_BITSPERPIXEL >= 16)
#if (LCD_BITSPERPIXEL == 16) && \
    (LCD_MIRROR_X == 0)      && \
    (LCD_SWAP_XY == 0)
static void DrawBitLine16BPP(int x, int y, U16 const GUI_UNI_PTR *p, int xsize) {
  register U32 Off;
  U16 * pDest;
  #if LCD_MIRROR_Y
    y = (LCD_YSIZE - 1 - (y));
  #endif
  Off = XY2OFF16(x,y);
  pDest = (U16 *)(LCD_VRAM_ADR + Off * 2);
  GUI_MEMCPY(pDest, (const void *)p, (U32)xsize << 1);
}

/*********************************************************************
*
*       Draw Bitmap 16 BPP, not optimized
*/
#else
static void DrawBitLine16BPP(int x, int y, U16 const GUI_UNI_PTR * p, int xsize) {
  for (;xsize > 0; xsize--, x++, p++) {
    LCD_L0_SetPixelIndex(x, y, *p);
  }
}
#endif
#endif

/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_L0_SetPixelIndex
*
* Purpose:
*   Sets the index of the given pixel. The upper layers
*   calling this routine make sure that the coordinates are in range, so
*   that no check on the parameters needs to be performed.
*/
void LCD_L0_SetPixelIndex(int x, int y, int PixelIndex) {
  U32 Off;
  /* Convert logical into physical coordinates (Dep. on LCDConf.h) */
  #if LCD_SWAP_XY | LCD_MIRROR_X| LCD_MIRROR_Y
    int xPhys = LOG2PHYS_X(x, y);
    int yPhys = LOG2PHYS_Y(x, y);
  #else
    #define xPhys x
    #define yPhys y
  #endif
  /* Write into hardware */
  Off = XY2OFF16(xPhys, yPhys);
  WRITE_MEM16(Off, PixelIndex);
}

/*********************************************************************
*
*       LCD_L0_GetPixelIndex
*
* Purpose:
*   Returns the index of the given pixel. The upper layers
*   calling this routine make sure that the coordinates are in range, so
*   that no check on the parameters needs to be performed.
*/
unsigned int LCD_L0_GetPixelIndex(int x, int y) {
  U32 Off;
  LCD_PIXELINDEX PixelIndex;
  /* Convert logical into physical coordinates (Dep. on LCDConf.h) */
  #if LCD_SWAP_XY | LCD_MIRROR_X| LCD_MIRROR_Y
    int xPhys = LOG2PHYS_X(x, y);
    int yPhys = LOG2PHYS_Y(x, y);
  #else
    #define xPhys x
    #define yPhys y
  #endif
  /* Read from hardware */
  Off        = XY2OFF16(xPhys, yPhys);
  PixelIndex = READ_MEM16(Off);
  return PixelIndex;
}

/*********************************************************************
*
*       LCD_L0_XorPixel
*/
void LCD_L0_XorPixel(int x, int y) {
  LCD_PIXELINDEX PixelIndex;
  LCD_PIXELINDEX IndexMask;
  PixelIndex = LCD_L0_GetPixelIndex(x, y);
  IndexMask  = LCD_L0_GetIndexMask();
  LCD_L0_SetPixelIndex(x, y, PixelIndex ^ IndexMask);
}

/*********************************************************************
*
*       LCD_L0_DrawHLine, optimized for LCD_BITSPERPIXEL == 16
*/
#if (LCD_BITSPERPIXEL == 16) && \
    (LCD_MIRROR_X == 0)      && \
    (LCD_SWAP_XY == 0)
void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; x0 <= x1; x0++) {
      LCD_L0_XorPixel(x0, y);
    }
  } else {
    U32 Off, RemPixels;
    U32 Data, ColorMask;
    #if LCD_MIRROR_Y
      y = LOG2PHYS_Y(x, y);
    #endif
    Off = XY2OFF32(x0, y);
    RemPixels = x1 - x0 + 1;
    /* First DWORD */
    if (x0 & 1) {
      Data = READ_MEM32(Off);
      #if (LCD_ENDIAN_BIG == 0)
        Data &= 0xFFFF;
        Data |= (((U32)LCD_COLORINDEX) << 16);
      #else
        Data &= 0xFFFF0000;
        Data |= LCD_COLORINDEX;
      #endif
      WRITE_MEM32(Off++, Data);
      RemPixels--;
    }
    /* Complete DWORDS */
    ColorMask = LCD_COLORINDEX * 0x00010001;
    if (RemPixels >= 16) {
      do {
        WRITE_MEM32(Off,     ColorMask);
        WRITE_MEM32(Off + 1, ColorMask);
        WRITE_MEM32(Off + 2, ColorMask);
        WRITE_MEM32(Off + 3, ColorMask);
        WRITE_MEM32(Off + 4, ColorMask);
        WRITE_MEM32(Off + 5, ColorMask);
        WRITE_MEM32(Off + 6, ColorMask);
        WRITE_MEM32(Off + 7, ColorMask);
        Off += 8;
      } while ((RemPixels -= 16) >= 16);
    }
    if (RemPixels >= 2) {
      do {
        WRITE_MEM32(Off++, ColorMask);
      } while ((RemPixels -= 2) >= 2);
    }
    /* Last DWORD */
    if (RemPixels > 0) {
      Data = READ_MEM32(Off);
      #if (LCD_ENDIAN_BIG == 0)
        Data &= 0xFFFF0000;
        Data |= LCD_COLORINDEX & 0xFFFF;
      #else
        Data &= 0xFFFF;
        Data |= (((U32)LCD_COLORINDEX) << 16);
      #endif
      WRITE_MEM32(Off, Data);
    }
  }
}

/*********************************************************************
*
*       LCD_L0_DrawHLine, not optimized
*/
#else
void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; x0 <= x1; x0++) {
      LCD_L0_XorPixel(x0, y);
    }
  } else {
    for (; x0 <= x1; x0++) {
      LCD_L0_SetPixelIndex(x0, y, LCD_COLORINDEX);
    }
  }
}
#endif

/*********************************************************************
*
*       LCD_L0_DrawVLine
*/
void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; y0 <= y1; y0++) {
      LCD_L0_XorPixel(x, y0);
    }
  } else {
    for (; y0 <= y1; y0++) {
      LCD_L0_SetPixelIndex(x, y0, LCD_COLORINDEX);
    }
  }
}

/*********************************************************************
*
*       LCD_L0_FillRect
*/
void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  #ifdef LCD_FILL_RECT
     LCD_FILL_RECT(x0, y0, x1, y1, LCD_COLORINDEX);
  #else
    #if !LCD_SWAP_XY
      for (; y0 <= y1; y0++) {
        LCD_L0_DrawHLine(x0, y0, x1);
      }
    #else
      for (; x0 <= x1; x0++) {
        LCD_L0_DrawVLine(x0, y0, y1);
      }
    #endif
  #endif
}

/*********************************************************************
*
*       LCD_L0_DrawBitmap
*/
void LCD_L0_DrawBitmap(int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8 GUI_UNI_PTR * pData, int Diff,
                       const LCD_PIXELINDEX* pTrans)
{
  int i;
  /* Use _DrawBitLineXBPP */
  for (i=0; i<ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      _DrawBitLine1BPP(x0, i + y0, pData, Diff, xsize, pTrans);
      break;
    #if (LCD_MAX_LOG_COLORS > 2)
      case 2:
        _DrawBitLine2BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 4)
      case 4:
        _DrawBitLine4BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 16)
      case 8:
        _DrawBitLine8BPP(x0, i + y0, pData, xsize, pTrans);
        break;
    #endif
    #if (LCD_BITSPERPIXEL > 8)
      case 16:
        DrawBitLine16BPP(x0, i + y0, (const U16 *)pData, xsize);
        break;
    #endif
    }
    pData += BytesPerLine;
  }
}

/*********************************************************************
*
*       LCD_L0_SetOrg
*/
void LCD_L0_SetOrg(int x, int y) {
  LCD_SET_ORG(x, y);
}

/*********************************************************************
*
*       LCD_On / LCD_Off
*/
void LCD_On (void) {
#ifdef LCD_ON
  LCD_ON();
#endif
}

void LCD_Off (void) {
#ifdef LCD_OFF
  LCD_OFF();
#endif
}

/*********************************************************************
*
*       LCD_L0_Init
*
* Purpose:
*   Initialises the LCD-controller.
*/
int  LCD_L0_Init(void) {
  LCD_INIT_CONTROLLER();
  return 0;
}

/*********************************************************************
*
*       LCD_L0_SetLUTEntry
*/
void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR Color) {
  GUI_USE_PARA(Pos);
  GUI_USE_PARA(Color);
}

/*********************************************************************
*
*       LCD_L0_GetDevFunc
*/
void * LCD_L0_GetDevFunc(int Index) {
  switch (Index) {
  case LCD_DEVFUNC_ISHW:
    return (void *)1;
  }
  return NULL;
}

#else

void LCDLin32168_c(void);
void LCDLin32168_c(void) { } /* avoid empty object files */

#endif /* (LCD_CONTROLLER undefined) */
