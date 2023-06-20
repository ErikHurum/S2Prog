#if !defined(AFX_USERPROGRAM_H__35BC1E2C_A5AF_47BB_91F2_6990A314F5D3__INCLUDED_)
#define AFX_USERPROGRAM_H__35BC1E2C_A5AF_47BB_91F2_6990A314F5D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserProgram.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserProgram dialog

class CUserProgram : public CDialog
{
// Construction
public:
	void OnChgLanguage();
	CUserProgram(CWnd* pParent = NULL);   // standard constructor
	void OnLoadData(); 

	int	    m_nPrevType;
	int 	m_nPrevUnit;
	float   m_nP006;
	float   m_nP007;
	float   m_nP110;
	float   m_nP111;
	float   m_nP112;
	float   m_nP113;
	float   m_nTotalV;
	float   m_nZeroLin;
// Dialog Data
	//{{AFX_DATA(CUserProgram)	
	enum { IDD = IDD_LINEDIT };
	CComboBox	m_cType;
	CComboBox	m_cUnit;
	CProgressCtrl	m_cProgress;
	double	m_nSemi1;
	double	m_nSemi2;
	double	m_nSemi3;
	double	m_nL1;
	double	m_nL3;
	double	m_nD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserProgram)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:

protected:
	int m_nTimer;
	// Generated message map functions
	//{{AFX_MSG(CUserProgram)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnLoad();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnStop();
	afx_msg void OnCreateLin();
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnButtonZero();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERPROGRAM_H__35BC1E2C_A5AF_47BB_91F2_6990A314F5D3__INCLUDED_)
