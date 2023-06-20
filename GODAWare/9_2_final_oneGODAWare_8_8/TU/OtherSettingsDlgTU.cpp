// OtherSettingsDlgTU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "OtherSettingsDlgTU.h"


// COtherSettingsDlgTU

IMPLEMENT_DYNAMIC(COtherSettingsDlgTU, COperationDlg)

COtherSettingsDlgTU::COtherSettingsDlgTU()
{

}

COtherSettingsDlgTU::~COtherSettingsDlgTU()
{
}


BEGIN_MESSAGE_MAP(COtherSettingsDlgTU, COperationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, &COtherSettingsDlgTU::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

void COtherSettingsDlgTU::LoadData()
{

	CProgress progress;
	CArray<BYTE> strData;
	CString str;
	UINT8 intData;

	theApp.m_pClient->LoadData(0x11, strData);
	str = _T("");
	for (int i = 0; i < strData.GetSize(); i++)
	{
		str.AppendChar(strData[i]);
	}

	m_senserTag.SetWindowText(str);

	theApp.m_pClient->LoadData(0x4, intData);
	m_senserType.SetCurSel(intData-1);

	str.Format(_T("%d"), theApp.m_pClient->GetDeviceAddr());
	m_editAddress.SetWindowText(str);

}

void COtherSettingsDlgTU::SaveData()
{
	int intData;

	intData = m_senserType.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x4, UINT8(intData));

	switch(m_senserType.GetCurSel())
	{
	case 0:
		theApp.m_pClient->SaveData(0x800, 0.25f);
		break;
	case 1:
		theApp.m_pClient->SaveData(0x800, 0.3f);
		break;
	case 2:
		theApp.m_pClient->SaveData(0x800, 0.5f);
		break;
	}
}

// COtherSettingsDlgTU 消息处理程序



void COtherSettingsDlgTU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SENSERTAG, m_senserTag);
	DDX_Control(pDX, IDC_COMBO_SENSERTYPE, m_senserType);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_editAddress);
}

void COtherSettingsDlgTU::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
