#pragma once
#include "../resource.h"
#include "afxwin.h"
#include "../OperationDlg.h"

// CLevelAdjustmentDlgSU

class CLevelAdjustmentDlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CLevelAdjustmentDlgSU)

public:
	CLevelAdjustmentDlgSU();
	virtual ~CLevelAdjustmentDlgSU();

	enum { IDD = IDD_LEVEL_ADJUSTMENT_SU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()


public:
	void LoadData();
	void SaveData();

public:
	CEdit m_highPercent;
	CEdit m_high;
	CEdit m_low;
	CEdit m_lowPercent;
	CEdit m_shadowRigion;
	CComboBox m_comboPointNumber;
	afx_msg void OnCbnSelchangeComboPointnumber();
};


	