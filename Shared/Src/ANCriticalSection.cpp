#ifndef S2TXU
	#include <process.h>
#ifdef BORLAND
  #include <windows.h>
#endif
#else
	#include "RTOS.h"
#endif
#include "TSNDefines.h"
#include "ANCriticalSection.h"

ANCriticalSection::ANCriticalSection(void)
{
#if defined(S2TXU) || defined(ANBOOLOADER)
	OS_CREATERSEMA(&MyHandle);
#else
	MyHandle  = CreateMutex( NULL, false, NULL );

#endif
}

ANCriticalSection::~ANCriticalSection(void)
{
#ifdef WIN32
	WaitForSingleObject( MyHandle, 10 );
	CloseHandle(MyHandle);
#endif
}
void ANCriticalSection::Acquire(void)
{
#ifdef S2TXU
	OS_Use(&MyHandle);
#else
	WaitForSingleObject( MyHandle, INFINITE );
#endif
}
int ANCriticalSection::AcquireTimeOut(int TimeOut)
{
#ifdef S2TXU
	OS_Use(&MyHandle);
	return (0);
#else
	return (WaitForSingleObject( MyHandle, TimeOut ));
	//return (0);
#endif
}

void ANCriticalSection::Release(void)
{
#ifdef S2TXU
	OS_Unuse(&MyHandle);
#else
	ReleaseMutex(MyHandle);
#endif
}
void ANCriticalSection::Enter(void)
{
	Acquire();
}
void ANCriticalSection::Leave(void)
{
	Release();
}


