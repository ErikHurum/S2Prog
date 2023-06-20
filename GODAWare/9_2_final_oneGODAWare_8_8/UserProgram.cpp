// UserProgram.cpp : implementation file
//

#include "stdafx.h"
#include "MicroPilot3.h"
#include "UserProgram.h"
#include "serial.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define PI 3.1415926
/////////////////////////////////////////////////////////////////////////////
// CUserProgram dialog
extern CMicroPilot3App theApp;
extern CString m_csLanguageTable[2][250];
extern int  m_nLanguageTable;
extern int  m_nSensorCnt;  //当前探头号	
extern int  m_nLanguageTable;
extern CSerial   *cSerial;
extern unsigned char m_ComDataIn[],m_ComDataOut[];
extern int m_InLen,m_OutLen, m_bStop, m_DataReady;
extern int  m_nSensorCnt;  //当前探头号
extern int timeout, trytimes;
extern int m_bInUse;
extern unsigned char m_nVesselType;
extern CString Instrument;
const int DlgItemLin[33] = {IDC_EDIT1, IDC_EDIT2, IDC_EDIT3, IDC_EDIT4, 
IDC_EDIT5, IDC_EDIT6, IDC_EDIT7, IDC_EDIT8, IDC_EDIT9, IDC_EDIT10, IDC_EDIT11, 
IDC_EDIT23, IDC_EDIT24, IDC_EDIT25, IDC_EDIT26, IDC_EDIT27, IDC_EDIT28,
IDC_EDIT29, IDC_EDIT30, IDC_EDIT31, IDC_EDIT32, IDC_EDIT33, IDC_EDIT45, 
IDC_EDIT46, IDC_EDIT47, IDC_EDIT48, IDC_EDIT49,IDC_EDIT50, IDC_EDIT51, 
IDC_EDIT52, IDC_EDIT53, IDC_EDIT54, IDC_EDIT55};

const int DlgItemVal[33] = {IDC_EDIT12, IDC_EDIT13, IDC_EDIT14,
IDC_EDIT15, IDC_EDIT16, IDC_EDIT17, IDC_EDIT18, IDC_EDIT19, IDC_EDIT20, IDC_EDIT21,
IDC_EDIT22, IDC_EDIT34, IDC_EDIT35, IDC_EDIT36, IDC_EDIT37, IDC_EDIT38, IDC_EDIT39, 
IDC_EDIT40, IDC_EDIT41, IDC_EDIT42, IDC_EDIT43, IDC_EDIT44, IDC_EDIT56, IDC_EDIT57, 
IDC_EDIT58, IDC_EDIT59, IDC_EDIT60, IDC_EDIT61, IDC_EDIT62, IDC_EDIT63, IDC_EDIT64, 
IDC_EDIT65, IDC_EDIT66};

float DlgItemLinNo[33];
float DlgItemValNo[33];
float MAP[3][66];

CUserProgram::CUserProgram(CWnd* pParent /*=NULL*/)
	: CDialog(CUserProgram::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserProgram)
	m_nSemi1 = 0.0;
	m_nSemi2 = 0.0;
	m_nSemi3 = 0.0;
	m_nL1 = 0.0;
	m_nL3 = 0.0;
	m_nD = 0.0;
	//}}AFX_DATA_INIT
}


void CUserProgram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserProgram)
	DDX_Control(pDX, IDC_COMBO3, m_cType);
	DDX_Control(pDX, IDC_COMBO4, m_cUnit);
	DDX_Control(pDX, IDC_PROGRESS1, m_cProgress);
	DDX_Text(pDX, IDC_EDIT70, m_nSemi1);
	DDX_Text(pDX, IDC_EDIT72, m_nSemi2);
	DDX_Text(pDX, IDC_EDIT74, m_nSemi3);
	DDX_Text(pDX, IDC_EDIT67, m_nL1);
	DDX_Text(pDX, IDC_EDIT73, m_nL3);
	DDX_Text(pDX, IDC_EDIT81, m_nD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserProgram, CDialog)
	//{{AFX_MSG_MAP(CUserProgram)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDOK2, OnLoad)
	ON_WM_TIMER()
	ON_WM_CAPTURECHANGED()
	ON_BN_CLICKED(IDC_BUTTON1, OnStop)
	ON_BN_CLICKED(IDC_BUTTON2, OnCreateLin)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButtonZero)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserProgram message handlers

BOOL CUserProgram::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
	CString csEditNo;
	memset(DlgItemLinNo, 0, 33*4);
	memset(DlgItemValNo, 0, 33*4);		
	theApp.SetDialogColor(0);
	m_nTimer = SetTimer(1, 100, 0);
	OnChgLanguage();
	switch(m_nVesselType)
	{
		case 1:
			GetDlgItem(IDC_EDIT67)->EnableWindow(true);
			GetDlgItem(IDC_EDIT70)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT81)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
			this->SetWindowText(m_csLanguageTable[m_nLanguageTable][35]);
			break;
		case 2:
			GetDlgItem(IDC_EDIT72)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
			this->SetWindowText(m_csLanguageTable[m_nLanguageTable][35]);	
			break;
		case 3:
			GetDlgItem(IDC_EDIT73)->EnableWindow(true);
			GetDlgItem(IDC_EDIT74)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
			this->SetWindowText(m_csLanguageTable[m_nLanguageTable][35]);	
			break;
	}
