// CurrentOutputDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "CurrentOutputDlgSU.h"


// CCurrentOutputDlgSU

IMPLEMENT_DYNAMIC(CCurrentOutputDlgSU, COperationDlg)

CCurrentOutputDlgSU::CCurrentOutputDlgSU()
{

}

CCurrentOutputDlgSU::~CCurrentOutputDlgSU()
{
}


BEGIN_MESSAGE_MAP(CCurrentOutputDlgSU, COperationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &CCurrentOutputDlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()

void CCurrentOutputDlgSU::LoadData()
{
	CProgress progress;


	int pn = m_comboPointNumber.GetCurSel();
	UINT8 intData;

	theApp.m_pClient->LoadData(0x20, intData, pn);
	m_output.SetCurSel(intData - 1);

	theApp.m_pClient->LoadData(0x21, intData, pn);
	m_error.SetCurSel(intData - 1);

	theApp.m_pClient->LoadData(0x22, intData, pn);
	m_min.SetCurSel(intData - 1);

}

void CCurrentOutputDlgSU::SaveData()
{
	CProgress progress;

	
	int intData;
	int pn = m_comboPointNumber.GetCurSel();

	intData = m_output.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x20, UINT8(intData), pn);

	intData = m_error.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x21, UINT8(intData), pn);

	intData = m_min.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x22, UINT8(intData), pn);
}

// CCurrentOutputDlgSU 消息处理程序



void CCurrentOutputDlgSU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ERROR, m_error);
	DDX_Control(pDX, IDC_COMBO_OUTPUT, m_output);
	DDX_Control(pDX, IDC_COMBO_MIN, m_min);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
}

void CCurrentOutputDlgSU::OnCbnSelchangeComboPointnumber()
{
	LoadData();
}
