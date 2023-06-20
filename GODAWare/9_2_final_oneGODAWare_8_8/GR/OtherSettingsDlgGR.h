#pragma once

#include "../OperationDlg.h"
#include "afxwin.h"
// COtherSettingsDlgGR

class COtherSettingsDlgGR : public COperationDlg
{
	DECLARE_DYNAMIC(COtherSettingsDlgGR)

public:
	COtherSettingsDlgGR();
	virtual ~COtherSettingsDlgGR();

	enum {IDD = IDD_OTHERSETTINGS_GR};

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


