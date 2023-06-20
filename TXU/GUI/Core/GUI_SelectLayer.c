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
File        : GUI_SelectLayer.c.C
Purpose     : Selection of Layer
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static unsigned  _aCursorLayer[GUI_NUM_LAYERS];
static GUI_POINT _aLayerPos[GUI_NUM_LAYERS];

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetDevFunc
*/
static void * _GetDevFunc(int Index, int Func) {
  void * pFunc;
  pFunc = NULL;
  switch (Index) {
  case 0:
    pFunc = (void *)LCD_L0_GetDevFunc  (Func);
    break;
  #if (GUI_NUM_LAYERS > 1)
  case 1:
    pFunc = (void *)LCD_L0_1_GetDevFunc(Func);
    break;
  #endif
  #if (GUI_NUM_LAYERS > 2)
  case 2:
    pFunc = (void *)LCD_L0_2_GetDevFunc(Func);
    break;
  #endif
  #if (GUI_NUM_LAYERS > 3)
  case 3:
    pFunc = (void *)LCD_L0_3_GetDevFunc(Func);
    break;
  #endif
  #if (GUI_NUM_LAYERS > 4)
  case 4:
    pFunc = (void *)LCD_L0_4_GetDevFunc(Func);
    break;
  #endif
  #if (GUI_NUM_LAYERS > 5)
  case 5:
    pFunc = (void *)LCD_L0_5_GetDevFunc(Func);
    break;
  #endif
  }
  return (void *)pFunc;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_SelectLayer
*/
unsigned GUI_SelectLayer(unsigned Index) {
  unsigned OldIndex;
  GUI_LOCK();
  OldIndex = GUI_Context.SelLayer;
  if (Index < GUI_NUM_LAYERS) {
    GUI_Context.SelLayer = Index;
    GUI_SelectLCD();
  }
  GUI_UNLOCK();
  return OldIndex;
}

/*********************************************************************
*
*       GUI_AssignCursorLayer
*/
void GUI_AssignCursorLayer(unsigned Index, unsigned CursorLayer) {
  if (Index < GUI_COUNTOF(_aCursorLayer)) {
    if (_GetDevFunc(Index, LCD_DEVFUNC_SETPOS)) {
      _aCursorLayer[Index] = CursorLayer;
    }
  }
}

/*********************************************************************
*
*       GUI_GetCursorLayer
*/
unsigned GUI_GetCursorLayer(unsigned Index) {
  unsigned r;
  r = 0;
  if (Index < GUI_COUNTOF(_aCursorLayer)) {
    r = _aCursorLayer[Index];
  }
  return r;
}

/*********************************************************************
*
*       GUI_SetLayerPosEx
*/
int GUI_SetLayerPosEx(unsigned Index, int xPos, int yPos) {
  void (* pFunc)(int, int);
  int r;
  r     = 1;
  pFunc = (void (*)(int, int))_GetDevFunc(Index, LCD_DEVFUNC_SETPOS);
  if (pFunc) {
    pFunc(xPos, yPos);
    _aLayerPos[Index].x = (I16)xPos;
    _aLayerPos[Index].y = (I16)yPos;
    r = 0;
  }
  return r;
}

/*********************************************************************
*
*       GUI_GetLayerPosEx
*/
void GUI_GetLayerPosEx(unsigned Index, GUI_POINT * pPos) {
  if (Index < GUI_COUNTOF(_aLayerPos)) {
    *pPos = _aLayerPos[Index];
  }
}

/*********************************************************************
*
*       GUI_SetLayerSizeEx
*/
int GUI_SetLayerSizeEx(unsigned Index, int xSize, int ySize) {
  void (* pFunc)(int, int);
  int r;
  r     = 1;
  pFunc = (void (*)(int, int))_GetDevFunc(Index, LCD_DEVFUNC_SETSIZE);
  if (pFunc) {
    pFunc(xSize, ySize);
    r = 0;
  }
  return r;
}

/*********************************************************************
*
*       GUI_SetLayerVisEx
*/
int GUI_SetLayerVisEx(unsigned Index, int OnOff) {
  void (* pFunc)(int);
  int r;
  r     = 1;
  pFunc = (void (*)(int))_GetDevFunc(Index, LCD_DEVFUNC_SETVIS);
  if (pFunc) {
    pFunc(OnOff);
    r = 0;
  }
  return r;
}

/*********************************************************************
*
*       GUI_SetLayerAlphaEx
*/
int GUI_SetLayerAlphaEx(unsigned Index, int Alpha) {
  void (* pFunc)(int);
  int r;
  r     = 1;
  pFunc = (void (*)(int))_GetDevFunc(Index, LCD_DEVFUNC_SETALPHA);
  if (pFunc) {
    pFunc(Alpha);
    r = 0;
  }
  return r;
}

/*************************** End of file ****************************/
