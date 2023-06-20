#pragma once
#include "../OperationDlg.h"
#include "afxwin.h"

// CAdvanced2DlgTU

class CAdvanced2DlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CAdvanced2DlgTU)

public:
	CAdvanced2DlgTU();
	virtual ~CAdvanced2DlgTU();

	enum {IDD = IDD_ADVANCEDSETUP2_TU};

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
};
