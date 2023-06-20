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
File        : GUIPolyR.c
Purpose     : Polygon rotation
----------------------------------------------------------------------
*/

#include <math.h>
#include "GUI.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_RotatePolygon
*/
void GUI_RotatePolygon(GUI_POINT* pDest, const GUI_POINT* pSrc, int NumPoints, float Angle) {
  int j;
  float fcos = cos(Angle);
  float fsin = sin(Angle);
  for (j=0; j<NumPoints; j++) {
    int x = (pSrc+j)->x;
    int y = (pSrc+j)->y;
    (pDest+j)->x =  x * fcos + y * fsin;
    (pDest+j)->y = -x * fsin + y * fcos;
  }
}

/*************************** End of file ****************************/
