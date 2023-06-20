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
*       Defines
*
**********************************************************************
*/
#define RCPC_APBPERIPHCLKCTRL1 *(volatile U32*)(0xfffe2028)
#define RCPC_AHBCLKCTRL        *(volatile U32*)(0xfffe202c)
#define RCPC_LCDPRESCALER      *(volatile U32*)(0xfffe2040)
#define CLCDC_TIMING0          *(volatile U32*)(0xffff4000)
#define CLCDC_TIMING1          *(volatile U32*)(0xffff4004)
#define CLCDC_TIMING2          *(volatile U32*)(0xffff4008)
#define CLCDC_UPBASE           *(volatile U32*)(0xffff4010)
#define CLCDC_LPBASE           *(volatile U32*)(0xffff4014)
#define CLCDC_INTRENABLE       *(volatile U32*)(0xffff4018)
#define CLCDC_CTRL             *(volatile U32*)(0xffff401c)
#define HRTFTC_SETUP           *(volatile U32*)(0xfffe4000)
#define HRTFTC_CTRL            *(volatile U32*)(0xfffe4004)
#define HRTFTC_TIMING1         *(volatile U32*)(0xfffe4008)
#define HRTFTC_TIMING2         *(volatile U32*)(0xfffe400c)
#define IOCON_PD_MUX           *(volatile U32*)(0xfffe5004)
#define IOCON_LCD_MUX          *(volatile U32*)(0xfffe5010)
#define GPIO_PDDR              *(volatile U32*)(0xfffde004)
#define GPIO_PDDDR             *(volatile U32*)(0xfffde00c)

#define HBP_INIT             17
#define HSW_INIT            100

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
  RCPC_APBPERIPHCLKCTRL1 &= ~(1 << 0);                       /* U0 peripheral clock is running. */  
  RCPC_AHBCLKCTRL        &= ~(1 << 0);                       /* AHB DMA clock is running. */  
  IOCON_LCD_MUX          =  (0x1 << 0);                      /* 4-bit Mono STN Mode */ 
  RCPC_LCDPRESCALER      =  (0x2 << 0);                      /* f(HCLK)/4 */ 
  CLCDC_UPBASE           =  LCD_VRAM_ADR;                    /* Upper Panel Frame Buffer Base Address Register */  
  CLCDC_LPBASE           =  LCD_VRAM_ADR;                    /* Lower Panel Frame Buffer Base Address Register */  
  CLCDC_TIMING0          =  (HBP_INIT << 24)                 /* Horizontal Back Porch */  
                         |  (32 << 16)                       /* Horizontal Front Porch */  
                         |  (HSW_INIT <<  8)                 /* Horizontal Synchronization Pulse Width */  
                         |  (((XSIZE / 16) - 1) << 2);       /* Pixels-Per-Line */ 
  CLCDC_TIMING1          =  (2 << 24)                        /* Vertical Back Porch */ 
                         |  (2 << 16)                        /* Vertical Front Porch */ 
                         |  (0 << 10)                        /* Vertical Synchronisation */ 
                         |  ((YSIZE - 1) << 0);              /* Lines Per Panel, should be odd */ 
  CLCDC_TIMING2          =  ( 0 << 26)                       /* Use the pixel clock divider logic */ 
                         |  (((XSIZE / 4) - 1) << 16)        /* Clocks per line init for 4-bit mono STN panels */ 
                         |  ( 1 << 14)                       /* LCDSPL aktive high */ 
                         |  ( 0 << 13)                       /* Data is driven out on rising edge of LCDDCLK  */ 
                         |  ( 0 << 12)                       /* LCDHRLP (Horizontal Synchronisation)is aktive high  */ 
                         |  ( 0 << 11)                       /* LCDSPS (Vertikal synchronisation) )is active high */ 
                         |  (22 <<  6)                       /* AC Bias Pin Frequency */ 
                         |  ( 2 <<  0);                      /* Panel Clock Divisor */ 
  CLCDC_INTRENABLE       =  0x00000000;                      /* Interrupt Enable Register, all disabled */  
  CLCDC_CTRL             =  (0 << 16)                        /* FIFO Watermark 4 or more empty locations */  
                         |  (0 << 15)                        /* No FIFO RAM Test */ 
                         |  (0 << 12)                        /* Interrupt at start of vertical synchronisation */ 
                         |  (1 << 11)                        /* LCD Powerenable: Pin LCDVDDEN in High wenn bit LcdEN is High  */ 
                         |  (0 <<  8)                        /* Normal output: Red and Blue not swapped */ 
                         |  (0 <<  7)                        /* Single panel LCD */ 
                         |  (0 <<  5)                        /* LCD is STN */ 
                         |  (1 <<  4)                        /* LCD is monochrome */ 
                         |  (2 <<  1)                        /* 4 bpp (bits per Pixel) */ 
                         |  (1 <<  0);                       /* Enable  LCD */ 
  IOCON_PD_MUX           |= 0x50;                            /* GPIO Config */  
  GPIO_PDDDR             |= 0x60;                            /* GPIO Config */  
  GPIO_PDDR              |= 0x60;                            /* GPIO Config */
}

/*********************************************************************
*
*       LCD_X_SetLUTEntry
*
* Purpose:
*   Sets one entry of the LUT
*/
void LCD_X_SetLUTEntry(int Pos, U32 Color) {
  volatile U32 * pPalette;
  U32 Index;
  pPalette = (volatile U32 *)(0xffff4200) + (Pos >> 1);
  Index    = LCD_Color2Index_444_16(Color) >> 1;
  if (Pos & 1) {
    *pPalette &= 0x0000FFFF;
    *pPalette |= Index << 16;
  } else {
    *pPalette &= 0xFFFF0000;
    *pPalette |= Index;
  }
}

/*************************** End of file ****************************/

