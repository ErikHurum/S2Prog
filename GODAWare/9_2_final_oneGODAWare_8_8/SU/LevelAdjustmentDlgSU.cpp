// LevelAdjustmentSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "../Client.h"
#include "LevelAdjustmentDlgSU.h"


// CLevelAdjustmentDlgSU

IMPLEMENT_DYNAMIC(CLevelAdjustmentDlgSU, COperationDlg)

CLevelAdjustmentDlgSU::CLevelAdjustmentDlgSU()
{

}

CLevelAdjustmentDlgSU::~CLevelAdjustmentDlgSU()
{
}

void CLevelAdjustmentDlgSU::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EDIT_HIGH_PERCENT, m_highPercent);
	DDX_Control(pDX, IDC_EDIT_HIGH, m_high);
	DDX_Control(pDX, IDC_EDIT_LOWADJUST, m_low);
	DDX_Control(pDX, IDC_EDIT_LOWADJUST_PERCENT, m_lowPercent);
	DDX_Control(pDX, IDC_EDIT_SHADOWRIGION, m_shadowRigion);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
}

BEGIN_MESSAGE_MAP(CLevelAdjustmentDlgSU, COperationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &CLevelAdjustmentDlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()


void CLevelAdjustmentDlgSU::LoadData()
{
	CProgress progress;


	int pn = m_comboPointNumber.GetCurSel();
	float dbData;
	CString str;

	theApp.m_pClient->LoadData(0x110, dbData, pn);
	str.Format(_T("%.0f"),dbData * 100);
	m_lowPercent.SetWindowText(str);

	theApp.m_pClient->LoadData(0x111, dbData, pn);
	str.Format(_T("%.3f"),dbData);
	m_low.SetWindowText(str);

	theApp.m_pClient->LoadData(0x112, dbData, pn);
	str.Format(_T("%.0f"),dbData * 100);
	m_highPercent.SetWindowText(str);

	theApp.m_pClient->LoadData(0x113, dbData, pn);
	str.Format(_T("%.3f"),dbData);
	m_high.SetWindowText(str);

	theApp.m_pClient->LoadData(0x800, dbData, pn);
	str.Format(_T("%.3f"),dbData);
	m_shadowRigion.SetWindowText(str);


}

void CLevelAdjustmentDlgSU::SaveData()
{
	CProgress progress;
	double dbData;
	CString str;


	int pn = m_comboPointNumber.GetCurSel();
	m_lowPercent.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x110, float(dbData) / 100, pn);

	m_low.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x111, float(dbData), pn);

	m_highPercent.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x112, float(dbData) / 100, pn);

	m_high.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x113, float(dbData), pn);

	m_shadowRigion.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x800, float(dbData), pn);

}

void CLevelAdjustmentDlgSU::OnCbnSelchangeComboPointnumber()
{
	LoadData();
}
