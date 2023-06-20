#pragma once

class TDUSysWin2:public TDUBasicWin
{
private:
    static unsigned IdSet1[];
    static unsigned IdSet2[];
    WM_HWIN hEditAtm, hDropAtmRef, hTextAtmUnit;
  WM_HWIN hEditTrim, hDropTrim, hTextTrimUnit;
    WM_HWIN hEditList, hDropList, hTextListUnit;
    WM_HWIN hEditDF, hEditDP, hEditDS, hEditDA, hRadioDraft;
    WM_HWIN hEditDFP, hEditDFS, hEditDAP, hEditDAS;
  WM_HWIN hEditSeaWater, hTextSWUnit;
  int IncAvailable;

public:
    TDUSysWin2(void);
    ~TDUSysWin2(void);
    AnsiString ValueString;
    void ExecDialogBox(WM_HWIN hCurrentWin);
    static const GUI_WIDGET_CREATE_INFO aDialogCreate[];
    void GetDialogHandles(void);
    void InitDropDown(void);
    void InitSysWin(void);
    void UpdateSysWin(void);
    void UpdateSystem(WM_HWIN hWin,int Key);
  void SetTrimSource(int Index);
  void SetListSource(int Index);
    static void cbSysWin(WM_MESSAGE *pMsg);
};
