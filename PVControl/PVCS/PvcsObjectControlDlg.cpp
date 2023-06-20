// PvcsObjectControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PvcsObjectControlDlg.h"
#include ".\pvcsobjectcontroldlg.h"
#include ".\pvcs v1.0.h"
#include "pvcscontrolobjectstatic.h"
#include "PvcsControlObjectSimplePump.h"
#include "PvcsControlObjectSimplePump2.h"
#include "PvcsControlObjectWartsilaPump.h"
#include "PvcsControlObjectPowerPack.h"
#include "pvcsControlObjectTempSetPoint.h"
#include "pvcscontrolobjectballastpump.h"
#include "pvcscontrolobjectballastvalve.h"
#include "pvcscontrolobjectcargovalve.h"
#include "pvcscontrolobjectcargovalve2.h"
#include "pvcscontrolobjectballastvalve2.h"
#include "pvcscontrolobjectthrottlevalve.h"
#include "pvcscontrolobjectStatus.h"
#include "pvcscontrolobjecttimeoutinfo.h"
#include "resource.h"
#include "PVCSWarningMessage.h"
#include "PVCSPasswordDialog.h"
#include "TimeOutListWin.h"//Added  JSD
#include "warningmessage.h"//Added JSD 22-08-2007
#include "writetimeouts.h"
#include "DxfLayout.h"
//LPTSTR CPvcsControlObjectDlg::WarningMessage1="";//Added JSD 22FEB2007
int CPvcsControlObjectDlg::m_iEditExist = 0; //Added JSD 22FEB2007
vector<WarningMessageStroge> CPvcsControlObjectDlg::WarningMessageVector; //JSD 07MARCH2007
CString CPvcsControlObjectDlg::CurrentDisplayObjName = " "; //JSD 07MARCH2007
int CPvcsControlObjectDlg::objectfoundstatus = 0;
CString CPvcsControlObjectDlg::WarningMessagetemp = " ";
CString CPvcsControlObjectDlg::dispalyObjName = "";
// CPvcsControlObjectDlg dialog

bool CPvcsControlObjectDlg::FirstTimeVectorLoading = false;

IMPLEMENT_DYNAMIC(CPvcsControlObjectDlg, CDialog)


// Function name   : CPvcsControlObjectDlg::CPvcsControlObjectDlg
// Description     : Constructor
// Return type     :
// Argument        : CWnd* pParent /*=NULL*/
#pragma warning (disable: 4101)
CPvcsControlObjectDlg::CPvcsControlObjectDlg(CWnd *pParent /*=NULL*/)
	: CDialog(CPvcsControlObjectDlg::IDD, pParent)
	, m_rectWnd(CRect(0, 0, 150, 70))
	, m_bRightPointer(false)
	, m_bBottomPointer(false)
	, m_pController(NULL)
	, m_bResponseTimedOut(false)
	, m_PasswordUnlock(false) {
	// Add the contoller classes to this dialog
	AddControllers();
	// Inialize memory DC for double buffering
	m_hMemDC = CreateCompatibleDC(NULL);
	// Start Addition 22-08-2007
	char WarningMessageXMLFile[60];
	//line added by mohit


	if (CPvcsControlObjectDlg::FirstTimeVectorLoading == false) {
		CWriteTimeouts TempObjWriteTimeouts;
		if (TempObjWriteTimeouts.LoadTimeOutXML("xmlfiles\\warningTimeOut.xml")) {
			TempObjWriteTimeouts.FillVector();
		}
		CPvcsControlObjectDlg::FirstTimeVectorLoading = true;
	}
}


// Function name   : CPvcsControlObjectDlg::~CPvcsControlObjectDlg
// Description     : Destructor
// Return type     :

CPvcsControlObjectDlg::~CPvcsControlObjectDlg() {

	ControllerMap_it it = m_mapController.begin();

	// Destroy the controller maps

	while (it != m_mapController.end()) {
		delete (*it).second;

			++it;
	} // while( it != m_mapController.end() )

}





// Function name   : theController
// Description     : Access function for one and only Controller Dialog
// Return type     : CPvcsControlObjectDlg&

CPvcsControlObjectDlg& theController() {
	static CPvcsControlObjectDlg dlgControl;
	return dlgControl;
}


// Function name   : CPvcsControlObjectDlg::DoDataExchange
// Description     : Not Implemented
// Return type     : void
// Argument        : CDataExchange* pDX

void CPvcsControlObjectDlg::DoDataExchange(CDataExchange *pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_chk);
	DDX_Control(pDX, IDC_EDIT2, m_editwin);
	DDX_Control(pDX, IDC_EDIT3, m_editwinPassword);
}


