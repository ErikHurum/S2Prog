#pragma once
#include "afxcmn.h"
#include "OperationDlg.h"
#include "UserManage.h"
#include "afxwin.h"
// CUserManageDlg dialog

class CUserManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserManageDlg)

public:
	CUserManageDlg(CUserManage& userManage, UINT id, CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserManageDlg();

// Dialog Data
	enum { IDD = IDD_USERMANAGE };

	void LoadData();
	void SaveData();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_userlist;
	CList<UserInfo> m_user;
	afx_msg void OnBnClickedModify();
	CEdit m_username;
	CEdit m_password;
	CEdit m_password_confirm;

	afx_msg void OnNMClickUserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	CButton m_factory;
	CButton m_advance;
	CButton m_normal;
	afx_msg void OnBnClickedAdd();
	void RefreshListCtrl();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedCancel();

private:
	CUserManage& m_userManage;
public:
	afx_msg void OnLvnItemchangedUserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeUsername();
};
