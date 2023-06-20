// DxfLayout.cpp : implementation file
//

#include "stdafx.h"
#include "DxfLayout.h"
#include "pvcstankview.h"
#include "pvcssplitterwnd.h"
#include "pvcscontrolobjecttimeoutinfo.h"
//#include "connect.h"
#include "pvcs v1.0.h"
#include "PVCSWarningMessage.h"//JSD
#include "PvcsScreenInfo.h"
#include "pvcsScreenFrame.h"

#include <cmath>
//LRESULT CALLBACK MouseHook( int nCode, WPARAM wParam, LPARAM lParam );
extern CCriticalSection g_CS_Update;
//extern struct Tank_Object_Name;
set<CPvcsControlObjectInfo> CDxfLayout             ::m_infoObject;
CDxfLayout                             *CDxfLayout ::PwrPack                    = NULL;
volatile bool                          CDxfLayout  ::m_bAddingObjectInfo        = false;
CDxfLayout   *CDxfLayout                           ::CDxfTank                   = NULL;
bool         CDxfLayout                            ::drawn                      = false;
bool CDxfLayout                                    ::m_bIsFindControlObjectInfo = false;
IMPLEMENT_DYNAMIC(CDxfLayout, CWnd)

// Function name   : CDxfLayout::CDxfLayout
// Description     : Constructor
// Return type     :

CDxfLayout::CDxfLayout()
	: m_ptrPath(NULL)
	, m_ptrHatch(NULL)
	, m_ptrRegionInfo(NULL)
	, m_bDraw(false)
	, m_bIsShipLayout(true)
	, m_strTankLayer(_T(""))
	, m_ptriMap(NULL)
	, m_dScale(1.0f)
	, m_bSuccess(false)
	, m_bAlmFirst(0)
	, m_bIsShowScreenStatusText(false)
	, m_hMemDC_Scaled(NULL)
	, m_PrevX(0)
	, m_PrevY(0)
	, m_PrevScrollX(0)
	, m_PrevScrollY(0)
	, Delta(0.25)
	, DragStart(true)
	, ScaleX(1.0)
	, ScaleY(1.0)
	, hasLineCol(false)
	, hasTextCol(false)
	, hasBackGround(false)
	, BackGroundCol(Gdiplus::Color::Blue) //White;; // Gray
	, ObjectCol(Gdiplus::Color::White) //Color::Black; // White EHSMark
	, LineCol(Gdiplus::Color::Black)
	, TextCol(Gdiplus::Color::Black)
	, UpdateDelay(0)
	,m_ptrTankMap(NULL)
	{
	using namespace Gdiplus;
	m_hMemDC = CreateCompatibleDC(NULL);
	OrgScaleX = theConfiguration().GetScaleX();
	OrgScaleY = theConfiguration().GetScaleY();
	SplitScreens = theConfiguration().GetSplitScreens();
	Delta = 1 / max(OrgScaleX, OrgScaleY);
	//m_hMemDCBuffer = CreateCompatibleDC( NULL );
	if (!m_hMemDC /*|| !m_hMemDCBuffer*/) MessageBox("Cannot create memDC");
}


// Function name   : CDxfLayout::~CDxfLayout
// Description     : Destructor
// Return type     :

CDxfLayout::~CDxfLayout() {

	if (m_ptrPath)   	 delete[] m_ptrPath;
	if (m_ptrHatch)      delete[] m_ptrHatch;
	if (m_ptrRegionInfo) delete[] m_ptrRegionInfo;
	if (m_ptriMap)       delete[] m_ptriMap;
}


BEGIN_MESSAGE_MAP(CDxfLayout, CWnd)
ON_WM_PAINT()
ON_WM_HSCROLL()
ON_WM_VSCROLL()
ON_WM_MOUSEMOVE()
ON_WM_SIZE()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// Function name   : CDxfLayout::OnPaint
// Description     : WM_PAINT message handler
// Return type     : void

void CDxfLayout::OnPaint() {
	CPaintDC dc(this);

	CRect    rc;

	GetClientRect(&rc);
	double xCurScrollPos = GetScrollPos(SB_HORZ);
	double yCurScrollPos = GetScrollPos(SB_VERT);
	double ScrollWidth   = (ScaleX - 1.0) * rc.Width();
	double ScrollHeight  = (ScaleY - 1.0) * rc.Height();
	double xCurPos       = 0.0;
	double yCurPos       = 0.0;
	if (!m_bIsShipLayout) {
		xCurPos = max(0.0, xCurScrollPos * ScrollWidth / double(GetScrollLimit(SB_HORZ) - 1));
		yCurPos = max(0.0, yCurScrollPos * ScrollHeight / double(GetScrollLimit(SB_VERT) - 1));
	}

	// The drawing has already being done on memory buffer pointed by m_hMemDC
	// so just copy the drawn Bitmap to the window
	BitBlt(dc, 0, 0, rc.Width(), rc.Height(), m_hMemDC, int(xCurPos), int(yCurPos), SRCCOPY);
	CWnd::OnPaint();

}

void CDxfLayout::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	// its horizontal scroll bar
	int   nCurPos = GetScrollPos(SB_HORZ);
	CRect rect;
	GetClientRect(&rect);
	bool EndScroll = false;
	// decide what to do for each diffrent scroll event
	switch (nSBCode) {
	case SB_LEFT:
		nCurPos = 0;
		break;
	case SB_RIGHT:
		nCurPos = GetScrollLimit(SB_HORZ) - 1;
		break;
	case SB_LINELEFT:
		if (nCurPos > 0) nCurPos--;
		break;
	case SB_LINERIGHT:
		if (nCurPos < GetScrollLimit(SB_HORZ) - 1) nCurPos++;
		break;
	case SB_PAGELEFT:
		nCurPos = 0;
		break;
	case SB_PAGERIGHT:
		nCurPos = GetScrollLimit(SB_HORZ) - 1;
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		nCurPos = nPos;
		break;
	case SB_ENDSCROLL:
		EndScroll = true;
		break;
	}
	if (!EndScroll && ScaleX >= 1.0) {
		m_PrevScrollX = SetScrollPos(SB_HORZ, nCurPos);
		CRect rect;
		GetClientRect(&rect);
		double ScrollWidth = (ScaleX - 1) * rect.Width();
		int    xScroll     = int((m_PrevScrollX - nCurPos) * ScrollWidth / double(GetScrollLimit(SB_HORZ)));
		ScrollWindow(xScroll, 0);
	}
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDxfLayout::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	// its horizontal scroll bar
	int  nCurPos   = GetScrollPos(SB_VERT);
	bool EndScroll = false;
	// decide what to do for each diffrent scroll event
	switch (nSBCode) {
	case SB_LEFT:
		nCurPos = 0;
		break;
	case SB_RIGHT:
		nCurPos = GetScrollLimit(SB_VERT) - 1;
		break;
	case SB_LINELEFT:
		if (nCurPos > 0) nCurPos--;
		break;
	case SB_LINERIGHT:
		if (nCurPos < GetScrollLimit(SB_VERT) - 1) nCurPos++;
		break;
	case SB_PAGELEFT:
		nCurPos = 0;
		break;
	case SB_PAGERIGHT:
		nCurPos = GetScrollLimit(SB_VERT) - 1;
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		nCurPos = nPos;
		break;
	case SB_ENDSCROLL:
		EndScroll = true;
		break;
	}
	if (!EndScroll && ScaleY >= 1.0) {
		m_PrevScrollY = SetScrollPos(SB_VERT, nCurPos);
		CRect rect;
		GetClientRect(&rect);
		double ScrollHeight = (ScaleY - 1) * rect.Height();
		int    yScroll      = int((m_PrevScrollY - nCurPos) * ScrollHeight / double(GetScrollLimit(SB_VERT)));
		ScrollWindow(0, yScroll);
	}
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

// Function name   : CDxfLayout::Draw
// Description     : Draws the dxf drawing on memory buffer pointed by m_hMemDC
// Return type     : void
// Argument        : void

void CDxfLayout::Draw(void) {
	using namespace Gdiplus;
	using namespace PvcsControlObjectTypes;
	if (UpdateDelay) {
		UpdateDelay--;
	}else{
		DrawBackground(); // First draw the background

	//  BEGINTICK("Draw");
		if (m_bDraw && m_bSuccess) { // If its OK to draw now
			Graphics graphics(m_hMemDC, m_hMemDC_Scaled); // Attach graphics to bitmap buffer
			if (graphics.GetSmoothingMode() != SmoothingModeHighQuality) {
				graphics.SetSmoothingMode(SmoothingModeHighQuality);
			}
			//graphics.SetPageScale(2.0);

			// If graphics was initialised properly
			if (graphics.GetLastStatus() == Ok) {
				Color brushColor;
				// Uncomment the next line to draw smoother but slower
				// EHSMark

				TransformGraphics(graphics); // Tranform the graphics

				// Get the number of regions to draw
				const int nCount = m_dxfDrawing.Entity().Polyline().GetCount();
				//m_ptrRegionInfo[0].GetType()
				for (int i = 0; i < nCount; i++) {
					CAcDbPolyLine *tmpPtr      = (CAcDbPolyLine *)&m_dxfDrawing.Entity().Polyline()[m_ptriMap[i]];
					double        PWidth       = tmpPtr->GetPenSize();

					bool          HasColorInfo;
					int           LineColor;
					if (hasLineCol) {
						LineColor = LineCol;
					} else {
						LineColor = tmpPtr->GetColor(&HasColorInfo);
						if (!HasColorInfo) {
							LineColor = m_dxfDrawing.Table().Layer().GetColor(tmpPtr->GetLayerName());
							tmpPtr->SetColor(LineColor);
						}
					}


					switch (m_ptrRegionInfo[i].GetType()) {
					default:
					case DxfRegionInfo::None:
						/*if (m_bIsShipLayout) {
				  m_ptrRegionInfo[i].SetPen(LineColor, (const float)(PWidth / m_dScale));
				  m_ptrRegionInfo[i].SetBrush(ObjectCol); // Object information not present in Config file
			  } else */{
							m_ptrRegionInfo[i].SetPen(LineColor, float(PWidth / m_dScale));
							m_ptrRegionInfo[i].SetBrush(UndefObjectCol/*BackGroundCol*/); // Object information not present in Config file
						}
						break;
					case DxfRegionInfo::Tank:
						if (m_bIsShipLayout) {
							double PWd = PWidth / m_dScale;
							if (m_ptrRegionInfo[i].m_bIsBold) {
								PWd *= 3.0;
							}
							m_ptrRegionInfo[i].SetPen(Color(LineColor), (const float)(PWd));
							// Get the color of this tank region
							CString color_strtemp;
							int     iTankID       = m_ptrRegionInfo[i].GetIndex();
							if (SplitScreens >= 2) {
								int     iAlarm        = atoi(theShipData().GetTank(iTankID, m_ptrTankMap).GetAlarmStatus());
								// If there is no Alarm
								if (iAlarm == 0) {
									color_strtemp = theShipData().GetTank(iTankID, m_ptrTankMap).GetCargoColor(); // Get the cargo color
								}  else
								// before JSD strtemp = "0x0000ff"; // Tank drawn in Red color
								{
									//Start JSD
									if ((iAlarm != 0) && (m_bAlmFirst == 0)) {
										color_strtemp = "0x0000ff"; // Tank drawn in Red color
									} else color_strtemp = "0x00ff00"; // Tank drawn in Red color
																	   //End JSD
								}
							} else {}
							if (color_strtemp.IsEmpty()) {
								m_ptrRegionInfo[i].SetBrush(ObjectCol); // Object information not present in Config file
							} else {
								COLORREF colorTank;
								// Get the color stored in Hex format
								sscanf_s(color_strtemp, "%x", &colorTank);

								// Now set the color
								m_ptrRegionInfo[i].SetBrush(Color(GetRValue(colorTank),	GetGValue(colorTank), GetBValue(colorTank)));

							}
						} else {
							m_ptrRegionInfo[i].SetBrush(BackGroundCol/*Color::White*/);
							m_ptrRegionInfo[i].SetPen(LineColor/*unsigned(Color::Black)*/, float(PWidth / m_dScale));
						}
						break;
					case DxfRegionInfo::Pipeline:
						m_ptrRegionInfo[i].SetPen(LineColor, (const float)(PWidth / m_dScale));
						m_ptrRegionInfo[i].SetBrush(ObjColorVector[i]); // Object information not present in Config file
						break;
					case DxfRegionInfo::ControlObject: // This region is control object
						{
							m_ptrRegionInfo[i].SetPen(LineColor, float(PWidth / m_dScale));
							int     iIndex = m_ptrRegionInfo[i].GetIndex(), iSubIndex = m_ptrRegionInfo[i].GetSubIndex(), iSubIndex2 = m_ptrRegionInfo[i].GetSubIndex2();

							Info_it it     = m_infoObject.find(CPvcsControlObjectInfo(iIndex, iSubIndex, iSubIndex2));
							// Now set the brush color according to the type and status of control object
							if (it != m_infoObject.end()) {
								Gdiplus::ARGB StatCol = theController().GetController((*it)).GetColor(*it, iSubIndex2);
								brushColor = StatCol;
								brushColor.SetFromCOLORREF(StatCol);

								m_ptrRegionInfo[i].SetBrush(brushColor);
							} else { // if( it != m_infoObject.end() )
								m_ptrRegionInfo[i].SetBrush(unsigned(ObjectCol)); // EHSMark Object information not present in Config file
							}
						}
						break;
					}
					// Now Draw the regions
					// See if we must fill a region
					if (tmpPtr->GetFlag() == 1) {
						graphics.FillPath(m_ptrRegionInfo[i].GetBrush(), &m_ptrPath[i]);
						graphics.DrawPath(&m_ptrRegionInfo[i].GetPen(), &m_ptrPath[i]);
					} else {
						//graphics.FillPath(m_ptrRegionInfo[i].GetBrush(), &m_ptrPath[i]);
						graphics.DrawPath(&m_ptrRegionInfo[i].GetPen(), &m_ptrPath[i]);
					}

					//Pen pen( Color::MidnightBlue );         // with Blue border
					//graphics.DrawPath(&pen, &m_ptrPath[i]);
				}
			} // if( graphics.GetLastStatus() == Ok )

	//      SHOWTICK("Done");
	// Now draw the text
			DrawText(); // Tank names and values
			DrawMText(); // The multiline text
			DrawFreeValues();

			// Send WM_PAINT message to window
			RedrawWindow();
		} // if(m_bDraw)

	}
}


