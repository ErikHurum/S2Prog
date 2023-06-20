#pragma once

#include "pvcscontrolobjectinfo.h"
#include "afxcmn.h"

#include "PvcsControlObjectDlgSpinCtrl.h"

// Class: CPvcsControlObjectDlgSpinBox
// Description: The Spin box to be used in the control dialog

class CPvcsControlObjectDlgSpinBox : public CEdit
{
	DECLARE_DYNAMIC(CPvcsControlObjectDlgSpinBox)

public:
	CPvcsControlObjectDlgSpinBox(CPvcsControlObject& param_refControlObject );
	virtual ~CPvcsControlObjectDlgSpinBox();
	CString PreviousSpinCtrlValue;
protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL Create(const CPvcsControlObjectInfo& param_info, const RECT& rect, CWnd* param_pParentWnd, const UINT& param_uiID);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nTimerID);
	void ChangeValue(void);


private:
	CPvcsControlObject& m_Controller;		// The controller class
	CPvcsControlObjectInfo m_objectInfo;	// The current object info
	CPvcsControlObjectDlgSpinCtrl m_spinCtrl;// The spin control

	UINT m_uiID;							// The ID of the spin box
};


