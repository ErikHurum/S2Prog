// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ �������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI �����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ���ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// MainFrmGR.cpp : CClientUIGR ���ʵ��
//

#include "stdafx.h"
#include "../MFC.h"
#include "../UserManageDlg.h"

#include "MainFrmGR.h"
#include "LevelAdjustmentDlgGR.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CClientUIGR

extern float gNullHight[3];

IMPLEMENT_DYNAMIC(CClientUIGR, CClientUI)

BEGIN_MESSAGE_MAP(CClientUIGR, CClientUI)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CClientUIGR::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CClientUIGR::OnUpdateApplicationLook)
	ON_COMMAND(ID_BASIC_LEVEL, &CClientUIGR::OnBasicLevel)
	ON_COMMAND(ID_BASIC_APPLICATION, &CClientUIGR::OnBasicApplication)
	ON_COMMAND(ID_BASIC_DAMPING, &CClientUIGR::OnBasicDamping)
	ON_COMMAND(ID_BASIC_LINERIZATION, &CClientUIGR::OnBasicLinerization)
	ON_COMMAND(ID_BASIC_OTHER, &CClientUIGR::OnBasicOther)
	ON_COMMAND(ID_DISPLAY_DISPLAY, &CClientUIGR::OnDisplayDisplay)
	ON_COMMAND(ID_DIAGNOSIS_DIAGNOSIS, &CClientUIGR::OnDiagnosisDiagnosis)
	ON_COMMAND(ID_SERVICE_RESET, &CClientUIGR::OnServiceReset)
	ON_COMMAND(ID_SERVICE_CURRENTOUTPUT, &CClientUIGR::OnServiceCurrentoutput)
	ON_COMMAND(ID_SERVICE_PIN, &CClientUIGR::OnServicePin)
	ON_COMMAND(ID_SERVICE_OTHER, &CClientUIGR::OnServiceOther)
	ON_COMMAND(ID_SERVICE_FALSEECHO, &CClientUIGR::OnServiceFalseecho)
	ON_COMMAND(ID_ADVANCED_ADVANVCED1, &CClientUIGR::OnAdvancedAdvanvced1)
	ON_COMMAND(ID_ADVANCED_ADVANVCED2, &CClientUIGR::OnAdvancedAdvanvced2)
	ON_COMMAND(ID_INFO_INFO, &CClientUIGR::OnInfo)
	ON_COMMAND(ID_DEVICEOP_LOAD, &CClientUIGR::OnDeviceopLoad)
	ON_COMMAND(ID_DEVICEOP_SAVE, &CClientUIGR::OnDeviceopSave)
	ON_COMMAND(ID_DEVICEOP_REFRESH, &CClientUIGR::OnRefresh)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CClientUIGR ����/����

CClientUIGR::CClientUIGR()
:sendBytes(0), recvBytes(0), errBytes(0)
{
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);

}

CClientUIGR::~CClientUIGR()
{
}

int CClientUIGR::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);



	// ����һ����ͼ��ռ�ÿ�ܵĹ�����
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("δ�ܴ�����ͼ����\n");
		return -1;
	}

	m_wndRibbonBar.Create(this);
	InitializeRibbon();

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	//CString strSend;
	//CString strRecv;
	//CString strErr;
	//bNameValid = strSend.LoadString(IDS_STATUS_SEND);
	//ASSERT(bNameValid);
	//bNameValid = strRecv.LoadString(IDS_STATUS_RECV);
	//ASSERT(bNameValid);
	//bNameValid = strErr.LoadString(IDS_STATUS_ERR);
	//ASSERT(bNameValid);
	//m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_SEND, strSend, TRUE), strSend);
	//m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_RECV, strRecv, TRUE), strRecv);
	//m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_ERR, strErr, TRUE), strErr);
	// m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	m_wndDeviceStat.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndDeviceStat);

	m_wndCurve.EnableDocking(CBRS_ALIGN_BOTTOM);
	DockPane(&m_wndCurve);

	// ����ˢ��״̬��ʾ�ļ�ʱ����10��һˢ
	SetTimer(1, 10000, NULL);
	OnTimer(1);


	return 0;
}

BOOL CClientUIGR::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	m_strTitle.LoadString(IDS_GRTITLE);
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

