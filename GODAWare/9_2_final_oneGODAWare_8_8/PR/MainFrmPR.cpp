// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// MainFrmPR.cpp : CClientUIPR 类的实现
//

#include "stdafx.h"
#include "../MFC.h"

#include "MainFrmPR.h"
#include "LevelAdjustmentDlgPR.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern float gNullHight[3];
// CClientUIPR

IMPLEMENT_DYNAMIC(CClientUIPR, CClientUI)

BEGIN_MESSAGE_MAP(CClientUIPR, CClientUI)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CClientUIPR::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CClientUIPR::OnUpdateApplicationLook)
	ON_COMMAND(ID_BASIC_LEVEL, &CClientUIPR::OnBasicLevel)
	ON_COMMAND(ID_BASIC_APPLICATION, &CClientUIPR::OnBasicApplication)
	ON_COMMAND(ID_BASIC_DAMPING, &CClientUIPR::OnBasicDamping)
	ON_COMMAND(ID_BASIC_LINERIZATION, &CClientUIPR::OnBasicLinerization)
	ON_COMMAND(ID_BASIC_OTHER, &CClientUIPR::OnBasicOther)
	ON_COMMAND(ID_DISPLAY_DISPLAY, &CClientUIPR::OnDisplayDisplay)
	ON_COMMAND(ID_DIAGNOSIS_DIAGNOSIS, &CClientUIPR::OnDiagnosisDiagnosis)
	ON_COMMAND(ID_SERVICE_RESET, &CClientUIPR::OnServiceReset)
	ON_COMMAND(ID_SERVICE_CURRENTOUTPUT, &CClientUIPR::OnServiceCurrentoutput)
	ON_COMMAND(ID_SERVICE_PIN, &CClientUIPR::OnServicePin)
	ON_COMMAND(ID_SERVICE_OTHER, &CClientUIPR::OnServiceOther)
	ON_COMMAND(ID_SERVICE_FALSEECHO, &CClientUIPR::OnServiceFalseecho)
	ON_COMMAND(ID_ADVANCED_ADVANVCED1, &CClientUIPR::OnAdvancedAdvanvced1)
	ON_COMMAND(ID_ADVANCED_ADVANVCED2, &CClientUIPR::OnAdvancedAdvanvced2)
	ON_COMMAND(ID_DEVICEOP_LOAD, &CClientUIPR::OnDeviceopLoad)
	ON_COMMAND(ID_DEVICEOP_SAVE, &CClientUIPR::OnDeviceopSave)
	ON_COMMAND(ID_INFO_INFO, &CClientUIPR::OnInfo)
	ON_COMMAND(ID_DEVICEOP_REFRESH, &CClientUIPR::OnRefresh)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CClientUIPR 构造/析构

CClientUIPR::CClientUIPR()
:sendBytes(0), recvBytes(0), errBytes(0)
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);

}

CClientUIPR::~CClientUIPR()
{
}

int CClientUIPR::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);



	// 创建一个视图以占用框架的工作区
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("未能创建视图窗口\n");
		return -1;
	}

	m_wndRibbonBar.Create(this);
	InitializeRibbon();

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
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

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

	m_wndDeviceStat.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndDeviceStat);

	m_wndCurve.EnableDocking(CBRS_ALIGN_BOTTOM);
	DockPane(&m_wndCurve);

	// 启动刷新状态显示的计时器，10秒一刷
	SetTimer(1, 10000, NULL);
	OnTimer(1);


	return 0;
}

BOOL CClientUIPR::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	m_strTitle.LoadString(IDS_PRTITLE);
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

void CClientUIPR::InitializeRibbon()
{
	BOOL bNameValid;

	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_RIBBON_FILE);
	ASSERT(bNameValid);

	// 加载面板图像:
	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_BUTTONS);

	// 初始主按钮://yaol 3.17
	//m_MainButton.SetImage(IDB_MAIN);
	//m_MainButton.SetText(_T("\nf"));
	//m_MainButton.SetToolTipText(strTemp);
