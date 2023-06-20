// FalseEchoDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "FalseEchoDlgSU.h"


// CFalseEchoDlgSU

IMPLEMENT_DYNAMIC(CFalseEchoDlgSU, COperationDlg)

CFalseEchoDlgSU::CFalseEchoDlgSU()
{

}

CFalseEchoDlgSU::~CFalseEchoDlgSU()
{
}


BEGIN_MESSAGE_MAP(CFalseEchoDlgSU, COperationDlg)
	ON_BN_CLICKED(IDC_BTN_NEW, &CFalseEchoDlgSU::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_UPDATE, &CFalseEchoDlgSU::OnBnClickedBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CFalseEchoDlgSU::OnBnClickedBtnDelete)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &CFalseEchoDlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()

void CFalseEchoDlgSU::LoadData()
{
	//theApp.m_pClient->SetDeviceNum(m_comboPointNumber.GetCurSel());
}

void CFalseEchoDlgSU::SaveData()
{

}

// CFalseEchoDlgSU 消息处理程序



void CFalseEchoDlgSU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
}

void CFalseEchoDlgSU::OnBnClickedBtnNew()
{
	double echoDist;
	if (GetNumMessageBox(IDS_MSG_ECHOLABEL, 0, 35, echoDist))
	{
		CProgress progress;
		int pn = m_comboPointNumber.GetCurSel();
		if (theApp.m_pClient->SaveData(0x922, float(echoDist), pn, false))
		{
			Sleep(5000);
			//UINT8 learning = 1;
			//while(learning == 1)
			//{
			//	Sleep(5000);
			//	theApp.m_pClient->LoadData(0x922, learning);
			//	theApp.m_pClient->SetVarInvalid(0x922);
			//}
			InfoMessageBox(IDS_SAVEOK);
		}
	}
}

void CFalseEchoDlgSU::OnBnClickedBtnUpdate()
{
	double echoDist;
	if (GetNumMessageBox(IDS_MSG_ECHOLABEL, 0, 35, echoDist))
	{
		CProgress progress;
		int pn = m_comboPointNumber.GetCurSel();
		if (theApp.m_pClient->SaveData(0x921, float(echoDist), pn, false))
		{
			Sleep(5000);	
			//UINT8 learning = 1;
			//while(learning == 1)
			//{
			//	Sleep(5000);
			//	theApp.m_pClient->LoadData(0x922, learning);
			//	theApp.m_pClient->SetVarInvalid(0x922);
			//}
			InfoMessageBox(IDS_SAVEOK);
		}
	}
}

void CFalseEchoDlgSU::OnBnClickedBtnDelete()
{
	double echoDist = 0;
	CProgress progress;
	int pn = m_comboPointNumber.GetCurSel();
	if (theApp.m_pClient->SaveData(0x920, float(echoDist), pn,false))
	{
		Sleep(5000);
		//UINT8 learning = 1;
		//while(learning == 1)
		//{
		//	Sleep(5000);
		//	theApp.m_pClient->LoadData(0x922, learning);
		//	theApp.m_pClient->SetVarInvalid(0x922);
		//}
		InfoMessageBox(IDS_SAVEOK);
	}
}

void CFalseEchoDlgSU::OnCbnSelchangeComboPointnumber()
{
	LoadData();
}
