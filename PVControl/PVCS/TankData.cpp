#include "StdAfx.h"
#include ".\tankdata.h"
CString CTankData::m_AlarmStatus="";
bool CTankData::AlarmListDraw=true;
CTankData::CTankData(void)
{
	 // Initialize the critical section one time only.
   InitializeCriticalSection(&CriticalSection);

}

CTankData::~CTankData(void)
{
// Release resources used by the critical section object.
    DeleteCriticalSection(&CriticalSection);

}

// Function to Get the Data of sensors for individual tank and assign it to the  Class Variables
bool CTankData::GetTankSensorsData(IN unsigned int param_uiTankNumber,IN CString param_strTankType)
{
	bool bolState=false;

	if(XMLDataLoadStatus)
	{

		MSXML2::IXMLDOMNodeListPtr pNodeList;
		MSXML2::IXMLDOMNodePtr pTempChild;
		MSXML2::IXMLDOMNodePtr pTempChildVal;
		MSXML2::IXMLDOMNodePtr pTempChildPacket;
		_bstr_t m_strNodeName(IntToBstr(param_uiTankNumber),FALSE);
		_bstr_t strPacketName(CStrToBstr(param_strTankType),FALSE);
		CString pcRetValue;
		CString pcRetPacketID;

		pNodeList=GetNode("Packet");

		if(pNodeList)
		{
			// make the area critical section so that data for two tanks is not read parallely
			EnterCriticalSection(&CriticalSection);

			for(int j=0;j<pNodeList->length;j++)
			{
				pNodeList->get_item(j, &pTempChild);

				pTempChildVal=pTempChild->selectSingleNode("TagID");
				pTempChildPacket=pTempChild->selectSingleNode("PacketID");
				if( (pTempChildVal==NULL) || (pTempChildPacket == NULL) )
				{
					bolState=false;
				}
				else
				{
					pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
					pcRetPacketID.Format(_T("%s"),(LPCTSTR)pTempChildPacket->text);
					if( (!strcmp(pcRetValue,m_strNodeName)) && (!strcmp(pcRetPacketID,strPacketName)) )
					{
						SetTankSensorData(pTempChild);
						bolState=true;
					}
				}
			}

			::SysFreeString(m_strNodeName);

			//GetAlarmStatus();

			LeaveCriticalSection(&CriticalSection);
		}

	}
	return bolState;
}

// Function to assign the Values to the Class variales that hold data for each tank
bool CTankData::SetTankSensorData(IN MSXML2::IXMLDOMNodePtr param_pTempChild)
{
	// to assign data to class variables
	Ullage=AssignSensorData(param_pTempChild,"Ullage");
	Level=AssignSensorData(param_pTempChild,"Level");
	Volume=AssignSensorData(param_pTempChild,"Volume");
	Weight=AssignSensorData(param_pTempChild,"Weight");
	LoadRate=AssignSensorData(param_pTempChild,"Loadrate");
	VolumePercentage=AssignSensorData(param_pTempChild,"Volumepercent");
	Temperature=AssignSensorData(param_pTempChild,"Temperature");
	TankPressure=AssignSensorData(param_pTempChild,"Tankpressure");
	LinePressure=AssignSensorData(param_pTempChild,"Linepressure");
	CargoType=AssignSensorData(param_pTempChild,"Cargotype");
	CargoColor=AssignSensorData(param_pTempChild,"Cargocolor");
	Alarmstatus=AssignSensorData(param_pTempChild,"Alarmstatus");
	AlarmText=AssignSensorData(param_pTempChild,"Alarmtext");
	AlarmData=AssignSensorData(param_pTempChild,"AlarmListEntryAct");
	//m_AlarmStatus = AssignSensorData(param_pTempChild,"AlarmSoundStatus");
	return true;
}

