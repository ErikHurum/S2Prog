// Advanced2DlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "Advanced2DlgSU.h"


// CAdvanced2DlgSU

IMPLEMENT_DYNAMIC(CAdvanced2DlgSU, COperationDlg)

CAdvanced2DlgSU::CAdvanced2DlgSU()
{

}

CAdvanced2DlgSU::~CAdvanced2DlgSU()
{
}


BEGIN_MESSAGE_MAP(CAdvanced2DlgSU, COperationDlg)
	ON_BN_CLICKED(IDC_BUTTON_DISTADJ, &CAdvanced2DlgSU::OnBnClickedButtonDistadj)
	ON_BN_CLICKED(IDC_BUTTON_VELOADJ, &CAdvanced2DlgSU::OnBnClickedButtonVeloadj)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &CAdvanced2DlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()

void CAdvanced2DlgSU::LoadData()
{
	CProgress progress;


	int pn = m_comboPointNumber.GetCurSel();

	CString str;
	UINT8 int8Data;
	INT16 int16Data;
	float floatData;

	theApp.m_pClient->LoadData(0x842, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_freq.SetWindowText(str);

	theApp.m_pClient->LoadData(0x825, int8Data, pn);
	str.Format(_T("%d"), int8Data);
	m_echoAm.SetWindowText(str);

	theApp.m_pClient->LoadData(0x826, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_tgc.SetWindowText(str);

	theApp.m_pClient->LoadData(0x652, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_distOffset.SetWindowText(str);

	theApp.m_pClient->LoadData(0x653, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_velocityOffset.SetWindowText(str);

	theApp.m_pClient->LoadData(0x215, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_20mA.SetWindowText(str);

	theApp.m_pClient->LoadData(0x214, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_4mA.SetWindowText(str);

	theApp.m_pClient->LoadData(0x551, int8Data, pn);
	str.Format(_T("%d"), int8Data);
	m_echoLimit.SetWindowText(str);

	theApp.m_pClient->LoadData(0x844, int16Data, pn);
	str.Format(_T("%d"), int16Data);
	m_editShortWidth.SetWindowText(str);

	theApp.m_pClient->LoadData(0x845, int16Data, pn);
	str.Format(_T("%d"), int16Data);
	m_editLongWidth.SetWindowText(str);

	theApp.m_pClient->LoadData(0x846, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_editFreqMin.SetWindowText(str);

	theApp.m_pClient->LoadData(0x847, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_editFreqMax.SetWindowText(str);

	theApp.m_pClient->LoadData(0x654, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_editTempOffset.SetWindowText(str);

	theApp.m_pClient->LoadData(0x553, int8Data, pn);
	str.Format(_T("%d"), int8Data);
	m_noiselimit.SetWindowText(str);


}

void CAdvanced2DlgSU::SaveData()
{
	CProgress progress;


	int pn = m_comboPointNumber.GetCurSel();

	CString str;
	int intData;
	double dbData;

	m_freq.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x842, float(dbData), pn);


	m_echoAm.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x825, UINT8(intData), pn);


	m_tgc.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x826, float(dbData), pn);

	m_distOffset.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x652, float(dbData), pn);

	m_velocityOffset.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x653, float(dbData), pn);

	m_editTempOffset.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x654, float(dbData), pn);

	m_20mA.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x215, float(dbData), pn);

	m_4mA.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x214, float(dbData), pn);

	m_echoLimit.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x551, UINT8(intData), pn);

	m_editShortWidth.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x844, INT16(intData), pn);

	m_editLongWidth.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x845, INT16(intData), pn);

	m_noiselimit.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x553, UINT8(intData), pn);
}

// CAdvanced2DlgSU 消息处理程序



void CAdvanced2DlgSU::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_EDIT_NOISE, m_noiselimit);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
}

void CAdvanced2DlgSU::OnBnClickedButtonDistadj()
{


	double dbData = 0;
	if (GetNumMessageBox(IDS_MSG_INPUTNULLHIGHT, dbData) != IDOK)
	{
		return;
	}

	CProgress progress;
	int pn = m_comboPointNumber.GetCurSel();
	theApp.m_pClient->SaveData(0x650, float(dbData), pn);

	Sleep(1000);

	float distOffset;
	theApp.m_pClient->LoadData(0x652, distOffset, pn);
	CString str;
	str.Format(_T("%.3f"), distOffset);
	m_distOffset.SetWindowText(str);
}

void CAdvanced2DlgSU::OnBnClickedButtonVeloadj()
{
	double dbData = 0;
	if (GetNumMessageBox(IDS_MSG_INPUTNULLHIGHT, dbData) != IDOK)
	{
		return;
	}

	CProgress progress;
	int pn = m_comboPointNumber.GetCurSel();
	theApp.m_pClient->SaveData(0x651, float(dbData), pn);

	Sleep(1000);

	float veloOffset;
	theApp.m_pClient->LoadData(0x653, veloOffset, pn);
	CString str;
	str.Format(_T("%.3f"), veloOffset);
	m_velocityOffset.SetWindowText(str);
}


void CAdvanced2DlgSU::OnCbnSelchangeComboPointnumber()
{
	LoadData();
}
