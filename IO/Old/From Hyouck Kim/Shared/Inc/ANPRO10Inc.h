#pragma once
#ifndef __ANPRO10INC__
#define __ANPRO10INC__
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "def.h"

#if defined(S2TXU)
    #include "2410addr.h"
    #include "2410lib.h"
    #include "mmu.h"
#endif
#include "TSNConstants.h"
#include "AnsiString.h"
#include "TSNConfigstring.h"
#include "TSNStruct.h"
#include "LanguageStructs.h"
#include "TSNDefines.h"
//#include "TSNVersion.h"
#include "TSNUtilities.h"
#include "ANPRO10Const.h"
#include "TSNUart.h"
#include "ANPRO10Packets.h"
#include "TSNAsyncSender.h"
#include "TSNAsyncReceiver.h"
#ifdef ANBOOTLOADER
#include "ANPRO10UnitInfo.h"
#endif



/////////////////////////////////////////////////////
//
// From 2410Lib.c
//
/////////////////////////////////////////////////////
extern "C"{
    extern void TSN_COM_Send1(U8 c);
}

    extern short CurrentDeviceId;
    extern short CurrentDeviceAddress;
    extern bool Master;


//////////////////////////////////////////////////////
//
//  From ANPro10.cpp
//
//////////////////////////////////////////////////////
#ifdef S2TXU
extern OS_EVENT AckFlashEvent;
#endif
extern volatile bool SysInfoAvailable;

#ifdef ANFLASH
extern U8   ExternDeviceId;
extern U8   ExternDeviceAddress;
extern ProgramVersionInfo ExternProgramVersion;
extern ProgramVersionInfo ExternBootVersion;
extern U8   ExternProgType;
extern AnsiString ExternProjectId;
extern U16 ExternDataVersion;
extern volatile bool GetFlashDataCompleted;
extern volatile int   GetFlashDataOffset;

extern char FileBuf[2000*1024];
extern volatile int  BytesInBufferFileBuf;
extern volatile int  FlashSize;
extern volatile int  CurrentOffset;


#endif

extern ProgramVersionInfo MyProgramVersion;
#ifdef ANBOOTLOADER
extern ANPRO10UnitInfo UnitInformation[];
#endif

extern volatile U8 DownloadAck;
extern volatile U16 RestartAck;
extern void SendTestMessage(TSNUart *CPort, int RxAddress,int DeviceId);
extern void SendSysInfoPacket(TSNUart *CPort, int RxAddress,int DeviceId);
extern void  ReceiveSysInfoPacket(U8 *Buf);
//extern void NetworkReceive(TSNUart *CPort);
extern int ReceiveFlashPacketFromPC(TSNUart *CPort, int RxAddress, int DeviceId,U8* Buf, U32 FirstSector, U32 LastSector);

//extern void SendAckToPC(U16 Command, U8 Status, TSNUart *CPort, int RxAddress, int DeviceId);

//extern void RequestSystemInfo(TSNUart *CPort, int Address, int DeviceId);
//extern bool SendPacket(TSNUart *CPort,NetPacket &Packet);
extern int ANPRO10_AddCommand(U8* packetbuf, U8* commandbuf);
extern int AddPacket(U8* TxBuf, NetPacket &Packet);
extern int AddHeading(NetHeading *HPtr, unsigned RxAddress, unsigned RxTypeId);
extern void ANPRO10_UnpackPacket(U8 *Buf,TSNUart *Port);
extern int ANPRO10_AddPacketTail(U8* Buf, int Size, bool RequestAck);
extern int ANPRO10_AddPacketPreAmble(U8 *TX);
extern int ANPRO10_AddPacketHeading(U8* buf, unsigned RxAddress, unsigned RxTypeId);
#if defined(ANWIN) | defined(ANFLASH)
extern void ANPRO10_UDP_Receive(U8 *RxBuf);
extern void ANPRO10_Receive(TSNUart *Port, U8 *RxBuf);
#else
extern void ANPRO10_Receive(TSNUart *Port, int TimeOut, U8 *RxBuf=NULL);
#endif

extern void ANPRO10_SendRestartTXU(TSNUart *port,unsigned RxAddress, unsigned RxTypeId);

extern void ANPRO10_SendTime(bool Fast=true);
extern void ANPRO10_ReceiveTime(ANPRO10_CommandHeading *pCH);
extern void ANPRO10_SendReqSysInfo(TSNUart *Port, unsigned RxAddress, unsigned RxTypeId);
extern void ANPRO10_SendSysInfo(TSNUart *port,unsigned RxAddress, unsigned RxTypeId);
extern void ANPRO10_SendAlarmSilence(void);
extern void ANPRO10_SendBuzzerTest(char TestMode);
extern void ANPRO10_SendZerosetAll(U16 ListTypeId );
extern void ANPRO10_ReceiveZerosetAll(U16 ListTypeId );
extern volatile U8 SendFlashDataInProgress;
extern volatile TSNUart *SendFlashDataTSNUart;
extern volatile U8      SendFlashDataAddress;
extern volatile U8      SendFlashDataDeviceId;


extern bool ANPRO10_SendCommand(TSNUart *port,U8* pCommand, unsigned RxAddress, unsigned RxTypeId);
extern void ANPRO10_FlashHandler(TSNUart *port,ANPRO10_PacketHeading *pPH, U8 *Buf);
extern U8 ANPRO10_ReceiveFlashData(U8* Buf, U32 FirstSector, U32 LastSector);
extern U8 ANPRO10_ReceiveFlashData(ANPRO10_FLASH_DATA *Cmd);
extern int ANPRO10_SendFlashData(TSNUart *port,U32 Address,U32 DeviceId, U16 CmdNo, U32 FirstSector, U32 LastSector);
extern int ANPRO10_SendSettings(TSNUart *port,U32 Address,U32 DeviceId);
extern bool ANPRO10_SendEraseCommand(TSNUart *port,U32 Address,U32 DeviceId, int EraseCommand);


extern void ANPRO10_ReceiveSysInfo(U8* Buf, TSNUart* port);
extern bool ANPRO10SendCommand(TSNUart *port,U32 Address,U32 DeviceId, U16 Cmd);
extern bool ANPRO10SendCommand(TSNUart *port,U32 Address,U32 DeviceId, U16 Cmd,U8 Data);
extern int EraseFlash(U8 Command);
#ifdef ANWIN
extern void ANPRO10SetDefaultPort(TSNUart *DefPort);
#endif
extern bool ANPRO10SendUrgent(void *Command);
extern bool ANPRO10SendNormal(void *Command);
extern void ReqReceived(void);
extern void AckReceived(void);
extern void Restart(TSNUart *port,U32 Address,U32 DeviceId);
extern void ANPRO10_SendReport(int PortNum, int ReportId);
extern void ANPRO10_ReceiveReport(TSNUart *port,U32 Address,U32 DeviceId, U8* Buf);
#if defined(S2TXU) || defined(ANBOOTLOADER)
void StartUploadTask(void);
#endif

//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////
//
// From StartTXU.cpp
//
////////////////////////////////////////////////////////////////
/*
#if defined(S2TXU) && !defined(ANBOOTLOADER)
extern OS_MEMF pANPRO10IOMemPool;

#endif
*/
#endif
