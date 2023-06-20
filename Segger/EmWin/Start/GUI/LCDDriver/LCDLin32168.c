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
File        : LCDLin32168.c
Purpose     : Driver for accessing linear video memory
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "LCD_SIM.h"

#if (LCD_CONTROLLER == 32168) \
    && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))

#if (GUI_VERSION >= 41700)
  #ifndef   LCD_DISPLAY_INDEX
    #define LCD_DISPLAY_INDEX 0
  #endif
  #if (LCD_DISPLAY_INDEX == 0)
    #include "LCD_L0_Generic.h"
  #endif
#endif

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
#if (LCD_BITSPERPIXEL != 16) && (LCD_BITSPERPIXEL != 32)
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
  U32  SIM_ReadMem32p(U32 * p);
  void SIM_WriteMem16(unsigned int Off, U16 Data);
  void SIM_WriteMem32(unsigned int Off, U32 Data);
  void SIM_WriteMem16p(U16 * p, U16 Data);
  void SIM_WriteMem32p(U32 * p, U32 Data);
  void SIM_memcpy(void * pDst, const void * pSrc, int Len);
  void SIM_SetVRAMAddr(U32 Addr);
  void SIM_SetVRAMSize(int xSize, int ySize);
  #undef  LCD_SET_ORG
  #define LCD_SET_ORG(x, y)          LCDSIM_SetOrg(x, y, LCD_DISPLAY_INDEX);
  #define LCD_READ_MEM16(Off)        SIM_ReadMem16(Off)
  #define LCD_READ_MEM32(Off)        SIM_ReadMem32(Off)
  #define LCD_READ_MEM32P(p)         SIM_ReadMem32p(p)
  #define LCD_WRITE_MEM16(Off, Data) SIM_WriteMem16(Off, Data)
  #define LCD_WRITE_MEM32(Off, Data) SIM_WriteMem32(Off, Data)
  #define LCD_WRITE_MEM16P(p, Data)  SIM_WriteMem16p(p, Data)
  #define LCD_WRITE_MEM32P(p, Data)  SIM_WriteMem32p(p, Data)
  #undef  GUI_MEMCPY
  #define GUI_MEMCPY(pDst, pSrc, Len) SIM_memcpy(pDst, pSrc, Len)
#else
  #define LCD_READ_MEM16(Off)        (*((U16 *)_VRAMAddr + (U32)Off))
  #define LCD_READ_MEM32(Off)        (*((U32 *)_VRAMAddr + (U32)Off))
  #define LCD_READ_MEM32P(p)         (*((U32 *)p                      ))
  #define LCD_WRITE_MEM16(Off, Data)  *((U16 *)_VRAMAddr + (U32)Off) = Data
  #define LCD_WRITE_MEM32(Off, Data)  *((U32 *)_VRAMAddr + (U32)Off) = Data
  #define LCD_WRITE_MEM16P(p, Data)   *((U16 *)p                      ) = Data
  #define LCD_WRITE_MEM32P(p, Data)   *((U32 *)p                      ) = Data
#endif

#define WRITE_MEM16(Off, Data) LCD_WRITE_MEM16(Off, Data)
#define WRITE_MEM32(Off, Data) LCD_WRITE_MEM32(Off, Data)
#define READ_MEM16(Off)        LCD_READ_MEM16(Off)
#define READ_MEM32(Off)        LCD_READ_MEM32(Off)
#define READ_MEM32P(p)         LCD_READ_MEM32P(p)
#define WRITE_MEM16P(p, Data)  LCD_WRITE_MEM16P(p, Data)
#define WRITE_MEM32P(p, Data)  LCD_WRITE_MEM32P(p, Data)

#define PIXELS_PER_DWORD (32 / LCD_BITSPERPIXEL)
#define PIXELS_PER_WORD  (16 / LCD_BITSPERPIXEL)
#define DWORDS_PER_LINE  (_vxSizePhys * LCD_BITSPERPIXEL / 32)
#define WORDS_PER_LINE   (_vxSizePhys * LCD_BITSPERPIXEL / 16)

#if   (LCD_BITSPERPIXEL == 16)
  #define XY2OFF32(x,y)    ((U32)y * DWORDS_PER_LINE + ((U32)x >> 1))
  #define XY2OFF16(x,y)    ((U32)y * WORDS_PER_LINE  + x)
#elif (LCD_BITSPERPIXEL == 32)
  #define XY2OFF32(x,y)    ((U32)y * DWORDS_PER_LINE + ((U32)x >> 0))
  #define XY2OFF16(x,y)    ((U32)y * WORDS_PER_LINE  + (x << 1))
#endif

#define OFF2PTR16(Off)     (U16 *)((U8 *)_VRAMAddr + Off * 2)
#define OFF2PTR32(Off)     (U32 *)((U8 *)_VRAMAddr + Off * 4)

/* Macros for MIRROR_, SWAP_ and LUT_ */
#if   ((LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 0)) 
  #define LOG2PHYS_X(x, y) x
  #define LOG2PHYS_Y(x, y) y
#elif ((LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 1)) 
  #define LOG2PHYS_X(x, y) y
  #define LOG2PHYS_Y(x, y) x
#elif ((LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 1) && (LCD_SWAP_XY == 0)) 
  #define LOG2PHYS_X(x, y) x
  #define LOG2PHYS_Y(x, y) _vySize - 1 - (y)
#elif ((LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 1) && (LCD_SWAP_XY == 1)) 
  #define LOG2PHYS_X(x, y) y
  #define LOG2PHYS_Y(x, y) _vxSize - 1 - (x)
#elif ((LCD_MIRROR_X == 1) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 0)) 
  #define LOG2PHYS_X(x, y) _vxSize - 1 - (x)
  #define LOG2PHYS_Y(x, y) y
#elif ((LCD_MIRROR_X == 1) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 1)) 
  #define LOG2PHYS_X(x, y) _vySize - 1 - (y)
  #define LOG2PHYS_Y(x, y) x
#elif ((LCD_MIRROR_X == 1) && (LCD_MIRROR_Y == 1) && (LCD_SWAP_XY == 0)) 
  #define LOG2PHYS_X(x, y) _vxSize - 1 - (x)
  #define LOG2PHYS_Y(x, y) _vySize - 1 - (y)
#elif ((LCD_MIRROR_X == 1) && (LCD_MIRROR_Y == 1) && (LCD_SWAP_XY == 1)) 
  #define LOG2PHYS_X(x, y) _vySize - 1 - (y)
  #define LOG2PHYS_Y(x, y) _vxSize - 1 - (x)
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static U32 _VRAMAddr;
static int _xSize, _ySize, _vxSize, _vySize, _vxSizePhys;

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
/*********************************************************************
*
*       Draw Bitmap 1 BPP, optimized for LCD_BITSPERPIXEL == 16, LCD_MIRROR_X == 0, LCD_SWAP_XY == 0
*/
#if (LCD_BITSPERPIXEL == 16) && \
    (LCD_MIRROR_X == 0)      && \
    (LCD_SWAP_XY == 0)
