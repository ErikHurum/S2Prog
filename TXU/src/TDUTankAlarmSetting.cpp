#include "TDUIncludes.h"

TDUTankAlarmSetting::~TDUTankAlarmSetting(void)
{
}

TDUTankAlarmSetting::TDUTankAlarmSetting(void)
{
	TankWinAlarmDiaIsClosed = true;
}

const GUI_WIDGET_CREATE_INFO TDUTankAlarmSetting::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect, "Alarm settings", 0, 0, 0, 0, 0, FRAMEWIN_CF_MOVEABLE, 0},
	{ BUTTON_CreateIndirect, "< Prev", GUI_ID_MINIMIZE,  10, 154,  80, 22},
	{ BUTTON_CreateIndirect, "Next >", GUI_ID_MAXIMIZE, 100, 154,  80, 22},
	{ BUTTON_CreateIndirect, "Close" ,    GUI_ID_CLOSE, 190, 154,  80, 22},

	{ CHECKBOX_CreateIndirect, NULL  , GUI_ID_CHECK1,  10,  20,   0, 0},
	{ CHECKBOX_CreateIndirect, NULL  , GUI_ID_CHECK2,  10,  39,   0, 0},
	{ CHECKBOX_CreateIndirect, NULL  , GUI_ID_CHECK3,  10,  58,   0, 0},
	{ CHECKBOX_CreateIndirect, NULL  , GUI_ID_CHECK4,  10,  77,   0, 0},
	{ CHECKBOX_CreateIndirect, NULL  , GUI_ID_CHECK5,  10,  96,   0, 0},
	{ CHECKBOX_CreateIndirect, NULL  , GUI_ID_CHECK6,  10, 115,   0, 0},
	{ CHECKBOX_CreateIndirect, NULL  , GUI_ID_CHECK7,  10, 134,   0, 0},

	{ TEXT_CreateIndirect, "Tag"      , GUI_ID_TEXT0,  30,   4, 200, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Overfill"           , GUI_ID_TEXT11,  30,  20, 100, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "High Level"         , GUI_ID_TEXT12,  30,  39, 100, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Low Level"          , GUI_ID_TEXT13,  30,  58, 100, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "High Temp"          , GUI_ID_TEXT14,  30,  77, 100, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Low Temp"           , GUI_ID_TEXT15,  30,  96, 100, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "High Tank Press"    , GUI_ID_TEXT16,  30, 115, 100, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, "Low Tank Press"     , GUI_ID_TEXT17,  30, 134, 100, 16, TEXT_CF_LEFT},

	{ EDIT_CreateIndirect, NULL       , GUI_ID_EDIT1, 130,  20,  50, 16, GUI_TA_RIGHT, 20},
	{ EDIT_CreateIndirect, NULL       , GUI_ID_EDIT2, 130,  39,  50, 16, GUI_TA_RIGHT, 20},
	{ EDIT_CreateIndirect, NULL       , GUI_ID_EDIT3, 130,  58,  50, 16, GUI_TA_RIGHT, 20},
	{ EDIT_CreateIndirect, NULL       , GUI_ID_EDIT4, 130,  77,  50, 16, GUI_TA_RIGHT, 20},
	{ EDIT_CreateIndirect, NULL       , GUI_ID_EDIT5, 130,  96,  50, 16, GUI_TA_RIGHT, 20},
	{ EDIT_CreateIndirect, NULL       , GUI_ID_EDIT6, 130, 115,  50, 16, GUI_TA_RIGHT, 20},
	{ EDIT_CreateIndirect, NULL       , GUI_ID_EDIT7, 130, 134,  50, 16, GUI_TA_RIGHT, 20},

	{ TEXT_CreateIndirect, ""         , GUI_ID_TEXT1, 184,  20,  80, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, ""         , GUI_ID_TEXT2, 184,  39,  80, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, ""         , GUI_ID_TEXT3, 184,  58,  80, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, ""         , GUI_ID_TEXT4, 184,  77,  80, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, ""         , GUI_ID_TEXT5, 184,  96,  80, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, ""         , GUI_ID_TEXT6, 184, 115,  80, 16, TEXT_CF_LEFT},
	{ TEXT_CreateIndirect, ""         , GUI_ID_TEXT7, 184, 134,  80, 16, TEXT_CF_LEFT},

//	{ SLIDER_CreateIndirect, NULL, GUI_ID_SLIDER0, 60, 140, 100, 20 },
//	{ SLIDER_CreateIndirect, NULL, GUI_ID_SLIDER1, 10, 170, 150, 30 }
};

