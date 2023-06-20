#include "TDUIncludes.h"

TDUSensorSetting::~TDUSensorSetting(void)
{
}

TDUSensorSetting::TDUSensorSetting(void)
{
	CurrentPROPtr = NULL;
	TankWinSensorDiaIsClosed = true;
}

const GUI_WIDGET_CREATE_INFO TDUSensorSetting::aDialogCreate[] =
{
	{ FRAMEWIN_CreateIndirect,"Sensor adjustments", 0, 0, 0, 0, 0, FRAMEWIN_CF_MOVEABLE, 0 },
	{ BUTTON_CreateIndirect, "Pin"	,		GUI_ID_MAXIMIZE, 210,   4,  60, 20 },
    { BUTTON_CreateIndirect, "< Prev", GUI_ID_MINIMIZE,  10, 154,  80, 22 },
	{ BUTTON_CreateIndirect, "Close" ,    GUI_ID_CLOSE, 190, 154,  80, 22 },
    { TEXT_CreateIndirect, "Tag"			,	GUI_ID_TEXT6,  20,   4,200, 16, TEXT_CF_LEFT },

    { TEXT_CreateIndirect, "Location"	,	GUI_ID_TEXT0,   2,  30, 50, 15, TEXT_CF_HCENTER },
	{ TEXT_CreateIndirect, "Ena"			,	GUI_ID_TEXT20, 52,  30, 20, 15, TEXT_CF_HCENTER },
	{ TEXT_CreateIndirect, "Gain"			,	GUI_ID_TEXT7,  70,  30, 50, 15, TEXT_CF_HCENTER },
	{ TEXT_CreateIndirect, "Offset"		,	GUI_ID_TEXT8, 120,  30, 50, 15, TEXT_CF_HCENTER },
	{ TEXT_CreateIndirect, "Value"		,	GUI_ID_TEXT9, 170,  30, 50, 15, TEXT_CF_HCENTER },

	{ CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK1,	 52,  50,  0, 0 },
	{ CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK2,	 52,  70,  0, 0 },
	{ CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK3,	 52,  90,  0, 0 },
	{ CHECKBOX_CreateIndirect, NULL, GUI_ID_CHECK4,	 52, 110,  0, 0 },

	{ TEXT_CreateIndirect, ""	,		   GUI_ID_TEXT10, 223,  50, 60, 15, TEXT_CF_LEFT },
	{ TEXT_CreateIndirect, ""	,		   GUI_ID_TEXT11, 223,  70, 60, 15, TEXT_CF_LEFT },
	{ TEXT_CreateIndirect, ""	,		   GUI_ID_TEXT12, 223,  90, 60, 15, TEXT_CF_LEFT },
	{ TEXT_CreateIndirect, ""	,			 GUI_ID_TEXT13, 223, 110, 60, 15, TEXT_CF_LEFT },

	{ TEXT_CreateIndirect, ""	,				GUI_ID_TEXT1,   2,  50, 50, 15, TEXT_CF_LEFT },
	{ TEXT_CreateIndirect, ""	,				GUI_ID_TEXT2,   2,  70, 50, 15, TEXT_CF_LEFT },
	{ TEXT_CreateIndirect, ""	,				GUI_ID_TEXT3,   2,  90, 50, 15, TEXT_CF_LEFT },
	{ TEXT_CreateIndirect, ""	,				GUI_ID_TEXT4,   2, 110, 50, 15, TEXT_CF_LEFT },

	{ EDIT_CreateIndirect, NULL,			GUI_ID_EDIT1,  70,  50, 50, 15, GUI_TA_RIGHT, 20 },
	{ EDIT_CreateIndirect, NULL,			GUI_ID_EDIT2,  70,  70, 50, 15, GUI_TA_RIGHT, 20 },
	{ EDIT_CreateIndirect, NULL,			GUI_ID_EDIT3,  70,  90, 50, 15, GUI_TA_RIGHT, 20 },
	{ EDIT_CreateIndirect, NULL,			GUI_ID_EDIT4,  70, 110, 50, 15, GUI_TA_RIGHT, 20 },

	{ EDIT_CreateIndirect, NULL,		 GUI_ID_EDIT11, 120,  50, 50, 15, GUI_TA_RIGHT, 20 },
	{ EDIT_CreateIndirect, NULL,		 GUI_ID_EDIT12, 120,  70, 50, 15, GUI_TA_RIGHT, 20 },
	{ EDIT_CreateIndirect, NULL,		 GUI_ID_EDIT13, 120,  90, 50, 15, GUI_TA_RIGHT, 20 },
	{ EDIT_CreateIndirect, NULL,		 GUI_ID_EDIT14, 120, 110, 50, 15, GUI_TA_RIGHT, 20 },

	{ EDIT_CreateIndirect, NULL,		 GUI_ID_EDIT21, 170,  50, 50, 15, GUI_TA_RIGHT, 20 },
	{ EDIT_CreateIndirect, NULL,		 GUI_ID_EDIT22, 170,  70, 50, 15, GUI_TA_RIGHT, 20 },
	{ EDIT_CreateIndirect, NULL,		 GUI_ID_EDIT23, 170,  90, 50, 15, GUI_TA_RIGHT, 20 },
	{ EDIT_CreateIndirect, NULL,		 GUI_ID_EDIT24, 170, 110, 50, 15, GUI_TA_RIGHT, 20 },

};

