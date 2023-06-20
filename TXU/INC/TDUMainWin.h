#pragma once
class TDUMainWin:public TDUBasicWin
{
public:
	TDUMainWin(void);
	~TDUMainWin(void);
 	int BHsize;
	int BWsize;
	int Height;

	TEXT_Handle HeadingText;
//Set Buttons:
	BUTTON_Handle MainWinButton[6];
//	BUTTON_Handle ButtonMW1,ButtonMW2,ButtonMW3,ButtonMW4,ButtonMW5,ButtonMW6,ButtonMW7,
	BUTTON_Handle ButtonSystem;
	BUTTON_Handle ButtonAlarm;
	int NewAppList[MAX_APPL];
	void SetCurrentWindow(int index);
	void SetPreviousWindow(void);
	void SetWindow(int WinID);
	static void cbEventHandler(WM_MESSAGE* pMsg);
	void SetBitmap(void);
};
