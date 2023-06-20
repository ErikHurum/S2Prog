#include "StdAfx.h"
#include ".\pvcsshipdata.h"

#include "pvcstankdata.h"
#include "PVCS v1.0.h"
#include "pvcsconfiguration.h"//Added JSD 22FEB2007
#include <stdlib.h>
#include ".\errorlog.h"

CCriticalSection g_CS_TankMap;
CCriticalSection g_CS_FreeValue;
// Function name   : theShipData
// Description     : Function to access the one and only Ship Data structure
// Return type     : CPvcsShipData&

CPvcsShipData& theShipData() {
    static CPvcsShipData ShipData;
    return ShipData;
}


// Function name   : CPvcsShipData::GetSysConfig
// Description     : returns CReadSystemConfig instance
// Return type     :
// Argument        : void
CReadSystemConfig& CPvcsShipData::GetSysConfig(void) {
    return m_SysConfig;
}

// Function name   : CPvcsShipData::CPvcsShipData
// Description     : Constructor
// Return type     :
// Argument        : void

CPvcsShipData::CPvcsShipData(void)
    : m_pBuffer(NULL)
    , m_uiBufferSize(100000)
    , m_bConnectStatus(false)
    , m_bIsBusy(false)
    , m_bNewFreeValue(false)
    , m_bCurrentState(false) {
    AlarmVectorHandle1  = CreateMutex(NULL, false, NULL);
    AlarmVectorHandle2  = CreateMutex(NULL, false, NULL);

    m_DefaultTankMap = new TankMap;

    if (m_SysConfig.LoadXMLFile(XML_MAIN_CONFIGURATION_FILE)) {
        MakeValid();
        //	m_bConnectStatus = m_IPSCommunication.RequestConnect(m_SysConfig.GetSurveyorIP(),m_SysConfig.GetConnectionPort());

    } else XmlLogError("Error loading main config file");
    try {

        //if(!m_bConnectStatus )
        //			m_IPSCommunication.DisconnectFromIPS();
        //	else
        //		m_pBuffer = new BYTE[theShipData().m_uiBufferSize];


    } catch (exception &e) {
        //TRACE("*****cpvcsshipdata-constructor******");
        m_pBuffer = 0;
        XmlLogError(e.what());
    }
}


// Function name   : CPvcsShipData::~CPvcsShipData
// Description     : Destructor
// Return type     :
// Argument        : void
#pragma warning (disable: 4101)
CPvcsShipData::~CPvcsShipData(void) {
    try {
        CloseHandle(AlarmVectorHandle1);
        CloseHandle(AlarmVectorHandle2);

        delete m_DefaultTankMap;
        delete[] m_pBuffer;

    } catch (exception &e) {}
}


// Function name   : CPvcsShipData::GetTankCount
// Description     : Get the number of tanks
// Return type     : int
// Argument        : void

int CPvcsShipData::GetTankCount(void) {
    return m_xmlTankData.GetCount();
}


// Function name   : CPvcsShipData::GetTankID
// Description     : Get the ID of the tanks
// Return type     : int
// Argument        : const int& param_nIndex

int CPvcsShipData::GetTankID(const int &param_nIndex) {
    return m_xmlTankData.GetTagID(param_nIndex);
}


// Function name   : CPvcsShipData::GetData
// Description     : Get the data from the surveyor
// Return type     : bool
// Argument        : void

CPvcsShipData::TankMap* CPvcsShipData::GetData(void) {
    TankMap *pTankMap = new TankMap;
    CSingleLock singlelock(&g_CS_TankMap);
    singlelock.Lock();
    *pTankMap = m_TemptankMap;
    singlelock.Unlock();
    return pTankMap;
}


// Function name   : CPvcsShipData::LoadTankData
// Description     : Loads the tank data into the given structure
// Return type     : bool
// Argument        : const int& param_iIndex
// Argument        : CPvcsTankData& param_TankData

