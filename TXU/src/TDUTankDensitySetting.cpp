#include "TDUIncludes.h"

TDUTankDensitySetting::~TDUTankDensitySetting(void)
{
}

TDUTankDensitySetting::TDUTankDensitySetting(void)
{
	TankWinDensityDiaIsClosed = true;
}

const GUI_WIDGET_CREATE_INFO TDUTankDensitySetting::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect,"Density settings",             0,   0,   0,   0,  0, FRAMEWIN_CF_MOVEABLE, 0},
	{ BUTTON_CreateIndirect, "Next >"         , GUI_ID_MAXIMIZE, 100, 154,  80, 22},
	{ BUTTON_CreateIndirect, "Close"            ,  GUI_ID_CLOSE, 190, 154,  80, 22},
	{ TEXT_CreateIndirect, "Tag      "          ,  GUI_ID_TEXT0,  30,   4, 200, 16, TEXT_CF_LEFT},

	{ RADIO_CreateIndirect,      NULL           , GUI_ID_RADIO0,   6,  26,  90, 40, 0, 2},
	//{ TEXT_CreateIndirect, "Linear"			    ,  GUI_ID_TEXT1,  30,  26,  70, 15, TEXT_CF_LEFT },
	//{ TEXT_CreateIndirect, "API / ASTM-IP"	    ,  GUI_ID_TEXT2,  30,  46,  70, 15, TEXT_CF_LEFT },

	{ CHECKBOX_CreateIndirect, NULL             , GUI_ID_CHECK0, 124,  28,   0,  0},
	{ TEXT_CreateIndirect,"Use measured density",  GUI_ID_TEXT3, 144,  28, 110, 15, TEXT_CF_LEFT},
// API
	{ TEXT_CreateIndirect,"API / ASTM-IP Table:", GUI_ID_TEXT10,   6,  74, 100, 15, TEXT_CF_LEFT},
	{ DROPDOWN_CreateIndirect,  NULL          ,GUI_ID_DROPDOWN1, 110,  74, 100,  60, 0, 3},
	{ TEXT_CreateIndirect,"Reference temperature",GUI_ID_TEXT11,   6, 100, 120, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL                 , GUI_ID_EDIT11, 130, 100,  50, 15, GUI_TA_RIGHT, 20},
	{ TEXT_CreateIndirect,"unit"                , GUI_ID_TEXT12, 182, 100,  50, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,"Density"             , GUI_ID_TEXT13,   6, 120, 120, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL                 , GUI_ID_EDIT13, 130, 120,  50, 15, GUI_TA_RIGHT, 20},
	{ TEXT_CreateIndirect,"unit"                , GUI_ID_TEXT14, 182, 120,  50, 15, TEXT_CF_LEFT},
// Linear
	{ CHECKBOX_CreateIndirect, NULL             , GUI_ID_CHECK2,   6,  74,   0,  0},
	{ TEXT_CreateIndirect,"Use reference density",GUI_ID_TEXT20,  26,  74, 120, 15, TEXT_CF_LEFT},

	{ TEXT_CreateIndirect,"Density"             , GUI_ID_TEXT21,   6, 100, 120, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL                 , GUI_ID_EDIT21, 130, 100,  50, 15, GUI_TA_RIGHT, 20},
	{ TEXT_CreateIndirect,"unit"                , GUI_ID_TEXT22, 182, 100,  50, 15, TEXT_CF_LEFT},

	{ TEXT_CreateIndirect,"Reference 1"         , GUI_ID_TEXT23,   6,  91,  60, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL                 , GUI_ID_EDIT24,  70,  91,  50, 15, GUI_TA_RIGHT, 20},
	{ TEXT_CreateIndirect,"unit"                , GUI_ID_TEXT24, 122,  91,  40, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,"Reference 2"         , GUI_ID_TEXT25,   6, 108,  60, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL                 , GUI_ID_EDIT26,  70, 108,  50, 15, GUI_TA_RIGHT, 20},
	{ TEXT_CreateIndirect,"unit"                , GUI_ID_TEXT26, 122, 108,  40, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL                 , GUI_ID_EDIT28, 165,  91,  50, 15, GUI_TA_RIGHT, 20},
	{ TEXT_CreateIndirect,"unit"                , GUI_ID_TEXT28, 217,  91,  40, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL                 , GUI_ID_EDIT30, 165, 108,  50, 15, GUI_TA_RIGHT, 20},
	{ TEXT_CreateIndirect,"unit"                , GUI_ID_TEXT30, 217, 108,  40, 15, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect,"Coefficient"         , GUI_ID_TEXT31,   6, 125,  60, 15, TEXT_CF_LEFT},
	{ EDIT_CreateIndirect, NULL                 , GUI_ID_EDIT32,  70, 125,  50, 15, GUI_TA_RIGHT, 20},
	{ TEXT_CreateIndirect,"unit"                , GUI_ID_TEXT32, 122, 125,  50, 15, TEXT_CF_LEFT},

};

