/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2009  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.00 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_SetTextStyle.C
Purpose     : Implementation of various text styles
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__cbDrawTextStyle
*/
static void GUI__cbDrawTextStyle(U16 Char) {
  int x0, x1;
  x1 = GUI_Context.DispPosX - 1;
  x0 = x1 - GUI_Context.pAFont->pfGetCharDistX(Char) + 1;
  /* Handle Underline */
  if (GUI_Context.TextStyle & GUI_TS_UNDERLINE) {
    int yOff = GUI_Context.pAFont->Baseline;
    if (yOff >= GUI_Context.pAFont->YSize) {
      yOff = GUI_Context.pAFont->YSize - 1;
    }
    LCD_DrawHLine(x0, GUI_Context.DispPosY + yOff, x1);
  }
  /* Handle strike thru */
  if (GUI_Context.TextStyle & GUI_TS_STRIKETHRU) {
    int yOff = GUI_Context.pAFont->Baseline - ((GUI_Context.pAFont->CHeight + 1) / 2);
    LCD_DrawHLine(x0, GUI_Context.DispPosY + yOff, x1);
  }
  /* Handle over line */
  if (GUI_Context.TextStyle & GUI_TS_OVERLINE) {
    int yOff = GUI_Context.pAFont->Baseline - GUI_Context.pAFont->CHeight - 1;
    if (yOff < 0) {
      yOff = 0;
    }
    LCD_DrawHLine(x0, GUI_Context.DispPosY + yOff, x1);
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_SetTextStyle
*/
char GUI_SetTextStyle(char Style) {
  char OldStyle;
  GUI_LOCK();
  OldStyle = GUI_Context.TextStyle;
  GUI_pfDispCharStyle = GUI__cbDrawTextStyle;    /* Init function pointer (function in this module) */
  GUI_Context.TextStyle = Style;
  GUI_UNLOCK();
  return OldStyle;
}

/*************************** End of file ****************************/