//	UpdateData(false);
	if(m_nVesselType != 4)
	{
		GetDlgItem(IDC_COMBO3)->EnableWindow(false);		
		for(int i = 0; i < 33; i++)
		{
			DlgItemValNo[i] = (float)(i * 3.125);
			DlgItemLinNo[i] = (float)(i * 3.125);
			csEditNo.Format("%2.3f", DlgItemLinNo[i]);
			GetDlgItem(DlgItemLin[i])->SetWindowText(csEditNo);
			csEditNo.Format("%2.3f", DlgItemValNo[i]);
			GetDlgItem(DlgItemVal[i])->SetWindowText(csEditNo);
		}			
	}	
	m_cType.SetCurSel(3);
	m_nP006 = 0;
//	m_bInUse = 1; //占用串口,防止headline窗口调用串口
	OnSelchangeCombo3();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserProgram::OnCancelMode() 
{
	CDialog::OnCancelMode();		
}

void CUserProgram::OnOK() 
{
	// TODO: Add extra validation here
	CString csEditNo;
	float fTemp;
	unsigned char nTemp;
	int customNum = 0;
	if(!cSerial->IsOpened())
	{
		if(!m_nLanguageTable)
			AfxMessageBox("串口未打开!");
		else
			myMessageBox("COM do not open!");
		return;
	}	 
	if(m_bInUse)
	{
		if(!m_nLanguageTable)		
			AfxMessageBox("串口正在使用!");
		else
			myMessageBox("COM be in used!");
		return;
	}
	GetDlgItem(IDOK2)->EnableWindow(false);
	GetDlgItem(IDOK)->EnableWindow(false);
//	SetCursor(::LoadCursor(NULL, IDC_WAIT));
	m_cProgress.SetRange(0,100);
	m_cProgress.SetPos(0);
	UpdateData(true);
	GetDlgItem(DlgItemLin[32])->GetWindowText(csEditNo);
//	if(atof(csEditNo)>0)
	m_nTotalV = (float)atof(csEditNo);
	GetDlgItem(DlgItemVal[32])->GetWindowText(csEditNo);
	fTemp = (float)atof(csEditNo);	
	memset(DlgItemLinNo, 0, 33*4);
	memset(DlgItemValNo, 0, 33*4);
	for(int i = 1, j = 1; i < 33; i++)
	{
		for(; j < 33;j++)
		{
			GetDlgItem(DlgItemLin[j])->GetWindowText(csEditNo);
			if(csEditNo == "")
			   continue;
			DlgItemLinNo[i] = (float)atof(csEditNo);
			if(DlgItemLinNo[i] > m_nTotalV || !DlgItemLinNo[i])
				continue;
			GetDlgItem(DlgItemVal[j])->GetWindowText(csEditNo);
			if(csEditNo == "")
			   continue;			
			DlgItemValNo[i] = (float)atof(csEditNo);
			if(DlgItemValNo[i] > fTemp || !DlgItemValNo[i])
				continue;
			j++;
			break;
		}
		if(j == 33)
			break;
	}
	//对于自定义映射，判断最大值
	if(m_nVesselType == 4)
	{
		customNum = i + 1;
		for(i = 0; i < customNum - 1; i++)
		{
			if(DlgItemValNo[i] > DlgItemValNo[i+1])
			{
				fTemp = DlgItemValNo[i];
				DlgItemValNo[i] = DlgItemValNo[i+1];
				DlgItemValNo[i+1] = fTemp;

				fTemp = DlgItemLinNo[i];
				DlgItemLinNo[i] = DlgItemLinNo[i+1];
				DlgItemLinNo[i+1] = fTemp;				
				if(i > 3)
				{
					for(int j = 0; j < i; j++)
					{
						if(DlgItemValNo[i] < DlgItemValNo[j])
						{
							fTemp = DlgItemLinNo[i];
							for(int k = i; k > j; k--)
								DlgItemLinNo[k] = DlgItemLinNo[k - 1];
							DlgItemLinNo[j] = fTemp;

							fTemp = DlgItemValNo[i];
							for(k = i; k > j; k--)
								DlgItemValNo[k] = DlgItemValNo[k - 1];
							DlgItemValNo[j] = fTemp;
							break;
						}
					}
				}
			}
		}
		for(i = 0; i < customNum - 1; i++)
		{
			if(DlgItemLinNo[i] >= DlgItemLinNo[i+1])
			{
				GetDlgItem(IDOK2)->EnableWindow(true);
				GetDlgItem(IDOK)->EnableWindow(true);
				memset(DlgItemLinNo, 0, 33*4);
				memset(DlgItemValNo, 0, 33*4);
				if(!m_nLanguageTable)
					AfxMessageBox("映射关系错误，请确认!");
				else
					myMessageBox("Lin error");
				return;
			}
		}
	/*	for(i = 0; i < customNum - 1; i++)
		{
			if(DlgItemValNo[i] > DlgItemValNo[i+1])
			{
				fTemp = DlgItemValNo[i];
				DlgItemValNo[i] = DlgItemValNo[i+1];
				DlgItemValNo[i+1] = fTemp;
				if(i > 3)
				{
					for(int j = 0; j < i; j++)
					{
						if(DlgItemValNo[i] < DlgItemValNo[j])
						{
							fTemp = DlgItemValNo[i];
							for(int k = i; k > j; k--)
								DlgItemValNo[k] = DlgItemValNo[k - 1];
							DlgItemValNo[j] = fTemp;
							break;
						}
					}
				}
			}

		}
		*/
	}
	if(!m_nTotalV||!m_nP006)
	{
		GetDlgItem(IDOK2)->EnableWindow(true);
		GetDlgItem(IDOK)->EnableWindow(true);
		memset(DlgItemLinNo, 0, 33*4);
		memset(DlgItemValNo, 0, 33*4);
		if(!m_nLanguageTable)
			AfxMessageBox("参数错误：最大料高或映射量为0");
		else
			myMessageBox("Parameter error：Max.Height or Max.Lin is zero");
		return;
	}
	this->EnableWindow(false);
	for(i = 0; i < 33; i++)
	{
		DlgItemLinNo[i]/=m_nTotalV;	
		DlgItemValNo[i]/=m_nP006;
	}
	
	memcpy((unsigned char*)&MAP[m_nSensorCnt] , (unsigned char*)&DlgItemValNo, 33*4);
	memcpy((unsigned char*)&MAP[m_nSensorCnt]+ 33*4, (unsigned char*)&DlgItemLinNo, 33*4);
	nTemp = m_nVesselType + 1;						
	cSerial->PcToDevice(0x010, (unsigned char*)&nTemp, 1, m_nSensorCnt);	
	cSerial->PcToDevice(0x018, (unsigned char*)&nTemp, 1, m_nSensorCnt);	
	m_cProgress.SetPos(10);	

//	cSerial->PcToDevice(0x0114, (unsigned char*)&m_nZeroLin, 4, m_nSensorCnt);
//	cSerial->PcToDevice(0x0117, (unsigned char*)&m_nZeroLin, 4, m_nSensorCnt);
	cSerial->PcToDevice(0x0115, (unsigned char*)&m_nTotalV, 4, m_nSensorCnt);
	cSerial->PcToDevice(0x0118, (unsigned char*)&m_nTotalV, 4, m_nSensorCnt);
	if(m_nTotalV > 10000.0)
		nTemp = 0;
	else if(m_nTotalV > 1000.0)
			nTemp = 1;
	else if(m_nTotalV > 100.0)
			nTemp = 2;
	else
			nTemp = 3;
	cSerial->PcToDevice(0x0116, (unsigned char*)&nTemp, 1, m_nSensorCnt);
	cSerial->PcToDevice(0x0119, (unsigned char*)&nTemp, 1, m_nSensorCnt);
	m_cProgress.SetPos(20);	
	if(m_nPrevType != m_cType.GetCurSel())
	{
		nTemp = m_cType.GetCurSel() + 1;
		cSerial->PcToDevice(0x0012, &nTemp, 1, m_nSensorCnt);
		cSerial->PcToDevice(0x0312, &nTemp, 1, m_nSensorCnt);
	}
	m_cProgress.SetPos(30);
	if(m_nPrevUnit != m_cUnit.GetCurSel())
	{
		nTemp = m_cUnit.GetCurSel() + 1;		
		cSerial->PcToDevice(0x0013, &nTemp, 1, m_nSensorCnt);
		cSerial->PcToDevice(0x0313, &nTemp, 1, m_nSensorCnt);
	}
	m_cProgress.SetPos(40);	
	m_nPrevType = m_cType.GetCurSel();
	m_nPrevUnit = m_cUnit.GetCurSel();
	cSerial->PcToDevice(0x0994, (unsigned char*)&MAP[m_nSensorCnt], 66*4, m_nSensorCnt);
	m_cProgress.SetPos(100);
	m_cProgress.SetPos(0);
//	m_nDealOK = 1;
	GetDlgItem(IDOK2)->EnableWindow(true);
	GetDlgItem(IDOK)->EnableWindow(true);
//	SetCursor(::LoadCursor(NULL, IDC_ARROW));
	this->EnableWindow(true);
}