/*
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

	// 下面开始画工具栏
	
	// 1. 仪表设置
	bNameValid = strTemp.LoadString(IDS_RIBBON_DEVICESETTINGS);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategoryDeviceSettings = m_wndRibbonBar.AddCategory(strTemp, IDB_WRITESMALL, IDB_WRITELARGE);

	// 1.1 存取panel
	bNameValid = strTemp.LoadString(IDS_RIBBON_DEVICEOP);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelOP = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	
	// 1.1.1 读取
	bNameValid = strTemp.LoadString(IDS_RIBBON_LOAD);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLoad = new CMFCRibbonButton(ID_DEVICEOP_LOAD, strTemp, 0, 0);
	pPanelOP->Add(pBtnLoad);
	
	// 1.1.2 存储
	bNameValid = strTemp.LoadString(IDS_RIBBON_SAVE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnSave = new CMFCRibbonButton(ID_DEVICEOP_SAVE, strTemp, 0, 0);
	pPanelOP->Add(pBtnSave);

	// 1.1.3 刷新
	bNameValid = strTemp.LoadString(IDS_DEVICEOP_REFRESH);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnRefresh = new CMFCRibbonButton(ID_DEVICEOP_REFRESH, strTemp, 0, 0);
	pPanelOP->Add(pBtnRefresh);

	// 1.2 基本设置 panel
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelBasic = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));


	// 1.2.1 物位调整
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC_LEVEL);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLevel = new CMFCRibbonButton(ID_BASIC_LEVEL, strTemp, 0, 0);
	pPanelBasic->Add(pBtnLevel);

	// 1.2.2 物料性质
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC_APPLICATION);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnApplication = new CMFCRibbonButton(ID_BASIC_APPLICATION, strTemp, 0, 0);
	pPanelBasic->Add(pBtnApplication);

	// 1.2.3 阻尼时间
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC_DAMPING);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnDamping = new CMFCRibbonButton(ID_BASIC_DAMPING, strTemp, 0, 0);
	pPanelBasic->Add(pBtnDamping);
	
	// 1.2.4 输出映射
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC_LINEARIZATION);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnLinearization = new CMFCRibbonButton(ID_BASIC_LINERIZATION, strTemp, 0, 0);
	pPanelBasic->Add(pBtnLinearization);

	// 1.2.5 其他
	bNameValid = strTemp.LoadString(IDS_RIBBON_BASIC_OTHER);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnOther = new CMFCRibbonButton(ID_BASIC_OTHER, strTemp, 0, 0);
	pPanelBasic->Add(pBtnOther);

	// 1.3 显示
	bNameValid = strTemp.LoadString(IDS_RIBBON_DISPLAY);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelDisplay = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	
	// 1.3.1 显示
	bNameValid = strTemp.LoadString(IDS_RIBBON_DISPLAY);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnDisplay = new CMFCRibbonButton(ID_DISPLAY_DISPLAY, strTemp, 0, 0);
	pPanelDisplay->Add(pBtnDisplay);

	// 1.4 诊断
	bNameValid = strTemp.LoadString(IDS_RIBBON_DIAGNOSIS);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelDiagnosis = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	
	// 1.4.1 诊断
	bNameValid = strTemp.LoadString(IDS_RIBBON_DIAGNOSIS);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnDiagnosis = new CMFCRibbonButton(ID_DIAGNOSIS_DIAGNOSIS, strTemp, 0, 0);
	pPanelDiagnosis->Add(pBtnDiagnosis);

	// 1.5 服务
	bNameValid = strTemp.LoadString(IDS_RIBBON_SERVICE);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelService = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));

	// 1.5.1 输出电流
	bNameValid = strTemp.LoadString(IDS_RIBBON_CURRENTOUTPUT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnCurrent = new CMFCRibbonButton(ID_SERVICE_CURRENTOUTPUT, strTemp, 0, 0);
	pPanelService->Add(pBtnCurrent);

	// 1.5.2 复位
	bNameValid = strTemp.LoadString(IDS_RIBBON_RESET);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnReset = new CMFCRibbonButton(ID_SERVICE_RESET, strTemp, 0, 0);
	pPanelService->Add(pBtnReset);

	// 1.5.3 虚假回波
	bNameValid = strTemp.LoadString(IDS_RIBBON_FALSEECHO);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnFalseEcho = new CMFCRibbonButton(ID_SERVICE_FALSEECHO, strTemp, 0, 0);
	pPanelService->Add(pBtnFalseEcho);

	// 1.5.4 密码
	bNameValid = strTemp.LoadString(IDS_RIBBON_PIN);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnPin = new CMFCRibbonButton(ID_SERVICE_PIN, strTemp, 0, 0);
	pPanelService->Add(pBtnPin);

	// 1.5.5 其他
	bNameValid = strTemp.LoadString(IDS_RIBBON_OTHER);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnServiceOther = new CMFCRibbonButton(ID_SERVICE_OTHER, strTemp, 0, 0);
	pPanelService->Add(pBtnServiceOther);

	// 1.6 高级设置
	bNameValid = strTemp.LoadString(IDS_RIBBON_ADVANCED);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelAdvanced = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	
	// 1.6.1 高级设置一
	bNameValid = strTemp.LoadString(IDS_RIBBON_ADVANCED1);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnAdvanced1 = new CMFCRibbonButton(ID_ADVANCED_ADVANVCED1, strTemp, 0, 0);
	pPanelAdvanced->Add(pBtnAdvanced1);
	
	// 1.6.2 高级设置二
	bNameValid = strTemp.LoadString(IDS_RIBBON_ADVANCED2);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnAdvanced2 = new CMFCRibbonButton(ID_ADVANCED_ADVANVCED2, strTemp, 0, 0);
	pPanelAdvanced->Add(pBtnAdvanced2);

	// 1.7 信息
	bNameValid = strTemp.LoadString(IDS_RIBBON_INFO);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelInfo = pCategoryDeviceSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	
	// 1.7.1 信息
	bNameValid = strTemp.LoadString(IDS_RIBBON_INFO);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnInfo = new CMFCRibbonButton(ID_INFO_INFO, strTemp, 0, 0);
	pPanelInfo->Add(pBtnInfo);

	// 2. 软件设置
	bNameValid = strTemp.LoadString(IDS_RIBBON_SOFTWARESETTINGS);
	ASSERT(bNameValid);
	CMFCRibbonCategory* pCategorySoftwareSettings = m_wndRibbonBar.AddCategory(strTemp, IDB_WRITESMALL, IDB_WRITELARGE);

	// 2.1 连接
	bNameValid = strTemp.LoadString(IDS_RIBBON_CONNECTION);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelConnection = pCategorySoftwareSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	pPanelConnection;

	// 2.1.1 重新连接
	bNameValid = strTemp.LoadString(IDS_RIBBON_RECONNECT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnReconnect = new CMFCRibbonButton(ID_RECONNECT, strTemp, 0, 0);
	pPanelConnection->Add(pBtnReconnect);

	// 2.2 用户
	bNameValid = strTemp.LoadString(IDS_RIBBON_USER);
	ASSERT(bNameValid);
	CMFCRibbonPanel* pPanelUser = pCategorySoftwareSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	pPanelUser;

	// 2.2.1 切换用户
	bNameValid = strTemp.LoadString(IDS_RIBBON_CHANGERUSER);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnChangeUser = new CMFCRibbonButton(ID_CHANGEUSER, strTemp, 0, 0);
	pPanelUser->Add(pBtnChangeUser);

	// 2.2.2 用户管理
	bNameValid = strTemp.LoadString(IDS_RIBBON_USERMANAGEMENT);
	ASSERT(bNameValid);
	CMFCRibbonButton* pBtnUserMangement = new CMFCRibbonButton(ID_USERMANAGEMENT, strTemp, 0, 0);
	pPanelUser->Add(pBtnUserMangement);

	//// 2.3 语言
	//bNameValid = strTemp.LoadString(IDS_RIBBON_LANGUAGE);
	//ASSERT(bNameValid);
	//CMFCRibbonPanel* pPanelLanguage = pCategorySoftwareSettings->AddPanel(strTemp, m_PanelImages.ExtractIcon(27));
	//pPanelLanguage;

	// 将元素添加到选项卡右侧:
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE);
	ASSERT(bNameValid);
	CMFCRibbonButton* pVisualStyleButton = new CMFCRibbonButton(UINT(-1), strTemp, UINT(-1), UINT(-1));

	pVisualStyleButton->SetMenu(IDR_THEME_MENU, FALSE /* 无默认命令*/, TRUE /* 右对齐*/);

	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_TIP);
	ASSERT(bNameValid);
	pVisualStyleButton->SetToolTipText(strTemp);
	bNameValid = strTemp.LoadString(IDS_RIBBON_STYLE_DESC);
	ASSERT(bNameValid);
	pVisualStyleButton->SetDescription(strTemp);
	m_wndRibbonBar.AddToTabs(pVisualStyleButton);

	// 添加快速访问工具栏命令:
	CList<UINT, UINT> lstQATCmds;

	//lstQATCmds.AddTail(ID_FILE_NEW);
	//lstQATCmds.AddTail(ID_FILE_OPEN);
	//lstQATCmds.AddTail(ID_FILE_SAVE);
	//lstQATCmds.AddTail(ID_FILE_PRINT_DIRECT);

