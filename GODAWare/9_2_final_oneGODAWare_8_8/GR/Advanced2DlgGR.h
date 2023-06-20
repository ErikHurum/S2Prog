#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CAdvanced2DlgGR

class CAdvanced2DlgGR : public COperationDlg
{
	DECLARE_DYNAMIC(CAdvanced2DlgGR)

public:
	CAdvanced2DlgGR();
	virtual ~CAdvanced2DlgGR();

	enum {IDD = IDD_ADVANCEDSETUP2_GR};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CEdit m_20mA;
	CEdit m_4mA;
	CEdit m_freq;
	CEdit m_diameter;
	CEdit m_tgc;
	CEdit m_echoAm;
	CEdit m_echoLimit;
	CEdit m_distOffset;
	CEdit m_velocityOffset;
	afx_msg void OnBnClickedButtonDistadj();
	afx_msg void OnBnClickedButtonVeloadj();
	afx_msg void OnBnClickedCheckEnabledia();
	CButton m_enableDia;
	afx_msg void OnStnClickedFrqzone4();
};
