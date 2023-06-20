#pragma once
#include "../resource.h"
#include "../curvedialog.h"

// CTrendDlgTU

class CTrendDlgTU : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CTrendDlgTU)

public:
	CTrendDlgTU();
	virtual ~CTrendDlgTU();

	enum {IDD = IDD_TREND_TU};

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


