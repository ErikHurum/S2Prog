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
#define __PERIPHCLKCTRL     *(volatile U32*)(__RCPCBASE + 0x0024)
#define __PERIPHCLKCTRL2    *(volatile U32*)(__RCPCBASE + 0x0028)
#define __PERPIHCLKSELECT	  *(volatile U32*)(__RCPCBASE + 0x0030)
#define __PERIPHCLKSELECT2	*(volatile U32*)(__RCPCBASE + 0x0034)
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
#define __MEMMUX            *(volatile U32*)(__IOCONBASE + 0x0000)
#define __LCDMUX            *(volatile U32*)(__IOCONBASE + 0x0004)

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
  __PERIPHCLKCTRL2   = (0    << 0);                 /* enable clock for LCD Controller */
  __PERIPHCLKSELECT2 = (0    << 0);                 /* select HCLK as Clock for LCD Controller */
  __LCDCLKPRESCALE   =  1;                          /* LCD clock prescaler /2 */
  __LCDMUX           = (0    << 0)                  /* Configure pin 142 as LCDREV (HR-TFT panels) */
                     | (1    << 1)                  /* Configure pin 142 as LCDREV (HR-TFT panels) */
                     | (1    << 2)                  /* Configure pin 141 as LCDVD13 */
                     | (1    << 3)                  /* Configure pin 140 as LCDVD14 */
                     | (1    << 4)                  /* Configure pin 139 as LCDVD15 */
                     | (0    << 5)                  /* Configure pin 139 as LCDVD15 */
                     | (0    << 6)                  /* Configure pin 137 as LCDSPL (HR-TFT panels) */
                     | (1    << 7)                  /* Configure pin 137 as LCDSPL (HR-TFT panels) */
                     | (0    << 8)                  /* Configure pin 135 as LCDCLS (HR-TFT panels) */
                     | (1    << 9)                  /* Configure pin 135 as LCDCLS (HR-TFT panels) */
                     | (0    << 10)                 /* Configure pin 134 as LCDCLKIN */
                     | (1    << 11)                 /* Configure pin 133 as LCDCLK   */
                     | (1    << 12)                 /* Configure pin 132 as LCDVD16  */
                     | (0    << 13)                 /* Configure pin 131 as LCDLP (HR-TFT panels) */
                     | (1    << 14)                 /* Configure pin 131 as LCDLP (HR-TFT panels) */
                     | (1    << 15)                 /* Configure pin 130 as LCDVD17 */
                     | (0    << 16)                 /* Configure pin 129 as LCDSPS (HR-TFT panels) */
                     | (1    << 17)                 /* Configure pin 129 as LCDSPS (HR-TFT panels) */
                     | (1    << 18)                 /* Configure pin 124 as LCDVD2 */
                     | (1    << 19)                 /* Configure pin 123 as LCDVD3 */
                     | (1    << 20)                 /* Configure pin 122 as LCDVD4 */
                     | (1    << 21)                 /* Configure pin 121 as LCDVD5 */
                     | (0    << 22)                 /* Configure pin 119 as LCDPS (HR-TFT panels) */
                     | (1    << 23)                 /* Configure pin 119 as LCDPS (HR-TFT panels) */
                     | (1    << 24)                 /* Configure pin 118 as LCDVD7 */
                     | (1    << 25)                 /* Configure pin 117 as LCDVD8 */
                     | (1    << 26)                 /* Configure pin 116 as LCDVD9 */
                     | (1    << 27)                 /* Configure pin 115 as LCDVD10 */
                     | (1    << 28);                /* Configure pin 114 as LCDVD11 */
  __LCDTIMING0       = (0x14 << 24)                 /* Horizontal back  porch */
                     | (0x14 << 16)                 /* Horizontal front porch */
                     | (0x3c <<  8)                 /* Horizontal synchronization pulse Width */
                     | ((LCD_XSIZE / 16 -1) << 2);  /* Pixels-Per-Line */
  __LCDTIMING1       = (0x07 << 24)                 /* Vertical back  porch */
                     | (0x05 << 16)                 /* Vertical front porch */
                     | (0    << 10)                 /* Vertical synchronization Pulse Width. */
                     | (LCD_YSIZE - 1);             /* Lines-Per-Panel */
  __LCDTIMING2       = (0    << 26)                 /* Bypass pixel Clock Divider */
                     | ((LCD_XSIZE - 1)<< 16)       /* Clocks per line */
                     | (0    << 14)                 /* Invert Output Enable */
                     | (1    << 13)                 /* Invert Panel Clock */
                     | (1    << 12)                 /* Invert Horizontal Synchronization */
                     | (0    << 11)                 /* Invert the Vertical Synchronization signal */
                     | (0    <<  6)                 /* AC Bias signal (LCDENAB) frequency */
                     | (0    <<  0);                /* Panel Clock Divisor.*/
  __LCDUPBASE        = LCD_VRAM_ADR;                /* LCD Upper Panel Base address */
  __LCDINTRENABLE    = 0;                           /* Disable LCD interrupts */
  __LCDCONTROL       = (0    << 16)                 /* LCD DMA FIFO Watermark level */
                     | (0    << 12)                 /* LCD Vertical Compare */
                     | (1    << 11)                 /* LCD Power Enable */
                     | (0    << 10)                 /* Big-Endian Pixel Ordering within a byte */
                     | (0    <<  9)                 /* Big-Endian Byte Ordering to the LCD */
                     | (0    <<  8)                 /* RGB or BGR format selection:
                                                       1 = BGR red and blue swapped
                                                       0 = RGB normal output*/
                     | (0    <<  7)                 /* RLCD is a Dual panel STN */
                     | (0    <<  6)                 /* LCD 8bit Mono (8bit interface)*/
                     | (1    <<  5)                 /* LCD is a TFT */
                     | (0    <<  4)                 /* LCD is STN mono */
                     | (4    <<  1)                 /* LCD bpp 4 = 16bpp
                                                               3 =  8bpp
                                                               2 =  4bpp
                                                               1 =  2bpp */
                     | (1    <<  0);                /* 0 =  Enable LCD Controller */
  __HRTFTCSETUP      = ((LCD_XSIZE - 1 ) << 4)      /* Number of pixels per line */
                     | (6    << 1)                  /* Conversion mode select (HF-TFT panels) */
                     | (1    << 0);                 /* Conversion mode select (HF-TFT panels) */
  __HRTFTCTIMING1    = (8    << 8)                  /* Delay in LCDDCLK periods from the 1st LOW
                                                       in the LCDLP signal, to the leading edge
                                                       of the LCDPS and LCD-CLS signals */
                     | (7    << 4)                  /* Polarity-Reversal delay */
                     | (12   << 0);                 /* Delay in LCDDCLK periods from the 1st LOW
                                                       in the LCDLP signal, to the leading edge
                                                       of the LCDLP signal */
  __HRTFTCTIMING2    = (0x53 << 9)                  /* Delay in LCDDCLK periods of the LCD-SPL signal
                                                       during vertical front and back porches. */
                     | (0xd0 << 0);                 /* Delay in LCDDCLK periods from the first
                                                       rising edge of the LCDSPL signal to the
                                                       trailing edge of the LCDCLS signal */
  __HRTFTCCONTROL    = (1    << 1)                  /* LCDCLS enable  */
                     | (1    << 0);                 /* LCDSPS enable */
}

/*************************** End of file ****************************/

