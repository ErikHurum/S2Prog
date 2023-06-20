// PvcsControlObjectDlgSpinCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PvcsControlObjectDlgSpinCtrl.h"
#include "PvcsControlObjectDlgSpinBox.h"
#include ".\pvcscontrolobjectdlgspinctrl.h"


// CPvcsControlObjectDlgSpinCtrl

IMPLEMENT_DYNAMIC(CPvcsControlObjectDlgSpinCtrl, CSpinButtonCtrl)

// Function name   : CPvcsControlObjectDlgSpinCtrl::CPvcsControlObjectDlgSpinCtrl
// Description     : Constructor
// Return type     : 

CPvcsControlObjectDlgSpinCtrl::CPvcsControlObjectDlgSpinCtrl()
{
}


// Function name   : CPvcsControlObjectDlgSpinCtrl::~CPvcsControlObjectDlgSpinCtrl
// Description     : Destructor
// Return type     : 

CPvcsControlObjectDlgSpinCtrl::~CPvcsControlObjectDlgSpinCtrl()
{
}

BEGIN_MESSAGE_MAP(CPvcsControlObjectDlgSpinCtrl, CSpinButtonCtrl)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// Function name   : CPvcsControlObjectDlgSpinCtrl::OnLButtonUp
// Description     : Message Handler
// Return type     : void 
// Argument        : UINT nFlags
// Argument        : CPoint point

void CPvcsControlObjectDlgSpinCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	CSpinButtonCtrl::OnLButtonUp(nFlags, point);

	// Get the buddy spin box
	CPvcsControlObjectDlgSpinBox *pSpinBox = 
		dynamic_cast <CPvcsControlObjectDlgSpinBox*> ( GetBuddy() );

	
	// Now change the value
	if( pSpinBox )
		pSpinBox->ChangeValue();
	else
		XmlLogError("Fatal Error while changing value.");
}
