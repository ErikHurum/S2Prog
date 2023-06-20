#include "TDUIncludes.h"




TDUPrinterSetupWin::~TDUPrinterSetupWin(void)
{
}

TDUPrinterSetupWin::TDUPrinterSetupWin(void)
{
	Closed = true;
}

const GUI_WIDGET_CREATE_INFO TDUPrinterSetupWin::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect,"Printer setup page"  ,TDU_LOG_SETUP_WIN, 0, 0, 0, 0, FRAMEWIN_CF_MAXIMIZED, 0},
	{ BUTTON_CreateIndirect  , "Close"              ,GUI_ID_CLOSE     ,190, 154,  80, 22},
	{ TEXT_CreateIndirect,   "Select logging:"      ,GUI_ID_TEXT0     ,  5,  10, 80, 20, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,   "Logging time"         ,GUI_ID_TEXT1     ,  5,  70, 60, 20, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect,    NULL                  ,GUI_ID_EDIT1     , 70,  70, 40, 15, GUI_TA_HCENTER | GUI_TA_VCENTER, 5},
	{ TEXT_CreateIndirect,   "Hours"                ,GUI_ID_TEXT2     ,115,  70, 80, 20, TEXT_CF_LEFT},
	{ CHECKBOX_CreateIndirect, NULL                 ,GUI_ID_CHECK0    ,  5,  30, 120, 15},
	{ CHECKBOX_CreateIndirect, NULL                 ,GUI_ID_CHECK1    ,  5,  50, 120, 15},
	{ CHECKBOX_CreateIndirect, NULL                 ,GUI_ID_CHECK2    ,  5,  90,  90, 15},
	{ CHECKBOX_CreateIndirect, NULL                 ,GUI_ID_CHECK3    ,  5, 110,  90, 15},
	{ CHECKBOX_CreateIndirect, NULL                 ,GUI_ID_CHECK4    ,  5, 130,  90, 15},
	{ CHECKBOX_CreateIndirect, NULL                 ,GUI_ID_CHECK5    ,  5, 150,  90, 15},
	{ CHECKBOX_CreateIndirect, NULL                 ,GUI_ID_CHECK6    ,160,  10, 110, 15},
};


void TDUPrinterSetupWin::ExecDialogBox(WM_HWIN hCurrentWin)
{
	//if ( !Closed ) {
	//	if ( WinHandl ) {
	//		CloseTimer.Stop();
	//	}
	//}
	//Closed = false;
	//WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbSysWin,
	//											hCurrentWin, 0, 0);
	//CloseTimer.Init(WinHandl,true,&Closed,TimeOut);
	// WM_EnableMemdev(WinHandl);

	if ( Closed ) {
		Closed = false;
		WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbEventHandler,
									   hCurrentWin, 0, 0);
		/*
		DROPDOWN_SetAutoScroll( WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN0), 1 );
		DROPDOWN_SetAutoScroll( WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN4), 1 );
		*/
		WM_EnableMemdev(WinHandl);
		GetDialogHandles();
	} else {
		WM_BringToTop(WinHandl);
	}
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUPrinterSetupWin::GetDialogHandles(void)
{
	for ( int i=0; i < P_SETUP_MAX_GUI_EDITS; i++ ) {
		hEdit[i] = WM_GetDialogItem(WinHandl, GUI_ID_EDIT0+i);
	}
	for ( int i=0; i < P_SETUP_MAX_GUI_TEXTS; i++ ) {
		hText[i] = WM_GetDialogItem(WinHandl, GUI_ID_TEXT0+i);
	}
	hButtons[0] = WM_GetDialogItem(WinHandl, GUI_ID_CLOSE);
	InitPrintWin();
	{
		const GUIKey Words[] ={
			{TDU_LOG_SETUP_WIN  ,0,L_WORD16},
			{GUI_ID_CLOSE       ,0,L_WORD18},
			{GUI_ID_TEXT0       ,0,L_WORD13},
			{GUI_ID_TEXT1       ,0,L_WORD14},
			{ 0/*GUI_ID_EDIT1*/ ,0,L_WORD14},
			{GUI_ID_TEXT2       ,0,L_WORD15},
			{GUI_ID_CHECK0      ,0,L_WORD7},
			{GUI_ID_CHECK1      ,0,L_WORD8},
			{GUI_ID_CHECK2      ,0,L_WORD9},
			{GUI_ID_CHECK3      ,0,L_WORD10},
			{GUI_ID_CHECK4      ,0,L_WORD11},
			{GUI_ID_CHECK5      ,0,L_WORD12},
			{GUI_ID_CHECK6      ,0,L_WORD620},
		};
		AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
	}
}

