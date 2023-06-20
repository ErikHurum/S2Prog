#include "TDUincludes.h"
/*******************************************************************
*       _cbBkWindow
*  This callback is necessary to redraw the background when
*  frame window is moved
********************************************************************/
static void _cbBkWindow(WM_MESSAGE * pMsg)
{
	switch ( pMsg->MsgId ) {
	case WM_GET_INSIDE_RECT:
		break;
	case WM_PAINT:
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

/*******************************************************************
*       Window init
*    Creates the Mainwindow and sets the callback for child
*    and background window
*/
void TDUStartupInit(void) {
	GUI_Init();
	WM_SetCreateFlags(WM_CF_MEMDEV);   /* Use memory devices on all windows to avoid flicker */

	LCDXSize = LCD_GET_XSIZE();
	LCDYSize = LCD_GET_YSIZE();
//Set Welcome picture:
	GUI_SetBkColor(GUI_LIGHTGRAY);
	GUI_Clear();
	GUI_SetColor(GUI_BLACK);
	GUI_DrawBitmap(&bmScanjetlogo,20,1);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(&GUI_Font24B_ASCII);
	GUI_DispStringHCenterAt("Display unit",LCDXSize/2,120);
	GUI_SetFont(&GUI_Font16B_ASCII);
	GUI_DispStringHCenterAt("Loading....",LCDXSize/2,150);
	TSN_Delay(1000);

#ifdef S2TXU
	StartCloseMsgBoxTask();
#endif

}

void StartWindowSystem(void)
{
//Default color for listview

	LISTVIEW_SetDefaultFont(&TDU_FONT_PW);
	int scrollwith = SCROLLBAR_SetDefaultWidth(15);

	OKMessageBox        = new TDUMessageBox;
	ConfirmMessageBox   = new TDUMessageBoxCancel;
	ListMessageBox      = new TDUMessageBoxList;
	ConfigWindow        = new TDUConfigWin;

//Keyboard and dialogs:
	AppWinSetup         = new TDUAppWinSetup;
	AppSetupBallast     = new TDUAppSetupBallast;
	AppSetupCargo       = new TDUAppSetupCargo;
	AppSetupTankFarm    = new TDUAppSetupTankFarm;
	AppSetupService     = new TDUAppSetupService;
	AppSetupTankPress   = new TDUAppSetupTankPress;
	AppSetupTemp        = new TDUAppSetupTemp;
	AppSetupVoidSpace   = new TDUAppSetupVoidSpace;
	KeyBoard            = new TDUKeyBoard;
	ConfigWarnings      = new TDUConfigWarning;
	CalibrateScreen     = new TDUCalibrateScreen;
	TankDetails         = new TDUMultipageTankDetails;
	SensorDetails       = new TDUCalDataWin;
// Initiate main windows:
	MainWindow          = new TDUMainWin;
	ButWindow           = new TDUButWin;
	PresentWindow       = new TDUPresentWin;
	AlarmWindow         = new TDUAlarmWindow;
	SystemWindow        = new TDUSystemWin;

	WM_EnableMemdev(MainWindow->WinHandl);
	WM_EnableMemdev(ButWindow->WinHandl);
	WM_EnableMemdev(PresentWindow->WinHandl);
	WM_EnableMemdev(AlarmWindow->WinHandl);
	WM_EnableMemdev(SystemWindow->WinHandl);
    WM_EnableMemdev(ConfigWarnings->WinHandl);

//Application activated
	if ( !PROCargoTank::ObjVector.empty() ) {
		switch ( PROProjectInfo::ProjectType ) {
		default:
		case 0:
		case 1:
			CargoWindow             = new TDUCargoWin;
			WM_EnableMemdev(CargoWindow->WinHandl);
			break;
		case 2:
			TankFarmWindow           = new TDUTankFarmWin;
			WM_EnableMemdev(TankFarmWindow->WinHandl);
			break;

		}
	}
	if ( !PROBallastTank::ObjVector.empty() ) {
		BallastWindow           = new TDUBallastWin;
		WM_EnableMemdev(BallastWindow->WinHandl);
	}
	if ( !PROServiceTank::ObjVector.empty() ) {
		ServiceWindow           = new TDUServiceWin;
		WM_EnableMemdev(ServiceWindow->WinHandl);
	}
	if ( !PROTankPressure::ObjVector.empty() ) {
		TankPressWindow     = new TDUTankPressWin;
		WM_EnableMemdev(TankPressWindow->WinHandl);
	}
	if ( !PROTemperature::ObjVector.empty() ) {
		TempWindow              = new TDUTempWin;
		WM_EnableMemdev(TempWindow->WinHandl);
	}
	if ( !PROWaterIngress::ObjVector.empty() ) {
		WaterIngrWindow         = new TDUWaterIngressWin;
		WM_EnableMemdev(WaterIngrWindow->WinHandl);
	}
	if ( !PROLevelSwitch::ObjVector.empty() ) {
		LevelSwitchWindow   = new TDULevelSwitchWin;
		WM_EnableMemdev(LevelSwitchWindow->WinHandl);
	}
	if ( !PROLinePressure::ObjVector.empty() ) {
		LinePressWindow     = new TDULinePressWin;
		WM_EnableMemdev(LinePressWindow->WinHandl);
	}
	if ( !PROVoidSpace::ObjVector.empty() ) {
		VoidSpaceWindow     = new TDUVoidSpaceWin;
		WM_EnableMemdev(VoidSpaceWindow->WinHandl);
	}
	if ( !PROTankWashingMachine::ObjectSet.empty() ) {
		TankCleaningWindow = new TDUTankCleaningWin;
		WM_EnableMemdev(TankCleaningWindow->WinHandl);

		// Init this window with one objects for now .. will be set later when the windows will appear:
		vector<PRogramObjectBase*> sampleVec;
		if (PROTankWashingMachine::AllTankWashingMachinesVector.size() > 0)
		{
			sampleVec.push_back(PROTankWashingMachine::AllTankWashingMachinesVector[0]);
		}
		TankCleaningDetailsWindow = new TDUTankCleaningDetailsWin(&sampleVec);
		WM_EnableMemdev(TankCleaningDetailsWindow->WinHandl);
	}


	NotConfWindow               = new TDUNotConfiguredWin;
	WM_EnableMemdev(NotConfWindow->WinHandl);

//	Set callback for background windows:
	WM_SetCallback(WM_HBKWIN                ,     _cbBkWindow);
	WM_SetCallback(MainWindow->WinHandl     ,    MainWindow->cbEventHandler);
	WM_SetCallback(ButWindow->WinHandl      ,    ButWindow->cbEventHandler);
	WM_SetCallback(ConfigWarnings->WinHandl ,    ConfigWarnings->cbConfigWarning);

}

void NoConfigWarning(void)
{
	GUI_Clear();
	GUI_SetBkColor(GUI_RED);
	GUI_SetColor(GUI_BLACK);
	GUI_DrawBitmap(&bmScanjetlogo,20,40);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(&GUI_Font24B_ASCII);
	GUI_DispStringHCenterAt("Display unit",LCDXSize/2,160);
	GUI_SetFont(&GUI_Font16B_ASCII);
	GUI_DispStringHCenterAt("No Configuration file found.",LCDXSize/2,220);
	TSN_Delay(3000);
}

