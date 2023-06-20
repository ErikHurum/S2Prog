// FalseEchoDlgPR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "FalseEchoDlgPR.h"


// CFalseEchoDlgPR

IMPLEMENT_DYNAMIC(CFalseEchoDlgPR, COperationDlg)

CFalseEchoDlgPR::CFalseEchoDlgPR()
{

}

CFalseEchoDlgPR::~CFalseEchoDlgPR()
{
}


BEGIN_MESSAGE_MAP(CFalseEchoDlgPR, COperationDlg)
	ON_BN_CLICKED(IDC_BTN_NEW, &CFalseEchoDlgPR::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_UPDATE, &CFalseEchoDlgPR::OnBnClickedBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CFalseEchoDlgPR::OnBnClickedBtnDelete)
END_MESSAGE_MAP()

void CFalseEchoDlgPR::LoadData()
{

}

void CFalseEchoDlgPR::SaveData()
{

}

// CFalseEchoDlgPR 消息处理程序



void CFalseEchoDlgPR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
}

void CFalseEchoDlgPR::OnBnClickedBtnNew()
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

void CFalseEchoDlgPR::OnBnClickedBtnUpdate()
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

void CFalseEchoDlgPR::OnBnClickedBtnDelete()
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
