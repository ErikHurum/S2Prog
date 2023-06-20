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
File        : LCDConf_1376_C8_C320x240.h
Purpose     : Internal sample configuration file
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

#define LCD_XSIZE      240      /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      320      /* Y-resolution of LCD, Logical coor. */

#define LCD_CONTROLLER 1376

#define LCD_BITSPERPIXEL    8
#define LCD_SWAP_BYTE_ORDER 1

/*********************************************************************
*
*       Full bus configuration
*
**********************************************************************
*/

#define LCD_READ_MEM(Off)       *((U16*)         (0x420000+(((U32)(Off))<<1)))
#define LCD_WRITE_MEM(Off,data) *((U16*)         (0x420000+(((U32)(Off))<<1)))=data
#define LCD_READ_REG(Off)       *((volatile U16*)(0x620000+(((U16)(Off))<<1)))
#define LCD_WRITE_REG(Off,data) *((volatile U16*)(0x620000+(((U16)(Off))<<1)))=data

#endif /* LCDCONF_H */
