// CurveDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "PR/EchoCurveDlgPR.h"
#include "CurveDialog.h"
#include <math.h>
#include <commctrl.h>

// CCurveDialog

IMPLEMENT_DYNAMIC(CCurveDialog, CStatic)

CCurveDialog::CCurveDialog()
{
	InitColor();
	InitCurve();
	m_sanjiaoVisable = false;
	m_arrowVisable = false;
	m_once = false;
	m_min = 0;
	m_max = 0;
	m_axisStyle = 0;
	m_yAxis = 100;
	m_downEnable = false;
	m_x_is_time = false;
}

CCurveDialog::~CCurveDialog()
{
}


BEGIN_MESSAGE_MAP(CCurveDialog, CStatic)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
//	ON_WM_LBUTTONDBLCLK()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CCurveDialog 消息处理程序


BOOL CCurveDialog::Init()
{
	// TODO:  在此添加额外的初始化
	CRect r;
	GetClientRect(&r);
	//InitBorder(r);
	if (m_axisStyle == 1) 
	{
		m_xAxis = int(r.bottom/2.0);
	}
	else {
		m_xAxis = int(r.bottom-20);
	}
	return TRUE; 
}

void CCurveDialog::OnPaint()
{
	CPaintDC m_dc(this); // device context for painting
	if (!m_once) 
	{
		SetRange();
		m_once = true;
	}	
	if (	(!m_echoCurveValue.empty() && m_echoCurveVisable)
		||	(!m_warpCurveValue.empty() && m_warpCurveVisable)
		||	(!m_falseEchoCurveValue.empty() && m_falseEchoCurveVisable)
		)
	{
		CRect r;
		GetClientRect(&r);
		//InitBorder(r);
		if (m_axisStyle == 1) 
		{
			m_xAxis = int(r.bottom/2.0);
		}
		else {
			m_xAxis = int(r.bottom-20);
		}
		Draw(m_dc);
	}
	else {
		DrawBackground(m_dc);
		DrawAxis(m_dc);
		DrawGrid(m_dc, m_axisStyle, 10, 10);
		DrawGraduation(m_dc);
	}

	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CCustomDialogEx::OnPaint()
}

void CCurveDialog::Draw( CPaintDC& m_dc )
{
//	SetRange();
	DrawBackground(m_dc);
	DrawAxis(m_dc);
	DrawGridByPoint(m_dc);
	DrawSelectArea(m_dc);
	Value2Point(m_echoCurveValue, m_echoCurvePoint);
	Value2Point(m_warpCurveValue, m_warpCurvePoint);
	Value2Point(m_falseEchoCurveValue, m_falseEchoCurvePoint);
	DrawCruses(m_dc);
	if (m_sanjiaoVisable) DrawSanjiao(m_dc, m_sanjiao);
	if (m_arrowVisable) DrawArrow(m_dc, m_arrow);
}

// 绘制直线
void CCurveDialog::DrawLine( CPaintDC& m_dc, int x0, int y0, int x1, int y1, bool dotted )
{
	if (dotted) DrawSolidLine(m_dc, x0, y0, x1, y1);
}

// 绘制实线
void CCurveDialog::DrawSolidLine( CPaintDC& m_dc, int x0, int y0, int x1, int y1, int style, int width, COLORREF color )
{
	CPen penAxis = CPen(style, width, color);
	m_dc.SelectObject(&penAxis);
	m_dc.MoveTo(x0, y0);
	m_dc.LineTo(x1, y1);
}

// 绘制实线
void CCurveDialog::DrawSolidLine( CPaintDC& m_dc, int x0, int y0, int x1, int y1 )
{
	DrawSolidLine(m_dc, x0, y0, x1, y1, PS_SOLID, 1, m_colorBorder);
}

