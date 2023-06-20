// DisplayDlgGR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "DisplayDlgGR.h"


// CDisplayDlgGR

IMPLEMENT_DYNAMIC(CDisplayDlgGR, COperationDlg)

CDisplayDlgGR::CDisplayDlgGR()
{

}

CDisplayDlgGR::~CDisplayDlgGR()
{
}


BEGIN_MESSAGE_MAP(CDisplayDlgGR, COperationDlg)
END_MESSAGE_MAP()

void CDisplayDlgGR::LoadData()
{
	CProgress progress;
	UINT8 intData;
	
	theApp.m_pClient->LoadData(0x1, intData);
	m_display.SetCurSel(intData);
	
}

void CDisplayDlgGR::SaveData()
{
	CProgress progress;
	int intData;

	intData = m_display.GetCurSel();
	theApp.m_pClient->SaveData(0x1, UINT8(intData));
	
}

// CDisplayDlgGR 消息处理程序



void CDisplayDlgGR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DISPLAY, m_display);
}