void CUserProgram::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(DlgItemLinNo[32] > 1 && DlgItemValNo[32] > 1){
		for(int i = 0; i < 33; i++)
		{
			DlgItemLinNo[i] /= DlgItemLinNo[32];	
			DlgItemValNo[i] /= DlgItemValNo[32];
		}
	}
//	m_bInUse = 0; //释放串口
	theApp.SetDialogColor(1);
	CDialog::OnCancel();
}

void CUserProgram::OnLoad() 
{
	// TODO: Add your control notification handler code here

	if(!cSerial->IsOpened())
	{
		if(!m_nLanguageTable)
			AfxMessageBox("串口未打开!");
		else
			myMessageBox("COM do not open!");
		return;
	}	
	if(m_bInUse)
	{
		if(!m_nLanguageTable)		
			AfxMessageBox("串口正在使用!");
		else
			myMessageBox("COM be in used!");
		return;
	}
	this->EnableWindow(false);
//	SetCursor(::LoadCursor(NULL, IDC_WAIT));
	GetDlgItem(IDOK2)->EnableWindow(false);
	GetDlgItem(IDOK)->EnableWindow(false);	
	GetDlgItem(IDCANCEL)->EnableWindow(false);	
	GetDlgItem(IDC_COMBO4)->EnableWindow(false);	
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);	
	