// 绘制虚线
void CCurveDialog::DrawDottedLine( CPaintDC& m_dc, int x0, int y0, int x1, int y1, int style, int width, COLORREF color )
{
	m_dc.SetBkColor(m_colorBackground);
	CPen penGraduation = CPen(style, width, color);
	m_dc.SelectObject(&penGraduation);
	m_dc.MoveTo(x0, y0);
	m_dc.LineTo(x1, y1);
}

// 绘制虚线
void CCurveDialog::DrawDottedLine( CPaintDC& m_dc, int x0, int y0, int x1, int y1 )
{
	DrawDottedLine(m_dc, x0, y0, x1, y1, PS_DOT, 1, m_colorAxis);
}

// 绘制标签
void CCurveDialog::DrawLabel( CPaintDC& m_dc, int x, int y, const CString& content )
{
	m_dc.SetBkColor(m_colorBackground);
	m_dc.SetTextColor(m_colorLabel);
	m_dc.TextOut(x, y, content);
}

// 绘制背景
void CCurveDialog::DrawBackground( CPaintDC& m_dc )
{
	m_dc.SetBkColor(m_colorBackground);
	CBrush brush = CBrush(m_colorBackground);
	GetClientRect(&m_bg);
	m_dc.FillRect(m_bg, &brush);
	m_dc.Draw3dRect(m_bg, m_colorBorder, m_colorBorder);
}

// 初始化颜色
void CCurveDialog::InitColor( void )
{
	m_colorArrow			= RGB(0, 0, 255);
	m_colorAxis				= RGB(0, 0, 0);
	m_colorBackground		= RGB(255, 255, 255);
	m_colorBorder			= RGB(0, 0, 0);
	m_colorGrid				= RGB(0, 0, 0);
	m_colorLabel			= RGB(0, 0, 0);
	m_colorEchoCurve		= RGB(255, 0, 0);
	m_colorWarpCurve		= RGB(0, 0, 255);
	m_colorFalseEchoCurve	= RGB(0, 255, 0);
}

// 绘制坐标轴
void CCurveDialog::DrawAxis( CPaintDC& m_dc )
{
	DrawSolidLine(m_dc, m_borderLeft, m_xAxis, m_borderRight, m_xAxis, PS_SOLID, 1, m_colorAxis); // Draw X Axis
	DrawSolidLine(m_dc, m_yAxis, m_borderTop, m_yAxis, m_borderBottom, PS_SOLID, 1, m_colorAxis); // Draw Y Axis
	m_dc.SetTextAlign(TA_RIGHT);
	DrawLabel(m_dc, m_borderRight - 5, m_xAxis + 2, m_xUnit);
	m_dc.SetTextAlign(TA_LEFT);
	DrawLabel(m_dc, m_borderLeft + 2 , m_borderTop + 2, m_yUnit);
}

// 绘制坐标网格
void CCurveDialog::DrawGrid( CPaintDC& m_dc, int x0, int y0, int x1, int y1, int xNum, int yNum )
{
	double xStep = (double( x1 - x0 ))/(double)xNum;
	double yStep = (double( y1 - y0 ))/(double)yNum;
	m_xGraduation = (int)fabs(xStep);
	m_yGraduation = (int)fabs(yStep);
	int tmp = 0;
	for (int i = 1; i < xNum; i++)
	{
		DrawDottedLine( m_dc, x0 + i * (int)xStep, y0, x0 + i * (int)xStep, y1);
	}
	if (m_axisStyle == 1) {	
		for(int j = 1; j < yNum; j++)
		{
			tmp = m_xAxis + j * (int)yStep;
			if (tmp > m_borderBottom || tmp < m_borderTop ) break;
			DrawDottedLine( m_dc, x0, tmp, x1, tmp);
		}
	}
	for(int j = 1; j < yNum; j++)
	{
		tmp = m_xAxis - j * (int)yStep;
		if (tmp > m_borderBottom || tmp < m_borderTop ) break;
		DrawDottedLine( m_dc, x0, tmp, x1, tmp);
	}
}

