#pragma once
#include "afxwin.h"
#include "../OperationDlg.h"

// CApplicationDlgTU

class CApplicationDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(CApplicationDlgTU)

public:
	CApplicationDlgTU();
	virtual ~CApplicationDlgTU();

	enum { IDD = IDD_APPLICATION_TU};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);

	void LoadData();
	void SaveData();

public:
	CComboBox m_mediaType;
	CButton m_foam;
	CButton m_agitatedSurface;
	CButton m_powder;
	CButton m_largeAngle;
	CComboBox m_additionalAdjust;
	afx_msg void OnCbnSelchangeComboMediatype();
	int m_nMultiEcho;
	CButton m_checkMultiEcho;
};


