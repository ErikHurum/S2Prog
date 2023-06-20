#pragma once
#ifndef ModbusProH
#define ModbusProH
///////////////////////////////////////////////////////////////
//
// Wago object.
//
// This module contains Wago support.
//
///////////////////////////////////////////////////////////////



class ModbusPro{
public:

	ModbusPro();
	void Initiate(void);

	void ReceiveStatus(TSNUart *Port);


	static unsigned CalcCRC(U8 *buf,int start,int cnt);
	static unsigned FastCalcCRC(U8 *puchMsg, unsigned usDataLen);

	static int Receive_Response( TSNUart *Port, U8 *received_string, int TimeOut, int FrameSpaceTime, int FrameTimeOut );
	static bool Send_Query(TSNUart *Port, U8 *query, U8 string_length );
	static int Modbus_Response(TSNUart *Port, U8 *data, U8 *query,int QueryLength, int TimeOut, int FrameSpaceTime, int FrameTimeOut);
	static int Preset_Response(TSNUart *Port, U8 *query,int QueryLength,int TimeOut, int FrameSpaceTime, int FrameTimeOut, U8 *Reply=NULL);

	static int Set_Single(TSNUart *Port, unsigned Function, unsigned SlaveAddress, unsigned Address, unsigned Value,int TimeOut, int FrameSpaceTime,int FrameTimeOut);
	static int Set_Multiple(TSNUart *Port, unsigned Function, unsigned SlaveAddress, unsigned Address, unsigned NumberOfRegisters, unsigned Size, U16 Value[],int TimeOut, int FrameSpaceTime,int FrameTimeOut);
	static int Get_Single(TSNUart *Port, unsigned Function, unsigned SlaveAddress, unsigned Address, unsigned NumberOfPoints, U8 *ReplyPtr,int TimeOut,int FrameSpaceTime,int FrameTimeOut);
	static int Get_Multiple(TSNUart *Port, unsigned Function, unsigned SlaveAddress, unsigned Address, unsigned NumberOfPoints, U8 *ReplyPtr,int TimeOut, int FrameSpaceTime,int FrameTimeOut);
	static int WriteMultipleCoils(TSNUart *Port, unsigned SlaveAddress, unsigned Channel, unsigned NumberOfRegisters, U8 Value[],int TimeOut, int FrameSpaceTime,int FrameTimeOut);
	static int WriteMultipleRegisters(TSNUart *Port, unsigned SlaveAddress, unsigned Channel, unsigned NumberOfRegisters, U8 Value[],int TimeOut, int FrameSpaceTime,int FrameTimeOut);

};
#endif


