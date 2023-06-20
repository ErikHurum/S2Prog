
// MFC.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "MFC.h"
#include "GodaLoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApp

BEGIN_MESSAGE_MAP(CMFCApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMFCApp::OnAppAbout)
END_MESSAGE_MAP()


// CMFCApp ����

CMFCApp::CMFCApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CMFCApp ����

CMFCApp theApp;


// CMFCApp ��ʼ��

BOOL CMFCApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������

	SetRegistryKey(_T("Scanjet Ariston"));

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	m_pServer = new CServer();

	m_pServerUI = new CServerUI();

	CGodaLoginDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	//��������Client��Server�д���

	return TRUE;
}

// CMFCApp ��Ϣ�������

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CMFCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFCApp �Զ������/���淽��

void CMFCApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CMFCApp::LoadCustomState()
{
}

void CMFCApp::SaveCustomState()
{
}

CMFCApp::~CMFCApp()
{
	delete m_pClient;
	m_pClient = 0;
	
	delete m_pServer;
	m_pServer = 0;

	delete m_pServerUI;
	m_pServerUI = 0;
}

int CMFCApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
          LPCTSTR pOldAppName = m_pszAppName;
          m_pszAppName = L"Scanjet DebugWare";// ��ʵafxmessgebox�ı�������������������
           int iRet = CWinApp::DoMessageBox(lpszPrompt, nType, nIDPrompt);
           m_pszAppName = pOldAppName ;
            return iRet ;
}

// CMFCApp ��Ϣ�������



