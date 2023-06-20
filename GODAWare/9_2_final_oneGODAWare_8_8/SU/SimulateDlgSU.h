#pragma once
#include "../resource.h"
#include "afxwin.h"

// CSimulateDlgSU

class CSimulateDlgSU : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CSimulateDlgSU)

public:
	CSimulateDlgSU();
	virtual ~CSimulateDlgSU();

	enum {IDD = IDD_SIMULATE_SU};

protected:


	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);

	bool m_bSim;
	bool m_bTest;
	bool m_bClose;
	int m_relayNum;

public:
	CButton m_btnSimulate;
	afx_msg void OnBnClickedBtnSimulate();
	CComboBox m_comboSimuType;
	CEdit m_editSimuValue;
	CStatic m_editUnit;
	afx_msg void OnCbnSelchangeComboSimutype();
	afx_msg void OnBnClickedBtnSave();
	virtual BOOL OnInitDialog();
	CButton m_btnSave;
	CButton m_btnStartRelayTest;
	CComboBox m_comboRelay;
	CButton m_btnTest;
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedBtnStartRelayTest();
	afx_msg void OnCbnSelchangeComboRelay();
	bool TestRelay(bool close, int num);
	CComboBox m_comboPointNumber;
};


