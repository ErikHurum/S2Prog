#pragma once

// MainWindow

class CMainWnd : public CFrameWnd
{
public:
	CMainWnd() {Create(NULL, _T("Test"));}
	DECLARE_MESSAGE_MAP()

private:
	CProgressDlg m_dlg;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};



// CProgressThread

class CProgressThread : public CWinThread
{
	DECLARE_DYNCREATE(CProgressThread)

protected:
	CProgressThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CProgressThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	afx_msg void OnExitProgress(WPARAM wParam, LPARAM lParam); 

protected:
	//CProgressDlg m_dlg;
	
	DECLARE_MESSAGE_MAP()
};