bool CPvcsShipData::LoadTankData(const int &param_iIndex, CPvcsTankData &param_TankData) {
    bool m_bSuccess = false;

    if (m_bConnectStatus) {
        if (m_xmlTankData.GetTankSensorsData(param_iIndex, "Tank")) {
            param_TankData.m_strUllage = m_xmlTankData.Ullage;
            param_TankData.m_strLevel = m_xmlTankData.Level;
            param_TankData.m_strVolume = m_xmlTankData.Volume;
            param_TankData.m_strVolumePercent = m_xmlTankData.VolumePercentage;
            param_TankData.m_strWeight = m_xmlTankData.Weight;
            param_TankData.m_strTemperature = m_xmlTankData.Temperature;
            param_TankData.m_strTankPressure = m_xmlTankData.TankPressure;
            param_TankData.m_strLinePressure = m_xmlTankData.LinePressure;
            param_TankData.m_strCargoType = m_xmlTankData.CargoType;
            param_TankData.m_strLoadRate = m_xmlTankData.LoadRate;
            param_TankData.m_strCargoColor = m_xmlTankData.CargoColor;
            param_TankData.m_strAlarmStatus = m_xmlTankData.Alarmstatus;
            param_TankData.m_strAlarmText = m_xmlTankData.AlarmText;
            //param_TankData.m_strAlarm = m_xmlTankData.AlarmData;

            param_TankData.MakeValid();
            m_bSuccess = true;
        } // if( m_xmlTankData.GetTankSensorsData( param_iIndex ) )

    } // if( m_bConnectStatus )

    return m_bSuccess;
}


// Function name   : CPvcsShipData::GetTank
// Description     : Retrives the indexed Tank data structure
// Return type     : const CPvcsTankData&
// Argument        : const int& param_iIndex

const CPvcsTankData& CPvcsShipData::GetTank(const int &param_iIndex, const TankMap *pTankMap) const {
    try {
        if (pTankMap == NULL) pTankMap = theShipData().m_DefaultTankMap;

        TankMap_it it = pTankMap->find(param_iIndex);

        if (it == pTankMap->end()) return m_blankTankData;
        else return (*it).second;
    } catch (exception &e) {
        pTankMap = theShipData().m_DefaultTankMap;

        TankMap_it it = pTankMap->find(param_iIndex);
        if (it == pTankMap->end()) return m_blankTankData;
        else return (*it).second;
    }
}


// Function name   : CPvcsShipData::GetTankMap
// Description     : Retrieves the tank map
// Return type     : const CPvcsShipData::TankMap&
// Argument        : void

const CPvcsShipData::TankMap& CPvcsShipData::GetTankMap(void) {
    return m_tankData;
}

void CPvcsShipData::LoadFreeValues(void) {
    while (m_bIsBusy);
    m_bIsBusy = true;

    for (FreeValueMap_it it = m_FreeValue.begin(); it != m_FreeValue.end(); ++it) {
        string strTemp = (*it).first.substr(3, 4);

        if (m_bCurrentState && m_xmlTankData.GetFreeValue(atoi(strTemp.c_str()), "Freevalue")) (*it).second = m_xmlTankData.m_strFreeValue;
        else (*it).second.clear();

    }
    for (FreeAlarmMap_it it = m_FreeAlarm.begin(); it != m_FreeAlarm.end(); ++it) {
        string strTemp = (*it).first.substr(3, 4);
		if (m_bCurrentState && m_xmlTankData.GetFreeValue(atoi(strTemp.c_str()), "Freevalue")) (*it).second = m_xmlTankData.m_AlarmState;

    }

    m_bIsBusy = false;
}

string CPvcsShipData::GetFreeValue(const string &param_strTagText) {
    string strValue;

    while (m_bIsBusy);
    m_bIsBusy = true;
    CSingleLock singlelock(&g_CS_FreeValue);
    singlelock.Lock();
    strValue = m_FreeValue[param_strTagText];
    singlelock.Unlock();
    m_bIsBusy = false;

    return strValue;
}


int CPvcsShipData::GetFreeAlarm(const string &param_strTagText) {
    int alarmState;

    while (m_bIsBusy);
    m_bIsBusy = true;
    CSingleLock singlelock(&g_CS_FreeValue);
    singlelock.Lock();
    alarmState = m_FreeAlarm[param_strTagText];
    singlelock.Unlock();
    m_bIsBusy = false;

    return alarmState;
}

CIPSCommunication& CPvcsShipData::GetIPSCommObj(void) {
    return m_IPSCommunication;
}

