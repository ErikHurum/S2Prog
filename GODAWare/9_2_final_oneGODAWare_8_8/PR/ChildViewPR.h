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

// ChildViewPR.h : CChildViewPR ��Ľӿ�
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

// CChildViewPR ����

class CChildViewPR : public CWnd
{
// ����
public:
	CChildViewPR();

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

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

