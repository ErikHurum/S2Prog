#pragma once
class TDUConfigWin
{
public:
	TDUConfigWin(void);
	~TDUConfigWin(void);
	WM_HWIN WinHandl;
	BUTTON_Handle CloseButton;

	static void cbEventHandler(WM_MESSAGE* pMsg);

};
