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
File        : GUICharLine.C
Purpose     : Implementation of character and string services
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include <stdio.h>
#include "GUI_Protected.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DispLine
*/
static void _DispLine(const char GUI_UNI_PTR *s, int MaxNumChars, const GUI_RECT *pRect) {
  #if GUI_SUPPORT_BIDI
    char acBuffer[GUI_BIDI_MAX_CHARS_PER_LINE * 3];
    MaxNumChars = GUI__BIDI_Log2Vis(s, MaxNumChars, acBuffer, sizeof(acBuffer));
    s = acBuffer;
  #endif
  /* Check if we have anything to do at all ... */
  if (GUI_Context.pClipRect_HL) {
    if (GUI_RectsIntersect(GUI_Context.pClipRect_HL, pRect) == 0)
      return;
  }
  #if GUI_COMPILER_SUPPORTS_FP
  if (GUI_Context.pAFont->pafEncode) {
    GUI_Context.pAFont->pafEncode->pfDispLine(s, MaxNumChars);
  } else {
  #else
  {
  #endif
    U16 Char;
    while (--MaxNumChars >= 0) {
      Char = GUI_UC__GetCharCodeInc(&s);
      GUI_Context.pAFont->pfDispChar(Char);
      if (GUI_pfDispCharStyle) {
        GUI_pfDispCharStyle(Char);
      }
    }
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
*       GUI__GetLineNumChars
*/
int GUI__GetLineNumChars(const char GUI_UNI_PTR *s, int MaxNumChars) {
  int NumChars = 0;
  if (s) {
    #if GUI_COMPILER_SUPPORTS_FP
      if (GUI_Context.pAFont->pafEncode) {
        if (GUI_Context.pAFont->pafEncode->pfGetLineLen) {
          return GUI_Context.pAFont->pafEncode->pfGetLineLen(s, MaxNumChars);
        }
      }
    #endif
    for (; NumChars < MaxNumChars; NumChars++) {
      U16 Data = GUI_UC__GetCharCodeInc(&s);
      if ((Data == 0) || (Data == '\n')) {
        break;
      }
    }
  }
  return NumChars;
}

/*********************************************************************
*
*       GUI__GetOverlap
*/
int GUI__GetOverlap(U16 Char) {
  int r = 0;
  if (GUI_Context.pAFont->pfGetCharInfo) {
    GUI_CHARINFO_EXT CharInfo;
    if (GUI_Context.pAFont->pfGetCharInfo(Char, &CharInfo) == 0) {
      if (CharInfo.XSize > CharInfo.XDist) {
        r = CharInfo.XSize - CharInfo.XDist;
      }
    }
  }
  return r;
}

/*********************************************************************
*
*       GUI__GetLineDistX
*
*  This routine is used to calculate the length of a line in pixels.
*/
int GUI__GetLineDistX(const char GUI_UNI_PTR *s, int MaxNumChars) {
  int Dist;
  #if GUI_SUPPORT_BIDI
    char acBuffer[GUI_BIDI_MAX_CHARS_PER_LINE * 3];
    MaxNumChars = GUI__BIDI_Log2Vis(s, MaxNumChars, acBuffer, sizeof(acBuffer));
    s = acBuffer;
  #endif
  Dist = 0;
  if (s) {
    U16 Char = 0;
    #if GUI_COMPILER_SUPPORTS_FP
      if (GUI_Context.pAFont->pafEncode) {
        if (GUI_Context.pAFont->pafEncode->pfGetLineDistX) {
          return GUI_Context.pAFont->pafEncode->pfGetLineDistX(s, MaxNumChars);
        }
      }
    #endif
    while (--MaxNumChars >= 0) {
      Char  = GUI_UC__GetCharCodeInc(&s);
      Dist += GUI_GetCharDistX(Char);
    }
    Dist += GUI__GetOverlap(Char);
  }
  return Dist;
}

/*********************************************************************
*
*       GUI__DispLine
*/
void GUI__DispLine(const char GUI_UNI_PTR *s, int MaxNumChars, const GUI_RECT* pr) {
  GUI_RECT r;
  #if GUI_SUPPORT_ROTATION
  if (GUI_pLCD_APIList) {
    #if GUI_WINSUPPORT
    WM_ITERATE_START(NULL) {
    #endif
      /* Do the actual drawing via routine call. */
      _DispLine(s, MaxNumChars, &r);
    #if GUI_WINSUPPORT
    } WM_ITERATE_END();
    #endif
  } else
  #endif
  {
    r = *pr;
    #if GUI_WINSUPPORT
    WM_ADDORG(r.x0, r.y0);
    WM_ADDORG(r.x1, r.y1);
    WM_ITERATE_START(&r) {
    #endif
      GUI_Context.DispPosX = r.x0;
      GUI_Context.DispPosY = r.y0;
      /* Do the actual drawing via routine call. */
      _DispLine(s, MaxNumChars, &r);
    #if GUI_WINSUPPORT
    } WM_ITERATE_END();
    WM_SUBORG(GUI_Context.DispPosX, GUI_Context.DispPosY);
    #endif
  }
}

/*************************** End of file ****************************/
