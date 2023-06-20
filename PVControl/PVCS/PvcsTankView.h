#pragma once
#include "pvcstankdlg.h"
#include "pvcsconfiguration.h"
#include "pvcsshipdata.h"


// CPvcsTankView view

class CPvcsTankView : public CView
{
	DECLARE_DYNCREATE(CPvcsTankView)

protected:
	CPvcsTankView();           // protected constructor used by dynamic creation
	virtual ~CPvcsTankView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	vector <CPvcsTankDlg*> m_dlgTankArray;
    double ScaleX;
    double ScaleY;
    int SplitScreens;
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	bool AddTank(const int& param_iTankID);
	void ShowTank(const int& param_iTankID);
private:
	bool m_bShowRightSide;
	CPvcsShipData::TankMap *m_ptrTankMap;
public:
	void Update(CPvcsShipData::TankMap *pTankMap);
};


