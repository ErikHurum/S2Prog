#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CAdvanced1DlgPR

class CAdvanced1DlgPR : public COperationDlg
{
	DECLARE_DYNAMIC(CAdvanced1DlgPR)

public:
	CAdvanced1DlgPR();
	virtual ~CAdvanced1DlgPR();

	enum {IDD = IDD_ADVANCEDSETUP1_PR};
	
	void LoadData();
	void SaveData();

protected:
	CArray<BYTE> ba;

	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CButton m_ratioLearned;
	CButton m_checkEnableFlow;
	CButton m_ratioNotLearn;
	afx_msg void OnBnClickedRadioNotlearn();
	afx_msg void OnBnClickedRadioLearn();
	afx_msg void OnBnClickedBtnSetlearn();
	CComboBox m_checkCalibration;
	afx_msg void OnCbnSelchangeComboCalibration();
	afx_msg void OnBnClickedBtnCalibrate();
};


