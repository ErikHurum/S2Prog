#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CCurrentOutputDlgPR

class CCurrentOutputDlgPR : public COperationDlg
{
	DECLARE_DYNAMIC(CCurrentOutputDlgPR)

public:
	CCurrentOutputDlgPR();
	virtual ~CCurrentOutputDlgPR();

	enum {IDD = IDD_CURRENTOUTPUT_PR};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CComboBox m_error;
	CComboBox m_output;
	CComboBox m_min;
};


