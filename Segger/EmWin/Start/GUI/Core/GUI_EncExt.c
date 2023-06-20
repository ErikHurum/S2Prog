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
File        : GUIEncEXT.c
Purpose     : Implementation of extended proportional fonts
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#include "GUI_Private.h"

/*********************************************************************
*
*       Private code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIPROP_EXT__ClearLine
*/
void GUIPROP_EXT__ClearLine(const char GUI_UNI_PTR * s, int Len) {
  U16 Char;
  int xDist, yDist, x0, y0;
  LCD_COLOR OldColor;
  OldColor = GUI_GetColor();
  GUI_SetColor((GUI_Context.TextMode & GUI_TM_REV) ? GUI_GetColor() : GUI_GetBkColor());
  xDist = 0;
  yDist = GUI_Context.pAFont->YDist * GUI_Context.pAFont->YMag;
  x0    = GUI_Context.DispPosX;
  y0    = GUI_Context.DispPosY;
  while (--Len >= 0) {
    const GUI_FONT_PROP_EXT GUI_UNI_PTR * pPropExt;
    const GUI_CHARINFO_EXT  GUI_UNI_PTR * pCharInfo;
    Char      = GUI_UC__GetCharCodeInc(&s);
    pPropExt  = GUIPROP_EXT__FindChar(GUI_Context.pAFont->p.pPropExt, Char);
    if (pPropExt) {
      pCharInfo = pPropExt->paCharInfo + (Char - pPropExt->First);
      xDist += pCharInfo->XDist * GUI_Context.pAFont->XMag;
    }
  }
  xDist += GUI__GetOverlap(Char);
  LCD_FillRect(x0, y0, x0 + xDist - 1, y0 + yDist - 1);
  GUI_SetColor(OldColor);
}

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static void (* _fpClearLine)(const char GUI_UNI_PTR * s, int Len) = GUIPROP_EXT__ClearLine;

/*********************************************************************
*
*       Private code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIPROP_EXT__DispLine
*/
void GUIPROP_EXT__DispLine(const char GUI_UNI_PTR * s, int Len) {
  U16 Char;
  int OldMode;
  /* Clear if not transparency mode has been selected */
  if (!GUI_Context.TextMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    _fpClearLine(s, Len);
  }
  /* Draw characters always transparent */
  OldMode = GUI_Context.TextMode;
  GUI_Context.TextMode |= GUI_TM_TRANS;
  while (--Len >= 0) {
    Char = GUI_UC__GetCharCodeInc(&s);
    GUI_Context.pAFont->pfDispChar(Char);
  }
  GUI_Context.TextMode = OldMode;
}

/*********************************************************************
*
*       GUIPROP_EXT__SetfpClearLine
*/
void GUIPROP_EXT__SetfpClearLine(void (* fpClearLine)(const char GUI_UNI_PTR * s, int Len)) {
  _fpClearLine = fpClearLine;
}

/*********************************************************************
*
*       Public APIList
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_ENC_APIList_EXT, API list
*/
const tGUI_ENC_APIList GUI_ENC_APIList_EXT = {
  NULL,
  NULL,
  GUIPROP_EXT__DispLine
};

/*************************** End of file ****************************/
