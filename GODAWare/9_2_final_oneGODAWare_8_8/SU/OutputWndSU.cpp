// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

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

	// ����ѡ�����:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_3D, rectDummy, this, 1, CMFCTabCtrl::LOCATION_TOP))
	{
		TRACE0("δ�ܴ������ѡ�����\n");
		return -1;      // δ�ܴ���
	}

	// �����������:

	if (!m_wndEchoCurve.Create(IDD_ECHOCURVE_SU, &m_wndTabs) ||
		!m_wndEchoData.Create(IDD_ECHODATA_SU, &m_wndTabs) ||
		!m_wndSimulate.Create(IDD_SIMULATE_SU, &m_wndTabs)||
		!m_wndOutputMapping.Create(IDD_OUTPUTMAPPING_SU, &m_wndTabs) ||
		!m_wndTrend.Create(IDD_TREND_SU, &m_wndTabs))
	{
		TRACE0("δ�ܴ����������\n");
		return -1;      // δ�ܴ���
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

	// ѡ��ؼ�Ӧ��������������:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}


BOOL COutputWndSU::CanBeClosed() const
{
	return false;
}

