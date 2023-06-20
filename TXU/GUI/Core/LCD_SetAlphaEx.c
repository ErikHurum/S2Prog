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
File        : LCD_SetAlphaEx.c
Purpose     : Setting the alpha blending factor of a layer
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* Needed for definition of NULL */
#include "LCD_Private.h"      /* Private modul definitions & config */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_SetAlphaEx
*/
int LCD_SetAlphaEx(int Alpha, int LayerIndex) {
  void (* pfSetAlpha)(int);
  if (LayerIndex == 0) {
    pfSetAlpha = (void (*)(int))LCD_L0_GetDevFunc(LCD_DEVFUNC_SETALPHA);
  }
  #if GUI_NUM_LAYERS > 1
    if (LayerIndex == 1) {
      pfSetAlpha = (void (*)(int))LCD_L0_1_GetDevFunc(LCD_DEVFUNC_SETALPHA);
    }
  #endif
  #if GUI_NUM_LAYERS > 2
    if (LayerIndex == 2) {
      pfSetAlpha = (void (*)(int))LCD_L0_2_GetDevFunc(LCD_DEVFUNC_SETALPHA);
    }
  #endif
  #if GUI_NUM_LAYERS > 3
    if (LayerIndex == 3) {
      pfSetAlpha = (void (*)(int))LCD_L0_3_GetDevFunc(LCD_DEVFUNC_SETALPHA);
    }
  #endif
  #if GUI_NUM_LAYERS > 4
    if (LayerIndex == 4) {
      pfSetAlpha = (void (*)(int))LCD_L0_4_GetDevFunc(LCD_DEVFUNC_SETALPHA);
    }
  #endif
  #if GUI_NUM_LAYERS > 5
    if (LayerIndex == 5) {
      pfSetAlpha = (void (*)(int))LCD_L0_5_GetDevFunc(LCD_DEVFUNC_SETALPHA);
    }
  #endif
  if (pfSetAlpha != NULL) {
    pfSetAlpha(Alpha);
  }
  return 0;
}

/*************************** End of file ****************************/
