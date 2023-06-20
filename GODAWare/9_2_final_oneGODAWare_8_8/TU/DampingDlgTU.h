#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDampingDlgTU

class CDampingDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CDampingDlgTU)

public:
	CDampingDlgTU();
	virtual ~CDampingDlgTU();
	
	enum {IDD = IDD_DAMPING_TU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CEdit m_damping;
};