// 绘制坐标网格
void CCurveDialog::DrawGrid(CPaintDC& m_dc, int style, int xNum, int YNum)
{
	m_axisStyle = style;
	m_xGraduation = xNum;
	m_yGraduation = YNum;
	m_dc.SetBkColor(m_colorBackground);
	if (style == 1) {
		DrawGrid(m_dc, m_yAxis, m_borderTop, m_borderRight, m_borderBottom, m_xGraduation, m_yGraduation);
	} else {
		DrawGrid(m_dc, m_yAxis, m_borderTop, m_borderRight, m_xAxis, m_xGraduation, m_yGraduation);
	}
}

// 绘制坐标网格
void CCurveDialog::DrawGridByPoint( CPaintDC& m_dc )
{
	curvevalue cv;
	cv.first = 0; cv.second = 0;
	CPoint cp;
	for (size_t i = 0; i < m_xAxisValueList.size(); i++)
	{
		cv.first = m_xAxisValueList[i];
		Value2Point(cv, cp);
		DrawDottedLine( m_dc, cp.x, m_borderBottom, cp.x, m_borderTop);
		m_dc.SetTextAlign(TA_CENTER);
		DrawLabel(m_dc, cp.x, m_xAxis + 2, m_xAxisLabelList[i]);
	}
	if (m_axisStyle == 1) {	
		for(size_t j = 0; j < m_yAxisValueMinusList.size(); j++)
		{
			cv.second = m_yAxisValueMinusList[j];
			Value2Point(cv, cp);
			if (cp.y > m_borderBottom) break;
			DrawDottedLine( m_dc, m_yAxis, cp.y, m_borderRight, cp.y);
			m_dc.SetTextAlign(TA_RIGHT);
			DrawLabel(m_dc, m_yAxis - 5, cp.y - 7, m_yAxisLabelMinusList[j]);
		}
	}
	for(size_t j = 0; j < m_yAxisValueList.size(); j++)
	{
		cv.second = m_yAxisValueList[j];
		Value2Point(cv, cp);
		if (cp.y < m_borderTop) break;
		DrawDottedLine( m_dc, m_yAxis, cp.y, m_borderRight, cp.y);
		m_dc.SetTextAlign(TA_RIGHT);
		DrawLabel(m_dc, m_yAxis - 5, cp.y - 7, m_yAxisLabelList[j]);
	}

	DrawLabel(m_dc, m_yAxis - 5, m_xAxis + 2, CString("0.00") );
}

// 获取边框界限
void CCurveDialog::InitBorder( CRect& background )
{
	m_borderTop = background.top;
	m_borderBottom = background.bottom;
	m_borderLeft = background.left;
	m_borderRight = background.right;
}

// 绘制坐标文字
void CCurveDialog::DrawGraduation(CPaintDC& m_dc)
{
	int tmp = 0;
	int foreAlign = m_dc.GetTextAlign();

	// Draw X+ labels
	m_dc.SetTextAlign(TA_CENTER);
	for (unsigned int j = 1; ; j++)
	{
		tmp = m_yAxis + j * m_xPointStep;		
		if (tmp + 5 > m_borderRight || tmp < m_borderLeft || j > m_xAxisLabelList.size()) break;
		DrawLabel(m_dc, tmp, m_xAxis + 2, m_xAxisLabelList[j-1]);
	}

	// Draw Y- lables
	m_dc.SetTextAlign(TA_RIGHT);
	if (m_axisStyle == 1) {
		for(unsigned int j = 1; ; j++)
		{
			tmp = m_xAxis + j * m_yPointStep;
			if (tmp > m_borderBottom || tmp < m_borderTop || j > m_yAxisLabelMinusList.size()) break;
			DrawLabel(m_dc, m_yAxis - 5, tmp - 7, m_yAxisLabelMinusList[j-1]);
		}
	}

	// Draw Y+ labels
	for(unsigned int j = 1; ; j++)
	{
		tmp = m_xAxis - j * m_yPointStep;
		if (tmp > m_borderBottom || tmp-7 < m_borderTop || j > m_yAxisLabelList.size()) break;
		DrawLabel(m_dc, m_yAxis - 5, tmp - 7, m_yAxisLabelList[j-1]);
	}

	// Draw O point
	DrawLabel(m_dc, m_yAxis - 2, m_xAxis + 2, CString("0") );

	m_dc.SetTextAlign(foreAlign);
}


