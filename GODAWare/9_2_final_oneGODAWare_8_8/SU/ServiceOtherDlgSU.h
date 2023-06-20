#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CServiceOtherDlgSU

class CServiceOtherDlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CServiceOtherDlgSU)

public:
	CServiceOtherDlgSU();
	virtual ~CServiceOtherDlgSU();

	enum {IDD = IDD_SERVICEOTHER_SU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CComboBox m_language;
	CComboBox m_unit;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
};


