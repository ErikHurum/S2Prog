#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CAdvanced2DlgSU

class CAdvanced2DlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CAdvanced2DlgSU)

public:
	CAdvanced2DlgSU();
	virtual ~CAdvanced2DlgSU();

	enum {IDD = IDD_ADVANCEDSETUP2_SU};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CEdit m_20mA;
	CEdit m_4mA;
	CEdit m_freq;
	CEdit m_tgc;
	CEdit m_echoAm;
	CEdit m_echoLimit;
	CEdit m_distOffset;
	CEdit m_velocityOffset;
	afx_msg void OnBnClickedButtonDistadj();
	afx_msg void OnBnClickedButtonVeloadj();
	CEdit m_editShortWidth;
	CEdit m_editLongWidth;
	CEdit m_editFreqMin;
	CEdit m_editFreqMax;
	CEdit m_editTempOffset;
	CEdit m_noiselimit;
	CComboBox m_comboPointNumber;
	afx_msg void OnCbnSelchangeComboPointnumber();
};
