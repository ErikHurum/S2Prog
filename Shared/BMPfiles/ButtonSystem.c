/*
  C-file generated by Bitmap converter for emWin GSC V2.40, compiled Feb  6 2003, 09:35:53

  Copyright (C) 1998-2002
	Segger Microcontroller Systeme GmbH
  www.segger.com

  Solutions for real time microcontroller applications

  Source file: ButtonSystem
  Dimensions:  32 * 32
  NumColors:   16
*/

#include "stdlib.h"

#include "GUI.H"

/*   Palette
The following are the entries of the palette table.
Every entry is a 32-bit value (of which 24 bits are actually used)
the lower   8 bits represent the Red component,
the middle  8 bits represent the Green component,
the highest 8 bits (of the 24 bits used) represent the Blue component
as follows:   0xBBGGRR
*/

const GUI_COLOR ColorsButtonSystem[] = {
     0xFF00FF,0x000080,0x008000,0x008080
    ,0x800000,0x800080,0x808000,0x808080
    ,0xC0C0C0,0x0000FF,0x00FF00,0x00FFFF
    ,0xFF0000,0x000000,0xFFFF00,0xFFFFFF
};

const GUI_LOGPALETTE PalButtonSystem = {
  16,	/* number of entries */
  1, 	/* Has transparency */
  &ColorsButtonSystem[0]
};

const unsigned char acButtonSystem[] = {
  0xFD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xDD, 0xDD, 0xDD, 0x00, 0x00,
  0x77, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xDF, 0xFF, 0xFF, 0xFF, 0xD0, 0x00,
  0x07, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDD, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x00,
  0x00, 0x77, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFF, 0xFF, 0xFF, 0x88, 0x88, 0x8D, 0x00,
  0x00, 0x07, 0x8D, 0xD0, 0x00, 0x00, 0x00, 0x0D, 0xFF, 0xFF, 0xFF, 0xF8, 0xDD, 0xDD, 0xDD, 0x00,
  0x00, 0x07, 0x78, 0xDD, 0x00, 0x00, 0x00, 0x0D, 0xFF, 0xDD, 0xDD, 0xF8, 0xDD, 0xDD, 0xD0, 0x00,
  0x00, 0x00, 0x77, 0x8D, 0xD0, 0x00, 0x00, 0x0D, 0xFF, 0xDF, 0xDD, 0xF8, 0xD0, 0x00, 0x0D, 0xD0,
  0x00, 0x00, 0x07, 0x78, 0xDD, 0x00, 0x00, 0x0D, 0xFF, 0xDD, 0xFD, 0xF8, 0xD0, 0x00, 0x0D, 0xD0,
  0x00, 0x00, 0x00, 0x77, 0x8D, 0xD0, 0x00, 0x0D, 0xFF, 0xDF, 0xDF, 0xF8, 0xD0, 0x00, 0xD7, 0xD0,
  0x00, 0x00, 0x00, 0x07, 0x78, 0xDD, 0x00, 0x0D, 0xFF, 0xDD, 0xFF, 0xF8, 0xDD, 0xDD, 0x77, 0xD0,
  0x00, 0x00, 0x00, 0x00, 0x77, 0x8D, 0xD0, 0x0D, 0xFF, 0xDF, 0xDF, 0xF8, 0xD7, 0x77, 0x7D, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x78, 0xD7, 0xDF, 0xFF, 0xDD, 0xFD, 0xF8, 0xD7, 0x77, 0xD8, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x7D, 0xF7, 0xDF, 0xFF, 0xFF, 0xF8, 0xDD, 0xDD, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xDF, 0x78, 0x8D, 0xFF, 0x88, 0x88, 0xD8, 0x88, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xF7, 0x88, 0x8D, 0xF8, 0xDD, 0xDD, 0xD8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0x78, 0x88, 0xDF, 0x7D, 0x77, 0x77, 0xD8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0D, 0xF7, 0x88, 0x8D, 0xF7, 0xD7, 0x77, 0x77, 0xD8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xDF, 0x78, 0x88, 0xDF, 0x7D, 0x77, 0xDD, 0xDD, 0xD8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0D, 0xF7, 0x88, 0x8D, 0xF7, 0xD7, 0x7D, 0x88, 0x88, 0x82, 0xD0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xDF, 0x78, 0x88, 0xDF, 0x7D, 0x77, 0xD8, 0xA2, 0xAD, 0x22, 0x2D, 0x00, 0x00,
  0x00, 0x00, 0x0D, 0xF7, 0x88, 0x8D, 0xF7, 0xD7, 0x7D, 0x8A, 0x2A, 0x2A, 0xD2, 0x22, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0x78, 0x88, 0xDF, 0x7D, 0x77, 0xD8, 0xD2, 0xA2, 0xA2, 0xAD, 0x22, 0x2D, 0x00,
  0x00, 0x0D, 0xF7, 0x88, 0x8D, 0xF7, 0xD7, 0x7D, 0x8A, 0xAD, 0x2A, 0x2A, 0x2A, 0xD2, 0x22, 0xD0,
  0x00, 0xDF, 0x78, 0x88, 0xDF, 0x7D, 0x77, 0xD8, 0xAA, 0xAA, 0xD2, 0xA2, 0xA2, 0xAD, 0x22, 0x2D,
  0x0D, 0xF7, 0x88, 0x8D, 0xF7, 0xD7, 0x7D, 0x80, 0xDA, 0xAA, 0xAD, 0x2A, 0x2A, 0x2A, 0xD2, 0x2D,
  0x0D, 0xF7, 0x88, 0xDF, 0x7D, 0x77, 0xD8, 0x00, 0x0D, 0xAA, 0xAA, 0xD2, 0xA2, 0xA2, 0xDD, 0xDD,
  0x0D, 0xFF, 0x7D, 0xF7, 0xD7, 0x7D, 0x80, 0x00, 0x00, 0xDA, 0xAA, 0xAD, 0x2A, 0x2D, 0x22, 0x2D,
  0x0D, 0xDF, 0xFF, 0x7D, 0x77, 0xD8, 0x00, 0x00, 0x00, 0x0D, 0xAA, 0xAA, 0xD2, 0xD2, 0x22, 0x2D,
  0x0D, 0x7D, 0xDD, 0xD7, 0x7D, 0x80, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xAA, 0xAD, 0x22, 0x22, 0x2D,
  0x0D, 0x77, 0x77, 0x77, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xAA, 0xAD, 0x22, 0x22, 0xD0,
  0x08, 0xD7, 0x77, 0x7D, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDA, 0xAD, 0x22, 0x2D, 0x00,
  0x00, 0x8D, 0xDD, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xDD, 0xDD, 0xD0, 0x00
};

const GUI_BITMAP bmButtonSystem = {
 32, /* XSize */
 32, /* YSize */
 16, /* BytesPerLine */
 4, /* BitsPerPixel */
 acButtonSystem,  /* Pointer to picture data (indices) */
 &PalButtonSystem  /* Pointer to palette */
};

/* *** End of file *** */
