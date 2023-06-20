#include "TDUIncludes.h"


TDUAppSetupTemp::~TDUAppSetupTemp(void)
{
}

TDUAppSetupTemp::TDUAppSetupTemp(void)
{
	AppSetupTempIsClosed = true;
}

const GUI_WIDGET_CREATE_INFO TDUAppSetupTemp::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect, "Application setup", TDU_APPTEMP_WIN, 0, 0, 0, 0, FRAMEWIN_CF_MAXIMIZED, 0},
	{ BUTTON_CreateIndirect, "Close"            ,  GUI_ID_CLOSE, 190, 154,  85, 25},
	{ TEXT_CreateIndirect, "Col. 1"             , GUI_ID_TEXT20,   4,   4,  40,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 2"             , GUI_ID_TEXT21,  44,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 3"             ,   GUI_ID_TEXT22, 124,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Col. 4"             ,   GUI_ID_TEXT23, 204,   4,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Name "              ,  GUI_ID_TEXT24,   4,  20,  74,  15, TEXT_CF_LEFT},
	{ DROPDOWN_CreateIndirect, NULL          , GUI_ID_DROPDOWN1,  44,  20,  74, 110, 0, 3},
	{ DROPDOWN_CreateIndirect, NULL          , GUI_ID_DROPDOWN2, 124,  20,  74, 110, 0, 3},
	{ DROPDOWN_CreateIndirect, NULL          , GUI_ID_DROPDOWN3, 204,  20,  74, 110, 0, 3},
	{ TEXT_CreateIndirect, "unit"                 ,  GUI_ID_TEXT2,  48,  40,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "unit"                 ,  GUI_ID_TEXT3, 128,  40,  74,  15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "unit"                 ,  GUI_ID_TEXT4, 208,  40,  74,  15, TEXT_CF_LEFT},

};


void TDUAppSetupTemp::ExecDialogBox(WM_HWIN hCurrentWin)
{
	if ( AppSetupTempIsClosed ) {
		AppSetupTempIsClosed = false;
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
void TDUAppSetupTemp::GetDialogHandles(void)
{
	/* Get window handles for all widgets */
	hDropdCol2      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN1);
	hDropdCol3      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN2);
	hDropdCol4      = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN3);
	hTextUnitCol2   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT2);
	hTextUnitCol3   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT3);
	hTextUnitCol4   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT4);
	hTextTotalCol2    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT5);
	hTextTotalCol3    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT6);
	hTextTotalCol4    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT7);
	InitDialog();
}

void TDUAppSetupTemp::InitDialog(void)
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
	int SizeOfList;
	ValueList *VList = PROTemperature::GetValueInfoTableStatic(SizeOfList);
	for ( int i = 0; i < SizeOfList; i++ ) {
		DROPDOWN_AddString(hDropdCol2,  FindDictionaryWord(VList[i].Name).c_str());
		DROPDOWN_AddString(hDropdCol3,  FindDictionaryWord(VList[i].Name).c_str());
		DROPDOWN_AddString(hDropdCol4,  FindDictionaryWord(VList[i].Name).c_str());
		if ( VList[i].Value==TempWindow->ValueTable[2].ValueId)ind1=i;
		if ( VList[i].Value==TempWindow->ValueTable[3].ValueId)ind2=i;
		if ( VList[i].Value==TempWindow->ValueTable[4].ValueId)ind3=i;
	}
	DROPDOWN_SetSel(hDropdCol2,ind1);
	DROPDOWN_SetSel(hDropdCol3,ind2);
	DROPDOWN_SetSel(hDropdCol4,ind3);
	{
		const GUIKey Words[] ={
			{TDU_APPTEMP_WIN    ,0,L_WORD69},
			{GUI_ID_CLOSE       ,0,L_WORD18},
			{GUI_ID_TEXT20      ,0,L_WORD70},
			{GUI_ID_TEXT21      ,0,L_WORD71},
			{GUI_ID_TEXT22      ,0,L_WORD72},
			{GUI_ID_TEXT23      ,0,L_WORD73},
			{GUI_ID_TEXT24      ,0,L_WORD74},
		};
		AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
	}
}

void TDUAppSetupTemp::UpdateDialog(WM_HWIN hWin,int Key)
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
	int SizeOfList;
	ValueList *VList = PROTemperature::GetValueInfoTableStatic(SizeOfList,0);
	TempWindow->ValueTable[col].ValueId = VList[DROPDOWN_GetSel(hDropd0)].Value;
	str = LibGetValue(TempWindow->ValueTable[col].ValueId,PROTemperature::AllObjVector[0],&unitstr);
	TempWindow->PaintnewHeading();
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

void TDUAppSetupTemp::Update(void)
{
}

void TDUAppSetupTemp::cbTankSetup(WM_MESSAGE *pMsg)
{
	int NCode, Id;
	WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
		case WM_INIT_DIALOG:
			AppSetupTemp->FirstTime = true;
			break;
		case WM_PAINT:
			GUI_DrawRect(   2,  55, 275, 98 );
			AppSetupTemp->UpdateLanguage();
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
			NCode = pMsg->Data.v;				/* Notification code */
			switch ( NCode ) {
				case WM_NOTIFICATION_RELEASED:	  /* React only if released */
					switch ( Id ) {
						case GUI_ID_CLOSE: /* Close Button */
							if ( !AppSetupTempIsClosed ) {
								AppSetupTempIsClosed = true;
								GUI_EndDialog(AppSetupTemp->WinHandl, 0);
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
								AppSetupTemp->UpdateDialog(hWin,Id);
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
								AppSetupTemp->UpdateDialog(hWin,Id);
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
