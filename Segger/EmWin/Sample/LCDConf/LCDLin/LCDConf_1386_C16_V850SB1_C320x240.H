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
File        : LCDConf_1386_C16_V850SB1_C320x240.h
Purpose     : Sample configuration file for Quarter VGA TFT
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

#define LCD_XSIZE      (320)      /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (240)      /* Y-resolution of LCD, Logical coor. */

#define LCD_CONTROLLER 1386

#define LCD_SWAP_BYTE_ORDER (0)
#define LCD_BITSPERPIXEL    (16)
#define LCD_SWAP_RB         (1)
#define LCD_USE_BITBLT      (1)

/*********************************************************************
*
*       Full bus configuration
*
**********************************************************************
*/

#define LCD_READ_MEM(Off)            *((U16 *)        (0x600000+(((U32)(Off))<<1)))
#define LCD_WRITE_MEM(Off,Data)      *((U16 *)        (0x600000+(((U32)(Off))<<1)))=Data
#define LCD_READ_REG(Off)            *((volatile U16*)(0x400000+(((U32)(Off))<<1)))
#define LCD_WRITE_REG(Off,Data)      *((volatile U16*)(0x400000+(((U32)(Off))<<1)))=Data

/*********************************************************************
*
*       LCD_ON / LCD_OFF
*
**********************************************************************
*/

//#define LCD_OFF() LCD_WRITE_REGLH(0x1FC >> 1,          0,          0)
//#define LCD_ON()  LCD_WRITE_REGLH(0x1FC >> 1, LCD_REG1FC,          0)

#endif /* LCDCONF_H */

