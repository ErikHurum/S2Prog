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
File        : 2DGL_DrawBMP.c
Purpose     : Example for drawing bitmap files
----------------------------------------------------------------------
*/

#include <windows.h>
#include <stdio.h>

#include "GUI.h"

/*******************************************************************
*
*       Static functions
*
********************************************************************
*/

/*******************************************************************
*
*       _ShowBMP
*
* Shows the contents of a bitmap file
*/
static void _ShowBMP(const char * sFilename) {
  int XSize, YSize, XPos, YPos;
  DWORD NumBytesRead;
  HANDLE hFile = CreateFile(sFilename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  DWORD FileSize = GetFileSize(hFile, NULL);
  char * pFile = malloc(FileSize);
  ReadFile(hFile, pFile, FileSize, &NumBytesRead, NULL);
  CloseHandle(hFile);
  GUI_ClearRect(0, 60, 319, 239);
  XSize = GUI_BMP_GetXSize(pFile);
  YSize = GUI_BMP_GetYSize(pFile);
  XPos = (XSize > 320) ?  0 : 160 - (XSize / 2);
  YPos = (YSize > 180) ? 60 : 150 - (YSize / 2);
  if (!GUI_BMP_Draw(pFile, XPos, YPos)) {
    GUI_Delay(2000);
  }
  free(pFile);
}

/*******************************************************************
*
*       _DrawWindowsDirectoryBitmaps
*
* Iterates over all *.bmp-files of the windows directory
*/
static void _DrawWindowsDirectoryBitmaps(void) {
  char acPath[_MAX_PATH];
  char acMask[_MAX_PATH];
  char acFile[_MAX_PATH];
  WIN32_FIND_DATA Context;
  HANDLE hFind;

  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("DrawBMP - Sample", 160, 5);
  GUI_SetFont(&GUI_Font8x16);

  GetWindowsDirectory(acPath, sizeof(acPath));
  sprintf(acMask, "%s\\*.bmp", acPath);
  hFind = FindFirstFile(acMask, &Context);
  if (hFind != INVALID_HANDLE_VALUE) {
    do {
      sprintf(acFile, "%s\\%s", acPath, Context.cFileName);
      GUI_DispStringAtCEOL(acFile, 5, 40);
      _ShowBMP(acFile);
    } while (FindNextFile(hFind, &Context));
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
*       MainTask
*/
void MainTask(void) {
  GUI_Init();
  while(1) {
    _DrawWindowsDirectoryBitmaps();
  }
}

/*************************** End of file ****************************/

