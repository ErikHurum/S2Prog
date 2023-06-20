#pragma once

class TDUAppWinSetup:public TDUBasicWin
{
private:
	WM_HWIN hDropdCol2, hDropdCol3, hDropdCol4;
	WM_HWIN hTextUnitCol2, hTextUnitCol3, hTextUnitCol4;
    WM_HWIN hTextWarning, hEditSimDens, hTextSimDens, hTextSimDensUnit;
	ValueList *TankValueList;
public:
	TDUAppWinSetup(void);
	~TDUAppWinSetup(void);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
    void ExecDialogBox(WM_HWIN hCurrentWin);
	void GetDialogHandles(void);
	void InitDialog(void);
	void UpdateDialog(WM_HWIN hWin,int Key);
	static void cbTankSetup(WM_MESSAGE *pMsg);
};
