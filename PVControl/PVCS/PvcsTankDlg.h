#pragma once
#include "dxflayout.h"
#include "pvcstankvaluelist.h"

#include "resource.h"
#include "pvcsobjectcontroldlg.h"
#include "pvcsshipdata.h"
#include "afxcmn.h"

// CPvcsTankDlg dialog
// CPvcsTankDlg dialog
struct AlarmListStructforTankDlg
{	CString Tankid;
	CString AlarmStatus;
	CString dateAlarm;
	CString dateAcknow;
	CString AcknowStatus;
};

class CPvcsTankDlg : public CDialog
{
	DECLARE_DYNAMIC(CPvcsTankDlg)

public:
	CPvcsTankDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPvcsTankDlg();

// Dialog Data
	enum { IDD = IDD_PVCSTANKDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public: // JSD again did it public from private:
	CDxfLayout m_dxfLayout;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
private:
	CPvcsTankValueList m_tankValueList;
	int SplitScreens;
private:
	CString m_strFile;
	CString m_strTankLayer;
	int m_iTankID;

public:
	BOOL Create(const CString& param_strFile, const CString& param_strTankLayer, const int& param_ScaleX, const int& param_ScaleY, const int& param_BackGroundCol, const int& param_UndefObjectCol, const int& param_ObjectCol, const int param_LineCol, const int param_TextCol, const bool param_hasLineCol, const bool param_hasTextCol, const bool param_hasBackGround, const int& param_iTankID, CWnd* param_pParent);
	const int& GetTankID(void);
private:
	volatile bool m_bActive;
public:
	void SetActive(const bool& param_bStatus = true);
	afx_msg void OnClose();
private:
	CPvcsControlObjectDlg m_dlgCtrl;
public:
	bool MustUpdate(void);
private:
	bool m_bMustUpdate;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void SetUpdate(bool param_bMustUpdate);
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	bool m_bChangePos;
	afx_msg void OnNcPaint();
private:
	HTHEME m_hTheme;
	CToolTipCtrl m_ToolTip;
public:
	void ShowToolTip(const CString& param_strToolTip);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT nIDEvent);
private:
	bool m_bFlash;
	bool m_bFlashState;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	bool MousePointerOutOfBounds(CPoint point);
	LRESULT OnMouseLeave(WPARAM wParam , LPARAM lParam);
	void CloseControlDlg(void);
public: // again to public from private:
	bool m_bAlarmActive;
	bool m_bAlarmAcknowledged;
	static int AlmCtrlDlgClicked;
	static int m_iGreenAcknow;
	static CPvcsShipData::TankMap *m_ptrTankMap;
};
