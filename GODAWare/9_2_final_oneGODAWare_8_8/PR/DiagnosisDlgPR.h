#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDiagnosisDlgPR

class CDiagnosisDlgPR : public COperationDlg
{
	DECLARE_DYNAMIC(CDiagnosisDlgPR)

public:
	CDiagnosisDlgPR();
	virtual ~CDiagnosisDlgPR();
	enum {IDD = IDD_DIAGNOSIS_PR};

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
};


