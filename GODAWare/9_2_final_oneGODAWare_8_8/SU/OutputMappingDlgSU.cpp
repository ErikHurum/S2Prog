// OutputMappingDlgSU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "OutputMappingDlgSU.h"


// COutputMappingDlgSU

IMPLEMENT_DYNAMIC(COutputMappingDlgSU, CCustomDialogEx)

COutputMappingDlgSU::COutputMappingDlgSU()
{

}

COutputMappingDlgSU::~COutputMappingDlgSU()
{
}


BEGIN_MESSAGE_MAP(COutputMappingDlgSU, CCustomDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_LOAD, &COutputMappingDlgSU::OnBnClickedBtnLoad)
END_MESSAGE_MAP()


// COutputMappingDlgSU 消息处理程序



int COutputMappingDlgSU::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CCustomDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
 
	return 0;
}


void COutputMappingDlgSU::OnSize(UINT nType, int cx, int cy)
{
	CCustomDialogEx::OnSize(nType, cx, cy);

	const int REGION = 25; //调节距离窗口边的距离

	if (::IsWindow(m_mapping))
	{
		CRect rect;
		GetClientRect(&rect);
		m_mapping.SetWindowPos (NULL, 0, 0, cx - REGION , cy - REGION, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void COutputMappingDlgSU::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAPPING, m_mapping);
}
BOOL COutputMappingDlgSU::OnInitDialog()
{
	CCustomDialogEx::OnInitDialog();

	CString str;
	BOOL bNameValid;

	bNameValid = str.LoadString(IDS_PERCENT);
	ASSERT(bNameValid);
	m_mapping.InsertColumn(0,str,LVCFMT_CENTER,100);

	bNameValid = str.LoadString(IDS_MAPPINGPERCENT);
	ASSERT(bNameValid);
	m_mapping.InsertColumn(1,str,LVCFMT_CENTER,100);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void COutputMappingDlgSU::OnBnClickedBtnLoad()
{
	if (!theApp.m_pClient->IsOnline())
	{
		return;
	}

	CProgress progress;
	CString str1, str2;
	CArray<float> arrayData;

	theApp.m_pClient->LoadData(0x994, arrayData,1);
	ASSERT(arrayData.GetSize() == 66);

	//float lowPercent, low, highPercent, high, val0, val100;

	//theApp.m_pClient->LoadData(0x110, lowPercent);
	//theApp.m_pClient->LoadData(0x111, low);
	//theApp.m_pClient->LoadData(0x112, highPercent);
	//theApp.m_pClient->LoadData(0x113, high);
	//theApp.m_pClient->LoadData(0x114, val0);
	//theApp.m_pClient->LoadData(0x115, val100);

	//double hightRatio = (low - high) / (highPercent - lowPercent);
	//double valRatio = val100 - val0;

	m_mapping.DeleteAllItems();
	if (arrayData.GetSize() == 66)
	{
		for (int i = 0; i < 33; i++)
		{
			str1.Format(_T("%.3f%%"), arrayData[i]*100);
			str2.Format(_T("%.3f%%"), arrayData[i+33]*100);

			m_mapping.InsertItem(i, _T(""));
			m_mapping.SetItemText(i, 0, str1);
			m_mapping.SetItemText(i, 1, str2);
		}
	}
}
