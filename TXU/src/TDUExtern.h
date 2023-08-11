/////////////////////////////////////////////////////////
//
// From TDUUtilities.Cpp
//
/////////////////////////////////////////////////////////

extern "C"{
	extern void LISTVIEW_SetItemTextWithColor(LISTVIEW_Handle hObj, unsigned Column, unsigned Row, const char *MyStr, GUI_COLOR FgColor, GUI_COLOR BkColor);
}



extern "C"{
	// Bitmap Files
	extern const GUI_BITMAP bmScanjetlogo;
	extern const GUI_BITMAP bmScanjetlogo_small;
	extern const GUI_BITMAP bmButtonSystem;
	extern const GUI_BITMAP bmButtonCargo;
	extern const GUI_BITMAP bmButtonBallast;
	extern const GUI_BITMAP bmButtonService;
	extern const GUI_BITMAP bmButtonTemperature;
	extern const GUI_BITMAP bmButtonVapourReturnPress;
	extern const GUI_BITMAP bmButtonTankPress;
	extern const GUI_BITMAP bmButtonHighLevel;
	extern const GUI_BITMAP bmButtonCargoLinePress;
	extern const GUI_BITMAP bmButtonGasSampling;
	extern const GUI_BITMAP bmButtonWaterIngress;
	extern const GUI_BITMAP bmButtonVoidSpace;
	extern const GUI_BITMAP bmLTank;
	extern const GUI_BITMAP bmLTankOverfill;
	extern const GUI_BITMAP bmLTankWaterInOil;
    extern const GUI_BITMAP bmButtonTankwash;

}

/////////////////////////////////////////////////////////
//
// From LCD_Lib.c
//
/////////////////////////////////////////////////////////
//extern "C"{
extern void LCD_BackLightOn(void);
extern void LCD_BackLightOff(void);
extern void LCD_BackLightAdjust(int Cnt);
//}


/////////////////////////////////////////////////////////
//
// From WindowsSystem.cpp
//
/////////////////////////////////////////////////////////
extern TSN_TASK AlarmWindowTCB     ;


extern int BackColor;
extern int TextColor;

extern WM_HWIN CurrentWinHandl;			// pointer to handler to acktiv window.
extern volatile int CurrentWinID;		// current windows ID
extern volatile int PreviousWinID;		// previous windows ID
extern volatile int LastApplIndex;		// previous application index
extern char UserString[BUF_SIZE];
extern bool AppWinSetupDiaIsClosed;
extern bool AppSetupBallastIsClosed;
extern bool AppSetupCargoIsClosed;
extern bool AppSetupServiceIsClosed;
extern bool AppSetupTankPressIsClosed;
extern bool AppSetupTempIsClosed;
extern bool AppSetupVoidSpaceIsClosed;
extern bool AppSetupTankFarmIsClosed;
//extern bool TankWinAlarmDiaIsClosed;
//extern bool TankWinDensityDiaIsClosed;
//extern bool TankWinSensorDiaIsClosed;
extern bool InConfigModus;
extern int LCDXSize;
extern int LCDYSize;


/////////////////////////////////////////////////////////
//
// From WindowsSystem.cpp
//
/////////////////////////////////////////////////////////

// TDU setup windows
extern TDUKeyBoard          *KeyBoard;
extern TDUMessageBox        *OKMessageBox;
extern TDUMessageBoxCancel  *ConfirmMessageBox;
extern TDUMessageBoxList    *ListMessageBox;
extern TDUAppWinSetup       *AppWinSetup;
extern TDUAppSetupBallast   *AppSetupBallast;
extern TDUAppSetupVoidSpace *AppSetupVoidSpace;

extern TDUAppSetupCargo     *AppSetupCargo;
extern TDUAppSetupTankFarm  *AppSetupTankFarm;
extern TDUAppSetupService   *AppSetupService;
extern TDUAppSetupTankPress *AppSetupTankPress;
extern TDUAppSetupTemp      *AppSetupTemp;
//  extern TDUTankAlarmSetting		*TankAlarmSetting;
//	extern TDUTankDensitySetting	*TankDensitySetting;
//	extern TDUSensorSetting			*SensorSetting;
extern TDUMultipageTankDetails  *TankDetails;
extern TDUCalDataWin            *SensorDetails;
// TDU windows
extern ConfigApp            *ConfigApplication;
extern TDUConfigWin         *ConfigWindow;
extern TDUCalibrateScreen   *CalibrateScreen;
extern TDUConfigWarning     *ConfigWarnings;
extern TDUMainWin           *MainWindow;
extern TDUPresentWin        *PresentWindow;
extern TDUButWin            *ButWindow;
extern TDUAlarmWindow       *AlarmWindow;
extern TDUSystemWin         *SystemWindow;
extern TDUCargoWin          *CargoWindow;
extern TDUTankFarmWin       *TankFarmWindow;
extern TDUBallastWin        *BallastWindow;
extern TDUServiceWin        *ServiceWindow;
extern TDUTankPressWin      *TankPressWindow;
extern TDUTempWin           *TempWindow;
extern TDUWaterIngressWin   *WaterIngrWindow;
extern TDUNotConfiguredWin  *NotConfWindow;
extern TDULevelSwitchWin    *LevelSwitchWindow;
extern TDULinePressWin      *LinePressWindow;
extern TDUVoidSpaceWin      *VoidSpaceWindow;
extern TDUTankCleaningWin	*TankCleaningWindow;
extern TDUTankCleaningDetailsWin *TankCleaningDetailsWindow;





