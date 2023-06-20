/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2008  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.18 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : MainTask.c
Purpose     : Sample which shows how to rotate the screen at runtime
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>

#include "GUI.h"
#include "DIALOG.h"
#include "LISTVIEW.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define GUI_NUMBYTES   15000 /* Available memory in bytes for emWin */
#define GUI_BLOCKSIZE     32 /* Average memory block size */

#define TIMER_VALUE 1000 /* One seond */

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static WM_HWIN   _hWin;
static WM_HTIMER _hTimer;

/*********************************************************************
*
*       Static prototypes
*
**********************************************************************
*/
static void _Rotate(void);

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbWin
*/
static void _cbWin(WM_MESSAGE * pMsg) {
  int NCode, Id;
  static int RemTime;
  switch (pMsg->MsgId) {
  case WM_CREATE:
    /* On initialization set remaining time to 10 seconds */
    RemTime = 10000;
    break;
  case WM_NOTIFY_PARENT:
    NCode = pMsg->Data.v;
    Id    = WM_GetId(pMsg->hWinSrc);
    switch (NCode) {
    case WM_NOTIFICATION_RELEASED:
      switch (Id) {
      case GUI_ID_BUTTON0:
        /* Rotate screen on pressing the button */
        _Rotate();
        break;
      }
      break;
    }
    break;
  case WM_TIMER:
    /* Decrement timer on each timer event */
    RemTime -= 1000;
    if (RemTime > 0) {
      WM_HWIN hItem;
      char acBuffer[10];
      /* If time has not expired update counter... */
      sprintf(acBuffer, "%d", RemTime / 1000);
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0);
      TEXT_SetText(hItem, acBuffer);
      /* ...and restart timer */
      WM_RestartTimer(pMsg->Data.v, TIMER_VALUE);
    } else {
      /* If time has expired rotate window */
      _Rotate();
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _CreateObjects
*/
static void _CreateObjects(int Layer) {
  WM_HWIN hClient;
  WM_HWIN hButton;
  WM_HWIN hList;
  WM_HWIN hText0, hText1;
  int xSize, ySize, xr, yr, i, j;
  char acBuffer[100];
  /* Get layer size */
  xSize = LCD_GetXSizeEx(Layer) - 20;
  ySize = LCD_GetYSizeEx(Layer) - 20;
  /* Make sure the desktop window will be redrawn */
  WM_SetDesktopColorEx(GUI_RED, Layer);
  /* Create frame window */
  _hWin = FRAMEWIN_CreateEx(10, 10, xSize, ySize, WM_HBKWIN, WM_CF_SHOW, FRAMEWIN_CF_MOVEABLE, 0, "Screen rotation sample", _cbWin);
  FRAMEWIN_SetActive(_hWin, 1);
  /* Get size of client window */
  hClient = WM_GetClientWindow(_hWin);
  xSize = WM_GetWindowSizeX(hClient);
  ySize = WM_GetWindowSizeY(hClient);
  xr = xSize / 7;
  yr = ySize / 12;
  /* Create button */
  hButton = BUTTON_CreateEx(xr, yr, xr * 5, yr * 2, hClient, WM_CF_SHOW, 0, GUI_ID_BUTTON0);
  BUTTON_SetFont(hButton, &GUI_Font24B_ASCII);
  BUTTON_SetText(hButton, "Rotate...");
  sprintf(acBuffer, "Screen rotation is %d degrees", 90 * Layer);
  /* Create text widget which shows the current screen rotation */
  hText0 = TEXT_CreateEx(0, yr * 3, xSize, yr * 2, hClient, WM_CF_SHOW, 0, 0, acBuffer);
  TEXT_SetFont(hText0, &GUI_Font16B_ASCII);
  TEXT_SetTextAlign(hText0, GUI_TA_HCENTER | GUI_TA_VCENTER);
  /* Create a listview */
  hList = LISTVIEW_CreateEx(xr, yr * 5, xr * 5, yr * 5, hClient, WM_CF_SHOW, 0, GUI_ID_LISTVIEW0);
  LISTVIEW_SetGridVis(hList, 1);
  for (i = 0; i < 5; i++) {
    char acBuffer[] = "CX";
    acBuffer[1] = '0' + i;
    LISTVIEW_AddColumn(hList, xr - 2, acBuffer, GUI_TA_HCENTER);
  }
  for (i = 0; i < 5; i++) {
    LISTVIEW_AddRow(hList, 0);
    for (j = 0; j < 5; j++) {
      char acBuffer[3] = {0};
      acBuffer[0] = '0' + i;
      acBuffer[1] = '0' + j;
      LISTVIEW_SetItemText(hList, j, i, acBuffer);
    }
  }
  /* Create a text widget for counting */
  hText1 = TEXT_CreateEx(0, yr * 10, xSize, yr * 2, hClient, WM_CF_SHOW, 0, GUI_ID_TEXT0, "10");
  TEXT_SetFont(hText1, &GUI_Font24B_ASCII);
  TEXT_SetTextAlign(hText1, GUI_TA_HCENTER | GUI_TA_VCENTER);
  /* Create timer */
  _hTimer = WM_CreateTimer(hClient, 0, TIMER_VALUE, 0);
}

/*********************************************************************
*
*       _Rotate
*/
static void _Rotate(void) {
  static int Layer;
  /* Delete timer if it exists */
  if (_hTimer) {
    WM_DeleteTimer(_hTimer);
  }
  /* Delete frame window (and its child windows) and switch to new layer */
  if (_hWin) {
    WM_DeleteWindow(_hWin);
    GUI_Clear();
    /* Prevent desktop area from redrawing because all layers use the same video RAM */
    WM_SetDesktopColorEx(GUI_INVALID_COLOR, Layer);
    /* Switch to new layer */
    if (++Layer == 4) {
      Layer = 0;
    }
    GUI_TOUCH_SetLayer(Layer);
    GUI_SelectLayer(Layer);
  }
  /* (Re)Initialize display controller */
  switch (Layer) {
  case 0:
    LCD_L0_Init();
    break;
  case 1:
    LCD_L0_1_Init();
    break;
  case 2:
    LCD_L0_2_Init();
    break;
  case 3:
    LCD_L0_3_Init();
    break;
  }
  /* Create frame window and child controlls */
  _CreateObjects(Layer);
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
  _Rotate();
  while (1) {
    GUI_Delay(100);
  }
}

/*********************************************************************
*
*       GUI_X_Config
*/
void GUI_X_Config(void) {
  static U32 aMemory[GUI_NUMBYTES >> 2];                      /* Memory block for emWin, 32bit aligned */
  GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES & 0xFFFFFFFC); /* Assign it to emWin */
  GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);                    /* Set average memory block size */
}

/*************************** End of file ****************************/

