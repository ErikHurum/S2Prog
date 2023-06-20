#pragma once

#include "cominc.h"

#include "resource.h"
#include "pvcscontrolobjectinfo.h"
#include "atltypes.h"
#include "pvcswagocontrol.h"
#include "afxwin.h"
#include "afxcmn.h"
#include ".\writetimeouts.h" //added by mohit
#include "pvcscontrolobjectstatic.h"
#include "pvcscontrolobjectdlgbutton.h"
#include "pvcscontrolobjectdlgspinbox.h"
#include "warningmessage.h"//Added JSD 22-08-2007

// Class: CPvcsControlObjectDlg
// Description: The control object controller dialog
//Start JSD 07MARCH2007
struct WarningMessageStroge
{
	CString ControlObjName;
	CString ObjWarningMessage;
};
//End JSD 07MARCH2007

class CPvcsControlObjectDlg : public CDialog
{
	friend CPvcsControlObjectDlg& theController();
	friend class CDxfLayout;

	DECLARE_DYNAMIC(CPvcsControlObjectDlg)

	CPvcsControlObjectDlg(CWnd* pParent = NULL);   // standard constructor

public:
	virtual ~CPvcsControlObjectDlg();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();

	void GetData(void);
	void Draw(void);
	//void SetTimeOut(bool param_bTimeOut = true);
	CRgn& CreateRgn(CRgn& Rgn);

// Dialog Data
	enum { IDD = IDD_PVCSOBJECTCONTROLDLG };
	CWarningMessage WarningMessageObj;
private:
	void Display(const CPvcsControlObjectInfo& param_infoObject, CPoint param_point, CWnd* param_pParent);
	afx_msg void OnTimer(UINT nIDEvent);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CWriteTimeouts wt; //line added by mohit

//	UINT m_uiValue;
public:

	typedef map < CString , CPvcsControlObject *> ControllerMap;
	typedef ControllerMap::const_iterator ControllerMap_it;

	ControllerMap m_mapController;	//The controller objects' map

	CPvcsControlObjectStatic m_defaultController;	// The default controller

	void AddControllers(void);
	CPvcsControlObject& GetController(const CPvcsControlObjectInfo& param_info);

private:
	CString m_SystemIP;
	CRect m_rectWnd;		// The window rectangle
	bool m_bRightPointer;	// Flag to determine if window pointer is on the right
	bool m_bBottomPointer;	// Falg to determine if the window pointer is at the bottom
	bool m_bTopPointer;		// Falg to determine if the window pointer is at the Top
	CPvcsControlObjectInfo m_infoObject; // The current control object info
	CRect m_rectText;		// The rectangle for text display
	HDC m_hMemDC;			// Handle to Memory DC
	CPvcsControlObject* m_pController;	// The controller class for the object
	bool m_bIsTopAdjusted;

	typedef std::list <CPvcsControlObjectDlgButton*> ButtonList;
	typedef ButtonList::const_iterator ButtonList_it;

	ButtonList m_Button;	// The buttons on the dialog

	typedef std::list <CPvcsControlObjectDlgSpinBox*> SpinBoxList;
	typedef SpinBoxList::const_iterator SpinBoxList_it;

	SpinBoxList m_SpinBox;	// The spin boxes on the dialog

	bool m_bResponseTimedOut;		// Flag to determine if the control object is faulty
    volatile bool m_PasswordUnlock;
public:
	const CPvcsControlObjectInfo& GetControlobjectInfo(void);
	afx_msg LRESULT OnTimeOut(WPARAM wParam, LPARAM lParam);
	bool GetTimeOut(void);
	static int m_iEditExist;//Added JSD 22FEB2007
	//static LPTSTR WarningMessage1;
	afx_msg void OnBnClickedCheck1();
	CButton m_chk;
	CEdit m_editwin;
	CEdit m_editwinPassword;
	int load_check;
	static vector <WarningMessageStroge> WarningMessageVector;//JSD 07MARCH2007
	static CString CurrentDisplayObjName;//JSD 07MARCH2007
	static int objectfoundstatus;//JSD 07MARCH2007
	static CString WarningMessagetemp;
	static CString dispalyObjName;
	CString GetSystemIP();
	afx_msg void OnBnClickedButtonOne();
	afx_msg void OnEnChangeEditValue();
	afx_msg void OnBnClickedButtonTwo();
	void OnCloseWarningMessageWindow();//Added JSD 20-09-2007
	static bool FirstTimeVectorLoading;//Added JSD 20-09-2007


	bool SetValueToSpinCtrl(CString pValue);
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
};

CPvcsControlObjectDlg& theController();
