#pragma once
#include "afxwin.h"
#include "warningmessage.h"//Added by JSD 22-08-2007
#include "pvcscontrolobjectinfo.h"


// PVCSWarningMessage dialog

class PVCSWarningMessage : public CDialog
{
	DECLARE_DYNAMIC(PVCSWarningMessage)

public:
	PVCSWarningMessage(CWnd* pParent = NULL);   // standard constructor
	virtual ~PVCSWarningMessage();
	MSXML2::IXMLDOMNodePtr m_pFileNode;

// Dialog Data
	enum { IDD = IDD_WARNING_MESSAGE };

public:
	//afx_msg virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//const CPvcsControlObjectInfo& GetControlobjectInfo(void);
	CString returnedittext();
	CEdit m_warningMessageedit;
	static CString m_WarningMessage;
	static int m_dialoginitalise;
	LPTSTR tempbuffer;
	//afx_msg void OnBnClickedButtonOk();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButtonOn();	
	afx_msg void OnClose(); 
	static bool DialgVisible;
	static LPTSTR WarningMessage1;//added JSD 29MARCH2007
	CWarningMessage WarningMessageObj1;
	CWarningMessage WarningMessageObj2;
	void onCommandTransfer();
};

PVCSWarningMessage& theWarningMessage();
