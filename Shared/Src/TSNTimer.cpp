//For all
//TSN Help Objects
#ifdef S2TXU
	//#include "stdafx.h"
#endif
#ifdef WIN32
#ifdef BORLAND
	#include<Windows.h>
	#pragma hdrstop
#endif
#else
	#include "RTOS.h"
#endif
#include "TSNTimer.h"

TSNTimer::TSNTimer(void)
{
	SeggerTimerIsCreated = false;
}

TSNTimer::~TSNTimer(void)
{
#ifdef WIN32
	DeleteTimerQueueEx(m_hTimerQueue,0);
#else
	OS_DeleteTimer((OS_TIMER*)&m_UserTimer);

#endif

}
bool TSNTimer::Start(unsigned int timeout)
{
	bool ret;
	if ( SeggerTimerIsCreated ) {
		ret = ReStart(timeout);
	} else {
#ifdef WIN32

		m_hTimerQueue = CreateTimerQueue();
		// ret = CreateTimerQueueTimer(&m_hTimer,m_hTimerQueue,WinCallback,this,timeout,timeout,0);
		ret = (bool)CreateTimerQueueTimer(&m_hTimer,m_hTimerQueue,WinCallback,this,timeout,0,0);
#else
		m_UserTimer.pObject = this;
		OS_CreateTimer((OS_TIMER*)&m_UserTimer,SeggerCallback,timeout);
		OS_StartTimer((OS_TIMER*)&m_UserTimer);
		SeggerTimerIsCreated = true;
		ret = true;
#endif
	}
	return(ret);
}

bool TSNTimer::ReStart(unsigned int timeout)
{
	bool ret;
	if ( SeggerTimerIsCreated ) {

#ifdef WIN32

//  m_hTimerQueue = CreateTimerQueue();
		ret = CreateTimerQueueTimer(&m_hTimer,m_hTimerQueue,WinCallback,this,timeout,0,0);
#else
		m_UserTimer.pObject = this;
		OS_RetriggerTimer((OS_TIMER*)&m_UserTimer);
		ret = true;
#endif
	} else {
		ret = Start(timeout);
	}
	return(ret);
}

void TSNTimer::Stop()
{
	if ( SeggerTimerIsCreated ) {
		SeggerTimerIsCreated = false;
#ifdef WIN32
		DeleteTimerQueueEx(m_hTimerQueue,0);
#else
		OS_DeleteTimer((OS_TIMER*)&m_UserTimer);
#endif
	}
}
#ifdef WIN32
void CALLBACK TSNTimer::WinCallback(PVOID lpParameter,BOOLEAN fired)
{
	if ( fired && lpParameter ) {
		((TSNTimer*)lpParameter)->TimerCallback();
	}

}
#else
void TSNTimer::SeggerCallback()
{

	// EHSMark
	USER_TIMER *pUserTimer = (USER_TIMER*)OS_GetpCurrentTimer();
	if ( pUserTimer->pObject )
		((TSNTimer*)pUserTimer->pObject)->TimerCallback();
	//if(pUserTimer)
	//OS_DeleteTimer((OS_TIMER*)&pUserTimer);

}
#endif
void TSNTimer::TimerCallback()
{
}
