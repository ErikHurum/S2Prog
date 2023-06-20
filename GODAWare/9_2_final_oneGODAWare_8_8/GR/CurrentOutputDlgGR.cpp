// CurrentOutputDlgGR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "CurrentOutputDlgGR.h"


// CCurrentOutputDlgGR

IMPLEMENT_DYNAMIC(CCurrentOutputDlgGR, COperationDlg)

CCurrentOutputDlgGR::CCurrentOutputDlgGR()
{

}

CCurrentOutputDlgGR::~CCurrentOutputDlgGR()
{
}


BEGIN_MESSAGE_MAP(CCurrentOutputDlgGR, COperationDlg)
END_MESSAGE_MAP()

void CCurrentOutputDlgGR::LoadData()
{
	CProgress progress;

	UINT8 intData;

	theApp.m_pClient->LoadData(0x20, intData);
	m_output.SetCurSel(intData - 1);

	theApp.m_pClient->LoadData(0x21, intData);
	m_error.SetCurSel(intData - 1);

	theApp.m_pClient->LoadData(0x22, intData);
	m_min.SetCurSel(intData - 1);

}

void CCurrentOutputDlgGR::SaveData()
{
	int intData;
	
	intData = m_output.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x20, UINT8(intData));

	intData = m_error.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x21, UINT8(intData));

	intData = m_min.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x22, UINT8(intData));
}

// CCurrentOutputDlgGR 消息处理程序



void CCurrentOutputDlgGR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ERROR, m_error);
	DDX_Control(pDX, IDC_COMBO_OUTPUT, m_output);
	DDX_Control(pDX, IDC_COMBO_MIN, m_min);
}
