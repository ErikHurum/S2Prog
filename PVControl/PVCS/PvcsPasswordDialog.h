#include "afxdialogex.h"
#pragma once


// PvcsPasswordDialog dialog

class PvcsPasswordDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PvcsPasswordDialog)

public:
	PvcsPasswordDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~PvcsPasswordDialog();

// Dialog Data
	enum { IDD = IDD_PASSWORD };

private:
	CRect m_rectWnd;		// The window rectangle
	bool m_bRightPointer;	// Flag to determine if window pointer is on the right
	bool m_bBottomPointer;	// Falg to determine if the window pointer is at the bottom
	bool m_bTopPointer;		// Falg to determine if the window pointer is at the Top
	CPvcsControlObjectInfo m_infoObject; // The current control object info
	CRect m_rectText;		// The rectangle for text display
	HDC m_hMemDC;			// Handle to Memory DC
	CPvcsControlObject* m_pController;	// The controller class for the object

protected:
    CString Password;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	const CPvcsControlObjectInfo& GetControlobjectInfo(void);


	DECLARE_MESSAGE_MAP()
public:
    static int m_dialoginitalise;
    static bool DialgVisible;



	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedOk();
};

PvcsPasswordDialog& thePasswordMessage();


