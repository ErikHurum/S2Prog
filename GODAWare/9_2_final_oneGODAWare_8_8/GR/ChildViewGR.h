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

// ChildViewGR.h : CChildViewGR ��Ľӿ�
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

// CChildViewGR ����

class CChildViewGR : public CWnd
{
// ����
public:
	CChildViewGR();

// ����
public:

// ����
public:
	void Show(unsigned dlgId);
	void Load();
	void Save();

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
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


	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

