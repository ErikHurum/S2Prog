o// DeviceStatWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "DeviceStatWnd.h"


// CDeviceStatWnd

IMPLEMENT_DYNAMIC(CDeviceStatWnd, CDockablePane)

CDeviceStatWnd::CDeviceStatWnd()
{

}

CDeviceStatWnd::~CDeviceStatWnd()
{
}


BEGIN_MESSAGE_MAP(CDeviceStatWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CDeviceStatWnd::CanBeClosed() const
{
	return FALSE;
}


// CDeviceStatWnd 消息处理程序



int CDeviceStatWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_dlg.Create(IDD_DEVICESTAT, this);
	m_dlg.SetBackgroundColor(RGB(255,255,255));
	m_dlg.ShowWindow(SW_SHOW);

	return 0;
}

void CDeviceStatWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_dlg.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CDeviceStatWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	m_dlg.RedrawWindow();
	// 不为绘图消息调用 CDockablePane::OnPaint()
}
