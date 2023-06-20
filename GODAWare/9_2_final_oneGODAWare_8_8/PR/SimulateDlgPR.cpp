// SimulateDlgPR.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../MFC.h"
#include "SimulateDlgPR.h"


// CSimulateDlgPR

IMPLEMENT_DYNAMIC(CSimulateDlgPR, CCustomDialogEx)

CSimulateDlgPR::CSimulateDlgPR()
:m_bSim(false)
{

}

CSimulateDlgPR::~CSimulateDlgPR()
{
}


BEGIN_MESSAGE_MAP(CSimulateDlgPR, CCustomDialogEx)
	ON_BN_CLICKED(IDC_BTN_SIMULATE, &CSimulateDlgPR::OnBnClickedBtnSimulate)
	ON_CBN_SELCHANGE(IDC_COMBO_SIMUTYPE, &CSimulateDlgPR::OnCbnSelchangeComboSimutype)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSimulateDlgPR::OnBnClickedBtnSave)
END_MESSAGE_MAP()



// CSimulateDlgPR ��Ϣ�������



void CSimulateDlgPR::DoDataExchange(CDataExchange* pDX)
{


	CCustomDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SIMUTYPE, m_comboSimuType);
	DDX_Control(pDX, IDC_EDIT_SIMUVALUE, m_editSimuValue);
	DDX_Control(pDX, IDC_EDIT_UNIT, m_editUnit);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BTN_SIMULATE, m_btnSimulate);
}

void CSimulateDlgPR::OnBnClickedBtnSimulate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bSim = !m_bSim;
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
		if (theApp.m_pClient->SaveData(0x996, byteArray))
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

void CSimulateDlgPR::OnCbnSelchangeComboSimutype()
{
	CString str;
	float floatData;
	CProgress progress;
	
	switch(m_comboSimuType.GetCurSel())
	{
	case 0:
		m_editUnit.SetWindowText(_T("m"));
		
		theApp.m_pClient->LoadData(0x990, floatData);
		str.Format(_T("%.3f"), floatData);
		m_editSimuValue.SetWindowText(str);
		break;
	case 1:
		m_editUnit.SetWindowText(_T("%"));

		theApp.m_pClient->LoadData(0x112, floatData);
		str.Format(_T("%.3f"), floatData*100);
		m_editSimuValue.SetWindowText(str);
		break;
	case 2:
		m_editUnit.SetWindowText(_T("mA"));

		theApp.m_pClient->LoadData(0x913, floatData);
		str.Format(_T("%.3f"), floatData);
		m_editSimuValue.SetWindowText(str);
		break;
	}
	RedrawWindow();
}

void CSimulateDlgPR::OnBnClickedBtnSave()
{
	CProgress progress;
	//while(!theApp.m_pClient->RefreshId());
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

	theApp.m_pClient->SaveData(0x996, arrayData);
}

BOOL CSimulateDlgPR::OnInitDialog()
{
	CCustomDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_comboSimuType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
