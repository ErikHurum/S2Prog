/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*
* C-file generated by
*
*        Bitmap converter for emWin V5.02c.
*        Compiled Jul 28 2009, 16:19:51
*        (C) 1998 - 2005 Segger Microcontroller Systeme GmbH
*
**********************************************************************
*
* Source file: ButtonTankwash
* Dimensions:  32 * 32
* NumColors:   16
*
**********************************************************************
*/

#include <stdlib.h>

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

static GUI_CONST_STORAGE GUI_COLOR ColorsButtonTankwash[] = {
        0xFF00FF,0x000080,0x008000,0x008080
    ,0x800000,0x800080,0x808000,0x808080
    ,0xC0C0C0,0x0000FF,0x00FF00,0x00FFFF
    ,0xFF0000,0x000000,0xFFFF00,0xFFFFFF
};

static GUI_CONST_STORAGE GUI_LOGPALETTE PalButtonTankwash = {
    16,	/* number of entries */
    1, 	/* Has transparency */
    &ColorsButtonTankwash[0]
};

static GUI_CONST_STORAGE unsigned char acButtonTankwash[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xDD, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDE, 0x8E, 0x8E, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD8, 0xE8, 0xE8, 0xE8, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDE, 0x8E, 0x8E, 0x8E, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xDD, 0xDD, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0x88, 0x88, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDF, 0xFF, 0xFD, 0x88, 0x88, 0xDF, 0xFF, 0xFF, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDF, 0xFF, 0xFD, 0x88, 0x88, 0xDF, 0xFF, 0xFF, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDF, 0xFF, 0xFD, 0x88, 0x88, 0xDF, 0xFF, 0xFF, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xD8, 0x8D, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xD8, 0x8D, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xD8, 0x8D, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xD8, 0x8D, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xD8, 0x8D, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xD8, 0x8D, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xD8, 0x8D, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xD8, 0x8D, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xD8, 0x8D, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xD8, 0x8D, 0xDD, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xD8, 0x88, 0x88, 0xDC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCD, 0xDD, 0xDD, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDF, 0xFF, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDF, 0xFF, 0xD0, 0x00,
    0x00, 0x00, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xD0, 0x00,
    0x00, 0x00, 0x0D, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDD, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xD0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static GUI_CONST_STORAGE GUI_BITMAP bmButtonTankwash = {
    32, /* XSize */
    32, /* YSize */
    16, /* BytesPerLine */
    4, /* BitsPerPixel */
    acButtonTankwash,  /* Pointer to picture data (indices) */
    &PalButtonTankwash  /* Pointer to palette */
};
    

/* *** End of file *** */