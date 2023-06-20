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

// ChildViewTU.cpp : CChildViewTU ���ʵ��
//

#include "stdafx.h"
#include "../MFC.h"
#include "ChildViewTU.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildViewTU

CChildViewTU::CChildViewTU()
{
}

CChildViewTU::~CChildViewTU()
{
}


BEGIN_MESSAGE_MAP(CChildViewTU, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CChildViewTU ��Ϣ�������

BOOL CChildViewTU::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildViewTU::OnPaint() 
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	
	// TODO: �ڴ˴������Ϣ����������
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}


int CChildViewTU::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	// ���������Ǳ�����ĶԻ���
	m_wndLevelAdjustment.Create(IDD_LEVEL_ADJUSTMENT_TU, this);
	m_wndLevelAdjustment.SetBackgroundColor(RGB(255,255,255));

	m_wndApplication.Create(IDD_APPLICATION_TU,this);
	m_wndApplication.SetBackgroundColor(RGB(255,255,255));

	m_wndDamping.Create(IDD_DAMPING_TU,this);
	m_wndDamping.SetBackgroundColor(RGB(255,255,255));

	m_wndLinearization.Create(IDD_LINEARIZATION_TU, this);
	m_wndLinearization.SetBackgroundColor(RGB(255,255,255));

	m_wndOtherSettings.Create(IDD_OTHERSETTINGS_TU, this);
	m_wndOtherSettings.SetBackgroundColor(RGB(255,255,255));

	m_wndDisplay.Create(IDD_DISPLAY_TU, this);
	m_wndDisplay.SetBackgroundColor(RGB(255,255,255));

	m_wndDiagnosis.Create(IDD_DIAGNOSIS_TU, this);
	m_wndDiagnosis.SetBackgroundColor(RGB(255,255,255));

	m_wndCurrentOutput.Create(IDD_CURRENTOUTPUT_TU, this);
	m_wndCurrentOutput.SetBackgroundColor(RGB(255,255,255));

	m_wndReset.Create(IDD_RESET_TU, this);
	m_wndReset.SetBackgroundColor(RGB(255,255,255));

	m_wndFalseEcho.Create(IDD_FALSEECHO_TU, this);
	m_wndFalseEcho.SetBackgroundColor(RGB(255,255,255));

	m_wndPin.Create(IDD_PIN_TU, this);
	m_wndPin.SetBackgroundColor(RGB(255,255,255));

	m_wndServiceOther.Create(IDD_SERVICEOTHER_TU, this);
	m_wndServiceOther.SetBackgroundColor(RGB(255,255,255));

	m_wndAdvanced1.Create(IDD_ADVANCEDSETUP1_TU, this);
	m_wndAdvanced1.SetBackgroundColor(RGB(255,255,255));
	
	m_wndAdvanced2.Create(IDD_ADVANCEDSETUP2_TU, this);
	m_wndAdvanced2.SetBackgroundColor(RGB(255,255,255));

	m_wndInfo.Create(IDD_INFO, this);
	m_wndInfo.SetBackgroundColor(RGB(255,255,255));

	m_pCurrentDlg = &m_wndLevelAdjustment;
	Show(IDD_LEVEL_ADJUSTMENT_TU);

	return 0;
}

void CChildViewTU::Show( unsigned dlgId )
{
	ASSERT(m_pCurrentDlg != 0);
	m_pCurrentDlg->ShowWindow(SW_HIDE);

	switch(dlgId)
	{
	case IDD_LEVEL_ADJUSTMENT_TU:
		m_wndLevelAdjustment.ShowWindow(SW_SHOW);
		m_pCurrentDlg =  &m_wndLevelAdjustment;
		break;
	case IDD_APPLICATION_TU:
		m_wndApplication.ShowWindow(SW_SHOW);
		m_pCurrentDlg =  &m_wndApplication;
		break;
	case IDD_DAMPING_TU:
		m_wndDamping.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndDamping;
		break;
	case IDD_LINEARIZATION_TU:
		m_wndLinearization.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndLinearization;
		break;
	case IDD_OTHERSETTINGS_TU:
		m_wndOtherSettings.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndOtherSettings;
		break;
	case IDD_DISPLAY_TU:
		m_wndDisplay.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndDisplay;
		break;
	case IDD_DIAGNOSIS_TU:
		m_wndDiagnosis.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndDiagnosis;
		break;
	case IDD_CURRENTOUTPUT_TU:
		m_wndCurrentOutput.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndCurrentOutput;
		break;
	case IDD_RESET_TU:
		m_wndReset.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndReset;
		break;
	case IDD_FALSEECHO_TU:
		m_wndFalseEcho.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndFalseEcho;
		break;
	case IDD_PIN_TU:
		m_wndPin.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndPin;
		break;
	case IDD_SERVICEOTHER_TU:
		m_wndServiceOther.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndServiceOther;
		break;
	case IDD_ADVANCEDSETUP1_TU:
		m_wndAdvanced1.ShowWindow(SW_SHOW);
		m_pCurrentDlg = &m_wndAdvanced1;
		break;
	case IDD_ADVANCEDSETUP2_TU:
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

void CChildViewTU::Load()
{
	m_pCurrentDlg->LoadData();
}

void CChildViewTU::Save()
{
	m_pCurrentDlg->SaveData();
}