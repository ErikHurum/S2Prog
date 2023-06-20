#pragma once

class TDUConfigWarning:public TDUBasicWin
{
private:
	WM_HWIN hText;
	MULTIEDIT_HANDLE hConfigWarning;
	static TDUConfigWarning *WinPtr;
public:
	TDUConfigWarning(void);
	~TDUConfigWarning(void);
	void ExecDialogBox(WM_HWIN hCurrentWin);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
	static void cbConfigWarning(WM_MESSAGE *pMsg);

  static const U32 TimeOut = 30000;
  bool Closed;
  CloseWindowTimer CloseTimer;
};