void TDUTankDensitySetting::ExecDialogBox(WM_HWIN hCurrentWin, PRogramObject *PROPtr)
{
	CurrentPROPtr = (PROTank *)PROPtr;
	if ( TankWinDensityDiaIsClosed ) {
		TankWinDensityDiaIsClosed = false;
		//	WinHandl = GUI_ExecDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbTankSetup,
		//												hCurrentWin, 0, 0);
		WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbTankSetup,
									   hCurrentWin, 0, 0);
	} else {
		WM_BringToTop(WinHandl);
	}
	GetDialogHandles();
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUTankDensitySetting::GetDialogHandles(void)
{
	hTextName       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT0);
	hRadioLinAPI    = WM_GetDialogItem(WinHandl, GUI_ID_RADIO0);
	hCheckMeasDens  = WM_GetDialogItem(WinHandl, GUI_ID_CHECK0);
//API
	hTextAPI        = WM_GetDialogItem(WinHandl, GUI_ID_TEXT10);
	hDropdAPI       = WM_GetDialogItem(WinHandl, GUI_ID_DROPDOWN1);
	DROPDOWN_SetAutoScroll(hDropdAPI,1);
	hTextAPI1       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT11);
	hEditAPI1       = WM_GetDialogItem(WinHandl, GUI_ID_EDIT11);
	hTextAPI1Unit   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT12);
	hTextAPI2       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT13);
	hEditAPI2       = WM_GetDialogItem(WinHandl, GUI_ID_EDIT13);
	hTextAPI2Unit   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT14);
//Linear
	hCheckLin       = WM_GetDialogItem(WinHandl, GUI_ID_CHECK2);
	hTextLin        = WM_GetDialogItem(WinHandl, GUI_ID_TEXT20);

	hTextSimDens    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT21);
	hEditSimDens    = WM_GetDialogItem(WinHandl, GUI_ID_EDIT21);
	hTextSimDensUnit= WM_GetDialogItem(WinHandl, GUI_ID_TEXT22);

	hTextRef1       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT23);
	hTextRef2       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT25);
	hTextCoeff      = WM_GetDialogItem(WinHandl, GUI_ID_TEXT31);
	hEditTemp1      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT24);
	hTextTemp1Unit  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT24);
	hEditDens1      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT28);
	hTextDens1Unit  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT28);
	hEditTemp2      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT26);
	hTextTemp2Unit  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT26);
	hEditDens2      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT30);
	hTextDens2Unit  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT30);
	hEditCoeff      = WM_GetDialogItem(WinHandl, GUI_ID_EDIT32);
	hTextCoeffUnit  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT32);

	InitDialog();
}

