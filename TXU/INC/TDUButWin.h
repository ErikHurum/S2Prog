#pragma once

#define NUMBER_OF_BUTTONS	5
class TDUButWin:public TDUBasicWin
{
public:
	TDUButWin(void);
	~TDUButWin(void);
	int BHsize;
	int BWsize;
//Set Buttons:
	BUTTON_Handle ButtonPW[NUMBER_OF_BUTTONS];
	void ChangeButtonText(int But1, int But2, int But3, int But4, int But5);
	void EnableButtons(bool Enable[NUMBER_OF_BUTTONS]);
	void EnableButtons(bool Enable1,bool Enable2,bool Enable3,bool Enable4,bool Enable5);
	void EnableButton(int Index, bool Enable);
	static void cbEventHandler(WM_MESSAGE* pMsg);

};
