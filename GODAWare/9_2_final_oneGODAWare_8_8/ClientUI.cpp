// ClientUI.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "ClientUI.h"
#include "UserManageDlg.h"


// CClientUI

IMPLEMENT_DYNCREATE(CClientUI, CFrameWndEx)

CClientUI::CClientUI()
{

}

CClientUI::~CClientUI()
{
	if ( !theApp.m_pClient )
	{
		theApp.m_pClient->Exit();
	}
}


BEGIN_MESSAGE_MAP(CClientUI, CFrameWndEx)

	ON_COMMAND(ID_USERMANAGEMENT, &CClientUI::OnUsermanagement)
	ON_COMMAND(ID_RECONNECT, &CClientUI::OnReconnect)
END_MESSAGE_MAP()

void CClientUI::OnReconnect()
{
	_TCHAR   szFileName[MAX_PATH];  
	GetModuleFileName(theApp.m_hInstance,   szFileName,   MAX_PATH);
	ShellExecute(NULL,   _T("Open"),   szFileName,   NULL,   NULL,   SW_SHOWNORMAL);
	PostQuitMessage(0);
}

void CClientUI::OnUsermanagement()
{
	CUserManage& userManage = theApp.m_pClient->GetUserManage();
	CUserManageDlg dlg(userManage, IDD_USERMANAGE, this);
	dlg.DoModal();
}
