#pragma once

class TDUSysWin4:public TDUBasicWin {
private:
	static const int NumberOfRows = 34;
	WM_HWIN hDropdHWUnit;
	WM_HWIN hListviewHWUnit;
	PRogramObjectBase *CurrentHWUnit;
	vector<PRogramObjectBase*>DropdHWUnitList;

public:
	TDUSysWin4(void);
	~TDUSysWin4(void);
	int CurrentIndex;
	void ExecDialogBox(WM_HWIN hCurrentWin);
	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
	void GetDialogHandles(void);
	void InitSysWin(void);
	void ClearList(void);
	void UpdateSysWin(void);
	static void cbSysWin(WM_MESSAGE *pMsg);
};
