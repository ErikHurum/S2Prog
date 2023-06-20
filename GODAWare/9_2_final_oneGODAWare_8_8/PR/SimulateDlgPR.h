#pragma once
#include "../resource.h"
#include "afxwin.h"

// CSimulateDlgPR

class CSimulateDlgPR : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CSimulateDlgPR)

public:
	CSimulateDlgPR();
	virtual ~CSimulateDlgPR();

	enum {IDD = IDD_SIMULATE_PR};

protected:


	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);

	bool m_bSim;


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
};


