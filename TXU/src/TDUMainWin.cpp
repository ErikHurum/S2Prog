#include "TDUIncludes.h"

TDUMainWin::~TDUMainWin(void)
{
}

TDUMainWin::TDUMainWin(void)
{
	BHsize = 34;
	BWsize = 34;
	Height = 18;
	int i=0;
	WinHandl  = WM_CreateWindow(0,0,LCDXSize,LCDYSize,WM_CF_SHOW,NULL,0);

	HeadingText  = TEXT_CreateAsChild(  2, 1, 150, Height, WinHandl, 1, WM_CF_SHOW, "Surveyor2", TEXT_CF_LEFT);
	ButtonAlarm = BUTTON_CreateAsChild(LCDXSize-BWsize-140,0,140,Height,WinHandl,TDU_BUTTON_ID_MW0,WM_CF_SHOW);
	MainWinButton[0]  = BUTTON_CreateAsChild(LCDXSize-BWsize,(i++)*BHsize,BWsize,BHsize,WinHandl,TDU_BUTTON_ID_MW1,WM_CF_SHOW);
	MainWinButton[1]  = BUTTON_CreateAsChild(LCDXSize-BWsize,(i++)*BHsize,BWsize,BHsize,WinHandl,TDU_BUTTON_ID_MW2,WM_CF_SHOW);
	MainWinButton[2]  = BUTTON_CreateAsChild(LCDXSize-BWsize,(i++)*BHsize,BWsize,BHsize,WinHandl,TDU_BUTTON_ID_MW3,WM_CF_SHOW);
	MainWinButton[3]  = BUTTON_CreateAsChild(LCDXSize-BWsize,(i++)*BHsize,BWsize,BHsize,WinHandl,TDU_BUTTON_ID_MW4,WM_CF_SHOW);
	MainWinButton[4]  = BUTTON_CreateAsChild(LCDXSize-BWsize,(i++)*BHsize,BWsize,BHsize,WinHandl,TDU_BUTTON_ID_MW5,WM_CF_SHOW);
	MainWinButton[5]  = BUTTON_CreateAsChild(LCDXSize-BWsize,(i++)*BHsize,BWsize,BHsize,WinHandl,TDU_BUTTON_ID_MW6,WM_CF_SHOW);
	ButtonSystem  = BUTTON_CreateAsChild(LCDXSize-BWsize,(i++)*BHsize,BWsize,BHsize+2,WinHandl,TDU_BUTTON_ID_MW7,WM_CF_SHOW);

	SetBitmap();
	TEXT_SetTextColor(HeadingText,TDU_C_HW_TEXT); TEXT_SetFont(HeadingText,&TDU_FONT_HW);
	BUTTON_SetBitmapEx(ButtonSystem,  0,&bmButtonSystem,1,1);
	BUTTON_SetFont(ButtonAlarm, &TDU_FONT_HW);
	BUTTON_SetBkColor(ButtonAlarm, 0, TDU_C_AL_BACK_NOAL);
	BUTTON_SetText(ButtonAlarm, "No Alarm");
	BUTTON_SetTextColor(ButtonAlarm, 0, TDU_C_AL_TEXT_NOAL);
	BUTTON_SetTextColor(ButtonAlarm, 1, TDU_C_AL_TEXT_NOAL);
}

