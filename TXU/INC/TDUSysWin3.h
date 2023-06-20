#pragma once

class TDUSysWin3:public TDUBasicWin {
private:
	WM_HWIN hDropdPRO;
	WM_HWIN hListviewIO;
	PRogramObject *CurrentIOUnit;
	vector<PRogramObjectBase*>DropdIOUnitList;
	bool UserTouch;
	int TimerCount;
	bool TimedOut;

	//AnsiString SensorInfo[MAX_SENSORS_ON_AD_CARD];

public:
	TDUSysWin3(void);
	~TDUSysWin3(void);
	PRONode *CurrentTNode;
	void SetListViewColor(void);

	void ExecDialogBox(WM_HWIN hCurrentWin);
	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
	void GetDialogHandles(void);
	void SetListviewRow(int Row,int Ch, AnsiString NameStr,AnsiString LocStr,AnsiString TypeStr,AnsiString RawValStr,AnsiString ValStr,AnsiString GainStr,AnsiString OffsetStr,AnsiString EnableStr,AnsiString UnitStr);
	void SetListviewRow2(int Row,AnsiString CalVal,AnsiString CnvCalErr,AnsiString PromStat,AnsiString PCStat,AnsiString UsePCSetUp, AnsiString ADSns, AnsiString PCSns, AnsiString UseFromPc);
	bool SetupWin(void);
	void InitSysWin(void);
	void ClearList(void);
	void UpdateSysWin(void);
	static void cbSysWin(WM_MESSAGE *pMsg);
};
