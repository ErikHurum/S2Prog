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
#define __CLCDCBASE     0x80003000
#define __LCDTIMING0    *(volatile U32*)(__CLCDCBASE + 0x0000)
#define __LCDTIMING1    *(volatile U32*)(__CLCDCBASE + 0x0004)
#define __LCDTIMING2    *(volatile U32*)(__CLCDCBASE + 0x0008)
#define __LCDTIMING3    *(volatile U32*)(__CLCDCBASE + 0x000C)
#define __LCDUPBASE     *(volatile U32*)(__CLCDCBASE + 0x0010)
#define __LCDLPBASE	    *(volatile U32*)(__CLCDCBASE + 0x0014)
#define __LCDINTRENABLE *(volatile U32*)(__CLCDCBASE + 0x0018)
#define __LCDCONTROL    *(volatile U32*)(__CLCDCBASE + 0x001C)
#define __LCDSTATUS	    *(volatile U32*)(__CLCDCBASE + 0x0020)
#define __LCDINTERRUPT  *(volatile U32*)(__CLCDCBASE + 0x0024)
#define __LCDPALLETTE   *(volatile U32*)(__CLCDCBASE + 0x0200)

#define __ALILCDCBASE    0x80001000
#define __ALISETUP      *(volatile U32*)(__ALILCDCBASE + 0x0000)
#define __ALICONTROL    *(volatile U32*)(__ALILCDCBASE + 0x0004)
#define __ALITIMING1    *(volatile U32*)(__ALILCDCBASE + 0x0008)
#define __ALITIMING2    *(volatile U32*)(__ALILCDCBASE + 0x000C)

#define __GPIOBASE  0x80000E00
#define __GPIO_PAD           *(volatile U32*)(__GPIOBASE + 0x0000)
#define __GPIO_PBD           *(volatile U32*)(__GPIOBASE + 0x0004)
#define __GPIO_PCD           *(volatile U32*)(__GPIOBASE + 0x0008)
#define __GPIO_PDD           *(volatile U32*)(__GPIOBASE + 0x000C)
#define __GPIO_PADD          *(volatile U32*)(__GPIOBASE + 0x0010)
#define __GPIO_PBDD          *(volatile U32*)(__GPIOBASE + 0x0014)
#define __GPIO_PCDD          *(volatile U32*)(__GPIOBASE + 0x0018)
#define __GPIO_PDDD          *(volatile U32*)(__GPIOBASE + 0x001C)
#define __GPIO_PED           *(volatile U32*)(__GPIOBASE + 0x0020)
#define __GPIO_PEDD          *(volatile U32*)(__GPIOBASE + 0x0024)
#define __GPIO_KBDCTL        *(volatile U32*)(__GPIOBASE + 0x0028)
#define __GPIO_PINMUX        *(volatile U32*)(__GPIOBASE + 0x002C)
#define __GPIO_PFD           *(volatile U32*)(__GPIOBASE + 0x0030)
#define __GPIO_PFDD          *(volatile U32*)(__GPIOBASE + 0x0034)
#define __GPIO_PGD           *(volatile U32*)(__GPIOBASE + 0x0038)
#define __GPIO_PGDD          *(volatile U32*)(__GPIOBASE + 0x003C)
#define __GPIO_PHD           *(volatile U32*)(__GPIOBASE + 0x0040)
#define __GPIO_PHDD          *(volatile U32*)(__GPIOBASE + 0x0044)

#define __GPIO_INTTYPE1      *(volatile U32*)(__GPIOBASE + 0x004C)
#define __GPIO_INTTYPE2      *(volatile U32*)(__GPIOBASE + 0x0050)
#define __GPIO_GPIOFEOI      *(volatile U32*)(__GPIOBASE + 0x0054)
#define __GPIO_GPIOINTEN     *(volatile U32*)(__GPIOBASE + 0x0058)
#define __GPIO_INTSTATUS     *(volatile U32*)(__GPIOBASE + 0x005C)
#define __GPIO_RAWINTSTATUS  *(volatile U32*)(__GPIOBASE + 0x0060)
#define __GPIO_DEBOUNCE      *(volatile U32*)(__GPIOBASE + 0x0064)
#define __GPIO_PAPD          *(volatile U32*)(__GPIOBASE + 0x0068)
#define __GPIO_PBPD          *(volatile U32*)(__GPIOBASE + 0x006C)
#define __GPIO_PCPD          *(volatile U32*)(__GPIOBASE + 0x0070)
#define __GPIO_PDPD          *(volatile U32*)(__GPIOBASE + 0x0074)
#define __GPIO_PEPD          *(volatile U32*)(__GPIOBASE + 0x0078)
#define __GPIO_PFPD          *(volatile U32*)(__GPIOBASE + 0x007C)
#define __GPIO_PGPD          *(volatile U32*)(__GPIOBASE + 0x0080)
#define __GPIO_PHPD          *(volatile U32*)(__GPIOBASE + 0x0084)

