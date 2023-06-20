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
File        : GUI_SetLUTColor.c
Purpose     : Implementation of GUI_SetLUTColor
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"
#include "LCD_Private.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_SetLUTColor
*/
#if (GUI_NUM_LAYERS == 1)
void GUI_SetLUTColor(U8 Pos, LCD_COLOR Color) {
  #if LCD_PHYSCOLORS_IN_RAM
    GUI_LOCK();
    LCD_PhysColors[Pos] = Color;
    LCD_SetLUTEntry(Pos, Color);
    GUI_UNLOCK();
  #else
    GUI_USE_PARA(Pos);
    GUI_USE_PARA(Color);
  #endif
}
#else

void GUI_SetLUTColor_C(void); /* Avoid empty object files */
void GUI_SetLUTColor_C(void) {}

#endif

/*************************** End of file ****************************/
