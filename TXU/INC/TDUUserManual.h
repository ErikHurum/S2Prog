#pragma once

class TDUUserManual:public TDUBasicWin
{
public:
	TDUUserManual(void);
	~TDUUserManual(void);
	MULTIEDIT_HANDLE hUserManual;
	void ExecDialogBox(WM_HWIN hCurrentWin);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
	static void cbUserManual(WM_MESSAGE *pMsg);

  static const U32 TimeOut = 60000;
  volatile bool Closed;
  CloseWindowTimer CloseTimer;
};
