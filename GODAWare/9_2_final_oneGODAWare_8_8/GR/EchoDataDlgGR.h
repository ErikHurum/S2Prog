#pragma once
#include "../resource.h"
#include "afxcmn.h"

// CEchoDataDlgGR

class CEchoDataDlgGR : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CEchoDataDlgGR)

public:
	CEchoDataDlgGR();
	virtual ~CEchoDataDlgGR();

	enum{IDD = IDD_ECHODATA_GR};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CListCtrl m_echoData;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnLoad();
};


