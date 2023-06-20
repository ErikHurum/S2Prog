// FalseEchoDlgGR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "FalseEchoDlgGR.h"


// CFalseEchoDlgGR

IMPLEMENT_DYNAMIC(CFalseEchoDlgGR, COperationDlg)

CFalseEchoDlgGR::CFalseEchoDlgGR()
{

}

CFalseEchoDlgGR::~CFalseEchoDlgGR()
{
}


BEGIN_MESSAGE_MAP(CFalseEchoDlgGR, COperationDlg)
	ON_BN_CLICKED(IDC_BTN_NEW, &CFalseEchoDlgGR::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_UPDATE, &CFalseEchoDlgGR::OnBnClickedBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CFalseEchoDlgGR::OnBnClickedBtnDelete)
END_MESSAGE_MAP()

void CFalseEchoDlgGR::LoadData()
{

}

void CFalseEchoDlgGR::SaveData()
{

}

// CFalseEchoDlgGR 消息处理程序



void CFalseEchoDlgGR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
}

void CFalseEchoDlgGR::OnBnClickedBtnNew()
{
	double echoDist;
	if (GetNumMessageBox(IDS_MSG_ECHOLABEL, 0, 35, echoDist))
	{
		CProgress progress;
		if (theApp.m_pClient->SaveData(0x922, float(echoDist),0, false))
		{
			Sleep(5000);
			UINT8 learning = 1;
			while(learning == 1)
			{
				Sleep(5000);
				theApp.m_pClient->LoadData(0x922, learning);
				theApp.m_pClient->SetVarInvalid(0x922);
			}
			InfoMessageBox(IDS_SAVEOK);
		}
	}
}

void CFalseEchoDlgGR::OnBnClickedBtnUpdate()
{
	double echoDist;
	if (GetNumMessageBox(IDS_MSG_ECHOLABEL, 0, 35, echoDist))
	{
		CProgress progress;
		if (theApp.m_pClient->SaveData(0x921, float(echoDist),0, false))
		{
			Sleep(5000);	
			UINT8 learning = 1;
			while(learning == 1)
			{
				Sleep(5000);
				theApp.m_pClient->LoadData(0x922, learning);
				theApp.m_pClient->SetVarInvalid(0x922);
			}
			InfoMessageBox(IDS_SAVEOK);
		}
	}
}

void CFalseEchoDlgGR::OnBnClickedBtnDelete()
{
	double echoDist = 0;
	CProgress progress;
	if (theApp.m_pClient->SaveData(0x920, float(echoDist),0,false))
	{
		Sleep(5000);
		UINT8 learning = 1;
		while(learning == 1)
		{
			Sleep(5000);
			theApp.m_pClient->LoadData(0x922, learning);
			theApp.m_pClient->SetVarInvalid(0x922);
		}
		InfoMessageBox(IDS_SAVEOK);
	}
}
