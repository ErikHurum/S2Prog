// DampingDlgGR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "DampingDlgGR.h"


// CDampingDlgGR

IMPLEMENT_DYNAMIC(CDampingDlgGR, COperationDlg)

CDampingDlgGR::CDampingDlgGR()
{

}

CDampingDlgGR::~CDampingDlgGR()
{
}


BEGIN_MESSAGE_MAP(CDampingDlgGR, COperationDlg)
END_MESSAGE_MAP()

void CDampingDlgGR::LoadData()
{
	CProgress progress;
	CString str;
	INT16 intData;
	
	theApp.m_pClient->LoadData(0x9, intData);
	str.Format(_T("%d"), intData);
	m_damping.SetWindowText(str);
}

void CDampingDlgGR::SaveData()
{
	CString str;
	int intData;
	
	m_damping.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x9, INT16(intData));
}

// CDampingDlgGR 消息处理程序



void CDampingDlgGR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DAMPING, m_damping);
}
