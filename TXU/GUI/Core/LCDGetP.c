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
File        : LCDGetP.c
Purpose     : Get Pixel routines
              Note: These routines are in a module of their own
                    because they are mostly not required to link
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"
#include "GUIDebug.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_GetPixelIndex
*
* NOTE:
*   We can not use the standard clipping which we use for drawing
*   operations as it is perfectly legal to read pixels outside of
*   the clipping area. We therefor get the bounding rectangle of the
*   device and use it for clipping.
*/
unsigned LCD_GetPixelIndex(int x, int y)  {
  LCD_RECT r;  
  GUI_ASSERT_LOCK();
  LCDDEV_L0_GetRect(&r);
  if (x < r.x0) {
    return 0;
  }
  if (x > r.x1) {
    return 0;
  }
  if (y < r.y0) {
    return 0;
  }
  if (y > r.y1) {
    return 0;
  }
  return LCDDEV_L0_GetPixelIndex(x,y);
}

/*************************** End of file ****************************/