void TDUTankDensitySetting::InitDialog(void)
{
	if ( CurrentPROPtr!=NULL ) {
		/* Initialize all widgets */
		AnsiString str =(AnsiString)"Name: "+(AnsiString)LibGetValue(SVT_PRO_NAME, CurrentPROPtr);
		TEXT_SetFont(hTextName,&TDU_FONT_HW);
		TEXT_SetText(hTextName, str.c_str());
		int Type = CurrentPROPtr->CargoType;// LibGetValue(SVT_CARGO_TYPE,CurrentPROPtr);
		int Sensors = CurrentPROPtr->AnalogInCount;
		RADIO_SetText(hRadioLinAPI, "Linear", 0);
		RADIO_SetText(hRadioLinAPI, "API / ASTM-IP", 1);
		if ( CurrentPROPtr->AnalogInCount < 2 ) {
			WM_DisableWindow(hCheckMeasDens);
		}
		switch ( CurrentPROPtr->TankType ) {
//            case TANKTYPE_NONE   :
		case TANKTYPE_CARGO  :
		case TANKTYPE_MISC   :
			switch ( CurrentPROPtr->CargoType ) {
			case CTY_NOT_DEFINED:
			case CTY_SIMPLE_LIN :
			case CTY_LINEAR     :
				UseLinear();
				break;
			case CTY_BALLAST    :
			case CTY_HFO        :
			case CTY_DO         :
			case CTY_LUB        :
			case CTY_FW         :
				//   case CTY_MISC	    :
			case CTY_SEA        :
				WM_DisableWindow(hRadioLinAPI);
				UseLinear();
				break;
			case CTY_API_6A     :
			case CTY_API_6B     :
			case CTY_API_6D     :
			case CTY_API_53A    :
			case CTY_API_53B    :
			case CTY_API_53D    :
			case CTY_API_53E    :
			case CTY_API_54A    :
			case CTY_API_54B    :
			case CTY_API_54D    :
			case CTY_API_54E    :
			case CTY_API_59A    :
			case CTY_API_59B    :
			case CTY_API_59D    :
			case CTY_API_59E    :
			case CTY_API_60A    :
			case CTY_API_60B    :
			case CTY_API_60D    :
			case CTY_API_60E    :
				UseAPI();
				break;
			}
			break;
		case TANKTYPE_BALLAST   :
		case TANKTYPE_HFO       :
		case TANKTYPE_DO        :
		case TANKTYPE_LUB       :
		case TANKTYPE_FW        :
			WM_DisableWindow(hRadioLinAPI);
			WM_DisableWindow(hCheckLin);
			UseLinear();
			break;
		}

		if ( CurrentPROPtr->TankType < CTY_API_6A ) {
			UseLinear();
		} else {
			UseAPI();
		}
		while ( DROPDOWN_GetNumItems(hDropdAPI)>0 ) {
			DROPDOWN_DeleteItem(hDropdAPI, 0);
		}
		DROPDOWN_AddString(hDropdAPI, "6A");
		DROPDOWN_AddString(hDropdAPI, "6B");
		DROPDOWN_AddString(hDropdAPI, "6D");
		DROPDOWN_AddString(hDropdAPI, "53A");
		DROPDOWN_AddString(hDropdAPI, "53B");
		DROPDOWN_AddString(hDropdAPI, "53D");
		DROPDOWN_AddString(hDropdAPI, "53E");
		DROPDOWN_AddString(hDropdAPI, "54A");
		DROPDOWN_AddString(hDropdAPI, "54B");
		DROPDOWN_AddString(hDropdAPI, "54D");
		DROPDOWN_AddString(hDropdAPI, "54E");
        DROPDOWN_AddString(hDropdAPI, "59A");
        DROPDOWN_AddString(hDropdAPI, "59B");
        DROPDOWN_AddString(hDropdAPI, "59D");
        DROPDOWN_AddString(hDropdAPI, "59E");
        DROPDOWN_AddString(hDropdAPI, "60A");
        DROPDOWN_AddString(hDropdAPI, "60B");
        DROPDOWN_AddString(hDropdAPI, "60D");
        DROPDOWN_AddString(hDropdAPI, "60E");
	}
}

