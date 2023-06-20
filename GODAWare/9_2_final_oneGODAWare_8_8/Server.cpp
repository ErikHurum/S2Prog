#include "StdAfx.h"
#include "Server.h"
#include "Packet.h"

#include "MFC.h"
#include "ServerUI.h"

bool comOpenSuccessed = FALSE;
//CEvent comOpened;

//CEvent UIPrepared;




struct ThreadParam
{
	DeviceProtocol dp;
};

bool CServer::Init(int port, BYTE /*unuse sensorID*/, DeviceProtocol p, BYTE instrumentID)
{
	m_comPort = port;
	//m_sensorID = sensorID;
	m_protocol = p;
	m_instrumentID = instrumentID;


	// 在这里先测试一下连接，连上了就断开，正式启动。连不上就返回。

	CProtocolManage pm;
if(port==0)
	{
		serial_port_found=GetSystemSerialComport(comarray);
		if(serial_port_found==0) return false;
		int num_of_sc,port_auto=0,device_found;
		CString c_com_num;
		num_of_sc=comarray.GetCount();
		while(num_of_sc)
		{	
			device_found=1;
			c_com_num=comarray.GetAt(num_of_sc-1);
			LPCTSTR p_com = c_com_num;
			CString c_com_num_new(p_com);
			c_com_num_new=c_com_num_new.Mid(3);
			port_auto = _tcstoul(c_com_num_new, NULL, 10 );
			num_of_sc--;
		//}
		
		if (p==ScanjetHART)
	{
		m_serial.m_sp.Open(port_auto, 9600);
		//m_serial.Init(p, port, CBR_9600, NOPARITY, 8, ONESTOPBIT);
		//m_serial.OVERTIME = 3000;
	}
	else if (p==HART)
	{
		m_serial.m_sp.Open(port_auto,1200,CSerialPort::OddParity);
		//m_serial.Init(p, port, CBR_1200, ODDPARITY, 8, ONESTOPBIT);
		//m_serial.OVERTIME = 3000;
	}
	else
	{
		m_serial.m_sp.Open(port_auto, 9600);
		//m_serial.Init(p, port, CBR_9600, NOPARITY, 8, ONESTOPBIT);
	}

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 3000;//ty changed this value, original value is 500
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 500;

	m_serial.m_sp.SetTimeouts(CommTimeOuts);


	if (!m_serial.m_sp.IsOpen())
	{
		//return false;
		device_found=0;
	}

	//m_serial.ClearError(
	CPacket pa;

	pa.cmdID = CONNECT_CMD;

	BYTE frame[200*200];
	int frameLen;
	if ( !pm.MakeFrame(p, pa, frame, frameLen) )
	{
		//return false;
		device_found=0;
	}

	::Sleep(1000);

	if ( m_serial.Write(frame, frameLen)  != frameLen)
	{
		TRACE("写串口错\n");
		//return false;
		device_found=0;
	}

	BYTE frameBack[200*200];
	BYTE frameBack1[200*200];
	BYTE frameBack2[200*200];
	int frameLenBack = 0;

	int bytesLeft;
	switch (p)
	{
	case ScanjetHART:
	case HART:

		if ( m_serial.Read(frameBack1, 15)  != 15)
		{
			TRACE("读串口错\n");
			//return false;
			device_found=0;
			
		}

		if ( frameBack1[5]&0x80 ) // 认为有且只有一个扩展字节，即frameBack1[11]
		{
			bytesLeft = frameBack1[11]*256 + frameBack1[13] + 5;
			if ( m_serial.Read( frameBack2, bytesLeft)  != bytesLeft)
			{
				//return false;
				device_found=0;
			}
			memcpy(frameBack, frameBack1, 15);
			memcpy(frameBack+15, frameBack2, bytesLeft);
			frameLenBack = 15 + bytesLeft;
		}
		else // 认为无扩展字节
		{
			if ( m_serial.Read( frameBack2, (int)(frameBack1[8]) )  != (int)(frameBack1[8]))
			{
				//return false;
				device_found=0;
			}
			memcpy(frameBack, frameBack1, 15);
			memcpy(frameBack+15, frameBack2, (int)(frameBack1[8]));
			frameLenBack = 15 + (int)(frameBack1[8]);
		}
		break;

	case Modbus:
		// TODO Modbus处理
		if (m_serial.Read(frameBack1, 4)  != 4)
		{
			//return false;
			device_found=0;
		}

		bytesLeft = static_cast<int>(frameBack1[3])*256 + static_cast<int>(frameBack1[2]) - 4;
		if ( m_serial.Read( frameBack2, bytesLeft)  != bytesLeft)
		{
			//return false;
			device_found=0;
		}
		memcpy(frameBack, frameBack1, 4);
		memcpy(frameBack+4, frameBack2, bytesLeft);
		frameLenBack = 4 + bytesLeft;

		break;

	default:
		//ASSERT(FALSE);
		device_found=0;
	}
	
	CPacket paback;

	if ( !pm.ParseFrame(p, paback, frameBack, frameLenBack) )
	{
		//return false;
		device_found=0;
	}
	
	if (paback.cmdID != CONNECT_OK)
	{
		//return false;
		device_found=0;
	}
	
	if(device_found==1)
		{
		return true;
		}
	}//while
	return false;
	}//if

	else{
	if (p==ScanjetHART)
	{
		m_serial.m_sp.Open(port, 9600);
		//m_serial.Init(p, port, CBR_9600, NOPARITY, 8, ONESTOPBIT);
		//m_serial.OVERTIME = 3000;
	}
	else if (p==HART)
	{
		m_serial.m_sp.Open(port,1200,CSerialPort::OddParity);
		//m_serial.Init(p, port, CBR_1200, ODDPARITY, 8, ONESTOPBIT);
		//m_serial.OVERTIME = 3000;
	}
	else
	{
		m_serial.m_sp.Open(port, 9600);
		//m_serial.Init(p, port, CBR_9600, NOPARITY, 8, ONESTOPBIT);
	}

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant =3000;//ty changed this value, original value is 500
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 500;

	m_serial.m_sp.SetTimeouts(CommTimeOuts);


	if (!m_serial.m_sp.IsOpen())
	{
		return false;
	}

	//m_serial.ClearError(
	CPacket pa;

	pa.cmdID = CONNECT_CMD;

	BYTE frame[200*200];
	int frameLen;
	if ( !pm.MakeFrame(p, pa, frame, frameLen) )
	{
		return false;
	}

	::Sleep(1000);

	if ( m_serial.Write(frame, frameLen)  != frameLen)
	{
		TRACE("写串口错\n");
		return false;
	}

	BYTE frameBack[200*200];
	BYTE frameBack1[200*200];
	BYTE frameBack2[200*200];
	int frameLenBack = 0;

	int bytesLeft;
	switch (p)
	{
	case ScanjetHART:
	case HART:

		if ( m_serial.Read(frameBack1, 15)  != 15)
		{
			TRACE("读串口错\n");
			return false;
		}

		if ( frameBack1[5]&0x80 ) // 认为有且只有一个扩展字节，即frameBack1[11]
		{
			bytesLeft = frameBack1[11]*256 + frameBack1[13] + 5;
			if ( m_serial.Read( frameBack2, bytesLeft)  != bytesLeft)
			{
				return false;
			}
			memcpy(frameBack, frameBack1, 15);
			memcpy(frameBack+15, frameBack2, bytesLeft);
			frameLenBack = 15 + bytesLeft;
		}
		else // 认为无扩展字节
		{
			if ( m_serial.Read( frameBack2, (int)(frameBack1[8]) )  != (int)(frameBack1[8]))
			{
				return false;
			}
			memcpy(frameBack, frameBack1, 15);
			memcpy(frameBack+15, frameBack2, (int)(frameBack1[8]));
			frameLenBack = 15 + (int)(frameBack1[8]);
		}
		break;

	case Modbus:
		// TODO Modbus处理
		if (m_serial.Read(frameBack1, 4)  != 4)
		{
			return false;
		}

		bytesLeft = static_cast<int>(frameBack1[3])*256 + static_cast<int>(frameBack1[2]) - 4;
		if ( m_serial.Read( frameBack2, bytesLeft)  != bytesLeft)
		{
			return false;
		}
		memcpy(frameBack, frameBack1, 4);
		memcpy(frameBack+4, frameBack2, bytesLeft);
		frameLenBack = 4 + bytesLeft;

		break;

	default:
		ASSERT(FALSE);
	}
	
	CPacket paback;

	if ( !pm.ParseFrame(p, paback, frameBack, frameLenBack) )
	{
		return false;
	}
	
	if (paback.cmdID != CONNECT_OK)
	{
		return false;
	}


	return true;
	}//else
}