// Function to assign values to the variables that hold tanker data
CString CTankData::AssignSensorData(IN MSXML2::IXMLDOMNodePtr param_pTempChild,IN CString param_pcTagName)
{
	// to read and assign data to indiviual member variables
	CString pcData;
	MSXML2::IXMLDOMNodePtr pTempChildVal;
	BSTR TagNames;
	TagNames =CStrToBstr(param_pcTagName);
	pTempChildVal=param_pTempChild->selectSingleNode(TagNames);

	if( NULL != pTempChildVal )
	{
		pcData.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
		pTempChildVal=NULL;
	}

	::SysFreeString(TagNames);
	return pcData;

}

// To get the Count of total number of packets
int CTankData::GetCount(void)
{
	if(XMLDataLoadStatus==false)
	{
		return false;
	}

	MSXML2::IXMLDOMNodeListPtr pNodeList;

	pNodeList=GetNode("Packet");
	if( NULL == pNodeList )
	{
		return false;
	}

	int iTotNodes=pNodeList->length;

	return iTotNodes;
}

// To get the TagID of specific packet
int CTankData::GetTagID(unsigned int param_uiPacketNo)
{
	if(XMLDataLoadStatus==false)
	{
		return false;
	}

MSXML2::IXMLDOMNodePtr pChildd ;
MSXML2::IXMLDOMNodePtr more ;
MSXML2::IXMLDOMNodeListPtr pDataList;
int iTagid;


	pDataList=m_plDomDocument->documentElement->selectNodes("Packet");

	for(int j=0;j<pDataList->length;j++)
	{
		if(j==int(param_uiPacketNo))
		{
			pDataList->get_item(j, &pChildd);

			more=pChildd->selectSingleNode("TagID");
			if(more==NULL)
			{
				iTagid=0;
			}
			else
			{
				iTagid=atoi(more->text);
			}
		} // root if ended
	} // for loop ended


	return iTagid;
}


///////////////////////////////////////////////////////////////////
// Changes made on 1 Feb 2006
// for free values
///////////////////////////////////////////////////////////////////
// Function to get the Free Values
bool CTankData::GetFreeValue(UINT param_uiTankNumber, CString param_strFreeValType, UINT param_uiValueKey)
{
	bool bolState=false;

	if(XMLDataLoadStatus)
	{

		MSXML2::IXMLDOMNodeListPtr pNodeList;
		MSXML2::IXMLDOMNodePtr pTempChild;
		MSXML2::IXMLDOMNodePtr pTempChildVal;
		MSXML2::IXMLDOMNodePtr pTempChildPacket;
		_bstr_t m_strNodeName(IntToBstr(param_uiTankNumber),FALSE);
		_bstr_t strPacketName(CStrToBstr(param_strFreeValType),FALSE);
		CString pcRetValue;
		CString pcRetPacketID;

		pNodeList=GetNode("Packet");

		if(pNodeList)
		{
			// make the area critical section so that data for two tanks is not read parallely
			EnterCriticalSection(&CriticalSection);
			int Cnt = 0;
			for(int j=0;j<pNodeList->length;j++)
			{
				Cnt++;
				pNodeList->get_item(j, &pTempChild);

				pTempChildVal=pTempChild->selectSingleNode("TagID");
	 			pTempChildPacket=pTempChild->selectSingleNode("PacketID");
				if( (pTempChildVal==NULL) || (pTempChildPacket == NULL) )
				{
					bolState=false;
				}
				else
				{
					pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
					pcRetPacketID.Format(_T("%s"),(LPCTSTR)pTempChildPacket->text);
					if( (!strcmp(pcRetValue,m_strNodeName)) && (!strcmp(pcRetPacketID,strPacketName)) )
					{
						SetFreeValueData(pTempChild);
						bolState=true;
					}
				}
			}
			::SysFreeString(m_strNodeName);

			LeaveCriticalSection(&CriticalSection);
		}

	}
	return bolState;
}

// To assign the free value data to the members varible to be accessed outside the class
bool CTankData::SetFreeValueData(MSXML2::IXMLDOMNodePtr param_pTempChild)
{
	// to assign data to class variables
	m_strFreeValue=AssignFreeValue(param_pTempChild,"Value");
	m_AlarmState = atoi(AssignFreeValue(param_pTempChild,"Alarm"));
	return true;
}

