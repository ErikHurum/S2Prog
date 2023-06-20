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

#pragma once

#include "EchoCurveDlgGR.h"
#include "EchoDataDlgGR.h"
#include "TrendDlgGR.h"
#include "SimulateDlgGR.h"
#include "OutputMappingDlgGR.h"

class COutputWndGR : public CDockablePane
{
// 构造
public:
	COutputWndGR();

// 属性
protected:
	CFont m_Font;

	CMFCTabCtrl	m_wndTabs;



	CEchoCurveDlgGR m_wndEchoCurve;
	CEchoDataDlgGR m_wndEchoData;
	CTrendDlgGR m_wndTrend;
	CSimulateDlgGR m_wndSimulate;
	COutputMappingDlgGR m_wndOutputMapping;


protected:
//重写
	BOOL CanBeClosed() const;

// 实现
public:
	virtual ~COutputWndGR();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

