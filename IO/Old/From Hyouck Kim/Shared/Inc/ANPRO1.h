#ifndef ANPro1_H
#define ANPro1_H
#pragma once
	extern U16 AddPacketHeading(U8* TxBuf, U8 RxAddress);
	extern U16 AddCommand(U8* TxBuf,U16 Ptr, U8 Command, U8* Data, U8  Size);
	extern U16 AddPacketTail(U8* TxBuf,U16 Size, U8 Cmd);
	//extern void UnpackPacket(U8 *Buf);
	extern bool ANPRO1Receive(TSNUart *PortPtr,int Delay,U8 Address,set<PRogramObjectBase*>&CurrenttpPCxList,bool (*UnpackFunction)(TSNUart*,U8*,int,set<PRogramObjectBase*>));

#endif
