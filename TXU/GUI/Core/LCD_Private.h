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
File        : LCD_Private.h
Purpose     : Internals of the LCD level
----------------------------------------------------------------------
*/

#ifndef LCD_Private_H
#define LCD_Private_H

#include "LCD_ConfDefaults.h"            /* Configuration header file */
#include "LCD_Protected.h"
#include "GUI.h"

typedef struct {
  LCD_COLOR * paColor;
  I16         NumEntries;
} LCD_LUT_INFO;

typedef struct {
  tLCDDEV_DrawPixel  * pfDrawPixel;
  tLCDDEV_DrawHLine  * pfDrawHLine;
  tLCDDEV_DrawVLine  * pfDrawVLine;
  tLCDDEV_FillRect   * pfFillRect;
  tLCDDEV_DrawBitmap * pfDrawBitmap;
} LCD_API_LIST;

#if GUI_SUPPORT_CURSOR
  const LCD_API_LIST * LCD_SetAPIList(const LCD_API_LIST * pAPIList);
#endif

tLCDDEV_DrawBitmap * LCD_GetpfDrawBitmap(void);
int                  LCD_PassingBitmapsAllowed(void);

void LCD_EnableCursor(int OnOff);

#if LCD_PHYSCOLORS_IN_RAM
  #if (LCD_FIXEDPALETTE == 0)
    #if (LCD_FIXEDPALETTE == 0)
      extern LCD_COLOR LCD_PhysColors[1 << LCD_BITSPERPIXEL];
    #endif
  #endif
  #if (GUI_NUM_LAYERS > 1)
    #if (LCD_FIXEDPALETTE_1 == 0)
      extern LCD_COLOR LCD_PhysColors_1[1 << LCD_BITSPERPIXEL_1];
    #endif
  #endif
  #if (GUI_NUM_LAYERS > 2)
    #if (LCD_FIXEDPALETTE_2 == 0)
      extern LCD_COLOR LCD_PhysColors_2[1 << LCD_BITSPERPIXEL_2];
    #endif
  #endif
  #if (GUI_NUM_LAYERS > 3)
    #if (LCD_FIXEDPALETTE_3 == 0)
      extern LCD_COLOR LCD_PhysColors_3[1 << LCD_BITSPERPIXEL_3];
    #endif
  #endif
  #if (GUI_NUM_LAYERS > 4)
    #if (LCD_FIXEDPALETTE_4 == 0)
      extern LCD_COLOR LCD_PhysColors_4[1 << LCD_BITSPERPIXEL_4];
    #endif
  #endif
#endif

#if GUI_COMPILER_SUPPORTS_FP

extern const struct tLCDDEV_APIList_struct * /* const */ LCD_aAPI[GUI_NUM_LAYERS];

const tLCDDEV_APIList* LCD_SetAPI      (const tLCDDEV_APIList* pAPI, int Index);
const tLCDDEV_APIList* LCD_SetAPIForAll(const tLCDDEV_APIList* pAPI, int Index);

#endif

#if   (GUI_NUM_LAYERS == 1)
  #if   (LCD_BITSPERPIXEL <=  8)
    #define SIZE_OF_COLORINDEX 8
  #elif (LCD_BITSPERPIXEL <= 16)
    #define SIZE_OF_COLORINDEX 16
  #else
    #define SIZE_OF_COLORINDEX 32
  #endif
#elif (GUI_NUM_LAYERS == 2)
  #if   (LCD_BITSPERPIXEL_0 <=  8) && (LCD_BITSPERPIXEL_1 <=  8)
    #define SIZE_OF_COLORINDEX 8
  #elif (LCD_BITSPERPIXEL_0 <= 16) && (LCD_BITSPERPIXEL_1 <= 16)
    #define SIZE_OF_COLORINDEX 16
  #else
    #define SIZE_OF_COLORINDEX 32
  #endif
