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
File        : LCDConf_1375_C4PR90_C320x240.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*       General configuration of LCD
*
**********************************************************************
*/

#define LCD_XSIZE      (240)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (320)   /* Y-resolution of LCD, Logical coor. */

#define LCD_CONTROLLER 1375

#define LCD_READ_MEM(Off)       *((U16*)         (0xc00000 + (((U32)(Off)) << 1)))
#define LCD_WRITE_MEM(Off,data) *((U16*)         (0xc00000 + (((U32)(Off)) << 1))) = data
#define LCD_READ_REG(Off)       *((volatile U16*)(0xc1ffe0 + (((U16)(Off)) << 1)))
#define LCD_WRITE_REG(Off,data) *((volatile U16*)(0xc1ffe0 + (((U16)(Off)) << 1))) = data

#define LCD_BITSPERPIXEL (4)

#define LCD_SWAP_BYTE_ORDER 0

/*********************************************************************
*
*       List of physical colors
*
**********************************************************************
*/
#define LCD_PHYSCOLORS  0x000000      /* 0000  black            */ \
                       ,0x000080      /* 0001  dark red         */ \
                       ,0x008000      /* 0010  dark green       */ \
                       ,0x008080      /* 0011  mustard          */ \
                       ,0x800000      /* 0100  dark blue        */ \
                       ,0x800080      /* 0101  purple           */ \
                       ,0x808000      /* 0110  dark turquoise   */ \
                       ,0xC0C0C0	    /* 1000  gray             */ \
                       ,0x808080      /* 0111  dark gray        */ \
                       ,0x0000ff      /* 1001  red              */ \
                       ,0x00FF00      /* 1010  green            */ \
                       ,0x00FFFF      /* 1011  yellow           */ \
                       ,0xFF0000      /* 1100  blue             */ \
                       ,0xFF00FF      /* 1101  pink (magenta)   */ \
                       ,0xFFFF00      /* 1110  cyan             */ \
											 ,0xFFFFFF      /* 1111  white            */

#endif /* LCDCONF_H */

