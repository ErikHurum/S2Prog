#ifndef ANCriticalSectionH
#define ANCriticalSectionH
class ANCriticalSection
{
private:
#if defined(S2TXU) || defined(ANBOOLOADER)
  OS_RSEMA MyHandle;
#else
	HANDLE MyHandle;
#endif
public:
	ANCriticalSection(void);
	~ANCriticalSection(void);
	void Acquire(void);
	int  AcquireTimeOut(int TimeOut);
	void Release(void);
	void Enter(void);
	void Leave(void);
};

#endif
