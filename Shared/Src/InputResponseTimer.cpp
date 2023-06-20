#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif


InputResponseTimer::InputResponseTimer(void)
{
  m_pObject = 0;
}
InputResponseTimer::InputResponseTimer(PRogramObjectBase *pobj)
{
  m_pObject = pobj;
}

InputResponseTimer::~InputResponseTimer(void)
{
}
void InputResponseTimer::TimerCallback()
{
  if(m_pObject)
  {
    m_pObject->InputTimeout();
  }
}
