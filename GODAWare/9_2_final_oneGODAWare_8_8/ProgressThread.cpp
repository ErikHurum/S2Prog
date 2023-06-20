// ProgressThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC.h"
#include "ProgressThread.h"
#include "ProgressDlg.h"


extern CEvent progressThreadOK;
const UINT WM_EXITPROGRESS = ::RegisterWindowMessage(_T("ExitProgress"));

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CProgressThread

IMPLEMENT_DYNCREATE(CProgressThread, CWinThread)

CProgressThread::CProgressThread()
{
}

CProgressThread::~CProgressThread()
{
}

BOOL CProgressThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	m_pMainWnd = new CMainWnd;
	//m_pMainWnd->ShowWindow(SW_SHOW);
	//m_pMainWnd->UpdateWindow();

	
	return TRUE;
}

int CProgressThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CProgressThread, CWinThread)
	ON_REGISTERED_THREAD_MESSAGE(WM_EXITPROGRESS, &CProgressThread::OnExitProgress)
END_MESSAGE_MAP()


void CProgressThread::OnExitProgress(WPARAM , LPARAM )
{
	delete m_pMainWnd;
}

// CProgressThread ��Ϣ�������

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_dlg.Create(IDD_PROGRESSDLG,this);
	m_dlg.ShowWindow(SW_SHOW);

	return 0;
}
