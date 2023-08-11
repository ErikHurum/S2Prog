#pragma once

#define TDU_TANK_CLEANING_MAX_TANKS			60
#define TDU_TANK_CLEANING_BUTTON_0_ID		GUI_ID_USER + 0x100


struct TDUTankCleaningWin_ButtonToTankMapping
{
public:
	TDUTankCleaningWin_ButtonToTankMapping(BUTTON_Handle _btnHandle, PROTank* _pTank)
	{
		btnHandle = _btnHandle;
		pTank = _pTank;
	}

	BUTTON_Handle btnHandle;
	//int tankId;
	PROTank* pTank;
};



class TDUTankCleaningWin :
	public TDUPresentWin
{
private:
    
	static const int UI_Refresh_Timer_UserId = 1;
#if defined(ANTDUSIM)
    static const int UI_Refresh_Timer_First_Wait_Secs = 15;
#else
    static const int UI_Refresh_Timer_First_Wait_Secs = 25;
#endif
    static const int UI_Refresh_Timer_Interval_Secs = 2;
	static const int UI_Button_Idle_Tank_Color = GUI_LIGHTGRAY;
	static const int UI_Button_Running_Tank_Color = GUI_GREEN;
	int countTimerTicks;									// used for some delayed paint

protected:
	WM_HWIN MainWinHandle;
	
	/// TankButton array holds handles of all the buttons representing tanks in this window
	vector<TDUTankCleaningWin_ButtonToTankMapping> tankMapVector;   //TankButton[TDU_TANK_CLEANING_MAX_TANKS];
	
	// Paging members, for those times when there are more tanks than can fit onto a single screen:
	int NumberOfPages;
	int CurrentPage;				

	PROTank* FindTankByButtonHandle(BUTTON_Handle handle);
	void ResetWinRefreshTimer(int seconds);
	void CreateTankButtonGrid(void);

public:
	TDUTankCleaningWin(void);
	~TDUTankCleaningWin(void);
	void SetButton(void);
	void ButtonClicked(int btnID);
	void MoveWin(void);
	void UnitClicked(WM_HWIN hWin,int btnHandle);
	void UpdateButtonColors(void);
	
	void cbEventHandler(WM_MESSAGE* pMsg);
	static void EventLoopTankCleaningWindow(WM_MESSAGE * pMsg);
};

