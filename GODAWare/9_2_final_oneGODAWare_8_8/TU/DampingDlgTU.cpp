// DampingDlgTU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "DampingDlgTU.h"


// CDampingDlgTU

IMPLEMENT_DYNAMIC(CDampingDlgTU, COperationDlg)

CDampingDlgTU::CDampingDlgTU()
{

}

CDampingDlgTU::~CDampingDlgTU()
{
}


BEGIN_MESSAGE_MAP(CDampingDlgTU, COperationDlg)
END_MESSAGE_MAP()

void CDampingDlgTU::LoadData()
{
	CProgress progress;

	CString str;
	INT16 intData;
	
	theApp.m_pClient->LoadData(0x9, intData);
	str.Format(_T("%d"), intData);
	m_damping.SetWindowText(str);
}

void CDampingDlgTU::SaveData()
{
	CProgress progress;

	CString str;
	int intData;
	
	m_damping.GetWindowText(str);
	intData = _tstoi(str);
	theApp.m_pClient->SaveData(0x9, INT16(intData));
}

// CDampingDlgTU 消息处理程序



void CDampingDlgTU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DAMPING, m_damping);
}
