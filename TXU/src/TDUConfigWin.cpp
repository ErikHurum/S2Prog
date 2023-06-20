#include "TDUIncludes.h"

TDUConfigWin::~TDUConfigWin(void)
{
}

TDUConfigWin::TDUConfigWin(void)
{
//	WinHandl = WM_CreateWindowAsChild(0,0,0,0,MainWindow->WinHandl,WM_CF_SHOW,NULL,0);
	WinHandl  = WM_CreateWindow(0,0,LCDXSize,LCDYSize,WM_CF_SHOW,NULL,0);
	CloseButton = BUTTON_CreateAsChild(250,210,60,22,WinHandl,CLOSE_BUT_ID_CONFIG,WM_CF_SHOW);
	BUTTON_SetText(CloseButton, "Close");
	WM_SetCallback(WinHandl, cbEventHandler);
}

void TDUConfigWin::cbEventHandler(WM_MESSAGE * pMsg)
{
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetBkColor(TDU_C_CONF_BACK);GUI_Clear();
			GUI_SetColor(TDU_C_CONF_TEXT);
			GUI_DrawBitmap(&bmScanjetlogo,2,60);
			GUI_SetTextMode(GUI_TM_TRANS);
			GUI_SetFont(&TDU_FONT_BIG);
			GUI_DispStringHCenterAt("Configuration",LCDXSize/2,160);
		break;
		case WM_CREATE:
		{
			GUI_SetBkColor(TDU_C_CONF_BACK);GUI_Clear();
		}
		break;
		case WM_NOTIFY_PARENT:
		{
			int NCode, Id;
			Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
			NCode = pMsg->Data.v;               /* Notification code */
			switch (NCode)
			{
				case WM_NOTIFICATION_RELEASED:  /* React only if released */
//				case WM_NOTIFICATION_CLICKED:   /* React only if pressed */
				{
					switch (Id){
					case CLOSE_BUT_ID_CONFIG:
						MainWindow->SetPreviousWindow();
					break;
					}
				}
				break;
			}

		}
		break;
		default:
		WM_DefaultProc(pMsg);
	}
}
