
#ifdef ANBOOTLOADER
	#include "Rtos.h"
	#include "ANPRO10Inc.h"
	#include "2410addr.h"
	#include "2410slib.h"
	#include "mx29LV160TB.h"
  #include "FixedVariables.h"
#elif S2TXU
#include "TSNIncludes.h"
#endif

#define BLOCK_SIZE					(0x40000-sizeof(U32))

U32 FlashStartOfFreeArea = 0;
int FlashActiveSector    = 0;
int FlashActiveSectorEnd = 0;
bool FlashSystemInit     = false;

U32 GetFlashStartAddress(void)
{
	return(SectorTable[FlashActiveSector]+FlashBaseAddress+sizeof(U32));
}

U32 FlashFindFreeArea(void)
{
	OS_Use(&FlashSema);
	U32* FreePtr      = (U32*)GetFlashStartAddress();
	U32 Cnt = (BLOCK_SIZE-1) >> 2;
	// First large steps to speed the search
	while ( Cnt > 0 && FreePtr[Cnt] == BLOCK_IS_UNUSED ) Cnt--;
	Cnt++; // We alway will go one too far
	//Cnt++; // We must correct for the sector info word
	OS_Unuse(&FlashSema);
	return(Cnt*sizeof(U32));
}

bool FlashVerifyArea(U32 Size)
{
	OS_Use(&FlashSema);
	U8* StartPtr      = (U8*)GetFlashStartAddress();
	bool NoError =true;
	bool NoInfo  =true;
	for(U32 Cnt=0; NoError && Cnt < Size; Cnt++){
		 NoError = ( StartPtr[Cnt] != 0xff );
	}
	// Check for PROProjectInfo
	if ( NoError) {
		for(U32 Cnt=0; NoInfo && Cnt < Size; Cnt++){
			 if ( StartPtr[Cnt] == 'P' ){
				 if ( strcmp("PROProjectInfo",(char*)StartPtr[Cnt])){
					 NoInfo = false;
				 }
			 }
		}

	}
	OS_Unuse(&FlashSema);
	return(NoError && !NoInfo);
}


bool FlashSetActiveSector(void)
{
	OS_Use(&FlashSema);
	U32* Bank1Address = (U32*)(SectorTable[SectorSettings1Start]+FlashBaseAddress);
	U32* Bank2Address = (U32*)(SectorTable[SectorSettings2Start]+FlashBaseAddress);
	switch ( *Bank1Address ) {
		case BLOCK_IS_OK    :
			// Always select sector 1 if sector 1 flagged with OK
			FlashActiveSector    = SectorSettings1Start;
			FlashActiveSectorEnd = SectorSettings1End;
			break;
		case BLOCK_IS_UNUSED:
			switch ( *Bank2Address ) {
				case BLOCK_IS_UNUSED:
					// If both sectors are unused select sector 1
					FlashActiveSector 	 = SectorSettings1Start;
					FlashActiveSectorEnd = SectorSettings1End;
					break;
				case BLOCK_IS_OK    :
					// Select sector 2
					FlashActiveSector    = SectorSettings2Start;
					FlashActiveSectorEnd = SectorSettings2End;
					break;
				case BLOCK_IS_RESERVED:
				default:
					// Something is wrong with sector 2.
					// Use sector 1
					FlashActiveSector    = SectorSettings1Start;
					FlashActiveSectorEnd = SectorSettings1End;
					break;
			}
			break;
		case BLOCK_IS_RESERVED:
		default:
			switch ( *Bank2Address ) {
				case BLOCK_IS_UNUSED:
					// Sector 1 has error, sector 2 is unused, select sector 2
					FlashActiveSector    = SectorSettings2Start;
					FlashActiveSectorEnd = SectorSettings2End;
					break;
				case BLOCK_IS_OK    :
					// Select sector 2
					FlashActiveSector    = SectorSettings2Start;
					FlashActiveSectorEnd = SectorSettings2End;
					break;
				case BLOCK_IS_RESERVED:
				default:
					// Something is wrong with sector 1 and 2.
					// Return 0 to flg that no sector was found
					// Possible erase of boot sector EHSMark
					FlashActiveSector    = 0;
					FlashActiveSectorEnd = 0;
					break;
			}
			break;
	}
	OS_Unuse(&FlashSema);

	return(FlashActiveSector != 0);
}

bool FlashInitFileSystem(void)
{
	OS_Use(&FlashSema);
	bool Success = FlashSetActiveSector();
	if ( Success ) {
		FlashStartOfFreeArea = FlashFindFreeArea();
		if (FlashStartOfFreeArea > sizeof(U32)) {
			if (!FlashVerifyArea(FlashStartOfFreeArea)) {
				Success = MX29LV_EraseSectors(FlashActiveSector,FlashActiveSectorEnd);
				FlashStartOfFreeArea = GetFlashStartAddress();
			}
		}
		FlashSystemInit = Success;
	}
	OS_Unuse(&FlashSema);
	return(Success);
}

