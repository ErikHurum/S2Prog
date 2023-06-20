#ifndef INPUTRESPONSTIMER_H
#define INPUTRESPONSTIMER_H
#pragma once

class InputResponseTimer :
  public TSNTimer
{
public:
  InputResponseTimer(void);
  InputResponseTimer(PRogramObjectBase *pobj);
  ~InputResponseTimer(void);
  void TimerCallback(void);
  PRogramObjectBase *m_pObject;
};

#endif