#define __CARD_ENGINE_CTRL   *(volatile U32*)(0x70200000)

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
  __GPIO_PINMUX         |= (1 << 1)
                         | (1 << 0);
  __LCDCONTROL           = 0x00000000;               /* Disable the LCD Controller first */
  __ALICONTROL           = 0x00000000;               /* Disable LCDCLS and LCDSPS signals */
  __ALISETUP             = (0x00 << 13)              /* Enable Advanced LCD Interface (ALI) */
                         | ((LCD_XSIZE - 1) <<  4);  /* Setup Pixels per lines for ALI  */
  __LCDTIMING0           = (((LCD_XSIZE / 16) - 1) << 2)    /* Setup Pixels per lines for LCD Timings register1 */
                         | (( 16 - 1) <<  8)         /* Setup Pixels per lines for LCD Timings register1 */
                         | (( 51 - 1) << 16)         /* Setup Pixels per lines for LCD Timings register1 */
                         | (( 90 - 1) << 24);        /* Setup Pixels per lines for LCD Timings register1 */
  __LCDTIMING1           = (LCD_YSIZE - 1)           /* Setup Pixels per lines for LCD Timings register1 */
                         | (( 8 - 1) << 10)          /* Use 4 Vertical Sychronization Pulse width */
                         | ((95 - 1) << 16)          /* Set Vertical Front Porch */
                         | ((27 - 1) << 24);         /* Set Vertical backporch */
  __LCDTIMING2           = (2 <<  0)                        /* Set Vertical backporch */
                         | (1 << 11)                        /* LCDFFP is active low */
                         | (1 << 12)                        /* LCDLP is active low  */
                         | ((LCD_XSIZE - 1) << 16);
  __LCDTIMING3           = 0;                        /* Not available */
  __LCDUPBASE            = LCD_MEMBASE;
  *(volatile U32*)(0x71a00000)            = 3;
  *(volatile U32*)(0x71800000)            = 3;
  *(volatile U32*)(0x71800000)            = 0x80;
  __LCDCONTROL           = (1 << 16)                /* LCD DMA FIFO Watermark level */
                         | (0 << 12)                /* LCD Vertical Compare */
                         | (1 << 11)                /* LCD Power Enable */
                         | (0 << 10)                /* Big-Endian Pixel Ordering within a byte */
                         | (0 <<  9)                /* Big-Endian Byte Ordering to the LCD */
                         | (0 <<  8)                /* RGB or BGR format selection:
                                                       1 = BGR red and blue swapped
                                                       0 = RGB normal output*/
                         | (0 <<  7)                /* RLCD is a Dual panel STN */
                         | (0 <<  6)                /* LCD 4bit Mono (4bit interface)*/
                         | (1 <<  5)                /* LCD is a TFT */
                         | (0 <<  4)                /* LCD is STN mono */
                         | (4 <<  1)                /* LCD bpp 4 = 16bpp
                                                               3 =  8bpp
                                                               2 =  4bpp
                                                               1 =  2bpp */
                         | (1 <<  0);                /* 0 =  Enable LCD Controller */
  /* Setup Port pins */
  __GPIO_PADD           |= 0xb5;
  __GPIO_PBDD           |= 0xc0;
  __GPIO_PCDD           |= 0xb5;
  __GPIO_PDDD           |= 0x00;
  __GPIO_PEDD           |= 0xff;
  __GPIO_PFDD           |= 0x00;
  __GPIO_PGDD           |= 0x00;
  __GPIO_PHDD           |= 0xcf;
  __GPIO_PAD            |= 0x0f;
  __GPIO_PBD            |= 0x3f;
  __GPIO_PCD            |= 0xb9;
  __GPIO_PDD            |= 0x00;
  __GPIO_PED            |= 0xf0;
  __GPIO_PFD            |= 0xff;
  __GPIO_PGD            |= 0xff;
  __GPIO_PHD            |= 0xfc;
  __GPIO_INTTYPE1        = 0x10;
  /* Enable VEE */
  __CARD_ENGINE_CTRL    = 0xffffffff;
}

/*************************** End of file ****************************/

