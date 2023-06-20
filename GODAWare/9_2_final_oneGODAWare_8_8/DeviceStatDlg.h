#pragma once
#include "afxwin.h"


// CDeviceStatDlg

class CDeviceStatDlg : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CDeviceStatDlg)

public:
	CDeviceStatDlg();
	virtual ~CDeviceStatDlg();

	void SetOnline(bool bOnline);
	void SetNullHight(double hight);

	enum {IDD = IDD_DEVICESTAT};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CStatic m_stat;
	CStatic m_hight;
	virtual BOOL OnInitDialog();
private:
	bool m_bOnline;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


