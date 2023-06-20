#pragma once
#include <vector>

using std::vector;
using std::pair;

typedef pair<double, double> curvevalue;
// CCurveDialog

class CCurveDialog : public CStatic
{
	DECLARE_DYNAMIC(CCurveDialog)

public:
	CCurveDialog();
	virtual ~CCurveDialog();

//	enum {IDD = IDD_CURVECANVAS};

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL Init();
	afx_msg void OnPaint();
	void DrawArrow(const double x);
	void DrawSanjiao(const double x);

	void SetAxis(const int xPos, const int yPos) { m_xAxis = xPos; m_yAxis = yPos; }
	void SetUnit(const CString& xUnit, const CString& yUnit) { m_xUnit = xUnit; m_yUnit = yUnit; }
	
	void SetStyle (const int val) { m_axisStyle = val; }
	void SetRange( const double xMin, const double xMax, const double yMin, const double yMax);
	void SetEchoCurveValue( const vector<curvevalue> & curveValue );
	void SetWarpCurveValue( const vector<curvevalue> & curveValue );
	void SetFalseEchoCurveValue( const vector<curvevalue> & curveValue );

	bool EchoCurveVisable() const { return m_echoCurveVisable; }
	void EchoCurveVisable(bool val) { m_echoCurveVisable = val; SetRange(); }
	bool WarpCurveVisable() const { return m_warpCurveVisable; }
	void WarpCurveVisable(bool val) { m_warpCurveVisable = val; SetRange(); }
	bool FalseEchoCurveVisable() const { return m_falseEchoCurveVisable; }
	void FalseEchoCurveVisable(bool val) { m_falseEchoCurveVisable = val; SetRange(); }

	void SetRange(const double xMin, const double xMax);
	void NBSet(void) {	SetRange();SetStep();SetAxis();}

	void SetXAxisTime(bool b) { m_x_is_time = b; }

private:
	void Draw(CPaintDC& m_dc);
	void DrawArrow(CPaintDC& m_dc,const double x);
	void DrawSanjiao(CPaintDC& m_dc,const double x);

	void DrawSelectArea(CPaintDC& m_dc);
	void InitColor(void);													// 初始化颜色
	void InitBorder(CRect& background);										// 初始化边框
	void InitCurve(void);

	void Drawcurve(CPaintDC& m_dc,const vector<CPoint> & points, COLORREF color);
	void DrawCruses(CPaintDC& m_dc);

	void DrawBackground(CPaintDC& m_dc);												// 背景区域
	void DrawAxis(CPaintDC& m_dc);													// 坐标轴
	void DrawGraduation(CPaintDC& m_dc);												// 坐标刻度

	void DrawGridByPoint(CPaintDC& m_dc);
	void DrawGrid(CPaintDC& m_dc, int style = 0, int xNum = 10, int yNum = 10);				// 0: normal,  1:half, 0 as default
	void DrawGrid(CPaintDC& m_dc, int x0, int y0, int x1, int y1, int xNum, int yNum);		// xNum, yNum: 横纵轴格数

	void DrawLine(CPaintDC& m_dc, int x0, int y0, int x1, int y1, bool dotted);
	void DrawArrow(CPaintDC& m_dc, int x, int y, int direction);							// 1: left, 2:up, 3;right, 0 or other: down
	void DrawSanjiao(CPaintDC& m_dc, int x, int y, int direction);							// 1: left, 2:up, 3;right, 0 or other: down
	void DrawLabel(CPaintDC& m_dc, int x, int y, const CString& content);
	void DrawSolidLine(CPaintDC& m_dc, int x0, int y0, int x1, int y1);
	void DrawDottedLine(CPaintDC& m_dc, int x0, int y0, int x1, int y1);
	void DrawSolidLine(CPaintDC& m_dc, int x0, int y0, int x1, int y1, int style, int width, COLORREF color);
	void DrawDottedLine(CPaintDC& m_dc, int x0, int y0, int x1, int y1, int style, int width, COLORREF color);

	void Value2Point (const vector <curvevalue> & curveValue, vector<CPoint>& curvePoint) ;
	void Value2Point (curvevalue & curveValue, CPoint& curvePoint);
	void Point2Value (CPoint& curvePoint, curvevalue & curveValue);

	void SetRange(void);
	void SetRange(const curvevalue& curveValue);

	void PostprocessRange(void);

	double SetStep(double minNum, double maxNum);
	void SetStep(void);
	void SetAxis(double startVal, double endVal, double step, vector<CString> & , vector<double>& );
	void SetTimeAxis(double startVal, double endVal, double step, vector<CString> & , vector<double>& );
	void SetAxis(void);

	void Drawcurve(CPaintDC& m_dc, const vector<CPoint> & points);
	void SetXAxisLabelList(const vector<CString> & labels);
	void SetYAxisLabelList(const vector<CString> & labels);
	void SetYAxisLabelMinusList(const vector<CString> & labels);
	void SetOPoint(const CString& val ) { m_oPoint = val; }
	void SetLine(int x);

	void updateMaxMin(double val);

private:
	COLORREF m_colorBorder;
	COLORREF m_colorGrid;
	COLORREF m_colorLabel;
	COLORREF m_colorArrow;
	COLORREF m_colorAxis;
	COLORREF m_colorBackground;
	COLORREF m_colorEchoCurve;
	COLORREF m_colorWarpCurve;
	COLORREF m_colorFalseEchoCurve;

	CRect m_bg;

	long m_borderTop, m_borderBottom, m_borderLeft, m_borderRight;
	int m_xAxis, m_yAxis;

	int m_xGraduation, m_yGraduation;
	int m_axisStyle;
	CString m_xUnit, m_yUnit;

	vector<CString> m_xAxisLabelList;
	vector<CString> m_yAxisLabelList;
	vector<CString> m_yAxisLabelMinusList;
	vector<double> m_xAxisValueList;
	vector<double> m_yAxisValueList;
	vector<double> m_yAxisValueMinusList;
	CString m_oPoint;

	double m_xMin, m_xMax, m_yMin, m_yMax;
	double m_max, m_min;

	vector <curvevalue> m_echoCurveValue;
	vector <curvevalue> m_warpCurveValue;
	vector <curvevalue> m_falseEchoCurveValue;

	vector <CPoint> m_echoCurvePoint;
	vector <CPoint> m_warpCurvePoint;
	vector <CPoint> m_falseEchoCurvePoint;

	bool m_echoCurveVisable;
	bool m_warpCurveVisable;
	bool m_falseEchoCurveVisable;

	double m_xStep, m_yStep;
	LONG m_xPointStep, m_yPointStep;

	double m_arrow, m_sanjiao;
	bool m_arrowVisable, m_sanjiaoVisable;
	double m_down, m_up;
	long m_downPos, m_upPos;
	bool m_downEnable, m_upEnable;
	bool m_once;
	CPoint m_lastPoint;

	bool m_x_is_time;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


