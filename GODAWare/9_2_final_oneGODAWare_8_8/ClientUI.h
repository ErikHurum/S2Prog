#pragma once
#include "DeviceStatWnd.h"
// CClientUI ���

class CClientUI : public CFrameWndEx
{
	DECLARE_DYNCREATE(CClientUI)
protected:
	CClientUI();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


