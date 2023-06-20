// DiagnosisDlgPR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "DiagnosisDlgPR.h"


// CDiagnosisDlgPR

IMPLEMENT_DYNAMIC(CDiagnosisDlgPR, COperationDlg)

CDiagnosisDlgPR::CDiagnosisDlgPR()
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

CDiagnosisDlgPR::~CDiagnosisDlgPR()
{
}


BEGIN_MESSAGE_MAP(CDiagnosisDlgPR, COperationDlg)
END_MESSAGE_MAP()

void CDiagnosisDlgPR::LoadData()
{
	CProgress progress;
	CString str;
	float floatData;

	theApp.m_pClient->LoadData(0x912, floatData);
	str.Format(_T("%.3f"), floatData);
	m_temperature.SetWindowText(str);

	theApp.m_pClient->LoadData(0x913, floatData);
	str.Format(_T("%.3f"), floatData);
	m_current.SetWindowText(str);

	theApp.m_pClient->LoadData(0x14, floatData);
	str.Format(_T("%.3f"), floatData);
	m_min.SetWindowText(str);

	theApp.m_pClient->LoadData(0x15, floatData);
	str.Format(_T("%.3f"), floatData);
	m_max.SetWindowText(str);

	m_statList.ResetContent();

	UINT8 displayValue, deviceStat;

	theApp.m_pClient->LoadData(0x1, displayValue);
	theApp.m_pClient->LoadData(0x70, deviceStat);
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

void CDiagnosisDlgPR::SaveData()
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

// CDiagnosisDlgPR 消息处理程序



void CDiagnosisDlgPR::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EDIT_MIN, m_min);
	DDX_Control(pDX, IDC_EDIT_MAX, m_max);
	DDX_Control(pDX, IDC_EDIT_TEMPERATURE, m_temperature);
	DDX_Control(pDX, IDC_EDIT_CURRENT, m_current);
	DDX_Control(pDX, IDC_LIST_DEVSTAT, m_statList);
}
