#pragma once
#include "afxwin.h"
#include "../OperationDlg.h"

// CApplicationDlgSU

class CApplicationDlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(CApplicationDlgSU)

public:
	CApplicationDlgSU();
	virtual ~CApplicationDlgSU();

	enum { IDD = IDD_APPLICATION_SU};

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
	CComboBox m_additionalAdjust;
	afx_msg void OnCbnSelchangeComboMediatype();
	CComboBox m_comboPointNumber;
	afx_msg void OnCbnSelchangeComboPointnumber2();
	CButton m_multiEcho;
};


