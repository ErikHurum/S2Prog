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
File        : GUIDEMO.c
Purpose     : Several GUIDEMO routines
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "GUI.h"
#if GUI_WINSUPPORT
  #include "PROGBAR.h"
  #include "LISTBOX.h"
  #include "FRAMEWIN.h"
  #include "BUTTON.h"
#endif
#include "GUI_VNC.h"
#include "GUIDEMO.h"

/*********************************************************************
*
*       Static variables
*
**********************************************************************
*/

#if GUI_WINSUPPORT
  static BUTTON_Handle   _ahButton[2];
  static FRAMEWIN_Handle _ahFrameWin[3];
  static int             _ButtonSizeX,      _ButtonSizeY;
  static FRAMEWIN_Handle _ahInfoWin[2];
  static const char* _sInfo;
#endif

static int         _iTest, _iTestMinor;
static char        _CmdNext;
static const char* _sExplain;

#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))

/*********************************************************************
*
*       Routine table
*
**********************************************************************
  The routines to be called are listed here. The advantage to calling
  directly is that we can execute some code before and after.
*/

static void (* _apfTest[])(void) = {
#if SHOW_GUIDEMO_ZOOMANDROTATE
   GUIDEMO_ZoomAndRotate,
#endif
#if SHOW_GUIDEMO_TRANSPARENTDIALOG
   GUIDEMO_TransparentDialog,
#endif
#if SHOW_GUIDEMO_WASHINGMACHINE
   GUIDEMO_WashingMachine,
#endif
#if SHOW_GUIDEMO_ICONVIEW
   GUIDEMO_IconView,
#endif
#if SHOW_GUIDEMO_IMAGEFLOW
   GUIDEMO_ImageFlow,
#endif
#if SHOW_GUIDEMO_TREEVIEW
   GUIDEMO_Treeview,
#endif
#if SHOW_GUIDEMO_LISTVIEW
   GUIDEMO_Listview,
#endif
#if SHOW_GUIDEMO_VSCREEN
   GUIDEMO_VScreen,
#endif
#if SHOW_GUIDEMO_GRAPH
   GUIDEMO_Graph,
#endif
#if SHOW_GUIDEMO_SPEED
   GUIDEMO_Speed,
#endif
#if SHOW_GUIDEMO_BITMAP
   GUIDEMO_Bitmap,
#endif
#if SHOW_GUIDEMO_CURSOR
   GUIDEMO_Cursor,
#endif
#if SHOW_GUIDEMO_SHOWCOLORBAR
   GUIDEMO_ShowColorBar,
#endif
#if SHOW_GUIDEMO_AUTOMOTIVE
   GUIDEMO_Automotive,
#endif
  0
};

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _UpdateCmdWin
*/
static void _UpdateCmdWin(void) {
  #if GUI_WINSUPPORT
    WM_InvalidateWindow(_ahInfoWin[1]);
  #endif
}

/*********************************************************************
*
*       _cbCmdWin
*/
#if (GUI_WINSUPPORT)
static void _cbCmdWin(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    /* Update info in command window */
    GUI_SetBkColor(GUI_GRAY);
    GUI_Clear();
    GUI_DispStringAt("Demo ", 0, 0);
    GUI_DispDecMin(_iTest + 1);
    GUI_DispString(".");
    GUI_DispDecMin(_iTestMinor);
    GUI_DispString("/");
    GUI_DispDecMin(countof(_apfTest));
  default:
    WM_DefaultProc(pMsg);
  }
}
#endif

/*********************************************************************
*
*       _UpdateInfoWin
*/
static void _UpdateInfoWin(void) {
  #if GUI_WINSUPPORT
    GUI_RECT rClient;
    WM_HWIN hWin;
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    /* Update info  window */
    WM_ShowWindow(_ahInfoWin[0]);
    WM_ShowWindow(_ahFrameWin[0]);
    hWin = WM_SelectWindow(_ahInfoWin[0]);
    GUI_GetClientRect(&rClient);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_Font13_1);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringHCenterAt(_sInfo, (rClient.x1 - rClient.x0) / 2, 0);
    GUI_SetTextAlign(GUI_TA_LEFT);
    GUI_SetFont(&GUI_Font8_ASCII);
    GUI_DispStringAt(_sExplain, 0, 20);
    WM_SelectWindow(hWin);
    GUI_RestoreContext(&ContextOld);
  #endif
}

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIDEMO_SetBkColor
*/
GUI_COLOR GUIDEMO_SetBkColor(GUI_COLOR Color) {
  GUI_COLOR r;
  if (GUI_ColorIsAvailable(GUI_RED)) {
    r = Color;
  } else {
    r = GUI_BLACK;
  }
  GUI_SetBkColor(r);
  return r;
}

