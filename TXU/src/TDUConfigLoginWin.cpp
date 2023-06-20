#include "TDUIncludes.h"

TDUConfigLoginWin::~TDUConfigLoginWin(void)
{
}

TDUConfigLoginWin::TDUConfigLoginWin(void)
{
	Closed = true;
}

const GUI_WIDGET_CREATE_INFO TDUConfigLoginWin::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect, "Configuration",         0, 100, 40, 110, 120, FRAMEWIN_CF_MOVEABLE, 0 },
	{ BUTTON_CreateIndirect, "Close",     GUI_ID_CLOSE   , 20,  70,  60, 20 },
	{ TEXT_CreateIndirect, "Enter pin code:",GUI_ID_TEXT0, 10,  10,  148, 26, TEXT_CF_LEFT },
	{ EDIT_CreateIndirect,  NULL,            GUI_ID_EDIT0, 10,  40, 76, 15, GUI_TA_RIGHT, 20},
};

void TDUConfigLoginWin::ExecDialogBox(WM_HWIN hCurrentWin)
{
	if ( !Closed ) {
		if ( WinHandl ) {
			CloseTimer.Stop();
		}
	}
	Closed = false;
	WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbConfigKey,
												hCurrentWin, 0, 0);
	CloseTimer.Init(WinHandl,true,&Closed,TimeOut);
  WM_EnableMemdev(WinHandl);
}

void TDUConfigLoginWin::cbConfigKey(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	WM_HWIN hWin = pMsg->hWin;
	switch (pMsg->MsgId)
	{
		case WM_INIT_DIALOG:
			SystemWindow->SysWin1->InitConfigLoginWin(hWin);
		break;
		case WM_TOUCH_CHILD:
			Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
			NCode = pMsg->Data.v;               /* Notification code */
			switch(Id){
				case GUI_ID_EDIT0:
					{
              KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(hWin),L_WORD664,Id);	//"Enter Pin code: "
					}
					break;
			}
		break;
		case WM_KEY:
			//switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key)
			//{
			//	case GUI_KEY_ESCAPE:
			//			GUI_EndDialog(hWin, 1);
			//		break;
			//	case GUI_KEY_ENTER:
			//			GUI_EndDialog(hWin, 0);
			//		break;
			//}
		break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
			NCode = pMsg->Data.v;               /* Notification code */
			switch (NCode)
			{
				case WM_NOTIFICATION_RELEASED:  /* React only if released */
					switch(Id)
					{
						case GUI_ID_CLOSE:   /* Close Button */
							SystemWindow->SysWin1->CloseSysWin();
						break;
					}
				break;
			}
		break;
		default:
		WM_DefaultProc(pMsg);
	}
}

