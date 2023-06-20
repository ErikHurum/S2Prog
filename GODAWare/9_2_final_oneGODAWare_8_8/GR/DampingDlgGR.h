#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDampingDlgGR

class CDampingDlgGR : public COperationDlg
{
	DECLARE_DYNAMIC(CDampingDlgGR)

public:
	CDampingDlgGR();
	virtual ~CDampingDlgGR();
	
	enum {IDD = IDD_DAMPING_GR};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CEdit m_damping;
};


