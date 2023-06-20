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
File        : LCDConf_1386_C16A_S1C33240_VGAMON.h
Purpose     : Sample configuration file for EPSON 13806 LCD controller
              connected to VGA monitor
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

#define LCD_XSIZE      (640)      /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (480)      /* Y-resolution of LCD, Logical coor. */

#define LCD_CONTROLLER 1386

#define LCD_SWAP_BYTE_ORDER (1)
#define LCD_BITSPERPIXEL    (16)
#define LCD_SWAP_RB         (1)

/*********************************************************************
*
*       Full bus configuration
*
**********************************************************************
*/

#define LCD_READ_MEM(Off)            *((U16 *)(0xa00000+(((U32)(Off))<<1)))
#define LCD_WRITE_MEM(Off,data)      *((U16 *)(0xa00000+(((U32)(Off))<<1)))=data
#define LCD_READ_REG(Off)            *((volatile U16*)(0x800000+(((U32)(Off))<<1)))
#define LCD_WRITE_REG(Off,data)      *((volatile U16*)(0x800000+(((U32)(Off))<<1)))=data

/*********************************************************************
*
*       LCD_ON / LCD_OFF
*
**********************************************************************
*/

#define LCD_OFF() LCD_WRITE_REG(0x01fc, 0x0000)
#define LCD_ON()  LCD_WRITE_REG(0x01fc, 0x0002)

#endif /* LCDCONF_H */

