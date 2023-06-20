/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2007  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.14 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDP0.C
Purpose     : Color conversion routines for LCD-drivers
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Private.h"    /* inter modul definitions */
#include "GUI.h"

/*********************************************************************
*
*       Public code, 1/2/4/8 bpp color, LUT
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_0
*/
unsigned LCD_Color2Index_0(LCD_COLOR Color, const LCD_PHYSPALETTE* pPhysPal) {
  int i;
  int NumEntries;
  int BestIndex;
  U32 Diff;
  U32 BestDiff;
  const LCD_COLOR* pPalEntry;
  
  NumEntries = pPhysPal->NumEntries;
  BestIndex  = 0;
  BestDiff   = 0xffffff;  /* Initialize to worst match */
/* Try to find perfect match */
  i = 0; pPalEntry = &pPhysPal->pPalEntries[0];
  do {
	  if (Color == (*(pPalEntry + i) /*& 0xffffff*/)) {
	    return i;
    }
  } while (++i < NumEntries);
/* Find best match */
  i = 0; pPalEntry = &pPhysPal->pPalEntries[0];
  do {
    Diff = GUI_CalcColorDist(Color, *(pPalEntry + i) /*& 0xffffff*/);
    if (Diff < BestDiff) {
      BestDiff  = Diff;
      BestIndex = i;
    }
  } while (++i < NumEntries);
  return BestIndex;
}

/*********************************************************************
*
*       LCD_Index2Color_0
*/
LCD_COLOR LCD_Index2Color_0(int Index, const LCD_PHYSPALETTE* pPhysPal) {
  if ((unsigned)Index >= (unsigned) pPhysPal->NumEntries) {
    return 0;     /* Illegal index */
  }
  return *(pPhysPal->pPalEntries+Index);
}

/*********************************************************************
*
*       LCD_GetIndexMask_0
*/
unsigned LCD_GetIndexMask_0(void) {
  return ((unsigned)(1 << LCD_BITSPERPIXEL) - 1);
}

/*************************** End of file ****************************/