// To assign free value data to the variable
CString CTankData::AssignFreeValue(MSXML2::IXMLDOMNodePtr param_pTempChild, CString param_pcTagName)
{
	// to read and assign data to indiviual member variables
	CString pcData;
	MSXML2::IXMLDOMNodePtr pTempChildVal;
	BSTR TagNames;
	TagNames =CStrToBstr(param_pcTagName);
	pTempChildVal=param_pTempChild->selectSingleNode(TagNames);

	if( NULL != pTempChildVal )
	{
		pcData.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
		pTempChildVal=NULL;
	}

	::SysFreeString(TagNames);
	return pcData;
}

// To get Alarm Data
bool CTankData::GetAlarmData(void)
{
    EnterCriticalSection(&CriticalSection);
	AlarmListDraw=false;
	CString pcRetValue="";
	m_strAckAlarmData.clear();
	//TRACE("\nm_strAckAlarmData.clear() ---------------------------------- called");
	m_strAlarmData.clear();
	if(XMLDataLoadStatus)
	{
			// make the area critical section so that data for two tanks is not read parallely

			//m_strAlarmData.clear();
		for(MSXML2::IXMLDOMNodePtr m_pNodeList=m_pDocRoot->firstChild;m_pNodeList !=NULL;m_pNodeList=m_pNodeList->nextSibling)
		{


			if (!strcmp(m_pNodeList->nodeName,"AlarmlistEntryAct"))
			{
				pcRetValue.Format(_T("%s"), (LPCTSTR)m_pNodeList->text);
				m_strAlarmData.push_back(pcRetValue);
				//m_strAlarmData.size;
				//return pcRetValue;
			}
			if (!strcmp(m_pNodeList->nodeName,"AlarmlistEntryAkn"))
			{
				pcRetValue.Format(_T("%s"), (LPCTSTR)m_pNodeList->text);
				m_strAckAlarmData.push_back(pcRetValue);
				//m_strAlarmData.size;
				//return pcRetValue;
			}
			if (!strcmp(m_pNodeList->nodeName,"AlarmSoundStatus"))
			{
				pcRetValue.Format(_T("%s"), (LPCTSTR)m_pNodeList->text);
				m_AlarmStatus=pcRetValue;
				//m_strAlarmData.size;
				//return pcRetValue;
			}
			if (!strcmp(m_pNodeList->nodeName,"AlarmCount"))
			{
				pcRetValue.Format(_T("%s"), (LPCTSTR)m_pNodeList->text);
				m_AlarmCount=pcRetValue;
				//m_strAlarmData.size;
				//return pcRetValue;
			}
//ended
			else
			{
				pcRetValue="";
			}
		}



			//::SysFreeString(m_strNodeName);


	}
	LeaveCriticalSection(&CriticalSection);
	AlarmListDraw=true;
	return(true);

}



// To Get The ALarm Status
CString CTankData::GetAlarmStatus(void)
{
	EnterCriticalSection(&CriticalSection);
	AlarmListDraw=false;
	//m_strAckAlarmData.clear();

	//m_strAlarmData.clear();
	CString pcRetValue="NULL";
	if(XMLDataLoadStatus)
	{
			// make the area critical section so that data for two tanks is not read parallely

			//m_strAlarmData.clear();
		for(MSXML2::IXMLDOMNodePtr m_pNodeList=m_pDocRoot->firstChild;m_pNodeList !=NULL;m_pNodeList=m_pNodeList->nextSibling)
		{

			if (!strcmp(m_pNodeList->nodeName,"AlarmSoundStatus"))
			{
				pcRetValue.Format(_T("%s"), (LPCTSTR)m_pNodeList->text);
				m_AlarmStatus=pcRetValue;

			}

			else
			{
				m_AlarmStatus = "";
				pcRetValue="";
			}
		}


			//::SysFreeString(m_strNodeName);


	}
	LeaveCriticalSection(&CriticalSection);
	AlarmListDraw=true;
	return pcRetValue;
}
