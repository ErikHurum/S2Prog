#pragma once

class TDUSensorSetting
{
private:
		WM_HWIN hText1, hText2, hText3, hText4, hText6;
		WM_HWIN hText10, hText11, hText12, hText13;
		WM_HWIN hEdit1, hEdit2, hEdit3, hEdit4;
		WM_HWIN hEdit11, hEdit12, hEdit13, hEdit14;
		WM_HWIN hEdit21, hEdit22, hEdit23, hEdit24;
		WM_HWIN hCheck1, hCheck2, hCheck3, hCheck4;

public:
	TDUSensorSetting(void);
	~TDUSensorSetting(void);
	WM_HWIN WinHandl;
	PRogramObject *CurrentPROPtr;

	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];

	void ExecDialogBox(WM_HWIN hCurrentWin, PRogramObject *PROPtr);
	void GetDialogHandles(void);
	void InitDialog(void);
	void UpdateDialog(int key, char *buf);

	static void cbTankSetup(WM_MESSAGE * pMsg);
};
