#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDisplayDlgPR

class CDisplayDlgPR : public COperationDlg
{
	DECLARE_DYNAMIC(CDisplayDlgPR)

public:
	CDisplayDlgPR();
	virtual ~CDisplayDlgPR();

	enum {IDD = IDD_DISPLAY_PR};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CComboBox m_display;
};


