#include "TDUIncludes.h"

TDUSysWin1::~TDUSysWin1(void)
{
	delete UserManualWin ;
	delete SysSetupWin   ;
	delete PrintSetupWin ;
	delete ConfigLoginWin;
	while ( DROPDOWN_GetNumItems(hDropdLanguage)>0 ) {
		DROPDOWN_DeleteItem(hDropdLanguage, 0);
	}

}

TDUSysWin1::TDUSysWin1(void)
{
	UserManualWin   = new TDUUserManual;
	SysSetupWin     = new TDUSysSetupWin();
	PrintSetupWin   = new TDUPrinterSetupWin();
	ConfigLoginWin  = new TDUConfigLoginWin;
}

const GUI_WIDGET_CREATE_INFO TDUSysWin1::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect, "System page 1", TDU_SYSTEM1_WIN,   0,   0, 286, 198, FRAMEWIN_CF_MAXIMIZED, 0},
	//{ BUTTON_CreateIndirect, "User manual"    ,GUI_ID_BUTTON0  ,  10, 154,  80, 22},
	{ BUTTON_CreateIndirect, "Setup"          ,GUI_ID_BUTTON1  , 100, 154,  80, 22},
	{ BUTTON_CreateIndirect, "Printer"        ,GUI_ID_BUTTON2  , 190, 154,  80, 22},
	{ TEXT_CreateIndirect, "Program version:" ,  GUI_ID_TEXT0  ,   6,   6,  95, 20, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Data version:"    ,  GUI_ID_TEXT1  ,   6,  26,  95, 20, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "System ID:"       ,  GUI_ID_TEXT2  ,   6,  46,  95, 20, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, ""                 ,  GUI_ID_TEXT3  , 100,   6,  70, 20, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, ""                 ,  GUI_ID_TEXT4  , 100,  26,  70, 20, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, ""                 ,  GUI_ID_TEXT5  , 100,  46,  70, 20, TEXT_CF_RIGHT},
	{ TEXT_CreateIndirect, "Unit System:"     ,  GUI_ID_TEXT6  ,   6,  84,  70, 15, TEXT_CF_LEFT},
	{ RADIO_CreateIndirect,      NULL         , GUI_ID_RADIO0  ,   6, 100,  60, 60, 0, 3},
//Language
	{ TEXT_CreateIndirect, "Language"         ,  GUI_ID_TEXT7  , 200, 105,  70, 15, TEXT_CF_LEFT},
	{ DROPDOWN_CreateIndirect,   NULL         ,GUI_ID_DROPDOWN1, 200, 120,  70, 50, 0, 3},

	{ EDIT_CreateIndirect, ""                 , GUI_ID_EDIT11  , 200,   8,  70, 15, GUI_TA_HCENTER | GUI_TA_VCENTER, 20},
	{ EDIT_CreateIndirect, ""                 , GUI_ID_EDIT10  , 200,  28,  70, 15, GUI_TA_HCENTER | GUI_TA_VCENTER, 20},
	{ TEXT_CreateIndirect, " GMT "            , GUI_ID_TEXT8   , 200,  48,  34, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, ""                 , GUI_ID_EDIT12  , 236,  48,  34, 15, GUI_TA_HCENTER | GUI_TA_VCENTER, 20},
	{ BUTTON_CreateIndirect, "+"              ,GUI_ID_BUTTON5  , 210,  66,  25, 18},
	{ BUTTON_CreateIndirect, "-"              ,GUI_ID_BUTTON6  , 245,  66,  25, 18},
	{ BUTTON_CreateIndirect, "-"              ,GUI_ID_BUTTON6  , 245,  66,  25, 18},
	{ CHECKBOX_CreateIndirect, NULL           ,GUI_ID_CHECK0   ,  200,  86,  50, 15},

	{ TEXT_CreateIndirect, "Operation Mode"   ,GUI_ID_TEXT9    ,  90,  84,  80, 15, TEXT_CF_LEFT},
	{ DROPDOWN_CreateIndirect,   NULL         ,GUI_ID_DROPDOWN2,  90, 100,  80, 50, 0, 3},

};

