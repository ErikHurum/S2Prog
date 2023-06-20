#pragma once
#include "afxcmn.h"
#include "resource.h"
#include "splashdummy.h"

// CSplashWnd dialog

class CSplashWnd : public CDialog
{
	DECLARE_DYNAMIC(CSplashWnd)

public:
	CSplashWnd(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSplashWnd();

// Dialog Data
	enum { IDD = IDD_SPLASHWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
private:
	UINT m_nSec;
public:
	afx_msg void OnTimer(UINT nIDEvent);
private:
	CSplashDummy m_wndDummy;
protected:
public:
	void OnOK(void);
};
