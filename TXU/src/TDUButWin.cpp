#include "TDUIncludes.h"


TDUButWin::~TDUButWin(void)
{
}

TDUButWin::TDUButWin(void)
{
	const GUIKey Words[] ={
		{TDU_BUT_WIN        ,0,L_WORD237},
		{TDU_BUTTON_ID_PW1  ,0,L_WORD237},
		{TDU_BUTTON_ID_PW2  ,0,L_WORD237},
		{TDU_BUTTON_ID_PW3  ,0,L_WORD237},
		{TDU_BUTTON_ID_PW4  ,0,L_WORD237},
		{TDU_BUTTON_ID_PW5  ,0,L_WORD237},
	};

	BHsize = 24;
	BWsize = 57;
//	WinHandl = WM_CreateWindowAsChild(0,LCDYSize-BHsize,LCDXSize-MainWindow->BWsize,
//										BHsize,MainWindow->WinHandl,WM_CF_SHOW,NULL,0);
	WinHandl = WM_CreateWindow(0,LCDYSize-BHsize,LCDXSize-MainWindow->BWsize,
							   BHsize,WM_CF_SHOW,NULL,0);
	WM_SetId(WinHandl,TDU_BUT_WIN);
	for ( int i=0; i < NUMBER_OF_BUTTONS; i++ ) {
		ButtonPW[i] = BUTTON_CreateAsChild(i*BWsize,0,BWsize    ,BHsize,WinHandl,TDU_BUTTON_ID_PW1+i,WM_CF_SHOW);
	}
	AddToSKeyList((GUIKey*)Words,NELEMENTS(Words));
}

void TDUButWin::ChangeButtonText(int But1, int But2, int But3, int But4, int But5)
{
	ButWindow->ChangeSWord(TDU_BUTTON_ID_PW1+0,0,But1);
	ButWindow->ChangeSWord(TDU_BUTTON_ID_PW1+1,0,But2);
	ButWindow->ChangeSWord(TDU_BUTTON_ID_PW1+2,0,But3);
	ButWindow->ChangeSWord(TDU_BUTTON_ID_PW1+3,0,But4);
	ButWindow->ChangeSWord(TDU_BUTTON_ID_PW1+4,0,But5);
	UpdateFields(true);
}

void TDUButWin::EnableButtons(bool Enable[NUMBER_OF_BUTTONS])
{
	for ( int i=0; i < NUMBER_OF_BUTTONS; i++ ) {
		if ( Enable[i] ) {
			WM_EnableWindow( ButtonPW[i]);
		} else {
			WM_DisableWindow(ButtonPW[i]);
		}
	}
}

void TDUButWin::EnableButtons(bool Enable1,bool Enable2,bool Enable3,bool Enable4,bool Enable5)
{
	bool Enable[NUMBER_OF_BUTTONS]={Enable1,Enable2,Enable3,Enable4,Enable5};
	for ( int i=0; i < NUMBER_OF_BUTTONS; i++ ) {
		if ( Enable[i] ) {
			WM_EnableWindow( ButtonPW[i]);
		} else {
			WM_DisableWindow(ButtonPW[i]);
		}
	}
}

void TDUButWin::EnableButton(int Index, bool Enable)
{
	if ( Enable ) {
		WM_EnableWindow( ButtonPW[Index]);
	} else {
		WM_DisableWindow(ButtonPW[Index]);
	}
}

void TDUButWin::cbEventHandler(WM_MESSAGE * pMsg)
{

	//WM_HWIN hWin = pMsg->hWin;
	switch ( pMsg->MsgId ) {
	case WM_PAINT:
		GUI_SetBkColor(TDU_C_BACK_DEFAULT);
		GUI_Clear();
		GUI_SetColor(TDU_C_TEXT_DEFAULT);
		ButWindow->UpdateLanguage();
		break;
	case WM_NOTIFY_PARENT:
		{
			int NCode, Id;
			Id    = WM_GetId(pMsg->hWinSrc);		/* Id of widget */
			NCode = pMsg->Data.v;								/* Notification code */
			switch ( NCode ) {
//			case WM_NOTIFICATION_CLICKED:   /* React only if pressed */
//Must use release her if button shall be disabled on event
			case WM_NOTIFICATION_RELEASED:		/* React only if released */
				{
					// Test that Dialog windows not active
					if ( AppWinSetupDiaIsClosed ) {
						switch ( CurrentWinID ) {
						case TDU_MAIN_WIN:
						case TDU_HEAD_WIN:
						case TDU_BUT_WIN:
						case TDU_PRESENT_WIN:
							break;
						case TDU_SYSTEM_WIN:
							SystemWindow->ButtonClicked(Id);
							break;
						case TDU_ALARM_WIN:
							AlarmWindow->ButtonClicked(Id);
							break;
						case TDU_CARGO_WIN:
							CargoWindow->ButtonClicked(Id);
							break;
						case TDU_TANKFARM_WIN:
							TankFarmWindow->ButtonClicked(Id);
							break;
						case TDU_BALLAST_WIN:
							BallastWindow->ButtonClicked(Id);
							break;
						case TDU_SERVICE_WIN:
							ServiceWindow->ButtonClicked(Id);
							break;
						case TDU_TANKPRESS_WIN:
							TankPressWindow->ButtonClicked(Id);
							break;
						case TDU_LINEPRESS_WIN:
							LinePressWindow->ButtonClicked(Id);
							break;
						case TDU_TEMP_WIN:
							TempWindow->ButtonClicked(Id);
							break;
						case TDU_LEVELSWITCH_WIN:
							LevelSwitchWindow->ButtonClicked(Id);
							break;
						case TDU_WATERINGR_WIN:
							WaterIngrWindow->ButtonClicked(Id);
							break;
						case TDU_VOIDSPACE_WIN:
							VoidSpaceWindow->ButtonClicked(Id);
							break;
						case TDU_TANK_CLEANING_WIN:
							TankCleaningWindow->ButtonClicked(Id);
							break;
						default:
							break;
						}
					}
				}
				break;
			}
		}
		break;
	case WM_CREATE:
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}









