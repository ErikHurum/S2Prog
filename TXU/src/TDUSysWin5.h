#pragma once

class TDUSysWin5:public TDUBasicWin
{
private:
	WM_HWIN uText[2];
	WM_HWIN vText[2][8];
	static const int VList[2][8];
	static unsigned IdSet2[];

public:
	TDUSysWin5(void);
	~TDUSysWin5(void);
	AnsiString ValueString;
	void ExecDialogBox(WM_HWIN hCurrentWin);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
    void GetDialogHandles(void);
	void InitSysWin(void);
	void UpdateSysWin(void);
	static void cbSysWin(WM_MESSAGE *pMsg);
};