void TDUTankDensitySetting::UseAPI(void)
{
	if ( CurrentPROPtr!=NULL ) {
//Linear
		WM_HideWindow(hCheckLin);
		WM_HideWindow(hTextLin );
		WM_HideWindow(hTextSimDens    );
		WM_HideWindow(hEditSimDens    );
		WM_HideWindow(hTextSimDensUnit);
		WM_HideWindow(hTextRef1     );
		WM_HideWindow(hTextRef2     );
		WM_HideWindow(hTextCoeff    );
		WM_HideWindow(hEditTemp1    );
		WM_HideWindow(hTextTemp1Unit);
		WM_HideWindow(hEditDens1    );
		WM_HideWindow(hTextDens1Unit);
		WM_HideWindow(hEditTemp2    );
		WM_HideWindow(hTextTemp2Unit);
		WM_HideWindow(hEditDens2    );
		WM_HideWindow(hTextDens2Unit);
		WM_HideWindow(hEditCoeff    );
		WM_HideWindow(hTextCoeffUnit);
//API
		WM_ShowWindow(hTextAPI     );
		WM_ShowWindow(hDropdAPI    );
		WM_ShowWindow(hTextAPI1    );
		WM_ShowWindow(hEditAPI1    );
		WM_ShowWindow(hTextAPI1Unit);
		WM_ShowWindow(hTextAPI2    );
		WM_ShowWindow(hEditAPI2    );
		WM_ShowWindow(hTextAPI2Unit);
		switch ( CurrentPROPtr->CargoType ) {
		case CTY_API_6A     :
			DROPDOWN_SetSel(hDropdAPI, 0);
			break;
		case CTY_API_6B     :
			DROPDOWN_SetSel(hDropdAPI, 1);
			break;
		case CTY_API_6D     :
			DROPDOWN_SetSel(hDropdAPI, 2);
			break;
		case CTY_API_53A    :
			DROPDOWN_SetSel(hDropdAPI, 3);
			break;
		case CTY_API_53B    :
			DROPDOWN_SetSel(hDropdAPI, 4);
			break;
		case CTY_API_53D    :
			DROPDOWN_SetSel(hDropdAPI, 5);
			break;
		case CTY_API_53E    :
			DROPDOWN_SetSel(hDropdAPI, 6);
			break;
		case CTY_API_54A    :
			DROPDOWN_SetSel(hDropdAPI, 7);
			break;
		case CTY_API_54B    :
			DROPDOWN_SetSel(hDropdAPI, 8);
			break;
		case CTY_API_54D    :
			DROPDOWN_SetSel(hDropdAPI, 9);
			break;
		case CTY_API_54E    :
			DROPDOWN_SetSel(hDropdAPI,10);
			break;
		case CTY_API_59A    :
			DROPDOWN_SetSel(hDropdAPI,11);
			break;
		case CTY_API_59B    :
			DROPDOWN_SetSel(hDropdAPI,12);
			break;
		case CTY_API_59D    :
			DROPDOWN_SetSel(hDropdAPI,13);
			break;
		case CTY_API_59E    :
			DROPDOWN_SetSel(hDropdAPI,14);
			break;
		case CTY_API_60A    :
			DROPDOWN_SetSel(hDropdAPI,15);
			break;
		case CTY_API_60B    :
			DROPDOWN_SetSel(hDropdAPI,16);
			break;
		case CTY_API_60D    :
			DROPDOWN_SetSel(hDropdAPI,17);
			break;
		case CTY_API_60E    :
			DROPDOWN_SetSel(hDropdAPI,18);
			break;
		}
		AnsiString CurValue1, CurUnit1;
		AnsiString CurValue2, CurUnit2;
		switch ( CurrentPROPtr->CargoType ) {
		case CTY_API_6A     :
		case CTY_API_6B     :
		case CTY_API_6D     :
			TEXT_SetText(hTextAPI1, "API");
			TEXT_SetText(hTextAPI2, "VCF");
			CurValue1 = LibGetValue(SVT_CT_API, CurrentPROPtr, &CurUnit1);
			CurValue2 = LibGetValue(SVT_CT_VCF, CurrentPROPtr, &CurUnit2);
			WM_EnableWindow(hEditAPI1);
			WM_DisableWindow(hEditAPI2);
			break;
		case CTY_API_53A    :
		case CTY_API_53B    :
		case CTY_API_53D    :
		case CTY_API_53E    :
		case CTY_API_59A    :
		case CTY_API_59B    :
		case CTY_API_59D    :
		case CTY_API_59E    :
			TEXT_SetText(hTextAPI1, "Reference temperature");
			TEXT_SetText(hTextAPI2, "Density");
			CurValue1 = LibGetValue(SVT_CT_RT2, CurrentPROPtr, &CurUnit1);
			CurValue2 = LibGetValue(SVT_CT_OD2, CurrentPROPtr, &CurUnit2);
			WM_EnableWindow(hEditAPI1);
			WM_EnableWindow(hEditAPI2);
			break;
		case CTY_API_54A    :
		case CTY_API_54B    :
		case CTY_API_54D    :
		case CTY_API_54E    :
		case CTY_API_60A    :
		case CTY_API_60B    :
		case CTY_API_60D    :
		case CTY_API_60E    :
			TEXT_SetText(hTextAPI1, "Reference temperature");
			TEXT_SetText(hTextAPI2, "Density");
			CurValue1 = LibGetValue(SVT_CT_RT1, CurrentPROPtr, &CurUnit1);
			CurValue2 = LibGetValue(SVT_CT_OD1, CurrentPROPtr, &CurUnit2);
			WM_DisableWindow(hEditAPI1);
			WM_EnableWindow(hEditAPI2);
			break;
		}
		EDIT_SetText(hEditAPI1, CurValue1.c_str());
		TEXT_SetText(hTextAPI1Unit, CurUnit1.c_str());
		EDIT_SetText(hEditAPI2, CurValue2.c_str());
		TEXT_SetText(hTextAPI2Unit, CurUnit2.c_str());
	}
}