// 设置X轴坐标文字
void CCurveDialog::SetXAxisLabelList( const vector<CString> & labels )
{
	m_xAxisLabelList.clear();
	for (unsigned int i = 0; i < labels.size(); i++)
	{
		m_xAxisLabelList.push_back(labels[i]);
	}
//	DrawGraduation();
}

// 设置Y+轴坐标文字
void CCurveDialog::SetYAxisLabelList( const vector<CString> & labels )
{
	m_yAxisLabelList.clear();
	for (unsigned int i = 0; i < labels.size(); i++)
	{
		m_yAxisLabelList.push_back(labels[i]);
	}
//	DrawGraduation();
}

// 设置Y-轴坐标文字
void CCurveDialog::SetYAxisLabelMinusList( const vector<CString> & labels )
{
	m_yAxisLabelMinusList.clear();
	for (unsigned int i = 0; i < labels.size(); i++)
	{
		m_yAxisLabelMinusList.push_back(labels[i]);
	}
//	DrawGraduation();
}

// 根据坐标绘制曲线
void CCurveDialog::Drawcurve( CPaintDC& m_dc, const vector<CPoint> & points )
{
	Drawcurve(m_dc, points, m_colorArrow);
}

void CCurveDialog::Drawcurve( CPaintDC& m_dc, const vector<CPoint> & points, COLORREF color )
{
	ASSERT(!points.empty());
	CPen pen = CPen(PS_SOLID, 1, color);
	m_dc.SelectObject(&pen);
	size_t i = 0;
	for (; i < points.size(); i++)
	{
		if (points[i].x <= m_borderRight && points[i].x >= m_yAxis) break;
	}
	if (i < points.size()) m_dc.MoveTo(points[i]);
	for (; i < points.size(); i++)
	{
		if (points[i].x > m_borderRight) break;
		m_dc.LineTo(points[i]);
	}
}



// 绘制箭头
void CCurveDialog::DrawArrow( CPaintDC& m_dc, const double x)
{
	curvevalue cv;
	CPoint cp;
	cv.first = x;
	cv.second = 0;
	Value2Point(cv, cp);
	CString s;
	s.Format(_T("%.3f"), x);
	DrawArrow(m_dc, cp.x, m_borderTop+12, 0);
	DrawArrow(m_dc, m_borderRight - 100, m_borderTop + 15, 0);
	m_dc.SetTextAlign(TA_LEFT);
	DrawLabel(m_dc, m_borderRight - 80, m_borderTop + 2, s);
}

// 绘制箭头
void CCurveDialog::DrawArrow(CPaintDC& m_dc, int x, int y, int direction )
{
	switch (direction) {
		case 1:
			DrawSolidLine(m_dc, x, y, x+10, y, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x+5, y+5, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x+5, y-5, PS_SOLID, 2, m_colorArrow);
			break;
		case 2:
			DrawSolidLine(m_dc, x, y, x, y+10, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x-5, y+5, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x+5, y+5, PS_SOLID, 2, m_colorArrow);
			break;
		case 3:
			DrawSolidLine(m_dc, x, y, x-10, y, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x-5, y-5, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x-5, y+5, PS_SOLID, 2, m_colorArrow);
			break;
		default:
			DrawSolidLine(m_dc, x, y, x, y-10, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x-5, y-5, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x+5, y-5, PS_SOLID, 2, m_colorArrow);
			break;
	}
}

