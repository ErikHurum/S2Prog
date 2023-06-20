#include "TDUIncludes.h"


TDUAppWinSetup::~TDUAppWinSetup(void)
{
}

TDUAppWinSetup::TDUAppWinSetup(void)
{
	AppWinSetupDiaIsClosed = true;
	TankValueList		   = NULL;
}

const GUI_WIDGET_CREATE_INFO TDUAppWinSetup::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect, "Application setup", TDU_APPSETUP_WIN, 0, 0, 0, 0, FRAMEWIN_CF_MAXIMIZED, 0},
	{ BUTTON_CreateIndirect, "Close"            ,  GUI_ID_CLOSE, 190, 154,  80, 22},
	{ TEXT_CreateIndirect, "Col. 1"             ,   GUI_ID_TEXT10,   4,   4,  40,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 2"             ,   GUI_ID_TEXT11,  44,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 3"             ,   GUI_ID_TEXT12, 124,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 4"             ,   GUI_ID_TEXT13, 204,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Name "              ,   GUI_ID_TEXT14,   4,  20,  74,  15, TEXT_CF_LEFT},
	{ DROPDOWN_CreateIndirect, NULL          , GUI_ID_DROPDOWN1,  44,  20,  74, 110, 0, 3},
	{ DROPDOWN_CreateIndirect, NULL          , GUI_ID_DROPDOWN2, 124,  20,  74, 110, 0, 3},
	{ DROPDOWN_CreateIndirect, NULL          , GUI_ID_DROPDOWN3, 204,  20,  74, 110, 0, 3},
//	{ TEXT_CreateIndirect, "unit"               ,  GUI_ID_TEXT1,   4,  40,  40,  15, TEXT_CF_LEFT },
	{ TEXT_CreateIndirect, "unit"               ,  GUI_ID_TEXT2,  48,  40,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "unit"               ,  GUI_ID_TEXT3, 128,  40,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "unit"               ,  GUI_ID_TEXT4, 208,  40,  74,  15, TEXT_CF_LEFT},

	{ TEXT_CreateIndirect,"Common input for all Ballast tanks"       , GUI_ID_TEXT20,   6,  64, 230, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,"Density"             , GUI_ID_TEXT21,   6,  84,  60, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL                 , GUI_ID_EDIT21,  70,  84,  50, 15, GUI_TA_RIGHT, 20},
	{ TEXT_CreateIndirect,"unit"                , GUI_ID_TEXT22, 122,  84,  50, 15, TEXT_CF_LEFT},

	//{ CHECKBOX_CreateIndirect, NULL  , GUI_ID_CHECK1,  10,  20,   0, 0 },
	//{ CHECKBOX_CreateIndirect, NULL  , GUI_ID_CHECK2,  10,  39,   0, 0 },

};


void TDUAppWinSetup::ExecDialogBox(WM_HWIN hCurrentWin)
{
	if ( AppWinSetupDiaIsClosed ) {
		AppWinSetupDiaIsClosed = false;
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
void TDUAppWinSetup::GetDialogHandles(void)
{
	/* Get window handles for all widgets */
	hDropdCol2      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN1);
	hDropdCol3      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN2);
	hDropdCol4      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN3);
	hTextUnitCol2   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT2);
	hTextUnitCol3   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT3);
	hTextUnitCol4   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT4);
	hTextWarning    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT20);
	hTextSimDens    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT21);
	hEditSimDens    = WM_GetDialogItem(WinHandl, GUI_ID_EDIT21);
	hTextSimDensUnit= WM_GetDialogItem(WinHandl, GUI_ID_TEXT22);
	InitDialog();
}

