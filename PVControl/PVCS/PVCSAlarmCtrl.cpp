// PVCSAlarmCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PVCSAlarmCtrl.h"
#include ".\pvcsalarmctrl.h"
#include "PvcsTankDlg.h"//JSD
#include "pvcsshipdata.h"
#include "PvcsAlarmObject.h"
#define MAXDIR 256
CString CPVCSAlarmCtrl::AckAlarmData="";
CListCtrl CPVCSAlarmCtrl::m_cList;
bool CPVCSAlarmCtrl::IsAlmDlgOpen=false;
int CPVCSAlarmCtrl::lastnoofitems=0;
bool CPVCSAlarmCtrl::blink=false;


// CPVCSAlarmCtrl dialog
CPVCSAlarmCtrl& thePVCSAlmCtrl()
{
	static CPVCSAlarmCtrl AlmCtrlObj;
	return AlmCtrlObj;
}

IMPLEMENT_DYNAMIC(CPVCSAlarmCtrl, CDialog)
CPVCSAlarmCtrl::CPVCSAlarmCtrl(CWnd* pParent /*=NULL*/)
: CDialog(CPVCSAlarmCtrl::IDD, pParent)

{
}

CPVCSAlarmCtrl::~CPVCSAlarmCtrl()
{
	delete ImagelistObj;
	ImagelistObj = NULL;
}

void CPVCSAlarmCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALARM_LIST, m_cList);
}


BEGIN_MESSAGE_MAP(CPVCSAlarmCtrl, CDialog)
ON_BN_CLICKED(IDC_OK, OnBnClickedOk)
ON_BN_CLICKED(IDC_ALARMACKNOW_BUTTON, OnBnClickedAlarmacknowButton)
ON_BN_CLICKED(IDC_SILENCEALARM_BUTTON, OnBnClickedSilencealarmButton)
ON_WM_TIMER()
ON_NOTIFY(NM_CUSTOMDRAW, IDC_ALARM_LIST, OnNMCustomdrawAlarmList)
END_MESSAGE_MAP()


// CPVCSAlarmCtrl message handlers

BOOL CPVCSAlarmCtrl::OnInitDialog()
{

	CDialog::OnInitDialog();
	SetTimer( IDD_ALARM_DLG, 2000, NULL );
//theShipData().FillAlarmData();
//theShipData().FillAckAlarmData();
    theShipData().Aquire();
	int count= theShipData().m_AlarmData.size();
	alarmcount = theShipData().m_AlarmData.size();
//int count=PvcsShipDataObj.m_AlarmData.size();
	BuildList();
	if ( count>0 ) {
		InsertAlaram(count);
	}
    theShipData().Release();

	return true;
}

void CPVCSAlarmCtrl::OnBnClickedOk()
{	//if()



//if(theShipData().m_AlarmData.size()!=0)
//	{
	KillTimer(IDD_ALARM_DLG);
	CPvcsTankDlg::AlmCtrlDlgClicked=0;
	IsAlmDlgOpen=false;
	m_cList.DeleteAllItems();
	m_cList.DestroyWindow();

//	}
	//delete m_cList;
	//ShowWindow(SW_HIDE);
	//thePVCSAlmCtrl().CloseWindow();
	EndDialog(1);
}
#pragma warning (disable: 4800)

