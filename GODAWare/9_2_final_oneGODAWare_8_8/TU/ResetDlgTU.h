#pragma once
#include "../OperationDlg.h"

// CResetDlgTU

class CResetDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CResetDlgTU)

public:
	CResetDlgTU();
	virtual ~CResetDlgTU();

	enum {IDD = IDD_RESET_TU};

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


