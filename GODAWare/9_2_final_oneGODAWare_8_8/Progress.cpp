#include "StdAfx.h"
#include "Progress.h"
#include "ProgressThread.h"

CEvent progressThreadOK;
extern const UINT WM_EXITPROGRESS = ::RegisterWindowMessage(_T("ExitProgress"));

CProgress::CProgress(void)
{
	Begin();
}

CProgress::~CProgress(void)
{
	End();
}

void CProgress::Begin()
{
	m_pThread = AfxBeginThread(RUNTIME_CLASS(CProgressThread));
}

void CProgress::End()
{
	//Sleep(1000);
	::WaitForSingleObject(progressThreadOK, INFINITE);
	//::SendMessage(m_pThread->GetMainWnd()->GetSafeHwnd(), WM_CLOSE, 0, 0);
	::PostThreadMessage(m_pThread->m_nThreadID, WM_EXITPROGRESS, 0, 0);
	//delete m_pThread;
}