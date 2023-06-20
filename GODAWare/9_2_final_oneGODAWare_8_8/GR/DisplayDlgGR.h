#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDisplayDlgGR

class CDisplayDlgGR : public COperationDlg
{
	DECLARE_DYNAMIC(CDisplayDlgGR)

public:
	CDisplayDlgGR();
	virtual ~CDisplayDlgGR();

	enum {IDD = IDD_DISPLAY_GR};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CComboBox m_display;
};


