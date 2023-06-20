#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CAdvanced1DlgSU

class CAdvanced1DlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CAdvanced1DlgSU)

public:
	CAdvanced1DlgSU();
	virtual ~CAdvanced1DlgSU();

	enum {IDD = IDD_ADVANCEDSETUP1_SU};
	
	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CButton m_checkEnableFlow;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CComboBox m_comboCurrentOutPort;
	CComboBox m_comboPointNumber;
	CComboBox m_comboCurrentOut;
	CComboBox m_comboSensor;
	CComboBox m_comboRelay;
	CComboBox m_comboRelayWarning;
	CEdit m_editHighWarning;
	CEdit m_editLowWarning;
	CEdit m_editHysteresys;
	CButton m_checkEnableMutiSensor;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboRelayalarm();
	afx_msg void OnCbnSelchangeComboRelay();
	afx_msg void OnCbnSelchangeComboSensor();
	afx_msg void OnCbnSelchangeCurrentOutPort();
	CButton m_solid;
	afx_msg void OnStnClickedTitle();
};


