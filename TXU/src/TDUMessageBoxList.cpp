#include "TDUIncludes.h"

TDUMessageBoxList::~TDUMessageBoxList(void)
{

}

TDUMessageBoxList::TDUMessageBoxList(void)
{
	Closed = true;
	{
		const GUIKey Words[] ={
			{TDU_WARNING_WIN	,0,L_WORD153},
			{GUI_ID_OK			,0,L_WORD161},
		};
		AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
	}
}

const GUI_WIDGET_CREATE_INFO TDUMessageBoxList::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect,  "Warning",  TDU_WARNING_WIN, 20, 20, 270, 190, FRAMEWIN_CF_MOVEABLE, 0},
	{ BUTTON_CreateIndirect,    "OK",       GUI_ID_OK   , 40, 150,  60,  20},
};


void TDUMessageBoxList::Exec(WM_HWIN hCurrentWin,AnsiString HeadingText,AnsiString MessageText)
{
	if ( !Closed ) {
		if ( WinHandl ) {
			CloseTimer.Stop();
		}
	}
	Closed = false;
	WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbMessageBox,
																 0, 0, 0);
	WM_HWIN hText = WM_GetDialogItem( WinHandl, GUI_ID_TEXT1);
	FRAMEWIN_SetText(WinHandl,HeadingText.c_str());

		hText = WM_GetDialogItem(WinHandl, GUI_ID_TEXT0);
		hMultiEdit = MULTIEDIT_Create(2, 14, 260, 150, WinHandl, 0,
			WM_CF_SHOW, MULTIEDIT_CF_AUTOSCROLLBAR_V, "test", 100);
		MULTIEDIT_SetReadOnly(hMultiEdit, 1);
		MULTIEDIT_SetWrapWord(hMultiEdit);

		int length1 = MessageText.length();
		if(length1 > 4000) MessageText.resize(4000);
		MULTIEDIT_SetText(hMultiEdit, MessageText.c_str());
		MULTIEDIT_SetBkColor(hMultiEdit, MULTIEDIT_CI_READONLY, TDU_C_AL_BACK_WARNING);

  CloseTimer.Init(WinHandl,true,&Closed,TimeOut);
  WM_EnableMemdev(WinHandl);
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUMessageBoxList::cbMessageBox(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	switch ( pMsg->MsgId ) {
		case WM_INIT_DIALOG:
			ListMessageBox->FirstTime = true;
			break;
		case WM_PAINT:
			ListMessageBox->UpdateLanguage();
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
								if ( !ListMessageBox->Closed ) {
									ListMessageBox->CloseTimer.Stop();
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
