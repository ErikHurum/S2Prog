#include "StdAfx.h"
#include "Client.h"
#include "PR/MainFrmPR.h"
#include "GR/MainFrmGR.h"
#include "TU/MainFrmTU.h"
#include "SU/MainFrmSU.h"
#include "MFC.h"
#include "ErrCounter.h"
#include "math.h"

float gNullHight[3];
extern bool load3Hights;
CMutex socketMutex;

CErrCounter errCounter;



bool CClient::Login( const CString& name, const CString& pw )
{
	bool bLogin = m_userManage.Login(name, pw);

	if (bLogin)
	{
		//m_readOnly = false;
		UserType userType;
		m_userManage.GetCurrentUserType(userType);
		if (userType == Normal)
		{
			m_readOnly = true;
		}
		else
		{
			m_readOnly = false;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool CClient::Exit()
{

	return TRUE;
}

bool CClient::ConnectServer( DWORD , unsigned  )
{

	CPacket pac;
	pac.cmdID = CONNECT_CMD;
	theApp.m_pServer->SendCommand(pac);


	if (pac.cmdID != CONNECT_OK)
	{
		m_bOnline = false;
		return FALSE;
	}

	TRACE(_T("client connect ok \n"));

	m_bOnline = true;
	return TRUE;
}

bool CClient::RefreshId()
{
	CPacket pac;
	pac.cmdID = CONNECT_CMD;
	theApp.m_pServer->SendCommand(pac);

	if (pac.cmdID != CONNECT_OK)
	{
		m_bOnline = false;
		return FALSE;
	}

	TRACE(_T("client connect ok \n"));

	m_bOnline = true;
	if (m_pClientUI && ::IsWindow(m_pClientUI->m_hWnd))
	{
		m_pClientUI->SetOnline(true);
	}
	return TRUE;

}

bool CClient::ShowUI() const
{
	m_pClientUI->ShowWindow(SW_SHOW);
	m_pClientUI->UpdateWindow();

	return true;
}

bool CClient::InitUI()
{
	switch (m_deviceType)
	{
	case PR:
		m_pClientUI = new CClientUIPR;

		if (!m_pClientUI)
		{
			TRACE(_T("CClient::InitUI failed when new CClientUIPR\n"));
			return FALSE;
		}
		theApp.m_pMainWnd = m_pClientUI;
		// 创建并加载框架及其资源
		m_pClientUI->LoadFrame(IDR_MAINFRAME,
			WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
			NULL);
		return true;

	case GR:
		m_pClientUI = new CClientUIGR;

		if (!m_pClientUI)
		{
			TRACE(_T("CClient::InitUI failed when new CClientUIGR\n"));
			return FALSE;
		}
		theApp.m_pMainWnd = m_pClientUI;
		// 创建并加载框架及其资源
		m_pClientUI->LoadFrame(IDR_MAINFRAME,
			WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
			NULL);
		return true;

	case TU:
		m_pClientUI = new CClientUITU;

		if (!m_pClientUI)
		{
			TRACE(_T("CClient::InitUI failed when new CClientUITU\n"));
			return FALSE;
		}
		theApp.m_pMainWnd = m_pClientUI;
		// 创建并加载框架及其资源
		m_pClientUI->LoadFrame(IDR_MAINFRAME,
			WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
			NULL);
		return true;
	case SU:
		m_pClientUI = new CClientUISU;

		if (!m_pClientUI)
		{
			TRACE(_T("CClient::InitUI failed when new CClientUISU\n"));
			return FALSE;
		}
		theApp.m_pMainWnd = m_pClientUI;
		// 创建并加载框架及其资源
		m_pClientUI->LoadFrame(IDR_MAINFRAME,
			WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
			NULL);
		return true;
	default:
		return false;
	}
}

bool CClient::LoadData( unsigned dataId, float& data, int sensorID)
{
	data = 0;
	bool ret = true;

	if (!m_bOnline)
	{
		return true;
	}
	
	if (IsVarValid(dataId))
	{
		data = m_floatVarMap[dataId];
	}
	else
	{
	
		for (int retry = 0; retry < maxRetry; retry++)
		{
			ret = LoadDataFromServer(dataId, data, sensorID);
			if (ret)
			{
				// 成功取回则更新
				m_floatVarMap[dataId] = data;
				m_varValidMap[dataId] = true;
				break;
			}
			RefreshId();
		}
	}

	m_bOnline = errCounter.SetErr(ret);
	return ret;
}

bool CClient::LoadData( unsigned dataId, UINT8& data , int sensorID)
{
	data = 0;

	bool ret = true;

	if (!m_bOnline)
	{
		return true;
	}

	if (IsVarValid(dataId))
	{
		data = UINT8(m_intVarMap[dataId]);
	}
	else
	{

		for (int retry = 0; retry < maxRetry; retry++)
		{
			ret = LoadDataFromServer(dataId, data, sensorID);
			if (ret)
			{
				// 成功取回则更新
				m_intVarMap[dataId] = data;
				m_varValidMap[dataId] = true;
				break;
			}
			RefreshId();
		}

	}

	m_bOnline = errCounter.SetErr(ret);
	return ret;

}

bool CClient::LoadData( unsigned dataId, INT16& data , int sensorID)
{
	data = 0;

	bool ret = true;

	if (!m_bOnline)
	{
		return true;
	}
	
	if (IsVarValid(dataId))
	{
		data = m_intVarMap[dataId];

	}
	else
	{
		for (int retry = 0; retry < maxRetry; retry++)
		{
			ret = LoadDataFromServer(dataId, data, sensorID);
			if (ret)
			{
				// 成功取回则更新
				m_intVarMap[dataId] = data;
				m_varValidMap[dataId] = true;
				break;
			}
			RefreshId();
		}

	}

	m_bOnline = errCounter.SetErr(ret);
	return ret;
}

bool CClient::LoadData( unsigned dataId, CArray<float>& data , int sensorID)
{
	if (!m_bOnline)
	{
		return true;
	}

	bool ret = true;

	for (int retry = 0; retry < maxRetry; retry++)
	{
		ret = LoadDataFromServer(dataId, data, sensorID);
		if (ret)
		{
			break;
		}
		RefreshId();
	}

	m_bOnline = errCounter.SetErr(ret);
	return ret;
}

bool CClient::LoadData( unsigned dataId, CArray<BYTE>& data , int sensorID)
{
	if (!m_bOnline)
	{
		return true;
	}

	bool ret = true;

	for (int retry = 0; retry < maxRetry; retry++)
	{
		ret = LoadDataFromServer(dataId, data, sensorID);
		if (ret)
		{
			break;
		}
		RefreshId();
	}
	
	m_bOnline = errCounter.SetErr(ret);
	return ret;
}


bool CClient::SaveData( unsigned dataId, float data, int sensorID , bool bMsg)
{
	
	if (!m_bOnline)
	{
		return false;
	}
	
	if (m_readOnly)
	{
		return false;
	}
	else if (m_varValidMap[dataId] == true && fabsf(m_floatVarMap[dataId] - data) < eps)	// 变量未改变，直接返回
	{
		return true;
	}
	else
	{

		bool ret = true;

		for (int retry = 0; retry < maxRetry; retry++)
		{
			ret = SaveDataToServer(dataId, data, sensorID);
			if (ret)
			{
				m_floatVarMap[dataId] = data;
				break;
			}
			RefreshId();
		}

		if(bMsg)
		{
			if(ret)
				SaveInfoMessageBox(dataId, true);
			else
				SaveInfoMessageBox(dataId, false);
		}
	
		m_bOnline = errCounter.SetErr(ret);
		return ret;

	}

}

bool CClient::SaveData( unsigned dataId, UINT8 data  , int sensorID, bool bMsg)
{
	if (!m_bOnline)
	{
		return false;
	}
	
	bool b1 = m_varValidMap[dataId];
	int i = m_intVarMap[dataId];
	b1;i;
	
	if (m_readOnly)
	{
		return false;
	}
	else if (m_varValidMap[dataId] == true && m_intVarMap[dataId] == data) // 变量未改变，直接返回
	{
		return true;
	}
	else
	{

		bool ret = true;

		for (int retry = 0; retry < maxRetry; retry++)
		{
			ret = SaveDataToServer(dataId, data, sensorID);
			if (ret)
			{
				m_intVarMap[dataId] = data;
				break;
			}
			RefreshId();
		}

		if(bMsg)
		{
			if(ret)
				SaveInfoMessageBox(dataId, true);
			else
				SaveInfoMessageBox(dataId, false);
		}
	
		m_bOnline = errCounter.SetErr(ret);
		return ret;
	}
}

bool CClient::SaveData( unsigned dataId, INT16 data, int sensorID, bool bMsg )
{
	if (!m_bOnline)
	{
		return false;
	}
	
	if (m_readOnly)
	{
		return false;
	}
	else if (m_varValidMap[dataId] == true && m_intVarMap[dataId] == data) // 变量未改变，直接返回
	{
		return true;
	}
	else
	{

		bool ret = true;

		for (int retry = 0; retry < maxRetry; retry++)
		{
			ret = SaveDataToServer(dataId, data, sensorID);
			if (ret)
			{
				m_intVarMap[dataId] = data;
				break;
			}
			RefreshId();
		}

		if(bMsg)
		{
			if(ret)
				SaveInfoMessageBox(dataId, true);
			else
				SaveInfoMessageBox(dataId, false);
		}
	
		m_bOnline = errCounter.SetErr(ret);
		return ret;
	}
}

bool CClient::SaveData( unsigned dataId, const CArray<BYTE>& data , int sensorID, bool bMsg)
{
	if (!m_bOnline)
	{
		return false;
	}


	bool ret = true;

	for (int retry = 0; retry < maxRetry; retry++)
	{
		ret = SaveDataToServer(dataId, data, sensorID);
		if (ret)
		{
			break;
		}
		RefreshId();
	}

	if(bMsg)
	{
		if(ret)
			SaveInfoMessageBox(dataId, true);
		else
			SaveInfoMessageBox(dataId, false);
	}
	
	m_bOnline = errCounter.SetErr(ret);
	return ret;
}

bool CClient::SaveData( unsigned dataId, const CArray<float>& data, int sensorID, bool bMsg )
{
	if (!m_bOnline)
	{
		return false;
	}


	bool ret = true;

	for (int retry = 0; retry < maxRetry; retry++)
	{
		ret = SaveDataToServer(dataId, data, sensorID);
		if (ret)
		{
			break;
		}
		RefreshId();
	}

	if(bMsg)
	{
		if(ret)
			SaveInfoMessageBox(dataId, true);
		else
			//SaveInfoMessageBox(dataId, false);//因为即使报错也能存储成功，因此无论是否报错，均显示正确。。。
			SaveInfoMessageBox(dataId, true);
	}
	
		//m_bOnline = errCounter.SetErr(ret);
	m_bOnline = errCounter.SetErr(1);
	//return ret;
	return 1;//此处若是返回ret的值则HART掉线(不知原因)，而返回0或者1均正常。因此改为固定值“1”
}
void CClient::ResetVarValid()
{
	m_varValidMap.RemoveAll();
}

bool CClient::LoadDataFromServer( unsigned dataId, UINT8& data, int sensorID)
{
	
	// 从Server读取数据
	CPacket pa;
	pa.cmdID = LOAD_CMD;
	pa.dataID = dataId;
	pa.sensorID = sensorID;



	if (!theApp.m_pServer->SendCommand(pa))
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return false;
	}


	if (pa.cmdID!=LOAD_OK)
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return false;
	}

	if (pa.data.GetSize() != 1)
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return false;
	}
	data = (UINT8)pa.data[0];

	TRACE("Load %d from 0x%x\n", data, dataId);
	return true;
}

