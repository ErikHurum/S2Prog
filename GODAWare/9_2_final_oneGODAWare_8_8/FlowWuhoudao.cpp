// FlowWuhoudao.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "FlowWuhoudao.h"
#include "Flow.h"


// FlowWuhoudao 对话框

IMPLEMENT_DYNAMIC(FlowWuhoudao, CDialog)

FlowWuhoudao::FlowWuhoudao(CWnd* pParent /*=NULL*/)
	: CDialog(FlowWuhoudao::IDD, pParent)
{

}

FlowWuhoudao::~FlowWuhoudao()
{
}

void FlowWuhoudao::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_B, m_combo_b);
}


BEGIN_MESSAGE_MAP(FlowWuhoudao, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_B, &FlowWuhoudao::OnCbnSelchangeComboB)
	ON_BN_CLICKED(IDCANCEL, &FlowWuhoudao::OnBnClickedCancel)
END_MESSAGE_MAP()


// FlowWuhoudao 消息处理程序
void FlowWuhoudao::OnOK()
{
	b = m_combo_b.GetCurSel();

	CDialog::OnOK();
}

bool FlowWuhoudao::GenerateMapping( CArray<double>& hightArray, CArray<double>& valArray, double P006 )
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
		double Q = CFlow::baxieer(b, hightArray[i]);
		if (Q == -999)
		{
			return false;
		}
		valArray[i] = Q;
	}
	return true;
}
void FlowWuhoudao::OnCbnSelchangeComboB()
{
	// TODO: Add your control notification handler code here
}

void FlowWuhoudao::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
