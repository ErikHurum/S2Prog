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
File        : LCDConf.c
Purpose     : Display controller initialization
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "LCDConf.h"

/*********************************************************************
*
*       SFR register definitions
*
**********************************************************************
*/
/* RESET, CLOCK AND POWER CONTROLLER */
#define __RCPCBASE  0xFFFE2000
#define __PERIPHCLKCTRL1    *(volatile U32*)(__RCPCBASE + 0x0028)
#define __AHBCLKCTRL        *(volatile U32*)(__RCPCBASE + 0x002C)
#define __LCDCLKPRESCALE	  *(volatile U32*)(__RCPCBASE + 0x0040)

/* COLOR LCD CONTROLLER */
#define __CLCDCBASE  0xFFFF4000
#define __LCDTIMING0        *(volatile U32*)(__CLCDCBASE + 0x0000)
#define __LCDTIMING1        *(volatile U32*)(__CLCDCBASE + 0x0004)
#define __LCDTIMING2        *(volatile U32*)(__CLCDCBASE + 0x0008)
#define __LCDUPBASE         *(volatile U32*)(__CLCDCBASE + 0x0010)
#define __LCDLPBASE	        *(volatile U32*)(__CLCDCBASE + 0x0014)
#define __LCDINTRENABLE     *(volatile U32*)(__CLCDCBASE + 0x0018)
#define __LCDCONTROL        *(volatile U32*)(__CLCDCBASE + 0x001C)
#define __LCDSTATUS	        *(volatile U32*)(__CLCDCBASE + 0x0020)
#define __LCDINTERRUPT      *(volatile U32*)(__CLCDCBASE + 0x0024)
#define __LCDPALLETTE       *(volatile U32*)(__CLCDCBASE + 0x0200)

/* HR-TFT LCD TIMING CONTROLLER */
#define __HRTFTCBASE  0xFFFE4000
#define __HRTFTCSETUP       *(volatile U32*)(__HRTFTCBASE + 0x0000)
#define __HRTFTCCONTROL     *(volatile U32*)(__HRTFTCBASE + 0x0004)
#define __HRTFTCTIMING1     *(volatile U32*)(__HRTFTCBASE + 0x0008)
#define __HRTFTCTIMING2     *(volatile U32*)(__HRTFTCBASE + 0x000C)

