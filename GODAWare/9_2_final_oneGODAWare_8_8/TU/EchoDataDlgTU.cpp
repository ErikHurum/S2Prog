// EchoDataDlgTU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "EchoDataDlgTU.h"


// CEchoDataDlgTU

IMPLEMENT_DYNAMIC(CEchoDataDlgTU, CCustomDialogEx)

CEchoDataDlgTU::CEchoDataDlgTU()
{

}

CEchoDataDlgTU::~CEchoDataDlgTU()
{
}


BEGIN_MESSAGE_MAP(CEchoDataDlgTU, CCustomDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_LOAD, &CEchoDataDlgTU::OnBnClickedBtnLoad)
END_MESSAGE_MAP()



// CEchoDataDlgTU 消息处理程序



void CEchoDataDlgTU::DoDataExchange(CDataExchange* pDX)
{

	CCustomDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ECHODATA, m_echoData);
}

BOOL CEchoDataDlgTU::OnInitDialog()
{
	CCustomDialogEx::OnInitDialog();

	CString str;
	BOOL bNameValid;

	bNameValid = str.LoadString(IDS_ECHODATA_NUMBER);
	ASSERT(bNameValid);
	m_echoData.InsertColumn(0,str,LVCFMT_CENTER,100);

	bNameValid = str.LoadString(IDS_ECHODATA_DISTANCE);
	ASSERT(bNameValid);
	m_echoData.InsertColumn(1,str,LVCFMT_CENTER,100);

	bNameValid = str.LoadString(IDS_ECHODATA_AMPLITUDE);
	ASSERT(bNameValid);
	m_echoData.InsertColumn(2,str,LVCFMT_CENTER,100);

	bNameValid = str.LoadString(IDS_ECHODATA_WIDTH);
	ASSERT(bNameValid);
	m_echoData.InsertColumn(3,str,LVCFMT_CENTER,100);

	bNameValid = str.LoadString(IDS_ECHODATA_POSSIBILITY);
	ASSERT(bNameValid);
	m_echoData.InsertColumn(4,str,LVCFMT_CENTER,100);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CEchoDataDlgTU::OnSize(UINT nType, int cx, int cy)
{
	CCustomDialogEx::OnSize(nType, cx, cy);

	const int REGION = 25; //调节距离窗口边的距离

	if (::IsWindow(m_echoData))
	{
		CRect rect;
		GetClientRect(&rect);
		m_echoData.SetWindowPos (NULL, 0, 20, cx - REGION , cy - 20 - REGION, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CEchoDataDlgTU::OnBnClickedBtnLoad()
{
	CProgress progress;
	CArray<float> floatArray;
	theApp.m_pClient->LoadData(0x995, floatArray);
	
	m_echoData.DeleteAllItems();
	

	for (int i = 0; i < floatArray.GetSize(); i += 4)
	{
		CString str;
		str.Format(_T("%d"), i/4);
		m_echoData.InsertItem(i/4, str);
		
		str.Format(_T("%2.3f"), floatArray[i]);
		m_echoData.SetItemText( i/4, 1, str);							
		str.Format(_T("%2.3f"), (floatArray[i + 1]/2047)*120);
		m_echoData.SetItemText(	i/4, 2, str);							
		str.Format(_T("%2.3f"), floatArray[i + 2]);
		m_echoData.SetItemText( i/4, 3, str);							
		str.Format(_T("%2.3f"), floatArray[i + 3]*100.0);
		m_echoData.SetItemText( i/4, 4, str);
	}
}
