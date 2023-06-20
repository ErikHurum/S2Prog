#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDiagnosisDlgSU

class CDiagnosisDlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CDiagnosisDlgSU)

public:
	CDiagnosisDlgSU();
	virtual ~CDiagnosisDlgSU();
	enum {IDD = IDD_DIAGNOSIS_SU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CEdit m_min;
	CEdit m_max;
	CEdit m_temperature;
	CEdit m_current;
	CStringArray m_deviceStat;
	CListBox m_statList;
	CComboBox m_comboPointNumber;
	afx_msg void OnCbnSelchangeComboPointnumber();
};