const GUIKey Words[] ={
	{TDU_SYSTEM1_WIN  ,0,L_WORD20},
	//{GUI_ID_BUTTON0   ,0,L_WORD21 },
	{GUI_ID_BUTTON1   ,0,L_WORD22},
	{GUI_ID_BUTTON2   ,0,L_WORD23},
	{GUI_ID_TEXT0     ,0,L_WORD24},
	{GUI_ID_TEXT1     ,0,L_WORD25},
	{GUI_ID_TEXT2     ,0,L_WORD26},
	{GUI_ID_TEXT6     ,0,L_WORD27},
	{GUI_ID_TEXT7     ,0,L_WORD28},
	{GUI_ID_TEXT8     ,0,L_WORD29},
	{GUI_ID_TEXT9     ,0,L_WORD857},
	{GUI_ID_RADIO0    ,0,L_WORD59},
	{GUI_ID_RADIO0    ,1,L_WORD60},
	{GUI_ID_RADIO0    ,2,L_WORD984},
	{GUI_ID_CHECK0    ,1,L_WORD652},

};

void TDUSysWin1::ExecDialogBox(WM_HWIN hCurrentWin)
{
    SystemWindow->Protect();
	if ( SystemWindow->SysWin1IsClosed ) {
		SystemWindow->SysWin1IsClosed = false;
		WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbSysWin,
									   hCurrentWin, 0, 0);
		SystemWindow->CurrentSysWin = TDU_SYSWIN1;
		WM_EnableMemdev(WinHandl);
		GetDialogHandles();
	} else {
		WM_BringToTop(WinHandl);
		WM_SetFocus(CurrentWinHandl);
	}
    SystemWindow->UnProtect();
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUSysWin1::GetDialogHandles(void)
{
	hTextProg         = WM_GetDialogItem(WinHandl, GUI_ID_TEXT0);
	hTextData         = WM_GetDialogItem(WinHandl, GUI_ID_TEXT1);
	hTextSystem       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT2);
	hTextProgVersion  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT3);
	hTextDataVersion  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT4);
	hTextSystemID     = WM_GetDialogItem(WinHandl, GUI_ID_TEXT5);
	htextLanguage     = WM_GetDialogItem(WinHandl, GUI_ID_TEXT7);

	hDropdLanguage    = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN1);
	hDropdOpMode      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN2);

	hRadioUnitSystem  = WM_GetDialogItem(WinHandl, GUI_ID_RADIO0);
	hEditTime         = WM_GetDialogItem(WinHandl, GUI_ID_EDIT10);
	hEditDate         = WM_GetDialogItem(WinHandl, GUI_ID_EDIT11);
	hEditGMT          = WM_GetDialogItem(WinHandl, GUI_ID_EDIT12);
	hEditPlus         = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON5);
	hEditMinus        = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON6);
	//hButManual        = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON0);
	hButSetup         = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON1);
	hButPrinter       = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON2);
	hDSTCheckbox          = WM_GetDialogItem(WinHandl, GUI_ID_CHECK0);
	//WM_DisableWindow(hButPrinter);
	WM_DisableWindow(hEditGMT);
	InitSysWin();
}

void TDUSysWin1::InitSysWin(void)
{
//		/* Initialize all widgets */
	TEXT_SetFont(hTextProg,&TDU_FONT_PW);
	TEXT_SetFont(hTextData,&TDU_FONT_PW);
	TEXT_SetFont(hTextSystem,&TDU_FONT_PW);
	TEXT_SetFont(hTextProgVersion,&TDU_FONT_PW);
	TEXT_SetFont(hTextDataVersion,&TDU_FONT_PW);
	TEXT_SetFont(hTextSystemID,&TDU_FONT_PW);
	DROPDOWN_SetAutoScroll(hDropdLanguage,1);
	while ( DROPDOWN_GetNumItems(hDropdLanguage)>0 ) {
		DROPDOWN_DeleteItem(hDropdLanguage, 0);
	}
	{
		int Selected = 0;	// First entry is English
		for ( int Key=0; Key < L_MAX_KEY; Key++ ) {
			AnsiString CName = GetLanguage(Key);
			if ( !CName.IsEmpty() ) {
				DROPDOWN_AddString(hDropdLanguage, CName.c_str());
				if ( Key == PROSystemData::CurrentLanguage ) {
					Selected = DROPDOWN_GetNumItems(hDropdLanguage);
				}
			}
		}
		SetSelected(GUI_ID_DROPDOWN1,Selected);
	}
	DROPDOWN_SetAutoScroll(hDropdOpMode,1);
	while ( DROPDOWN_GetNumItems(hDropdOpMode)>0 ) {
		DROPDOWN_DeleteItem(hDropdOpMode, 0);
	}
	{
		const TankState TankStates[] = {tSeaGoing,tUndefined};
		for ( int OpModeKey = 0; OpModeKey < NELEMENTS(TankStates); OpModeKey++ ) {
			AnsiString CName = PROXRefObject::GetStateString(TankStates[OpModeKey]);
			if ( !CName.IsEmpty() ) {
				DROPDOWN_AddString(hDropdOpMode, CName.c_str());
			}
		}
		int Selected = int(PROSystemData::TXUSystemData->GetOpModeState());
		//Quick and dirty.
		switch ( Selected ) {
		case tSeaGoing:
			Selected = 0;
			break;
		default:
			Selected = 1;
			break;
		}
		SetSelected(GUI_ID_DROPDOWN2,Selected);

	}
	AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
	switch(PROProjectInfo::ProjectType) {
	case 0:
	case 1:
		break;
	case 2:
		Hide(GUI_ID_TEXT9);
		Hide(GUI_ID_DROPDOWN2);
		break;
	}

}

