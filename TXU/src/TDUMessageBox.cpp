#include "TDUIncludes.h"

TDUMessageBox::~TDUMessageBox(void)
{

}

TDUMessageBox::TDUMessageBox(void)
{
	Closed = true;
	{
		const GUIKey Words[] ={
			{TDU_MESSAGE_WIN	,0,L_WORD153},
			{GUI_ID_OK			,0,L_WORD161},
		};
		AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
	}
}

const GUI_WIDGET_CREATE_INFO TDUMessageBox::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect,  "Warning",  TDU_MESSAGE_WIN, 50, 50, 160, 100, FRAMEWIN_CF_MOVEABLE, 0},
	{ BUTTON_CreateIndirect,    "OK",       GUI_ID_OK   , 40, 60,  60,  20},
	{ TEXT_CreateIndirect,      ""	,     GUI_ID_TEXT1,  4,  4, 150,  50, TEXT_CF_LEFT},
};

void TDUMessageBox::Exec(WM_HWIN hCurrentWin,AnsiString HeadingText,AnsiString MessageText)
{
  MessageText = DivideString(MessageText,28);
	if ( !Closed ) {
		if ( WinHandl ) {
			CloseTimer.Stop();
		}
	}
	Closed = false;
	WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbMessageBox,
																 0, 0, 0);
	WM_HWIN hText;
	hText = WM_GetDialogItem( WinHandl, GUI_ID_TEXT1);
	FRAMEWIN_SetText(WinHandl,HeadingText.c_str());
	TEXT_SetText(hText,MessageText.c_str());
	CloseTimer.Init(WinHandl,true,&Closed,TimeOut);
  WM_EnableMemdev(WinHandl);
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUMessageBox::cbMessageBox(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	switch ( pMsg->MsgId ) {
		case WM_INIT_DIALOG:
			OKMessageBox->FirstTime = true;
			break;
		case WM_PAINT:
			OKMessageBox->UpdateLanguage();
			break;
		case WM_KEY:
					break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);		/* Id of widget */
			NCode = pMsg->Data.v;								/* Notification code */
			switch ( NCode ) {
				case WM_NOTIFICATION_RELEASED:		/* React only if released */
					switch ( Id ) {
						case GUI_ID_OK:
							{					 /* OK Button */
								if ( !OKMessageBox->Closed ) {
									OKMessageBox->CloseTimer.Stop();
								}
							}
							break;
					}
					break;
			}
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}
