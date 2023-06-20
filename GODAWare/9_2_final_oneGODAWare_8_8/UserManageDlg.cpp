// UserManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFC.h"
#include "UserManageDlg.h"
#include "UserManage.h"

// CUserManageDlg dialog

IMPLEMENT_DYNAMIC(CUserManageDlg, CDialogEx)

CUserManageDlg::CUserManageDlg(CUserManage& userManage, UINT id, CWnd* pParent)
:m_userManage(userManage), CDialogEx(id, pParent)
{

}

CUserManageDlg::~CUserManageDlg()
{
}

void CUserManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERINFO, m_userlist);
	DDX_Control(pDX, IDC_USERNAME, m_username);
	DDX_Control(pDX, IDC_PASSWORD, m_password);
	DDX_Control(pDX, IDC_PASSWORD2, m_password_confirm);

	DDX_Control(pDX, IDC_RADIO1, m_factory);
	DDX_Control(pDX, IDC_RADIO2, m_advance);
	DDX_Control(pDX, IDC_RADIO3, m_normal);
}

BOOL CUserManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_userlist.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP); 
	CString usernamecol;
	CString usertypecol;
	usernamecol.LoadString(IDS_USERNAME);
	usertypecol.LoadString(IDS_USERTYPE);
	m_userlist.InsertColumn(0,usernamecol,LVCFMT_LEFT,250);
	m_userlist.InsertColumn(1,usertypecol,LVCFMT_LEFT,250);
	
	
	m_userManage.GetAllUser(m_user);
	

	for(int i=0; i< m_user.GetCount();i++)
	{

		m_userlist.InsertItem(LVIF_TEXT|LVIF_STATE, i, _T(""),0,LVIS_SELECTED,0,0);

		CString username,usertype;

		POSITION ps=m_user.FindIndex(i);
		username=m_user.GetAt(ps).name;
		
		switch(m_user.GetAt(ps).usertype)
		{
		case Factory:usertype.LoadString(IDS_USERTYPEFACTORY);break;
		case Advanced:usertype.LoadString(IDS_USERTYPEADVANCED);break;
		case Normal:usertype.LoadString(IDS_USERTYPENORMAL);break;
		
		}
		
		m_userlist.SetItemText(i,0,username);
		m_userlist.SetItemText(i,1,usertype);


	}

	return TRUE;
}

void CUserManageDlg::LoadData()
{

}

void CUserManageDlg::SaveData()
{

}

BEGIN_MESSAGE_MAP(CUserManageDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MODIFY, &CUserManageDlg::OnBnClickedModify)
	ON_NOTIFY(NM_CLICK, IDC_USERINFO, &CUserManageDlg::OnNMClickUserinfo)
	ON_BN_CLICKED(IDC_ADD, &CUserManageDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CUserManageDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDCANCEL, &CUserManageDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_USERNAME, &CUserManageDlg::OnEnChangeUsername)
END_MESSAGE_MAP()


// CUserManageDlg message handlers

void CUserManageDlg::OnBnClickedModify()
{
	// 先找出被选中的用户
	if (m_userlist.GetSelectionMark() == -1)
	{
		AfxMessageBox(IDS_SELECTAUSER);
		return;
	}
	
	if(m_factory.GetCheck()+m_advance.GetCheck()+m_normal.GetCheck()==0)
	{
		AfxMessageBox(IDS_SELECTUSERTYPE);
		return;
	}


	CString username;
	m_username.GetWindowText(username);
	if(username==_T(""))
	{

		AfxMessageBox(IDS_USERNAMENOTNULL);
		return;
	}
	if(!m_userManage.FindUser(username))
	{

		AfxMessageBox(IDS_USERNOTEXIST);
		return;
	}
	CString password,password2;
	m_password.GetWindowText(password);
	m_password_confirm.GetWindowText(password2);

	if(password==_T("") || password2==_T("") )
	{

		AfxMessageBox(IDS_PASSWORDNOTNULL);
		return;
	}

	if(password!=password2 )
	{

		AfxMessageBox(IDS_MSG_CONFIRMERR);
		return;
	}

	UserType type=Factory;
	if(m_factory.GetCheck())
	{
		type=Factory;
	}
	else if(m_advance.GetCheck())
	{
		type=Advanced;
	}
	else if(m_normal.GetCheck())
	{
		type=Normal;
	}

	m_userManage.EditUser(username,password,type);
	m_user.RemoveAll();

	m_userManage.GetAllUser(m_user);
	RefreshListCtrl();
	

}

