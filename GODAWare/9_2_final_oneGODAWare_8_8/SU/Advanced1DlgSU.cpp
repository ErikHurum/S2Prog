// Advanced1DlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "Advanced1DlgSU.h"
#include "../CalibrationDlg.h"


// CAdvanced1DlgSU

IMPLEMENT_DYNAMIC(CAdvanced1DlgSU, COperationDlg)

CAdvanced1DlgSU::CAdvanced1DlgSU()
{

}

CAdvanced1DlgSU::~CAdvanced1DlgSU()
{
}


BEGIN_MESSAGE_MAP(CAdvanced1DlgSU, COperationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_RELAYALARM, &CAdvanced1DlgSU::OnCbnSelchangeComboRelayalarm)
	ON_CBN_SELCHANGE(IDC_COMBO_RELAY, &CAdvanced1DlgSU::OnCbnSelchangeComboRelay)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSOR, &CAdvanced1DlgSU::OnCbnSelchangeComboSensor)
	ON_CBN_SELCHANGE(IDC_COMBO_CURRENTPORT, &CAdvanced1DlgSU::OnCbnSelchangeCurrentOutPort)
	
END_MESSAGE_MAP()

void CAdvanced1DlgSU::LoadData()
{
	CProgress progress;

	UINT8 intData;
	theApp.m_pClient->LoadData(0x36, intData);
	m_checkEnableFlow.SetCheck(intData);

	theApp.m_pClient->LoadData(0x35, intData);

	
	//if (intData == 0)
	//	m_solid.SetCheck(TRUE);
	//else
	//	m_solid.SetCheck(FALSE);


	if(intData == 0) 
	{
		CheckDlgButton(IDC_GDSL53S, 1);
		CheckDlgButton(IDC_GDSL53E, 0);
	}
	else 
	{
		CheckDlgButton(IDC_GDSL53E, 1);
		CheckDlgButton(IDC_GDSL53S, 0);
	}

	theApp.m_pClient->LoadData(0x302, intData);
	this->m_checkEnableMutiSensor.SetCheck(intData);

	int maOut = m_comboCurrentOutPort.GetCurSel() + 1;

	float floatData;
	
	theApp.m_pClient->LoadData(0x202, floatData, maOut);
	m_comboCurrentOut.SetCurSel((int)floatData - 1);

	OnCbnSelchangeComboRelay();
	// OnCbnSelchangeComboRelay();

}

void CAdvanced1DlgSU::SaveData()
{
	CProgress progress;

	

	int intData;

	intData = IsDlgButtonChecked(IDC_GDSL53E)?1:0;

	theApp.m_pClient->SaveData(0x35, UINT8(intData));


	intData = m_checkEnableFlow.GetCheck();
	theApp.m_pClient->SaveData(0x36, UINT8(intData));

	intData = m_checkEnableMutiSensor.GetCheck();
	theApp.m_pClient->SaveData(0x302, UINT8(intData));


	int maOut = m_comboCurrentOutPort.GetCurSel() + 1;

	theApp.m_pClient->SaveData(0x202, (float)(m_comboCurrentOut.GetCurSel()+1), maOut);


	// 继电器部分
	int relayNum = m_comboRelay.GetCurSel() + 1;


	intData = this->m_comboSensor.GetCurSel();
	theApp.m_pClient->SaveData(0x100, (UINT8)intData, relayNum);

	intData = this->m_comboRelayWarning.GetCurSel();
	theApp.m_pClient->SaveData(0x104, (UINT8)intData, relayNum);

	double floatData;
	CString s;
	m_editHighWarning.GetWindowText(s);
	floatData = _tstof(s);
	theApp.m_pClient->SaveData(0x101, (float)floatData, relayNum);

	m_editLowWarning.GetWindowText(s);
	floatData = _tstof(s);
	theApp.m_pClient->SaveData(0x102, (float)floatData, relayNum);

	m_editHysteresys.GetWindowText(s);
	floatData = _tstof(s);
	theApp.m_pClient->SaveData(0x103, (float)floatData, relayNum);


}


