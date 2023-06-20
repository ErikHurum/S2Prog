#pragma once
#include "DeviceStatDlgSU.h"

// CDeviceStatWndSU

class CDeviceStatWndSU : public CDockablePane
{
	DECLARE_DYNAMIC(CDeviceStatWndSU)

public:
	CDeviceStatWndSU();
	virtual ~CDeviceStatWndSU();

	void SetOnline(bool bOnline) {m_dlg.SetOnline(bOnline);}
	void SetNullHight(double hight, size_t index) {m_dlg.SetNullHight(hight, index);}

protected:
	BOOL CanBeClosed() const;

protected:
	DECLARE_MESSAGE_MAP()

public:
	CDeviceStatDlgSU m_dlg;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
};


