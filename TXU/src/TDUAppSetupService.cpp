#include "TDUIncludes.h"


TDUAppSetupService::~TDUAppSetupService(void)
{
}

TDUAppSetupService::TDUAppSetupService(void)
{
	ValTabPtr = PROServiceTank::GetValueInfoTableStatic(ValTabEntries,TAB_TANK_VALUES);

	AppSetupServiceIsClosed = true;
}

const GUI_WIDGET_CREATE_INFO TDUAppSetupService::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect, "Application setup", TDU_APPSERVICE_WIN, 0, 0, 0, 0, FRAMEWIN_CF_MAXIMIZED, 0},
	{ BUTTON_CreateIndirect, "Close"            ,  GUI_ID_CLOSE, 190, 154,  85, 25},
	{ TEXT_CreateIndirect, "Col. 1"           ,  GUI_ID_TEXT20,   4,   4,  40,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 2"           ,  GUI_ID_TEXT21,  44,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 3"           ,  GUI_ID_TEXT22, 124,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 4"           ,  GUI_ID_TEXT23, 204,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Name "              , GUI_ID_TEXT24,   4,  20,  74,  15, TEXT_CF_LEFT},
	{ DROPDOWN_CreateIndirect, NULL          , GUI_ID_DROPDOWN1,  44,  20,  74, 110, 0, 3},
	{ DROPDOWN_CreateIndirect, NULL          , GUI_ID_DROPDOWN2, 124,  20,  74, 110, 0, 3},
	{ DROPDOWN_CreateIndirect, NULL          , GUI_ID_DROPDOWN3, 204,  20,  74, 110, 0, 3},
//	{ TEXT_CreateIndirect, "unit"               ,  GUI_ID_TEXT1,   4,  40,  40,  15, TEXT_CF_LEFT },
//	{ TEXT_CreateIndirect, "Total"           ,  0,   4,  56,  40,  15, TEXT_CF_LEFT },
	{ TEXT_CreateIndirect, "unit"             ,  GUI_ID_TEXT2,  48,  40,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "unit"             ,  GUI_ID_TEXT3, 128,  40,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "unit"             ,  GUI_ID_TEXT4, 208,  40,  74,  15, TEXT_CF_LEFT},
//	{ TEXT_CreateIndirect, ""	            ,  GUI_ID_TEXT5, 48,  56,  74,  15, TEXT_CF_LEFT },
//	{ TEXT_CreateIndirect, ""	            ,  GUI_ID_TEXT6, 128,  56,  74,  15, TEXT_CF_LEFT },
//	{ TEXT_CreateIndirect, ""	            ,  GUI_ID_TEXT7, 208,  56,  74,  15, TEXT_CF_LEFT },
	{ TEXT_CreateIndirect, "Density for:"   ,  GUI_ID_TEXT25,   5,  60,  70, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Heavy fuel"     ,  GUI_ID_TEXT26,   5,  75,  70, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL             ,  GUI_ID_EDIT10,  80,  75,  65, 15, GUI_TA_RIGHT},
	{ TEXT_CreateIndirect, ""               ,  GUI_ID_TEXT10, 150,  75,  65, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Diesel oil"     ,  GUI_ID_TEXT27,   5,  90,  70, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL             ,  GUI_ID_EDIT11,  80,  90,  65, 15, GUI_TA_RIGHT},
	{ TEXT_CreateIndirect, ""               ,  GUI_ID_TEXT11, 150,  90,  65, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Lubricants"     ,  GUI_ID_TEXT28 ,   5, 105,  70, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL             ,  GUI_ID_EDIT12,  80, 105,  65, 15, GUI_TA_RIGHT},
	{ TEXT_CreateIndirect, ""               ,  GUI_ID_TEXT12, 150, 105,  65, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Fresh water"    ,  GUI_ID_TEXT29 ,   5, 120,  70, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL             ,  GUI_ID_EDIT13,  80, 120,  65, 15, GUI_TA_RIGHT},
	{ TEXT_CreateIndirect, ""               ,  GUI_ID_TEXT13, 150, 120,  65, 15, TEXT_CF_LEFT},
};

void TDUAppSetupService::ExecDialogBox(WM_HWIN hCurrentWin)
{
	if ( AppSetupServiceIsClosed ) {
		AppSetupServiceIsClosed = false;
		//	WinHandl = GUI_ExecDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbTankSetup,
		//												hCurrentWin, 0, 0);
		WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbTankSetup,
																	 hCurrentWin, 0, 0);
		DROPDOWN_SetAutoScroll( WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN1), 1 );
		DROPDOWN_SetAutoScroll( WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN2), 1 );
		DROPDOWN_SetAutoScroll( WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN3), 1 );
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
void TDUAppSetupService::GetDialogHandles(void)
{
	/* Get window handles for all widgets */
	hDropdCol2      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN1);
	hDropdCol3      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN2);
	hDropdCol4      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN3);
	hTextUnitCol2   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT2);
	hTextUnitCol3   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT3);
	hTextUnitCol4   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT4);
	hTextTotalCol2  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT5);
	hTextTotalCol3  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT6);
	hTextTotalCol4  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT7);
