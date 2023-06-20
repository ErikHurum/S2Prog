#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDisplayDlgTU

class CDisplayDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CDisplayDlgTU)

public:
	CDisplayDlgTU();
	virtual ~CDisplayDlgTU();

	enum {IDD = IDD_DISPLAY_TU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CComboBox m_display;
};


