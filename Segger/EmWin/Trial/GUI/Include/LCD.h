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
File        : LCD.h
Purpose     : Declares LCD interface functions
----------------------------------------------------------------------
*/

#ifndef LCD_H
#define LCD_H

#include "GUI_ConfDefaults.h" /* Used for GUI_UNI_PTR */
#include "Global.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Basic type defines
*
* The follwing are defines for types used in the LCD-driver and the
* GUI layers on top of that. Since "C" does not provide data types of
* fixed length which are identical on all platforms, this is done here.
* For most 16/32 controllers, the settings will work fine. However, if
* you have similar defines in other sections of your program, you might
* want to change or relocate these defines, e.g. in a TYPE.h file.
*/
#define I16P I16              /*   signed 16 bits OR MORE ! */
#define U16P U16              /* unsigned 16 bits OR MORE ! */

/*********************************************************************
*
*       Settings for windows simulation
*
* Some settings in the configuration may conflict with the values required
* in the Simulation. This is why we ignore the target settings for data
* types and use the correct settings for the simulation.
* (U32 could be defined as long, which would yield a 64 bit type on
* the PC)
*/
#ifdef WIN32
  #pragma warning( disable : 4244 )  // Disable warning messages in simulation
  #pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
#endif                                      

/*********************************************************************
*
*       Constants
*/
#define LCD_ERR0 (0x10)
#define LCD_ERR_CONTROLLER_NOT_FOUND (LCD_ERR0+1)
#define LCD_ERR_MEMORY               (LCD_ERR0+2)

/*********************************************************************
*
*       Drawing modes
*/
#define LCD_DRAWMODE_NORMAL (0)
#define LCD_DRAWMODE_XOR    (1<<0)
#define LCD_DRAWMODE_TRANS  (1<<1)
#define LCD_DRAWMODE_REV    (1<<2)

/*********************************************************************
*
*       Typedefs
*/
typedef int LCD_DRAWMODE;
typedef U32 LCD_COLOR;
 
/*********************************************************************
*
*       Data structures
*/
typedef struct { I16P x,y; } GUI_POINT;
typedef struct { I16 x0,y0,x1,y1; } LCD_RECT;

typedef struct {
  int              NumEntries; 
  char             HasTrans;         
  const LCD_COLOR GUI_UNI_PTR * pPalEntries; 
} LCD_LOGPALETTE; 

/* This is used for the simulation only ! */
typedef struct {
  int x,y;
  unsigned char KeyStat;
} LCD_tMouseState;

/*********************************************************************
*
*       LCD_L0_... color conversion
*/
typedef LCD_COLOR      tLCDDEV_Index2Color  (int Index);
typedef unsigned int   tLCDDEV_Color2Index  (LCD_COLOR Color);
typedef unsigned int   tLCDDEV_GetIndexMask (void);

#define DECLARE_L0_COLOR_CONVERSION(x) \
unsigned  LCD_L0##x##Color2Index (LCD_COLOR Color); \
LCD_COLOR LCD_L0##x##Index2Color (int Index);       \
unsigned  LCD_L0##x##GetIndexMask(void)

DECLARE_L0_COLOR_CONVERSION(_);
DECLARE_L0_COLOR_CONVERSION(_1_);
DECLARE_L0_COLOR_CONVERSION(_2_);
DECLARE_L0_COLOR_CONVERSION(_3_);
DECLARE_L0_COLOR_CONVERSION(_4_);
DECLARE_L0_COLOR_CONVERSION(_5_);

/*********************************************************************
*
*       Color conversion API tables
*/
typedef struct {
  tLCDDEV_Color2Index*  pfColor2Index;
  tLCDDEV_Index2Color*  pfIndex2Color;
  tLCDDEV_GetIndexMask* pfGetIndexMask;
} LCD_API_COLOR_CONV;