BEGIN_MESSAGE_MAP(CPvcsControlObjectDlg, CDialog)
ON_WM_CREATE()
ON_WM_PAINT()
ON_WM_TIMER()
ON_WM_DESTROY()
ON_WM_SIZE()
ON_WM_CLOSE()
ON_MESSAGE(WM_TIMEOUT, OnTimeOut)
ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
ON_BN_CLICKED(IDC_BUTTON_ONE, OnBnClickedButtonOne)
ON_EN_CHANGE(IDC_EDIT_VALUE, OnEnChangeEditValue)
ON_BN_CLICKED(IDC_BUTTON_TWO, OnBnClickedButtonTwo)
ON_EN_CHANGE(IDC_EDIT2, &CPvcsControlObjectDlg::OnEnChangeEdit2)
ON_EN_CHANGE(IDC_EDIT3, &CPvcsControlObjectDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()

// CPvcsControlObjectDlg message handlers


// Function name   : CPvcsControlObjectDlg::Display
// Description     : Displays the control window
// Return type     : void
// Argument        : const CPvcsControlObjectInfo& param_infoObject
// Argument        : CPoint param_point
// Argument        : CWnd* param_pParent

void CPvcsControlObjectDlg::Display(const CPvcsControlObjectInfo &param_infoObject, CPoint param_point, CWnd *param_pParent) {
	using namespace PvcsControlObjectTypes;

	m_bIsTopAdjusted = false;
	// Assign the Object Info
	m_infoObject = param_infoObject;

	//Assign Controller
	m_pController = &GetController(m_infoObject);
	//Start JSD 07MARCH2007
	CString WarningMessage1;
	dispalyObjName = m_infoObject.GetName();
	CurrentDisplayObjName = dispalyObjName;
	theController().objectfoundstatus = 0; //JSD 07MARCH2007
	int messagesize = WarningMessageVector.size();
	if (messagesize > 0) {
		for (int i = 0; i < messagesize; i++) {
			CString TempObjName;
			TempObjName = WarningMessageVector[i].ControlObjName;
			if (TempObjName == dispalyObjName) {
				CString Temp12 = WarningMessageVector[i].ObjWarningMessage;
				int length = Temp12.GetLength();
				WarningMessage1 = Temp12.GetBuffer(length);
				WarningMessagetemp = Temp12;
				theController().objectfoundstatus = 1;
			}

		}
		if (theController().objectfoundstatus == 0) {

			WarningMessagetemp = " ";
		}
	} else {
		WarningMessagetemp = " ";
	}
	//END JSD 07MARCH2007
	// Now resize the control window
	// before JSD m_rectWnd.bottom = 65;
	m_rectWnd.bottom = 75; //JSD change to 85, change to 75 by

	m_rectWnd.right = 150; //JSD

	if (param_infoObject.GetStatusCount() > 0)
		// before JSD m_rectWnd.bottom += 20;
		m_rectWnd.bottom += 60;

	if (param_infoObject.GetOutText().GetLength() > 0)
		//  BF JSD m_rectWnd.bottom += 20;
		m_rectWnd.bottom += 80;
	const int NumberOfButtons = m_infoObject.GetNumberOfButtons();
	switch (m_infoObject.GetNumberOfButtons()) {
	case 2:
	case 1:
	case 0:
		m_rectWnd.bottom += 20;
		break;
	case 3:
	case 4:
		m_rectWnd.bottom += 100;
		break;
	case 5:
	case 8:
		m_rectWnd.bottom += 200;
		m_rectWnd.right  += 50;
		break;
	}
	if (m_pController->GetValueString(m_infoObject).GetLength() > 0) m_rectWnd.bottom += 15;
	if (m_rectWnd.bottom == 135) {
		m_rectWnd.bottom += 45;
	}
	CRect rectParentWnd, rectWnd(m_rectWnd);
	rectWnd.OffsetRect(param_point.x, param_point.y);

	m_bRightPointer = false;
	m_bBottomPointer = false;
	m_bResponseTimedOut = false;

	param_pParent->GetWindowRect(&rectParentWnd);


	switch (m_infoObject.GetNumberOfButtons()) {
	case 5:
	case 8:
		m_rectText = CRect(30, 10, 138+50, 62);
		break;
	default:
		m_rectText = CRect(30, 10, 138, 62);
		break;
	}



	if (rectWnd.right > rectParentWnd.Width()) {
		m_rectText.OffsetRect(-20, 0);

		rectWnd.OffsetRect(-rectWnd.Width(), 0);
		m_bRightPointer = true;
	} // if( rectWnd.right > rectParentWnd.Width() )

	if (rectWnd.bottom > rectParentWnd.Height()) {
		rectWnd.OffsetRect(0, -rectWnd.Height());
		m_bBottomPointer = true;
		m_bIsTopAdjusted = true;

	} // if( rectWnd.bottom > rectParentWnd.Height() )
//Start Addition JSD 27-08-2007
//commented by
	if (rectWnd.top < rectParentWnd.top && m_bIsTopAdjusted) {
		if (NumberOfButtons > 2) {
			rectWnd.OffsetRect(0, (rectParentWnd.top - rectWnd.top) + 50);
		} else if (NumberOfButtons > 0 || m_infoObject.GetNumberOfSpinBox() > 0) {
			rectWnd.OffsetRect(0, (rectParentWnd.top - rectWnd.top) + 10);
		}
	}
//End Addition  JSD 27-08-2007
// Create the window and show it
	Create(IDD_PVCSOBJECTCONTROLDLG, param_pParent);
	CRgn m_Rgn;
	SetWindowRgn(CreateRgn(m_Rgn), true);

	RedrawWindow();
	MoveWindow(rectWnd);
	ShowWindow(SW_SHOW);
	int length = WarningMessagetemp.GetLength(); //JSD 07MARCH2007
	theWarningMessage().WarningMessage1 = WarningMessagetemp.GetBuffer(length); //JSD 07MARCH2007
	m_editwin.SetWindowText(theWarningMessage().WarningMessage1); //JSD 07MARCH2007
	switch (m_infoObject.GetNumberOfButtons()) {
	case 5:
	case 8:
		{
			m_editwin.ShowWindow(SW_SHOW);
			RECT tmpRectEdit = { 35, 300, 185, 325 };
			RECT tmpRectChk  = { 35, 280, 85, 299 };
			//m_editwin.GetRect((LPRECT)&tmpRect);
			//tmpRect.top    += 300;
			//tmpRect.bottom += 315;
			m_chk.MoveWindow((LPRECT)&tmpRectChk);
			m_editwin.MoveWindow((LPRECT)&tmpRectEdit);
		}
		break;
	case 0:
		if (m_infoObject.GetNumberOfSpinBox() < 1) {
			m_chk.ShowWindow(SW_HIDE);
			m_editwin.ShowWindow(SW_HIDE);
		}
		break;
	default:
		m_chk.ShowWindow(SW_SHOW);
		m_editwin.ShowWindow(SW_SHOW);
		break;
	}
	bool HasPassword = m_infoObject.GetPassword();

	if (HasPassword) {
		if (thePasswordMessage().m_dialoginitalise == 0) {
			PvcsPasswordDialog::DialgVisible = true;
			if (thePasswordMessage().DoModal() == IDOK) {
				ButtonList_it itButList;
				for (itButList = m_Button.begin(); itButList != m_Button.end(); itButList++) {
					(*itButList)->ShowWindow(SW_SHOW);
				}
			}
		}
	}
}


// Function name   : CPvcsControlObjectDlg::CreateRgn
// Description     : Creates the Popup window region with pointed end
// Return type     : CRgn&
// Argument        : CRgn& Rgn

CRgn& CPvcsControlObjectDlg::CreateRgn(CRgn &Rgn) {
	CRgn TrRgn, RcRgn;

	CRect tempRect(m_rectWnd);

	if (m_bRightPointer) tempRect.right -= 20;
	else tempRect.left += 20;

	RcRgn.CreateRoundRectRgn(tempRect.left, tempRect.top, tempRect.right, tempRect.bottom, 10, 10);
	CPoint tpt[3];

	if (m_bRightPointer) {
		tpt[0].x = tempRect.right - 1;
		tpt[1].x = tempRect.right - 1;
		tpt[2].x = tempRect.right + 20;
	} // if( m_bRightPointer )
	else {
		tpt[0].x = tempRect.left;
		tpt[1].x = tempRect.left;
		tpt[2].x = tempRect.left - 20;
	}

	if (m_bBottomPointer) {
		tpt[0].y = tempRect.bottom - 15;
		tpt[1].y = tempRect.bottom - 30;
		tpt[2].y = tempRect.bottom;
	} // if( m_bBottomPointer )
	else {
		tpt[0].y = tempRect.top + 15;
		tpt[1].y = tempRect.top + 30;
		tpt[2].y = tempRect.top;
	}
	//if(m_bTopPointer)
	//{
	//  tpt[0].y = tempRect.top+15;
	//  tpt[1].y = tempRect.top + 30;
	//  tpt[2].y = tempRect.top;
	//}
	//else
	//{
	////think
	//}

	TrRgn.CreatePolygonRgn(tpt, 3, WINDING);

	Rgn.CreateRoundRectRgn(tempRect.left, tempRect.top, tempRect.right, tempRect.bottom, 10, 10);
	if (!m_bIsTopAdjusted) Rgn.CombineRgn(&TrRgn, &RcRgn, RGN_OR);

	return Rgn;
}


// Function name   : CPvcsControlObjectDlg::OnCreate
// Description     : Message Handler
// Return type     : int
// Argument        : LPCREATESTRUCT lpCreateStruct

int CPvcsControlObjectDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CDialog::OnCreate(lpCreateStruct) == -1) return -1;
	bool HasPassword = m_infoObject.GetPassword();

	const UINT NumberOfButtons = m_infoObject.GetNumberOfButtons();
	//if( m_infoObject )
	{

		// Offset position for spinboxes/buttons
		int nOffsetX = 35;
		int nOffsetY = 75;

		// Adjust x-offset if the pointer is on the right
		if (m_bRightPointer) nOffsetX -= 20;

		if (m_pController->GetValueString(m_infoObject).GetLength() > 0) nOffsetY += 15;

		// , for control having both spin box and buttons
		bool bIsSpinBox = false;

		switch (NumberOfButtons) {
		case 5:
		case 8:
			nOffsetY += 35;
			// Now create the Spin boxes
			for (unsigned i = 0; i < m_infoObject.GetNumberOfSpinBox(); i++) {
				bIsSpinBox = true;
				CPvcsControlObjectDlgSpinBox *tempSpinBox = new CPvcsControlObjectDlgSpinBox(*m_pController);
				tempSpinBox->Create(m_infoObject, CRect(nOffsetX+50, nOffsetY - 25 + 25 * i, nOffsetX + 75+50, nOffsetY - 25 + 20 + 25 * i), this, i);

				m_SpinBox.push_back(tempSpinBox);
			} // for(i=0; i<m_infoObject.GetNumberOfSpinBox(); i++)
			break;
		default:
			// Now create the Spin boxes
			for (unsigned i = 0; i < m_infoObject.GetNumberOfSpinBox(); i++) {
				bIsSpinBox = true;
				CPvcsControlObjectDlgSpinBox *tempSpinBox = new CPvcsControlObjectDlgSpinBox(*m_pController);
				tempSpinBox->Create(m_infoObject, CRect(nOffsetX + 50 * i, nOffsetY, nOffsetX + 45 + 50 * i, nOffsetY + 20), this, i);

				m_SpinBox.push_back(tempSpinBox);
			} // for(i=0; i<m_infoObject.GetNumberOfSpinBox(); i++)
			break;
		}

		// Now create the buttons
		switch (NumberOfButtons) {
		case 5:
		case 8:
			{
				for (unsigned i = 0; i < NumberOfButtons; i++) {
					CPvcsControlObjectDlgButton *tempButton = new CPvcsControlObjectDlgButton(*m_pController);

					int XCor = 0;
					int YCor = i / 2;
					switch (i % 2) {
					case 0:
						break;
					case 1:
						XCor++;
						break;
					}
					//if (bIsSpinBox) { //if having spin box, along with button
					//	tempButton->Create(m_infoObject, CRect(nOffsetX + 45 + 15, (nOffsetY)+(29 * i), nOffsetX + 45 + 15 + 45, (nOffsetY)+25 + (29 * i)), this, i);
					//} else {
					tempButton->Create(m_infoObject, CRect(nOffsetX + 80 * XCor, nOffsetY + 30 * YCor, nOffsetX + 70 + 80 * XCor, nOffsetY + 25 + 30 * YCor), this, i);
					//}

					if (HasPassword) {
						m_editwinPassword.EnableWindow(true);
						tempButton->ShowWindow(SW_HIDE);
					} else {
						tempButton->ShowWindow(SW_SHOW);
					}

					m_Button.push_back(tempButton);
				} // for(i=0; i<m_infoObject.GetNumberOfButtons(); i++)
			}
			break;
		default:
			for (unsigned i = 0; i < NumberOfButtons; i++) {
				CPvcsControlObjectDlgButton *tempButton = new CPvcsControlObjectDlgButton(*m_pController);

				if (bIsSpinBox) { //if having spin box, along with button
					tempButton->Create(m_infoObject, CRect(nOffsetX + 45 + 15, (nOffsetY)+(29 * i), nOffsetX + 45 + 15 + 45, (nOffsetY)+25 + (29 * i)), this, i);
				} else {
					int XCor = 0;
					int YCor = -1;
					YCor = i / 2;
					switch (i % 2) {
					case 0:
						break;
					case 1:
						XCor++;
						break;
					}
					tempButton->Create(m_infoObject, CRect(nOffsetX + 50 * XCor, nOffsetY + 30 * YCor, nOffsetX + 45 + 50 * XCor, nOffsetY + 25 + 30 * YCor), this, i);
				}
				if (HasPassword) {
					m_editwinPassword.EnableWindow(true);
					tempButton->ShowWindow(SW_HIDE);
				} else {
					tempButton->ShowWindow(SW_SHOW);
				}

				m_Button.push_back(tempButton);
			} // for(i=0; i<m_infoObject.GetNumberOfButtons(); i++)
			break;
		case 2:
			{
				for (unsigned i = 0; i < NumberOfButtons; i++) {
					CPvcsControlObjectDlgButton *tempButton = new CPvcsControlObjectDlgButton(*m_pController);

					if (bIsSpinBox) { //if having spin box, along with button
						tempButton->Create(m_infoObject, CRect(nOffsetX + 45 + 15, (nOffsetY)+(29 * i), nOffsetX + 45 + 15 + 45, (nOffsetY)+25 + (29 * i)), this, i);
					} else {
						tempButton->Create(m_infoObject, CRect(nOffsetX + 50 * i, nOffsetY, nOffsetX + 45 + 50 * i, nOffsetY + 25), this, i);
					}
					if (HasPassword) {
						//m_editwinPassword.ShowWindow(SW_SHOW);
						tempButton->ShowWindow(SW_HIDE);
					} else {
						tempButton->ShowWindow(SW_SHOW);
					}

					m_Button.push_back(tempButton);
				}
			}
			break;
		case 1:
			{
				CPvcsControlObjectDlgButton *tempButton = new CPvcsControlObjectDlgButton(*m_pController);

				tempButton->Create(m_infoObject, CRect(nOffsetX, nOffsetY, nOffsetX + 70, nOffsetY + 40), this, 0);
				if (HasPassword) {
					//m_editwinPassword.ShowWindow(SW_SHOW);
					tempButton->ShowWindow(SW_HIDE);
				} else {
					tempButton->ShowWindow(SW_SHOW);
				}

				m_Button.push_back(tempButton);
			}
			break;
		}
	}

	return 0;
}