/* INPUT/OUTPUT CONTROL */
#define __IOCONBASE  0xFFFE5000
#define __MUXCTL1             *(volatile U32*)(__IOCONBASE + 0x0000)
#define __MUXCTL19            *(volatile U32*)(__IOCONBASE + 0x0090)
#define __MUXCTL20            *(volatile U32*)(__IOCONBASE + 0x0098)
#define __MUXCTL21            *(volatile U32*)(__IOCONBASE + 0x00A0)
#define __MUXCTL22            *(volatile U32*)(__IOCONBASE + 0x00A8)

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_InitController
*
* Purpose:
*   Initializes the display controller
*/
void LCD_X_InitController(unsigned LayerIndex) {
  GUI_USE_PARA(LayerIndex);
  __AHBCLKCTRL       = 0x00000000;
  __PERIPHCLKCTRL1   &= ~(  1 << 0);                  /* Enable clock for LCD Controller */
  __LCDCLKPRESCALE   = 0x00000001;                    /* LCD clock prescaler /2 */
  __MUXCTL1          |=  (  1 <<  2)                  /* PL1 = LCDVDD15 */
                     |   (  1 <<  0);                 /* PL0 = LCDVDD14 */
  __MUXCTL19         |=  (  2 << 12)                  /* PE6 = LCDMOD */
                     |   (  1 <<  8)                  /* PE5 = LCDVDDEN */
                     |   (  2 <<  4)                  /* PE4 = LCDREV */
                     |   (  1 <<  2);                 /* PE3 = LCDCLS */
  __MUXCTL20         |=  (  1 << 10)                  /* PE1 = LCDDCLK */
                     |   (  2 <<  6)                  /* PE0 = LCDHRLP */
                     |   (  2 <<  2)                  /* PF7 = LCDSPS */
                     |   (  2 <<  0);                 /* PF6 = LCDSPL */
  __MUXCTL21         |=  (  1 << 10)                  /* PF5 = LCDVDD11 */
                     |   (  1 <<  8)                  /* PL3 = LCDVDD13 */
                     |   (  1 <<  6)                  /* PF4 = LCDVDD10 */
                     |   (  1 <<  4)                  /* PL2 = LCDVDD12 */
                     |   (  1 <<  2)                  /* PF3 = LCDVDD9 */
                     |   (  1 <<  0);                 /* PF2 = LCDVDD8 */
  __MUXCTL22         |=  (  1 << 14)                  /* PF1 = LCDVDD7 */
                     |   (  1 << 12)                  /* PF0 = LCDVDD6 */
                     |   (  1 << 10)                  /* PG7 = LCDVDD5 */
                     |   (  1 <<  8)                  /* PG6 = LCDVDD4 */
                     |   (  1 <<  6)                  /* PG5 = LCDVDD3 */
                     |   (  1 <<  4)                  /* PG4 = LCDVDD2 */
                     |   (  1 <<  2)                  /* PG3 = LCDVDD1 */
                     |   (  1 <<  0);                 /* PG2 = LCDVDD0 */
  __LCDTIMING0       =   ( 20 << 24)                  /* Horizontal back  porch */
                     |   ( 20 << 16)                  /* Horizontal front porch */
                     |   ( 60 <<  8)                  /* Horizontal synchronization pulse Width */
                     |   ((LCD_XSIZE / 16 - 1) << 2); /* Pixels-Per-Line */
  __LCDTIMING1       =   (  7 << 24)                  /* Vertical back  porch */
                     |   (  5 << 16)                  /* Vertical front porch */
                     |   (  0 << 10)                  /* Vertical synchronization Pulse Width. */
                     |   (LCD_YSIZE - 1);             /* Lines-Per-Panel */
  __LCDTIMING2       =   (  0 << 27)                  /* Panel Clock Divisor (upper five bits) */
                     |   (  0 << 26)                  /* Bypass pixel Clock Divider */
                     |   ((LCD_XSIZE - 1) << 16)      /* Clocks per line */
                     |   (  0 << 14)                  /* Invert Output Enable */
                     |   (  1 << 13)                  /* Invert Panel Clock */
                     |   (  1 << 12)                  /* Invert Horizontal Synchronization */
                     |   (  0 << 11)                  /* Invert the Vertical Synchronization signal */
                     |   (  0 <<  6)                  /* AC Bias signal (LCDENAB) frequency */
                     |   (  0 <<  0);                 /* Panel Clock Divisor.*/
  __LCDUPBASE        = LCD_VRAM_ADR;                  /* LCD Upper Panel Base address */
  __LCDINTRENABLE    = 0x00000000;                    /* Interrupt Enable Register */
  __LCDCONTROL       =   (  0 << 16)                  /* LCD DMA FIFO Watermark level */
                     |   (  0 << 12)                  /* LCD Vertical Compare */
                     |   (  1 << 11)                  /* LCD Power Enable */
                     |   (  0 << 10)                  /* Big-Endian Pixel Ordering within a byte */
                     |   (  0 <<  9)                  /* Big-Endian Byte Ordering to the LCD */
                     |   (  0 <<  8)                  /* RGB or BGR format selection:
                                                         1 = BGR red and blue swapped
                                                         0 = RGB normal output*/
                     |   (  0 <<  7)                  /* RLCD is a Dual panel STN */
                     |   (  0 <<  6)                  /* LCD 8bit Mono (8bit interface)*/
                     |   (  1 <<  5)                  /* LCD is a TFT */
                     |   (  0 <<  4)                  /* LCD is STN mono */
                     |   (  3 <<  1)                  /* LCD bpp 4 = 16bpp
                                                                 3 =  8bpp
                                                                 2 =  4bpp
                                                                 1 =  2bpp */
                     |   (  1 <<  0);                 /* 0 =  Enable LCD Controller */
  __HRTFTCSETUP      =   ((LCD_XSIZE - 1 ) << 4)      /* Number of pixels per line */
                     |   (  6 << 1)                   /* Conversion mode select (HF-TFT panels) */
                     |   (  1 << 0);                  /* Conversion mode select (HF-TFT panels) */
  __HRTFTCTIMING1    =   (  8 << 8)                   /* Delay in LCDDCLK periods from the 1st LOW
                                                      in the LCDLP signal, to the leading edge
                                                      of the LCDPS and LCD-CLS signals */
                     |   (  7 << 4)                   /* Polarity-Reversal delay */
                     |   ( 12 << 0);                  /* Delay in LCDDCLK periods from the 1st LOW
                                                       in the LCDLP signal, to the leading edge
                                                       of the LCDLP signal */
  __HRTFTCTIMING2    =   ( 83 << 9)                   /* Delay in LCDDCLK periods of the LCD-SPL signal
                                                       during vertical front and back porches. */
                     |   (208 << 0);                  /* Delay in LCDDCLK periods from the first
                                                       rising edge of the LCDSPL signal to the
                                                       trailing edge of the LCDCLS signal */
  __HRTFTCCONTROL    =   (  1 << 1)                   /* LCDCLS enable  */
                     |   (  1 << 0);                  /* LCDSPS enable */
}

/*********************************************************************
*
*       LCD_X_SetLUTEntry
*
* Purpose:
*   Sets one LUT entry
*/
void LCD_X_SetLUTEntry(int Pos, U32 Color) {
  volatile U32 * pPalette;
  U32 Index;
  pPalette = (volatile U32 *)(__CLCDCBASE + 0x0200) + (Pos >> 1);
  Index    = LCD_Color2Index_555(Color);
  if (Pos & 1) {
    *pPalette &= 0x0000FFFF;
    *pPalette |= Index << 16;
  } else {
    *pPalette &= 0xFFFF0000;
    *pPalette |= Index;
  }
}

/*************************** End of file ****************************/

