// ResetDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "ResetDlgSU.h"


// CResetDlgSU

IMPLEMENT_DYNAMIC(CResetDlgSU, COperationDlg)

CResetDlgSU::CResetDlgSU()
{

}

CResetDlgSU::~CResetDlgSU()
{
}


BEGIN_MESSAGE_MAP(CResetDlgSU, COperationDlg)
	ON_BN_CLICKED(IDC_BTN_RESET1, &CResetDlgSU::OnBnClickedBtnReset1)
	ON_BN_CLICKED(IDC_BTN_RESET2, &CResetDlgSU::OnBnClickedBtnReset2)
	ON_BN_CLICKED(IDC_BTN_RESET3, &CResetDlgSU::OnBnClickedBtnReset3)
	ON_BN_CLICKED(IDC_BTN_RESET4, &CResetDlgSU::OnBnClickedBtnReset4)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &CResetDlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()

void CResetDlgSU::LoadData()
{

}

void CResetDlgSU::SaveData()
{

}

// CResetDlgSU 消息处理程序



void CResetDlgSU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
}

void CResetDlgSU::Reset( int nResetMode )
{
	theApp.m_pClient->SaveData(0x220, UINT8(nResetMode), 0, false);
	theApp.m_pClient->ResetVarValid();
}
void CResetDlgSU::OnBnClickedBtnReset1()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(1);
	}
}

void CResetDlgSU::OnBnClickedBtnReset2()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(2);
	}
}

void CResetDlgSU::OnBnClickedBtnReset3()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(3);
	}
}

void CResetDlgSU::OnBnClickedBtnReset4()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(4);
	}
}

void CResetDlgSU::OnCbnSelchangeComboPointnumber()
{
}