// Function name   : CPvcsControlObjectDlg::OnPaint
// Description     : Message Handler
// Return type     : void

void CPvcsControlObjectDlg::OnPaint() {
	using namespace Gdiplus;
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);

	// First draw the legend to the buffer
	Draw();

	// Now copy the buffer to the window
	BitBlt(dc, 0, 0, rc.Width(), rc.Height(), m_hMemDC, 0, 0, SRCCOPY);

	CBrush brblk(RGB(0, 0, 0));
	CRgn m_Rgn;
	dc.PaintRgn(&m_Rgn);
	dc.FrameRgn(&CreateRgn(m_Rgn), &brblk, 1, 1);
}


// Function name   : CPvcsControlObjectDlg::GetData
// Description     : Updates the Data
// Return type     : void
// Argument        : void

void CPvcsControlObjectDlg::GetData(void) {
	using namespace PvcsControlObjectTypes;

	UpdateData(false);
}



// Function name   : CPvcsControlObjectDlg::OnTimer
// Description     : Message Handler
// Return type     : void
// Argument        : UINT nIDEvent

void CPvcsControlObjectDlg::OnTimer(UINT nIDEvent) {

	if (nIDEvent == IDT_GETWAGODATA) {
		GetData();
		RedrawWindow();
	}
	CDialog::OnTimer(nIDEvent);
}


