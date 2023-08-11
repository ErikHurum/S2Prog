#pragma once

class TDUMessageBoxCancel:public TDUBasicWin
{
public:
	TDUMessageBoxCancel(void);
	~TDUMessageBoxCancel(void);
	WM_HWIN DialogWinHandl;

	char ReturnBuf[BUF_SIZE];
	int ValueID;
  int DialogIndex;
//	bool Exec(WM_HWIN hCurrentWin,AnsiString HeadingText,AnsiString MessageText);
  void Exec(WM_HWIN hCurrentWin,int HeadingText,int MessageText, int ID);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
	static void cbMessageBox(WM_MESSAGE *pMsg);

  static const U32 TimeOut = 20000;
  bool Closed;
  CloseWindowTimer CloseTimer;
};
