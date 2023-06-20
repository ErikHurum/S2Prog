#include "TDUIncludes.h"

TDUNotConfiguredWin::~TDUNotConfiguredWin(void)
{
}

TDUNotConfiguredWin::TDUNotConfiguredWin(void)
{
}

void TDUNotConfiguredWin::SetButton(void)
{
	ButWindow->EnableButtons(false,false,false,false,false);
	ButWindow->ChangeButtonText(L_WORD237,L_WORD237,L_WORD237,L_WORD237,L_WORD237);
}

void TDUNotConfiguredWin::ButtonClicked(int ButtID)
{
	switch ( ButtID ) {
		case TDU_BUTTON_ID_PW1:
			break;
		case TDU_BUTTON_ID_PW2:
			break;
		case TDU_BUTTON_ID_PW3:
			break;
		case TDU_BUTTON_ID_PW4:
			break;
		case TDU_BUTTON_ID_PW5:
			break;
	}
}

void TDUNotConfiguredWin::cbEventHandler(WM_MESSAGE * pMsg)
{
	//WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
		case WM_NOTIFY_PARENT:
			{
				int NCode;//, Id;
				//Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
				NCode = pMsg->Data.v;				/* Notification code */
				switch ( NCode ) {
					case WM_NOTIFICATION_RELEASED:	  /* React only if released */
//				case WM_NOTIFICATION_CLICKED:   /* React only if pressed */
						{
						}
						break;
				}
			}
			break;
		case WM_PAINT:
			GUI_SetBkColor(TDU_C_PW_BACK);
			GUI_Clear();
			GUI_SetColor(TDU_C_PW_TEXT);
			GUI_SetTextMode(GUI_TM_TRANS);
			GUI_SetFont(&TDU_FONT_BIG);
			GUI_DispStringAt(FindDictionaryWord(L_WORD100).c_str(),70,80);
			UpdateFields(true);
			break;
		case WM_CREATE:
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

