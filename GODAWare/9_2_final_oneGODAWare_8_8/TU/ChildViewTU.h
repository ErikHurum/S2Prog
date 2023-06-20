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

// ChildViewTU.h : CChildViewTU 类的接口
//


#pragma once

#include "LevelAdjustmentDlgTU.h"
#include "ApplicationDlgTU.h"
#include "DampingDlgTU.h"
#include "LinearizationDlgTU.h"
#include "OtherSettingsDlgTU.h"
#include "DisplayDlgTU.h"
#include "DiagnosisDlgTU.h"
#include "CurrentOutputDlgTU.h"
#include "ResetDlgTU.h"
#include "FalseEchoDlgTU.h"
#include "PinDlgTU.h"
#include "ServiceOtherDlgTU.h"
#include "Advanced1DlgTU.h"
#include "Advanced2DlgTU.h"
#include "../InfoDlg.h"
// CChildViewTU 窗口

class CChildViewTU : public CWnd
{
// 构造
public:
	CChildViewTU();

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
	virtual ~CChildViewTU();

private:
	COperationDlg* m_pCurrentDlg;

	CLevelAdjustmentDlgTU m_wndLevelAdjustment;
	CApplicationDlgTU m_wndApplication;
	CDampingDlgTU m_wndDamping;
	CLinearizationDlgTU m_wndLinearization;
	COtherSettingsDlgTU m_wndOtherSettings;
	CDisplayDlgTU m_wndDisplay;
	CDiagnosisDlgTU m_wndDiagnosis;
	CCurrentOutputDlgTU m_wndCurrentOutput;
	CResetDlgTU m_wndReset;
	CFalseEchoDlgTU m_wndFalseEcho;
	CPinDlgTU m_wndPin;
	CServiceOtherDlgTU m_wndServiceOther;
	CAdvanced1DlgTU m_wndAdvanced1;
	CAdvanced2DlgTU m_wndAdvanced2;
	CInfoDlg m_wndInfo;

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

