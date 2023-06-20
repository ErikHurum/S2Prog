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
File        : GUI_XBF_PropExt.c
Purpose     : Implementation of external binary fonts
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#include "GUI_Private.h"

#if GUI_COMPILER_SUPPORTS_FP

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DispChar
*/
static void _DispChar(U16P c) {
  GUI_DRAWMODE DrawMode;
  GUI_DRAWMODE OldDrawMode;
  U8 aBuffer[GUI_MAX_XBF_BYTES];
  const U8 * pBuffer;
  const GUI_XBF_DATA * pXBF_Data;
  U32 Off;
  U16 Size;
  U16 XSize, YSize;
  U16 BytesPerLine;
  U16 xDist, xOff, yOff;

  pBuffer = aBuffer;
  pXBF_Data = (const GUI_XBF_DATA *)GUI_Context.pAFont->p.pFontData;
  if ((c < pXBF_Data->First) || (c > pXBF_Data->Last)) {
    return;
  }
  GUI_XBF__GetOffAndSize(pXBF_Data, c, &Off, &Size); /* Get offset and size of character data */
  if (!Off) {
    return;
  }
  if (Size > GUI_MAX_XBF_BYTES) {
    GUI_DEBUG_ERROROUT("GUI_XBF_Prop.c: Character buffer size too small");
    return;
  }
  pBuffer = aBuffer;
  pXBF_Data->pfGetData(Off, Size, pXBF_Data->pVoid, aBuffer); /* Get character data */
  xDist        = GUI__Read16(&pBuffer);
  XSize        = GUI__Read16(&pBuffer);
  YSize        = GUI__Read16(&pBuffer);
  xOff         = GUI__Read16(&pBuffer);
  yOff         = GUI__Read16(&pBuffer);
  BytesPerLine = GUI__Read16(&pBuffer);
  DrawMode     = GUI_Context.TextMode;
  OldDrawMode  = LCD_SetDrawMode(DrawMode);
  LCD_DrawBitmap(GUI_Context.DispPosX + xOff, GUI_Context.DispPosY + yOff,
                 XSize,
								 YSize,
                 GUI_Context.pAFont->XMag,
								 GUI_Context.pAFont->YMag,
                 1,
                 BytesPerLine,
                 pBuffer,
                 &LCD_BKCOLORINDEX);
  /*
   * Fill empty pixel lines
   */
  if ((DrawMode & LCD_DRAWMODE_TRANS) == 0) {
    if (GUI_Context.pAFont->YDist > GUI_Context.pAFont->YSize) {
      int YMag  = GUI_Context.pAFont->YMag;
      int YDist = GUI_Context.pAFont->YDist * YMag;
      int YSize = GUI_Context.pAFont->YSize * YMag;
      LCD_COLOR OldColor = GUI_GetColor();
      GUI_SetColor(GUI_GetBkColor());
      LCD_FillRect(GUI_Context.DispPosX,
                   GUI_Context.DispPosY + YSize,
                   GUI_Context.DispPosX + XSize,
                   GUI_Context.DispPosY + YDist);
      GUI_SetColor(OldColor);
    }
  }
  /*
   * Restore dramode and adjust cursor position
   */
  LCD_SetDrawMode(OldDrawMode);
  GUI_Context.DispPosX += xDist;
}

/*********************************************************************
*
*       _ClearLine
*/
static void _ClearLine(const char GUI_UNI_PTR * s, int Len) {
  U16 c;
  I16 XDist;
  int yDist, DispPosX, DispPosY;
  LCD_COLOR OldColor;
  OldColor = GUI_GetColor();
  GUI_SetColor((GUI_Context.TextMode & GUI_TM_REV) ? GUI_GetColor() : GUI_GetBkColor());
  yDist    = GUI_Context.pAFont->YDist * GUI_Context.pAFont->YMag;
  DispPosX = GUI_Context.DispPosX;
  DispPosY = GUI_Context.DispPosY;
  XDist    = 0;
  while (--Len >= 0) {
    c = GUI_UC__GetCharCodeInc(&s);
    XDist += GUI_XBF__GetCharDistX(c);
  }
  XDist += GUI__GetOverlap(c);
  LCD_FillRect(DispPosX, 
               DispPosY, 
               DispPosX + XDist, 
               DispPosY + yDist);
  GUI_SetColor(OldColor);
}

/*********************************************************************
*
*       _DispLine
*/
static void _DispLine(const char GUI_UNI_PTR * s, int Len) {
  GUIPROP_EXT__SetfpClearLine(_ClearLine);
  GUI_ENC_APIList_EXT.pfDispLine(s, Len);
  GUIPROP_EXT__SetfpClearLine(GUIPROP_EXT__ClearLine);
}

/*********************************************************************
*
*       _APIList
*/
static const tGUI_ENC_APIList _APIList = {
  NULL,
  NULL,
  _DispLine
};

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_XBF_TYPE_PROP_EXT
*/
const tGUI_XBF_APIList GUI_XBF_APIList_Prop_Ext = {
  _DispChar,
  GUI_XBF__GetCharDistX,
  GUI_XBF__GetFontInfo,
  GUI_XBF__IsInFont,
  GUI_XBF__GetCharInfo,
  &_APIList
};

#else

void GUI_XBF_PropExt_C(void);
void GUI_XBF_PropExt_C(void) {} /* Avoid empty object files */

#endif

/*************************** End of file ****************************/
