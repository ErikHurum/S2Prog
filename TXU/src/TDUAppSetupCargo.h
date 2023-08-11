#pragma once

class TDUAppSetupCargo:public TDUBasicWin
{
private:
	WM_HWIN hDropdCol2, hDropdCol3, hDropdCol4,hDropdOpMode;
	WM_HWIN hTextUnitCol2, hTextUnitCol3, hTextUnitCol4,hTextTotalCol2,hTextTotalCol3,hTextTotalCol4;
  WM_HWIN hTextWarning, hEditSimDens, hTextSimDens, hTextSimDensUnit;
  WM_HWIN hButZeroTP, hButZeroLevel;
  int ValTabEntries;
  ValueList *ValTabPtr;

public:
	TDUAppSetupCargo(void);
	~TDUAppSetupCargo(void);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
    void ExecDialogBox(WM_HWIN hCurrentWin);
	void GetDialogHandles(void);
	void InitDialog(void);
	void UpdateDialog(WM_HWIN hWin,int Key);
	void Update(void);
	static void cbTankSetup(WM_MESSAGE *pMsg);
};