// Function name   : CDxfLayout::Open
// Description     : Opens and loads a dxf file
// Return type     : bool
// Argument        : const CString& param_strFileName
// Argument        : const CString& param_strTankLayer
// Argument        : const bool& param_bIsShipLayout

bool CDxfLayout::Open(const CString &param_strFileName, const CString &param_strTankLayer, const bool &param_bIsShipLayout, const unsigned param_Color, const unsigned param_BGColor, const unsigned param_LineColor, const unsigned param_TextColor, const bool param_hasLineCol, const bool param_hasTextCol, const bool param_hasBackGround) {
	bool bSuccess = true;
	using namespace DxfErrorCodes;
	if (param_bIsShipLayout) {
		ObjectCol     = param_Color;
		hasLineCol	  = param_hasLineCol;
		hasTextCol	  = param_hasTextCol;
		hasBackGround =	param_hasBackGround;
		ObjectCol     = param_Color;
		LineCol 	  = param_LineColor;
		TextCol 	  = param_TextColor;
		BackGroundCol = param_BGColor;
		UndefObjectCol = 0;
	}
	// Load and store the dxf drawing
	if (m_dxfDrawing.Load(static_cast<LPCTSTR>(param_strFileName)) != NoError) {
		CString strTemp;
		strTemp.Format("Error Loading File: %s", param_strFileName);
		XmlLogError(strTemp);
		bSuccess = false;
	}

	// Check if the specified tank layer is present in the drawing
	// EHSMark
	if (param_bIsShipLayout && bSuccess && !m_dxfDrawing.Table().Layer().GetLayer(LPCTSTR(param_strTankLayer))) {
		CString strTemp;
		strTemp.Format("Cannot find layer : %s", param_strTankLayer);
		XmlLogError(strTemp);
		bSuccess = false;
	}

	if (bSuccess) { // If the Load was successful and tank layer is present
		m_strTankLayer = static_cast<LPCTSTR>(param_strTankLayer);
		m_bIsShipLayout = param_bIsShipLayout;
		const int nCount = m_dxfDrawing.Entity().Polyline().GetCount();
		try {
			m_ptriMap = new int[nCount+100]; // initialize the mapping vector  EHSMark, possible overrun, thus increasing size
		} catch (exception &e) {
			//TRACE("*******exception in dxflayout-open*****");
			XmlLogError("Cannot allocate memory for mapping vector");
			XmlLogError(e.what());
			bSuccess = false;
		}

		if (bSuccess) {
			int j = 0;

			// Set the mapping vector so that the tank regions are mapped first
			// The tank regions are identified by their Layer name
			// All the polylines in this layer will be interpreted as tank polylines
			for (int i = 0; i < nCount; i++) if (m_dxfDrawing.Entity().Polyline()[i].GetLayerName() == m_strTankLayer) m_ptriMap[j++] = i;

			// Now map the rest of the regions
			for (int i = 0; i < nCount; i++) if (m_dxfDrawing.Entity().Polyline()[i].GetLayerName() != m_strTankLayer) m_ptriMap[j++] = i;
		} // if( bSuccess )


		if (bSuccess && !LoadRegions()) {
			XmlLogError("Error Loaing Regions");
			bSuccess = false;
		}
	} // if( bSuccess )

	if (bSuccess) {
		m_bSuccess = true;

		if (!m_bIsShipLayout) {
			if (theApp.ZoomEnabled()) {}
			CDxfTank = this;
		}
		// *********** Done by  , as told by Asle, to remove Red color bar and Alarm text
		//SetTimer( IDT_ALARM_BEEP, 10000, NULL );

		Draw();
		int Index = param_strFileName.Find("BESI");
		if (Index != -1) {
			PwrPack = this;

		}
	}
	return bSuccess;
}


// Function name   : CDxfLayout::LoadRegions
// Description     : Stores the polyline entities in the dxf as Gdiplus::GraphicsPath
// Return type     : bool
// Argument        : void

bool CDxfLayout::LoadRegions(void) {
	bool      bSuccess = true;
	using namespace Gdiplus;


	// Get the number of polylines
	const int nCount   = m_dxfDrawing.Entity().Polyline().GetCount();
	// Get the number of Hatch
	const int oCount   = m_dxfDrawing.Entity().Hatch().GetCount();

	// Check if there ARE any polylines or not
	if (!nCount) {
		XmlLogError("No polylines present in the drawing");
		bSuccess = false;
	}

	if (bSuccess) {
		try {
			m_ptrPath       = new GraphicsPath[nCount];
			m_ptrHatch      = new GraphicsPath[oCount];
			m_ptrRegionInfo = new CDxfRegionInfo[nCount];
		} catch (exception &e) {
			//TRACE("*******exception in dxflayout-loadregion*****");
			XmlLogError("Cannot allocate memory for GraphicsPath/RegionInfo");
			XmlLogError(e.what());
			bSuccess = false;
		}
		if (bSuccess) {
			// First create the hatches
			//
			for (int i = 0; i < oCount && bSuccess; i++) {
				//int PtriM = m_ptriMap[i];
				CAcDbPolyLine tempPolyline = m_dxfDrawing.Entity().Hatch()[i];
				const int     nVertex      = tempPolyline.GetVertexCount();

				for (int j = 0; j < (nVertex - 1); j++) AddPath(m_ptrHatch[i], tempPolyline[j], tempPolyline[j + 1]);
				m_ptrHatch[i].CloseFigure();
			}

			// Now load the polylines as Gdipluas::GraphicsPath
			// The graphics path wiil be used to draw the regions
			// and to create regions for hit-testing
			for (int i = 0; i < nCount && bSuccess; i++) {
				// Get the polyline using m_ptriMap mapping vector
				// so that the tank regions are stored first
				{
					CAcDbPolyLine tempPolyline = m_dxfDrawing.Entity().Polyline()[m_ptriMap[i]];
					const int     nVertex      = tempPolyline.GetVertexCount();

					for (int j = 0; j < (nVertex - 1); j++) {
						AddPath(m_ptrPath[i], tempPolyline[j], tempPolyline[j + 1]);
					}
					//AddPath(m_ptrPath[i], tempPolyline[0], tempPolyline[0 + 1]);
					if (tempPolyline.GetFlag() == 1) {
						m_ptrPath[i].CloseFigure();
					}
				}

				// Get the Bounding rectangle for the drawing
				RectF rect;

				m_ptrPath[i].GetBounds(&rect);

				if (i == 0) {
					m_boundRect.minPoint.SetX(rect.X);
					m_boundRect.minPoint.SetY(rect.Y);

					m_boundRect.maxPoint.SetX(rect.X + rect.Width);
					m_boundRect.maxPoint.SetY(rect.Y + rect.Height);
				} else {
					m_boundRect.minPoint.SetX(min(m_boundRect.minPoint.GetX(), rect.X));
					m_boundRect.minPoint.SetY(min(m_boundRect.minPoint.GetY(), rect.Y));

					m_boundRect.maxPoint.SetX(max(m_boundRect.maxPoint.GetX(), rect.X + rect.Width));
					m_boundRect.maxPoint.SetY(max(m_boundRect.maxPoint.GetY(), rect.Y + rect.Height));
				}
				int Color = ObjectCol;
				for (int j = 0; j < oCount; j++) {
					RectF rect2;
					m_ptrHatch[j].GetBounds(&rect2);

					if (rect.Contains(rect2)) {
						CAcDbPolyLine tmpPtr = m_dxfDrawing.Entity().Hatch()[j];
						Color = m_dxfDrawing.Table().Layer().GetColor(tmpPtr.GetLayerName());
					}
				}
				ObjColorVector.push_back(Color);
			} // for(int i=0; i<nCount; i++)

			// Since the regions have been loaded now, its OK to draw the layout
			m_bDraw = true;
			GetRegionInfo(); // Load the information about the regions
			LoadTankNames(); // Load the names for tank
							 //Draw();

		} // if( bSuccess )
	} // if( bSuccess )

	return bSuccess;
}


// Function name   : CDxfLayout::DrawBackground
// Description     : Draws the background for the Layout
// Return type     : void

void CDxfLayout::DrawBackground() {
	using namespace Gdiplus;

	CRect rectWindow;
	GetClientRect(&rectWindow);
	if (!m_bIsShipLayout) {
		rectWindow.right *= LONG(OrgScaleX);
		rectWindow.bottom *= LONG(OrgScaleY);
	}
	Graphics graphics(m_hMemDC);

	if (graphics.GetLastStatus() == Ok) {
		Color Clr;
		if (hasBackGround) {
			Clr = BackGroundCol;
		} else {
			Clr = Color::Black;
		}

		//SolidBrush brush(BackGroundCol/*Color::MidnightBlue*//*BackGroundCol | 0xff000000*/);
		SolidBrush brush(Clr);

		Pen        pen(Color::MidnightBlue);         // with Blue border
		graphics.FillRectangle(&brush, rectWindow.left, rectWindow.top, rectWindow.right, rectWindow.bottom);
		graphics.DrawRectangle(&pen, rectWindow.left, rectWindow.top, rectWindow.right - 1, rectWindow.bottom - 1);
	}

}


// Function name   : CDxfLayout::OnSize
// Description     : WM_SIZE message handler
// Return type     : void
// Argument        : UINT nType
// Argument        : int cx
// Argument        : int cy

void CDxfLayout::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);
	// The window has been initiazed to valid size
	if (cx || cy) {
		CClientDC dc(this);
		CRect     rect;
		GetClientRect(&rect);

		int DlgCtrlID = GetDlgCtrlID();
		if (DlgCtrlID) {
			rect.right *= LONG(OrgScaleX);
			rect.bottom *= LONG(OrgScaleY);
		}
		// Initialize the drawing buffer with appropriate size
		m_hMemDC_Scaled = SelectObject(m_hMemDC, CreateCompatibleBitmap(dc, rect.Width(), rect.Height())); //EHSMark
		Draw();
	}
}


// Function name   : CDxfLayout::GetRegionInfo
// Description     : Stores the information about the regions
// Return type     : bool
// Argument        : void

