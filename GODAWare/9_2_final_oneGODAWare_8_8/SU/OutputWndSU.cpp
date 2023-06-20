// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

#include "stdafx.h"

#include "OutputWndSU.h"
#include "../Resource.h"
#include "MainFrmSU.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWndSU::COutputWndSU()
{
}

COutputWndSU::~COutputWndSU()
{
}

BEGIN_MESSAGE_MAP(COutputWndSU, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int COutputWndSU::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Font.CreateStockObject(DEFAULT_GUI_FONT);

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建选项卡窗口:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_3D, rectDummy, this, 1, CMFCTabCtrl::LOCATION_TOP))
	{
		TRACE0("未能创建输出选项卡窗口\n");
		return -1;      // 未能创建
	}

	// 创建输出窗格:

	if (!m_wndEchoCurve.Create(IDD_ECHOCURVE_SU, &m_wndTabs) ||
		!m_wndEchoData.Create(IDD_ECHODATA_SU, &m_wndTabs) ||
		!m_wndSimulate.Create(IDD_SIMULATE_SU, &m_wndTabs)||
		!m_wndOutputMapping.Create(IDD_OUTPUTMAPPING_SU, &m_wndTabs) ||
		!m_wndTrend.Create(IDD_TREND_SU, &m_wndTabs))
	{
		TRACE0("未能创建输出窗口\n");
		return -1;      // 未能创建
	}

	m_wndEchoCurve.SetBackgroundColor(RGB(255,255,255));
	m_wndEchoData.SetBackgroundColor(RGB(255,255,255));
	m_wndOutputMapping.SetBackgroundColor(RGB(255,255,255));
	m_wndSimulate.SetBackgroundColor(RGB(255,255,255));
	m_wndTrend.SetBackgroundColor(RGB(255,255,255));

	CString strTabName;
	BOOL bNameValid;

	bNameValid = strTabName.LoadString(IDS_OUTPUT_ECHOCURVE);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndEchoCurve, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_OUTPUT_ECHODATA);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndEchoData, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_OUTPUT_OUTPUTMAPPING);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputMapping, strTabName, (UINT)2);
	bNameValid = strTabName.LoadString(IDS_OUTPUT_SIMULATE);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndSimulate, strTabName, (UINT)3);
	bNameValid = strTabName.LoadString(IDS_OUTPUT_TREND);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndTrend, strTabName, (UINT)4);

	return 0;
}

void COutputWndSU::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// 选项卡控件应覆盖整个工作区:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}


BOOL COutputWndSU::CanBeClosed() const
{
	return false;
}

