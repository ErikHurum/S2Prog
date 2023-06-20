#pragma once
#include "../OperationDlg.h"

// CResetDlgPR

class CResetDlgPR : public COperationDlg
{
	DECLARE_DYNAMIC(CResetDlgPR)

public:
	CResetDlgPR();
	virtual ~CResetDlgPR();

	enum {IDD = IDD_RESET_PR};

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