extern const LCD_API_COLOR_CONV LCD_API_ColorConv_1;
extern const LCD_API_COLOR_CONV LCD_API_ColorConv_2;
extern const LCD_API_COLOR_CONV LCD_API_ColorConv_4;
extern const LCD_API_COLOR_CONV LCD_API_ColorConv_8666;
extern const LCD_API_COLOR_CONV LCD_API_ColorConv_888;
extern const LCD_API_COLOR_CONV LCD_API_ColorConv_8888;
extern const LCD_API_COLOR_CONV LCD_API_ColorConv_565;
extern const LCD_API_COLOR_CONV LCD_API_ColorConv_M565;

#define GUI_COLOR_CONV_1    &LCD_API_ColorConv_1
#define GUI_COLOR_CONV_2    &LCD_API_ColorConv_2
#define GUI_COLOR_CONV_4    &LCD_API_ColorConv_4
#define GUI_COLOR_CONV_8666 &LCD_API_ColorConv_8666
#define GUI_COLOR_CONV_888  &LCD_API_ColorConv_888
#define GUI_COLOR_CONV_8888 &LCD_API_ColorConv_8888
#define GUI_COLOR_CONV_565  &LCD_API_ColorConv_565
#define GUI_COLOR_CONV_M565 &LCD_API_ColorConv_M565

