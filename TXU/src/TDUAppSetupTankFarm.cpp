#include "TDUIncludes.h"


TDUAppSetupTankFarm::~TDUAppSetupTankFarm(void)
{
}

TDUAppSetupTankFarm::TDUAppSetupTankFarm(void)
{
	ValTabPtr = PROCargoTank::GetValueInfoTableStatic(ValTabEntries,TAB_TANK_VALUES);
	AppSetupTankFarmIsClosed = true;
}

const GUI_WIDGET_CREATE_INFO TDUAppSetupTankFarm::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect, "Application setup",TDU_APPCARGO_WIN , 0, 0, 0, 0, FRAMEWIN_CF_MAXIMIZED, 0},
	{ TEXT_CreateIndirect, "Operation mode"       , GUI_ID_TEXT15   ,   5, 157,  80, 15, TEXT_CF_LEFT},
	{ DROPDOWN_CreateIndirect,   NULL             , GUI_ID_DROPDOWN4,  90, 157,  85, 50, DROPDOWN_CF_UP, 3},
	{ BUTTON_CreateIndirect, "Close"              , GUI_ID_CLOSE    , 190, 154,  85, 25},
	{ TEXT_CreateIndirect, "Col. 1"               , GUI_ID_TEXT10   ,   4,   4,  40,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 2"               , GUI_ID_TEXT11   ,  44,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 3"               , GUI_ID_TEXT12   , 124,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 4"               , GUI_ID_TEXT13   , 204,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Name "                , GUI_ID_TEXT14   ,   4,  20,  74,  15, TEXT_CF_LEFT},
	{ DROPDOWN_CreateIndirect, NULL               , GUI_ID_DROPDOWN1,  44,  20,  74, 110, 0, 0},
	{ DROPDOWN_CreateIndirect, NULL               , GUI_ID_DROPDOWN2, 124,  20,  74, 110, 0, 0},
	{ DROPDOWN_CreateIndirect, NULL               , GUI_ID_DROPDOWN3, 204,  20,  74, 110, 0, 0},
	{ TEXT_CreateIndirect, "unit"                 , GUI_ID_TEXT2    ,  48,  40,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "unit"                 , GUI_ID_TEXT3    , 128,  40,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "unit"                 , GUI_ID_TEXT4    , 208,  40,  74,  15, TEXT_CF_LEFT},
	{ BUTTON_CreateIndirect,"Zero adjust tank\n pressure sensor for\n all tanks." ,GUI_ID_BUTTON0,  5,  105, 130, 45},
	{ BUTTON_CreateIndirect,"Zero adjust level\n sensor(s) for\n all tanks."      ,GUI_ID_BUTTON1,  144, 105, 130, 45},
};


void TDUAppSetupTankFarm::ExecDialogBox(WM_HWIN hCurrentWin)
{
	if ( AppSetupTankFarmIsClosed ) {
		AppSetupTankFarmIsClosed = false;
		WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbTankSetup,
									   hCurrentWin, 0, 0);
		DROPDOWN_SetAutoScroll( WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN1), 1 );
		DROPDOWN_SetAutoScroll( WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN2), 1 );
		DROPDOWN_SetAutoScroll( WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN3), 1 );
		WM_EnableMemdev(WinHandl);
		GetDialogHandles();
		//if ( hTimer ) WM_RestartTimer(hTimer, 1000); else hTimer  = WM_CreateTimer(WinHandl, 0, 1000, 0);
	} else {
		WM_BringToTop(WinHandl);
	}
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUAppSetupTankFarm::GetDialogHandles(void)
{
	/* Get window handles for all widgets */
	hDropdCol2      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN1);
	hDropdCol3      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN2);
	hDropdCol4      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN3);
	hDropdOpMode    = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN4);
	hTextUnitCol2   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT2);
	hTextUnitCol3   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT3);
	hTextUnitCol4   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT4);
	hTextTotalCol2  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT5);
	hTextTotalCol3  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT6);
	hTextTotalCol4  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT7);
	hButZeroTP    = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON0);
	hButZeroLevel = WM_GetDialogItem(WinHandl, GUI_ID_BUTTON1);
	InitDialog();
}