#elif (GUI_NUM_LAYERS == 3)
  #if   (LCD_BITSPERPIXEL_0 <=  8) && (LCD_BITSPERPIXEL_1 <=  8) && (LCD_BITSPERPIXEL_2 <=  8)
    #define SIZE_OF_COLORINDEX 8
  #elif (LCD_BITSPERPIXEL_0 <= 16) && (LCD_BITSPERPIXEL_1 <= 16) && (LCD_BITSPERPIXEL_2 <= 16)
    #define SIZE_OF_COLORINDEX 16
  #else
    #define SIZE_OF_COLORINDEX 32
  #endif
#elif (GUI_NUM_LAYERS == 4)
  #if   (LCD_BITSPERPIXEL_0 <=  8) && (LCD_BITSPERPIXEL_1 <=  8) && (LCD_BITSPERPIXEL_2 <=  8) && (LCD_BITSPERPIXEL_3 <=  8)
    #define SIZE_OF_COLORINDEX 8
  #elif (LCD_BITSPERPIXEL_0 <= 16) && (LCD_BITSPERPIXEL_1 <= 16) && (LCD_BITSPERPIXEL_2 <= 16) && (LCD_BITSPERPIXEL_3 <= 16)
    #define SIZE_OF_COLORINDEX 16
  #else
    #define SIZE_OF_COLORINDEX 32
  #endif
#elif (GUI_NUM_LAYERS == 5)
  #if   (LCD_BITSPERPIXEL_0 <=  8) && (LCD_BITSPERPIXEL_1 <=  8) && (LCD_BITSPERPIXEL_2 <=  8) && (LCD_BITSPERPIXEL_3 <=  8) && (LCD_BITSPERPIXEL_4 <=  8)
    #define SIZE_OF_COLORINDEX 8
  #elif (LCD_BITSPERPIXEL_0 <= 16) && (LCD_BITSPERPIXEL_1 <= 16) && (LCD_BITSPERPIXEL_2 <= 16) && (LCD_BITSPERPIXEL_3 <= 16) && (LCD_BITSPERPIXEL_4 <= 16)
    #define SIZE_OF_COLORINDEX 16
  #else
    #define SIZE_OF_COLORINDEX 32
  #endif
#elif (GUI_NUM_LAYERS == 6)
  #if   (LCD_BITSPERPIXEL_0 <=  8) && (LCD_BITSPERPIXEL_1 <=  8) && (LCD_BITSPERPIXEL_2 <=  8) && (LCD_BITSPERPIXEL_3 <=  8) && (LCD_BITSPERPIXEL_4 <=  8) && (LCD_BITSPERPIXEL_5 <=  8)
    #define SIZE_OF_COLORINDEX 8
  #elif (LCD_BITSPERPIXEL_0 <= 16) && (LCD_BITSPERPIXEL_1 <= 16) && (LCD_BITSPERPIXEL_2 <= 16) && (LCD_BITSPERPIXEL_3 <= 16) && (LCD_BITSPERPIXEL_4 <= 16) && (LCD_BITSPERPIXEL_5 <= 16)
    #define SIZE_OF_COLORINDEX 16
  #else
    #define SIZE_OF_COLORINDEX 32
  #endif
#endif

#if (SIZE_OF_COLORINDEX == 8)
  #define LCD_BKCOLORINDEX GUI_Context.LCD.aColorIndex8[0]
  #define LCD_COLORINDEX   GUI_Context.LCD.aColorIndex8[1]
  #define LCD_ACOLORINDEX  GUI_Context.LCD.aColorIndex8
#elif (SIZE_OF_COLORINDEX == 16)
  #define LCD_BKCOLORINDEX GUI_Context.LCD.aColorIndex16[0]
  #define LCD_COLORINDEX   GUI_Context.LCD.aColorIndex16[1]
  #define LCD_ACOLORINDEX  GUI_Context.LCD.aColorIndex16
