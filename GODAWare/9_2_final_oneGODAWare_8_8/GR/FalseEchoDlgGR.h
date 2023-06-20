#pragma once
#include "../OperationDlg.h"

// CFalseEchoDlgGR

class CFalseEchoDlgGR : public COperationDlg
{
	DECLARE_DYNAMIC(CFalseEchoDlgGR)

public:
	CFalseEchoDlgGR();
	virtual ~CFalseEchoDlgGR();

	enum {IDD = IDD_FALSEECHO_GR};

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


