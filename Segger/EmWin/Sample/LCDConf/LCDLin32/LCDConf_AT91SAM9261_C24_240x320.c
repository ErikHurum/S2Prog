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
/* SFR definitions */
#define AT91C_PIOA_PER        (*(volatile U32 *) 	0xFFFFF400) // (PIOA) PIO Enable Register
#define AT91C_PIOA_OER        (*(volatile U32 *) 	0xFFFFF410) // (PIOA) Output Enable Register
#define AT91C_PIOA_CODR       (*(volatile U32 *) 	0xFFFFF434) // (PIOA) Clear Output Data Register

#define AT91C_PIOB_BSR        (*(volatile U32 *) 	0xFFFFF674) // (PIOB) Select B Register
#define AT91C_PIOB_PDR        (*(volatile U32 *) 	0xFFFFF604) // (PIOB) PIO Disable Register

#define AT91C_PMC_SCER        (*(volatile U32 *) 	0xFFFFFC00) // (PMC) System Clock Enable Register

#define AT91C_LCDC_BA1        (*(volatile U32 *) 	0x00600000) // (LCDC) DMA Base Address Register 1
#define AT91C_LCDC_FRMCFG     (*(volatile U32 *) 	0x00600018) // (LCDC) DMA Frame Configuration Register
#define AT91C_LCDC_DMACON     (*(volatile U32 *) 	0x0060001C) // (LCDC) DMA Control Register

#define AT91C_LCDC_LCDCON1    (*(volatile U32 *) 	0x00600800) // (LCDC) LCD Control 1 Register
#define AT91C_LCDC_LCDCON2    (*(volatile U32 *) 	0x00600804) // (LCDC) LCD Control 2 Register
#define AT91C_LCDC_TIM2       (*(volatile U32 *) 	0x0060080C) // (LCDC) LCD Timing Config 2 Register
#define AT91C_LCDC_LCDFRCFG   (*(volatile U32 *) 	0x00600810) // (LCDC) LCD Frame Config Register
#define AT91C_LCDC_FIFO       (*(volatile U32 *) 	0x00600814) // (LCDC) LCD FIFO Register
#define AT91C_LCDC_MVAL       (*(volatile U32 *) 	0x00600818) // (LCDC) LCD Mode Toggle Rate Value Register
#define AT91C_LCDC_TIM1       (*(volatile U32 *) 	0x00600808) // (LCDC) LCD Timing Config 1 Register
#define AT91C_LCDC_PWRCON     (*(volatile U32 *) 	0x0060083C) // (LCDC) Power Control Register
#define AT91C_LCDC_CTRSTCON   (*(volatile U32 *) 	0x00600840) // (LCDC) Contrast Control Register
#define AT91C_LCDC_CTRSTVAL   (*(volatile U32 *) 	0x00600844) // (LCDC) Contrast Value Register
#define AT91C_LCDC_IDR        (*(volatile U32 *) 	0x0060084C) // (LCDC) Interrupt Disable Register

/* PLA frequency */
#define MAIN_OSC_CLK (18432000UL)
#define MUL_PLLA     (109UL)
#define DIV_PLLA     (10UL)
#define PLLA_FREQ    ((MAIN_OSC_CLK * MUL_PLLA) / DIV_PLLA)

/* Further controller values */
#define VL_COL       _XSIZE
#define VL_ROW       _YSIZE
#define VL_PIXCLOCK  4965000
#define VL_HSP       1
#define VL_VSP       2
#define VL_TFT       1
#define VL_HPW       5
#define VL_BLW       1
#define VL_ELW       33
#define VL_VPW       1
#define VL_BFW       1
#define VL_EFW       0
#if   (_BITSPERPIXEL == 8)
  #define VL_BPIX      3
  #define SHIFT        0
#elif (_BITSPERPIXEL == 16)
  #define VL_BPIX      4
  #define SHIFT        0
#elif (_BITSPERPIXEL == 24)
  #define VL_BPIX      5
  #define SHIFT        1
#endif

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
  /* Initialize port pins */
  AT91C_PIOB_PDR      = 0x1F9F9F9E;
  AT91C_PIOB_BSR      = 0x1F800000;
  AT91C_PIOA_PER      = (1 << 12);
  AT91C_PIOA_OER      = (1 << 12);
  AT91C_PIOA_CODR     = (1 << 12);

  /* Enable clock */
  AT91C_PMC_SCER      = (1 << 17);

  /* Initialize LCDC registers */
  AT91C_LCDC_PWRCON   = 0x0C;
  AT91C_LCDC_DMACON   = 0;
  AT91C_LCDC_DMACON   = (1 << 1);
  AT91C_LCDC_FRMCFG   = ((U32)((512 - 1) << 24))
                      | (((U32)VL_ROW * (U32)VL_COL * (U32)(1 << VL_BPIX)) / 32);
  AT91C_LCDC_LCDCON1  = ((((PLLA_FREQ / 2) / VL_PIXCLOCK + 1) / 2) - 1) << 12;
  AT91C_LCDC_LCDCON2  = ((U32)(1 << 31)
                      | 2
                      | (1 << 15))
                      | ((U32)(VL_BPIX << 5));
  AT91C_LCDC_TIM1     = ((U32)((VL_VPW - 1) << 16))
                      | ((U32)(VL_BFW << 8))
                      | ((U32)VL_EFW);
  AT91C_LCDC_TIM2     = ((U32)((VL_ELW - 1) << 21))
                      | ((U32)((VL_HPW - 1) << 8))
                      | ((U32)(VL_BLW - 1));
  AT91C_LCDC_LCDFRCFG = ((U32)((_XSIZE - 1) << 21))
                      | ((U32)(VL_ROW - 1) << (SHIFT));
  AT91C_LCDC_FIFO     = 512 - (2 * 16 + 3);
  AT91C_LCDC_MVAL     = 0;
  AT91C_LCDC_IDR      = ~0UL;
  AT91C_LCDC_CTRSTCON = 3
                      | (1 << 2)
                      | (1 << 3);
  AT91C_LCDC_CTRSTVAL = 0xDA;
  AT91C_LCDC_BA1      = (U32)LCD_VRAM_ADR;
  AT91C_LCDC_FRMCFG   = (15 << 24)
                      | ((U32)VL_COL * (U32)VL_ROW * (U32)(1 << VL_BPIX)) / 32;
  AT91C_LCDC_DMACON   = (1 << 0);
}

/*********************************************************************
*
*       LCD_X_SetLUTEntry
*
* Purpose:
*   Sets one entry of the LUT
*/
void LCD_X_SetLUTEntry(int Pos, U32 Color) {
  U32 r, g, b;
  r = (Color & 0x0000ff) >>  0;
  g = (Color & 0x00ff00) >>  8;
  b = (Color & 0xff0000) >> 16;
  *(((volatile U32 *)0x00600C00) + Pos) = (r >> 3 | ((g & 0xf8) << 2) | ((b & 0xf8) << 7));
}

/*********************************************************************
*
*       LCD_X_On
*
*/
void LCD_X_On(void) {
  AT91C_LCDC_PWRCON = (1 << 0) | 0x0C;
}

/*********************************************************************
*
*       LCD_X_Off
*
*/
void LCD_X_Off(void) {
  AT91C_LCDC_PWRCON = (0 << 0) | 0x0C;
}

/*************************** End of file ****************************/