void CPVCSAlarmCtrl::BuildList()
{
	CRect aa;
	aa.left = 10;
	aa.top = 10;
	aa.bottom = 200;
	aa.right=300;

	//m_cList.Create(0,aa,NULL,IDC_ALARM_LIST);
	m_cList.SetExtendedStyle( m_cList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |LVS_EX_FLATSB|LVS_EX_HEADERDRAGDROP|LVS_ICON| LVS_EDITLABELS|LVIF_IMAGE);


	ImagelistObj=new CImageList();
	ImagelistObj->Create(16, 16,ILC_COLOR8,0, 1);
	CBitmap *bm;
	bm=new  CBitmap();
	bool status;
	status=bm->LoadBitmap(IDB_BITMAP2);
	if ( bm->m_hObject )
		CString m;
	int j;
	j= ImagelistObj->Add (bm, RGB (0, 0, 0));
	m_cList.SetImageList(ImagelistObj, LVSIL_SMALL);

	delete bm;
	// determine the columns
//	m_cList.InsertColumn( 0, "Tank ID");//JSD 09-08-2007
	m_cList.InsertColumn( 0, "Tank Name");//JSD 22FEB2007
	m_cList.InsertColumn( 1, "Alarm Text");
	m_cList.InsertColumn( 2, "Limit");
	m_cList.InsertColumn( 3, "Current Value");
	m_cList.InsertColumn( 4, "Unit");
	m_cList.InsertColumn( 5, "Time Raised");
	m_cList.InsertColumn( 6,"Time Acknowledged");
	m_cList.InsertColumn( 7,"AlarmId");

	//m_cList.SetColumnWidth( 0, 30);
	m_cList.SetColumnWidth( 0, 80);
	m_cList.SetColumnWidth( 1, 70);
	m_cList.SetColumnWidth( 2, 100);
	m_cList.SetColumnWidth( 3, 100);
	m_cList.SetColumnWidth( 4, 45);
	m_cList.SetColumnWidth( 5, 100);
	m_cList.SetColumnWidth(6, 100);
	m_cList.SetColumnWidth(7, 0);


	// set functionality of list according to column
	//
	//m_cList.SetColumnType ( (fGetType)_List_Type );

	// insert string elements  for the ComboBox :
	//JSDfor ( int i=0 ; i < 2 ; i++)
	//JSD	m_cList.m_strList.AddTail( Product[i]);

	// insert a dummy row
/*	for (  i=1 ; i <= 10 ; i++)
	{
	InsertEmpty(i);
	}
*/
}
void CPVCSAlarmCtrl::OnBnClickedAlarmacknowButton()
{
	CString tankidforIPSText="";
	AckAlarmData="";
	CString Check;
	CString TankIdAlarm;
	CString soundStatus;
	Check=m_cList.GetItemText(0,6);
    theShipData().Aquire();
	if ( (theShipData().m_AlarmData.size()!=0)&& (Check=="") ) {
		static int SelectedItem=0;
		AlarmListStruct tempobj;
		AlarmDataStruct tempobjship;
		tankidforIPSText=tempobj.Tankid=m_cList.GetItemText(0,0);
		tempobj.TankName=m_cList.GetItemText(0,0);
		tempobj.AlarmText=m_cList.GetItemText(0,1);
		tempobj.Limit=m_cList.GetItemText(0,2);
		tempobj.CurrentValue=m_cList.GetItemText(0,3);
		tempobj.Unit=m_cList.GetItemText(0,4);
		tempobj.TimeRised=m_cList.GetItemText(0,5);
		TankIdAlarm=tempobj.Tankid=m_cList.GetItemText(0,7);
		COleDateTime TempDate;
		TempDate = COleDateTime::GetCurrentTime();
		CString TempdateAcknow=TempDate.Format();
		tempobj.TimeAcknowledged=TempdateAcknow;
		if ( theShipData().m_AlarmData.size() >0 ) {
			theShipData().m_AlarmData.erase(theShipData().m_AlarmData.begin()+ (SelectedItem));
		}
		m_cList.DeleteItem(SelectedItem);
		int n=m_cList.GetItemCount();
		m_cList.InsertItem(LVIF_IMAGE | LVIF_TEXT,n,"", 0, 0, 0, 0L);
		m_cList.SetItemText(n,0,tempobj.TankName);
		m_cList.SetItemText( n,1, tempobj.AlarmText );
		m_cList.SetItemText( n,2, tempobj.Limit);
		m_cList.SetItemText( n,3, tempobj.CurrentValue);
		m_cList.SetItemText( n,4, tempobj.Unit);
		m_cList.SetItemText( n,5, tempobj.TimeRised );
		//m_cList.SetItemText( n,6, tempobj.TimeAcknowledged );
		m_cList.SetItemText( n,7, tempobj.Tankid );

		//Addition Start JSD 09-08-2007
		AckAlarmData+= "<Alarms>";
		AckAlarmData+="\n";
		AckAlarmData+="<AlarmAck>";
		AckAlarmData+=TankIdAlarm;
		AckAlarmData+="</AlarmAck>";
		AckAlarmData+="\n";
		AckAlarmData+="<AlarmSoundStatus>";
		soundStatus=CTankData::m_AlarmStatus;
		AckAlarmData+=soundStatus;
		AckAlarmData+="</AlarmSoundStatus>";
		AckAlarmData+="\n";
		AckAlarmData+= "<AlarmCount>";
		int m=theShipData().m_AlarmData.size();
		CString Almcount;
		Almcount.Format("%d",m);
		AckAlarmData+=Almcount;
		AckAlarmData+="</AlarmCount>\n";
		AckAlarmData+="</Alarms>\n";
		bool abc;
		abc=theApp.SendAlarmDataToIPS(AckAlarmData);
		//End Start JSD 09-08-2007
		CPvcsTankDlg::AlmCtrlDlgClicked=1;
	} else
		::AfxMessageBox("No Alarm is Generated till now or selected Alarm allready Acknowledged",0,0);
    theShipData().Release();



}

