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

// ChildViewTU.h : CChildViewTU ��Ľӿ�
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
// CChildViewTU ����

class CChildViewTU : public CWnd
{
// ����
public:
	CChildViewTU();

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

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

