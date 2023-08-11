#pragma once
#define NUMBER_OF_SERVICE_DNS	4
class TDUAppSetupService:public TDUBasicWin
{
private:
	WM_HWIN hDropdCol2, hDropdCol3, hDropdCol4;
	WM_HWIN hTextUnitCol2, hTextUnitCol3, hTextUnitCol4,hTextTotalCol2,hTextTotalCol3,hTextTotalCol4;
  WM_HWIN hTextWarning, hEditSimDens, hTextSimDens, hTextSimDensUnit;
  WM_HWIN hButZeroTP, hButZeroLevel;
	WM_HWIN hTextDensityUnit[NUMBER_OF_SERVICE_DNS];
	WM_HWIN hEditDensity[NUMBER_OF_SERVICE_DNS];
	int ValTabEntries;
	ValueList *ValTabPtr;
public:
	TDUAppSetupService(void);
	~TDUAppSetupService(void);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
    void ExecDialogBox(WM_HWIN hCurrentWin);
	void GetDialogHandles(void);
	void InitDialog(void);
	void Update(void);
	void UpdateDialog(WM_HWIN hWin,int Key);
	static void cbTankSetup(WM_MESSAGE *pMsg);
};
