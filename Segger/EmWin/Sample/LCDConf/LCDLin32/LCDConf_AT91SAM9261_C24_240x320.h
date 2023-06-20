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
File        : LCDConf_AT91SAM9261_C24_240x320.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

#define _CONTROLLER            3200
#define _BITSPERPIXEL            24
#define _ENDIAN_BIG               0
#define _VRAM_ADR        0x22000000
#define _XSIZE                  240
#define _YSIZE                  320

#if (_BITSPERPIXEL != 8) && (_BITSPERPIXEL != 16) && (_BITSPERPIXEL != 24)
  #error Currently not supported by this configuration file!
#endif

/*********************************************************************
*
*       General configuration of LCD
*
**********************************************************************
*/
#define LCD_CONTROLLER          _CONTROLLER
#define LCD_BITSPERPIXEL        _BITSPERPIXEL
#define LCD_ENDIAN_BIG          _ENDIAN_BIG
#define LCD_VRAM_ADR            _VRAM_ADR
#define LCD_XSIZE               _XSIZE
#define LCD_YSIZE               _YSIZE

/*********************************************************************
*
*       Define fixed palette mode 555 for 16bpp color depth
*
**********************************************************************
*/
#if (_BITSPERPIXEL == 16)
  #define LCD_FIXEDPALETTE      555
#endif

#if !defined(WIN32)

void LCD_X_SetLUTEntry(int Pos, U32 Color);
void LCD_X_On(void);
void LCD_X_Off(void);

/*********************************************************************
*
*       LCD_SET_LUT_ENTRY, LCD_ON, LCD_OFF
*
**********************************************************************
*/
#define LCD_SET_LUT_ENTRY(Pos, Color) LCD_X_SetLUTEntry(Pos, Color)
#define LCD_ON()                      LCD_X_On()
#define LCD_OFF()                     LCD_X_Off()

#endif

#endif