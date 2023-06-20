// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// MainFrmPR.h : CClientUIPR 类的接口
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

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	void SetSendBytes(long);
	void SetRecvBytes(long);
	void SetErrBytes(long);


// 实现
public:
	virtual ~CClientUIPR();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
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

// 生成的消息映射函数
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