static void _DrawBitLine1BPP(unsigned x, unsigned y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  unsigned Pixels, PixelCnt;
  LCD_PIXELINDEX Index, Index0, Index1, IndexMask;
  U32 Off;
  #if LCD_MIRROR_Y
    y = (_vySize - 1 - (y));
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
*       Draw Bitmap 1 BPP, optimized for LCD_BITSPERPIXEL == 16, LCD_MIRROR_X == 1, LCD_SWAP_XY == 0
*/
#elif (LCD_BITSPERPIXEL == 16) && \
    (LCD_MIRROR_X == 1)      && \
    (LCD_SWAP_XY == 0)
static void _DrawBitLine1BPP(unsigned x, unsigned y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  unsigned Pixels, PixelCnt;
  LCD_PIXELINDEX Index, Index0, Index1, IndexMask;
  U32 Off;
  x       += Diff;
  x = LOG2PHYS_X(x, y);
  #if LCD_MIRROR_Y
    y = LOG2PHYS_Y(x, y);
  #endif
  Index0   = *(pTrans + 0);
  Index1   = *(pTrans + 1);
  Off      = XY2OFF16(x, y);
  PixelCnt = 8 - Diff;
  Pixels   = LCD_aMirror[*p] >> Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    do {
      Index = (Pixels & 1) ? Index1 : Index0;
      WRITE_MEM16(Off, Index);
      Off--;
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
      Off--;
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
      Off--;
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
*       Draw Bitmap 1 BPP, optimized for LCD_BITSPERPIXEL == 16, LCD_SWAP_XY == 1
*/
#elif (LCD_BITSPERPIXEL == 16) && \
      (LCD_SWAP_XY == 1)
static void _DrawBitLine1BPP_Swap(unsigned x, unsigned y, U8 const GUI_UNI_PTR * pData, int ySize, const LCD_PIXELINDEX * pTrans, int BytesPerLine, U8 Pos) {
  LCD_PIXELINDEX Index, Index0, Index1, IndexMask;
  U32 Off;
  U8 Mask;
  U16 * pDest;
  #if LCD_MIRROR_Y
    int y0 = _vxSize - x - 1;
  #else
    int y0 = x;
  #endif
  #if LCD_MIRROR_X
    int x0 = _vySize - y - 1;
  #else
    int x0 = y;
  #endif
  IndexMask = LCD_L0_GetIndexMask();
  Off = XY2OFF16(x0,y0);
  Index0 = *(pTrans + 0);
  Index1 = *(pTrans + 1);
  Mask = 0x80 >> (Pos & 0x7);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    pDest = OFF2PTR16(Off);
    while (ySize >= 4) {
      do {
        #if (LCD_MIRROR_X == 1)
          Index = (*pData & Mask) ? Index1 : Index0;
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest--;
          Index = (*pData & Mask) ? Index1 : Index0;
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest--;
          Index = (*pData & Mask) ? Index1 : Index0;
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest--;
          Index = (*pData & Mask) ? Index1 : Index0;
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest--;
        #else
          Index = (*pData & Mask) ? Index1 : Index0;
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest++;
          Index = (*pData & Mask) ? Index1 : Index0;
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest++;
          Index = (*pData & Mask) ? Index1 : Index0;
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest++;
          Index = (*pData & Mask) ? Index1 : Index0;
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest++;
        #endif
        ySize -= 4;
      } while (ySize >= 4);
    }
    if (ySize) { 
	    do {
        #if (LCD_MIRROR_X == 1)
          Index = (*pData & Mask) ? Index1 : Index0;
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest--;
        #else
          Index = (*pData & Mask) ? Index1 : Index0;
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest++;
        #endif
      } while (--ySize);
    }
    break;
  case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
  case LCD_DRAWMODE_XOR:
    do {
      if (*pData & Mask) {
        Index = READ_MEM16(Off);
        Index ^= IndexMask;
        WRITE_MEM16(Off, Index);
      }
      pData += BytesPerLine;
      #if (LCD_MIRROR_X == 1)
        Off--;
      #else
        Off++;
      #endif
    } while (--ySize);
    break;
  case LCD_DRAWMODE_TRANS:
    pDest = OFF2PTR16(Off);
    while (ySize >= 4) {
      do {
        #if (LCD_MIRROR_X == 1)
          if (*pData & Mask) {
            WRITE_MEM16P(pDest, Index1);
          }
          pData += BytesPerLine;
          pDest--;
          if (*pData & Mask) {
            WRITE_MEM16P(pDest, Index1);
          }
          pData += BytesPerLine;
          pDest--;
          if (*pData & Mask) {
            WRITE_MEM16P(pDest, Index1);
          }
          pData += BytesPerLine;
          pDest--;
          if (*pData & Mask) {
            WRITE_MEM16P(pDest, Index1);
          }
          pData += BytesPerLine;
          pDest--;
        #else
          if (*pData & Mask) {
            WRITE_MEM16P(pDest, Index1);
          }
          pData += BytesPerLine;
          pDest++;
          if (*pData & Mask) {
            WRITE_MEM16P(pDest, Index1);
          }
          pData += BytesPerLine;
          pDest++;
          if (*pData & Mask) {
            WRITE_MEM16P(pDest, Index1);
          }
          pData += BytesPerLine;
          pDest++;
          if (*pData & Mask) {
            WRITE_MEM16P(pDest, Index1);
          }
          pData += BytesPerLine;
          pDest++;
        #endif
        ySize -= 4;
      } while (ySize >= 4);
    }
    if (ySize) { 
	    do {
        if (*pData & Mask) {
          WRITE_MEM16P(pDest, Index1);
        }
        pData += BytesPerLine;
        #if (LCD_MIRROR_X == 1)
          pDest--;
        #else
          pDest++;
        #endif
      } while (--ySize);
    }
    break;
  }
}

/*********************************************************************
*
*       Draw Bitmap 1 BPP, optimized for LCD_BITSPERPIXEL == 32, LCD_MIRROR_X == 0, LCD_SWAP_XY == 0
*/
#elif (LCD_BITSPERPIXEL == 32) && \
      (LCD_MIRROR_X == 0)      && \
      (LCD_SWAP_XY == 0)
static void _DrawBitLine1BPP(unsigned x, unsigned y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Index0 = *(pTrans + 0);
  LCD_PIXELINDEX Index1 = *(pTrans + 1);
  LCD_PIXELINDEX IndexMask;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    {
      U32 * pDest;
      U32 Color;
      unsigned Pixels, PixelCnt, Off;
      #if LCD_MIRROR_Y
        y = (_vySize - 1 - (y));
      #endif
      PixelCnt = 8 - Diff;
      Pixels   = LCD_aMirror[*p] >> Diff;
      Off      = XY2OFF32(x, y);
      pDest    = OFF2PTR32(Off);
      do {
        Color    = (Pixels & 1) ? Index1 : Index0;
        Pixels >>= 1;
        if (--PixelCnt == 0) {
          Pixels = LCD_aMirror[*(++p)];
          PixelCnt = 8;
        }
        WRITE_MEM32P(pDest, Color);
        pDest++;
      } while (--xsize);
    }
    break;
  case LCD_DRAWMODE_TRANS:
    {
      U32 * pDest;
      unsigned Pixels, PixelCnt, Off;
      #if LCD_MIRROR_Y
        y = (_vySize - 1 - (y));
      #endif
      PixelCnt = 8 - Diff;
      Pixels   = LCD_aMirror[*p] >> Diff;
      Off      = XY2OFF32(x, y);
      pDest    = OFF2PTR32(Off);
      do {
        if (Pixels & 1) {
          WRITE_MEM32P(pDest, Index1);
        }
        pDest++;
        Pixels >>= 1;
        if (--PixelCnt == 0) {
          Pixels = LCD_aMirror[*(++p)];
          PixelCnt = 8;
        }
      } while (--xsize);
    }
    break;
  case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
  case LCD_DRAWMODE_XOR:
    IndexMask = LCD_L0_GetIndexMask();
    do {
      if (*p & (0x80 >> Diff)) {
        int Pixel = LCD_L0_GetPixelIndex(x, y);
        LCD_L0_SetPixelIndex(x, y, Pixel ^ IndexMask);
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

/*********************************************************************
*
*       Draw Bitmap 1 BPP, not optimized
*/
#else
static void  _DrawBitLine1BPP(int x, int y, U8 const GUI_UNI_PTR *p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX Index0 = *(pTrans + 0);
  LCD_PIXELINDEX Index1 = *(pTrans + 1);
  LCD_PIXELINDEX Index, IndexMask;
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
  		if (*p & (0x80 >> Diff)) {
        LCD_L0_SetPixelIndex(x, y, Index1);
      }
      x++;
			if (++Diff == 8) {
        Diff = 0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
  case LCD_DRAWMODE_XOR:
    IndexMask = LCD_L0_GetIndexMask();
    do {
  		if (*p & (0x80 >> Diff)) {
        Index = LCD_L0_GetPixelIndex(x, y);
        Index ^= IndexMask;
        LCD_L0_SetPixelIndex(x, y, Index);
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
*       Draw Bitmap 2 BPP, optimized for LCD_BITSPERPIXEL == 32, LCD_MIRROR_X == 0, LCD_SWAP_XY == 0
*/
#if (LCD_MAX_LOG_COLORS > 2)
#if (LCD_BITSPERPIXEL == 32) && \
    (LCD_MIRROR_X == 0)      && \
    (LCD_SWAP_XY == 0)
static void  _DrawBitLine2BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels, PixelIndex;
  int CurrentPixel, Shift, Index;
  U32 * pDest;
  U32 Off;
  if (pTrans == NULL) {
    return; /* pTrans is required */
  }
  #if LCD_MIRROR_Y
    y = (_vySize - 1 - (y));
  #endif
  CurrentPixel = Diff;
  Pixels       = *p;
  x           += Diff;
  Off          = XY2OFF32(x, y);
  pDest        = OFF2PTR32(Off);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    do {
      Shift = (3 - CurrentPixel) << 1;
      Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
      PixelIndex = *(pTrans + Index);
      WRITE_MEM32P(pDest, PixelIndex);
      pDest++;
      if (++CurrentPixel == 4) {
        CurrentPixel = 0;
        Pixels = *(++p);
      }
		} while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
      Shift = (3 - CurrentPixel) << 1;
      Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
      if (Index) {
        PixelIndex = *(pTrans + Index);
        WRITE_MEM32P(pDest, PixelIndex);
      }
      pDest++;
      if (++CurrentPixel == 4) {
        CurrentPixel = 0;
        Pixels = *(++p);
      }
		} while (--xsize);
    break;
  }
}

/*********************************************************************
*
*       Draw Bitmap 2 BPP, not optimized
*/
#else
static void  _DrawBitLine2BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels, PixelIndex;
  int CurrentPixel, Shift, Index;
  Pixels       = *p;
  CurrentPixel = Diff;
  x           += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    if (pTrans) {
      do {
        Shift = (3 - CurrentPixel) << 1;
        Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
        PixelIndex = *(pTrans + Index);
        LCD_L0_SetPixelIndex(x++, y, PixelIndex);
        if (++CurrentPixel == 4) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
    } else {
      do {
        Shift = (3 - CurrentPixel) << 1;
        Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
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
        Shift = (3 - CurrentPixel) << 1;
        Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
        if (Index) {
          PixelIndex = *(pTrans + Index);
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
        Shift = (3 - CurrentPixel) << 1;
        Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
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
#endif

/*********************************************************************
*
*       Draw Bitmap 4 BPP, optimized for LCD_BITSPERPIXEL == 32, LCD_MIRROR_X == 0, LCD_SWAP_XY == 0
*/
#if (LCD_MAX_LOG_COLORS > 4)
#if (LCD_BITSPERPIXEL == 32) && \
    (LCD_MIRROR_X == 0)      && \
    (LCD_SWAP_XY == 0)
static void  _DrawBitLine4BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels, PixelIndex;
  int CurrentPixel, Shift, Index;
  U32 * pDest;
  U32 Off;
  if (pTrans == NULL) {
    return; /* pTrans is required */
  }
  #if LCD_MIRROR_Y
    y = (_vySize - 1 - (y));
  #endif
  Pixels       = *p;
  CurrentPixel = Diff;
  x           += Diff;
  Off          = XY2OFF32(x, y);
  pDest        = OFF2PTR32(Off);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    do {
      Shift = (1 - CurrentPixel) << 2;
      Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
      PixelIndex = *(pTrans + Index);
      WRITE_MEM32P(pDest, PixelIndex);
      pDest++;
      if (++CurrentPixel == 2) {
        CurrentPixel = 0;
        Pixels = *(++p);
      }
		} while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
      Shift = (1 - CurrentPixel) << 2;
      Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
      if (Index) {
        PixelIndex = *(pTrans + Index);
        WRITE_MEM32P(pDest, PixelIndex);
      }
      pDest++;
      if (++CurrentPixel == 2) {
        CurrentPixel = 0;
        Pixels = *(++p);
      }
		} while (--xsize);
    break;
  }
}

/*********************************************************************
*
*       Draw Bitmap 4 BPP, not optimized
*/
#else
static void  _DrawBitLine4BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels, PixelIndex;
  int CurrentPixel, Shift, Index;
  Pixels       = *p;
  CurrentPixel = Diff;
  x           += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    if (pTrans) {
      do {
        Shift = (1 - CurrentPixel) << 2;
        Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
        PixelIndex = *(pTrans + Index);
        LCD_L0_SetPixelIndex(x++, y, PixelIndex);
        if (++CurrentPixel == 2) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
    } else {
      do {
        Shift = (1 - CurrentPixel) << 2;
        Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
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
        Shift = (1 - CurrentPixel) << 2;
        Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
        if (Index) {
          PixelIndex = *(pTrans + Index);
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
        Shift = (1 - CurrentPixel) << 2;
        Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
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
#endif

/*********************************************************************
*
*       Draw Bitmap 8 BPP, optimized for LCD_BITSPERPIXEL == 16, LCD_MIRROR_X == 0, LCD_SWAP_XY == 0
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
    y = (_vySize - 1 - (y));
  #endif
  Off   = XY2OFF16(x,y);
  pDest = OFF2PTR16(Off);
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
*       Draw Bitmap 8 BPP, optimized for LCD_BITSPERPIXEL == 16, LCD_MIRROR_X == 1, LCD_SWAP_XY == 0
*/
#elif (LCD_BITSPERPIXEL == 16) && \
    (LCD_MIRROR_X == 1)      && \
    (LCD_SWAP_XY == 0)
static void  _DrawBitLine8BPP(int x, int y, U8 const GUI_UNI_PTR * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixel;
  register U32 Off;
  U16 * pDest;
  if (!pTrans) {
    return; /* No translation from 8bpp BMP to 16bpp device makes no sense */
  }
  x = LOG2PHYS_X(x, y);
  #if LCD_MIRROR_Y
    y = (_vySize - 1 - (y));
  #endif
  Off   = XY2OFF16(x,y);
  pDest = OFF2PTR16(Off);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    while (xsize >= 8) {
      WRITE_MEM16P(pDest - 0, *(pTrans + *(p + 0)));
      WRITE_MEM16P(pDest - 1, *(pTrans + *(p + 1)));
      WRITE_MEM16P(pDest - 2, *(pTrans + *(p + 2)));
      WRITE_MEM16P(pDest - 3, *(pTrans + *(p + 3)));
      WRITE_MEM16P(pDest - 4, *(pTrans + *(p + 4)));
      WRITE_MEM16P(pDest - 5, *(pTrans + *(p + 5)));
      WRITE_MEM16P(pDest - 6, *(pTrans + *(p + 6)));
      WRITE_MEM16P(pDest - 7, *(pTrans + *(p + 7)));
      xsize -= 8;
      p     += 8;
      pDest -= 8;
    }
    while (xsize >= 4) {
      WRITE_MEM16P(pDest - 0, *(pTrans + *(p + 0)));
      WRITE_MEM16P(pDest - 1, *(pTrans + *(p + 1)));
      WRITE_MEM16P(pDest - 2, *(pTrans + *(p + 2)));
      WRITE_MEM16P(pDest - 3, *(pTrans + *(p + 3)));
      xsize -= 4;
      p     += 4;
      pDest -= 4;
    }
    while (xsize) {
      WRITE_MEM16P(pDest + 0, *(pTrans + *(p + 0)));
      xsize--;
      p++;
      pDest--;
    }
    break;
  case LCD_DRAWMODE_TRANS:
    for (; xsize > 0; xsize--, p++, pDest--) {
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
*       Draw Bitmap 8 BPP, optimized for LCD_BITSPERPIXEL == 16, LCD_SWAP_XY == 1
*/
#elif (LCD_BITSPERPIXEL == 16) && \
      (LCD_SWAP_XY == 1)
static void _DrawBitLine8BPP_Swap(unsigned x, unsigned y, U8 const GUI_UNI_PTR * pData, int ySize, const LCD_PIXELINDEX * pTrans, int BytesPerLine, U8 Pos) {
  LCD_PIXELINDEX Index;
  U32 Off;
  U8 Pixel;
  U16 * pDest;
  #if LCD_MIRROR_Y
    int y0 = _vxSize - x - 1;
  #else
    int y0 = x;
  #endif
  #if LCD_MIRROR_X
    int x0 = _vySize - y - 1;
  #else
    int x0 = y;
  #endif
  if (pTrans == NULL) {
    return; /* Because it makes no sense to use 8bpp bitmaps without palette with a 16bpp configuration */
  }
  Off = XY2OFF16(x0, y0);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    pDest = OFF2PTR16(Off);
    while (ySize >= 4) {
      do {
        #if (LCD_MIRROR_X == 1)
          Index = *(pTrans + *pData);
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest--;
          Index = *(pTrans + *pData);
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest--;
          Index = *(pTrans + *pData);
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest--;
          Index = *(pTrans + *pData);
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest--;
        #else
          Index = *(pTrans + *pData);
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest++;
          Index = *(pTrans + *pData);
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest++;
          Index = *(pTrans + *pData);
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest++;
          Index = *(pTrans + *pData);
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest++;
        #endif
        ySize -= 4;
      } while (ySize >= 4);
    }
    if (ySize) { 
	    do {
        #if (LCD_MIRROR_X == 1)
          Index = *(pTrans + *pData);
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest--;
        #else
          Index = *(pTrans + *pData);
          WRITE_MEM16P(pDest, Index);
          pData += BytesPerLine;
          pDest++;
        #endif
      } while (--ySize);
    }
    break;
  case LCD_DRAWMODE_TRANS:
    pDest = OFF2PTR16(Off);
    while (ySize >= 4) {
      do {
        #if (LCD_MIRROR_X == 1)
          Pixel = *pData;
          if (Pixel) {
            Index = *(pTrans + Pixel);
            WRITE_MEM16P(pDest, Index);
          }
          pData += BytesPerLine;
          pDest--;
          Pixel = *pData;
          if (Pixel) {
            Index = *(pTrans + Pixel);
            WRITE_MEM16P(pDest, Index);
          }
          pData += BytesPerLine;
          pDest--;
          Pixel = *pData;
          if (Pixel) {
            Index = *(pTrans + Pixel);
            WRITE_MEM16P(pDest, Index);
          }
          pData += BytesPerLine;
          pDest--;
          Pixel = *pData;
          if (Pixel) {
            Index = *(pTrans + Pixel);
            WRITE_MEM16P(pDest, Index);
          }
          pData += BytesPerLine;
          pDest--;
        #else
          Pixel = *pData;
          if (Pixel) {
            Index = *(pTrans + Pixel);
            WRITE_MEM16P(pDest, Index);
          }
          pData += BytesPerLine;
          pDest++;
          Pixel = *pData;
          if (Pixel) {
            Index = *(pTrans + Pixel);
            WRITE_MEM16P(pDest, Index);
          }
          pData += BytesPerLine;
          pDest++;
          Pixel = *pData;
          if (Pixel) {
            Index = *(pTrans + Pixel);
            WRITE_MEM16P(pDest, Index);
          }
          pData += BytesPerLine;
          pDest++;
          Pixel = *pData;
          if (Pixel) {
            Index = *(pTrans + Pixel);
            WRITE_MEM16P(pDest, Index);
          }
          pData += BytesPerLine;
          pDest++;
        #endif
        ySize -= 4;
      } while (ySize >= 4);
    }
    if (ySize) { 
	    do {
        Pixel = *pData;
        if (Pixel) {
          Index = *(pTrans + Pixel);
          WRITE_MEM16P(pDest, Index);
        }
        pData += BytesPerLine;
        #if (LCD_MIRROR_X == 1)
          pDest--;
        #else
          pDest++;
        #endif
      } while (--ySize);
    }
    break;
  }
}

/*********************************************************************
*
*       Draw Bitmap 8 BPP, optimized for LCD_BITSPERPIXEL == 32, LCD_MIRROR_X == 0, LCD_SWAP_XY == 0
*/
#elif (LCD_BITSPERPIXEL == 32) && \
      (LCD_MIRROR_X == 0)      && \
      (LCD_SWAP_XY == 0)
static void  _DrawBitLine8BPP(int x, int y, U8 const GUI_UNI_PTR * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixel;
  register U32 Off;
  U32 * pDest;
  if (!pTrans) {
    return; /* No translation from 8bpp BMP to 16bpp device makes no sense */
  }
  #if LCD_MIRROR_Y
    y = (_vySize - 1 - (y));
  #endif
  Off   = XY2OFF32(x,y);
  pDest = OFF2PTR32(Off);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    while (xsize >= 8) {
      WRITE_MEM32P(pDest + 0, *(pTrans + *(p + 0)));
      WRITE_MEM32P(pDest + 1, *(pTrans + *(p + 1)));
      WRITE_MEM32P(pDest + 2, *(pTrans + *(p + 2)));
      WRITE_MEM32P(pDest + 3, *(pTrans + *(p + 3)));
      WRITE_MEM32P(pDest + 4, *(pTrans + *(p + 4)));
      WRITE_MEM32P(pDest + 5, *(pTrans + *(p + 5)));
      WRITE_MEM32P(pDest + 6, *(pTrans + *(p + 6)));
      WRITE_MEM32P(pDest + 7, *(pTrans + *(p + 7)));
      xsize -= 8;
      p     += 8;
      pDest += 8;
    }
    while (xsize >= 4) {
      WRITE_MEM32P(pDest + 0, *(pTrans + *(p + 0)));
      WRITE_MEM32P(pDest + 1, *(pTrans + *(p + 1)));
      WRITE_MEM32P(pDest + 2, *(pTrans + *(p + 2)));
      WRITE_MEM32P(pDest + 3, *(pTrans + *(p + 3)));
      xsize -= 4;
      p     += 4;
      pDest += 4;
    }
    while (xsize) {
      WRITE_MEM32P(pDest + 0, *(pTrans + *(p + 0)));
      xsize--;
      p++;
      pDest++;
    }
    break;
  case LCD_DRAWMODE_TRANS:
    for (; xsize > 0; xsize--, p++, pDest++) {
      Pixel = *p;
      if (Pixel) {
        WRITE_MEM32P(pDest, *(pTrans + *p));
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
*       Draw Bitmap 16 BPP, optimized for LCD_BITSPERPIXEL == 16, LCD_MIRROR_X == 0, LCD_SWAP_XY == 0
*/
#if (LCD_BITSPERPIXEL >= 16)
#if (LCD_BITSPERPIXEL == 16) && \
    (LCD_MIRROR_X == 0)      && \
    (LCD_SWAP_XY == 0)
static void _DrawBitLine16BPP(int x, int y, U16 const GUI_UNI_PTR *p, int xsize) {
  U32 Off;
  U16 * pDest;
  #if LCD_MIRROR_Y
    y = (_vySize - 1 - (y));
  #endif
  Off = XY2OFF16(x,y);
  pDest = OFF2PTR16(Off);
  GUI_MEMCPY(pDest, (const void *)p, (U32)xsize << 1);
}

/*********************************************************************
*
*       Draw Bitmap 16 BPP, optimized for LCD_BITSPERPIXEL == 16, LCD_MIRROR_X == 1, LCD_SWAP_XY == 0
*/
#elif (LCD_BITSPERPIXEL == 16) && \
    (LCD_MIRROR_X == 1)      && \
    (LCD_SWAP_XY == 0)
static void _DrawBitLine16BPP(int x, int y, U16 const GUI_UNI_PTR * pData, int xSize) {
  U32 Off;
  U16 * pDest;
  x = LOG2PHYS_X(x, y);
  #if LCD_MIRROR_Y
    y = (_vySize - 1 - (y));
  #endif
  Off = XY2OFF16(x, y);
  pDest = OFF2PTR16(Off);
  while (xSize >= 4) {
    do {
      WRITE_MEM16P(pDest, *pData);
      pDest--;
      pData++;
      WRITE_MEM16P(pDest, *pData);
      pDest--;
      pData++;
      WRITE_MEM16P(pDest, *pData);
      pDest--;
      pData++;
      WRITE_MEM16P(pDest, *pData);
      pDest--;
      pData++;
      xSize -= 4;
    } while (xSize >= 4);
  }
  if (xSize) { 
	  do {
      WRITE_MEM16P(pDest, *pData);
      pDest--;
      pData++;
    } while (--xSize);
  }
}

/*********************************************************************
*
*       Draw Bitmap 16 BPP, optimized for LCD_BITSPERPIXEL == 16, LCD_SWAP_XY == 1
*/
#elif (LCD_BITSPERPIXEL == 16) && \
      (LCD_SWAP_XY == 1)
static void _DrawBitLine16BPP_Swap(int x, int y, U16 const GUI_UNI_PTR * pData, int ySize, int BytesPerLine, U8 Pos) {
  U32 Off;
  U16 *pDest;
  int WordsPerLine;
  WordsPerLine = BytesPerLine >> 1;
  #if LCD_MIRROR_X
    y = _vySize - y - 1;
  #endif
  #if LCD_MIRROR_Y
    x = _vxSize - x - 1;
  #endif
  Off = XY2OFF16(y, x);
  pDest = OFF2PTR16(Off);
  while (ySize >= 4) {
    do {
      #if (LCD_MIRROR_X == 1)
        WRITE_MEM16P(pDest, *pData);
        pDest--;
        pData += WordsPerLine;
        WRITE_MEM16P(pDest, *pData);
        pDest--;
        pData += WordsPerLine;
        WRITE_MEM16P(pDest, *pData);
        pDest--;
        pData += WordsPerLine;
        WRITE_MEM16P(pDest, *pData);
        pDest--;
        pData += WordsPerLine;
      #else
        WRITE_MEM16P(pDest, *pData);
        pDest++;
        pData += WordsPerLine;
        WRITE_MEM16P(pDest, *pData);
        pDest++;
        pData += WordsPerLine;
        WRITE_MEM16P(pDest, *pData);
        pDest++;
        pData += WordsPerLine;
        WRITE_MEM16P(pDest, *pData);
        pDest++;
        pData += WordsPerLine;
      #endif
      ySize -= 4;
    } while (ySize >= 4);
  }
  if (ySize) { 
	  do {
        WRITE_MEM16P(pDest, *pData);
        pData += WordsPerLine;
        #if (LCD_MIRROR_X == 1)
          pDest--;
        #else
          pDest++;
        #endif
    } while (--ySize);
  }
}

/*********************************************************************
*
*       Draw Bitmap 16 BPP, not optimized
*/
#else
static void _DrawBitLine16BPP(int x, int y, U16 const GUI_UNI_PTR * p, int xsize) {
  for (;xsize > 0; xsize--, x++, p++) {
    LCD_L0_SetPixelIndex(x, y, *p);
  }
}
#endif
#endif

/*********************************************************************
*
*       Draw Bitmap 32 BPP, not optimized
*/
#if (LCD_BITSPERPIXEL > 16)
static void _DrawBitLine32BPP(int x, int y, U32 const GUI_UNI_PTR * p, int xsize) {
  for (;xsize > 0; xsize--, x++, p++) {
    LCD_L0_SetPixelIndex(x, y, *p);
  }
}
#endif

/*********************************************************************
*
*       _SetVRAMAddr
*/
static void _SetVRAMAddr(U32 Addr) {
  _VRAMAddr = Addr;
  #ifdef WIN32
    SIM_SetVRAMAddr(Addr);
  #endif
}

/*********************************************************************
*
*       _SetVSize
*/
static void _SetVSize(int xSize, int ySize) {
  _vxSize = xSize;
  _vySize = ySize;
  _vxSizePhys = (LCD_SWAP_XY) ? _vySize : _vxSize;
  #ifdef WIN32
    SIM_SetVRAMSize(xSize, ySize);
  #endif
}

/*********************************************************************
*
*       _SetSize
*/
static void _SetSize(int xSize, int ySize) {
  _xSize = xSize;
  _ySize = ySize;
}

/*********************************************************************
*
*       _ReadRect, optimized for LCD_BITSPERPIXEL == 16, LCD_MIRROR_X == 0, LCD_MIRROR_Y == 0, LCD_SWAP_XY == 0
*/
#if (LCD_BITSPERPIXEL == 16) && \
    (LCD_MIRROR_X == 0) && \
    (LCD_MIRROR_Y == 0) && \
    (LCD_SWAP_XY == 0)
static void _ReadRect(int x0, int y0, int x1, int y1, LCD_PIXELINDEX * pBuffer) {
  U32 Off;
  int x, NumPixelsPerLine;
  U16 * p;

  p = (U16 *)pBuffer;
  x = x0;
  do {
    Off = XY2OFF16(x0, y0);
    NumPixelsPerLine = x1 - x0 + 1;
    do {
      *p++ = READ_MEM16(Off);
      Off++;
    } while (--NumPixelsPerLine);
    x0 = x;
  } while (y0++ < y1);
}

/*********************************************************************
*
*       _ReadRect, optimized for LCD_BITSPERPIXEL == 16, LCD_MIRROR_X == 1, LCD_MIRROR_Y == 1, LCD_SWAP_XY == 0
*/
#elif (LCD_BITSPERPIXEL == 16) && \
    (LCD_MIRROR_X == 1) && \
    (LCD_MIRROR_Y == 1) && \
    (LCD_SWAP_XY == 0)
static void _ReadRect(int x0, int y0, int x1, int y1, LCD_PIXELINDEX * pBuffer) {
  U32 Off;
  int x, x0Phys, y0Phys, x1Phys, y1Phys, NumPixelsPerLine;
  U16 * p;

  p = (U16 *)pBuffer;
  x0Phys = _xSize - x1 - 1;
  x1Phys = _xSize - x0 - 1;
  y0Phys = _ySize - y1 - 1;
  y1Phys = _ySize - y0 - 1;
  x = x1Phys;
  do {
    Off = XY2OFF16(x1Phys, y1Phys);
    NumPixelsPerLine = x1Phys - x0Phys + 1;
    do {
      *p++ = READ_MEM16(Off);
      Off--;
    } while (--NumPixelsPerLine);
    x1Phys = x;
  } while (y1Phys-- > y0Phys);
}

#else

/*********************************************************************
*
*       _ReadRect, not existing
*/
#define _ReadRect NULL

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
  #if   (LCD_BITSPERPIXEL == 16)
    Off = XY2OFF16(xPhys, yPhys);
    WRITE_MEM16(Off, PixelIndex);
  #elif (LCD_BITSPERPIXEL == 32)
    Off = XY2OFF32(xPhys, yPhys);
    WRITE_MEM32(Off, PixelIndex);
  #endif
  #undef xPhys
  #undef yPhys
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
  #if   (LCD_BITSPERPIXEL == 16)
    Off        = XY2OFF16(xPhys, yPhys);
    PixelIndex = READ_MEM16(Off);
  #elif (LCD_BITSPERPIXEL == 32)
    Off        = XY2OFF32(xPhys, yPhys);
    PixelIndex = READ_MEM32(Off);
  #endif
  return PixelIndex;
  #undef xPhys
  #undef yPhys
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
*       LCD_L0_DrawHLine, optimized for LCD_BITSPERPIXEL == 16, LCD_SWAP_XY == 0
*/
#if (LCD_BITSPERPIXEL == 16) && \
    (LCD_SWAP_XY == 0)
void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; x0 <= x1; x0++) {
      LCD_L0_XorPixel(x0, y);
    }
  } else {
    U32 * pDest;
    U32 Off;
    int RemPixels;
    U32 Data, ColorMask;
    #if (LCD_MIRROR_X == 1)
    {
      int temp;
      temp = x0;
      x0 = _vxSize - x1   - 1;
      x1 = _vxSize - temp - 1;
    }
    #endif
    #if LCD_MIRROR_Y
      y = LOG2PHYS_Y(x, y);
    #endif
    Off = XY2OFF32(x0, y);
    pDest = OFF2PTR32(Off);
    RemPixels = x1 - x0 + 1;
    /* First DWORD */
    if (x0 & 1) {
      Data = READ_MEM32P(pDest);
      #if (LCD_ENDIAN_BIG == 0)
        Data &= 0xFFFF;
        Data |= (((U32)LCD_COLORINDEX) << 16);
      #else
        Data &= 0xFFFF0000;
        Data |= LCD_COLORINDEX;
      #endif
      WRITE_MEM32P(pDest, Data);
      pDest++;
      RemPixels--;
    }
    /* Complete DWORDS */
    ColorMask = LCD_COLORINDEX * 0x00010001;
    if (RemPixels >= 16) {
      RemPixels -= 16;
      do {
        WRITE_MEM32P(pDest,     ColorMask);
        WRITE_MEM32P(pDest + 1, ColorMask);
        WRITE_MEM32P(pDest + 2, ColorMask);
        WRITE_MEM32P(pDest + 3, ColorMask);
        WRITE_MEM32P(pDest + 4, ColorMask);
        WRITE_MEM32P(pDest + 5, ColorMask);
        WRITE_MEM32P(pDest + 6, ColorMask);
        WRITE_MEM32P(pDest + 7, ColorMask);
        pDest += 8;
        RemPixels -= 16;
      } while (RemPixels >= 0);
      RemPixels += 16;
    }
    if (RemPixels >= 2) {
      do {
        WRITE_MEM32P(pDest, ColorMask);
        pDest++;
        RemPixels -= 2;
      } while (RemPixels >= 2);
    }
    /* Last DWORD */
    if (RemPixels > 0) {
      Data = READ_MEM32P(pDest);
      #if (LCD_ENDIAN_BIG == 0)
        Data &= 0xFFFF0000;
        Data |= LCD_COLORINDEX & 0xFFFF;
      #else
        Data &= 0xFFFF;
        Data |= (((U32)LCD_COLORINDEX) << 16);
      #endif
      WRITE_MEM32P(pDest, Data);
    }
  }
}

/*********************************************************************
*
*       LCD_L0_DrawHLine, optimized for LCD_BITSPERPIXEL == 32, LCD_SWAP_XY == 0
*/
#elif (LCD_BITSPERPIXEL == 32) && \
      (LCD_SWAP_XY == 0)
void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; x0 <= x1; x0++) {
      LCD_L0_XorPixel(x0, y);
    }
  } else {
    register LCD_PIXELINDEX Color;
    U32 * pDest;
    U32 Off, RemPixels;
    #if (LCD_MIRROR_X == 1)
    {
      int temp;
      temp = x0;
      x0 = _vxSize - x1   - 1;
      x1 = _vxSize - temp - 1;
    }
    #endif
    #if LCD_MIRROR_Y
      y = LOG2PHYS_Y(x, y);
    #endif
    Color = LCD_COLORINDEX;
    Off = XY2OFF32(x0, y);
    pDest = OFF2PTR32(Off);
    RemPixels = x1 - x0 + 1;
    if (RemPixels >= 16) {
      do {
        WRITE_MEM32P(pDest     , Color);
        WRITE_MEM32P(pDest +  1, Color);
        WRITE_MEM32P(pDest +  2, Color);
        WRITE_MEM32P(pDest +  3, Color);
        WRITE_MEM32P(pDest +  4, Color);
        WRITE_MEM32P(pDest +  5, Color);
        WRITE_MEM32P(pDest +  6, Color);
        WRITE_MEM32P(pDest +  7, Color);
        WRITE_MEM32P(pDest +  8, Color);
        WRITE_MEM32P(pDest +  9, Color);
        WRITE_MEM32P(pDest + 10, Color);
        WRITE_MEM32P(pDest + 11, Color);
        WRITE_MEM32P(pDest + 12, Color);
        WRITE_MEM32P(pDest + 13, Color);
        WRITE_MEM32P(pDest + 14, Color);
        WRITE_MEM32P(pDest + 15, Color);
        pDest += 16;
        RemPixels -= 16;
      } while (RemPixels >= 16);
    }
    if (RemPixels) {
      do {
        WRITE_MEM32P(pDest, LCD_COLORINDEX);
        pDest++;
      } while (--RemPixels);
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
*       LCD_L0_DrawVLine, optimized for LCD_BITSPERPIXEL == 16, LCD_SWAP_XY == 1
*/
#if (LCD_BITSPERPIXEL == 16) && \
    (LCD_SWAP_XY == 1)
void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; y0 <= y1; y0++) {
      LCD_L0_XorPixel(x, y0);
    }
  } else {
    U32 Off, RemPixels;
    U32 Data, ColorMask;
    U32 * pDest;
    int x0, x1, y;

    #if (LCD_MIRROR_X == 1)
      x0  = _vySize - y1 - 1;
      x1  = _vySize - y0 - 1;
    #else
      x0  = y0;
      x1  = y1;
    #endif
    #if (LCD_MIRROR_Y == 1)
      y   = _vxSize - x - 1;
    #else
      y   = x;
    #endif
    Off = XY2OFF32(x0, y);
    RemPixels = x1 - x0 + 1;
    pDest = OFF2PTR32(Off);
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
      WRITE_MEM32P(pDest, Data);
      pDest++;
      RemPixels--;
    }
    /* Complete DWORDS */
    ColorMask = LCD_COLORINDEX * 0x00010001;
    if (RemPixels >= 16) {
      do {
        WRITE_MEM32P(pDest,     ColorMask);
        WRITE_MEM32P(pDest + 1, ColorMask);
        WRITE_MEM32P(pDest + 2, ColorMask);
        WRITE_MEM32P(pDest + 3, ColorMask);
        WRITE_MEM32P(pDest + 4, ColorMask);
        WRITE_MEM32P(pDest + 5, ColorMask);
        WRITE_MEM32P(pDest + 6, ColorMask);
        WRITE_MEM32P(pDest + 7, ColorMask);
        pDest += 8;
      } while ((RemPixels -= 16) >= 16);
    }
    if (RemPixels >= 2) {
      do {
        WRITE_MEM32P(pDest, ColorMask);
        pDest++;
      } while ((RemPixels -= 2) >= 2);
    }
    /* Last DWORD */
    if (RemPixels > 0) {
      Data = READ_MEM32P(pDest);
      #if (LCD_ENDIAN_BIG == 0)
        Data &= 0xFFFF0000;
        Data |= LCD_COLORINDEX & 0xFFFF;
      #else
        Data &= 0xFFFF;
        Data |= (((U32)LCD_COLORINDEX) << 16);
      #endif
      WRITE_MEM32P(pDest, Data);
    }
  }
}

/*********************************************************************
*
*       LCD_L0_DrawVLine, not optimized
*/
#else

#if LCD_SWAP_XY
  #if LCD_ALLOW_NON_OPTIMIZED_MODE == 0
    #error Non-optimized mode. Please select an other mode, define LCD_ALLOW_NON_OPTIMIZED_MODE in LCDCOnf.h or contact support.
  #endif
#endif

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
#endif

/*********************************************************************
*
*       LCD_L0_FillRect
*/
void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  #ifdef LCD_FILL_RECT
     LCD_FILL_RECT(x0, y0, x1, y1, LCD_COLORINDEX);
  #else
    #if (LCD_SWAP_XY == 0)
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
                       int xSize, int ySize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8 GUI_UNI_PTR * pData, int Diff,
                       const LCD_PIXELINDEX* pTrans)
{
  int i;
  /* Use _DrawBitLineXBPP and _DrawBitLineXBPP_Swap */
  switch (BitsPerPixel) {
  case 1:
    #if (LCD_BITSPERPIXEL == 16) && (LCD_SWAP_XY == 1)
      xSize += Diff & 7;
      for (i = Diff; i < xSize; i++) {
        _DrawBitLine1BPP_Swap(x0 + i, y0, pData + (i >> 3), ySize, pTrans, BytesPerLine, i);
      }
    #else
      for (i = 0; i < ySize; i++) {
        _DrawBitLine1BPP(x0, i + y0, pData, Diff, xSize, pTrans);
        pData += BytesPerLine;
      }
    #endif
    break;
  #if (LCD_MAX_LOG_COLORS > 2)
    case 2:
      for (i = 0; i < ySize; i++) {
        _DrawBitLine2BPP(x0, i + y0, pData, Diff, xSize, pTrans);
        pData += BytesPerLine;
      }
      break;
  #endif
  #if (LCD_MAX_LOG_COLORS > 4)
    case 4:
      for (i = 0; i < ySize; i++) {
        _DrawBitLine4BPP(x0, i + y0, pData, Diff, xSize, pTrans);
        pData += BytesPerLine;
      }
      break;
  #endif
  #if (LCD_MAX_LOG_COLORS > 16)
    case 8:
      #if (LCD_BITSPERPIXEL == 16) && (LCD_SWAP_XY == 1)
        for (i = 0; i < xSize; i++) {
          _DrawBitLine8BPP_Swap(x0 + i, y0, pData + i, ySize, pTrans, BytesPerLine, i);
        }
      #else
        for (i = 0; i < ySize; i++) {
          _DrawBitLine8BPP(x0, i + y0, pData, xSize, pTrans);
          pData += BytesPerLine;
        }
      #endif
      break;
  #endif
  #if (LCD_BITSPERPIXEL > 8)
    case 16:
      #if (LCD_BITSPERPIXEL == 16) && (LCD_SWAP_XY == 1)
        for (i = Diff; i < xSize; i++) {
          _DrawBitLine16BPP_Swap(x0 + i, y0, (U16 *)(pData + (i << 1)), ySize, BytesPerLine, i);
        }
      #else
        for (i = 0; i < ySize; i++) {
          _DrawBitLine16BPP(x0, i + y0, (const U16 *)pData, xSize);
          pData += BytesPerLine;
        }
      #endif
      break;
  #endif
  #if (LCD_BITSPERPIXEL > 16)
    case 32:
      for (i = 0; i < ySize; i++) {
        _DrawBitLine32BPP(x0, i + y0, (const U32 *)pData, xSize);
        pData += BytesPerLine;
      }
      break;
  #endif
  }
}

/*********************************************************************
*
*       LCD_L0_SetOrg
*/
void LCD_L0_SetOrg(int x, int y) {
  int xPhys, yPhys;
  #ifdef WIN32
    xPhys = x;
    yPhys = y;
  #else
    #if (LCD_SWAP_XY == 0)
      #if   ((LCD_MIRROR_Y == 0) && (LCD_MIRROR_X == 0)) 
        xPhys = x;
        yPhys = y;
      #elif ((LCD_MIRROR_Y == 0) && (LCD_MIRROR_X == 1)) 
        xPhys = _vxSize - _xSize - x;
        yPhys = y;
      #elif ((LCD_MIRROR_Y == 1) && (LCD_MIRROR_X == 0)) 
        xPhys = x;
        yPhys = _vySize - _ySize - y;
      #elif ((LCD_MIRROR_Y == 1) && (LCD_MIRROR_X == 1)) 
        xPhys = _vxSize - _xSize - x;
        yPhys = _vySize - _ySize - y;
      #endif
    #else
      #if   ((LCD_MIRROR_Y == 0) && (LCD_MIRROR_X == 0)) 
        xPhys = y;
        yPhys = x;
      #elif ((LCD_MIRROR_Y == 0) && (LCD_MIRROR_X == 1)) 
        xPhys = _vySize - _ySize - y;
        yPhys = x;
      #elif ((LCD_MIRROR_Y == 1) && (LCD_MIRROR_X == 0)) 
        xPhys = y;
        yPhys = _vxSize - _xSize - x;
      #elif ((LCD_MIRROR_Y == 1) && (LCD_MIRROR_X == 1)) 
        xPhys = _vySize - _ySize - y;
        yPhys = _vxSize - _xSize - x;
      #endif
    #endif
  #endif
  LCD_SET_ORG(xPhys, yPhys);
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
  #if defined(LCD_VRAM_ADR)
    _SetVRAMAddr(LCD_VRAM_ADR);
  #endif
  _SetVSize(LCD_VXSIZE, LCD_VYSIZE);
  _SetSize(LCD_XSIZE, LCD_YSIZE);
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
  case LCD_DEVFUNC_READRECT:
    return (void *)_ReadRect;
  case LCD_DEVFUNC_SET_VRAM_ADDR:
    return (void *)_SetVRAMAddr;
  case LCD_DEVFUNC_SET_VSIZE:
    return (void *)_SetVSize;
  case LCD_DEVFUNC_SET_SIZE:
    return (void *)_SetSize;
  case LCD_DEVFUNC_ISHW:
    return (void *)1;
  }
  return NULL;
}

#else

void LCDLin32168_c(void);
void LCDLin32168_c(void) { } /* avoid empty object files */

#endif /* (LCD_CONTROLLER undefined) */