bool CDxfLayout::GetRegionInfo(void) {
	using namespace Gdiplus;
	using namespace DxfRegionInfo;

	//int mCount = m_dxfDrawing.Entity().Hatch().GetCount();
	int  nCount     = m_dxfDrawing.Entity().Polyline().GetCount();
	int  nTextCount = m_dxfDrawing.Entity().Text().GetCount();

	// The tank regions will be gone through first
	bool bIsTank    = true;
	for (int i = 0; i < nCount; i++) {
		// EHSMark
		CAcDbPolyLine *tmpPtr   = (CAcDbPolyLine *)&m_dxfDrawing.Entity().Polyline()[m_ptriMap[i]];
		const double  PWidth    = tmpPtr->GetPenSize();
		int           LineColor = m_dxfDrawing.Table().Layer().GetLayer(tmpPtr->GetLayerName());
		//m_ptrRegionInfo[i].SetPenWidth(PWidth);
		if (bIsTank && (m_dxfDrawing.Entity().Polyline()[m_ptriMap[i]].GetLayerName() != m_strTankLayer)) bIsTank = false; // All the tanks regions have been done

		Region reg(&m_ptrPath[i]);

		for (int j = 0; j < nTextCount; j++) {
			const string &tempText = m_dxfDrawing.Entity().Text()[j].GetValue();

			// If this This is a locator text
			if (CDxfRegionInfo::IsLocatorText(tempText)) {
				if ((bIsTank && tolower(tempText[1]) == 't') // if current region is tank and this is locator for tank
					|| (!bIsTank && tolower(tempText[1]) != 't')) { // if current region is not a tank and this is not a locator for tank
					float x = (float)m_dxfDrawing.Entity().Text()[j].GetPosition().GetX();
					float y = (float)m_dxfDrawing.Entity().Text()[j].GetPosition().GetY();

					// If the locator text falls into the current region
					if (reg.IsVisible(x, y)) m_ptrRegionInfo[i].SetInfo(tempText); // Set the type info for this region using the locator text

				} // if( ( bIsTank && tempText[1] == 't') || ( !bIsTank && tempText[1] != 't') )
			} // if( CDxfRegionInfo::IsLocatorText( tempText ) )
		} // for(int j=0; j<nTextCount; j++)

		// Process the region furter depending upon the type of region
		switch (m_ptrRegionInfo[i].GetType()) {
		case Tank :
			ProcessClickOnTank(i);
			break;
		case Pipeline :
			// If this is Tank layout, draw all the pipes as blue
			// EHSMark Changed width
			if (!m_bIsShipLayout) {
				m_ptrRegionInfo[i].SetBrush(unsigned(Color::DodgerBlue));
				//m_ptrRegionInfo[i].SetPen( Color::MidnightBlue, (float)(1.0/m_dScale) );
				// EHSMark
				//CAcDbPolyLine *tmpPolyline = (CAcDbPolyLine*)&m_dxfDrawing.Entity().Polyline()[m_ptriMap[i]];
				//const double lPWidth = tmpPolyline->GetPenSize();
				//m_ptrRegionInfo[i].SetPenWidth(lPWidth/m_dScale);

			} // if( !m_bIsShipLayout )
			break;
		case ControlObject:
			{
				CPvcsControlObjectInfo        tempInfo;

				CPvcsControlObjectTimeOutInfo tempTimeOutInfo(m_ptrRegionInfo[i].GetIndex(), m_ptrRegionInfo[i].GetSubIndex());

				tempInfo.LoadInfo(m_ptrRegionInfo[i].GetIndex(), m_ptrRegionInfo[i].GetSubIndex(), m_ptrRegionInfo[i].GetSubIndex2());

				while (m_bAddingObjectInfo) Sleep(0);
				m_bAddingObjectInfo = true;
				m_infoObject.insert(tempInfo);
				theTimeOutInfo().insert(tempTimeOutInfo);
				m_bAddingObjectInfo = false;
			}
			break;
		default:
			//m_ptrRegionInfo[i].SetPen( Color::LightGreen, (float)(4.0/m_dScale),false );
			break;

		} // switch( m_ptrRegionInfo[i].GetType() )

	} // for(int i=0; i<nCount; i++)

	return false;
}


// Function name   : CDxfLayout::OnLButtonDown
// Description     : WM_LBUTTONDOWN Message handler
// Return type     : void
// Argument        : UINT nFlags
// Argument        : CPoint point

void CDxfLayout::OnLButtonDown(UINT nFlags, CPoint point) {
	using namespace Gdiplus;
	using namespace DxfRegionInfo;

	if (WaitForSingleObject(CPvcsScreenFrame::m_hMutex, 3000) == WAIT_OBJECT_0) {
		//CSingleLock singlelock(&g_CS_Update);
		//singlelock.Lock();
		//if (singlelock.IsLocked()) {
		// Inform the parent window of the mouse click
		// and let the parent process the message before we go further
		GetParent()->SendMessage(WM_LBUTTONDOWN);

		Graphics graphics(m_hMemDC, m_hMemDC_Scaled); // Attach graphics to bitmap buffer
		if (graphics.GetLastStatus() == Ok) {
			CRect rc;
			GetClientRect(&rc);

			Matrix matrix;
			TransformGraphics(graphics);
			graphics.GetTransform(&matrix);

			CPoint ScrolPoint = point;
			if (GetScrollLimit(SB_HORZ) && GetScrollLimit(SB_VERT)) {
				double ScrollWidth  = (ScaleX - 1) * rc.Width();
				double ScrollHeight = (ScaleY - 1) * rc.Height();
				int    xScroll      = int(GetScrollPos(SB_HORZ) * ScrollWidth / double(GetScrollLimit(SB_HORZ)));
				int    yScroll      = int(GetScrollPos(SB_VERT) * ScrollHeight / double(GetScrollLimit(SB_VERT)));
				ScrolPoint.x += xScroll;
				ScrolPoint.y += yScroll;
			}
/*
		PointF Spoint( float(ScrolPoint.x),float(ScrolPoint.y));

		// transform the coordinates of the locator to the screen coordinates
		matrix.TransformPoints( &Spoint );
*/
			int  nCount = m_dxfDrawing.Entity().Polyline().GetCount();

			bool bDone  = false;

			for (int i = 0; i < nCount; i++) {
				// Reset the colors for all the regions
				CAcDbPolyLine *tmpPtr   = (CAcDbPolyLine *)&m_dxfDrawing.Entity().Polyline()[m_ptriMap[i]];
				double        PWidth    = tmpPtr->GetPenSize();
				unsigned      LineColor = m_dxfDrawing.Table().Layer().GetLayer(tmpPtr->GetLayerName());
				m_ptrRegionInfo[i].SetPen(Color(LineColor), float(PWidth / m_dScale));

				// If clicked on a tank in the ship layout
				if (!bDone && m_bIsShipLayout && m_ptrRegionInfo[i].GetType() == Tank) {
					// Transform the drawing to the screen coordiantes

					//Matrix matrix;
					//TransformGraphics( graphics );
					//graphics.GetTransform(&matrix);

					Region reg(&m_ptrPath[i]);
					reg.Transform(&matrix);

					// If this tank region is the one which has been clicked upon
					if (reg.IsVisible(ScrolPoint.x, ScrolPoint.y)) {
						bDone = true;

						// Get the main splitter window
						// The hierarchy is... ( Child > Parent )
						// CDxfLayout > CPvcsShipView > CPvcsSplitterLowerWnd > CPvcsSplitterWnd
						CPvcsSplitterWnd *tempSplitterWnd = dynamic_cast<CPvcsSplitterWnd *>(GetParent()->GetParent()->GetParent());

						// Now tell the window to take action corresponding to this click
						if (tempSplitterWnd) tempSplitterWnd->ActivateTank(m_ptrRegionInfo[i].GetIndex());

					} // if( reg.IsVisible( ScrolPoint.x, ScrolPoint.y, &graphics ) )


				} // if( !bDone && m_bIsShipLayout && m_ptrRegionInfo[i].GetType() == Tank )

				// If the mouse click was upon a Control object in tank window
				else if (!bDone && m_ptrRegionInfo[i].GetType() == ControlObject) {
					//get the Active window
					CPvcsFrame *ptrScreenFrame = (CPvcsFrame *)CWnd::GetActiveWindow();
					if (ptrScreenFrame != NULL) {
						CString strWindowText = "";
						ptrScreenFrame->GetWindowText(strWindowText);

						strWindowText.MakeLower();
						//if having 'command' text for more conformity, if not found, then some other window is active
						if (strWindowText.Find("command") != -1) {
							//Check for the Command status, if having command then show control otherwise not
							if (CPvcsScreenInfo::m_vecScreenInfo[ptrScreenFrame->ScreenNumber - 1]->m_bCommandStatus) {
								// Transform the drawing to the screen coordiantes
								// Matrix matrix;
								// TransformGraphics( graphics );
								// graphics.GetTransform(&matrix);

								Region reg(&m_ptrPath[i]);
								reg.Transform(&matrix);

								Rect rect;
								reg.GetBounds(&rect, &graphics);

								// If this control object region is the one which has been clicked upon
								if (rect.Contains(Point(ScrolPoint.x, ScrolPoint.y))) {
									bDone = true;

									// Now take the desired action
									ProcessClickOnObject(i, point, ptrScreenFrame->ScreenNumber);
								} // if( reg.IsVisible( point.x, point.y, &graphics ) )
							} //if(CPvcsScreenInfo::m_vecScreenInfo[ptrScreenFrame->ScreenNumber - 1]->m_bCommandStatus)
						} //if(strWindowText.Find("command"))
					} //if(ptrScreenFrame != NULL)
				}

			} // for(int i=0; i<nCount; i++)

		} // if( graphics.GetLastStatus() == Ok )
		  // Redraw the layout as some colors or bush may have changed
		Draw();
		//singlelock.Unlock();
		ReleaseMutex(CPvcsScreenFrame::m_hMutex);
	}
}


// Function name   : CDxfLayout::OnMButtonDown
// Description     : WM_MBUTTONDOWN Message handler
// Return type     : void
// Argument        : UINT nFlags
// Argument        : CPoint point

void CDxfLayout::OnMButtonDown(UINT nFlags, CPoint point) {
	using namespace Gdiplus;
	using namespace DxfRegionInfo;

	if (WaitForSingleObject(CPvcsScreenFrame::m_hMutex, 3000) == WAIT_OBJECT_0) {
		//CSingleLock singlelock(&g_CS_Update);
		//singlelock.Lock();
		ReleaseMutex(CPvcsScreenFrame::m_hMutex);
	}
	// Inform the parent window of the mouse click
	// and let the parent process the message before we go further
	GetParent()->SendMessage(WM_MBUTTONDOWN);
}


// Function name   : CDxfLayout::OnRButtonDown
// Description     : WM_RBUTTONDOWN Message handler
// Return type     : void
// Argument        : UINT nFlags
// Argument        : CPoint point

void CDxfLayout::OnRButtonDown(UINT nFlags, CPoint point) {
	using namespace Gdiplus;
	using namespace DxfRegionInfo;


	if (WaitForSingleObject(CPvcsScreenFrame::m_hMutex, 3000) == WAIT_OBJECT_0) {
		//CSingleLock singlelock(&g_CS_Update);
		//singlelock.Lock();
		ReleaseMutex(CPvcsScreenFrame::m_hMutex);
	}
	// Inform the parent window of the mouse click
	// and let the parent process the message before we go further
	GetParent()->SendMessage(WM_RBUTTONDOWN);
}


void CDxfLayout::OnMButtonUp(UINT nFlags, CPoint point) {
	// Inform the parent window of the mouse click
	// and let the parent process the message before we go further
	GetParent()->SendMessage(WM_MBUTTONUP);
}


// Function name   : CDxfLayout::OnRButtonDown
// Description     : WM_RBUTTONDOWN Message handler
// Return type     : void
// Argument        : UINT nFlags
// Argument        : CPoint point

void CDxfLayout::OnRButtonUp(UINT nFlags, CPoint point) {
	// Inform the parent window of the mouse click
	// and let the parent process the message before we go further
	GetParent()->SendMessage(WM_RBUTTONUP);
}
// Function name   : CDxfLayout::Create
// Description     : Creates a dxflayout window as a child window
// Return type     : bool
// Argument        : const RECT& param_rect
// Argument        : CWnd* param_pParentWnd

