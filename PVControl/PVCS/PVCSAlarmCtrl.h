#pragma once
#include "afxcmn.h"
//#include "EditList.h"
#include "pvcsshipdata.h"
#include "PvcsTankDlg.h"
#include "ipscommunication.h"//Added JSD 09-08-2007


// CPVCSAlarmCtrl dialog

struct AlarmListStruct
{	CString Tankid;
	CString TankName;
	CString AlarmText;
	CString Limit;
	CString CurrentValue;
	CString Unit;
	CString TimeRised;
	CString TimeAcknowledged;
};

class CPVCSAlarmCtrl : public CDialog
{
	DECLARE_DYNAMIC(CPVCSAlarmCtrl)

public:
	CPVCSAlarmCtrl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPVCSAlarmCtrl();

// Dialog Data
	enum { IDD = IDD_ALARM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg virtual BOOL OnInitDialog();
public:
	DECLARE_MESSAGE_MAP()
	
public:	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedAlarmacknowButton();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void BuildList();
	static CListCtrl m_cList;	
	afx_msg void OnBnClickedSilencealarmButton();
	void InsertAlaram(int count);
	void InsertEmpty(int id );	
	static CString AckAlarmData;//Added JSD 07-08-2007
	int tankidforIPS;
	CIPSCommunication CIPSCommunicationobj;
	static bool IsAlmDlgOpen;
	static int lastnoofitems;
	static bool blink;
	CImageList* ImagelistObj;
private:
	int alarmcount;
	
	
public:
	afx_msg void OnNMCustomdrawAlarmList(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL CPVCSAlarmCtrl::colorAlmList(/*CDC* pDC*/);
};
CPVCSAlarmCtrl& thePVCSAlmCtrl();