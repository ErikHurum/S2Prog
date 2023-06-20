
// GodaLoginDlg.h : ͷ�ļ�
//

#pragma once

#include "Resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "Server.h"
#include "Client.h"

// CGodaLoginDlg �Ի���
class CGodaLoginDlg : public CDialog
{
// ����
public:
	CGodaLoginDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GODALOGIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

private:
	CComboBox m_comboLoginType;
	CComboBox m_comboDeviceType;
	CComboBox m_comboComPort;
	CComboBox m_comboProtocol;
	


	CEdit m_editName;
	CEdit m_editPassword;

	static const unsigned port = 20007;

private:
	void ShowIpCtrl(bool);

	void EnableDeviceCtrl(bool);
	void EnableUserCtrl(bool);
	
	
	void RestoreSettings();
	void SaveSettings();
	bool LocalLogin();
	bool RemoteLogin();

	bool OfflineLogin();


	bool StartServer();
	bool StartServerUI();
	bool StartClient();

	bool m_serverStarted;
	

public:
	CIPAddressCtrl m_ipAddress;
	afx_msg void OnCbnSelchangeComboLogintype();
	//bool GetSystemSerialComport(CArray<CString,CString>&);//ty changed
	CStatic m_ipLabel;
	CComboBox m_comboAddress;
	
	//CArray<CString,CString> comarray;//ty changed
	afx_msg void OnEnChangeEditName();
	afx_msg void OnCbnSelchangeComboDevicetype();
	afx_msg void OnCbnSelchangeComboProtocol();
	afx_msg void OnCbnSelchangeComboComport();
};
