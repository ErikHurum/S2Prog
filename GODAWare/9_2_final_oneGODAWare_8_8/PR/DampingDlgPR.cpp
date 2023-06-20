// DampingDlgPR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "DampingDlgPR.h"


// CDampingDlgPR

IMPLEMENT_DYNAMIC(CDampingDlgPR, COperationDlg)

CDampingDlgPR::CDampingDlgPR()
{

}

CDampingDlgPR::~CDampingDlgPR()
{
}


BEGIN_MESSAGE_MAP(CDampingDlgPR, COperationDlg)
END_MESSAGE_MAP()

void CDampingDlgPR::LoadData()
{
	CProgress progress;
	CString str;
	INT16 intData;
	
	theApp.m_pClient->LoadData(0x9, intData);
	str.Format(_T("%d"), intData);
	m_damping.SetWindowText(str);
}

void CDampingDlgPR::SaveData()
{
	CString str;
	int intData;
	
	m_damping.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x9, INT16(intData));
}

// CDampingDlgPR 消息处理程序



void CDampingDlgPR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DAMPING, m_damping);
}
