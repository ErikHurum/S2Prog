#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CPvcsLodingDialog dialog

class CPvcsLodingDialog : public CDialog
{
	DECLARE_DYNAMIC(CPvcsLodingDialog)

public:
	CPvcsLodingDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPvcsLodingDialog();

// Dialog Data
	enum { IDD = IDD_LODING_PVCS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
public:
	CStatic m_strScreenHandle;
	CStatic m_strLoading;
	CProgressCtrl m_PVCSProgressCtrl;
	void ShowClosingWindow(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
