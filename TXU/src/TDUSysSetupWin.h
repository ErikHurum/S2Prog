#pragma once

class TDUSysSetupWin:public TDUBasicWin
{
private:
	WM_HWIN hButBuzzer, hButUpp, hButDown,hButFactDef,hButWriteConfig;
	WM_HWIN hEditScreen, hEditAlOffTime;
  WM_HWIN hDropdBackColor, hDropdForeColor;

	bool HoldSound;

public:
	TDUSysSetupWin(void);
	~TDUSysSetupWin(void);
	AnsiString ConfigKey;
  volatile bool PinCodeOK;
  AnsiString TempPinCode;
	void ExecDialogBox(WM_HWIN hCurrentWin);
 	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
  void GetDialogHandles(void);
	void InitSysWin(void);
	void UpdateSysWin(void);
  void SetAppColor(WM_HWIN hWin,int Key);
	void SetScreenOffTime(AnsiString StringBuf);
	void SetAlarmOffTime(AnsiString StringBuf);
  void ChangePinCode(AnsiString PinCodeStr);
  bool CheckPinCode(AnsiString PinCodeStr);

  void FirstNewPinCode(AnsiString PinCodeStr);
  void SecondNewPinCode(AnsiString PinCodeStr);
  //void CalibrateScreen(void);

	void MakeSound(void);
	static void cbSysWin(WM_MESSAGE *pMsg);

  static const U32 TimeOut = 60000;
  volatile bool Closed;
  CloseWindowTimer CloseTimer;
};
