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
File        : GUI_XBF.c
Purpose     : Implementation of external binary fonts
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

/*********************************************************************
*
*       Private code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_XBF__GetOff
*/
int GUI_XBF__GetOff(const GUI_XBF_DATA * pXBF_Data, unsigned c, U32 * pOff) {
  c -= pXBF_Data->First;
  if (pXBF_Data->pfGetData(18 + (c << 1) + (c << 2), 4, pXBF_Data->pVoid, pOff)) { /* Get offset of character data */
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       GUI_XBF__GetOffAndSize
*/
int GUI_XBF__GetOffAndSize(const GUI_XBF_DATA * pXBF_Data, unsigned c, U32 * pOff, U16 * pSize) {
  U8 aBuffer[6];
  const U8 * pBuffer;

  pBuffer = aBuffer;
  c -= pXBF_Data->First;
  if (pXBF_Data->pfGetData(18 + (c << 1) + (c << 2), 6, pXBF_Data->pVoid, aBuffer)) { /* Get offset and size of character data */
    return 1;
  }
  *pOff  = GUI__Read32(&pBuffer);
  *pSize = GUI__Read16(&pBuffer);
  return 0;
}

/*********************************************************************
*
*       GUI_XBF__GetCharDistX
*/
int GUI_XBF__GetCharDistX(U16P c) {
  U16 DistX;
  U32 Off;
  const GUI_XBF_DATA * pXBF_Data;

  pXBF_Data = (const GUI_XBF_DATA *)GUI_Context.pAFont->p.pFontData;
  if ((c < pXBF_Data->First) || (c > pXBF_Data->Last)) {
    return 0;
  }
  GUI_XBF__GetOff(pXBF_Data, c, &Off);
  if (!Off) {
    return 0; /* Character not available */
  }
  pXBF_Data->pfGetData(Off, 2, pXBF_Data->pVoid, &DistX);
  return DistX;
}

/*********************************************************************
*
*       GUI_XBF__GetFontInfo
*/
void GUI_XBF__GetFontInfo(const GUI_FONT GUI_UNI_PTR * pFont, GUI_FONTINFO * pInfo) {
  pInfo->Baseline = pFont->Baseline;
  pInfo->LHeight  = pFont->LHeight;
  pInfo->CHeight  = pFont->CHeight;
  pInfo->Flags    = GUI_FONTINFO_FLAG_PROP;
}

/*********************************************************************
*
*       GUI_XBF__IsInFont
*/
char GUI_XBF__IsInFont(const GUI_FONT GUI_UNI_PTR * pFont, U16 c) {
  U32 Off;
  const GUI_XBF_DATA * pXBF_Data;

  pXBF_Data = (const GUI_XBF_DATA *)pFont->p.pFontData;
  if ((c < pXBF_Data->First) || (c > pXBF_Data->Last)) {
    return 1;
  }
  GUI_XBF__GetOff(pXBF_Data, c, &Off);
  if (!Off) {
    return 0; /* Character not available */
  }
  return 1;
}

/*********************************************************************
*
*       GUI_XBF__GetCharInfo
*/
int GUI_XBF__GetCharInfo(U16P c, GUI_CHARINFO_EXT * pInfo) {
  U32 Off;
  const GUI_XBF_DATA * pXBF_Data;

  pXBF_Data = (const GUI_XBF_DATA *)GUI_Context.pAFont->p.pFontData;
  if ((c < pXBF_Data->First) || (c > pXBF_Data->Last)) {
    return 1;
  }
  GUI_XBF__GetOff(pXBF_Data, c, &Off);
  if (!Off) {
    return 1; /* Character not available */
  }
  pXBF_Data->pfGetData(Off + 0, 2, pXBF_Data->pVoid, &pInfo->XDist);
  pXBF_Data->pfGetData(Off + 2, 2, pXBF_Data->pVoid, &pInfo->XSize);
  return 0; /* ok */
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_XBF_CreateFont
*/
int GUI_XBF_CreateFont(GUI_FONT * pFont, GUI_XBF_DATA * pXBF_Data, const GUI_XBF_TYPE * pFontType, GUI_XBF_GET_DATA_FUNC * pfGetData, void * pVoid) {
  U32 Id;
  U8 aBuffer[18];
  const U8 * pBuffer;

  pBuffer = aBuffer;
  if (!pfGetData) {
    GUI_DEBUG_ERROROUT("GUI_XBF_CreateFont: No get data function passed!");
    return 1;
  }
  /* Set void pointer which is passed to GetData function */
  pXBF_Data->pVoid = pVoid;
  if (pfGetData( 0, 18, pVoid, aBuffer)) { /* Get data */
    return 1;
  }
  /* Read and check ID */
  Id = GUI__Read32(&pBuffer);
  if (Id != 0x58495547) { /* 'GUIX' */
    GUI_DEBUG_ERROROUT("GUI_XBF_CreateFont: ID of font wrong!");
    return 1;
  }
  /* Fill GUI_FONT structure */
  pFont->YSize     = (U8)GUI__Read16(&pBuffer);
  pFont->YDist     = (U8)GUI__Read16(&pBuffer);
  pFont->Baseline  = (U8)GUI__Read16(&pBuffer);
  pFont->LHeight   = (U8)GUI__Read16(&pBuffer);
  pFont->CHeight   = (U8)GUI__Read16(&pBuffer);
  pFont->XMag = 1;
  pFont->YMag = 1;
  /* Fill GUI_XBF_DATA structure */
  pXBF_Data->First = GUI__Read16(&pBuffer);
  pXBF_Data->Last  = GUI__Read16(&pBuffer);
  /* Store function pointer for getting data */
  pXBF_Data->pfGetData = pfGetData;
  /* Use font data pointer for storing address of GUI_XBF_DATA structure */
  pFont->p.pFontData = pXBF_Data;
  /* Set function pointers */
  pFont->pfDispChar     = pFontType->pfDispChar;
  pFont->pfGetCharDistX = pFontType->pfGetCharDistX;
  pFont->pfGetFontInfo  = pFontType->pfGetFontInfo;
  pFont->pfIsInFont     = pFontType->pfIsInFont;
  pFont->pfGetCharInfo  = pFontType->pfGetCharInfo;
  pFont->pafEncode      = pFontType->pafEncode;
  /* Use the new font */
  GUI_SetFont(pFont);
  return 0;
}

/*********************************************************************
*
*       GUI_XBF_DeleteFont
*/
void GUI_XBF_DeleteFont(GUI_FONT * pFont) {
  GUI_USE_PARA(pFont);
}

/*************************** End of file ****************************/
