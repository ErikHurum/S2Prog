#pragma once

#include "Packet.h"

enum DeviceProtocol
{
	HART,
	ScanjetHART,
	Modbus
};

class CProtocolManage
{
public:
	CProtocolManage();
	virtual ~CProtocolManage();

	bool MakeFrame(DeviceProtocol dp, const CPacket &pa, BYTE *frame, int &frameLen);
	bool ParseFrame(DeviceProtocol dp, CPacket &pa, const BYTE *frame, int frameLen);

	bool MakeHartFrame(BYTE cmdID, int nDataLen, BYTE *pData, BYTE *pHartFrame, int &nHartFrameLen);
	bool ParseHartFrame(const BYTE *pHartFrame, int nHartFrameLen, BYTE * pGodaFrame, int &nGodaFrameLen);

	bool MakeScanjetHARTFrame(BYTE cmdID, int nDataLen, BYTE *pData, BYTE *pHartFrame, int &nHartFrameLen);
	bool ParseScanjetHARTFrame(const BYTE *pHartFrame, int nHartFrameLen, BYTE * pGodaFrame, int &nGodaFrameLen);

	bool MakeModbusFrame(BYTE cmdID, BYTE instrumentID, BYTE sensorID, INT16 dataID, const CArray<BYTE> &data, 
											BYTE *pBytes, int &nBytesLen);
	bool ParseModbusFrame(BYTE &cmdID, INT16 &dataID, CArray<BYTE> &data, const BYTE *pBytes, int nBytesLen);
};
