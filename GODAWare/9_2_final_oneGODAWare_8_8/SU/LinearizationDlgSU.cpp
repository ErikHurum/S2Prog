// LinearizationDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "LinearizationDlgSU.h"



// CLinearizationDlgSU

IMPLEMENT_DYNAMIC(CLinearizationDlgSU, COperationDlg)

CLinearizationDlgSU::CLinearizationDlgSU()
{

}

CLinearizationDlgSU::~CLinearizationDlgSU()
{
}


BEGIN_MESSAGE_MAP(CLinearizationDlgSU, COperationDlg)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CLinearizationDlgSU::OnBnClickedButtonEdit)
	ON_CBN_SELCHANGE(IDC_COMBO_LIN0EARIZATIONTYPE, &CLinearizationDlgSU::OnCbnSelchangeComboLinearizationtype)
	ON_CBN_SELCHANGE(IDC_COMBO_VESSELTYPE, &CLinearizationDlgSU::OnCbnSelchangeComboVesseltype)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &CLinearizationDlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()

void CLinearizationDlgSU::LoadData()
{
	CProgress progress;

	int pn = m_comboPointNumber.GetCurSel();

	CString str;
	UINT8 intData;
	float floatData;

	theApp.m_pClient->LoadData(0x10, intData, pn);
	m_comboVesselType.SetCurSel(intData -  1);
	OnCbnSelchangeComboVesseltype();

	theApp.m_pClient->LoadData(0x12, intData, pn);
	m_linearizationType.SetCurSel(intData -  1);
	OnCbnSelchangeComboLinearizationtype();

	theApp.m_pClient->LoadData(0x13, intData, pn);
	m_unit.SetCurSel(intData - 1);

	theApp.m_pClient->LoadData(0x114, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_0percent.SetWindowText(str);

	theApp.m_pClient->LoadData(0x115, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_100percent.SetWindowText(str);

}

void CLinearizationDlgSU::SaveData()
{
	CProgress progress;
	CString str;
	int intData;
	double dbData;
	int pn = m_comboPointNumber.GetCurSel();

	intData = m_comboVesselType.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x10, UINT8(intData), pn);

	intData = m_linearizationType.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x12, UINT8(intData), pn);

	intData = m_unit.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x13, UINT8(intData), pn);

	m_0percent.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x114, float(dbData), pn);

	m_100percent.GetWindowText(str);
	dbData = _tstof(str);
	theApp.m_pClient->SaveData(0x115, float(dbData), pn);

}

// CLinearizationDlgSU 消息处理程序



void CLinearizationDlgSU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_0PERCENT, m_0percent);
	DDX_Control(pDX, IDC_EDIT_100PERCENT, m_100percent);
	DDX_Control(pDX, IDC_COMBO_UNIT, m_unit);
	DDX_Control(pDX, IDC_COMBO_LIN0EARIZATIONTYPE, m_linearizationType);
	DDX_Control(pDX, IDC_COMBO_VESSELTYPE, m_comboVesselType);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
}

void CLinearizationDlgSU::OnBnClickedButtonEdit()
{
	int pn = m_comboPointNumber.GetCurSel();
	CMappingEditDlg pDlg(this, pn);
	pDlg.DoModal();
	LoadData();
}

void CLinearizationDlgSU::OnCbnSelchangeComboLinearizationtype()
{
	int nType;
	nType = m_linearizationType.GetCurSel();
	m_unit.ResetContent();
	switch(nType)
	{
	case 0:
		m_unit.InsertString(0,_T("m"));	
		m_unit.InsertString(1,_T("ft"));	
		m_unit.InsertString(2,_T("in"));	
		m_unit.InsertString(3,_T("cm"));	
		m_unit.InsertString(4,_T("mm"));	
		break;
	case 1:
		m_unit.InsertString(0,_T("kg"));	
		m_unit.InsertString(1,_T("t"));	
		m_unit.InsertString(2,_T("lb"));	
		break;
	case 2:
		m_unit.InsertString(0,_T("m3/s"));	
		m_unit.InsertString(1,_T("m3/h"));	
		m_unit.InsertString(2,_T("ft3/s"));	
		m_unit.InsertString(3,_T("ft3/min"));	
		m_unit.InsertString(4,_T("gal/min"));			
		m_unit.InsertString(5,_T("gal/h"));			
		m_unit.InsertString(6,_T("l/s"));			
		m_unit.InsertString(7,_T("l/min"));			
		m_unit.InsertString(8,_T("l/h"));			
		break;	   						
	case 3:
		m_unit.InsertString(0,_T("m3"));	
		m_unit.InsertString(1,_T("l"));	
		m_unit.InsertString(2,_T("hl"));	
		m_unit.InsertString(3,_T("ft3"));	
		m_unit.InsertString(4,_T("in3"));	
		m_unit.InsertString(5,_T("gal"));	
		break;
	}
}

void CLinearizationDlgSU::OnCbnSelchangeComboVesseltype()
{
	if (m_comboVesselType.GetCurSel() == 0)	// 线性
	{
		m_0percent.SetReadOnly(FALSE);
		m_100percent.SetReadOnly(FALSE);
		m_linearizationType.EnableWindow(TRUE);
		m_unit.EnableWindow(TRUE);
		m_btnEdit.EnableWindow(FALSE);
	}
	else
	{
		m_0percent.SetReadOnly(TRUE);
		m_100percent.SetReadOnly(TRUE);
		m_linearizationType.EnableWindow(FALSE);
		m_unit.EnableWindow(FALSE);
		m_btnEdit.EnableWindow(TRUE);
	}
}

void CLinearizationDlgSU::OnCbnSelchangeComboPointnumber()
{
	LoadData();
}
