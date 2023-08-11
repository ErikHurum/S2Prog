#pragma once

class TDUAlarmWindow :
	public TDUPresentWin
{
private:
	int PageCount, CurrentPage, NumUnitsOnPage;
	int NumberOfUnits, NumberOfUnitsLastPage;
	int TimerCount;
	bool TimedOut;
	HEADER_Handle ListHeadHandl;
	LISTVIEW_Handle ListViewHandl;
	bool UserTouch;

public:
	TDUAlarmWindow(void);
	~TDUAlarmWindow(void);

	AlarmBasic *OldFirstElementActive;
	AlarmBasic *OldFirstElementAck;

	void SetListViewColor(void);
	void TableSetup(void);
	void SetButton(void);
	void ButtonBlink(void);
  void PWTimer(void);
	void SetColours(int Line,AlarmBasic *AlElement);
	void Paintnew(void);
	void ButtonClicked(int ButtID);
	void AckAllButtonClicked(void);
	void AckButtonClicked(int ButtID);
	void cbEventHandler(WM_MESSAGE* pMsg);

};
