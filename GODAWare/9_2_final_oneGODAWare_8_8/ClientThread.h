#pragma once

#include "./ErrCounter.h"


// CClientThread

class CClientThreadWnd : public CFrameWnd
{
public:
	CClientThreadWnd() {Create(NULL, _T(""));}
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);


};


class CClientThread : public CWinThread
{
	DECLARE_DYNCREATE(CClientThread)

protected:
	CClientThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CClientThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();


protected:
	DECLARE_MESSAGE_MAP()
};