void TDUSysWin1::InitConfigLoginWin(WM_HWIN hWin)
{
	WM_HWIN hEdit0;
	if ( hWin ) {
		hEdit0 = WM_GetDialogItem(hWin, GUI_ID_EDIT0);
		if ( hEdit0 )EDIT_SetText(hEdit0, "******");
	}
}


void TDUSysWin1::CloseSysWin(void)
{
	if ( !UserManualWin->Closed ) {
		UserManualWin->Closed = true;
		if ( UserManualWin->WinHandl>0 ) GUI_EndDialog(UserManualWin->WinHandl, 0);
	}
	if ( !SysSetupWin->Closed ) {
		SysSetupWin->Closed = true;
		if ( SysSetupWin->WinHandl>0 ) GUI_EndDialog(SysSetupWin->WinHandl, 0);
	}
	if ( !PrintSetupWin->Closed ) {
		PrintSetupWin->Closed = true;
		if ( PrintSetupWin->WinHandl>0 ) GUI_EndDialog(PrintSetupWin->WinHandl, 0);
	}
	if ( !ConfigLoginWin->Closed ) {
		if ( ConfigLoginWin->WinHandl ) {
			ConfigLoginWin->CloseTimer.Stop();
		}
	}
	//GetDialogHandles();
}

void TDUSysWin1::UpdateSysWin(void)
{
	AnsiString str = LibGetValue(SVT_PROG_VERSION, PROSystemData::TXUSystemData);
	TEXT_SetText(hTextProgVersion, str.c_str());
	str = LibGetValue(SVT_DATA_VERSION, PROSystemData::TXUSystemData);
	TEXT_SetText(hTextDataVersion, str.c_str());
	str = LibGetValue(SVT_SYSTEM_ID, PROSystemData::TXUSystemData);
	TEXT_SetText(hTextSystemID, str.c_str());

	if ( PROSystemData::TXUSystemData ) {
		int CurrentUnitSystem =(int)PROSystemData::TXUSystemData->CurrentUnitSystem;
		RADIO_SetValue(hRadioUnitSystem,CurrentUnitSystem);
	}
	EDIT_SetText(hEditTime,(TSNTime()).c_str());
	EDIT_SetText(hEditDate,(TSNDate()).c_str());

	int RawTZone = (int)TSNTimeZone();
	int TZone  = RawTZone / 60;
	int RTzone = RawTZone % 60;	// Min step is 30 min
	char Buf[BUF_SIZE];
	if ( RTzone ) {
		sprintf(Buf,"%+i.5",TZone);
	} else {
		sprintf(Buf,"%+i",TZone);
	}
	EDIT_SetText(hEditGMT,Buf);
	if ( GetDaylightSaving() ) {
		CHECKBOX_Check(hDSTCheckbox);
	} else {
		CHECKBOX_Uncheck(hDSTCheckbox);
	}
	{
		int Selected = int(PROSystemData::TXUSystemData->GetOpModeState());
		//Quick and dirty.
		switch ( Selected ) {
		case tSeaGoing:
			Selected = 0;
			break;
		default:
			Selected = 1;
			break;
		}
		SetSelected(GUI_ID_DROPDOWN2,Selected);
	}
}

