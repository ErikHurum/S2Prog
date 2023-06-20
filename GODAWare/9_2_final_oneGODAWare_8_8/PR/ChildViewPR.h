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

// ChildViewPR.h : CChildViewPR 类的接口
//


#pragma once

#include "LevelAdjustmentDlgPR.h"
#include "ApplicationDlgPR.h"
#include "DampingDlgPR.h"
#include "LinearizationDlgPR.h"
#include "OtherSettingsDlgPR.h"
#include "DisplayDlgPR.h"
#include "DiagnosisDlgPR.h"
#include "CurrentOutputDlgPR.h"
#include "ResetDlgPR.h"
#include "FalseEchoDlgPR.h"
#include "PinDlgPR.h"
#include "ServiceOtherDlgPR.h"
#include "Advanced1DlgPR.h"
#include "Advanced2DlgPR.h"
#include "../InfoDlg.h"

// CChildViewPR 窗口

class CChildViewPR : public CWnd
{
// 构造
public:
	CChildViewPR();

// 属性
public:

// 操作
public:
	void Show(unsigned dlgId);
	void Load();
	void Save();

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildViewPR();

private:
	COperationDlg* m_pCurrentDlg;

	CLevelAdjustmentDlgPR m_wndLevelAdjustment;
	CApplicationDlgPR m_wndApplication;
	CDampingDlgPR m_wndDamping;
	CLinearizationDlgPR m_wndLinearization;
	COtherSettingsDlgPR m_wndOtherSettings;
	CDisplayDlgPR m_wndDisplay;
	CDiagnosisDlgPR m_wndDiagnosis;
	CCurrentOutputDlgPR m_wndCurrentOutput;
	CResetDlgPR m_wndReset;
	CFalseEchoDlgPR m_wndFalseEcho;
	CPinDlgPR m_wndPin;
	CServiceOtherDlgPR m_wndServiceOther;
	CAdvanced1DlgPR m_wndAdvanced1;
	CAdvanced2DlgPR m_wndAdvanced2;
	CInfoDlg m_wndInfo;

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

