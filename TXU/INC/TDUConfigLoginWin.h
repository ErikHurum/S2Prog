#pragma once

class TDUConfigLoginWin
{
public:
	TDUConfigLoginWin(void);
	~TDUConfigLoginWin(void);
	WM_HWIN WinHandl;
	void ExecDialogBox(WM_HWIN hCurrentWin);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[]; 
	static void cbConfigKey(WM_MESSAGE *pMsg); 

  static const U32 TimeOut = 60000;
  volatile bool Closed;
  CloseWindowTimer CloseTimer;
};
