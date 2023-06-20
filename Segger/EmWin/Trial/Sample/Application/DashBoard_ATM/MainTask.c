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
Purpose     : Self executing emWin demo for VGA resolutions
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#ifdef WIN32
  #include "SIM.h"
#endif

#include "DIALOG.h"

/*********************************************************************
*
*       Externals
*
**********************************************************************
*/
extern GUI_CONST_STORAGE GUI_FONT GUI_FontAA2_21;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontAA2_32;

int AppDashBoard(void);
int AppCashTerminal(void);

extern GUI_CONST_STORAGE GUI_BITMAP bmBlueBlack;
extern GUI_CONST_STORAGE GUI_BITMAP bmCashTerminal;
extern GUI_CONST_STORAGE GUI_BITMAP bmDashboard;
extern GUI_CONST_STORAGE GUI_BITMAP bmSeggerLogo;

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define GUI_NUMBYTES   4000000 /* Available memory in bytes for emWin */
#define GUI_BLOCKSIZE      128 /* Average memory block size */

#define APP_DASHBOARD    1
#define APP_CASHTERMINAL 2

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static int _AppSelection;
static int _AppSelectionOld;
static int _Break;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbBkWin
*/
static void _cbBkWin(WM_MESSAGE * pMsg) {
  int NCode, Id;
  const WM_KEY_INFO * pKeyInfo;
  switch (pMsg->MsgId) {
  case WM_KEY:
    pKeyInfo = (const WM_KEY_INFO*)pMsg->Data.p;
    if (pKeyInfo->PressedCnt > 0) {
      switch (pKeyInfo->Key) {
      case GUI_KEY_TAB:
        WM_SetFocusOnNextChild(pMsg->hWin);
        break;
      case GUI_KEY_BACKTAB:
        WM_SetFocusOnPrevChild(pMsg->hWin);
        break;
      case GUI_KEY_ESCAPE:
        _Break = 1;
        break;
      }
    }
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
    NCode = pMsg->Data.v;               /* Notification code */
    switch (NCode) {
    case WM_NOTIFICATION_RELEASED:      /* React only if released */
      switch (Id) {
      case GUI_ID_BUTTON0:
        _AppSelection = APP_DASHBOARD;
        break;
      case GUI_ID_BUTTON1:
        _AppSelection = APP_CASHTERMINAL;
        break;
      }
      break;
    }
    break;
  case WM_PAINT:
    GUI_DrawBitmapMag(&bmBlueBlack, 0, 0, 640, 1);
    GUI_SetFont(&GUI_FontAA2_32);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetColor(GUI_WHITE);
    GUI_DispStringHCenterAt("emWin VGA Demonstration\n", 400, 44);
    GUI_SetFont(&GUI_FontAA2_21);
    GUI_DispStringHCenterAt("Press the 'Dashboard' or the 'Cash Terminal'\nbutton to start one of the applications\n", 320, 150);
    GUI_DrawBitmap(&bmSeggerLogo, 30, 30);
    break;
  }
}

/*********************************************************************
*
*       _CreateButton
*/
static WM_HWIN _CreateButton(int x, int y, int w, int h, int bx, int by, const char * pText, GUI_CONST_STORAGE GUI_BITMAP * pBm, int Id) {
  WM_HWIN hWin;
  hWin = BUTTON_CreateEx(x, y, w, h, WM_HBKWIN, WM_CF_SHOW, 0, Id);
  BUTTON_SetBitmapEx(hWin, 0, pBm, bx + 0, by + 0);
  BUTTON_SetBitmapEx(hWin, 1, pBm, bx + 1, by + 0);
  BUTTON_SetFont(hWin, &GUI_FontAA2_21);
  BUTTON_SetTextAlign(hWin, GUI_TA_TOP | GUI_TA_HCENTER);
  BUTTON_SetText(hWin, pText);
  BUTTON_SetBkColor(hWin, 0, GUI_LIGHTBLUE);
  return hWin;
}

/*********************************************************************
*
*       _cbKey
*/
#ifdef WIN32
static void _cbKey0(int key, int state) { GUI_StoreKeyMsg(GUI_KEY_BACKTAB, state); };
static void _cbKey1(int key, int state) { GUI_StoreKeyMsg(GUI_KEY_SPACE  , state); };
static void _cbKey2(int key, int state) { GUI_StoreKeyMsg(GUI_KEY_TAB    , state); };
static void _cbKey3(int key, int state) { GUI_StoreKeyMsg(GUI_KEY_ESCAPE , state); };
#endif

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
void MainTask(void);
void MainTask(void) {
  int tEnd;
  GUI_Init();
  #ifdef WIN32
    SIM_HARDKEY_SetCallback(0, &_cbKey0);
    SIM_HARDKEY_SetCallback(1, &_cbKey1);
    SIM_HARDKEY_SetCallback(2, &_cbKey2);
    SIM_HARDKEY_SetCallback(3, &_cbKey3);
  #endif
  do {
    WM_HWIN hButton0, hButton1;
    WM_SetCallback(WM_HBKWIN, _cbBkWin);
    hButton0 = _CreateButton(100, 220, 170, 150, 5, 25, "Dashboard"    , &bmDashboard   , GUI_ID_BUTTON0);
    hButton1 = _CreateButton(370, 220, 170, 150, 5, 25, "Cash Terminal", &bmCashTerminal, GUI_ID_BUTTON1);
    WM_SetFocus(hButton0);
    tEnd = GUI_GetTime() + 15000;
    do {
      static GUI_PID_STATE OldState;
      GUI_PID_STATE CurrentState;
      GUI_PID_GetState(&CurrentState);
      if ((OldState.x != CurrentState.x) || (OldState.y != CurrentState.y)) {
        tEnd = GUI_GetTime() + 10000;
      }
      OldState = CurrentState;
      GUI_Delay(100);
      if (GUI_GetTime() >= tEnd) {
        if (_AppSelectionOld) {
          _AppSelection = ((_AppSelectionOld - 1) ^ 1) + 1;
        } else {
          _AppSelection = APP_DASHBOARD;
        }
      }
    } while (!_AppSelection && !_Break);
    WM_DeleteWindow(hButton0);
    WM_DeleteWindow(hButton1);
    if (!_Break) {
      switch (_AppSelection) {
      case APP_DASHBOARD:
        AppDashBoard();
        break;
      case APP_CASHTERMINAL:
        AppCashTerminal();
        break;
      }
      GUI_CURSOR_Hide();
      _AppSelectionOld = _AppSelection;
      _AppSelection    = 0;
    }
  } while (!_Break);
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