// Function name   : CPvcsControlObjectDlg::GetController
// Description     : Helper class which returnes controller class associated with the control object
// Return type     : CPvcsControlObject&
// Argument        : const CPvcsControlObjectInfo& param_info

CPvcsControlObject& CPvcsControlObjectDlg::GetController(const CPvcsControlObjectInfo &param_info) {
	ControllerMap_it it = m_mapController.find(param_info.GetClassName());

	if (it != m_mapController.end()) return *((*it).second);
	else return m_defaultController;
}


// Function name   : CPvcsControlObjectDlg::AddControllers
// Description     : Builds up the controller class info
// Return type     : void
// Argument        : void

void CPvcsControlObjectDlg::AddControllers(void) {

#define ADD(x) m_mapController.insert( make_pair(#x, new x) )

	ADD(CPvcsControlObjectStatic);
	ADD(CPvcsControlObjectTempSetPoint);
	ADD(CPvcsControlObjectBallastPump);
	ADD(CPvcsControlObjectBallastValve);
	ADD(CPvcsControlObjectCargoValve);
	ADD(CPvcsControlObjectCargoValve2);
	ADD(CPvcsControlObjectThrottleValve);
	ADD(CPvcsControlObjectBallastValve2);
	ADD(CPvcsControlObjectSimplePump);
	ADD(CPvcsControlObjectSimplePump2);
	ADD(CPvcsControlObjectWartsilaPump);
	ADD(CPvcsControlObjectStatus);
	ADD(CPvcsControlObjectPowerPack);


}



