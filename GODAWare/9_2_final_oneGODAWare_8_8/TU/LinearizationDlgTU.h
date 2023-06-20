#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"
#include "../MappingEditDlg.h"
// CLinearizationDlgTU

class CLinearizationDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CLinearizationDlgTU)

public:
	CLinearizationDlgTU();
	virtual ~CLinearizationDlgTU();

	enum {IDD = IDD_LINEARIZATION_TU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CEdit m_0percent;
	CEdit m_100percent;
	CComboBox m_unit;
	CComboBox m_linearizationType;
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnCbnSelchangeComboLinearizationtype();
	afx_msg void OnBnClickedRadioLinear();
	CComboBox m_comboVesselType;
	afx_msg void OnCbnSelchangeComboVesseltype();
	CButton m_btnEdit;
};


