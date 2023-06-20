#pragma once
#include "afxwin.h"


// CDeviceStatDlgSU

class CDeviceStatDlgSU : public CCustomDialogEx
{
	DECLARE_DYNAMIC(CDeviceStatDlgSU)

public:
	CDeviceStatDlgSU();
	virtual ~CDeviceStatDlgSU();

	void SetOnline(bool bOnline);
	void SetNullHight(double hight, size_t index);

	enum {IDD = IDD_DEVICESTAT_3};

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	CStatic m_stat;
	CStatic m_hight[3];
	virtual BOOL OnInitDialog();
private:
	bool m_bOnline;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