//	m_cProgress.SetRange(0,100);
	//m_cProgress.SetPos(0);
	OnLoadData();
//	m_cProgress.SetPos(100);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);		
	GetDlgItem(IDC_COMBO4)->EnableWindow(true);	
	GetDlgItem(IDCANCEL)->EnableWindow(true);	
	GetDlgItem(IDOK2)->EnableWindow(true);
	GetDlgItem(IDOK)->EnableWindow(true);
	if(m_nVesselType == 4)
		GetDlgItem(IDC_BUTTON2)->EnableWindow(false);	
//	SetCursor(::LoadCursor(NULL, IDC_ARROW));
	this->EnableWindow(true);
}

void CUserProgram::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(m_nTimer);
	OnLoad();
	CDialog::OnTimer(nIDEvent);
}

void CUserProgram::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	CDialog::OnCaptureChanged(pWnd);
}

void CUserProgram::OnStop() 
{
	// TODO: Add your control notification handler code here
	m_bStop = 1;
	m_bInUse = 0;	
}

void CUserProgram::OnCreateLin() 
{
	// TODO: Add your control notification handler code here
    int i;
	CString csEditNo;
	UpdateData(true);
	memset(DlgItemLinNo, 0, 33*4);
	memset(DlgItemValNo, 0, 33*4);
	if(!m_nP006)
	{
		if(cSerial->DeviceToPc(0x0110, m_nSensorCnt))
			memcpy((unsigned char*)&m_nP110, m_ComDataIn + 9, 4);
		else
		{	
			//AfxMessageBox("读取参数P110失败!");
			return;
		}
		if(cSerial->DeviceToPc(0x0111, m_nSensorCnt))
			memcpy((unsigned char*)&m_nP111, m_ComDataIn + 9, 4);
		else
		{	
		//	AfxMessageBox("读取参数P111失败!");
			return;
		}
		if(cSerial->DeviceToPc(0x0112, m_nSensorCnt))
			memcpy((unsigned char*)&m_nP112, m_ComDataIn + 9, 4);
		else
		{	
		//	AfxMessageBox("读取参数P112失败!");
			return;
		}
		if(cSerial->DeviceToPc(0x0113, m_nSensorCnt))
			memcpy((unsigned char*)&m_nP113, m_ComDataIn + 9, 4);
		else
		{	
		//	AfxMessageBox("读取参数P113失败!");
			return;
		}
	}	
	m_nP007=(m_nP111-m_nP113)/(m_nP112-m_nP110);
	m_nP006 = m_nP007;
	if(!m_nP006)
	{
		if(!m_nLanguageTable)
			AfxMessageBox("参数错误, 最高料位读取错误，请重新读取!");
		else
			myMessageBox("Parameter error, Max.height error!");
		return;
	}
   	switch(m_nVesselType)
	{
		case 1:
			if(!m_nSemi1||!m_nL1)
			{
				if(!m_nLanguageTable)
					AfxMessageBox("参数不能为零!");
				else
					myMessageBox("Parameter never be zero!");
				return;
			}
			if(m_nSemi1 < m_nP006)
			{
				AfxMessageBox("圆筒直径设置错误!");
				return;
			}
			/*
			m_nTotalV = (float)(1/3.0*PI*pow(m_nP006, 2.0)*(3.0*m_nSemi1 - m_nP006) 
			+ (pow(m_nSemi1, 2.0)*(1.0/(cos((m_nSemi1-m_nP006)/m_nSemi1)))
			- ((m_nSemi1-m_nP006)*sqrt(2.0*m_nSemi1*m_nP006-pow(m_nP006,2.0))))*m_nL1);
			*/
			if(m_nSemi1/2>=m_nP006)
			{
				m_nTotalV=PI*pow(m_nSemi1/2,2)*m_nL1;
				m_nTotalV=acos((m_nSemi1/2-m_nP006)/(m_nSemi1/2))/PI*m_nTotalV;
				m_nTotalV=m_nTotalV-(m_nSemi1/2-m_nP006)*sqrt(m_nSemi1*m_nP006-pow(m_nP006,2))*m_nL1;
			}
			else
			{
				m_nTotalV=PI*pow(m_nSemi1/2,2)*m_nL1;
				m_nTotalV=(PI-acos((m_nP006-m_nSemi1/2)/(m_nSemi1/2)))/PI*m_nTotalV;
				m_nTotalV=m_nTotalV+(m_nP006-m_nSemi1/2)*sqrt(pow(m_nSemi1/2,2)-pow((m_nP006-m_nSemi1/2),2))*m_nL1;
			}

			DlgItemValNo[0] = DlgItemLinNo[0] = 0.0;	
			for(i = 1; i < 33; i++)
			{
				DlgItemValNo[i] = (float)(i * 0.03125*m_nP006);
				/*
				DlgItemLinNo[i] = (float)(1/3.0*PI*pow(DlgItemValNo[i], 2.0)*(3.0*m_nSemi1 - DlgItemValNo[i]) 
				+ (pow(m_nSemi1, 2.0)*(1.0/(cos((m_nSemi1-DlgItemValNo[i])/m_nSemi1)))
				- ((m_nSemi1-DlgItemValNo[i])*sqrt(2.0*m_nSemi1*DlgItemValNo[i]-pow(DlgItemValNo[i],2.0))))*m_nL1 - m_nD/10.0);
				*/
				if(DlgItemValNo[i]<=m_nSemi1/2)
				{
					DlgItemLinNo[i]=PI*pow(m_nSemi1/2,2)*m_nL1;
					DlgItemLinNo[i]=acos((m_nSemi1/2-DlgItemValNo[i])/(m_nSemi1/2))/PI*DlgItemLinNo[i];
					DlgItemLinNo[i]=DlgItemLinNo[i]-(m_nSemi1/2-DlgItemValNo[i])*sqrt(m_nSemi1*DlgItemValNo[i]-pow(DlgItemValNo[i],2))*m_nL1;
				}
				else
				{
					DlgItemLinNo[i]=PI*pow(m_nSemi1/2,2)*m_nL1;
					DlgItemLinNo[i]=(PI-acos((DlgItemValNo[i]-m_nSemi1/2)/(m_nSemi1/2)))/PI*DlgItemLinNo[i];
					DlgItemLinNo[i]=DlgItemLinNo[i]+(DlgItemValNo[i]-m_nSemi1/2)*sqrt(pow(m_nSemi1/2,2)-pow((DlgItemValNo[i]-m_nSemi1/2),2))*m_nL1;
				}
			
			}	
			break;
		case 2:
			if(!m_nSemi2)
			{
				if(!m_nLanguageTable)
					AfxMessageBox("参数不能为零!");
				else
					myMessageBox("Parameter never be zero!");
				return;
			}
			if(2*m_nSemi2 < m_nP006)
			{
				if(!m_nLanguageTable)
					AfxMessageBox("半径设置错误:容器直径应该大于最大料位!");
				else
					myMessageBox("Parameter error!");
				return;
			}
			m_nTotalV = (float)(1/3.0*PI*pow(m_nP006,2.0)*(3.0*m_nSemi2 - m_nP006));
			DlgItemValNo[0] = DlgItemLinNo[0] = 0.0;
			for(i = 1; i < 33; i++)
			{
				DlgItemValNo[i] = (float)(i * 0.03125*m_nP006);
				DlgItemLinNo[i] = (float)(1/3.0*PI*pow(DlgItemValNo[i],2.0)*(3.0*m_nSemi2 - DlgItemValNo[i]));
			}	
			break;
		case 3:
			if(!m_nSemi3||!m_nL3)
			{
				if(!m_nLanguageTable)
					AfxMessageBox("参数不能为零!");
				else
					myMessageBox("Parameter never be zero!");
				return;
			}
			if(m_nP006 < m_nL3 )
				m_nTotalV = (float)(1/3.0*PI*pow(m_nSemi3,2.0)*m_nP006);
			else
				m_nTotalV = (float)(1/3.0*PI*pow(m_nSemi3,2.0)*m_nL3 + PI*pow(m_nSemi3,2.0)*(m_nP006 - m_nL3));
			DlgItemValNo[0] = DlgItemLinNo[0] = 0.0;
			for(i = 1; i < 33; i++)
			{
				DlgItemValNo[i] = (float)(i * 0.03125*m_nP006);
				if(DlgItemValNo[i] < m_nL3 )
					DlgItemLinNo[i] = (float)(1/3.0*PI*pow(m_nSemi3,2.0)*DlgItemValNo[i]);
				else
					DlgItemLinNo[i] = (float)(1/3.0*PI*pow(m_nSemi3,2.0)*m_nL3 + PI*pow(m_nSemi3,2.0)*(DlgItemValNo[i] - m_nL3));
			}	
			break;
	}	
	switch(m_cUnit.GetCurSel())//    m3=>other
	{
		case 0:break;			// m3
		case 1:m_nTotalV*=1000;break;//l		
		case 2:m_nTotalV*=10;break;//hl
		case 3:m_nTotalV *= 35.315;break;	// ft3
		case 4:	m_nTotalV *= (35.315*1728);break;	// in3
		case 5:m_nTotalV /=3.785;m_nTotalV *=1000; break;		// gal/h  "使用 美加仑3.785   英加仑为4.546"		
	}
	for(i = 0; i < 33; i++)
	{
		switch(m_cUnit.GetCurSel())//    m3=>other
		{
			case 0:break;			// m3
			case 1:DlgItemLinNo[i]*=1000;break;//l		
			case 2:DlgItemLinNo[i]*=10;break;//hl
			case 3:DlgItemLinNo[i] *= 35.315;break;	// ft3
			case 4:	DlgItemLinNo[i] *= (35.315*1728);break;	// in3
			case 5:DlgItemLinNo[i] /=3.785;DlgItemLinNo[i] *=1000; break;		// gal/h  "使用 美加仑3.785   英加仑为4.546"		
		}
		csEditNo.Format("%2.3f", DlgItemLinNo[i]);
		GetDlgItem(DlgItemLin[i])->SetWindowText(csEditNo);
		csEditNo.Format("%2.3f", DlgItemValNo[i]);
		GetDlgItem(DlgItemVal[i])->SetWindowText(csEditNo);
	}
}

