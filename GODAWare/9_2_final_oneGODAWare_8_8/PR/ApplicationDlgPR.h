#pragma once
#include "afxwin.h"
#include "../OperationDlg.h"

// CApplicationDlgPR

class CApplicationDlgPR : public COperationDlg
{
	DECLARE_DYNAMIC(CApplicationDlgPR)

public:
	CApplicationDlgPR();
	virtual ~CApplicationDlgPR();

	enum { IDD = IDD_APPLICATION_PR};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);

	void LoadData();
	void SaveData();

public:
	CComboBox m_mediaType;
	CButton m_foam;
	CButton m_agitatedSurface;
	//CButton m_mutiEcho;
	CButton m_powder;
	CButton m_largeAngle;
	CButton m_lowDK;
	CEdit m_nullHight;
	CEdit m_dkValue;
	CComboBox m_additionalAdjust;
	afx_msg void OnCbnSelchangeComboMediatype();
	int m_nMultiEcho;
	afx_msg void OnBnClickedCheckLowdk();
};


