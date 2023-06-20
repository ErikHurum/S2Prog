// DisplayDlgPR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "DisplayDlgPR.h"


// CDisplayDlgPR

IMPLEMENT_DYNAMIC(CDisplayDlgPR, COperationDlg)

CDisplayDlgPR::CDisplayDlgPR()
{

}

CDisplayDlgPR::~CDisplayDlgPR()
{
}


BEGIN_MESSAGE_MAP(CDisplayDlgPR, COperationDlg)
END_MESSAGE_MAP()

void CDisplayDlgPR::LoadData()
{
	CProgress progress;
	UINT8 intData;
	
	theApp.m_pClient->LoadData(0x1, intData);
	m_display.SetCurSel(intData);
	
}

void CDisplayDlgPR::SaveData()
{
	CProgress progress;
	int intData;

	intData = m_display.GetCurSel();
	theApp.m_pClient->SaveData(0x1, UINT8(intData));
	
}

// CDisplayDlgPR 消息处理程序



void CDisplayDlgPR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DISPLAY, m_display);
}
