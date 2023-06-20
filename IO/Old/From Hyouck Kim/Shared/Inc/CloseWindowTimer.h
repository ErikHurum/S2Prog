#pragma once
#ifndef CLOSEWINDOWTIMER_H
#define CLOSEWINDOWTIMER_H
#include "tsntimer.h"

#ifdef S2TXU

struct CloseWinPacket {
    GUI_HWIN m_WinHandl;
    bool IsDialogWin;
    volatile bool *m_Closed;
    USER_TIMER m_UserTimer;
};
#endif

/*
struct{
    WM_HWIN hWin;
    WM_MESSAGE pMsg;
} EventMsg;
*/
class CloseWindowTimer :
public TSNTimer {
private:
    bool IsDialogWin;
public:
    CloseWindowTimer(void);
    CloseWindowTimer(GUI_HWIN WinHandl, volatile bool *Closed);
    ~CloseWindowTimer(void);
    void TimerCallback(void);
    void Init(GUI_HWIN WinHandl, bool IsDialogWin, volatile bool *Closed,unsigned int timeout);
    void Stop(void);
    GUI_HWIN m_WinHandl;
    volatile bool *m_Closed;
};

#endif
