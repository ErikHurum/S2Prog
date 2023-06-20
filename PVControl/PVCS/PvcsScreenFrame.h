#pragma once
#include "pvcsframe.h"

class CPvcsScreenFrame :
    public CPvcsFrame{
    DECLARE_DYNCREATE(CPvcsScreenFrame)

public:
	static HANDLE m_hMutex;

	CPvcsScreenFrame(void);
    virtual ~CPvcsScreenFrame(void);

    DECLARE_MESSAGE_MAP()
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int	OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnClose();
    //afx_msg void OnMenuSelect(UINT nItemID,UINT nFlags,HMENU hSysMenu);
    afx_msg void OnUpdateControlCommand(CCmdUI *pCmdUI);
    afx_msg void OnControlCommand();
    afx_msg void OnScreenSwitchMenu(UINT ID);
    static void CloseApp();


};