void TDUAppWinSetup::InitDialog(void)
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
	switch ( CurrentWinID ) {
	case TDU_CARGO_WIN:
		{
			int SizeOfTankValueList;
			TankValueList = PROCargoTank::GetValueInfoTableStatic(SizeOfTankValueList,TAB_TANK_VALUES);
			for ( int i = 0; i < SizeOfTankValueList; i++ ) {
				DROPDOWN_AddString(hDropdCol2, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol3, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol4, FindDictionaryWord(TankValueList[i].Name).c_str());
				if ( TankValueList[i].Value==CargoWindow->ValueTable[2].ValueId )ind1=i;
				if ( TankValueList[i].Value==CargoWindow->ValueTable[3].ValueId )ind2=i;
				if ( TankValueList[i].Value==CargoWindow->ValueTable[4].ValueId )ind3=i;
			}
		}
		break;
	case TDU_TANKFARM_WIN:
		{
			int SizeOfTankValueList;
			TankValueList = PROCargoTank::GetValueInfoTableStatic(SizeOfTankValueList,TAB_TANK_VALUES);
			for ( int i = 0; i < SizeOfTankValueList; i++ ) {
				DROPDOWN_AddString(hDropdCol2, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol3, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol4, FindDictionaryWord(TankValueList[i].Name).c_str());
				if ( TankValueList[i].Value==TankFarmWindow->ValueTable[2].ValueId )ind1=i;
				if ( TankValueList[i].Value==TankFarmWindow->ValueTable[3].ValueId )ind2=i;
				if ( TankValueList[i].Value==TankFarmWindow->ValueTable[4].ValueId )ind3=i;
			}
		}
		break;
	case TDU_BALLAST_WIN:
		{
			int SizeOfTankValueList;
			TankValueList = PROBallastTank::GetValueInfoTableStatic(SizeOfTankValueList,TAB_TANK_VALUES);
			for ( int i = 0; i < SizeOfTankValueList; i++ ) {
				DROPDOWN_AddString(hDropdCol2, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol3, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol4, FindDictionaryWord(TankValueList[i].Name).c_str());
				if ( TankValueList[i].Value==BallastWindow->ValueTable[2].ValueId )ind1=i;
				if ( TankValueList[i].Value==BallastWindow->ValueTable[3].ValueId )ind2=i;
				if ( TankValueList[i].Value==BallastWindow->ValueTable[4].ValueId )ind3=i;
				TEXT_SetText(hTextWarning,"Common input for all Ballast tanks");
			}
		}
		break;
	case TDU_SERVICE_WIN:
		{
			int SizeOfTankValueList;
			TankValueList = PROServiceTank::GetValueInfoTableStatic(SizeOfTankValueList,TAB_TANK_VALUES);
			for ( int i = 0; i < SizeOfTankValueList; i++ ) {
				DROPDOWN_AddString(hDropdCol2, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol3, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol4, FindDictionaryWord(TankValueList[i].Name).c_str());
				if ( TankValueList[i].Value==ServiceWindow->ValueTable[2].ValueId )ind1=i;
				if ( TankValueList[i].Value==ServiceWindow->ValueTable[3].ValueId )ind2=i;
				if ( TankValueList[i].Value==ServiceWindow->ValueTable[4].ValueId )ind3=i;
			}
		}
		break;
	case TDU_TANKPRESS_WIN:
		{
			int SizeOfTankValueList;
			TankValueList = PROTankPressure::GetValueInfoTableStatic(SizeOfTankValueList,TAB_TANK_VALUES);
			for ( int i = 0; i < SizeOfTankValueList; i++ ) {
				DROPDOWN_AddString(hDropdCol2, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol3, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol4, FindDictionaryWord(TankValueList[i].Name).c_str());
				if ( TankValueList[i].Value==TankPressWindow->ValueTable[2].ValueId )ind1=i;
				if ( TankValueList[i].Value==TankPressWindow->ValueTable[3].ValueId )ind2=i;
				if ( TankValueList[i].Value==TankPressWindow->ValueTable[4].ValueId )ind3=i;
			}
		}
		break;
	case TDU_TEMP_WIN:
		{
			int SizeOfTankValueList;
			TankValueList = PROTemperature::GetValueInfoTableStatic(SizeOfTankValueList,TAB_TANK_VALUES);
			for ( int i = 0; i < SizeOfTankValueList; i++ ) {
				DROPDOWN_AddString(hDropdCol2, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol3, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol4, FindDictionaryWord(TankValueList[i].Name).c_str());
				if ( TankValueList[i].Value==TempWindow->ValueTable[2].ValueId )ind1=i;
				if ( TankValueList[i].Value==TempWindow->ValueTable[3].ValueId )ind2=i;
				if ( TankValueList[i].Value==TempWindow->ValueTable[4].ValueId )ind3=i;
			}
		}
		break;
	case TDU_VOIDSPACE_WIN:
		{
			int SizeOfTankValueList;
			TankValueList = PROVoidSpace::GetValueInfoTableStatic(SizeOfTankValueList,TAB_TANK_VALUES);
			for ( int i = 0; i < SizeOfTankValueList; i++ ) {
				DROPDOWN_AddString(hDropdCol2, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol3, FindDictionaryWord(TankValueList[i].Name).c_str());
				DROPDOWN_AddString(hDropdCol4, FindDictionaryWord(TankValueList[i].Name).c_str());
				if ( TankValueList[i].Value==VoidSpaceWindow->ValueTable[2].ValueId )ind1=i;
				if ( TankValueList[i].Value==VoidSpaceWindow->ValueTable[3].ValueId )ind2=i;
				if ( TankValueList[i].Value==VoidSpaceWindow->ValueTable[4].ValueId )ind3=i;
				TEXT_SetText(hTextWarning,"Common input for all Void spaces");
			}
		}
		break;
	case TDU_LINEPRESS_WIN:
	case TDU_LEVELSWITCH_WIN:
	case TDU_WATERINGR_WIN:
	default:
		break;
	}
	DROPDOWN_SetSel(hDropdCol2,ind1);
	DROPDOWN_SetSel(hDropdCol3,ind2);
	DROPDOWN_SetSel(hDropdCol4,ind3);
	{
		const GUIKey Words[] ={
			{TDU_APPSETUP_WIN   ,0,L_WORD69},
			{GUI_ID_CLOSE       ,0,L_WORD18},
			{GUI_ID_TEXT10      ,0,L_WORD70},
			{GUI_ID_TEXT11      ,0,L_WORD71},
			{GUI_ID_TEXT12      ,0,L_WORD72},
			{GUI_ID_TEXT13      ,0,L_WORD73},
			{GUI_ID_TEXT14      ,0,L_WORD74},
			{GUI_ID_TEXT20      ,0,L_WORD82},
			{GUI_ID_TEXT21      ,0,L_WORD83},
		};
		AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
	}
}

