#pragma once
#include "../resource.h"
#include "afxcmn.h"

// CEchoDataDlgPR

class CEchoDataDlgPR : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CEchoDataDlgPR)

public:
	CEchoDataDlgPR();
	virtual ~CEchoDataDlgPR();

	enum{IDD = IDD_ECHODATA_PR};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CListCtrl m_echoData;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnLoad();
};


