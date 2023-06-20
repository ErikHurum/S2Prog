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

// ChildViewSU.h : CChildViewSU 类的接口
//


#pragma once

#include "LevelAdjustmentDlgSU.h"
#include "ApplicationDlgSU.h"
#include "DampingDlgSU.h"
#include "LinearizationDlgSU.h"
#include "OtherSettingsDlgSU.h"
#include "DisplayDlgSU.h"
#include "DiagnosisDlgSU.h"
#include "CurrentOutputDlgSU.h"
#include "ResetDlgSU.h"
#include "FalseEchoDlgSU.h"
#include "PinDlgSU.h"
#include "ServiceOtherDlgSU.h"
#include "Advanced1DlgSU.h"
#include "Advanced2DlgSU.h"
#include "../InfoDlg.h"

// CChildViewSU 窗口

class CChildViewSU : public CWnd
{
// 构造
public:
	CChildViewSU();

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
	virtual ~CChildViewSU();

private:
	COperationDlg* m_pCurrentDlg;

	CLevelAdjustmentDlgSU m_wndLevelAdjustment;
	CApplicationDlgSU m_wndApplication;
	CDampingDlgSU m_wndDamping;
	CLinearizationDlgSU m_wndLinearization;
	COtherSettingsDlgSU m_wndOtherSettings;
	CDisplayDlgSU m_wndDisplay;
	CDiagnosisDlgSU m_wndDiagnosis;
	CCurrentOutputDlgSU m_wndCurrentOutput;
	CResetDlgSU m_wndReset;
	CFalseEchoDlgSU m_wndFalseEcho;
	CPinDlgSU m_wndPin;
	CServiceOtherDlgSU m_wndServiceOther;
	CAdvanced1DlgSU m_wndAdvanced1;
	CAdvanced2DlgSU m_wndAdvanced2;
	CInfoDlg m_wndInfo;

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

