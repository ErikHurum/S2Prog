// PvcsToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "PVCS v1.0.h"
#include "PvcsToolBar.h"
#include "PVCSAlarmCtrl.h"
#include "pvcsshipdata.h"

// CPvcsToolBar

IMPLEMENT_DYNAMIC(CPvcsToolBar, CToolBar)
CPvcsToolBar::CPvcsToolBar()
{
}

CPvcsToolBar::~CPvcsToolBar()
{
	delete m_pPvcsToolBarAlarmButton;

	for(unsigned i =0; i < m_PvcsToolBarEmgButton.size(); i++)
	{
		delete m_PvcsToolBarEmgButton[i];
	}

	for(unsigned i =0; i < m_PvcsToolBarPumpButton.size(); i++)
	{
		delete m_PvcsToolBarPumpButton[i];
	}
}


BEGIN_MESSAGE_MAP(CPvcsToolBar, CToolBar)
	ON_BN_CLICKED(IDC_ALARMBUTTON, OnBnClickedAlarmbutton)
END_MESSAGE_MAP()


// CPvcsToolBar message handlers



void CPvcsToolBar::OnBnClickedAlarmbutton()
{
	CString ScilenceAlarm="";
	CString soundStatus;
	theShipData().Aquire();
	int iActiveAlarmCount = theShipData().m_AlarmData.size();
	theShipData().Release();

	if (iActiveAlarmCount > 0)
	{
		ScilenceAlarm+= "<Alarms>";
		ScilenceAlarm+="\n";
		ScilenceAlarm+="<AlarmAck>";
		ScilenceAlarm+="</AlarmAck>";
		ScilenceAlarm+="\n";
		ScilenceAlarm+="<AlarmSoundStatus>"	;
		soundStatus.Format("%d",0);
		ScilenceAlarm+=soundStatus;
		ScilenceAlarm+="</AlarmSoundStatus>";
		ScilenceAlarm+="\n";
		ScilenceAlarm+= "<AlarmCount>";

		CString Almcount;
		Almcount.Format("%d",iActiveAlarmCount);
		ScilenceAlarm+=Almcount;
		ScilenceAlarm+="</AlarmCount>\n";
		ScilenceAlarm+="</Alarms>\n";

		theApp.SendAlarmDataToIPS(ScilenceAlarm);
	}

	theApp.m_bAlarmSoundOFF = true;

	if(CPVCSAlarmCtrl::IsAlmDlgOpen==false)
	{
		CPVCSAlarmCtrl::IsAlmDlgOpen=true;
		thePVCSAlmCtrl().DoModal();
	}
	else
	{
		thePVCSAlmCtrl().SetForegroundWindow();
	}

}



void CPvcsToolBar::OnBnClickedPumpButton(int Id)
{
/*CString ScilenceAlarm="";
	CString soundStatus;
	theShipData().Aquire();
	int iActiveAlarmCount = theShipData().m_AlarmData.size();
	theShipData().Release();

	if (iActiveAlarmCount > 0)
	{
		ScilenceAlarm+= "<Alarms>";
		ScilenceAlarm+="\n";
		ScilenceAlarm+="<AlarmAck>";
		ScilenceAlarm+="</AlarmAck>";
		ScilenceAlarm+="\n";
		ScilenceAlarm+="<AlarmSoundStatus>"	;
		soundStatus.Format("%d",0);
		ScilenceAlarm+=soundStatus;
		ScilenceAlarm+="</AlarmSoundStatus>";
		ScilenceAlarm+="\n";
		ScilenceAlarm+= "<AlarmCount>";

		CString Almcount;
		Almcount.Format("%d",iActiveAlarmCount);
		ScilenceAlarm+=Almcount;
		ScilenceAlarm+="</AlarmCount>\n";
		ScilenceAlarm+="</Alarms>\n";

		theApp.SendAlarmDataToIPS(ScilenceAlarm);
	}

	theApp.m_bAlarmSoundOFF = true;

	if(CPVCSAlarmCtrl::IsAlmDlgOpen==false)
	{
		CPVCSAlarmCtrl::IsAlmDlgOpen=true;
		thePVCSAlmCtrl().DoModal();
	}
	else
	{
		thePVCSAlmCtrl().SetForegroundWindow();
	}
	*/

}


void CPvcsToolBar::OnBnClickedPumpButton1()
{
	OnBnClickedPumpButton(0);
}
void CPvcsToolBar::OnBnClickedPumpButton2()
{
	OnBnClickedPumpButton(1);
}
void CPvcsToolBar::OnBnClickedPumpButton3()
{
	OnBnClickedPumpButton(2);
}
void CPvcsToolBar::OnBnClickedPumpButton4()
{
	OnBnClickedPumpButton(3);
}
void CPvcsToolBar::OnBnClickedPumpButton5()
{
	OnBnClickedPumpButton(4);
}


