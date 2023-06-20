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
#define REG_CRTTV_HDP              (((LCD_XSIZE + 7) >> 3) - 1)
#define REG_CRTTV_MEM_ADDR_OFFSET0 ((((LCD_XSIZE + 15) >> 4) * LCD_BITSPERPIXEL) & 0xff)
#define REG_CRTTV_MEM_ADDR_OFFSET1 ((((LCD_XSIZE + 15) >> 4) * LCD_BITSPERPIXEL) >> 8)
#define REG_CRTTV_MEM_ADDR_OFFSET  ((REG_CRTTV_MEM_ADDR_OFFSET1 << 8) + REG_CRTTV_MEM_ADDR_OFFSET0)

#if   (LCD_BITSPERPIXEL == 4)
  #define REG_CRTTV_DISPLAY_MODE 0x02
#elif (LCD_BITSPERPIXEL == 8)
  #define REG_CRTTV_DISPLAY_MODE 0x03
#elif (LCD_BITSPERPIXEL == 16)
  #define REG_CRTTV_DISPLAY_MODE 0x05
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
  LCD_WRITE_REG(0x0000/2, 0x0000);                        /* REG_MISC */ 
  LCD_WRITE_REG(0x001c/2, 0x0002);                        /* REG_MPCLK_CFG */ 
  LCD_WRITE_REG(0x0020/2, 0x0380);                        /* REG_MEM_CFG, REG_DRAM_REFRESH */ 
  LCD_WRITE_REG(0x002a/2, 0x0100);                        /* REG_DRAM_TIMINGS_CTRL0, REG_DRAM_TIMINGS_CTRL1 */ 
  LCD_WRITE_REG(0x01fc/2, 0x0000);                        /* REG_DISPLAY_MODE */ 
  LCD_WRITE_REG(0x0004/2, 0x0000);                        /* REG_GPIO_CONFIG0, REG_GPIO_CONFIG1 */ 
  LCD_WRITE_REG(0x0008/2, 0x0000);                        /* REG_GPIO_CTRL0, REG_GPIO_CTRL1 */ 
  LCD_WRITE_REG(0x0010/2, 0x0002);                        /* REG_MEM_CLOCK_CFG */ 
  LCD_WRITE_REG(0x0014/2, 0x0000);                        /* REG_LCD_PCLK_CFG */ 
  LCD_WRITE_REG(0x0018/2, 0x0000);                        /* REG_CRTTV_PCLK_CFG */ 
  LCD_WRITE_REG(0x001e/2, 0x0000);                        /* REG_CPU2MEM_WAIT_SEL */ 
  LCD_WRITE_REG(0x0020/2, 0x0380);                        /* REG_MEM_CFG, REG_DRAM_REFRESH */ 
  LCD_WRITE_REG(0x002a/2, 0x0100);                        /* REG_DRAM_TIMINGS_CTRL0, REG_DRAM_TIMINGS_CTRL1 */ 
  LCD_WRITE_REG(0x0050/2, REG_CRTTV_HDP);                 /* REG_CRTTV_HDP */ 
  LCD_WRITE_REG(0x0052/2, 0x0113);                        /* REG_CRTTV_HNDP, REG_CRTTV_HRTC_START */ 
  LCD_WRITE_REG(0x0054/2, 0x000b);                        /* REG_CRT_HRTC_PULSE */ 
  LCD_WRITE_REG(0x0056/2, 0x01df);                        /* REG_CRTTV_VDP0, REG_CRTTV_VDP1 */ 
  LCD_WRITE_REG(0x0058/2, 0x092b);                        /* REG_CRTTV_VNDP, REG_CRTTV_VRTC_START */ 
  LCD_WRITE_REG(0x005a/2, 0x1001);                        /* REG_CRT_VRTC_PULSE, REG_TV_OUTPUT_CTRL */ 
  LCD_WRITE_REG(0x0060/2, REG_CRTTV_DISPLAY_MODE);        /* REG_CRTTV_DISPLAY_MODE */ 
  LCD_WRITE_REG(0x0062/2, 0x0000);                        /* REG_CRTTV_START_ADDR0, REG_CRTTV_START_ADDR1 */ 
  LCD_WRITE_REG(0x0064/2, 0x0000);                        /* REG_CRTTV_START_ADDR2 */ 
  LCD_WRITE_REG(0x0066/2, REG_CRTTV_MEM_ADDR_OFFSET);     /* REG_CRTTV_MEM_ADDR_OFFSET0, REG_CRTTV_MEM_ADDR_OFFSET1 */ 
  LCD_WRITE_REG(0x0068/2, 0x0000);                        /* REG_CRTTV_PIXEL_PANNING */ 
  LCD_WRITE_REG(0x006a/2, 0x0000);                        /* REG_CRTTV_FIFO_HIGH_THRESHOLD, REG_CRTTV_FIFO_LOW_THRESHOLD */ 
  LCD_WRITE_REG(0x01f0/2, 0x0010);                        /* REG_PWR_SAVE_CFG, REG_PWR_SAVE_STATUS */ 
  LCD_WRITE_REG(0x01fc/2, 0x0002);                        /* REG_DISPLAY_MODE */
}

/*************************** End of file ****************************/

