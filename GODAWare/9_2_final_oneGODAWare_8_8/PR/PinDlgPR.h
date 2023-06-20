#pragma once
#include "../OperationDlg.h"

// CPinDlgPR

class CPinDlgPR : public COperationDlg
{
	DECLARE_DYNAMIC(CPinDlgPR)

public:
	CPinDlgPR();
	virtual ~CPinDlgPR();

	enum {IDD = IDD_PIN_PR};

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