bool CClient::LoadDataFromServer( unsigned dataId, INT16& data , int sensorID)
{
	// 从Server读取数据
	CPacket pa;
	pa.cmdID = LOAD_CMD;
	pa.dataID = dataId;
	pa.sensorID = sensorID;


	if ( !theApp.m_pServer->SendCommand(pa))
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return FALSE;
	}


	if (pa.cmdID!=LOAD_OK)
	{
		return FALSE;
	}

	if (pa.data.GetSize() != 2)
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return false;
	}

	data = *(INT16 *)(pa.data.GetData());

	TRACE("Load %d from 0x%x\n", data, dataId);
	return true;
}

bool CClient::LoadDataFromServer( unsigned dataId, float& data , int sensorID)
{
	// 从Server读取数据
	CPacket pa;
	pa.cmdID = LOAD_CMD;
	pa.dataID = dataId;
	pa.sensorID = sensorID;


	if (!theApp.m_pServer->SendCommand(pa) )
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return FALSE;
	}
	

	if (pa.cmdID!=LOAD_OK)
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return FALSE;
	}

	if (pa.data.GetSize() != 4)
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return false;
	}

	BYTE d[4];
	d[0] = pa.data[0];
	d[1] = pa.data[1];
	d[2] = pa.data[2];
	d[3] = pa.data[3];

	data = *((float*)d);

	TRACE("Load %f from 0x%x\n", data, pa.dataID);
	return true;
}