void CClientUIGR::InitializeRibbon()
{
	BOOL bNameValid;

	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);

	// �������ͼ��:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_BUTTONS);

	// ��ʼ����ť:
	/*
	m_MainButton.SetImage(IDB_MAIN);
	m_MainButton.SetText(_T("\nf"));
	m_MainButton.SetToolTipText(strTemp);

	m_wndRibbonBar.SetApplicationButton(&m_MainButton, CSize (45, 45));
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(strTemp, IDB_FILESMALL, IDB_FILELARGE);

	bNameValid = strTemp.LoadString(IDS_RIBBON_LOAD);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_DEVICEOP_LOAD, strTemp, 1, 1));
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_DEVICEOP_SAVE, strTemp, 2, 2));

	bNameValid = strTemp.LoadString(IDS_RIBBON_CLOSE);
	ASSERT(bNameValid);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, strTemp, 9, 9));

	bNameValid = strTemp.LoadString(IDS_RIBBON_EXIT);
	ASSERT(bNameValid);
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton(ID_APP_EXIT, strTemp, 15));
*/

	// ���濪ʼ��������
	
	// 1. �Ǳ�����
	bNameValid = strTemp.LoadString(IDS_RIBBON_DEVICESETTINGS);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryDeviceSettings = m_wndRibbonBar.AddCategory(strTemp, IDB_WRITESMALL, IDB_WRITELARGE);

	// 1.1 ��ȡpanel
	bNameValid = strTemp.LoadString(IDS_RIBBON_DEVICEOP);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelOP = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	
	// 1.1.1 ��ȡ
	bNameValid = strTemp.LoadString(IDS_RIBBON_LOAD);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLoad = new CMFCRibbonButton(ID_DEVICEOP_LOAD, strTemp, 0, 0);
	pPanelOP->Add(pBtnLoad);
	
	// 1.1.2 �洢
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnSave = new CMFCRibbonButton(ID_DEVICEOP_SAVE, strTemp, 0, 0);
	pPanelOP->Add(pBtnSave);

	// 1.1.3 ˢ��
	bNameValid = strTemp.LoadString(IDS_DEVICEOP_REFRESH);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnRefresh = new CMFCRibbonButton(ID_DEVICEOP_REFRESH, strTemp, 0, 0);
	pPanelOP->Add(pBtnRefresh);


	// 1.2 �������� panel
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelBasic = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));


	// 1.2.1 ��λ����
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC_LEVEL);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLevel = new CMFCRibbonButton(ID_BASIC_LEVEL, strTemp, 0, 0);
	pPanelBasic->Add(pBtnLevel);

	// 1.2.2 ��������
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC_APPLICATION);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnApplication = new CMFCRibbonButton(ID_BASIC_APPLICATION, strTemp, 0, 0);
	pPanelBasic->Add(pBtnApplication);

	// 1.2.3 ����ʱ��
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC_DAMPING);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnDamping = new CMFCRibbonButton(ID_BASIC_DAMPING, strTemp, 0, 0);
	pPanelBasic->Add(pBtnDamping);
	
	// 1.2.4 ���ӳ��
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC_LINEARIZATION);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLinearization = new CMFCRibbonButton(ID_BASIC_LINERIZATION, strTemp, 0, 0);
	pPanelBasic->Add(pBtnLinearization);

	// 1.2.5 ����
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC_OTHER);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnOther = new CMFCRibbonButton(ID_BASIC_OTHER, strTemp, 0, 0);
	pPanelBasic->Add(pBtnOther);

	// 1.3 ��ʾ
	bNameValid = strTemp.LoadString(IDS_RIBBON_DISPLAY);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelDisplay = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	
	// 1.3.1 ��ʾ
	bNameValid = strTemp.LoadString(IDS_RIBBON_DISPLAY);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnDisplay = new CMFCRibbonButton(ID_DISPLAY_DISPLAY, strTemp, 0, 0);
	pPanelDisplay->Add(pBtnDisplay);

	// 1.4 ���
	bNameValid = strTemp.LoadString(IDS_RIBBON_DIAGNOSIS);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelDiagnosis = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	
	// 1.4.1 ���
	bNameValid = strTemp.LoadString(IDS_RIBBON_DIAGNOSIS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnDiagnosis = new CMFCRibbonButton(ID_DIAGNOSIS_DIAGNOSIS, strTemp, 0, 0);
	pPanelDiagnosis->Add(pBtnDiagnosis);

	// 1.5 ����
	bNameValid = strTemp.LoadString(IDS_RIBBON_SERVICE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelService = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));

	// 1.5.1 �������
	bNameValid = strTemp.LoadString(IDS_RIBBON_CURRENTOUTPUT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnCurrent = new CMFCRibbonButton(ID_SERVICE_CURRENTOUTPUT, strTemp, 0, 0);
	pPanelService->Add(pBtnCurrent);

	// 1.5.2 ��λ
	bNameValid = strTemp.LoadString(IDS_RIBBON_RESET);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnReset = new CMFCRibbonButton(ID_SERVICE_RESET, strTemp, 0, 0);
	pPanelService->Add(pBtnReset);

	// 1.5.3 ��ٻز�
	bNameValid = strTemp.LoadString(IDS_RIBBON_FALSEECHO);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnFalseEcho = new CMFCRibbonButton(ID_SERVICE_FALSEECHO, strTemp, 0, 0);
	pPanelService->Add(pBtnFalseEcho);

	// 1.5.4 ����
	bNameValid = strTemp.LoadString(IDS_RIBBON_PIN);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPin = new CMFCRibbonButton(ID_SERVICE_PIN, strTemp, 0, 0);
	pPanelService->Add(pBtnPin);

	// 1.5.5 ����
	bNameValid = strTemp.LoadString(IDS_RIBBON_OTHER);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnServiceOther = new CMFCRibbonButton(ID_SERVICE_OTHER, strTemp, 0, 0);
	pPanelService->Add(pBtnServiceOther);

	// 1.6 �߼�����
	bNameValid = strTemp.LoadString(IDS_RIBBON_ADVANCED);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelAdvanced = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	
	// 1.6.1 �߼�����һ
	bNameValid = strTemp.LoadString(IDS_RIBBON_ADVANCED1);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnAdvanced1 = new CMFCRibbonButton(ID_ADVANCED_ADVANVCED1, strTemp, 0, 0);
	pPanelAdvanced->Add(pBtnAdvanced1);
	
	// 1.6.2 �߼����ö�
	bNameValid = strTemp.LoadString(IDS_RIBBON_ADVANCED2);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnAdvanced2 = new CMFCRibbonButton(ID_ADVANCED_ADVANVCED2, strTemp, 0, 0);
	pPanelAdvanced->Add(pBtnAdvanced2);

	// 1.7 ��Ϣ
	bNameValid = strTemp.LoadString(IDS_RIBBON_INFO);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelInfo = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	
	// 1.7.1 ��Ϣ
	bNameValid = strTemp.LoadString(IDS_RIBBON_INFO);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnInfo = new CMFCRibbonButton(ID_INFO_INFO, strTemp, 0, 0);
	pPanelInfo->Add(pBtnInfo);


	// 2. ��������
	bNameValid = strTemp.LoadString(IDS_RIBBON_SOFTWARESETTINGS);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategorySoftwareSettings = m_wndRibbonBar.AddCategory(strTemp, IDB_WRITESMALL, IDB_WRITELARGE);

	// 2.1 ����
	bNameValid = strTemp.LoadString(IDS_RIBBON_CONNECTION);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelConnection = pCategorySoftwareSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	pPanelConnection;

	// 2.1.1 ��������
	bNameValid = strTemp.LoadString(IDS_RIBBON_RECONNECT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnReconnect = new CMFCRibbonButton(ID_RECONNECT, strTemp, 0, 0);
	pPanelConnection->Add(pBtnReconnect);

	// 2.2 �û�
	bNameValid = strTemp.LoadString(IDS_RIBBON_USER);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelUser = pCategorySoftwareSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	pPanelUser;

	// 2.2.1 �л��û�
	bNameValid = strTemp.LoadString(IDS_RIBBON_CHANGERUSER);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnChangeUser = new CMFCRibbonButton(ID_CHANGEUSER, strTemp, 0, 0);
	pPanelUser->Add(pBtnChangeUser);

	// 2.2.2 �û�����
	bNameValid = strTemp.LoadString(IDS_RIBBON_USERMANAGEMENT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnUserMangement = new CMFCRibbonButton(ID_USERMANAGEMENT, strTemp, 0, 0);
	pPanelUser->Add(pBtnUserMangement);

	//// 2.3 ����
	//bNameValid = strTemp.LoadString(IDS_RIBBON_LANGUAGE);
	//ASSERT(bNameValid);
	//CMFCRibbonPanel* pPanelLanguage = pCategorySoftwareSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	//pPanelLanguage;

	// ��Ԫ�����ӵ�ѡ��Ҳ�:
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pVisualStyleButton = new CMFCRibbonButton(UINT(-1), strTemp, UINT(-1), UINT(-1));

	pVisualStyleButton->SetMenu(IDR_THEME_MENU, FALSE /* ��Ĭ������*/, TRUE /* �Ҷ���*/);

	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_TIP);
	ASSERT(bNameValid);
	pVisualStyleButton->SetToolTipText(strTemp);
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_DESC);
	ASSERT(bNameValid);
	pVisualStyleButton->SetDescription(strTemp);
	m_wndRibbonBar.AddToTabs(pVisualStyleButton);

	// ���ӿ��ٷ��ʹ���������:
	CList<UINT, UINT> lstQATCmds;

	//lstQATCmds.AddTail(ID_FILE_NEW);
	//lstQATCmds.AddTail(ID_FILE_OPEN);
	//lstQATCmds.AddTail(ID_FILE_SAVE);
	//lstQATCmds.AddTail(ID_FILE_GRINT_DIRECT);

	//m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);

	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));
}

