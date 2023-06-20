#pragma once
#include "../resource.h"
#include "../curvedialog.h"

// CTrendDlgPR

class CTrendDlgPR : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CTrendDlgPR)

public:
	CTrendDlgPR();
	virtual ~CTrendDlgPR();

	enum {IDD = IDD_TREND_PR};

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CCurveDialog m_curveDraw;
};