void TDUPrinterSetupWin::InitPrintWin(void)
{
	const GUIUpdateKey UpdateValues[] ={
		{ GUI_ID_EDIT1 , 0, PROSystemData::TXUSystemData,SVT_LOG_TIME         ,0,0,L_WORD19},
		{ GUI_ID_CHECK0, 0, PROSystemData::TXUSystemData,SVT_LOG_ALARMS       ,0,0,             0},
		{ GUI_ID_CHECK1, 0, PROSystemData::TXUSystemData,SVT_LOG_BALLAST_EXCH ,0,0,             0},
		{ GUI_ID_CHECK2, 0, PROSystemData::TXUSystemData,SVT_LOG_CARGO        ,0,0,             0},
		{ GUI_ID_CHECK3, 0, PROSystemData::TXUSystemData,SVT_LOG_SERVICE      ,0,0,             0},
		{ GUI_ID_CHECK4, 0, PROSystemData::TXUSystemData,SVT_LOG_TEMPERATURE  ,0,0,             0},
		{ GUI_ID_CHECK5, 0, PROSystemData::TXUSystemData,SVT_LOG_TANK_PRESSURE,0,0,             0},
		{ GUI_ID_CHECK6, 0, PROSystemData::TXUSystemData,SVT_PRINTER_ON_TXU   ,0,0,             0},

	};
	SetUpWidgetInfoTable((GUIUpdateKey*)UpdateValues,GUI_COUNTOF(UpdateValues));
	// Currently disable ballaste exchange log
	DisableWidget(GUI_ID_CHECK1);	// Maybe WM_HideWindow
	WM_GetDialogItem(WinHandl, GUI_ID_EDIT1);
	//UpdateFields(true);
}

void TDUPrinterSetupWin::cbEventHandler(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	//WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
		case WM_PAINT:
			GUI_DrawRect(   2,   5,  150, 170);
			//SystemWindow->SysWin1->PrintSetupWin->UpdateLanguage();
			SystemWindow->SysWin1->PrintSetupWin->UpdateFields(true);
			break;
		case MESSAGE_PINCODE_RETURN:
			break;
		case MESSAGE_KEYPAD_RETURN:
			{
				AnsiString StringBuf =(char*)pMsg->Data.p;
				int ValueId = pMsg->hWinSrc;
				switch ( ValueId ) {
					case GUI_ID_EDIT1:
					case GUI_ID_EDIT2:
					case GUI_ID_EDIT3:
					case GUI_ID_EDIT4:
					case GUI_ID_EDIT5:
						SystemWindow->SysWin1->PrintSetupWin->EDIT_InputValue(ValueId,StringBuf);
						break;
				}
			}
			/*
			if ( !SystemWindow->SysWin1->SysSetupWin->Closed ) {
				SystemWindow->SysWin1->SysSetupWin->UpdateSysWin();
			}
			*/
			break;
		case WM_TOUCH_CHILD:
			{
				Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
				switch ( Id ) {
					case GUI_ID_EDIT0 :
					case GUI_ID_EDIT1 :
					case GUI_ID_EDIT2 :
					case GUI_ID_EDIT3 :
						SystemWindow->SysWin1->PrintSetupWin->EDIT_ExecKeyboard(Id);
						break;
					default:
						break;
				}
			}
			break;
		case WM_NOTIFY_PARENT:
			{
				Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
				NCode = pMsg->Data.v;				/* Notification code */
				switch ( NCode ) {
					case WM_NOTIFICATION_SEL_CHANGED:
						{
							switch ( Id ) {
								case GUI_ID_DROPDOWN0:
								case GUI_ID_DROPDOWN4:
									//SystemWindow->SysWin1->SysSetupWin->SetAppColor(hWin,Id);
									break;
							}
						}
						break;
					case WM_NOTIFICATION_CLICKED:	 /* React only if released */
						switch ( Id ) {
							case GUI_ID_BUTTON0: /* TestBuzzer Button */
							case GUI_ID_BUTTON2:
							case GUI_ID_BUTTON3:
							case GUI_ID_BUTTON4: /* Change pin code */
							case GUI_ID_BUTTON5: /* Calibrate screen */
								break;
						}
						break;
					case WM_NOTIFICATION_RELEASED:		/* React only if released */
						switch ( Id ) {
							case GUI_ID_CHECK0:
							case GUI_ID_CHECK1:
							case GUI_ID_CHECK2:
							case GUI_ID_CHECK3:
							case GUI_ID_CHECK4:
							case GUI_ID_CHECK5:
							case GUI_ID_CHECK6:
								SystemWindow->SysWin1->PrintSetupWin->CHECKBOX_UpdateValue(Id);
								break;
							case GUI_ID_CLOSE:	 /* Close Button */
								SystemWindow->SysWin1->CloseSysWin();
								break;
						}
						break;
				}
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}
