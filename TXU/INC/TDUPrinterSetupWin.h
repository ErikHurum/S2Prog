#pragma once

#define P_SETUP_GUI_SEL_FIRST 	GUI_ID_CHECK0
#define P_SETUP_GUI_SEL_LAST  	GUI_ID_CHECK5
#define P_SETUP_MAX_GUI_SELECTS (P_SETUP_GUI_SEL_LAST-P_SETUP_GUI_SEL_FIRST+1)
#define P_SETUP_GUI_EDIT_FIRST 	GUI_ID_EDIT0
#define P_SETUP_GUI_EDIT_LAST  	GUI_ID_EDIT0
#define P_SETUP_MAX_GUI_EDITS   (P_SETUP_GUI_EDIT_LAST-P_SETUP_GUI_EDIT_FIRST+1)
#define P_SETUP_GUI_TEXT_FIRST 	GUI_ID_TEXT0
#define P_SETUP_GUI_TEXT_LAST  	GUI_ID_TEXT2
#define P_SETUP_MAX_GUI_TEXTS   (P_SETUP_GUI_TEXT_LAST-P_SETUP_GUI_TEXT_FIRST+1)
#define P_SETUP_MAX_BUTTONS	1
class TDUPrinterSetupWin:public TDUBasicWin {
private:
		WM_HWIN hSelect[P_SETUP_MAX_GUI_SELECTS];
		WM_HWIN hEdit[P_SETUP_MAX_GUI_EDITS];
		WM_HWIN hText[P_SETUP_MAX_GUI_TEXTS];
		WM_HWIN hButtons[P_SETUP_MAX_BUTTONS];

public:
		TDUPrinterSetupWin(void);
		~TDUPrinterSetupWin(void);
		void ExecDialogBox(WM_HWIN hCurrentWin);
		static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
		void GetDialogHandles(void);
		void InitPrintWin(void);
		static void cbEventHandler(WM_MESSAGE *pMsg);

		static const U32 TimeOut = 60000;
		volatile bool Closed;
		CloseWindowTimer CloseTimer;
};
