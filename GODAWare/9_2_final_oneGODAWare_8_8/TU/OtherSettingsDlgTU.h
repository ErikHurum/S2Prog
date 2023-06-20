#pragma once

#include "../OperationDlg.h"
#include "afxwin.h"
// COtherSettingsDlgTU

class COtherSettingsDlgTU : public COperationDlg
{
	DECLARE_DYNAMIC(COtherSettingsDlgTU)

public:
	COtherSettingsDlgTU();
	virtual ~COtherSettingsDlgTU();

	enum {IDD = IDD_OTHERSETTINGS_TU};

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