void TDUTankDensitySetting::UseLinear(void)
{
	if ( CurrentPROPtr!=NULL ) {
//API
		WM_HideWindow(hTextAPI     );
		WM_HideWindow(hDropdAPI    );
		WM_HideWindow(hTextAPI1    );
		WM_HideWindow(hEditAPI1    );
		WM_HideWindow(hTextAPI1Unit);
		WM_HideWindow(hTextAPI2    );
		WM_HideWindow(hEditAPI2    );
		WM_HideWindow(hTextAPI2Unit);
		//Linear
		WM_ShowWindow(hCheckLin);
		WM_ShowWindow(hTextLin );
		AnsiString CurValue1, CurUnit1;
		switch ( CurrentPROPtr->CargoType ) {
		case CTY_NOT_DEFINED:
		case CTY_SIMPLE_LIN :
			CHECKBOX_Uncheck(hCheckLin);
			WM_ShowWindow(hTextSimDens);
			WM_ShowWindow(hEditSimDens);
			WM_ShowWindow(hTextSimDensUnit);
			WM_HideWindow(hTextRef1     );
			WM_HideWindow(hTextRef2     );
			WM_HideWindow(hTextCoeff    );
			WM_HideWindow(hEditTemp1    );
			WM_HideWindow(hTextTemp1Unit);
			WM_HideWindow(hEditDens1    );
			WM_HideWindow(hTextDens1Unit);
			WM_HideWindow(hEditTemp2    );
			WM_HideWindow(hTextTemp2Unit);
			WM_HideWindow(hEditDens2    );
			WM_HideWindow(hTextDens2Unit);
			WM_HideWindow(hEditCoeff    );
			WM_HideWindow(hTextCoeffUnit);
			CurValue1 = LibGetValue(SVT_CT_OD1, CurrentPROPtr, &CurUnit1);
			EDIT_SetText(hEditSimDens, CurValue1.c_str());
			TEXT_SetText(hTextSimDensUnit, CurUnit1.c_str());
			break;
		case CTY_BALLAST:
		case CTY_HFO    :
		case CTY_DO     :
		case CTY_LUB    :
		case CTY_FW     :
//            case CTY_MISC	 :
		case CTY_SEA    :
			CHECKBOX_Uncheck(hCheckLin);
			WM_ShowWindow(hTextSimDens);
			WM_ShowWindow(hEditSimDens);
			WM_ShowWindow(hTextSimDensUnit);
			WM_HideWindow(hTextRef1     );
			WM_HideWindow(hTextRef2     );
			WM_HideWindow(hTextCoeff    );
			WM_HideWindow(hEditTemp1    );
			WM_HideWindow(hTextTemp1Unit);
			WM_HideWindow(hEditDens1    );
			WM_HideWindow(hTextDens1Unit);
			WM_HideWindow(hEditTemp2    );
			WM_HideWindow(hTextTemp2Unit);
			WM_HideWindow(hEditDens2    );
			WM_HideWindow(hTextDens2Unit);
			WM_HideWindow(hEditCoeff    );
			WM_HideWindow(hTextCoeffUnit);
			CurValue1 = LibGetValue(SVT_CT_OD1, CurrentPROPtr, &CurUnit1);
			EDIT_SetText(hEditSimDens, CurValue1.c_str());
			TEXT_SetText(hTextSimDensUnit, CurUnit1.c_str());
			break;
		case CTY_LINEAR     :
			CHECKBOX_Check(hCheckLin);
			WM_HideWindow(hTextSimDens    );
			WM_HideWindow(hEditSimDens    );
			WM_HideWindow(hTextSimDensUnit);
			WM_ShowWindow(hTextRef1     );
			WM_ShowWindow(hTextRef2     );
			WM_ShowWindow(hTextCoeff    );
			WM_ShowWindow(hEditTemp1    );
			WM_ShowWindow(hTextTemp1Unit);
			WM_ShowWindow(hEditDens1    );
			WM_ShowWindow(hTextDens1Unit);
			WM_ShowWindow(hEditTemp2    );
			WM_ShowWindow(hTextTemp2Unit);
			WM_ShowWindow(hEditDens2    );
			WM_ShowWindow(hTextDens2Unit);
			WM_ShowWindow(hEditCoeff    );
			WM_DisableWindow(hEditCoeff );
			WM_ShowWindow(hTextCoeffUnit);
			CurValue1 = LibGetValue(SVT_CT_RT1, CurrentPROPtr, &CurUnit1);
			EDIT_SetText(hEditTemp1, CurValue1.c_str());
			TEXT_SetText(hTextTemp1Unit, CurUnit1.c_str());
			CurValue1 = LibGetValue(SVT_CT_OD1, CurrentPROPtr, &CurUnit1);
			EDIT_SetText(hEditDens1, CurValue1.c_str());
			TEXT_SetText(hTextDens1Unit, CurUnit1.c_str());
			CurValue1 = LibGetValue(SVT_CT_RT2, CurrentPROPtr, &CurUnit1);
			EDIT_SetText(hEditTemp2, CurValue1.c_str());
			TEXT_SetText(hTextTemp2Unit, CurUnit1.c_str());
			CurValue1 = LibGetValue(SVT_CT_OD2, CurrentPROPtr, &CurUnit1);
			EDIT_SetText(hEditDens2, CurValue1.c_str());
			TEXT_SetText(hTextDens2Unit, CurUnit1.c_str());
			CurValue1 = LibGetValue(SVT_CT_COEFF, CurrentPROPtr, &CurUnit1);
			EDIT_SetText(hEditCoeff, CurValue1.c_str());
			TEXT_SetText(hTextCoeffUnit, CurUnit1.c_str());

			break;
		}

	}
}

