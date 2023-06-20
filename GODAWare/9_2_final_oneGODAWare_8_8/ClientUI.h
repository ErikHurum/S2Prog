#pragma once
#include "DeviceStatWnd.h"
// CClientUI 框架

class CClientUI : public CFrameWndEx
{
	DECLARE_DYNCREATE(CClientUI)
protected:
	CClientUI();           // 动态创建所使用的受保护的构造函数
	virtual ~CClientUI();

protected:
	DECLARE_MESSAGE_MAP()

	

public:
	virtual void SetSendBytes(long){}
	virtual void SetRecvBytes(long){}
	virtual void SetErrBytes(long){}
	virtual void SetOnline(bool){}

	afx_msg void OnReconnect();
	afx_msg void OnUsermanagement();
};


