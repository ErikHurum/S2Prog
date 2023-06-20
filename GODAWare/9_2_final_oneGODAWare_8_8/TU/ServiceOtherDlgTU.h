#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CServiceOtherDlgTU

class CServiceOtherDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CServiceOtherDlgTU)

public:
	CServiceOtherDlgTU();
	virtual ~CServiceOtherDlgTU();

	enum {IDD = IDD_SERVICEOTHER_TU};

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


