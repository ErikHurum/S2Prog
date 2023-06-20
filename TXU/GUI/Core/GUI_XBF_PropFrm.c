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
File        : GUI_XBF_PropFrm.c
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
  GUI_DRAWMODE OldDrawMode;
  LCD_PIXELINDEX OldIndex;
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
  /*
   * Set drawmode to transparent and draw the character using the foreground color
   */
  OldDrawMode  = LCD_SetDrawMode(GUI_TM_TRANS | (GUI_Context.TextMode & GUI_TM_REV));
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
   * Draw the frame using the background color
   */
  OldIndex = LCD_COLORINDEX;
  LCD_COLORINDEX = LCD_BKCOLORINDEX;
  LCD_DrawBitmap(GUI_Context.DispPosX + xOff, GUI_Context.DispPosY + yOff,
                 XSize,
								 YSize,
                 GUI_Context.pAFont->XMag,
								 GUI_Context.pAFont->YMag,
                 1,
                 BytesPerLine,
                 pBuffer + BytesPerLine * YSize,
                 &LCD_BKCOLORINDEX);
  /*
   * Restore colors and dramode and adjust cursor position
   */
  LCD_COLORINDEX = OldIndex;
  LCD_SetDrawMode(OldDrawMode);
  GUI_Context.DispPosX += xDist;
}

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_XBF_TYPE_PROP_FRM
*/
const tGUI_XBF_APIList GUI_XBF_APIList_Prop_Frm = {
  _DispChar,
  GUI_XBF__GetCharDistX,
  GUI_XBF__GetFontInfo,
  GUI_XBF__IsInFont,
};

#else

void GUI_XBF_PropFrm_C(void);
void GUI_XBF_PropFrm_C(void) {} /* Avoid empty object files */

#endif

/*************************** End of file ****************************/