void TDUMainWin::SetWindow(int WinID)
{
	// Test that Dialog windows not active
	Protect();
	if ( !KeyBoard->Closed ) {					 //1
		KeyBoard->CloseTimer.Stop();
	}
	if ( !OKMessageBox->Closed ) {			 //2
		OKMessageBox->CloseTimer.Stop();
	}
	if ( !ConfirmMessageBox->Closed ) {	 //3
		ConfirmMessageBox->CloseTimer.Stop();
	}
	if ( !ListMessageBox->Closed ) {	//3
		ListMessageBox->CloseTimer.Stop();
	}
	if ( !AppWinSetupDiaIsClosed ) {		 //4
		AppWinSetupDiaIsClosed = true;
		GUI_EndDialog(AppWinSetup->WinHandl, 0);
	}
	if ( !AppSetupBallastIsClosed ) {		 //5
		AppSetupBallastIsClosed = true;
		GUI_EndDialog(AppSetupBallast->WinHandl, 0);
	}
	if ( !AppSetupCargoIsClosed ) {			 //6
		AppSetupCargoIsClosed = true;
		GUI_EndDialog(AppSetupCargo->WinHandl, 0);
	}
	if ( !AppSetupServiceIsClosed ) {		 //7
		AppSetupServiceIsClosed = true;
		GUI_EndDialog(AppSetupService->WinHandl, 0);
	}
	if ( !AppSetupTankPressIsClosed ) {	 //8
		AppSetupTankPressIsClosed = true;
		GUI_EndDialog(AppSetupTankPress->WinHandl, 0);
	}
	if ( !AppSetupTempIsClosed ) {			 //9
		AppSetupTempIsClosed = true;
		GUI_EndDialog(AppSetupTemp->WinHandl, 0);
	}
	if ( !AppSetupVoidSpaceIsClosed ) {			 //9
		AppSetupVoidSpaceIsClosed = true;
		GUI_EndDialog(AppSetupVoidSpace->WinHandl, 0);
	}
	if ( !TankDetails->Closed ) {				 //10
		TankDetails->Closed = true;
		GUI_EndDialog(TankDetails->WinHandl, 0);
	}
	if ( !AppSetupTankFarmIsClosed ) {			 //6
		AppSetupTankFarmIsClosed = true;
		GUI_EndDialog(AppSetupTankFarm->WinHandl, 0);
	}
	switch ( WinID ) {
	case TDU_CARGO_WIN:
		if ( CargoWindow ) {
			CurrentWinHandl = CargoWindow->WinHandl;
			CurrentWinID = TDU_CARGO_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD9).c_str());	// Cargo
			CargoWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_TANKFARM_WIN:
		if ( TankFarmWindow ) {
			CurrentWinHandl = TankFarmWindow->WinHandl;
			CurrentWinID = TDU_TANKFARM_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD893).c_str());	// Tanks
			TankFarmWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;

	case TDU_BALLAST_WIN:
		if ( BallastWindow ) {
			CurrentWinHandl = BallastWindow->WinHandl;
			CurrentWinID = TDU_BALLAST_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD47).c_str());	// Ballast
			BallastWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_SERVICE_WIN:
		if ( ServiceWindow ) {
			CurrentWinHandl = ServiceWindow->WinHandl;
			CurrentWinID = TDU_SERVICE_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD10).c_str());	// Service
			ServiceWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_TANKPRESS_WIN:
		if ( TankPressWindow ) {
			CurrentWinHandl = TankPressWindow->WinHandl;
			CurrentWinID = TDU_TANKPRESS_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD12).c_str());	// Tank pressure
			TankPressWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_LINEPRESS_WIN:
		if ( LinePressWindow ) {
			CurrentWinHandl = LinePressWindow->WinHandl;
			CurrentWinID = TDU_LINEPRESS_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD92).c_str());	// Cargo line pressure
			LinePressWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_TEMP_WIN:
		if ( TempWindow ) {
			CurrentWinHandl = TempWindow->WinHandl;
			CurrentWinID = TDU_TEMP_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD11).c_str());	// Temperature
			TempWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_LEVELSWITCH_WIN:
		if ( LevelSwitchWindow ) {
			CurrentWinHandl = LevelSwitchWindow->WinHandl;
			CurrentWinID = TDU_LEVELSWITCH_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD95).c_str());	// Level switch
			LevelSwitchWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_WATERINGR_WIN:
		if ( WaterIngrWindow ) {
			CurrentWinHandl = WaterIngrWindow->WinHandl;
			CurrentWinID = TDU_WATERINGR_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD94).c_str());	// Water Ingress Detection
			WaterIngrWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_VOIDSPACE_WIN:
		if ( VoidSpaceWindow ) {
			CurrentWinHandl = VoidSpaceWindow->WinHandl;
			CurrentWinID = TDU_VOIDSPACE_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD642).c_str());	// Void space
			VoidSpaceWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_SYSTEM_WIN:
		if ( SystemWindow ) {
			CurrentWinHandl = SystemWindow->WinHandl;
			CurrentWinID = TDU_SYSTEM_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD96).c_str());	// System
			SystemWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD99).c_str());	// Not Configured
		}
		break;
	case TDU_ALARM_WIN:
		if ( AlarmWindow ) {
			CurrentWinHandl = AlarmWindow->WinHandl;
			CurrentWinID = TDU_ALARM_WIN;
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD97).c_str());	// Alarm
			AlarmWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_CONFIG_MAIN_WIN:
		if ( ConfigWindow ) {
			CurrentWinHandl = ConfigWindow->WinHandl;
			CurrentWinID = TDU_CONFIG_MAIN_WIN;
			TEXT_SetText(HeadingText,"Configuration");
//			ConfigWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_CALIBRATE_WIN:
		if ( ConfigWindow ) {
			CurrentWinHandl = CalibrateScreen->WinHandl;
			CurrentWinID = TDU_CALIBRATE_WIN;
			TEXT_SetText(HeadingText,"Calibration");
//			ConfigWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_TANK_CLEANING_WIN:
		if ( ConfigWindow ) {
			CurrentWinHandl = TankCleaningWindow->WinHandl;
			CurrentWinID = TDU_TANK_CLEANING_WIN;
			TEXT_SetText(HeadingText, "Tank cleaning");
			TankCleaningWindow->SetButton();
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	case TDU_TANK_CLEANING_DETAILS_WIN:
		if ( ConfigWindow ) {

			if (TankCleaningDetailsWindow != NULL && TankCleaningDetailsWindow->GetTank() != NULL)
			{
				PROTank* pTank = TankCleaningDetailsWindow->GetTank();

				CurrentWinHandl = TankCleaningDetailsWindow->WinHandl;
				CurrentWinID = TDU_TANK_CLEANING_DETAILS_WIN;

				AnsiString titleStr;
				titleStr.cat_sprintf("%s TCMs", pTank->Name.c_str());
				TEXT_SetText(HeadingText, titleStr.c_str());
				TankCleaningDetailsWindow->SetButton();
			}
		} else {
			TEXT_SetText(HeadingText,FindDictionaryWord(L_WORD100).c_str()); // Not in use
		}
		break;
	default:
		break;
	}
	UnProtect();
	WM_BringToTop(CurrentWinHandl);
}

void TDUMainWin::SetCurrentWindow(int index)
{
	Protect();
	int OrgWinId= CurrentWinID;
	if ( index==6 ) {
		if ( CurrentWinID != TDU_SYSTEM_WIN ) {
			PreviousWinID = CurrentWinID;
		}
		CurrentWinID = TDU_SYSTEM_WIN;
	} else if ( index==7 ) {
		if ( CurrentWinID != TDU_ALARM_WIN ) {
			PreviousWinID = CurrentWinID;
		}
		CurrentWinID = TDU_ALARM_WIN;
	} else {
		if ( PROProjectInfo::PROProjectInfoPtr ) {
			switch ( NewAppList[index] ) {
			case TSN_TANKFARM_APP   :
			case TSN_CARGO_APP      :
			case TSN_BALLAST_APP    :
			case TSN_SERVICE_APP    :
			case TSN_TANKPRESS_APP  :
			case TSN_LINEPRESS_APP  :
			case TSN_TEMP_APP       :
			case TSN_LEVELSWITCH_APP:
			case TSN_WATERINGR_APP  :
			case TSN_VOIDSPACE_APP  :
				LastApplIndex = index;
				break;
			default:
				break;
			}
			switch ( NewAppList[index] ) {
			case TSN_TANKFARM_APP:
				CurrentWinID  = TDU_TANKFARM_WIN;
				LastApplIndex = index;
				break;
			case TSN_CARGO_APP:
				CurrentWinID  = TDU_CARGO_WIN;
				LastApplIndex = index;
				break;
			case TSN_BALLAST_APP:
				CurrentWinID  = TDU_BALLAST_WIN;
				LastApplIndex = index;
				break;
			case TSN_SERVICE_APP:
				CurrentWinID  = TDU_SERVICE_WIN;
				LastApplIndex = index;
				break;
			case TSN_TANKPRESS_APP:
				CurrentWinID  = TDU_TANKPRESS_WIN;
				LastApplIndex = index;
				break;
			case TSN_LINEPRESS_APP:
				CurrentWinID  = TDU_LINEPRESS_WIN;
				LastApplIndex = index;
				break;
			case TSN_TEMP_APP:
				CurrentWinID  = TDU_TEMP_WIN;
				LastApplIndex = index;
				break;
			case TSN_LEVELSWITCH_APP:
				CurrentWinID  = TDU_LEVELSWITCH_WIN;
				LastApplIndex = index;
				break;
			case TSN_WATERINGR_APP:
				CurrentWinID  = TDU_WATERINGR_WIN;
				LastApplIndex = index;
				break;
			case TSN_VOIDSPACE_APP:
				CurrentWinID  = TDU_VOIDSPACE_WIN;
				LastApplIndex = index;
				break;
			case TSN_TANK_CLEANING_APP:
				CurrentWinID  = TDU_TANK_CLEANING_WIN;
				LastApplIndex = index;
				break;
			case TSN_TANK_CLEANING_DETAILS_APP:
				CurrentWinID = TDU_TANK_CLEANING_DETAILS_WIN;
				LastApplIndex = index;
				break;
			default:
				break;
			}
			if ( OrgWinId != CurrentWinID ) {
				PreviousWinID = CurrentWinID;
			}

		} else {
			GiveConfigWarning((AnsiString)FindDictionaryWord(L_WORD91).c_str());	// Unknown error in Configuration.
			PreviousWinID = CurrentWinID;
			CurrentWinID = TDU_SYSTEM_WIN;
		}
	}
	SetWindow(CurrentWinID);
	if ( SystemWindow && ( OrgWinId != CurrentWinID) ) {
		SystemWindow->SetModifiedFlag();
	}

	UnProtect();
}

void TDUMainWin::SetPreviousWindow(void)
{
	Protect();

	if ( CurrentWinID == TDU_CONFIG_MAIN_WIN ) {
		WM_BringToBottom(ConfigWindow->WinHandl);
	}
	if ( CurrentWinID == TDU_CALIBRATE_WIN ) {
		WM_BringToBottom(CalibrateScreen->WinHandl);
	}
	if ( (CurrentWinID == TDU_SYSTEM_WIN) && (PreviousWinID == TDU_SYSTEM_WIN) ) {
		SetCurrentWindow(LastApplIndex);
	} else {
		SetWindow(PreviousWinID);
	}
	UnProtect();
}

void TDUMainWin::cbEventHandler(WM_MESSAGE * pMsg)
{
	//WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	case WM_PAINT:
		GUI_SetBkColor(TDU_C_HW_BACK);GUI_Clear();
		break;
	case WM_CREATE:
		{
			GUI_SetBkColor(TDU_C_HW_BACK);GUI_Clear();
		}
		break;
	case WM_NOTIFY_PARENT:
		{
			int NCode, Id;
			Id    = WM_GetId(pMsg->hWinSrc);		/* Id of widget */
			NCode = pMsg->Data.v;								/* Notification code */
			switch ( NCode ) {
			
			case WM_NOTIFICATION_CLICKED:		/* React only if pressed */
				{
					switch ( Id ) {
					case TDU_BUTTON_ID_MW1:
						MainWindow->SetCurrentWindow(0);
						break;
					case TDU_BUTTON_ID_MW2:
						MainWindow->SetCurrentWindow(1);
						break;
					case TDU_BUTTON_ID_MW3:
						MainWindow->SetCurrentWindow(2);
						break;
					case TDU_BUTTON_ID_MW4:
						MainWindow->SetCurrentWindow(3);
						break;
					case TDU_BUTTON_ID_MW5:
						MainWindow->SetCurrentWindow(4);
						break;
					case TDU_BUTTON_ID_MW6:
						MainWindow->SetCurrentWindow(5);
						break;
					case TDU_BUTTON_ID_MW7:
						// System button
						MainWindow->SetCurrentWindow(6);
						break;
					case TDU_BUTTON_ID_MW0:
						// Alarm button
						MainWindow->SetCurrentWindow(7);
						if ( AlarmCriticalComFailure::ComFailure ) {
							GiveRelayDutyMessage(0,RELAY_MSG_OFF,0,0);
							AlarmBasic::AlarmSilence = true;
						} else {
							ANPRO10_SendAlarmSilence();
						}
						break;
					}
				}
				break;
			}
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void TDUMainWin::SetBitmap(void)
{
	bool CargoSelected        = false;
	bool BallastSelected      = false;
	bool ServiceSelected      = false;
	bool TankPressSelected    = false;
	bool LinePressSelected    = false;
	bool TempSelected         = false;
	bool WaterIngrSelected    = false;
	bool LevelSwitchSelected  = false;
	bool VoidSpaceSelected    = false;
	bool TankFramSelected     = false;
	bool TankCleaningSelected = false;
	int ButListIndex = 0;

	if ( PROProjectInfo::PROProjectInfoPtr ) {
// switch 1
		int NumberOfConfiguredApp = PROProjectInfo::PROProjectInfoPtr->NumberOfApp;
		if ( NumberOfConfiguredApp>MAX_APPL )	NumberOfConfiguredApp = MAX_APPL;
		for ( int AppListIndex=0; AppListIndex<NumberOfConfiguredApp; AppListIndex++ ) {
			switch ( PROProjectInfo::PROProjectInfoPtr->ApplicationList[AppListIndex] ) {
			case TSN_TANKFARM_APP:
				if ( !PROCargoTank::ObjVector.empty() ) {
					TankFramSelected = true;
					NewAppList[ButListIndex] = TSN_TANKFARM_APP;
					BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmLTank,1,1);
				}
				break;
			case TSN_CARGO_APP:
				if ( !PROCargoTank::ObjVector.empty() ) {
					CargoSelected = true;
					NewAppList[ButListIndex] = TSN_CARGO_APP;
					BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonCargo,1,1);
				} else {

				}
				break;
			case TSN_BALLAST_APP:
				if ( !PROBallastTank::ObjVector.empty() ) {
					BallastSelected = true;
					NewAppList[ButListIndex] = TSN_BALLAST_APP;
					BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonBallast,1,1);
				}
				break;
			case TSN_SERVICE_APP:
				if ( !PROServiceTank::ObjVector.empty() ) {
					ServiceSelected = true;
					NewAppList[ButListIndex] = TSN_SERVICE_APP;
					BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonService,1,1);
				}
				break;
			case TSN_TANKPRESS_APP:
				if ( !PROTankPressure::ObjVector.empty() ) {
					TankPressSelected = true;
					NewAppList[ButListIndex] = TSN_TANKPRESS_APP;
					BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonTankPress,1,1);
				}
				break;
			case TSN_LINEPRESS_APP:
				if ( !PROLinePressure::ObjVector.empty() ) {
					LinePressSelected = true;
					NewAppList[ButListIndex] = TSN_LINEPRESS_APP;
					BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonCargoLinePress,1,1);
				}
				break;
			case TSN_TEMP_APP:
				if ( !PROTemperature::ObjVector.empty() ) {
					TempSelected = true;
					NewAppList[ButListIndex] = TSN_TEMP_APP;
					BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonTemperature,1,1);
				}
				break;
			case TSN_LEVELSWITCH_APP:
				if ( !PROLevelSwitch::ObjVector.empty() ) {
					LevelSwitchSelected = true;
					NewAppList[ButListIndex] = TSN_LEVELSWITCH_APP;
					BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonHighLevel,1,1);
				}
				break;
			case TSN_WATERINGR_APP:
				if ( !PROWaterIngress::ObjVector.empty() ) {
					WaterIngrSelected = true;
					NewAppList[ButListIndex] = TSN_WATERINGR_APP;
					BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonWaterIngress,1,1);
				}
				break;
			case TSN_VOIDSPACE_APP:
				if ( !PROVoidSpace::ObjVector.empty() ) {
					WaterIngrSelected = true;
					NewAppList[ButListIndex] = TSN_VOIDSPACE_APP;
					BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonVoidSpace,1,1);
				}
				break;
			case TSN_TANK_CLEANING_APP:
				if ( !PROTankWashingMachine::ObjectSet.empty() ) {
					TankCleaningSelected = true;
					NewAppList[ButListIndex] = TSN_TANK_CLEANING_APP;
					BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0, &bmButtonTankwash,1,1);
				}
				break;
			}
		}//end Switch
	}//end for(NumberOfConfiguredApp)
	if ( (PROProjectInfo::ProjectType==2) ) {
		if ( (ButListIndex<MAX_APPL) && !PROCargoTank::ObjVector.empty() && !TankFramSelected ) {
			TankFramSelected = true;
			NewAppList[ButListIndex] = TSN_TANKFARM_APP;
			BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmLTank,1,1);
		}
		if ( (ButListIndex<MAX_APPL) && !PROLevelSwitch::ObjVector.empty() && !LevelSwitchSelected ) {
			LevelSwitchSelected = true;
			NewAppList[ButListIndex] = TSN_LEVELSWITCH_APP;
			BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmLTankOverfill,1,1);
		}
	} else {
		if ( (ButListIndex<MAX_APPL) && !PROCargoTank::ObjVector.empty() && !CargoSelected ) {
			CargoSelected = true;
			NewAppList[ButListIndex] = TSN_CARGO_APP;
			BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonCargo,1,1);
		}
		if ( (ButListIndex<MAX_APPL) && !PROLevelSwitch::ObjVector.empty() && !LevelSwitchSelected ) {
			LevelSwitchSelected = true;
			NewAppList[ButListIndex] = TSN_LEVELSWITCH_APP;
			BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonHighLevel,1,1);
		}
	}
	if ( (ButListIndex<MAX_APPL) && !PROBallastTank::ObjVector.empty() && !BallastSelected ) {
		BallastSelected = true;
		NewAppList[ButListIndex] = TSN_BALLAST_APP;
		BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonBallast,1,1);
	}
	if ( (ButListIndex<MAX_APPL) && !PROServiceTank::ObjVector.empty() && !ServiceSelected ) {
		ServiceSelected = true;
		NewAppList[ButListIndex] = TSN_SERVICE_APP;
		BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonService,1,1);
	}
	if ( (ButListIndex<MAX_APPL) && !PROTankPressure::ObjVector.empty() && !TankPressSelected ) {
		TankPressSelected = true;
		NewAppList[ButListIndex] = TSN_TANKPRESS_APP;
		BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonTankPress,1,1);
	}
	if ( (ButListIndex<MAX_APPL) && !PROLinePressure::ObjVector.empty() && !LinePressSelected ) {
		LinePressSelected = true;
		NewAppList[ButListIndex] = TSN_LINEPRESS_APP;
		BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonCargoLinePress,1,1);
	}
	if ( (ButListIndex<MAX_APPL) && !PROTemperature::ObjVector.empty() && !TempSelected ) {
		TempSelected = true;
		NewAppList[ButListIndex] = TSN_TEMP_APP;
		BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonTemperature,1,1);
	}
	if ( (ButListIndex<MAX_APPL) && !PROWaterIngress::ObjVector.empty() && !WaterIngrSelected ) {
		WaterIngrSelected = true;
		NewAppList[ButListIndex] = TSN_WATERINGR_APP;
		BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonWaterIngress,1,1);
	}
	if ( (ButListIndex<MAX_APPL) && !PROVoidSpace::ObjVector.empty()&& !VoidSpaceSelected ) {
		WaterIngrSelected = true;
		NewAppList[ButListIndex] = TSN_VOIDSPACE_APP;
		BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0,&bmButtonVoidSpace,1,1);
	}
	if ( (ButListIndex<MAX_APPL) && !PROTankWashingMachine::ObjectSet.empty() && !TankCleaningSelected ) {
		TankCleaningSelected = true;
		NewAppList[ButListIndex] = TSN_TANK_CLEANING_APP;
		BUTTON_SetBitmapEx(MainWinButton[ButListIndex++], 0, &bmButtonTankwash,1,1);
	}

}

