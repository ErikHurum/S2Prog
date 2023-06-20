// DisplayDlgTU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "DisplayDlgTU.h"


// CDisplayDlgTU

IMPLEMENT_DYNAMIC(CDisplayDlgTU, COperationDlg)

CDisplayDlgTU::CDisplayDlgTU()
{

}

CDisplayDlgTU::~CDisplayDlgTU()
{
}


BEGIN_MESSAGE_MAP(CDisplayDlgTU, COperationDlg)
END_MESSAGE_MAP()

void CDisplayDlgTU::LoadData()
{
	CProgress progress;
	UINT8 intData;
	
	theApp.m_pClient->LoadData(0x1, intData);
	m_display.SetCurSel(intData);
	
}

void CDisplayDlgTU::SaveData()
{
	CProgress progress;
	int intData;

	intData = m_display.GetCurSel();
	theApp.m_pClient->SaveData(0x1, UINT8(intData));
	
}

// CDisplayDlgTU 消息处理程序



void CDisplayDlgTU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DISPLAY, m_display);
}
