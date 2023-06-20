#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDampingDlgPR

class CDampingDlgPR : public COperationDlg
{
	DECLARE_DYNAMIC(CDampingDlgPR)

public:
	CDampingDlgPR();
	virtual ~CDampingDlgPR();
	
	enum {IDD = IDD_DAMPING_PR};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CEdit m_damping;
};


