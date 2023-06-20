#pragma once
#include "PvcsToolBarEmgButton.h"
#include "PvcsToolBarPumpButton.h"
#include "PvcsToolBarAlarmButton.h"
// CPvcsToolBar


class CPvcsToolBar : public CToolBar
{
	DECLARE_DYNAMIC(CPvcsToolBar)

public:
	CPvcsToolBar();
	virtual ~CPvcsToolBar();

	CPvcsToolBarAlarmButton *m_pPvcsToolBarAlarmButton;
	
	vector <CPvcsToolBarEmgButton *> m_PvcsToolBarEmgButton;
	vector <CPvcsToolBarPumpButton *> m_PvcsToolBarPumpButton;
protected:
	DECLARE_MESSAGE_MAP()
	void OnBnClickedPumpButton(int Id);
public:
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedAlarmbutton();
	afx_msg void OnBnClickedPumpButton1();
	afx_msg void OnBnClickedPumpButton2();
	afx_msg void OnBnClickedPumpButton3();
	afx_msg void OnBnClickedPumpButton4();
	afx_msg void OnBnClickedPumpButton5();
};