////No need for zero common zero adjust
//  hButZeroTP    = WM_GetDialogItem(WinHandl, GUI_ID_MINIMIZE);
//	hButZeroLevel = WM_GetDialogItem(WinHandl, GUI_ID_MAXIMIZE);
	for ( int i=0; i < NUMBER_OF_SERVICE_DNS; i++ ) {
		hTextDensityUnit[i]= WM_GetDialogItem(WinHandl, GUI_ID_TEXT10+i);
		hEditDensity[i]    = WM_GetDialogItem(WinHandl, GUI_ID_EDIT10+i);
	}
	InitDialog();
}

void TDUAppSetupService::InitDialog(void)
{
	/* Initialize all widgets */
	while ( DROPDOWN_GetNumItems(hDropdCol2)>0 ) {
		DROPDOWN_DeleteItem(hDropdCol2, 0);
	}
	while ( DROPDOWN_GetNumItems(hDropdCol3)>0 ) {
		DROPDOWN_DeleteItem(hDropdCol3, 0);
	}
	while ( DROPDOWN_GetNumItems(hDropdCol4)>0 ) {
		DROPDOWN_DeleteItem(hDropdCol4, 0);
	}
	int ind1 = 0;
	int ind2 = 0;
	int ind3 = 0;
	for ( int i = 0; i < ValTabEntries; i++ ) {
		DROPDOWN_AddString(hDropdCol2, FindDictionaryWord(ValTabPtr[i].Name).c_str());
		DROPDOWN_AddString(hDropdCol3,  FindDictionaryWord(ValTabPtr[i].Name).c_str());
		DROPDOWN_AddString(hDropdCol4,  FindDictionaryWord(ValTabPtr[i].Name).c_str());
		if ( ValTabPtr[i].Value==ServiceWindow->ValueTable[2].ValueId )ind1=i;
		if ( ValTabPtr[i].Value==ServiceWindow->ValueTable[3].ValueId )ind2=i;
		if ( ValTabPtr[i].Value==ServiceWindow->ValueTable[4].ValueId )ind3=i;
	}
	DROPDOWN_SetSel(hDropdCol2,ind1);
	DROPDOWN_SetSel(hDropdCol3,ind2);
	DROPDOWN_SetSel(hDropdCol4,ind3);
	{
		const GUIKey Words[] ={
			{TDU_APPSERVICE_WIN	,0,L_WORD69},
			{GUI_ID_CLOSE     	,0,L_WORD18},
			{GUI_ID_TEXT20		,0,L_WORD70},
			{GUI_ID_TEXT21		,0,L_WORD71},
			{GUI_ID_TEXT22		,0,L_WORD72},
			{GUI_ID_TEXT23		,0,L_WORD73},
			{GUI_ID_TEXT24		,0,L_WORD74},
			{GUI_ID_TEXT25   	,0,L_WORD80},
			{GUI_ID_TEXT26   	,0,L_WORD48},
			{GUI_ID_TEXT27   	,0,L_WORD49},
			{GUI_ID_TEXT28  	,0,L_WORD50},
			{GUI_ID_TEXT29   	,0,L_WORD51},
		};
		AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
	}
}

void TDUAppSetupService::UpdateDialog(WM_HWIN hWin,int Key)
{
	WM_HWIN hDropd0 = WM_GetDialogItem(hWin, Key);
	AnsiString str, unitstr;
	int col;
	switch ( Key ) {
		case GUI_ID_DROPDOWN1:
			col = 2;
			break;
		case GUI_ID_DROPDOWN2:
			col = 3;
			break;
		case GUI_ID_DROPDOWN3:
			col = 4;
			break;
	}
	ServiceWindow->ValueTable[col].ValueId = ValTabPtr[DROPDOWN_GetSel(hDropd0)].Value;
	str = LibGetValue(ServiceWindow->ValueTable[col].ValueId,PROServiceTank::AllObjVector[0],&unitstr);
	ServiceWindow->PaintnewHeading();
	switch ( Key ) {
		case GUI_ID_DROPDOWN1:
			TEXT_SetText(hTextUnitCol2, unitstr.c_str());
			break;
		case GUI_ID_DROPDOWN2:
			TEXT_SetText(hTextUnitCol3, unitstr.c_str());
			break;
		case GUI_ID_DROPDOWN3:
			TEXT_SetText(hTextUnitCol4, unitstr.c_str());
			break;
	}
	SystemWindow->IsModified = true;
	SignalSaveSettings(FLASH_SAVE_SETTINGS);
}

