#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CAdvanced1DlgGR

class CAdvanced1DlgGR : public COperationDlg
{
	DECLARE_DYNAMIC(CAdvanced1DlgGR)

public:
	CAdvanced1DlgGR();
	virtual ~CAdvanced1DlgGR();

	enum {IDD = IDD_ADVANCEDSETUP1_GR};
	
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


