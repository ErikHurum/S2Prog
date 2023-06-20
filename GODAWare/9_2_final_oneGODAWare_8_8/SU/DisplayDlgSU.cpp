// DisplayDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "DisplayDlgSU.h"


// CDisplayDlgSU

IMPLEMENT_DYNAMIC(CDisplayDlgSU, COperationDlg)

CDisplayDlgSU::CDisplayDlgSU()
{

}

CDisplayDlgSU::~CDisplayDlgSU()
{
}


BEGIN_MESSAGE_MAP(CDisplayDlgSU, COperationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &CDisplayDlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()

void CDisplayDlgSU::LoadData()
{
	CProgress progress;

	int pn = m_comboPointNumber.GetCurSel();
	UINT8 intData;
	
	theApp.m_pClient->LoadData(0x1, intData, pn);
	m_display.SetCurSel(intData);
	
}

void CDisplayDlgSU::SaveData()
{
	CProgress progress;
	int pn = m_comboPointNumber.GetCurSel();

	int intData;

	intData = m_display.GetCurSel();
	theApp.m_pClient->SaveData(0x1, UINT8(intData), pn);
	
}

// CDisplayDlgSU 消息处理程序



void CDisplayDlgSU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DISPLAY, m_display);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
}

void CDisplayDlgSU::OnCbnSelchangeComboPointnumber()
{
	LoadData();
}
