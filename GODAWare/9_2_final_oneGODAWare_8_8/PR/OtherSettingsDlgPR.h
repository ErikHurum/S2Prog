#pragma once

#include "../OperationDlg.h"
#include "afxwin.h"
// COtherSettingsDlgPR

class COtherSettingsDlgPR : public COperationDlg
{
	DECLARE_DYNAMIC(COtherSettingsDlgPR)

public:
	COtherSettingsDlgPR();
	virtual ~COtherSettingsDlgPR();

	enum {IDD = IDD_OTHERSETTINGS_PR};

	void LoadData();
	void SaveData();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	afx_msg void OnCbnSelchangeCombo1();
	CEdit m_senserTag;
	CComboBox m_senserType;
	CEdit m_editAddress;
};


