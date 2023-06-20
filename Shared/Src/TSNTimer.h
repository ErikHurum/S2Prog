// this class defines a software timer that works on both Segger and win32 plattforms.
// the timerobjects need an objectpointer as input when created or started, this should be done
// via inheritance (using a child that implements TimerCallBack())
#pragma once
#ifndef TSNTIMER_H
#define TSNTIMER_H
#ifdef WIN32
	#ifdef ANTDUSIM
		#include "stdafx.h"
	#endif
  #include<Windows.h>
#else
  //#pragma pack(1)
  struct USER_TIMER{
    OS_TIMER Timer;
    void *pObject;
  };
  //#pragma pack(4)
  //#pragma pop
#endif

class TSNTimer
{
private:
	bool SeggerTimerIsCreated;
public:
  TSNTimer(void);
  ~TSNTimer(void);
  bool Start(unsigned int timeout);
  bool ReStart(unsigned int timeout);
  virtual void Stop();
  virtual void TimerCallback(void);
#ifdef WIN32
  HANDLE m_hTimer;
  HANDLE  m_hTimerQueue;
  static void CALLBACK WinCallback(void* lpParameter,BOOLEAN TimerOrWaitFired);
#else
  static void SeggerCallback();
  USER_TIMER m_UserTimer;
#endif

};
#endif