void TDUSysWin1::SetTime(AnsiString TimeString)
{
	char *DivideSting = ". ,/-:";
	char *Ptr1,*Ptr2,*Ptr3;
	int Hour=24;
	int Minute=60;
	int Second=60;
	Ptr1 = (char*)TimeString.c_str();
	Ptr2 = strpbrk( Ptr1, DivideSting );
	if ( Ptr2 ) {
		Ptr2++;
		Ptr3 = strpbrk(Ptr2,DivideSting);
		if ( Ptr3 ) {
			Ptr3++;
			Hour   = atoi(Ptr1);
			Minute = atoi(Ptr2);
			Second = atoi(Ptr3);
		} else {
			Hour   = atoi(Ptr1);
			Minute = atoi(Ptr2);
		}
	} else {
		Hour   = atoi(Ptr1);
	}
	//RBMARK test on fault
//	EncodeTime( Hour, Minute, Second); Only suported in Borland
	if ( (Hour >= 0) && (Hour <= 24) ) {// && (Minute >= 0) && (Minute < 60) && (Second >= 0) &&( Second < 60 )){
#ifdef S2TXU
		const time_t TimeNow = time(NULL)+3600*GetDaylightSaving();
		struct tm *timeBuffer = localtime((const time_t*)&TimeNow);
		timeBuffer->tm_hour = Hour;

		if ( (Minute >= 0) && (Minute < 60) ) {
			timeBuffer->tm_min  = Minute;
		}
		if ( (Second >= 0) &&( Second < 60 ) ) {
			timeBuffer->tm_sec  = Second;
		}
		time_t NewTime = mktime(timeBuffer);
		if ( int(NewTime)!=-1 ) {
			NewTime -= 3600*GetDaylightSaving();
			SetRTC(NewTime);
			ANPRO10_SendTime();
		} else {
			AnsiString Text1(FindDictionaryWord(L_WORD176).c_str());	// Fault in insert of Time!
			AnsiString Text2(FindDictionaryWord(L_WORD177).c_str());	// Time format h.m.s
			OKMessageBox->Exec(WinHandl,Text1 , Text2);
		}
#else
		AnsiString Text2;
		if ( (Hour >= 0) && (Hour <= 24) ) {
			Text2 +=(AnsiString)" Hour "+(AnsiString)Hour;
		}
		if ( (Minute >= 0) && (Minute < 60) ) {
			Text2 +=(AnsiString)", Minute "+(AnsiString)Minute;
		}
		if ( (Second >= 0) &&( Second < 60 ) ) {
			Text2 +=(AnsiString)", Second "+(AnsiString)Second;
		}
		AnsiString Text1("OK Insert of Time!");
		OKMessageBox->Exec(WinHandl,Text1 , Text2);
#endif
	} else {
		AnsiString Text1(FindDictionaryWord(L_WORD176).c_str());	// Fault in insert of Time!
		AnsiString Text2(FindDictionaryWord(L_WORD177).c_str());	// Time format h.m.s
		OKMessageBox->Exec(WinHandl,Text1 , Text2);
	}
}