void CCurveDialog::DrawArrow( const double x )
{
	m_arrow = x;
	m_arrowVisable = true;
}
// 绘制三角
void CCurveDialog::DrawSanjiao( CPaintDC& m_dc, const double x )
{
	curvevalue cv;
	CPoint cp;
	cv.first = x;
	cv.second = 0;
	Value2Point(cv, cp);
	CString s;
	s.Format(_T("%.3f"), x);
	DrawSanjiao(m_dc, cp.x, m_borderTop+12, 0);
	DrawSanjiao(m_dc, m_borderRight - 100, m_borderTop + 40, 0);
	m_dc.SetTextAlign(TA_LEFT);
	DrawLabel(m_dc, m_borderRight - 80, m_borderTop + 27, s);
}

// 绘制三角
void CCurveDialog::DrawSanjiao( CPaintDC& m_dc, int x, int y, int direction )
{
	switch (direction) {
		case 1:
			DrawSolidLine(m_dc, x, y, x+10, y-5, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x+10, y+5, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x+10, y-5, x+10, y+5, PS_SOLID, 2, m_colorArrow);
			break;
		case 2:
			DrawSolidLine(m_dc, x, y, x-5, y+10, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x+5, y+10, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x-5, y+10, x+5, y+10, PS_SOLID, 2, m_colorArrow);
			break;
		case 3:
			DrawSolidLine(m_dc, x, y, x-10, y+5, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x-10, y-5, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x-10, y+5, x-10, y-5, PS_SOLID, 2, m_colorArrow);
			break;
		default:
			DrawSolidLine(m_dc, x, y, x+5, y-10, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x, y, x-5, y-10, PS_SOLID, 2, m_colorArrow);
			DrawSolidLine(m_dc, x-5, y-10, x+5, y-10, PS_SOLID, 2, m_colorArrow);
			break;
	}
}

void CCurveDialog::DrawSanjiao( const double x )
{
	m_sanjiao = x;
	m_sanjiaoVisable = true;
}
// 设置 x,y 轴范围
void CCurveDialog::SetRange( const double xMin, const double xMax, const double yMin, const double yMax )
{
	m_xMin = xMin;
	m_xMax = xMax;
	m_yMin = yMin;
	m_yMax = yMax;
	SetStep();
	SetAxis();

}

void CCurveDialog::SetRange( void )
{
	if ( m_echoCurveVisable ) {
		for ( size_t i = 0; i < m_echoCurveValue.size(); i++)
			SetRange(m_echoCurveValue[i]);
	}
	if ( m_warpCurveVisable ) {
		for ( size_t i = 0; i < m_warpCurveValue.size(); i++)
			SetRange(m_warpCurveValue[i]);
	}
	if ( m_falseEchoCurveVisable ) {
		for ( size_t i = 0; i < m_falseEchoCurveValue.size(); i++)
			SetRange(m_falseEchoCurveValue[i]);
	}
	PostprocessRange();
}

void CCurveDialog::SetRange( const curvevalue& curveValue )
{
	if ( m_xMin > curveValue.first )
		m_xMin = curveValue.first;
	else if ( m_xMax < curveValue.first )
		m_xMax = curveValue.first;
	if ( m_yMin > curveValue.second )
		m_yMin = curveValue.second;
	else if ( m_yMax < curveValue.second )
		m_yMax = curveValue.second;
}

