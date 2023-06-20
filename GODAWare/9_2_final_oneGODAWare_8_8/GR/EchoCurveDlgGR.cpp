	// EchoCurveDlgGR.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "EchoCurveDlgGR.h"


// CEchoCurveDlgGR

IMPLEMENT_DYNAMIC(CEchoCurveDlgGR, CCustomDialogEx)

CEchoCurveDlgGR::CEchoCurveDlgGR()
{
	
}

CEchoCurveDlgGR::~CEchoCurveDlgGR()
{
}


BEGIN_MESSAGE_MAP(CEchoCurveDlgGR, CCustomDialogEx)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CEchoCurveDlgGR::OnBnClickedBtnLoad)
	ON_WM_SIZE()
//	ON_WM_CREATE()
//	ON_WM_PAINT()
END_MESSAGE_MAP()



// CEchoCurveDlgGR 消息处理程序



void CEchoCurveDlgGR::DoDataExchange(CDataExchange* pDX)
{
	CCustomDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ECHOCURVE, m_echoCurve);
	DDX_Control(pDX, IDC_CHECK_ENVELOP, m_envelop);
	DDX_Control(pDX, IDC_CHECK_FALSEECHO, m_falseEcho);
	DDX_Control(pDX, IDC_CURVE, m_curveDraw);
}

void CEchoCurveDlgGR::OnBnClickedBtnLoad()
{
	if (!m_echoCurve.GetCheck() && !m_envelop.GetCheck() && !m_falseEcho.GetCheck())
		return;
	if (!theApp.m_pClient->IsOnline())
	{
		return;
	}

	CProgress progress;

	float region = 10;
	theApp.m_pClient->LoadData(0x17, region);

	
	m_curveDraw.SetStyle(1);
	m_curveDraw.SetUnit(CString("(m)"), CString("(mV)"));
	m_curveDraw.SetRange(0, region, 0 , 60);

	m_curveDraw.EchoCurveVisable(false);
	m_curveDraw.FalseEchoCurveVisable(false);
	m_curveDraw.WarpCurveVisable(false);

	double xScale = 0.012818667;


	if (m_echoCurve.GetCheck())
	{
		CArray<BYTE> byteArray;
		theApp.m_pClient->LoadData(0x991, byteArray);

		UncompressData(byteArray, m_echoCurveVec, xScale, region);
		
		double sanjiao =  *(float*)(&byteArray[8]);
		double arrow =  *(float*)(&byteArray[12]);

		if (byteArray.GetSize() < 16)
		{
			return;
		}


		
		m_curveDraw.SetEchoCurveValue(m_echoCurveVec);
		m_curveDraw.EchoCurveVisable(true);


		m_curveDraw.DrawArrow(arrow);
		m_curveDraw.DrawSanjiao(sanjiao);
		m_curveDraw.SetRange(0, region, 0 , 60);
		m_curveDraw.NBSet();
		m_curveDraw.RedrawWindow();

	}

	if (m_envelop.GetCheck())
	{
		CArray<BYTE> byteArray;
		theApp.m_pClient->LoadData(0x993, byteArray);
		UncompressData(byteArray, m_envelopVec, xScale, region);
		
		m_curveDraw.SetWarpCurveValue(m_envelopVec);
		m_curveDraw.WarpCurveVisable(true);
		m_curveDraw.SetRange(0, region, 0 , 60);
		m_curveDraw.NBSet();
		m_curveDraw.RedrawWindow();
	}

	if (m_falseEcho.GetCheck())
	{
		CArray<BYTE> byteArray;
		theApp.m_pClient->LoadData(0x992, byteArray);
		UncompressData(byteArray, m_falseEchoVec, xScale, region);
		
		m_curveDraw.SetFalseEchoCurveValue(m_falseEchoVec);
		m_curveDraw.FalseEchoCurveVisable(true);
		m_curveDraw.SetRange(0, region, 0 , 60);
		m_curveDraw.NBSet();
		m_curveDraw.RedrawWindow();
	}
}

BOOL CEchoCurveDlgGR::OnInitDialog()
{
	CCustomDialogEx::OnInitDialog();

	m_echoCurve.SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CEchoCurveDlgGR::UncompressData( const CArray<BYTE>& byteArray , vector<curvevalue>& curveValueVec, double xScale, double /*maxXvalue*/)
{
	curveValueVec.clear();
	
	double x = 0, y = 0, sumY = 0;


	
	for (int i = 17; i < byteArray.GetSize()-1; i += 2)
	{
		int tempY = int(((byteArray[i+1] << 8) | byteArray[i]) & 0xfff);

		
		y = double(tempY) / 1023 * 120 - 40;
		sumY += y;
		x += ((byteArray[i+1] >> 4) & 0xf) * xScale;

	
		curvevalue cv;
		cv.first = x;
		cv.second = y;
		curveValueVec.push_back(cv);
	}

	for (size_t i = 0; i < curveValueVec.size(); i++)
	{
		curveValueVec[i].second -= sumY/curveValueVec.size();
	}
	

}
void CEchoCurveDlgGR::OnSize(UINT nType, int cx, int cy)
{
	CCustomDialogEx::OnSize(nType, cx, cy);

	if (IsWindow(m_curveDraw.GetSafeHwnd()))
	{
		m_curveDraw.SetWindowPos(NULL, 0, 20, cx - 20, cy - 40, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
	Invalidate();
	
}

//int CEchoCurveDlgGR::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CCustomDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//
//	return 0;
//}

//void CEchoCurveDlgGR::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//	// TODO: 在此处添加消息处理程序代码
//
//	//m_curveDraw.RedrawWindow();
//	// 不为绘图消息调用 CCustomDialogEx::OnPaint()
//}