U32 GetFreeSize(void)
{
	OS_Use(&FlashSema);
	if ( !FlashSystemInit ) {
		FlashInitFileSystem();
	}
	U32 Size = 0;
	if ( FlashSystemInit ) {
		Size = BLOCK_SIZE - FlashStartOfFreeArea;
	}
	OS_Unuse(&FlashSema);
	return(Size);


}

U32 GetUsedSize(void)
{
	OS_Use(&FlashSema);
	if ( !FlashSystemInit ) {
		if ( FlashInitFileSystem() ) {

		}
	}
	OS_Unuse(&FlashSema);
	return(FlashStartOfFreeArea);

}

bool ProgramFlash(U32 FirstSector,U32 targetAddress,U32 srcAddress,U32 srcSize)
{
	OS_Use(&FlashSema);

	// Assume that the datablock has sufficient size
	U32 SrcEndAddress = srcAddress+srcSize;
	char *SrcEndPtr   = (char*)SrcEndAddress;
	int  Alignment    = srcSize %4;	// Align to 4 byte boundry
	if ( Alignment ) {
		Alignment = 4-Alignment;
		for ( int i=0; i < Alignment;  i++ ) {
			SrcEndPtr[i] = '\n';
		}
	}
	bool Status=ProgramMX29LV(FirstSector,targetAddress,srcAddress,srcSize);
	OS_Unuse(&FlashSema);
	return(Status);

}

bool FlashWrite(U32 SrcAddress, U32 Size)
{
	

	OS_Use(&FlashSema);
#if (WATCHDOG == 1)
    OS_SignalEvent(WD_FLASH_WRITE,&WatchDogTaskHandle);
#endif
	bool Success = FlashInitFileSystem();
#ifndef ANBOOTLOADER
	if ( Success ) {
		if ( Size < GetFreeSize() ) {
			Success = ProgramFlash(FlashActiveSector,FlashStartOfFreeArea,SrcAddress,Size);
			if ( Success ) {
				PRogramObjectBase::WriteAll = false;
			} else {
				PRogramObjectBase::WriteAll = true;
				SignalSaveSettings(FLASH_SAVE_SETTINGS);
			}
		} else {
			PRogramObjectBase::WriteAll = true;
			SignalSaveSettings(FLASH_SAVE_SETTINGS);
		}
	} else {
		PRogramObjectBase::WriteAll = true;
		SignalSaveSettings(FLASH_SAVE_SETTINGS);
	}
#endif
	OS_Unuse(&FlashSema);
	return(Success);
}


// This routine assumes that the active sector shall be changed

bool FlashWriteAll(U32 SrcAddress, U32 Size)
{
	OS_Use(&FlashSema);
#if (WATCHDOG == 1)
    OS_SignalEvent(WD_FLASH_WRITE,&WatchDogTaskHandle);
#endif

	bool Success = true;

	U32* Bank1Address = (U32*)(SectorTable[SectorSettings1Start]+FlashBaseAddress);
	U32* Bank2Address = (U32*)(SectorTable[SectorSettings2Start]+FlashBaseAddress);
	switch ( *Bank1Address ) {
		case BLOCK_IS_OK    :
			{
				switch ( *Bank2Address ) {
					case BLOCK_IS_UNUSED:
						// Sector 2 is free, write to sector 2
						Success = MX29LV_ProgFlash((U32)Bank2Address,BLOCK_IS_RESERVED);
						if ( Success ) {
							Success = ProgramFlash(SectorSettings2Start,sizeof(U32),SrcAddress,Size);
							if ( Success ) {
								Success = MX29LV_ProgFlash((U32)Bank2Address,BLOCK_IS_OK);
								if ( Success ) {
									// We had success, erase sector 1.
									Success = MX29LV_EraseSectors(SectorSettings1Start,SectorSettings1End);
									FlashActiveSector    = SectorSettings2Start;
									FlashActiveSectorEnd = SectorSettings2End;
								}
							}
						}
						break;
					case BLOCK_IS_OK    :
						// Something is not correct.
						// We always select the first sector as OK and erase
						// sector 2
						{
							// We assume that the data in sector 1 is valid and
							// erase sector 2 before writing to sector 2.
							// After writing, erasee sector 1.
							Success = MX29LV_EraseSectors(SectorSettings2Start,SectorSettings2End);
							if ( Success ) {
								Success = MX29LV_ProgFlash((U32)Bank2Address,BLOCK_IS_RESERVED);
								if ( Success ) {
									Success = ProgramFlash(SectorSettings2Start,sizeof(U32),SrcAddress,Size);
									if ( Success ) {
										Success = MX29LV_ProgFlash((U32)Bank2Address,BLOCK_IS_OK);
										if ( Success ) {
											// We had success, erase sector 1.
											Success = MX29LV_EraseSectors(SectorSettings1Start,SectorSettings1End);
											FlashActiveSector    = SectorSettings2Start;
											FlashActiveSectorEnd = SectorSettings2End;
										}
									}
								}
							}
						}
						break;
					case BLOCK_IS_RESERVED:
					default:
						// Sector 2 is not OK. We write to this sector
						// First erase sector 2
						Success = MX29LV_EraseSectors(SectorSettings2Start,SectorSettings2End);
						if ( Success ) {
							// Write to sector 2
							Success = MX29LV_ProgFlash((U32)Bank2Address,BLOCK_IS_RESERVED);
							if ( Success ) {
								Success = ProgramFlash(SectorSettings2Start,sizeof(U32),SrcAddress,Size);
								if ( Success ) {
									Success = MX29LV_ProgFlash((U32)Bank2Address,BLOCK_IS_OK);
									if ( Success ) {
										// We had success, erase sector 1.
										Success = MX29LV_EraseSectors(SectorSettings1Start,SectorSettings1End);
										FlashActiveSector    = SectorSettings2Start;
										FlashActiveSectorEnd = SectorSettings2End;
									}
								}
							}
						}
						break;
				}
			}
			break;
		case BLOCK_IS_RESERVED:
		default:
			// Sector 1 is not OK. We erase this sector
			Success = MX29LV_EraseSectors(SectorSettings1Start,SectorSettings1End);
			// Just fall through
		case BLOCK_IS_UNUSED:
			if ( Success ) {
				Success = MX29LV_ProgFlash((U32)Bank1Address,BLOCK_IS_RESERVED);
				if ( Success ) {
					Success = ProgramFlash(SectorSettings1Start,sizeof(U32),SrcAddress,Size);
					if ( Success ) {
						Success = MX29LV_ProgFlash((U32)Bank1Address,BLOCK_IS_OK);
						FlashActiveSector    = SectorSettings1Start;
						FlashActiveSectorEnd = SectorSettings1End;
					}
				}
			}
			break;
	}
#ifndef ANBOOTLOADER
	if ( Success ) {
		PRogramObjectBase::WriteAll = false;
	} else {
		PRogramObjectBase::WriteAll = true;
		SignalSaveSettings(FLASH_SAVE_SETTINGS);
	}
#endif
	OS_Unuse(&FlashSema);
	return(Success);
}

