// DiagnosisDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "DiagnosisDlgSU.h"


// CDiagnosisDlgSU

IMPLEMENT_DYNAMIC(CDiagnosisDlgSU, COperationDlg)

CDiagnosisDlgSU::CDiagnosisDlgSU()
{
	CString str;
	str.LoadString(IDS_DEVSTAT0);
	m_deviceStat.Add(str);
	str.LoadString(IDS_DEVSTAT1);
	m_deviceStat.Add(str);
	str.LoadString(IDS_DEVSTAT2);
	m_deviceStat.Add(str);
	str.LoadString(IDS_DEVSTAT3);
	m_deviceStat.Add(str);
	str.LoadString(IDS_DEVSTAT4);
	m_deviceStat.Add(str);
	str.LoadString(IDS_DEVSTAT5);
	m_deviceStat.Add(str);
	str.LoadString(IDS_DEVSTAT6);
	m_deviceStat.Add(str);
	str.LoadString(IDS_DEVSTAT7);
	m_deviceStat.Add(str);
}

CDiagnosisDlgSU::~CDiagnosisDlgSU()
{
}


BEGIN_MESSAGE_MAP(CDiagnosisDlgSU, COperationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_POINTNUMBER, &CDiagnosisDlgSU::OnCbnSelchangeComboPointnumber)
END_MESSAGE_MAP()

void CDiagnosisDlgSU::LoadData()
{
	CProgress progress;

	int pn = m_comboPointNumber.GetCurSel()+1;

	CString str;
	float floatData;

	theApp.m_pClient->LoadData(0x912, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_temperature.SetWindowText(str);

	theApp.m_pClient->LoadData(0x913, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_current.SetWindowText(str);

	theApp.m_pClient->LoadData(0x14, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_min.SetWindowText(str);

	theApp.m_pClient->LoadData(0x15, floatData, pn);
	str.Format(_T("%.3f"), floatData);
	m_max.SetWindowText(str);

	m_statList.ResetContent();

	UINT8 displayValue, deviceStat;

	theApp.m_pClient->LoadData(0x1, displayValue, pn);
	theApp.m_pClient->LoadData(0x70, deviceStat, pn);
	if (displayValue == 0)
	{
		CString str;
		str.LoadString(IDS_SENSORDONOTHING);
		m_statList.AddString(str);
	}
	else
	{
		if (deviceStat == 0)
		{
			CString str;
			str.LoadString(IDS_SENSOROK);
			m_statList.AddString(str);
		} 
		else
		{
			for(int i = 0; i < 8; i++)
			{
				if((deviceStat >>i) & 1)
				{
					m_statList.AddString(m_deviceStat[i]);
				}
			}
		}
	}

}

void CDiagnosisDlgSU::SaveData()
{
	//CString str;
	//double dbData;

	//m_temperature.GetWindowText(str);
	//dbData = _tstof(str);
	//theApp.m_pClient->SaveData(0x912, float(dbData));

	//m_current.GetWindowText(str);
	//dbData = _tstof(str);
	//theApp.m_pClient->SaveData(0x913, float(dbData));

	//m_min.GetWindowText(str);
	//dbData = _tstof(str);
	//theApp.m_pClient->SaveData(0x14, float(dbData));

	//m_max.GetWindowText(str);
	//dbData = _tstof(str);
	//theApp.m_pClient->SaveData(0x15, float(dbData));
}

// CDiagnosisDlgSU 消息处理程序



void CDiagnosisDlgSU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EDIT_MIN, m_min);
	DDX_Control(pDX, IDC_EDIT_MAX, m_max);
	DDX_Control(pDX, IDC_EDIT_TEMPERATURE, m_temperature);
	DDX_Control(pDX, IDC_EDIT_CURRENT, m_current);
	DDX_Control(pDX, IDC_LIST_DEVSTAT, m_statList);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER, m_comboPointNumber);
}

void CDiagnosisDlgSU::OnCbnSelchangeComboPointnumber()
{
	LoadData();
}