bool CDxfLayout::Create(const RECT &param_rect, CWnd *param_pParentWnd) {
	RECT myRect    = (RECT)param_rect;
	int  Flags     = WS_CHILD | WS_VISIBLE;
	int  DlgCtrlID = param_pParentWnd->GetDlgCtrlID();
	if (!DlgCtrlID) {
		if (OrgScaleX != 1.0) {
			Flags |= WS_HSCROLL;
			//myRect.bottom -= 25;
		}
		if (OrgScaleY != 1.0) {
			Flags |= WS_VSCROLL;
		}
	}
	return CWnd::Create(NULL, NULL, Flags, myRect, param_pParentWnd, IDC_DXFLAYOUT) != 0;
}


// Function name   : CDxfLayout::TransformGraphics
// Description     : Tranforms the coordinates of the original dxf drawing to screen coordinates
// Return type     : void
// Argument        : Gdiplus::Graphics& param_graphics

void CDxfLayout::TransformGraphics(Gdiplus::Graphics &param_graphics) {
	using namespace Gdiplus;

	// The is the border width
	const int border   = 10;
	CRect     rect;

	// The coordinates in the drawing has Y-axis positive in the
	// upward direction like this ( Cartesian coordinate system )
	//  A
	//  |
	//  |
	//  +------>
	//
	//But the screen has Y-axis positive in the downward direction like this
	//  +------>
	//  |
	//  |
	//  V
	//
	// So first of all we have to flip the drawing upside down
	// This matrix flips the drawing upside down
	Matrix    myMatrix(1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);

	// Get the size of this window
	GetClientRect(&rect);
	if (!m_bIsShipLayout) {
		rect.right = LONG((rect.right - rect.left) * ScaleX + rect.left);
		rect.bottom = LONG((rect.bottom - rect.top) * ScaleY + rect.top);
	} else {
		rect.bottom -= 25;
	}
	ScreenToClient(&rect);
	double Width  = rect.Width();
	double Height = rect.Height();
	double MaxX;
	double MaxY;
	double MinX;
	double MinY;

	if (m_bIsShipLayout) {
		MaxX = m_boundRect.maxPoint.GetX();
		MaxY = m_boundRect.maxPoint.GetY();
		MinX = m_boundRect.minPoint.GetX();
		MinY = m_boundRect.minPoint.GetY();
	} else {
		MaxX = m_dxfDrawing.GetMaxX();
		MaxY = m_dxfDrawing.GetMaxY();
		MinX = m_dxfDrawing.GetMinX();
		MinY = m_dxfDrawing.GetMinY();
	}
	// Get the Vertical scaling factor
	double vfactor = static_cast<double>(Height - (2 * border)) / (MaxY - MinY);
	// Get the Horizontal scaling factor
	double hfactor = static_cast<double>(Width - (2 * border)) / (MaxX - MinX);


	// Now flip the graphics using the matrix
	param_graphics.SetTransform(&myMatrix);

	// Now translate the graphics according to the current window size
	param_graphics.TranslateTransform(REAL(border), REAL(-Height + border));

	// The actual scaling factor will be the minimum of the two
	m_dScale = min(vfactor, hfactor);

	// Now scale the graphics so that the drawing occupies the window fully
	if (m_bIsShipLayout) {
		param_graphics.ScaleTransform(REAL(m_dScale), REAL(m_dScale));
	} else {
		param_graphics.ScaleTransform(REAL(hfactor), REAL(vfactor));
	}
	// Now again translate the graphics so that its origin is at the minimum coordinates of the drawing
	param_graphics.TranslateTransform(REAL(-MinX), REAL (-MinY));

}


// Function name   : CDxfLayout::LoadTankNames
// Description     : Stores the tank names from the config file
// Return type     : void
// Argument        : void

void CDxfLayout::LoadTankNames(void) {
	using namespace Gdiplus;

	const int nCount  = m_dxfDrawing.Entity().Text().GetCount();

	string    tempStr;
	for (int i = 0; i < nCount; i++) { // Loop through all the text
		CAcDbText tempText  = m_dxfDrawing.Entity().Text()[i];
		unsigned  TextColor = m_dxfDrawing.Table().Layer().GetColor(tempText.GetLayer());
		if (hasTextCol) {
			TextColor = TextCol;
		}
		tempStr = m_dxfDrawing.Entity().Text()[i].GetValue();

		// If this text is tank name locator
		if ((tempStr.size() > 2) && (tempStr[0] == '_')) {
			if ((tolower(tempStr[1]) == 't') && (tolower(tempStr[2]) == 'n')) {
				// Store the corresponding tank name
				m_strTankName.push_back(static_cast<LPCTSTR>(theConfiguration().GetTankName(CDxfRegionInfo::GetIndex(tempStr))));
				//string LayerName = m_dxfDrawing.Entity().Text().GetLayerName();
				PointF point((float)m_dxfDrawing.Entity().Text()[i].GetPosition().GetX(),
							 (float)m_dxfDrawing.Entity().Text()[i].GetPosition().GetY());

				// Store the coodinates
				m_posTankName.push_back(point);
				m_TankNameColor.push_back(TextColor);
				// Store font information
				m_FontTankName.push_back(tempText.GetFont());
				if (m_bIsShipLayout) {
					m_FontSizeTankName.push_back(12.0);
				} else {
					if (SplitScreens < 2) {
						m_FontSizeTankName.push_back(tempText.GetHeight());
					} else {
						m_FontSizeTankName.push_back(11.0);
					}
				}

			}

			// If this text is tank value locator
			else if ((tolower(tempStr[1]) == 't') && (tolower(tempStr[2]) == 'v')) {
				// Store the locator text for future reference
				m_strTankValues.push_back(tempStr);
				PointF point((float)m_dxfDrawing.Entity().Text()[i].GetPosition().GetX(),
							 (float)m_dxfDrawing.Entity().Text()[i].GetPosition().GetY());

				// Store the coodinates
				m_posTankValues.push_back(point);
				m_TankValueColor.push_back(TextColor);
				// Store font information

				m_FontTankValues.push_back(tempText.GetFont());
				if (SplitScreens < 2) {
					m_FontSizeTankValues.push_back(tempText.GetHeight());
				} else {
					m_FontSizeTankValues.push_back(11.0);
				}
			}
			// If this text is tank bargraph locator
			else if ((tolower(tempStr[1]) == 't') && (tolower(tempStr[2]) == 'b')) {
				string   tmpStr     = tempText.GetLayer();
				unsigned TextColor2 = m_dxfDrawing.Table().Layer().GetColor(tmpStr);
				// Store the locator text for future reference
				m_strTankBarGraphs.push_back(tempStr);
				PointF point((float)m_dxfDrawing.Entity().Text()[i].GetPosition().GetX(),
							 (float)m_dxfDrawing.Entity().Text()[i].GetPosition().GetY());
				RectF  tmpRect = LocateBarGraphRect(point);
				m_rectBarGraphs.push_back(tmpRect);
				// Store the coodinates
				m_posTankBarGraphs.push_back(point);
				m_TankBarGraphColor.push_back(TextColor);
				int Index    = CDxfRegionInfo::GetIndex(tempStr);
				int SubIndex = CDxfRegionInfo::GetSubIndex(tempStr);
				m_TankBarIndex.push_back(Index);
				m_TankBarSubIndex.push_back(SubIndex);

			}
			// If this text is tank alarm locator
			else if ((tolower(tempStr[1]) == 't') && (tolower(tempStr[2]) == 'a')) {
				// Store the locator text for future reference
				m_strTankAlarms.push_back(tempStr);
				PointF point((float)m_dxfDrawing.Entity().Text()[i].GetPosition().GetX(),
							 (float)m_dxfDrawing.Entity().Text()[i].GetPosition().GetY());

				// Store the coodinates
				m_posTankAlarms.push_back(point);
				m_TankAlarmColor.push_back(TextColor);
				m_TankAlarmColInverted.push_back(false);
				// Store font information
				m_FontTankAlarms.push_back(tempText.GetFont());
				m_FontSizeTankAlarms.push_back(tempText.GetHeight());

				int Index    = CDxfRegionInfo::GetIndex(tempStr);
				int SubIndex = CDxfRegionInfo::GetSubIndex(tempStr);
				int SubIndex2= CDxfRegionInfo::GetSubIndex2(tempStr);
				m_TankAlarmIndex.push_back(Index);
				m_TankAlarmSubIndex.push_back(SubIndex);
				m_TankAlarmSubIndex2.push_back(SubIndex2);
			}

			// If this text is Object value locator
			else if ((tempStr.size() > 3) && (tolower(tempStr[1]) == 'c') && (tolower(tempStr[3]) == 'v')) {
				// Store the locator text for future reference
				m_strObjectValues.push_back(tempStr);
				PointF point((float)m_dxfDrawing.Entity().Text()[i].GetPosition().GetX(),
							 (float)m_dxfDrawing.Entity().Text()[i].GetPosition().GetY());
				// Store the coodinates
				m_posObjectValues.push_back(point);
				m_ObjectValuesColor.push_back(TextColor);

				// Store font information
				m_FontObjectValues.push_back(tempText.GetFont());
				//if (SplitScreens < 2) {
					m_FontSizeObjectValues.push_back(tempText.GetHeight());
				//} else {
				//	m_FontSizeObjectValues.push_back(11.0);
				//}
			}
		}

	} // for( int i=0; i<nCount; i++ )

	const int nCountM = m_dxfDrawing.Entity().MText().GetCount();

	for (int i = 0; i < nCountM; i++) { // Loop through all the text
		CAcDbText tempText  = m_dxfDrawing.Entity().MText()[i];
		CString   strTemp   = tempText.GetValue().c_str();
		unsigned  TextColor = m_dxfDrawing.Table().Layer().GetColor(tempText.GetLayer());
		if (hasTextCol) {
			TextColor = TextCol;
		}

		strTemp.Remove('{');
		strTemp.Remove('}');

		if (strTemp[0] == '\\') {
			switch (strTemp[1]) {
			case 'L':
			case 'O':
				break;
			case 'C':
				strTemp = strTemp.Mid(4);
				break;
			}
		}

		int LineNumbers = strTemp.Replace("\\P", "\n");

		// If this text is tank name locator
		if ((strTemp.GetLength() > 2) && (strTemp[0] == '_')) {
			if ((tolower(strTemp[1]) == 't') && (tolower(strTemp[2]) == 'n')) {
				// Store the corresponding tank name
				m_strTankNameM.push_back(static_cast<LPCTSTR>(theConfiguration().GetTankName(CDxfRegionInfo::GetIndex(string(strTemp)))));

				PointF point((float)m_dxfDrawing.Entity().MText()[i].GetPosition().GetX(),
							 (float)m_dxfDrawing.Entity().MText()[i].GetPosition().GetY());

				// Store the coodinates
				m_posTankNameM.push_back(point);
				m_TankNameColorM.push_back(TextColor);
				// Store font information
				m_FontTankNameM.push_back(tempText.GetFont());
				m_FontSizeTankNameM.push_back(tempText.GetHeight());
			}

			// If this text is tank value locator
			else if ((tolower(strTemp[1]) == 't') && (tolower(strTemp[2]) == 'v')) {
				// Store the locator text for future reference
				m_strTankValuesM.push_back(string(strTemp));
				PointF point((float)m_dxfDrawing.Entity().MText()[i].GetPosition().GetX(),
							 (float)m_dxfDrawing.Entity().MText()[i].GetPosition().GetY());

				// Store the coodinates
				m_posTankValuesM.push_back(point);
				m_TankValueColorM.push_back(TextColor);
				// Store font information
				m_FontTankValuesM.push_back(tempText.GetFont());
				m_FontSizeTankValuesM.push_back(tempText.GetHeight());
			}

			// If this text is Object value locator
			else if ((strTemp.GetLength() > 3) && (tolower(strTemp[1]) == 'c') && (tolower(strTemp[3]) == 'v')) {
				// Store the locator text for future reference
				m_strObjectValuesM.push_back(string(strTemp));
				PointF point((float)m_dxfDrawing.Entity().MText()[i].GetPosition().GetX(),
							 (float)m_dxfDrawing.Entity().MText()[i].GetPosition().GetY());
				// Store the coodinates
				m_posObjectValuesM.push_back(point);
				m_ObjectValuesColorM.push_back(TextColor);
				// Store font information
				m_FontObjectValuesM.push_back(tempText.GetFont());
				m_FontSizeObjectValuesM.push_back(tempText.GetHeight());
			}
		}
	} // for( int i=0; i<nCount; i++ )

}




