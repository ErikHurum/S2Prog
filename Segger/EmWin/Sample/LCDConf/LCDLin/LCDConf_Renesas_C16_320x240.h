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
File        : LCDConf_Renesas_C16_320x240.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*       Configuration of LCD
*
**********************************************************************
*/
#define LCD_XSIZE                   320
#define LCD_YSIZE                   240

#define LCD_BITSPERPIXEL             16
#define LCD_SWAP_RB                   1
#define LCD_MIRROR_Y                  1

#define LCD_CONTROLLER            32168
#define LCD_ENDIAN_BIG                1

void VGAinit(void);

#define LCD_INIT_CONTROLLER() VGAinit()

extern unsigned int display_buffer[];

#define LCD_VRAM_ADR (long)display_buffer

#endif /* LCDCONF_H */

 
