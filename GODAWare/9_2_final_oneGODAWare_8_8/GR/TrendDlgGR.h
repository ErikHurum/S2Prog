#pragma once
#include "../resource.h"
#include "../curvedialog.h"

// CTrendDlgGR

class CTrendDlgGR : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CTrendDlgGR)

public:
	CTrendDlgGR();
	virtual ~CTrendDlgGR();

	enum {IDD = IDD_TREND_GR};

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


