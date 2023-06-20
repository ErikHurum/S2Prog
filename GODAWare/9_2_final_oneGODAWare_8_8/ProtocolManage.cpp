// ProtocolManage.cpp: implementation of the CProtocolManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProtocolManage.h"
#include "MFC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CMFCApp theApp;

enum ModbusID
{
	MODBUS_CONNECT1 = 0xF8, 
	MODBUS_CONNECT2 = 'C', 
	MODBUS_GET = 'G', 
	MODBUS_SET = 'S', 
	MODBUS_DIRECTIVE = 'D', 
	MODBUS_ERROR = 'E'
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProtocolManage::CProtocolManage()
{

}

CProtocolManage::~CProtocolManage()
{

}

bool CProtocolManage::MakeFrame(DeviceProtocol dp, const CPacket &pa, BYTE *frame, int &frameLen)
{
	if (dp==HART)
	{
		BYTE *pBytes = new BYTE[pa.data.GetSize()*sizeof(BYTE)+20];
		int nBytesLen;
		if ( !MakeModbusFrame((BYTE)pa.cmdID, theApp.m_pServer->m_instrumentID, (BYTE)pa.sensorID, (INT16)pa.dataID, pa.data, pBytes, nBytesLen) )
		{
			delete [] pBytes;
			return FALSE;
		}

		if (pa.cmdID==CONNECT_CMD)
		{
			nBytesLen = 0;
		}

		if ( !MakeHartFrame((BYTE)pa.cmdID, nBytesLen, pBytes, frame, frameLen) )
		{
			delete [] pBytes;
			return FALSE;
		}
		delete [] pBytes;
		return TRUE;
	}
	else if (dp==ScanjetHART)
	{
		BYTE *pBytes = new BYTE[pa.data.GetSize()*sizeof(BYTE)+20];
		int nBytesLen;
		if ( !MakeModbusFrame((BYTE)pa.cmdID, theApp.m_pServer->m_instrumentID, (BYTE)pa.sensorID, (INT16)pa.dataID, pa.data, pBytes, nBytesLen) )
		{
			delete [] pBytes;
			return FALSE;
		}

		if (pa.cmdID==CONNECT_CMD)
		{
			nBytesLen = 0;
		}

		if ( !MakeScanjetHARTFrame((BYTE)pa.cmdID, nBytesLen, pBytes, frame, frameLen) )
		{
			delete [] pBytes;
			return FALSE;
		}
		delete [] pBytes;
		return TRUE;
	}
	else if (dp==Modbus)
	{
		return MakeModbusFrame((BYTE)pa.cmdID, theApp.m_pServer->m_instrumentID, (BYTE)pa.sensorID, (INT16)pa.dataID, pa.data, frame, frameLen);
	}

	return FALSE;
}

bool CProtocolManage::ParseFrame(DeviceProtocol dp, CPacket &pa, const BYTE *frame, int frameLen)
{
	if (dp==HART)
	{
		BYTE *pBytes = new BYTE[frameLen];
		int nBytesLen;
		if ( !ParseHartFrame(frame, frameLen, pBytes, nBytesLen) )
		{
			delete [] pBytes;
			return FALSE;
		}

		BYTE cmdID;
		INT16 dataID;
		if ( !ParseModbusFrame(cmdID, dataID, pa.data, pBytes, nBytesLen) )
		{
			delete [] pBytes;
			return FALSE;
		}
		pa.cmdID = static_cast<CommandID>(cmdID);
		pa.dataID = dataID;

		delete [] pBytes;
		return TRUE;
	}
	else if (dp==ScanjetHART)
	{
		BYTE *pBytes = new BYTE[frameLen];
		int nBytesLen;
		if ( !ParseScanjetHARTFrame(frame, frameLen, pBytes, nBytesLen) )
		{
			delete [] pBytes;
			return FALSE;
		}

		BYTE cmdID;
		INT16 dataID;
		if ( !ParseModbusFrame(cmdID, dataID, pa.data, pBytes, nBytesLen) )
		{
			delete [] pBytes;
			return FALSE;
		}
		pa.cmdID = static_cast<CommandID>(cmdID);
		pa.dataID = dataID;

		delete [] pBytes;
		return TRUE;
	}
	else if (dp==Modbus)
	{
		BYTE cmdID;
		INT16 dataID;

		if ( !ParseModbusFrame(cmdID, dataID, pa.data, frame, frameLen) )
			return FALSE;

		pa.cmdID = static_cast<CommandID>(cmdID);
		pa.dataID = dataID;

		return TRUE;
	}

	return FALSE;
}

bool CProtocolManage::MakeModbusFrame(BYTE cmdID, BYTE instrumentID, BYTE sensorID, INT16 dataID, const CArray<BYTE> &data, 
									BYTE *pBytes, int &nBytesLen)
{
	pBytes[0] = 0xFE;
	pBytes[4] = instrumentID;

	switch(cmdID)
	{
	case CONNECT_CMD:
		pBytes[1] = MODBUS_CONNECT2;
		nBytesLen = 7;
		break;
	case LOAD_CMD:
		pBytes[1] = MODBUS_GET;
		nBytesLen = 10;
		pBytes[6] = sensorID;
		pBytes[7] = dataID & 0xFF;
		pBytes[8] = (dataID>>8) & 0xFF;
		break;
	case SAVE_CMD:
		pBytes[1] = MODBUS_SET;
		nBytesLen = 10+data.GetSize()*sizeof(BYTE);
		pBytes[6] = sensorID;
		pBytes[7] = dataID & 0xFF;
		pBytes[8] = (dataID>>8) & 0xFF;
		memcpy(pBytes+9, data.GetData(), data.GetSize()*sizeof(BYTE));
	}

	pBytes[2] = nBytesLen & 0xFF;
	pBytes[3] = (nBytesLen>>8) & 0xFF;

	pBytes[5] = (pBytes[0]+pBytes[1]+pBytes[2]+pBytes[3]+pBytes[4]) & 0xFF;

	pBytes[nBytesLen-1] = 0;
	for (int i=0;i<nBytesLen-1;i++)
	{
		pBytes[nBytesLen-1] += pBytes[i];
	}

	return TRUE;
}

bool CProtocolManage::ParseModbusFrame(BYTE &cmdID, INT16 &dataID, CArray<BYTE> &data, const BYTE *pBytes, int nBytesLen)
{
	if (nBytesLen<7)
	{
		return FALSE;
	}

	//INT16 len = 0;
 	switch(pBytes[1])
	{
	case MODBUS_GET:
		//memcpy( &len, pBytes+2, sizeof(INT16));
		cmdID = LOAD_OK;
		memcpy( &dataID, pBytes+7, sizeof(INT16) );
		for (int i=9;i<nBytesLen-1;i++)
			data.Add(pBytes[i]);
		break;
	case MODBUS_SET:
		cmdID = SAVE_OK;
		memcpy( &dataID, pBytes+7, sizeof(INT16) );
		break;
	case MODBUS_CONNECT1:
	case MODBUS_CONNECT2:
		cmdID = CONNECT_OK;
		data.Add(pBytes[1] & 0x3F );
		data.Add(pBytes[2]);
		data.Add(pBytes[9]);
		data.Add(pBytes[10]);
		data.Add(pBytes[11]);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

bool CProtocolManage::MakeHartFrame(BYTE cmdID, int nDataLen, BYTE *pData, BYTE *pHartFrame, int &nHartFrameLen)
{
	BYTE nDelimiter;
	BYTE nCommand;
	BYTE pAddress[5];
	memcpy(pAddress, theApp.m_pServer->m_meterID, 5);

	switch(cmdID)
	{
	case CONNECT_CMD:
		nDelimiter = 0x02;
		nCommand = 0;
		break;
	case LOAD_CMD:
		nDelimiter = 0xA2;
		nCommand = 128;
		break;
	case SAVE_CMD:
		nDelimiter = 0xA2;
		nCommand = 128;
		break;
	default:
		return FALSE;
	}

	if (pHartFrame==NULL)
	{
		return FALSE;
	}

	nHartFrameLen = 0;

	// 帧头
	pHartFrame[0] = pHartFrame[1] = pHartFrame[2] = pHartFrame[3] = pHartFrame[4] = 0xff;
	nHartFrameLen += 5;

	// 定界符
	pHartFrame[nHartFrameLen] = nDelimiter;
	nHartFrameLen += 1;

	// 地址
	if (nDelimiter & 0x80)
	{
		memcpy(&pHartFrame[nHartFrameLen], pAddress, 5); //唯一地址方式
		nHartFrameLen += 5;
	}
	else
	{
		pHartFrame[nHartFrameLen] = theApp.m_pServer->m_instrumentID | 0x80; //轮询方式
		nHartFrameLen += 1;
	}

	// 扩展字节
	int nExtendLen = (nDelimiter >> 5) & 0x03;
	switch (nExtendLen)
	{
	case 0:
		break;
	case 1:
		pHartFrame[nHartFrameLen] = (nDataLen>>8) & 0xFF;
		break;
	default:
		return FALSE;
	}
	nHartFrameLen += nExtendLen;

	// 命令
	pHartFrame[nHartFrameLen] = nCommand;
	nHartFrameLen += 1;

	// 数据长度
	pHartFrame[nHartFrameLen] = nDataLen & 0xFF;
	nHartFrameLen += 1;

	// 数据
	if (pData==NULL)
	{
		return FALSE;
	}
	memcpy(&pHartFrame[nHartFrameLen], pData, nDataLen);
	nHartFrameLen += nDataLen;

	// 校验
	BYTE nCheckData = 0;
	for(int i = 5; i < nHartFrameLen; i++)
	{
		nCheckData ^= pHartFrame[i];
	}
	pHartFrame[nHartFrameLen++] = nCheckData;
	//pHartFrame[nHartFrameLen++] = 0x04;
	//pHartFrame[nHartFrameLen++] = 0xcf;
	//pHartFrame[nHartFrameLen++] = 0x5f;
	//pHartFrame[nHartFrameLen++] = 0xff;

	return TRUE;
}

bool CProtocolManage::ParseHartFrame(const BYTE *pHartFrame, int nHartFrameLen, BYTE * pGodaFrame, int &nGodaFrameLen)
{
	const BYTE *pDelimiter;
	int nAddressLen;
	const BYTE *pAddress;
	int nExtendLen;
	BYTE bExtend;
	const BYTE *pCommand;
	int nDataLen;
	const BYTE *pData;
	const BYTE *pCheckData;

	if (pHartFrame==NULL)
	{
		return FALSE;
	}

	int iter = 0;

	while (iter<nHartFrameLen && pHartFrame[iter]==0xFF)
	{
		iter++;
	}
	if (iter>=nHartFrameLen || iter<2)
	{
		return FALSE;
	}

	pDelimiter = &pHartFrame[iter];
	iter++;
	if (iter>=nHartFrameLen)
	{
		return FALSE;
	}

	pAddress = &pHartFrame[iter];
	if ((*pDelimiter) & 0x80)
	{
		nAddressLen = 5;    //唯一地址方式
		iter += 5;
	}
	else
	{
		nAddressLen = 1;    //轮询方式
		iter += 1;
	}
	if (iter>=nHartFrameLen)
	{
		return FALSE;
	}

	nExtendLen = ((*pDelimiter)>>5)&0x03;
	switch (nExtendLen)
	{
	case 0:
		bExtend = 0;
		break;
	case 1:
		bExtend = pHartFrame[iter];
		break;
	default:
		return FALSE;
	}
	iter += nExtendLen;
	if (iter>=nHartFrameLen)
	{
		return FALSE;
	}

	pCommand = &pHartFrame[iter];
	iter++;
	if (iter>=nHartFrameLen)
	{
		return FALSE;
	}

	nDataLen = bExtend*256 + pHartFrame[iter];
	iter++;
	if (iter>=nHartFrameLen)
	{
		return FALSE;
	}

	pData = &pHartFrame[iter];
	iter += nDataLen;
	if (iter>=nHartFrameLen)
	{
		return FALSE;
	}

	pCheckData = &pHartFrame[iter];
	BYTE tempCheckData = 0;
	for (const BYTE *i = pDelimiter;i<pCheckData;i++)
	{
		tempCheckData ^= *i;
	}
	if (tempCheckData!=*pCheckData)
	{
		return FALSE;
	}

	if (iter>=nHartFrameLen)
	{
		return FALSE;
	}

	if (pGodaFrame==NULL)
	{
		return FALSE;
	}
	nGodaFrameLen = nDataLen-2;
	memcpy(pGodaFrame, &pData[2], nGodaFrameLen);

	return TRUE;
}

bool CProtocolManage::MakeScanjetHARTFrame(BYTE cmdID, int nDataLen, BYTE *pData, BYTE *pHartFrame, int &nHartFrameLen)
{
	if ( !MakeHartFrame(cmdID, nDataLen, pData, pHartFrame, nHartFrameLen) )
		return FALSE;

	pHartFrame[nHartFrameLen++] = 0x04;
	pHartFrame[nHartFrameLen++] = 0xcf;
	pHartFrame[nHartFrameLen++] = 0x5f;
	pHartFrame[nHartFrameLen++] = 0xff;

	return TRUE;
}

bool CProtocolManage::ParseScanjetHARTFrame(const BYTE *pHartFrame, int nHartFrameLen, BYTE * pGodaFrame, int &nGodaFrameLen)
{
	return ParseHartFrame(pHartFrame, nHartFrameLen, pGodaFrame, nGodaFrameLen);
}
