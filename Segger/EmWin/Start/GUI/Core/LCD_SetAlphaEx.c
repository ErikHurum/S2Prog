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
File        : LCD_SetAlphaEx.c
Purpose     : Setting the alpha blending factor of a layer
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#include "GUI_Private.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetpFunc
*/
static void * _GetpFunc(int LayerIndex, int Index) {
  void * pFunc = NULL;
  if (LayerIndex == 0) {
    pFunc = LCD_L0_GetDevFunc(Index);
  }
  #if GUI_NUM_LAYERS > 1
    if (LayerIndex == 1) {
      pFunc = LCD_L0_1_GetDevFunc(Index);
    }
  #endif
  #if GUI_NUM_LAYERS > 2
    if (LayerIndex == 2) {
      pFunc = LCD_L0_2_GetDevFunc(Index);
    }
  #endif
  #if GUI_NUM_LAYERS > 3
    if (LayerIndex == 3) {
      pFunc = LCD_L0_3_GetDevFunc(Index);
    }
  #endif
  #if GUI_NUM_LAYERS > 4
    if (LayerIndex == 4) {
      pFunc = LCD_L0_4_GetDevFunc(Index);
    }
  #endif
  #if GUI_NUM_LAYERS > 5
    if (LayerIndex == 5) {
      pFunc = LCD_L0_5_GetDevFunc(Index);
    }
  #endif
  return pFunc;
}

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
  void (* pFunc)(int);
  int r = 1;

  pFunc = (void (*)(int))_GetpFunc(LayerIndex, LCD_DEVFUNC_SETALPHA);
  if (pFunc) {
    pFunc(Alpha);
    r = 0;
  }
  return r;
}

/*********************************************************************
*
*       LCD_SetVRAMAddrEx
*/
int LCD_SetVRAMAddrEx(U32 Addr, int LayerIndex) {
  void (* pFunc)(U32);
  int r = 1;

  pFunc = (void (*)(U32))_GetpFunc(LayerIndex, LCD_DEVFUNC_SET_VRAM_ADDR);
  if (pFunc) {
    pFunc(Addr);
    r = 0;
  }
  return r;
}

/*********************************************************************
*
*       LCD_SetVSizeEx
*/
int LCD_SetVSizeEx(int xSize, int ySize, int LayerIndex) {
  void (* pFunc)(int, int);
  int r = 1;

  pFunc = (void (*)(int, int))_GetpFunc(LayerIndex, LCD_DEVFUNC_SET_VSIZE);
  if (pFunc) {
    pFunc(xSize, ySize);
    r = 0;
  }
  return r;
}

/*********************************************************************
*
*       LCD_SetSizeEx
*/
int LCD_SetSizeEx(int xSize, int ySize, int LayerIndex) {
  void (* pFunc)(int, int);
  int r = 1;

  pFunc = (void (*)(int, int))_GetpFunc(LayerIndex, LCD_DEVFUNC_SET_SIZE);
  if (pFunc) {
    pFunc(xSize, ySize);
    r = 0;
  }
  return r;
}

/*************************** End of file ****************************/