void TDUSensorSetting::ExecDialogBox(WM_HWIN hCurrentWin,PRogramObject *PROPtr)
{
	CurrentPROPtr = PROPtr;
	if(TankWinSensorDiaIsClosed)
	{
		TankWinSensorDiaIsClosed = false;
	//	WinHandl = GUI_ExecDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbTankSetup,
	//												hCurrentWin, 0, 0);
		WinHandl = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate),&cbTankSetup,
													hCurrentWin, 0, 0);
	}else{
		WM_BringToTop(WinHandl);
	}
	GetDialogHandles();
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUSensorSetting::GetDialogHandles(void)
{
		/* Get window handles for all widgets */
		hText6 = WM_GetDialogItem(WinHandl, GUI_ID_TEXT6);
		hText1 = WM_GetDialogItem(WinHandl, GUI_ID_TEXT1);
		hText2 = WM_GetDialogItem(WinHandl, GUI_ID_TEXT2);
		hText3 = WM_GetDialogItem(WinHandl, GUI_ID_TEXT3);
		hText4 = WM_GetDialogItem(WinHandl, GUI_ID_TEXT4);
		hText10 = WM_GetDialogItem(WinHandl, GUI_ID_TEXT10);
		hText11 = WM_GetDialogItem(WinHandl, GUI_ID_TEXT11);
		hText12 = WM_GetDialogItem(WinHandl, GUI_ID_TEXT12);
		hText13 = WM_GetDialogItem(WinHandl, GUI_ID_TEXT13);
		hEdit1 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT1);
		hEdit2 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT2);
		hEdit3 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT3);
		hEdit4 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT4);
		hEdit11 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT11);
		hEdit12 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT12);
		hEdit13 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT13);
		hEdit14 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT14);
		hEdit21 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT21);
		hEdit22 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT22);
		hEdit23 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT23);
		hEdit24 = WM_GetDialogItem(WinHandl, GUI_ID_EDIT24);
		hCheck1 = WM_GetDialogItem(WinHandl, GUI_ID_CHECK1);
		hCheck2 = WM_GetDialogItem(WinHandl, GUI_ID_CHECK2);
		hCheck3 = WM_GetDialogItem(WinHandl, GUI_ID_CHECK3);
		hCheck4 = WM_GetDialogItem(WinHandl, GUI_ID_CHECK4);
		InitDialog();
}