void CPVCSAlarmCtrl::OnBnClickedSilencealarmButton()
{
	CString ScilenceAlarm="";
	CString soundStatus;
	if ( m_cList.GetItemCount()>0 ) {
		ScilenceAlarm+= "<Alarms>";
		ScilenceAlarm+="\n";
		ScilenceAlarm+="<AlarmAck>";
		ScilenceAlarm+="</AlarmAck>";
		ScilenceAlarm+="\n";
		ScilenceAlarm+="<AlarmSoundStatus>" ;
		soundStatus.Format("%d",0);
		ScilenceAlarm+=soundStatus;
		ScilenceAlarm+="</AlarmSoundStatus>";
		ScilenceAlarm+="\n";
		ScilenceAlarm+= "<AlarmCount>";
        theShipData().Aquire();
		int m=theShipData().m_AlarmData.size();
        theShipData().Release();
		CString Almcount;
		Almcount.Format("%d",m);
		ScilenceAlarm+=Almcount;
		ScilenceAlarm+="</AlarmCount>\n";
		ScilenceAlarm+="</Alarms>\n";

		bool abc;
		abc=theApp.SendAlarmDataToIPS(ScilenceAlarm);
	}

	theApp.m_bAlarmSoundOFF = true;

}
void CPVCSAlarmCtrl::InsertEmpty(int id )
{
	theShipData().Aquire();
	int num = m_cList.GetItemCount();
	CString strText;
	COleDateTime dateTest;

	dateTest = COleDateTime::GetCurrentTime();
	CString str1 = dateTest.Format();
	strText.Format(TEXT("Tank %d"), id);
	m_cList.InsertItem( num, strText );
	m_cList.SetItemText( num,1, "Active" );
	m_cList.SetItemText( num,2,str1);
    theShipData().Release();

}

void CPVCSAlarmCtrl::InsertAlaram(int count)
{
	CString TankidText;
	theShipData().Aquire();
	int i= 0;
	for (;i<count;i++ ) {

		if ( theShipData().m_AlarmData.size()>0 ) {

			m_cList.InsertItem(LVIF_IMAGE | LVIF_TEXT,
							   i, "", 0, 0, 0, 0L);
			m_cList.SetItemText(i,0,theShipData().m_AlarmData[i].TankNameDisplay );
			m_cList.SetItemText( i,1, theShipData().m_AlarmData[i].AlarmText );
			m_cList.SetItemText( i,2,theShipData().m_AlarmData[i].Limit);
			m_cList.SetItemText( i,3,theShipData().m_AlarmData[i].CurrentValue);
			m_cList.SetItemText(i,4,theShipData().m_AlarmData[i].Unit);
			m_cList.SetItemText(i,5,theShipData().m_AlarmData[i].TimeRaised);
			m_cList.SetItemText(i,7,theShipData().m_AlarmData[i].Tankid);
		}
	}
	int count1=theShipData().m_AckAlarmData.size();
	int count2=count1+count;
	for (int j=0 ;i<count2;i++ ) {
		CString temp;
		if ( (theShipData().m_AckAlarmData.size()>0) && (j<int(theShipData().m_AckAlarmData.size())) ) {
			m_cList.InsertItem(LVIF_IMAGE | LVIF_TEXT,
							   i, "", 0, 0, I_IMAGECALLBACK, 0L);
			m_cList.SetItemText(i,0,theShipData().m_AckAlarmData[j].TankNameDisplay );
			m_cList.SetItemText( i,1, theShipData().m_AckAlarmData[j].AlarmText );
			temp=theShipData().m_AckAlarmData[j].Limit;
			m_cList.SetItemText( i,2, theShipData().m_AckAlarmData[j].Limit);
			m_cList.SetItemText( i,3,theShipData().m_AckAlarmData[j].CurrentValue);
			m_cList.SetItemText(i,4,theShipData().m_AckAlarmData[j].Unit);
			m_cList.SetItemText(i,5,theShipData().m_AckAlarmData[j].TimeRaised);
			m_cList.SetItemText(i,6,theShipData().m_AckAlarmData[j].TimeAck);
			m_cList.SetItemText(i,7,theShipData().m_AckAlarmData[j].Tankid);
		}
		j++;

	}
	/*if(lastnoofitems>count2)
	{
		for(;i<lastnoofitems;i++)
		{
			m_cList.InsertItem(LVIF_IMAGE | LVIF_TEXT,
			i, "", 0, 0, I_IMAGECALLBACK, 0L);
			m_cList.SetItemText(i,0,"");
			m_cList.SetItemText(i,1,"");
			m_cList.SetItemText(i,2,"");
			m_cList.SetItemText(i,3,"");
			m_cList.SetItemText(i,4,"");
			m_cList.SetItemText(i,5,"");
			m_cList.SetItemText(i,6,"");
			m_cList.SetItemText(i,7,"");
		}
	}*/

	lastnoofitems=count2;
    theShipData().Release();

}

