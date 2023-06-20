#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CServiceOtherDlgPR

class CServiceOtherDlgPR : public COperationDlg
{
	DECLARE_DYNAMIC(CServiceOtherDlgPR)

public:
	CServiceOtherDlgPR();
	virtual ~CServiceOtherDlgPR();

	enum {IDD = IDD_SERVICEOTHER_PR};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CComboBox m_language;
	CComboBox m_unit;
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSave();
};


