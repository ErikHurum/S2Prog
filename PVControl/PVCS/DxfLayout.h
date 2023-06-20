#pragma once
#include "dxfdrawing.h"
#include "atltypes.h"
#include "dxfregioninfo.h"
#include "pvcsconfiguration.h"
#include "pvcscontrolobjectinfo.h"
#include "pvcsshipdata.h"

#include "pvcswagocontrol.h"
#include "pvcsobjectcontroldlg.h"

#include <set>
using std::set;

// Class Name   : CDxfLayout
// Description  : Window class responsible for drawing the Dxf drawing

class CDxfLayout : public CWnd {
    DECLARE_DYNAMIC(CDxfLayout)

public:
    CDxfLayout();
    virtual ~CDxfLayout();
private:
    volatile double m_PrevX;
    volatile double m_PrevY;
    volatile int m_PrevScrollX;
    volatile int m_PrevScrollY;
    static CDxfLayout *CDxfTank;
    double Delta;

protected:
    DECLARE_MESSAGE_MAP()

    struct __BOUNDEXTREMES {
        CDxfPoint minPoint;
        CDxfPoint maxPoint;
    }m_boundRect;


    HDC m_hMemDC;
    HGDIOBJ m_hMemDC_Scaled;

    CDxfDrawing m_dxfDrawing;
    string m_strTankLayer;
    bool m_bIsShipLayout;

    bool   m_bDraw;
    double m_dScale;
    bool   m_bIsShowScreenStatusText;
    int    m_iScreenNumber;
    Gdiplus::GraphicsPath *m_ptrPath;
    Gdiplus::GraphicsPath *m_ptrHatch;

    CDxfRegionInfo *m_ptrRegionInfo;

    int *m_ptriMap;

    CPvcsShipData::TankMap *m_ptrTankMap;
    static set<CPvcsControlObjectInfo> m_infoObject;
    typedef set<CPvcsControlObjectInfo>::iterator Info_it;

    vector<int> ObjColorVector;
    vector<string>   m_strTankName;
    vector<wstring>  m_FontTankName;
    vector<double>   m_FontSizeTankName;
    vector<unsigned> m_TankNameColor;
    vector<Gdiplus::PointF> m_posTankName;

    vector<string>   m_strTankValues;
    vector<wstring>  m_FontTankValues;
    vector<double>   m_FontSizeTankValues;
    vector<unsigned> m_TankValueColor;
    vector<Gdiplus::PointF> m_posTankValues;

    vector<string>   m_strTankBarGraphs;
    vector<unsigned> m_TankBarIndex;
    vector<unsigned> m_TankBarSubIndex;
    vector<unsigned> m_TankBarGraphColor;
    vector<Gdiplus::PointF> m_posTankBarGraphs;
    vector<Gdiplus::RectF> m_rectBarGraphs;


    vector<string>   m_strObjectValues;
    vector<wstring>  m_FontObjectValues;
    vector<double>   m_FontSizeObjectValues;
    vector<unsigned> m_ObjectValuesColor;
    vector<Gdiplus::PointF> m_posObjectValues;

    vector<string>   m_strTankAlarms;
    vector<wstring>  m_FontTankAlarms;
    vector<double>   m_FontSizeTankAlarms;
    vector<unsigned> m_TankAlarmColor;
    vector<bool>     m_TankAlarmColInverted;
    vector<unsigned> m_TankAlarmIndex;
    vector<unsigned> m_TankAlarmSubIndex;
    vector<unsigned> m_TankAlarmSubIndex2;
    vector<Gdiplus::PointF> m_posTankAlarms;

    vector<string>   m_strTankNameM;
    vector<unsigned> m_TankNameColorM;
    vector<wstring>  m_FontTankNameM;
    vector<double>   m_FontSizeTankNameM;
    vector<Gdiplus::PointF> m_posTankNameM;

    vector<string>   m_strTankValuesM;
    vector<wstring>  m_FontTankValuesM;
    vector<double>   m_FontSizeTankValuesM;
    vector<unsigned> m_TankValueColorM;
    vector<Gdiplus::PointF> m_posTankValuesM;

    vector<string>   m_strObjectValuesM;
    vector<wstring>  m_FontObjectValuesM;
    vector<double>   m_FontSizeObjectValuesM;
    vector<unsigned> m_ObjectValuesColorM;
    vector<Gdiplus::PointF> m_posObjectValuesM;


public:
    static CDxfLayout *PwrPack;
    //CPvcsControlObjectDlg m_dlgCtrl;
    static bool drawn;
    static int GetControlScreenNumber(int pIndex, int pSubIndex, int pSubIndex2);
    void Draw(void);
    bool Open(const CString &param_strFileName, const CString &param_strTankLayer, const bool &param_bIsShipLayout = false, const unsigned param_Color = 0, const unsigned param_BGColor = 0, const unsigned param_LineColor = 0, const unsigned param_TextColor = 0, const bool param_hasLineCol=false, const bool param_hasTextCol=false, const bool param_hasBackGround=true); 
    afx_msg void OnPaint();
    void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
    void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
    BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