//	m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);

	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));
}

BOOL CClientUIPR::CreateDockingWindows()
{
	BOOL bNameValid;

	// 创建输出窗口
	CString strOutputWndPR;
	bNameValid = strOutputWndPR.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndCurve.Create(strOutputWndPR, this, CRect(0, 0, 200, 200),TRUE, ID_WND_OUTPUT, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	// 创建状态窗口
	CString str;
	bNameValid = str.LoadString(IDS_DEVICESTAT_WND);
	ASSERT(bNameValid);
	if (!m_wndDeviceStat.Create(str, this, CRect(0, 0, 200, 200),TRUE, ID_WND_DEVICESTAT, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建状态窗口\n");
		return FALSE; // 未能创建
	}


	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CClientUIPR::SetDockingWindowIcons(BOOL /*bHiColorIcons*/)
{
	//HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	//m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// CClientUIPR 诊断

#ifdef _DEBUG
void CClientUIPR::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CClientUIPR::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CClientUIPR 消息处理程序

void CClientUIPR::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 将焦点前移到视图窗口
	m_wndView.SetFocus();
}

BOOL CClientUIPR::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 否则，执行默认处理
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CClientUIPR::OnApplicationLook(UINT id)
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

void CClientUIPR::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}
void CClientUIPR::OnBasicLevel()
{
	m_wndView.Show(IDD_LEVEL_ADJUSTMENT_PR);
}

void CClientUIPR::OnBasicApplication()
{
	m_wndView.Show(IDD_APPLICATION_PR);
}

void CClientUIPR::OnBasicDamping()
{
	m_wndView.Show(IDD_DAMPING_PR);
}

void CClientUIPR::OnBasicLinerization()
{
	m_wndView.Show(IDD_LINEARIZATION_PR);
}

void CClientUIPR::OnBasicOther()
{
	m_wndView.Show(IDD_OTHERSETTINGS_PR);
}

void CClientUIPR::OnDisplayDisplay()
{
	m_wndView.Show(IDD_DISPLAY_PR);
}

void CClientUIPR::OnDiagnosisDiagnosis()
{
	m_wndView.Show(IDD_DIAGNOSIS_PR);
}

void CClientUIPR::OnServiceCurrentoutput()
{
	m_wndView.Show(IDD_CURRENTOUTPUT_PR);
}

void CClientUIPR::OnServiceReset()
{
	m_wndView.Show(IDD_RESET_PR);
}

void CClientUIPR::OnServicePin()
{
	m_wndView.Show(IDD_PIN_PR);
}

void CClientUIPR::OnServiceOther()
{
	m_wndView.Show(IDD_SERVICEOTHER_PR);
}

void CClientUIPR::OnServiceFalseecho()
{
	m_wndView.Show(IDD_FALSEECHO_PR);
}

void CClientUIPR::OnAdvancedAdvanvced1()
{
	m_wndView.Show(IDD_ADVANCEDSETUP1_PR);
}

void CClientUIPR::OnAdvancedAdvanvced2()
{
	m_wndView.Show(IDD_ADVANCEDSETUP2_PR);
}

void CClientUIPR::OnInfo()
{
	m_wndView.Show(IDD_INFO);
}

void CClientUIPR::OnDeviceopLoad()
{
	m_wndView.Load();
}

void CClientUIPR::OnDeviceopSave()
{
	m_wndView.Save();
}

void CClientUIPR::OnRefresh()
{
	theApp.m_pClient->RefreshId();
}

void CClientUIPR::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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

void CClientUIPR::SetSendBytes( long )
{

}

void CClientUIPR::SetRecvBytes( long )
{

}

void CClientUIPR::SetErrBytes( long )
{

}