void TDUTankAlarmSetting::ExecDialogBox(WM_HWIN hCurrentWin,PRogramObject *PROPtr)
{
	CurrentPROPtr = PROPtr;
	if ( TankWinAlarmDiaIsClosed ) {
		TankWinAlarmDiaIsClosed = false;
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
void TDUTankAlarmSetting::GetDialogHandles(void)
{
	/* Get window handles for all widgets */
	hTextName       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT0);
	hTextOverfill   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT1);
	hTextHighLev    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT2);
	hTextLowLev     = WM_GetDialogItem(WinHandl, GUI_ID_TEXT3);
	hTextHighTemp   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT4);
	hTextLowTemp    = WM_GetDialogItem(WinHandl, GUI_ID_TEXT5);
	hTextHighPress  = WM_GetDialogItem(WinHandl, GUI_ID_TEXT6);
	hTextLowPress   = WM_GetDialogItem(WinHandl, GUI_ID_TEXT7);
	hOverfill       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT11);
	hHighLev        = WM_GetDialogItem(WinHandl, GUI_ID_TEXT12);
	hLowLev         = WM_GetDialogItem(WinHandl, GUI_ID_TEXT13);
	hHighTemp       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT14);
	hLowTemp        = WM_GetDialogItem(WinHandl, GUI_ID_TEXT15);
	hHighPress      = WM_GetDialogItem(WinHandl, GUI_ID_TEXT16);
	hLowPress       = WM_GetDialogItem(WinHandl, GUI_ID_TEXT17);
	hEditOverfill   = WM_GetDialogItem(WinHandl, GUI_ID_EDIT1);
	hEditHighLev    = WM_GetDialogItem(WinHandl, GUI_ID_EDIT2);
	hEditLowLev     = WM_GetDialogItem(WinHandl, GUI_ID_EDIT3);
	hEditHighTemp   = WM_GetDialogItem(WinHandl, GUI_ID_EDIT4);
	hEditLowTemp    = WM_GetDialogItem(WinHandl, GUI_ID_EDIT5);
	hEditHighPress  = WM_GetDialogItem(WinHandl, GUI_ID_EDIT6);
	hEditLowPress   = WM_GetDialogItem(WinHandl, GUI_ID_EDIT7);
	hCheckOverfill  = WM_GetDialogItem(WinHandl, GUI_ID_CHECK1);
	hCheckHighLev   = WM_GetDialogItem(WinHandl, GUI_ID_CHECK2);
	hCheckLowLev    = WM_GetDialogItem(WinHandl, GUI_ID_CHECK3);
	hCheckHighTemp  = WM_GetDialogItem(WinHandl, GUI_ID_CHECK4);
	hCheckLowTemp   = WM_GetDialogItem(WinHandl, GUI_ID_CHECK5);
	hCheckHighPress = WM_GetDialogItem(WinHandl, GUI_ID_CHECK6);
	hCheckLowPress  = WM_GetDialogItem(WinHandl, GUI_ID_CHECK7);
	hPrevBut        = WM_GetDialogItem(WinHandl, GUI_ID_MINIMIZE);
	InitDialog();
}

