#pragma once

class TDUSystemWin :
public TDUPresentWin {

public:
	TDUSystemWin(void);
	~TDUSystemWin(void);

#ifdef S2TXU
	OS_RSEMA SysWinSema;
#else
	int AcquireCnt;
	ANCriticalSection *SysWinSema;
#endif

	TDUSysWin1      *SysWin1;
	TDUSysWin2      *SysWin2;
	TDUSysWin3      *SysWin3;
	TDUSysWin4      *SysWin4;
	TDUSysWin5      *SysWin5;

	volatile int CurrentSysWin;
	volatile bool SysWin1IsClosed;
	volatile bool SysWin2IsClosed;
	volatile bool SysWin3IsClosed;
	volatile bool SysWin4IsClosed;
	volatile bool SysWin5IsClosed;
	void SetButton(void);
	void ButtonClicked(int ButtID);
	void CloseSystemWin(void);
	void cbEventHandler(WM_MESSAGE* pMsg);
	// Routines for Saving of Settings
	bool IsModified;
	void SaveSettings(TSNConfigString *SettingsString);
	bool RestoreSettings(TSNConfigString *SettingsString);
	void SetModifiedFlag(void);
	void Protect(void);
	void UnProtect(void);
    void ChangeSystemWindow(int NewWindow);
};