void TDUTankDensitySetting::UpdateDialog(int key, AnsiString ValueString)
{
	if ( CurrentPROPtr!=NULL ) {
		LibPutValue( SVT_CT_OD1, CurrentPROPtr, ValueString);
	}
}

void TDUTankDensitySetting::cbTankSetup(WM_MESSAGE * pMsg)
{
	int NCode, Id;
	WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	case WM_PAINT:
		GUI_DrawRect(   2,  22, 110,  62);
		GUI_DrawRect( 120,  24, 260,  46);
		GUI_DrawRect(   2,  70, 270, 146);
		//GUI_DrawRect(  86, 80, 174, 140);
		break;
	case WM_INIT_DIALOG:
//			TankDensitySetting->GetDialogHandles();
		break;
	case MESSAGE_KEYPAD_RETURN:
		{
			int ValueId = pMsg->hWinSrc;
			char StringBuf[BUF_SIZE]={""};
			strcpy( StringBuf,(char *)pMsg->Data.p);
			TankDensitySetting->UpdateDialog( ValueId, StringBuf);
		}
		break;
	case WM_TOUCH_CHILD:
		{
			Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
			NCode = pMsg->Data.v;				/* Notification code */
			switch ( Id ) {
			case GUI_ID_EDIT0:
				KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),"New Density ",Id);
				break;
			}
		}
		break;
	case WM_KEY:
