// ResetDlgGR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "ResetDlgGR.h"


// CResetDlgGR

IMPLEMENT_DYNAMIC(CResetDlgGR, COperationDlg)

CResetDlgGR::CResetDlgGR()
{

}

CResetDlgGR::~CResetDlgGR()
{
}


BEGIN_MESSAGE_MAP(CResetDlgGR, COperationDlg)
	ON_BN_CLICKED(IDC_BTN_RESET1, &CResetDlgGR::OnBnClickedBtnReset1)
	ON_BN_CLICKED(IDC_BTN_RESET2, &CResetDlgGR::OnBnClickedBtnReset2)
	ON_BN_CLICKED(IDC_BTN_RESET3, &CResetDlgGR::OnBnClickedBtnReset3)
	ON_BN_CLICKED(IDC_BTN_RESET4, &CResetDlgGR::OnBnClickedBtnReset4)
END_MESSAGE_MAP()

void CResetDlgGR::LoadData()
{

}

void CResetDlgGR::SaveData()
{

}

// CResetDlgGR 消息处理程序



void CResetDlgGR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
}

void CResetDlgGR::Reset( int nResetMode )
{
	theApp.m_pClient->SaveData(0x220, UINT8(nResetMode), 0, false);
	theApp.m_pClient->ResetVarValid();
}
void CResetDlgGR::OnBnClickedBtnReset1()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(1);
	}
}

void CResetDlgGR::OnBnClickedBtnReset2()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(2);
	}
}

void CResetDlgGR::OnBnClickedBtnReset3()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(3);
	}
}

void CResetDlgGR::OnBnClickedBtnReset4()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(4);
	}
}