void CAdvanced1DlgSU::DoDataExchange(CDataExchange* pDX)
{
	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CURRENTPORT, m_comboCurrentOutPort);
	DDX_Control(pDX, IDC_COMBO_POINTNUM, m_comboPointNumber);
	DDX_Control(pDX, IDC_COMBO_CURRENTOUT, m_comboCurrentOut);
	DDX_Control(pDX, IDC_COMBO_SENSOR, m_comboSensor);
	DDX_Control(pDX, IDC_COMBO_RELAY, m_comboRelay);
	DDX_Control(pDX, IDC_COMBO_RELAYALARM, m_comboRelayWarning);
	DDX_Control(pDX, IDC_EDIT_HIGHALARM, m_editHighWarning);
	DDX_Control(pDX, IDC_EDIT_LOWALARM, m_editLowWarning);
	DDX_Control(pDX, IDC_EDIT_HYSTERESYS, m_editHysteresys);
	DDX_Control(pDX, IDC_CHECK_ENABLEMULTISENSOR, m_checkEnableMutiSensor);
	DDX_Control(pDX, IDC_CHECK_ENABLEFLOW, m_checkEnableFlow);
	DDX_Control(pDX, IDC_GDSL53S, m_solid);
}

BOOL CAdvanced1DlgSU::OnInitDialog()
{
	COperationDlg::OnInitDialog();

	m_comboCurrentOut.SetCurSel(0);
	m_comboCurrentOutPort.SetCurSel(0);
	m_comboRelay.SetCurSel(0);
	m_comboRelayWarning.SetCurSel(0);
	m_comboSensor.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAdvanced1DlgSU::OnCbnSelchangeComboRelayalarm()
{
	int alarmType = m_comboRelayWarning.GetCurSel() + 1;

	switch(alarmType)
	{
	case 0:
		m_editHysteresys.EnableWindow(false);
		m_editHighWarning.EnableWindow(false);
		m_editLowWarning.EnableWindow(false);
		break;
	case 1:
		m_editHysteresys.EnableWindow(true);
		m_editHighWarning.EnableWindow(true);
		m_editLowWarning.EnableWindow(false);
		break;
	case 2:
		m_editHysteresys.EnableWindow(true);
		m_editHighWarning.EnableWindow(false);
		m_editLowWarning.EnableWindow(true);
		break;
	case 3:
		m_editHysteresys.EnableWindow(true);
		m_editHighWarning.EnableWindow(true);
		m_editLowWarning.EnableWindow(true);
		break;
	case 4:
		m_editHysteresys.EnableWindow(true);
		m_editHighWarning.EnableWindow(true);
		m_editLowWarning.EnableWindow(true);
		break;
	default:
		break;
	}

}

void CAdvanced1DlgSU::OnCbnSelchangeComboRelay()
{
	int pn = m_comboRelay.GetCurSel()+1;
	UINT8 intData;
	
	theApp.m_pClient->LoadData(0x100, intData, pn);
	this->m_comboSensor.SetCurSel(intData);

	theApp.m_pClient->LoadData(0x104, intData, pn);
	this->m_comboRelayWarning.SetCurSel(intData);
	OnCbnSelchangeComboRelayalarm();

	float floatData;
	CString s;
	theApp.m_pClient->LoadData(0x101, floatData, pn);
	s.Format(_T("%.3f"), floatData);
	this->m_editHighWarning.SetWindowTextW(s);

	theApp.m_pClient->LoadData(0x102, floatData, pn);
	s.Format(_T("%.3f"), floatData);
	this->m_editLowWarning.SetWindowTextW(s);

	theApp.m_pClient->LoadData(0x103, floatData, pn);
	s.Format(_T("%.3f"), floatData);
	this->m_editHysteresys.SetWindowTextW(s);

}


void CAdvanced1DlgSU::OnCbnSelchangeCurrentOutPort()
{

	int maOut = m_comboCurrentOutPort.GetCurSel() + 1;
	float floatData;
	
	theApp.m_pClient->LoadData(0x202, floatData, maOut);
	m_comboCurrentOut.SetCurSel((int)floatData - 1);


}
void CAdvanced1DlgSU::OnCbnSelchangeComboSensor()
{
	if (this->m_comboSensor.GetCurSel() == 0)
	{
		m_comboRelayWarning.EnableWindow(false);
		m_editHysteresys.EnableWindow(false);
		m_editHighWarning.EnableWindow(false);
		m_editLowWarning.EnableWindow(false);
	}
}