void CUserManageDlg::OnNMClickUserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_factory.SetCheck(false);

	m_advance.SetCheck(false);

	m_normal.SetCheck(false);

	m_password.SetWindowText(_T(""));
	m_password_confirm.SetWindowText(_T(""));

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	pNMItemActivate ;


	int row=m_userlist.GetSelectionMark();
	
	CString username,usertype;
	
	username=m_userlist.GetItemText(row,0);
	m_username.SetWindowText(username);

	usertype=m_userlist.GetItemText(row,1);
	CString usertype_compared1,usertype_compared2,usertype_compared3;
	usertype_compared1.LoadString(IDS_USERTYPEFACTORY);
	usertype_compared2.LoadString(IDS_USERTYPEADVANCED);
	usertype_compared3.LoadString(IDS_USERTYPENORMAL);
	if(usertype==usertype_compared1)
	{
		m_factory.SetCheck(true);
	}
	else if(usertype==usertype_compared2)
	{
		m_advance.SetCheck(true);
	}
	else if(usertype==usertype_compared3)
	{
		m_normal.SetCheck(true);
	}
	

	*pResult = 0;
}

void CUserManageDlg::OnBnClickedAdd()
{
	// 检查输入值完整性

	if(m_factory.GetCheck()+m_advance.GetCheck()+m_normal.GetCheck()==0)
	{
		AfxMessageBox(IDS_SELECTUSERTYPE);
		return;
	}

	CString username;
	m_username.GetWindowText(username);
	if(username==_T(""))
	{
		
		AfxMessageBox(IDS_USERNAMENOTNULL);
		return;
	}

	CString password,password2;
	m_password.GetWindowText(password);
	m_password_confirm.GetWindowText(password2);

	if(password==_T("") || password2==_T("") )
	{

		AfxMessageBox(IDS_PASSWORDNOTNULL);
		return;
	}

	if(password!=password2 )
	{

		AfxMessageBox(IDS_MSG_CONFIRMERR);
		return;
	}

	if(m_userManage.FindUser(username))
	{

		AfxMessageBox(IDS_USERALREADYEXIST);
		return;
	}

	UserType type=Factory;
	if(m_factory.GetCheck())
	{
		type=Factory;
	}
	else if(m_advance.GetCheck())
	{
		type=Advanced;
	}
	else if(m_normal.GetCheck())
	{
		type=Normal;
	}
	m_userManage.AddUser(username,password,type);
	m_user.RemoveAll();

	m_userManage.GetAllUser(m_user);
	RefreshListCtrl();
}

void CUserManageDlg::RefreshListCtrl()
{
	m_userlist.DeleteAllItems();

	for(int i=0; i< m_user.GetCount();i++)
	{

		m_userlist.InsertItem(LVIF_TEXT|LVIF_STATE, i, _T(""),0,LVIS_SELECTED,0,0);

		CString username,usertype;

		POSITION ps=m_user.FindIndex(i);
		username=m_user.GetAt(ps).name;

		switch(m_user.GetAt(ps).usertype)
		{
		case Factory:usertype.LoadString(IDS_USERTYPEFACTORY);break;
		case Advanced:usertype.LoadString(IDS_USERTYPEADVANCED);break;
		case Normal:usertype.LoadString(IDS_USERTYPENORMAL);break;

		}

		m_userlist.SetItemText(i,0,username);
		m_userlist.SetItemText(i,1,usertype);


	}
}
void CUserManageDlg::OnBnClickedDelete()
{
	if (m_userlist.GetSelectionMark() == -1)
	{
		AfxMessageBox(IDS_SELECTAUSER);
		return;
	}

	CString username;
	m_username.GetWindowText(username);
	if(username==_T(""))
	{

		AfxMessageBox(IDS_USERNAMENOTNULL);
		return;
	}
	if(!m_userManage.FindUser(username))
	{

		AfxMessageBox(IDS_USERNOTEXIST);
		return;
	}

	m_userManage.DeleteUser(username);
	m_user.RemoveAll();

	m_userManage.GetAllUser(m_user);
	RefreshListCtrl();
}

void CUserManageDlg::OnBnClickedCancel()
{
	
	//theApp.m_pControl->m_pMainFrm->OnBasicLevel();
	OnCancel();
}


void CUserManageDlg::OnEnChangeUsername()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
