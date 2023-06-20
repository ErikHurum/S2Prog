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

// ChildViewSU.cpp : CChildViewSU 类的实现
//

#include "stdafx.h"
#include "../MFC.h"
#include "ChildViewSU.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern bool load3Hights;
// CChildViewSU

CChildViewSU::CChildViewSU()
{
}

CChildViewSU::~CChildViewSU()
{
}


BEGIN_MESSAGE_MAP(CChildViewSU, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CChildViewSU 消息处理程序

BOOL CChildViewSU::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildViewSU::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}


int CChildViewSU::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	// 创建用于仪表操作的对话框
	m_wndLevelAdjustment.Create(IDD_LEVEL_ADJUSTMENT_SU, this);
	m_wndLevelAdjustment.SetBackgroundColor(RGB(255,255,255));

	m_wndApplication.Create(IDD_APPLICATION_SU,this);
	m_wndApplication.SetBackgroundColor(RGB(255,255,255));

	m_wndDamping.Create(IDD_DAMPING_SU,this);
	m_wndDamping.SetBackgroundColor(RGB(255,255,255));

	m_wndLinearization.Create(IDD_LINEARIZATION_SU, this);
	m_wndLinearization.SetBackgroundColor(RGB(255,255,255));

	m_wndOtherSettings.Create(IDD_OTHERSETTINGS_SU, this);
	m_wndOtherSettings.SetBackgroundColor(RGB(255,255,255));

	m_wndDisplay.Create(IDD_DISPLAY_SU, this);
	m_wndDisplay.SetBackgroundColor(RGB(255,255,255));

	m_wndDiagnosis.Create(IDD_DIAGNOSIS_SU, this);
	m_wndDiagnosis.SetBackgroundColor(RGB(255,255,255));

	m_wndCurrentOutput.Create(IDD_CURRENTOUTPUT_SU, this);
	m_wndCurrentOutput.SetBackgroundColor(RGB(255,255,255));

	m_wndReset.Create(IDD_RESET_SU, this);
	m_wndReset.SetBackgroundColor(RGB(255,255,255));

	m_wndFalseEcho.Create(IDD_FALSEECHO_SU, this);
	m_wndFalseEcho.SetBackgroundColor(RGB(255,255,255));

	m_wndPin.Create(IDD_PIN_SU, this);
	m_wndPin.SetBackgroundColor(RGB(255,255,255));

	m_wndServiceOther.Create(IDD_SERVICEOTHER_SU, this);
	m_wndServiceOther.SetBackgroundColor(RGB(255,255,255));

	m_wndAdvanced1.Create(IDD_ADVANCEDSETUP1_SU, this);
	m_wndAdvanced1.SetBackgroundColor(RGB(255,255,255));
	
	m_wndAdvanced2.Create(IDD_ADVANCEDSETUP2_SU, this);
	m_wndAdvanced2.SetBackgroundColor(RGB(255,255,255));

	m_wndInfo.Create(IDD_INFO, this);
	m_wndInfo.SetBackgroundColor(RGB(255,255,255));

	m_pCurrentDlg = &m_wndLevelAdjustment;
	Show(IDD_LEVEL_ADJUSTMENT_SU);

	load3Hights = true;
	return 0;
}

void CChildViewSU::Show( unsigned dlgId )
{
	ASSERT(m_pCurrentDlg != 0);
	m_pCurrentDlg->ShowWindow(SW_HIDE);

	switch(dlgId)
	{
	case IDD_LEVEL_ADJUSTMENT_SU:
		m_wndLevelAdjustment.ShowWindow(SW_SHOW);
		m_pCurrentDlg =  &m_wndLevelAdjustment;
		break;
	case IDD_APPLICATION_SU:
		m_wndApplication.ShowWindow(SW_SHOW);
		m_pCurrentDlg =  &m_wndApplication;
		break;
	case IDD_DAMPING_SU:
		m_wndDamping.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndDamping;
		break;
	case IDD_LINEARIZATION_SU:
		m_wndLinearization.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndLinearization;
		break;
	case IDD_OTHERSETTINGS_SU:
		m_wndOtherSettings.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndOtherSettings;
		break;
	case IDD_DISPLAY_SU:
		m_wndDisplay.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndDisplay;
		break;
	case IDD_DIAGNOSIS_SU:
		m_wndDiagnosis.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndDiagnosis;
		break;
	case IDD_CURRENTOUTPUT_SU:
		m_wndCurrentOutput.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndCurrentOutput;
		break;
	case IDD_RESET_SU:
		m_wndReset.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndReset;
		break;
	case IDD_FALSEECHO_SU:
		m_wndFalseEcho.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndFalseEcho;
		break;
	case IDD_PIN_SU:
		m_wndPin.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndPin;
		break;
	case IDD_SERVICEOTHER_SU:
		m_wndServiceOther.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndServiceOther;
		break;
	case IDD_ADVANCEDSETUP1_SU:
		m_wndAdvanced1.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndAdvanced1;
		break;
	case IDD_ADVANCEDSETUP2_SU:
		m_wndAdvanced2.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndAdvanced2;
		break;
	case IDD_INFO:
		m_wndInfo.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndInfo;

		break;

	default:
		m_pCurrentDlg->ShowWindow(SW_SHOW);
		break;
	}
}

void CChildViewSU::Load()
{
	m_pCurrentDlg->LoadData();
}

void CChildViewSU::Save()
{
	m_pCurrentDlg->SaveData();
}