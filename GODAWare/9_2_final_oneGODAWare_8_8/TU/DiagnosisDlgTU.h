#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDiagnosisDlgTU

class CDiagnosisDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CDiagnosisDlgTU)

public:
	CDiagnosisDlgTU();
	virtual ~CDiagnosisDlgTU();
	enum {IDD = IDD_DIAGNOSIS_TU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CEdit m_min;
	CEdit m_max;
	CEdit m_current;
	CEdit m_temperature;
	CStringArray m_deviceStat;
	CListBox m_statList;
};