// Function name   : CPvcsControlObjectDlg::OnDestroy
// Description     : Message Handler
// Return type     : void

void CPvcsControlObjectDlg::OnDestroy() {
	CDialog::OnDestroy();

	ButtonList_it b_it = m_Button.begin();

	// Delete all the buttons
	while (b_it != m_Button.end()) {
		(*b_it)->DestroyWindow();

		delete (*b_it);
			++b_it;
	} // while( b_it != m_Button.end() )

	m_Button.clear();

	SpinBoxList_it s_it = m_SpinBox.begin();

	// Delete all the spin boxes
	while (s_it != m_SpinBox.end()) {
		(*s_it)->DestroyWindow();

		delete (*s_it);
			++s_it;
	} // while( s_it != m_SpinBox.end() )

	m_SpinBox.clear();
}


// Function name   : CPvcsControlObjectDlg::OnSize
// Description     : Message Handler
// Return type     : void
// Argument        : UINT nType
// Argument        : int cx
// Argument        : int cy

void CPvcsControlObjectDlg::OnSize(UINT nType, int cx, int cy) {
	CDialog::OnSize(nType, cx, cy);

	if (cx || cy) {
		CClientDC dc(this);
		CRect rect;
		GetClientRect(&rect);

		SelectObject(m_hMemDC, CreateCompatibleBitmap(dc, rect.Width(), rect.Height()));

		RedrawWindow();
	} // if( cx || cy )
}


