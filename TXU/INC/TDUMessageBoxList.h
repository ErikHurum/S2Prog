#pragma once
#include "CloseWindowTimer.h"


class TDUMessageBoxList:public TDUBasicWin
{
private:
	WM_HWIN hText;
	MULTIEDIT_HANDLE hMultiEdit;

public:
	TDUMessageBoxList(void);
	~TDUMessageBoxList(void);
	void Exec(WM_HWIN hCurrentWin,AnsiString HeadingText,AnsiString MessageText);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
	static void cbMessageBox(WM_MESSAGE *pMsg);

  static const U32 TimeOut = 20000;
  bool Closed;
  CloseWindowTimer CloseTimer;
};