void TDUSysWin1::SetDate(AnsiString TimeString)
{
	char *DivideSting = ". ,/-:";
	char *Ptr1,*Ptr2,*Ptr3;
	int Day=0;
	int Month=0;
	int Year=0;
	Ptr1 = (char*)TimeString.c_str();
	Ptr2 = strpbrk(Ptr1,DivideSting);
	if ( Ptr2 ) {
		Ptr2++;
		Ptr3 = strpbrk(Ptr2,DivideSting);
		if ( Ptr3 ) {
			Ptr3++;
			Day   = atoi(Ptr1);
			Month = atoi(Ptr2);
			Year  = atoi(Ptr3);
			if ( Year < 100 ) {
				Year += 2000;
			}
		} else {
			Month = atoi(Ptr2);
			Day   = atoi(Ptr1);
		}
	} else {
		Day   = atoi(Ptr1);
	}
	if ( (Day >= 1) && (Day <= 31) ) {
#ifdef S2TXU
		const time_t TimeNow = time(NULL)+3600*GetDaylightSaving();
		struct tm *timeBuffer = localtime((const time_t*)&TimeNow);
		timeBuffer->tm_mday  = Day;
		if ( (Month >= 1) && (Month <= 12) ) {
			timeBuffer->tm_mon   = Month-1;
		}
		if ( (Year >= 2004) ) {
			timeBuffer->tm_year  = Year-1900;
		}
		time_t NewTime = mktime(timeBuffer);
		if ( int(NewTime)!=-1 ) {
			NewTime -= 3600*GetDaylightSaving();
			SetRTC(NewTime);
			ANPRO10_SendTime();
		} else {
			AnsiString Text1(FindDictionaryWord(L_WORD178).c_str());	// Fault in insert of Date!
			AnsiString Text2(FindDictionaryWord(L_WORD179).c_str());	// Date format \"d.m.y\"
			OKMessageBox->Exec(WinHandl,Text1 , Text2);
		}
#else
		AnsiString Text2;
		if ( (Day >= 1) && (Day <= 31) ) {
			Text2 +=(AnsiString)" Day "+(AnsiString)Day;
		}
		if ( (Month >= 1) && (Month <= 12) ) {
			Text2 +=(AnsiString)" Month "+(AnsiString)Month;
		}
		if ( (Year >= 2004) ) {
			Text2 +=(AnsiString)" Year "+(AnsiString)Year;
		}
		AnsiString Text1("OK Insert of Date!");
		//		AnsiString Text2("Date format \"d.m.y\"");
		OKMessageBox->Exec(WinHandl,Text1 , Text2);
#endif
	} else {
		AnsiString Text1(FindDictionaryWord(L_WORD178).c_str());	// Fault in insert of Date!
		AnsiString Text2(FindDictionaryWord(L_WORD179).c_str());	// Date format \"d.m.y\"
		OKMessageBox->Exec(WinHandl,Text1 , Text2);
	}
}

void TDUSysWin1::UpdateUnitSystem(WM_HWIN hWin)
{
	WM_HWIN hRadio0;
	hRadio0 = WM_GetDialogItem(hWin, GUI_ID_RADIO0);
	int Key = RADIO_GetValue(hRadio0);
	switch ( Key ) {
	case 0:
        PROSystemData::TXUSystemData->CurrentUnitSystem = UNIT_SYS_SI;
		SetStdSIUnits();
        break;
    case 1:
		PROSystemData::TXUSystemData->CurrentUnitSystem = UNIT_SYS_US;
		SetStdUSUnits();
        break;
    case 2:
        PROSystemData::TXUSystemData->CurrentUnitSystem = UNIT_SYS_USER;
        SetUserUnits();
        break;
	}
	PROSystemData::TXUSystemData->SetModifiedFlag();
	SignalSaveSettings(FLASH_SAVE_SETTINGS);

}