/*			switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) {
				case GUI_KEY_ESCAPE:
						GUI_EndDialog(hWin, 1);
					break;
				case GUI_KEY_ENTER:
						GUI_EndDialog(hWin, 0);
					break;
			}
*/          break;
	case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
		NCode = pMsg->Data.v;				/* Notification code */
		switch ( NCode ) {
		case WM_NOTIFICATION_SEL_CHANGED:
			switch ( Id ) {
			case GUI_ID_DROPDOWN1:
				{
					int type;
					switch ( DROPDOWN_GetSel(TankDensitySetting->hDropdAPI) ) {
					case 0:
						type = CTY_API_6A;
						break;
					case 1:
						type = CTY_API_6B;
						break;
					case 2:
						type = CTY_API_6D;
						break;
					case 3:
						type = CTY_API_53A;
						break;
					case 4:
						type = CTY_API_53B;
						break;
					case 5:
						type = CTY_API_53D;
						break;
					case 6:
						type = CTY_API_53E;
						break;
					case 7:
						type = CTY_API_54A;
						break;
					case 8:
						type = CTY_API_54B;
						break;
					case 9:
						type = CTY_API_54D;
						break;
					case 10:
						type = CTY_API_54E;
						break;
					case 11:
						type = CTY_API_59A;
						break;
					case 12:
						type = CTY_API_59B;
						break;
					case 13:
						type = CTY_API_59D;
						break;
					case 14:
						type = CTY_API_59E;
						break;
					case 15:
						type = CTY_API_60A;
						break;
					case 16:
						type = CTY_API_60B;
						break;
					case 17:
						type = CTY_API_60D;
						break;
					case 18:
						type = CTY_API_60E;
						break;
					}
					TankDensitySetting->CurrentPROPtr->CargoType = type;
					TankDensitySetting->UseAPI();
				}
				break;
			}
			break;
		case WM_NOTIFICATION_VALUE_CHANGED:
			switch ( Id ) {
			case GUI_ID_RADIO0:
				if ( RADIO_GetValue(TankDensitySetting->hRadioLinAPI)==0 ) {
					if ( CHECKBOX_IsChecked(TankDensitySetting->hCheckLin) ) {
						TankDensitySetting->CurrentPROPtr->CargoType = CTY_LINEAR;
					} else {
						TankDensitySetting->CurrentPROPtr->CargoType = CTY_SIMPLE_LIN;
					}
					TankDensitySetting->UseLinear();
				} else {
					TankDensitySetting->CurrentPROPtr->CargoType = CTY_API_54A;
					TankDensitySetting->UseAPI();
				}
				break;
			}
			break;
		case WM_NOTIFICATION_RELEASED:	  /* React only if released */
			switch ( Id ) {
			case GUI_ID_CHECK0:
				break;
			case GUI_ID_CHECK2:
				if ( CHECKBOX_IsChecked(TankDensitySetting->hCheckLin) ) {
					TankDensitySetting->CurrentPROPtr->CargoType = CTY_LINEAR;
				} else {
					TankDensitySetting->CurrentPROPtr->CargoType = CTY_SIMPLE_LIN;
				}
				TankDensitySetting->UseLinear();
				break;
			case GUI_ID_MAXIMIZE: /* Next Button */
				{
					if ( !TankWinDensityDiaIsClosed ) {
						TankWinDensityDiaIsClosed = true;
						GUI_EndDialog(TankDensitySetting->WinHandl, 0);
					}
					TankAlarmSetting->ExecDialogBox(CurrentWinHandl,TankDensitySetting->CurrentPROPtr);
				}
				break;
			case GUI_ID_CLOSE:
				{		   /* Close Button */
					if ( !TankWinDensityDiaIsClosed ) {
						TankWinDensityDiaIsClosed = true;
						GUI_EndDialog(TankDensitySetting->WinHandl, 0);
					}
					if ( !TankWinAlarmDiaIsClosed ) {
						TankWinAlarmDiaIsClosed = true;
						GUI_EndDialog(TankAlarmSetting->WinHandl, 0);
					}
					if ( !TankWinSensorDiaIsClosed ) {
						TankWinSensorDiaIsClosed = true;
						GUI_EndDialog(SensorSetting->WinHandl, 0);
					}
				}
				break;
			}
			break;
		}
		break;
	case WM_NOTIFY_CHILD_HAS_FOCUS:
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}
