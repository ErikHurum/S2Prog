#pragma once
#include "../OperationDlg.h"

// CPinDlgGR

class CPinDlgGR : public COperationDlg
{
	DECLARE_DYNAMIC(CPinDlgGR)

public:
	CPinDlgGR();
	virtual ~CPinDlgGR();

	enum {IDD = IDD_PIN_GR};

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


