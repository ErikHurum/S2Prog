#pragma once
#include "../resource.h"
#include "afxcmn.h"

// CEchoDataDlgTU

class CEchoDataDlgTU : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CEchoDataDlgTU)

public:
	CEchoDataDlgTU();
	virtual ~CEchoDataDlgTU();

	enum{IDD = IDD_ECHODATA_TU};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CListCtrl m_echoData;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnLoad();
};