// Function name   : CDxfLayout::DrawText
// Description     : Draws the tank names and values
// Return type     : void
// Argument        : void
// Constants defined in ANPRO1Const.h
#define TPC_LED_OFF			 				 0
#define TPC_LED_ON 			 				 1
#define TPC_LED_FLASH		 				 2

void CDxfLayout::DrawText(void) {
	using namespace Gdiplus;
	using namespace DxfRegionInfo;


	Graphics graphics(m_hMemDC, m_hMemDC_Scaled); // Attach graphics to bitmap buffer
												  // Initialize a dummy graphics for the tansformation of coordinates
	Graphics dummygfx(m_hMemDC);
	if (graphics.GetLastStatus() == Ok && dummygfx.GetLastStatus() == Ok) {
		Matrix matrix;
		TransformGraphics(dummygfx);
		dummygfx.GetTransform(&matrix);

		//graphics.ScaleTransform(ScaleX,ScaleY);
		graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);

		//StringFormat stringFormat;


		// Get the height of the font in pixels
		// So that the font can be drawn with bottom-left alignment
		CString strTemp;
		// Draw the tank names first
		for (int i = 0; i < (int)m_strTankName.size(); i++) {
			FontFamily    fontFamily(m_FontTankName[i].c_str());
			double        MaxFontScale = max(ScaleX, ScaleY);
			Gdiplus::Font font(&fontFamily, REAL(m_FontSizeTankName[i] * MaxFontScale + 0.5), FontStyleBold, UnitPixel);
			float         ascent       = fontFamily.GetCellAscent(FontStyleBold);
			float         ascentPixel  = font.GetSize() * ascent / fontFamily.GetEmHeight(FontStyleBold);
			int tmpTxtColor = m_TankNameColor[i];
			if (hasTextCol) {
				tmpTxtColor = TextCol;
			}
			SolidBrush    brush2(tmpTxtColor);
			//SolidBrush brush(Color::Yellow);

			PointF        point(m_posTankName[i].X, m_posTankName[i].Y);
			matrix.TransformPoints(&point);
			point = point - PointF(0, ascentPixel);
			strTemp = m_strTankName[i].c_str();

			BSTR str = strTemp.AllocSysString();
			graphics.DrawString(str, -1, &font, point, &brush2);
			SysFreeString(str);
		} // for( int i=0; i< (int)m_strTankName.size(); i++ )

		CPvcsTankData tankData;
		if (m_ptrTankMap == NULL) m_ptrTankMap = theShipData().m_DefaultTankMap;

		// Now draw the tank volumes
		for (int i = 0; i < (int)m_strTankValues.size(); i++) {
			FontFamily    fontFamily(m_FontTankValues[i].c_str());
			double        MaxFontScale = max(ScaleX, ScaleY);
			Gdiplus::Font font(&fontFamily, REAL(m_FontSizeTankValues[i] * MaxFontScale + 0.5), FontStyleBold, UnitPixel);
			float         ascent       = fontFamily.GetCellAscent(FontStyleBold);
			float         ascentPixel  = font.GetSize() * ascent / fontFamily.GetEmHeight(FontStyleBold);
			SolidBrush    brush2(m_TankValueColor[i]);

			PointF        point(m_posTankValues[i].X, m_posTankValues[i].Y);
			matrix.TransformPoints(&point);
			point = point - PointF(0, ascentPixel);
			//while( theShipData().m_bIsBusy );, , old
			//theShipData().m_bIsBusy = true;  old
			int  Index  = CDxfRegionInfo::GetIndex(m_strTankValues[i]);
			int  Index2 = CDxfRegionInfo::GetSubIndex(m_strTankValues[i]);
			BSTR str;
			switch (Index2) {
			default:
			case 0:
				str = theShipData().GetTank(Index, m_ptrTankMap).GetVolume().AllocSysString();
				break;
			case 1:
				str = theShipData().GetTank(Index, m_ptrTankMap).GetVolumePercent().AllocSysString();
				break;
			case 2:
				str = theShipData().GetTank(Index, m_ptrTankMap).GetUllage().AllocSysString();
				break;
			case 3:
				str = theShipData().GetTank(Index, m_ptrTankMap).GetWeight().AllocSysString();
				break;
			case 4:
				str = theShipData().GetTank(Index, m_ptrTankMap).GetLevel().AllocSysString();
				break;
			case 5:
				str = theShipData().GetTank(Index, m_ptrTankMap).GetTemperature().AllocSysString();
				break;
			case 6:
				str = theShipData().GetTank(Index, m_ptrTankMap).GetTankPressure().AllocSysString();
				break;
			case 7:
				str = theShipData().GetTank(Index, m_ptrTankMap).GetLoadRate().AllocSysString();
				break;
			case 8:
				str = theShipData().GetTank(Index, m_ptrTankMap).GetCargoType().AllocSysString();
				break;
			}
			//theShipData().m_bIsBusy = false;  old
			graphics.DrawString(str, -1, &font, point, &brush2);
			SysFreeString(str);
		} // for( int i=0; i< (int)m_strTankValues.size(); i++ )

		// Now draw the tank bar graphs
		for (int i = 0; i < (int)m_strTankBarGraphs.size(); i++) {
			//int Index  = CDxfRegionInfo::GetIndex(m_strTankBarGraphs[i]);
			//int tmpColor  = CDxfRegionInfo::GetSubIndex(m_strTankBarGraphs[i]);
			int Index    = m_TankBarIndex[i];
			int tmpColor = m_TankBarSubIndex[i];


			if (!tmpColor) {
				tmpColor = Color::Black;
			}
			//int Width  = m_rectBarGraphs[i].W * ScaleX;
			//int Height = CDxfRegionInfo::GetSubIndex2(m_strTankBarGraphs[i]) * ScaleY;
			//PointF point(m_posTankBarGraphs[i].X, m_posTankBarGraphs[i].Y);
			RectF  rectBar   = m_rectBarGraphs[i];
			//SizeF tmpSize(rectBar.Width,rectBar.Height);
			PointF tmpPoint1(rectBar.X, rectBar.Y);
			PointF tmpPoint2(rectBar.X + rectBar.Width, rectBar.Y + rectBar.Height);
			matrix.TransformPoints(&tmpPoint1);
			matrix.TransformPoints(&tmpPoint2);
			RectF        rectBarScaled(tmpPoint1.X, tmpPoint2.Y, tmpPoint2.X - tmpPoint1.X, tmpPoint1.Y - tmpPoint2.Y);
			float        Width         = rectBarScaled.Width;
			float        Height        = rectBarScaled.Height;
			CString      str           = theShipData().GetTank(Index, m_ptrTankMap).GetVolumePercent();
			const double VolPercent    = 100.0 - atof(str);
			const double BarGraphValue = Height / 100.0 * VolPercent + 0.0001;
			RectF        rectVol(REAL(tmpPoint1.X), REAL(tmpPoint2.Y + BarGraphValue), REAL(Width), REAL(Height - BarGraphValue));
			Pen          pen(m_TankBarGraphColor[i], 2.0);
			graphics.DrawRectangle(&pen, rectBarScaled);
			// paint background
			SolidBrush m_brushBackground(tmpColor);
			SolidBrush m_brushBar(m_TankBarGraphColor[i]);
			graphics.FillRectangle(&m_brushBackground, rectBarScaled);
			graphics.FillRectangle(&m_brushBar, rectVol);

		} // for( int i=0; i< (int)m_strTankValues.size(); i++ )

		// Now draw the tank alarms
		for (int i = 0; i < (int)m_strTankAlarms.size(); i++) {
			int           Index        = m_TankAlarmIndex[i];
			double        Width        = m_TankAlarmSubIndex[i] * ScaleX;
			double        Height       = m_TankAlarmSubIndex2[i] * ScaleY;
			FontFamily    fontFamily(m_FontTankAlarms[i].c_str());
			double        MaxFontScale = max(ScaleX, ScaleY);
			Gdiplus::Font font(&fontFamily, REAL(m_FontSizeTankAlarms[i] * MaxFontScale + 0.5), FontStyleBold, UnitPixel);
			float         ascent       = fontFamily.GetCellAscent(FontStyleBold);
			float         ascentPixel  = font.GetSize() * ascent / fontFamily.GetEmHeight(FontStyleBold);

			PointF        point(REAL(m_posTankAlarms[i].X + Width), REAL(m_posTankAlarms[i].Y + Height));
			string        tagStr       = "_Fv ";
			char          tmpBuf[80];
			tagStr += _itoa(Index, tmpBuf, 10);
			matrix.TransformPoints(&point);
			const int AlarmState    = theShipData().GetFreeAlarm(tagStr);
			RectF     rectCircle(REAL(point.X), REAL(point.Y), REAL(Width), REAL(Height));
			Pen       pen(m_TankAlarmColor[i], 2.0);
			//graphics.DrawEllipse(&pen, rectCircle);
			graphics.DrawRectangle(&pen, rectCircle);
			// paint background
			SolidBrush m_brushBackground(Color::Black);
			int        AlarmCol          = Color::Black;
			switch (AlarmState) {
			case TPC_LED_OFF:
				AlarmCol = Color::Green;
				break;
			case TPC_LED_FLASH:
				if (m_TankAlarmColInverted[i]) {
					AlarmCol = 0xff9a2b46; //Color::MistyRose;
				} else {
					AlarmCol = Color::Red;
				}
				m_TankAlarmColInverted[i] = !m_TankAlarmColInverted[i];
				break;
			case TPC_LED_ON:
				AlarmCol = Color::Red;
				break;
			}
			SolidBrush m_brushBar(AlarmCol);
			//graphics.FillEllipse(&m_brushBar,rectCircle);
			graphics.FillRectangle(&m_brushBar, rectCircle);

		} // for( int i=0; i< (int)m_strTankValues.size(); i++ )


		int FontN = m_FontObjectValues.size();
		// Now draw the Object values
		for (int i = 0; i < (int)m_strObjectValues.size(); i++) {
			//FontFamily    fontFamily(L"Tahoma");
			FontFamily    fontFamily(m_FontObjectValues[i].c_str());
			CAcDbText     tempText   = m_dxfDrawing.Entity().Text()[i];

			Gdiplus::Font font(&fontFamily, REAL(m_FontSizeObjectValues[i] * m_dScale  * 1.4), FontStyleRegular, UnitPixel);
			float         ascent       = fontFamily.GetCellAscent(FontStyleBold);
			float         ascentPixel  = font.GetSize() * ascent / fontFamily.GetEmHeight(FontStyleRegular);

			SolidBrush    brush2(m_ObjectValuesColor[i]);
			int           iIndex       = CDxfRegionInfo::GetIndex(m_strObjectValues[i]);
			int           iSubIndex    = CDxfRegionInfo::GetSubIndex(m_strObjectValues[i]);
			int           iSubIndex2   = CDxfRegionInfo::GetSubIndex2(m_strObjectValues[i]);

			Info_it       it           = m_infoObject.find(CPvcsControlObjectInfo(iIndex, iSubIndex, iSubIndex2));

			if (it != m_infoObject.end()) {
				strTemp = theController().GetController(*it).GetValueString(*it, iSubIndex2);
				PointF point(m_posObjectValues[i].X, m_posObjectValues[i].Y);
				matrix.TransformPoints(&point);
				point = point - PointF(0, ascentPixel);
				BSTR str = strTemp.AllocSysString();
				graphics.DrawString(str, -1, &font, point, &brush2);
				SysFreeString(str);
			} // if( it != m_infoObject.end() )

		} // for( int i=0; i< (int)m_strObjectValues.size(); i++ )

		//Code for showing Screen Title and Command Mode in the Ship Layout window
		if (m_bIsShowScreenStatusText) {
			SolidBrush    brush(Color::Black);
			FontFamily    fontFamily(L"Tahoma");

			Gdiplus::Font Screenfont(&fontFamily, 12, FontStyleRegular, UnitPixel);
			PointF        ScreenPoint(5, 10);
			CString       strScreenText = CPvcsScreenInfo::m_vecScreenInfo[m_iScreenNumber - 1]->m_strScreenTitle;
			if (CPvcsScreenInfo::m_vecScreenInfo[m_iScreenNumber - 1]->m_bCommandStatus) strScreenText += "\nCommand Mode";
			else strScreenText += "\nDisplay Mode";

			BSTR bsScreenText = strScreenText.AllocSysString();
			graphics.DrawString(bsScreenText, -1, &Screenfont, ScreenPoint, &brush);
			SysFreeString(bsScreenText);
		}
		//Code for showing Screen Title and Command Mode in the Ship Layout window

	} // if( graphics.GetLastStatus() == Ok )

}