// Function name   : CPvcsControlObjectDlg::Draw
// Description     : Paints the Control Window
// Return type     : void
// Argument        : void

void CPvcsControlObjectDlg::Draw(void) {



	CRect rectWindow;
	GetClientRect(&rectWindow);

	using namespace Gdiplus;

	COLORREF color1 = GetSysColor(COLOR_GRADIENTACTIVECAPTION), color2 = GetSysColor(COLOR_ACTIVECAPTION);


	Graphics graphics(m_hMemDC);

	if (graphics.GetLastStatus() == Ok) {
		SolidBrush brush((unsigned)Color::LightGoldenrodYellow);
		FontFamily fontFamily(L"Tahoma");
		Gdiplus::Font font(&fontFamily, 14, FontStyleBoldItalic, UnitPixel);
		Gdiplus::Font fontText(&fontFamily, 12, FontStyleRegular, UnitPixel);
		Gdiplus::Font fontWarning(&fontFamily, 12, FontStyleBold, UnitPixel);
		RectF rectF(REAL(m_rectText.left),
					REAL(m_rectText.top),
					REAL(m_rectText.Width()),
					REAL(15));
		RectF rectFText(REAL(m_rectText.left),
						REAL(20),
						REAL(m_rectText.Width()),
						REAL(m_rectText.Height() - 15));

		// The title gradient rectangle
		graphics.FillRectangle(&brush, rectWindow.left, rectWindow.top, rectWindow.Width(), rectWindow.Height());
		LinearGradientBrush lgbrTitle(rectF,
									  Color(GetRValue(color1), GetGValue(color1), GetBValue(color1)),
									  Color(GetRValue(color2), GetGValue(color2), GetBValue(color2)), 90);
		StringFormat stringFormat;
		stringFormat.SetAlignment(StringAlignmentCenter);

		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
		graphics.FillRectangle(&lgbrTitle, rectF);

		// Draw the title
		CStringW strTitle = (CStringW)m_infoObject.GetName();
		graphics.DrawString(strTitle, -1, &font, rectF, &stringFormat, &brush);

		brush.SetColor((unsigned)Color::Black);
		// Get object status like Run, stop, tripped etc.
		CStringW tmpStr;

		const UINT NumberOfButtons = m_infoObject.GetNumberOfButtons();
		switch (NumberOfButtons) {
		case 8:
			/*
			tmpStr = (CStringW)m_pController->GetInText(m_infoObject);
			if ((m_infoObject.GetStatusCount() > 1) && (tmpStr.GetLength() > 0)) {
				//unsigned tmpCol = unsigned(m_pController->GetColor(m_infoObject));
				//Color brushColor;
				//brushColor.SetFromCOLORREF(tmpCol);
				//brush.SetColor(brushColor);
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
				brush.SetColor((unsigned)Color::Black);
			} // if( m_pController->GetInText().GetLength() > 0 )
			*/
			{
				tmpStr = m_pController->GetValueString(m_infoObject, 7);
				int OperationMode = atoi((char *)tmpStr.GetString());
				switch (OperationMode) {
				case 3: //strValue = "Discharge"; break;
					for (ButtonList_it itButList = m_Button.begin(); itButList != m_Button.end();itButList++) {
						(*itButList)->EnableWindow(false);
					}
					break;
				case 0: //strValue = "Discharge"; break;
					for (ButtonList_it itButList = m_Button.begin(); itButList != m_Button.end();itButList++) {
						(*itButList)->EnableWindow(true);
					}
					break;
				case 1: //strValue = "Stripping"; break;
					{
						bool EnableTable[] = {
							false, // Start
							true,  // Stop
							true,  // Lo speed
							true,  // Reset
							false, // Heat on
							false, // Strip on
							false, // Circ on
							false, // Wash on
						};

						int i = 0;
						for (ButtonList_it itButList = m_Button.begin(); itButList != m_Button.end(); i++,itButList++) {
							(*itButList)->EnableWindow(EnableTable[i]);
						}
					}
					break;
				case 2: //strValue = "Wash"; 
					{
						bool EnableTable[] = {
							false, // Start
							false,  // Stop
							true,  // Reset
							false,  // Lo speed
							false, // Heat on
							false, // Strip on
							false, // Circ on
							false, // Wash on
						};

						int i = 0;
						for (ButtonList_it itButList = m_Button.begin(); itButList != m_Button.end(); i++,itButList++) {
							(*itButList)->EnableWindow(EnableTable[i]);
						}
					}
					break;
				}
			}

			//Get pump speed RPM
			tmpStr = m_pController->GetValueString(m_infoObject, 0)+" rpm";
			if (tmpStr.GetLength() > 0) {
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
			} // if( m_pController->GetValueString().GetLength() > 0 )
			// Get operation mode
			tmpStr = m_pController->GetValueString(m_infoObject, 4);
			if (tmpStr.GetLength() > 0) {
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
			} // if( m_pController->GetValueString().GetLength() > 0 )
			tmpStr = m_pController->GetValueString(m_infoObject, 5);
			if (tmpStr.GetLength() > 0) {
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
			} // if( m_pController->GetValueString().GetLength() > 0 )
			tmpStr = m_pController->GetValueString(m_infoObject, 6);
			if (tmpStr.GetLength() > 0) {
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
			} // if( m_pController->GetValueString().GetLength() > 0 )
			break;
		case 5: 

			tmpStr = (CStringW)m_pController->GetInText(m_infoObject);
			if ((m_infoObject.GetStatusCount() > 1) && (tmpStr.GetLength() > 0)) {
				//unsigned tmpCol = unsigned(m_pController->GetColor(m_infoObject));
				//Color brushColor;
				//brushColor.SetFromCOLORREF(tmpCol);
				//brush.SetColor(brushColor);
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
				brush.SetColor((unsigned)Color::Black);
			} // if( m_pController->GetInText().GetLength() > 0 )

			//Get pump speed RPM
			tmpStr = m_pController->GetValueString(m_infoObject, 0);
			if (tmpStr.GetLength() > 0) {
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
			} // if( m_pController->GetValueString().GetLength() > 0 )
			// Get operation mode
			tmpStr = m_pController->GetValueString(m_infoObject, 4);
			if (tmpStr.GetLength() > 0) {
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
			} // if( m_pController->GetValueString().GetLength() > 0 )
			tmpStr = m_pController->GetValueString(m_infoObject, 5);
			if (tmpStr.GetLength() > 0) {
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
			} // if( m_pController->GetValueString().GetLength() > 0 )
			tmpStr = m_pController->GetValueString(m_infoObject, 6);
			if (tmpStr.GetLength() > 0) {
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
			} // if( m_pController->GetValueString().GetLength() > 0 )
			break;
		default:

			tmpStr = (CStringW)m_pController->GetInText(m_infoObject);
			if ((m_infoObject.GetStatusCount() > 1) && (tmpStr.GetLength() > 0)) {
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
			} // if( m_pController->GetInText().GetLength() > 0 )
			tmpStr = m_pController->GetValueString(m_infoObject);
			if (tmpStr.GetLength() > 0) {
				rectF.Offset(0, 15);
				graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
			} // if( m_pController->GetValueString().GetLength() > 0 )
			break;
		}

		Pen pen(Color(GetRValue(color2) / 2, GetGValue(color2) / 2, GetBValue(color2) / 2));
		graphics.DrawRectangle(&pen, m_rectText.left, m_rectText.top, m_rectText.Width(), INT(rectF.GetBottom() - m_rectText.top));

		tmpStr = m_infoObject.GetOutText();
		if (tmpStr.GetLength() > 0) {
			rectF.Offset(0, 15);
			graphics.DrawString(tmpStr, -1, &fontText, rectF, &stringFormat, &brush);
		} // if( m_infoObject.GetOutText().GetLength() > 0 )

		brush.SetColor((unsigned)Color::Red);
		if (GetTimeOut()) {
			rectF.Offset(0, 15);
			tmpStr = m_infoObject.GetOutText();
			graphics.DrawString(L"Warning: Timeout", -1, &fontWarning, rectF, &stringFormat, &brush);



			//Srat Addition JSD
			//wt.WriteTimeOutDataToFile(CurrentDisplayObjName,m_SystemIP,"TimeOut");
			//wt.SaveXMLFile("XMLFILES\\warningTimeOut.xml");
			//End addition JSD

			//set "" (empty string) to value to be set

			if (!CDxfLayout::GetTimeoutState(m_infoObject.GetIndex(), m_infoObject.GetSubIndex())) {
				CDxfLayout::SetValueToBeSet(m_infoObject.GetIndex(), m_infoObject.GetSubIndex(), "");

				//set current value to the spin ctrl.
				CString strControlCurrentValue = m_pController->GetValueString(m_infoObject);
				int iControlCurrentValue = atoi(strControlCurrentValue);
				strControlCurrentValue.Format("%d", iControlCurrentValue);
				SetValueToSpinCtrl(strControlCurrentValue);
				CDxfLayout::SetTimeoutState(m_infoObject.GetIndex(), m_infoObject.GetSubIndex(), true);
			}

		} // if( m_infoObject.GetOutText().GetLength() > 0 )
		else {
			CDxfLayout::SetTimeoutState(m_infoObject.GetIndex(), m_infoObject.GetSubIndex(), false);
		}
	} // if( graphics.GetLastStatus() == Ok )
	if (theController().objectfoundstatus == 1) {
		m_chk.SetCheck(BST_CHECKED);
	}
}


