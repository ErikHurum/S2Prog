#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CAdvanced1DlgTU

class CAdvanced1DlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CAdvanced1DlgTU)

public:
	CAdvanced1DlgTU();
	virtual ~CAdvanced1DlgTU();

	enum {IDD = IDD_ADVANCEDSETUP1_TU};
	
	void LoadData();
	void SaveData();

protected:
	CArray<BYTE> ba;
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CButton m_checkEnableFlow;
	CComboBox m_checkCalibration;
	afx_msg void OnCbnSelchangeComboCalibration();
	afx_msg void OnBnClickedBtnCalibrate();
};


