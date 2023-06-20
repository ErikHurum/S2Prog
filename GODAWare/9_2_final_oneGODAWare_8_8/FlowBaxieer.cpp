// FlowBaxieer.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "FlowBaxieer.h"

#include "Flow.h"

// FlowBaxieer 对话框

IMPLEMENT_DYNAMIC(FlowBaxieer, CDialog)

FlowBaxieer::FlowBaxieer(CWnd* pParent /*=NULL*/)
	: CDialog(FlowBaxieer::IDD, pParent)
{

}

FlowBaxieer::~FlowBaxieer()
{
}

void FlowBaxieer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_B, m_combo_b);
}


BEGIN_MESSAGE_MAP(FlowBaxieer, CDialog)
END_MESSAGE_MAP()

bool FlowBaxieer::GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 )
{
	hightArray.RemoveAll();
	valArray.RemoveAll();


	for (int i = 0; i < 33; i++)
	{
		hightArray.Add(0.0);
		valArray.Add(0.0);
	}

	hightArray[0] = valArray[0] = 0.0;	
	for(int i = 1; i < 33; i++)
	{
		hightArray[i] = i * 0.03125*P006;
		double Q = CFlow::baxieer(p981, hightArray[i]);
		if (Q == -999)
		{
			return false;
		}
		valArray[i] = Q;
	}
	return true;
}


// FlowBaxieer 消息处理程序

void FlowBaxieer::OnOK()
{
	p981 = m_combo_b.GetCurSel() + 3;
	CDialog::OnOK();
}
