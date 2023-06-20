#pragma once
#include "CloseWindowTimer.h"


class TDUMessageBox:public TDUBasicWin
{
public:
	TDUMessageBox(void);
	~TDUMessageBox(void);
	void Exec(WM_HWIN hCurrentWin,AnsiString HeadingText,AnsiString MessageText);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
	static void cbMessageBox(WM_MESSAGE *pMsg);

  static const U32 TimeOut = 20000;
  bool Closed;
  CloseWindowTimer CloseTimer;
};
