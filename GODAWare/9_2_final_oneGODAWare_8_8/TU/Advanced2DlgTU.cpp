// Advanced2DlgTU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "Advanced2DlgTU.h"


// CAdvanced2DlgTU

IMPLEMENT_DYNAMIC(CAdvanced2DlgTU, COperationDlg)

CAdvanced2DlgTU::CAdvanced2DlgTU()
{

}

CAdvanced2DlgTU::~CAdvanced2DlgTU()
{
}


BEGIN_MESSAGE_MAP(CAdvanced2DlgTU, COperationDlg)
	ON_BN_CLICKED(IDC_BUTTON_DISTADJ, &CAdvanced2DlgTU::OnBnClickedButtonDistadj)
	ON_BN_CLICKED(IDC_BUTTON_VELOADJ, &CAdvanced2DlgTU::OnBnClickedButtonVeloadj)
END_MESSAGE_MAP()

void CAdvanced2DlgTU::LoadData()
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

	theApp.m_pClient->LoadData(0x844, int16Data);
	str.Format(_T("%d"), int16Data);
	m_editShortWidth.SetWindowText(str);

	theApp.m_pClient->LoadData(0x845, int16Data);
	str.Format(_T("%d"), int16Data);
	m_editLongWidth.SetWindowText(str);

	theApp.m_pClient->LoadData(0x846, floatData);
	str.Format(_T("%.3f"), floatData);
	m_editFreqMin.SetWindowText(str);

	theApp.m_pClient->LoadData(0x847, floatData);
	str.Format(_T("%.3f"), floatData);
	m_editFreqMax.SetWindowText(str);

	theApp.m_pClient->LoadData(0x654, floatData);
	str.Format(_T("%.3f"), floatData);
	m_editTempOffset.SetWindowText(str);



}

void CAdvanced2DlgTU::SaveData()
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

	m_editTempOffset.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x654, float(dbData));

	m_20mA.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x215, float(dbData));

	m_4mA.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x214, float(dbData));

	m_echoLimit.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x551, UINT8(intData));

	m_editShortWidth.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x844, INT16(intData));

	m_editLongWidth.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x845, INT16(intData));
}

// CAdvanced2DlgTU 消息处理程序



void CAdvanced2DlgTU::DoDataExchange(CDataExchange* pDX)
{
	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_20MA, m_20mA);
	DDX_Control(pDX, IDC_EDIT_4MA, m_4mA);
	DDX_Control(pDX, IDC_EDIT_FREQ, m_freq);
	DDX_Control(pDX, IDC_EDIT_TGC, m_tgc);
	DDX_Control(pDX, IDC_EDIT_ECHOAM, m_echoAm);
	DDX_Control(pDX, IDC_EDIT_ECHOLIMIT, m_echoLimit);
	DDX_Control(pDX, IDC_EDIT_DISTOFFSET, m_distOffset);
	DDX_Control(pDX, IDC_EDIT_VELOCITYOFFSET, m_velocityOffset);
	DDX_Control(pDX, IDC_EDIT_SHORTWITDH, m_editShortWidth);
	DDX_Control(pDX, IDC_EDIT_LONGWIDTH, m_editLongWidth);
	DDX_Control(pDX, IDC_EDIT_FREQMIN, m_editFreqMin);
	DDX_Control(pDX, IDC_EDIT_FREQMAX, m_editFreqMax);
	DDX_Control(pDX, IDC_EDIT_TEMPFFFSET, m_editTempOffset);
}

void CAdvanced2DlgTU::OnBnClickedButtonDistadj()
{


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

void CAdvanced2DlgTU::OnBnClickedButtonVeloadj()
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

