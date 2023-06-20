/* 
   This object is only used by the Bootloader and ANFlash.
 
*/
#ifdef ANBOOTLOADER
	#include "RTOS.h"
	#include "ANPro10Inc.h"
#else
	#include "TSNIncludes.h"
	#pragma hdrstop
	#ifdef BORLAND
		#pragma package(smart_init)
	#endif

#endif

ANPRO10UnitInfo::ANPRO10UnitInfo(void)
{
#ifndef WIN32
	pTask         = NULL;
#endif
	ErrorStatus   = 0;
	HasInfo       = false;
	SignalHasInfo = false;
	UnitID        =0;
	UnitAdress    =0;
	ProgramType   =0;	// 0 = Bootloader, 1 = Application
	UpdateTime    = 0;
	ErrorStatus   = FLASH_NO_ERROR;

}

void ANPRO10UnitInfo::Update_Unit_Info(ANPRO10_COMMAND_2001 *InfoStruct)
{
	UnitID        = InfoStruct->UnitID;
	UnitAdress    = InfoStruct->UnitAdress;
	ProgramType   = InfoStruct->ProgramType; // 0 = Bootloader, 1 = Application

	strcpy(SystemID,InfoStruct->SystemID);// #### 7 bytes for this??????
	DataVersion                 = InfoStruct->DataVersion;
	ProgramVersion.Build        = InfoStruct->ProgramVersion.Build;
	ProgramVersion.NewFunctions = InfoStruct->ProgramVersion.NewFunctions;
	ProgramVersion.PacketFormat = InfoStruct->ProgramVersion.PacketFormat;
	ProgramVersion.ProdNo       = InfoStruct->ProgramVersion.ProdNo;
	BootVersion.Build           = InfoStruct->BootVersion.Build;
	BootVersion.NewFunctions    = InfoStruct->BootVersion.NewFunctions;
	BootVersion.PacketFormat    = InfoStruct->BootVersion.PacketFormat;
	BootVersion.ProdNo          = InfoStruct->BootVersion.ProdNo;
	ProgrDate                   = InfoStruct->ProgrDate;
	UpdateTime                  = time(NULL);
	LastOSErr                   = InfoStruct->LastOSError;
	LastErrAddr                 = InfoStruct->LastErrAddress;
	FlashErrStatus              = InfoStruct->FlashErrorStatus;
	strncpy(LastOSErrTask,InfoStruct->LastOSErrorTask,TASK_NAME_LENGTH);



	HasInfo       = true;
#ifndef WIN32
	if ( pTask && SignalHasInfo ) {
		SignalHasInfo = false;
		OS_SignalEvent(SYSINFO_RECEIVED_EVENT,pTask);
	}
#endif

}


void ANPRO10UnitInfo::VersionControl(TSNUart *Port)
{
#if !defined(ANBOOTLOADER) && !defined(WIN32)
	pTask = OS_GetpCurrentTask();
	switch ( ProgramType ) {
		case 0:// Bootloader
			ErrorStatus = ANPRO10_SendFlashData(Port,UnitAdress,UnitID,CMD_SEND_FLASH_PROG,SectorProgStart,SectorProgEnd);
			if ( ErrorStatus == FLASH_NO_ERROR ) {
				ErrorStatus = ANPRO10_SendFlashData(Port,UnitAdress,UnitID,CMD_SEND_CONFIG,SectorConfigStart,SectorConfigEnd);
				if ( ErrorStatus == FLASH_NO_ERROR ) {
					ANPRO10_SendRestartTXU(Port,UnitAdress,UnitID);
				}
			}
			break;
		case 1:
			{
				if ( memcmp(&MyProgramVersion,&ProgramVersion,sizeof(ProgramVersionInfo) ) ) {
					ErrorStatus = ANPRO10_SendFlashData(Port,UnitAdress,UnitID,CMD_SEND_FLASH_PROG,SectorProgStart,SectorProgEnd);
					if ( ErrorStatus == FLASH_NO_ERROR ) {
						ErrorStatus = ANPRO10_SendFlashData(Port,UnitAdress,UnitID,CMD_SEND_CONFIG,SectorConfigStart,SectorConfigEnd);
						if ( ErrorStatus == FLASH_NO_ERROR ) {
							ANPRO10_SendRestartTXU(Port,UnitAdress,UnitID);
						}
					}
				} else if ( strncmp(SystemID,PROProjectInfo::PROProjectInfoPtr->ProjectName.c_str(),ANPRO10_ID_LENGTH-1) || DataVersion != ConfigInfoPtr->PrevConfigDataRevision ) {
					ErrorStatus = ANPRO10_SendFlashData(Port,UnitAdress,UnitID,CMD_SEND_CONFIG,SectorConfigStart,SectorConfigEnd);
					if ( ErrorStatus == FLASH_NO_ERROR ) {
						ANPRO10_SendRestartTXU(Port,UnitAdress,UnitID);
					}
				}

			}
			break;
		case 2:
			if ( strncmp(SystemID,PROProjectInfo::PROProjectInfoPtr->ProjectName.c_str(),ANPRO10_ID_LENGTH-1) || DataVersion != ConfigInfoPtr->PrevConfigDataRevision ) {
				ErrorStatus = ANPRO10_SendFlashData(Port,UnitAdress,UnitID,CMD_SEND_CONFIG,SectorConfigStart,SectorConfigEnd);
				if ( ErrorStatus == FLASH_NO_ERROR ) {
					ANPRO10_SendRestartTXU(Port,UnitAdress,UnitID);
				}
			}
			break;

	}
#endif
}

