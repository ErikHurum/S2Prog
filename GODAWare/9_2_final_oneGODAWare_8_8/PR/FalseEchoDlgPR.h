#pragma once
#include "../OperationDlg.h"

// CFalseEchoDlgPR

class CFalseEchoDlgPR : public COperationDlg
{
	DECLARE_DYNAMIC(CFalseEchoDlgPR)

public:
	CFalseEchoDlgPR();
	virtual ~CFalseEchoDlgPR();

	enum {IDD = IDD_FALSEECHO_PR};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnUpdate();
	afx_msg void OnBnClickedBtnDelete();
};


