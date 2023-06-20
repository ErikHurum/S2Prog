#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CResetDlgSU

class CResetDlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CResetDlgSU)

public:
	CResetDlgSU();
	virtual ~CResetDlgSU();

	enum {IDD = IDD_RESET_SU};

	void LoadData();
	void SaveData();

	void Reset(int nResetMode);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	afx_msg void OnBnClickedBtnReset1();
	afx_msg void OnBnClickedBtnReset2();
	afx_msg void OnBnClickedBtnReset3();
	afx_msg void OnBnClickedBtnReset4();
	CComboBox m_comboPointNumber;
	afx_msg void OnCbnSelchangeComboPointnumber();
};