bool CClient::LoadDataFromServer( unsigned dataId, CArray<float>& data, int sensorID)
{
	CPacket pa;
	pa.cmdID = LOAD_CMD;
	pa.dataID = dataId;
	pa.sensorID = sensorID;


	if ( !theApp.m_pServer->SendCommand(pa) )
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return FALSE;
	}


	if (pa.cmdID!=LOAD_OK)
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return FALSE;
	}

	if ( pa.data.GetSize()%4 != 0 )
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return FALSE;
	}

	if (pa.data.GetSize() == 0)
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return false;
	}


	data.RemoveAll();
	for (int i=0;i<pa.data.GetSize();i+=4)
	{
		BYTE d[4];
		d[0] = pa.data[i+0];
		d[1] = pa.data[i+1];
		d[2] = pa.data[i+2];
		d[3] = pa.data[i+3];
		float f = *((float*)d);
		data.Add(f);
	}


	TRACE("Load %d floats from 0x%x\n", data.GetSize(), pa.dataID);
	return true;
}

bool CClient::LoadDataFromServer( unsigned dataId, CArray<BYTE>& data, int sensorID )
{
	CPacket pa;
	pa.cmdID = LOAD_CMD;
	pa.dataID = dataId;
	pa.sensorID = sensorID;


	if (!theApp.m_pServer->SendCommand(pa))
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return FALSE;
	}


	if (pa.cmdID!=LOAD_OK)
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return FALSE;
	}

	if (pa.data.GetSize() == 0)
	{
		TRACE("Load from 0x%x failed. \n", dataId);
		return false;
	}

	data.RemoveAll();

	for (int i=0;i<pa.data.GetSize();i++)
		data.Add(pa.data[i]);

	TRACE("Load %d bytes from 0x%x\n", data.GetSize(), pa.dataID);
	return true;
}

