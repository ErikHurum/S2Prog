#pragma once
#include "tdupresentwin.h"

class TDUGroupWin :
public TDUPresentWin {
private:
	int CurrentPage;
	static const int  NumUnitsOnPage;
	int NumberOfUnits, NumberOfUnitsLastPage;
	int But5LangKey;
protected:
	vector<PRogramObjectBase*> ObjectVector;
	int NumberOfPages;
	bool UserTouch;
	int TimerCount;
	bool TimedOut;
	HEADER_Handle ListHeadHandl;
	LISTVIEW_Handle ListViewHandl;

public:
	TDUGroupWin(vector<PRogramObjectBase*> ObjVector, int WinId, TDUValueTable *DefValTable);
	~TDUGroupWin(void);

	PRONode *CurrentTNode;
	TDUValueTable *ValueTable;
	TDUValueTable *DefValueTable;

	void SetListViewColor(void);
	void TableSetup(void);
	void PWTimer(void);
	virtual void SetButton(void);
	void Paintnew(void);
	void PaintnewHeading(void);
	bool SetupWin(void);
	void UpdateWinSetup(WM_HWIN hWin,int Key);

	virtual void ButtonClicked(int ButtID);
	void cbEventHandler(WM_MESSAGE* pMsg);
	virtual void AppSetup(void);
	virtual void PrintReport(int PrinterId);
};
