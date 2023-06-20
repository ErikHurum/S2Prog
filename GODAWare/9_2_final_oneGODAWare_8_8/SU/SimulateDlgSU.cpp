// SimulateDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "SimulateDlgSU.h"


// CSimulateDlgSU

IMPLEMENT_DYNAMIC(CSimulateDlgSU, CCustomDialogEx)

CSimulateDlgSU::CSimulateDlgSU()
:m_bSim(false), m_bTest(false), m_bClose(false)
{


}

CSimulateDlgSU::~CSimulateDlgSU()
{
}


BEGIN_MESSAGE_MAP(CSimulateDlgSU, CCustomDialogEx)
	ON_BN_CLICKED(IDC_BTN_SIMULATE, &CSimulateDlgSU::OnBnClickedBtnSimulate)
	ON_CBN_SELCHANGE(IDC_COMBO_SIMUTYPE, &CSimulateDlgSU::OnCbnSelchangeComboSimutype)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSimulateDlgSU::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSimulateDlgSU::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_TEST, &CSimulateDlgSU::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_RELAYTEST, &CSimulateDlgSU::OnBnClickedBtnStartRelayTest)
	ON_CBN_SELCHANGE(IDC_COMBO_RELAY, &CSimulateDlgSU::OnCbnSelchangeComboRelay)
END_MESSAGE_MAP()



// CSimulateDlgSU 消息处理程序



void CSimulateDlgSU::DoDataExchange(CDataExchange* pDX)
{


	CCustomDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SIMUTYPE, m_comboSimuType);
	DDX_Control(pDX, IDC_EDIT_SIMUVALUE, m_editSimuValue);
	DDX_Control(pDX, IDC_EDIT_UNIT, m_editUnit);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_SIMULATE, m_btnSimulate);
	DDX_Control(pDX, IDC_BTN_TEST, m_btnTest);
	DDX_Control(pDX, IDC_BTN_RELAYTEST, m_btnStartRelayTest);
	DDX_Control(pDX, IDC_COMBO_RELAY, m_comboRelay);
	DDX_Control(pDX, IDC_COMBO_POINTNUMBER2, m_comboPointNumber);
}

void CSimulateDlgSU::OnBnClickedBtnSimulate()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bSim = !m_bSim;

	int pn = m_comboPointNumber.GetCurSel() + 1;

	if (m_bSim)
	{
		m_comboSimuType.EnableWindow(TRUE);
		m_editSimuValue.EnableWindow(TRUE);
		m_btnSave.EnableWindow(TRUE);

		OnCbnSelchangeComboSimutype();
		
		CString str;
		BOOL bNameValid = str.LoadString(IDS_STOPSIM);
		ASSERT(bNameValid);
		m_btnSimulate.SetWindowText(str);

	} 
	else
	{
		CArray<BYTE> byteArray;
		for (int i = 0; i < 6; i++)
		{
			byteArray.Add(BYTE(0));
		}
		if (theApp.m_pClient->SaveData(0x996, byteArray, pn, false))
		{
			m_comboSimuType.EnableWindow(FALSE);
			m_editSimuValue.EnableWindow(FALSE);
			m_btnSave.EnableWindow(FALSE);

			CString str;
			BOOL bNameValid = str.LoadString(IDS_STARTSIM);
			ASSERT(bNameValid);
			m_btnSimulate.SetWindowText(str);
		}


	}
}