void TDUSensorSetting::InitDialog(void)
{
	if(CurrentPROPtr!=NULL){
		/* Initialize all widgets */
        AnsiString str =(AnsiString)"Name: "+(AnsiString)LibGetValue(SVT_PRO_NAME, CurrentPROPtr);
		TEXT_SetFont(hText6,&TDU_FONT_HW);
		TEXT_SetText(hText6, str.c_str());
		AnsiString UnitStr;

		if ( PinUnlock ) {
		{
					WM_EnableWindow(hCheck1);
					WM_EnableWindow(hCheck2);
					WM_EnableWindow(hCheck3);
					WM_EnableWindow(hCheck4);
					WM_EnableWindow(hEdit1);
					WM_DisableWindow(hEdit11);
					WM_EnableWindow(hEdit21);
					WM_EnableWindow(hEdit2);
					WM_DisableWindow(hEdit12);
					WM_EnableWindow(hEdit22);
					WM_EnableWindow(hEdit3);
					WM_DisableWindow(hEdit13);
					WM_EnableWindow(hEdit23);
					WM_EnableWindow(hEdit4);
					WM_DisableWindow(hEdit14);
					WM_EnableWindow(hEdit24);
		}else{
					WM_DisableWindow(hCheck1);
					WM_DisableWindow(hCheck2);
					WM_DisableWindow(hCheck3);
					WM_DisableWindow(hCheck4);
					WM_DisableWindow(hEdit1);
					WM_DisableWindow(hEdit11);
					WM_DisableWindow(hEdit21);
					WM_DisableWindow(hEdit2);
					WM_DisableWindow(hEdit12);
					WM_DisableWindow(hEdit22);
					WM_DisableWindow(hEdit3);
					WM_DisableWindow(hEdit13);
					WM_DisableWindow(hEdit23);
					WM_DisableWindow(hEdit4);
					WM_DisableWindow(hEdit14);
					WM_DisableWindow(hEdit24);
		}

		if(CurrentPROPtr->AnalogInList.size()>= 1)
		{
			if(CurrentPROPtr->AnalogInList[0]->Enable){
				CHECKBOX_Check(hCheck1);
			}else{
				CHECKBOX_Uncheck(hCheck1);
			}
			str = LibGetValue(SVT_AI_LOCATION, CurrentPROPtr->AnalogInList[0],&UnitStr);
			TEXT_SetText(hText1, str.c_str());
			str = LibGetValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[0],&UnitStr);
			EDIT_SetText(hEdit1, str.c_str());
			str = LibGetValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[0],&UnitStr);
			EDIT_SetText(hEdit11, str.c_str());
			str = LibGetValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[0],&UnitStr);
			EDIT_SetText(hEdit21, str.c_str());
			TEXT_SetText(hText10, UnitStr.c_str());
		}else{
					WM_DisableWindow(hCheck1);
					WM_DisableWindow(hEdit1);
					WM_DisableWindow(hEdit11);
					WM_DisableWindow(hEdit21);
		}
		if(CurrentPROPtr->AnalogInList.size()>= 2)
		{
			if(CurrentPROPtr->AnalogInList[1]->Enable){
				CHECKBOX_Check(hCheck2);
			}else{
				CHECKBOX_Uncheck(hCheck2);
			}
			str = LibGetValue(SVT_AI_LOCATION, CurrentPROPtr->AnalogInList[1],&UnitStr);
			TEXT_SetText(hText2, str.c_str());
			str = LibGetValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[1],&UnitStr);
			EDIT_SetText(hEdit2, str.c_str());
			str = LibGetValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[1],&UnitStr);
			EDIT_SetText(hEdit12, str.c_str());
			str = LibGetValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[1],&UnitStr);
			EDIT_SetText(hEdit22, str.c_str());
			TEXT_SetText(hText11, UnitStr.c_str());
		}else{
					WM_DisableWindow(hCheck2);
					WM_DisableWindow(hEdit2);
					WM_DisableWindow(hEdit12);
					WM_DisableWindow(hEdit22);
		}
		if(CurrentPROPtr->AnalogInList.size()>= 3)
		{
			if(CurrentPROPtr->AnalogInList[2]->Enable){
				CHECKBOX_Check(hCheck3);
			}else{
				CHECKBOX_Uncheck(hCheck3);
			}
			str = LibGetValue(SVT_AI_LOCATION, CurrentPROPtr->AnalogInList[2],&UnitStr);
			TEXT_SetText(hText3, str.c_str());
			str = LibGetValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[2],&UnitStr);
			EDIT_SetText(hEdit3, str.c_str());
			str = LibGetValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[2],&UnitStr);
			EDIT_SetText(hEdit13, str.c_str());
			str = LibGetValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[2],&UnitStr);
			EDIT_SetText(hEdit23, str.c_str());
			TEXT_SetText(hText12, UnitStr.c_str());
		}else{
					WM_DisableWindow(hCheck3);
					WM_DisableWindow(hEdit3);
					WM_DisableWindow(hEdit13);
					WM_DisableWindow(hEdit23);
		}
		if(CurrentPROPtr->AnalogInList.size()>= 4)
		{
			if(CurrentPROPtr->AnalogInList[3]->Enable){
				CHECKBOX_Check(hCheck4);
			}else{
				CHECKBOX_Uncheck(hCheck4);
			}
			str = LibGetValue(SVT_AI_LOCATION, CurrentPROPtr->AnalogInList[3],&UnitStr);
			TEXT_SetText(hText4, str.c_str());
			str = LibGetValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[3],&UnitStr);
			EDIT_SetText(hEdit4, str.c_str());
			str = LibGetValue(SVT_AI_OFFSET, CurrentPROPtr->AnalogInList[3],&UnitStr);
			EDIT_SetText(hEdit14, str.c_str());
			str = LibGetValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[3],&UnitStr);
			EDIT_SetText(hEdit24, str.c_str());
			TEXT_SetText(hText13, UnitStr.c_str());
		}else{
					WM_DisableWindow(hCheck4);
					WM_DisableWindow(hEdit4);
					WM_DisableWindow(hEdit14);
					WM_DisableWindow(hEdit24);
		}
	}
}

