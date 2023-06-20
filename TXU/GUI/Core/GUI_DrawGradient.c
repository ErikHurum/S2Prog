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
File        : GUI_DrawGradient.c
Purpose     : Drawing of horizontal and vertical color gradients
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawGradient
*/
static void _DrawGradient(int x0, int y0, int x1, int y1, GUI_COLOR Color0, GUI_COLOR Color1, void (* pFunc)(int, int, int), int v) {
  int r0, g0, b0, r1, g1, b1, r, g, b, y, d, ySize;
  GUI_COLOR Color, OldColor;
  ySize = y1 - y0 + 1;
  r0 = (Color0      ) & 0xff;
  g0 = (Color0 >>  8) & 0xff;
  b0 = (Color0 >> 16) & 0xff;
  r1 = (Color1      ) & 0xff;
  g1 = (Color1 >>  8) & 0xff;
  b1 = (Color1 >> 16) & 0xff;
  OldColor = GUI_GetColor();
  for (y = y0; y <= y1; y++) {
    d = (y - y0);
    r = (r0 + ((r1 - r0) * d) / ySize) & 0xff;
    g = (g0 + ((g1 - g0) * d) / ySize) & 0xff;
    b = (b0 + ((b1 - b0) * d) / ySize) & 0xff;
    Color = r | (g << 8) | ((U32)b << 16);
    LCD_SetColor(Color);
    if (v) {
      pFunc(x0, y, x1);
    } else {
      pFunc(y, x0, x1);
    }
  }
  LCD_SetColor(OldColor);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawGradientV
*/
void GUI_DrawGradientV(int x0, int y0, int x1, int y1, GUI_COLOR Color0, GUI_COLOR Color1) {
  #if (GUI_WINSUPPORT)
    GUI_RECT r;
  #endif
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    WM_ADDORG(x1,y1);
    r.x0 = x0;
    r.x1 = x1;
    r.y0 = y0;
    r.y1 = y1;
    WM_ITERATE_START(&r); {
  #endif
  _DrawGradient(x0, y0, x1, y1, Color0, Color1, LCD_DrawHLine, 1);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_DrawGradientH
*/
void GUI_DrawGradientH(int x0, int y0, int x1, int y1, GUI_COLOR Color0, GUI_COLOR Color1) {
  #if (GUI_WINSUPPORT)
    GUI_RECT r;
  #endif
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    WM_ADDORG(x1,y1);
    r.x0 = x0;
    r.x1 = x1;
    r.y0 = y0;
    r.y1 = y1;
    WM_ITERATE_START(&r); {
  #endif
  _DrawGradient(y0, x0, y1, x1, Color0, Color1, LCD_DrawVLine, 0);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

/*************************** End of file ****************************/
