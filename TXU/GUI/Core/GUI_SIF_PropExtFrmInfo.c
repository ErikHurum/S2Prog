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
File        : GUI_SIF_PropExtFrmInfo.c
Purpose     : Implementation of system independend fonts
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
*       GUI_SIF__GetCharDistX_ExtFrm
*/
int GUI_SIF__GetCharDistX_ExtFrm(U16P c) {
  const U8 * pCharInfo;
  I16 DistX = 0;
  pCharInfo = GUI_SIF__GetpCharInfo(GUI_Context.pAFont, c, sizeof(GUI_SIF_CHARINFO_EXT));       /* Get pointer to char info data */
  if (pCharInfo) {
    pCharInfo += 4 * sizeof(U16);                                   /* Skip unused data */
    DistX = GUI__Read16(&pCharInfo);
  }
  return DistX;
}

/*********************************************************************
*
*       _GetFontInfo_ExtFrm
*/
void GUI_SIF__GetFontInfo_ExtFrm(const GUI_FONT GUI_UNI_PTR * pFont, GUI_FONTINFO * pfi) {
  const U8 * pData;
  pData = (const U8 *)pFont->p.pFontData + 4;             /* Skip unused data */
  pfi->Baseline = GUI__Read16(&pData);
  pfi->LHeight  = GUI__Read16(&pData);
  pfi->CHeight  = GUI__Read16(&pData);
  pfi->Flags    = GUI_FONTINFO_FLAG_PROP;
}

/*********************************************************************
*
*       GUI_SIF__IsInFont_ExtFrm
*/
char GUI_SIF__IsInFont_ExtFrm(const GUI_FONT GUI_UNI_PTR * pFont, U16 c) {
  const U8 * pCharInfo;
  GUI_USE_PARA(pFont);
  pCharInfo = GUI_SIF__GetpCharInfo(GUI_Context.pAFont, c, sizeof(GUI_SIF_CHARINFO_EXT));
  return (pCharInfo) ? 1 : 0;
}

/*********************************************************************
*
*       GUI_SIF__GetCharInfo_ExtFrm
*/
int GUI_SIF__GetCharInfo_ExtFrm(U16P c, GUI_CHARINFO_EXT * pInfo) {
  const U8 * pCharInfo;
  pCharInfo = GUI_SIF__GetpCharInfo(GUI_Context.pAFont, c, sizeof(GUI_SIF_CHARINFO_EXT));
  if (pCharInfo) {
    pInfo->XSize = GUI__Read16(&pCharInfo);
    pCharInfo += 3 * sizeof(U16);                                   /* Skip unused data */
    pInfo->XDist = GUI__Read16(&pCharInfo);
    return 0;
  }
  return 1;
}
