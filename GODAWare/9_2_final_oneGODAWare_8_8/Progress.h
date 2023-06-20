#pragma once
#include "ProgressDlg.h"


class CProgress
{
public:
	CProgress(void);
	~CProgress(void);

public:
	void Begin();
	void End();

private:
	CWinThread* m_pThread;
	//CProgressDlg* m_pDlg;
};
