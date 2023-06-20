#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CServiceOtherDlgGR

class CServiceOtherDlgGR : public COperationDlg
{
	DECLARE_DYNAMIC(CServiceOtherDlgGR)

public:
	CServiceOtherDlgGR();
	virtual ~CServiceOtherDlgGR();

	enum {IDD = IDD_SERVICEOTHER_GR};

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