/*********************************************************************
*
*       LCDDEV function table
*
*  Below the routines which need to in an LCDDEV routine table are
*  defined. All of these routines have to be in the low-level driver
*  (LCD_L0) or in the memory device which can be used to replace the
*  driver.
*  The one exception to this is the SetClipRect routine, which would
*  be identical for all drivers and is therefor contained in the
*  level above (LCD).
*/
typedef void         tLCDDEV_DrawPixel    (int x, int y);
typedef void         tLCDDEV_DrawHLine    (int x0, int y0,  int x1);
typedef void         tLCDDEV_DrawVLine    (int x , int y0,  int y1);
typedef void         tLCDDEV_FillRect     (int x0, int y0, int x1, int y1);
typedef unsigned int tLCDDEV_GetPixelIndex(int x, int y);
typedef void         tLCDDEV_SetPixelIndex(int x, int y, int ColorIndex);
typedef void         tLCDDEV_XorPixel     (int x, int y);
typedef void         tLCDDEV_FillPolygon  (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
typedef void         tLCDDEV_FillPolygonAA(const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
typedef void         tLCDDEV_GetRect      (LCD_RECT*pRect);
typedef int          tLCDDEV_Init         (void);
typedef void         tLCDDEV_On           (void);
typedef void         tLCDDEV_Off          (void);
typedef void         tLCDDEV_SetLUTEntry  (U8 Pos, LCD_COLOR color);
typedef void *       tLCDDEV_GetDevFunc   (int Index);
typedef I32          tLCDDEV_GetDevProp   (int Index);
typedef void         tLCDDEV_SetOrg       (int x, int y);

/*********************************************************************
*
*       Memory device API tables
*/
typedef struct tLCDDEV_APIList_struct tLCDDEV_APIList;

typedef void tLCDDEV_DrawBitmap   (int x0, int y0, int xsize, int ysize,
                       int BitsPerPixel, int BytesPerLine,
                       const U8 GUI_UNI_PTR * pData, int Diff,
                       const void* pTrans);   /* Really LCD_PIXELINDEX, but is void to avoid compiler warnings*/

struct tLCDDEV_APIList_struct {
  tLCDDEV_Color2Index*        pfColor2Index;
  tLCDDEV_Index2Color*        pfIndex2Color;
  tLCDDEV_GetIndexMask*       pfGetIndexMask;
  tLCDDEV_DrawBitmap*         pfDrawBitmap;
  tLCDDEV_DrawHLine*          pfDrawHLine;
  tLCDDEV_DrawVLine*          pfDrawVLine;
  tLCDDEV_FillRect*           pfFillRect;
  tLCDDEV_GetPixelIndex*      pfGetPixelIndex;
  tLCDDEV_GetRect*            pfGetRect;
  tLCDDEV_SetPixelIndex*      pfSetPixelIndex;
  tLCDDEV_XorPixel*           pfXorPixel;
  tLCDDEV_SetLUTEntry*        pfSetLUTEntry;
  tLCDDEV_GetDevFunc*         pfGetDevFunc;
  tLCDDEV_GetDevProp*         pfGetDevProp;
  #if GUI_SUPPORT_MEMDEV
    tLCDDEV_FillPolygon*      pfFillPolygon;
    tLCDDEV_FillPolygonAA*    pfFillPolygonAA;
    const tLCDDEV_APIList*    pMemDevAPI;
    unsigned                  BitsPerPixel;
  #endif
};

extern const tLCDDEV_APIList LCD_L0_APIList;
extern const tLCDDEV_APIList LCD_L0_1_APIList;
extern const tLCDDEV_APIList LCD_L0_2_APIList;
extern const tLCDDEV_APIList LCD_L0_3_APIList;
extern const tLCDDEV_APIList LCD_L0_4_APIList;
extern const tLCDDEV_APIList LCD_L0_5_APIList;

extern const struct tLCDDEV_APIList_struct GUI_MEMDEV__APIList1;
extern const struct tLCDDEV_APIList_struct GUI_MEMDEV__APIList8;
extern const struct tLCDDEV_APIList_struct GUI_MEMDEV__APIList16;
extern const struct tLCDDEV_APIList_struct GUI_MEMDEV__APIList32;

#define GUI_MEMDEV_APILIST_1  &GUI_MEMDEV__APIList1
#define GUI_MEMDEV_APILIST_8  &GUI_MEMDEV__APIList8
#define GUI_MEMDEV_APILIST_16 &GUI_MEMDEV__APIList16
#define GUI_MEMDEV_APILIST_32 &GUI_MEMDEV__APIList32

/*********************************************************************
*
*       Defines for device capabilities
*
* The following is the list of device capabilities which can, but do
* not have to be implemented in the driver. This way the driver can be
* enhanced in the future without affecting the driver interface,
* keeping older drivers compatible.
* More DevCaps can always be added in the future, as older drivers
* are guaranteed to return 0 for all unimplemented features or queries.
*
* The values below define the legal parameters to the LCD_GetDeviceCaps
* and the LCD_GetpCapFunc routines.
*/

#define LCD_DEVCAP_NUMCOLORS         0x0     /* Quest number of colors
                                                which LCD can display */
#define LCD_DEVCAP_XSIZE             0x01    /* Quest horiz. res. of display */
#define LCD_DEVCAP_YSIZE             0x02    /* Quest vert. res. of display */
#define LCD_DEVCAP_VXSIZE            0x03    /* Quest vert. res. of virtual disp.*/
#define LCD_DEVCAP_VYSIZE            0x04    /* Quest vert. res. of virtual disp.*/
#define LCD_DEVCAP_XORG              0x05    /* X-origin ... usually 0 */
#define LCD_DEVCAP_YORG              0x06    /* Y-origin ... usually 0 */
#define LCD_DEVCAP_CONTROLLER        0x07    /* LCD Controller (Numerical) */
#define LCD_DEVCAP_BITSPERPIXEL      0x08    /* Bits per pixel ... 1/2/4/8 */
#define LCD_DEVCAP_NUM_COLORS        0x09    /* Quest number of colors */
#define LCD_DEVCAP_XMAG              0x0A
#define LCD_DEVCAP_YMAG              0x0B
#define LCD_DEVCAP_FIXEDPALETTE      0x0C
#define LCD_DEVCAP_MIRROR_X          0x0D
#define LCD_DEVCAP_MIRROR_Y          0x0E
#define LCD_DEVCAP_SWAP_XY           0x0F
#define LCD_DEVCAP_SWAP_RB           0x10
#define LCD_DEVCAP_PHYSCOLORS_IN_RAM 0x11
#define LCD_DEVCAP_REVERSE_LUT       0x12

#define LCD_DEVCAP_COLOR        0x1000  /* Quest Color[0]
                                0x1001     Quest Color[1]
                                0x1002     Quest Color[2]
                                         ...                    */
 /* The next 4095 entries are reserved so up to 4096 colors
    can be queried          ...*/

int LCD_GetXSizeMax(void);
int LCD_GetYSizeMax(void);
int LCD_GetVXSizeMax(void);
int LCD_GetVYSizeMax(void);
int LCD_GetBitsPerPixelMax(void);

int LCD_GetXSize       (void);
int LCD_GetYSize       (void);
int LCD_GetVXSize      (void);
int LCD_GetVYSize      (void);
U32 LCD_GetNumColors   (void);
int LCD_GetBitsPerPixel(void);
int LCD_GetFixedPalette(void);
int LCD_GetXMag        (void);
int LCD_GetYMag        (void);

int LCD_GetXSizeEx          (int LayerIndex);
int LCD_GetYSizeEx          (int LayerIndex);
int LCD_GetVXSizeEx         (int LayerIndex);
int LCD_GetVYSizeEx         (int LayerIndex);
U32 LCD_GetNumColorsEx      (int LayerIndex);
int LCD_GetBitsPerPixelEx   (int LayerIndex);
I32 LCD_GetFixedPaletteEx   (int LayerIndex);
int LCD_GetXMagEx           (int LayerIndex);
int LCD_GetYMagEx           (int LayerIndex);
int LCD_GetMirrorXEx        (int LayerIndex);
int LCD_GetMirrorYEx        (int LayerIndex);
int LCD_GetSwapXYEx         (int LayerIndex);
int LCD_GetSwapRBEx         (int LayerIndex);
int LCD_GetDeltaModeEx      (int LayerIndex);
int LCD_GetBitsPerPixel_L0Ex(int LayerIndex);
int LCD_GetReversLUTEx      (int LayerIndex);
int LCD_GetPhysColorsInRAMEx(int LayerIndex);

tLCDDEV_Index2Color * LCD_GetpfIndex2ColorEx(int LayerIndex);
tLCDDEV_Color2Index * LCD_GetpfColor2IndexEx(int LayerIndex);

tLCDDEV_Color2Index * LCD_GetpfColor2Index(void);

int LCD_GetNumLayers(void);

#define LCD_GetNumDisplays() LCD_GetNumLayers()

#define LCD_GET_XSIZE()        LCD_GetXSize()
#define LCD_GET_YSIZE()        LCD_GetYSize()
#define LCD_GET_VXSIZE()       LCD_GetVXSize()
#define LCD_GET_VYSIZE()       LCD_GetVYSize()
#define LCD_GET_NUMCOLORS()    LCD_GetNumColors()
#define LCD_GET_BITSPERPIXEL() LCD_GetBitsPerPixel()

#define LCD_DEVFUNC_READRECT      0x01 /* Request of a function pointer for reading a rectangular display area */
#define LCD_DEVFUNC_SETALPHA      0x02 /* Request of a function pointer for setting the alpha blending factor */
#define LCD_DEVFUNC_SETPOS        0x03 /* Request of a function pointer for setting the layer position */
#define LCD_DEVFUNC_SETSIZE       0x04 /* Request of a function pointer for setting the layer size */
#define LCD_DEVFUNC_SETVIS        0x05 /* Request of a function pointer for setting the visibility of a layer */
#define LCD_DEVFUNC_ISHW          0x06 /* Request if the current selected device is a display driver */
#define LCD_DEVFUNC_24BPP         0x07 /* Request if the driver is able to draw a 24bpp bitmap */
#define LCD_DEVFUNC_NEXT_PIXEL    0x08 /* Request if the driver is able to draw a bitmap pixel by pixel */
#define LCD_DEVFUNC_SET_VRAM_ADDR 0x09 /* Request of a function pointer for setting the VRAM address */
#define LCD_DEVFUNC_SET_VSIZE     0x0A /* Request of a function pointer for setting the VRAM size */
#define LCD_DEVFUNC_SET_SIZE      0x0B /* Request of a function pointer for setting the display size */

/*********************************************************************
*
*       Set display properties
*/
int LCD_SetAlphaEx   (int Alpha, int LayerIndex);
int LCD_SetVRAMAddrEx(U32 Addr, int LayerIndex);
int LCD_SetVSizeEx   (int xSize, int ySize, int LayerIndex);
int LCD_SetSizeEx    (int xSize, int ySize, int LayerIndex);

/*********************************************************************
*
*       NEXT_PIXEL API support
*/
typedef struct {
  void (* pfStart)   (int x0, int y0, int x1, int y1);
  void (* pfSetPixel)(int PixelIndex);
  void (* pfNextLine)(void);
  void (* pfEnd)     (void);
} LCD_API_NEXT_PIXEL;

LCD_API_NEXT_PIXEL * LCD_GetNextPixelAPI(void);

/*********************************************************************
*
*      LCD_CLIP function table
*/
typedef void         tLCD_HL_DrawHLine    (int x0, int y0,  int x1);
typedef void         tLCD_HL_DrawPixel    (int x0, int y0);

typedef struct {
  tLCD_HL_DrawHLine*          pfDrawHLine;
  tLCD_HL_DrawPixel*          pfDrawPixel;
} tLCD_HL_APIList;

void LCD_DrawHLine(int x0, int y0,  int x1);
void LCD_DrawPixel(int x0, int y0);
void LCD_DrawVLine  (int x, int y0,  int y1);


/*********************************************************************
*
*       Declarations for LCD_
*/
void LCD_SetClipRectEx(const LCD_RECT* pRect);
void LCD_SetClipRectMax(void);

/* Get device capabilities (0 if not supported) */
I32  LCD_GetDevCap(int Index);

/* Initialize LCD using config-paramters */
int LCD_Init(void);

void LCD_SetBkColor   (LCD_COLOR Color); /* Set background color */
void LCD_SetColor     (LCD_COLOR Color); /* Set foreground color */
void LCD_SetPixelIndex(int x, int y, int ColorIndex);

/* Palette routines (Not available on all drivers) */
void LCD_InitLUT(void);
void LCD_SetLUTEntryEx(U8 Pos, LCD_COLOR Color, unsigned int LayerIndex);

/* Decompressors */
//typedef void tfDrawSpecialBitmap(int x0,int y0,int xsize, int ysize, const U8 GUI_UNI_PTR *pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, int xMag, int yMag);
void         LCD_DrawBitmap_RLE8(int x0,int y0,int xsize, int ysize, const U8 GUI_UNI_PTR *pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, int xMag, int yMag);
void         LCD_DrawBitmap_RLE4(int x0,int y0,int xsize, int ysize, const U8 GUI_UNI_PTR *pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, int xMag, int yMag);
void         LCD_DrawBitmap_565 (int x0,int y0,int xsize, int ysize, const U8 GUI_UNI_PTR *pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, int xMag, int yMag);
void         LCD_DrawBitmap_M565(int x0,int y0,int xsize, int ysize, const U8 GUI_UNI_PTR *pPixel, const LCD_LOGPALETTE GUI_UNI_PTR * pLogPal, int xMag, int yMag);

LCD_DRAWMODE LCD_SetDrawMode  (LCD_DRAWMODE dm);
void LCD_SetColorIndex(unsigned PixelIndex);
void LCD_SetBkColorIndex(unsigned PixelIndex);
void LCD_FillRect(int x0, int y0, int x1, int y1);
typedef void tLCD_SetPixelAA(int x, int y, U8 Intens);

void LCD_SetPixelAA        (int x, int y, U8 Intens);
void LCD_SetPixelAA_NoTrans(int x, int y, U8 Intens);
void LCD_SetPixelAA_Xor    (int x, int y, U8 Intens);

LCD_COLOR    LCD_AA_MixColors(LCD_COLOR Color, LCD_COLOR BkColor, U8 Intens);
LCD_COLOR    LCD_MixColors256(LCD_COLOR Color, LCD_COLOR BkColor, unsigned Intens);
LCD_COLOR    LCD_GetPixelColor(int x, int y);     /* Get RGB color of pixel */
unsigned int LCD_GetPixelIndex(int x, int y);
int          LCD_GetBkColorIndex (void);
int          LCD_GetColorIndex (void);

/*********************************************************************
*
*       Optional support for rotatation
*/
#if GUI_SUPPORT_ROTATION

typedef void tLCD_DrawBitmap(int x0, int y0, int xsize, int ysize,
                             int xMul, int yMul, int BitsPerPixel, int BytesPerLine,
                             const U8 GUI_UNI_PTR * pPixel, const void * pTrans);
typedef void tRect2TextRect (LCD_RECT * pRect);

struct tLCD_APIList_struct {
  tLCD_DrawBitmap   * pfDrawBitmap;
  tRect2TextRect    * pfRect2TextRect;
};

typedef struct tLCD_APIList_struct tLCD_APIList;

extern tLCD_APIList LCD_APIListCCW;
extern tLCD_APIList LCD_APIListCW;
extern tLCD_APIList LCD_APIList180;

#define GUI_ROTATION   tLCD_APIList
#define GUI_ROTATE_CCW &LCD_APIListCCW
#define GUI_ROTATE_CW  &LCD_APIListCW
#define GUI_ROTATE_180 &LCD_APIList180
#define GUI_ROTATE_0   0
#endif

/*********************************************************************
*
*       LCD  publics not used by GUI
*/
#define LCD_On          LCD_L0_On
#define LCD_Off         LCD_L0_Off
#define LCD_ReInit      LCD_L0_ReInit
#define LCD_SetLUTEntry LCD_L0_SetLUTEntry

/*********************************************************************
*
*       Physical color access, internally used only
*/
void LCD__SetPhysColor(U8 Pos, LCD_COLOR Color);

#define LCD_CC_UNLOCK (0)    /* Default mode: Cache is transparent */
#define LCD_CC_LOCK   (1)    /* Cache is locked, no write operations */
#define LCD_CC_FLUSH  (2)    /* Flush cache, do not change mode */

#define DECLARE_LCD_L0_CONTROLCACHE(x) U8 LCD_L0##x##ControlCache(U8 mode);
DECLARE_LCD_L0_CONTROLCACHE(_)
DECLARE_LCD_L0_CONTROLCACHE(_1_)
DECLARE_LCD_L0_CONTROLCACHE(_2_)
DECLARE_LCD_L0_CONTROLCACHE(_3_)
DECLARE_LCD_L0_CONTROLCACHE(_4_)
DECLARE_LCD_L0_CONTROLCACHE(_5_)

#define DECLARE_LCD_L0_REFRESH(x) void LCD_L0##x##Refresh(void);
DECLARE_LCD_L0_REFRESH(_)
DECLARE_LCD_L0_REFRESH(_1_)
DECLARE_LCD_L0_REFRESH(_2_)
DECLARE_LCD_L0_REFRESH(_3_)
DECLARE_LCD_L0_REFRESH(_4_)
DECLARE_LCD_L0_REFRESH(_5_)

#define LCD_ControlCache LCD_L0_ControlCache

/*********************************************************************
*
*       Support for paging (obsolete)
*/
int LCD_SelPage  (int NewPage);    /* returns formerly sel. page */
int LCD_ShowPage (int NewPage);    /* sets / returns visible page */
int LCD_GetSelPage (void);         /* returns selected page */
int LCD_GetVisPage (void);         /* returns visible page */


/*********************************************************************
*
*       Color conversion
*/
unsigned         LCD_Color2Index     (LCD_COLOR Color);
LCD_COLOR        LCD_Index2Color     (int Index);
LCD_COLOR        LCD_Index2ColorEx   (int i, unsigned LayerIndex);

/*********************************************************************
*
*       LCD_X_...
*/
void LCD_X_InitController(unsigned LayerIndex); /* Callback function called from LCD_L0_Init() */

void LCD_X_Init(void);
void LCD_X_On  (void);
void LCD_X_Off (void);

char LCD_X_Read00(void);
char LCD_X_Read01(void);
void LCD_X_Write00(char c);
void LCD_X_Write01(char c);
void LCD_X_WriteM01(char * pData, int NumBytes);

#if defined(__cplusplus)
  }
#endif

#endif /* LCD_H */

/*************************** End of file ****************************/
