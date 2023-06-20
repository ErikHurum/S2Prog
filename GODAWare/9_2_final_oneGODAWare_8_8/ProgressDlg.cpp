// ProgressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC.h"
#include "ProgressDlg.h"

extern CEvent progressThreadOK;
// CProgressDlg �Ի���

IMPLEMENT_DYNAMIC(CProgressDlg, CDialog)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, m_flash);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CProgressDlg ��Ϣ�������

BOOL CProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetEvent(progressThreadOK);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	TCHAR strCurDrt[500];
	int nLen = ::GetCurrentDirectory(500,strCurDrt);
	if( strCurDrt[nLen]!='\\' )
	{
		strCurDrt[nLen++] = '\\';
		strCurDrt[nLen] = '\0';
	}

	CString strFileName = strCurDrt;
	strFileName += _T("ConnectProgress.swf"); //����Ϊ��ľ���·��


	m_flash.LoadMovie(0, strFileName);
	SetTimer(1, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CProgressDlg::PlayFlash()
{
	//m_flash.Play();
}
void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnTimer(nIDEvent);
}


void CProgressDlg::OnOK()
{

}


void CProgressDlg::OnCancel()
{

}
