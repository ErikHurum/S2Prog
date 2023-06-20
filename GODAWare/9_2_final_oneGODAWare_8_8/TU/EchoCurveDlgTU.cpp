	// EchoCurveDlgTU.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFC.h"
#include "EchoCurveDlgTU.h"


// CEchoCurveDlgTU

IMPLEMENT_DYNAMIC(CEchoCurveDlgTU, CCustomDialogEx)

CEchoCurveDlgTU::CEchoCurveDlgTU()
{
	
}

CEchoCurveDlgTU::~CEchoCurveDlgTU()
{
}


BEGIN_MESSAGE_MAP(CEchoCurveDlgTU, CCustomDialogEx)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CEchoCurveDlgTU::OnBnClickedBtnLoad)
	ON_WM_SIZE()
//	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CEchoCurveDlgTU 消息处理程序



void CEchoCurveDlgTU::DoDataExchange(CDataExchange* pDX)
{


	CCustomDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ECHOCURVE, m_echoCurve);
	DDX_Control(pDX, IDC_CHECK_ENVELOP, m_envelop);
	DDX_Control(pDX, IDC_CHECK_FALSEECHO, m_falseEcho);
	DDX_Control(pDX, IDC_CURVE, m_curveDraw);
}

void CEchoCurveDlgTU::OnBnClickedBtnLoad()
{
	if (!m_echoCurve.GetCheck() && !m_envelop.GetCheck() && !m_falseEcho.GetCheck())
		return;
	if (!theApp.m_pClient->IsOnline())
	{
		return;
	}
	CProgress progress;

	float region = 10, low = 10;
	theApp.m_pClient->LoadData(0x6, region);

	theApp.m_pClient->LoadData(0x111, low);

	if (low > region)
	{
		region = low;
	}

	m_curveDraw.SetUnit(CString("(m)"), CString("(dB)"));
	m_curveDraw.SetRange(0, region, 0 , 120);

	m_curveDraw.EchoCurveVisable(false);
	m_curveDraw.FalseEchoCurveVisable(false);
	m_curveDraw.WarpCurveVisable(false);

	double xScale = 1;



	if (m_echoCurve.GetCheck())
	{
		CArray<BYTE> byteArray;
		theApp.m_pClient->LoadData(0x991, byteArray);

		UncompressData(byteArray, m_echoCurveVec, xScale, region);
		
		float arrow, sanjiao;
		theApp.m_pClient->LoadData(0x998, arrow);
		theApp.m_pClient->LoadData(0x990,sanjiao);


		
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

BOOL CEchoCurveDlgTU::OnInitDialog()
{
	CCustomDialogEx::OnInitDialog();


	m_echoCurve.SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CEchoCurveDlgTU::UncompressData( const CArray<BYTE>& byteArray , vector<curvevalue>& curveValueVec, double xScale, double maxXvalue)
{
	curveValueVec.clear();
	
	double x = 0, y = 0;


	xScale = maxXvalue * 1.1 / (byteArray.GetSize()/2);

	for (int i = 0; i < byteArray.GetSize()-1; i += 2)
	{
		int tempY = int(((byteArray[i+1] << 8) | byteArray[i]) & 0xfff);

		
		DMT_TRACE("Data Word%d: 0x%x", i/2, *(WORD*)(&byteArray[i]));

		DMT_TRACE("x raw value: %d", ((byteArray[i+1] >> 4) & 0xf));
		DMT_TRACE("y raw value: %d", tempY);

		y = double(tempY) / 2047 * 120;
		

		DMT_TRACE("x value: %f", x);
		DMT_TRACE("y value: %f", y);
		DMT_TRACE("\n");

		maxXvalue;
	
		curvevalue cv;
		cv.first = x;
		cv.second = y;
		curveValueVec.push_back(cv);

		x += xScale;
	}
	

}
void CEchoCurveDlgTU::OnSize(UINT nType, int cx, int cy)
{
	CCustomDialogEx::OnSize(nType, cx, cy);

	if (IsWindow(m_curveDraw.GetSafeHwnd()))
	{
		m_curveDraw.SetWindowPos(NULL, 0, 20, cx - 20, cy - 40, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
	Invalidate();
	
}

//int CEchoCurveDlgTU::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CCustomDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//
//	return 0;
//}

void CEchoCurveDlgTU::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码

	//m_curveDraw.RedrawWindow();
	// 不为绘图消息调用 CCustomDialogEx::OnPaint()
}