void CCurveDialog::SetRange( const double xMin, const double xMax )
{
	m_xMin = xMin;
	m_xMax = xMax;
	if ( m_echoCurveVisable ) {
		for ( size_t i = 0; i < m_echoCurveValue.size(); i++)
		{
			if (m_echoCurveValue[i].first >= xMin && m_echoCurveValue[i].first <= xMax)
				SetRange(m_echoCurveValue[i]);
		}
	}
	if ( m_warpCurveVisable ) {
		for ( size_t i = 0; i < m_warpCurveValue.size(); i++)
		{
			if (m_warpCurveValue[i].first >= xMin && m_warpCurveValue[i].first <= xMax) 
				SetRange(m_warpCurveValue[i]);
		}
	}
	if ( m_falseEchoCurveVisable ) {
		for ( size_t i = 0; i < m_falseEchoCurveValue.size(); i++)
		{
			if (m_falseEchoCurveValue[i].first >= xMin && m_falseEchoCurveValue[i].first <= xMax)
				SetRange(m_falseEchoCurveValue[i]);
		}
	}
	SetStep();
	SetAxis();
	PostprocessRange();

}
void CCurveDialog::PostprocessRange( void )
{
	m_yMax = fabs(m_yMax) > fabs(m_yMin) ? fabs(m_yMax) : fabs(m_yMin);
}

// 曲线值转化为坐标
void CCurveDialog::Value2Point( const vector <curvevalue> & curveValue, vector<CPoint>& curvePoint )
{
	curvePoint.clear();
	for (size_t i = 0; i < curveValue.size(); i++)
	{
		CPoint cp;
		curvevalue cv = curveValue[i];
		Value2Point( cv, cp);
		curvePoint.push_back(cp);
	}
}

void CCurveDialog::Value2Point( curvevalue & curveValue, CPoint& curvePoint )
{
	curvePoint.x = LONG (m_yAxis + (m_borderRight - m_yAxis) * (curveValue.first - m_xMin) / (m_xMax - m_xMin));
	if (curveValue.second > 0) 
		curvePoint.y = LONG (m_xAxis - (m_xAxis-(m_borderTop+30)) * curveValue.second / m_yMax);
	else 
		curvePoint.y = LONG (m_xAxis + (m_xAxis-(m_borderTop+30)) * (-curveValue.second) / m_yMax);
}

// 设置回波曲线值
void CCurveDialog::SetEchoCurveValue( const vector<curvevalue> & curveValue )
{
	m_echoCurveValue.clear();
	for (size_t i = 0; i < curveValue.size(); i++)
	{		
		m_echoCurveValue.push_back(curveValue[i]);
		updateMaxMin(curveValue[i].first);
	}
	SetStep();
	SetAxis();
}

// 设置包络线值
void CCurveDialog::SetWarpCurveValue( const vector<curvevalue> & curveValue )
{
	m_warpCurveValue.clear();
	for (size_t i = 0; i < curveValue.size(); i++)
	{
		m_warpCurveValue.push_back(curveValue[i]);
		updateMaxMin(curveValue[i].first);
	}
	SetStep();
	SetAxis();
}

// 设置虚假回波曲线值
void CCurveDialog::SetFalseEchoCurveValue( const vector<curvevalue> & curveValue )
{
	m_falseEchoCurveValue.clear();
	for (size_t i = 0; i < curveValue.size(); i++)
	{	
		m_falseEchoCurveValue.push_back(curveValue[i]);
		updateMaxMin(curveValue[i].first);
	}
	SetStep();
	SetAxis();
}

// 初始化曲线可见
void CCurveDialog::InitCurve( void )
{
	m_echoCurveVisable = true;
	m_warpCurveVisable = false;
	m_falseEchoCurveVisable = false;
}

// 绘制所有曲线
void CCurveDialog::DrawCruses( CPaintDC& m_dc )
{
	if (m_echoCurveVisable && !m_echoCurveValue.empty())
		Drawcurve(m_dc, m_echoCurvePoint, m_colorEchoCurve);
	if (m_warpCurveVisable && !m_warpCurveValue.empty())
		Drawcurve(m_dc, m_warpCurvePoint, m_colorWarpCurve);
	if (m_falseEchoCurveVisable && !m_falseEchoCurveValue.empty())
		Drawcurve(m_dc, m_falseEchoCurvePoint, m_colorFalseEchoCurve);
}

