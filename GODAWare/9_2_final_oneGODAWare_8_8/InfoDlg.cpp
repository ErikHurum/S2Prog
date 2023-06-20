// ApplicationDlgPR.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "InfoDlg.h"


// CInfoDlg

IMPLEMENT_DYNAMIC(CInfoDlg, COperationDlg)

CInfoDlg::CInfoDlg()

{

}

CInfoDlg::~CInfoDlg()
{
}


BEGIN_MESSAGE_MAP(CInfoDlg, COperationDlg)

END_MESSAGE_MAP()



// CInfoDlg 消息处理程序

void ByteArrayToCString(const CArray<BYTE>& byteArray, CString& str)
{
	str = _T("");
	for (int i = 0; i < byteArray.GetSize(); i++)
	{
		str.AppendChar(byteArray[i]);
	}
}

void CStringToByteArray(CString& str, CArray<BYTE>& byteArray)
{
	byteArray.RemoveAll();
	for (int i = 0; i < str.GetLength(); i++)
	{
		byteArray.Add((char)str[i]);
	}
	byteArray.Add(BYTE(0));
}


void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{



	COperationDlg::DoDataExchange(pDX);

}

void CInfoDlg::LoadData()
{
	CProgress progress;

	CArray<BYTE> strData;
	CString str;
	theApp.m_pClient->LoadData(0x50, strData);	
	ByteArrayToCString(strData, str);
	lastDeviceType = str;
	GetDlgItem(IDC_EDIT_DEVICETYPE)->SetWindowTextW(str);

	theApp.m_pClient->LoadData(0x51, strData);	
	ByteArrayToCString(strData, str);
	lastSerialNum = str;
	GetDlgItem(IDC_EDIT_SERIALNUM)->SetWindowTextW(str);

	theApp.m_pClient->LoadData(0x52, strData);	
	ByteArrayToCString(strData, str);
	lastDate = str;
	GetDlgItem(IDC_EDIT_DATE)->SetWindowTextW(str);

	theApp.m_pClient->LoadData(0x53, strData);	
	ByteArrayToCString(strData, str);
	GetDlgItem(IDC_EDIT_VERSION)->SetWindowTextW(str);
}

void CInfoDlg::SaveData()
{
	CProgress progress;
	
	CArray<BYTE> strData;
	CString str;

	
	GetDlgItem(IDC_EDIT_DEVICETYPE)->GetWindowText(str);

	if (str != lastDeviceType)
	{
	
		CStringToByteArray(str, strData);
		theApp.m_pClient->SaveData(0x50, strData);
	}

	GetDlgItem(IDC_EDIT_SERIALNUM)->GetWindowText(str);
	if (str != lastSerialNum)
	{

		CStringToByteArray(str, strData);
		theApp.m_pClient->SaveData(0x51, strData);
		theApp.m_pClient->RefreshId();

	}

	GetDlgItem(IDC_EDIT_DATE)->GetWindowText(str);

	if (str != lastDate)
	{
		CStringToByteArray(str, strData);
		theApp.m_pClient->SaveData(0x52, strData);
	}

}

