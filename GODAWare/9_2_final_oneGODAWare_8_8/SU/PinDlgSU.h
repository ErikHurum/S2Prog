#pragma once
#include "../OperationDlg.h"

// CPinDlgSU

class CPinDlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CPinDlgSU)

public:
	CPinDlgSU();
	virtual ~CPinDlgSU();

	enum {IDD = IDD_PIN_SU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnUpdate();
};


