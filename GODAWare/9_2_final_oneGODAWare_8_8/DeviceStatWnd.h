#pragma once
#include "DeviceStatDlg.h"

// CDeviceStatWnd

class CDeviceStatWnd : public CDockablePane
{
	DECLARE_DYNAMIC(CDeviceStatWnd)

public:
	CDeviceStatWnd();
	virtual ~CDeviceStatWnd();

	void SetOnline(bool bOnline) {m_dlg.SetOnline(bOnline);}
	void SetNullHight(double hight) {m_dlg.SetNullHight(hight);}

protected:
	BOOL CanBeClosed() const;

protected:
	DECLARE_MESSAGE_MAP()

public:
	CDeviceStatDlg m_dlg;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
};


