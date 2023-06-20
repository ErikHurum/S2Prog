#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDisplayDlgSU

class CDisplayDlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CDisplayDlgSU)

public:
	CDisplayDlgSU();
	virtual ~CDisplayDlgSU();

	enum {IDD = IDD_DISPLAY_SU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CComboBox m_display;
	CComboBox m_comboPointNumber;
	afx_msg void OnCbnSelchangeComboPointnumber();
};


