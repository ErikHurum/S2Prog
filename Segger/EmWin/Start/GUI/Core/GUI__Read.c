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
File        : GUI__ReadData.c
Purpose     : Implementation of reading data
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__Read16
*/
U16 GUI__Read16(const U8 ** ppData) {
  const U8 * pData;
  U16  Value;
  pData = *ppData;
  Value = *pData;
  Value |= (U16)(*(pData + 1) << 8);
  pData += 2;
  *ppData = pData;
  return Value;
}

/*********************************************************************
*
*       GUI__Read32
*/
U32 GUI__Read32(const U8 ** ppData) {
  const U8 * pData;
  U32  Value;
  pData = *ppData;
  Value = *pData;
  Value |= ((U32)*(pData + 1) << 8);
  Value |= ((U32)*(pData + 2) << 16);
  Value |= ((U32)*(pData + 3) << 24);
  pData += 4;
  *ppData = pData;
  return Value;
}

