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
File        : LCDConf_LH79520_C8_VGA.h
Purpose     : Sample configuration file for Sharp LH79520
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
#define LCD_VRAM_ADR         0x21F6A000
#define LCD_BITSPERPIXEL    8
#define LCD_CONTROLLER   3200
#define LCD_XSIZE         640
#define LCD_YSIZE         480
#define LCD_ENDIAN_BIG      0

/*********************************************************************
*
*       LCD_SET_LUT_ENTRY
*
**********************************************************************
*/
void LCD_X_SetLUTEntry(int Pos, U32 Color);
#define LCD_SET_LUT_ENTRY(Pos, Color) LCD_X_SetLUTEntry(Pos, Color)

#endif /* LCDCONF_H */

