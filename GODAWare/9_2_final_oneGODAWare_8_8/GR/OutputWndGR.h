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

#include "EchoCurveDlgGR.h"
#include "EchoDataDlgGR.h"
#include "TrendDlgGR.h"
#include "SimulateDlgGR.h"
#include "OutputMappingDlgGR.h"

class COutputWndGR : public CDockablePane
{
// ����
public:
	COutputWndGR();

// ����
protected:
	CFont m_Font;

	CMFCTabCtrl	m_wndTabs;



	CEchoCurveDlgGR m_wndEchoCurve;
	CEchoDataDlgGR m_wndEchoData;
	CTrendDlgGR m_wndTrend;
	CSimulateDlgGR m_wndSimulate;
	COutputMappingDlgGR m_wndOutputMapping;


protected:
//��д
	BOOL CanBeClosed() const;

// ʵ��
public:
	virtual ~COutputWndGR();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

