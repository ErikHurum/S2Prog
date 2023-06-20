// ResetDlgTU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "ResetDlgTU.h"


// CResetDlgTU

IMPLEMENT_DYNAMIC(CResetDlgTU, COperationDlg)

CResetDlgTU::CResetDlgTU()
{

}

CResetDlgTU::~CResetDlgTU()
{
}


BEGIN_MESSAGE_MAP(CResetDlgTU, COperationDlg)
	ON_BN_CLICKED(IDC_BTN_RESET1, &CResetDlgTU::OnBnClickedBtnReset1)
	ON_BN_CLICKED(IDC_BTN_RESET2, &CResetDlgTU::OnBnClickedBtnReset2)
	ON_BN_CLICKED(IDC_BTN_RESET3, &CResetDlgTU::OnBnClickedBtnReset3)
	ON_BN_CLICKED(IDC_BTN_RESET4, &CResetDlgTU::OnBnClickedBtnReset4)
END_MESSAGE_MAP()

void CResetDlgTU::LoadData()
{

}

void CResetDlgTU::SaveData()
{

}

// CResetDlgTU 消息处理程序



void CResetDlgTU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
}

void CResetDlgTU::Reset( int nResetMode )
{
	theApp.m_pClient->SaveData(0x220, UINT8(nResetMode), 0, false);
	theApp.m_pClient->ResetVarValid();
}
void CResetDlgTU::OnBnClickedBtnReset1()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(1);
	}
}

void CResetDlgTU::OnBnClickedBtnReset2()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(2);
	}
}

void CResetDlgTU::OnBnClickedBtnReset3()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(3);
	}
}

void CResetDlgTU::OnBnClickedBtnReset4()
{
	if (ConfirmMessageBox(IDS_MSG_RESETCONFIRM) == IDOK)
	{
		Reset(4);
	}
}
