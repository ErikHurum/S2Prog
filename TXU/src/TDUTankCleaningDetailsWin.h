#pragma once


class TDUTankCleaningDetailsWin :
	public TDUGroupWin
{
private:

    static const int UI_Refresh_Timer_UserId = 1;
#if defined(ANTDUSIM)
    static const int UI_Refresh_Timer_First_Wait_Secs = 15;
#else
    static const int UI_Refresh_Timer_First_Wait_Secs = 15;
#endif
    static const int UI_Refresh_Timer_Interval_Secs = 2;

	static const TDUValueTable TableValues[TDU_WIN_COL];
	PROTank *pTank;

protected:
	//WM_HWIN MainWinHandle;
	// Paging members, for those times when there are more tanks than can fit onto a single screen:
	int NumberOfPages;
	int CurrentPage;	

public:
	TDUTankCleaningDetailsWin(vector<PRogramObjectBase*> *pItemVec);
	~TDUTankCleaningDetailsWin(void);

	void SetButton(void);
	void ButtonClicked(int btnID);
	void cbEventHandler(WM_MESSAGE * pMsg);
	void TableUpdate(void);
	void SetTankToDisplay(PROTank *pTank);
	PROTank* GetTank(void);
    void ResetWinRefreshTimer(int seconds);

	//static void EventLoopTankCleaningWindow(WM_MESSAGE * pMsg);
};

