#pragma once

#include "ProtocolManage.h"
#include "Serial.h"



class CServer
{
public:
	CServer() {}

	~CServer(void) {}

	bool Init(int port, BYTE sensorID, DeviceProtocol p, BYTE instrumentID);
	bool SendCommand(CPacket& pac);
	//bool GetResult(CPacket& pac);

	static UINT CommunicationLoopThread(LPVOID pParam);

	BYTE m_instrumentID; // ���
	//BYTE m_sensorID; // ��λ��
	BYTE m_meterID[5]; // �Ǳ�ID

private:

	CSerial m_serial;
	CProtocolManage m_pm;

	CPacket m_paback;
	CMutex m_serverMutex;

	int m_comPort;
	DeviceProtocol m_protocol;
	bool GetSystemSerialComport(CArray<CString,CString>&);//ty changed
	bool serial_port_found;//ty changed
	CArray<CString,CString> comarray;//ty changed
};
