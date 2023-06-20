// OtherSettingsDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "OtherSettingsDlgSU.h"


// COtherSettingsDlgSU

IMPLEMENT_DYNAMIC(COtherSettingsDlgSU, COperationDlg)

COtherSettingsDlgSU::COtherSettingsDlgSU()
{

}

COtherSettingsDlgSU::~COtherSettingsDlgSU()
{
}


BEGIN_MESSAGE_MAP(COtherSettingsDlgSU, COperationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, &COtherSettingsDlgSU::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &COtherSettingsDlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()

void COtherSettingsDlgSU::LoadData()
{

	CProgress progress;


	int pn = m_comboPointNumber.GetCurSel();

	CArray<BYTE> strData;
	CString str;
	UINT8 intData;

	theApp.m_pClient->LoadData(0x11, strData, pn);
	str = _T("");
	for (int i = 0; i < strData.GetSize(); i++)
	{
		str.AppendChar(strData[i]);
	}

	m_senserTag.SetWindowText(str);

	theApp.m_pClient->LoadData(0x4, intData, pn);
	m_senserType.SetCurSel(intData-1);

	str.Format(_T("%d"), theApp.m_pClient->GetDeviceAddr());
	m_editAddress.SetWindowText(str);

	float floatData;
	CString s;
	theApp.m_pClient->LoadData(0x800, floatData, pn);
	s.Format(_T("%.3f"), floatData);
	this->m_editBlendArea.SetWindowTextW(s);

	theApp.m_pClient->LoadData(0x3, intData, pn);
	s.Format(_T("%.3f"), floatData);
	this->m_editChangeDistrict.SetWindowTextW(s);

}

void COtherSettingsDlgSU::SaveData()
{
	int intData;
	int pn = m_comboPointNumber.GetCurSel();
	intData = m_senserType.GetCurSel()+1;
	theApp.m_pClient->SaveData(0x4, UINT8(intData), pn);
}

// COtherSettingsDlgSU 消息处理程序



void COtherSettingsDlgSU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SENSERTAG, m_senserTag);
	DDX_Control(pDX, IDC_COMBO_SENSERTYPE, m_senserType);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_editAddress);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
	DDX_Control(pDX, IDC_EDIT_CHANGEDISTRICT, m_editChangeDistrict);
	DDX_Control(pDX, IDC_EDIT_BLENDAREA, m_editBlendArea);
	DDX_Control(pDX, IDC_EDIT_ECHORANGE, m_editEchoRange);
	DDX_Control(pDX, IDC_EDIT_TGC1, m_editTGC1);
}

void COtherSettingsDlgSU::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void COtherSettingsDlgSU::OnCbnSelchangeComboPointnumber()
{
	LoadData();
}
