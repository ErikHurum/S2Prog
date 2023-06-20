// DeviceStatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "DeviceStatDlg.h"


// CDeviceStatDlg

IMPLEMENT_DYNAMIC(CDeviceStatDlg, CCustomDialogEx)

CDeviceStatDlg::CDeviceStatDlg()
{
	
}

CDeviceStatDlg::~CDeviceStatDlg()
{
}


BEGIN_MESSAGE_MAP(CDeviceStatDlg, CCustomDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CDeviceStatDlg 消息处理程序



void CDeviceStatDlg::DoDataExchange(CDataExchange* pDX)
{


	CCustomDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STAT, m_stat);
	DDX_Control(pDX, IDC_EDIT_NULLHIGHT, m_hight);
}

BOOL CDeviceStatDlg::OnInitDialog()
{
	CCustomDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetOnline(false);
	SetNullHight(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDeviceStatDlg::SetOnline( bool bOnline )
{
	m_bOnline = bOnline;
	if (bOnline)
	{
		CString str;
		BOOL bNameValid = str.LoadString(IDS_ONLINE);
		ASSERT(bNameValid);		
		m_stat.SetWindowText(str);
	}
	else 
	{
		CString str;
		BOOL bNameValid = str.LoadString(IDS_OFFLINE);
		ASSERT(bNameValid);		
		m_stat.SetWindowText(str);
	}
}

void CDeviceStatDlg::SetNullHight( double hight )
{
	CString str;
	str.Format(_T("%.3f m"), hight);
	m_hight.SetWindowText(str);
}
HBRUSH CDeviceStatDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
