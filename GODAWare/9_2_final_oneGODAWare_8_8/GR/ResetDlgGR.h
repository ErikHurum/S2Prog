#pragma once
#include "../OperationDlg.h"

// CResetDlgGR

class CResetDlgGR : public COperationDlg
{
	DECLARE_DYNAMIC(CResetDlgGR)

public:
	CResetDlgGR();
	virtual ~CResetDlgGR();

	enum {IDD = IDD_RESET_GR};

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
};