#elif (SIZE_OF_COLORINDEX == 32)
  #define LCD_BKCOLORINDEX GUI_Context.LCD.aColorIndex32[0]
  #define LCD_COLORINDEX   GUI_Context.LCD.aColorIndex32[1]
  #define LCD_ACOLORINDEX  GUI_Context.LCD.aColorIndex32
#endif

extern LCD_PIXELINDEX LCD__aConvTable[LCD_MAX_LOG_COLORS];
void LCD_DrawBitmap   (int x0, int y0,
                       int xsize, int ysize,
                       int xMul, int yMul,
                       int BitsPerPixel,
                       int BytesPerLine,
                       const U8 GUI_UNI_PTR * pPixel,
                       const LCD_PIXELINDEX* pTrans);
void LCD_UpdateColorIndices(void);

#if GUI_SUPPORT_DEVICES
  void LCD_ReadRect  (int x0, int y0, int x1, int y1, LCD_PIXELINDEX * pBuffer, const tLCDDEV_APIList * pAPI);
  void LCD_ReadRectEx(int x0, int y0, int x1, int y1, LCD_PIXELINDEX * pBuffer, void * (* pfGetDevFunc)(int Index), unsigned (* pfGetPixelIndex)(int x, int y));
#endif

/*********************************************************************
*
*          Support for Segment/COMLUTs
*
**********************************************************************
*/

#define LCD_TYPE_SEGTRANS U16
#define LCD_TYPE_COMTRANS U16

#ifdef LCD_LUT_COM
  #ifdef LCDCOLOR_C
    LCD_TYPE_COMTRANS LCD__aLine2Com0[LCD_YSIZE] = { LCD_LUT_COM };
  #else
    extern LCD_TYPE_COMTRANS LCD__aLine2Com0[LCD_YSIZE];
  #endif
#endif

#ifdef LCD_LUT_SEG
  #ifdef LCDCOLOR_C
    LCD_TYPE_SEGTRANS LCD__aCol2Seg0[LCD_XSIZE] = { LCD_LUT_SEG };
  #else
    extern LCD_TYPE_COMTRANS LCD__aCol2Seg0[LCD_XSIZE];
  #endif
#endif

/*********************************************************************
*
*       Support for multiple display controllers
*
**********************************************************************
*/
#define DECLARE_PROTOTYPES(DISTX) \
  void     LCD_##DISTX##_SetPixelIndex(int x, int y, int PixelIndex); \
  unsigned LCD_##DISTX##_GetPixelIndex(int x, int y); \
  void     LCD_##DISTX##_XorPixel     (int x, int y); \
  void     LCD_##DISTX##_DrawHLine    (int x0, int y,  int x1); \
  void     LCD_##DISTX##_DrawVLine    (int x, int y0,  int y1); \
  void     LCD_##DISTX##_FillRect     (int x0, int y0, int x1, int y1); \
  void     LCD_##DISTX##_DrawBitmap   (int x0, int y0, int xsize, int ysize, int BitsPerPixel, int BytesPerLine,  const U8 GUI_UNI_PTR * pData, int Diff, const LCD_PIXELINDEX * pTrans); \
  void     LCD_##DISTX##_SetOrg       (int x, int y); \
  void     LCD_##DISTX##_On           (void); \
  void     LCD_##DISTX##_Off          (void); \
  int      LCD_##DISTX##_Init         (void); \
  void     LCD_##DISTX##_SetLUTEntry  (U8 Pos, LCD_COLOR Color); \
  void   * LCD_##DISTX##_GetDevFunc   (int Index); \
  void     LCD_##DISTX##_ReInit       (void)
    
DECLARE_PROTOTYPES(DIST0);
DECLARE_PROTOTYPES(DIST1);
DECLARE_PROTOTYPES(DIST2);
DECLARE_PROTOTYPES(DIST3);

#endif /* Avoid multiple inclusion */


/*************************** End of file ****************************/