void TDUSensorSetting::UpdateDialog(int key, char *buf)
{
	if(CurrentPROPtr!=NULL){
		switch(key)
		{
			case GUI_ID_CHECK1:
				if(CurrentPROPtr->AnalogInList.size()>= 1)
				{
					CurrentPROPtr->AnalogInList[0]->Enable =(bool)CHECKBOX_IsChecked(hCheck1);
				}
			break;
			case GUI_ID_CHECK2:
				if(CurrentPROPtr->AnalogInList.size()>= 2)
				{
					CurrentPROPtr->AnalogInList[1]->Enable =(bool)CHECKBOX_IsChecked(hCheck2);
				}
			break;
			case GUI_ID_CHECK3:
				if(CurrentPROPtr->AnalogInList.size()>= 3)
				{
					CurrentPROPtr->AnalogInList[2]->Enable =(bool)CHECKBOX_IsChecked(hCheck3);
				}
			break;
			case GUI_ID_CHECK4:
				if(CurrentPROPtr->AnalogInList.size()>= 4)
				{
					CurrentPROPtr->AnalogInList[3]->Enable =(bool)CHECKBOX_IsChecked(hCheck4);
				}
			break;
			case GUI_ID_EDIT1:
				if(CurrentPROPtr->AnalogInList.size()>= 1)
				{
					LibPutValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[0], buf);
					EDIT_SetText(hEdit1, buf);
				}
			break;
			case GUI_ID_EDIT2:
				if(CurrentPROPtr->AnalogInList.size()>= 2)
				{
					LibPutValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[1], buf);
					EDIT_SetText(hEdit2, buf);
				}
			break;
			case GUI_ID_EDIT3:
				if(CurrentPROPtr->AnalogInList.size()>= 3])
				{
					LibPutValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[2], buf);
					EDIT_SetText(hEdit3, buf);
				}
			break;
			case GUI_ID_EDIT4:
				if(CurrentPROPtr->AnalogInList.size()>= 4)
				{
					LibPutValue(SVT_AI_GAIN, CurrentPROPtr->AnalogInList[3], buf);
					EDIT_SetText(hEdit4, buf);
				}
			break;
/*
			case GUI_ID_EDIT11:
				if(TElement->AnalogInList[0])
				{
					LibPutValue(SVT_AI_OFFSET, TElement->AnalogInList[0], buf);
					EDIT_SetText(hEdit0, buf);
				}
			break;
			case GUI_ID_EDIT12:
				if(TElement->AnalogInList[1])
				{
					LibPutValue(SVT_AI_OFFSET, TElement->AnalogInList[1], buf);
					EDIT_SetText(hEdit0, buf);
				}
			break;
			case GUI_ID_EDIT13:
				if(TElement->AnalogInList[2])
				{
					LibPutValue(SVT_AI_OFFSET, TElement->AnalogInList[2], buf);
					EDIT_SetText(hEdit0, buf);
				}
			break;
			case GUI_ID_EDIT14:
				if(TElement->AnalogInList[3])
				{
					LibPutValue(SVT_AI_OFFSET, TElement->AnalogInList[3], buf);
					EDIT_SetText(hEdit0, buf);
				}
			break;
*/
			case GUI_ID_EDIT21:
				if(CurrentPROPtr->AnalogInList.size()>= 1)
				{
					LibPutValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[0], buf);
					EDIT_SetText(hEdit21, buf);
				}
			break;
			case GUI_ID_EDIT22:
				if(CurrentPROPtr->AnalogInList.size()>= 2)
				{
					LibPutValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[1], buf);
					EDIT_SetText(hEdit22, buf);
				}
			break;
			case GUI_ID_EDIT23:
				if(CurrentPROPtr->AnalogInList.size()>= 3)
				{
					LibPutValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[2], buf);
					EDIT_SetText(hEdit23, buf);
				}
			break;
			case GUI_ID_EDIT24:
				if(CurrentPROPtr->AnalogInList.size()>= 4)
				{
					LibPutValue(SVT_AI_CALC_VAL, CurrentPROPtr->AnalogInList[3], buf);
					EDIT_SetText(hEdit24, buf);
				}
			break;
		}
	}
}