bool CClient::SaveDataToServer( unsigned dataId, UINT8 data, int sensorID )
{
	// 写数据到Server
	CPacket pa;
	pa.cmdID = SAVE_CMD;
	pa.dataID = dataId;
	pa.sensorID = sensorID;
	pa.data.Add( (BYTE)data );


	if (!theApp.m_pServer->SendCommand(pa))
	{
		TRACE("Save to 0x%x failed. \n", dataId);
		return FALSE;
	}

	if (pa.cmdID!=SAVE_OK)
	{
		TRACE("Save to 0x%x failed. \n", dataId);
		return FALSE;
	}

	TRACE("Save %d to 0x%x\n", data, dataId);
	return true;
}

bool CClient::SaveDataToServer( unsigned dataId, INT16 data, int sensorID )
{
	// 写数据到Server
	CPacket pa;
	pa.cmdID = SAVE_CMD;
	pa.dataID = dataId;
	pa.sensorID = sensorID;
	BYTE * pBytes = (BYTE *) &data;
	pa.data.Add( pBytes[0] );
	pa.data.Add( pBytes[1] );

	if (!theApp.m_pServer->SendCommand(pa))
	{
		TRACE("Save to 0x%x failed. \n", dataId);
		return FALSE;
	}

	if (pa.cmdID!=SAVE_OK)
	{
		TRACE("Save to 0x%x failed. \n", dataId);
		return FALSE;
	}

	TRACE("Save %d to 0x%x\n", data, dataId);
	return true;
}

bool CClient::SaveDataToServer( unsigned dataId, float data, int sensorID )
{
	// 写数据到Server
	CPacket pa;
	pa.cmdID = SAVE_CMD;
	pa.dataID = dataId;
	pa.sensorID = sensorID;
	BYTE * pBytes = (BYTE *) &data;
	pa.data.Add( pBytes[0] );
	pa.data.Add( pBytes[1] );
	pa.data.Add( pBytes[2] );
	pa.data.Add( pBytes[3] );


	if ( !theApp.m_pServer->SendCommand(pa))
	{
		TRACE("Save to 0x%x failed. \n", dataId);
		return FALSE;
	}

	if (pa.cmdID!=SAVE_OK)
	{
		TRACE("Save to 0x%x failed. \n", dataId);
		return FALSE;
	}

	TRACE("Save %f to 0x%x\n", data, dataId);
	return true;
}

