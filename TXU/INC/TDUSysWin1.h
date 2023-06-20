#pragma once
#include "TDUUserManual.h"
#include "TDUConfigLoginWin.h"
#include "TDUSysSetupWin.h"
#include "TDUPrinterSetupWin.h"

class TDUSysWin1:public TDUBasicWin
{
private:
		WM_HWIN hTextProg, hTextData, hTextSystem;
		WM_HWIN hTextProgVersion, hTextDataVersion, hTextSystemID;
		WM_HWIN hDropdLanguage, hRadioUnitSystem, hDSTCheckbox;
		WM_HWIN hDropdOpMode;
		WM_HWIN hEditTime, hEditDate, hEditGMT, hEditPlus, hEditMinus;
		WM_HWIN hButManual, hButSetup, hButPrinter, htextLanguage;

public:
		TDUSysWin1(void);
		~TDUSysWin1(void);
		AnsiString ConfigKey;

		TDUUserManual *UserManualWin;
		TDUSysSetupWin *SysSetupWin;
		TDUPrinterSetupWin *PrintSetupWin;
		TDUConfigLoginWin *ConfigLoginWin;

		void InitConfigLoginWin(WM_HWIN hWin);
		void CheckConfigKey(char* StrPtr);
		void ExecDialogBox(WM_HWIN hCurrentWin);
		static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
		void CloseSysWin(void);
		void GetDialogHandles(void);
		void InitSysWin(void);
		void UpdateSysWin(void);
		void SetTime(AnsiString TimeString);
		void SetDate(AnsiString TimeString);
		void UpdateUnitSystem(WM_HWIN hWin);
		static void cbSysWin(WM_MESSAGE *pMsg);
};
