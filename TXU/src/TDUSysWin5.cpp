#include "TDUIncludes.h"

TDUSysWin5::TDUSysWin5(void)
{
}

TDUSysWin5::~TDUSysWin5(void)
{
}

const int TDUSysWin5::VList[2][8]={
	{SVT_CARGO_VOLUME ,SVT_BALLAST_VOLUME ,SVT_HEAVY_FUEL_VOLUME ,SVT_DIESEL_OIL_VOLUME ,SVT_LUBRICANTS_VOLUME ,SVT_FRESH_WATER_VOLUME ,SVT_MISC_VOLUME,SVT_TOTAL_VOLUME},
	{SVT_CARGO_WEIGHT ,SVT_BALLAST_WEIGHT ,SVT_HEAVY_FUEL_WEIGHT ,SVT_DIESEL_OIL_WEIGHT ,SVT_LUBRICANTS_WEIGHT ,SVT_FRESH_WATER_WEIGHT ,SVT_MISC_WEIGHT,SVT_TOTAL_WEIGHT},
};
const GUI_WIDGET_CREATE_INFO TDUSysWin5::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect, "System page 5",TDU_SYSTEM5_WIN, 0, 0, 286, 198, FRAMEWIN_CF_MAXIMIZED, 0},
	{ TEXT_CreateIndirect, "Total for all tanks"  , GUI_ID_TEXT0,   10,  10, 85, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Volume" 		,    	GUI_ID_TEXT28,  100 ,  10, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "Weight" 		,    	GUI_ID_TEXT29,  190 ,  10, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, ""     			,GUI_ID_TEXT1	,   10 ,  25, 80, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Cargo"    	,GUI_ID_TEXT2	,   10 ,  40, 80, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Ballast"  	,GUI_ID_TEXT3	,   10 ,  55, 80, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Heavy fuel" ,GUI_ID_TEXT4	,   10 ,  70, 80, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Diesel oil" ,GUI_ID_TEXT5	,   10 ,  85, 80, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Lubricants" ,GUI_ID_TEXT6	,   10 , 100, 80, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Fresh water",GUI_ID_TEXT7	,   10 , 115, 80, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Misc"   		,GUI_ID_TEXT8	,   10 , 130, 80, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Grand total",GUI_ID_TEXT9 ,   10 , 145, 80, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "--"   			,GUI_ID_TEXT10,   100,  25, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT11,   100,  40, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT12,   100,  55, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT13,   100,  70, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT14,   100,  85, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT15,   100, 100, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT16,   100, 115, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT17,   100, 130, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT18,   100, 145, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "--"   			,GUI_ID_TEXT19,   190,  25, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT20,   190,  40, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT21,   190,  55, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT22,   190,  70, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT23,   190,  85, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT24,   190, 100, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT25,   190, 115, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT26,   190, 130, 70, 15, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "0.0"     		,GUI_ID_TEXT27,   190, 145, 70, 15, TEXT_CF_RIGHT},
};

unsigned TDUSysWin5::IdSet2[] ={
	GUI_ID_TEXT3,
	GUI_ID_TEXT4,
	GUI_ID_TEXT5,
	GUI_ID_TEXT6,
	GUI_ID_TEXT7,
	GUI_ID_TEXT8,
	GUI_ID_TEXT9,

	GUI_ID_TEXT12,
	GUI_ID_TEXT13,
	GUI_ID_TEXT14,
	GUI_ID_TEXT15,
	GUI_ID_TEXT16,
	GUI_ID_TEXT17,
	GUI_ID_TEXT18,

	GUI_ID_TEXT21,
	GUI_ID_TEXT22,
	GUI_ID_TEXT23,
	GUI_ID_TEXT24,
	GUI_ID_TEXT25,
	GUI_ID_TEXT26,
	GUI_ID_TEXT27,

};