void TDUTankAlarmSetting::InitDialog(void)
{
	if ( CurrentPROPtr!=NULL ) {
		//WM_EnableWindow(hPrevBut);
		//WM_EnableWindow(hEditOverfill);
		//WM_EnableWindow(hEditHighLev);
		//WM_EnableWindow(hEditLowLev);
		//WM_EnableWindow(hEditHighPress);
		//WM_EnableWindow(hEditLowPress);
		//WM_EnableWindow(hTextOverfill);
		//WM_EnableWindow(hTextHighLev);
		//WM_EnableWindow(hTextLowLev);
		//WM_EnableWindow(hTextHighPress);
		//WM_EnableWindow(hTextLowPress);
		//WM_EnableWindow(hCheckOverfill);
		//WM_EnableWindow(hCheckHighLev);
		//WM_EnableWindow(hCheckLowLev);
		//WM_EnableWindow(hCheckHighPress);
		//WM_EnableWindow(hCheckLowPress);

		switch ( CurrentWinID ) {
		case TDU_MAIN_WIN:
		case TDU_HEAD_WIN:
		case TDU_BUT_WIN:
		case TDU_PRESENT_WIN:
		case TDU_SYSTEM_WIN:
		case TDU_ALARM_WIN:
			break;
		case TDU_CARGO_WIN:
		case TDU_BALLAST_WIN:
		case TDU_SERVICE_WIN:
		case TDU_TANKFARM_WIN:
			{
				PROTank *TElement = (PROTank*)CurrentPROPtr;
				if ( TElement!=NULL ) {
					/* Initialize all widgets */
					AnsiString str =(AnsiString)"Name: "+(AnsiString)LibGetValue(SVT_PRO_NAME, TElement);
					TEXT_SetFont(hTextName,&TDU_FONT_HW);
					TEXT_SetText(hTextName, str.c_str());
					AnsiString UnitStr;
					if ( TElement->OverfillPtr ) {
						if ( TElement->OverfillPtr->Enable ) {
							CHECKBOX_Check(hCheckOverfill);
						} else {
							CHECKBOX_Uncheck(hCheckOverfill);
						}
						str = LibGetValue(SVT_AL_LIMIT, TElement->OverfillPtr,&UnitStr);
						EDIT_SetText(hEditOverfill, str.c_str());
						TEXT_SetText(hTextOverfill, UnitStr.c_str());
					} else {
						WM_HideWindow(hOverfill);
						WM_HideWindow(hEditOverfill);
						WM_HideWindow(hTextOverfill);
						WM_HideWindow(hCheckOverfill);
					}
					if ( TElement->HighLevelPtr->Enable ) {
						CHECKBOX_Check(hCheckHighLev);
					} else {
						CHECKBOX_Uncheck(hCheckHighLev);
					}
					if ( TElement->LowLevelPtr->Enable ) {
						CHECKBOX_Check(hCheckLowLev);
					} else {
						CHECKBOX_Uncheck(hCheckLowLev);
					}
					str = LibGetValue(SVT_AL_LIMIT, TElement->HighLevelPtr,&UnitStr);
					EDIT_SetText(hEditHighLev, str.c_str());
					TEXT_SetText(hTextHighLev, UnitStr.c_str());
					str = LibGetValue(SVT_AL_LIMIT, TElement->LowLevelPtr,&UnitStr);
					EDIT_SetText(hEditLowLev, str.c_str());
					TEXT_SetText(hTextLowLev, UnitStr.c_str());


					if ( TElement->TemperaturePtr ) {
						if ( TElement->TemperaturePtr->HighTempPtr->Enable ) {
							CHECKBOX_Check(hCheckHighTemp);
						} else {
							CHECKBOX_Uncheck(hCheckHighTemp);
						}
						if ( TElement->TemperaturePtr->LowTempPtr->Enable ) {
							CHECKBOX_Check(hCheckLowTemp);
						} else {
							CHECKBOX_Uncheck(hCheckLowTemp);
						}
						str = LibGetValue(SVT_AL_LIMIT, TElement->TemperaturePtr->HighTempPtr,&UnitStr);
						EDIT_SetText(hEditHighTemp, str.c_str());
						TEXT_SetText(hTextHighTemp, UnitStr.c_str());
						str = LibGetValue(SVT_AL_LIMIT, TElement->TemperaturePtr->LowTempPtr,&UnitStr);
						EDIT_SetText(hEditLowTemp, str.c_str());
						TEXT_SetText(hTextLowTemp, UnitStr.c_str());
					} else {
						//WM_DisableWindow(hCheckHighTemp);
						//WM_DisableWindow(hCheckLowTemp);
						//WM_DisableWindow(hEditHighTemp);
						//WM_DisableWindow(hEditLowTemp);
						WM_HideWindow(hHighTemp);
						WM_HideWindow(hLowTemp);
						WM_HideWindow(hCheckHighTemp);
						WM_HideWindow(hCheckLowTemp);
						WM_HideWindow(hEditHighTemp);
						WM_HideWindow(hEditLowTemp);
						WM_HideWindow(hTextHighTemp);
						WM_HideWindow(hTextLowTemp);
					}
					if ( TElement->PressurePtr ) {
						if ( TElement->PressurePtr->HighPressurePtr->Enable ) {
							CHECKBOX_Check(hCheckHighPress);
						} else {
							CHECKBOX_Uncheck(hCheckHighPress);
						}
						if ( TElement->PressurePtr->LowPressurePtr->Enable ) {
							CHECKBOX_Check(hCheckLowPress);
						} else {
							CHECKBOX_Uncheck(hCheckLowPress);
						}
						str = LibGetValue(SVT_AL_LIMIT, TElement->PressurePtr->HighPressurePtr,&UnitStr);
						EDIT_SetText(hEditHighPress, str.c_str());
						TEXT_SetText(hTextHighPress, UnitStr.c_str());
						str = LibGetValue(SVT_AL_LIMIT, TElement->PressurePtr->LowPressurePtr,&UnitStr);
						EDIT_SetText(hEditLowPress, str.c_str());
						TEXT_SetText(hTextLowPress, UnitStr.c_str());
					} else {
						//WM_DisableWindow(hCheckHighPress);
						//WM_DisableWindow(hCheckLowPress);
						//WM_DisableWindow(hEditHighPress);
						//WM_DisableWindow(hEditLowPress);
						WM_HideWindow(hHighPress);
						WM_HideWindow(hLowPress);
						WM_HideWindow(hCheckHighPress);
						WM_HideWindow(hCheckLowPress);
						WM_HideWindow(hTextHighPress);
						WM_HideWindow(hTextLowPress);
						WM_HideWindow(hEditHighPress);
						WM_HideWindow(hEditLowPress);
					}
				}
			}
			break;
		case TDU_TANKPRESS_WIN:
			{
				PROTankPressure *TElement = (PROTankPressure*)CurrentPROPtr;
				if ( TElement!=NULL ) {
					//WM_DisableWindow(hPrevBut);
					//WM_DisableWindow(hEditOverfill);
					//WM_DisableWindow(hEditHighLev);
					//WM_DisableWindow(hEditLowLev);
					//WM_DisableWindow(hEditHighTemp);
					//WM_DisableWindow(hEditLowTemp);
					//WM_DisableWindow(hTextOverfill);
					//WM_DisableWindow(hTextHighLev);
					//WM_DisableWindow(hTextHighTemp);
					//WM_DisableWindow(hTextHighPress);
					//   WM_DisableWindow(hCheckOverfill);
					//WM_DisableWindow(hCheckHighLev);
					//WM_DisableWindow(hCheckLowLev);
					//WM_DisableWindow(hCheckHighTemp);
					//WM_DisableWindow(hCheckLowTemp);
					WM_HideWindow(hPrevBut);
					WM_HideWindow(hOverfill);
					WM_HideWindow(hHighLev);
					WM_HideWindow(hLowLev);
					WM_HideWindow(hHighTemp);
					WM_HideWindow(hLowTemp);
					WM_HideWindow(hEditOverfill);
					WM_HideWindow(hEditHighLev);
					WM_HideWindow(hEditLowLev);
					WM_HideWindow(hEditHighTemp);
					WM_HideWindow(hEditLowTemp);
					WM_HideWindow(hTextOverfill);
					WM_HideWindow(hTextHighLev);
					WM_HideWindow(hTextLowLev);
					WM_HideWindow(hTextHighTemp);
					WM_HideWindow(hTextLowTemp);
					WM_HideWindow(hCheckOverfill);
					WM_HideWindow(hCheckHighLev);
					WM_HideWindow(hCheckLowLev);
					WM_HideWindow(hCheckHighTemp);
					WM_HideWindow(hCheckLowTemp);
					/* Initialize all widgets */
					AnsiString str = LibGetValue( SVT_PRO_NAME, TElement);
					TEXT_SetFont(hTextName,&TDU_FONT_HW);
					TEXT_SetText(hTextName, str.c_str());
					AnsiString UnitStr;
					str = LibGetValue(SVT_AL_LIMIT, TElement->HighPressurePtr,&UnitStr);
					EDIT_SetText(hEditHighPress, str.c_str());
					TEXT_SetText(hTextHighPress, UnitStr.c_str());
					str = LibGetValue(SVT_AL_LIMIT, TElement->LowPressurePtr,&UnitStr);
					EDIT_SetText(hEditLowPress, str.c_str());
					TEXT_SetText(hTextLowPress, UnitStr.c_str());

					if ( TElement->HighPressurePtr->Enable ) {
						CHECKBOX_Check(hCheckHighPress);
					} else {
						CHECKBOX_Uncheck(hCheckHighPress);
					}
					if ( TElement->LowPressurePtr->Enable ) {
						CHECKBOX_Check(hCheckLowPress);
					} else {
						CHECKBOX_Uncheck(hCheckLowPress);
					}
				}
			}
			break;
		case TDU_LINEPRESS_WIN:
			break;
		case TDU_TEMP_WIN:
			{
				PROTemperature *TElement = (PROTemperature*)CurrentPROPtr;
				//WM_DisableWindow(hPrevBut);
				//WM_DisableWindow(hEditOverfill);
				//WM_DisableWindow(hEditHighLev);
				//WM_DisableWindow(hEditLowLev);
				//WM_DisableWindow(hEditHighPress);
				//WM_DisableWindow(hEditLowPress);
				//WM_DisableWindow(hTextOverfill);
				//WM_DisableWindow(hTextHighLev);
				//WM_DisableWindow(hTextHighPress);
				//WM_DisableWindow(hTextLowPress);
				//WM_DisableWindow(hCheckOverfill);
				//WM_DisableWindow(hCheckHighLev);
				//WM_DisableWindow(hCheckLowLev);
				//WM_DisableWindow(hCheckHighPress);
				//WM_DisableWindow(hCheckLowPress);
				WM_HideWindow(hPrevBut);
				WM_HideWindow(hOverfill);
				WM_HideWindow(hHighLev);
				WM_HideWindow(hLowLev);
				WM_HideWindow(hHighPress);
				WM_HideWindow(hLowPress);
				WM_HideWindow(hEditOverfill);
				WM_HideWindow(hEditHighLev);
				WM_HideWindow(hEditLowLev);
				WM_HideWindow(hEditHighPress);
				WM_HideWindow(hEditLowPress);
				WM_HideWindow(hTextOverfill);
				WM_HideWindow(hTextHighLev);
				WM_HideWindow(hTextLowLev);
				WM_HideWindow(hTextHighPress);
				WM_HideWindow(hTextLowPress);
				WM_HideWindow(hCheckOverfill);
				WM_HideWindow(hCheckHighLev);
				WM_HideWindow(hCheckLowLev);
				WM_HideWindow(hCheckHighPress);
				WM_HideWindow(hCheckLowPress);

				/* Initialize all widgets */
				AnsiString str = LibGetValue(SVT_PRO_NAME, TElement);
				TEXT_SetFont(hTextName,&TDU_FONT_HW);
				TEXT_SetText(hTextName, str.c_str());
				AnsiString UnitStr;
				str = LibGetValue(SVT_AL_LIMIT, TElement->HighTempPtr,&UnitStr);
				EDIT_SetText(hEditHighTemp, str.c_str());
				TEXT_SetText(hTextHighTemp, UnitStr.c_str());
				str = LibGetValue(SVT_AL_LIMIT, TElement->LowTempPtr,&UnitStr);
				EDIT_SetText(hEditLowTemp, str.c_str());
				TEXT_SetText(hTextLowTemp, UnitStr.c_str());

				if ( TElement->HighTempPtr->Enable ) {
					CHECKBOX_Check(hCheckHighTemp);
				} else {
					CHECKBOX_Uncheck(hCheckHighTemp);
				}
				if ( TElement->LowTempPtr->Enable ) {
					CHECKBOX_Check(hCheckLowTemp);
				} else {
					CHECKBOX_Uncheck(hCheckLowTemp);
				}
			}
			break;
		case TDU_LEVELSWITCH_WIN:
		case TDU_OVERFILL_WIN:
		case TDU_BILGE_WIN:
		case TDU_WATERINGR_WIN:
		default:
			break;
		}
	}
}
void TDUTankAlarmSetting::UpdateDialog(int key, char *buf)
{
	if ( CurrentPROPtr!=NULL ) {
		switch ( CurrentWinID ) {
		case TDU_MAIN_WIN:
		case TDU_HEAD_WIN:
		case TDU_BUT_WIN:
		case TDU_PRESENT_WIN:
		case TDU_SYSTEM_WIN:
		case TDU_ALARM_WIN:
			break;
		case TDU_CARGO_WIN:
		case TDU_BALLAST_WIN:
		case TDU_SERVICE_WIN:
		case TDU_TANKFARM_WIN:
			{
				PROTank *TElement = (PROTank*)CurrentPROPtr;
				if ( TElement!=NULL ) {
					switch ( key ) {
					case GUI_ID_EDIT1:
						LibPutValue(SVT_AL_LIMIT, TElement->OverfillPtr, buf);
						EDIT_SetText(hEditOverfill, buf);
						break;
					case GUI_ID_EDIT2:
						LibPutValue(SVT_AL_LIMIT, TElement->HighLevelPtr, buf);
						EDIT_SetText(hEditHighLev, buf);
						break;
					case GUI_ID_EDIT3:
						LibPutValue(SVT_AL_LIMIT, TElement->LowLevelPtr, buf);
						EDIT_SetText(hEditLowLev, buf);
						break;
					case GUI_ID_EDIT4:
						if ( TElement->TemperaturePtr ) {
							LibPutValue(SVT_AL_LIMIT, TElement->TemperaturePtr->HighTempPtr, buf);
							EDIT_SetText(hEditHighTemp, buf);
						}
						break;
					case GUI_ID_EDIT5:
						if ( TElement->TemperaturePtr ) {
							LibPutValue(SVT_AL_LIMIT, TElement->TemperaturePtr->LowTempPtr, buf);
							EDIT_SetText(hEditLowTemp, buf);
						}
						break;
					case GUI_ID_EDIT6:
						if ( TElement->PressurePtr ) {
							LibPutValue(SVT_AL_LIMIT, TElement->PressurePtr->HighPressurePtr, buf);
							EDIT_SetText(hEditHighPress, buf);
						}
						break;
					case GUI_ID_EDIT7:
						if ( TElement->TemperaturePtr ) {
							LibPutValue(SVT_AL_LIMIT, TElement->PressurePtr->LowPressurePtr, buf);
							EDIT_SetText(hEditLowPress, buf);
						}
						break;
					case GUI_ID_CHECK1:
						TElement->OverfillPtr->Enable =(bool)CHECKBOX_IsChecked(hCheckOverfill);
						break;
					case GUI_ID_CHECK2:
						TElement->HighLevelPtr->Enable =(bool)CHECKBOX_IsChecked(hCheckHighLev);
						break;
					case GUI_ID_CHECK3:
						TElement->LowLevelPtr->Enable =(bool)CHECKBOX_IsChecked(hCheckLowLev);
						break;
					case GUI_ID_CHECK4:
						if ( TElement->TemperaturePtr )TElement->TemperaturePtr->HighTempPtr->Enable =(bool)CHECKBOX_IsChecked(hCheckHighTemp);
						break;
					case GUI_ID_CHECK5:
						if ( TElement->TemperaturePtr )TElement->TemperaturePtr->LowTempPtr->Enable =(bool)CHECKBOX_IsChecked(hCheckLowTemp);
						break;
					case GUI_ID_CHECK6:
						if ( TElement->PressurePtr )TElement->PressurePtr->HighPressurePtr->Enable =(bool)CHECKBOX_IsChecked(hCheckHighPress);
						break;
					case GUI_ID_CHECK7:
						if ( TElement->PressurePtr )TElement->PressurePtr->LowPressurePtr->Enable =(bool)CHECKBOX_IsChecked(hCheckLowPress);
						break;
					}
				}
			}
			break;
		case TDU_TANKPRESS_WIN:
			{
				PROTankPressure *TElement = (PROTankPressure*)CurrentPROPtr;
				if ( TElement!=NULL ) {
					switch ( key ) {
					case GUI_ID_EDIT6:
						LibPutValue(SVT_AL_LIMIT, TElement->HighPressurePtr, buf);
						EDIT_SetText(hEditHighPress, buf);
						break;
					case GUI_ID_EDIT7:
						LibPutValue(SVT_AL_LIMIT, TElement->LowPressurePtr, buf);
						EDIT_SetText(hEditLowPress, buf);
						break;
					case GUI_ID_CHECK6:
						TElement->HighPressurePtr->Enable =(bool)CHECKBOX_IsChecked(hCheckHighPress);
						break;
					case GUI_ID_CHECK7:
						TElement->LowPressurePtr->Enable =(bool)CHECKBOX_IsChecked(hCheckLowPress);
						break;
					}
				}
			}
			break;
		case TDU_LINEPRESS_WIN:
			break;
		case TDU_TEMP_WIN:
			{
				PROTemperature *TElement = (PROTemperature*)CurrentPROPtr;
				if ( TElement!=NULL ) {
					switch ( key ) {
					case GUI_ID_EDIT4:
						LibPutValue(SVT_AL_LIMIT, TElement->HighTempPtr, buf);
						EDIT_SetText(hEditHighTemp, buf);
						break;
					case GUI_ID_EDIT5:
						LibPutValue(SVT_AL_LIMIT, TElement->LowTempPtr, buf);
						EDIT_SetText(hEditLowTemp, buf);
						break;
					case GUI_ID_CHECK4:
						TElement->HighTempPtr->Enable =(bool)CHECKBOX_IsChecked(hCheckHighTemp);
						break;
					case GUI_ID_CHECK5:
						TElement->LowTempPtr->Enable =(bool)CHECKBOX_IsChecked(hCheckHighTemp);
						break;
					}
				}
			}
			break;
		case TDU_LEVELSWITCH_WIN:
		case TDU_OVERFILL_WIN:
		case TDU_BILGE_WIN:
		case TDU_WATERINGR_WIN:
		default:
			break;
		}
	}
}

