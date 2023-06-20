#pragma once

class TDUCalDataWin:public TDUBasicWin {
private:
	WM_HWIN SnsListView;
	bool LevOffsetWinEnable;
	PRogramObjectBase *CurrentHWUnit;
	bool UserTouch;
	int TimerCount;
	bool TimedOut;
	PROIOComponent    *SnsPtr;
	PRogramObjectBase *Owner;
	AnsiString SnsInfo;
public:
	TDUCalDataWin(void);
	~TDUCalDataWin(void);
	void CreatePage(WM_HWIN hCurrentWin,PRogramObjectBase *OwnerPtr, PROIOComponent *PROPtr, AnsiString SnsInfo);
	void Update(void);

	volatile bool IsClosed;
	volatile int PreviousSysWin;

	void ExecDialogBox(WM_HWIN hCurrentWin);
	static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
	void GetDialogHandles(void);
	void InitSysWin(void);

	void ClearList(const char *Title[]);
	void PWTimer(void);
	void Paintnew(void);
	PROIOComponent* 	GetSnsPtr(void);
	PRogramObjectBase*  GetOwner(void);
	static void cbSysWin(WM_MESSAGE *pMsg);
	void ChangeText(int Index);

};
