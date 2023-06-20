// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// MainFrmPR.h : CClientUIPR ��Ľӿ�
//

#pragma once
#include "ChildViewPR.h"

#include "OutputWndPR.h"
#include "LevelAdjustmentDlgPR.h"
#include "../ClientUI.h"
#include "../DeviceStatDlg.h"

class CClientUIPR : public CClientUI
{
	
public:
	CClientUIPR();
protected: 
	DECLARE_DYNAMIC(CClientUIPR)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	void SetSendBytes(long);
	void SetRecvBytes(long);
	void SetErrBytes(long);


// ʵ��
public:
	virtual ~CClientUIPR();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;

	CChildViewPR    m_wndView;

	COutputWndPR	m_wndCurve;
	CDeviceStatWnd m_wndDeviceStat;


	long sendBytes;
	long recvBytes;
	long errBytes;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	void InitializeRibbon();

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:

	void SetNullHight(double hight) {m_wndDeviceStat.SetNullHight(hight);}
	void SetOnline(bool bOnline) {m_wndDeviceStat.SetOnline(bOnline);}


	afx_msg void OnBasicLevel();
	afx_msg void OnBasicApplication();
	afx_msg void OnBasicDamping();
	afx_msg void OnBasicLinerization();
	afx_msg void OnBasicOther();
	afx_msg void OnDisplayDisplay();
	afx_msg void OnDiagnosisDiagnosis();
	afx_msg void OnServiceReset();
	afx_msg void OnServiceCurrentoutput();
	afx_msg void OnServicePin();
	afx_msg void OnServiceOther();
	afx_msg void OnServiceFalseecho();
	afx_msg void OnAdvancedAdvanvced1();
	afx_msg void OnAdvancedAdvanvced2();
	afx_msg void OnDeviceopLoad();
	afx_msg void OnDeviceopSave();
	afx_msg void OnInfo();
	afx_msg void OnRefresh();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


