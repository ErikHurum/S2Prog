#pragma once



// CPvcsScreenThread

class CPvcsScreenThread : public CWinThread
{
	DECLARE_DYNCREATE(CPvcsScreenThread)

protected:
	CPvcsScreenThread();           // protected constructor used by dynamic creation
	virtual ~CPvcsScreenThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


