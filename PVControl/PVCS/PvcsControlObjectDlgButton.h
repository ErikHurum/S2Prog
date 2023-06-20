#pragma once
#include "pvcscontrolobjectinfo.h"


//Class: CPvcsControlObjectDlgButton
// Description: The buttons to be displayed on the control window

class CPvcsControlObjectDlgButton : public CButton
{
	DECLARE_DYNAMIC(CPvcsControlObjectDlgButton)

public:
	CPvcsControlObjectDlgButton( CPvcsControlObject& param_refControlObject );
	virtual ~CPvcsControlObjectDlgButton();
	BOOL Create(const CPvcsControlObjectInfo& param_info, const RECT& param_rect, CWnd* param_pParentWnd, const UINT& param_uiID);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);



//For: Button click, hang up, for feedback.
	UINT Get_uID(void);//Add by  
	CPvcsControlObject* Get_CPvcsControlObject(void);//Add by   
	CPvcsControlObjectInfo Get_CPvcsControlObjectInfo(void);//Add by  

protected:
	DECLARE_MESSAGE_MAP()

private:
	CPvcsControlObjectInfo m_objectInfo;	// The current object info
	CPvcsControlObject& m_Controller;		// Associated controller class
	UINT m_uiID;							// The button ID
	bool m_bButtonDown;						// Current state of the button
	CString m_strCaption;	
};
//Code Add By :  
//Thread Proc. declaration
//For: Button click, hang up, for feedback.
 UINT DlgButtonDownThread(LPVOID pParam);