// Function name   : CPvcsControlObjectDlg::OnClose
// Description     : Message Handler
// Return type     : void

void CPvcsControlObjectDlg::OnClose() {
	CDialog::OnClose();

	// Destroy the window on close
	DestroyWindow();
}




const CPvcsControlObjectInfo& CPvcsControlObjectDlg::GetControlobjectInfo(void) {
	return m_infoObject;
}

afx_msg LRESULT CPvcsControlObjectDlg::OnTimeOut(WPARAM wParam, LPARAM lParam) {
	m_bResponseTimedOut = true;
	return afx_msg LRESULT();
}

bool CPvcsControlObjectDlg::GetTimeOut(void) {
	TimeOutInfoSet::const_iterator it
		= theTimeOutInfo().find(CPvcsControlObjectTimeOutInfo(m_infoObject.GetIndex(), m_infoObject.GetSubIndex()));


	if (it != theTimeOutInfo().end()) return (*it).GetTimeOut();
	else return false;
}

void CPvcsControlObjectDlg::OnBnClickedCheck1() {
	//get screen number by below line

	//int sNo=  GetControlobjectInfo().GetScreenNumber();
	CString O_Name = GetControlobjectInfo().GetName();


	if (m_chk.GetCheck() == BST_UNCHECKED) {
		m_editwin.EnableWindow(false);
		PVCSWarningMessage::m_dialoginitalise = 0;
		int messagesize1 = theController().WarningMessageVector.size();
		if (messagesize1 > 0) {
			for (int i = 0; i < messagesize1; i++) {
				CString TempObjName;
				TempObjName = theController().WarningMessageVector[i].ControlObjName;
				if (TempObjName == dispalyObjName) {
					theController().WarningMessageVector.erase(WarningMessageVector.begin() + i);
					theWarningMessage().m_WarningMessage = "";
					m_editwin.SetWindowText(theWarningMessage().m_WarningMessage);
					theController().objectfoundstatus = 0;
				}
			}
		}

		int sNo = theController().GetControlobjectInfo().GetScreenNumber();
		CString sn;
		sn.Format("%d", sNo);
		sn = "SNO" + sn;

		XmlQueue *tempXmlQueue;

		tempXmlQueue = new XmlQueue;

		tempXmlQueue->eType = Message;
		tempXmlQueue->strScreenNumber = sn;
		tempXmlQueue->strObjectName = O_Name;
		tempXmlQueue->strMessage = "";

		tempXmlQueue->strMachineIP = "";
		tempXmlQueue->strTime = "";
		tempXmlQueue->bIsWarning_Timeout = false;

		//Thread that push item into the queue
		AfxBeginThread(XmlWTQueuePush_Thread, tempXmlQueue);



	} else {
		m_editwin.EnableWindow(true);

		if (theWarningMessage().m_dialoginitalise == 0) {
			PVCSWarningMessage::DialgVisible = true;
			theWarningMessage().DoModal();
		}

	}


}



