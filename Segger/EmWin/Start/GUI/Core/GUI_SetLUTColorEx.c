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
File        : GUI_SetLUTColorEx.c
Purpose     : Implementation of GUI_SetLUTColorEx
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#include "GUI_Private.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const LCD_LUT_INFO * _apLutInfo[GUI_NUM_LAYERS] = {
  &LCD_L0_LutInfo,
  #if GUI_NUM_LAYERS > 1
    &LCD_L0_1_LutInfo,
  #endif
  #if GUI_NUM_LAYERS > 2
    &LCD_L0_2_LutInfo,
  #endif
  #if GUI_NUM_LAYERS > 3
    &LCD_L0_3_LutInfo,
  #endif
  #if GUI_NUM_LAYERS > 4
    &LCD_L0_4_LutInfo,
  #endif
  #if GUI_NUM_LAYERS > 5
    &LCD_L0_5_LutInfo,
  #endif
};

static void (* _afpSetLUTEntry[GUI_NUM_LAYERS])(U8 Pos, LCD_COLOR Color) = {
  LCD_L0_SetLUTEntry,
  #if GUI_NUM_LAYERS > 1
    LCD_L0_1_SetLUTEntry,
  #endif
  #if GUI_NUM_LAYERS > 2
    LCD_L0_2_SetLUTEntry,
  #endif
  #if GUI_NUM_LAYERS > 3
    LCD_L0_3_SetLUTEntry,
  #endif
  #if GUI_NUM_LAYERS > 4
    LCD_L0_4_SetLUTEntry,
  #endif
  #if GUI_NUM_LAYERS > 5
    LCD_L0_5_SetLUTEntry,
  #endif
};

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_SetLUTColorEx
*/
void GUI_SetLUTColorEx(U8 Pos, LCD_COLOR Color, unsigned int LayerIndex) {
  if (LayerIndex < GUI_NUM_LAYERS) {
    if (Pos < _apLutInfo[LayerIndex]->NumEntries) {
      LCD_aAPI[LayerIndex]->pfSetLUTEntry(Pos, Color);
      _apLutInfo[LayerIndex]->paColor[Pos] = Color;
    }
  }
}

/*********************************************************************
*
*       LCD_SetLUTEntryEx
*/
void LCD_SetLUTEntryEx(U8 Pos, LCD_COLOR Color, unsigned int LayerIndex) {
  if (LayerIndex < GUI_NUM_LAYERS) {
    _afpSetLUTEntry[LayerIndex](Pos, Color);
  }
}

/*************************** End of file ****************************/
