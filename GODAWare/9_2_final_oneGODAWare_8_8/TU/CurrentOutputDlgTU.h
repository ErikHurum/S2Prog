#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CCurrentOutputDlgTU

class CCurrentOutputDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CCurrentOutputDlgTU)

public:
	CCurrentOutputDlgTU();
	virtual ~CCurrentOutputDlgTU();

	enum {IDD = IDD_CURRENTOUTPUT_TU};

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