// 计算坐标轴步长
double CCurveDialog::SetStep( double minNum, double maxNum )
{
	double prev = 1.0;
	double curr = 2.0;
	double next = 5.0;
	double temp = 0;
	double alpha;
	double length = maxNum - minNum;
	double retval;

	if ( length <= next )
	{
		alpha = 0.1;
		while (length < curr) {
			temp = next * alpha;
			next = curr;
			curr = prev;
			prev = temp;
		}
		if ( length == curr || fabs ((next-length)/(length-curr)) < fabs(2.0 * next/curr)) {
			retval = curr;
		} else {
			retval = next;
		}
	}
	else 
	{
		alpha = 10.0;
		while (length > curr) {
			temp = prev * alpha;
			prev = curr;
			curr = next;
			next = temp;
		}
		if ( length == prev || fabs((curr-length)/(length-prev)) > fabs(2.0 * curr/prev)) {
			retval = prev;
		} else {
			retval = curr;
		}
	}
	return retval/10.0;
}

void CCurveDialog::SetStep( void )
{
	m_xStep = SetStep(m_xMin, m_xMax);
	m_yStep = SetStep(m_yMin, m_yMax*1.15);
	CPoint cp;
	curvevalue cv;
	cv.first = m_xStep;
	cv.second = m_yStep;
	Value2Point(cv, cp);
	m_xPointStep = cp.x;
	m_yPointStep = cp.y;
}

// 设置坐标轴刻度值
void CCurveDialog::SetAxis( double startVal, double endVal, double step, vector<CString>& objLabelList, vector<double>& objValueList)
{
	objLabelList.clear();
	objValueList.clear();
	double curr = 0.0;
	if (startVal >= 0) {
		while ( curr <= startVal ) 
			curr += step;
		while ( curr <= endVal) {
			CString s;

			s.Format(_T("%.3f"), curr);
			//if (curr >= 1.0) 
			//	s.Format(_T("%.3f"), curr);
			//else 
			//	s.Format(_T("%f"), curr);
			objLabelList.push_back(s);
			objValueList.push_back(curr);
			curr += step;
		}
	} else {
		while ( curr >= endVal ) 
			curr -= step;
		while ( curr > startVal) {
			CString s;
			s.Format(_T("%.3f"), curr);
			//if (curr <= -1.0) 
			//	s.Format(_T("%.3f"), curr);
			//else 
			//	s.Format(_T("%f"), curr);
			objLabelList.push_back(s);
			objValueList.push_back(curr);
			curr -= step;
		}
	}
}

// 设置时间轴刻度值
void CCurveDialog::SetTimeAxis( double startVal, double endVal, double step, vector<CString>& objLabelList, vector<double>& objValueList)
{
	objLabelList.clear();
	objValueList.clear();

	CTime tim = CTime::GetCurrentTime();
	INT64 currTime = tim.GetTime();
	INT64 timeStep = (INT64)(40.0*step*(double)(endVal - startVal)/2160.0);
	currTime -= (INT64) ((endVal - startVal) / 2160 * 86400.0);
	double curr = 0.0;
	if (startVal >= 0) {
		while ( curr <= startVal ) {
			curr += step;
			currTime += timeStep;
		}
		while ( curr <= endVal) {
			CString s;
			CTime ct = CTime(currTime);
			s = ct.Format(_T("%H:%M"));
			objLabelList.push_back(s);
			objValueList.push_back(curr);
			currTime += timeStep;
			curr += step;
		}
	}
}

void CCurveDialog::SetAxis( void )
{
	if (m_x_is_time)
		SetTimeAxis( m_xMin, m_xMax, m_xStep, m_xAxisLabelList, m_xAxisValueList);
	else 
		SetAxis( m_xMin, m_xMax, m_xStep, m_xAxisLabelList, m_xAxisValueList);
	SetAxis( 0, m_yMax*1.15, m_yStep, m_yAxisLabelList, m_yAxisValueList);
	SetAxis( -m_yMax*1.15,0, m_yStep, m_yAxisLabelMinusList, m_yAxisValueMinusList);
}

