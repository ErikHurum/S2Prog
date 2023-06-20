/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*
* C-file generated by
*
*        Bitmap converter for emWin V3.78.
*        Compiled Apr 30 2004, 16:45:20
*        (C) 1998 - 2004 Segger Microcontroller Systeme GmbH
*
**********************************************************************
*
* Source file: Ariston_logo2_small
* Dimensions:  98 * 40
* NumColors:   16
*
**********************************************************************
*/

#include "stdlib.h"

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

/*   Palette
The following are the entries of the palette table.
Every entry is a 32-bit value (of which 24 bits are actually used)
the lower   8 bits represent the Red component,
the middle  8 bits represent the Green component,
the highest 8 bits (of the 24 bits used) represent the Blue component
as follows:   0xBBGGRR
*/

static GUI_CONST_STORAGE GUI_COLOR ColorsAriston_logo2_small[] = {
     0xFFFFFF,0x000080,0x008000,0x008080
    ,0x800000,0x800080,0x808000,0x808080
    ,0xC0C0C0,0x0000FF,0x00FF00,0x00FFFF
    ,0xFF0000,0xFF00FF,0xFFFF00,0x000000
};

static GUI_CONST_STORAGE GUI_LOGPALETTE PalAriston_logo2_small = {
  16,	/* number of entries */
  1, 	/* Has transparency */
  &ColorsAriston_logo2_small[0]
};

static GUI_CONST_STORAGE unsigned char acAriston_logo2_small[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x88, 0xBB, 0xBB, 0xBB, 0xBB, 0xB8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x88, 0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x88, 0x88, 0x88, 0x80, 0x00, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0x88, 0x88, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xB8, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x88, 0x88, 0x88, 0x88, 0x88, 0xBB, 0xBB, 0xBB, 0xB8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x88, 0x80, 0x00, 0x00, 0x00, 0x08, 0x88, 0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0xB8, 0x88, 0x88, 0x00, 0x00, 0x08, 0x88, 0x88, 0x88, 0x88, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xB8, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xB8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x88, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x88, 0x80, 0x00, 0x00, 0x08, 0x88, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x88, 0x88, 0x88, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x88, 0x00, 0x00, 0x00, 0x00, 0x08, 0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0x88, 0x00, 0x00, 0x00, 0x88, 0x8B, 0xBB, 0xBB, 0xBB, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x88, 0x00, 0x00, 0x00, 0x00, 0x08, 0x8B, 0xBB, 0xBB, 0xBB, 0xB8, 0x80, 0x00, 0x00, 0x08, 0x8B, 0xBB, 0xBB, 0xBB, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xBB, 0xBB, 0xBB, 0xB8, 0x80, 0x00, 0x00, 0x08, 0x8B, 0xBB, 0xBB, 0xB8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0xBB, 0xBB, 0x88, 0x00, 0x00, 0x00, 0x88, 0xBB, 0xBB, 0xB8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x8B, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0B, 0xBB, 0xBB, 0xBB, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x8B, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xBB, 0xBB, 0xBB, 0xB0, 0x00, 0x00, 0x00, 0x0B, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0B, 0xBB, 0xBB, 0xBB, 0xBB, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0xBB, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0xBB, 0xB0, 0x00, 0x00, 0x00, 0x0B, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x0B, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xBB, 0xBB, 0xBB, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x0B, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x8B, 0xBB, 0xBB, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x0B, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0B, 0xBB, 0xBB, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0xBB, 0xB0, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x08, 0xBB, 0xBB, 0xBB, 0xBB, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xBB, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xBB, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x8B, 0xBB, 0xBB, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xBB, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x08, 0xBB, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xBB, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xBB, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x08, 0x8B, 0xB8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0xB8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x88, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xBB, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xBB, 0xBB, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x88, 0x80, 0x00, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBB, 0xBB, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x8B, 0xBB, 0xBB, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0xB8, 0x00, 0x00, 0x00, 0x0B, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xBB, 0xBB, 0xBB, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xB8, 0xBB, 0x00, 0x00, 0x08, 0x00, 0x00, 0x08, 0x80, 0x00, 0x8B, 0x80, 0x00, 0x08, 0x80, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x8B, 0xBB, 0xBB, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xB0, 0xBB, 0x00, 0xBB, 0xBB, 0x0B, 0xB0, 0xBB, 0xBB, 0x80, 0xBB, 0xBB, 0x08, 0xBB, 0xBB, 0x00, 0xBB, 0xBB, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x8B, 0xBB, 0xBB, 0x88, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xB0, 0x8B, 0x80, 0xBB, 0x0B, 0x8B, 0xB0, 0xB8, 0x08, 0x00, 0x8B, 0x00, 0x0B, 0xB0, 0x0B, 0x80, 0xB8, 0x0B, 0xB0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xB8, 0x8B, 0x80, 0xBB, 0x00, 0x0B, 0xB0, 0x8B, 0xBB, 0xB0, 0x8B, 0x00, 0x0B, 0xB0, 0x0B, 0x80, 0xB8, 0x0B, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x88, 0x8B, 0xB0, 0xBB, 0x00, 0x0B, 0xB0, 0x88, 0x08, 0xB0, 0x8B, 0x0B, 0x88, 0xB0, 0x8B, 0x80, 0xB8, 0x0B, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0x00, 0x0B, 0xB0, 0xBB, 0x00, 0x0B, 0xB0, 0xBB, 0xBB, 0x80, 0x8B, 0xBB, 0x08, 0xBB, 0xBB, 0x00, 0xB8, 0x0B, 0xB0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x80, 0x70, 0x00, 0x08, 0x88, 0x00, 0x08, 0x88, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x88, 0x00, 0x00, 0x00, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x00, 0x70, 0x07, 0x00, 0x07, 0x00, 0x80, 0x07, 0x07, 0x87, 0x00, 0x08, 0x88, 0x70, 0x00, 0x70, 0x70,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x08, 0x70, 0x00, 0x88, 0x87, 0x00, 0x07, 0x00, 0x00, 0x00, 0x70, 0x78, 0x00, 0x07, 0x00, 0x70, 0x00, 0x87, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x87, 0x00
};

GUI_CONST_STORAGE GUI_BITMAP bmAriston_logo_small = {
  98, /* XSize */
  40, /* YSize */
  49, /* BytesPerLine */
  4, /* BitsPerPixel */
  acAriston_logo2_small,  /* Pointer to picture data (indices) */
  &PalAriston_logo2_small  /* Pointer to palette */
};

/* *** End of file *** */