void TDUSysWin5::ExecDialogBox(WM_HWIN hCurrentWin) {
    SystemWindow->Protect();
	if ( SystemWindow->SysWin5IsClosed ) {
		SystemWindow->SysWin5IsClosed = false;
		WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbSysWin,
																	 hCurrentWin, 0, 0);
		SystemWindow->CurrentSysWin = TDU_SYSWIN5;
		WM_EnableMemdev(WinHandl);
		GetDialogHandles();
	} else {
		WM_BringToTop(WinHandl);
	}
    SystemWindow->UnProtect();
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUSysWin5::GetDialogHandles(void)
{
	uText[0]    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT10);
	vText[0][0] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT11);
	vText[0][1] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT12);
	vText[0][2] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT13);
	vText[0][3] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT14);
	vText[0][4] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT15);
	vText[0][5] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT16);
	vText[0][6] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT17);
	vText[0][7] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT18);

	uText[1]    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT19);
	vText[1][0] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT20);
	vText[1][1] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT21);
	vText[1][2] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT22);
	vText[1][3] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT23);
	vText[1][4] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT24);
	vText[1][5] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT25);
	vText[1][6] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT26);
	vText[1][7] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT27);
	InitSysWin();
}

void TDUSysWin5::InitSysWin(void)
{
	{
		const GUIKey Words[] ={
			{TDU_SYSTEM5_WIN	,0,L_WORD42},
			{GUI_ID_TEXT0     	,0,L_WORD43},
			{GUI_ID_TEXT28     	,0,L_WORD44},
			{GUI_ID_TEXT29     	,0,L_WORD45},
			{GUI_ID_TEXT2     	,0,L_WORD9 },
			{GUI_ID_TEXT3     	,0,L_WORD47},
			{GUI_ID_TEXT4     	,0,L_WORD48},
			{GUI_ID_TEXT5     	,0,L_WORD49},
			{GUI_ID_TEXT6     	,0,L_WORD50},
			{GUI_ID_TEXT7     	,0,L_WORD51},
			{GUI_ID_TEXT8     	,0,L_WORD52},
			{GUI_ID_TEXT9     	,0,L_WORD53},
		};

		AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
	}
	switch(PROProjectInfo::ProjectType) {
	case 0:
	case 1:
		break;
	case 2:
		for(int i=0; i < NELEMENTS(IdSet2); i++){
			Hide(IdSet2[i]);
		}
		break;
	}
}

void TDUSysWin5::UpdateSysWin(void)
{
	if ( PROSystemData::TXUSystemData) {
		for ( int i=0; i < 2; i++ ) {
			AnsiString UnitStr;
			for ( int j = 0; j < 8; j++ ) {
				AnsiString tmpStr = LibGetValue(VList[i][j], PROSystemData::TXUSystemData, &UnitStr);
				TEXT_SetText(vText[i][j], tmpStr.c_str());
			}
			TSN_Delay(2);
		  TEXT_SetText(uText[i], UnitStr.c_str());
		}
	}
}

void TDUSysWin5::cbSysWin(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
		case WM_DELETE:
			SystemWindow->SysWin5IsClosed = true;
			break;
		case WM_PAINT:
			SystemWindow->SysWin5->UpdateLanguage();
			break;
		case WM_INIT_DIALOG:
			SystemWindow->SysWin5->FirstTime = true;
			break;
		case WM_KEY:
			switch ( ((WM_KEY_INFO*)(pMsg->Data.p))->Key ) {
				case GUI_KEY_ESCAPE:
					GUI_EndDialog(hWin, 1);
					break;
				case GUI_KEY_ENTER:
					GUI_EndDialog(hWin, 0);
					break;
			}
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);		/* Id of widget */
			NCode = pMsg->Data.v;								/* Notification code */
			switch ( NCode ) {
				case WM_NOTIFICATION_RELEASED:		/* React only if released */
					switch ( Id ) {
						case GUI_ID_RADIO0:
							break;
						case GUI_ID_BUTTON0: /* User manual Button */
							break;
						case GUI_ID_BUTTON1: /* Setup Button */
							break;
						case GUI_ID_BUTTON2: /* Config Button */
							break;
						case GUI_ID_CLOSE:	 /* Close Button */
							if ( !SystemWindow->SysWin5IsClosed ) {
								GUI_EndDialog(hWin, 0);
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
