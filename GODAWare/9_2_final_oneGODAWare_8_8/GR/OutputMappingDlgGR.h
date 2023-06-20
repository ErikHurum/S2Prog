#pragma once
#include "../resource.h"
#include "afxcmn.h"
#include "../OperationDlg.h"
// COutputMappingDlgGR

class COutputMappingDlgGR : public CCustomDialogEx
{
	DECLARE_DYNAMIC(COutputMappingDlgGR)

public:
	COutputMappingDlgGR();
	virtual ~COutputMappingDlgGR();

	enum {IDD = IDD_OUTPUTMAPPING_GR};

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListCtrl m_mapping;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnLoad();
};