void TDUTankAlarmSetting::cbTankSetup(WM_MESSAGE * pMsg)
{
	int NCode, Id;
	WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	case WM_INIT_DIALOG:
// 			TankAlarmSetting->GetDialogHandles();
		break;
	case MESSAGE_KEYPAD_RETURN:
		{
			int ValueId = pMsg->hWinSrc;
			char StringBuf[BUF_SIZE]={""};
			strcpy( StringBuf,(char *)pMsg->Data.p);
			TankAlarmSetting->UpdateDialog( ValueId, StringBuf);
		}
		break;
	case WM_TOUCH_CHILD:
		{
			Id    = WM_GetId(pMsg->hWinSrc);	/* Id of widget */
			NCode = pMsg->Data.v;				/* Notification code */
			switch ( Id ) {
			case GUI_ID_EDIT1:
			case GUI_ID_EDIT2:
			case GUI_ID_EDIT3:
				KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),"New Alarm limit ",Id);
				break;
			case GUI_ID_EDIT4:
			case GUI_ID_EDIT5:
				KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),"New Alarm limit ",Id);
				break;
			case GUI_ID_EDIT6:
			case GUI_ID_EDIT7:
				KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),"New Alarm limit ",Id);
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
		case WM_NOTIFICATION_RELEASED:	  /* React only if released */
			switch ( Id ) {
			case GUI_ID_CHECK0:
			case GUI_ID_CHECK1:
			case GUI_ID_CHECK2:
			case GUI_ID_CHECK3:
			case GUI_ID_CHECK4:
			case GUI_ID_CHECK5:
				TankAlarmSetting->UpdateDialog( Id, " ");
				break;
			case GUI_ID_MINIMIZE: /* Prev Button */
				{
					if ( !TankWinAlarmDiaIsClosed ) {
						TankWinAlarmDiaIsClosed = true;
						GUI_EndDialog(TankAlarmSetting->WinHandl, 0);
					}
					TankDensitySetting->ExecDialogBox(CurrentWinHandl,TankAlarmSetting->CurrentPROPtr);
				}
				break;
			case GUI_ID_MAXIMIZE: /* Next Button */
				{
					if ( !TankWinAlarmDiaIsClosed ) {
						TankWinAlarmDiaIsClosed = true;
						GUI_EndDialog(TankAlarmSetting->WinHandl, 0);
					}
					SensorSetting->ExecDialogBox(CurrentWinHandl,TankAlarmSetting->CurrentPROPtr);
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
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}
