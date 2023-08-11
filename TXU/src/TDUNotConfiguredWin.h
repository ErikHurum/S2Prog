#pragma once

class TDUNotConfiguredWin :
	public TDUPresentWin
{
public:
	TDUNotConfiguredWin(void);
	~TDUNotConfiguredWin(void);
	
	void SetButton(void);
	void ButtonClicked(int ButtID);
	void cbEventHandler(WM_MESSAGE* pMsg);

};