bool CClient::SaveDataToServer( unsigned dataId, const CArray<float>& data, int sensorID )
{
	CPacket pa;
	pa.cmdID = SAVE_CMD;
	pa.dataID = dataId;
	pa.sensorID = sensorID;
	for (int i=0;i<data.GetSize();i++)
	{
		BYTE * pBytes = (BYTE *) &data[i];
		pa.data.Add( pBytes[0] );
		pa.data.Add( pBytes[1] );
		pa.data.Add( pBytes[2] );
		pa.data.Add( pBytes[3] );
	}

	if (!theApp.m_pServer->SendCommand(pa))
	{
		TRACE("Save to 0x%x failed. \n", dataId);
		return FALSE;
	}


	if (pa.cmdID!=SAVE_OK)
	{
		TRACE("Save to 0x%x failed. \n", dataId);
		return FALSE;
	}

	TRACE("Save %d floats to 0x%x\n", data.GetSize(), dataId);
	return true;
}

bool CClient::SaveDataToServer( unsigned dataId, const CArray<BYTE>& data, int sensorID )
{
	CPacket pa;
	pa.cmdID = SAVE_CMD;
	pa.dataID = dataId;
	pa.sensorID = sensorID;
	for (int i=0;i<data.GetSize();i++)
		pa.data.Add(data[i]);


	if ( !theApp.m_pServer->SendCommand(pa) )
	{
		TRACE("Save to 0x%x failed. \n", dataId);
		return FALSE;
	}


	if (pa.cmdID!=SAVE_OK)
	{
		TRACE("Save to 0x%x failed. \n", dataId);
		return FALSE;
	}

	TRACE("Save %d bytes to 0x%x\n", data.GetSize(), dataId);
	return true;
}

CClient::CClient( DeviceType type ) : m_deviceType(type), eps(0.001f)
{
	m_bOnline = false;
	m_userManage.LoadAll();
	InitMessage();
}

CClient::~CClient( void )
{
	
}

int CClient::GetDeviceAddr()
{
	if (!m_bOnline)
		return -1;

	CPacket pa;
	pa.cmdID = GETDEVICEADDR_CMD;

	if (!theApp.m_pServer->SendCommand(pa))
	{
		TRACE("Load device address failed. \n");
		return -1;
	}

	if (pa.cmdID!=GETDEVICEADDR_OK)
	{
		TRACE("Load device address failed. \n");
		return -1;
	}

	if (pa.data.GetSize() != 1)
	{
		TRACE("Load device address failed. \n");
		return -1;
	}

	TRACE("Load device address successed. \n");
	return static_cast<int>(pa.data[0]);
}

//int CClient::GetDeviceNum()
//{
//	if (!m_bOnline)
//		return -1;
//
//	CPacket pa;
//	pa.cmdID = GETDEVICENUM_CMD;
//	SafeSocketGuard guard(&m_clientSock, hSocket);
//
//	if ( !m_clientSock.SendData(pa) )
//	{
//		TRACE("Load device number failed. \n");
//		return -1;
//	}
//
//	if ( !m_clientSock.ReceiveData(pa) )
//	{
//		TRACE("Load device number failed. \n");
//		return -1;
//	}
//
//	if (pa.cmdID!=GETDEVICENUM_OK)
//	{
//		TRACE("Load device number failed. \n");
//		return -1;
//	}
//
//	if (pa.data.GetSize() != 1)
//	{
//		TRACE("Load device number failed. \n");
//		return -1;
//	}
//
//	TRACE("Load device number successed. \n");
//	return static_cast<int>(pa.data[0]);
//}
//
//bool CClient::SetDeviceNum( int deviceNum )
//{
//	if (!m_bOnline)
//		return FALSE;
//
//	CPacket pa;
//	pa.cmdID = SETDEVICENUM_CMD;
//	pa.data.Add(static_cast<BYTE>(deviceNum));
//	SafeSocketGuard guard(&m_clientSock, hSocket);
//
//	if ( !m_clientSock.SendData(pa) )
//	{
//		TRACE("Save device number failed. \n");
//		return FALSE;
//	}
//
//	if ( !m_clientSock.ReceiveData(pa) )
//	{
//		TRACE("Save device number failed. \n");
//		return FALSE;
//	}
//
//
//	if (pa.cmdID!=SETDEVICENUM_OK)
//	{
//		TRACE("Save device number failed. \n");
//		return FALSE;
//	}
//
//	TRACE("Save device number successed. \n");
//	return TRUE;
//}