void CSimulateDlgSU::OnCbnSelchangeComboSimutype()
{
	CString str;
	float floatData;
	CProgress progress;

	int pn = m_comboPointNumber.GetCurSel() + 1;
	
	switch(m_comboSimuType.GetCurSel())
	{
	case 0:
		m_editUnit.SetWindowText(_T("m"));
		
		theApp.m_pClient->LoadData(0x990, floatData, pn);
		str.Format(_T("%.3f"), floatData);
		m_editSimuValue.SetWindowText(str);
		break;
	case 1:
		m_editUnit.SetWindowText(_T("%"));

		theApp.m_pClient->LoadData(0x112, floatData, pn);
		str.Format(_T("%.3f"), floatData*100);
		m_editSimuValue.SetWindowText(str);
		break;
	case 2:
		m_editUnit.SetWindowText(_T("mA"));

		theApp.m_pClient->LoadData(0x913, floatData, pn);
		str.Format(_T("%.3f"), floatData);
		m_editSimuValue.SetWindowText(str);
		break;
	}
	RedrawWindow();
}

bool CSimulateDlgSU::TestRelay(bool close, int num)
{

	if(close)
	{
		UINT8 data = 1;
		return theApp.m_pClient->SaveData(0x941, data, num, false);
	}
	else
	{
		UINT8 data = 0;
		return theApp.m_pClient->SaveData(0x941, data, num, false);
	}

}

void CSimulateDlgSU::OnBnClickedBtnTest()
{
	CString str;
	m_bClose = !m_bClose;
	while(!TestRelay(m_bClose, m_relayNum));
	if(m_bClose)
	{
		str.LoadString(IDS_OPENRELAY);
		m_btnTest.SetWindowTextW(str);
	}
	else
	{
		str.LoadString(IDS_CLOSERELAY);
		m_btnTest.SetWindowTextW(str);
	}
}

void CSimulateDlgSU::OnBnClickedBtnStartRelayTest()
{
	CString str;
	if(!m_bTest)
	{
		if(theApp.m_pClient->SaveData(0x940, (UINT8)1,1, false))
		{
			m_bTest = !m_bTest;
			m_comboRelay.EnableWindow(TRUE);
			m_btnTest.EnableWindow(TRUE);
			str.LoadString(IDS_STOPRELAYTEST);
			m_btnStartRelayTest.SetWindowText(str);
		}
	}
	else
	{
		if(theApp.m_pClient->SaveData(0x940, (UINT8)0,1, false))
		{
			m_bTest = !m_bTest;
			m_comboRelay.EnableWindow(FALSE);
			m_btnTest.EnableWindow(FALSE);
			str.LoadString(IDS_STARTRELAYTEST);
			m_btnStartRelayTest.SetWindowText(str);
		}
	}
}

void CSimulateDlgSU::OnCbnSelchangeComboRelay()
{
	if(m_bClose)
	{
		OnBnClickedBtnTest();
	}
	m_relayNum = m_comboRelay.GetCurSel()+1;
}

void CSimulateDlgSU::OnBnClickedBtnSave()
{
	CProgress progress;

	while(!theApp.m_pClient->RefreshId());

	int pn = m_comboPointNumber.GetCurSel() + 1;
	
	CArray<BYTE> arrayData;
	BYTE b = 1;
	arrayData.Add(b);

	CString str;
	m_editSimuValue.GetWindowText(str);

	float simValue = static_cast<float>(_tstof(str));
	BYTE *pByte = reinterpret_cast<BYTE*>(&simValue);
	arrayData.Add(pByte[0]);
	arrayData.Add(pByte[1]);
	arrayData.Add(pByte[2]);
	arrayData.Add(pByte[3]);

	int simType = m_comboSimuType.GetCurSel();
	if (simType == 2)
	{
		simType = 3;
	}
	arrayData.Add(BYTE(simType));

	theApp.m_pClient->SaveData(0x996, arrayData, pn, false);
}

BOOL CSimulateDlgSU::OnInitDialog()
{
	CCustomDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_comboSimuType.SetCurSel(0);
	m_comboRelay.SetCurSel(0);
	m_comboPointNumber.SetCurSel(0);

	CString str;
	
	m_comboRelay.EnableWindow(FALSE);
	m_btnTest.EnableWindow(FALSE);
	str.LoadString(IDS_STARTRELAYTEST);
	m_btnStartRelayTest.SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