    bool LoadRegions(void);
    void DrawBackground();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    bool GetRegionInfo(void);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    bool Create(const RECT &param_rect, CWnd *param_pParentWnd);
    void TransformGraphics(Gdiplus::Graphics &param_graphics);
    void LoadTankNames(void);
    void DrawText(void);
    void DrawMText(void);
    bool ProcessClickOnObject(const int &param_iIndex, CPoint param_point, int ScreenNumber);
    void ProcessClickOnTank(const int &param_iIndex);
    void Update(CPvcsShipData::TankMap *pTankMap, int ScreenNumber, bool ShowScreenText);
    void ActivateTank(const int &param_iTankID);
    void AddPath(Gdiplus::GraphicsPath &param_path, const CDxfPoint &param_ptFirst, const CDxfPoint &param_ptSecond);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    void EnableDraw(const bool &param_bEnable = true);
private:
    bool m_bSuccess;
    static volatile bool m_bAddingObjectInfo;
    static bool m_bIsFindControlObjectInfo;
    volatile double ScaleX;
    volatile double ScaleY;
    double OrgScaleX;
    double OrgScaleY;
    int    SplitScreens;
    int    BackGroundCol;
	int    UndefObjectCol;
    int    ObjectCol;
    int    LineCol;
    int    TextCol;
    bool   DragStart;
	bool   hasLineCol;
	bool   hasTextCol;
	bool   hasBackGround;
	int    UpdateDelay;
public:
    void DrawFreeValues(void);
    // Added BY JSD
    int m_bAlmFirst;
    static CString GetObjectName(int pIndex, int pSubIndex, int pSubIndex2 = -1);

    //function to set value to be set by user for a control
    static void SetValueToBeSet(int pIndex, int pSubIndex, CString pValuetoSet, int pSubIndex2 = -1);

    //function to get value to be set by user for a control
    static bool GetValueToBeSet(int pIndex, int pSubIndex, CString &pstrValue, int pSubIndex2 = -1);

    //Get Control Object
    static void GetControlObject(int pIndex, int pSubIndex, CPvcsControlObjectInfo &pPvcsCOntrolObject, int pSubIndex2 = -1);

    static bool GetThreadRunningState(int pIndex, int pSubIndex, int pSubIndex2 = -1);

    static bool GetThreadExitState(int pIndex, int pSubindex, int pSubIndex2 = -1);

    static bool GetThreadExitedState(int pIndex, int pSubIndex, int pSubIndex2 = -1);

    static bool GetThreadBusyState(int pIndex, int pSubIndex, int pSubIndex2 = -1);

    static void SetThreadRunningState(int pIndex, int pSubIndex, bool pState, int pSubIndex2 = -1);

    static void SetThreadExitState(int pIndex, int pSubindex, bool pState, int pSubIndex2 = -1);

    static void SetThreadExitedState(int pIndex, int pSubIndex, bool pState, int pSubIndex2 = -1);

    static void SetThreadBusyState(int pIndex, int pSubIndex, bool pState, int pSubIndex2 = -1);

    static bool GetTimeoutState(int pIndex, int pSubIndex, int pSubIndex2 = -1);

    static void SetTimeoutState(int pIndex, int pSubIndex, bool pState, int pSubIndex2 = -1);

    static void SetControlOperationState(int pIndex, int pSubIndex, bool bState, int pSubIndex2 = -1);

    static bool GetControlOperationState(int pIndex, int pSubIndex, int pSubIndex2 = -1);

    void SetActive(void);
    void SetScale(const double param_ScaleX, const double param_ScaleY, const int param_BackGround, const int param_UndefBackGround, const int param_ObjectCol, const int param_LineCol, const int param_TextCol, const bool param_hasLineCol, const bool param_hasTextCol, bool param_hasBackGround);

    void UpdateScale(short zDelta);
    static LRESULT CALLBACK MouseHook(int nCode, WPARAM wParam, LPARAM lParam);
    Gdiplus::RectF LocateBarGraphRect(Gdiplus::PointF param_Point);
    //struct Tank_Object_Name
    //{
    //  CString TankName;
    //  CString ObjectName;
    //};
    //static vector <Tank_Object_Name> m_struct_TankObjectNames;
};

