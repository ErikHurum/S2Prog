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

#include "EchoCurveDlgPR.h"
#include "EchoDataDlgPR.h"
#include "TrendDlgPR.h"
#include "SimulateDlgPR.h"
#include "OutputMappingDlgPR.h"

class COutputWndPR : public CDockablePane
{
// ����
public:
	COutputWndPR();

// ����
protected:
	CFont m_Font;

	CMFCTabCtrl	m_wndTabs;



	CEchoCurveDlgPR m_wndEchoCurve;
	CEchoDataDlgPR m_wndEchoData;
	CTrendDlgPR m_wndTrend;
	CSimulateDlgPR m_wndSimulate;
	COutputMappingDlgPR m_wndOutputMapping;


protected:
//��д
	BOOL CanBeClosed() const;

// ʵ��
public:
	virtual ~COutputWndPR();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

