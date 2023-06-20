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
File        : GUI_BMP_Private.h
Purpose     : Private header file for GUI_BMP... functions
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_BMP_PRIVATE_H
#define GUI_BMP_PRIVATE_H

#include "GUI_Private.h"

#if GUI_COMPILER_SUPPORTS_FP

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define BI_RGB  0
#define BI_RLE8 1
#define BI_RLE4 2

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
/* Default parameter structure for reading data from memory */
typedef struct {
  const U8 * pFileData;
  U32        Off;
} GUI_BMP_PARAM;

/* Context structure for getting stdio input */
typedef struct {
  GUI_BMP_GET_DATA_FUNC * fpGetData; /* Function pointer */
  void * pParam;                     /* Parameter pointer passed to function */
} GUI_BMP_CONTEXT;

/*********************************************************************
*
*       Interface
*
**********************************************************************
*/
int GUI_BMP__GetData    (void * p, int NumBytesReq, const U8 ** ppData, unsigned StartOfFile);
int GUI_BMP__Init       (GUI_BMP_CONTEXT * pContext, I32 * pWidth, I32 * pHeight, U16 * pBitCount, int * pNumColors, int * pCompression);
int GUI_BMP__ReadData   (GUI_BMP_CONTEXT * pContext, int NumBytes, const U8 ** ppData, unsigned StartOfFile);
int GUI_BMP__ReadPalette(GUI_BMP_CONTEXT * pContext, int NumColors);

#endif /* GUI_COMPILER_SUPPORTS_FP */

#endif /* GUI_BMP_PRIVATE_H */

/*************************** End of file ****************************/
