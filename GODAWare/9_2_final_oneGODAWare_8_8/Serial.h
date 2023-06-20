#pragma once

#include "SerialPort.h"

class CSerial
{
public:
	CSerial(void);
	~CSerial(void);

	int Read(BYTE * bytes, int bytesToRead);
	int Write(const BYTE * bytes, int bytesToWrite);
	int OVERTIME; // ∫¡√Î

	CSerialPort m_sp;
};