//Get Data From IPS using Thread
UINT GetDataFromIPSThread(LPVOID pParam) {
    bool bSuccess = false;
    static int iSendFailCounter = 0;
    static int iRecFailCounter = 0;
    int counter = 0;

    theShipData().m_bConnectStatus = theShipData().GetIPSCommObj().RequestConnect(theShipData().GetSysConfig().GetSurveyorIP(), theShipData().GetSysConfig().GetConnectionPort());

    if (theShipData().m_bConnectStatus) theShipData().m_pBuffer = new char[theShipData().m_uiBufferSize];

    //if( !theShipData().m_bConnectStatus )
    //	theShipData().GetIPSCommObj().DisconnectFromIPS();
    //else
    //	theShipData().m_pBuffer = new char[theShipData().m_uiBufferSize];

    while (CPVCSApp::m_bIsAlive) { //if application alive, worker thread keep on running
        counter++;
        CPVCSApp::bIsShipDataThreadExit = false;
        theShipData().m_tankData.clear();





        if (theShipData().m_bConnectStatus) {
            theShipData().m_bCurrentState = true;

            CSingleLock lock_freevalue(&g_CS_FreeValue);
            theShipData().LoadFreeValues();
            lock_freevalue.Unlock();

            if (theShipData().m_IPSCommunication.SendDataRequest()) {
                UINT size = theShipData().m_uiBufferSize;
                iSendFailCounter = 0;
                if (theShipData().m_IPSCommunication.ReceiveIPSData(theShipData().m_pBuffer, size)) {
                    iRecFailCounter = 0;
                    //theShipData().m_pBuffer[size] = '\0';
                    CString m_pcRecvData = theShipData().m_pBuffer;

                    if (theShipData().m_xmlTankData.LoadXMLData(m_pcRecvData)) {

                        CPvcsTankData tempData;

                        while (theShipData().m_bIsBusy);
                        theShipData().m_bIsBusy = true;
                        //theShipData().m_AlarmData.clear(); //JSD
                        for (int i = 0; i < theShipData().GetTankCount(); i++) {
                            theShipData().LoadTankData(theShipData().GetTankID(i), tempData);

                            theShipData().m_tankData.insert(CPvcsShipData::TankMapValue(theShipData().GetTankID(i), tempData));
                            //START JSD
                            /*	struct AlarmDataStruct AlarmDataStructObj;
                            int temp =theShipData().GetTankID(i);
                            CString TempTankName=theConfiguration().GetTankName(temp);
                            COleDateTime dateTemp1;
                            dateTemp1 = COleDateTime::GetCurrentTime();
                            AlarmDataStructObj.Tankid =temp;
                            AlarmDataStructObj.TankNameDisplay=TempTankName;
                            AlarmDataStructObj.dateAlarm=dateTemp1;
                            AlarmDataStructObj.AcknowStatus=false;
                            AlarmDataStructObj.AlarmText=theShipData().GetTank(AlarmDataStructObj.Tankid, &theShipData().m_tankData).GetAlarmText();
                            AlarmDataStructObj.AlarmStatus=atoi(theShipData().GetTank(AlarmDataStructObj.Tankid,&theShipData().m_tankData).GetAlarmStatus());*/


                            //int j =theShipData().m_AlarmData.size();
                            //if(j<=theShipData().GetTankCount())
                            //{
                            //	if(AlarmDataStructObj.AlarmStatus!=0)
                            //		theShipData().m_AlarmData.push_back(AlarmDataStructObj);
                            //}
                            //END JSD
                        }

                        theShipData().FillAlarmData();
                        theShipData().FillAckAlarmData();

                        theShipData().m_bIsBusy = false;
                        bSuccess = true;
                        if (bSuccess) {
                            CSingleLock singlelock(&g_CS_TankMap);
                            singlelock.Lock();
                            theShipData().m_TemptankMap = theShipData().m_tankData;
                            singlelock.Unlock();
                        }
                    } //loadxml data
                    else {
                        //	//for error loging
                        //CErrorLog obj;

                        //	obj.WriteError("GetDataFromIPSThread","Xml load fails","");
                        Sleep(10);
                    }
                } // if( m_IPSCommunication.ReceiveIPSData( m_pBuffer, size ) )
                else { //if receive fails
                    if (CPVCSApp::m_bIsAlive) { //Go for reconnection, if PVCS still alive
                        int iSocketErrorCode = WSAGetLastError();

                        //CString strError = "";
                        //strError.Format("Socket Error Number = %d",iSocketErrorCode);
                        ////for error loging
                        //CErrorLog obj;

                        //obj.WriteError("GetDataFromIPSThread","Receive Fails",strError);


                        //if 10054  connection reset by peer, 10061 = connection refused, 10064 = Host is down, 10065 = No route to host, 10060 = Connection timed out
                        if (iSocketErrorCode == 10054 || iSocketErrorCode == 10061 || iSocketErrorCode == 10064 || iSocketErrorCode == 10065 || iSocketErrorCode == 10060) {
                            iRecFailCounter++;
                            if (iRecFailCounter == 5) {
                                iRecFailCounter = 0;
                                CSingleLock singlelock(&g_CS_TankMap);
                                singlelock.Lock();
                                theShipData().m_TemptankMap.clear();
                                singlelock.Unlock();
                                theShipData().m_bCurrentState = false;
                                theShipData().m_bConnectStatus = theShipData().m_IPSCommunication.resatblishConnection(theShipData().m_SysConfig.GetSurveyorIP(), theShipData().m_SysConfig.GetConnectionPort());
                                if (theShipData().m_bConnectStatus) {
                                    delete[] theShipData().m_pBuffer;
                                    theShipData().m_pBuffer = new char[theShipData().m_uiBufferSize];
                                }
                            }
                        } else { //for error 10053 (software caused connection abort or others
                            iRecFailCounter = 0;
                            theShipData().m_bCurrentState = false;
                            theShipData().m_bConnectStatus = theShipData().m_IPSCommunication.resatblishConnection(theShipData().m_SysConfig.GetSurveyorIP(), theShipData().m_SysConfig.GetConnectionPort());
                            if (theShipData().m_bConnectStatus) {
                                delete[] theShipData().m_pBuffer;
                                theShipData().m_pBuffer = new char[theShipData().m_uiBufferSize];
                            }
                        }
                    } else {
                        CPVCSApp::bIsShipDataThreadExit = true;
                        return 0;
                    }
                }

            } else { //if SendDataRequest fails
                if (CPVCSApp::m_bIsAlive) { //Go for reconnection, if PVCS still alive
                    int iSocketErrorCode = WSAGetLastError();

                    CString strError = "";
                    strError.Format("Socket Error Number = %d", iSocketErrorCode);
                    //for error loging
                    //CErrorLog obj;

                    //obj.WriteError("GetDataFromIPSThread","Send Data reuest Fails",strError);
                    //if 10054 = connection reset by peer, 10061 = connection refused, 10064 = Host is down, 10065 = No route to host, 10060 = Connection timed out
                    if (iSocketErrorCode == 10054 || iSocketErrorCode == 10061 || iSocketErrorCode == 10064 || iSocketErrorCode == 10065 || iSocketErrorCode == 10060) {
                        iSendFailCounter++;
                        if (iSendFailCounter == 2) {
                            iSendFailCounter = 0;
                            CSingleLock singlelock(&g_CS_TankMap);
                            singlelock.Lock();
                            theShipData().m_TemptankMap.clear();
                            singlelock.Unlock();
                            theShipData().m_bCurrentState = false;
                            theShipData().m_bConnectStatus = theShipData().m_IPSCommunication.resatblishConnection(theShipData().m_SysConfig.GetSurveyorIP(), theShipData().m_SysConfig.GetConnectionPort());
                            if (theShipData().m_bConnectStatus) {
                                delete[] theShipData().m_pBuffer;
                                theShipData().m_pBuffer = new char[theShipData().m_uiBufferSize];
                            }
                        }
                    } else { //for error 10053 (software caused connection abort or others
                        iRecFailCounter = 0;
                        theShipData().m_bCurrentState = false;
                        theShipData().m_bConnectStatus = theShipData().m_IPSCommunication.resatblishConnection(theShipData().m_SysConfig.GetSurveyorIP(), theShipData().m_SysConfig.GetConnectionPort());
                        if (theShipData().m_bConnectStatus) {
                            delete[] theShipData().m_pBuffer;
                            theShipData().m_pBuffer = new char[theShipData().m_uiBufferSize];
                        }
                    }

                } else {
                    CPVCSApp::bIsShipDataThreadExit = true;
                    return 0;
                }
            }
        } // if( m_bConnectStatus )
        else { //if( theShipData().m_bConnectStatus )
            if (CPVCSApp::m_bIsAlive) { //Go for reconnection, if PVCS still alive
                int iSocketErrorCode = WSAGetLastError();

                CString strError = "";
                strError.Format("Socket Error Number = %d", iSocketErrorCode);
                //for error loging
                //CErrorLog obj;

                //obj.WriteError("GetDataFromIPSThread","Connect status fails",strError);

                iSendFailCounter = 0;
                iRecFailCounter = 0;
                //clear buffer
                CSingleLock singlelock(&g_CS_TankMap);
                singlelock.Lock();
                theShipData().m_TemptankMap.clear();
                singlelock.Unlock();
                theShipData().m_bCurrentState = false;

                CSingleLock lock_freevalue(&g_CS_FreeValue);
                theShipData().LoadFreeValues();
                lock_freevalue.Unlock();
                theShipData().Aquire();
                theShipData().m_AlarmData.clear();
                theShipData().m_AckAlarmData.clear();
                theShipData().Release();

                theShipData().m_bConnectStatus = theShipData().m_IPSCommunication.resatblishConnection(theShipData().m_SysConfig.GetSurveyorIP(), theShipData().m_SysConfig.GetConnectionPort());
                {
                    delete[] theShipData().m_pBuffer;
                    theShipData().m_pBuffer = new char[theShipData().m_uiBufferSize];
                }
            } else {
                CPVCSApp::bIsShipDataThreadExit = true;
                return 0;
            }
        }
        Sleep(2000);
    }
    CPVCSApp::bIsShipDataThreadExit = true;
    return 0;

}
// Function to fill the Alarm data Vector
void CPvcsShipData::FillAlarmData(void) {

// added in NO
    bool status;
    status = false;
    m_xmlTankData.GetAlarmData();
    //m_xmlTankData.m_strAlarmData;
    int tot = (UINT)m_xmlTankData.m_strAlarmData.size();
    Aquire();

    m_AlarmData.clear();

    for (int j = 0; j < tot; j++) {
        AlarmDataStruct obj_AD;
        int membercounter = 0;
        CString str = m_xmlTankData.m_strAlarmData.at(j);
        CString tempstr = "";
        for (int i = 0; i < str.GetLength(); i++) {
            if (str.GetAt(i) != '|') {
                tempstr += str.GetAt(i);
            } else {
                membercounter += 1;
                if (membercounter == 1) {
                    obj_AD.Tankid = tempstr;
                    tempstr = " ";
                } else if (membercounter == 2) {
                    obj_AD.TankNameDisplay = tempstr;
                    tempstr = "";
                } else if (membercounter == 3) {
                    obj_AD.AlarmText = tempstr;
                    tempstr = "";
                } else if (membercounter == 4) {
                    obj_AD.Limit = tempstr;
                    tempstr = "";
                } else if (membercounter == 5) {
                    obj_AD.CurrentValue = tempstr;
                    tempstr = "";
                } else if (membercounter == 6 && status == false) {
                    obj_AD.Unit = tempstr;
                    tempstr = "";

                }

            }

        }
        obj_AD.TimeRaised = tempstr;
        tempstr = "";
        m_AlarmData.push_back(obj_AD);
    }
    Release();


}


