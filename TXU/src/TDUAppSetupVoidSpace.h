#pragma once

class TDUAppSetupVoidSpace:public TDUBasicWin
{
private:
	WM_HWIN hDropdCol2, hDropdCol3, hDropdCol4;
	WM_HWIN hTextUnitCol2, hTextUnitCol3, hTextUnitCol4,hTextTotalVol,hTextTotalVolUnit,hTextTotalWgt,hTextTotalWgtUnit;
	WM_HWIN hTextDensUnit5;
	WM_HWIN hEditBallastDens1;
  WM_HWIN hTextWarning, hEditSimDens, hTextSimDens, hTextSimDensUnit;
  WM_HWIN hButZeroTP, hButZeroLevel;
  int ValTabEntries;
  ValueList *ValTabPtr;

public:
	TDUAppSetupVoidSpace(void);
	~TDUAppSetupVoidSpace(void);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
    void ExecDialogBox(WM_HWIN hCurrentWin);
	void GetDialogHandles(void);
	void InitDialog(void);
	void UpdateDialog(WM_HWIN hWin,int Key);
	void Update(void);
	static void cbTankSetup(WM_MESSAGE *pMsg);
};
