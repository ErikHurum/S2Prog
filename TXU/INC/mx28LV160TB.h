#pragma once
//////////////////////////////////////////////////////////////////
//
//  From MX29LV160TB.cpp
//
//////////////////////////////////////////////////////////////////
#if defined(S2TXU) || defined(ANBOOTLOADER)
extern OS_RSEMA FlashSema;
extern U32 *SectorTable;
extern U32 SectorBootStart;
extern U32 SectorBootEnd;
extern U32 SectorProgStart;
extern U32 SectorProgEnd;
extern U32 SectorConfigStart;
extern U32 SectorConfigEnd;
extern U32 SectorConfigBakStart;
extern U32 SectorConfigBakEnd;
extern U32 SectorSettings1Start;
extern U32 SectorSettings1End;
extern U32 SectorSettings2Start;
extern U32 SectorSettings2End;
extern U32 SectorLocalSettings;

extern U32 FlashBaseAddress;

extern bool MX29LV_ProgFlash(U32 realAddr,U32 data);
extern bool MX29LV_EraseSector(int targetAddr);
extern bool MX29LV_EraseSectors(int FirstSector, int LastSector);
extern void MX29LV_ProtectionStatus(int targetAddr);

extern bool MX29LV_EraseChip(void);
extern bool MX29LV_CheckId(void);
extern void SetFlashSectorTable(void);
extern bool BlankCheck(int targetAddr,int targetSize);
extern bool WaitForFlash(void);
extern bool GetBlockInfoMX29LV(U32 FirstSector, U32 LastSector, U8** FlashStartPtr, U32 *Size);
extern bool CopyFromFlash(U32 FirstSector, U32 LastSector, char *TargetPtr);
extern bool ProgramMX29LV(U32 FirstSector,U32 targetAddress,U32 srcAddress,U32 targetSize);
extern bool MarkCompletedMX29LV(U32 LastSector, U32 Size);
extern U32 GetBlockAddress(U32 FirstSector);


#endif

