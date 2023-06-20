// ServiceOtherDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "ServiceOtherDlgSU.h"


// CServiceOtherDlgSU

IMPLEMENT_DYNAMIC(CServiceOtherDlgSU, COperationDlg)

CServiceOtherDlgSU::CServiceOtherDlgSU()
{

}

CServiceOtherDlgSU::~CServiceOtherDlgSU()
{
}


BEGIN_MESSAGE_MAP(CServiceOtherDlgSU, COperationDlg)
	ON_BN_CLICKED(IDC_BUTTON1, &CServiceOtherDlgSU::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CServiceOtherDlgSU::OnBnClickedButton6)
END_MESSAGE_MAP()

void CServiceOtherDlgSU::LoadData()
{
	CProgress progress;
	UINT8 intData;

	theApp.m_pClient->LoadData(0x5, intData);
	m_unit.SetCurSel(intData - 1);

	theApp.m_pClient->LoadData(0x30, intData);
	m_language.SetCurSel(intData - 1);
}

void CServiceOtherDlgSU::SaveData()
{
	int intData;

	intData = m_unit.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x5, UINT8(intData));

	intData = m_language.GetCurSel() + 1;
	theApp.m_pClient->SaveData(0x30, UINT8(intData));
}

// CServiceOtherDlgSU 消息处理程序



void CServiceOtherDlgSU::DoDataExchange(CDataExchange* pDX)
{


	COperationDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LANGUAGE, m_language);
	DDX_Control(pDX, IDC_COMBO_UNIT, m_unit);
}

void CServiceOtherDlgSU::OnBnClickedButton1()
{
	CFileDialog fileDlg(FALSE, _T(".sen"),0 ,4|2 ,_T("Sensor Data Files (*.sen)|*.sen|"),this);
	if (fileDlg.DoModal() == IDOK)
	{
		CString filename(fileDlg.GetPathName());
		CFile file;
		if (file.Open(filename, CFile::modeWrite | CFile::modeCreate | CFile::typeBinary))
		{
			CProgress progress;
			CArray<BYTE> arrayData;
			theApp.m_pClient->LoadData(0x950, arrayData);
			file.Write(&arrayData[0], arrayData.GetCount());
		}
	}
}

void CServiceOtherDlgSU::OnBnClickedButton6()
{
	CFileDialog fileDlg(TRUE, _T(".sen"),0 ,4|2 ,_T("Sensor Data Files (*.sen)|*.sen|"),this);
	if (fileDlg.DoModal() == IDOK)
	{
		CString filename(fileDlg.GetPathName());
		CFile file;
		if (file.Open(filename, CFile::modeRead | CFile::typeBinary))
		{
			CProgress progress;
			CArray<BYTE> arrayData;
			BYTE buf;
			for (int i=0; i<file.GetLength(); i++)
			{
				file.Read(&buf, 1);
				arrayData.Add(buf);
			}
			theApp.m_pClient->SaveData(0x950, arrayData);
		}
	}
}