bool FlashRead(char *Destination, int &FlashSize)
{
	OS_Use(&FlashSema);

	bool Success = FlashInitFileSystem();

	if ( Success ) {
		int FSize = FlashStartOfFreeArea-sizeof(U32);
		if ( FSize ) {
			FlashSize = FSize;
			char *Src = (char*)GetFlashStartAddress();
			memcpy(Destination,Src,FlashSize);
		} else {
			Success = false;
		}
	}
	OS_Unuse(&FlashSema);
	return(Success);
}

int SaveConfig(U32 SrcAddress, U32 Size)
{
	int ErrorStatus     = FLASH_NO_ERROR;
	U8  *ConfigStartPtr = NULL;
	U32 ConfigSize      = 0;
	U32 SConfigStart    = 0;
	U32 SConfigEnd      = 0;
	U32 SConfigBakStart = 0;
	U32 SConfigBakEnd   = 0;
	bool FlashOK        = false;
	// First, check if it is the main or backup which exist
	if ( GetBlockInfoMX29LV(SectorConfigStart,SectorConfigEnd, &ConfigStartPtr, &ConfigSize ) ) {
		SConfigStart    = SectorConfigStart;
		SConfigEnd      = SectorConfigEnd;
		SConfigBakStart = SectorConfigBakStart;
		SConfigBakEnd   = SectorConfigBakEnd;
		FlashOK         = true;
	} else if ( GetBlockInfoMX29LV(SectorConfigBakStart,SectorConfigBakEnd, &ConfigStartPtr, &ConfigSize ) ) {
		SConfigStart    = SectorConfigBakStart;
		SConfigEnd      = SectorConfigBakEnd;
		SConfigBakStart = SectorConfigStart;
		SConfigBakEnd   = SectorConfigEnd;
		FlashOK         = true;
	} else {
		// Should never get here!!!!
	}
	//FlashOK = false; // EHSMarkva_list
	if ( FlashOK ) {
		// Always erase what we consider for backup
		if ( !MX29LV_EraseSectors(SConfigBakStart,SConfigBakEnd) ) {
			ErrorStatus = FLASH_ERASE_FAILURE;
		} else if ( !ProgramMX29LV(SConfigBakStart,0,SrcAddress,Size) ) {
			ErrorStatus = FLASH_PROGRAM_FAILURE;
		} else if ( !MarkCompletedMX29LV(SConfigBakEnd,Size) ) {
			ErrorStatus = FLASH_MARK_COMPLETE_FAILURE;
		} if ( !MX29LV_EraseSectors(SConfigStart,SConfigEnd) ) {
			ErrorStatus = FLASH_ERASE_FAILURE;
		}else{
			SectorConfigStart    = SConfigBakStart;
			SectorConfigEnd      = SConfigBakEnd;
			SectorConfigBakStart = SConfigStart;
			SectorConfigBakEnd   = SConfigEnd;
		}
	}
	return ErrorStatus;
}

