#pragma once
#include "../OperationDlg.h"

// CFalseEchoDlgTU

class CFalseEchoDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CFalseEchoDlgTU)

public:
	CFalseEchoDlgTU();
	virtual ~CFalseEchoDlgTU();

	enum {IDD = IDD_FALSEECHO_TU};

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


