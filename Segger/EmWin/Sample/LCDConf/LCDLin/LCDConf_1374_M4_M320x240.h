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
File        : LCDConf.H
Purpose     : This file is the internal configuration file for the
              emWin LCD-Driver.
              It might be necessary to include header files of other
              modules if the driver relies on macros or routines of
              other modules.
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
#define LCD_XSIZE      (320)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (240)   /* Y-resolution of LCD, Logical coor. */
#define LCD_MIRROR_X   (0)     /* If active:  X -> -X */
#define LCD_MIRROR_Y   (0)     /* If active:  Y -> -Y */
#define LCD_SWAP_XY    (0)     /* If active:  X <-> Y */

#define LCD_CONTROLLER 1374

#define LCD_SWAP_BYTE_ORDER 0

#define LCD_READ_MEM(Off)       *((U16*)         (0xc00000 + (((U32)(Off)) << 1)))
#define LCD_WRITE_MEM(Off,data) *((U16*)         (0xc00000 + (((U32)(Off)) << 1))) = data
#define LCD_READ_REG(Off)       *((volatile U16*)(0xc1ffe0 + (((U16)(Off)) << 1)))
#define LCD_WRITE_REG(Off,data) *((volatile U16*)(0xc1ffe0 + (((U16)(Off)) << 1))) = data

/* Number of bits per pixel.
   Permitted values depend on controller used.
   e.g:
   1 for  black/white
   2 for  4 gray scales
   4 for 16 gray scales          */
#define LCD_BITSPERPIXEL (4)
 
#endif /* LCDCONF_H */

