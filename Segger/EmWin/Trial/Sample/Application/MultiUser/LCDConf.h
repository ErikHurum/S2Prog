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
Purpose     : SEGGER internal standard configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*       Layer 0
*/
#define LCD_CONTROLLER_0               9101 /* Selects the Xylon FPGA display driver */

#define LCD_XSIZE_0                     320 /* Physical display size in X */
#define LCD_YSIZE_0                     240 /* Physical display size in Y */
#define LCD_BITSPERPIXEL_0               16 /* Color depth */
#define LCD_SWAP_RB_0                     1

#define LCD_INIT_CONTROLLER_0()

/*********************************************************************
*
*       Layer 1
*/
#define LCD_CONTROLLER_1               9101 /* Selects the Xylon FPGA display driver */

#define LCD_XSIZE_1                     320 /* Physical display size in X */
#define LCD_YSIZE_1                     240 /* Physical display size in Y */
#define LCD_BITSPERPIXEL_1                8 /* Color depth */
#define LCD_FIXEDPALETTE_1           822216

/*********************************************************************
*
*       Layer 2
*/
#define LCD_CONTROLLER_2               9101 /* Selects the Xylon FPGA display driver */

#define LCD_XSIZE_2                     320 /* Physical display size in X */
#define LCD_YSIZE_2                     240 /* Physical display size in Y */
#define LCD_BITSPERPIXEL_2                8 /* Color depth */

#define LCD_INIT_CONTROLLER_2()

#endif /* LCDCONF_H */