// Function to fill the Acknowledged Alarm data Vector
void CPvcsShipData::FillAckAlarmData(void) {

// added in NO
    m_xmlTankData.GetAlarmData();
    //m_xmlTankData.m_strAlarmData;
    int tot = (UINT)m_xmlTankData.m_strAckAlarmData.size();
    m_AckAlarmData.clear();
    Aquire();
    for (int j = 0; j < tot; j++) {
        AckAlarmDataStruct obj_AD;
        int membercounter = 0;
        if (m_xmlTankData.m_strAckAlarmData.size() > 0) {
            //TRACE("\nAccessing m_strAckAlarmData -----------------------------------------");
            CString str = m_xmlTankData.m_strAckAlarmData.at(j);
            CString tempstr = "";
            for (int i = 0; i < str.GetLength(); i++) {
                if (str.GetAt(i) != '|') {
                    tempstr += str.GetAt(i);
                } else {
                    membercounter += 1;
                    if (membercounter == 1) {
                        obj_AD.Tankid = tempstr;
                        tempstr = " ";
                    } else if (membercounter == 2) {
                        obj_AD.TankNameDisplay = tempstr;
                        tempstr = "";
                    } else if (membercounter == 3) {
                        obj_AD.AlarmText = tempstr;
                        tempstr = "";
                    } else if (membercounter == 4) {
                        obj_AD.Limit = tempstr;
                        tempstr = "";
                    } else if (membercounter == 5) {
                        obj_AD.CurrentValue = tempstr;
                        tempstr = "";
                    } else if (membercounter == 6) {
                        obj_AD.Unit = tempstr;
                        tempstr = "";
                    } else if (membercounter == 7) {
                        obj_AD.TimeRaised = tempstr;
                        tempstr = "";
                    }

                }

            }
            obj_AD.TimeAck = tempstr;
            tempstr = "";
            m_AckAlarmData.push_back(obj_AD);
        }
    }
    Release();


}

void CPvcsShipData::Aquire(void) {
    WaitForSingleObject(AlarmVectorHandle1, INFINITE);
}

void CPvcsShipData::Release(void) {
    ReleaseMutex(AlarmVectorHandle1);
}