CString CPvcsControlObjectDlg::GetSystemIP() {
	sockaddr_in service;

	char *ip, ipaddress[200];
	char name[255];
	PHOSTENT hostinfo;



	//added 12.12
	ip = new char;
	gethostname(name, sizeof(name));
	if ((hostinfo = gethostbyname(name)) != NULL) {
		ip = inet_ntoa(*(struct in_addr *)hostinfo->h_addr_list[0]);
		strcpy_s(ipaddress, ip);
	}
	return ipaddress;
}
void CPvcsControlObjectDlg::OnBnClickedButtonOne() {
	// TODO: Add your control notification handler code here
}

void CPvcsControlObjectDlg::OnEnChangeEditValue() {
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CPvcsControlObjectDlg::OnBnClickedButtonTwo() {
	// TODO: Add your control notification handler code here
}
//Strting Addition JSD 20-09-2007
//To Close Warning Message is Exist at the time of command transfer
void CPvcsControlObjectDlg::OnCloseWarningMessageWindow() {
	if (PVCSWarningMessage::DialgVisible == true) {
		theWarningMessage().m_WarningMessage = "";
		PVCSWarningMessage::m_dialoginitalise = 0;
		PVCSWarningMessage::DialgVisible = false;
		theWarningMessage().EndDialog(1);
		CDC *Temp = theWarningMessage().GetWindowDC();
		if (Temp != NULL) {
			char *ptr = (char *)malloc(5);
			free(ptr);
			ptr = NULL;
		}
	}
}

bool CPvcsControlObjectDlg::SetValueToSpinCtrl(CString pValue) {
	if (m_SpinBox.size() > 0) {
		SpinBoxList_it s_it = m_SpinBox.begin();
		(*s_it)->SetWindowText(pValue);
		return true;
	}

	return false;
}


void CPvcsControlObjectDlg::OnEnChangeEdit2() {
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CPvcsControlObjectDlg::OnEnChangeEdit3() {
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString tmpStr;
	GetDlgItemText(IDC_EDIT3, tmpStr);
	if (true) {
		m_PasswordUnlock = true;
	}
}
