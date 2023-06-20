// DampingDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "DampingDlgSU.h"


// CDampingDlgSU

IMPLEMENT_DYNAMIC(CDampingDlgSU, COperationDlg)

CDampingDlgSU::CDampingDlgSU()
{

}

CDampingDlgSU::~CDampingDlgSU()
{
}


BEGIN_MESSAGE_MAP(CDampingDlgSU, COperationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &CDampingDlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()

void CDampingDlgSU::LoadData()
{
	CProgress progress;

	int pn = m_comboPointNumber.GetCurSel();

	CString str;
	INT16 intData;
	
	theApp.m_pClient->LoadData(0x9, intData, pn);
	str.Format(_T("%d"), intData);
	m_damping.SetWindowText(str);
}

void CDampingDlgSU::SaveData()
{
	CProgress progress;


	int pn = m_comboPointNumber.GetCurSel();
	CString str;
	int intData;
	
	m_damping.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x9, INT16(intData), pn);
}

// CDampingDlgSU 消息处理程序



void CDampingDlgSU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DAMPING, m_damping);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
}

void CDampingDlgSU::OnCbnSelchangeComboPointnumber()
{
	LoadData();
}
