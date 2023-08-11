#pragma once
#include "CloseWindowTimer.h"

class TDUKeyBoard
{
public:
	TDUKeyBoard(void);
	~TDUKeyBoard(void);
private:
	WM_HWIN DialogWinHandl;

	BUTTON_Handle ahButtonPinCode[10];
	BUTTON_Handle ahButton[12];
	BUTTON_Handle hButtonBackSpace;
	BUTTON_Handle hButtonESC;
	BUTTON_Handle hButtonEnter;
	TEXT_Handle   hText;
	EDIT_Handle   hTextEdit;
  EDIT_Handle   hTextEditPinCode;
	char ReturnBuf[BUF_SIZE];
	int ReturnValue;
	int ValueID;

	bool UseCallBack;

public:
	WM_HWIN WinHandl;

	int ExecKeyBoardAll(WM_HWIN hCurrentWin,char *buf);
  void ExecKeyBoardPinCode(WM_HWIN hCurrentWin,int WordKey, int ID);
	void ExecKeyBoardNum(WM_HWIN hCurrentWin,int WordKey, int ID);
	void EndKeyBoardNum(void);
	static void cbKeyBoard(WM_MESSAGE * pMsg);
	static void cbKeyBoardPinCode(WM_MESSAGE * pMsg);

  static const U32 TimeOut = 6000;
  bool Closed;
  CloseWindowTimer CloseTimer;
};
