#pragma once

#include "../OperationDlg.h"
#include "afxwin.h"
// COtherSettingsDlgSU

class COtherSettingsDlgSU : public COperationDlg
{
	DECLARE_DYNAMIC(COtherSettingsDlgSU)

public:
	COtherSettingsDlgSU();
	virtual ~COtherSettingsDlgSU();

	enum {IDD = IDD_OTHERSETTINGS_SU};

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
	CComboBox m_comboPointNumber;
	afx_msg void OnCbnSelchangeComboPointnumber();
	CEdit m_editChangeDistrict;
	CEdit m_editBlendArea;
	CEdit m_editEchoRange;
	CEdit m_editTGC1;
};


