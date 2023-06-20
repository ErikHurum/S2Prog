#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CCurrentOutputDlgGR

class CCurrentOutputDlgGR : public COperationDlg
{
	DECLARE_DYNAMIC(CCurrentOutputDlgGR)

public:
	CCurrentOutputDlgGR();
	virtual ~CCurrentOutputDlgGR();

	enum {IDD = IDD_CURRENTOUTPUT_GR};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CComboBox m_error;
	CComboBox m_output;
	CComboBox m_min;
	afx_msg void OnCbnSelchangeComboError();
};


