#pragma once
#include "../resource.h"
#include "../curvedialog.h"
#include "afxwin.h"

// CTrendDlgSU

class CTrendDlgSU : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CTrendDlgSU)

public:
	CTrendDlgSU();
	virtual ~CTrendDlgSU();

	enum {IDD = IDD_TREND_SU};

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CCurveDialog m_curveDraw;
	CComboBox m_comboPointNumber;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboPointnumber();
};