BOOL CClientUIGR::CreateDockingWindows()
{
	BOOL bNameValid;

	// �����������
	CString strOutputWndGR;
	bNameValid = strOutputWndGR.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndCurve.Create(strOutputWndGR, this, CRect(0, 0, 200, 200),TRUE, ID_WND_OUTPUT, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	// ����״̬����
	CString str;
	bNameValid = str.LoadString(IDS_DEVICESTAT_WND);
	ASSERT(bNameValid);
	if (!m_wndDeviceStat.Create(str, this, CRect(0, 0, 200, 200),TRUE, ID_WND_DEVICESTAT, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ���״̬����\n");
		return FALSE; // δ�ܴ���
	}


	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CClientUIGR::SetDockingWindowIcons(BOOL /*bHiColorIcons*/)
{
	//HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_GROPERTIES_WND_HC : IDI_GROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	//m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// CClientUIGR ���

#ifdef _DEBUG
void CClientUIGR::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CClientUIGR::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CClientUIGR ��Ϣ��������

void CClientUIGR::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// ������ǰ�Ƶ���ͼ����
	m_wndView.SetFocus();
}

BOOL CClientUIGR::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ����ͼ��һ�γ��Ը�����
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// ����ִ��Ĭ�ϴ���
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CClientUIGR::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CClientUIGR::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}
void CClientUIGR::OnBasicLevel()
{
	m_wndView.Show(IDD_LEVEL_ADJUSTMENT_GR);
}

void CClientUIGR::OnBasicApplication()
{
	m_wndView.Show(IDD_APPLICATION_GR);
}

void CClientUIGR::OnBasicDamping()
{
	m_wndView.Show(IDD_DAMPING_GR);
}

void CClientUIGR::OnBasicLinerization()
{
	m_wndView.Show(IDD_LINEARIZATION_GR);
}

void CClientUIGR::OnBasicOther()
{
	m_wndView.Show(IDD_OTHERSETTINGS_GR);
}

void CClientUIGR::OnDisplayDisplay()
{
	m_wndView.Show(IDD_DISPLAY_GR);
}

void CClientUIGR::OnDiagnosisDiagnosis()
{
	m_wndView.Show(IDD_DIAGNOSIS_GR);
}

void CClientUIGR::OnServiceCurrentoutput()
{
	m_wndView.Show(IDD_CURRENTOUTPUT_GR);
}

void CClientUIGR::OnServiceReset()
{
	m_wndView.Show(IDD_RESET_GR);
}

void CClientUIGR::OnServicePin()
{
	m_wndView.Show(IDD_PIN_GR);
}

void CClientUIGR::OnServiceOther()
{
	m_wndView.Show(IDD_SERVICEOTHER_GR);
}

void CClientUIGR::OnServiceFalseecho()
{
	m_wndView.Show(IDD_FALSEECHO_GR);
}

void CClientUIGR::OnAdvancedAdvanvced1()
{
	m_wndView.Show(IDD_ADVANCEDSETUP1_GR);
}

void CClientUIGR::OnAdvancedAdvanvced2()
{
	m_wndView.Show(IDD_ADVANCEDSETUP2_GR);
}

void CClientUIGR::OnInfo()
{
	m_wndView.Show(IDD_INFO);
}

void CClientUIGR::OnDeviceopLoad()
{
	m_wndView.Load();
}

void CClientUIGR::OnDeviceopSave()
{
	m_wndView.Save();
}

void CClientUIGR::OnRefresh()
{
	theApp.m_pClient->RefreshId();
}
void CClientUIGR::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ

	if (theApp.m_pClient->IsOnline())
	{
		SetOnline(true);

		SetNullHight(gNullHight[0]);

		CClientUI::OnTimer(nIDEvent);

		m_wndDeviceStat.RedrawWindow();
	}
	else
	{
		SetOnline(false);
		CClientUI::OnTimer(nIDEvent);
		m_wndDeviceStat.RedrawWindow();
	}
}

void CClientUIGR::SetSendBytes( long )
{

}

void CClientUIGR::SetRecvBytes( long )
{

}

void CClientUIGR::SetErrBytes( long )
{

}
//void CClientUIGR::OnUsermanagement()
//{
//
//}