// DeviceStatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "DeviceStatDlgSU.h"


// CDeviceStatDlgSU

IMPLEMENT_DYNAMIC(CDeviceStatDlgSU, CCustomDialogEx)

CDeviceStatDlgSU::CDeviceStatDlgSU()
{
	
}

CDeviceStatDlgSU::~CDeviceStatDlgSU()
{
}


BEGIN_MESSAGE_MAP(CDeviceStatDlgSU, CCustomDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CDeviceStatDlgSU 消息处理程序



void CDeviceStatDlgSU::DoDataExchange(CDataExchange* pDX)
{


	CCustomDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STAT, m_stat);
	DDX_Control(pDX, IDC_EDIT_NULLHIGHT1, m_hight[0]);
	DDX_Control(pDX, IDC_EDIT_NULLHIGHT2, m_hight[1]);
	DDX_Control(pDX, IDC_EDIT_NULLHIGHT3, m_hight[2]);

}

BOOL CDeviceStatDlgSU::OnInitDialog()
{
	CCustomDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetOnline(false);
	SetNullHight(0, 1);
	SetNullHight(0, 2);
	SetNullHight(0, 3);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDeviceStatDlgSU::SetOnline( bool bOnline )
{
	m_bOnline = bOnline;
	if (bOnline)
	{
		CString str;
		BOOL bNameValid = str.LoadString(IDS_ONLINE);
		ASSERT(bNameValid);	
		if (::IsWindow(m_stat.m_hWnd))
		{
			m_stat.SetWindowText(str);
		}
	}
	else 
	{
		CString str;
		BOOL bNameValid = str.LoadString(IDS_OFFLINE);
		ASSERT(bNameValid);	
		if (::IsWindow(m_stat.m_hWnd))
		{
			m_stat.SetWindowText(str);
		}
	}
}

void CDeviceStatDlgSU::SetNullHight( double hight, size_t index )
{
	if (index < 1 || index > 3)
	{
		return;
	}
	CString str;
	str.Format(_T("%.3f m"), hight);
	m_hight[index - 1].SetWindowText(str);
}
HBRUSH CDeviceStatDlgSU::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CCustomDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	if (pWnd == GetDlgItem(IDC_EDIT_STAT))
	{
		if (m_bOnline)
		{
			pDC->SetTextColor(RGB(80,180,80));
		} 
		else
		{
			pDC->SetTextColor(RGB(255,0,0));
		}
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
