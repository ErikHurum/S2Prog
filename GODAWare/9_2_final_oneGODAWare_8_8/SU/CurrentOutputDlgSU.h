#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CCurrentOutputDlgSU

class CCurrentOutputDlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CCurrentOutputDlgSU)

public:
	CCurrentOutputDlgSU();
	virtual ~CCurrentOutputDlgSU();

	enum {IDD = IDD_CURRENTOUTPUT_SU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CComboBox m_error;
	CComboBox m_output;
	CComboBox m_min;
	CComboBox m_comboPointNumber;
	afx_msg void OnCbnSelchangeComboPointnumber();
};


