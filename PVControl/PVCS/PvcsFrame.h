#pragma once
#include "pvcssplitterwnd.h"
#include "pvcsSplitterLowerWnd.h"
#include "pvcstankview.h"

#include "pvcsshipdata.h"
#include "PvcsToolBar.h"


// Class Name   : CPvcsFrame
// Description  : Generic Frame Window

class CPvcsFrame : public CFrameWnd
{
    DECLARE_DYNCREATE(CPvcsFrame)
protected:
    CPvcsFrame();           // protected constructor used by dynamic creation
    virtual ~CPvcsFrame();
    DECLARE_MESSAGE_MAP()

    afx_msg LRESULT OnUpdateValues(WPARAM wParam, LPARAM lParam);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    bool m_bIsBallast;
    HANDLE m_hMutex;
    CPvcsToolBar m_PvcsToolBar;

private:
    CPvcsSplitterWnd m_wndSplitter;
    CPvcsSplitterLowerWnd m_wndLowerSplitter;
    int SplitScreens;
public:

    int ScreenNumber;
    CPvcsShipData::TankMap *m_ptrTankMap;
    void UpdateValues(void);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnNcMouseMove(UINT nHitTest,CPoint point);

    afx_msg void OnBnClickedAlarmbutton();
	afx_msg void OnBnClickedPumpButton1();
	afx_msg void OnBnClickedPumpButton2();
	afx_msg void OnBnClickedPumpButton3();
	afx_msg void OnBnClickedPumpButton4();
	afx_msg void OnBnClickedPumpButton5();
};


