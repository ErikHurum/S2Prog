/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2004  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf_1375_C8_C320x240.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#include "..\..\Shared\inc\TSNConstants.h"
#ifndef LCDCONF_H
#define LCDCONF_H

																						
#define LCD_ALLOW_NON_OPTIMIZED_MODE			 1 // Because 16 bit colour can not be
																						 //	supported by LCDLin 8
#define LCD_SWAP_BYTE_ORDER 1
#define LCD_SWAP_RB			1
/*********************************************************************
*
*                   General configuration of LCD
*
**********************************************************************
*/

#define LCD_XSIZE      (320)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (240)   /* Y-resolution of LCD, Logical coor. */

#define LCD_BITSPERPIXEL (16)

#define LCD_CONTROLLER 1375

/*********************************************************************
*
*                   Full bus configuration
*
**********************************************************************
*/

#define LCD_READ_MEM(Off)            *((U16*)         (LCD_STARTADDRESS+(((U32)(Off))<<1)))
#define LCD_WRITE_MEM(Off,data)      *((U16*)         (LCD_STARTADDRESS+(((U32)(Off))<<1)))=data
#define LCD_READ_REG(Off)            *((volatile U16*)(LCD_STARTADDRESS+LCD_RAM_SIZE+(((U16)(Off))<<1)))
#define LCD_WRITE_REG(Off,data)      *((volatile U16*)(LCD_STARTADDRESS+LCD_RAM_SIZE+(((U16)(Off))<<1)))=data

/*********************************************************************
*
*                   Init sequence for 16 bit access
*
**********************************************************************
*/

#if !LCD_SWAP_BYTE_ORDER
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d0)<<8) | (d1))
#else
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d1)<<8) | (d0))
#endif

#define LCD_INIT_CONTROLLER()

#endif /* LCDCONF_H */


