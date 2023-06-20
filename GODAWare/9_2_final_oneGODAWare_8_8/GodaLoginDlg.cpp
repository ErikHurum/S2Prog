
// GodaLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GodaLoginDlg.h"
#include "Client.h"
#include "Server.h"
#include "ServerUI.h"
#include "MFC.h"
#include "Progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CGodaLoginDlg::CGodaLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGodaLoginDlg::IDD, pParent), m_serverStarted(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGodaLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LOGINTYPE, m_comboLoginType);
	DDX_Control(pDX, IDC_COMBO_DEVICETYPE, m_comboDeviceType);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_comboComPort);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_comboProtocol);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_PW, m_editPassword);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipAddress);
	DDX_Control(pDX, IDC_LABEL_IP, m_ipLabel);
	DDX_Control(pDX, IDC_COMBO_ADDRESS, m_comboAddress);
}

BEGIN_MESSAGE_MAP(CGodaLoginDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CGodaLoginDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_LOGINTYPE, &CGodaLoginDlg::OnCbnSelchangeComboLogintype)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICETYPE, &CGodaLoginDlg::OnCbnSelchangeComboDevicetype)
	ON_CBN_SELCHANGE(IDC_COMBO_PROTOCOL, &CGodaLoginDlg::OnCbnSelchangeComboProtocol)
	ON_CBN_SELCHANGE(IDC_COMBO_COMPORT, &CGodaLoginDlg::OnCbnSelchangeComboComport)
END_MESSAGE_MAP()


// CGodaLoginDlg 消息处理程序

BOOL CGodaLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//m_comboLoginType.SetCurSel(0);
	//OnCbnSelchangeComboLogintype();
	//m_comboLoginType.SetMinVisibleItems(5);
	RestoreSettings();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGodaLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGodaLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGodaLoginDlg::OnBnClickedOk()
{
	SaveSettings();
	//bool bLoginOk;

	switch (m_comboLoginType.GetCurSel())
	{
	case 0:	//本地登录
		if (LocalLogin())
			OnOK();
		break;
	case 1:	//登录服务器
		if (RemoteLogin())
		{
			OnOK();
		}
		break;
	case 2:	//仅服务器
		if (StartServer())
		{
			StartServerUI();
			OnOK();
		}
		break;
	case 3:	//离线登录
		OfflineLogin();
		OnOK();
	}
}

void CGodaLoginDlg::RestoreSettings()
{
	// 从存储文件中读取上次的设置
	CStdioFile f;

	int nLoginType = 0;
	DWORD ip = (BYTE(127)<<24) + (BYTE(0)<<16) + (BYTE(0)<<8) + BYTE(1);
	int nDeviceType = 0;
	int nProtocol = 0;
	int nComPort = 0;
	int nAddress = 0;
	CString username;
	CString pw;

	if (f.Open(_T("settings.dat"), CFile::modeRead))
	{
		CString str;
		f.ReadString(str);
		nLoginType = _tstoi(str);

		f.ReadString(str);
		ip = _tstoi(str);

		f.ReadString(str);
		nDeviceType = _tstoi(str);

		f.ReadString(str);
		nProtocol = _tstoi(str);

		f.ReadString(str);
		nComPort = _tstoi(str);

		f.ReadString(str);
		nAddress = _tstoi(str);

		f.ReadString(username);
		f.ReadString(pw);
	}
	
	m_comboLoginType.SetCurSel(nLoginType);
	m_ipAddress.SetAddress(ip);
	m_comboDeviceType.SetCurSel(nDeviceType);
	m_comboProtocol.SetCurSel(nProtocol);
	m_comboComPort.SetCurSel(nComPort);
	m_comboAddress.SetCurSel(nAddress);
	m_editName.SetWindowText(username);
	m_editPassword.SetWindowText(pw);

	OnCbnSelchangeComboLogintype();
}

void CGodaLoginDlg::SaveSettings()
{
	// 将设置存储到文件
	CStdioFile f;
	if(f.Open(_T("settings.dat"),CFile::modeCreate | CFile::modeWrite))
	{
		CString str;

		str.Format(_T("%d\n"),m_comboLoginType.GetCurSel());
		f.WriteString(str);

		DWORD ip;
		m_ipAddress.GetAddress(ip);

		str.Format(_T("%d\n"), ip);
		f.WriteString(str);

		str.Format(_T("%d\n"), m_comboDeviceType.GetCurSel());
		f.WriteString(str);

		str.Format(_T("%d\n"), m_comboProtocol.GetCurSel());
		f.WriteString(str);

		str.Format(_T("%d\n"), m_comboComPort.GetCurSel());
		f.WriteString(str);

		str.Format(_T("%d\n"), m_comboAddress.GetCurSel());
		f.WriteString(str);

		m_editName.GetWindowText(str);
		f.WriteString(str + _T("\n"));


		m_editPassword.GetWindowText(str);
		f.WriteString(str + _T("\n"));

	}
}

