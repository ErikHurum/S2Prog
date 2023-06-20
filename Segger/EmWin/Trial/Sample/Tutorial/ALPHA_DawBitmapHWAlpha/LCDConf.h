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
File        : LCDConf.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

#define LCD_XSIZE_0            320
#define LCD_YSIZE_0            240
#define LCD_BITSPERPIXEL_0       8
#define LCD_CONTROLLER_0      3200
#define LCD_VRAM_ADR_0     0x20000
#define LCD_ENDIAN_BIG_0         0

#define LCD_INIT_CONTROLLER_0()

#define LCD_XSIZE_1            320
#define LCD_YSIZE_1            240
#define LCD_BITSPERPIXEL_1      32
#define LCD_CONTROLLER_1      3200
#define LCD_VRAM_ADR_1     0x20000
#define LCD_ENDIAN_BIG_1         0
#define LCD_FIXEDPALETTE_1      -1

#define LCD_INIT_CONTROLLER_1()

#endif