void CPVCSAlarmCtrl::OnTimer(UINT nIDEvent)
{
    theShipData().Aquire();
	//if( nIDEvent == IDD_ALARM_DLG )
	//{
	///CPVCSAlarmCtrl* wndAlmCtrl = dynamic_cast <CPVCSAlarmCtrl*> ( GetDlgItem( IDD_ALARM_DLG ) );
	//if(wndAlmCtrl)
	//wndAlmCtrl->RedrawWindow();
	//CPVCSAlarmCtrl::RedrawWindow();
	if ( CTankData::AlarmListDraw==true ) {
		if ( blink==false ) {
			ImagelistObj=new CImageList();
			ImagelistObj->Create(16, 16,ILC_COLOR8,0, 1);
			CBitmap *bm;
			bm=new  CBitmap();
			bool status;
			status=bm->LoadBitmap(IDB_BITMAP2);
			if ( bm->m_hObject )
				CString m;
			int j;
			j= ImagelistObj->Add (bm, RGB (0, 0, 0));
			m_cList.SetImageList(ImagelistObj, LVSIL_SMALL);
			blink=true;
		} else {
			ImagelistObj=new CImageList();
			ImagelistObj->Create(16, 16,ILC_COLOR8,0, 1);
			CBitmap *bm;
			bm=new  CBitmap();
			bool status;
			status=bm->LoadBitmap(IDB_BITMAP3);
			if ( bm->m_hObject )
				CString m;
			int j;
			j= ImagelistObj->Add (bm, RGB (0, 0, 0));
			m_cList.SetImageList(ImagelistObj, LVSIL_SMALL);
			blink=false;
		}
		//theShipData().FillAlarmData();
		//theShipData().FillAckAlarmData();
		int jtemp=m_cList.GetItemCount();
		if ( jtemp>0 ) {
			m_cList.DeleteAllItems();

		}
		int last=theShipData().m_AlarmData.size();
		InsertAlaram(last);
	}
	CDC *pCtlDC;
	CWnd* PWnd=FindWindow(NULL,"Alarm List");
	CWnd* PWndAlarmList;
	PWndAlarmList=PWnd->GetDlgItem(IDC_ALARM_LIST);
	pCtlDC=PWndAlarmList->GetWindowDC();
	//m_cList.RedrawItems(0,last);
	CDialog::OnTimer(nIDEvent);
	PvcsAlarmObject::CheckAlarms();
    theShipData().Release();
}
//Start JSD
BOOL CPVCSAlarmCtrl::PreTranslateMessage(MSG* pMsg)
{
	/*if( pMsg->message == WM_KEYDOWN )
	{
		char key1= 'k';*/
	//VkKeyScan(VK_F10);
	//if(pMsg->wParam == VkKeyScan(key1) )
	if ( pMsg->wParam == VK_F10 ) {
		OnBnClickedAlarmacknowButton();
		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		return 1;
	}
	//}
	return CDialog::PreTranslateMessage(pMsg);
}
// End JSD


void CPVCSAlarmCtrl::OnNMCustomdrawAlarmList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	//int iRow = lplvcd->nmcd.dwItemSpec;

	*pResult = 0;
}

BOOL CPVCSAlarmCtrl::colorAlmList(/*CDC* pDC*/)
{
	// TODO: Add your message handler code here and/or call default
	CDC* pDC=m_cList.GetWindowDC();
	CRect rect;
	m_cList.GetClientRect(rect);


	POINT mypoint;

	CBrush brush0(RGB(0,255,0));
	CBrush brush1(RGB(255,0,0));
	int chunk_height=m_cList.GetItemCount();
	//GetCountPerPage();
	//pDC->FillRect(&rect,&brush0);

	for ( int i=0;i<=chunk_height;i++ ) {

		if ( m_cList.GetItemText(i,6)=="" ) {

			m_cList.GetItemPosition(i,&mypoint);
			rect.top=mypoint.y ;
			m_cList.GetItemPosition(i+1,&mypoint);
			rect.bottom =mypoint.y;
			pDC->FillRect(&rect,&brush0);
		} else {
			m_cList.GetItemPosition(i,&mypoint);
			rect.top=mypoint.y ;
			m_cList.GetItemPosition(i+1,&mypoint);
			rect.bottom =mypoint.y;
			pDC->FillRect(&rect,&brush1);
		}


	}

	brush0.DeleteObject();
	//brush1.DeleteObject();

	return FALSE;
}

