#pragma once
#define MAX_ENTRIES_ON_WI	60

void HEADER_AddItem            (HEADER_Handle hObj, int Width, const char * s, int Align);

class TDUWaterIngressWin :
	public TDUPresentWin
{
private:
	int PageCount, CurrentPage;
	static const int NumUnitsOnPage;
	int NumberOfUnits, NumberOfUnitsLastPage;
	int LineHeight;
	static const int Col0, Col1, Col2, Col3, Col4, Col5, Col6;
  int StartX,StartY,PageSize;
	bool UserTouch;
	WM_HWIN MainWinHandl, UnitHandl[MAX_ENTRIES_ON_WI];
	HEADER_Handle HeaderHandl;
	TEXT_Handle StatusText[MAX_ENTRIES_ON_WI], NameText[MAX_ENTRIES_ON_WI];
	TEXT_Handle EnableText[MAX_ENTRIES_ON_WI], TempText[MAX_ENTRIES_ON_WI];
	CHECKBOX_Handle OverChBox[MAX_ENTRIES_ON_WI], ProtChBox[MAX_ENTRIES_ON_WI];
	BUTTON_Handle MainButton[MAX_ENTRIES_ON_WI], PreButton[MAX_ENTRIES_ON_WI];
	SCROLLBAR_Handle ScrollHandl;
public:
	TDUWaterIngressWin(void);
	~TDUWaterIngressWin(void);
  PROWaterIngress *CurrentWIPtr;
  bool ProtPlate;
//  int CurrentIndex;
//	int XScrollPos;

	void PWTimer(void);
	void SetButton(void);
	void Paintnew(void);
	void MoveWin(void);
	void ButtonClicked(int ButtID);
//	void UpdateWindow(void);
	void UnitClicked(WM_HWIN hWin,int ButtID);
	void cbEventHandler(WM_MESSAGE* pMsg);
//	void cbWin1(WM_MESSAGE* pMsg);
};
