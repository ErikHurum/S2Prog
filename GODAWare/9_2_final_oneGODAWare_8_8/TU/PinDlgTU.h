#pragma once
#include "../OperationDlg.h"

// CPinDlgTU

class CPinDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CPinDlgTU)

public:
	CPinDlgTU();
	virtual ~CPinDlgTU();

	enum {IDD = IDD_PIN_TU};

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


