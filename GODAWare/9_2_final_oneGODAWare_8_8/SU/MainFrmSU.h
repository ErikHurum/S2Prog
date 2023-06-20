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

// MainFrmSU.h : CClientUISU ��Ľӿ�
//

#pragma once
#include "ChildViewSU.h"

#include "OutputWndSU.h"
#include "LevelAdjustmentDlgSU.h"
#include "../ClientUI.h"
#include "DeviceStatWndSU.h"

class CClientUISU : public CClientUI
{
	
public:
	CClientUISU();
protected: 
	DECLARE_DYNAMIC(CClientUISU)

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
	virtual ~CClientUISU();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;

	CChildViewSU    m_wndView;

	COutputWndSU	m_wndCurve;
	CDeviceStatWndSU m_wndDeviceStat;


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

	void SetNullHight(double hight, size_t index) {m_wndDeviceStat.SetNullHight(hight, index);}
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


