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

// ChildViewGR.h : CChildViewGR 类的接口
//


#pragma once

#include "LevelAdjustmentDlgGR.h"
#include "ApplicationDlgGR.h"
#include "DampingDlgGR.h"
#include "LinearizationDlgGR.h"
#include "OtherSettingsDlgGR.h"
#include "DisplayDlgGR.h"
#include "DiagnosisDlgGR.h"
#include "CurrentOutputDlgGR.h"
#include "ResetDlgGR.h"
#include "FalseEchoDlgGR.h"
#include "PinDlgGR.h"
#include "ServiceOtherDlgGR.h"
#include "Advanced1DlgGR.h"
#include "Advanced2DlgGR.h"
#include "../InfoDlg.h"

// CChildViewGR 窗口

class CChildViewGR : public CWnd
{
// 构造
public:
	CChildViewGR();

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
	virtual ~CChildViewGR();

private:
	COperationDlg* m_pCurrentDlg;

	CLevelAdjustmentDlgGR m_wndLevelAdjustment;
	CApplicationDlgGR m_wndApplication;
	CDampingDlgGR m_wndDamping;
	CLinearizationDlgGR m_wndLinearization;
	COtherSettingsDlgGR m_wndOtherSettings;
	CDisplayDlgGR m_wndDisplay;
	CDiagnosisDlgGR m_wndDiagnosis;
	CCurrentOutputDlgGR m_wndCurrentOutput;
	CResetDlgGR m_wndReset;
	CFalseEchoDlgGR m_wndFalseEcho;
	CPinDlgGR m_wndPin;
	CServiceOtherDlgGR m_wndServiceOther;
	CAdvanced1DlgGR m_wndAdvanced1;
	CAdvanced2DlgGR m_wndAdvanced2;
	CInfoDlg m_wndInfo;


	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

