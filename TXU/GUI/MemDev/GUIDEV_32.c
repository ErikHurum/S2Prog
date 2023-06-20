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
File        : GUIDEV_32.c
Purpose     : Implementation of memory devices
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>
#include "GUI_Private.h"
#include "GUIDebug.h"
#if GUI_WINSUPPORT
  #include "WM.h"
#endif

/* Memory device capabilities are compiled only if support for them is enabled.*/ 
#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       Macros
*
**********************************************************************
*/

#define PIXELINDEX                      U32
#define BITSPERPIXEL                     32
#define API_LIST      GUI_MEMDEV__APIList32

/*********************************************************************
*
*       _DrawBitLine32BPP_DDB
*/
static void _DrawBitLine32BPP_DDB(GUI_USAGE * pUsage, int x, int y, const U32 * pSrc, int xsize, PIXELINDEX * pDest) {
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    GUI_MEMCPY(pDest, pSrc, xsize * 4);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
      if (*pSrc) {
        *pDest = *pSrc;
        if (pUsage) {
          GUI_USAGE_AddPixel(pUsage, x, y);
        }
      }
      x++;
      pDest++;
      pSrc++;
    } while (--xsize);
    break;
  }
}

/*********************************************************************
*
*       #include GUIDev code
*
**********************************************************************
*
* The main code is in an other "C" file.
* This has been done to avoid duplication of code.
*/
#include "GUIDEV_8.c"

#else

void GUIDEV_32_C(void);
void GUIDEV_32_C(void) {}

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