void TDUAppSetupTankFarm::InitDialog(void)
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
		if ( ValTabPtr[i].Value==TankFarmWindow->ValueTable[2].ValueId )ind1=i;
		if ( ValTabPtr[i].Value==TankFarmWindow->ValueTable[3].ValueId )ind2=i;
		if ( ValTabPtr[i].Value==TankFarmWindow->ValueTable[4].ValueId )ind3=i;
	}
	DROPDOWN_SetSel(hDropdCol2,ind1);
	DROPDOWN_SetSel(hDropdCol3,ind2);
	DROPDOWN_SetSel(hDropdCol4,ind3);
// Operation Mode Drop Down
	DROPDOWN_SetAutoScroll(hDropdOpMode,1);
	while ( DROPDOWN_GetNumItems(hDropdOpMode)>0 ) {
		DROPDOWN_DeleteItem(hDropdOpMode, 0);
	}
	{
		for ( int OpModeKey = (int)tSeaGoing; OpModeKey <= (int)tUndefined; OpModeKey++ ) {
			AnsiString CName = PROXRefObject::GetStateString((TankState)OpModeKey);
			if ( !CName.IsEmpty() ) {
				DROPDOWN_AddString(hDropdOpMode, CName.c_str());
			}
		}
		int Selected = PROSystemData::TXUSystemData->GetOpModeState(SVT_TANK_STATE_STR_CGO);
		SetSelected(GUI_ID_DROPDOWN4,Selected);

	}


	{
		const GUIKey Words[] ={
			{TDU_APPCARGO_WIN   ,0,L_WORD69},
			{GUI_ID_TEXT10      ,0,L_WORD70},
			{GUI_ID_TEXT11      ,0,L_WORD71},
			{GUI_ID_TEXT12      ,0,L_WORD72},
			{GUI_ID_TEXT13      ,0,L_WORD73},
			{GUI_ID_TEXT14      ,0,L_WORD74},
			{GUI_ID_TEXT15      ,0,L_WORD857},
			{GUI_ID_BUTTON0     ,0,L_WORD78},
			{GUI_ID_BUTTON1     ,0,L_WORD79},
			{GUI_ID_CLOSE       ,0,L_WORD18},
		};
		AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
	}
}

void TDUAppSetupTankFarm::UpdateDialog(WM_HWIN hWin,int Key)
{
	switch ( Key ) {
	case GUI_ID_DROPDOWN1:
	case GUI_ID_DROPDOWN2:
	case GUI_ID_DROPDOWN3:
		{
			int col;
			WM_HWIN hTextUnitCol;
			switch ( Key ) {
			case GUI_ID_DROPDOWN1:
				col          = 2;
				hTextUnitCol = hTextUnitCol2;
				break;
			case GUI_ID_DROPDOWN2:
				col          = 3;
				hTextUnitCol = hTextUnitCol3;
				break;
			case GUI_ID_DROPDOWN3:
				col          = 4;
				hTextUnitCol = hTextUnitCol4;
				break;
			}
			AnsiString str, unitstr;
			WM_HWIN hDropd0 = WM_GetDialogItem(hWin, Key);
			TankFarmWindow->ValueTable[col].ValueId = ValTabPtr[DROPDOWN_GetSel(hDropd0)].Value;
			str = LibGetValue(TankFarmWindow->ValueTable[col].ValueId,PROCargoTank::AllObjVector[0],&unitstr);
			TankFarmWindow->PaintnewHeading();
			TEXT_SetText(hTextUnitCol, unitstr.c_str());
		}
		break;
	case GUI_ID_DROPDOWN4:
		SetSelected(GUI_ID_DROPDOWN4,PROSystemData::TXUSystemData->GetOpModeState(SVT_TANK_STATE_STR_CGO));
		break;
	}
	SystemWindow->IsModified = true;

	SignalSaveSettings(FLASH_SAVE_SETTINGS);
}
void TDUAppSetupTankFarm::Update(void)
{
	SetSelected(GUI_ID_DROPDOWN4,PROSystemData::TXUSystemData->GetOpModeState(SVT_TANK_STATE_STR_CGO));
	if ( hTimer ) WM_RestartTimer(hTimer, 1000);
}

