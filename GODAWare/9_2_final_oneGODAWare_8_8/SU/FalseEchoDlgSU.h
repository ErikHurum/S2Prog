#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CFalseEchoDlgSU

class CFalseEchoDlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CFalseEchoDlgSU)

public:
	CFalseEchoDlgSU();
	virtual ~CFalseEchoDlgSU();

	enum {IDD = IDD_FALSEECHO_SU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnUpdate();
	afx_msg void OnBnClickedBtnDelete();
	CComboBox m_comboPointNumber;
	afx_msg void OnCbnSelchangeComboPointnumber();
};


