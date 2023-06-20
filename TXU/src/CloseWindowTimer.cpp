
#ifdef S2TXU
    #include "rtos.h"
    #include "stdafx.h"
#endif
#include "CloseWindowTimer.h"
#ifdef S2TXU
extern OS_MAILBOX CloseWinTimerBuf;
#endif
CloseWindowTimer::CloseWindowTimer(void)
{
}
CloseWindowTimer::CloseWindowTimer(GUI_HWIN WinHandl, volatile bool *Closed)
{
    m_WinHandl = WinHandl;
    m_Closed = Closed;
}

CloseWindowTimer::~CloseWindowTimer(void)
{
}

void CloseWindowTimer::TimerCallback()
{
    if ( !(*m_Closed) ) {
        *m_Closed = true;
        // Problem EHSMark
#ifdef S2TXU
        CloseWinPacket CWinPacket;
        CWinPacket.IsDialogWin= IsDialogWin;
        CWinPacket.m_Closed   = m_Closed;
        CWinPacket.m_WinHandl = m_WinHandl;
        CWinPacket.m_UserTimer= m_UserTimer;
        if ( !OS_PutMailCond(&CloseWinTimerBuf,(char*)&CWinPacket) ) {
            // If we get her, the message was not transferred
        }
#else
        if ( m_WinHandl > 0 ) {
            if ( IsDialogWin ) {
                GUI_EndDialog(m_WinHandl, 0);
            } else {
                WM_DeleteWindow(m_WinHandl);
            }
        }
#endif
    }
}

void CloseWindowTimer::Init(GUI_HWIN WinHandl,bool IsDialog, volatile bool *Closed,unsigned int timeout)
{
    m_Closed   = Closed;
    m_WinHandl = WinHandl;
    IsDialogWin= IsDialog;
    Start(timeout);
}

void CloseWindowTimer::Stop(void)
{
    TSNTimer::Stop();
    if ( m_Closed ) {
        if ( !(*m_Closed) ) {
            *m_Closed = true;
            if ( m_WinHandl > 0 ) {
                if ( IsDialogWin ) {
                    GUI_EndDialog(m_WinHandl, 0);
                } else {
                    WM_DeleteWindow(m_WinHandl);
                }
            }
        }
    }
}
