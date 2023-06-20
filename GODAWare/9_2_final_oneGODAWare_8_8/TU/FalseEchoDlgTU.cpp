// FalseEchoDlgTU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "FalseEchoDlgTU.h"


// CFalseEchoDlgTU

IMPLEMENT_DYNAMIC(CFalseEchoDlgTU, COperationDlg)

CFalseEchoDlgTU::CFalseEchoDlgTU()
{

}

CFalseEchoDlgTU::~CFalseEchoDlgTU()
{
}


BEGIN_MESSAGE_MAP(CFalseEchoDlgTU, COperationDlg)
	ON_BN_CLICKED(IDC_BTN_NEW, &CFalseEchoDlgTU::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_UPDATE, &CFalseEchoDlgTU::OnBnClickedBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CFalseEchoDlgTU::OnBnClickedBtnDelete)
END_MESSAGE_MAP()

void CFalseEchoDlgTU::LoadData()
{

}

void CFalseEchoDlgTU::SaveData()
{

}

// CFalseEchoDlgTU 消息处理程序



void CFalseEchoDlgTU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
}

void CFalseEchoDlgTU::OnBnClickedBtnNew()
{
	double echoDist;
	if (GetNumMessageBox(IDS_MSG_ECHOLABEL, 0, 35, echoDist))
	{
		CProgress progress;
		if (theApp.m_pClient->SaveData(0x922, float(echoDist), 0, false))
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

void CFalseEchoDlgTU::OnBnClickedBtnUpdate()
{
	double echoDist;
	if (GetNumMessageBox(IDS_MSG_ECHOLABEL, 0, 35, echoDist))
	{
		CProgress progress;
		if (theApp.m_pClient->SaveData(0x921, float(echoDist), 0,false))
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

void CFalseEchoDlgTU::OnBnClickedBtnDelete()
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
