#pragma once

class TDUTankAlarmSetting
{
private:
	WM_HWIN hOverfill, hHighLev, hLowLev, hHighTemp, hLowTemp, hHighPress, hLowPress;
	WM_HWIN hEditOverfill, hEditHighLev, hEditLowLev, hEditHighTemp, hEditLowTemp, hEditHighPress, hEditLowPress;
	WM_HWIN hTextOverfill, hTextHighLev, hTextLowLev, hTextHighTemp, hTextLowTemp, hTextHighPress, hTextLowPress;
	WM_HWIN hCheckOverfill,hCheckHighLev,hCheckLowLev,hCheckHighTemp,hCheckLowTemp,hCheckHighPress,hCheckLowPress;
	WM_HWIN hPrevBut, hTextName;

public:
	TDUTankAlarmSetting(void);
	~TDUTankAlarmSetting(void);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[]; 
	WM_HWIN WinHandl;
	PRogramObject *CurrentPROPtr;
	void ExecDialogBox(WM_HWIN hCurrentWin, PRogramObject *PROPtr);
	void GetDialogHandles(void);
	void InitDialog(void);
	void UpdateDialog(int key, char *buf);
	static void cbTankSetup(WM_MESSAGE * pMsg);
};