// Function name   : CDxfLayout::DrawMText
// Description     : Draws the Multiline text entities in the drawing
// Return type     : void
// Argument        : void

void CDxfLayout::DrawMText(void) {
	using namespace Gdiplus;

	// Initialize graphics for drawing
	Graphics graphics(m_hMemDC);

	// Initialize a dummy graphics for the tansformation of coordinates
	Graphics dummygfx(m_hMemDC);

	if (graphics.GetLastStatus() == Ok && dummygfx.GetLastStatus() == Ok) {
		Matrix matrix;
		TransformGraphics(dummygfx);
		dummygfx.GetTransform(&matrix);

		graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);


		//SolidBrush brush(Color::White);

		const int nCount = m_dxfDrawing.Entity().MText().GetCount();

		// Now draw the multiline text
		for (int i = 0; i < nCount; i++) {
			CAcDbText     tempText   = m_dxfDrawing.Entity().MText()[i];
			unsigned      TextColor  = TextCol;
			const wstring FntStr     = tempText.GetFont();
			FontFamily    fontFamily(FntStr.c_str());
			if (!hasTextCol) {
				TextColor = m_dxfDrawing.Table().Layer().GetColor(tempText.GetLayer());
			}
			SolidBrush    brush(TextColor);

			FontStyle     fStyle     = FontStyleRegular; //FontStyleUnderline

			CString       strTemp    = tempText.GetValue().c_str();
			CStringW      strFormat;
			strTemp.Remove('{');
			strTemp.Remove('}');


			if (strTemp[0] == '\\') {
				switch (strTemp[1]) {
				case 'L':
					fStyle = FontStyleUnderline;
					strTemp = strTemp.Right(strTemp.GetLength() - 2);
					break;
				case 'O':
					fStyle = FontStyleUnderline;
					strTemp = strTemp.Right(strTemp.GetLength() - 2);
					break;
				case 'C':
					{
						Color FntCol;
						switch (strTemp[2]) {
						case '1':
							FntCol = (unsigned)Color::Red;
							break;
						case '2':
							FntCol = (unsigned)Color::Yellow;
							break;
						case '3':
							FntCol = (unsigned)Color::Green;
							break;
						case '4':
							FntCol = (unsigned)Color::Cyan;
							break;
						case '5':
							FntCol = (unsigned)Color::Blue;
							break;
						case '6':
							FntCol = (unsigned)Color::Magenta;
							break;
						case '7':
						default :
							// Assume that the default background is white
							FntCol = (unsigned)Color::Black;
							break;
						}
						if (hasTextCol) {
							brush.SetColor(TextCol);
						} else {
							brush.SetColor(FntCol);
						}
					}

					strTemp = strTemp.Mid(4);
					break;
				}
			}

			StringFormat  stringFormat(StringFormatFlagsNoClip); //StringFormatFlagsDirectionVertical

			int           LineNumbers  = strTemp.Replace("\\P", "\n");

			Gdiplus::Font font(&fontFamily, (float)((tempText.GetHeight() * m_dScale) * 1.4), fStyle, UnitPixel);
			PointF        ulCorner     = PointF(REAL(tempText.GetPosition().GetX()), REAL(tempText.GetPosition().GetY()));
			matrix.TransformPoints(&ulCorner, 1);
			// Measure string.

			bool Special = false;
			// If this text is tank name locator
			if ((strTemp.GetLength() > 2) && (strTemp[0] == '_')) {
				if ((tolower(strTemp[1]) == 't') && (tolower(strTemp[2]) == 'n')) {
					Special = true;
				}

				// If this text is tank value locator
				if ((tolower(strTemp[1]) == 't') && (tolower(strTemp[2]) == 'v')) {
					Special = true;
				}

				// If this text is Object value locator
				if ((strTemp.GetLength() > 3) && (tolower(strTemp[1]) == 'c') && (tolower(strTemp[3]) == 'v')) {
					string LocStr      = CStringA(strTemp);
					int    iIndex      = CDxfRegionInfo::GetIndex(LocStr);
					int    iSubIndex   = CDxfRegionInfo::GetSubIndex(LocStr);
					int    iSubIndex2  = CDxfRegionInfo::GetSubIndex2(LocStr);
					int    FormatStart = strTemp.Find("#");
					if (FormatStart != -1) {
						strFormat = strTemp.Mid(FormatStart);
						Special = true;
					}
					Info_it it = m_infoObject.find(CPvcsControlObjectInfo(iIndex, iSubIndex, iSubIndex2));

					if (it != m_infoObject.end()) {
						strTemp = "RR" + theController().GetController(*it).GetValueString(*it, iSubIndex2);
					} else { // if( it != m_infoObject.end() )
						strTemp = "RR";
					}
				}
			}
			if (Special) {} else {}
			bool DrawRect = false;
			if (strTemp[0] == 'R' && strTemp[1] == 'R') {
				DrawRect = true;
				strTemp = strTemp.Mid(2);
			}
			CStringW tmpStr(strTemp);

			BSTR     str       = strTemp.AllocSysString();

			RectF    tRect;
			RectF    rectF;
			int      AttachPnt = tempText.GetAttachPnt();
			if (tempText.GetYAngle() == 1.0) {
				stringFormat.SetFormatFlags(StringFormatFlagsDirectionVertical | StringFormatFlagsDirectionRightToLeft);

				if (Special) {
					graphics.MeasureString(strFormat.GetBuffer(), strFormat.GetLength(), &font, ulCorner, &stringFormat, &tRect);
				} else {
					graphics.MeasureString(tmpStr.GetBuffer(), tmpStr.GetLength(), &font, ulCorner, &stringFormat, &tRect);
				}

				switch (AttachPnt) {
				case 1: // Top left
					{
						RectF tmpRectF(ulCorner.X - tRect.Width / 2, ulCorner.Y - tRect.Height, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 2: // Top center
					{
						RectF tmpRectF(ulCorner.X, ulCorner.Y - tRect.Height / 2, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 3: // Top right
					{
						RectF tmpRectF(ulCorner.X, ulCorner.Y - tRect.Height, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 4: // Middle left
					{
						RectF tmpRectF(ulCorner.X, ulCorner.Y - tRect.Height, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 5: // Middle center
					{
						RectF tmpRectF(ulCorner.X - tRect.Width / 2, ulCorner.Y + tRect.Height / 2 - tRect.Height, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 6: // Middle right
					{
						RectF tmpRectF(ulCorner.X, ulCorner.Y - tRect.Height, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 7: // Bottom left
					{
						RectF tmpRectF(ulCorner.X, ulCorner.Y - tRect.Height, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 8: // Bottom center
					{
						RectF tmpRectF(ulCorner.X, ulCorner.Y - tRect.Height, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 9: // Bottom right
					{
						RectF tmpRectF(ulCorner.X, ulCorner.Y - tRect.Height, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				}
				/*
				CPaintDC dc(this);
				CRect rc;
				GetClientRect(&rc);

				double w = rc.Width()-rectF.Y;
				double h = rc.Height()-rectF.X;
				graphics.TranslateTransform(w, h);
				graphics.RotateTransform(180);
				RectF tmpRectF(0, 0, rectF.Width, rectF.Height);
				graphics.DrawString(str, -1, &font, tmpRectF, &stringFormat, &brush);
				graphics.ResetTransform();
				*/
				graphics.DrawString(str, -1, &font, rectF, &stringFormat, &brush);
			} else {
				if (Special) {
					graphics.MeasureString(strFormat.GetBuffer(), strFormat.GetLength(), &font, ulCorner, &stringFormat, &tRect);
				} else {
					graphics.MeasureString(tmpStr.GetBuffer(), tmpStr.GetLength(), &font, ulCorner, &stringFormat, &tRect);
				}
				//tRect.Width /= 2;
				switch (AttachPnt) {
				case 1: // Top left
					{
						RectF tmpRectF(ulCorner.X/*+tRect.Width/4*/, ulCorner.Y/*+tRect.Height/2*/, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 2: // Top center
					{
						RectF tmpRectF(ulCorner.X - tRect.Width / 2, ulCorner.Y /*- tRect.Height / 6*/, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 3: // Top right
					{
						RectF tmpRectF(ulCorner.X + tRect.Width / 4, ulCorner.Y, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 4: // Middle left
					{
						RectF tmpRectF(ulCorner.X/* + tRect.Width / 4*/, ulCorner.Y - tRect.Height / 2, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 5: // Middle center
					{
						RectF tmpRectF(ulCorner.X + tRect.Width / 4, ulCorner.Y - tRect.Height / 2, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 6: // Middle right
					{
						RectF tmpRectF(ulCorner.X + tRect.Width / 4, ulCorner.Y - tRect.Height / 2, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 7: // Bottom left
					{
						RectF tmpRectF(ulCorner.X/* + tRect.Width / 4*/, ulCorner.Y, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 8: // Bottom center
					{
						RectF tmpRectF(ulCorner.X + tRect.Width / 4, ulCorner.Y, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				case 9: // Bottom right
					{
						RectF tmpRectF(ulCorner.X + tRect.Width / 4, ulCorner.Y, tRect.Width, tRect.Height);
						rectF = tmpRectF;
					}
					break;
				}
				graphics.DrawString(str, -1, &font, rectF, &stringFormat, &brush);
			}
			SysFreeString(str);
			if (DrawRect) {
				Pen pen(Color::Black, 2.0);
				graphics.DrawRectangle(&pen, rectF);
			}
		} // for( int i=0; i< nCount; i++ )


	} // if( graphics.GetLastStatus() == Ok && dummygfx.GetLastStatus() == Ok )2

}

// Function name   : CDxfLayout::ProcessClickOnObject
// Description     : Take action upon click on an object in the tank window
// Return type     : bool
// Argument        : const int& param_iIndex
// Argument        : CPoint param_point

bool CDxfLayout::ProcessClickOnObject(const int &param_iIndex, CPoint param_point, int ScreenNumber) {
	// Ensure this is tank window
	if (!m_bIsShipLayout) {
		//while( theController().m_hWnd );

		int     iIndex = m_ptrRegionInfo[param_iIndex].GetIndex(), iSubIndex = m_ptrRegionInfo[param_iIndex].GetSubIndex(), iSubIndex2 = m_ptrRegionInfo[param_iIndex].GetSubIndex2();

		Info_it it     = m_infoObject.find(CPvcsControlObjectInfo(iIndex, iSubIndex, iSubIndex2));

		//set screen number to which screen it belongs
		it->SetScreenNumber(ScreenNumber);

		// Display control window corresponding to this object
		if (it != m_infoObject.end()) theController().Display(*it, param_point, this);
		else theController().Display(CPvcsControlObjectInfo(), param_point, this);
	}

	return true;
}


// Function name   : CDxfLayout::ProcessClickOnTank
// Description     : Take action upon click on tank in the ship layout
// Return type     : void
// Argument        : const int& param_iIndex

void CDxfLayout::ProcessClickOnTank(const int &param_iIndex) {
	// Ensure this is ship layout
	if (m_bIsShipLayout) {
		// Get the main splitter window
		// The hierarchy is... ( Child > Parent )
		// CDxfLayout > CPvcsShipView > CPvcsSplitterLowerWnd > CPvcsSplitterWnd
		CPvcsSplitterWnd *tempSplitterWnd =
			dynamic_cast<CPvcsSplitterWnd *>(GetParent()->GetParent()->GetParent());

		if (tempSplitterWnd) {
			// Now get the tank View pane ( the upper pane )
			CPvcsTankView *tempTankView =
				dynamic_cast<CPvcsTankView *>(tempSplitterWnd->GetPane(0, 0));

			if (tempTankView) {
				// Now add add a tank to this pane
				tempTankView->AddTank(m_ptrRegionInfo[param_iIndex].GetIndex());
			} // if( tempTankView )

		} // if( tempSplitterWnd )

	} // if( m_bIsShipLayout )
}


// Function name   : CDxfLayout::Update
// Description     : Updates the color/text of the layout correspond to current situation
// Return type     : void
// Argument        : void

void CDxfLayout::Update(CPvcsShipData::TankMap *pTankMap, int ScreenNumber, bool ShowScreenText) {
	if (m_bSuccess) {
		using namespace Gdiplus;
		//int x_offset = GetScrollPos(SB_HORZ) ;
		//int y_offset = GetScrollPos(SB_VERT) ;
		//static int xOff;


		// offset the window by the scroll amount to get correct drawing
		//rect.OffsetRect(x_offset, y_offset);
		//SetWindowOrg(CPoint(x_offset, y_offset)) ;
		//int nRes = ScrollWindowEx (xOff++,y_offset, NULL,NULL, NULL, NULL, SW_INVALIDATE);


		m_bIsShowScreenStatusText = ShowScreenText;
		if (m_bIsShowScreenStatusText) m_iScreenNumber = ScreenNumber;

		m_ptrTankMap = pTankMap;
		if (m_ptrTankMap == NULL) m_ptrTankMap = theShipData().m_DefaultTankMap;

		//set tankmap pointer;

		const int     nCount    = m_dxfDrawing.Entity().Polyline().GetCount();
		//COLORREF      colorTank;

		CPvcsTankData tankData;
/*
		// Update all the polylines
		for (int i = 0; i < nCount; i++) {
			// If this region is tank region
			if (m_ptrRegionInfo[i].GetType() == DxfRegionInfo::Tank) {
				int     iTankID       = m_ptrRegionInfo[i].GetIndex();
				// Get the tank data from Surveyor
				//if( theShipData().LoadTankData( , tankData ) )
				{
					// Get the color of this tank region
					CString color_strtemp;
					if (SplitScreens >= 2) {
						int iAlarm = atoi(theShipData().GetTank(iTankID, m_ptrTankMap).GetAlarmStatus());
						// If there is no Alarm
						if (iAlarm == 0) {
							color_strtemp = theShipData().GetTank(iTankID, m_ptrTankMap).GetCargoColor(); // Get the cargo color
						}  else
						// before JSD strtemp = "0x0000ff"; // Tank drawn in Red color
						{
							//Start JSD
							if ((iAlarm != 0) && (m_bAlmFirst == 0)) {
								color_strtemp = "0x0000ff"; // Tank drawn in Red color
							} else color_strtemp = "0x00ff00"; // Tank drawn in Red color
															   //End JSD
						}

					}

					// Ensure the color string is not empty
					if (!color_strtemp.IsEmpty()) {
						// Get the color stored in Hex format
						sscanf_s(color_strtemp, "%x", &colorTank);

						// Now set the color
						m_ptrRegionInfo[i].SetBrush(Color(GetRValue(colorTank), GetGValue(colorTank), GetBValue(colorTank)));
					} // if( strtemp != "" )
					else { // No color information
						m_ptrRegionInfo[i].SetBrush(ObjectCol);
					}

				} // if( theTankData().LoadTankData( m_ptrRegionInfo[i].GetIndex() ) )
				  //else // Failed to load tank data
				//  m_ptrRegionInfo[i].SetBrush( Color::White );
			} // for(i=0; i<nCount; i++)
		} // if( m_bSuccess )
		*/
	} //if (m_bSuccess )

	Draw();
}


// Function name   : CDxfLayout::ActivateTank
// Description     : Commands the tank view pane to show tank window
//                   and sets the color of corresponding pipeline
// Return type     : void
// Argument        : const int& param_iTankID

void CDxfLayout::ActivateTank(const int &param_iTankID) {
	using namespace DxfRegionInfo;
	using namespace Gdiplus;

	int nCount = m_dxfDrawing.Entity().Polyline().GetCount();

	for (int i = 0; i < nCount; i++) {
		// First set all the tank region border thickness to One
		//m_ptrRegionInfo[i].SetPen(Color::Black, 1.0f/(float)m_dScale );
		// First set all the tank region border thickness to default
		CAcDbPolyLine *tempPolyline = (CAcDbPolyLine *)&m_dxfDrawing.Entity().Polyline()[m_ptriMap[i]];
		const double  PWidth        = tempPolyline->GetPenSize();
		int           LineColor     = m_dxfDrawing.Table().Layer().GetLayer(tempPolyline->GetLayerName());

		// If this tank has been clicked
		if (m_ptrRegionInfo[i].GetType() == Tank) {
			if (m_ptrRegionInfo[i].GetIndex() == param_iTankID) {
				// Set the border thickness to Four
				m_ptrRegionInfo[i].m_bIsBold = true;
				m_ptrRegionInfo[i].SetPen(Color(LineColor), (float)(4.0 * PWidth / m_dScale), false);

				// Get the main splitter window
				// The hierarchy is... ( Child > Parent )
				// CDxfLayout > CPvcsShipView > CPvcsSplitterLowerWnd > CPvcsSplitterWnd
				CPvcsSplitterWnd *tempSplitterWnd = dynamic_cast<CPvcsSplitterWnd *>(GetParent()->GetParent()->GetParent());

				if (tempSplitterWnd) {
					// Now get the tank View pane ( the upper pane )
					CPvcsTankView *tempTankView = dynamic_cast<CPvcsTankView *>(tempSplitterWnd->GetPane(0, 0));

					if (tempTankView) {
						// Display this tank window
						tempTankView->ShowTank(param_iTankID);
					}
				} // if( tempSplitterWnd )
				  // Now set the color for the pipelines
				for (int j = 0; j < nCount; j++) {
					// If this region is pipeline
					if (m_ptrRegionInfo[j].GetType() == Pipeline) {
						// If this pipeline belongs to this tank
						// EHSMark Changed colours
						if (m_ptrRegionInfo[j].GetIndex() == m_ptrRegionInfo[i].GetIndex()) {
							m_ptrRegionInfo[j].SetBrush((unsigned)Color::DodgerBlue);
							m_ptrRegionInfo[j].SetPen((unsigned)Color::MidnightBlue, float(PWidth / m_dScale));
						} else // All other pipelines should be drawn in White
							m_ptrRegionInfo[j].SetBrush((unsigned)Color::Black); //EHSMark
					}
				} // for(int j=0; j<nCount; j++)

			} else { // if(  m_ptrRegionInfo[i].GetIndex() == param_iTankID )
					 // EHSMark
				// Set all the tank region border thickness to PWidth
				m_ptrRegionInfo[i].SetPen(Color(LineColor), float(PWidth / m_dScale));
				m_ptrRegionInfo[i].m_bIsBold = false;
			}
		} else { // if( m_ptrRegionInfo[i].GetType() == Tank )
				 // Set all the tank region border thickness to PWidth
			m_ptrRegionInfo[i].SetPen(Color(LineColor), float(PWidth / m_dScale));
			m_ptrRegionInfo[i].m_bIsBold = false;

		}
	} // for(int i=0; i<nCount; i++)

	// Since some of the colors may have been changed, so redraw the window
	RedrawWindow();
	UpdateWindow();
}


// Function name   : CDxfLayout::AddPath
// Description     : Adds a line/curve to a GraphicsPath object
// Return type     : void
// Argument        : Gdiplus::GraphicsPath& param_path
// Argument        : const CDxfPoint& param_ptFirst
// Argument        : const CDxfPoint& param_ptSecond

void CDxfLayout::AddPath(Gdiplus::GraphicsPath &param_path, const CDxfPoint &param_ptFirst, const CDxfPoint &param_ptSecond) {
	using namespace Gdiplus;
	const double PI       = 3.1415926538973284;

	PointF       ptFirst(static_cast<float>(param_ptFirst.GetX()),
						 static_cast<float>(param_ptFirst.GetY()));
	PointF       ptSecond(static_cast<float>(param_ptSecond.GetX()),
						  static_cast<float>(param_ptSecond.GetY()));

	// This will add a line or curve to the region depending upon weather
	// the first vetex containes a bulge or not


	if (param_ptFirst.GetBulge() == 0.0)
		// There is no bulge, so add a line between two points
		param_path.AddLine(ptFirst, ptSecond);
	else { // There is a bulge

#define LWPOLYLINE_BULGE

#ifdef LWPOLYLINE_BULGE
		// Now calculate the arc depending upon the bulge
		// Accoding to DXF specs, bulge is defined thus:
		// "The bulge is the tangent of one fourth the
		// included angle for an arc segment, made negative if the arc goes
		// clockwise from the start point to the endpoint. A bulge of 0 indicates a
		// straight segment, and a bulge of 1 is a semicircle"

		// Between the two poins, the bulge is stored in the first point
		double bulge   = param_ptFirst.GetBulge();
		double x1      = param_ptFirst.GetX();
		double y1      = param_ptFirst.GetY();
		double x2      = param_ptSecond.GetX();
		double y2      = param_ptSecond.GetY();

		// Now do the mathematical calculations
		double cot     = (0.5 * ((1.0 / bulge) - bulge));
		double x       = ((x1 + x2 - ((y2 - y1) * cot)) / 2.0);
		double y       = ((y1 + y2 + ((x2 - x1) * cot)) / 2.0);

		double r       = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));

		double theta1  = atan2((y1 - y), (x1 - x)) * (180.0f / PI);
		double theta2  = atan2((y2 - y), (x2 - x)) * (180.0f / PI);

		double theta11;
		double theta22;

		if (theta1 >= 0.0 && theta1 < 180.0) // I & II Quadrant
			theta11 = theta1;
		else theta11 = 360.0f + theta1;  // III & IV Quadrant

		if (theta2 >= 0.0 && theta2 < 180.0) // I & II Quadrant
			theta22 = theta2;
		else theta22 = 360.0f + theta2;  // III & IV Quadrant

		// Calculate the sweep angle
		double sweep;

		if ((param_ptFirst.GetBulge() > 0.0) && (theta22 > theta11)) sweep = (theta22 - theta11);
		else if ((param_ptFirst.GetBulge() > 0.0) && (theta22 < theta11)) sweep = 360.0f - (theta11 - theta22);
		else if ((param_ptFirst.GetBulge() < 0.0) && (theta11 > theta22)) sweep = -(theta11 - theta22);
		else sweep = -(360 - (theta22 - theta11));

		// Now add the arc
		param_path.AddArc(REAL(x - r),
						  REAL(y - r),
						  REAL(2.0 * r),
						  REAL(2.0 * r),
						  REAL(theta1),
						  REAL(sweep));
#else
		param_path.AddLine( ptFirst, ptSecond );
#endif // #define LWPOLYLINE_BULGE

	}
}

void CDxfLayout::OnMouseMove(UINT nFlags, CPoint ScrolPoint) {

	if (WaitForSingleObject(CPvcsScreenFrame::m_hMutex, 3000) == WAIT_OBJECT_0) {
		//CSingleLock singlelock(&g_CS_Update);
		//singlelock.Lock();
		//if (singlelock.IsLocked()) {
		using namespace DxfRegionInfo;
		using namespace Gdiplus;
		CRect rc;
		GetClientRect(&rc);
		if (nFlags == MK_MBUTTON || nFlags == MK_SHIFT || nFlags == MK_RBUTTON) {
			UpdateDelay = 2;
			if (!(!m_PrevX || !m_PrevY)) {
				int xCurScrollPos = GetScrollPos(SB_HORZ);
				int yCurScrollPos = GetScrollPos(SB_VERT);
				int deltaX        = int((m_PrevX - ScrolPoint.x) / 4 + xCurScrollPos);
				int deltaY        = int((m_PrevY - ScrolPoint.y) / 4 + yCurScrollPos);
				if (deltaX) {
					if (deltaX > 100) {
						deltaX = 100;
					}
					SetScrollPos(SB_HORZ, deltaX, true);
				}
				if (deltaY) {
					if (deltaY > 100) {
						deltaY = 100;
					}
					SetScrollPos(SB_VERT, deltaY, true);
				}
				RedrawWindow();
			}
			m_PrevX = ScrolPoint.x;
			m_PrevY = ScrolPoint.y;
			// Sleep(10);
		} else if (nFlags == MK_MBUTTON || nFlags == MK_SHIFT || nFlags == MK_RBUTTON) {} else {
			m_PrevX = 0;
			m_PrevY = 0;
			SetActive();
			// Ensure this is ship layout
			// If mouse is here, close the Control Window
			if (m_bIsShipLayout && theController().m_hWnd && (PVCSWarningMessage::DialgVisible == false)) {
				//theController().DestroyWindow();

				::SendMessage(theController().m_hWnd, WM_CLOSE, 0, 0);
			}


			// The code below calls the parent tank dialog class to show the tool-tip for
			// the various control objects

			// Make sure we are showing tool tips in tank window
			if (!m_bIsShipLayout) {
				int      nCount    = m_dxfDrawing.Entity().Polyline().GetCount();
				int      i         = 0;

				// Flag to check weather to show toll-tip
				bool     bFoundRgn = false;

				// Transform the drawing to the screen coordiantes
				Graphics graphics(m_hMemDC);

				if (graphics.GetLastStatus() == Ok) {
					Matrix matrix;
					TransformGraphics(graphics);
					graphics.GetTransform(&matrix);

					for (i = 0; i < nCount && !bFoundRgn; i++) {
						// If the mouse was upon a Control object in tank window
						if (!bFoundRgn && m_ptrRegionInfo[i].GetType() == ControlObject) {
							Region reg(&m_ptrPath[i]);
							reg.Transform(&matrix);

							Rect rect;
							reg.GetBounds(&rect, &graphics);

							// If this control object region is the one which has been clicked upon
							if (rect.Contains(Point(ScrolPoint.x, ScrolPoint.y))) bFoundRgn = true;

						} // if( !bFoundRgn && m_ptrRegionInfo[i].GetType() == ControlObject )
					} // for(i=0; i<nCount; i++)
				} // if( graphics.GetLastStatus() == Ok )

				// Stores the tool tip text
				CString strTipText;

				// Decrement i for proper indexing
				i--;

				// If mouse was upon a control object

				if (bFoundRgn) {
					int        iIndex          = m_ptrRegionInfo[i].GetIndex(), iSubIndex = m_ptrRegionInfo[i].GetSubIndex(), iSubIndex2 = m_ptrRegionInfo[i].GetSubIndex2();
					Info_it    it              = m_infoObject.find(CPvcsControlObjectInfo(iIndex, iSubIndex, iSubIndex2));

					//get active window
					CPvcsFrame *ptrScreenFrame = (CPvcsFrame *)CWnd::GetActiveWindow();
					if (ptrScreenFrame != NULL) {
						CString strWindowText = "";
						ptrScreenFrame->GetWindowText(strWindowText);
						strWindowText.MakeLower();
						//if having 'mode' text for more conformity, if not found, then some other window is active
						if (strWindowText.Find("mode") != -1) {
							//if having command then show appropiate tooltip, otherwise show not in command tooltip
							if (CPvcsScreenInfo::m_vecScreenInfo[ptrScreenFrame->ScreenNumber - 1]->m_bCommandStatus) {
								if (it != m_infoObject.end()) strTipText = (*it).GetToolTip();
								else strTipText.Format("No Info");
							} else strTipText.Format("This Screen is in Display Mode");
						}
					} //if(ptrScreenFrame != NULL)
				}

				// Get the parent tank dialog
				CPvcsTankDlg *tempDlg = dynamic_cast<CPvcsTankDlg *>(GetParent());

				// Now tell the parent to show the tooltip
				// If strTipText is blank, the tool-tip will not be displayed
				if (tempDlg) tempDlg->ShowToolTip(strTipText);

			} // if( !m_bIsShipLayout )
		}
		//singlelock.Unlock();
		ReleaseMutex(CPvcsScreenFrame::m_hMutex);
	}
	CWnd::OnMouseMove(nFlags, ScrolPoint);

}

void CDxfLayout::EnableDraw(const bool &param_bEnable) {
	m_bDraw = param_bEnable;
}

void CDxfLayout::DrawFreeValues(void) {
	using namespace Gdiplus;

	// Initialize graphics for drawing
	Graphics  graphics(m_hMemDC);

	// Initialize a dummy graphics for the tansformation of coordinates
	Graphics  dummygfx(m_hMemDC);
	const int nCount   = m_dxfDrawing.Entity().Text().GetCount();

	if (graphics.GetLastStatus() == Ok && dummygfx.GetLastStatus() == Ok) {
		Matrix matrix;
		TransformGraphics(dummygfx);
		dummygfx.GetTransform(&matrix);

		graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);


		//FontFamily    fontFamily(L"Tahoma");
		//double        MaxFontScale = max(ScaleX, ScaleY);
		//Gdiplus::Font font(&fontFamily, REAL(11.0 * MaxFontScale + 0.5), FontStyleRegular, UnitPixel);
		StringFormat  stringFormat;

		//float         ascent       = fontFamily.GetCellAscent(FontStyleRegular);
		//float         ascentPixel  = font.GetSize() * ascent / fontFamily.GetEmHeight(FontStyleRegular);

 
		// Now draw the free values
		for (int i = 0; i < nCount; i++) {
			CAcDbText  tempText  = m_dxfDrawing.Entity().Text()[i];
			unsigned   TextColor = TextCol;
			if (!hasTextCol) {
				TextColor = m_dxfDrawing.Table().Layer().GetColor(tempText.GetLayer());
			}
			//TextColor = 0xffffff;
			SolidBrush brush(TextColor);
			//tempText = m_dxfDrawing.Entity().Text()[i];

			if (tempText.GetValue().size() > 2 && tempText.GetValue().at(0) == '_'&& tolower(tempText.GetValue().at(1)) == 'f') {
				const wstring FntStr     = tempText.GetFont();
				FontFamily    fontFamily(FntStr.c_str());
                double        MaxFontScale = max(ScaleX, ScaleY);
				int			  FontHeight = tempText.GetHeight();	

				Gdiplus::Font font(&fontFamily, (float)((tempText.GetHeight() * m_dScale) * 1.4), FontStyleRegular, UnitPixel);
                //Gdiplus::Font font(&fontFamily, REAL(FontHeight * MaxFontScale + 0.5), FontStyleRegular, UnitPixel);
                float         ascent       = fontFamily.GetCellAscent(FontStyleRegular);
                float         ascentPixel  = font.GetSize() * ascent / fontFamily.GetEmHeight(FontStyleRegular);

				PointF pointF = PointF((float)tempText.GetPosition().GetX(), (float)tempText.GetPosition().GetY());
				matrix.TransformPoints(&pointF);

				//pointF = pointF - PointF(0, ascentPixel);
				CString tmpstr = theShipData().GetFreeValue(tempText.GetValue()).c_str();
				BSTR    str    = tmpstr.AllocSysString();
				RectF strRect;
				StringFormat stringFormat(StringFormatFlagsNoClip); //StringFormatFlagsDirectionVertical
				graphics.MeasureString(str, tmpstr.GetLength(), &font, pointF, &stringFormat, &strRect);

				//graphics.DrawString(str, -1, &font, pointF, &stringFormat, &brush);
				graphics.DrawString(str, -1, &font, strRect, &stringFormat, &brush);
				SysFreeString(str);
			}
		} // for( int i=0; i< nCount; i++ )

	} // if( graphics.GetLastStatus() == Ok && dummygfx.GetLastStatus() == Ok )

}

int CDxfLayout::GetControlScreenNumber(int pIndex, int pSubIndex, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	//set screen number to which screen it belongs
	return it->GetScreenNumber();
}

CString CDxfLayout::GetObjectName(int pIndex, int pSubIndex, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	return it->GetName();
}

void CDxfLayout::SetValueToBeSet(int pIndex, int pSubIndex, CString pValuetoSet, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	it->SetValueToBeSet(pValuetoSet);
	m_bIsFindControlObjectInfo = true;
	return;
}

bool CDxfLayout::GetValueToBeSet(int pIndex, int pSubIndex, CString &pstrValue, int pSubIndex2) {
	bool    bResult = false;

	Info_it it      = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	pstrValue = it->GetValueToBeSet();
	m_bIsFindControlObjectInfo = false;
	bResult = true;


	return bResult;
}

//Get Control Object
void CDxfLayout::GetControlObject(int pIndex, int pSubIndex, CPvcsControlObjectInfo &pPvcsCOntrolObject, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	pPvcsCOntrolObject = *it;
	//theController().GetController(*it).OnButton(*it,1,true);
	return;
}

bool CDxfLayout::GetThreadRunningState(int pIndex, int pSubIndex, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	return it->GetThreadRunningState();
}

bool CDxfLayout::GetThreadExitState(int pIndex, int pSubIndex, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	return it->GetThreadExitState();
}

bool CDxfLayout::GetThreadExitedState(int pIndex, int pSubIndex, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	return it->GetThreadExitedState();
}

bool CDxfLayout::GetThreadBusyState(int pIndex, int pSubIndex, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	return it->GetThreadBusyState();
}

void CDxfLayout::SetThreadRunningState(int pIndex, int pSubIndex, bool pState, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	it->SetThreadRunningState(pState);
	return;
}

void CDxfLayout::SetThreadExitState(int pIndex, int pSubIndex, bool pState, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	it->SetThreadExitState(pState);
	return;
}

void CDxfLayout::SetThreadExitedState(int pIndex, int pSubIndex, bool pState, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	it->SetThreadExitedState(pState);
	return;
}

void CDxfLayout::SetThreadBusyState(int pIndex, int pSubIndex, bool pState, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	it->SetThreadBusyState(pState);
	return;
}

bool CDxfLayout::GetTimeoutState(int pIndex, int pSubIndex, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	return it->GetTimeOutState();
}

void CDxfLayout::SetTimeoutState(int pIndex, int pSubIndex, bool pState, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	return it->SetTimeOutState(pState);
}

void CDxfLayout::SetControlOperationState(int pIndex, int pSubIndex, bool bState, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	it->SetControlOperationState(bState);
	return;
}

bool CDxfLayout::GetControlOperationState(int pIndex, int pSubIndex, int pSubIndex2) {
	Info_it it = m_infoObject.find(CPvcsControlObjectInfo(pIndex, pSubIndex, pSubIndex2));
	return it->GetControlOperationState();
}

void CDxfLayout::SetActive(void) {
	if (!m_bIsShipLayout) {
		CDxfTank = this;
	}
}

void CDxfLayout::SetScale(const double param_ScaleX, const double param_ScaleY, const int param_BackGround, const int param_UndefBackGround, const int param_ObjectCol, const int param_LineCol, const int param_TextCol,  const bool param_hasLineCol, const bool param_hasTextCol, const bool param_hasBackGround) {
	//ScaleX       = param_ScaleX  ;
	//ScaleY       = param_ScaleY  ;
	OrgScaleX 	= param_ScaleX;
	OrgScaleY 	= param_ScaleY;
	Delta 		= 1 / max(OrgScaleX, OrgScaleY);
	BackGroundCol 	= param_BackGround;
	UndefObjectCol 	= param_UndefBackGround;
	ObjectCol 		= param_ObjectCol;
	LineCol   		= param_LineCol;
	TextCol   		= param_TextCol;
	hasLineCol   	= param_hasLineCol;
	hasTextCol   	= param_hasTextCol;
	hasBackGround   = param_hasBackGround;

}

void CDxfLayout::UpdateScale(short zDelta) {
	double Step = double(zDelta) / (60 * 120.0);
	Delta += Step;
	double OrgMaxScale = max(OrgScaleX, OrgScaleY);
	double OrgMinScale = min(OrgScaleX, OrgScaleY);
	double MaxScale    = OrgMaxScale * Delta;
	//double MinScale = OrgMinScale * Delta;

	if (MaxScale < 0.9) {
		Delta -= Step;
	}
	ScaleX = OrgScaleX * Delta;
	ScaleY = OrgScaleY * Delta;
}

BOOL CDxfLayout::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	if (zDelta) {
		CDxfLayout::CDxfTank->UpdateScale(zDelta);
		Draw();
	}

	return true;

}

Gdiplus::RectF CDxfLayout::LocateBarGraphRect(Gdiplus::PointF param_Point) {
	// Get the number of polylines
	const int      nCount        = m_dxfDrawing.Entity().Polyline().GetCount();
	Gdiplus::RectF Rect(0, 0, 0, 0);
	bool           FindFirstRect = true;
	for (int i = 0; i < nCount; i++) {
		Gdiplus::RectF tmpRect;
		m_ptrPath[i].GetBounds(&tmpRect);
		if (tmpRect.Contains(param_Point)) {
			if (FindFirstRect) {
				FindFirstRect = false;
				Rect = tmpRect;
			} else {
				float Area1 = Rect.Width * Rect.Height;
				float Area2 = tmpRect.Width * tmpRect.Height;
				if (Area2 < Area1) {
					Rect = tmpRect;
				}
			}
		}

	} // for(int i=0; i<nCount; i++)
	return Rect;
}
