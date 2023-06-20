#include "StdAfx.h"
#include "ErrCounter.h"



bool CErrCounter::SetErr( bool stat )
{
	CCriticalSection cs;	
	CSingleLock lock(&cs);
	lock.Lock();

	if (stat == false)
	{
		m_errCounter++;
		if (m_errCounter >= 3)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		m_errCounter = 0;
		return true;
	}
}