void CUserProgram::OnSelchangeCombo3() 
{
	int nType;
	nType = m_cType.GetCurSel();
	m_cUnit.ResetContent();
	switch(nType)
	{
	case 0:
		m_cUnit.InsertString(0,"m");	
		m_cUnit.InsertString(1,"ft");	
		m_cUnit.InsertString(2,"in");	
		m_cUnit.InsertString(3,"cm");	
		m_cUnit.InsertString(4,"mm");	
		break;
	case 1:
		m_cUnit.InsertString(0,"kg");	
		m_cUnit.InsertString(1,"t");	
		m_cUnit.InsertString(2,"lb");	
		break;
	case 2:
		m_cUnit.InsertString(0,"m3/s");	
		m_cUnit.InsertString(1,"m3/h");	
		m_cUnit.InsertString(2,"ft3/s");	
		m_cUnit.InsertString(3,"ft3/min");	
		m_cUnit.InsertString(4,"gal/s");	
		m_cUnit.InsertString(5,"gal/min");			
		m_cUnit.InsertString(6,"gal/h");			
		m_cUnit.InsertString(7,"l/s");			
		m_cUnit.InsertString(8,"l/min");			
		m_cUnit.InsertString(9,"l/h");			
		break;	   						
	case 3:
		m_cUnit.InsertString(0,"m3");	
		m_cUnit.InsertString(1,"l");//升	
		m_cUnit.InsertString(2,"hl");//百升	
		m_cUnit.InsertString(3,"ft3");	
		m_cUnit.InsertString(4,"in3");	
		m_cUnit.InsertString(5,"gal");//使用 美加仑3.785 	
		break;
	}
	m_cUnit.SetCurSel(0);	
}
void CUserProgram::OnLoadData() 
{
	m_cProgress.SetRange(0,66*4 + 50);
	m_cProgress.SetPos(0);
	m_bStop = 0;
	if(!m_bStop&&cSerial->DeviceToPc(0x0115, m_nSensorCnt))
		memcpy((unsigned char*)&m_nTotalV, m_ComDataIn + 9, 4);
	else
	{
		m_cProgress.SetPos(0);
		return;	
	}
/*	if(cSerial->DeviceToPc(0x0114, m_nSensorCnt))
		memcpy((unsigned char*)&m_nZeroLin, m_ComDataIn + 9, 4);
	else
	{
		m_cProgress.SetPos(0);
		return;	
	}
*/	m_cProgress.SetPos(10);
	if(!m_bStop&&cSerial->DeviceToPc(0x0013, m_nSensorCnt))
		m_cUnit.SetCurSel(m_ComDataIn[9] - 1);	
	m_cProgress.SetPos(30);
	if(!m_bStop&&cSerial->DeviceToPc(0x0110, m_nSensorCnt))
		memcpy((unsigned char*)&m_nP110, m_ComDataIn + 9, 4);
	else
	{
		m_cProgress.SetPos(0);
		return;
	}
	if(!m_bStop&&cSerial->DeviceToPc(0x0111, m_nSensorCnt))
		memcpy((unsigned char*)&m_nP111, m_ComDataIn + 9, 4);
	else
	{
		m_cProgress.SetPos(0);		
		return;
	}
	m_cProgress.SetPos(40);
	if(!m_bStop&&cSerial->DeviceToPc(0x0112, m_nSensorCnt))
		memcpy((unsigned char*)&m_nP112, m_ComDataIn + 9, 4);
	else
	{
		m_cProgress.SetPos(0);		
		return;
	}
	if(!m_bStop&&cSerial->DeviceToPc(0x0113, m_nSensorCnt))
		memcpy((unsigned char*)&m_nP113, m_ComDataIn + 9, 4);
	else
	{
		m_cProgress.SetPos(0);		
		return;
	}
	if(!m_bStop&&cSerial->DeviceToPc(0x0012, m_nSensorCnt))
	{
		if(m_nVesselType != 4 && (m_ComDataIn[9] - 1) == 2)
		{
			m_cProgress.SetPos(0);
			return;
		}
	}
	m_cProgress.SetPos(50);
	m_nP007=(m_nP111-m_nP113)/(m_nP112-m_nP110);
	m_nP006 = m_nP007;	
	/*if(m_nVesselType == 5)
	{
		CString csEditNo1;
		csEditNo1.Format("0.00");
		GetDlgItem(DlgItemLin[0])->SetWindowText(csEditNo1);
		GetDlgItem(DlgItemLin[32])->SetWindowText(csEditNo1);
		GetDlgItem(DlgItemVal[0])->SetWindowText(csEditNo1);
		csEditNo1.Format("%2.2f", m_nP006);
		GetDlgItem(DlgItemVal[32])->SetWindowText(csEditNo1);
		m_cProgress.SetPos(66*4+50);
		return;
	}*/
	UpdateData(false);
	m_nPrevType = m_cType.GetCurSel();
	m_nPrevUnit = m_cUnit.GetCurSel();
	int funcID = 0x994;
	unsigned char nCheckSum = 0x0;
	unsigned char nCheckCnt = 0x0;
	
	int nYvalue = 0;
	CString csEditNo;
	m_bStop = 0;	
	m_bInUse = 1;
	m_OutLen=10;
	m_ComDataOut[0]=0xfe;
	m_ComDataOut[1]='G';
	m_ComDataOut[2]=m_OutLen & 0xff;
	m_ComDataOut[3]=0;// p_len
	m_ComDataOut[4]=atoi(Instrument)&0xff;// instrument ID
	m_ComDataOut[5]=(m_ComDataOut[0]+m_ComDataOut[1]+m_ComDataOut[2]+
		m_ComDataOut[3]+m_ComDataOut[4])&0xff;
	m_ComDataOut[6] = (m_nSensorCnt) & 0xff;//sensor ID
	m_ComDataOut[7]=funcID & 0xff;//funcID
	m_ComDataOut[8]=(funcID>>8)&0xff;
	int sum,i;
	sum=0;
	for(i=0;i<m_OutLen-1;i++)sum+=m_ComDataOut[i];//notice:count m_outlen-1 byte
	m_ComDataOut[m_OutLen-1]=sum&0xff;
	// send data

	for(int k=0; k<=trytimes; k++)//try times alltogether
	{
		cSerial->ReadData(m_ComDataIn, INBUFLEN);
		memset(m_ComDataIn, 0 ,INBUFLEN);
        cSerial->SendData(m_ComDataOut, m_OutLen);
		_sleep(150);
        m_DataReady = 0;
		CTime t=CTime::GetCurrentTime();
		time_t t0=t.GetTime();
		MSG msg;
		while(m_DataReady < 274&&!m_bStop)//poll receive_ok mark
		{
			m_DataReady = cSerial->ReadDataWaiting();
			if(::PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			m_cProgress.SetPos(m_DataReady + 50);			
			t=CTime::GetCurrentTime();
			time_t t1=t.GetTime();
			if( (t1-t0) >= 10)//time_out second
				break;	
		}
		if(m_bStop)
		{
			if(!m_nLanguageTable)
				AfxMessageBox("用户中断!");
			else
				myMessageBox("User pause!");
			m_cProgress.SetPos(0);
			m_bInUse = 0;  
			return;
		}
		m_InLen = cSerial->ReadData(m_ComDataIn, INBUFLEN);	    
		if(m_InLen == 274)
		{
		   
		   for(i = 0; i < m_InLen - 1; i++)
			   nCheckSum += m_ComDataIn[i];
		   if(nCheckSum != m_ComDataIn[m_InLen - 1])      
		   {
				nCheckCnt ++;
				continue;
		   }		  
		   if(m_ComDataIn[1] == 'G')//receive right value
		   {
				memcpy((unsigned char*)&DlgItemLinNo, m_ComDataIn + 9, 33*4);
				memcpy((unsigned char*)&DlgItemValNo, m_ComDataIn + 9 + 33*4, 33*4);	
			    for(int i = 0; i < 33; i++)
				{
					if(DlgItemLinNo[i] == 1)
					{
						DlgItemLinNo[i] = 0;
						DlgItemValNo[i] = 0;
					}
					csEditNo.Format("%2.3f", DlgItemLinNo[i]*m_nTotalV);
					GetDlgItem(DlgItemLin[i])->SetWindowText(csEditNo);
					csEditNo.Format("%2.3f", DlgItemValNo[i]*m_nP006);
					GetDlgItem(DlgItemVal[i])->SetWindowText(csEditNo);
				}
				DlgItemLinNo[32] = 1;
				DlgItemValNo[32] = 1;
				csEditNo.Format("%2.3f", m_nTotalV);
				GetDlgItem(DlgItemLin[32])->SetWindowText(csEditNo);
				csEditNo.Format("%2.3f", m_nP006);
				GetDlgItem(DlgItemVal[32])->SetWindowText(csEditNo);
   				m_bInUse = 0;  			
				return;
		   }
		}
	}//end for
	m_bInUse = 0;
	if(nCheckCnt == trytimes)
	{
		 if(!m_nLanguageTable)			
				AfxMessageBox("读取参数 '输出映射数据' 错误：校验错误!",MB_OK);
			else
				myMessageBox("Load 'Lin.Data' error: check error!");
	}
	else
	{
		 if(!m_nLanguageTable)			
			AfxMessageBox("读取参数 '输出映射数据' 错误：超时!",MB_OK);
		else
			myMessageBox("Load 'Lin.Data' error: overtime!");
	}
}

void CUserProgram::OnButtonZero() 
{
	// TODO: Add your control notification handler code here
	CString csEditNo1;
	for(int i = 0; i < 32; i++)
	{
		csEditNo1.Format("");
		GetDlgItem(DlgItemLin[i])->SetWindowText(csEditNo1);
		GetDlgItem(DlgItemVal[i])->SetWindowText(csEditNo1);
		DlgItemLinNo[i] = 0;
		DlgItemValNo[i] = 0;
	}	
	csEditNo1.Format("0.00");
	GetDlgItem(DlgItemLin[0])->SetWindowText(csEditNo1);
//	GetDlgItem(DlgItemLin[32])->SetWindowText(csEditNo1);	
	GetDlgItem(DlgItemVal[0])->SetWindowText(csEditNo1);
	csEditNo1.Format("%2.2f", m_nP006);
	GetDlgItem(DlgItemVal[32])->SetWindowText(csEditNo1);
}

void CUserProgram::OnChgLanguage()
{
	this->SetWindowText(m_csLanguageTable[m_nLanguageTable][34]);
	GetDlgItem(IDC_STATIC8)->SetWindowText(m_csLanguageTable[m_nLanguageTable][24]);
	GetDlgItem(IDC_STATIC3)->SetWindowText(m_csLanguageTable[m_nLanguageTable][40]);
	GetDlgItem(IDC_STATIC4)->SetWindowText(m_csLanguageTable[m_nLanguageTable][41]);
	GetDlgItem(IDC_STATIC5)->SetWindowText(m_csLanguageTable[m_nLanguageTable][31]);
	GetDlgItem(IDC_STATIC6)->SetWindowText(m_csLanguageTable[m_nLanguageTable][32]);
	GetDlgItem(IDC_STATIC7)->SetWindowText(m_csLanguageTable[m_nLanguageTable][27]);
	GetDlgItem(IDC_STATIC9)->SetWindowText(m_csLanguageTable[m_nLanguageTable][CONTROLNUM_MAINVIEW+4]);
	GetDlgItem(IDC_STATIC10)->SetWindowText(m_csLanguageTable[m_nLanguageTable][50]);
	GetDlgItem(IDC_STATIC12)->SetWindowText(m_csLanguageTable[m_nLanguageTable][50]);
	
	if(!m_nLanguageTable)
	{
		GetDlgItem(IDC_STATIC11)->SetWindowText("映射量");	
		GetDlgItem(IDC_STATIC13)->SetWindowText("映射量");	
		GetDlgItem(IDC_BUTTON2)->SetWindowText("参数生成");
		GetDlgItem(IDC_BUTTON4)->SetWindowText("参数置零");
		GetDlgItem(IDC_MAXHEIGH)->SetWindowText("L : 最大料高");
		this->SetWindowText("用户管理");
	}
	else
	{
		GetDlgItem(IDC_BUTTON2)->SetWindowText("Create new");
		GetDlgItem(IDC_BUTTON4)->SetWindowText("Set zero");
		GetDlgItem(IDC_STATIC11)->SetWindowText("Lin.value");
		GetDlgItem(IDC_STATIC13)->SetWindowText("Lin.value");
		GetDlgItem(IDC_MAXHEIGH)->SetWindowText("L : Max.Height");
		this->SetWindowText("User Managerment");
	}
	GetDlgItem(IDOK2)->SetWindowText(m_csLanguageTable[m_nLanguageTable][107]);
	GetDlgItem(IDOK)->SetWindowText(m_csLanguageTable[m_nLanguageTable][106]);
	GetDlgItem(IDC_BUTTON1)->SetWindowText(m_csLanguageTable[m_nLanguageTable][63]);
	GetDlgItem(IDCANCEL)->SetWindowText(m_csLanguageTable[m_nLanguageTable][DIALOG_HARTDEAL+8]);
	
	m_cType.InsertString(0,m_csLanguageTable[m_nLanguageTable][45]);
	m_cType.InsertString(1,m_csLanguageTable[m_nLanguageTable][46]);
	m_cType.InsertString(2,m_csLanguageTable[m_nLanguageTable][47]);
	m_cType.InsertString(3,m_csLanguageTable[m_nLanguageTable][48]);
	m_cType.SetCurSel(0);
}

BOOL CUserProgram::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bInUse==1)
		SetCursor(::LoadCursor(NULL, IDC_WAIT));	
	else
		SetCursor(::LoadCursor(NULL, IDC_ARROW));	
	return true;
	//return CDialog::OnSetCursor(pWnd, nHitTest, message);
}