void CCurveDialog::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	
	CRect r;
	GetClientRect(&r);
	InitBorder(r);
	if (m_axisStyle == 1) 
	{
		m_xAxis = int(r.bottom/2.0);
	}
	else {
		m_xAxis = int(r.bottom-20);
	}

	if (	!m_echoCurveValue.empty()
		||	!m_warpCurveValue.empty()
		||	!m_falseEchoCurveValue.empty()) 
	{
		SetAxis(m_xAxis, m_yAxis);
		this->RedrawWindow();
	}
}


void CCurveDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x > m_yAxis && point.x < m_borderRight && point.y > m_borderTop && point.y < m_borderBottom)
	{
		curvevalue cv;
		Point2Value(point, cv);
		m_down = cv.first;
		m_downEnable = true;
		m_downPos = point.x;
		m_lastPoint = point;
//		SetLine(point.x);
	}
	CStatic::OnLButtonDown(nFlags, point);
}

void CCurveDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_downEnable && point.x > m_yAxis && point.x < m_borderRight && point.y > m_borderTop && point.y < m_borderBottom)
	{
		curvevalue cv;
		Point2Value(point, cv);
		m_up = cv.first;
		if (   m_up != m_down						// 没动
			&& fabs(m_up-m_down)/(m_max-m_min) > 10.0/m_echoCurvePoint.size() // 取样区间太小
			) 
		{
			if (m_down > m_up) SetRange(m_up, m_down);
			else SetRange(m_down, m_up);
			this->RedrawWindow();
		}
		m_downEnable = false;
		m_upPos = point.x;
		this->RedrawWindow();
	}
	CStatic::OnLButtonUp(nFlags, point);
}

void CCurveDialog::OnRButtonUp(UINT /*nFlags*/, CPoint /*point*/)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetRange();
	SetStep();
	SetAxis();
	this->RedrawWindow();
	//CStatic::OnRButtonUp(nFlags, point);
}

void CCurveDialog::Point2Value( CPoint& curvePoint, curvevalue & curveValue )
{
	curveValue.first = m_xMin + (curvePoint.x - m_yAxis) * (m_xMax - m_xMin) / (m_borderRight - m_yAxis);
}

void CCurveDialog::updateMaxMin( double val )
{
	if (m_max < val) m_max = val;
	if (m_min > val) m_min = val;
}
// void CCurveDialog::OnLButtonDblClk(UINT nFlags, CPoint point)
// {
// 	// TODO: 在此添加消息处理程序代码和/或调用默认值
// 
// 
// 
// 	CStatic::OnLButtonDblClk(nFlags, point);
// }


void CCurveDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x > m_yAxis && point.x < m_borderRight && point.y > m_borderTop && point.y < m_borderBottom)
	{
		if (m_downEnable) {
			m_upPos = point.x;
			long left, right, bottom;
			if (m_lastPoint.x < m_upPos)
			{
				left = m_lastPoint.x;
				right = m_upPos;
			} 
			else
			{
				right = m_lastPoint.x;
				left = m_upPos;
			}
			bottom = (m_axisStyle == 1) ? m_borderBottom : m_xAxis;
			CRect r = CRect(left-20, m_borderTop, right+20, bottom);
			m_lastPoint = point;
			InvalidateRect(&r);

		}
	}	
	CStatic::OnMouseMove(nFlags, point);
}

void CCurveDialog::DrawSelectArea( CPaintDC& m_dc )
{
	if (!m_downEnable) 
		return;
	long left, right, bottom;
	if (m_downPos < m_upPos)
	{
		left = m_downPos;
		right = m_upPos;
	} 
	else
	{
		right = m_downPos;
		left = m_upPos;
	}
	bottom = (m_axisStyle == 1) ? m_borderBottom : m_xAxis;
	CRect r = CRect(left+1, m_borderTop+1, right-1, bottom-1);
	m_dc.Draw3dRect(r, RGB(0, 0, 255), RGB(0, 0, 255));


}