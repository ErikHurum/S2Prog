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

// ChildViewSU.h : CChildViewSU ��Ľӿ�
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

// CChildViewSU ����

class CChildViewSU : public CWnd
{
// ����
public:
	CChildViewSU();

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

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

