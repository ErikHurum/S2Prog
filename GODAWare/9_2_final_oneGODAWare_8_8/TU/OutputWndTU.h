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

#include "EchoCurveDlgTU.h"
#include "EchoDataDlgTU.h"
#include "TrendDlgTU.h"
#include "SimulateDlgTU.h"
#include "OutputMappingDlgTU.h"

class COutputWndTU : public CDockablePane
{
// ����
public:
	COutputWndTU();

// ����
protected:
	CFont m_Font;

	CMFCTabCtrl	m_wndTabs;



	CEchoCurveDlgTU m_wndEchoCurve;
	CEchoDataDlgTU m_wndEchoData;
	CTrendDlgTU m_wndTrend;
	CSimulateDlgTU m_wndSimulate;
	COutputMappingDlgTU m_wndOutputMapping;


protected:
//��д
	BOOL CanBeClosed() const;

// ʵ��
public:
	virtual ~COutputWndTU();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

