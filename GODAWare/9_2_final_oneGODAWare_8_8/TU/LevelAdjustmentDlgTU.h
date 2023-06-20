#pragma once
#include "../resource.h"
#include "afxwin.h"
#include "../OperationDlg.h"

// CLevelAdjustmentDlgTU

class CLevelAdjustmentDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CLevelAdjustmentDlgTU)

public:
	CLevelAdjustmentDlgTU();
	virtual ~CLevelAdjustmentDlgTU();

	enum { IDD = IDD_LEVEL_ADJUSTMENT_TU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()


public:
	void LoadData();
	void SaveData();

public:
	CEdit m_highPercent;
	CEdit m_high;
	CEdit m_rigion;
	CEdit m_low;
	CEdit m_lowPercent;
	CEdit m_shadowRigion;
};


	