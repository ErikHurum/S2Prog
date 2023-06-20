#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDampingDlgSU

class CDampingDlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CDampingDlgSU)

public:
	CDampingDlgSU();
	virtual ~CDampingDlgSU();
	
	enum {IDD = IDD_DAMPING_SU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CEdit m_damping;
	CComboBox m_comboPointNumber;
	afx_msg void OnCbnSelchangeComboPointnumber();
};