void TDUAppSetupTankFarm::cbTankSetup(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	case WM_INIT_DIALOG:
		AppSetupTankFarm->FirstTime = true;
		break;
	case WM_PAINT:
		GUI_DrawRect(   2,  55, 275, 98 );
		GUI_DrawRect(   2,  154, 175, 177 );
		AppSetupTankFarm->UpdateLanguage();
		break;
	case MESSAGE_PINCODE_RETURN:
		{
			int ValueId = pMsg->hWinSrc;
			char StringBuf[BUF_SIZE]={""};
			strcpy( StringBuf,(char *)pMsg->Data.p);
			if ( PinUnlock || CheckPinCode(StringBuf) ) {
				switch ( ValueId ) {
				case GUI_ID_BUTTON0:	/* Pressure Button */
					{
						ConfirmMessageBox->Exec(WM_GetClientWindow(hWin), L_WORD602, L_WORD603, ValueId);
						// Zero adjust tank pressure!  The tanks must be vented to the atmosphere. This operation affects all cargo tanks.
					}
					break;
				case GUI_ID_BUTTON1:	/* Level Button */
					{
						ConfirmMessageBox->Exec(WM_GetClientWindow(hWin), L_WORD604, L_WORD605, ValueId);
						// Zero adjust level sensor(s)! The tanks must be empty and no tank cleaning the last 30 minutes. This operation affects all cargo tanks.
					}
					break;
				}
			}
		}
		break;
	case MESSAGE_YES_RETURN:
		{
			AnsiString TmpString;
			int ValueId = pMsg->hWinSrc;
			char StringBuf[BUF_SIZE]={""};
			strncpy( StringBuf,(char *)pMsg->Data.p,BUF_SIZE);
			switch ( ValueId ) {
			case GUI_ID_BUTTON0:	/* Pressure Button */
				TmpString = PROTank::ZeroSetAllTankPressureSensor(PROCargoTank::ObjectSet,true);
				ANPRO10_SendZerosetAll(CMD_ZSET_ALL_CARGO_TANK_PRESS);
				break;
			case GUI_ID_BUTTON1:	/* Level Button */
				TmpString = PROTank::ZeroSetAllLevelSensors(PROCargoTank::ObjectSet,true);
 				ANPRO10_SendZerosetAll(CMD_ZSET_ALL_CARGO_LEVEL);
				break;
			}
			if ( TmpString.Length() ) {
				DisplayMessage(FindDictionaryWord(L_WORD606), TmpString); // Zeroset warnings:
			}
		}
		break;
	case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
		NCode = pMsg->Data.v;				/* Notification code */
		switch ( NCode ) {
		case WM_NOTIFICATION_RELEASED:	  /* React only if released */
			switch ( Id ) {
			case GUI_ID_BUTTON0:	/* Pressure Button */
			case GUI_ID_BUTTON1:	/* Level Button */
				KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(hWin),L_WORD150,Id);// Enter Pin code:
				break;
			case GUI_ID_CLOSE: /* Close Button */
				if ( !AppSetupTankFarmIsClosed ) {
					AppSetupTankFarmIsClosed = true;
					GUI_EndDialog(AppSetupTankFarm->WinHandl, 0);
				}
				break;
			}
			break;
		case WM_NOTIFICATION_VALUE_CHANGED:
			switch ( Id ) {
			case GUI_ID_DROPDOWN1:
			case GUI_ID_DROPDOWN2:
			case GUI_ID_DROPDOWN3:
				AppSetupTankFarm->UpdateDialog(hWin,Id);
				break;
			case GUI_ID_DROPDOWN4: /* OpMode  */
				break;
			}
			break;
		case WM_NOTIFICATION_SEL_CHANGED:
			switch ( Id ) {
			case GUI_ID_DROPDOWN1:
			case GUI_ID_DROPDOWN2:
			case GUI_ID_DROPDOWN3:
				AppSetupTankFarm->UpdateDialog(hWin,Id);
				break;
			case GUI_ID_DROPDOWN4: /* OpMode  */
				AppSetupTankFarm->GetSelected(GUI_ID_DROPDOWN4,SVT_TANK_STATE_STR_CGO,PROSystemData::TXUSystemData);
				break;
			}
			break;
		case WM_NOTIFICATION_GOT_FOCUS:
			switch ( Id ) {
			case GUI_ID_DROPDOWN4: /* OpMode  */
				break;
			}
			break;
		}
		break;
	case WM_TIMER:
		AppSetupTankFarm->Update();
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}
