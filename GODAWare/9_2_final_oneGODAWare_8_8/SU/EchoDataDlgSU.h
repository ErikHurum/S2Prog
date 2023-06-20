#pragma once
#include "../resource.h"
#include "afxcmn.h"
#include "afxwin.h"

// CEchoDataDlgSU

class CEchoDataDlgSU : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CEchoDataDlgSU)

public:
	CEchoDataDlgSU();
	virtual ~CEchoDataDlgSU();

	enum{IDD = IDD_ECHODATA_SU};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CListCtrl m_echoData;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnLoad();
	CComboBox m_comboPointNumber;
};