void TDUAppSetupService::Update(void)
{
	static const int ValueList[]={SVT_HEAVY_FUEL_DNS,SVT_DIESEL_DNS,SVT_LUBRICANTS_DNS,SVT_FRESHWATER_DNS};

	for ( int i=0; i < NUMBER_OF_SERVICE_DNS; i++ ) {
		AnsiString UnitStr;
		AnsiString DensityStr = LibGetValue(ValueList[i],PROSystemData::TXUSystemData, &UnitStr);
		EDIT_SetText(hEditDensity[i],DensityStr.c_str());
		TEXT_SetText(hTextDensityUnit[i],UnitStr.c_str());
	}

}


void TDUAppSetupService::cbTankSetup(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
		case WM_INIT_DIALOG:
			AppSetupService->FirstTime = true;
			break;
		case WM_PAINT:
			GUI_DrawRect(   2,  56, 270, 140);
			AppSetupService->UpdateLanguage();
			break;
		case MESSAGE_YES_RETURN:
			{
				AnsiString TmpString;
				//int ValueId = pMsg->hWinSrc;
				char StringBuf[BUF_SIZE]={""};
				strncpy( StringBuf,(char *)pMsg->Data.p,BUF_SIZE);
				if ( TmpString.Length() ) {
					AnsiString Text1("Zeroset warnings:");
					DisplayMessage(Text1, TmpString);
				}
			}
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);		/* Id of widget */
			NCode = pMsg->Data.v;								/* Notification code */
			switch ( NCode ) {
				case WM_NOTIFICATION_RELEASED:		/* React only if released */
					switch ( Id ) {
						case GUI_ID_CLOSE: /* Close Button */
							if ( !AppSetupServiceIsClosed ) {
								AppSetupServiceIsClosed = true;
								GUI_EndDialog(AppSetupService->WinHandl, 0);
							}
							break;
					}
					break;
				case WM_NOTIFICATION_VALUE_CHANGED:
					{
						switch ( Id ) {
							case GUI_ID_DROPDOWN1:
							case GUI_ID_DROPDOWN2:
							case GUI_ID_DROPDOWN3:
								AppSetupService->UpdateDialog(hWin,Id);
								break;
						}
					}
					break;
				case WM_NOTIFICATION_SEL_CHANGED:
					{
						switch ( Id ) {
							case GUI_ID_DROPDOWN1:
							case GUI_ID_DROPDOWN2:
							case GUI_ID_DROPDOWN3:
								AppSetupService->UpdateDialog(hWin,Id);
								break;
						}
					}
					break;
			}
			break;
		case MESSAGE_KEYPAD_RETURN:
			{
				int ValueId = pMsg->hWinSrc;
				AnsiString StringBuf =(char*)pMsg->Data.p;
				switch ( ValueId ) {
					case GUI_ID_EDIT10:
						LibPutValue( SVT_HEAVY_FUEL_DNS, PROSystemData::TXUSystemData, StringBuf);
						break;
					case GUI_ID_EDIT11:
						LibPutValue( SVT_DIESEL_DNS, PROSystemData::TXUSystemData, StringBuf);
						break;
					case GUI_ID_EDIT12:
						LibPutValue( SVT_LUBRICANTS_DNS, PROSystemData::TXUSystemData, StringBuf);
						break;
					case GUI_ID_EDIT13:
						LibPutValue( SVT_FRESHWATER_DNS, PROSystemData::TXUSystemData, StringBuf);
						break;
				}
			}
			break;
		case WM_TOUCH_CHILD:
			{
				Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
				switch ( Id ) {
					case GUI_ID_EDIT10:
						KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD609,Id); // Heavy fuel density.
						break;
					case GUI_ID_EDIT11:
						KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD610,Id); // Diesel oil density.
						break;
					case GUI_ID_EDIT12:
						KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD611,Id); // Lubricants density.
						break;
					case GUI_ID_EDIT13:
						KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),L_WORD612,Id); // Fresh water density
						break;
				}
			}
			break;

		default:
			WM_DefaultProc(pMsg);
	}
}