/*********************************************************************
*
*       GUIDEMO_SetColor
*/
GUI_COLOR GUIDEMO_SetColor(GUI_COLOR Color) {
  GUI_COLOR r;
  if (GUI_ColorIsAvailable(GUI_RED)) {
    r = Color;
  } else {
    r = GUI_WHITE;
  }
  GUI_SetColor(r);
  return r;
}

/*********************************************************************
*
*       GUIDEMO_Delay
*/
int GUIDEMO_Delay(int t) {
  int r = 0;
  /**/
  //t /= 10;
  /**/
  #if GUI_WINSUPPORT
  {
    U32 value, tm;
    PROGBAR_Handle hProg;
    WM_SetForegroundWindow(_ahButton[0]);
    hProg = (t > 100) ? PROGBAR_CreateAsChild(10, 10, 60, 7, _ahInfoWin[1], 0,
                                      WM_CF_SHOW | WM_CF_STAYONTOP| WM_CF_MEMDEV) : 0;
    PROGBAR_SetMinMax(hProg, 0, t);
    tm = GUI_GetTime();
    do {
      value = GUI_GetTime() - tm;
      PROGBAR_SetValue(hProg, value);
      WM_ExecIdle();
      GUI_Delay(50);
    } while ((value < (U32)t) && !GUIDEMO_CheckCancel());
    PROGBAR_Delete(hProg);
    _UpdateCmdWin();
    WM_ExecIdle();
  }
  #else
    GUI_Delay(t);
  #endif
  return r;
}

/*********************************************************************
*
*       GUIDEMO_Wait
*/
void GUIDEMO_Wait(void) {
  GUIDEMO_Delay(4000);
  GUIDEMO_NotifyStartNext();
}

/*********************************************************************
*
*       GUIDEMO_CheckCancel
*/
int GUIDEMO_CheckCancel(void) {
  int c;
  #if GUI_WINSUPPORT
    #if GUI_SUPPORT_MEMDEV
      GUI_MEMDEV_Handle hMem;
      //
      // This needs to be done to make sure the WM is activated. Please
      // note, that in case of a selected memory device, the WM is
      // deactivated and the key of a key message is not stored into the
      // key buffer.
      //
      hMem = GUI_MEMDEV_Select(0);
    #endif
    WM_ExecIdle();
  #endif
  c = GUI_GetKey();
  if ((c == 'n') || (c=='N'))
    _CmdNext =1;
  if ((c == 'h') || (c=='H')) {
    GUI_Delay(500);
    do {
      GUI_Delay(10);
      #if GUI_WINSUPPORT
        WM_ExecIdle();
      #endif
      c = GUI_GetKey();
    } while (!c);
  }
  #if GUI_WINSUPPORT
    #if GUI_SUPPORT_MEMDEV
      hMem = GUI_MEMDEV_Select(hMem);
    #endif
  #endif
  return _CmdNext;
}

/*********************************************************************
*
*       GUIDEMO_ShowInfo
*/
void GUIDEMO_ShowInfo(const char* s) {
  _sExplain = s;
  _UpdateInfoWin();
}

/*********************************************************************
*
*       GUIDEMO_HideInfoWin
*/
void GUIDEMO_HideInfoWin(void) {
  #if GUI_WINSUPPORT
    WM_HideWindow(_ahFrameWin[0]);
  #endif
}

/*********************************************************************
*
*       GUIDEMO_ShowControlWin
*/
void GUIDEMO_ShowControlWin(int Show) {
  #if GUI_WINSUPPORT
    if (Show) {
      WM_ShowWindow(_ahFrameWin[1]);
    }else {
      WM_HideWindow(_ahFrameWin[1]);
    }
  #endif
}

/*********************************************************************
*
*       GUIDEMO_NotifyStartNext
*/
void GUIDEMO_NotifyStartNext(void) {
  _CmdNext = 0;
  _UpdateCmdWin();
  _iTestMinor++;
}

/*********************************************************************
*
*       GUIDEMO_WaitKey
*/
int GUIDEMO_WaitKey(void) {
  int r = 0;
  U32 tMax = GUI_GetTime() + 4000;
  U32 tDiff; 
  #if GUI_WINSUPPORT
    PROGBAR_Handle hProg = PROGBAR_Create(LCD_GetXSize() - 70, 
                                          LCD_GetYSize() - 40, 
                                          80, 5, WM_CF_SHOW);
  #endif
  while (tDiff = tMax - GUI_GetTime(), (tDiff > 0) && !GUIDEMO_CheckCancel()) {
    if ((r = GUI_GetKey()) != 0)
      break;
  }
  #if GUI_WINSUPPORT
    PROGBAR_Delete(hProg);
    WM_ExecIdle();
  #endif
  return r;
}

