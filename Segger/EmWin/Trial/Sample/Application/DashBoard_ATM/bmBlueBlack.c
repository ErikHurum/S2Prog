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
File        : bmBlueBlack.c
Purpose     : Bitmap file
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include "GUI.h"

static GUI_CONST_STORAGE unsigned short acBlueBlack[] = {
  0x7C00,  0x7C00,  0x7C00,  0x7C00,  0x7C00,  0x7C00,  0x7C00,  0x7C00,  0x7C00,  0x7C00,  0x7C00,  0x7C00,  0x7C00,  0x7C00,  0x7800,  0x7800,  0x7800,  0x7800,  0x7800,  0x7800,  0x7800,  0x7800,  0x7800,  0x7800,
  0x7800,  0x7800,  0x7800,  0x7800,  0x7800,  0x7800,  0x7400,  0x7400,  0x7400,  0x7400,  0x7400,  0x7400,  0x7400,  0x7400,  0x7400,  0x7400,  0x7400,  0x7400,  0x7400,  0x7400,  0x7400,  0x7000,  0x7000,  0x7000,
  0x7000,  0x7000,  0x7000,  0x7000,  0x7000,  0x7000,  0x7000,  0x7000,  0x7000,  0x7000,  0x7000,  0x6C00,  0x6C00,  0x6C00,  0x6C00,  0x6C00,  0x6C00,  0x6C00,  0x6C00,  0x6C00,  0x6C00,  0x6C00,  0x6C00,  0x6C00,
  0x6C00,  0x6C00,  0x6C00,  0x6800,  0x6800,  0x6800,  0x6800,  0x6800,  0x6800,  0x6800,  0x6800,  0x6800,  0x6800,  0x6800,  0x6800,  0x6800,  0x6800,  0x6800,  0x6400,  0x6400,  0x6400,  0x6400,  0x6400,  0x6400,
  0x6400,  0x6400,  0x6400,  0x6400,  0x6400,  0x6400,  0x6400,  0x6400,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,  0x6000,
  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5C00,  0x5800,  0x5800,  0x5800,  0x5800,  0x5800,  0x5800,  0x5800,  0x5800,  0x5800,
  0x5800,  0x5800,  0x5800,  0x5800,  0x5800,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5400,  0x5000,  0x5000,  0x5000,
  0x5000,  0x5000,  0x5000,  0x5000,  0x5000,  0x5000,  0x5000,  0x5000,  0x5000,  0x5000,  0x5000,  0x5000,  0x4C00,  0x4C00,  0x4C00,  0x4C00,  0x4C00,  0x4C00,  0x4C00,  0x4C00,  0x4C00,  0x4C00,  0x4C00,  0x4C00,
  0x4C00,  0x4C00,  0x4800,  0x4800,  0x4800,  0x4800,  0x4800,  0x4800,  0x4800,  0x4800,  0x4800,  0x4800,  0x4800,  0x4800,  0x4800,  0x4800,  0x4800,  0x4400,  0x4800,  0x4400,  0x4400,  0x4400,  0x4400,  0x4400,
  0x4400,  0x4400,  0x4400,  0x4400,  0x4400,  0x4400,  0x4400,  0x4400,  0x4400,  0x4000,  0x4000,  0x4000,  0x4000,  0x4000,  0x4000,  0x4000,  0x4000,  0x4000,  0x4000,  0x4000,  0x4000,  0x4000,  0x4000,  0x3C00,
  0x4000,  0x3C00,  0x3C00,  0x3C00,  0x3C00,  0x3C00,  0x3C00,  0x3C00,  0x3C00,  0x3C00,  0x3C00,  0x3C00,  0x3C00,  0x3C00,  0x3800,  0x3800,  0x3800,  0x3800,  0x3800,  0x3800,  0x3800,  0x3800,  0x3800,  0x3800,
  0x3800,  0x3800,  0x3800,  0x3800,  0x3800,  0x3800,  0x3400,  0x3400,  0x3400,  0x3400,  0x3400,  0x3400,  0x3400,  0x3400,  0x3400,  0x3400,  0x3400,  0x3400,  0x3400,  0x3400,  0x3000,  0x3000,  0x3000,  0x3000,
  0x3000,  0x3000,  0x3000,  0x3000,  0x3000,  0x3000,  0x3000,  0x3000,  0x3000,  0x3000,  0x3000,  0x3000,  0x2C00,  0x2C00,  0x2C00,  0x2C00,  0x2C00,  0x2C00,  0x2C00,  0x2C00,  0x2C00,  0x2C00,  0x2C00,  0x2C00,
  0x2C00,  0x2C00,  0x2C00,  0x2C00,  0x2800,  0x2800,  0x2800,  0x2800,  0x2800,  0x2800,  0x2800,  0x2800,  0x2800,  0x2800,  0x2800,  0x2800,  0x2800,  0x2800,  0x2800,  0x2400,  0x2400,  0x2400,  0x2400,  0x2400,
  0x2400,  0x2400,  0x2400,  0x2400,  0x2400,  0x2400,  0x2400,  0x2400,  0x2400,  0x2000,  0x2000,  0x2000,  0x2000,  0x2000,  0x2000,  0x2000,  0x2000,  0x2000,  0x2000,  0x2000,  0x2000,  0x2000,  0x2000,  0x2000,
  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1C00,  0x1800,  0x1800,  0x1800,  0x1800,  0x1800,  0x1800,  0x1800,  0x1800,
  0x1800,  0x1800,  0x1800,  0x1800,  0x1800,  0x1800,  0x1400,  0x1400,  0x1400,  0x1400,  0x1400,  0x1400,  0x1400,  0x1400,  0x1400,  0x1400,  0x1400,  0x1400,  0x1400,  0x1400,  0x1000,  0x1400,  0x1000,  0x1000,
  0x1000,  0x1000,  0x1000,  0x1000,  0x1000,  0x1000,  0x1000,  0x1000,  0x1000,  0x1000,  0x1000,  0x1000,  0x1000,  0x0C00,  0x0C00,  0x0C00,  0x0C00,  0x0C00,  0x0C00,  0x0C00,  0x0C00,  0x0C00,  0x0C00,  0x0C00,
  0x0C00,  0x0C00,  0x0C00,  0x0C00,  0x0800,  0x0800,  0x0800,  0x0800,  0x0800,  0x0800,  0x0800,  0x0800,  0x0800,  0x0800,  0x0800,  0x0800,  0x0800,  0x0800,  0x0400,  0x0400,  0x0400,  0x0400,  0x0400,  0x0400,
  0x0400,  0x0400,  0x0400,  0x0400,  0x0400,  0x0400,  0x0400,  0x0400,  0x0400,  0x0400,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000
};

GUI_CONST_STORAGE GUI_BITMAP bmBlueBlack = {
  1, /* XSize */
  480, /* YSize */
  2, /* BytesPerLine */
  16, /* BitsPerPixel */
  (unsigned char *)acBlueBlack,  /* Pointer to picture data */
  NULL  /* Pointer to palette */
 ,GUI_DRAW_BMP555
};
