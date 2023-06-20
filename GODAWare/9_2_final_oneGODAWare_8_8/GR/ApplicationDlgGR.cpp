// ApplicationDlgGR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "ApplicationDlgGR.h"


// CApplicationDlgGR

IMPLEMENT_DYNAMIC(CApplicationDlgGR, COperationDlg)

CApplicationDlgGR::CApplicationDlgGR()
: m_nMultiEcho(0)
{

}

CApplicationDlgGR::~CApplicationDlgGR()
{
}


BEGIN_MESSAGE_MAP(CApplicationDlgGR, COperationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_MEDIATYPE, &CApplicationDlgGR::OnCbnSelchangeComboMediatype)
	ON_BN_CLICKED(IDC_CHECK_LOWDK, &CApplicationDlgGR::OnBnClickedCheckLowdk)
END_MESSAGE_MAP()



// CApplicationDlgGR 消息处理程序



void CApplicationDlgGR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MEDIATYPE, m_mediaType);
	DDX_Control(pDX, IDC_CHECK_FOAM, m_foam);
	DDX_Control(pDX, IDC_CHECK_AGITATEDSURFACE, m_agitatedSurface);
	DDX_Control(pDX, IDC_CHECK_POWDER, m_powder);
	DDX_Control(pDX, IDC_CHECK_LARGEANGLE, m_largeAngle);
	DDX_Control(pDX, IDC_CHECK_LOWDK, m_lowDK);
	DDX_Control(pDX, IDC_EDIT_NULLHIGHT, m_nullHight);
	DDX_Control(pDX, IDC_EDIT_DKVALUE, m_dkValue);
	DDX_Control(pDX, IDC_COMBO_ADDITIONALADJUST, m_additionalAdjust);
	DDX_Radio(pDX, IDC_RADIO1, m_nMultiEcho);
}

void CApplicationDlgGR::LoadData()
{
	CProgress progress;
	CString str;
	UINT8 int8Data;
	float floatData;

	theApp.m_pClient->LoadData(0x2, int8Data);
	if (int8Data == 1 || int8Data == 2 || int8Data == 3)
	{
		m_mediaType.SetCurSel(int8Data - 1);
	}
	else
	{
		m_mediaType.SetCurSel(0);
	}
	OnCbnSelchangeComboMediatype();

	theApp.m_pClient->LoadData(0x502, int8Data);
	m_foam.SetCheck(int8Data);

	theApp.m_pClient->LoadData(0x501, int8Data);
	m_agitatedSurface.SetCheck(int8Data);

	theApp.m_pClient->LoadData(0x505, int8Data);
	//m_mutiEcho.SetCheck(int8Data);
	if (int8Data == 0)
	{
		m_nMultiEcho = 1;
	}
	else if (int8Data == 1)
	{
		m_nMultiEcho = 0;
	}
	else
	{
		m_nMultiEcho = int8Data;
	}
	UpdateData(FALSE);

	theApp.m_pClient->LoadData(0x506, int8Data);
	m_powder.SetCheck(int8Data);

	theApp.m_pClient->LoadData(0x507, int8Data);
	m_largeAngle.SetCheck(int8Data);

	theApp.m_pClient->LoadData(0x503, int8Data);
	m_lowDK.SetCheck(int8Data);
	OnBnClickedCheckLowdk();

	theApp.m_pClient->LoadData(0x101, floatData);
	str.Format(_T("%.3f"), floatData);
	m_nullHight.SetWindowText(str);

	theApp.m_pClient->LoadData(0x102, floatData);
	str.Format(_T("%.3f"), floatData);
	m_dkValue.SetWindowText(str);

	theApp.m_pClient->LoadData(0x500, int8Data);
	m_additionalAdjust.SetCurSel(int8Data);
}

void CApplicationDlgGR::SaveData()
{
	CProgress progress;
	CString str;
	int intData;
	double dbData;

	intData = m_mediaType.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x2, UINT8(intData));

	intData = m_foam.GetCheck();
	theApp.m_pClient->SaveData(0x502, UINT8(intData));

	intData = m_agitatedSurface.GetCheck();
	theApp.m_pClient->SaveData(0x501, UINT8(intData));

	UpdateData(TRUE);
	//intData = m_mutiEcho.GetCheck();
	if (m_nMultiEcho == 0)
	{
		intData = 1;
	} 
	else if (m_nMultiEcho == 1)
	{
		intData = 0;
	}
	else 
	{
		intData = m_nMultiEcho;
	}
	
	theApp.m_pClient->SaveData(0x505, UINT8(intData));

	intData = m_powder.GetCheck();
	theApp.m_pClient->SaveData(0x506, UINT8(intData));

	intData = m_largeAngle.GetCheck();
	theApp.m_pClient->SaveData(0x507, UINT8(intData));

	intData = m_lowDK.GetCheck();
	theApp.m_pClient->SaveData(0x503, UINT8(intData));

	m_nullHight.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x101, float(dbData));

	m_dkValue.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x102, float(dbData));

	intData = m_additionalAdjust.GetCurSel();
	theApp.m_pClient->SaveData(0x500, UINT8(intData));
}
void CApplicationDlgGR::OnCbnSelchangeComboMediatype()
{
	switch(m_mediaType.GetCurSel())
	{
	case 0: // 液体
		m_foam.EnableWindow(true);
		m_agitatedSurface.EnableWindow(true);
		//m_mutiEcho.EnableWindow(true);
		m_powder.EnableWindow(false);
		m_largeAngle.EnableWindow(false);
		m_lowDK.EnableWindow(true);
		OnBnClickedCheckLowdk();
		break;

	case 1: // 固体
		m_foam.EnableWindow(false);
		m_agitatedSurface.EnableWindow(false);
		//m_mutiEcho.EnableWindow(true);
		m_powder.EnableWindow(true);
		m_largeAngle.EnableWindow(true);
		m_lowDK.EnableWindow(true);
		OnBnClickedCheckLowdk();

		break;

	case 2:	// 微DK
		m_foam.EnableWindow(false);
		m_agitatedSurface.EnableWindow(false);
		//m_mutiEcho.EnableWindow(false);
		m_powder.EnableWindow(false);
		m_largeAngle.EnableWindow(false);
		m_lowDK.EnableWindow(false);
		m_nullHight.SetReadOnly(false);
		m_dkValue.SetReadOnly(false);

		break; 
	}
}

void CApplicationDlgGR::OnBnClickedCheckLowdk()
{
	if (m_lowDK.GetCheck())
	{
		m_nullHight.SetReadOnly(false);
		m_dkValue.SetReadOnly(false);
	} 
	else
	{
		m_nullHight.SetReadOnly(true);
		m_dkValue.SetReadOnly(true);
	}
}
