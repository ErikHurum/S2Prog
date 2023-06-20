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
File        : LCD_API.c
Purpose     : Selection of LCD display
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */

#include "GUI_Private.h"

/*********************************************************************
*
*                 LCD_aAPI
*
* Purpose:
*  This table lists the available displays/layers by a single pointer.
*  It is important that these are non-constants, because some high level
*  software (such as the VNC server, but maybe also the mouse "Cursor" mdoule)
*  may need to override these pointers in order to link itself into the chain
*  of drawing routines.
*  However, the API tables may of course be constants.
*
*/
const tLCDDEV_APIList * LCD_aAPI[] = {
  &LCD_L0_APIList
#if GUI_NUM_LAYERS > 1
  ,&LCD_L0_1_APIList
#endif
#if GUI_NUM_LAYERS > 2
  ,&LCD_L0_2_APIList
#endif
#if GUI_NUM_LAYERS > 3
  ,&LCD_L0_3_APIList
#endif
#if GUI_NUM_LAYERS > 4
  ,&LCD_L0_4_APIList
#endif
#if GUI_NUM_LAYERS > 5
  ,&LCD_L0_5_APIList
#endif
};

/*************************** End of file ****************************/