void TDUSysWin1::cbSysWin(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	case WM_DELETE:
		SystemWindow->SysWin1IsClosed = true;
		break;
	case WM_PAINT:
		GUI_DrawRect(   2,  2, 174,  66); // Prog, data verson etc
		GUI_DrawRect( 194,  2, 276, 145); // Time/date etc.
		GUI_DrawRect(   2, 80,  72, 165); //Unit system
		GUI_DrawRect(  86, 80, 174, 145); // Operation mode
		SystemWindow->SysWin1->UpdateLanguage();
		SystemWindow->SysWin1->UpdateFields(false);
		SystemWindow->SysWin1->SetSelected(GUI_ID_DROPDOWN1,PROSystemData::CurrentLanguage);
		{
			int Selected = int(PROSystemData::TXUSystemData->GetOpModeState());
			//Quick and dirty.
			switch ( Selected ) {
			case tSeaGoing:
				Selected = 0;
				break;
			default:
				Selected = 1;
				break;
			}
			SystemWindow->SysWin1->SetSelected(GUI_ID_DROPDOWN2,Selected);
		}
		//SystemWindow->SysWin1->Repaint();
		//New????          GUI_DrawBitmap(&bmScanjetlogo_small, 180, 100);
		break;
	case WM_INIT_DIALOG:
		SystemWindow->SysWin1->FirstTime = true;
		break;
	case MESSAGE_PINCODE_RETURN:
		{
			int ValueId = pMsg->hWinSrc;
			char StringBuf[BUF_SIZE]={""};
			strcpy( StringBuf,(char *)pMsg->Data.p);
			switch ( ValueId ) {
			case GUI_ID_BUTTON2: // Config Button
				if ( PinUnlock || CheckPinCode(StringBuf) ) {
					PreviousWinID = CurrentWinID;
					CurrentWinID = TDU_CONFIG_MAIN_WIN;
					MainWindow->SetWindow(CurrentWinID);
				}
				break;
			}
		}
		break;
	case MESSAGE_KEYPAD_RETURN:
		{
			int ValueId = pMsg->hWinSrc;
			char StringBuf[BUF_SIZE]={""};
			if ( ValueId == GUI_ID_EDIT10 ) {
				strcpy( StringBuf,(char *)pMsg->Data.p);
				SystemWindow->SysWin1->SetTime(StringBuf);
			}
			if ( ValueId == GUI_ID_EDIT11 ) {
				strcpy( StringBuf,(char *)pMsg->Data.p);
				SystemWindow->SysWin1->SetDate(StringBuf);
			}
			//if(ValueId == GUI_ID_EDIT12){
			//	strcpy( StringBuf,(char *)pMsg->Data.p);
			//	SystemWindow->SysWin1->SetGMT(StringBuf);
			//}
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
		// break;
	case WM_TOUCH_CHILD:
		{
			Id    = WM_GetId(pMsg->hWinSrc);		// Id of widget
			NCode = pMsg->Data.v;								// Notification code
			switch ( Id ) {
			case GUI_ID_EDIT10:
				KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin), L_WORD175,Id);	// Set time \'hh.mm.ss\'
				break;
			case GUI_ID_EDIT11:
				KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin), L_WORD174,Id);	// Set date \'dd.mm.yy\'
				break;
			}
		}
		break;
	case WM_NOTIFY_CHILD_HAS_FOCUS:
		//Id    = WM_GetId(pMsg->hWinSrc);		// Id of widget
		//NCode = pMsg->Data.v;								// Notification code
		break;
	case WM_NOTIFY_PARENT:
		{
			Id    = WM_GetId(pMsg->hWinSrc);		// Id of widget
			NCode = pMsg->Data.v;								// Notification code
			switch ( NCode ) {
			case WM_NOTIFICATION_RELEASED:		// React only if released
				switch ( Id ) {
				case GUI_ID_RADIO0:
					SystemWindow->SysWin1->UpdateUnitSystem(hWin);
					break;
				case GUI_ID_BUTTON0: // User manual Button
					SystemWindow->SysWin1->UserManualWin->ExecDialogBox(hWin);
					break;
				case GUI_ID_BUTTON1: // Setup Button
					SystemWindow->SysWin1->SysSetupWin->ExecDialogBox(hWin);
					break;
				case GUI_ID_BUTTON2: // Config Button
					SystemWindow->SysWin1->PrintSetupWin->ExecDialogBox(hWin);
					break;
				case GUI_ID_BUTTON5: // GMT + Button
					SetGMT(+1);
					break;
				case GUI_ID_BUTTON6: // GMT - Button
					SetGMT(-1);
					break;
				case GUI_ID_CLOSE:	 // Close Button
					SystemWindow->Protect();
					if ( !SystemWindow->SysWin1IsClosed ) {
						SystemWindow->SysWin1->CloseSysWin();
						GUI_EndDialog(hWin, 0);
					}
					SystemWindow->UnProtect();
					break;
				case GUI_ID_CHECK0:
					if ( CHECKBOX_IsChecked(SystemWindow->SysWin1->hDSTCheckbox) ) {
						PROSystemData::SetDST(1);
					} else {
						PROSystemData::SetDST(0);
					}
					break;
				}
				break;
			case WM_NOTIFICATION_GOT_FOCUS:
				switch ( Id ) {
				case GUI_ID_DROPDOWN1: /* Language  */
					SystemWindow->SysWin1->GetSelected(GUI_ID_DROPDOWN1,SVT_CURRENT_LANGUAGE,PROSystemData::TXUSystemData);
					RepaintAll();
					NewLanguage();
				case GUI_ID_DROPDOWN2: /* OpMode  */
					SystemWindow->SysWin1->GetSelected(GUI_ID_DROPDOWN2,SVT_TANK_STATE_STR_CGO,PROSystemData::TXUSystemData);
					SystemWindow->SysWin1->GetSelected(GUI_ID_DROPDOWN2,SVT_TANK_STATE_STR_BAL,PROSystemData::TXUSystemData);
					SystemWindow->SysWin1->GetSelected(GUI_ID_DROPDOWN2,SVT_TANK_STATE_STR_PRE,PROSystemData::TXUSystemData);
					break;
				}
				break;
			default:
				break;
			}
		}
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}
