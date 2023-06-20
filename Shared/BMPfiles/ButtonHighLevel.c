/*
  C-file generated by Bitmap converter for emWin GSC V2.40, compiled Feb  6 2003, 09:35:53

  Copyright (C) 1998-2002
	Segger Microcontroller Systeme GmbH
  www.segger.com

  Solutions for real time microcontroller applications

  Source file: ButtonHighLevel
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

const GUI_COLOR ColorsButtonHighLevel[] = {
     0xFF00FF,0x000080,0x008000,0x008080
    ,0x800000,0x800080,0x808000,0xC0C0C0
    ,0x808080,0x0000FF,0x00FF00,0x00FFFF
    ,0xFF0000,0x000000,0xFFFF00,0xFFFFFF
};

const GUI_LOGPALETTE PalButtonHighLevel = {
  16,	/* number of entries */
  1, 	/* Has transparency */
  &ColorsButtonHighLevel[0]
};

const unsigned char acButtonHighLevel[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xDD, 0xDD, 0xD9, 0x99, 0x99, 0x9D, 0xDD, 0x99, 0x99, 0x99, 0xDD, 0xDD, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xD9, 0x99, 0x99, 0x9D, 0xFD, 0xDD, 0x99, 0x99, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xD9, 0x99, 0x99, 0x9D, 0xDD, 0x99, 0xDD, 0xDD, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xD9, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x9D, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDF, 0xFF, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDF, 0xFF, 0xD0, 0x00,
  0x00, 0x00, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xD0, 0x00,
  0x00, 0x00, 0x0D, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDD, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xD0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const GUI_BITMAP bmButtonHighLevel = {
 32, /* XSize */
 32, /* YSize */
 16, /* BytesPerLine */
 4, /* BitsPerPixel */
 acButtonHighLevel,  /* Pointer to picture data (indices) */
 &PalButtonHighLevel  /* Pointer to palette */
};

/* *** End of file *** */
