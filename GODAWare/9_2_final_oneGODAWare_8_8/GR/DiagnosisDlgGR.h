#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CDiagnosisDlgGR

class CDiagnosisDlgGR : public COperationDlg
{
	DECLARE_DYNAMIC(CDiagnosisDlgGR)

public:
	CDiagnosisDlgGR();
	virtual ~CDiagnosisDlgGR();
	enum {IDD = IDD_DIAGNOSIS_GR};

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


