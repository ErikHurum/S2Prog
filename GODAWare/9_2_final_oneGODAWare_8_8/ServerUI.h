#pragma once


#define WM_USERCONNECTED (WM_USER+301)
#define WM_USERDISCONNECTED (WM_USER+302)

// CServerUI �Ի���

class CServerUI : public CDialog
{
	DECLARE_DYNAMIC(CServerUI)

public:
	CServerUI(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServerUI();

// �Ի�������
	enum { IDD = IDD_SERVER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg LRESULT OnUserConnected(WPARAM wParam, LPARAM lPARAM);
	afx_msg LRESULT OnUserDisconnected(WPARAM wParam, LPARAM lPARAM);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:
	BOOL GetIP(WCHAR * Hostaddress);
};