void TDUAppWinSetup::UpdateDialog(WM_HWIN hWin,int Key)
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
	switch ( CurrentWinID ) {
	case TDU_CARGO_WIN:
		CargoWindow->ValueTable[col].ValueId = TankValueList[DROPDOWN_GetSel(hDropd0)].Value;
		str = LibGetValue(CargoWindow->ValueTable[col].ValueId,PROCargoTank::AllObjVector[0],&unitstr);
		CargoWindow->PaintnewHeading();
		break;
	case TDU_TANKFARM_WIN:
		TankFarmWindow->ValueTable[col].ValueId = TankValueList[DROPDOWN_GetSel(hDropd0)].Value;
		str = LibGetValue(TankFarmWindow->ValueTable[col].ValueId,PROCargoTank::AllObjVector[0],&unitstr);
		TankFarmWindow->PaintnewHeading();
		break;
	case TDU_BALLAST_WIN:
		BallastWindow->ValueTable[col].ValueId = TankValueList[DROPDOWN_GetSel(hDropd0)].Value;
		BallastWindow->PaintnewHeading();
		break;
	case TDU_SERVICE_WIN:
		ServiceWindow->ValueTable[col].ValueId = TankValueList[DROPDOWN_GetSel(hDropd0)].Value;
		ServiceWindow->PaintnewHeading();
		break;
	case TDU_TANKPRESS_WIN:
		TankPressWindow->ValueTable[col].ValueId = TankValueList[DROPDOWN_GetSel(hDropd0)].Value;
		TankPressWindow->PaintnewHeading();
		break;
	case TDU_LINEPRESS_WIN:
		break;
	case TDU_TEMP_WIN:
		TempWindow->ValueTable[col].ValueId = TankValueList[DROPDOWN_GetSel(hDropd0)].Value;
		TempWindow->PaintnewHeading();
		break;
	case TDU_VOIDSPACE_WIN:
		VoidSpaceWindow->ValueTable[col].ValueId = TankValueList[DROPDOWN_GetSel(hDropd0)].Value;
		VoidSpaceWindow->PaintnewHeading();
		break;
	case TDU_LEVELSWITCH_WIN:
	case TDU_WATERINGR_WIN:
	default:
		break;
	}
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
}

void TDUAppWinSetup::cbTankSetup(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	case WM_INIT_DIALOG:
		AppWinSetup->FirstTime = true;
		break;
	case WM_PAINT:
		//           GUI_DrawRect(   2,  22, 110,  62);
		//           GUI_DrawRect( 120,  24, 260,  46);
		GUI_DrawRect(   2,  60, 270, 140);
		AppWinSetup->UpdateLanguage();
		break;
	case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
		NCode = pMsg->Data.v;				/* Notification code */
		switch ( NCode ) {
		case WM_NOTIFICATION_RELEASED:	  /* React only if released */
			switch ( Id ) {
			case GUI_ID_CLOSE: /* Close Button */
				if ( !AppWinSetupDiaIsClosed ) {
					AppWinSetupDiaIsClosed = true;
					GUI_EndDialog(AppWinSetup->WinHandl, 0);
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
					AppWinSetup->UpdateDialog(hWin,Id);
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
					AppWinSetup->UpdateDialog(hWin,Id);
					break;
				}
			}
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}
