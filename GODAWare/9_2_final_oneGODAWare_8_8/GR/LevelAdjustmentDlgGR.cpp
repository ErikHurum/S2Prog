// LevelAdjustmentGR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "../Client.h"
#include "LevelAdjustmentDlgGR.h"


// CLevelAdjustmentDlgGR

IMPLEMENT_DYNAMIC(CLevelAdjustmentDlgGR, COperationDlg)

CLevelAdjustmentDlgGR::CLevelAdjustmentDlgGR()
{

}

CLevelAdjustmentDlgGR::~CLevelAdjustmentDlgGR()
{
}

void CLevelAdjustmentDlgGR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EDIT_HIGH_PERCENT, m_highPercent);
	DDX_Control(pDX, IDC_EDIT_HIGH, m_high);
	DDX_Control(pDX, IDC_EDIT_RIGION, m_rigion);
	DDX_Control(pDX, IDC_EDIT_LOWADJUST, m_low);
	DDX_Control(pDX, IDC_EDIT_LOWADJUST_PERCENT, m_lowPercent);
	DDX_Control(pDX, IDC_EDIT_SHADOWRIGION, m_shadowRigion);
}

BEGIN_MESSAGE_MAP(CLevelAdjustmentDlgGR, COperationDlg)
END_MESSAGE_MAP()


void CLevelAdjustmentDlgGR::LoadData()
{
	CProgress progress;
	float dbData;
	CString str;

	theApp.m_pClient->LoadData(0x17, dbData);
	str.Format(_T("%.3f"),dbData);
	m_rigion.SetWindowText(str);

	theApp.m_pClient->LoadData(0x110, dbData);
	str.Format(_T("%.0f"),dbData * 100);
	m_lowPercent.SetWindowText(str);

	theApp.m_pClient->LoadData(0x111, dbData);
	str.Format(_T("%.3f"),dbData);
	m_low.SetWindowText(str);

	theApp.m_pClient->LoadData(0x112, dbData);
	str.Format(_T("%.0f"),dbData * 100);
	m_highPercent.SetWindowText(str);

	theApp.m_pClient->LoadData(0x113, dbData);
	str.Format(_T("%.3f"),dbData);
	m_high.SetWindowText(str);

	theApp.m_pClient->LoadData(0x800, dbData);
	str.Format(_T("%.3f"),dbData);
	m_shadowRigion.SetWindowText(str);


}

void CLevelAdjustmentDlgGR::SaveData()
{
	CProgress progress;
	double dbData;
	CString str;

	m_rigion.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x17, float(dbData));

	m_lowPercent.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x110, float(dbData) / 100);

	m_low.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x111, float(dbData));

	m_highPercent.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x112, float(dbData) / 100);

	m_high.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x113, float(dbData));

	m_shadowRigion.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x800, float(dbData));

}
