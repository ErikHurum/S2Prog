#include "TDUIncludes.h"

TDUUserManual::~TDUUserManual(void)
{
}

TDUUserManual::TDUUserManual(void)
{
  Closed = true;
  {
	  const GUIKey Words[] ={
		  {TDU_USERMAN_WIN	,0,L_WORD21},
		  {GUI_ID_CLOSE		,0,L_WORD18},
	  };
	  AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
  }
}

const GUI_WIDGET_CREATE_INFO TDUUserManual::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect, "User manual", TDU_USERMAN_WIN, 0, 0, 0, 0, FRAMEWIN_CF_MAXIMIZED, 0 },
	{ BUTTON_CreateIndirect, "Close",     GUI_ID_CLOSE   ,190, 160,  60, 22 },
};

void TDUUserManual::ExecDialogBox(WM_HWIN hCurrentWin)
{

	if(Closed){
		Closed = false;
		//int scrollwith = SCROLLBAR_SetDefaultWidth(20);
		WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbUserManual,hCurrentWin, 0, 0);
		hUserManual = MULTIEDIT_Create(4, 16, 274, 156, WinHandl, 0, WM_CF_SHOW, MULTIEDIT_CF_AUTOSCROLLBAR_V, "User manual", 100);
		MULTIEDIT_SetReadOnly(hUserManual, 1);
		MULTIEDIT_SetWrapWord(hUserManual);
		MULTIEDIT_SetText(hUserManual, UserManual.c_str());
		MULTIEDIT_SetAutoScrollV(hUserManual, 1);
		WM_EnableMemdev(WinHandl);
	}else{
		WM_BringToTop(WinHandl);
	}
}

void TDUUserManual::cbUserManual(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	WM_HWIN hWin = pMsg->hWin;
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			SystemWindow->SysWin1->UserManualWin->UpdateLanguage();
			break;
		case WM_INIT_DIALOG:
			SystemWindow->SysWin1->InitConfigLoginWin(hWin);
			SystemWindow->SysWin1->UserManualWin->FirstTime = true;
		break;
		case WM_TOUCH_CHILD:
		break;
		case WM_KEY:
		break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
			NCode = pMsg->Data.v;               /* Notification code */
			switch (NCode)
			{
				case WM_NOTIFICATION_RELEASED:    /* React only if released */
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

