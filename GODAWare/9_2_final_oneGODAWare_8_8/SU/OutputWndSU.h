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

#pragma once

#include "EchoCurveDlgSU.h"
#include "EchoDataDlgSU.h"
#include "TrendDlgSU.h"
#include "SimulateDlgSU.h"
#include "OutputMappingDlgSU.h"

class COutputWndSU : public CDockablePane
{
// ����
public:
	COutputWndSU();

// ����
protected:
	CFont m_Font;

	CMFCTabCtrl	m_wndTabs;



	CEchoCurveDlgSU m_wndEchoCurve;
	CEchoDataDlgSU m_wndEchoData;
	CTrendDlgSU m_wndTrend;
	CSimulateDlgSU m_wndSimulate;
	COutputMappingDlgSU m_wndOutputMapping;


protected:
//��д
	BOOL CanBeClosed() const;

// ʵ��
public:
	virtual ~COutputWndSU();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