/*********************************************************************
*
* Dialog procedure
*/
void TDUSensorSetting::cbTankSetup(WM_MESSAGE * pMsg)
{
	int NCode, Id;
	WM_HWIN hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
		case WM_INIT_DIALOG:
//			SensorSetting->GetDialogHandles();
		break;
		case WM_TOUCH_CHILD:
			{
				Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
				NCode = pMsg->Data.v;               /* Notification code */
				switch(Id){
					case GUI_ID_EDIT1:
					case GUI_ID_EDIT2:
					case GUI_ID_EDIT3:
					case GUI_ID_EDIT4:
/* 					case GUI_ID_EDIT11:
					case GUI_ID_EDIT12:
					case GUI_ID_EDIT13:
					case GUI_ID_EDIT14: */
					case GUI_ID_EDIT21:
					case GUI_ID_EDIT22:
					case GUI_ID_EDIT23:
					case GUI_ID_EDIT24:
						KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(hWin),"Set sensor value ",Id);
					break;
				}
			}
		break;
		case MESSAGE_PINCODE_RETURN:
			{
				int ValueId = pMsg->hWinSrc;
				char StringBuf[BUF_SIZE]={""};
				strcpy( StringBuf,(char *)pMsg->Data.p);
				switch(ValueId)
				{
					case GUI_ID_MAXIMIZE: /* PinCode Button */
                        CheckPinCode(StringBuf);
						SensorSetting->InitDialog();
					break;
                }
            }
        break;
		case MESSAGE_KEYPAD_RETURN:
			{
				int ValueId = pMsg->hWinSrc;
				char StringBuf[BUF_SIZE]={""};
				strcpy( StringBuf,(char *)pMsg->Data.p);
				switch(ValueId)
				{
					//case GUI_ID_MAXIMIZE: /* PinCode Button */
     //                   SensorSetting->PinCodeOK = CheckPinCode(StringBuf);
					//	SensorSetting->InitDialog();
					//break;
					case GUI_ID_EDIT1:
					case GUI_ID_EDIT2:
					case GUI_ID_EDIT3:
					case GUI_ID_EDIT4:
/* 					case GUI_ID_EDIT11:
					case GUI_ID_EDIT12:
					case GUI_ID_EDIT13:
					case GUI_ID_EDIT14: */
					case GUI_ID_EDIT21:
					case GUI_ID_EDIT22:
					case GUI_ID_EDIT23:
					case GUI_ID_EDIT24:
						SensorSetting->UpdateDialog(ValueId,StringBuf);
					break;
				}
			}
		break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
			NCode = pMsg->Data.v;               /* Notification code */
			switch (NCode) {
				case WM_NOTIFICATION_RELEASED:    /* React only if released */
					switch(Id)
					{
						case GUI_ID_CHECK1:
						case GUI_ID_CHECK2:
						case GUI_ID_CHECK3:
						case GUI_ID_CHECK4:
							SensorSetting->UpdateDialog(Id,"");
						break;
						case GUI_ID_MINIMIZE: /* Prev Button */
						{
							if ( !TankWinSensorDiaIsClosed ){
								TankWinSensorDiaIsClosed = true;
								GUI_EndDialog(SensorSetting->WinHandl, 0);
							}
							TankAlarmSetting->ExecDialogBox(CurrentWinHandl,SensorSetting->CurrentPROPtr);
						}
						break;
						case GUI_ID_MAXIMIZE: /* PinCode Button */
                            KeyBoard->ExecKeyBoardPinCode(WM_GetClientWindow(hWin),"Enter Pin code:",Id);
						break;
						case GUI_ID_CLOSE:
						{          /* Close Button */
							if ( !TankWinDensityDiaIsClosed ){
								TankWinDensityDiaIsClosed = true;
								GUI_EndDialog(TankDensitySetting->WinHandl, 0);
							}
							if ( !TankWinAlarmDiaIsClosed ){
								TankWinAlarmDiaIsClosed = true;
								GUI_EndDialog(TankAlarmSetting->WinHandl, 0);
							}
							if ( !TankWinSensorDiaIsClosed ){
								TankWinSensorDiaIsClosed = true;
								GUI_EndDialog(SensorSetting->WinHandl, 0);
							}
						}
						break;
					}
				break;
				}
			break;
		case WM_KEY:
		break;
		case WM_NOTIFY_CHILD_HAS_FOCUS:
		break;
		default:
		WM_DefaultProc(pMsg);
	}
}