bool CGodaLoginDlg::LocalLogin()
{
	if (!StartServer())
	{
		return false;
	}

	if (!StartClient())
	{
		return false;
	}
	return true;
}

bool CGodaLoginDlg::RemoteLogin()
{
	return StartClient();
}


bool CGodaLoginDlg::StartClient()
{
	theApp.m_pClient = new CClient(static_cast<DeviceType>(m_comboDeviceType.GetCurSel()));

	CString name;
	m_editName.GetWindowText(name);
	CString password;
	m_editPassword.GetWindowText(password);
	if (!theApp.m_pClient->Login(name, password))
	{
		WarnMessageBox(IDS_MSG_LOGINERR);
		delete theApp.m_pClient;
		theApp.m_pClient = 0;
		return false;
	}
	
	DWORD ip;
	m_ipAddress.GetAddress(ip);

	if (!theApp.m_pClient->ConnectServer(ip, port))
	{
		WarnMessageBox(IDS_MSG_CONNECTERR);

		////下面四行重启应用程序，ws一下，没办法了
		//_TCHAR   szFileName[MAX_PATH];  
		//GetModuleFileName(theApp.m_hInstance,   szFileName,   MAX_PATH);
		//ShellExecute(NULL,   _T("Open"),   szFileName,   NULL,   NULL,   SW_SHOWNORMAL);
		//PostQuitMessage(0);


		delete theApp.m_pClient;
		theApp.m_pClient = 0;
		return false;
	}

	theApp.m_pClient->StartLoadHightBackground();

	theApp.m_pClient->InitUI();
	theApp.m_pClient->ShowUI();

	return true;
}



bool CGodaLoginDlg::StartServer()
{
	if (m_serverStarted)
	{
		return true;
	}
	
	

	//m_serverStarted = theApp.m_pServer->Init(m_comboComPort.GetCurSel() + 1, 
	m_serverStarted = theApp.m_pServer->Init(m_comboComPort.GetCurSel(), 
               1, 
               static_cast<DeviceProtocol>(m_comboProtocol.GetCurSel()),
			   static_cast<BYTE>(m_comboAddress.GetCurSel()) );

	if (!m_serverStarted)
	{
		WarnMessageBox(IDS_MSG_COMERR);
	}

	return m_serverStarted;
}

void CGodaLoginDlg::OnCbnSelchangeComboLogintype()
{
	switch (m_comboLoginType.GetCurSel())
	{
	case 0:	// 本地登录
	case 1: 
	case 2: 
		ShowIpCtrl(false);
		m_ipAddress.SetAddress(127, 0, 0, 1);
		EnableDeviceCtrl(true);
		EnableUserCtrl(true);
		break;
		/*
	case 1:	// 登录到服务器
		ShowIpCtrl(true);
		m_ipAddress.ClearAddress();
		EnableDeviceCtrl(false);
		EnableUserCtrl(true);
		break;
	case 2:	// 仅服务器
		ShowIpCtrl(false);
		EnableDeviceCtrl(true);
		EnableUserCtrl(false);
		break;
				*/
	case 3:	// 离线模式
		ShowIpCtrl(false);
		EnableDeviceCtrl(true);
		EnableUserCtrl(false);

	}
}

void CGodaLoginDlg::ShowIpCtrl( bool bShow )
{
	if (bShow)
	{
		m_ipLabel.ShowWindow(SW_SHOW);
		m_ipAddress.ShowWindow(SW_SHOW);
	}
	else
	{
		m_ipLabel.ShowWindow(SW_HIDE);
		m_ipAddress.ShowWindow(SW_HIDE);
	}
}

void CGodaLoginDlg::EnableDeviceCtrl( bool bEnable )
{
	m_comboComPort.EnableWindow(bEnable);
	m_comboDeviceType.EnableWindow(bEnable);
	m_comboProtocol.EnableWindow(bEnable);
	m_comboAddress.EnableWindow(bEnable);
}

void CGodaLoginDlg::EnableUserCtrl( bool bEnable )
{
	m_editName.EnableWindow(bEnable);
	m_editPassword.EnableWindow(bEnable);
}

bool CGodaLoginDlg::OfflineLogin()
{
	if (theApp.m_pClient == 0)
		theApp.m_pClient = new CClient(static_cast<DeviceType>(m_comboDeviceType.GetCurSel()));

	theApp.m_pClient->InitUI();
	theApp.m_pClient->ShowUI();

	return true;
}

bool CGodaLoginDlg::StartServerUI()
{
	ShowWindow(SW_HIDE);

	theApp.m_pServerUI->DoModal();

	return TRUE;
}


void CGodaLoginDlg::OnCbnSelchangeComboDevicetype()
{
	// TODO: Add your control notification handler code here
}


void CGodaLoginDlg::OnCbnSelchangeComboProtocol()
{
	// TODO: Add your control notification handler code here
}


void CGodaLoginDlg::OnCbnSelchangeComboComport()
{
	// TODO: Add your control notification handler code here
}
