// PinDlgTU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "PinDlgTU.h"


// CPinDlgTU

IMPLEMENT_DYNAMIC(CPinDlgTU, COperationDlg)

CPinDlgTU::CPinDlgTU()
{

}

CPinDlgTU::~CPinDlgTU()
{
}


BEGIN_MESSAGE_MAP(CPinDlgTU, COperationDlg)
	ON_BN_CLICKED(IDC_BTN_NEW, &CPinDlgTU::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_DEL, &CPinDlgTU::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_UPDATE, &CPinDlgTU::OnBnClickedBtnUpdate)
END_MESSAGE_MAP()

void CPinDlgTU::LoadData()
{
	CProgress progress;
	UINT8 intData;
	theApp.m_pClient->LoadData(0x40, intData);
	if (intData != 0)
	{
		GetDlgItem(IDC_BTN_NEW)->EnableWindow(false);
		GetDlgItem(IDC_BTN_DEL)->EnableWindow(true);
		GetDlgItem(IDC_BTN_UPDATE)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_BTN_NEW)->EnableWindow(true);
		GetDlgItem(IDC_BTN_DEL)->EnableWindow(false);
		GetDlgItem(IDC_BTN_UPDATE)->EnableWindow(false);
	}
}

void CPinDlgTU::SaveData()
{

}

// CPinDlgTU 消息处理程序



void CPinDlgTU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
}

void CPinDlgTU::OnBnClickedBtnNew()
{
	int pw1, pw2;
	if (GetNumMessageBox(IDS_MSG_INPUTPW, 0, 65535, pw1) == IDOK)
	{
		if (GetNumMessageBox(IDS_MSG_CONFIRMPW, 0, 65535, pw2) == IDOK)
		{
			if (pw1 == pw2)
			{
				CProgress progress;
				theApp.m_pClient->SaveData(0x40, UINT8(1));
				theApp.m_pClient->SaveData(0x41, INT16(pw1));

				GetDlgItem(IDC_BTN_NEW)->EnableWindow(false);
				GetDlgItem(IDC_BTN_DEL)->EnableWindow(true);
				GetDlgItem(IDC_BTN_UPDATE)->EnableWindow(true);
			}
			else
			{
				WarnMessageBox(IDS_MSG_CONFIRMERR);
			}
		}
	}
}

void CPinDlgTU::OnBnClickedBtnDel()
{
	int oldPw;

	if (GetNumMessageBox(IDS_MSG_INPUTORGPW, oldPw) == IDOK)
	{
		
		INT16 intData;
		theApp.m_pClient->LoadData(0x41, intData);

		if (intData == oldPw)
		{
			CProgress progress;
			theApp.m_pClient->SaveData(0x40, UINT8(0));

			GetDlgItem(IDC_BTN_NEW)->EnableWindow(true);
			GetDlgItem(IDC_BTN_DEL)->EnableWindow(false);
			GetDlgItem(IDC_BTN_UPDATE)->EnableWindow(false);
		}
		else
		{
			WarnMessageBox(IDS_MSG_PWERR);
		}
	}
}

void CPinDlgTU::OnBnClickedBtnUpdate()
{
	int oldPw;

	if (GetNumMessageBox(IDS_MSG_INPUTORGPW, oldPw) == IDOK)
	{
		//CProgress progress;
		INT16 intData;
		theApp.m_pClient->LoadData(0x41, intData);

		if (intData == oldPw)
		{
			OnBnClickedBtnNew();
		}
		else
		{
			WarnMessageBox(IDS_MSG_PWERR);
		}
	}
}
