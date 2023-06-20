// ResetDlgPR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "ResetDlgPR.h"


// CResetDlgPR

IMPLEMENT_DYNAMIC(CResetDlgPR, COperationDlg)

CResetDlgPR::CResetDlgPR()
{

}

CResetDlgPR::~CResetDlgPR()
{
}


BEGIN_MESSAGE_MAP(CResetDlgPR, COperationDlg)
	ON_BN_CLICKED(IDC_BTN_RESET1, &CResetDlgPR::OnBnClickedBtnReset1)
	ON_BN_CLICKED(IDC_BTN_RESET2, &CResetDlgPR::OnBnClickedBtnReset2)
	ON_BN_CLICKED(IDC_BTN_RESET3, &CResetDlgPR::OnBnClickedBtnReset3)
	ON_BN_CLICKED(IDC_BTN_RESET4, &CResetDlgPR::OnBnClickedBtnReset4)
END_MESSAGE_MAP()

void CResetDlgPR::LoadData()
{

}

void CResetDlgPR::SaveData()
{

}

// CResetDlgPR 消息处理程序



void CResetDlgPR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
}

void CResetDlgPR::Reset( int nResetMode )
{
	theApp.m_pClient->SaveData(0x220, UINT8(nResetMode), 0, false);
	theApp.m_pClient->ResetVarValid();
}
void CResetDlgPR::OnBnClickedBtnReset1()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(1);
	}
}

void CResetDlgPR::OnBnClickedBtnReset2()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(2);
	}
}

void CResetDlgPR::OnBnClickedBtnReset3()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(3);
	}
}

void CResetDlgPR::OnBnClickedBtnReset4()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(4);
	}
}
