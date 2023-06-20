// Advanced2DlgPR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "Advanced2DlgPR.h"


// CAdvanced2DlgPR

IMPLEMENT_DYNAMIC(CAdvanced2DlgPR, COperationDlg)

CAdvanced2DlgPR::CAdvanced2DlgPR()
{

}

CAdvanced2DlgPR::~CAdvanced2DlgPR()
{
}


BEGIN_MESSAGE_MAP(CAdvanced2DlgPR, COperationDlg)
	ON_BN_CLICKED(IDC_BUTTON_DISTADJ, &CAdvanced2DlgPR::OnBnClickedButtonDistadj)
	ON_BN_CLICKED(IDC_BUTTON_VELOADJ, &CAdvanced2DlgPR::OnBnClickedButtonVeloadj)
	ON_BN_CLICKED(IDC_CHECK_ENABLEDIA, &CAdvanced2DlgPR::OnBnClickedCheckEnabledia)
END_MESSAGE_MAP()

void CAdvanced2DlgPR::LoadData()
{
	CProgress progress;
	CString str;
	UINT8 int8Data;
	INT16 int16Data;
	float floatData;

	theApp.m_pClient->LoadData(0x842, floatData);
	str.Format(_T("%.3f"), floatData);
	m_freq.SetWindowText(str);

	theApp.m_pClient->LoadData(0x825, int8Data);
	str.Format(_T("%d"), int8Data);
	m_echoAm.SetWindowText(str);

	theApp.m_pClient->LoadData(0x826, floatData);
	str.Format(_T("%.3f"), floatData);
	m_tgc.SetWindowText(str);

	theApp.m_pClient->LoadData(0x652, floatData);
	str.Format(_T("%.3f"), floatData);
	m_distOffset.SetWindowText(str);

	theApp.m_pClient->LoadData(0x653, floatData);
	str.Format(_T("%.3f"), floatData);
	m_velocityOffset.SetWindowText(str);

	theApp.m_pClient->LoadData(0x215, floatData);
	str.Format(_T("%.3f"), floatData);
	m_20mA.SetWindowText(str);

	theApp.m_pClient->LoadData(0x214, floatData);
	str.Format(_T("%.3f"), floatData);
	m_4mA.SetWindowText(str);

	theApp.m_pClient->LoadData(0x551, int8Data);
	str.Format(_T("%d"), int8Data);
	m_echoLimit.SetWindowText(str);

	theApp.m_pClient->LoadData(0x510, int16Data);
	str.Format(_T("%d"), int16Data);
	m_diameter.SetWindowText(str);


}

void CAdvanced2DlgPR::SaveData()
{
	CString str;
	int intData;
	double dbData;

	CProgress progress;

	m_freq.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x842, float(dbData));


	m_echoAm.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x825, UINT8(intData));


	m_tgc.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x826, float(dbData));

	m_distOffset.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x652, float(dbData));

	m_velocityOffset.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x653, float(dbData));

	m_20mA.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x215, float(dbData));

	m_4mA.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x214, float(dbData));

	m_echoLimit.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x551, UINT8(intData));

	m_diameter.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x510, INT16(intData));
}

// CAdvanced2DlgPR 消息处理程序



void CAdvanced2DlgPR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_20MA, m_20mA);
	DDX_Control(pDX, IDC_EDIT_4MA, m_4mA);
	DDX_Control(pDX, IDC_EDIT_FREQ, m_freq);
	DDX_Control(pDX, IDC_EDIT_PIPEDIAMETER, m_diameter);
	DDX_Control(pDX, IDC_EDIT_TGC, m_tgc);
	DDX_Control(pDX, IDC_EDIT_ECHOAM, m_echoAm);
	DDX_Control(pDX, IDC_EDIT_ECHOLIMIT, m_echoLimit);
	DDX_Control(pDX, IDC_EDIT_DISTOFFSET, m_distOffset);
	DDX_Control(pDX, IDC_EDIT_VELOCITYOFFSET, m_velocityOffset);
	DDX_Control(pDX, IDC_CHECK_ENABLEDIA, m_enableDia);
}

void CAdvanced2DlgPR::OnBnClickedButtonDistadj()
{
	// TODO: 在此添加控件通知处理程序代码

	double dbData = 0;
	if (GetNumMessageBox(IDS_MSG_INPUTNULLHIGHT, dbData) != IDOK)
	{
		return;
	}

	CProgress progress;
	theApp.m_pClient->SaveData(0x650, float(dbData));

	Sleep(1000);
		
	float distOffset;
	theApp.m_pClient->LoadData(0x652, distOffset);
	CString str;
	str.Format(_T("%.3f"), distOffset);
	m_distOffset.SetWindowText(str);
}

void CAdvanced2DlgPR::OnBnClickedButtonVeloadj()
{
	double dbData = 0;
	if (GetNumMessageBox(IDS_MSG_INPUTNULLHIGHT, dbData) != IDOK)
	{
		return;
	}

	CProgress progress;
	theApp.m_pClient->SaveData(0x651, float(dbData));

	Sleep(1000);

	float veloOffset;
	theApp.m_pClient->LoadData(0x653, veloOffset);
	CString str;
	str.Format(_T("%.3f"), veloOffset);
	m_velocityOffset.SetWindowText(str);
}

void CAdvanced2DlgPR::OnBnClickedCheckEnabledia()
{
	m_diameter.SetReadOnly(!m_enableDia.GetCheck());
}
