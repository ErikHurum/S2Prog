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
File        : DIALOG_Count.c
Purpose     : Shows a dialog which is continously counting
---------------------------END-OF-HEADER------------------------------
*/

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define GUI_NUMBYTES   150000 /* Available memory in bytes for emWin */
#define GUI_BLOCKSIZE      32 /* Average memory block size */

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Counting...",     0,      30,  90, 260, 140, FRAMEWIN_CF_MOVEABLE },
  { TEXT_CreateIndirect,     "00",     GUI_ID_TEXT0,    10,  10, 120,  80 },
  { RADIO_CreateIndirect,    "",       GUI_ID_RADIO0,  150,  10, 100,  80, 0, 4 },
  { BUTTON_CreateIndirect,   "OK",     GUI_ID_OK,       10, 100,  60,  18 },
  { BUTTON_CreateIndirect,   "Cancel", GUI_ID_CANCEL,  180, 100,  60,  18 },
};

static const char * _apLabel[] = {
  {"GUI_FontFD32"},
  {"GUI_FontFD48"},
  {"GUI_FontFD64"},
  {"GUI_FontFD80"},
};

static const GUI_FONT * _apFont[] = {
  &GUI_FontD32,
  &GUI_FontD48,
  &GUI_FontD64,
  &GUI_FontD80
};

static const char * _asExplain[] = {
  {"Please use the RADIO buttons to select"},
  {"the big digit font used for counting."}
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetFont
*/
static void _SetFont(WM_HWIN hDlg) {
  WM_HWIN hItem;
  int Index;
  hItem = WM_GetDialogItem(hDlg, GUI_ID_RADIO0);
  Index = RADIO_GetValue(hItem);
  hItem = WM_GetDialogItem(hDlg, GUI_ID_TEXT0);
  TEXT_SetFont(hItem, _apFont[Index]);
}

/*********************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE * pMsg) {
  int i;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_BLUE);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("Counting Sample", 160, 5);
    GUI_SetFont(&GUI_Font8x16);
    for (i = 0; i < GUI_COUNTOF(_asExplain); i++) {
      GUI_DispStringAt(_asExplain[i], 5, 40 + i * 16);
    }
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbCallback
*/
static void _cbCallback(WM_MESSAGE * pMsg) {
  int i;
  int NCode, Id;
  WM_HWIN hDlg, hItem;
  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      hItem = WM_GetDialogItem(hDlg, GUI_ID_RADIO0);
      for (i = 0; i < GUI_COUNTOF(_apLabel); i++) {
        RADIO_SetText(hItem, _apLabel[i], i);
      }
      _SetFont(hDlg);
      break;
    case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
      NCode = pMsg->Data.v;               /* Notification code */
      switch (NCode) {
      case WM_NOTIFICATION_VALUE_CHANGED: /* Value has changed */
        _SetFont(hDlg);
        break;
      case WM_NOTIFICATION_RELEASED:      /* React only if released */
        if (Id == GUI_ID_OK) {            /* OK Button */
          GUI_EndDialog(hDlg, 0);
        }
        if (Id == GUI_ID_CANCEL) {        /* Cancel Button */
          GUI_EndDialog(hDlg, 1);
        }
        break;
      }
      break;
    default:
      WM_DefaultProc(pMsg);
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
  int Value = 0;
  WM_HWIN hDlgFrame;
  GUI_Init();
  WM_SetCallback(WM_HBKWIN, _cbBkWindow);  
  WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
  hDlgFrame = 0;
  while(1) {
    WM_HWIN hDlg, hText;
    char acText[3] = {0};
    GUI_Delay(150);
    if (!WM_IsWindow(hDlgFrame)) {
      hDlgFrame = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
    }
    Value = (Value + 1) % 100;
    acText[0] = '0' + Value / 10;
    acText[1] = '0' + Value % 10;
    hDlg = WM_GetClientWindow(hDlgFrame);
    hText = WM_GetDialogItem(hDlg, GUI_ID_TEXT0);
    TEXT_SetText(hText, acText);
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

