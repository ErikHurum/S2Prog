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
File        : HEADER_Default.c
Purpose     : Implementation of header widget
---------------------------END-OF-HEADER------------------------------
*/

#include "HEADER_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       HEADER_SetDefautCursor
*/
const GUI_CURSOR GUI_UNI_PTR * HEADER_SetDefaultCursor(const GUI_CURSOR * pCursor) {
  const GUI_CURSOR GUI_UNI_PTR * pOldCursor = HEADER__pDefaultCursor;
  HEADER__pDefaultCursor = pCursor;
  return pOldCursor;
}

/*********************************************************************
*
*       HEADER_SetDefaultBkColor
*/
GUI_COLOR HEADER_SetDefaultBkColor(GUI_COLOR Color) {
  GUI_COLOR OldColor = HEADER_DefaultProps.BkColor;
  HEADER_DefaultProps.BkColor = Color;
  return OldColor;
}

/*********************************************************************
*
*       HEADER_SetDefaultTextColor
*/
GUI_COLOR HEADER_SetDefaultTextColor(GUI_COLOR Color) {
  GUI_COLOR OldColor = HEADER_DefaultProps.TextColor;
  HEADER_DefaultProps.TextColor = Color;
  return OldColor;
}

/*********************************************************************
*
*       HEADER_SetDefaultArrowColor
*/
GUI_COLOR HEADER_SetDefaultArrowColor(GUI_COLOR Color) {
  GUI_COLOR OldColor = HEADER_DefaultProps.ArrowColor;
  HEADER_DefaultProps.ArrowColor = Color;
  return OldColor;
}

/*********************************************************************
*
*       HEADER_SetDefaultBorderH
*/
int HEADER_SetDefaultBorderH(int Spacing) {
  int OldSpacing = HEADER__DefaultBorderH;
  HEADER__DefaultBorderH = Spacing;
  return OldSpacing;
}

/*********************************************************************
*
*       HEADER_SetDefaultBorderV
*/
int HEADER_SetDefaultBorderV(int Spacing) {
  int OldSpacing = HEADER__DefaultBorderV;
  HEADER__DefaultBorderV = Spacing;
  return OldSpacing;
}

/*********************************************************************
*
*       HEADER_SetDefaultFont
*/
const GUI_FONT GUI_UNI_PTR * HEADER_SetDefaultFont(const GUI_FONT GUI_UNI_PTR * pFont) {
  const GUI_FONT GUI_UNI_PTR * pOldFont = HEADER_DefaultProps.pFont;
  HEADER_DefaultProps.pFont = pFont;
  return pOldFont;
}

/*********************************************************************
*
*       HEADER_GetDefaultCursor
*/
const GUI_CURSOR GUI_UNI_PTR *  HEADER_GetDefaultCursor(void) { 
  return HEADER__pDefaultCursor;
}

/*********************************************************************
*
*       HEADER_GetDefaultBkColor
*/
GUI_COLOR HEADER_GetDefaultBkColor(void) {
  return HEADER_DefaultProps.BkColor;
}

/*********************************************************************
*
*       HEADER_GetDefaultArrowColor
*/
GUI_COLOR HEADER_GetDefaultArrowColor(void) {
  return HEADER_DefaultProps.ArrowColor;
}

/*********************************************************************
*
*       HEADER_GetDefaultTextColor
*/
GUI_COLOR HEADER_GetDefaultTextColor(void) {
  return HEADER_DefaultProps.TextColor;
}

/*********************************************************************
*
*       HEADER_GetDefaultBorderH
*/
int HEADER_GetDefaultBorderH(void) {
  return HEADER__DefaultBorderH;
}

/*********************************************************************
*
*       HEADER_GetDefaultBorderV
*/
int HEADER_GetDefaultBorderV(void) {
  return HEADER__DefaultBorderV;
}

/*********************************************************************
*
*       HEADER_GetDefaultFont
*/
const GUI_FONT GUI_UNI_PTR * HEADER_GetDefaultFont(void) {
  return HEADER_DefaultProps.pFont;
}

#else /* avoid empty object files */

void HEADER_Default_C(void);
void HEADER_Default_C(void){}

#endif  /* #if GUI_WINSUPPORT */
