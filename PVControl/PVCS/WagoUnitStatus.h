#pragma once
#include "afxcmn.h"


// CWagoUnitStatus dialog

class CWagoUnitStatus : public CDialog
{
	DECLARE_DYNAMIC(CWagoUnitStatus)

public:
	CWagoUnitStatus(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWagoUnitStatus();
	afx_msg virtual BOOL OnInitDialog();
   // Dialog Data
	enum { IDD = IDD_WagoUnitStatus };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
	CListCtrl m_WagoUnitStatusList;

private:
	void BuildGrid(void);
	void FillGrid(void);
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedWagounitstatusok();
	afx_msg void OnLvnItemchangedWagounitstatuslist(NMHDR *pNMHDR, LRESULT *pResult);
};
