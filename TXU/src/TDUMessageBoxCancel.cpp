#include "TDUIncludes.h"

TDUMessageBoxCancel::~TDUMessageBoxCancel(void)
{
}

const GUI_WIDGET_CREATE_INFO TDUMessageBoxCancel::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect ,"Warning" , TDU_MESSAGE_CAN_WIN ,    50, 50, 160, 110, FRAMEWIN_CF_MOVEABLE, 0},
	{ BUTTON_CreateIndirect   ,"Yes"     , GUI_ID_YES   , 10, 70,  60,  20},
	{ BUTTON_CreateIndirect   ,"No"      , GUI_ID_NO    , 80, 70,  60,  20},
	{ TEXT_CreateIndirect     ,""        , GUI_ID_TEXT1 ,  4,  2, 150,  52, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect     ,"Continue?", GUI_ID_TEXT0, 10, 55, 100,  20, TEXT_CF_LEFT},
};

TDUMessageBoxCancel::TDUMessageBoxCancel(void)
{
	Closed = true;
	{
		const GUIKey Words[] ={
			{TDU_MESSAGE_CAN_WIN    ,0,L_WORD153},
			{GUI_ID_YES                     ,0,L_WORD162},
			{GUI_ID_NO                      ,0,L_WORD163},
			{GUI_ID_TEXT0                   ,0,L_WORD164},
			//{GUI_ID_TEXT1					,0,L_WORD0	},
		};
		AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
	}
}


void TDUMessageBoxCancel::Exec(WM_HWIN hCurrentWin,int HeadingText,int MessageText, int ID)
{
	AnsiString MsgText = DivideString(FindDictionaryWord(MessageText),28);
	if ( !Closed ) {
		if ( WinHandl ) {
			Closed = true;
			GUI_EndDialog(WinHandl, 0);
		}
	}
	Closed = false;
	WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbMessageBox,
								   0, 0, 0);
	WM_HWIN hText = WM_GetDialogItem( WinHandl, GUI_ID_TEXT1 );
	ValueID     = ID;
	DialogWinHandl = hCurrentWin;
	ChangeSWord(TDU_MESSAGE_CAN_WIN,0,HeadingText);
	//ChangeSWord(GUI_ID_TEXT1			 ,0,MessageText);
	TEXT_SetText(hText,MsgText.c_str());
	CloseTimer.Init(WinHandl,true,&Closed,TimeOut);
	WM_EnableMemdev(WinHandl);
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUMessageBoxCancel::cbMessageBox(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	//WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	case WM_INIT_DIALOG:
		ConfirmMessageBox->FirstTime = true;
		break;
	case WM_PAINT:
		ConfirmMessageBox->UpdateLanguage();
		break;
	case WM_KEY:
		break;
	case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
		NCode = pMsg->Data.v;				/* Notification code */
		switch ( NCode ) {
		case WM_NOTIFICATION_RELEASED:	  /* React only if released */
			switch ( Id ) {
			case GUI_ID_NO:
				{
					ConfirmMessageBox->ReturnBuf[0]=0;
					WM_MESSAGE MyMsgPtr;
					MyMsgPtr.hWin = ConfirmMessageBox->DialogWinHandl;
					MyMsgPtr.hWinSrc = ConfirmMessageBox->ValueID;
					MyMsgPtr.MsgId = MESSAGE_CANCEL_RETURN;
					//  	MyMsgPtr.Data.v = ValueID;
					MyMsgPtr.Data.p = ConfirmMessageBox->ReturnBuf;
					ConfirmMessageBox->CloseTimer.Stop();
					if ( ConfirmMessageBox->DialogWinHandl > 0 )
						WM_SendMessage(ConfirmMessageBox->DialogWinHandl,&MyMsgPtr);
				}
				break;
			case GUI_ID_YES:
				{
					ConfirmMessageBox->ReturnBuf[0]=0;
					WM_MESSAGE MyMsgPtr;
					MyMsgPtr.hWin = ConfirmMessageBox->DialogWinHandl;
					MyMsgPtr.hWinSrc = ConfirmMessageBox->ValueID;
					MyMsgPtr.MsgId = MESSAGE_YES_RETURN;
					//  	MyMsgPtr.Data.v = ValueID;
					MyMsgPtr.Data.p = ConfirmMessageBox->ReturnBuf;
					ConfirmMessageBox->CloseTimer.Stop();
					if ( ConfirmMessageBox->DialogWinHandl > 0 )
						WM_SendMessage(ConfirmMessageBox->DialogWinHandl,&MyMsgPtr);
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

