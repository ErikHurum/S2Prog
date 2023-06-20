#pragma once

class TDUTankDensitySetting
{
private:
	WM_HWIN hTextName, hRadioLinAPI;
	WM_HWIN hCheckMeasDens, hTextMeasDens;
//API
    WM_HWIN hTextAPI, hTextAPI1, hTextAPI2, hTextAPI1Unit, hTextAPI2Unit;
    WM_HWIN hDropdAPI, hEditAPI1, hEditAPI2;
//Linear
    WM_HWIN hTextLin, hCheckLin;
    WM_HWIN hEditSimDens, hTextSimDens, hTextSimDensUnit;
    WM_HWIN hTextRef1, hTextRef2, hTextCoeff;
    WM_HWIN hEditTemp1, hEditTemp2, hEditDens1, hEditDens2, hEditCoeff;
    WM_HWIN hTextTemp1Unit, hTextTemp2Unit, hTextDens1Unit, hTextDens2Unit, hTextCoeffUnit;

public:
	TDUTankDensitySetting(void);
	~TDUTankDensitySetting(void);
	WM_HWIN WinHandl;
//	PRogramObject *CurrentPROPtr;
	PROTank *CurrentPROPtr;
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];

  void ExecDialogBox(WM_HWIN hCurrentWin, PRogramObject *PROPtr);
	void GetDialogHandles(void);
	void InitDialog(void);
    void UseAPI(void);
    void UseLinear(void);
    void UpdateDialog(int key, AnsiString ValueString);

	static void cbTankSetup(WM_MESSAGE * pMsg);
};