/*********************************************************************
*
*       GUIDEMO_ShowIntro
*/
void GUIDEMO_ShowIntro(const char * s, const char * sExp) {
  GUI_CONTEXT ContextOld;
  int xSize, ySize;

  GUI_SaveContext(&ContextOld);
#if GUI_WINSUPPORT
  _sInfo = s;
#endif
  _sExplain = sExp;
  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  GUI_SetDefault();
  GUIDEMO_HideInfoWin();
  GUIDEMO_SetBkColor(GUI_BLUE);
  GUI_SetColor(GUI_WHITE);
  GUI_Clear();
  GUI_SetFont(&GUI_FontComic18B_ASCII);
  GUI_DispStringHCenterAt(s, xSize / 2, ySize / 3 - 10);
  if (_sExplain) {
    GUI_SetFont(&GUI_Font8_ASCII);
    GUI_DispStringHCenterAt(_sExplain, xSize / 2, ySize / 2 - 10);
  }
  GUIDEMO_Delay(_sExplain ? 2000 : 4000);
#if GUI_WINSUPPORT
  _UpdateInfoWin();
  _UpdateCmdWin();
#endif
  GUI_RestoreContext(&ContextOld);
  #if GUI_WINSUPPORT
    WM_ExecIdle();
  #endif
  GUIDEMO_NotifyStartNext();
  GUIDEMO_SetBkColor(GUI_RED);
  GUI_Clear();
}

/*********************************************************************
*
*       GUIDEMO_main
*/
void GUIDEMO_main(void);
void GUIDEMO_main(void) {
  #if GUI_WINSUPPORT
    int i;
    int xSize, ySize, xPos, yPos;
  #endif
  #if GUI_WINSUPPORT
    WM_SelectWindow(WM_HBKWIN);
  #endif
  #if (GUI_SUPPORT_CURSOR|GUI_SUPPORT_TOUCH)
    GUI_CURSOR_Show();
  #endif
  GUI_Clear();
  #if GUI_WINSUPPORT
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Automatically use memory devices on all windows */
    /* Calculate position and size of FrameWin[1] */
    _ButtonSizeX = 30;
    _ButtonSizeY = 20;
    /* Create the control window incl. buttons */
    _ahFrameWin[1] = FRAMEWIN_Create("Control", &_cbCmdWin, WM_CF_SHOW | WM_CF_STAYONTOP,
                                                LCD_GetXSize() - 80, LCD_GetYSize() - 60, 80, 60);
    _ahInfoWin[1] = WM_GetClientWindow(_ahFrameWin[1]);
    _ahButton[0] = BUTTON_CreateAsChild(4, 20, _ButtonSizeX, _ButtonSizeY, _ahInfoWin[1], 
                                        'H' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    _ahButton[1] = BUTTON_CreateAsChild(40, 20, _ButtonSizeX, _ButtonSizeY, _ahInfoWin[1], 
                                        'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    BUTTON_SetText(_ahButton[0], "Halt");
    BUTTON_SetText(_ahButton[1], "Next");
    _UpdateCmdWin();
    WM_ExecIdle();
  #endif
  /* Show Intro */
  GUIDEMO_Intro();
  #if GUI_WINSUPPORT
    /* Calculate position and size of FrameWin[0] */
    xSize = LCD_GetXSize() / 2;
    ySize = 65;
    xPos  = LCD_GetXSize() - xSize;
    yPos  = 0;
    /* Create info window and run the individual demos */
    _ahFrameWin[0] = FRAMEWIN_Create("emWin Demo", NULL, WM_CF_STAYONTOP, 
                                     xPos, yPos, xSize, ySize);
    _ahInfoWin[0] = WM_CreateWindowAsChild(0, 0, 0, 0, WM_GetFirstChild(_ahFrameWin[0]), WM_CF_SHOW | WM_CF_STAYONTOP, 0, 0);
    WM_ExecIdle();
  #endif
  /* Run the individual demos !  */
  for (_iTest = 0; _apfTest[_iTest]; _iTest++) {
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    _iTestMinor = 0;
    _UpdateCmdWin();
    (*_apfTest[_iTest])();
    _CmdNext = 0;
    GUI_RestoreContext(&ContextOld);
  }
  /* Cleanup */
  #if GUI_WINSUPPORT
    for (i = 0; i < countof(_ahFrameWin); i++) {
      WM_DeleteWindow(_ahFrameWin[i]);
    }
  #endif
  #if (GUI_SUPPORT_CURSOR|GUI_SUPPORT_TOUCH)
    GUI_CURSOR_Hide();
  #endif
}

/*********************************************************************
*
*       MainTask
*/
void MainTask(void);
void MainTask(void) {
  GUI_Init();
  #if GUIDEMO_USE_VNC
    GUI_VNC_X_StartServer(0, 0);
  #endif
  while (1) {
    GUI_SelectLayer(0);
    GUI_TOUCH_SetLayer(0);
    GUIDEMO_main();
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();
  }
}

/*************************** End of file ****************************/
