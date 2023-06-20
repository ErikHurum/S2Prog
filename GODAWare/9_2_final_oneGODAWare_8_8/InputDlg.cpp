// InputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "InputDlg.h"


// CInputDlg 对话框

IMPLEMENT_DYNAMIC(CInputDlg, CDialog)

CInputDlg::CInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputDlg::IDD, pParent), m_range(false)
{

}

CInputDlg::CInputDlg( double low, double high, CWnd* pParent /*= NULL*/ )
	: CDialog(CInputDlg::IDD, pParent), m_low(low), m_high(high), m_range(true)
{

}
CInputDlg::~CInputDlg()
{
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL, m_label);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_value);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CInputDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInputDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CInputDlg 消息处理程序

void CInputDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_value.GetWindowText(m_strValue);
	
	double d = _tstof(m_strValue);
	if (m_range)
	{
		if (m_low < d && m_high >d)
		{
			m_dbValue = d;
			OnOK();
		}
		else
		{
			CString str;
			BOOL b = str.LoadString(IDS_MSG_ILLEGALNUM);
			ASSERT(b);
			CString msg;
			msg.Format(str, m_low, m_high);
			AfxMessageBox(msg, MB_OK | MB_ICONSTOP);
		}
	}
	else
	{
		m_dbValue = d;
		OnOK();
	}

}

void CInputDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

BOOL CInputDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_label.SetWindowText(m_labelText);
	m_value.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
