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
File        : LCDConf_LH7A404_C16_VGA.h
Purpose     : Sample Configuration file for LH79524
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*       General configuration
*
**********************************************************************
*/
#define LCD_MEMBASE      0xC1000000
#define LCD_BITSPERPIXEL   16
#define LCD_XSIZE         640
#define LCD_YSIZE         480

#define LCD_CONTROLLER   3200

#define LCD_FIXEDPALETTE    555
#define LCD_SWAP_RB         (0)
#define LCD_SWAP_BYTE_ORDER (1)
#define LCD_ENDIAN_BIG       0
#define LCD_VRAM_ADR  LCD_MEMBASE

#endif /* LCDCONF_H */

