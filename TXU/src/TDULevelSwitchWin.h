#pragma once
#define LSW_MAX_ENTRIES	   60
#define LSW_NOT_DEFINED			-1
#define LSW_HIGH_LEVEL			0
#define LSW_OVERFILL			  1
#define LSW_MAX_PAGES				10

#define LSW_BUTTON0		GUI_ID_USER
class TDULevelSwitchWin :
    public TDUPresentWin {
private:
    set<int> Page;
    set<short> XPos;
    set<short> YPos;
    int PageCount, CurrentPage;
    int FirstPage;
    static const int LineHeight = 20;
    int StartX,StartY; //,PageSize;
    bool UserTouch;
    BUTTON_Handle TankButton[LSW_MAX_ENTRIES];
    int  LastPage;
    SCROLLBAR_Handle ScrollHandl;
    int LevelSwicthSystem;
    WM_HWIN MainWinHandl;
    WM_HWIN VisibleWinHandl;
    void SetButtonColours(BUTTON_Handle TButton, PROLevelSwitch *LSwitchPtr);

public:
    TDULevelSwitchWin(void);
    ~TDULevelSwitchWin(void);
//  int CurrentIndex;
//	int XScrollPos;

    void PWTimer(void);
    void SetButton(void);
    void RefreshWindow(void);
    void MoveWin(void);
    void ButtonClicked(int ButtID);
//	void UpdateWindow(void);
    void UnitClicked(WM_HWIN hWin, int ButtID);
    void cbEventHandler(WM_MESSAGE *pMsg);
//	void cbWin1(WM_MESSAGE* pMsg);
};
