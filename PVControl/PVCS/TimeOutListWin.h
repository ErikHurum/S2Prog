#pragma once
#include "afxcmn.h"


// CTimeOutListWin dialog

class CTimeOutListWin : public CDialog
{
	DECLARE_DYNAMIC(CTimeOutListWin)

public:
	CTimeOutListWin(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTimeOutListWin();
	BOOL OnInitDialog();
	void BuildList();

// Dialog Data
	enum { IDD = IDD_Time_out_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_TimeoutList;	
	afx_msg void OnBnClickedButton1();	
	static bool WarningTimeoutStatus;
	void CreateTimeoutListWindow(void);
	void SetVectorUpdated(bool State);

private:
	bool m_bIsVectorUpdated;
};
CTimeOutListWin& theCTimeOut();