bool CServer::SendCommand(CPacket& pa)
{
	CSingleLock singleLock(&m_serverMutex);
	singleLock.Lock();
	if (pa.cmdID==DISCONNECT_CMD)
	{
		// TODO 这里需要干啥吗
	}

	CPacket paback;

	if (pa.cmdID==GETDEVICEADDR_CMD)
	{
		paback.cmdID = GETDEVICEADDR_OK;
		paback.data.Add(theApp.m_pServer->m_instrumentID);
		m_paback = paback;
		pa = paback;
		return true;
	}


	BYTE frame[200*200];
	int frameLen;
	if ( !m_pm.MakeFrame(this->m_protocol, pa, frame, frameLen) )
	{
		DMT_TRACE("Make Connect Frame Failed. \n");
	}

	BYTE frameBack[200*200];
	BYTE frameBack1[200*200];
	BYTE frameBack2[200*200];
	int frameLenBack = 0;
	int tbytesRead ;

	int tryTimes = 0;
	while( (tryTimes++)<1 )
	{
		if ( m_serial.Write(frame, frameLen)  !=  frameLen)
		{
			TRACE("写串口失败\n");
			continue;
		}
		
		int bytesLeft;
		switch (m_protocol)
		{
		case ScanjetHART:
		case HART:

			tbytesRead = m_serial.Read(frameBack1, 15);
			if ( tbytesRead  != 15)
			{
				TRACE("读串口1失败  %d\n", tbytesRead);
				continue;
			}

			if ( frameBack1[5]&0x80 ) // 认为有且只有一个扩展字节，即frameBack1[11]
			{
				bytesLeft = frameBack1[11]*256 + frameBack1[13] + 5;
				if ( m_serial.Read( frameBack2, bytesLeft)  !=bytesLeft)
				{
					TRACE("读串口2_有扩展失败\n");
					continue;
				}
				memcpy(frameBack, frameBack1, 15);
				memcpy(frameBack+15, frameBack2, bytesLeft);
				frameLenBack = 15 + bytesLeft;
			}
			else // 认为无扩展字节
			{
				if (m_serial.Read( frameBack2, (int)(frameBack1[8]) )  != (int)(frameBack1[8])  )
				{
					TRACE("读串口2_无扩展失败\n");
					continue;
				}
				memcpy(frameBack, frameBack1, 15);
				memcpy(frameBack+15, frameBack2, (int)(frameBack1[8]));
				frameLenBack = 15 + (int)(frameBack1[8]);
			}
			break;

		case Modbus:
			// TODO Modbus处理
			//Sleep(300);
			if ( m_serial.Read(frameBack1, 4) != 4)
			{
				//serial->Close();
				//serial->Open();
				TRACE("read serial error\n");
				continue;
			}

			bytesLeft = static_cast<int>(frameBack1[3])*256 + static_cast<int>(frameBack1[2]) - 4;
			if ( m_serial.Read( frameBack2, bytesLeft)  != bytesLeft)
			{
				//serial->Close();
				//serial->Open();
				TRACE("read serial error\n");
				continue;
			}
			memcpy(frameBack, frameBack1, 4);
			memcpy(frameBack+4, frameBack2, bytesLeft);
			frameLenBack = 4 + bytesLeft;

			break;

		default:
			ASSERT(FALSE);
		}

		if ( m_pm.ParseFrame(m_protocol, paback, frameBack, frameLenBack) )
		{
			break;
		}
		else
			DMT_TRACE("Parse Connect Frame Failed. \n");
	}

	if (paback.cmdID==CONNECT_OK && (m_protocol==HART || m_protocol==ScanjetHART) && paback.data.GetSize() == 5)
	{
		theApp.m_pServer->m_meterID[0] = paback.data[0];
		theApp.m_pServer->m_meterID[1] = paback.data[1];
		theApp.m_pServer->m_meterID[2] = paback.data[2];
		theApp.m_pServer->m_meterID[3] = paback.data[3];
		theApp.m_pServer->m_meterID[4] = paback.data[4];
	}
	m_paback = paback;
	pa = paback;
	return true;
}

//bool CServer::GetResult(CPacket& pac)
//{
//	pac = m_paback;
//	return true;
//}


////////////ty////////////////////////
bool CServer::GetSystemSerialComport(CArray<CString,CString>&)  
{  
    HKEY hKey=NULL;  
  
    comarray.RemoveAll();  
  
   if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"),0,KEY_READ,&hKey)!=ERROR_SUCCESS)  
    {  
        return FALSE;  
    }  
  
   CString valuename,databuffer;  
  DWORD valuenamebufferlength=200,valuetype,databuddersize=200;  
  
    int i=0;  
    while(RegEnumValue(hKey,i++,valuename.GetBuffer(200),&valuenamebufferlength,NULL,&valuetype,(BYTE*)databuffer.GetBuffer(200),&databuddersize) != ERROR_NO_MORE_ITEMS)  
    {  
       comarray.Add(CString(databuffer));  
  
        databuddersize=200;  
        valuenamebufferlength=200;  
    }  
/*	CString a;
	for(i=0;i<5;i++)
	{
		a=comarray.GetAt(1);
	}*/
  
   RegCloseKey(hKey);  
  
    return TRUE;  
}  


/////////////ty/////////////////////////