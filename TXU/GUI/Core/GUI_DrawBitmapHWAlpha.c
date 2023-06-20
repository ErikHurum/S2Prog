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
File        : GUI_DrawBitmap.C
Purpose     : Implementation of GUI_DrawBitmap
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include "GUI_Private.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawBitmapHWAlpha
*/
static void _DrawBitmapHWAlpha(const GUI_BITMAP GUI_UNI_PTR * pBM, int x0, int y0) {
  if (pBM->pMethods) {
    #if GUI_COMPILER_SUPPORTS_FP      /* Do not support this on VERY simple chips and compilers */
      if (pBM->pMethods->pfDrawHW) {
        pBM->pMethods->pfDrawHW(x0, y0, pBM->XSize ,pBM->YSize, (U8 const *)pBM->pData, pBM->pPal, 1, 1);
      }
    #else
      GUI_USE_PARA(x0);
      GUI_USE_PARA(y0);
    #endif
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
*       GUI_DrawBitmapHWAlpha
*/
void GUI_DrawBitmapHWAlpha(const GUI_BITMAP GUI_UNI_PTR * pBM, int x0, int y0) {
  #if (GUI_WINSUPPORT)
    GUI_RECT r;
  #endif
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    r.x1 = (r.x0 = x0) + pBM->XSize-1;
    r.y1 = (r.y0 = y0) + pBM->YSize-1;
    WM_ITERATE_START(&r) {
  #endif
  _DrawBitmapHWAlpha(pBM, x0, y0);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

/*************************** End of file ****************************/
