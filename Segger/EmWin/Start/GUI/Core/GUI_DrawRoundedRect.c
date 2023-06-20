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
File        : GUI_DrawRoundedRect.c
Purpose     : Implementation of GUI_DrawRoundedRect
---------------------------END-OF-HEADER------------------------------
*/

#include <math.h>

#include "GUI_Private.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawRoundedRect
*/
static void _DrawRoundedRect(int x0, int y0, int x1, int y1, int r) {
  I32 rr;
  int i, y, ye, x, xs, xe, l, xOld;

  if (((y1 - y0 + 1) >= (r << 1)) && ((x1 - x0 + 1) >= (r << 1))) {
    rr = (I32)r * r;
    y  = r;
    xOld = -1;
    for (i = y0; i <= (y0 + r); i++, y--, xOld = x) {
      x = (int)sqrt((float)(rr - (I32)y * y));
      xs = x0 + r - x;
      xe = x1 - r + x;
      ye = y1 - (i - y0);
      l = x - xOld;
      if (l > 1) {
        LCD_DrawHLine(xs,          i, xs + l - 1);
        LCD_DrawHLine(xe - l + 1,  i, xe        );
        LCD_DrawHLine(xs,         ye, xs + l - 1);
        LCD_DrawHLine(xe - l + 1, ye, xe        );
      } else {
        LCD_DrawPixel(xs,  i);
        LCD_DrawPixel(xe,  i);
        LCD_DrawPixel(xs, ye);
        LCD_DrawPixel(xe, ye);
      }
    }
    LCD_DrawHLine(x0 + r + 1, y0, x1 - r - 1);
    LCD_DrawHLine(x0 + r + 1, y1, x1 - r - 1);
    LCD_DrawVLine(x0, y0 + r + 1, y1 - r - 1);
    LCD_DrawVLine(x1, y0 + r + 1, y1 - r - 1);
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
*       GUI_DrawRoundedRect
*/
void GUI_DrawRoundedRect(int x0, int y0, int x1, int y1, int r) {
  #if (GUI_WINSUPPORT)
    GUI_RECT Rect;
  #endif
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    WM_ADDORG(x1,y1);
    Rect.x0 = x0; Rect.x1 = x1;
    Rect.y0 = y0; Rect.y1 = y1;
    WM_ITERATE_START(&Rect); {
  #endif
  _DrawRoundedRect(x0, y0, x1, y1, r);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

/*************************** End of file ****************************/
