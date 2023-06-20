#include "TDUIncludes.h"

/*******************************************************************
*	PresentWindow event handler
*/


void cbPWEventHandler(WM_MESSAGE* pMsg)
{
	TDUPresentWin *WinPtr;
	int Size =WM_GetUserData(pMsg->hWin, (void*)&WinPtr, sizeof(WinPtr));
	WinPtr->cbEventHandler(pMsg);
}

TDUPresentWin::~TDUPresentWin(void)
{
}

TDUPresentWin::TDUPresentWin(void)
{

	BackColor = TDU_C_PW_BACK;
	TextColor = TDU_C_PW_TEXT;
	MyPtr = this;
	PWinXSize = LCDXSize-MainWindow->BWsize;
	PWinYSize = LCDYSize-MainWindow->Height-ButWindow->BHsize;

//	WinHandl = WM_CreateWindowAsChild(0,MainWindow->Height,PWinXSize,PWinYSize,
//						MainWindow->WinHandl,WM_CF_SHOW,NULL,sizeof(MyPtr));
	WinHandl = WM_CreateWindow(0,MainWindow->Height,PWinXSize,PWinYSize,WM_CF_SHOW,NULL,sizeof(MyPtr));

	ExtraSize= WM_SetUserData(WinHandl, (void*)&MyPtr, sizeof(MyPtr));
	WM_SetCallback(WinHandl, cbPWEventHandler);

}

void TDUPresentWin::SetButton(void)
{
}
void TDUPresentWin::Paintnew(void)
{
}

void TDUPresentWin::cbEventHandler(WM_MESSAGE * pMsg) {
  //WM_HWIN hWin = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_PAINT:
		GUI_SetBkColor(TDU_C_BACK_DEFAULT);
		GUI_Clear();
		GUI_SetColor(TDU_C_TEXT_DEFAULT);
	break;
  case WM_CREATE:
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

