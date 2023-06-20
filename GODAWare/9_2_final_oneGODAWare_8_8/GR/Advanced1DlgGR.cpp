// Advanced1DlgGR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "Advanced1DlgGR.h"
#include "../CalibrationDlg.h"


// CAdvanced1DlgGR

IMPLEMENT_DYNAMIC(CAdvanced1DlgGR, COperationDlg)

CAdvanced1DlgGR::CAdvanced1DlgGR()
{

}

CAdvanced1DlgGR::~CAdvanced1DlgGR()
{
}


BEGIN_MESSAGE_MAP(CAdvanced1DlgGR, COperationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_CALIBRATION, &CAdvanced1DlgGR::OnCbnSelchangeComboCalibration)
	ON_BN_CLICKED(IDC_BTN_CALIBRATE, &CAdvanced1DlgGR::OnBnClickedBtnCalibrate)
END_MESSAGE_MAP()

void CAdvanced1DlgGR::LoadData()
{
	CProgress progress;

	while(!(theApp.m_pClient->LoadData(0x999, ba)));
	UINT8 intData;
	theApp.m_pClient->LoadData(0x36, intData);
	m_checkEnableFlow.SetCheck(intData);

	theApp.m_pClient->LoadData(0x655, intData);	
	if (intData > 1)
	{
		m_checkCalibration.SetCurSel(ba[0] - 1);
	}
	else
	{
		m_checkCalibration.SetCurSel(0);
	}
	OnCbnSelchangeComboCalibration();

	//theApp.m_pClient->LoadData(0x656, intData);

}

void CAdvanced1DlgGR::SaveData()
{
	CProgress progress;
	int intData;
	intData = m_checkEnableFlow.GetCheck();
	theApp.m_pClient->SaveData(0x36, UINT8(intData));

	intData = m_checkCalibration.GetCurSel();

	if (intData != 0)
	{
		intData++;
	}
	theApp.m_pClient->SaveData(0x655, UINT8(intData));

}

// CAdvanced1DlgGR 消息处理程序



void CAdvanced1DlgGR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ENABLEFLOW, m_checkEnableFlow);
	DDX_Control(pDX, IDC_COMBO_CALIBRATION, m_checkCalibration);
}


void CAdvanced1DlgGR::OnCbnSelchangeComboCalibration()
{
	if (m_checkCalibration.GetCurSel() == 0)
	{
		GetDlgItem(IDC_BTN_CALIBRATE)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_BTN_CALIBRATE)->ShowWindow(SW_SHOW);
	}
	
}

void CAdvanced1DlgGR::OnBnClickedBtnCalibrate()
{
	CCalibrationDlg dlg;

	int caliNum = m_checkCalibration.GetCurSel();
	if (caliNum != 0)
		caliNum++;

	dlg.validPoint = caliNum;



	for (int i = 0; i < (ba.GetSize()-1)/8; i++)
	{
		dlg.m_measuredVal[i] = *(float*)(&(ba[i*4+1]));
	}

	for (int i = 0; i < (ba.GetSize()-1)/8; i++)
	{
		dlg.m_caliVal[i] = *(float*)(&(ba[i*4+ (ba.GetSize()-1)/2 +1]));
	}

	if (dlg.DoModal() == IDOK)
	{
		CProgress progress;
		CArray<BYTE> byteArray;

		byteArray.Add(BYTE(caliNum));
		for (int i = 0; i < caliNum; i++)
		{
			BYTE *p = reinterpret_cast<BYTE*>(&(dlg.m_measuredVal[i]));
			byteArray.Add(BYTE(p[0]));
			byteArray.Add(BYTE(p[1]));
			byteArray.Add(BYTE(p[2]));
			byteArray.Add(BYTE(p[3]));
		}
		for (int i = 0; i < caliNum; i++)
		{
			BYTE *p = reinterpret_cast<BYTE*>(&(dlg.m_caliVal[i]));
			byteArray.Add(BYTE(p[0]));
			byteArray.Add(BYTE(p[1]));
			byteArray.Add(BYTE(p[2]));
			byteArray.Add(BYTE(p[3]));
		}
		theApp.m_pClient->SaveData(0x999, byteArray);
	}
	else
	{
		LoadData();
	}
}
